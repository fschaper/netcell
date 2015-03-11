/*!
 *  \file
 *  Copyright (C) 2006-2009 Jedox AG, Freiburg i.Br., Germany
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
#include "array_return_converter.hpp"

void array_return_converter::operator()( variant& value, const sheet_range& range )
{
    if ( value.is_array() ) {
        //if the range is a single cell, do nothing
        if ( 1 == range.count() ) {
            return;
        }

        // excel returns values not in a single blob but divided by rows
        // if more than one value needs to be returned
        variant converted( variant::type_array );
        const variant::variant_array_type& value_array = value.array();
        variant::variant_array_type& converted_array   = converted.array();

        const sheet_range::integer_type max_row = range.row_count();
        const sheet_range::integer_type max_column = range.column_count();

        for ( sheet_range::integer_type cr = /*range.upper_left().row()*/0; cr < max_row; ++cr ) {
            variant columns( variant::type_array );
            variant::variant_array_type& columns_array = columns.array();
            const sheet_range::integer_type row_offset = cr * max_column;

            for ( sheet_range::integer_type cc = /*range.upper_left().column()*/0; cc < max_column; ++cc ) {
                columns_array.push_back( value_array[row_offset + cc] );
            }
            converted_array.push_back( columns );
        }

        value = converted;
    }
}
