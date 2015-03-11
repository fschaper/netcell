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
#include "named_formula_kernel.hpp"
#include "wss/reference_operation.hpp"
#include "wss/calculation_context.hpp"
#include "wss/workbook.hpp"
#include "wss/worksheet.hpp"
#include "wss/calculation.hpp"
#include "wss/opcode.hpp"
#include "named_formula_dependency_wrapper.hpp"

//#define LOG_TRACE_NF_KERNEL 1

#if defined(LOG_TRACE_NF_KERNEL) && defined(_DEBUG) && !defined(LOG_CORE_TRACE_NF_KERNEL)
#   include "debug_logging_helper.hpp"
#   include "core_logging.hpp"
#   define LOG_CORE_TRACE_NF_KERNEL(message) LOG_CORE_TRACE(message)
#else
#   define LOG_CORE_TRACE_NF_KERNEL(message)
#endif // LOG_TRACE_DEPENDENCIES

template<class ptr_type>
inline void check_if_named_formula_dependency_wrapper_type( const ptr_type d )
{
#ifdef _DEBUG
    assert( "only dependencies of type i_dependency::named_formula_wrapper_type can be used here!"
            && d->type() == i_dependency::named_formula_wrapper_type );
#endif // _DEBUG
}

named_formula_kernel::named_formula_kernel( const shared_dependency_type& container, ast_formula& ast, const referencetable_type& references )
    : m_container( container )
    , m_formula( ast, container, ( *container ).position(), references )
    , m_volatile_count( 0 )
    , m_unload_triggered( false )
    , m_is_dirty( true )
{
    LOG_CORE_TRACE_NF_KERNEL( "creating new nf kernel for " + debug_logging_helper::get_identifier( m_container ) );
    register_variables();
}

named_formula_kernel::named_formula_kernel( const shared_dependency_type& parent, const named_formula_kernel& other, const geometry::point& distance, bool is_rewrite_to_clone_sheet )
    : m_container( parent )
    , m_formula( other.m_formula, m_container, distance, is_rewrite_to_clone_sheet )
    , m_volatile_count( 0 )
    , m_unload_triggered( false )
    , m_is_dirty( true )
{
    LOG_CORE_TRACE_NF_KERNEL( "copy_constructing nf kernel for " + debug_logging_helper::get_identifier( m_container ) );
    register_variables();
}

named_formula_kernel::named_formula_kernel( const shared_dependency_type& parent, const named_formula_kernel& other, const geometry::point& distance, bool is_rewrite_to_clone_sheet, bool use_copy_move, const sheet_range& source_range, const referencetable_type& references )
    : m_container( parent )
    , m_formula( other.m_formula, m_container, distance, is_rewrite_to_clone_sheet, use_copy_move, source_range, references )
    , m_volatile_count( 0 )
    , m_unload_triggered( false )
    , m_is_dirty( true )
{
    LOG_CORE_TRACE_NF_KERNEL( "copy_constructing nf kernel for " + debug_logging_helper::get_identifier( m_container ) );
    register_variables();;
}

named_formula_kernel::~named_formula_kernel()
{
    LOG_CORE_TRACE_NF_KERNEL( "destroying nf kernel for " + debug_logging_helper::get_identifier( m_container ) );
#ifdef _DEBUG
    assert( "unload should be triggered first! " && m_unload_triggered );
#endif // _DEBUG
}

void named_formula_kernel::unload( const std::list<shared_dependency_type>& m )
{
    if ( ! m_unload_triggered ) {
        // do this only once.
        m_unload_triggered = true;
        LOG_CORE_TRACE_NF_KERNEL( "unload called on nf kernel for " + debug_logging_helper::get_identifier( m_container ) );
        if ( m_formula.has_precedents() ) {
            disconnect_precedents();
            for ( std::list<shared_dependency_type>::const_iterator it = m.begin(), end_it = m.end(); it != end_it; ++it ) {
                const referencetable_type precedent_set( m_formula.precedents( *it ) );
                if ( !precedent_set.empty() ) {
                    reference_operation( *it, precedent_set, boost::bind( &i_dependency::unregister_dependent, _1, *it ), true );
                    if ( is_volatile( *it ) ) {
                        // will lower the volatile count for all dependents on the current
                        // container but the current object.
                        ( *it )->lower_volatile_count();
                        ( *it )->internal_lower_volatile_count();
                    }
                }
                m_formula.remove_position( it->get() );
            }

        }
        // (fschaper) remove all registered variables from the worksheet that are connected
        // to this formula (lower the reference count).
        unregister_variables();
        m_container.reset();
    }
}

void named_formula_kernel::connect_precedents()
{
    LOG_CORE_TRACE_NF_KERNEL( "connect precedents of nf kernel to " + debug_logging_helper::get_identifier( m_container ) );
    if ( m_formula.has_precedents() ) {
        reference_operation( m_container, m_formula.precedents(), boost::bind( &i_dependency::register_dependent, _1, m_container ) );
    }
}

