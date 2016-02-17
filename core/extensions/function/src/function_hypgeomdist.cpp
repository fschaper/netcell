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
 * Returns the hypergeometric distribution.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the hypergeometric distribution
 *
 * \details
 * HYPGEOMDIST returns the probability of a given number of sample successes (sample_s),
 * given the sample size (number_sample), population successes (population_s), and population size (number_population).
 *
 * \see
 * function_binomdist | function_combin | function_negbinomdist
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
interpreter_variant function_hypgeomdist( function_parameter& parameters )
{
    if ( parameters.count() != 4 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    // If any argument is nonnumeric, HYPGEOMDIST returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double || parameters[1].type() != variant::type_double ||
            parameters[2].type() != variant::type_double || parameters[3].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }

    // All arguments are truncated to integers.
    // the number of successes in the sample.
    long long sample_s = static_cast<long long>( parameters[0].numeric() );
    // the size of the sample.
    long long number_sample = static_cast<long long>( parameters[1].numeric() );
    // the number of successes in the population.
    long long population_s = static_cast<long long>( parameters[2].numeric() );
    // the population size.
    long long number_population = static_cast<long long>( parameters[3].numeric() );

    // If sample_s < 0 or sample_s is greater than the lesser of number_sample or population_s, HYPGEOMDIST returns the #NUM! error value.
    long long lesser = number_sample < population_s ? number_sample : population_s;
    if ( sample_s < 0 || sample_s > lesser ) {
        return interpreter_variant( variant::error_num );
    }
    // If sample_s is less than the larger of 0 or (number_sample - number_population + population_s), HYPGEOMDIST returns the #NUM! error value.
    long long limit = number_sample - number_population + population_s;
    long long larger = 0 > limit ? 0 : limit;
    if ( sample_s < larger ) {
        return interpreter_variant( variant::error_num );
    }
    // If number_sample < 0 or number_sample > number_population, HYPGEOMDIST returns the #NUM! error value.
    if ( number_sample < 0 || number_sample > number_population ) {
        return interpreter_variant( variant::error_num );
    }
    // If population_s < 0 or population_s > number_population, HYPGEOMDIST returns the #NUM! error value.
    // If number_population < 0, HYPGEOMDIST returns the #NUM! error value.
    if ( population_s < 0 || population_s > number_population || number_population < 0 ) {
        return interpreter_variant( variant::error_num );
    }

    double result = static_cast<double>( combin( population_s, sample_s ) );
    result *= static_cast<double>( combin( number_population - population_s, number_sample - sample_s ) );
    result /= static_cast<double>( combin( number_population, number_sample ) );

    return interpreter_variant( variant( result ) );
    // HYPGEOMDIST (hypergeometric distribution) returns the probability of a given number of sample successes (sample_s),
    // given the sample size (number_sample), population successes (population_s), and population size (number_population).
}
