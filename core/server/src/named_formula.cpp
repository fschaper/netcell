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
#include "named_formula.hpp"

#include "wss/variant.hpp"
#include "wss/workbook.hpp"
#include "wss/formula.hpp"
#include "wss/worksheet.hpp"
#include "wss/sheet_point.hpp"
#include "wss/calculation.hpp"
#include "wss/interpreter_context.hpp"
#include "wss/calculation_context.hpp"
#include "wss/i_dependency_reference.hpp"
#include "wss/range_reference.hpp"
#include "wss/named_formula_reference.hpp"
#include "wss/not_implemented_exception.hpp"

#include "stack_calculation.hpp"
#include "named_formula_utility.hpp"
#include "core_logging.hpp"

#include "wss/reference_operation.hpp"
#include "named_formula_dependency_wrapper.hpp"
#include "named_formula_kernel.hpp"
#include "wss/invalid_worksheet_exception.hpp"
#include "wss/non_instantiable.hpp"
#include "free_formula_impl.hpp"

#if defined( WIN32 )
# pragma warning( push )
# pragma warning( disable:4355 )
#endif

using namespace named_formula_utils;

template<class operation_T>
void call_operation_on_interested_dependencies( const weak_dependency_set_type& deps, const operation_T& op )
{
    typedef weak_dependency_set_type::const_iterator const_iterator;
    for ( const_iterator it = deps.begin(), end_it = deps.end(); it != end_it; ++it ) {
        if ( shared_dependency_type sd = it->lock() ) {
            boost::bind( op, sd );
        }
    }
}

void flag_interested_dependencies_dirty( const weak_dependency_set_type& deps )
{
    typedef weak_dependency_set_type::const_iterator const_iterator;
    for ( const_iterator it = deps.begin(), end_it = deps.end(); it != end_it; ++it ) {
        if ( shared_dependency_type sd = it->lock() ) {
            sd->flag_dirty();
            sd->internal_flag_dirty();
        }
    }
}

template<class operation_T1, class operation_T2>
void call_operation_on_interested_dependencies( const weak_dependency_set_type& deps, const operation_T1& op1, const operation_T2& op2 )
{
    typedef weak_dependency_set_type::const_iterator const_iterator;
    for ( const_iterator it = deps.begin(), end_it = deps.end(); it != end_it; ++it ) {
        if ( shared_dependency_type sd = it->lock() ) {
            boost::bind( op1, sd );
            boost::bind( op2, sd );
        }
    }
}


inline bool is_free_formula( const shared_dependency_type& sd )
{
    return sd->type() == i_dependency::free_formula_type;
}

named_formula::named_formula( const bool scope_is_ws, const std::string& name, const shared_worksheet_type& ws, const bool is_inside_ff )
    : identifiable_object( convert_utf8_ci( name ) )
    , m_position( sheet_point( 0, 0 ) )
    , m_worksheet( ws )
    , m_workbook( ws ? ws->parent() : weak_workbook_type() )
    , m_ws_scope( scope_is_ws )
    , m_got_moved( false )
    , m_hidden( false )
    , m_special_caching( false )
    , m_is_inside_ff( is_inside_ff )
#ifdef _DEBUG
    , m_unload_called( true )
#endif // _DEBUG
{
#ifdef _DEBUG
    ++m_counter;
#endif // _DEBUG
}

inline void named_formula::check_use_count_of_wrappers( const named_formula::dependency_wrapper_map_type& m )
{
#ifdef _DEBUG
    foreach( const dependency_wrapper_map_type::value_type & v, m ) {
        assert( "use count should be down to 1 now!" && v.second.use_count() == 1 );
    }
#endif // _DEBUG
}

named_formula::~named_formula()
{
#ifdef _DEBUG
    --m_counter;
    assert( m_unload_called );
#endif // _DEBUG
    LOG_CORE_TRACE( "release named formula with uuid: \"" << boost::lexical_cast<std::string>( uuid() ) << "\" name: \"" << convert_utf8_ci( name() ) << "\"" );
}

