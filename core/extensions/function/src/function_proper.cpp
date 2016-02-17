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
 * Capitalizes the first letter in a text string and any other letters in text
 * that follow any character other than a letter.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the converted text
 *
 * \details
 * Converts all other letters to lowercase letters.
 *
 * \see
 * function_toupper | function_tolower
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
interpreter_variant function_proper( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    // If the argument is no text, it is returned unchanged.
    if ( parameters[0].type() != variant::type_string ) {
        return interpreter_variant( parameters[0] );
    }

    std::string text = parameters[0].string();
    bool inWord = false;
    for ( unsigned int i = 0; i < text.length(); i++ ) {
        if ( isalpha( text[i] ) ) {
            if ( inWord ) {
                text[i] = tolower( text[i] );
            } else {
                text[i] = toupper( text[i] );
                inWord = true;
            }
        } else {
            inWord = false;
        }
    }

    return interpreter_variant( variant( text ) );
    // Capitalizes the first letter in a text string and
    // any other letters in text that follow any character other than a letter.
    // Converts all other letters to lowercase letters.
}

