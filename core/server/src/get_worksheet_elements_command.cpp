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
#include "wss/get_worksheet_elements_command.hpp"
#include "wss/worksheet.hpp"
#include "wss/workbook.hpp"
#include "object_lookup.hpp"
#include "wss/worksheet_element_storage.hpp"
#include "command_helper.hpp"

get_worksheet_elements_command::get_worksheet_elements_command( session& s, const std::string& ws_id, const id_vec_type& ws_elem_ids, const key_vec_type& keys, const key_value_vector_type& vals, const bool wb_scope /* = false */ )
    : base_command<i_command>::base_command( s )
    , m_ids( ws_elem_ids )
    , m_keys( keys )
    , m_vals( vals )
    , m_wb_scope( wb_scope )
{
    if ( m_wb_scope ) {
        m_wb =  command_helper::worksheet( s, ws_id )->parent();
    } else {
        m_ws = command_helper::worksheet( s, ws_id );
    }
}

void get_worksheet_elements_command::execute()
{
    m_cached_value = command_helper::elements( m_wb_scope, m_wb, m_ws ).get_worksheet_elements_filtered( m_session, m_ids, m_keys, m_vals );
}

get_worksheet_elements_command::result_type get_worksheet_elements_command::value() const
{
    return m_cached_value;
}

DEFINE_CLONEABLE( get_worksheet_elements_command );