void named_formula::unload()
{
#ifdef _DEBUG
    if ( !m_unload_called ) {
        m_unload_called = true;
#endif // _DEBUG
        locked_dependency_wrapper_map_type::access m( m_dependency_wrappers );
        clean_up_dependency_wrapper_map( m );
        flag_interested_dependencies_dirty( *m_dependencies_that_use_the_nf.lock() );
        locked_kernel_type::access kernel( m_kernel );

        internal_flag_dirty();
        if ( *kernel ) {
            ( *kernel )->unload( internal_access_wrappers() );
        }
        check_use_count_of_wrappers( *m );

        ( *kernel ).reset();
        ( *m ).clear();
        LOG_CORE_TRACE( "unload named formula with uuid: \"" << boost::lexical_cast<std::string>( uuid() ) << "\" name: \"" << convert_utf8_ci( name() ) << "\"" );
#ifdef _DEBUG
    }
#endif // _DEBUG
}

void named_formula::init_formula( session& s, const std::string& f, const sheet_point& position /*= sheet_point( 0, 0 ) */ )
{
    // (fschaper) parse the formula. without having a live lock on the cell.
    weak_worksheet_type current_worksheet( * m_worksheet.lock() );
    ast_formula parsed_formula( s, current_worksheet, f );
    const bool executes_on_set        = !s.is_loading()  && s.calculation_settings().auto_calculation() && parsed_formula.executes_on_set();
    const bool is_view_independent        = parsed_formula.is_view_independent();
#ifdef _DEBUG
    friendly_name( f );
#endif
    {
        // (fschaper) the lock on the kernel will keep other cells from changing their dirty
        // state since the value of the kernel can not be accessed now.
        locked_kernel_type::access kernel( m_kernel );

        locked_dependency_wrapper_map_type::access m( m_dependency_wrappers );
        ( * m_position.lock() ) = position;


        if ( *kernel ) {
            ( *kernel )->unload( internal_access_wrappers() );
            ( *kernel ).reset();
        }

        ( *kernel ) = named_formula_kernel::create( shared_from_this(), parsed_formula, ( ( *kernel ).get() != NULL ? ( *kernel )->precedents() : referencetable_type() ) );

        if (  ( *kernel )->is_volatile() ) {
            raise_volatile_count();
        }
        foreach( const dependency_wrapper_map_type::value_type & v, *m ) {
            shared_dependency_type sd = v.first.lock();
            if ( sd ) {
                internal_register_reference( kernel, m, sd, v.second );
                sd->flag_dirty();
            }
        }
        flag_interested_dependencies_dirty( *m_dependencies_that_use_the_nf.lock() );
    }

    if ( executes_on_set ) {
        calculation_context   tmp( s );
        calculate( tmp );
    }

    if ( is_view_independent || !s.is_loading() ) {
        //we changed something, lets see if we need to recompute the view independents
        shared_worksheet_type sw = this->worksheet().lock();
        if ( sw ) {
            if ( is_view_independent ) {
                sw->register_view_independent( shared_from_this() );
            }
            if ( !s.is_loading() ) {
                sw->compute_view_independent( s );
            }
        }
    }
#ifdef _DEBUG
    m_unload_called = false;
#endif // _DEBUG
}

shared_named_formula_type named_formula::create( const bool scope_is_ws, const shared_worksheet_type& ws, const std::string& name, session& s, const variant& formula, const sheet_point& position /* = sheet_point */, const bool hidden, const bool is_inside_ff )
{
    shared_dependency_type new_nf( boost::make_shared<named_formula>( scope_is_ws, name, ws, is_inside_ff ) );
    LOG_CORE_TRACE( "create named formula with name: \"" << convert_utf8_ci( boost::shared_static_cast<named_formula>( new_nf )->name() )
                    << "\", uuid: \"" << boost::lexical_cast<std::string>( boost::shared_static_cast<named_formula>( new_nf )->uuid() )
                    << "\" and formula: \"" << formula.string() << "\"" );

    boost::shared_static_cast<named_formula>( new_nf )->init_formula( s, formula.string(), position );
    boost::shared_static_cast<named_formula>( new_nf )->m_hidden = hidden;
    return boost::shared_static_cast<named_formula>( new_nf );
}

