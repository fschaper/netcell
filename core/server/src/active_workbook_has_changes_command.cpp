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
#include "wss/active_workbook_has_changes_command.hpp"
#include "wss/workbook.hpp"
#include "wss/invalid_workbook_exception.hpp"

active_worbook_has_changes_command::active_worbook_has_changes_command( session& s )
    : base_command<i_command>( s )
    , m_workbook_has_changes( false )
{}

void active_worbook_has_changes_command::execute()
{
    shared_workbook_type wb = m_session.selected().workbook().lock();
    if ( ! wb ) {
        throw invalid_workbook_exception();
    }
    m_workbook_has_changes = wb->has_changes();
}

active_worbook_has_changes_command::result_type active_worbook_has_changes_command::value() const
{
    return m_workbook_has_changes;
}

DEFINE_CLONEABLE( active_worbook_has_changes_command );
