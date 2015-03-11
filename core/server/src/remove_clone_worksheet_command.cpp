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
#include "wss/remove_clone_worksheet_command.hpp"
#include "wss/worksheet.hpp"
#include "wss/session.hpp"
#include "wss/session_sheet_map.hpp"
#include "wss/invalid_worksheet_exception.hpp"
#include "object_lookup.hpp"

remove_clone_worksheet_command::remove_clone_worksheet_command( session& s, const uuid_type& original_sheet_id, const bool select_original_sheet /*= false */ )
    : base_command<i_command>::base_command( s )
    , m_original_id( original_sheet_id )
    , m_select_original_sheet( select_original_sheet )
{
    shared_worksheet_type ws = s.selected().worksheet().lock();
    if ( ! ws ) {
        throw invalid_worksheet_exception();
    } else if ( ws->uuid() != m_original_id ) {
        ws = object_lookup::worksheet( s, ws, m_original_id );
    }
    if ( ! ws ) {
        throw invalid_worksheet_exception();
    }
    m_original_ws = ws;
}

void remove_clone_worksheet_command::execute()
{
    m_session.session_sheets().remove_session_sheet( m_original_id );
    if ( m_select_original_sheet ) {
        shared_worksheet_type ws = m_original_ws.lock();
        if ( !ws ) {
            throw invalid_worksheet_exception();
        }
        m_session.selected().worksheet( ws );
    }
}

DEFINE_CLONEABLE( remove_clone_worksheet_command );
