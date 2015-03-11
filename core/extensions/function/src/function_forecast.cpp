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
 * Calculates, or predicts, a future value by using linear regression through existing values.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the predicted value is a y-value for a given x-value
 *
 * \details
 * The known values must be arrays or references that contain numbers.
 * If any array or reference argument contains text, logical values, or empty cells, those value-pairs are ignored.
 * Error values cause errors.
 *
 * \see
 * function_growth | function_linest | function_logest | function_slope | function_trend
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */

interpreter_variant function_forecast( function_parameter& parameters )
{
    if ( parameters.count() != 3 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    interpreter_variant known_xs = parameters[2]; // a cell range of values or an array.
    if ( known_xs.i_type() != interpreter_variant::type_range && known_xs.type() != variant::type_array ) {
        return interpreter_variant( variant::error_div_null );
    }
    variant::sparse_array_type arrx, arry;
    if ( known_xs.i_type() == interpreter_variant::type_range ) {
        range_reference& rref1 = range_reference_cast( known_xs.reference() );
        sparse_range_array sra1( rref1, parameters.context() );
        size_t imax1 = sra1.size();
        arrx = variant::sparse_array_type( imax1 );
        for ( unsigned int i1 = 0; i1 < imax1; i1++ ) {
            arrx[i1] = sra1[i1];
        }
    } else {
        arrx = known_xs.array();
    }
    size_t arraySize = arrx.size();
    interpreter_variant known_ys = parameters[1]; // another cell range of values or an array.
    if ( known_ys.i_type() != interpreter_variant::type_range && known_ys.type() != variant::type_array ) {
        return interpreter_variant( variant::error_div_null );
    }

    if ( known_ys.i_type() == interpreter_variant::type_range ) {
        range_reference& rref2 = range_reference_cast( known_ys.reference() );
        sparse_range_array sra2( rref2, parameters.context() );
        size_t imax2 = sra2.size();
        arry = variant::sparse_array_type( imax2 );
        for ( unsigned int i2 = 0; i2 < imax2; i2++ ) {
            arry[i2] = sra2[i2];
        }
    } else {
        arry = known_ys.array();
    }
    // If known_xs and known_ys have a different number of data points, INTERCEPT returns the #N/A error value.
    if ( arraySize != arry.size() ) {
        return interpreter_variant( variant::error_n_a );
    }
    interpreter_variant given_xValue = parameters[0];
    double given_x = 0.0;
    // error values cause errors.
    if ( given_xValue.type() == variant::type_error ) {
        return given_xValue;
    }

    if ( given_xValue.type() == variant::type_string ) {
        try { // text representations of numbers are evaluated.
            given_x = boost::lexical_cast<double>( static_cast<const std::string&>( given_xValue.string() ) );
        } catch ( boost::bad_lexical_cast& ) {
            // text that cannot be translated into numbers causes the #VALUE! error value.
            return interpreter_variant( variant::error_value );
        }
    } else { // Arguments that are numbers or logical values are counted.
        given_x = given_xValue.numeric();
    }
    double sumx = 0.0; // the sum of the data of known_xs.
    double sumx2 = 0.0; // the sum of the squares of the data of known_xs.
    double sumy = 0.0; // the sum of the data of known_ys.
    double sumxy = 0.0; // the sum of the products of corresponding data of known_xs and known_ys.
    unsigned long int counter = 0; // the number of the proper pairs of data of known_xs and known_ys.
    for ( unsigned long int i = 0; i < arraySize; i++ ) {
        variant xi = arrx[i];
        variant yi = arry[i];
        // error values cause errors.
        if ( xi.type() == variant::type_error ) {
            return interpreter_variant( xi );
        }

        if ( yi.type() == variant::type_error ) {
            return interpreter_variant( yi );
        }

        // If any array or reference argument contains empty cells, logical values, or text, those value-pairs are ignored.
        if ( xi.type() == variant::type_double && yi.type() == variant::type_double ) {
            counter++;
            sumx += xi.numeric();
            sumx2 += xi.numeric() * xi.numeric();
            sumy += yi.numeric();
            sumxy += xi.numeric() * yi.numeric();
        }
    }
    // If there is only one or no counted value-pair, INTERCEPT returns the #DIV/0! error value.
    if ( counter == 0 || counter == 1 ) {
        return interpreter_variant( variant::error_div_null );
    }

    double sx = sumx2 - sumx * sumx / counter;
    // If the standard deviation equals zero, INTERCEPT returns the #DIV/0! error value.
    if ( sx <= 0.0 ) {
        return interpreter_variant( variant::error_div_null );
    }
    double slope = ( sumxy - sumx * sumy / counter ) / sx; // the slope of the linear regression line.
    double intercept = sumy / counter - slope * sumx / counter;
    double result = intercept + slope * given_x;
    return interpreter_variant( variant( result ) );
    // Calculates, or predicts, a future value by using linear regression through existing values.
    // The predicted value is a y-value for a given x-value.
    // The known values are existing x-values and y-values, and the new value is predicted by using linear regression.

}
