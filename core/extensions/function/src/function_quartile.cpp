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
 * Returns the quartile of a data set.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the quartile
 *
 * \details
 * MIN, MEDIAN, and MAX return the same value as QUARTILE when quart is equal to 0, 2, and 4, respectively.
 *
 * \see
 * function_large | function_max | function_median | function_min | function_percentile | function_percentrank | function_small
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 * Radu Racariu <radu@yalos-solutions.com>
 */
interpreter_variant function_quartile( function_parameter& parameters )
{
    if ( parameters.count() != 2 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    interpreter_variant arrayx = parameters[0]; // the array or cell range of numeric values for which you want the quartile value.
    int quart = static_cast<int>( parameters[1].numeric() ); // indicates which value to return.
    // If quart < 0 or if quart > 4, QUARTILE returns the #NUM! error value.
    if ( quart < 0 || quart > 4 ) {
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
    size_t count = numbers.size();
    // If array is empty, QUARTILE returns the #NUM! error value.
    if ( count == 0 ) {
        return interpreter_variant( variant::error_num );
    }

    if ( count == 1 ) {
        return interpreter_variant( variant( numbers[0] ) );
    }
    // Sort all numbers from small to large.
    std::sort( numbers.begin(), numbers.end() );
    size_t index;
    switch ( quart ) {
        case 1: // First quartile.
            index = count / 4;
            switch ( count % 4 ) {
                case 0:
                    return interpreter_variant( variant( ( numbers[index-1] + 3.0 * numbers[index] ) * 0.25 ) );
                case 1:
                    return interpreter_variant( variant( numbers[index] ) );
                case 2:
                    return interpreter_variant( variant( ( 3.0 * numbers[index] + numbers[index+1] ) * 0.25 ) );
                case 3:
                    return interpreter_variant( variant( ( numbers[index] + numbers[index+1] ) * 0.5 ) );
            }
        case 2: // Median value.
            index = count / 2;
            if ( count % 2 == 1 ) {
                return interpreter_variant( variant( numbers[index] ) );
            } else {
                return interpreter_variant( variant( ( numbers[index - 1] + numbers[index] ) * 0.5 ) );
            }
        case 3: // Third quartile.
            index = ( count * 3 ) / 4;
            switch ( count % 4 ) {
                case 0:
                    return interpreter_variant( variant( ( 3.0 * numbers[index-1] + numbers[index] ) * 0.25 ) );
                case 1:
                    return interpreter_variant( variant( numbers[index] ) );
                case 2:
                    return interpreter_variant( variant( ( numbers[index-1] + 3.0 * numbers[index] ) * 0.25 ) );
                case 3:
                    return interpreter_variant( variant( ( numbers[index-1] + numbers[index] ) * 0.5 ) );
            }
        case 4: // Maximum value.
            return interpreter_variant( variant( numbers[ count - 1 ] ) );
    }

    // moved here just to make g++ happy
    // case 0: Minimum value.
    return interpreter_variant( variant( numbers[0] ) );

    // Returns the quartile of a data set.
}


