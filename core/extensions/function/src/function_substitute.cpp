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
 * Substitutes new_text for old_text in a text string.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the substituted text
 *
 * \details
 * Use SUBSTITUTE when you want to replace specific text in a text string.
 *
 * \see
 * function_replace | function_trim
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
interpreter_variant function_substitute( function_parameter& parameters )
{
    if ( parameters.count() < 3 || parameters.count() > 4 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    // If any of the first 3 arguments is no text, SUBSTITUTE returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_string || parameters[1].type() != variant::type_string || parameters[2].type() != variant::type_string ) {
        return interpreter_variant( variant::error_value );
    }

    std::string text = parameters[0].string(); // the text or the reference to a cell containing text, for which you want to substitute characters.
    std::string old_text = parameters[1].string(); // the text you want to replace.
    std::string new_text = parameters[2].string(); // the text you want to replace old_text with.

    int begin = -1;
    if ( parameters.count() > 3 ) {
        begin = ( static_cast<int>( parameters[3].numeric() ) - 1 );
    } // specifies which occurrence of old_text you want to replace with new_text.
    // If you specify it, only that instance of old_text is replaced.
    // Otherwise, every occurrence of old_text in text is changed to new_text.
    if ( begin != -1 ) {
        boost::algorithm::replace_nth( text, old_text, begin, new_text );
    } else {
        boost::algorithm::replace_all( text, old_text, new_text );
    }
    return interpreter_variant( variant( text ) );
    // Substitutes new_text for old_text in a text string.
    // Use SUBSTITUTE when you want to replace specific text in a text string.
}

