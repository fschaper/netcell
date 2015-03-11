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
 * Returns the probability that values in a range are between two limits.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * result of the calculation
 *
 * \details
 * If upper_limit is not supplied, PROB returns the probability that values in x_range are equal to lower_limit.
 *
 * \see
 * function_binomdist | function_critbinom
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 * Vali Nitu <vali@yalos-solutions.com>
 */
interpreter_variant function_prob( function_parameter& parameters )
{
    if ( parameters.count() < 3 || parameters.count() > 4 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    interpreter_variant x_range = parameters[0]; // the range of numeric values of x with which there are associated probabilities.
    interpreter_variant prob_range = parameters[1]; // a set of probabilities associated with values in x_range.


    interpreter_variant value = parameters[2];

    // error values cause errors.
    if ( value.type() == variant::type_error ) {
        return interpreter_variant( value );
    }

    double lower_limit = 0.0; // the lower bound on the value for which you want a probability.
    double upper_limit = 0.0; // the optional upper bound on the value for which you want a probability.

    if ( value.type() == variant::type_string ) {
        try { // text representations of numbers are evaluated.
            lower_limit = boost::lexical_cast<double>( static_cast<const std::string&>( value.string() ) );
        } catch ( boost::bad_lexical_cast& ) {
            // text that cannot be translated into numbers causes the #VALUE! error value.
            return interpreter_variant( variant::error_value );
        }
    } else { // Arguments that are numbers or logical values are counted.
        lower_limit = value.numeric();
        upper_limit = lower_limit;
    }



    if ( parameters.count() > 3 ) {
        interpreter_variant value_upper = parameters[3];
        if ( value_upper.type() == variant::type_string ) {
            try { // text representations of numbers are evaluated.
                upper_limit = boost::lexical_cast<double>( static_cast<const std::string&>( value_upper.string() ) );
            } catch ( boost::bad_lexical_cast& ) {
                // text that cannot be translated into numbers causes the #VALUE! error value.
                return interpreter_variant( variant::error_value );
            }
        } else { // Arguments that are numbers or logical values are counted.
            upper_limit = value_upper.numeric();

        }
    }

    if ( lower_limit > upper_limit ) {
        return interpreter_variant( variant( 0.0 ) );
    }
    double sum = 0.0; // the sum of the probabilities.
    double result = 0.0;
    if ( x_range.i_type() == interpreter_variant::type_range || x_range.type() == variant::type_array ) {
        variant::sparse_array_type x_arr;
        if ( x_range.i_type() == interpreter_variant::type_range ) {
            range_reference& rref1 = range_reference_cast( x_range.reference() );
            sparse_range_array sra1( rref1, parameters.context() );
            size_t imax1 = sra1.size();
            x_arr = variant::sparse_array_type( imax1 );
            for ( unsigned int i1 = 0; i1 < imax1; i1++ ) {
                x_arr[i1] = sra1[i1];
            }
        } else {
            x_arr = x_range.array();
        }
        size_t arraySize = x_arr.size();
        if ( prob_range.i_type() == interpreter_variant::type_range || prob_range.type() == variant::type_array ) {
            variant::sparse_array_type prob_arr;
            if ( prob_range.i_type() == interpreter_variant::type_range ) {
                range_reference& rref2 = range_reference_cast( prob_range.reference() );
                sparse_range_array sra2( rref2, parameters.context() );
                size_t imax2 = sra2.size();
                prob_arr = variant::sparse_array_type( imax2 );
                for ( unsigned int i2 = 0; i2 < imax2; i2++ ) {
                    prob_arr[i2] = sra2[i2];
                }
            } else {
                prob_arr = prob_range.array();
            }
            // If x_range and prob_range contain a different number of data points, PROB returns the #N/A error value.
            if ( arraySize != prob_arr.size() ) {
                return interpreter_variant( variant::error_n_a );
            }
            variant xi, probi;
            for ( unsigned long int i = 0; i < arraySize; i++ ) {
                xi = x_arr[i];
                if ( xi.type() == variant::type_error ) {
                    return interpreter_variant( xi );
                }
                probi = prob_arr[i];
                if ( probi.type() == variant::type_error ) {
                    return interpreter_variant( probi );
                }

                if ( xi.type() != variant::type_double || probi.type() != variant::type_double ) {
                    return interpreter_variant( variant::error_num );
                }
                double dprobi = probi.numeric();
                // If any value in prob_range <= 0 or if any value in prob_range > 1, PROB returns the #NUM! error value.
                if ( dprobi <= 0.0 || dprobi > 1.0 ) {
                    return interpreter_variant( variant::error_num );
                }
                sum += dprobi;
                // If the sum of the values in prob_range > 1, PROB returns the #NUM! error value.
                if ( sum > 1.0 ) {
                    return interpreter_variant( variant::error_num );
                }

                if ( !( lower_limit > xi.numeric() || xi.numeric() > upper_limit ) ) {
                    result += dprobi;
                }
            }
        } else {
            return interpreter_variant( variant::error_num );
        }
    } else {
        return interpreter_variant( variant::error_num );
    }

    return interpreter_variant( variant( result ) );
    // Returns the probability that values in a range are between two limits.
    // If upper_limit is not supplied, PROB returns the probability that values in x_range are equal to lower_limit.
}
