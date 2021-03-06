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
struct calculate_leftb {
    template<class lhs_T>
    static variant transform( const lhs_T& v, const variant& count, const ::locale& l ) {
        try {
            return transform( v, count.as_double(), l );
        } catch ( const variant_conversion_exception& ) {}
        // text that cannot be translated into numbers causes the #VALUE! error value.
        return variant( variant::error_value );
    }

    template<class lhs_T>
    static variant transform( const lhs_T& v, double count, const ::locale& l ) {
        try { // text representations of numbers are evaluated.
            if ( 0 > count ) {
                return variant( variant::error_value );
            }
            if ( v.is_error() ) {
                return v;
            }
            return variant( ( v.as_string( l ) ).substr( 0, static_cast<size_t>( count ) ) );
        } catch ( const variant_conversion_exception& ) {}
        // text that cannot be translated into numbers causes the #VALUE! error value.
        return variant( variant::error_value );
    }
};

/*!
 * \brief
 * LEFTB returns the first character or characters in a text string,
 * based on the number of bytes (count) you specify.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the first character or characters in a text string, based on the number of bytes (count) you specify
 *
 * \details
 * This function is for use with bytes. Use function_left for characters.
 *
 * \see
 * function_left
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
interpreter_variant function_leftb( function_parameter& parameters )
{
    if ( parameters.count() == 0 || parameters.count() > 2 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    if ( parameters.count() > 1 ) {
        return function_helper::create_array_or_return_single_value<variant, variant, calculate_leftb>(
                   parameters[0],
                   parameters[1],
                   parameters.context().locale()
               );
    }
    variant v( 1.0 );
    return function_helper::create_array_or_return_single_value<variant, variant, calculate_leftb>(
               parameters[0], v, parameters.context().locale() );
    // LEFTB returns the first character or characters in a text string,
    // based on the number of bytes (count) you specify.
    // This function is for use with double-byte characters.
}
