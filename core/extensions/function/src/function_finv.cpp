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






#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
# include <cmath>
# include <boost/foreach.hpp>
#endif

/*!
 * \brief
 * Returns the inverse of the F probability distribution.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the inverse of the F probability distribution
 *
 * \details
 * If probability = FDIST(x,...), then FINV(probability,...) = x.
 *
 * \see
 * function_fdist | function_ftest
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
interpreter_variant function_finv( function_parameter& parameters )
{
    if ( parameters.count() != 3 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    // If any argument is nonnumeric, FINV returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double || parameters[1].type() != variant::type_double || parameters[2].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }
    double probability = parameters[0].numeric(); // a probability associated with the F cumulative distribution.
    double degrees_freedom1 = parameters[1].numeric(); // the numerator degrees of freedom.
    double degrees_freedom2 = parameters[2].numeric(); // the denominator degrees of freedom.
    // If probability < 0 or probability > 1, FINV returns the #NUM! error value.
    if ( probability < 0.0 || probability > 1.0 ) {
        return interpreter_variant( variant::error_num );
    }
    // If degrees_freedom1 < 1 or degrees_freedom1 >= 10^10 or if degrees_freedom2 < 1 or degrees_freedom2 >= 10^10, FINV returns the #NUM! error value.
    if ( degrees_freedom1 < 1.0 || degrees_freedom1 >= 1.0e+10 || degrees_freedom2 < 1.0 || degrees_freedom2 >= 1.0e+10 ) {
        return interpreter_variant( variant::error_num );
    }
    boost::math::fisher_f dist( degrees_freedom1, degrees_freedom2 );
    double result = quantile( complement( dist, probability ) );
    return interpreter_variant( variant( result ) );
    // Returns the inverse of the F probability distribution.
}


