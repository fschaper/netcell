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
 * Counts empty cells in a specified range of cells.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the number of empty cells in the specified range of cells
 *
 * \details
 * If the argument is no range, COUNTBLANK returns the #VALUE! error value.
 *
 * \see
 * function_countif
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
interpreter_variant function_countblank( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #REF! until we can give a message-window.
        return interpreter_variant( variant::error_ref );
    }
    // If the argument is no range, COUNTBLANK returns the #VALUE! error value.
    // The argument is the range from which you want to count the blank cells.
    if ( parameters[0].i_type() != interpreter_variant::type_range ) {
        return interpreter_variant( variant::error_value );
    }
    size_t sum = 0;
    range_reference& rref = range_reference_cast( parameters[0].reference() );
    sparse_range_array sra( rref, parameters.context() );
    unsigned int xmax = rref.actualize().position().row_count();
    unsigned int ymax = rref.actualize().position().column_count();
    for ( unsigned int y = 0; y < ymax; y++ ) {
        for ( unsigned int x = 0; x < xmax; x++ ) {
            if ( sra( y, x ).is_empty() ) {
                // Counts empty cells, cells with formulas that return ""(empty text) are also counted.
                ++sum;
            }
        }
    }

    return interpreter_variant( variant( static_cast<double>( sum ) ) );
    // Counts empty cells in a specified range of cells.
}
