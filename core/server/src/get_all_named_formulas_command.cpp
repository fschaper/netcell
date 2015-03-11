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
#include "wss/get_all_named_formulas_command.hpp"
#include "wss/workbook.hpp"
#include "wss/named_formula_exception.hpp"

#include "object_lookup.hpp"

get_all_named_formulas_command::get_all_named_formulas_command( session& s, shared_workbook_type& wb, sheet_point position /*= sheet_point(0,0) */ )
    : base_command<i_command>::base_command( s )
    , m_wb( wb )
    , m_position( position )
{}

void get_all_named_formulas_command::execute()
{
    shared_workbook_type wb = m_wb.lock();
    if ( !wb ) {
        throw named_formula_exception( "requested workbook does not exist!" );
    }
    m_cached_value = wb->named_formulas().get_all_as_strings( m_session, boost::uuids::nil_uuid(), m_position );
}

get_all_named_formulas_command::result_type get_all_named_formulas_command::value() const
{
    return m_cached_value;
}

DEFINE_CLONEABLE( get_all_named_formulas_command );
