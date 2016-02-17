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
 *  Frieder Hofmann <frieder.hofmann@jedox.com>
 *  Radu Ialovoi <ialovoi@yalos-solutions.com>
 */

#include "precompiled_header.hpp"

#if !defined(FUNCTION_HAS_PRECOMPILED_HEADER ) || FUNCTION_HAS_PRECOMPILED_HEADER == 0
#   include "function_helper.hpp"
#endif // FUNCTION_HAS_PRECOMPILED_HEADER == 0

/*!
 * \brief
 * little helper
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
template<bool default_value>
struct check_if_logical {
    static bool check_for_non_default( const variant& v ) {
        return !v.is_boolean();
    }
};
template<>
bool check_if_logical<false>::check_for_non_default( const variant& v )
{
    return !check_if_logical<true>::check_for_non_default( v );
}

/*!
 * \brief
 * Returns true, if the argument refers to a logical value.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * logical value, if the argument refers to a logical value
 *
 * \details
 *
 * \see
 * function_isnumber
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
interpreter_variant function_islogical( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #REF! until we can give a message-window.
        return interpreter_variant( variant::error_ref );
    }

    return function_helper::create_array_or_return_single_value<check_if_logical>( parameters[0] );
    // Returns true, if the argument refers to a logical value.
}
