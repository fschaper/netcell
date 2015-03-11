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
#include "named_formula_manager.hpp"

#include "named_formula_storage.hpp"
#include "wss/application.hpp"
#include "wss/workbook.hpp"
#include "wss/named_formula_reference.hpp"
#include "named_formula.hpp"
#include "named_formula_wrapper.hpp"
#include "wss/named_formula_not_found_exception.hpp"
#include "wss/named_formula_accessor.hpp"
#include "wss/invalid_worksheet_exception.hpp"
#include "wss/named_formula_exception.hpp"

using namespace named_formula_utils;


named_formula_manager::named_formula_manager( workbook* parent )
    : m_store( new locked_store_type() )
    , m_parent( parent ) {}

named_formula_manager::~named_formula_manager() {}

void named_formula_manager::rename( session& s, const uuid_type& id, const std::string& new_name )
{
    ( *m_store->lock() ).rename( id, new_name );
    s.clear_cache();
}

void named_formula_manager::rename( session& s, const named_formula_identifier& nf_identifier, const std::string& new_name )
{
    ( *m_store->lock() ).rename( nf_identifier, new_name );
    s.clear_cache();
}

shared_reference_type named_formula_manager::register_dependency( const shared_dependency_type& d, const named_formula_identifier& nf_identifier, const named_formula_scope::type scope )
{
    shared_worksheet_type ws = d->worksheet().lock();
    if ( !ws ) {
        throw invalid_worksheet_exception();
    }

    return ( *m_store->lock() ).register_dependency( d, nf_identifier, scope, ws );
}

shared_reference_type named_formula_manager::register_dependency( const shared_dependency_type& d, const utf8_ci_string& name, const uuid_type& sheet_id, const named_formula_scope::type scope )
{
    shared_worksheet_type ws = d->worksheet().lock();
    if ( !ws ) {
        throw invalid_worksheet_exception();
    }

    return ( *m_store->lock() ).register_dependency( d, name, sheet_id, scope, ws );
}

void named_formula_manager::remove( session& s, const named_formula_identifier& nf_identifier )
{
    ( *m_store->lock() ).remove( nf_identifier );
    s.clear_cache();
}

void named_formula_manager::remove( session& s, const uuid_type& id )
{
    ( *m_store->lock() ).remove( id );
    s.clear_cache();
}

i_named_formula_manager::named_formula_list_type named_formula_manager::get_all( session& s, const uuid_type& sheet_id, const sheet_point& position /* = sheet_point */, const bool show_hidden/* = false */ )
{
    return ( *m_store->lock() ).get_all<i_named_formula_manager::named_formula_list_type>( s, sheet_id, position, show_hidden );
}

i_named_formula_manager::key_val_vec_vec_type named_formula_manager::get_all_as_strings( session& s, const uuid_type& sheet_id, const sheet_point& position /* = sheet_point */, const bool show_hidden/* = false */ )
{
    return ( *m_store->lock() ).get_all<i_named_formula_manager::key_val_vec_vec_type>( s, sheet_id, position, show_hidden );
}

shared_named_formula_accessor_type named_formula_manager::create_and_get_accessor( session& s, const std::string& name, const variant& formula, const named_formula_scope::type scope, const shared_worksheet_type& ws, const sheet_point& position, const bool hidden /*= false*/ )
{
    return named_formula_accessor::create( m_parent->shared_from_this(), internal_create( s, name, formula, scope, ws, position, hidden ) );
}

shared_named_formula_accessor_type named_formula_manager::get_accessor( session& s, const uuid_type& id )
{
    return named_formula_accessor::create( m_parent->shared_from_this(),  ( *m_store->lock() ).get_and_throw_if_not_found( id ) );
}

shared_named_formula_accessor_type named_formula_manager::get_accessor( session& s, const named_formula_identifier& nf_identifier )
{
    return named_formula_accessor::create( m_parent->shared_from_this(),  ( *m_store->lock() ).get_and_throw_if_not_found( nf_identifier ) );
}

void named_formula_manager::create( session& s, const std::string& name, const variant& formula, const named_formula_scope::type scope, const shared_worksheet_type& ws, const sheet_point& position /*= sheet_point( 0, 0 ) */, const bool hidden /* = false */ )
{
    internal_create( s, name, formula, scope, ws, position, hidden );
}

void named_formula_manager::create( session& s, const named_formula& nf, const shared_worksheet_type& target_ws )
{
    bool target_is_clone_sheet = target_ws ? target_ws->hidden() : false;
    static const geometry::point dummy_distance = geometry::point( 0, 0 );
    static const  sheet_range dummy_source_range = sheet_range( sheet_point( 0, 0 ) );
    shared_named_formula_type new_nf( named_formula::create( nf, target_is_clone_sheet, target_ws ) );

    ( *m_store->lock() ).set( nf.name(), new_nf );

    s.clear_cache();
}

