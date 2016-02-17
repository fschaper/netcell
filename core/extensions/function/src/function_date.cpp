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
 * Returns the sequential serial number that represents a particular date.
 *
 * \param function_parameter& parameters
 * Serial_number   is the date of the month you are trying to find.
 *
 * \returns
 * Returns the sequential serial number that represents a particular date.
 *
 * \details
 *
 *
 * \see
 * function_now, function_today, function_month, function_year, function_day, funtion_time
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com.com>
 */
interpreter_variant function_date( function_parameter& parameters )
{


    if ( parameters.count() != 3 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    int year = 0;

    if ( parameters[0].type() == variant::type_string ) {
        try { // text representations of numbers are evaluated.
            year = boost::lexical_cast<int>( static_cast<const std::string&>( parameters[0].string() ) );
        } catch ( boost::bad_lexical_cast& ) {
            // text that cannot be translated into numbers causes the #VALUE! error value.
            return interpreter_variant( variant::error_value );
        }
    } else {
        year = ( int )parameters[0].numeric();
    }

    int month = 0;

    if ( parameters[1].type() == variant::type_string ) {
        try { // text representations of numbers are evaluated.
            month = boost::lexical_cast<int>( static_cast<const std::string&>( parameters[0].string() ) );
        } catch ( boost::bad_lexical_cast& ) {
            // text that cannot be translated into numbers causes the #VALUE! error value.
            return interpreter_variant( variant::error_value );
        }
    } else {
        month = ( int )parameters[1].numeric();
    }

    int day = 0;

    if ( parameters[2].type() == variant::type_string ) {
        try { // text representations of numbers are evaluated.
            day = boost::lexical_cast<int>( static_cast<const std::string&>( parameters[0].string() ) );
        } catch ( boost::bad_lexical_cast& ) {
            // text that cannot be translated into numbers causes the #VALUE! error value.
            return interpreter_variant( variant::error_value );
        }
    } else {
        day = ( int )parameters[2].numeric();
    }

    if ( year < 0 || year > 9999 ) {
        return interpreter_variant( variant::error_num );
    }

    if ( year >= 0 && year <= 1899 ) {
        year += 1900;
    }

    if ( month > 12 ) {
        int add_years = month / 12;
        month = month % 12;
        year += add_years;
    }

    if ( month < 1 ) {
        int add_years = ( -month / 12 ) + 1;
        month = 12 + month % 12;
        year -= add_years;
    }


    boost::gregorian::date d;


    try {
        d = boost::gregorian::date( year, month, day );
    } catch ( boost::gregorian::bad_day_of_month& ) {
        d = boost::gregorian::date( year, month, 1 );
        d += boost::gregorian::date_duration( day - 1 );
    }


    boost::gregorian::date d0( 1900, 1, 1 );

    boost::gregorian::date_duration dd = d - d0;

    int excelBugg = 1;
    if ( dd.days() > 58 ) {
        excelBugg++;
    }

    dd += boost::gregorian::date_duration( excelBugg );

    return interpreter_variant( ( double )dd.days() );

}
