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
 * Calculates the interest paid during a specific period of an investment.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the interest paid during a specific period
 *
 * \details
 * Make sure that you are consistent about the units you use for specifying rate and nper.
 * If you make monthly payments on a four-year loan at an annual interest rate of 12 percent,
 * use 12%/12 for rate and 4*12 for nper. If you make annual payments on the same loan,
 * use 12% for rate and 4 for nper.
 * For all the arguments, the cash you pay out, such as deposits to savings or other withdrawals, is represented by negative numbers;
 * the cash you receive, such as dividend checks and other deposits, is represented by positive numbers.
 *
 * \see
 * function_rate | function_nper | function_pv
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
interpreter_variant function_ispmt( function_parameter& parameters )
{
    if ( parameters.count() != 4 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    double rate = parameters[0].numeric(); // the interest rate for the investment.
    double per = parameters[1].numeric(); // the period for which you want to find the interest, and must be between 1 and nper.
    double nper = parameters[2].numeric(); // the total number of payment periods for the investment.
    double pv = parameters[3].numeric(); // the present value of the investment. For a loan, pv is the loan amount.

    double result = -pv * rate;
    return interpreter_variant( variant( result - result * per / nper ) );
    // Calculates the interest paid during a specific period of an investment.
    // This function is provided for compatibility with Lotus 1-2-3.
}