shared_named_formula_type named_formula_manager::internal_create( session& s, const std::string& name, const variant& formula, const named_formula_scope::type scope, const shared_worksheet_type& ws, const sheet_point& position, const bool hidden, const bool get_if_already_defined /* = false */ )
{
    assert( "ERROR - named_formula named_formula_scope \"none\" not valid in this context (named_formula_manager::add) " && scope != named_formula_scope::none );
    shared_worksheet_type local_ws = nf::named_formula_storage::lookup_worksheet( ws, s.selected().worksheet() );
    const bool is_ws_scope = scope == named_formula_scope::worksheet_scope;
    if ( ( *m_store->lock() ).name_invalid_or_taken( named_formula_identifier( name, scope == named_formula_scope::worksheet_scope ? local_ws->uuid() : boost::uuids::nil_uuid() ) ) ) {
        if ( get_if_already_defined ) {
            return ( *m_store->lock() ).get( named_formula_identifier( name, is_ws_scope ? local_ws->uuid() : boost::uuids::nil_uuid() ) );
        }
        throw named_formula_exception();
    }
    shared_named_formula_type new_nf(
        named_formula::create(
            is_ws_scope,
            local_ws,
            name,
            s,
            formula,
            position,
            hidden
        ) );

    ( *m_store->lock() ).set( convert_utf8_ci( name ), new_nf );

    s.clear_cache();
    return new_nf;
}

void named_formula_manager::unload()
{
    ( *m_store->lock() ).unload();
}

void named_formula_manager::value( session& s, const named_formula_identifier& nf_identifier, const variant& v, const sheet_point& position /*= sheet_point( 0, 0 ) */ )
{
    ( *m_store->lock() ).get_and_throw_if_not_found( nf_identifier )->value( s, v, position );
    s.clear_cache();
}

variant named_formula_manager::value( session& s, const named_formula_identifier& nf_identifier, const sheet_point& position /*= sheet_point( 0, 0 ) */ ) const
{
    calculation_context cc( s, s.selected().application()->calculation_settings() );
    return ( *m_store->lock() ).get_and_throw_if_not_found( nf_identifier )->value( cc, position );
}

variant named_formula_manager::formula( const locale& l, const named_formula_identifier& nf_identifier, const sheet_point& position /*= sheet_point( 0, 0 ) */ ) const
{
    return ( *m_store->lock() ).get_and_throw_if_not_found( nf_identifier )->formula( l, position );
}

i_named_formula_manager::key_val_vec_type named_formula_manager::get_key_val_vec( session& s, const named_formula_identifier& nf_identifier, const sheet_point& position ) const
{
    const shared_named_formula_type& nf = ( *m_store->lock() ).get_and_throw_if_not_found( nf_identifier );
    return named_formula_utility::get_key_val_vec( s, *nf, position );
}

i_named_formula_manager::key_val_vec_type named_formula_manager::get_key_val_vec( session& s, const uuid_type& id, const sheet_point& position /*= sheet_point( 0, 0 ) */ ) const
{
    const shared_named_formula_type& nf = ( *m_store->lock() ).get_and_throw_if_not_found( id );
    return named_formula_utility::get_key_val_vec( s, *nf, position );
}


void named_formula_manager::comment( const std::string& comment, const named_formula_identifier& nf_identifier )
{
    ( *m_store->lock() ).get( nf_identifier )->comment( comment );
}

const std::string& named_formula_manager::comment( const named_formula_identifier& nf_identifier ) const
{
    return  ( *m_store->lock() ).get( nf_identifier )->comment();
}

void named_formula_manager::copy_to_sheet( session& s, const uuid_type& source_ws_id, const shared_worksheet_type& target_ws ) const
{
    ( *m_store->lock() ).copy_to_sheet( s, source_ws_id, target_ws );
}

void named_formula_manager::unload_sheet( const uuid_type& sheet_id )
{
    ( *m_store->lock() ).unload_sheet( sheet_id );

}

void named_formula_manager::update( session& s, const uuid_type& id, const std::string& name, const variant& formula, const std::string& comment, const sheet_point& position )
{
    shared_named_formula_type nf = ( *m_store->lock() ).get_and_throw_if_not_found( id );
    nf->value( s, formula, position );
    if ( !comment.empty() ) {
        nf->comment( comment );
    }
    if ( ! name.empty() ) {
        rename( s, nf->uuid(), name );
    }
    s.clear_cache();
}

bool named_formula_manager::exists( const named_formula_identifier& nf_identifier ) const
{
    return ( *m_store->lock() ).get( nf_identifier );
}
