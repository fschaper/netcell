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
#include "wss/select_workbook_command.hpp"
#include "wss/application.hpp"

select_workbook_command::select_workbook_command( session& s, const uuid_type& uuid )
    : base_command<i_undoable_command>::base_command( s )
    , m_uuid( uuid )
#ifdef CORE_DO_UNDO_SUPPORT
    , m_previous_uuid( boost::uuids::nil_uuid() )
#endif
{}

select_workbook_command::select_workbook_command( session& s, const std::string& name )
    : base_command<i_undoable_command>::base_command( s )
    , m_uuid( boost::uuids::nil_uuid() )
#ifdef CORE_DO_UNDO_SUPPORT
    , m_previous_uuid( boost::uuids::nil_uuid() )
#endif
    , m_name( name )
{}

void select_workbook_command::execute()
{
    shared_application_type app = m_session.selected().application();
    if ( ! app ) {
        throw object_not_found_exception();
    }
    if ( ! m_name ) {
        shared_workbook_type current_workbook = m_session.selected().workbook().lock();
#ifdef CORE_DO_UNDO_SUPPORT
        if ( current_workbook ) {
            m_previous_uuid = current_workbook->uuid();
        }
#endif
        app->get( m_session, m_uuid )->select( m_session.selected() );
    } else {
        shared_workbook_type workbook = app->get( m_session, convert_utf8_ci( *m_name ) );
        m_uuid = workbook->uuid();
        m_name.reset();
        workbook->select( m_session.selected() );
    }
}

void select_workbook_command::un_execute()
{
#ifdef CORE_DO_UNDO_SUPPORT
    if ( m_previous_uuid != boost::uuids::nil_uuid() ) {
        shared_application_type app = m_session.selected().application();
        if ( ! app ) {
            throw object_not_found_exception();
        }
        app->get( m_session, m_previous_uuid )->select( m_session.selected() );
        std::swap( m_uuid, m_previous_uuid );
    }
#endif
}

DEFINE_CLONEABLE( select_workbook_command );
