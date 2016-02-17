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
#include "wss/remove_worksheet_element_command.hpp"
#include "wss/worksheet.hpp"
#include "wss/workbook.hpp"
#include "object_lookup.hpp"
#include "wss/worksheet_element_storage.hpp"
#include "command_helper.hpp"

remove_worksheet_element_command::remove_worksheet_element_command( session& s, const std::string& ws_id, const worksheet_element_id_vector_type& ws_elem_ids, const bool wb_scope /* = false */ )
    : base_command<i_command>::base_command( s )
    , m_ids( ws_elem_ids )
    , m_wb_scope( wb_scope )
{
    if ( m_wb_scope ) {
        m_wb =  command_helper::worksheet( s, ws_id )->parent();
    } else {
        m_ws = command_helper::worksheet( s, ws_id );
    }
}

void remove_worksheet_element_command::execute()
{
    if ( m_wb_scope ) {
        if ( shared_workbook_type wb = m_wb.lock() ) {
            wb->flag_changed();
        }
    } else {
        if (  shared_worksheet_type ws = m_ws.lock() ) {
            ws->parent()->flag_changed();
        }
    }

    command_helper::elements( m_wb_scope, m_wb, m_ws ).delete_worksheet_elements( m_session, m_ids );
}

DEFINE_CLONEABLE( remove_worksheet_element_command );

