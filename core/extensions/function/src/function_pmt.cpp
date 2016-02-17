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
 * Calculates the payment for a loan based on constant payments and a constant interest rate.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the payment for a loan
 *
 * \details
 * The payment returned by PMT includes principal and interest but no taxes,
 * reserve payments, or fees sometimes associated with loans.
 * Make sure that you are consistent about the units you use for specifying rate and nper.
 * If you make monthly payments on a four-year loan at an annual interest rate of 12 percent,
 * use 12%/12 for rate and 4*12 for nper. If you make annual payments on the same loan,
 * use 12 percent for rate and 4 for nper.
 *
 * \see
 * function_fv | function_ipmt | function_nper | function_pv | function_rate
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
interpreter_variant function_pmt( function_parameter& parameters )
{
    if ( parameters.count() < 3 || parameters.count() > 5 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    double rate = parameters[0].numeric(); // the interest rate for the loan.
    double nper = parameters[1].numeric(); // the total number of payments for the loan.
    double pv   = parameters[2].numeric(); // the present value, or the total amount that a series of future payments is worth now; also known as the principal.
    double fv = 0.0; // the future value, or a cash balance you want to attain after the last payment is made.
    // If fv is omitted, it is assumed to be 0, that is, the future value of a loan is 0.
    if ( parameters.count() > 3 && parameters[3].type() != variant::type_empty ) {
        fv = parameters[3].numeric();
    }
    double type = 0; // the number 0 or 1. type indicates when payments are due.
    if ( parameters.count() == 5 ) {
        type = parameters[4].numeric();
    }

    if ( rate == 0.0 ) {
        return interpreter_variant( variant( -( pv + fv ) / nper ) );
    }

    double pvfact  = pow( 1.0 + rate, nper );
    double pmtfact = ( pvfact - 1.0 ) / rate;
    double result = ( -pv * pvfact - fv ) / ( ( 1.0 + rate * type ) * pmtfact );
    return interpreter_variant( variant( result ) );
    // Calculates the payment for a loan based on constant payments and a constant interest rate.
}
