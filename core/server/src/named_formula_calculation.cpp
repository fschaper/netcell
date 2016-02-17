/**
 *  \file
 *  Copyright (C) 2006-2010 Jedox AG
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License (Version 2) as published
 *  by the Free Software Foundation at http://www.gnu.org/copyleft/gpl.html.
 *
 *  This program is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 *  more details.
 *
 *  You should have received a copy of the GNU General Public License along with
 *  this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 *  Place, Suite 330, Boston, MA 02111-1307 USA
 *
 *  You may obtain a copy of the License at
 *
 *  <a href="http://www.jedox.com/license_palo_bi_suite.txt">
 *    http://www.jedox.com/license_palo_bi_suite.txt
 *  </a>
 *
 *  If you are developing and distributing open source applications under the
 *  GPL License, then you are free to use Worksheetserver under the GPL License.
 *  For OEMs, ISVs, and VARs who distribute Worksheetserver with their products,
 *  and do not license and distribute their source code under the GPL, Jedox provides
 *  a flexible OEM Commercial License.
 *
 *  \author
 *  Florian Schaper <florian.schaper@jedox.com>
 */

#include "precompiled_header.hpp"
#include "wss/named_formula_calculation.hpp"
#include "wss/interpreter_context.hpp"
#include "wss/worksheet.hpp"
#include "wss/calculation_setting.hpp"
#include "stack_calculation.hpp"
#include "named_formula_kernel.hpp"
#include "wss/cyclic_dependency_set.hpp"
#include "wss/formula.hpp"

named_formula_calculation::named_formula_calculation( const named_formula_calculation& other )
    : abstract_calculation( other )
    , m_kernel( other.m_kernel ) {}

named_formula_calculation::named_formula_calculation( calculation_context& cc, const shared_named_formula_kernel_type& kernel, const shared_dependency_type& formula_container, const ::formula& f, const variant& old_value, long token_id )
    : abstract_calculation( cc, formula_container, f, old_value, token_id )
    , m_kernel( kernel )
{}

named_formula_calculation::~named_formula_calculation()
{
    // (fschaper) we only update the value of the kernel in case
    // a calculation was actually performed on the object.
    if ( m_calculation_performed ) {
        if ( m_named_formula ) {
            m_kernel->update_value( m_cc, m_cached_value, m_token, m_named_formula );
        } else {
            m_kernel->update_value( m_cc, m_cached_value, m_token );
        }
    }
}

void named_formula_calculation::operator()( const shared_dependency_type& named_formula, long different_token_id )
{
    if ( !m_formula_container || !m_formula ) {
        return;
    }
    if ( named_formula_initiator( named_formula, different_token_id ) ) {
        return operator_with_different_initiator( named_formula );
    }

    // (fschaper) calculate the formula in case it is marked as dirty or
    // in volatile state.
    interpreter_context ic( m_formula_container, *this, m_cc );
    if ( m_cc.perform_stackwalk() ) {
        // (fschaper) order all precedents on a calculation stack and calculate
        // them in the order of dependency. since this need be done only
        // for the issuing cell (and because of possible cycles in the
        // calculation) we turn the stackwalk off for this calculation round.
        m_cc.perform_stackwalk( false );
        stack_based_calculation( m_formula_container, m_cc, ic );
        m_cc.perform_stackwalk( true );
    } else {
        m_cached_value = m_formula->calculate( ic );
    }
    if ( m_cc.cache().cyclic_dependencies().check_if_cyclic( m_formula_container ) ) {
        m_kernel->update_value( m_cc, m_cached_value, m_token );
    }
    if ( m_kernel->is_volatile() && !m_cc.cache().retrieve( *m_formula_container ) ) {
        m_cc.cache().store( *m_formula_container, m_cached_value );
    }
    m_calculation_performed = true;
}

void named_formula_calculation::operator()()
{
    if ( !m_formula_container || !m_formula ) {
        return;
    }


    // (fschaper) calculate the formula in case it is marked as dirty or
    // in volatile state.
    interpreter_context ic( m_formula_container, *this, m_cc, m_formula_container );
    if ( m_cc.perform_stackwalk() ) {
        // (fschaper) order all precedents on a calculation stack and calculate
        // them in the order of dependency. since this need be done only
        // for the issuing cell (and because of possible cycles in the
        // calculation) we turn the stackwalk off for this calculation round.
        m_cc.perform_stackwalk( false );
        stack_based_calculation( m_formula_container, m_cc, ic );
        m_cc.perform_stackwalk( true );
    } else {
        m_cached_value = m_formula->calculate( ic );
    }
    if ( m_cc.cache().cyclic_dependencies().check_if_cyclic( m_formula_container ) ) {
        m_kernel->update_value( m_cc, m_cached_value, m_token );
    }
    m_calculation_performed = true;
}


