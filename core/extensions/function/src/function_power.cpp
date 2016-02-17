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
 * Returns the result of a number raised to a power.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the power
 *
 * \details
 * The "^" operator can be used instead of POWER to indicate to what power the base number is to be raised.
 * base^exponent
 *
 * \see
 * function_log | function_exp
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */

interpreter_variant function_power( function_parameter& parameters )
{
    if ( parameters.count() != 2 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    // If there are less than 2 arguments, POWER returns the #VALUE! error value.
    if ( parameters.count() < 2 ) {
        return interpreter_variant( variant::error_value );
    }
    // If any argument is nonnumeric, POWER returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double || parameters[1].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }
    double number = parameters[0].numeric(); // the base.
    double exponent = parameters[1].numeric(); // the exponent to which the base number is raised.
    // If the base is zero and the exponent negative, POWER returns the #DIV/0! error value.
    if ( number == 0.0 && exponent < 0.0 ) {
        return interpreter_variant( variant::error_div_null );
    }
    // If the base is negative and the exponent no integer, POWER returns the #NUM! error value.
    if ( number < 0.0 && exponent != floor( exponent ) ) {
        return interpreter_variant( variant::error_num );
    }
    return interpreter_variant( variant( pow( number, exponent ) ) );
    // Returns the result of a number raised to a power.
}

