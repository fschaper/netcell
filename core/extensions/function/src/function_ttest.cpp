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
 * Returns the probability associated with a Student's t-Test to determine
 * whether two samples are likely to have come from the same two underlying populations
 * that have the same mean.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the probability associated with a Stundent's t-Test
 *
 * \details
 * If type = 1, this test is performed paired.
 * If type = 2, this test is performed unpaired and it is assumed, that the sample variances are equal (homoscedastic).
 * If type = 3, this test is performed unpaired and it is assumed, that the sample variances can differ (heteroscedastic).
 *
 * \see
 * function_tdist | function_tinv
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */

interpreter_variant function_ttest( function_parameter& parameters )
{
    if ( parameters.count() != 4 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    if ( ( parameters[0].i_type() != interpreter_variant::type_range && parameters[0].type() != variant::type_array )
            || ( parameters[1].i_type() != interpreter_variant::type_range && parameters[1].type() != variant::type_array ) ) {
        return interpreter_variant( variant::error_div_null );
    }
    variant::sparse_array_type arr0, arr1;
    if ( parameters[0].i_type() == interpreter_variant::type_range ) {
        range_reference& rref0 = range_reference_cast( parameters[0].reference() );
        sparse_range_array sra0( rref0, parameters.context() );
        size_t imax0 = sra0.size();
        arr0 = variant::sparse_array_type( imax0 );
        for ( unsigned int i = 0; i < imax0; i++ ) {
            arr0[i] = sra0[i];
        }
    } else {
        arr0 = parameters[0].array();
    }

    if ( parameters[1].i_type() == interpreter_variant::type_range ) {
        range_reference& rref1 = range_reference_cast( parameters[1].reference() );
        sparse_range_array sra1( rref1, parameters.context() );
        size_t imax1 = sra1.size();
        arr1 = variant::sparse_array_type( imax1 );
        for ( unsigned int i = 0; i < imax1; i++ ) {
            arr1[i] = sra1[i];
        }
    } else {
        arr1 = parameters[1].array();
    }
    size_t arraySize0 = arr0.size();
    size_t arraySize1 = arr1.size();
    // If tails or type is nonnumeric, TTEST returns the #VALUE! error value.
    if ( parameters[2].type() != variant::type_double || parameters[3].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }
    // The tails and type arguments are truncated to integers.
    int tails = static_cast<int>( parameters[2].numeric() );
    int type = static_cast<int>( parameters[3].numeric() );
    // If tails is any value other than 1 or 2 or if type is any value other than 1 or 2 or 3, TTEST returns the #NUM! error value.
    if ( tails < 1 || tails > 2 || type < 1 || type > 3 ) {
        return interpreter_variant( variant::error_num );
    }
    // If the two arrays have a different number of data points, and type = 1 (paired), TTEST returns the #N/A error value.
    if ( type == 1 && arraySize0 != arraySize1 ) {
        return interpreter_variant( variant::error_n_a );
    }

    if ( type == 1 ) { // paired
        double summe = 0.0;
        double sumsq = 0.0;
        unsigned long int counter = 0;
        for ( unsigned long int i = 0; i < arraySize0; i++ ) {
            variant val0i = arr0[i];
            if ( val0i.type() == variant::type_error ) {
                return interpreter_variant( val0i );
            }
            variant val1i = arr1[i];
            if ( val1i.type() == variant::type_error ) {
                return interpreter_variant( val1i );
            }
            if ( val0i.type() != variant::type_double || val1i.type() != variant::type_double ) {
                continue;
            }
            counter++;
            double diff = val0i.numeric() - val1i.numeric();
            summe += diff;
            sumsq += diff * diff;
        }
        if ( counter < 2 ) {
            return interpreter_variant( variant::error_div_null );
        }
        double var = ( sumsq - summe * summe / counter ) / ( counter - 1 );
        if ( var <= 0.0 ) {
            return interpreter_variant( variant::error_div_null );
        }
        double t = summe / sqrt( counter * var );
        boost::math::students_t dist( counter - 1 );
        if ( tails == 2 ) { // two-tailed
            return interpreter_variant( variant( 2.0 * cdf( complement( dist, fabs( t ) ) ) ) );
        } else { // one-tailed
            return interpreter_variant( variant( cdf( complement( dist, fabs( t ) ) ) ) );
        }
    } else { // unpaired
        double sumx = 0.0;
        double sumy = 0.0;
        double sumx2 = 0.0;
        double sumy2 = 0.0;
        unsigned long int countx = 0;
        unsigned long int county = 0;
        for ( unsigned long int i = 0; i < arraySize0; i++ ) {
            variant vali = arr0[i];
            if ( vali.type() == variant::type_error ) {
                return interpreter_variant( vali );
            }
            if ( vali.type() != variant::type_double ) {
                continue;
            }
            countx++;
            sumx += vali.numeric();
            sumx2 += vali.numeric() * vali.numeric();
        }
        if ( countx < 2 ) {
            return interpreter_variant( variant::error_div_null );
        }
        for ( unsigned long int i = 0; i < arraySize1; i++ ) {
            variant vali = arr1[i];
            if ( vali.type() == variant::type_error ) {
                return interpreter_variant( vali );
            }
            if ( vali.type() != variant::type_double ) {
                continue;
            }
            county++;
            sumy += vali.numeric();
            sumy2 += vali.numeric() * vali.numeric();
        }
        if ( county < 2 ) {
            return interpreter_variant( variant::error_div_null );
        }
        double var = ( sumx2 - sumx * sumx / countx + sumy2 - sumy * sumy / county ) / ( countx + county - 2 );
        if ( var <= 0.0 ) {
            return interpreter_variant( variant::error_div_null );
        }
        if ( type == 2 ) { // homoscedastic (It is assumed that the variances of x and y are equal.)
            double t = sqrt( countx * county / ( ( countx + county ) * var ) ) * ( sumx / countx - sumy / county );
            boost::math::students_t dist( countx + county - 2 );
            if ( tails == 2 ) { // two-tailed
                return interpreter_variant( variant( 2.0 * cdf( complement( dist, fabs( t ) ) ) ) );
            } else { // one-tailed
                return interpreter_variant( variant( cdf( complement( dist, fabs( t ) ) ) ) );
            }
        } else { // heteroscedastic (It is assumed that the variances of x and y can differ.)
            double varxN = ( sumx2 - sumx * sumx / countx ) / ( countx * ( countx - 1 ) );
            double varyN = ( sumy2 - sumy * sumy / county ) / ( county * ( county - 1 ) );
            double t = ( sumx / countx - sumy / county ) / sqrt( varxN + varyN );
            double degrees_freedom = ( varxN + varyN ) * ( varxN + varyN ) / ( varxN * varxN / ( countx - 1 ) + ( varyN * varyN / ( county - 1 ) ) );
            boost::math::students_t dist( degrees_freedom );
            if ( tails == 2 ) { // two-tailed
                return interpreter_variant( variant( 2.0 * cdf( complement( dist, fabs( t ) ) ) ) );
            } else { // one-tailed
                return interpreter_variant( variant( cdf( complement( dist, fabs( t ) ) ) ) );
            }
        }
    }
    //return interpreter_variant( variant::error_div_null ); // We should not get here!
}
