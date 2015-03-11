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
 * Returns the factorial of a number.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the factorial
 *
 * \details
 * The factorial of a number is equal to 1*2*3*...*number.
 *
 * \see
 * function_factdouble | function_product
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
interpreter_variant function_fact( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    if ( parameters[0].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }

    double number = parameters[0].numeric(); // the nonnegative number you want the factorial of.
    // If number < 0 or number >= 171, FACT returns the #NUM! error value.
    // double ends at 1.7976931348623158e+308
    if ( number < 0.0 || number >= 171 ) {
        return interpreter_variant( variant::error_num );
    }

    double product = 1.0;
    // If number is not an integer, it is truncated.
    for ( int i = 2; i <= number; i++ ) {
        product *= i;
    }
    return interpreter_variant( variant( product ) );
    // Returns the factorial of a number. The factorial of a number is equal to 1*2*3*...*number.
}
