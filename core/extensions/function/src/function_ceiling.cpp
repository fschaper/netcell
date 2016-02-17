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
 * Returns number rounded up, away from zero, to the nearest multiple of significance.
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
 * Regardless of the sign of number, a value is rounded up when adjusted away from zero.
 * If number is an exact multiple of significance, no rounding occurs.
 *
 * \see
 * function_floor | function_int | function_round | function_rounddown | function_roundup | function_trunc
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
interpreter_variant function_ceiling( function_parameter& parameters )
{
    if ( parameters.count() != 2 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    // If either argument is nonnumeric, CEILING returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double || parameters[1].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }
    double number = parameters[0].numeric(); // the value you want to round.
    double significance = parameters[1].numeric(); // the multiple to which you want to round.
    if ( number == 0.0 ) {
        return interpreter_variant( variant( 0.0 ) );
    }
    // If number and significance have different signs, CEILING returns the #NUM! error value.
    if ( number* significance < 0.0 || significance == 0.0 ) {
        return interpreter_variant( variant::error_num );
    }

    long long quotient = static_cast<long long>( number / significance );
    double rest = number - quotient * significance;

    if ( rest != 0.0 ) {
        ++quotient;
    }

    return interpreter_variant( variant( quotient * significance ) );
    // Returns number rounded up, away from zero, to the nearest multiple of significance.
}

