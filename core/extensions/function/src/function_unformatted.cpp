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
 * Returns the value that represents a particular formated string.
 *
 * \param function_parameter& parameters
 *
 * \returns
 * Returns the value that represents a particular formated string.
 *
 * \details
 *
 *
 * \see
 *
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com.com>
 */
interpreter_variant function_unformatted( function_parameter& parameters )
{


    if ( parameters.count() != 1 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }


    if ( parameters[0].type() != variant::type_string ) {
        return interpreter_variant( parameters[0] );
    }

    variant new_value;
    std::string  f;

    formatter::shared_format_engine_type    engine = formatter::instance().engine();

    if ( !engine ) {
        throw std::logic_error( "no format engine" );
    }


    if ( engine->find_format(  parameters.session(), parameters[0].string(), new_value, f ) ) {

        return interpreter_variant( new_value );

    }


    return interpreter_variant( parameters[0] );

}
