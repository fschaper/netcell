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
 * Returns the matrix product of two arrays.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the matrix product of the two arrays
 *
 * \details
 * MMULT must be entered as an array formula in a range that has the same number
 * of rows as the first array and the same number of columns as the second array.
 * Select the range starting with the formula cell, press F2, and then press CTRL SHIFT ENTER together.
 *
 * \see
 * function_mdeterm | function_minverse | function_transpose
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
interpreter_variant function_mmult( function_parameter& parameters )
{
    if ( parameters.count() != 2 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    interpreter_variant array1 = parameters[0];
    interpreter_variant array2 = parameters[1];
    variant::sparse_array_type arr1, arr2;
    if ( array1.i_type() == interpreter_variant::type_range || array1.type() == variant::type_array ) {
        size_t colWidth1;
        if ( array1.i_type() == interpreter_variant::type_range ) { // TODO: sparse
            range_reference& rref1 = range_reference_cast( array1.reference() );
            sparse_range_array sra1( rref1, parameters.context() );
            size_t imax1 = sra1.size();
            size_t xmax1 = rref1.actualize().position().column_count();
            arr1 = variant::sparse_array_type( imax1 );
            for ( unsigned int i = 0; i < imax1; i++ ) {
                arr1[i] = sra1[i];
            }
            colWidth1 = xmax1;
        } else {
            arr1 = array1.array();
            colWidth1 = array1.column_width();
        }
        size_t arraySize1 = arr1.size();
        size_t rows1 = arraySize1 / colWidth1;
        for ( unsigned int i1 = 0; i1 < arraySize1; i1++ ) {
            variant val1 = arr1[i1];
            // Error values cause errors.
            if ( val1.type() == variant::type_error ) {
                return interpreter_variant( val1 );
            }
            // If any cell contains no number, MMULT returns the #VALUE! error value.
            if ( val1.type() != variant::type_double ) {
                return interpreter_variant( variant::error_value );
            }
        }
        if ( array2.i_type() == interpreter_variant::type_range || array2.type() == variant::type_array ) {
            size_t colWidth2;
            if ( array2.i_type() == interpreter_variant::type_range ) { // TODO: sparse
                range_reference& rref2 = range_reference_cast( array2.reference() );
                sparse_range_array sra2( rref2, parameters.context() );
                size_t imax2 = sra2.size();
                size_t xmax2 = rref2.actualize().position().column_count();
                arr2 = variant::sparse_array_type( imax2 );
                for ( unsigned int i = 0; i < imax2; i++ ) {
                    arr2[i] = sra2[i];
                }
                colWidth2 = xmax2;
            } else {
                arr2 = array2.array();
                colWidth2 = array2.column_width();
            }
            size_t arraySize2 = arr2.size();
            size_t rows2 = arraySize2 / colWidth2;
            for ( unsigned int i2 = 0; i2 < arraySize2; i2++ ) {
                variant val2 = arr2[i2];
                // Error values cause errors.
                if ( val2.type() == variant::type_error ) {
                    return interpreter_variant( val2 );
                }
                // If any cell contains no number, MMULT returns the #VALUE! error value.
                if ( val2.type() != variant::type_double ) {
                    return interpreter_variant( variant::error_value );
                }
            }
            // If the number of columns in array1 is different from the number of rows in array2, MMULT returns the #VALUE! error value.
            if ( colWidth1 != rows2 ) {
                return interpreter_variant( variant::error_value );
            }
            variant::sparse_array_type resultArray;
            for ( unsigned int i = 0; i < rows1; i++ ) {
                for ( unsigned int j = 0; j < colWidth2; j++ ) {
                    double sum = 0.0;
                    for ( unsigned int k = 0; k < colWidth1; k++ ) {
                        sum += static_cast<const variant&>( arr1[i*colWidth1+k] ).numeric() * static_cast<const variant&>( arr2[k*colWidth2+j] ).numeric();
                    }
                    resultArray.push_back( sum ); // Fill resultArray row by row.
                }
            }
            variant result( resultArray, ( unsigned int )colWidth2 );
            return interpreter_variant( result );
            // Returns the matrix product of the two arrays.
        } else {
            // Error values cause errors.
            if ( array2.type() == variant::type_error ) {
                return array2;
            }
            // If any cell contains no number, MMULT returns the #VALUE! error value.
            if ( array2.type() != variant::type_double ) {
                return interpreter_variant( variant::error_value );
            }

            if ( arraySize1 != 1 ) {
                return interpreter_variant( variant::error_value );
            }
            variant content1 = arr1[0];
            // Error values cause errors.
            if ( content1.type() == variant::type_error ) {
                return interpreter_variant( content1 );
            }
            // If any cell contains no number, MMULT returns the #VALUE! error value.
            if ( content1.type() != variant::type_double ) {
                return interpreter_variant( variant::error_value );
            }
            return interpreter_variant( content1.numeric() * array2.numeric() );
        }
    } else {
        // Error values cause errors.
        if ( array1.type() == variant::type_error ) {
            return array1;
        }
        // If any cell contains no number, MMULT returns the #VALUE! error value.
        if ( array1.type() != variant::type_double ) {
            return interpreter_variant( variant::error_value );
        }

        if ( array2.i_type() == interpreter_variant::type_range || array2.type() == variant::type_array ) {
            if ( array2.i_type() == interpreter_variant::type_range ) { // TODO: sparse
                range_reference& rref2 = range_reference_cast( array2.reference() );
                sparse_range_array sra2( rref2, parameters.context() );
                size_t imax2 = sra2.size();
                arr2 = variant::sparse_array_type( imax2 );
                for ( unsigned i = 0; i < imax2; i++ ) {
                    arr2[i] = sra2[i];
                }
            } else {
                arr2 = array2.array();
            }
            size_t arraySize2 = arr2.size();
            if ( arraySize2 != 1 ) {
                return interpreter_variant( variant::error_value );
            }
            variant content2 = arr2[0];
            // Error values cause errors.
            if ( content2.type() == variant::type_error ) {
                return interpreter_variant( content2 );
            }
            // If any cell contains no number, MMULT returns the #VALUE! error value.
            if ( content2.type() != variant::type_double ) {
                return interpreter_variant( variant::error_value );
            }
            return interpreter_variant( array1.numeric() * content2.numeric() );
        } else {
            // Error values cause errors.
            if ( array2.type() == variant::type_error ) {
                return array1;
            }
            // If any cell contains no number, MMULT returns the #VALUE! error value.
            if ( array2.type() != variant::type_double ) {
                return interpreter_variant( variant::error_value );
            }
            return interpreter_variant( array1.numeric() * array2.numeric() );
        }
    }

    // making gcc happy for now; a design cleanup is required!
    return interpreter_variant( variant::error_value );
}
