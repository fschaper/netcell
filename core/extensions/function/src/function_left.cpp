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

#if !defined(FUNCTION_HAS_PRECOMPILED_HEADER ) || FUNCTION_HAS_PRECOMPILED_HEADER == 0
#   include "function_helper.hpp"
#   include <wss/variant_conversion_exception.hpp>
#endif // FUNCTION_HAS_PRECOMPILED_HEADER == 0

/*!
 * \brief
 * the actual calculation is done in this helper struct
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
struct calculate_left {
    template<class lhs_T>
    static variant transform( const lhs_T& v, const variant& c, const ::locale& l ) {
        try { // text representations of numbers are evaluated.
            double count = c.as_double();
            if ( 0 > count ) {
                return variant( variant::error_value );
            }
            if ( v.is_error() ) {
                return v;
            }

            std::string utf8_str = v.as_string( l );

            size_t total = 0;
            //correction for count with respect to utf8
            for ( size_t i = 0, e = utf8_str.size(); i < e; i++ ) {
                if ( 0 == count ) {
                    break;
                }
                unsigned char crt = ( unsigned char ) utf8_str[i];
                if ( 0xC0 == ( crt & 0xE0 )  ) {     //two bytes character
                    i++;
                    total += 2;
                } else if ( 0xE0 == ( crt & 0xF0 ) ) {    //three bytes character
                    i += 2;
                    total += 3;
                } else if ( 0xF0 == ( crt & 0xF8 ) ) {     //four bytes character
                    i += 3;
                    total += 4;
                } else {
                    total++;
                }
                count--;
            }

            return variant( utf8_str.substr( 0, static_cast<size_t>( total ) ) );
        } catch ( const variant_conversion_exception& ) {}
        // text that cannot be translated into numbers causes the #VALUE! error value.
        return variant( variant::error_value );
    }
};

/*!
 * \brief
 * LEFT returns the first character or characters in a text string,
 * based on the number of characters (count) you specify.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the first character or characters in a text string, based on the number of characters (count) you specify
 *
 * \details
 * This function is for use with characters. Use function_leftb for bytes.
 *
 * \see
 * function_leftb | function_mid | function_right
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 * Radu Ialovoi <ialovoi@yalos-solutions.com>
 */
interpreter_variant function_left( function_parameter& parameters )
{
    if ( 0 == parameters.count() || 2 < parameters.count() ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    if ( parameters.count() > 1 ) {
        return function_helper::create_array_or_return_single_value<variant, variant, calculate_left>(
                   parameters[0],
                   parameters[1],
                   parameters.context().locale()
               );
    }
    variant v( 1.0 );
    return function_helper::create_array_or_return_single_value<variant, variant, calculate_left>(
               parameters[0], v, parameters.context().locale() );
    // LEFT returns the first character or characters in a text string,
    // based on the number of characters (count) you specify.
}
