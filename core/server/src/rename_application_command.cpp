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
#include "wss/rename_application_command.hpp"
#include "wss/invalid_application_exception.hpp"
#include "wss/application.hpp"
#include "wss/session.hpp"

rename_application_command::rename_application_command( session& s, const std::string& new_name )
    : abstract_undoable_command( s )
    , m_new_name( convert_utf8_ci( new_name ) )
{}

void rename_application_command::execute()
{
    shared_application_type app = m_session.selected().application();
    if ( ! app ) {
        throw invalid_application_exception();
    }
#ifdef CORE_DO_UNDO_SUPPORT
    m_old_name = app->name();
#endif
    app->name( m_new_name );
}

void rename_application_command::un_execute()
{
#ifdef CORE_DO_UNDO_SUPPORT
    shared_application_type app = m_session.selected().application();
    if ( ! app ) {
        throw invalid_application_exception();
    }
    m_new_name = app->name();
    app->name( m_old_name );
#endif
}

DEFINE_CLONEABLE( rename_application_command );

