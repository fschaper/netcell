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
 *  Frieder Hofmann <frieder.hofmann@jedox.com>
 */

#include "precompiled_header.hpp"
#include "named_formula_dependency_wrapper.hpp"
#include "named_formula_kernel.hpp"

/*!
 * \brief
 * careful, this will generate a lot of output!
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
//#define LOG_TRACE_NF_DEPENDENCIES 1

#ifdef _DEBUG
#   include "core_logging.hpp"
#   include "debug_logging_helper.hpp"
#endif
#if defined(LOG_TRACE_NF_DEPENDENCIES) && defined(_DEBUG) && !defined(LOG_CORE_TRACE_NF_DEPENDENCIES)
//#   define LOG_CORE_TRACE_NF_DEPENDENCIES(message) LOG_CORE_TRACE(message)
#   define LOG_CORE_TRACE_NF_DEPENDENCIES(message)
#else
#   define LOG_CORE_TRACE_NF_DEPENDENCIES(message)
#endif // LOG_TRACE_DEPENDENCIES
#include "wss/named_formula_calculation.hpp"
#include "wss/named_formula_exception.hpp"
#include "free_formula_impl.hpp"
#include "cell.hpp"

struct named_formula_dependency_wrapper::nf_dep_helper : non_instantiable {

    template<bool do_assertion>
    static inline void check( const shared_dependency_type& parent ) {
        assert( "we lost our parent! named_formula already deleted!" && parent );
    }
    template<bool do_assertion>
    static inline const named_formula* cast( const weak_dependency_type& weak_parent ) {
        shared_dependency_type parent = weak_parent.lock();
        check<do_assertion>( parent );
        return cast( parent );
    }
    static inline const named_formula* cast( const shared_dependency_type& parent ) {
        return static_cast<const named_formula*>( parent.get() );
    }

    static named_formula_dependency_wrapper* non_const( const named_formula_dependency_wrapper* ptr ) {
        return const_cast<named_formula_dependency_wrapper*>( ptr );
    }

    static shared_dependency_type get_shared_from_this( const named_formula_dependency_wrapper* ptr ) {
        return non_const( ptr )->shared_from_this();
    }

};
named_formula_dependency_wrapper::named_formula_dependency_wrapper( const shared_dependency_type& m_initiator, const shared_dependency_type& parent_named_formula ) : abstract_dependency()
    , m_parent( parent_named_formula )
    , m_initiator( m_initiator )
    , m_got_moved( false )
    , m_is_inside_ff( boost::shared_static_cast<named_formula>( parent_named_formula )->is_inside_ff() )
{
#ifdef _DEBUG
    m_debug_name = convert_utf8_ci( boost::shared_static_cast<named_formula>( parent_named_formula )->name() );
    friendly_name(  boost::shared_static_cast<named_formula>( parent_named_formula )->friendly_name() );
    ++m_counter;
#endif // _DEBUG
}

shared_dependency_type named_formula_dependency_wrapper::create( const shared_dependency_type& initiator, const shared_dependency_type& parent_named_formula )
{
    assert( "m_initiator not initiated! ouch!" && initiator != NULL );
    return boost::make_shared<named_formula_dependency_wrapper>( initiator, parent_named_formula );
}

const uuid_type& named_formula_dependency_wrapper::uuid() const
{
    return nf_dep_helper::cast<true>( m_parent )->uuid();
}

const utf8_ci_string& named_formula_dependency_wrapper::name() const
{
    return nf_dep_helper::cast<true>( m_parent )->name();
}

i_dependency::dependency_type named_formula_dependency_wrapper::type() const
{
    return named_formula_wrapper_type;
}

bool named_formula_dependency_wrapper::has_formula() const
{
    return true;
}

bool named_formula_dependency_wrapper::has_precedents() const
{
    return nf_dep_helper::cast<true>( m_parent )->has_precedents();
}

referencetable_type named_formula_dependency_wrapper::precedents() const
{
#ifdef _DEBUG
    shared_dependency_type d = m_initiator.lock();
    if ( !d ) {
        throw named_formula_exception();
    }
#endif // _DEBUG
    named_formula::locked_kernel_type::access locked_kernel( nf_dep_helper::cast<true>( m_parent )->m_kernel );
    return ( *locked_kernel ) ? ( *locked_kernel )->precedents( nf_dep_helper::get_shared_from_this( this ) ) : referencetable_type();
}

void named_formula_dependency_wrapper::connect_precedents()
{
    named_formula::locked_kernel_type::access locked_kernel( nf_dep_helper::cast<true>( m_parent )->m_kernel );
    if ( *locked_kernel ) {
        ( *locked_kernel )->connect_precedents( shared_from_this() );
    }
}

void named_formula_dependency_wrapper::disconnect_precedents()
{
    named_formula::locked_kernel_type::access locked_kernel( nf_dep_helper::cast<true>( m_parent )->m_kernel );
    if ( *locked_kernel ) {
        ( *locked_kernel )->disconnect_precedents( shared_from_this() );
    }
}

void named_formula_dependency_wrapper::value( session&, const variant&, const sheet_point& )
{
    assert( !"this function can't be called, value shouldn't be set via the proxy!" );
}

variant named_formula_dependency_wrapper::value( calculation_context& cc ) const
{
    shared_dependency_type parent = m_parent.lock();

#ifdef _DEBUG
    shared_dependency_type d = m_initiator.lock();
    if ( !d ) {
        throw named_formula_exception();
    }
#endif // _DEBUG
    if ( parent ) {
        named_formula::locked_kernel_type::access locked_kernel( nf_dep_helper::cast( parent )->m_kernel );

        if ( *locked_kernel ) {
            shared_dependency_type shared_this = nf_dep_helper::get_shared_from_this( this );
            optional_variant_type cached_volatile = ( * locked_kernel )->fetch_cached_volatile( cc, shared_this );
            if (
                (
                    ( !cached_volatile && ( *locked_kernel )->is_volatile( shared_this ) )
                    ||
                    ( *locked_kernel )->is_dirty( shared_this )
                )
                &&
                cc.is_calculation_enabled()
            ) {
                {
                    named_formula_calculation c = ( *locked_kernel )->delayed_calculation( cc );
                    c( shared_this, ++( nf_dep_helper::non_const( this )->m_update_token ) );
                }
                cached_volatile = ( *locked_kernel )->fetch_cached_volatile( cc, shared_this );
            }

            if ( cached_volatile ) {
                return *cached_volatile;
            }
        }

    }
    return m_cached_value;
}

std::string named_formula_dependency_wrapper::formula( const locale& l ) const
{
    shared_dependency_type parent = m_parent.lock();
    if ( parent ) {
        named_formula::locked_kernel_type::access locked_kernel( nf_dep_helper::cast( parent )->m_kernel );
        if ( *locked_kernel ) {
            return ( *locked_kernel )->formula( l, nf_dep_helper::get_shared_from_this( this ) );
        }
    }
    return "";
}

std::string named_formula_dependency_wrapper::formula_without_sheet_references( const locale& l ) const
{
    shared_dependency_type parent = m_parent.lock();
    if ( parent ) {
        named_formula::locked_kernel_type::access locked_kernel( nf_dep_helper::cast( parent )->m_kernel );
        if ( *locked_kernel ) {
            return  ( *locked_kernel )->formula_without_sheet_references( l, nf_dep_helper::get_shared_from_this( this ) );
        }
    }
    return "";
}

void named_formula_dependency_wrapper::calculate( calculation_context& cc )
{
    shared_dependency_type parent = m_parent.lock();
    if ( parent ) {
        named_formula::locked_kernel_type::access locked_kernel( nf_dep_helper::cast( parent )->m_kernel );
        if ( *locked_kernel ) {

            named_formula_calculation c = ( **locked_kernel ).delayed_calculation( cc );
            c( shared_from_this(), ++m_update_token );
        }
    }
}

weak_worksheet_type named_formula_dependency_wrapper::worksheet() const
{
    shared_dependency_type d = m_initiator.lock();
    if ( d ) {
        return d->worksheet();
    }
    return weak_worksheet_type();
}

optional_variant_type named_formula_dependency_wrapper::fetch_cached_volatile( calculation_context& cc ) const
{
    shared_dependency_type parent = m_parent.lock();
    if ( parent ) {
        named_formula::locked_kernel_type::access locked_kernel( nf_dep_helper::cast( parent )->m_kernel );
        if ( *locked_kernel ) {
            return ( *locked_kernel )->fetch_cached_volatile( cc, nf_dep_helper::get_shared_from_this( this ) );
        }
    }
    return optional_variant_type();
}

bool named_formula_dependency_wrapper::is_dirty() const
{
    shared_dependency_type parent = m_parent.lock();
    if ( parent ) {
        named_formula::locked_kernel_type::access locked_kernel( nf_dep_helper::cast( parent )->m_kernel );
        return ( *locked_kernel ) ? ( *locked_kernel )->is_dirty( nf_dep_helper::get_shared_from_this( this ) ) : false;
    }
    return false;
}

bool named_formula_dependency_wrapper::is_volatile() const
{
    shared_dependency_type parent = m_parent.lock();
    if ( parent ) {
        named_formula::locked_kernel_type::access locked_kernel( nf_dep_helper::cast( parent )->m_kernel );
        return ( *locked_kernel ) ? ( *locked_kernel )->is_volatile( nf_dep_helper::get_shared_from_this( this ) ) : false;
    }
    return false;
}

bool named_formula_dependency_wrapper::is_array() const
{
    return false;
}

sheet_range named_formula_dependency_wrapper::array_coverage() const
{
    return sheet_range( sheet_point( 0, 0 ) );
}

const sheet_point& named_formula_dependency_wrapper::position() const
{
    shared_dependency_type d = m_initiator.lock();
    if ( !d ) {
        throw named_formula_exception();
    }
    return d->position();
}

void named_formula_dependency_wrapper::internal_raise_volatile_count()
{
    shared_dependency_type parent = m_parent.lock();
    if ( parent ) {
        named_formula::locked_kernel_type::access locked_kernel( nf_dep_helper::cast( parent )->m_kernel );
        if ( *locked_kernel ) {
            ( *locked_kernel )->internal_raise_volatile_count( shared_from_this() );
        }
        shared_dependency_type initiator( m_initiator.lock() );
        if ( initiator && initiator->type() == i_dependency::named_formula_type ) {
            nf_dep_helper::cast( initiator )->raise_volatile_on_wrappers();
        }
    }
    LOG_CORE_TRACE_NF_DEPENDENCIES( std::string( "raise volatile count of: \"" ) + debug_logging_helper::get_identifier( shared_from_this() )
                                    + std::string( "\" to: \"" ) + boost::lexical_cast<std::string>( volatile_count() ) + std::string( "\"" ) );
}

void named_formula_dependency_wrapper::internal_lower_volatile_count()
{

    shared_dependency_type parent = m_parent.lock();
    if ( parent ) {
        LOG_CORE_TRACE_NF_DEPENDENCIES( std::string( "lower volatile count of: \"" ) + debug_logging_helper::get_identifier( shared_from_this() )
                                        + std::string( "\" to: \"" ) + boost::lexical_cast<std::string>( volatile_count() - 1 ) + std::string( "\"" ) );
        named_formula::locked_kernel_type::access locked_kernel( nf_dep_helper::cast( parent )->m_kernel );
        if ( *locked_kernel ) {
            ( *locked_kernel )->internal_lower_volatile_count( shared_from_this() );
        }
        shared_dependency_type initiator( m_initiator.lock() );
        if ( initiator && initiator->type() == i_dependency::named_formula_type ) {
            nf_dep_helper::cast( initiator )->lower_volatile_on_wrappers();
        }
    }
}

unsigned long named_formula_dependency_wrapper::volatile_count() const
{
    shared_dependency_type parent = m_parent.lock();
    if ( parent ) {
        named_formula::locked_kernel_type::access locked_kernel( nf_dep_helper::cast( parent )->m_kernel );
        if ( *locked_kernel ) {
            return ( *locked_kernel )->volatile_count( nf_dep_helper::get_shared_from_this( this ) );
        }
    }
    return 0;
}


unsigned long named_formula_dependency_wrapper::volatile_count_without_formula() const
{
    shared_dependency_type parent = m_parent.lock();
    if ( parent ) {
        named_formula::locked_kernel_type::access locked_kernel( nf_dep_helper::cast( parent )->m_kernel );
        if ( *locked_kernel ) {
            return ( *locked_kernel )->volatile_count_without_formula( nf_dep_helper::get_shared_from_this( this ) );
        }
    }
    return 0;
}

void named_formula_dependency_wrapper::internal_flag_dirty()
{
    LOG_CORE_TRACE_NF_DEPENDENCIES( std::string( "flag nf wrapper dirty: \"" ) + debug_logging_helper::get_identifier( shared_from_this() ) );
    shared_dependency_type parent = m_parent.lock();
    if ( parent ) {
        named_formula::locked_kernel_type::access locked_kernel( nf_dep_helper::cast( parent )->m_kernel );
        if ( *locked_kernel ) {
            ( *locked_kernel )->flag_dirty( shared_from_this() );
        }
    }
}

void named_formula_dependency_wrapper::flag_moved()
{
    LOG_CORE_TRACE_NF_DEPENDENCIES( std::string( "flag nf wrapper moved: \"" ) + debug_logging_helper::get_identifier( shared_from_this() ) );
    m_got_moved = true;
}

void named_formula_dependency_wrapper::update_position( const geometry::point& distance )
{
    LOG_CORE_TRACE_NF_DEPENDENCIES( std::string( "update position of nf wrapper: \"" ) + debug_logging_helper::get_identifier( shared_from_this() ) );
    shared_dependency_type parent = m_parent.lock();
    if ( parent ) {
        named_formula::locked_kernel_type::access locked_kernel( nf_dep_helper::cast( parent )->m_kernel );
        if ( *locked_kernel ) {
            ( *locked_kernel  )->update_position( shared_from_this(), distance, true );
        }
    }
}

bool named_formula_dependency_wrapper::moved( session& s ) const
{
    if ( m_got_moved ) {
        m_got_moved = false;
        return true;
    }
    return false;
}

optional_sheet_range_type named_formula_dependency_wrapper::coverage() const
{
    shared_dependency_type parent = m_parent.lock();
    if ( parent ) {
        named_formula::locked_kernel_type::access locked_kernel( nf_dep_helper::cast( parent )->m_kernel );
        if ( *locked_kernel ) {
            return  ( *locked_kernel )->coverage( nf_dep_helper::get_shared_from_this( this ) ) ;
        }
    }
    return optional_sheet_range_type();
}


void named_formula_dependency_wrapper::update_value( calculation_context& cc, const variant& v, long token_id )
{
    if ( token_id == m_update_token ) {
        m_cached_value = v;
        shared_dependency_type parent = m_parent.lock();
        if ( parent ) {
            named_formula::locked_kernel_type::access locked_kernel( nf_dep_helper::cast( parent )->m_kernel );
            if ( ( *locked_kernel ) && !( *locked_kernel )->is_volatile( shared_from_this() ) ) {
                ( *locked_kernel )->flag_dirty( shared_from_this() );
                ( *locked_kernel )->unflag_dirty( shared_from_this() );
            }
        }
    }
}

variant named_formula_dependency_wrapper::internal_value( interpreter_context& ic )
{
    return m_cached_value;
}

void named_formula_dependency_wrapper::internal_calculate( interpreter_context& ic )
{
    if ( ic.initiator().get() == this ) {
        reinterpret_cast<abstract_calculation&>( ic.alias() )( ic );
    } else {
        shared_dependency_type parent = m_parent.lock();
        if ( parent ) {
            named_formula::locked_kernel_type::access locked_kernel( nf_dep_helper::cast( parent )->m_kernel );
            named_formula_calculation c = ( **locked_kernel ).delayed_calculation( ic.context() );
            c( shared_from_this(), ++m_update_token );
        }
    }
}

bool named_formula_dependency_wrapper::put_in_general_cache() const
{
    shared_dependency_type parent = m_parent.lock();
    if ( parent ) {
        return parent->put_in_general_cache();
    }
    return true;
}


void named_formula_dependency_wrapper::trigger_register_dependent() const
{
    shared_dependency_type initiator( m_initiator.lock() );
    if ( initiator ) {
        if ( initiator->type() == i_dependency::cell_type ) {
            boost::shared_static_cast<cell>( initiator )->trigger_commit_kernel_change();
        } else if ( initiator->type() == i_dependency::free_formula_type ) {
            boost::shared_static_cast<free_formula_impl>( initiator )->trigger_register_dependent();
        } else if ( initiator->type() == i_dependency::named_formula_type ) {
            boost::shared_static_cast< ::named_formula >( initiator )->trigger_register_dependent();
        }
    }
}

named_formula_dependency_wrapper::~named_formula_dependency_wrapper()
{
#ifdef _DEBUG
    --m_counter;
#endif // _DEBUG
}

#ifdef _DEBUG

size_t named_formula_dependency_wrapper::m_counter = 0;

std::string named_formula_dependency_wrapper::get_debug_identifier() const
{
    shared_dependency_type d( m_initiator.lock() );
    shared_dependency_type parent( m_parent.lock() );
    std::string return_val;
    return_val +=  "[nf_wrapper from ";
    if ( d ) {
        return_val += debug_logging_helper::get_identifier( d );
    } else {
        return_val += "unknown";
    }
    return_val += " to ";
    if ( parent ) {
        return_val += convert_utf8_ci( name() ) ;
    } else {
        return_val += "unknown_name";
    }
    return_val += "]";
    return return_val;
}

#endif // _DEBUG