shared_named_formula_type named_formula::create( const shared_dependency_type& other, const geometry::point& distance, bool is_rewrite_to_clone_sheet, bool use_copy_move, const sheet_range& source_range, const shared_worksheet_type& ws /* = shared_worksheet_type() */ )
{
    shared_worksheet_type target_ws = ws ? ws : other->worksheet().lock();
    if ( !target_ws ) {
        throw invalid_worksheet_exception();
    }
    shared_dependency_type new_nf(
        boost::make_shared<named_formula>(
            boost::shared_static_cast<named_formula>( other )->m_ws_scope,
            convert_utf8_ci( boost::shared_static_cast<named_formula>( other )->name() ),
            target_ws,
            boost::shared_static_cast<named_formula>( other )->m_is_inside_ff
        )
    );
    ( *boost::shared_static_cast<named_formula>( new_nf )->m_position.lock() ) = other->position().offset( distance );
    {
        //copy the kernel
        locked_kernel_type::access kernel( boost::shared_static_cast<named_formula>( new_nf )->m_kernel );
        locked_kernel_type::access other_kernel( boost::shared_static_cast<named_formula>( other )->m_kernel );

        ( *kernel ) = named_formula_kernel::create( new_nf, **other_kernel, distance, is_rewrite_to_clone_sheet, use_copy_move, source_range, referencetable_type() );
        if (  ( *kernel )->is_volatile() ) {
            new_nf->raise_volatile_count();
        }
        boost::shared_static_cast<named_formula>( new_nf )->m_hidden = boost::shared_static_cast<named_formula>( other )->m_hidden;
    }
    return boost::shared_static_cast<named_formula>( new_nf );
}

shared_named_formula_type named_formula::create( const named_formula& other, bool is_rewrite_to_clone_sheet, const shared_worksheet_type& target_ws )
{
    if ( !target_ws ) {
        throw invalid_worksheet_exception();
    }
    shared_dependency_type new_nf(
        boost::make_shared<named_formula>(
            other.m_ws_scope,
            convert_utf8_ci( other.name() ),
            target_ws,
            other.m_is_inside_ff
        )
    );
    ( *boost::shared_static_cast<named_formula>( new_nf )->m_position.lock() ) = other.position();
    {
        //copy the kernel
        locked_kernel_type::access kernel( boost::shared_static_cast<named_formula>( new_nf )->m_kernel );
        locked_kernel_type::access other_kernel( other.m_kernel );
        static const sheet_range dummy_source_range = sheet_range( sheet_point( 0, 0 ) );
        static const sheet_point dummy_distance = sheet_point( 0, 0 );
        ( *kernel ) = named_formula_kernel::create( new_nf, **other_kernel, dummy_distance, is_rewrite_to_clone_sheet, false, dummy_source_range , referencetable_type() );
        if ( ( *kernel )->is_volatile() ) {
            new_nf->raise_volatile_count();
        }
        boost::shared_static_cast<named_formula>( new_nf )->m_hidden = other.m_hidden;
    }
    return boost::shared_static_cast<named_formula>( new_nf );
}

bool named_formula::has_precedents() const
{
    return ( * m_kernel.lock() )->has_precedents();
}

std::string named_formula::formula( const locale& l, const sheet_point& position /* = sheet_point */ ) const
{
    locked_kernel_type::access kernel( const_cast<named_formula*>( this )->m_kernel );
    const_cast<named_formula*>( this )->adjust_position( kernel, position );
    return ( *kernel )->formula( l );
}

std::string named_formula::formula_without_sheet_references( const locale& l, const sheet_point& position /* = sheet_point */ ) const
{
    locked_kernel_type::access kernel( const_cast<named_formula*>( this )->m_kernel );
    const_cast<named_formula*>( this )->adjust_position( kernel, position );
    return ( *kernel )->formula_without_sheet_references( l );
}

void named_formula::value( session& s, const variant& v, const sheet_point& position, const bool clear_cache )
{
    init_formula( s, v.string(), position );
    internal_flag_dirty();
    flag_dirty();
    if ( clear_cache ) {
        s.clear_cache();
    }
}

variant named_formula::value( calculation_context& cc, const sheet_point& position /* = sheet_point */ ) const
{
    {
        locked_kernel_type::access kernel( const_cast<named_formula*>( this )->m_kernel );
        const_cast<named_formula*>( this )->adjust_position( kernel, position );
    }
    const_cast<named_formula*>( this )->calculate( cc );
    return ( * m_kernel.lock() )->value();
}

void named_formula::internal_raise_volatile_count()
{
    assert( !"since we never directly connect to anything this method should not be called!" );
}

