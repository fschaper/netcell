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
 * Repeats text a given number of times.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * a string which contains a text a given number of times
 *
 * \details
 * If number_times is 0, REPT returns "". If number_times is not an integer, it is truncated.
 * The result of the REPT function cannot be longer than 32767 characters, or REPT returns the #VALUE! error value.
 *
 * \see
 * function_concatenate
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
interpreter_variant function_rept( function_parameter& parameters )
{
    if ( parameters.count() != 2 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    unsigned int number_times = static_cast<unsigned int>( parameters[1].numeric() ); // a positive number specifying the number of times to repeat text.
    // If number_times is not an integer, it is truncated.
    interpreter_variant text = parameters[0]; // the text you want to repeat.
    if ( ( text.string() ).length() * number_times > 32767 ) {
        return interpreter_variant( variant::error_value );
    }
    interpreter_variant result( "" ); // If number_times is zero, REPT returns ""(empty text).
    std::string res = result.as_string( parameters.context().locale() );
    for ( unsigned int i = 0; i < number_times; i++ ) {
        res.append( text.string() );
    }


    return interpreter_variant( variant( res ) );
    // Repeats text a given number of times.
}

