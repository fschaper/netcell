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
 * Calculates the net present value of an investment by using a discount rate and a series
 * of future payments (negative values) and income (positive values).
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the net present value
 *
 * \details
 * The NPV investment begins one period before the date of the value 1 cash flow
 * and ends with the last cash flow in the list. The NPV calculation is based on future cash flows.
 * If your first cash flow occurs at the beginning of the first period,
 * the first value must be added to the NPV result, not included in the values arguments.
 * If n is the number of cash flows in the list of values, the formula for NPV is:
 * NPV = Sum{j=1..n}values{j}/(1+rate)^j
 * NPV is similar to the PV function (present value). The primary difference between PV and NPV is
 * that PV allows cash flows to begin either at the end or at the beginning of the period.
 * Unlike the variable NPV cash flow values, PV cash flows must be constant throughout the investment.
 * NPV is also related to the IRR function (internal rate of return).
 * IRR is the rate for which NPV equals zero:
 * NPV(IRR(...),...) = 0
 *
 * \see
 * function_fv | function_irr | function_pv | function_xnpv
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
interpreter_variant function_npv( function_parameter& parameters )
{
    if ( parameters.count() < 2 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    double rate = parameters[0].numeric(); // the rate of discount over the length of one period.
    unsigned long int counter = 0; // the number of proper values.
    double result = 0.0;
    for ( size_t i = 1; i < parameters.count(); i++ ) {
        if ( parameters[i].i_type() == interpreter_variant::type_range ) {
            range_reference& rref = range_reference_cast( parameters[i].reference() );
            sparse_range_array sra( rref, parameters.context() );
            size_t imax = sra.size();
            for ( unsigned long int j = 0; j < imax; j++ ) {
                variant currentj = sra[j];
                // error values in the array or reference cause errors.
                if ( currentj.type() == variant::type_error ) {
                    return interpreter_variant( currentj );
                }
                // only numbers in that array or reference are counted.
                if ( currentj.type() == variant::type_double ) {
                    counter++;
                    result += currentj.numeric() / pow( 1.0 + rate, static_cast<double>( counter ) );
                }
                // Empty cells, logical values, or text are ignored.
            }
        } else {
            // Arguments that are error values cause errors.
            if ( parameters[i].type() == variant::type_error ) {
                return parameters[i];
            }

            if ( parameters[i].type() == variant::type_array ) {
                const variant::sparse_array_type& arr = parameters[i].array();
                size_t arraySize = arr.size();
                for ( unsigned long int j = 0; j < arraySize; j++ ) {
                    variant currentj = arr[j];
                    // error values in the array or reference cause errors.
                    if ( currentj.type() == variant::type_error ) {
                        return interpreter_variant( currentj );
                    }
                    // only numbers in that array or reference are counted.
                    if ( currentj.type() == variant::type_double ) {
                        counter++;
                        result += currentj.numeric() / pow( 1.0 + rate, static_cast<double>( counter ) );
                    }
                    // logical values, or text are ignored.
                }
            }

            if ( parameters[i].type() == variant::type_string ) {
                counter++;
                try { // text representations of numbers are counted.
                    result += boost::lexical_cast<double>( static_cast<const std::string&>( parameters[i].string() ) ) / pow( 1.0 + rate, static_cast<double>( counter ) );
                } catch ( boost::bad_lexical_cast& ) {
                    // text that cannot be translated into numbers causes the #VALUE! error value.
                    return interpreter_variant( variant::error_value );
                }
            }
            // numbers and logical values are counted.
            if ( parameters[i].type() == variant::type_double || parameters[i].type() == variant::type_bool ) {
                counter++;
                result += parameters[i].numeric() / pow( 1.0 + rate, static_cast<double>( counter ) );
            }
            // empty cells are ignored.
        }
    }

    return interpreter_variant( variant( result ) );
    // Calculates the net present value of an investment by using a discount rate and a series
    // of future payments (negative values) and income (positive values).
}