void named_formula::internal_lower_volatile_count()
{
    assert( !"since we never directly connect to anything this method should not be called!" );
}

bool named_formula::has_formula() const
{
    return true;
}

weak_worksheet_type named_formula::worksheet() const
{
    if ( !m_ws_scope ) {
        if ( ( *m_worksheet.lock() ).expired() ) {
            shared_workbook_type wb( workbook().lock() );
            if ( wb ) {
                //this isn't run often, so foreach is okay here
                foreach( const shared_worksheet_type & first_ws, wb->locking_iterator() ) {
                    if ( first_ws ) {
                        *m_worksheet.lock() = first_ws;
                        return ( * m_worksheet.lock() );
                    }
                }
            }
        }
    }
    return ( * m_worksheet.lock() );
}


weak_workbook_type named_formula::workbook() const
{
    return ( * m_workbook.lock() );
}


void named_formula::internal_flag_dirty()
{
    locked_dependency_wrapper_map_type::access m( m_dependency_wrappers );
    for ( dependency_wrapper_map_type::const_iterator it = ( *m ).begin(), end_it = ( *m ).end(); it != end_it; ++it ) {
        if ( !it->first.expired() ) {
            it->second->flag_dirty();
        }
    }
}

sheet_range named_formula::array_coverage() const
{
    return sheet_range( sheet_point( 0, 0 ) );
}

bool named_formula::is_dirty() const
{
    locked_kernel_type::access kernel( const_cast<named_formula*>( this )->m_kernel );
    return ( *kernel )->is_dirty();
}

void named_formula::comment( const std::string& comment )
{
    ( * m_comment.lock() ) = comment;
}

const std::string& named_formula::comment() const
{
    return ( * m_comment.lock() );
}

bool named_formula::is_array() const
{
    return false;
}

utf8_ci_string named_formula::scope_as_string() const
{
    return named_formula_utility::scope_as_string( *this ) ;
}

const named_formula_scope::type named_formula::scope() const
{
    return m_ws_scope ? named_formula_scope::worksheet_scope : named_formula_scope::workbook_scope;
}

bool named_formula::adjust_position( locked_kernel_type::access& kernel, const sheet_point& position )
{
    if ( ( * m_position.lock() ) != position && ( *kernel )->is_relative() ) {
        locked_dependency_wrapper_map_type::access m( m_dependency_wrappers );
        clean_up_dependency_wrapper_map( m );
        locked_kernel_type::access kernel( m_kernel );
        locked_position_type::access old_position( m_position );
        const geometry::point distance = ( *old_position ).distance( position );
        ( *old_position ) = position;
        if ( *kernel ) {
            ( * m_position.lock() ) = position;

            if ( *kernel ) {
                if ( ( *kernel )->has_precedents() ) {
                    foreach( const dependency_wrapper_map_type::value_type & v, *m ) {
                        ( *kernel )->disconnect_precedents( v.second );
                        if (  ( *kernel )->is_volatile( v.second ) ) {
                            // will lower the volatile count for all dependents on the current
                            // container but the current object.
                            v.second->lower_volatile_count();
                        }
                    }
                    reference_operation( shared_from_this(), ( *kernel )->precedents(), boost::bind( &i_dependency::unregister_dependent, _1, shared_from_this() ), true );
                }
                ( *kernel )->m_unload_triggered = true;
            }

            ( *kernel ) = named_formula_kernel::create( shared_from_this(), *( *kernel ), distance, false  );

            if ( ( *kernel )->has_precedents() ) {
                foreach( const dependency_wrapper_map_type::value_type & v, *m ) {
                    shared_dependency_type sd = v.first.lock();
                    if ( sd ) {
                        ( *kernel )->connect_precedents( v.second );
                    }
                }
            }
            return true;
        }
    }
    return false;
}

bool named_formula::moved( session& s ) const
{
    if ( m_got_moved ) {
        m_got_moved = false;
        return true;
    }
    return false;
}

bool named_formula::is_volatile() const
{
    return false;//( * m_kernel.lock() )->is_volatile();
}

unsigned long named_formula::volatile_count() const
{
    return 0;
}

unsigned long named_formula::volatile_count_without_formula() const
{
    return 0;
}

