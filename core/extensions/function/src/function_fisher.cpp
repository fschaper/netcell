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
 * Returns the Fisher transformation at x.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the Fisher transformation
 *
 * \details
 * This transformation produces a function that is normally distributed rather than skewed.
 * Use this function to perform hypothesis testing on the correlation coefficient.
 * The equation for the Fisher transformation is:
 * z=0.5*log((1+x)/(1-x))
 *
 * \see
 * function_fisherinv | function_correl | function_covar
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */

interpreter_variant function_fisher( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    // If x is nonnumeric, FISHER returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }

    double x = parameters[0].numeric(); // a numeric value for which you want the transformation.

    // If x <= -1 or if x >= 1, FISHER returns the #NUM! error value.
    if ( x <= -1.0 || x >= 1.0 ) {
        return interpreter_variant( variant::error_num );
    }

    return interpreter_variant( variant( 0.5 * log( ( 1.0 + x ) / ( 1.0 - x ) ) ) );
    // Returns the Fisher transformation at x.
}
