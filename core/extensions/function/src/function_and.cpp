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
#include "internal_functions.hpp"

/*!
 * \brief
 * Returns true if all arguments are true; returns false if one or more argument is false.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the logical value if all arguments are true
 *
 * \details
 * The arguments must evaluate to logical values, or the arguments must be arrays or references that contain logical values.
 * If an array or reference argument contains text or empty cells, those values are ignored.
 *
 * \see
 * function_or | function_not
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */

interpreter_variant function_and( function_parameter& parameters )
{
    internal::And iAnd( parameters );
    try {
        for ( size_t i = 0; i < parameters.count(); i++ ) {
            iAnd( parameters[i] );
        }
    } catch ( const variant& e ) {
        return interpreter_variant( e );
    }
    internal::AndStrategy::and_result res = iAnd;
    if ( res.has_value ) {
        return interpreter_variant( variant( res.result ) );
    } else {
        // If there are no logical values, AND returns the #VALUE! error value.
        return interpreter_variant( variant::error_value );
    }
}

