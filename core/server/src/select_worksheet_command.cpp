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
#include "wss/select_worksheet_command.hpp"
#include "wss/invalid_worksheet_exception.hpp"
#include "wss/workbook.hpp"
#include "object_lookup.hpp"


select_worksheet_command::select_worksheet_command( session& s, const uuid_type& uuid )
    : base_command<i_undoable_command>::base_command( s )
    , m_uuid( uuid )
#ifdef CORE_DO_UNDO_SUPPORT
    , m_previous_uuid( boost::uuids::nil_uuid() )
#endif
{}

select_worksheet_command::select_worksheet_command( session& s, const std::string& name )
    : base_command<i_undoable_command>::base_command( s )
    , m_uuid( boost::uuids::nil_uuid() )
#ifdef CORE_DO_UNDO_SUPPORT
    , m_previous_uuid( boost::uuids::nil_uuid() )
#endif
    , m_name( name )
{}

void select_worksheet_command::execute()
{
    shared_workbook_type wb = m_session.selected().workbook().lock();
    if ( ! wb ) {
        throw object_not_found_exception();
    }
    if ( ! m_name ) {
        shared_worksheet_type current_worksheet = m_session.selected().worksheet().lock();
#ifdef CORE_DO_UNDO_SUPPORT
        if ( current_worksheet ) {
            m_previous_uuid = current_worksheet->uuid();
        }
#endif
        try {
            wb->get( m_session, m_uuid )->select( m_session.selected() );
        } catch ( ... ) {
            session_sheet_map::uuid_list list = m_session.session_sheets().list_active_session_sheets();
            session_sheet_map::uuid_list::iterator it = std::find( list.begin(), list.end(), m_uuid );
            if ( it != list.end() ) {
                shared_worksheet_type ws = m_session.selected().worksheet().lock();
                ws = object_lookup::worksheet( m_session, ws, *it );
                if ( ws ) {
                    ws->select( m_session.selected() );
                } else {
                    throw invalid_worksheet_exception();
                }
            } else {
                throw invalid_worksheet_exception();
            }
        }
    } else {
        shared_worksheet_type worksheet = wb->get( m_session, convert_utf8_ci( *m_name ) );
        m_uuid = worksheet->uuid();
        m_name.reset();
        worksheet->select( m_session.selected() );
    }
}

void select_worksheet_command::un_execute()
{
#ifdef CORE_DO_UNDO_SUPPORT
    if ( m_previous_uuid != boost::uuids::nil_uuid() ) {
        shared_workbook_type wb = m_session.selected().workbook().lock();
        if ( ! wb ) {
            throw object_not_found_exception();
        }
        wb->get( m_session, m_previous_uuid )->select( m_session.selected() );
        std::swap( m_uuid, m_previous_uuid );
    }
#endif
}

DEFINE_CLONEABLE( select_worksheet_command );