variant named_formula_calculation::operator()( interpreter_context& ic )
{
    if ( has_named_formula_initiator() ) {
        return operator_with_different_initiator( ic );
    }
    if ( ic.context().cache().cyclic_dependencies().check_if_cyclic( m_formula_container ) ) {
        const variant tmp_val = m_formula->calculate( ic );
        if ( tmp_val.is_error() || check_minimum_change( tmp_val ) ) {
            m_cached_value = tmp_val;
            m_kernel->update_value( m_cc, m_cached_value, m_token );
        }

    } else {
        // (fschaper) calculate the formula in case it is marked as dirty or
        // in volatile state.
        // if ( m_kernel->is_dirty_or_uncached_volatile( m_cc ) ) {
        assert( "perform stackwalk is true, this is a problem deep down in the calculation engine" && !m_cc.perform_stackwalk() );

        m_cached_value = m_formula->calculate( ic );
        // (fhofmann) add the computed value to the calculation cache if the kernel is volatile
        // but only if no one beat us to it!
        if ( m_kernel->is_volatile(  ) && !m_cc.cache().retrieve( *m_formula_container ) ) {
            m_cc.cache().store( *m_formula_container, m_cached_value );
        }

        m_calculation_performed = true;
    }
    return m_cached_value;
}

bool named_formula_calculation::named_formula_initiator( const shared_dependency_type& named_formula, long different_token_id )
{
    if ( named_formula && named_formula != m_formula_container ) {
        m_named_formula = named_formula;
        m_token = different_token_id;
        return true;
    }
    return false;
}

void named_formula_calculation::operator_with_different_initiator( const shared_dependency_type& named_formula )
{
    // (fschaper) calculate the formula in case it is marked as dirty or
    // in volatile state.
    interpreter_context ic( m_formula_container, *this, m_cc, named_formula );
    if ( m_cc.perform_stackwalk() ) {
        // (fschaper) order all precedents on a calculation stack and calculate
        // them in the order of dependency. since this need be done only
        // for the issuing cell (and because of possible cycles in the
        // calculation) we turn the stackwalk off for this calculation round.
        m_cc.perform_stackwalk( false );
        stack_based_calculation( named_formula, m_cc, ic );
        m_cc.perform_stackwalk( true );
    } else {
        if ( m_cc.cache().cyclic_dependencies().check_if_cyclic( named_formula_initiator() ) || m_cc.cache().cyclic_dependencies().check_if_cyclic(  m_formula_container ) ) {
            const variant tmp_val = m_formula->calculate( ic );
            if ( check_minimum_change( tmp_val ) ) {
                m_cached_value = tmp_val;
                m_kernel->update_value( m_cc, m_cached_value, m_token, m_named_formula );
            }

        } else {
            m_cached_value = m_formula->calculate( ic );
        }
    }
    if ( m_kernel->is_volatile( m_formula_container ) && ! m_cc.cache().retrieve( *m_formula_container ) ) {
        m_cc.cache().store( *m_formula_container, m_cached_value );
    }
    m_calculation_performed = true;
}

variant named_formula_calculation::operator_with_different_initiator( interpreter_context& ic )
{
    if ( ic.context().cache().cyclic_dependencies().check_if_cyclic( named_formula_initiator() ) || ic.context().cache().cyclic_dependencies().check_if_cyclic(  m_formula_container ) ) {
        const variant tmp_val = m_formula->calculate( ic );
        if ( check_minimum_change( tmp_val ) ) {
            m_cached_value = tmp_val;
            m_kernel->update_value( m_cc, m_cached_value, m_token, m_named_formula );
        }

    } else {
        // (fschaper) calculate the formula in case it is marked as dirty or
        // in volatile state.
        assert( "perform stackwalk is true, this is a problem deep down in the calculation engine" && !m_cc.perform_stackwalk() );

        m_cached_value = m_formula->calculate( ic );
        // (fhofmann) add the computed value to the calculation cache if the kernel is volatile
        // but only if no one beat us to it!
        if ( m_kernel->is_volatile( m_formula_container ) && !m_cc.cache().retrieve( *m_formula_container )  ) {
            m_cc.cache().store( *m_formula_container, m_cached_value );
        }

        m_calculation_performed = true;
    }
    return m_cached_value;
}
