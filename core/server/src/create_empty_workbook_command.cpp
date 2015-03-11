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
#include "wss/create_empty_workbook_command.hpp"
#include "wss/session.hpp"
#include "wss/create_workbook_command.hpp"
#include "wss/create_worksheet_command.hpp"
#include "wss/select_worksheet_command.hpp"
#include "wss/select_workbook_command.hpp"
#include "wss/set_value_command.hpp"

DEFINE_CLONEABLE( create_empty_workbook_command );

create_empty_workbook_command::create_empty_workbook_command( session& s )
    : base_command<i_command>::base_command( s )
{}

void create_empty_workbook_command::execute()
{
    create_workbook_command command( m_session, "Workbook1" );
    command.execute();
    m_result = command.value();
    select_workbook_command command_s( m_session, boost::lexical_cast<uuid_type>( command.value() ) );
    command_s.execute();
    create_worksheet_command command_ws( m_session, "Sheet1" );
    command_ws.execute();
    select_worksheet_command command_sw( m_session, boost::lexical_cast<uuid_type>( command_ws.value() ) );
    command_sw.execute();

    set_value_command command_set_value( m_session,  sheet_range( sheet_point( 0, 0 ), sheet_point( 0, 0 ) ), variant() );
    command_set_value.execute();
}

create_empty_workbook_command::result_type create_empty_workbook_command::value() const
{
    return m_result;
}
