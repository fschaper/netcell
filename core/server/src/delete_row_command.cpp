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
#include "wss/delete_row_command.hpp"
#include "wss/worksheet.hpp"
#include "wss/invalid_worksheet_exception.hpp"

delete_row_command::delete_row_command( session& s, unsigned int row, unsigned int row_count )
    : abstract_undoable_command( s )
    , m_row( row )
    , m_row_count( row_count )
{}

void delete_row_command::execute()
{
    shared_worksheet_type ws = lock_worksheet_and_throw_if_not_there();
    ws->delete_row( m_session, m_row, m_row_count );
}

void delete_row_command::un_execute()
{
    shared_worksheet_type ws = lock_worksheet_and_throw_if_not_there();
    ws->insert_row( m_session, m_row, m_row_count );
}

DEFINE_CLONEABLE( delete_row_command );
