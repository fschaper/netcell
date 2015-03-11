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
 * Returns the matrix determinant of an array.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the matrix determinant of the argument
 *
 * \details
 *
 * \see
 * function_inverse | function_mmult | function_transpose
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */


interpreter_variant function_mdeterm( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    interpreter_variant current = parameters[0];
    if ( current.i_type() == interpreter_variant::type_range ) { // TODO: sparse
        range_reference& rref = range_reference_cast( current.reference() );
        sparse_range_array sra( rref, parameters.context() );
        unsigned int xmax = rref.actualize().position().column_count();
        unsigned int ymax = rref.actualize().position().row_count();
        // If the array does not have an equal number of rows and columns, MDETERM returns the #VALUE! error value.
        if ( xmax != ymax ) {
            return interpreter_variant( variant::error_value );
        }
        boost::numeric::ublas::matrix<double> m( xmax, ymax );
        for ( unsigned int i = 0; i < xmax; i++ ) {
            for ( unsigned int j = 0; j < xmax; j++ ) {
                variant val = sra[xmax * i + j];
                // Error values cause errors.
                if ( val.type() == variant::type_error ) {
                    return interpreter_variant( val );
                }
                // If any cell contains no number, MDETERM returns the #VALUE! error value.
                if ( val.type() != variant::type_double ) {
                    return interpreter_variant( variant::error_value );
                }
                m( i, j ) = val.numeric();
            }
        }
        try {
            return interpreter_variant( lu_det( m ) );
        } catch ( std::string ) {
            return interpreter_variant( variant::error_value );
        }
    } else if ( current.type() == variant::type_array ) {
        const variant::sparse_array_type& arr = current.array();
        size_t arraySize = arr.size();
        size_t columnWidth = current.column_width();
        size_t rowWidth = arraySize / columnWidth;
        // If the array does not have an equal number of rows and columns, MDETERM returns the #VALUE! error value.
        if ( columnWidth != rowWidth || arraySize % columnWidth != 0 ) {
            return interpreter_variant( variant::error_value );
        }
        boost::numeric::ublas::matrix<double> m( columnWidth, columnWidth );
        for ( size_t i = 0; i < columnWidth; i++ ) {
            for ( size_t j = 0; j < columnWidth; j++ ) {
                variant val = arr[columnWidth * i + j];
                // Error values cause errors.
                if ( val.type() == variant::type_error ) {
                    return interpreter_variant( val );
                }
                // If any cell contains no number, MDETERM returns the #VALUE! error value.
                if ( val.type() != variant::type_double ) {
                    return interpreter_variant( variant::error_value );
                }
                m( i, j ) = val.numeric();
            }
        }
        try {
            return interpreter_variant( lu_det( m ) );
        } catch ( std::string ) {
            return interpreter_variant( variant::error_value );
        }
    }
    // Error values cause errors.
    if ( current.type() == variant::type_error ) {
        return current;
    }
    // If any cell contains no number, MDETERM returns the #VALUE! error value.
    if ( current.type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }
    return current;
}



