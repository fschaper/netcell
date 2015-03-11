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
 *  Radu Ialovoi <ialovoi@yalos-solutions.com>
 */

#include "precompiled_header.hpp"


/*!
 * \brief
 * Returns a vertical range of cells as a horizontal range, or vice versa.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the transposed range
 *
 * \details
 * TRANSPOSE must be entered as an array formula in a range that has the same number
 * of rows and columns, respectively, as an array has columns and rows.
 *
 * \see
 * function_mdeterm | function_minverse | function_mmult
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
interpreter_variant function_transpose( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        return interpreter_variant( variant::error_ref );
    }
    interpreter_variant current = parameters[0];
    if ( current.i_type() == interpreter_variant::type_range ) { // TODO: sparse
        range_reference& rref = range_reference_cast( current.reference() );
        sparse_range_array sra( rref, parameters.context() );
        unsigned int xmax = rref.actualize().position().column_count();
        unsigned int ymax = rref.actualize().position().row_count();
        variant::sparse_array_type resultArray;
        for ( unsigned int rowi = 0; rowi < xmax; rowi++ ) { // Fill the resultArray row by row.
            for ( unsigned coli = 0; coli < ymax; coli++ ) {
                resultArray.push_back( sra( rowi, coli ) );// resultArray by rows - original array by columns.
            }
        }
        variant result( resultArray, ymax );
        return interpreter_variant( result );
    } else if ( current.type() == variant::type_array ) {
        const variant::sparse_array_type& arr = current.array();
        size_t arraySize = arr.size();
        unsigned int columnWidth = current.column_width(); // the number of columns ( the length of a row )
        size_t rowWidth = arraySize / columnWidth; // the number of rows ( the length of a column )
        variant::sparse_array_type resultArray;
        for ( unsigned int rowi = 0; rowi < columnWidth; rowi++ ) { // Fill the resultArray row by row.
            for ( unsigned int coli = 0; coli < rowWidth; coli++ ) {
                resultArray.push_back( arr[coli*columnWidth + rowi] ); // resultArray by rows - original array by columns.
            }
        }
        variant result( resultArray, static_cast<unsigned int>( rowWidth ) );
        return interpreter_variant( result );
    }
    return current;
}
