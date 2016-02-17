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
#include "wss/copy_worksheet_command.hpp"
#include "wss/workbook.hpp"
#include "object_lookup.hpp"
#include "wss/object_not_found_exception.hpp"
#include "wss/invalid_worksheet_exception.hpp"
#include "wss/invalid_workbook_exception.hpp"

copy_worksheet_command::copy_worksheet_command( session& s, const std::string& ws_id, const std::string& next_ws_id, const std::string& target_wb_id )
    : base_command<i_command>::base_command( s )
    , m_next_id( next_ws_id.empty() ? boost::uuids::nil_uuid() : boost::lexical_cast<uuid_type>( next_ws_id ) )
{
    shared_worksheet_type ws = s.selected().worksheet().lock();
    if ( !ws_id.empty() ) {
        if ( ! ws ) {
            throw object_not_found_exception();
        }
        ws = object_lookup::worksheet( s, ws, boost::lexical_cast<uuid_type>( ws_id ) );
    }
    if ( ! ws ) {
        throw object_not_found_exception();
    }
    m_source_ws = ws;
    if ( !target_wb_id.empty() ) {
        m_target_wb = object_lookup::workbook( s, ws, boost::lexical_cast<uuid_type>( target_wb_id ) );
    } else {
        m_target_wb = ws->parent();
    }
}

void copy_worksheet_command::execute()
{
    shared_worksheet_type source_ws = m_source_ws.lock();
    if ( ! source_ws ) {
        throw invalid_worksheet_exception();
    }
    shared_workbook_type target_wb = m_target_wb.lock();
    if ( ! target_wb ) {
        throw invalid_workbook_exception();
    }
    shared_worksheet_type ws = source_ws->copy( m_session, target_wb, m_next_id );
    m_copied_sheet_id = boost::lexical_cast<std::string>( ws->uuid() );
    m_session.selected().worksheet( ws );
}

copy_worksheet_command::result_type copy_worksheet_command::value() const
{
    return m_copied_sheet_id;
}

DEFINE_CLONEABLE( copy_worksheet_command );
