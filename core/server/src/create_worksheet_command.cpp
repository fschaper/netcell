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
#include "wss/workbook.hpp"
#include "wss/create_worksheet_command.hpp"
#include "wss/worksheet.hpp"
#include "wss/workbook.hpp"

create_worksheet_command::create_worksheet_command( session& s, const std::string& name, const uuid_type& next_ws_id /* = boost::uuids::nil_uuid */ )
    : base_command<i_command>::base_command( s )
    , m_name( name )
    , m_next_ws_uuid( next_ws_id )
{}

void create_worksheet_command::execute()
{
    shared_workbook_type wb = m_session.selected().workbook().lock();
    if ( ! wb ) {
        throw object_not_found_exception();
    }
    m_uuid = wb->add( convert_utf8_ci( m_name ), m_next_ws_uuid )->uuid();
}

create_worksheet_command::result_type create_worksheet_command::value() const
{
    return boost::lexical_cast<std::string>( m_uuid );
}

DEFINE_CLONEABLE( create_worksheet_command );
