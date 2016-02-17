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
 *  Radu Racariu <radu@yalos-solutions.com>
 */

#include "precompiled_header.hpp"

/*!
 * \brief
 * Returns the future value of an investment based on periodic, constant payments and a constant interest rate.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the future value
 *
 * \details
 * Make sure that you are consistent about the units you use for specifying rate and nper.
 * If you make monthly payments on a four-year loan at 12 percent annual interest, use 12%/12 for rate and 4*12 for nper.
 * If you make annual payments on the same loan, use 12% for rate and 4 for nper.
 * For all the arguments, cash you pay out, such as deposits to savings, is represented by negative numbers;
 * cash you receive, such as dividend checks, is represented by positive numbers.
 *
 * \see
 * function_fvschedule | function_ipmt | function_nper | function_pmt | function_pv | function_rate
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
interpreter_variant function_fv( function_parameter& parameters )
{
    if ( parameters.count() < 3 || parameters.count() > 5 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    double rate = parameters[0].numeric(); // the interest rate per period.
    double nper = parameters[1].numeric(); // the total number of payment periods in an annuity.
    double pmt  = parameters[2].numeric(); // the payment made each period.
    // It cannot change over the life of the annuity.
    // Typically, pmt contains principal and interest but no other fees or taxes.
    double pv   = 0; // the present value, or the lump-sum amount that a series of future payments is worth right now.
    // If pv is omitted, it is assumed to be zero, and you must include the pmt argument.
    if ( parameters.count() >= 4 && parameters[3].type() != variant::type_empty ) {
        pv = parameters[3].numeric();
    }
    bool typ = false; // 0 or 1, indicates when payments are due. If typ is omitted, it is assumed to be 0.
    if ( parameters.count() >= 5 ) {
        typ = parameters[4].numeric() != 0.0;
    }

    if ( rate == 0 ) {
        return interpreter_variant( variant( -1 * ( pv + ( nper * pmt ) ) ) );
    } else {
        double tmp = rate + 1;
        return interpreter_variant( variant( ( ( 1 - pow( tmp, nper ) ) * ( typ ? tmp : 1 ) * pmt ) / rate  - pv * pow( tmp, nper ) ) );
    }
    // Returns the future value of an investment based on periodic, constant payments and a constant interest rate.
}