const sheet_point& named_formula::position() const
{
    return *locked_position_type::access( m_position );
}

optional_sheet_range_type named_formula::coverage( const shared_dependency_type& d ) const
{
    locked_kernel_type::access kernel( const_cast<named_formula*>( this )->m_kernel );
    return ( *kernel )->coverage( d );
}

void named_formula::register_reference( const shared_dependency_type& dependent )
{
    if ( dependent.get() == this ) {
        return;
    }
    locked_kernel_type::access kernel_access( m_kernel );
    if ( ( *m_dependency_wrappers.lock() ).empty() && dependent->position() != sheet_point( 0, 0 ) ) {
        adjust_position( kernel_access, dependent->position() );
    }
    locked_dependency_wrapper_map_type::access dep_access( m_dependency_wrappers );
    internal_register_reference( kernel_access, dep_access, dependent );
}

void named_formula::internal_register_reference( locked_kernel_type::access& kernel, locked_dependency_wrapper_map_type::access& map, const shared_dependency_type& dependent )
{
    add_to_dependencies_that_use_the_nf( dependent );

    if ( is_free_formula( dependent ) ) {
        shared_dependency_type dep_wrapper = named_formula_dependency_wrapper::create( dependent, shared_from_this() );
        ( *map ).insert( dependency_wrapper_map_type::value_type( dependent, dep_wrapper ) );
        internal_register_reference( kernel, map, dependent, dep_wrapper );
    }
}

void named_formula::internal_register_reference( locked_kernel_type::access& kernel, locked_dependency_wrapper_map_type::access& map, const shared_dependency_type& dependent, const shared_dependency_type& dep_wrapper )
{
    ( *kernel )->register_reference( dep_wrapper );
    if ( ( *kernel )->is_volatile( dep_wrapper ) ) {
        dep_wrapper->raise_volatile_count();
    }
    ( *kernel )->connect_precedents( dep_wrapper );
}

void named_formula::unregister_reference( const shared_dependency_type& dependent )
{
    if ( dependent.get() == this ) {
        return;
    }
    ( *m_dependencies_that_use_the_nf.lock() ).erase( dependent );
    if ( is_free_formula( dependent )  ) {
        locked_dependency_wrapper_map_type::access map( m_dependency_wrappers );
        locked_kernel_type::access kernel( m_kernel );
        dependency_wrapper_map_type::iterator it( ( *map ).find( dependent ) );
        if ( it != ( *map ).end() ) {
            internal_unregister_reference( kernel, dependent, it->second );
            ( *map ).erase( it );
        }
    }
    //TODO this has to be handled somewhere
    /*else if ( ( *m_kernel.lock() )->is_volatile() ) {
        dependent->lower_volatile_count();
        dependent->internal_lower_volatile_count();
    }*/

}

void named_formula::internal_unregister_reference( locked_kernel_type::access& kernel, const shared_dependency_type& dependent, const shared_dependency_type& dep_wrapper )
{
    if ( *kernel ) {
        ( *kernel )->disconnect_precedents( dep_wrapper );
        if ( ( *kernel )->is_volatile( dep_wrapper ) ) {
            dep_wrapper->lower_volatile_count();
        }
        ( *kernel )->unregister_reference( dep_wrapper.get() );
    }
}



void named_formula::trigger_register_dependent()
{
    locked_dependency_wrapper_map_type::access map( m_dependency_wrappers );
    locked_kernel_type::access kernel( m_kernel );
    for ( dependency_wrapper_map_type::const_iterator it = ( *map ).begin(), end_it = ( *map ).end(); it != end_it; ++it ) {
        boost::shared_static_cast<named_formula_dependency_wrapper>( it->second )->trigger_register_dependent();
    }

    const weak_dependency_set_type& deps = *m_dependencies_that_use_the_nf.lock();
    typedef weak_dependency_set_type::const_iterator const_iterator;
    for ( const_iterator it = deps.begin(), end_it = deps.end(); it != end_it; ++it ) {
        if ( shared_dependency_type sd = it->lock() ) {
            if ( sd->type() == i_dependency::free_formula_type ) {
                boost::shared_static_cast<free_formula_impl>( sd )->trigger_register_dependent();
            } else if ( sd->type() == i_dependency::named_formula_wrapper_type  ) {
                boost::shared_static_cast<named_formula_dependency_wrapper>( sd )->trigger_register_dependent();
            }
        }
    }
}

