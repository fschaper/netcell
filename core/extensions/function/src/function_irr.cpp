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
 *  Frieder Hofmann <frieder.hofmann@jedox.com>
 *  Radu Ialovoi <ialovoi@yalos-solutions.com>
 */

#include "precompiled_header.hpp"


/*!
 * \brief
 * Returns the internal rate of return for a series of cash flows represented by the numbers in values.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the internal rate of return
 *
 * \details
 * The cash flows must occur at regular intervals, such as monthly or annually.
 * The internal rate of return is the interest rate received for an investment consisting of
 * payments (negative values) and income (positive values) that occur at regular periods.
 * We use an iterative technique for calculating IRR.
 * If IRR can't find a result that works after 20 tries, the #NUM! error value is returned.
 * If IRR gives the #NUM! error value, or if the result is not close to what you expected,
 * try again with a different value for guess.
 *
 * \see
 * function_mirr | function_npv | function_rate | function_xirr | function_xnpv
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
interpreter_variant function_irr( function_parameter& parameters )
{
    if ( parameters.count() == 0 || parameters.count() > 2 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    interpreter_variant values = parameters[0]; // an array or reference to cells that contain numbers
    // for which you want to calculate the internal rate of return.
    double guess = 0.1; // a number that you guess is close to the result of IRR.
    if ( parameters.count() > 1 ) {
        guess = parameters[1].numeric();
    }

    std::vector<double> coefficient;
    if ( values.i_type() == interpreter_variant::type_range ) {
        range_reference& rref = range_reference_cast( values.reference() );
        sparse_range_array sra( rref, parameters.context() );
        size_t imax = sra.size();
        for ( unsigned int i = 0; i < imax; i++ ) {
            variant vi = sra[i];
            if ( vi.type() == variant::type_error ) {
                return interpreter_variant( variant::error_value );
            }

            if ( vi.type() == variant::type_double ) {
                coefficient.push_back( vi.numeric() );
            }
        }
    } else if ( values.type() == variant::type_array ) {
        const variant::sparse_array_type& arr = values.array();
        size_t arraySize = arr.size();
        for ( unsigned long int i = 0; i < arraySize; i++ ) {
            variant vi = arr[i];
            if ( vi.type() == variant::type_error ) {
                return interpreter_variant( variant::error_value );
            }

            if ( vi.type() == variant::type_double ) {
                coefficient.push_back( vi.numeric() );
            }
        }
    } else {
        return interpreter_variant( variant::error_num );
    }
    size_t count = coefficient.size();

    double result = guess;
    double old, function, derivation;
    for ( int n = 0; n < 20; n++ ) {
        old = result;
        function = 0.0;
        derivation = 0.0;
        for ( unsigned long int j = 0; j < count; j++ ) {
            function += coefficient[j] / pow( 1.0 + old, static_cast<double>( j ) );
            derivation -= j * coefficient[j] / pow( 1.0 + old, j + 1.0 );
        }

        if ( derivation == 0.0 ) {
            return interpreter_variant( variant::error_num );
        }
        result = old - function / derivation; // Newton's method.
        if ( fabs( result - old ) <= 0.0000001 ) {
            return interpreter_variant( variant( result ) );
        }
    }
    // If IRR can't find a result that works after 20 tries, the #NUM! error value is returned.
    // If IRR gives the #NUM! error value, or if the result is not close to what you expected,
    // try again with a different value for guess.
    return interpreter_variant( variant::error_num );
    // Returns the internal rate of return for a series of cash flows represented by the numbers in values.
    // The cash flows must occur at regular intervals, such as monthly or annually.
    // The internal rate of return is the interest rate received for an investment consisting of
    // payments (negative values) and income (positive values) that occur at regular periods.
}
