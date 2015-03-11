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
 * Returns a normalized value from a distribution characterized by mean and standard_dev.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the normalized value
 *
 * \details
 * The equation of the normalized value is:
 * Z=(x-mean)/standard_dev
 *
 * \see
 * function_normdist | function_norminv | function_normsdist | function_normsinv | function_ztest
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
interpreter_variant function_standardize( function_parameter& parameters )
{
    if ( parameters.count() != 3 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    // the value you want to normalize.
    double x = parameters[0].numeric();
    // the arithmetic mean of the distribution.
    double mean = parameters[1].numeric();
    // the standard deviation of the distribution.
    double standard_dev = parameters[2].numeric();

    // If standard_dev <= 0, STANDARDIZE returns the #NUM! error value.
    if ( !( standard_dev > 0.0 ) ) {
        return interpreter_variant( variant::error_num );
    }
    return interpreter_variant( variant( ( x - mean ) / standard_dev ) );
    // Returns a normalized value from a distribution characterized by mean and standard_dev.
}
