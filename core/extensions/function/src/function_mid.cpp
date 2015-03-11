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
 * MID returns a specific number of characters from a text string, starting at the position you specify,
 * based on the number of characters you specify.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the specific number of characters from a text string
 *
 * \details
 * MIDB is for use with double-byte characters.
 *
 * \see
 * function_midb | function_code | function_find | function_left | function_right | function_search
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */

interpreter_variant function_mid( function_parameter& parameters )
{
    if ( parameters.count() != 3 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    // If the first argument is no text or either other argument is nonnumeric, MID returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_string || parameters[1].type() != variant::type_double || parameters[2].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }
    if ( parameters[0].is_error() ) {
        return parameters[0];
    }
    std::string text = parameters[0].string(); // the text string containing the characters you want to extract.
    int start_num = static_cast<int>( parameters[1].numeric() ); // the position of the first character you want to extract in text.
    // The first character in text has start_num 1, and so on.
    int num_chars = static_cast<int>( parameters[2].numeric() ); // specifies the number of characters you want MID to return from text.
    // If start_num is less than 1 or num_chars is negative, MID returns the #VALUE! error value.
    if ( start_num < 1 || num_chars < 0 ) {
        return interpreter_variant( variant::error_value );
    }
    // If start_num is greater than the length of text, MID returns ""(empty text).
    if ( static_cast<unsigned>( start_num ) > text.length() ) {
        return interpreter_variant( variant( "" ) );
    }
    // If start_num is less than the length of text, but start_num plus num_chars exceeds the length of text,
    // MID returns the characters up to the end of text.
    text = text.substr( ( start_num - 1 ), num_chars );

    return interpreter_variant( variant( text ) );
    // MID returns a specific number of characters from a text string, starting at the position you specify,
    // based on the number of characters you specify.
}


