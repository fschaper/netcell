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
 *  Vali Nitu <vali@yalos-solutions.com>
 */

#include "precompiled_header.hpp"
#include "wss/formatter.hpp"

/*!
 * \brief
 * Converts a value to text in a specific number format.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * text in a specific number format if the second parameter could be parsed as a format,
 * types::XlError::XL_VALUE if not. returns types::XlError::XL_REF if the parameter count
 * does not equal 2
 *
 * \details
 *
 * \see
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
interpreter_variant function_text( function_parameter& parameters )
{
    if ( parameters.count() != 2 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_ref );
    }

    variant::variant_type type = parameters[0].type();

    if ( variant::type_array == type ) {
        return interpreter_variant( variant( variant::error_value ) );
    }

    if ( variant::type_double != type ) {
        return interpreter_variant( parameters[0] );
    }

    type = parameters[1].type();

    if ( variant::type_array == type || variant::type_bool == type ) {
        return interpreter_variant( variant( variant::error_value ) );
    }

    if ( variant::type_empty == type || variant::type_error == type ) {
        return interpreter_variant( variant( parameters[1] ) );
    }

    if ( variant::type_double == type ) {
        return interpreter_variant( variant( parameters[1].as_string( parameters.context().locale() ) ) );
    }

    std::string format_string = parameters[1].string();

    if ( format_string.empty() ) {
        return interpreter_variant( variant( format_string ) );
    }


    formatter::shared_format_engine_type    engine = formatter::instance().engine();

    if ( !engine ) {
        // TODO (fschaper) throw specialized exception
        throw std::logic_error( "no format engine" );
    }

    try {
        return interpreter_variant( engine->formatted_value_locale( parameters.session(), format_string, parameters[0] ) );
    } catch ( std::exception& ) {
        return interpreter_variant( format_string );
    }

}
