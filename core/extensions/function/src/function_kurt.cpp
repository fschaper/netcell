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
 * Returns the kurtosis of data.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the kurtosis
 *
 * \details
 * Kurtosis characterizes the relative peakedness or flatness of a distribution compared with the normal distribution.
 * Arguments that are numbers or logical values or text representations of numbers are counted.
 * Error values cause errors. Text that cannot be translated into numbers cause the #VALUE! error value.
 * If an array or reference argument contains text, logical values, or empty cells, those values are ignored;
 * only numbers are counted.
 *
 * \see
 * function_skew | function_stdev | function_stdevp | function_var | function_varp
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */

interpreter_variant function_kurt( function_parameter& parameters )
{
    double summe = 0.0;
    double sumsq = 0.0;
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
                    sumsq += currenti.numeric() * currenti.numeric();
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
                for ( i = 0; i < arraySize; i++ ) {
                    variant currenti = arr[i];
                    // error values cause errors.
                    if ( currenti.type() == variant::type_error ) {
                        return interpreter_variant( currenti );
                    }
                    // text, logical values are ignored.
                    if ( currenti.type() == variant::type_double ) {
                        vx.push_back( currenti.numeric() );
                        summe += currenti.numeric();
                        sumsq += currenti.numeric() * currenti.numeric();
                    }
                }
            } else if ( current.type() == variant::type_string ) {
                try { // text representations of numbers are counted.
                    double currentd = boost::lexical_cast<double>( static_cast<const std::string&>( current.string() ) );
                    vx.push_back( currentd );
                    summe += currentd;
                    sumsq += currentd * currentd;
                } catch ( boost::bad_lexical_cast& ) {
                    // text that cannot be translated into numbers causes the #VALUE! error value.
                    return interpreter_variant( variant::error_value );
                }
            } else {
                // Arguments that are numbers or logical values are counted.
                // TRUE evaluates as 1. FALSE evaluates as 0.
                vx.push_back( current.numeric() );
                summe += current.numeric();
                sumsq += current.numeric() * current.numeric();
            }
        }
    }

    size_t count = vx.size();
    if ( count < 4 ) {
        // If there are fewer than 4 counted values, KURT returns the #DIV/0! error value.
        return interpreter_variant( variant::error_div_null );
    }
    double stdev = sqrt( ( sumsq - summe * summe / count ) / ( count - 1.0 ) );
    if ( stdev <= 0.0 ) {
        // If the sample standard deviation is zero, KURT returns the #DIV/0! error value.
        return interpreter_variant( variant::error_div_null );
    }

    for ( i = 0; i < count; i++ ) {
        result += pow( vx[i] - summe / count, 4.0 );
    }

    result = result * pow( stdev, -4.0 ) * count * ( count + 1.0 ) / ( count - 1.0 ) / ( count - 2.0 ) / ( count - 3.0 );
    result -= 3.0 * ( count - 1 ) * ( count - 1 ) / ( count - 2 ) / ( count - 3 );

    return interpreter_variant( variant( result ) );
    // Returns the kurtosis of a data set.
    // Kurtosis characterizes the relative peakedness or flatness of a distribution compared with the normal distribution.
    // Positive kurtosis indicates a relatively peaked distribution.
    // Negative kurtosis indicates a relatively flat distribution.
}
