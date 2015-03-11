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
#include "wss/clone_worksheet_command.hpp"
#include "wss/worksheet.hpp"
#include "object_lookup.hpp"
#include "wss/invalid_worksheet_exception.hpp"
#include "wss/object_not_found_exception.hpp"
#include "wss/session_sheet_map.hpp"
#include "wss/range.hpp"
#include "wss/session.hpp"

clone_worksheet_command::clone_worksheet_command( session& s, const uuid_type& original_ws_id /* = boost::uuids::nil */, const bool select_clone_sheet /* = false */ )
    : base_command<i_command>::base_command( s )
    , m_select_clone_sheet( select_clone_sheet )
{
    shared_worksheet_type ws = s.selected().worksheet().lock();
    if ( !original_ws_id.is_nil() ) {
        if ( ! ws ) {
            throw object_not_found_exception();
        }
        ws = object_lookup::worksheet( s, ws, original_ws_id );
    }
    if ( ! ws ) {
        throw object_not_found_exception();
    }
    m_source_ws = ws;
}

void clone_worksheet_command::execute()
{
    shared_worksheet_type source_ws = m_source_ws.lock();
    if ( ! source_ws ) {
        throw invalid_worksheet_exception();
    }
    m_session_sheet_id = boost::lexical_cast<std::string>( m_session.session_sheets().create_session_sheet( m_session, source_ws, m_select_clone_sheet ) );
}

clone_worksheet_command::result_type clone_worksheet_command::value() const
{
    return m_session_sheet_id;
}

DEFINE_CLONEABLE( clone_worksheet_command );