void named_formula_kernel::disconnect_precedents()
{
    LOG_CORE_TRACE_NF_KERNEL( "connect precedents of nf kernel to " + debug_logging_helper::get_identifier( m_container ) );
    reference_operation( m_container, m_formula.precedents(), boost::bind( &i_dependency::unregister_dependent, _1, m_container ) );
}

void named_formula_kernel::connect_precedents( const shared_dependency_type& d )
{
    LOG_CORE_TRACE_NF_KERNEL( "connect precedents of the kernel of \"" + debug_logging_helper::get_identifier( m_container ) + "\" to " + debug_logging_helper::get_identifier( d ) );
    if ( m_formula.has_precedents() ) {
        // in this case we can have invalid references that we just want to skip - because the formula can have invalid
        // references and we don't need to connect to them
        reference_operation( d, m_formula.precedents( d ), boost::bind( &i_dependency::register_dependent, _1, d ), true );
    }
}

void named_formula_kernel::disconnect_precedents( const shared_dependency_type& d )
{
    if ( m_formula.has_precedents() ) {
        // in this case we can have invalid references that we just want to skip - because the formula can have invalid
        // references and we don't need to connect to them
        reference_operation( d, m_formula.precedents( d ), boost::bind( &i_dependency::unregister_dependent, _1, d ), true );
        if ( is_volatile( d ) ) {
            // will lower the volatile count for all dependents on the current
            // container but the current object.
            d->lower_volatile_count();
        }
    }
}

bool named_formula_kernel::has_precedents() const
{
    return m_formula.has_precedents();
}

referencetable_type named_formula_kernel::precedents() const
{
    return m_formula.precedents();
}

referencetable_type named_formula_kernel::precedents( const shared_dependency_type& d ) const
{
    return m_formula.precedents( d );
}

std::string named_formula_kernel::formula( const locale& l ) const
{
    return m_formula.pretty_print( l );
}

std::string named_formula_kernel::formula_without_sheet_references( const locale& l ) const
{
    return m_formula.pretty_print( l, false );
}

std::string named_formula_kernel::formula( const locale& l, const shared_dependency_type& d ) const
{
    return m_formula.pretty_print( l, d );
}

std::string named_formula_kernel::formula_without_sheet_references( const locale& l, const shared_dependency_type& d ) const
{
    return m_formula.pretty_print( l, d, false );
}

variant named_formula_kernel::value() const
{
    return m_cached_value;
}

named_formula_calculation named_formula_kernel::delayed_calculation( calculation_context& cc )
{
    return named_formula_calculation( cc, shared_from_this(), m_container, m_formula, m_cached_value, ++m_update_token );
}

optional_variant_type named_formula_kernel::fetch_cached_volatile( calculation_context& cc, const shared_dependency_type& d ) const
{
    return cc.cache().retrieve( *d );
}

bool named_formula_kernel::is_volatile() const
{
    return m_formula.is_volatile() || volatile_count() > 0;
}

bool named_formula_kernel::is_volatile( const shared_dependency_type& d ) const
{
    return m_formula.is_volatile() || volatile_count( d ) > 0;
}

unsigned long named_formula_kernel::volatile_count( const shared_dependency_type& d ) const
{
    return m_formula.is_relative() ? m_formula.volatile_count( d ) : volatile_count();
}

unsigned long named_formula_kernel::volatile_count_without_formula( const shared_dependency_type& d ) const
{
    return m_formula.is_relative() ? m_formula.volatile_count_without_formula( d ) : volatile_count_without_formula();
}

void named_formula_kernel::flag_dirty( const shared_dependency_type& d )
{
    if ( !m_unload_triggered ) {
        if ( m_formula.is_relative() ) {
            m_formula.flag_dirty( d );
        } else {
            m_is_dirty = true;
        }
    }
}

void named_formula_kernel::flag_dirty()
{
    m_is_dirty = true;
}

void named_formula_kernel::internal_raise_volatile_count( const shared_dependency_type& d )
{
    LOG_CORE_TRACE_NF_KERNEL( "raise volatile count of the kernel of \"" + debug_logging_helper::get_identifier( m_container ) + "\" for dependency: " + debug_logging_helper::get_identifier( d ) );
    if( m_formula.is_relative() ) {
        m_formula.raise_volatile_count( d );
    } else {
        internal_raise_volatile_count();
    }
}

void named_formula_kernel::internal_lower_volatile_count( const shared_dependency_type& d )
{
    LOG_CORE_TRACE_NF_KERNEL( "lower volatile count of the kernel of \"" + debug_logging_helper::get_identifier( m_container ) + "\" for dependency: " + debug_logging_helper::get_identifier( d ) );
    if( m_formula.is_relative() ) {
        m_formula.lower_volatile_count( d );
    } else {
        internal_lower_volatile_count();
    }
}

