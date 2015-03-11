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
 * Returns the average of the absolute deviations of data points from their mean.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the average of the absolute deviations
 *
 * \details
 * The arguments must be numbers, logical values, or text that contains numbers, or arrays or references that contain numbers.
 * Empty cells are ignored. Empty parameters are evaluated as 0.
 * Error values cause errors. Text that cannot be translated into numbers causes the #VALUE! error value.
 * If an array or reference argument contains text, logical values, or empty cells, those values are ignored.
 *
 * \see
 * function_average | function_devsq | function_stdev | function_stdevp | function_var | function_varp
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
interpreter_variant function_avedev( function_parameter& parameters )
{
    double summe = 0.0;
    double result = 0.0;
    std::vector<double> vx;
    unsigned long int i;
    for ( size_t p = 0; p < parameters.count(); p++ ) {
        interpreter_variant current = parameters[p];
        if ( current.i_type() == interpreter_variant::type_range ) {
            range_reference& rref = range_reference_cast( current.reference() );
            sparse_range_array sra( rref, parameters.context() );
            size_t arraySize = sra.size();
            for ( i = 0; i < arraySize; i++ ) {
                variant currenti = sra[i];
                // error values cause errors.
                if ( currenti.type() == variant::type_error ) {
                    return interpreter_variant( currenti );
                }
                // text, logical values, or empty cells are ignored.
                if ( currenti.type() == variant::type_double ) {
                    vx.push_back( currenti.numeric() );
                    summe += currenti.numeric();
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
                variant currenti;
                for ( i = 0; i < arraySize; i++ ) {
                    currenti = arr[i];
                    // error values cause errors.
                    if ( currenti.type() == variant::type_error ) {
                        return interpreter_variant( currenti );
                    }
                    // text, logical values are ignored.
                    if ( currenti.type() == variant::type_double ) {
                        vx.push_back( currenti.numeric() );
                        summe += currenti.numeric();
                    }
                }
            } else if ( current.type() == variant::type_string ) {
                try { // text representations of numbers are counted.
                    double currentd = boost::lexical_cast<double>( static_cast<const std::string&>( current.string() ) );
                    vx.push_back( currentd );
                    summe += currentd;
                } catch ( boost::bad_lexical_cast& ) {
                    // text that cannot be translated into numbers causes the #VALUE! error value.
                    return interpreter_variant( variant::error_value );
                }
            } else {
                // Arguments that are numbers or logical values are counted.
                // TRUE evaluates as 1. FALSE evaluates as 0.
                vx.push_back( current.numeric() );
                summe += current.numeric();
            }
        }
    }
    size_t count = vx.size();
    if ( count == 0 ) {
        // If there is no counted value, AVEDEV returns the #NUM! error value.
        return interpreter_variant( variant::error_num );
    }

    for ( i = 0; i < count; i++ ) {
        result += fabs( vx[i] - summe / count );
    }

    result = result / count;
    return interpreter_variant( variant( result ) );
    // Returns the average of the absolute deviations of data points from their mean.
    // AVEDEV is a measure of the variability in a data set.
}
