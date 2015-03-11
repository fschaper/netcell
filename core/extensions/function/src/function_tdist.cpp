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
 * Returns the probability for the Student t-distribution
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the probability for the Student t-distribution
 *
 * \details
 * If probability = TDIST(x,...), then TINV(probability,...) = x.
 *
 * \see
 * function_tinv | function_ttest
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
interpreter_variant function_tdist( function_parameter& parameters )
{
    if ( parameters.count() != 3 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    // If any argument is nonnumeric, TDIST returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double || parameters[1].type() != variant::type_double || parameters[2].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }
    double x = parameters[0].numeric(); // the numeric value at which to evaluate the distribution.
    double degrees_freedom = parameters[1].numeric(); // the number of degrees of freedom.
    int tails = static_cast<int>( parameters[2].numeric() ); // the number of distribution tails to return.
    // 1 for one-tailed distribution, 2 for two-tailed distribution.
    // If x < 0 or degrees_freedom < 1 or tails is any value other than 1 or 2, TDIST returns the #NUM! error value.
    if ( x < 0.0 || degrees_freedom < 1.0 || ( tails != 1 && tails != 2 ) ) {
        return interpreter_variant( variant::error_num );
    }
    boost::math::students_t dist( degrees_freedom );
    double result;
    if ( tails == 1 ) {
        result = cdf( complement( dist, x ) );
    } else {
        result = 2.0 * cdf( complement( dist, x ) );
    }
    return interpreter_variant( variant( result ) );
    // Returns the Percentage Points (probability) for the Student t-distribution, where a numeric value (x) is a calculated value of t,
    // for which the Percentage Points are to be computed.
    // The t-distribution is used in the hypothesis testing of small sample data sets.
}
