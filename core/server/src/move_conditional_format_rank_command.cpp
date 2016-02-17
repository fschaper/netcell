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
#include "wss/move_conditional_format_rank_command.hpp"

#include <wss/conditional_format_exception.hpp>
#include <wss/worksheet.hpp>

#include "wss/conditional_format_manager.hpp"
#include "wss/invalid_worksheet_exception.hpp"

move_conditional_format_rank_command::move_conditional_format_rank_command( session& s, const conditional_format_lookup_id_type id, const int move_rank, const shared_worksheet_type ws, const sheet_range::rectangles_type& selected_region )
    : base_command<i_command>::base_command( s )
    , m_id( id )
    , m_move_rank( move_rank )
    , m_selected_region( selected_region )
{
    if ( ws ) {
        m_ws = ws;
    } else {
        shared_worksheet_type active_ws =  m_session.selected().worksheet().lock();
        if ( ! active_ws ) {
            throw invalid_worksheet_exception( " no worksheet selected and none specified! " );
        }
        m_ws = active_ws;
    }
}

void move_conditional_format_rank_command::execute()
{
    if ( m_move_rank == 0 ) {
        return;
    }
    shared_worksheet_type ws =  m_ws.lock();
    if ( ! ws ) {
        throw conditional_format_exception( "worksheet no longer present!" );
    }
    if ( m_move_rank < 0 ) {
        for ( int i = m_move_rank; i < 0; ++i ) {
            ws->conditional_formats().move_down( m_session, m_id, m_selected_region );
        }
    } else {
        for ( int i = m_move_rank; i > 0; --i ) {
            ws->conditional_formats().move_up( m_session, m_id, m_selected_region );
        }
    }
}

DEFINE_CLONEABLE( move_conditional_format_rank_command );
