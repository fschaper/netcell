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
 * little helper
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
struct calculate_not {
    static variant transform( const variant& v, const locale& l ) {
        try {
            return variant( !v.as_boolean( l ) );
        } catch ( const variant_conversion_exception& ) {}
        return variant( variant::error_value );
    }
};

/*!
 * \brief
 * Reverses the logical value of its argument.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the reversed logical value
 *
 * \details
 * If the argument is false, NOT returns true. If the argument is true, NOT returns false.
 *
 * \see
 * function_and | function_or
 *
 * \author
 * Radu Ialovoi <ialovoi@yalos-solutions.com>
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
interpreter_variant function_not( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    return function_helper::create_array_or_return_single_value<calculate_not>( parameters[0], parameters.context().locale() );
    // Reverses the value of its argument.
    // If the argument is false, NOT returns true. If the argument is true, NOT returns false.
}
