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
 * Removes all spaces from text except for single spaces between words.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the trimmed text
 *
 * \details
 * Use TRIM on text that you have received from another application that may have irregular spacing.
 *
 * \see
 * function_clean | function_mid | function_replace | function_substitute
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
interpreter_variant function_trim( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    // If the argument is no text, TRIM returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_string ) {
        return interpreter_variant( variant::error_value );
    }

    std::string text = parameters[0].string(); // the text from which you want spaces removed.

    typedef std::vector<std::string> SplitVector;
    SplitVector Elements;
    boost::algorithm::split( Elements, text, boost::algorithm::is_from_range( ' ', ' ' ) );

    std::string returnValue = "";
    for ( size_t i = 0; i < Elements.size(); i++ ) {
        if ( Elements[i] != " " && Elements[i] != "" ) {
            returnValue.append( Elements[i] );
            returnValue.append( " " );
        }
    }

    size_t newSize = returnValue.size();
    if ( newSize > 0 ) {
        returnValue = returnValue.substr( 0, newSize - 1 );
    }

    return interpreter_variant( variant( returnValue ) );
    // Removes all spaces from text except for single spaces between words.
}

