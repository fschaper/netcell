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
#include "wss/get_sparse_max_cell_width_command.hpp"
#include "wss/sheet_layout_manager.hpp"

get_sparse_max_cell_width_command::get_sparse_max_cell_width_command( session& s, const sheet_layout_trait::line_type& from_to )
    : base_command<i_command>::base_command( s ),
      m_from_to( from_to ) {}

void get_sparse_max_cell_width_command::execute()
{
    shared_worksheet_type ws = m_session.selected().worksheet().lock();
    if ( ! ws ) {
        throw invalid_worksheet_exception();
    }

    m_max_width = ws->layout().sparse_max_cell_width( m_session, m_from_to );
}

get_sparse_max_cell_width_command::result_type get_sparse_max_cell_width_command::value() const
{
    return m_max_width;
}

DEFINE_CLONEABLE( get_sparse_max_cell_width_command );
