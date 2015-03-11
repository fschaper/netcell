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
 * FIND finds one string (find) within another text string (text),
 * and returns the number of the starting position of find, from the first character of text.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the number of the starting position of the found text
 *
 * \details
 * FIND is case sensitive and doesn't allow wildcard characters.
 *
 * \see
 * function_findb | function_mid | function_search | function_searchb
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
interpreter_variant function_find( function_parameter& parameters )
{
    if ( parameters.count() < 2 || parameters.count() > 3 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    // If any of the first two arguments is no text, FIND returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_string || parameters[1].type() != variant::type_string ) {
        return interpreter_variant( variant::error_value );
    }

    std::string find = parameters[0].string(); // the text you want to find.
    std::string text = parameters[1].string(); // the text containing the text you want to find.
    int begin = -1;
    if ( parameters.count() > 2 ) {
        // If the third parameter is not greater than zero, FIND returns the #VALUE! error value.
        if ( parameters[2].numeric() < 1.0 ) {
            return interpreter_variant( variant::error_value );
        }
        // If the third parameter is greater than the length of text, FIND returns the #VALUE! error value.
        if ( parameters[2].numeric() >= text.length() + 1 ) {
            return interpreter_variant( variant::error_value );
        }
        begin = ( static_cast<int>( parameters[2].numeric() ) - 1 );
    } // specifies the character at which to start the search.
    // The first character in text is character number 1.
    // If you omit the third parameter, it is assumed to be 1.

    // If text is ""(empty text), FIND matches the first character in the search string.
    // That is, the character numbered by the third parameter or 1.
    if ( text == "" ) {
        return interpreter_variant( variant( static_cast<double>( std::max( 1, begin + 1 ) ) ) );
    }
    size_t pos = 0;
    if ( begin != -1 ) {
        pos = text.find( find, begin ) + 1;
    } else {
        pos = text.find( find, 0 ) + 1;
    }
    // If find does not appear in text, FIND returns the #VALUE! error value.
    if ( pos == 0 ) {
        return interpreter_variant( variant::error_value );
    }

    return interpreter_variant( variant( static_cast<double>( pos ) ) );
    // FIND finds one string (find) within another text string (text),
    // and returns the number of the starting position of find, from the first character of text.
    // FIND is case sensitive and doesn't allow wildcard characters.
}

