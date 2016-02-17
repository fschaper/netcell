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
#include "wss/dependency_info_utility.hpp"
#include "wss/application.hpp"
#include "wss/i_dependency_reference.hpp"
#include "wss/workbook.hpp"
#include "wss/worksheet.hpp"

dependency_info_list_type to_dependency_info( const range::range_set_type& rs )
{
    dependency_info_list_type return_value;
    for ( range::range_set_type::const_iterator it = rs.begin(), end_it = rs.end(); it != end_it; ++it ) {
        //foreach( const range & sr, rs ) {
        shared_worksheet_type sw( ( *it ).worksheet().lock() );
        if ( sw ) {
            return_value.push_back( dependency_info( sw->uuid(), sw->parent()->uuid(), sw->parent()->parent()->uuid(), ( *it ).coverage() ) );
        }
    }
    return return_value;
}