const shared_dependency_type& named_formula::get_proxy( const shared_dependency_type& d ) const
{
    static shared_dependency_type dummy;
    if ( !*locked_kernel_type::access( m_kernel ) ) {
        return dummy;
    }
    {
        locked_dependency_wrapper_map_type::access map( const_cast<named_formula*>( this )->m_dependency_wrappers );
        dependency_wrapper_map_type::const_iterator it( ( *map ).find( d ) );
        if ( it != ( *map ).end() ) {
            return it->second;
        }
    }
    //lock should be free again, so this call should be safe!
    const_cast<named_formula*>( this )->register_reference( d );
    //try again:
    {
        locked_dependency_wrapper_map_type::access map( const_cast<named_formula*>( this )->m_dependency_wrappers );
        dependency_wrapper_map_type::const_iterator it( ( *map ).find( d ) );
        if ( it != ( *map ).end() ) {
            return it->second;
        }
    }
    return dummy;
}

void named_formula::update_position( const shared_dependency_type& dependent, const geometry::point& distance )
{
    locked_kernel_type::access kernel( m_kernel );
    ( *kernel )->update_position( dependent, distance, true );
    if ( is_free_formula( dependent )  ) {
        const shared_dependency_type& dep_wrapper = get_proxy( dependent );
        ( *kernel )->disconnect_precedents( dep_wrapper );
        ( *kernel )->update_position( dep_wrapper, distance, true );
        ( *kernel )->connect_precedents( dep_wrapper );
    }
}

abstract_dependency::dependency_type named_formula::type() const
{
    return named_formula_type;
}

std::string named_formula::formula( const locale& ) const
{
    assert( !"this function should never be called, the proxy object should handle this!" );
    return "";
}

void named_formula::calculate( calculation_context& cc )
{
    if ( !cc.is_calculation_enabled() || !cc.cache().iteration_count_still_valid( *this, cc.settings().maximum_iterations() ) ) {
        return;
    }

    locked_kernel_type::access kernel( m_kernel );
    named_formula_calculation c = ( **kernel ).delayed_calculation( cc );
    c();
}

optional_variant_type named_formula::fetch_cached_volatile( calculation_context& ) const
{
    return optional_variant_type();
}

variant named_formula::internal_value( interpreter_context& )
{
    assert( !"this function should never be called, the proxy object should handle this!" );
    return variant();
}

void named_formula::internal_calculate( interpreter_context& ic )
{
    calculation_context& cc = ic.context();

    if ( ic.initiator().get() == this || ( ic.is_inside_named_formula() &&  ic.named_formula_initiator().get() == this ) ) {
        reinterpret_cast<abstract_calculation&>( ic.alias() )( ic );
    } else {
        locked_kernel_type::access kernel( m_kernel );
        named_formula_calculation c = ( **kernel ).delayed_calculation( cc );
        reinterpret_cast<abstract_calculation&>( c )( ic );

    }
}

referencetable_type named_formula::precedents() const
{
    return ( * m_kernel.lock() )->precedents();
}

referencetable_type named_formula::precedents( const shared_dependency_type& sd ) const
{
    if ( sd.get() == this ) {
        return ( * m_kernel.lock() )->precedents();
    } else {
        add_to_dependencies_that_use_the_nf( sd );
        return ( * m_kernel.lock() )->precedents( sd );
    }
}

variant named_formula::value( calculation_context& ) const
{
    assert( !"this function should never be called, the proxy object should handle this!" );
    return variant();
}

void named_formula::value( session& s, const variant& v, const sheet_point& position )
{
    value( s, v, position, true );
}

bool named_formula::hidden()
{
    return m_hidden;
}
void named_formula::adjust_legacy_references( const sheet_point& position )
{
    ( * m_kernel.lock() )->adjust_legacy_references( position );
}

