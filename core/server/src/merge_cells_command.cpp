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
#include "wss/merge_cells_command.hpp"
#include <wss/worksheet.hpp>
#include <wss/merged_cell_manager.hpp>
#include <wss/invalid_worksheet_exception.hpp>
#include "wss/range.hpp"


merge_cells_command::merge_cells_command( session& s, const sheet_range& range )
    : abstract_undoable_command( s ), m_range( range ), m_ws( s.selected().worksheet() )
{}

void merge_cells_command::execute()
{
    shared_worksheet_type ws = m_ws.lock();
    if ( !ws ) {
        throw invalid_worksheet_exception();
    }
    ws->range( m_range ).merge( m_session );
}

void merge_cells_command::un_execute()
{
#ifdef CORE_DO_UNDO_SUPPORT
    shared_worksheet_type ws = m_ws.lock();
    if ( !ws ) {
        throw invalid_worksheet_exception();
    }
    //TODO this is not always the right way to do this.
    ws->range( m_range ).un_merge( m_session );
#endif
}

DEFINE_CLONEABLE( merge_cells_command );
