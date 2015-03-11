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
 * Returns the Poisson distribution.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the Poisson distribution
 *
 * \details
 * For cumulative=FALSE: POISSON = exp(-mean)*mean^x /x!
 * For cumulative=TRUE: POISSON = Sum{k=0..x} exp(-mean)*mean^k /k!
 *
 * \see
 * function_expondist
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
interpreter_variant function_poisson( function_parameter& parameters )
{
    if ( parameters.count() != 3 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    // If x or mean is nonnumeric, POISSON returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double || parameters[1].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }

    // If x is not an integer, it is truncated.
    // the number of events.
    long long x = static_cast<long long>( parameters[0].numeric() );
    // the expected numeric value.
    double mean = parameters[1].numeric();
    // Flag.
    bool cumulative = parameters[2].numeric() != 0.0;

    // If x < 0, POISSON returns the #NUM! error value.
    // If mean <= 0, POISSON returns the #NUM! error value.
    if ( x < 0 || mean <= 0.0 ) {
        return interpreter_variant( variant::error_num );
    }

    double result = 0.0;
    if ( !cumulative ) {
        result = poisson_density( x, mean );
    } else {
        for ( long long k = 0; k <= x; k++ ) {
            result += poisson_density( k, mean );
        }
    }
    return interpreter_variant( variant( result ) );
    // If cumulative is TRUE, POISSON returns the cumulative Poisson probability,
    // that the number of random events occurring will be between zero and x inclusive.
    // If FALSE, it returns the Poisson probability mass function, that the number of events occurring will be exactly x.
}
