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
 * Returns the inverse of the Fisher transformation.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the inverse of the Fisher transformation
 *
 * \details
 * Use this transformation when analyzing correlations between ranges or arrays of data.
 * The equation for the inverse of the Fisher transformation is:
 * x=(exp(2*y)-1)/(exp(2*y)+1)
 * If y = FISHER(x), then FISHERINV(y) = x.
 *
 * \see
 * function_fisher | function_correl | function_covar
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
interpreter_variant function_fisherinv( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #N/A until we can give a mesage-window.
        return interpreter_variant( variant::error_n_a );
    }

    // If y is nonnumeric, FISHERINV returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }

    double y = parameters[0].numeric(); // the value for which you  want to perform the inverse of the transformation.

    return interpreter_variant( variant( ( exp( 2.0 * y ) - 1.0 ) / ( exp( 2.0 * y ) + 1.0 ) ) );
    // Returns the inverse of the Fisher transformation.
}
