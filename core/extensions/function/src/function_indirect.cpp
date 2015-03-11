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
#include "wss/precedent_proxy.hpp"
#include "wss/worksheet.hpp"
#include "wss/workbook.hpp"
#include <wss/a1conversion.hpp>


/*!
 * \brief
 * Returns the reference specified by a text string.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \returns
 * the reference to the cell
 *
 * \details
 *
 * \see
 * function_offset
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
interpreter_variant function_indirect( function_parameter& parameters )
{

    if ( parameters.count() < 1 || parameters.count() > 2 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }


    bool a1 = true;

    if ( parameters.count() == 2 ) {
        if ( parameters[1].type() != interpreter_variant::type_bool ) {
            // formula-error! We give #N/A until we can give a message-window.
            return interpreter_variant( variant::error_n_a );
        } else {
            a1 = parameters[1].boolean();
            if ( !a1 ) {
                return interpreter_variant( variant::error_n_a );
            }
        }
    }



    if ( parameters[0].i_type() == interpreter_variant::type_range || parameters[0].type() == variant::type_string ) {
        try {
            shared_worksheet_type sw = parameters.context().caller()->worksheet().lock();
            std::string reference = parameters[0].string();

            std::string::size_type sheet_end = reference.find( '!' );

            if ( std::string::npos != sheet_end ) {
                std::string ws_name = reference.substr( 0, sheet_end );
                if ( !ws_name.empty() && ws_name[0] == '\'' ) {
                    ws_name = ws_name.substr( 1, ws_name.size() - 2 );
                }

                sw = sw->parent()->get( parameters.session(), utf8_ci_string( ws_name.c_str() ) );

                reference = reference.substr( sheet_end + 1, reference.size() );
            }

            sheet_point c = a1conversion::from_a1::cell( reference );
            range crt = sw->range( sheet_range( c ) );
            variant val = crt.value( parameters.session() );
            return interpreter_variant( val );
        } catch ( std::exception& ) {
            return interpreter_variant( variant::error_ref );
        }

    }


    return interpreter_variant( variant::error_value );



}

