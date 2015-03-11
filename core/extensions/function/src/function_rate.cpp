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
 * Returns the interest rate per period of an annuity.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the interest rate per period
 *
 * \details
 * RATE is calculated by iteration and can have zero or more solutions.
 * If the successive results of RATE do not converge to within 0.0000001 after 20 iterations, RATE returns the #NUM! error value.
 * If RATE does not converge, try different values for guess. RATE usually converges, if guess is between 0 and 1.
 * Make sure that you are consistent about the units you use for specifying guess or nper.
 * If you make monthly payments on a four-year loan at 12 percent annual interest, use 12%/12 for guess and 4*12 for nper.
 * If you make annual payments on the same loan, use 12% for guess and 4 for nper.
 *
 * \see
 * function_fv | function_ipmt | function_nper | function_pmt | function_pv
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
interpreter_variant function_rate( function_parameter& parameters )
{
    if ( parameters.count() < 3 || parameters.count() > 6 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    double nper = parameters[0].numeric(); // the total number of payment periods in an annuity.
    double pmt = parameters[1].numeric(); // the payment made each period, cannot change over the life of the annuity.
    // Typically, pmt includes principal and interest but no other fees or taxes.
    // If pmt is omitted, you must include the fv argument.
    double pv = parameters[2].numeric(); // the present value - the total amount that a series of future payments is worth now.
    double fv = 0.0; // the future value, or a cash balance you want to attain after the last payment is made.
    if ( parameters.count() > 3 && parameters[3].type() != variant::type_empty ) {
        fv = parameters[3].numeric();
    }
    double type = 0.0; // indicates when payments are due.
    // 0 or omitted: payments are due at the end of the period.
    // 1: payments are due at the beginning of the period.
    if ( parameters.count() > 4 && parameters[4].type() != variant::type_empty ) {
        type = parameters[4].numeric();
    }
    double guess = 0.1; // your guess for what the rate will be.
    if ( parameters.count() > 5 ) {
        guess = parameters[5].numeric();
    }

    double result = guess;
    double old, function, derivation;
    for ( int i = 0; i < 20; i++ ) {
        old = result;
        if ( type == 0.0 ) {
            function = fv + pv * pow( 1.0 + old, nper );
            function += pmt * ( pow( 1.0 + old, nper ) - 1.0 ) / old;
            derivation = pv * nper * pow( 1.0 + old, nper - 1.0 );
            derivation += pmt * ( ( old * ( nper - 1.0 ) - 1.0 ) * pow( 1.0 + old, nper - 1.0 ) + 1.0 ) / old / old;
        } else {
            function = fv + pv * pow( 1.0 + old, nper );
            function += pmt * ( 1.0 + old ) * ( pow( 1.0 + old, nper ) - 1.0 ) / old;
            derivation = pv * nper * pow( 1.0 + old, nper - 1.0 );
            derivation += pmt * ( ( nper - 1.0 ) * pow( 1.0 + old, nper ) + 1.0 ) / old / old;
        }

        if ( derivation == 0.0 ) {
            return interpreter_variant( variant::error_num );
        }
        result = old - function / derivation; // Newton's method.
        if ( fabs( result - old ) <= 0.0000001 ) {
            return interpreter_variant( variant( result ) );
        }
    }

    // If the successive results of RATE do not converge to within 0.0000001 after 20 iterations, RATE returns the #NUM! error value.
    return interpreter_variant( variant::error_num );
    // Returns the interest rate per period of an annuity.
    // RATE is calculated by iteration and can have zero or more solutions.
    // If the successive results of RATE do not converge to within 0.0000001 after 20 iterations, RATE returns the #NUM! error value.
    // If RATE does not converge, try different values for guess. RATE usually converges, if guess is between 0 and 1.
}