optional_sheet_range_type named_formula_kernel::coverage() const
{
    return m_formula.coverage();
}

optional_sheet_range_type named_formula_kernel::coverage( const shared_dependency_type& d ) const
{
    if ( m_formula.is_relative() ) {
        return m_formula.coverage( d );
    } else {
        return m_formula.coverage();
    }
}

void named_formula_kernel::update_value( calculation_context& cc, const variant& v, long token_id )
{
    // only update the cached value if the passed token id is still valid.
    if ( token_id == m_update_token ) {
        if ( cc.cache().cyclic_dependencies().check_if_cyclic( m_container ) ) {
            if ( v.is_error() || abstract_calculation::check_minimum_change( cc, m_cached_value, v ) ) {
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

void named_formula_kernel::update_value(  calculation_context& cc, const variant& v, long token_id, const shared_dependency_type& different_initiator )
{
    check_if_named_formula_dependency_wrapper_type( different_initiator );
    boost::shared_static_cast<named_formula_dependency_wrapper>( different_initiator )->update_value( cc, v, token_id );
}

shared_named_formula_kernel_type named_formula_kernel::create( const shared_dependency_type& parent, ast_formula& ast, const referencetable_type& reference_table /*= referencetable_type() */ )
{
    return boost::make_shared<named_formula_kernel>( parent, boost::ref( ast ), reference_table );
}

shared_named_formula_kernel_type named_formula_kernel::create( const shared_dependency_type& parent, const named_formula_kernel& other, const geometry::point& distance, bool is_rewrite_to_clone_sheet )
{
    return boost::make_shared<named_formula_kernel>( parent, other, distance, is_rewrite_to_clone_sheet );
}

shared_named_formula_kernel_type named_formula_kernel::create( const shared_dependency_type& parent, const named_formula_kernel& other, const geometry::point& distance, bool is_rewrite_to_clone_sheet, bool use_copy_move, const sheet_range& source_range, const referencetable_type& references )
{
    return boost::make_shared<named_formula_kernel>( parent, other, distance, is_rewrite_to_clone_sheet, use_copy_move, source_range, references );
}

void named_formula_kernel::register_reference( const shared_dependency_type& d )
{
    LOG_CORE_TRACE_NF_KERNEL( "register reference in the kernel of \"" + debug_logging_helper::get_identifier( m_container ) + "\" for dependency: " + debug_logging_helper::get_identifier( d ) );
    m_formula.add_position( d );
}

void named_formula_kernel::unregister_reference( i_dependency* d )
{
    LOG_CORE_TRACE_NF_KERNEL( "unregister reference in the kernel of \"" + debug_logging_helper::get_identifier( m_container ) + "\" for dependency: " + debug_logging_helper::get_identifier( d ) );
    m_formula.remove_position( d );
}

void named_formula_kernel::update_position( const shared_dependency_type& d, const geometry::point& distance, const bool move_absolute_references )
{
    LOG_CORE_TRACE_NF_KERNEL( "updating position of reference in the kernel of \"" + debug_logging_helper::get_identifier( m_container ) + "\" for dependency: " + debug_logging_helper::get_identifier( d ) );
    m_formula.update_position( d, distance, move_absolute_references );
}

void named_formula_kernel::unflag_dirty( const shared_dependency_type& d )
{
    if ( m_formula.is_relative() ) {
        m_formula.unflag_dirty( d );
    } else {
        m_is_dirty = false;
    }
}

void named_formula_kernel::register_variables() const
{
    if ( named_formula_scope::workbook_scope == boost::shared_static_cast<named_formula>( m_container )->scope() ) {
        shared_workbook_type wb = boost::shared_static_cast<named_formula>( m_container )->workbook().lock();
        if ( wb ) {
            wb->variable().merge( m_formula.variable() );
        }
    } else {
        shared_worksheet_type ws = m_container->worksheet().lock();
        if ( ws ) {
            ws->variable().merge( m_formula.variable() );
        }
    }
}

void named_formula_kernel::unregister_variables() const
{

    if ( named_formula_scope::workbook_scope == boost::shared_static_cast<named_formula>( m_container )->scope() ) {
        shared_workbook_type wb = boost::shared_static_cast<named_formula>( m_container )->workbook().lock();
        if ( wb ) {
            wb->variable().remove( m_formula.variable() );
        }
    } else {
        shared_worksheet_type ws = m_container->worksheet().lock();
        if ( ws ) {
            ws->variable().remove( m_formula.variable() );
        }
    }
}

void named_formula_kernel::adjust_legacy_references( const sheet_point& position )
{
    m_formula.adjust_legacy_references( position );
}

