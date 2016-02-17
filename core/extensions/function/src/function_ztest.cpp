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
 * Returns the one-tailed probability-value of a z-test.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the one-tailed probability-value of a z-test
 *
 * \details
 * For a given hypothesized population mean, mu0, ZTEST returns the probability
 * that the sample mean would be greater than the average of observations in the data set(array) -
 * that is, the observed sample mean.
 *
 * \see
 * function_confidence | function_normdist | function_norminv | function_normsdist | function_normsinv | function_standardize
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */

interpreter_variant function_ztest( function_parameter& parameters )
{
    if ( parameters.count() == 0 || parameters.count() > 3 ) {
        // formula-error! We give #REF! until we can give a message-window.
        return interpreter_variant( variant::error_ref );
    }

    interpreter_variant array = parameters[0];

    if ( array.i_type() != interpreter_variant::type_range && array.type() != variant::type_array ) {
        return interpreter_variant( variant::error_div_null );
    }

    double mu0 = 0.0;
    if ( parameters.count() > 1 && parameters[1].type() != variant::type_empty ) {
        mu0 = parameters[1].numeric();
    }
    double sigma = -1.0;
    if ( parameters.count() > 2 ) {
        // If sigma <= 0, ZTEST returns the #NUM! error value.
        if ( parameters[2].numeric() <= 0.0 ) {
            return interpreter_variant( variant::error_num );
        }
        sigma = parameters[2].numeric();
    }

    double summe = 0.0;
    double sumsq = 0.0;
    unsigned long int counter = 0;
    variant::sparse_array_type arr;
    if ( array.i_type() == interpreter_variant::type_range ) {
        range_reference& rref = range_reference_cast( array.reference() );
        sparse_range_array sra( rref, parameters.context() );
        size_t imax = sra.size();
        arr = variant::sparse_array_type( imax );
        for ( unsigned int i = 0; i < imax; i++ ) {
            arr[i] = sra[i];
        }
    } else {
        arr = array.array();
    }
    size_t arraySize = arr.size();
    for ( unsigned long int i = 0; i < arraySize; i++ ) {
        variant val = arr[i];
        if ( val.type() == variant::type_error ) {
            return interpreter_variant( val );
        }
    }
    // If an argument is an array or reference, only numbers in that array or reference are counted.
    // Empty cells, logical values, or text in the array or reference are ignored.
    counter += std::for_each( arr.begin(), arr.end(), internal::Counter() ).counter;
    summe += std::for_each( arr.begin(), arr.end(), internal::Sum() ).summe;
    if ( sigma == -1.0 ) {
        sumsq += std::for_each( arr.begin(), arr.end(), internal::SumSq() ).summe;
    }

    if ( counter == 0 ) {
        return interpreter_variant( variant::error_n_a );
    }
    double std_dev;
    if ( sigma == -1.0 ) {
        if ( counter == 1 ) {
            return interpreter_variant( variant::error_div_null );
        }
        std_dev = sumsq - summe * summe / counter;
        std_dev = sqrt( std_dev / ( counter - 1 ) );
    } else {
        std_dev = sigma;
    }
    double z = ( summe / counter - mu0 ) * sqrt( static_cast<double>( counter ) ) /  std_dev;
    boost::math::normal s; // standard normal distribution.
    return interpreter_variant( variant( 1.0 - cdf( s, z ) ) );
    // Returns the one-tailed probability-value of a z-test.
    // For a given hypothesized population mean, mu0, ZTEST returns the probability
    // that the sample mean would be greater than the average of observations in the data set(array) -
    // that is, the observed sample mean.
}

