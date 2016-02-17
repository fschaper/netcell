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
 * LEN returns the number of characters in a text string.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the number of characters in the text string
 *
 * \details
 * LENB is for use with double-byte characters.
 *
 * \see
 * function_lenb | function_exact | function_search
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 * Radu Ialovoi <ialovoi@yalos-solutions.com>
 */
interpreter_variant length( const std::string utf8_str )
{

    //corection for size with respect to utf8
    size_t length = 0;
    for ( size_t i = utf8_str.size(); i > 0; i-- ) {
        if ( 0x80 != ( ( ( unsigned char ) utf8_str[i-1] ) & 0xC0 ) ) {  //test for 10xxxxxx (part of a multi-byte character).
            ++length;
        }
    }

    return interpreter_variant( variant( static_cast<double>( length ) ) );
}

interpreter_variant function_len( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    // If the argument is not a string, LEN returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_string ) {
        try {
            //return interpreter_variant( variant::error_value );
            return length( parameters[0].as_string( parameters.context().locale() )  );
        } catch ( std::exception& ) {
            return interpreter_variant( variant::error_value );
        }
    } else {
        return length( parameters[0].string() );
    }
    return interpreter_variant( 0.0 );


    // LEN returns the number of characters in a text string.
}
