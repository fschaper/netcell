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
 * Returns the gamma distribution.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the gamma distribution
 *
 * \details
 * If probability = GAMMADIST(x,...), then GAMMAINV(probability,...) = x.
 *
 * \see
 * function_gammainv | function_expondist | function_chidist
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
interpreter_variant function_gammadist( function_parameter& parameters )
{
    if ( parameters.count() != 4 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    // If x, alpha, or beta is nonnumeric, GAMMADIST returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double || parameters[1].type() != variant::type_double || parameters[2].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }

    double x = parameters[0].numeric(); // the value at which you want to evaluate the distribution.
    double alpha = parameters[1].numeric(); // the shape parameter to the distribution.
    double beta = parameters[2].numeric(); // the scale parameter to the distribution.
    bool cumulative = parameters[3].numeric() != 0.0; // Flag.

    // If x < 0, GAMMADIST returns the #NUM! error value.
    // If alpha <= 0 or if beta <= 0, GAMMADIST returns the #NUM! error value.
    if ( x < 0.0 || alpha <= 0.0 || beta <= 0.0 ) {
        return interpreter_variant( variant::error_num );
    }

    double result = 0.0;
    boost::math::gamma_distribution<> dist( alpha, beta );
    if ( cumulative ) {
        result = cdf( dist, x );
    } else {
        result = pdf( dist, x );
    }
    return interpreter_variant( variant( result ) );
    // Returns the gamma distribution.
}
