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
 *  Vali Nitu <vali@yalos-solutions.com>
 */

#include "precompiled_header.hpp"

/*!
 * \brief
 * Returns the decimal number for a particular time.
 *
 * \param function_parameter& parameters
 * Serial_number   is the date of the month you are trying to find.
 *
 * \returns
 * Returns the decimal number for a particular time.
 *
 * \details
 *
 * \see
 * function_now, function_today, function_month, function_year, function_day, funtion_date
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com.com>
 */
interpreter_variant function_time( function_parameter& parameters )
{

    if ( parameters.count() != 3 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }


    int hour = 0;

    if ( parameters[0].type() == variant::type_string ) {
        try { // text representations of numbers are evaluated.
            hour = boost::lexical_cast<int>( static_cast<const std::string&>( parameters[0].string() ) );
        } catch ( boost::bad_lexical_cast& ) {
            // text that cannot be translated into numbers causes the #VALUE! error value.
            return interpreter_variant( variant::error_value );
        }
    } else {
        hour = ( int )parameters[0].numeric();
    }

    int minute = 0;

    if ( parameters[1].type() == variant::type_string ) {
        try { // text representations of numbers are evaluated.
            minute = boost::lexical_cast<int>( static_cast<const std::string&>( parameters[0].string() ) );
        } catch ( boost::bad_lexical_cast& ) {
            // text that cannot be translated into numbers causes the #VALUE! error value.
            return interpreter_variant( variant::error_value );
        }
    } else {
        minute = ( int )parameters[1].numeric();
    }

    int second = 0;

    if ( parameters[2].type() == variant::type_string ) {
        try { // text representations of numbers are evaluated.
            second = boost::lexical_cast<int>( static_cast<const std::string&>( parameters[0].string() ) );
        } catch ( boost::bad_lexical_cast& ) {
            // text that cannot be translated into numbers causes the #VALUE! error value.
            return interpreter_variant( variant::error_value );
        }
    } else {
        second = ( int )parameters[2].numeric();
    }

    double time = ( ( ( hour % 24 ) * 3600 ) + ( minute * 60 ) + second ) / 86400.0;

    if ( time < 0 ) {
        return interpreter_variant( variant::error_num );
    }

    return interpreter_variant( time );

}
