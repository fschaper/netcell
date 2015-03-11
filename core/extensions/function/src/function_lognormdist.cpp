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
 * Returns the cumulative lognormal distribution of x, where ln(x) is normally distributed with parameters mean and standard_dev.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the cumulative lognormal distribution
 *
 * \details
 * If probability = LOGNORMDIST(x,...), then LOGINV(probability,...) = x.
 *
 * \see
 * function_loginv
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 * Vali Nitu <vali@yalos-solutions.com>
 */

interpreter_variant function_lognormdist( function_parameter& parameters )
{
    if ( parameters.count() != 3 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    // If x, mean or standard_dev is error, NORMDIST returns the #VALUE! error value.
    if ( parameters[0].type() == variant::type_error || parameters[1].type() == variant::type_error || parameters[2].type() == variant::type_error ) {
        return interpreter_variant( variant::error_value );
    }

    // the value for which you want the distribution.
    double x = 0.0;
    // the arithmetic mean of the distribution.
    double mean = 0.0;
    // the standard deviation of the distribution.
    double standard_dev = 0.0;

    if ( parameters[0].type() == variant::type_string ) {
        try { // text representations of numbers are evaluated.
            x = boost::lexical_cast<double>( static_cast<const std::string&>( parameters[0].string() ) );
        } catch ( boost::bad_lexical_cast& ) {
            // text that cannot be translated into numbers causes the #VALUE! error value.
            return interpreter_variant( variant::error_value );
        }
    } else { // Arguments that are numbers or logical values are counted.
        x = parameters[0].numeric();
    }

    if ( parameters[1].type() == variant::type_string ) {
        try { // text representations of numbers are evaluated.
            mean = boost::lexical_cast<double>( static_cast<const std::string&>( parameters[1].string() ) );
        } catch ( boost::bad_lexical_cast& ) {
            // text that cannot be translated into numbers causes the #VALUE! error value.
            return interpreter_variant( variant::error_value );
        }
    } else { // Arguments that are numbers or logical values are counted.
        mean = parameters[1].numeric();
    }

    if ( parameters[2].type() == variant::type_string ) {
        try { // text representations of numbers are evaluated.
            standard_dev = boost::lexical_cast<double>( static_cast<const std::string&>( parameters[2].string() ) );
        } catch ( boost::bad_lexical_cast& ) {
            // text that cannot be translated into numbers causes the #VALUE! error value.
            return interpreter_variant( variant::error_value );
        }
    } else { // Arguments that are numbers or logical values are counted.
        standard_dev = parameters[2].numeric();
    }

    // If x <= 0 or if standard_dev <= 0, LOGNORMDIST returns the #NUM! error value.
    if ( x <= 0.0 || standard_dev <= 0.0 ) {
        return interpreter_variant( variant::error_num );
    }

    double z = ( log( x ) - mean ) / standard_dev;
    boost::math::normal s; // standard normal distribution.
    return interpreter_variant( cdf( s, z ) );
    // Returns the cumulative lognormal distribution of x, where ln(x) is normally distributed with parameters mean and standard_dev.
}
