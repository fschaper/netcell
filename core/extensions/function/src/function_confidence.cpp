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
 * Returns a value that you can use to construct a confidence interval for a population mean.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the half length of the confidence interval
 *
 * \details
 * The confidence interval is population mean+-CONFIDENCE.
 *
 * \see
 * function_normsdist | function_normsinv | function_ztest
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
interpreter_variant function_confidence( function_parameter& parameters )
{
    if ( parameters.count() != 3 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    // If any argument is nonnumeric, CONFIDENCE returns the #VALUE! error value.
    if ( parameters[0].type() != variant::type_double || parameters[1].type() != variant::type_double || parameters[2].type() != variant::type_double ) {
        return interpreter_variant( variant::error_value );
    }
    double alpha = parameters[0].numeric(); // the significance level used to compute the confidence level. The confidence level equals 1-alpha.
    double standard_dev = parameters[1].numeric(); // the population standard deviation for the data range (is assumed to be known).
    long long size = static_cast<long long>( parameters[2].numeric() ); // the sample size.
    // If alpha <= 0 or alpha >= 1 or standard_dev <= 0 or size < 1, CONFIDENCE returns the #NUM! error value.
    if ( alpha <= 0.0 || alpha >= 1.0 || standard_dev <= 0.0 || size < 1 ) {
        return interpreter_variant( variant::error_num );
    }

    boost::math::normal s; // standard normal distribution.
    double quant = quantile( s, 1.0 - alpha / 2.0 );
    double result = quant * standard_dev / sqrt( static_cast<double>( size ) );
    return interpreter_variant( variant( result ) );
    // Returns a value that you can use to construct a confidence interval for a population mean.
    // The confidence interval is a range of values.
    // Your sample mean m is at the center of this range and the range is m+-CONFIDENCE.
    // Assume that we use m, standard_dev, and size to construct a two-tailed test at significance level alpha
    // of the hypothesis that the population mean is mu. Then we will not reject that hypothesis,
    // if mu is in the confidence interval, and will reject that hypothesis, if mu is not in the confidence interval.
}
