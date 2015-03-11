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


/*!
 * \brief
 * Returns a reference to a range that is a specified number of rows and columns from a cell or range of cells.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the reference to the range
 *
 * \details
 *
 *
 * \see
 * function_address | function_choose | function_hlookup | function_index | function_indirect | function_lookup | function_match | function_vlookup
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
interpreter_variant function_offset( function_parameter& parameters )
{

    if ( parameters.count() < 3 || parameters.count() > 5 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }


    if ( parameters[0].i_type() != interpreter_variant::type_range ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    double row = 0.0;
    double col = 0.0;

    if ( parameters[1].type() == variant::type_string ) {
        try { // text representations of numbers are evaluated.
            row = boost::lexical_cast<int>( static_cast<const std::string&>( parameters[1].string() ) );
        } catch ( boost::bad_lexical_cast& ) {
            // text that cannot be translated into numbers causes the #VALUE! error value.
            return interpreter_variant( variant::error_value );
        }
    } else { // Arguments that are numbers or logical values are counted.
        row = static_cast<int>( parameters[1].numeric() );
    }

    if ( parameters[2].type() == variant::type_string ) {
        try { // text representations of numbers are evaluated.
            col = boost::lexical_cast<int>( static_cast<const std::string&>( parameters[2].string() ) );
        } catch ( boost::bad_lexical_cast& ) {
            // text that cannot be translated into numbers causes the #VALUE! error value.
            return interpreter_variant( variant::error_value );
        }
    } else { // Arguments that are numbers or logical values are counted.
        col = static_cast<int>( parameters[2].numeric() );
    }

    range_reference& rref = range_reference_cast( parameters[0].reference() );
    unsigned int width =  rref.actualize().position().column_count(); // the number of columns ( the length of a row )
    unsigned int height =  rref.actualize().position().row_count(); // the number of rows ( the length of a column )


    if ( parameters.count() >= 4 ) {
        if ( parameters[3].type() == variant::type_string ) {
            try { // text representations of numbers are evaluated.
                height = boost::lexical_cast<unsigned int>( static_cast<const std::string&>( parameters[3].string() ) );
            } catch ( boost::bad_lexical_cast& ) {
                // text that cannot be translated into numbers causes the #VALUE! error value.
                return interpreter_variant( variant::error_value );
            }
        } else { // Arguments that are numbers or logical values are counted.
            height = static_cast<unsigned int>( parameters[3].numeric() );
            if ( 0 >= height ) {
                return interpreter_variant( variant::error_ref );
            }
        }
    }

    if ( parameters.count() == 5 ) {
        if ( parameters[4].type() == variant::type_string ) {
            try { // text representations of numbers are evaluated.
                width = boost::lexical_cast<unsigned int>( static_cast<const std::string&>( parameters[4].string() ) );
            } catch ( boost::bad_lexical_cast& ) {
                // text that cannot be translated into numbers causes the #VALUE! error value.
                return interpreter_variant( variant::error_value );
            }
        } else { // Arguments that are numbers or logical values are counted.
            width = static_cast<unsigned int>( parameters[4].numeric() );
            if ( 0 >= width ) {
                return interpreter_variant( variant::error_ref );
            }
        }
    }

    range_reference::actual actual_reference( rref.actualize() );
    if ( !actual_reference.is_valid() ) {
        return interpreter_variant( variant::error_ref );
    }
    const sheet_range area = actual_reference.position();

    sheet_point ul = sheet_point( area.upper_left().row() + static_cast<boost::uint_fast32_t>( row ),  area.upper_left().column() + static_cast<boost::uint_fast32_t>( col ) );
    sheet_point lr = sheet_point( area.upper_left().row() + static_cast<boost::uint_fast32_t>( row + height - 1 ),  area.upper_left().column() + static_cast<boost::uint_fast32_t>( col + width - 1 ) );

    sheet_range sr = sheet_range( ul, lr );

    precedent_proxy proxy( parameters.context().caller() );

    range_reference& res = range_reference_cast( proxy.register_dependency( parameters.context().caller()->worksheet().lock()->cells(), sr ) );

    sparse_range_array sra( res, parameters.context() );

    //unsigned int xmax = res.actualize().position().column_count();
    //unsigned int ymax = res.actualize().position().row_count();

    variant::sparse_array_type resultArray;
    for ( unsigned int i = 0; i < height; i++ ) {
        for ( unsigned int j = 0; j < width; j++ ) {
            variant val = sra( j, i );
            resultArray.push_back( variant( val ) );
        }
    }

    variant result( resultArray, width );


    range_reference::actual res_reference( res.actualize() );
    if ( !res_reference.is_valid() ) {
        return interpreter_variant( variant::error_ref );
    }

    //return interpreter_variant( variant( proxy.register_dependency( parameters.context().caller()->worksheet().lock()->cells(), sr ) ) );

    return interpreter_variant( result );


}

