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
 * Returns the arccosine, or inverse cosine, of a number.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the arccosine
 *
 * \details
 * The arccosine is the angle whose cosine is number. The returned angle is given in radians in the range 0 to pi.
 *
 * \see
 * function_cos | function_asin | function_atan | function_atan2 | function_pi
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
interpreter_variant function_acos( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        return interpreter_variant( variant::error_n_a );
    }
    // If the argument is nonnumeric, ACOS returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }
    double number = parameters[0].numeric(); // number is the cosine of the angle you want.
    // And must be from -1 to 1, else ACOS returns the #NUM! error value.
    if ( number < -1.0 || number > 1.0 ) {
        return interpreter_variant( variant::error_num );
    }

    return interpreter_variant( variant( acos( number ) ) );
    // Returns the arccosine, or inverse cosine, of a number.
    // The arccosine is the angle whose cosine is number.
    // The returned angle is given in radians in the range 0 to pi.
}
