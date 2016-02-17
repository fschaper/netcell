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
#include <boost/foreach.hpp>
#include <limits>
#define foreach BOOST_FOREACH

/*!
 * \brief
 * concatenates the cell values in the specified cell range, using the (optional) delimiter
 * String between them (if no delimiter specified = don't use anything between the values)
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the concatenated result string
 *
 * \see
 * function_concatenate
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
interpreter_variant function_concatenate_range( function_parameter& parameters )
{

    std::string sep = "";
    if ( parameters.count() > 2 || parameters.count() < 1 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    if ( parameters.count() == 2 && parameters[1].type() == variant::type_string ) {
        sep = parameters[1].string();
    } else {
        sep = "";
    }

    interpreter_variant array1 = parameters[0];

    interpreter_variant result( variant( "" ) );
    std::string res = result.as_string( parameters.context().locale() );
    if ( array1.i_type() == interpreter_variant::type_range ) {
        range_reference& rref = range_reference_cast( array1.reference() );
        sparse_range_array sra( rref, parameters.context() );
        const size_t colWidth = rref.actualize().position().column_count();
        const size_t rows = sra.size() / colWidth;


        for ( unsigned int i = 0; i < colWidth; i++ ) {
            for ( unsigned int j = 0; j < rows; j++ ) {
                variant val = sra( i, j );
                // Error values cause errors.
                if ( val.type() == variant::type_error ) {
                    return interpreter_variant( val );
                }

                res.append( static_cast<const variant&>( val ).as_string( parameters.context().locale() ) );
                if ( !( i == colWidth - 1 && j == rows - 1 ) ) {
                    res.append(  static_cast<const std::string&>( sep ) );
                }
            }
        }



    } else {

        return interpreter_variant( variant::error_value );

    }



    return interpreter_variant( variant( res ) );

}
