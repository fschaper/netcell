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
 * Returns the modified internal rate of return for a series of periodic cash flows.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the modified internal rate of return
 *
 * \details
 * MIRR considers both the cost of the investment and the interest received on reinvestment of cash.
 * MIRR uses the order of values to interpret the order of cash flows.
 * Be sure to enter your payment and income values in the sequence you want and with the correct signs
 * (positive values for cash received, negative values for cash paid).
 * MIRR=((-NPV(rrate,values[positive])*(1+rrate)^n)/(NPV(frate,values[negative])*(1+frate)))^(1/(n-1)) -1
 *
 * \see
 * function_rate | function_xirr | function_xnpv
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
interpreter_variant function_mirr( function_parameter& parameters )
{
    if ( parameters.count() != 3 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    interpreter_variant values = parameters[0]; // array or reference to cells that contain numbers.
    // These numbers represent a series of payments (negative values) and income (positive values) occurring at regular periods.
    double finance_rate = parameters[1].numeric(); // the interest rate you pay on the money used in the cash flows.
    double reinvest_rate = parameters[2].numeric(); // the interest rate you receive on the cash flows as you reinvest them.

    // values must contain at least one positive and one negative value to calculate the modified internal rate of return.
    // Otherwise, MIRR returns the #DIV/0! error value.
    double npv_pos = 0.0, npv_neg = 0.0;
    int counter = 0; // the number of proper values.

    if ( values.i_type() == interpreter_variant::type_range ) {
        range_reference& rref = range_reference_cast( values.reference() );
        sparse_range_array sra( rref, parameters.context() );
        size_t n = sra.size();
        for ( unsigned int i = 0; i < n; i++ ) {
            variant v = sra[i];
            // If values contains text, logical values, or empty cells, those values are ignored.
            if ( v.type() == variant::type_double ) {
                counter++;
                if ( v.numeric() >= 0.0 ) {
                    npv_pos += v.numeric() / pow( 1.0 + reinvest_rate, counter );
                } else {
                    npv_neg += v.numeric() / pow( 1.0 + finance_rate, counter );
                }
            }
        }
    } else if ( values.type() == variant::type_array ) {
        const variant::sparse_array_type& arr = values.array();
        size_t n = arr.size();
        for ( size_t i = 0; i < n; i++ ) {
            variant v = arr[i];
            // If values contains text, logical values, or empty cells, those values are ignored.
            if ( v.type() == variant::type_double ) {
                counter++;
                if ( v.numeric() >= 0.0 ) {
                    npv_pos += v.numeric() / pow( 1.0 + reinvest_rate, counter );
                } else {
                    npv_neg += v.numeric() / pow( 1.0 + finance_rate, counter );
                }
            }
        }
    } else {
        return interpreter_variant( variant::error_div_null );
    }

    if ( npv_neg == 0.0 || npv_pos == 0.0 || reinvest_rate <= -1.0 ) {
        return interpreter_variant( variant::error_div_null );
    }

    double result = pow( ( -npv_pos * pow( 1.0 + reinvest_rate, counter ) ) / ( npv_neg * ( 1.0 + finance_rate ) ), ( 1.0 / ( counter - 1.0 ) ) ) - 1.0;

    return interpreter_variant( variant( result ) );
    // Returns the modified internal rate of return for a series of periodic cash flows.
    // MIRR considers both the cost of the investment and the interest received on reinvestment of cash.
}
