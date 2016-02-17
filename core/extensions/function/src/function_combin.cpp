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
 * Returns the number of combinations for a given number of items.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the number of combinations
 *
 * \details
 * Use COMBIN to determine the total possible number of groups for a given number of items.
 *
 * \see
 * function_fact | function_permut
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
interpreter_variant function_combin( function_parameter& parameters )
{
    if ( parameters.count() != 2 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    // If either argument is non numeric, COMBIN returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double || parameters[1].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }

    // Numeric arguments are truncated to integers.
    // the number of items.
    long long number = static_cast<long long>( parameters[0].numeric() );
    // the number of items in each combination.
    long long number_chosen = static_cast<long long>( parameters[1].numeric() );

    // If number < 0, number_chosen < 0, or number < number_chosen, COMBIN returns the #NUM! error value.
    if ( number < 0 || number_chosen < 0 || number < number_chosen ) {
        return interpreter_variant( variant::error_num );
    }

    return interpreter_variant( variant( static_cast<double>( combin( number, number_chosen ) ) ) );
    // Returns the number of combinations (groups with number_chosen items) for a given number of items (number).
}
