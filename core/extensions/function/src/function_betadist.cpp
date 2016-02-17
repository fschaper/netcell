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
 * Returns the beta cumulative distribution function.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the beta cumulative distribution function
 *
 * \details
 * If probability = BETADIST(x,...), then BETAINV(probability,...) = x.
 *
 * \see
 * function_betainv
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
interpreter_variant function_betadist( function_parameter& parameters )
{
    if ( parameters.count() < 3 || parameters.count() > 5 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    // If any argument is nonnumeric, BETADIST returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double || parameters[1].type() != variant::type_double || parameters[2].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }

    double x = parameters[0].numeric(); // the value at which to evaluate the function.
    double alpha = parameters[1].numeric(); // shape parameter of the distribution.
    double beta = parameters[2].numeric(); // shape parameter of the distribution.
    double A = 0.0; // optional lower bound to the interval of x.
    double B = 1.0; // optional upper bound to the interval of x.

    if ( parameters.count() > 3 && parameters[3].type() != variant::type_empty ) {
        if ( parameters[3].type() != variant::type_double ) {
            return interpreter_variant( variant::error_value );
        }
        A = parameters[3].numeric();
    }

    if ( parameters.count() > 4 ) {
        if ( parameters[4].type() != variant::type_double ) {
            return interpreter_variant( variant::error_value );
        }
        B = parameters[4].numeric();
    }
    // If alpha <= 0 or beta <= 0 or if x < A, x > B or A = B, BETADIST returns the #NUM! error value.
    if ( alpha <= 0.0 || beta <= 0.0 || x < A || x > B || A == B ) {
        return interpreter_variant( variant::error_num );
    }
    boost::math::beta_distribution<> dist( alpha, beta );
    double y = ( x - A ) / ( B - A );
    double result = cdf( dist, y );
    return interpreter_variant( variant( result ) );
    // Returns the beta cumulative distribution function.
}

