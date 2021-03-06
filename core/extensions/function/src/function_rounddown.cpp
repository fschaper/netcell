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
 * Rounds a number down, toward zero.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the rounded number
 *
 * \details
 * If num_digits is greater than 0, then number is rounded down to the specified number of decimal places.
 * If num_digits is 0, then number is rounded down to the nearest integer.
 * If num_digits is less than 0, then number is rounded down to the left of the decimal point.
 *
 * \see
 * function_ceiling | function_floor | function_int | function_mround | function_round | function_roundup | function_trunc
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
interpreter_variant function_rounddown( function_parameter& parameters )
{
    if ( parameters.count() != 2 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    // If either argument is nonnumeric, ROUNDDOWN returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double || parameters[1].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }

    double number = parameters[0].numeric(); // the real number that you want rounded down.
    int num_digits = static_cast<int>( parameters[1].numeric() ); // the number of digits to which you want to round number.
    // If num_digits is greater than 0, then number is rounded down to the specified number of decimal places.
    // If num_digits is 0, then number is rounded down to the nearest integer.
    // If num_digits is less than 0, then number is rounded down to the left of the decimal point.
    double factor = pow( 10.0, num_digits );
    double result = 0.0;
    if ( number < 0.0 ) {
        result = ceil( number * factor ) / factor;
    } else {
        result = floor( number * factor ) / factor;
    }

    return interpreter_variant( variant( result ) );
    // Rounds a number down, toward zero.
}

