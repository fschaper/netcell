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
#include "wss/set_default_row_height_command.hpp"
#include "wss/invalid_worksheet_exception.hpp"
#include "wss/worksheet.hpp"
#include "wss/sheet_layout_manager.hpp"

set_default_row_height_command::set_default_row_height_command( session& s, unsigned int row_height )
    : abstract_undoable_command( s )
#ifdef CORE_DO_UNDO_SUPPORT
    , m_old_height( 0 )
#endif
    , m_new_height( row_height )
    , m_worksheet( s.selected().worksheet() )
{}

void set_default_row_height_command::execute()
{
    shared_worksheet_type ws = lock_worksheet_and_throw_if_not_there();
#ifdef CORE_DO_UNDO_SUPPORT
    if ( supports_do_undo::check( ws ) ) {
        m_old_height = ws->layout().default_row_height();
    }
#endif
    ws->layout().default_row_height( m_new_height );
}

void set_default_row_height_command::un_execute()
{
#ifdef CORE_DO_UNDO_SUPPORT
    shared_worksheet_type ws = lock_worksheet_and_throw_if_not_there();
    assert( "un_execute called on a command that is on a temporary wb or on a cloned sheet!" && supports_do_undo::check( ws ) );
    m_new_height = ws->layout().default_row_height();
    ws->layout().default_row_height( m_old_height );
#endif
}

DEFINE_CLONEABLE( set_default_row_height_command );

