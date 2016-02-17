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

/*!
 * \brief
 * Returns the k-th smallest value in a data set.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the k-th smallest value
 *
 * \details
 * Use this function to return values with a particular relative standing in a data set.
 *
 * \see
 * function_large | function_max | function_median | function_min | function_percentile | function_percentrank | function_quartile
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
interpreter_variant function_small( function_parameter& parameters )
{
    if ( parameters.count() != 2 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    if ( parameters[1].type() != variant::type_double || ( parameters[0].i_type() != interpreter_variant::type_range && parameters[0].type() != variant::type_array ) ) {
        return interpreter_variant( variant::error_value );
    }

    std::vector<double> numbers;
    variant::sparse_array_type arr;
    if ( parameters[0].i_type() == interpreter_variant::type_range ) {
        range_reference& rref = range_reference_cast( parameters[0].reference() );
        sparse_range_array sra( rref, parameters.context() );
        size_t imax = sra.size();
        arr = variant::sparse_array_type( imax );
        for ( unsigned int i = 0; i < imax; i++ ) {
            arr[i] = sra[i];
        }
    } else {
        arr = parameters[0].array();
    }
    size_t iSize = arr.size();
    for ( size_t i = 0; i < iSize; i++ ) {
        if ( static_cast<const variant&>( arr[i] ).type() == variant::type_double ) {
            numbers.push_back( static_cast<const variant&>( arr[i] ).numeric() );
        }
    }

    std::vector<double>::size_type index = static_cast<std::vector<double>::size_type>( parameters[1].numeric() - 1 ); // k=index+1 is the position (from the smallest) in the array or range of data to return.
    // If the array is empty or index+1 <= 0 or if index+1 exceeds the number of data points, SMALL returns the #NUM! error value.
    if ( index >= numbers.size() || index < 0 ) {
        return interpreter_variant( variant::error_num );
    } else {
        std::sort( numbers.begin(), numbers.end(), std::less<double>() ); // sort upwards.
        return interpreter_variant( variant( numbers[ index ] ) );
    }
    // Returns the k-th smallest value in a data set.
}

