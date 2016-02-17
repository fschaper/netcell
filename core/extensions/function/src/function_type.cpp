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
 * Returns the type of value.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the type of value
 *
 * \details
 * Use TYPE when the behavior of another function depends on the type of value in a particular cell.
 *
 * \see
 * function_isblank | function_iserror | function_islogical | function_isnumber | function_isref | function_istext
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
interpreter_variant function_type( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    // If the argument is a number, TYPE returns 1.
    if ( parameters[0].type() == variant::type_double ) {
        return interpreter_variant( variant( 1.0 ) );
    }
    // If the argument is text, TYPE returns 2.
    if ( parameters[0].type() == variant::type_string ) {
        return interpreter_variant( variant( 2.0 ) );
    }
    // If the argument is a logical value, TYPE returns 4.
    if ( parameters[0].type() == variant::type_bool ) {
        return interpreter_variant( variant( 4.0 ) );
    }
    // If the argument is an array, TYPE returns 64.
    if ( parameters[0].type() == variant::type_array ) {
        return interpreter_variant( variant( 64.0 ) );
    }
    // If the argument is an error value, TYPE returns 16.
    return interpreter_variant( variant( 16.0 ) );
    // Returns the type of value.
}
