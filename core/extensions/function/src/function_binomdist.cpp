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


interpreter_variant binomdist_density( function_parameter& parameters );

/*!
 * \brief
 * Returns the individual term binomial distribution probability.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * result of the calculation
 *
 * \details
 * Use BINOMDIST in problems with a fixed number of tests or trials,
 * when the outcomes of any trial are only success or failure, when trials are independent,
 * and when the probability of success is constant throughout the experiment.
 *
 * \see
 * function_combin | function_critbinom | function_hypgeomdist | function_negbinomdist
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
interpreter_variant function_binomdist( function_parameter& parameters )
{
    if ( parameters.count() != 4 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    // If number_s, trials, or probability_s is non numeric, BINOMDIST returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double || parameters[1].type() != variant::type_double ||
            parameters[2].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }

    // number_s and trials are truncated to integers.
    // the number of successes in trials.
    long long number_s = static_cast<long long>( parameters[0].numeric() );
    // the number of independent trials.
    long long trials = static_cast<long long>( parameters[1].numeric() );

    // If number_s < 0 or number_s > trials, BINOMDIST returns the #NUM! error value.
    if ( number_s < 0 || number_s > trials ) {
        return interpreter_variant( variant::error_num );
    }

    // the probability of success on each trial.
    double probability_s = parameters[2].numeric();
    // If probability_s < 0 or probability_s > 1, BINOMDIST returns the #NUM! error value.
    if ( probability_s < 0.0 || probability_s > 1.0 ) {
        return interpreter_variant( variant::error_num );
    }

    // Flag.
    bool cumulative = parameters[3].numeric() != 0.0;
    double result = 0.0;
    if ( !cumulative ) {
        result = binomdist_density( number_s, trials, probability_s );
    } else {
        if ( number_s <= trials / 2 ) {
            for ( long long i = 0; i <= number_s; i++ ) {
                result += binomdist_density( i, trials, probability_s );
            }
        } else {
            result = 1.0;
            for ( long long i = trials; i > number_s; i-- ) {
                result -= binomdist_density( i, trials, probability_s );
            }
        }
    }
    return interpreter_variant( variant( result ) );
    // If cumulative is TRUE, then BINOMDIST returns the cumulative distribution function,
    // which is the probability, that there are at most number_s successes. If FLASE,
    // it returns the probability mass function, which is the probability, that there are number_s successes.
}

