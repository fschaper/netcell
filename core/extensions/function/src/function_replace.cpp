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
 * Replaces part of a text, based on the number of characters you specify, with a different text string.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * text containing the replacement
 *
 * \details
 * This function is for use with characters. Use function_replaceb for bytes.
 *
 * \see
 * function_replaceb | function_mid | function_search | function_substitute | function_trim
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
interpreter_variant function_replace( function_parameter& parameters )
{
    if ( parameters.count() != 4 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    using namespace std;

    interpreter_variant temp     = parameters[3];

    string new_text = string( "" );
    try {
        new_text = temp.as_string( parameters.context().locale() ); // the text that will replace characters in old_text.
    } catch ( std::exception& ) {
        return interpreter_variant( variant::error_value );
    }

    int count       = static_cast<int>( parameters[2].numeric() ); // the number of characters in old_text that you want REPLACE to replace with new_text.
    int begin       = static_cast<int>( parameters[1].numeric() ); // the position of the character in old_text that you want to replace with new_text.
    temp            = parameters[0];

    string old_text = string( "" );
    try {
        old_text = temp.as_string( parameters.context().locale() ); // the text in which you want to replace some characters.
    } catch ( std::exception& ) {
        return interpreter_variant( variant::error_value );
    }

    string first_part = old_text.substr( 0, begin - 1 );
    string end_part = old_text.substr( ( begin + count ) - 1 );

    return interpreter_variant( first_part + new_text + end_part );
    // Replaces part of a text, based on the number of characters you specify, with a different text string.
}

