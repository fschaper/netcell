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
#include "wss/define.hpp"
#include "wss/worksheet_element_storage.hpp"
#include "worksheet_element_filter.hpp"
#include "wss/insert_from_temporary.hpp"
#include "core_logging.hpp"
#include "uuid_adjust.hpp"

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <boost/foreach.hpp>
#endif // HAS_PRECOMPILED_HEADER == 0


worksheet_element_storage::worksheet_element_storage()
    : m_mutex()
    , m_counter( 0 )
{}

worksheet_element_storage::~worksheet_element_storage()
{
    m_container.clear();
    m_insert_order.clear();
}

void worksheet_element_storage::add_worksheet_element( shared_worksheet_element_type e )
{
    lock_type lock( m_mutex );
    m_container[ e->uuid() ] = e;
    m_insert_order.push_back( e );
}


void worksheet_element_storage::delete_worksheet_element( session& s, const std::string& uuid )
{
    lock_type lock( m_mutex );
    delete_worksheet_element( lock, s, uuid_adjust::cast_uuid( uuid ) );
}

void worksheet_element_storage::delete_worksheet_element( session& s, const ws_elem_id_type& uuid )
{
    lock_type lock( m_mutex );
    delete_worksheet_element( lock, s, uuid );
}

void worksheet_element_storage::delete_worksheet_element( lock_type& lock, session& /* s */, const ws_elem_id_type& uuid )
{
    m_container.erase( uuid );
    m_insert_order.erase( std::remove_if( m_insert_order.begin(), m_insert_order.end(), boost::bind( &worksheet_element::uuid, _1 ) == uuid ), m_insert_order.end() );
}

void worksheet_element_storage::delete_worksheet_elements( session& s, const std::vector< std::string >& list )
{
    lock_type lock( m_mutex );
    foreach( const std::string & id, list ) {
        delete_worksheet_element( lock, s, uuid_adjust::cast_uuid( id ) );
    }
}

shared_worksheet_element_type worksheet_element_storage::get_worksheet_element( session& /* s */, const std::string& uuid ) const
{
    lock_type lock( m_mutex );
    const_iterator it( find( lock, uuid ) );
    if ( it != m_container.end() ) {
        return it->second;
    } else {
        throw worksheet_element_exception( " - uuid: " + uuid );
    }
}

worksheet_element_storage::key_value_vector_vector_type worksheet_element_storage::get_worksheet_elements_filtered( session& s, const id_vec_type& elem_ids, const key_vec_type& keys, const key_value_vector_type& vals ) const
{
    lock_type lock( m_mutex );
    worksheet_element_filter::key_value_vector_vector_type return_vec;
    if ( elem_ids.empty() ) {
        worksheet_element_filter::get_values_filter( s, return_vec, m_insert_order, keys, vals );
    } else {
        worksheet_element_filter::get_values_filter( s, return_vec, m_container, elem_ids, keys, vals );
    }
    return return_vec;
}

void worksheet_element_storage::set_worksheet_elements_filtered( session& s, const id_vec_type& elem_id_vec, const key_value_vector_vector_type& vals )
{
    lock_type lock( m_mutex );
    worksheet_element_vec_type::iterator ws_e_end( m_container.end() );
    std::vector<std::string>::const_iterator it = elem_id_vec.begin(), end = elem_id_vec.end();
    key_value_vector_vector_type::const_iterator kv_vec_it = vals.begin(), kv_vec_end = vals.end();

    while ( it != end && kv_vec_it != kv_vec_end ) {
        std::string uuid_string( *it );
        worksheet_element_vec_type::iterator ws_e_it = m_container.find( uuid_adjust::cast_uuid( uuid_string ) );
        if ( ws_e_it != ws_e_end ) {
            ws_e_it->second->properties( s, *kv_vec_it );
        }
        ++it;
        ++kv_vec_it;
    }
}

worksheet_element_storage::iterator worksheet_element_storage::find( lock_type& lock, const std::string& uuid )
{
    return find( lock, uuid_adjust::cast_uuid( uuid ) );
}

worksheet_element_storage::const_iterator worksheet_element_storage::find( lock_type& lock, const std::string& uuid ) const
{
    return find( lock, uuid_adjust::cast_uuid( uuid ) );
}

worksheet_element_storage::iterator worksheet_element_storage::find( lock_type&,  const ws_elem_id_type& uuid )
{
    return m_container.find( uuid );
}

worksheet_element_storage::const_iterator worksheet_element_storage::find( lock_type&, const ws_elem_id_type& uuid ) const
{
    return m_container.find( uuid );
}
template<class ws_elem_id_T>
struct id_handler : non_instantiable {
    static ws_elem_id_type set_to_null() {
        return boost::uuids::nil_uuid();
    }
    static bool check_if_null( const ws_elem_id_type& id ) {
        return id.is_nil();
    }
};

template<>
struct id_handler<long> : non_instantiable {
    static long set_to_null() {
        return 0;
    }
    static bool check_if_null( const long id ) {
        return 0 == id;
    }
};

typedef id_handler<ws_elem_id_type> id_handler_type;

void worksheet_element_storage::copy_to_sheet( session& s, const shared_worksheet_type& target_sheet ) const
{
    worksheet_element_filter::key_value_vector_vector_type return_vec;
    worksheet_element_filter::get_values( s, return_vec, m_insert_order );
    foreach ( const worksheet_element_filter::key_value_vector_type & vec, return_vec ) {
        ws_elem_id_type id = id_handler_type::set_to_null();
        for ( worksheet_element_filter::key_value_vector_type::const_iterator it = vec.begin(); it != vec.end() && id_handler_type::check_if_null( id ); ++it ) {
            if ( it->first == "e_id" ) {
                id = uuid_adjust::cast_uuid( it->second.string() );
            }
        }
        if ( id_handler_type::check_if_null( id ) ) {
            shared_worksheet_element_type e = worksheet_element::create( target_sheet );
            e->properties( s, vec, worksheet_element::copied_ws_element() );
        } else {
            shared_worksheet_element_type e = worksheet_element::create( target_sheet, id );
            e->properties( s, vec, worksheet_element::copied_ws_element() );
        }

    }
}

worksheet_element_storage::list_type worksheet_element_storage::list_all_elements() const
{
    lock_type lock( m_mutex );
    list_type return_list;
    const_iterator it( m_container.begin() ), end_it( m_container.end() );
    for ( ; it != end_it; ++it ) {
        return_list.push_back( it->second );
    }
    return return_list;
}
