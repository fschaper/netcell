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
 * Returns the negative binomial distribution.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the negative binomial distribution
 *
 * \details
 * NEGBINOMDIST returns the probability, that there will be number_f failures
 * before the number_s-th success, when the constant probability of a success is probability_s.
 *
 * \see
 * function_binomdist | function_combin | function_hypgeomdist
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */


interpreter_variant function_negbinomdist( function_parameter& parameters )
{
    if ( parameters.count() != 3 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    // If any argument is nonnumeric, NEGBINOMDIST returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double || parameters[1].type() != variant::type_double || parameters[2].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }

    // number_f and number_s are truncated to integers.
    // the number of failures.
    long long number_f = static_cast<long long>( parameters[0].numeric() );
    // the threshold number of successes.
    long long number_s = static_cast<long long>( parameters[1].numeric() );
    // the probability of a success.
    double probability_s = parameters[2].numeric();

    // If probability_s < 0 or if probability_s > 1, NEGBINOMDIST returns the #NUM! error value.
    // If number_f < 0 or number_s < 1, NEGBINOMDIST returns the #NUM! error value.
    if ( probability_s < 0.0 || probability_s > 1.0 || number_f < 0 || number_s < 1 ) {
        return interpreter_variant( variant::error_num );
    }

    double result = pow( probability_s, static_cast<double>( number_s ) ) * pow( 1.0 - probability_s, static_cast<double>( number_f ) );
    result *= static_cast<double>( combin( number_f + number_s - 1, number_f ) );

    return interpreter_variant( variant( result ) );
    // NEGBINOMDIST (negative binomial distribution) returns the probability, that there will be number_f failures
    // before the number_s-th success, when the constant probability of a success is probability_s.
}

