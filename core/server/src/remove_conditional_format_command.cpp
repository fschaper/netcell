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
#include "wss/remove_conditional_format_command.hpp"
#include <wss/conditional_format_exception.hpp>
#include <wss/worksheet.hpp>
#include "wss/conditional_format_manager.hpp"


remove_conditional_format_command::remove_conditional_format_command( session& s, const shared_worksheet_type& ws, const sheet_range::rectangles_type& ranges, const id_list_type& ids )
    : base_command<i_command>::base_command( s )
    , m_ws( ws )
    , m_ranges( ranges )
    , m_ids( ids )
{}

void remove_conditional_format_command::execute()
{
    shared_worksheet_type ws =  m_ws.lock();
    if ( ! ws ) {
        throw conditional_format_exception();
    }

    ws->conditional_formats().erase( m_session, m_ranges, m_ids );
}

DEFINE_CLONEABLE( remove_conditional_format_command );
