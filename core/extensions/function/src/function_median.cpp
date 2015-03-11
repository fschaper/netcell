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
 * Returns the median of the given numbers.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the median
 *
 * \details
 * The median is the number in the middle of a set of numbers; that is,
 * half the numbers have values that are greater than the median, and half have values that are less.
 *
 * \see
 * function_average | function_averagea | function_daverage | function_mode
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
interpreter_variant function_median( function_parameter& parameters )
{
    if ( parameters.count() == 0 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    std::vector<double> numbers;

    // Write all numbers into a vector.
    for ( size_t p = 0; p < parameters.count(); p++ ) {
        interpreter_variant current = parameters[p];
        if ( current.i_type() == interpreter_variant::type_range ) {
            range_reference& rref = range_reference_cast( current.reference() );
            sparse_range_array sra( rref, parameters.context() );
            size_t imax = sra.size();
            for ( unsigned int i = 0; i < imax; i++ ) {
                variant currenti = sra[i];
                // error values cause errors.
                if ( currenti.type() == variant::type_error ) {
                    return interpreter_variant( currenti );
                }

                // text, logical values, or empty cells are ignored.
                if ( currenti.type() == variant::type_double ) {
                    numbers.push_back( currenti.numeric() );
                }
            }
        } else {
            // Arguments that are error values cause errors.
            if ( current.type() == variant::type_error ) {
                return current;
            }

            if ( current.type() == variant::type_array ) {
                const variant::sparse_array_type& arr = current.array();
                size_t arraySize = arr.size();
                for ( unsigned long int i = 0; i < arraySize; i++ ) {
                    variant currenti = arr[i];
                    // error values cause errors.
                    if ( currenti.type() == variant::type_error ) {
                        return interpreter_variant( currenti );
                    }
                    // text, logical values are ignored.
                    if ( currenti.type() == variant::type_double ) {
                        numbers.push_back( currenti.numeric() );
                    }
                }
            } else if ( current.type() == variant::type_string ) {
                try {
                    // text representations of numbers are counted.
                    double currentd = boost::lexical_cast<double>( static_cast<const std::string&>( current.string() ) );
                    numbers.push_back( currentd );
                } catch ( boost::bad_lexical_cast& ) {
                    // text that cannot be translated into numbers causes the #VALUE! error value.
                    return interpreter_variant( variant::error_value );
                }
            } else {
                // Arguments that are numbers or logical values are counted.
                // TRUE evaluates as 1. FALSE evaluates as 0.
                numbers.push_back( current.numeric() );
            }
        }
    }
    // Sort all numbers from small to large.
    std::sort( numbers.begin(), numbers.end() );

    // Find the middle.
    double result;
    size_t index = numbers.size() / 2;
    if ( numbers.size() % 2 == 1 ) {
        result = numbers[index];
    } else {
        result = ( numbers[index-1] + numbers[index] ) * 0.5;
    }
    return interpreter_variant( variant( result ) );
    // Returns the median of the given numbers.
    // The median is the number in the middle of a set of numbers; that is,
    // half the numbers have values that are greater than the median, and half have values that are less.
}

