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


/*!
 * \brief
 * Returns a value or the reference to a value from within a table or range.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the indexed value or reference
 *
 * \details
 * There are two forms of the INDEX function:
 * INDEX(array,row_num,column_num) returns the value of a specified cell or array of cells within array.
 * INDEX(reference,row_num,column_num,area_num) returns a reference to specified cells within reference.
 *
 * \see
 * function_choose
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
interpreter_variant function_index( function_parameter& parameters )
{
    //assert( param > 0 );
    if ( parameters.count() == 0 /*|| parameters.count() > 4*/ ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    unsigned int area_num = 1;
    long int row = 0; // the number of the row in the array: 1 for the first row in the array, 2 for the second row ...
    long int col = 0; // the number of the column in the array: 1 for the first column in the array, 2 for the second ...

    if ( parameters.count() > 3 ) {

        if ( parameters[parameters.count()-1].type() == variant::type_string ) {
            try { // text representations of numbers are evaluated.
                area_num = boost::lexical_cast<unsigned int>( static_cast<const std::string&>( parameters[parameters.count()-1].string() ) );
            } catch ( boost::bad_lexical_cast& ) {
                // text that cannot be translated into numbers causes the #VALUE! error value.
                return interpreter_variant( variant::error_value );
            }
        } else { // Arguments that are numbers or logical values are counted.
            area_num = static_cast<unsigned int>( parameters[parameters.count()-1].numeric() );
        }

        if ( parameters.count() > 1 && !parameters[parameters.count()-3].is_empty() ) {
            row = static_cast<long int>( parameters[parameters.count()-3].numeric() );
        }
        if ( parameters.count() > 2 && !parameters[parameters.count()-2].is_empty() ) {
            col = static_cast<long int>( parameters[parameters.count()-2].numeric() );
        }

    } else {

        if ( parameters.count() > 1 && !parameters[1].is_empty() ) {
            row = static_cast<long int>( parameters[1].numeric() );
        }
        if ( parameters.count() > 2 && !parameters[2].is_empty() ) {
            col = static_cast<long int>( parameters[2].numeric() );
        }

    }

    if ( row < 0 || col < 0 ) {
        return interpreter_variant( variant::error_ref );
    }

    if ( parameters[area_num-1].i_type() == interpreter_variant::type_range ) {
        range_reference& rref = range_reference_cast( parameters[area_num-1].reference() );
        sparse_range_array sra( rref, parameters.context() );
        long int xmax = ( long int ) rref.actualize().position().column_count(); // the number of columns ( the length of a row )
        long int ymax = ( long int ) rref.actualize().position().row_count(); // the number of rows ( the length of a column )

        //for one-dimensional arrays the row/col can be optional
        if ( 1 == xmax && 0 == col ) {
            col = 1;
        }
        if ( 1 == ymax && 0 == row ) {
            row = 1;
        }
        // If the specified cell is not within the array, INDEX returns the #REF! error value.
        if ( row > ymax || col > xmax ) {
            return interpreter_variant( variant::error_ref );
        }

        if ( row > 0 && col > 0 ) { // Get a single value.
            return interpreter_variant( sra( col - 1, row - 1 ) );
        }

        if ( row > 0 && col == 0 ) { // Get the whole row.
            variant::sparse_array_type resultArray( xmax );
            for ( long int x = 0; x < xmax; x++ ) {
                resultArray.push_back( sra( x, row - 1 ) );
            }
            variant result( resultArray, xmax );
            return interpreter_variant( result );
        }

        if ( row == 0 && col > 0 ) { // Get the whole column.
            variant::sparse_array_type resultArray( ymax );
            for ( long int y = 0; y < ymax; y++ ) {
                resultArray.push_back( sra( col - 1, y ) );
            }
            variant result( resultArray, 1 );
            return interpreter_variant( result );
        }

        if ( row == 0 && col == 0 ) { // Get the whole rectangle.
            variant::sparse_array_type resultArray( xmax * ymax );
            for ( long int y = 0; y < ymax; y++ ) {
                for ( long int x = 0; x < xmax; x++ ) {
                    resultArray.push_back( sra( x, y ) );
                }
            }
            variant result( resultArray, xmax );
            return interpreter_variant( result );
        }

        return interpreter_variant( variant::error_ref );
    } else if ( parameters[0].type() == variant::type_array ) {
        const variant::sparse_array_type& arr = parameters[0].array();
        long int arraySize = ( long int ) arr.size();
        long int cols = parameters[0].column_width();
        long int rows = arraySize / cols;
        // If the specified cell is not within the array, INDEX returns the #REF! error value.
        if ( row > rows || col > cols ) {
            return interpreter_variant( variant::error_ref );
        }

        if ( row > 0 && col > 0 ) { // Get a single value.
            return interpreter_variant( arr[ ( row-1 )*cols + col-1 ] );
        }

        if ( row > 0 && col == 0 ) { // Get the whole row.
            variant::sparse_array_type resultArray( cols );
            for ( long int coli = 0; coli < cols; coli++ ) {
                resultArray.push_back( arr[ ( row-1 )*cols + coli ] );
            }
            variant result( resultArray, cols );
            return interpreter_variant( result );
        }

        if ( row == 0 && col > 0 ) { // Get the whole column.
            variant::sparse_array_type resultArray( rows );
            for ( long int rowi = 0; rowi < rows; rowi++ ) {
                resultArray.push_back( arr[ rowi*cols + col-1 ] );
            }
            variant result( resultArray, 1 );
            return interpreter_variant( result );
        }

        if ( row == 0 && col == 0 ) {
            return parameters[0];
        }
        return interpreter_variant( variant::error_ref );
    } else {
        if ( row > 1 || col > 1 ) {
            return interpreter_variant( variant::error_ref );
        }
        return parameters[0];
    }
    // Returns the value of an element in a table or an array, selected by the row and column number indexes.
}

