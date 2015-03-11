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
 * Returns the present value of an investment.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the present value
 *
 * \details
 * The present value is the total amount that a series of future payments is worth now.
 * For example, when you borrow money, the loan amount is the present value to the lender.
 * Make sure that you are consistent about the units you use for specifying rate and nper.
 * If you make monthly payments on a four-year loan at 12 percent annual interest,
 * use 12%/12 for rate and 4*12 for nper. If you make annual payments on the same loan,
 * use 12% for rate and 4 for nper.
 * An annuity is a series of constant cash payments made over a continuous period.
 * For example, a car loan or a mortgage is a annuity.
 * In annuity functions, cash you pay out, such as a deposit to savings, is represented by a negative number;
 * cash you receive, such as a dividend check, is represented by a positive number.
 * For example, a $1000 deposit to the bank would be represented by the argument -1000
 * if you are the depositor and by the argument 1000 if you are the bank.
 * pv*(1+rate)^nper + pmt*(1+rate*type)*((1+rate)^nper -1)/rate + fv = 0
 * If rate is 0, then: (pmt*nper) + pv + fv = 0
 *
 * \see
 * function_fv | function_ipmt | function_nper | function_pmt | function_rate
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
interpreter_variant function_pv( function_parameter& parameters )
{
    if ( parameters.count() < 3 || parameters.count() > 5 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    double rate = parameters[0].numeric(); // the interest rate per period.
    double nper = parameters[1].numeric(); // the total number of payment periods in an annuity.
    double pmt  = parameters[2].numeric(); // the payment made each period , pmt cannot change over the life of the annuity.
    // Typically, pmt includes principal and interest but no other fees or taxes.
    double fv = 0.0; // the future value, or a cash balance you want to attain after the last payment is made.
    // If fv is omitted, it is assumed to be 0 (the future value of a loan, for example, is 0).
    if ( parameters.count() > 3 && parameters[3].type() != variant::type_empty ) {
        fv = parameters[3].numeric();
    }
    double type = 0.0; // indicates when payments are due.
    // 0 or omitted: payments are due at the end of the period.
    // 1: payments are due at the beginning of the period.
    if ( parameters.count() > 4 ) {
        type = parameters[4].numeric();
    }
    double result = 0.0;
    if ( rate == 0.0 ) {
        result = -fv - pmt * nper;
    } else {
        double numerator = -fv - pmt * ( 1.0 + rate * type ) * ( pow( 1.0 + rate, nper ) - 1.0 ) / rate;
        double denominator = pow( 1.0 + rate , nper );
        result = numerator / denominator;
    }
    return interpreter_variant( variant( result ) );
    // Returns the present value of an investment.
    // The present value is the total amount that a series of future payments is worth now.
}
