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
 *  Radu Racariu <radu@yalos-solutions.com>
 */

#include "precompiled_header.hpp"

/*!
 * \brief
 * Uses index_num to return a value from the list of value arguments.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the index_num-th value from the list of value arguments
 *
 * \details
 * Use CHOOSE to select one of up to 29 values based on the index number.
 *
 * \see
 * function_index
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
interpreter_variant function_choose( function_parameter& parameters )
{
    // If there are less than 2 parameters, or if index_num is non numeric, CHOOSE returns the #VALUE! error value.
    if ( parameters.count() < 2 || parameters[0].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }

    unsigned int index_num = static_cast<unsigned int>( parameters[0].numeric() ); // specifies which value argument is selected.
    // index_num must be a number between 1 and at most 29, or a formula or reference to a cell containing a number between 1 and at most 29.
    // If index_num is less than 1 or greater than the number of the last value in the list, CHOOSE returns the #VALUE! error value.
    if ( index_num < 1 || index_num > parameters.count() - 1 ) {
        return interpreter_variant( variant::error_value );
    }
    return parameters[index_num];
    // Uses index_num to return a value from the list of value arguments.
    // Use CHOOSE to select one of up to 29 values based on the index number.
}
