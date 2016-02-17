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
#include "wss/invalid_worksheet_exception.hpp"
#include "wss/worksheet.hpp"
#include "wss/set_row_height_command.hpp"
#include "wss/sheet_layout_manager.hpp"

set_row_height_command::set_row_height_command( session& s, const sheet_layout_trait::line_type& line, unsigned int row_height )
    : abstract_undoable_command( s )
    , m_new_row_height( row_height )
#ifdef CORE_DO_UNDO_SUPPORT
    , m_old_row_height( 0 )
#endif
    , m_line ( line )
    , m_worksheet( s.selected().worksheet() )
{}

void set_row_height_command::execute()
{
    shared_worksheet_type ws = lock_worksheet_and_throw_if_not_there();
    sheet_layout_manager& layout_manager = ws->layout();
#ifdef CORE_DO_UNDO_SUPPORT
    m_old_row_height = layout_manager.sparse_row_range( m_line );
#endif
    layout_manager.row_height( m_line, m_new_row_height );
}

void set_row_height_command::un_execute()
{
#ifdef CORE_DO_UNDO_SUPPORT
    shared_worksheet_type ws = lock_worksheet_and_throw_if_not_there();
    sheet_layout_manager& layout_manager = ws->layout();
    for ( size_t start_idx = 0, stop_idx = m_old_row_height.size(); start_idx + 1 < stop_idx; start_idx += 2 ) {
        layout_manager.row_height( m_old_row_height[start_idx], m_old_row_height[start_idx+1] );
    }
#endif
}

DEFINE_CLONEABLE( set_row_height_command );
