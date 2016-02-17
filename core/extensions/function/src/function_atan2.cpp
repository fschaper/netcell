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
 * Returns the arctangent, or inverse tangent, of the specified x- and y-coordinates.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the arctangent
 *
 * \details
 * The arctangent is the angle from the x-axis to a line containing the origin (0,0) and a point with coordinates (x_num, y_num).
 * The angle is given in radians between -pi and pi, excluding -pi.
 *
 * \see
 * function_atan | function_tan | function_asin | function_acos | function_pi
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
interpreter_variant function_atan2( function_parameter& parameters )
{
    if ( parameters.count() != 2 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    // If there are less than 2 arguments, ATAN2 returns the #VALUE! error value.
    if ( parameters.count() < 2 ) {
        return interpreter_variant( variant::error_value );
    }
    // If any argument is nonnumeric, ATAN2 returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double || parameters[1].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }
    double x_num = parameters[0].numeric(); // the x-coordinate of the point.
    double y_num = parameters[1].numeric(); // the y-coordinate of the point.
    // If both x_num and y_num are 0, ATAN2 returns the #DIV/0! error value.
    if ( x_num == 0.0 && y_num == 0.0 ) {
        return interpreter_variant( variant::error_div_null );
    }
    return interpreter_variant( variant( atan2( x_num, y_num ) ) );
    // Returns the arctangent, or inverse tangent, of the specified x- and y-coordinates.
    // The arctangent is the angle from the x-axis to a line containing the origin (0,0)
    // and a point with coordinates (x_num, y_num).
    // The angle is given in radians between -pi and pi, excluding -pi.
}