void named_formula::clean_up_dependency_wrapper_map( locked_dependency_wrapper_map_type::access& map )
{
    {
        locked_weak_dependency_set_type::access dep_access( m_dependencies_that_use_the_nf );
        weak_dependency_set_type& deps = *dep_access;
        typedef weak_dependency_set_type::iterator iterator;
        iterator it = deps.begin();
        while ( it != deps.end() ) {
            if ( it->expired() ) {
                deps.erase( it++ );
            } else {
                ++it;
            }
        }
    }
    {
        dependency_wrapper_map_type& m = ( *map );
        dependency_wrapper_map_type::iterator it( m.begin() );
        const bool kernel_has_precedents = has_precedents();
        while ( it != m.end() ) {
            if ( it->first.expired() || ( kernel_has_precedents && it->second.use_count() == 1 ) ) {
                ( * m_kernel.lock() )->disconnect_precedents( it->second );
                ( * m_kernel.lock() )->unregister_reference( it->second.get() );
                m.erase( it++ );
            } else {
                ++it;
            }
        }
    }
}

inline void named_formula::add_to_dependencies_that_use_the_nf(  const shared_dependency_type& sd ) const
{
    if ( ( *m_dependencies_that_use_the_nf.lock() ).insert( sd ).second ) {
        if (  ( * m_kernel.lock() )->is_volatile() ) {
            sd->raise_volatile_count();
            if ( sd->type() != named_formula_type ) {
                sd->internal_raise_volatile_count();
            }
        }
    }
}

void named_formula::raise_volatile_on_wrappers() const
{
    call_operation_on_interested_dependencies( *m_dependencies_that_use_the_nf.lock(), &i_dependency::internal_raise_volatile_count );
    locked_dependency_wrapper_map_type::access map( m_dependency_wrappers );
    for ( dependency_wrapper_map_type::const_iterator it = ( *map ).begin(), end_it = ( *map ).end(); it != end_it; ++it ) {
        boost::shared_static_cast<named_formula_dependency_wrapper>( it->second )->internal_raise_volatile_count();
    }
}

void named_formula::lower_volatile_on_wrappers() const
{
    call_operation_on_interested_dependencies( *m_dependencies_that_use_the_nf.lock(), &i_dependency::internal_lower_volatile_count );
    locked_dependency_wrapper_map_type::access map( m_dependency_wrappers );
    for ( dependency_wrapper_map_type::const_iterator it = ( *map ).begin(), end_it = ( *map ).end(); it != end_it; ++it ) {
        boost::shared_static_cast<named_formula_dependency_wrapper>( it->second )->internal_lower_volatile_count();
    }
}

void named_formula::register_wrappers_at_cell( const shared_dependency_type& new_cell ) const
{
    locked_dependency_wrapper_map_type::access map( m_dependency_wrappers );
    for ( dependency_wrapper_map_type::const_iterator it = ( *map ).begin(), end_it = ( *map ).end(); it != end_it; ++it ) {
        if ( shared_dependency_type sd = it->first.lock() ) {
            new_cell->register_dependent( it->second );
        }
    }
}

void named_formula::unregister_wrappers_at_cell( const shared_dependency_type& new_cell ) const
{
    locked_dependency_wrapper_map_type::access map( m_dependency_wrappers );
    for ( dependency_wrapper_map_type::const_iterator it = ( *map ).begin(), end_it = ( *map ).end(); it != end_it; ++it ) {
        if ( shared_dependency_type sd = it->first.lock() ) {
            new_cell->unregister_dependent( it->second );
        }
    }
}


const std::list<shared_dependency_type> named_formula::internal_access_wrappers() const
{
    std::list<shared_dependency_type> return_val;
    locked_dependency_wrapper_map_type::access map( m_dependency_wrappers );
    for ( dependency_wrapper_map_type::const_iterator it = ( *map ).begin(), end_it = ( *map ).end(); it != end_it; ++it ) {
        shared_dependency_type sd = it->first.lock();
        if ( sd ) {
            return_val.push_back( it->second );
        }
    }
    return return_val;
}

const positioned_op_codes& named_formula::get_opcode() const
{
    return ( *m_kernel.lock() )->m_formula.m_opcode;
}

bool named_formula::is_relative() const
{
    return ( *m_kernel.lock() )->is_relative();
}

void named_formula::flag_moved()
{
    m_got_moved = true;
}

#ifdef _DEBUG
std::string named_formula::get_debug_identifier() const
{
    return "[nf " + convert_utf8_ci( name() ) + "]";
}
size_t named_formula::m_counter = 0;
#endif // _DEBUG

#if defined( WIN32 )
# pragma warning( pop )
#endif
