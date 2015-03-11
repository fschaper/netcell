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
 * Returns the first most frequently occurring, or repetitive, value in an array or range of data.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the first most frequently occurring, or repetitive, value
 *
 * \details
 * Arguments should be numbers. Error values cause errors.
 * Logical values or text or empty cells or empty parameters cause the #VALUE! error value.
 * If an array or reference argument contains text, logical values, or empty cells, those values are ignored.
 *
 * \see
 * function_average | function_geomean | function_harmean | function_median | function_trimmean
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
interpreter_variant function_mode( function_parameter& parameters )
{
    std::vector<double> numbers;
    for ( size_t p = 0; p < parameters.count(); p++ ) {
        interpreter_variant current = parameters[p];
        if ( current.i_type() == interpreter_variant::type_range ) {
            range_reference& rref = range_reference_cast( current.reference() );
            sparse_range_array sra( rref, parameters.context() );
            size_t arraySize = sra.size();
            for ( unsigned int i = 0; i < ( unsigned int ) arraySize; i++ ) {
                variant currenti = sra[i] ;
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
                    if ( currenti.type() == variant::type_error ) {
                        return interpreter_variant( currenti );
                    }
                    // text, logical values are ignored.
                    if ( currenti.type() == variant::type_double ) {
                        numbers.push_back( currenti.numeric() );
                    }
                }
            } else if ( current.type() == variant::type_double ) {
                numbers.push_back( current.numeric() );
            } else {
                return interpreter_variant( variant::error_value );
            }
        }
    }
    std::vector<double> vx;
    std::vector<unsigned long int> vf; // absolute frequencies.
    for ( size_t i = 0; i < numbers.size(); i++ ) {
        bool newNumber = true;
        for ( unsigned long int j = 0; j < vx.size(); j++ ) {
            if ( numbers[i] == vx[j] ) {
                newNumber = false;
                vf[j]++;
                break;
            }
        }

        if ( newNumber ) {
            vx.push_back( numbers[i] );
            vf.push_back( 1 );
        }
    }
    unsigned long int maxf = 0; // the maximum frequency.
    for ( size_t i = 0; i < vf.size(); i++ ) {
        if ( vf[i] > maxf ) {
            maxf = vf[i];
        }
    }
    // If the data set contains no duplicate data points, MODE returns the #N/A error value.
    if ( maxf == 0 || maxf == 1 ) {
        return interpreter_variant( variant::error_n_a );
    }

    for ( size_t i = 0; i < vf.size(); i++ ) {
        if ( vf[i] == maxf ) {
            // MODE returns the first most frequently value.
            return interpreter_variant( variant( vx[i] ) );
        }
    }
    return interpreter_variant( variant::error_n_a );
    // Returns the first most frequently occurring, or repetitive, value in an array or range of data.
    // MODE is a location measure.
}
