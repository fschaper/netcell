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
*   Frieder Hofmann <frieder.hofmann@jedox.com>
*/

#include "precompiled_header.hpp"
#include "wss/session_sheet_map.hpp"
#include "wss/worksheet.hpp"
#include "wss/session.hpp"

const uuid_type& session_sheet_map::create_session_sheet( session& s, const shared_worksheet_type& original_sheet, const bool activate_created_sheet /*= false */ )
{
    shared_worksheet_type session_sheet = worksheet::create_session_sheet( s, original_sheet );
    insert_session_sheet( original_sheet, session_sheet );
    if ( activate_created_sheet ) {
        s.selected().worksheet( session_sheet );
    }
    original_sheet->fill_session_sheet( s, session_sheet );
    return session_sheet->uuid();
}

session_sheet_map::uuid_list session_sheet_map::list_sheets_that_have_a_session_sheet() const
{
    uuid_list return_list;
    const_translation_iterator it( m_id_translation.begin() ), end_it( m_id_translation.end() );
    for ( ; it != end_it; ++it ) {
        return_list.push_back( it->second );
    }
    return return_list;
}

session_sheet_map::uuid_list session_sheet_map::list_active_session_sheets() const
{
    uuid_list return_list;
    const_translation_iterator it( m_id_translation.begin() ), end_it( m_id_translation.end() );
    for ( ; it != end_it; ++it ) {
        return_list.push_back( it->first );
    }
    return return_list;
}

const shared_worksheet_type& session_sheet_map::session_sheet( const uuid_type& session_sheet_id ) const
{
    const_iterator it( m_storage.find( session_sheet_id ) );
    if ( it != m_storage.end() ) {
        return it->second;
    }
    static shared_worksheet_type dummy;
    return dummy;
}

const shared_worksheet_type& session_sheet_map::session_sheet( const utf8_ci_string& name ) const
{
    const_name_iterator it( m_name_lookup.find( name ) );
    if ( it != m_name_lookup.end() ) {
        return session_sheet( it->second );
    }
    static shared_worksheet_type dummy;
    return dummy;
}

const shared_worksheet_type& session_sheet_map::session_sheet_by_original_uuid( const uuid_type& original_sheet_id ) const
{
    const_iterator it( m_storage.find( m_original_uuid_lookup.find( original_sheet_id )->second ) );
    if ( it != m_storage.end() ) {
        return it->second;
    }
    static shared_worksheet_type dummy;
    return dummy;
}

void session_sheet_map::insert_session_sheet( const shared_worksheet_type& original_sheet, const shared_worksheet_type& session_sheet )
{
    m_storage[session_sheet->uuid()] = session_sheet;
    m_id_translation[session_sheet->uuid()] = original_sheet->uuid();
    m_name_lookup[original_sheet->name()] = session_sheet->uuid();
    m_original_uuid_lookup[original_sheet->uuid()] = session_sheet->uuid();
}

void session_sheet_map::remove_session_sheet( const uuid_type& session_sheet_id )
{
    translation_iterator id_it( m_id_translation.find( session_sheet_id ) );
    if ( id_it != m_id_translation.end() ) {
        iterator store_it( m_storage.find( session_sheet_id ) );
        assert( "session sheet storage is in an unstable state!!" && store_it != m_storage.end() );
        //make sure everything is removed properly!
        store_it->second->unload();
        //then erase the sheet
        //m_id_translation.erase( session_sheet_id );
        m_original_uuid_lookup.erase( m_id_translation.find( id_it->first )->second );
        m_name_lookup.erase( store_it->second->name() );
        m_id_translation.erase( id_it );
        m_storage.erase( store_it );
    }
}

void session_sheet_map::notify_sheet_unload( const uuid_type& sheet_id )
{
    std::vector< uuid_type > uuids_to_remove;
    const_translation_iterator it( m_id_translation.begin() ), end_it( m_id_translation.end() );
    for ( ; it != end_it; ++it ) {
        if ( sheet_id == it->second ) {
            uuids_to_remove.push_back( it->first );
        }
    }

    std::vector< uuid_type >::const_iterator it_del( uuids_to_remove.begin() ), end_it_del( uuids_to_remove.end() );
    for ( ; it_del != end_it_del; ++it_del ) {
        remove_session_sheet( *it_del );
    }
}

const bool session_sheet_map::check( const uuid_type& session_sheet_id ) const
{
    return m_storage.find( session_sheet_id ) != m_storage.end();
}

const bool session_sheet_map::check( const utf8_ci_string& name ) const
{
    return m_name_lookup.find( name ) != m_name_lookup.end();
}

const bool session_sheet_map::check_original_uuid( const uuid_type& original_sheet_id ) const
{
    return m_original_uuid_lookup.find( original_sheet_id ) != m_original_uuid_lookup.end();
}

const session_sheet_map::session_to_original_sheet_id_map_type& session_sheet_map::list_sheets_with_their_session_sheet() const
{
    return m_id_translation;
}

session_sheet_map::~session_sheet_map()
{
    std::vector< uuid_type > uuids_to_remove;
    const_translation_iterator it( m_id_translation.begin() ), end_it( m_id_translation.end() );
    for ( ; it != end_it; ++it ) {
        uuids_to_remove.push_back( it->first );
    }

    std::vector< uuid_type >::const_iterator it_del( uuids_to_remove.begin() ), end_it_del( uuids_to_remove.end() );
    for ( ; it_del != end_it_del; ++it_del ) {
        remove_session_sheet( *it_del );
    }
}
