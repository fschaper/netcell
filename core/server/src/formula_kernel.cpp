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
#include "formula_kernel.hpp"
#include "wss/calculation_context.hpp"
#include "wss/interpreter_context.hpp"
#include "wss/worksheet.hpp"
#include "cell.hpp"
#include "wss/reference_operation.hpp"
#include "wss/interpreter_context.hpp"
#include "wss/scoped_selection_state.hpp"

/*!
 * \brief
 * careful, this will generate a lot of output!
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
//#define LOG_TRACE_DEPENDENCIES 1

#if defined(LOG_TRACE_DEPENDENCIES) && defined(_DEBUG) && !defined(LOG_CORE_TRACE_DEPENDENCIES)
#   include "debug_logging_helper.hpp"
#   include "wss/a1conversion.hpp"
#   include "core_logging.hpp"
#   define LOG_CORE_TRACE_DEPENDENCIES(message) LOG_CORE_TRACE(message)
#else
#   define LOG_CORE_TRACE_DEPENDENCIES(message)
#endif // LOG_TRACE_DEPENDENCIES


shared_formula_kernel_type formula_kernel::create( const shared_dependency_type& container, ast_formula& ast, const referencetable_type& reference_table )
{
    return boost::make_shared<formula_kernel>( container, boost::ref( ast ), reference_table );
}

shared_formula_kernel_type formula_kernel::create( const shared_dependency_type& container, const formula_kernel& other, const geometry::point& distance, bool is_rewrite_to_clone_sheet, bool use_copy_move, const sheet_range& source_range, const referencetable_type& reference_table )
{
    return boost::make_shared<formula_kernel>( container, other, distance, is_rewrite_to_clone_sheet, use_copy_move, source_range, reference_table );
}

formula_kernel::formula_kernel( const shared_dependency_type& container, ast_formula& ast, const referencetable_type& references )
    : m_container( container )
    , m_formula( ast, container, ( *container ).position(), references )
    , m_volatile_count( 0 )
    , m_is_dirty( true )
    , m_unload_triggered( false )
{
    shared_worksheet_type ws = m_container->worksheet().lock();
    ws->variable().merge( m_formula.variable() );
}

formula_kernel::formula_kernel( const shared_dependency_type& parent, const formula_kernel& other, const geometry::point& distance, bool is_rewrite_to_clone_sheet, bool use_copy_move, const sheet_range& source_range, const referencetable_type& references )
    : m_container( parent )
    , m_formula( other.m_formula, m_container, distance, is_rewrite_to_clone_sheet, use_copy_move, source_range, references )
    , m_volatile_count( 0 )
    , m_is_dirty( true )
    , m_unload_triggered( false )
{
    shared_worksheet_type ws = m_container->worksheet().lock();
    ws->variable().merge( m_formula.variable() );
}

formula_kernel::~formula_kernel()
{
    if ( !m_unload_triggered ) {
        unload();
    }
}

void formula_kernel::unload()
{
    if ( !m_unload_triggered ) {
        // do this only once.
        m_unload_triggered = true;

        LOG_CORE_TRACE_DEPENDENCIES( std::string( "unload called on formula_kernel of: \"" ) + debug_logging_helper::get_identifier( m_container ) + "\"" );

        // (fschaper) unregister from all precedents. we don't care about the volatile count here.
        // there can be a problem with the order of reference deletion:
        // f.ex. named formulas might point to cells that have already been deleted by a "remove workbook" operation.
        // this references will now be invalid. this is perfectly fine we just have to tell our reference operation
        // to swallow any exception that would normally be generated in that case and to proceed with the next reference.
        //(fhofmann) check if we want to unregister (in case of a named formula kernel we don't want to do this here
        reference_operation( m_container, m_formula.precedents(), boost::bind( &i_dependency::unregister_dependent, _1, m_container ), true );

        // in case the kernel is flagged volatile, lower the volatile count for all dependents.
        if ( is_volatile() ) {
            // will lower the volatile count for all dependents on the current
            // container but the current object.
            m_container->lower_volatile_count();
        }

        // (fschaper) remove all registered variables from the worksheet that are connected
        // to this formula (lower the reference count).
        shared_worksheet_type ws = m_container->worksheet().lock();
        if ( ws ) {
            ws->variable().remove( m_formula.variable() );
        }

        //check for correct volatile book keeping.
        // assert( "not all volatile references were removed upon destruction!" && ( !m_volatile_count ) );
    }
}

void formula_kernel::connect_precedents()
{
    if ( m_formula.has_precedents() ) {
        reference_operation( m_container, m_formula.precedents(), boost::bind( &i_dependency::register_dependent, _1, m_container ) );
    }
}

bool formula_kernel::has_precedents() const
{
    return m_formula.has_precedents();
}

referencetable_type formula_kernel::precedents() const
{
    return m_formula.precedents();
}

std::string formula_kernel::formula( const locale& l ) const
{
    return m_formula.pretty_print( l );
}

variant formula_kernel::value() const
{
    return m_cached_value;
}

formula_calculation formula_kernel::delayed_calculation( calculation_context& cc )
{
    return formula_calculation( cc, shared_from_this(), m_container, m_formula, m_cached_value, ++m_update_token );
}

optional_variant_type formula_kernel::fetch_cached_volatile( calculation_context& cc ) const
{
    return cc.cache().retrieve( *m_container );
}

//bool formula_kernel::is_dirty() const

//bool formula_kernel::is_volatile() const


//unsigned long formula_kernel::volatile_count() const


unsigned long formula_kernel::volatile_count_without_formula() const
{
    return m_volatile_count;
}

void formula_kernel::flag_dirty()
{
    LOG_CORE_TRACE_DEPENDENCIES( std::string( "flag dirty on : \"" ) + debug_logging_helper::get_identifier( m_container ) );
    m_is_dirty = true;
}

void formula_kernel::internal_raise_volatile_count()
{
    ++m_volatile_count;
    LOG_CORE_TRACE_DEPENDENCIES( std::string( "raise volatile count of: \"" ) + debug_logging_helper::get_identifier( m_container )
                                 + std::string( "\" to: \"" ) + boost::lexical_cast<std::string>( m_volatile_count ) + "\"" );
}

void formula_kernel::internal_lower_volatile_count()
{
    LOG_CORE_TRACE_DEPENDENCIES( std::string( "lower volatile count of: \"" ) + debug_logging_helper::get_identifier( m_container )
                                 + std::string( "\" current count is: \"" ) + boost::lexical_cast<std::string>( m_volatile_count ) + "\"" );
    assert( "tried to lower volatile count below zero!" && m_volatile_count > 0 );
    --m_volatile_count;
    // when the volatile count reaches zero we still need to calculate
    // everything one more time
    if ( m_volatile_count == 0 ) {
        flag_dirty();
    }
}

optional_sheet_range_type formula_kernel::coverage() const
{
    return m_formula.coverage();
}

void formula_kernel::update_value( calculation_context& cc, const variant& v, long token_id )
{
    // only update the cached value if the passed token id is still valid.
    if ( token_id == m_update_token ) {
        if ( cc.cache().cyclic_dependencies().check_if_cyclic( m_container ) ) {
            if ( abstract_calculation::check_minimum_change( cc, m_cached_value, v ) ) {
                m_cached_value = v;
                if ( !is_volatile() ) {
                    m_container->flag_dirty();
                }
                if ( cc.cache().increment_and_check_iteration_count( *m_container, m_cached_value, cc.settings().maximum_iterations() + 1 ) ) {
                    cc.cache().store_cyclic( *m_container, m_cached_value );
                }
                cc.cache().cyclic_dependencies().value_changed();
                m_is_dirty = true;
            }
        } else {
            m_cached_value = v;
            if ( !is_volatile() ) {
                m_container->flag_dirty();
            }

            m_is_dirty = false;
        }
    }
}

