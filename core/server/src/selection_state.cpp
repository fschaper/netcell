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
#include "wss/selection_state.hpp"
#include "wss/application.hpp"
#include "wss/workbook.hpp"
#include "wss/server.hpp"

selection_state::selection_state()
    : m_range_on_sheet( sheet_point( 0, 0 ) )
{}

selection_state::~selection_state()
{
    m_workbook_active_worksheet.clear();
}

void selection_state::application( const shared_application_type& app )
{
    m_application = app;
    m_workbook = weak_workbook_type();
    m_worksheet = weak_worksheet_type();
}

void selection_state::workbook( const shared_workbook_type& wb )
{
    m_application = wb->parent();
    m_workbook = wb;
    active_sheet_map::const_iterator it( m_workbook_active_worksheet.find( wb->uuid() ) );
    m_worksheet = it != m_workbook_active_worksheet.end() ? it->second : weak_worksheet_type();
}

void selection_state::worksheet( const shared_worksheet_type& ws )
{
    m_application = ws->parent()->parent();
    m_workbook = ws->parent();
    m_worksheet = ws;
    m_workbook_active_worksheet[ ws->parent()->uuid() ] = ws;
}
