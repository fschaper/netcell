/**
 *  \file
 *  Copyright (C) 2008-2010 Jedox AG, Freiburg i.Br., Germany
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
 *  <a href="http://www.jedox.com/license_worksheetserver.txt">
 *    http://www.jedox.com/license_worksheetserver.txt
 *  </a>
 *
 *  If you are developing and distributing open source applications under the
 *  GPL License, then you are free to use Worksheetserver under the GPL License.
 *  For OEMs, ISVs, and VARs who distribute Worksheetserver with their products,
 *  and do not license and distribute their source code under the GPL, Jedox provides
 *  a flexible OEM Commercial License.
 *
 *  \author
 *  Frieder Hofmann <frieder.hofmann@jedox.com>
 */

#include "precompiled_header.hpp"
#include "wss/i_dependency.hpp"
#include "wss/named_formula_reference.hpp"
#include "wss/workbook.hpp"
#include "wss/locale.hpp"
#include "named_formula_manager.hpp"
#include "named_formula_wrapper.hpp"
#include "named_formula.hpp"
#include "named_formula_utility.hpp"
#include "cell.hpp"
#include "free_formula_impl.hpp"

named_formula_reference::named_formula_reference( const shared_dependency_type& dependent, const shared_worksheet_type& ws, const utf8_ci_string& name, const named_formula_scope::type scope, const shared_named_formula_wrapper_type& nf )
    : m_target_worksheet( ws )
    , m_name( name )
    , m_dependent( dependent )
    , m_nf( nf )
    , unload_called( false )
    , m_scope( scope )
    , m_is_redirected( false )
{
#ifdef _DEBUG
    ++m_counter;
#endif // _DEBUG
}

named_formula_reference::~named_formula_reference()
{
    if ( !unload_called && is_valid() ) {
        shared_dependency_type d = m_dependent.lock();
        if ( d ) {
            m_nf->named_formula()->unregister_reference( d );
        }
    }
#ifdef _DEBUG
    --m_counter;
#endif // _DEBUG
}

shared_reference_type named_formula_reference::create( const shared_dependency_type& dependent, const shared_worksheet_type& ws, const utf8_ci_string& name, const named_formula_scope::type scope, const shared_named_formula_wrapper_type& nf )
{
    //this block is just for testing!
#ifdef _DEBUG
    if ( dependent->type() == i_dependency::named_formula_type ) {
        std::string find_out_why( "" );
    }
#endif // _DEBUG
    return boost::make_shared<named_formula_reference>( dependent, ws, name, scope, nf );
}

i_dependency_reference::reference_type named_formula_reference::type() const
{
    return i_dependency_reference::named_formula_reference;
}

const utf8_ci_string named_formula_reference::name() const
{
    return is_valid() ? m_nf->named_formula()->name() : m_name;
}

const std::string named_formula_reference::formula( const locale& l ) const
{
    return is_valid() ? m_nf->named_formula( m_dependent.lock() )->formula( l ) : convert_utf8_ci( m_name );
}

const weak_dependency_type& named_formula_reference::dependent()
{
    return m_dependent;
}

void named_formula_reference::unload()
{
    if ( is_valid() ) {
        shared_dependency_type d = m_dependent.lock();
        if ( d ) {
            m_nf->named_formula()->unregister_reference( d );
        }
    }
    m_dependent.reset();
    unload_called = true;
}

const bool named_formula_reference::is_valid() const
{
    return m_nf && m_nf->is_valid();
}

const bool named_formula_reference::better_fit( const shared_named_formula_wrapper_type& other ) const
{
    if ( m_scope == named_formula_scope::none || m_scope == named_formula_scope::worksheet_scope ) {
        if ( other && other->is_valid() && other->named_formula() ) {
            shared_dependency_type d = m_dependent.lock();
            if ( d ) {
                shared_worksheet_type parent_ws = d->worksheet().lock();
                shared_worksheet_type ws = other->named_formula()->worksheet().lock();
                if ( parent_ws && ws ) {
                    return ws == parent_ws;
                }
            }
        }
    }
    return false;
}

void named_formula_reference::update_wrapper( const shared_named_formula_wrapper_type& other )
{
    assert( "shared_named_formula_wrapper_type is not initialized!" && other->is_valid() );
    m_nf = other;
    shared_dependency_type d = m_dependent.lock();
    if ( d ) {
        m_nf->named_formula()->register_reference( d );
        d->internal_flag_dirty();
        if ( d->type() == i_dependency::cell_type ) {
            boost::shared_static_cast<cell>( d )->trigger_commit_kernel_change();
        } else if ( d->type() == i_dependency::free_formula_type ) {
            boost::shared_static_cast<free_formula_impl>( d )->trigger_register_dependent();
        } else if ( d->type() == i_dependency::named_formula_type ) {
            boost::shared_static_cast< ::named_formula >( d )->trigger_register_dependent();
        }
    }
}

weak_worksheet_type named_formula_reference::worksheet() const
{
    return m_target_worksheet;
}

weak_worksheet_type named_formula_reference::nf_worksheet() const
{
    return m_nf->named_formula()->worksheet();
}

const named_formula_scope::type named_formula_reference::scope() const
{
    return m_scope;
}

bool named_formula_reference::has_relative_references() const
{
    if ( is_valid() ) {
        return m_nf->named_formula()->is_relative();
    }
    return false;
}

shared_dependency_type named_formula_reference::precedent() const
{
    shared_dependency_type d( m_dependent.lock() );
    if ( d && d->type() == i_dependency::named_formula_wrapper_type ) {
        if ( m_nf->named_formula() == boost::shared_static_cast<named_formula_dependency_wrapper>( d )->parent_nf() ) {
            return d;
        }
    }
    return m_nf->named_formula( d );
}

shared_dependency_type named_formula_reference::named_formula() const
{
    assert( "uninitialized named_formula!!" && m_nf->named_formula().get() );
    return m_nf->named_formula( m_dependent.lock() );
}

shared_dependency_type named_formula_reference::real_nf() const
{
    assert( "uninitialized named_formula!!" && m_nf->named_formula().get() );
    return m_nf->named_formula();
}

void named_formula_reference::update_position( const geometry::point& distance )
{
    if ( is_valid() ) {
        assert( "uninitialized named_formula!!" && m_nf->named_formula().get() );
        return m_nf->named_formula()->update_position( m_dependent.lock(), distance );
    }
}

bool named_formula_reference::nf_is_workbook_scope() const
{
    return is_valid() ? ( m_nf->named_formula()->scope() == named_formula_scope::workbook_scope ) : false;
}

const shared_named_formula_wrapper_type& named_formula_reference::internal_access() const
{
    return m_nf;
}

#ifdef _DEBUG
size_t named_formula_reference::m_counter = 0;
#endif // _DEBUG
