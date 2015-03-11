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

#pragma once

#include <wss/type.hpp>

class WSS_MODULE session_sheet_map
{

public:
    typedef std::map<uuid_type, shared_worksheet_type> map_type;
    typedef std::map<uuid_type, uuid_type> session_to_original_sheet_id_map_type;
    typedef std::map<utf8_ci_string, uuid_type> name_to_session_sheet_id_map_type;

    typedef map_type::iterator iterator;
    typedef map_type::const_iterator const_iterator;

    typedef session_to_original_sheet_id_map_type::iterator translation_iterator;
    typedef session_to_original_sheet_id_map_type::const_iterator const_translation_iterator;


    typedef name_to_session_sheet_id_map_type::iterator name_iterator;
    typedef name_to_session_sheet_id_map_type::const_iterator const_name_iterator;

    typedef std::list<uuid_type> uuid_list;

    ~session_sheet_map();

    const uuid_type& create_session_sheet( session& s, const shared_worksheet_type& original_sheet, const bool activate_created_sheet = false );

    uuid_list list_sheets_that_have_a_session_sheet() const;

    uuid_list list_active_session_sheets() const;

    const shared_worksheet_type& session_sheet( const uuid_type& session_sheet_id ) const;

    const shared_worksheet_type& session_sheet( const utf8_ci_string& name ) const;

    const shared_worksheet_type& session_sheet_by_original_uuid( const uuid_type& original_sheet_id ) const;

    void remove_session_sheet( const uuid_type& session_sheet_id );

    void notify_sheet_unload( const uuid_type& sheet_id );

    const bool check( const uuid_type& session_sheet_id ) const;

    const bool check( const utf8_ci_string& name ) const;

    const bool check_original_uuid( const uuid_type& original_sheet_id ) const;

    const session_to_original_sheet_id_map_type& list_sheets_with_their_session_sheet() const;

private:
    void insert_session_sheet( const shared_worksheet_type& original_sheet, const shared_worksheet_type& session_sheet );

private:
    map_type m_storage;
    session_to_original_sheet_id_map_type m_id_translation;
    name_to_session_sheet_id_map_type m_name_lookup;
    session_to_original_sheet_id_map_type m_original_uuid_lookup;
};
