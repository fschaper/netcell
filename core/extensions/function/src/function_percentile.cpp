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
 *  Radu Racariu <radu@yalos-solutions.com>
 */

#include "precompiled_header.hpp"

/*!
 * \brief
 * Returns the k-th percentile of values in a range.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the k-th percentile
 *
 * \details
 * If k is not a multiple of 1/(n-1), PERCENTILE interpolates to determine the value at the k-th percentile.
 *
 * \see
 * function_large | function_max | function_median | function_min | function_percentrank | function_quartile | function_small
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
interpreter_variant function_percentile( function_parameter& parameters )
{
    if ( parameters.count() != 2 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    interpreter_variant arrayx = parameters[0]; // array or range of data that defines relative standing.
    // If k is nonnumeric, PERCENTILE returns the #VALUE! error value.
    if ( parameters[1].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }
    double k = parameters[1].numeric(); // the percentile value in the range 0..1, inclusive.
    // If k < 0 or if k > 1, PERCENTILE returns the #NUM! error value.
    if ( k < 0.0 || k > 1.0 ) {
        return interpreter_variant( variant::error_num );
    }
    std::vector<double> numbers;
    if ( arrayx.i_type() == interpreter_variant::type_range ) {
        range_reference& rref = range_reference_cast( arrayx.reference() );
        sparse_range_array sra( rref, parameters.context() );
        size_t imax = sra.size();
        for ( unsigned int i = 0; i < imax; i++ ) {
            variant iValue = sra[i];
            if ( iValue.type() == variant::type_error ) {
                return interpreter_variant( iValue );
            }

            if ( iValue.type() == variant::type_double ) {
                numbers.push_back( iValue.numeric() );
            }
        }
    } else if ( arrayx.type() == variant::type_array ) {
        const variant::sparse_array_type& arr = arrayx.array();
        size_t arraySize = arr.size();
        for ( unsigned long int i = 0; i < arraySize; i++ ) {
            variant iValue = arr[i];
            if ( iValue.type() == variant::type_error ) {
                return interpreter_variant( iValue );
            }

            if ( iValue.type() == variant::type_double ) {
                numbers.push_back( iValue.numeric() );
            }
        }
    } else {
        if ( arrayx.type() == variant::type_error ) {
            return arrayx;
        }

        if ( arrayx.type() == variant::type_string ) {
            try {
                double d = boost::lexical_cast<double>( static_cast<const std::string&>( arrayx.string() ) );
                numbers.push_back( d );
            } catch ( boost::bad_lexical_cast& ) {
                return interpreter_variant( variant::error_value );
            }
        } else {
            numbers.push_back( arrayx.numeric() );
        }
    }
    size_t n = numbers.size();
    // If array is empty or contains more than 8191 data points, PERCENTILE returns the #NUM! error value.
    if ( n == 0 || n > 8191 ) {
        return interpreter_variant( variant::error_num );
    }

    if ( n == 1 ) {
        return interpreter_variant( variant( numbers[0] ) );
    }
    // Sort all numbers from small to large.
    std::sort( numbers.begin(), numbers.end() );
    unsigned long int index = static_cast<unsigned long int>( k * ( n - 1.0 ) );
    if ( k * ( n - 1.0 ) == static_cast<double>( index ) ) {
        return interpreter_variant( variant( numbers[index] ) );
    }
    // If k is not a multiple of 1/(n-1), PERCENTILE interpolates to determine the value at the k-th percentile.
    double result = numbers[index] + ( numbers[index+1] - numbers[index] ) * ( k * ( n - 1.0 ) - index );
    return interpreter_variant( variant( result ) );
    // Returns the k-th percentile of values in a range.
}

