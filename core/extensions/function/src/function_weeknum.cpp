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
#include "wss/formatter.hpp"

/*!
 * \brief
 * Returns a number that indicates where the week falls numerically within a year.
 *
 * \param function_parameter& parameters
 * Serial_number   is the date of the month you are trying to find.
 *
 * \returns
 * Returns a number that indicates where the week falls numerically within a year.
 *
 * \details
 * By default, January 1, 1900 is serial number 1, and January 1, 2008 is
 * serial number 39448 because it is 39,448 days after January 1, 1900.
 *
 * \see
 * function_now, function_today, function_month, function_year
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com.com>
 */
interpreter_variant function_weeknum( function_parameter& parameters )
{

    long int arg = 0;
    size_t return_type = 1;

    if ( 2 < parameters.count() || 0 == parameters.count() ) {
        return interpreter_variant( variant::error_value );
    }

    if ( parameters[0].type() == variant::type_string ) {
        try { // text representations of numbers are evaluated.
            arg = boost::lexical_cast<long int>( static_cast<const std::string&>( parameters[0].string() ) );
        } catch ( boost::bad_lexical_cast& ) {
            variant value;
            std::string format;
            if ( formatter::instance().engine() && formatter::instance().engine()->find_format( parameters.context().context().session(), parameters[0].string(), value, format ) ) {
                arg = ( long int ) value.numeric() ;
            } else {
                return interpreter_variant( variant( variant::error_value ) );
            }
        }
    } else {
        arg = ( long int )parameters[0].numeric();
    }

    if ( 2 == parameters.count() ) {
        if ( parameters[1].type() == variant::type_string ) {
            try { // text representations of numbers are evaluated.
                return_type = boost::lexical_cast<size_t>( static_cast<const std::string&>( parameters[1].string() ) );
            } catch ( boost::bad_lexical_cast& ) {
                // text that cannot be translated into numbers causes the #VALUE! error value.
                return interpreter_variant( variant::error_value );
            }
        } else {
            return_type = ( size_t )parameters[1].numeric();
        }

    }

    boost::gregorian::date d( 1900, 1, 1 );
    boost::gregorian::date_duration dd( arg - 1 );

    int excelBugg = 0;
    if ( dd.days() > 58 ) {
        excelBugg++;
    }

    dd -= boost::gregorian::date_duration( excelBugg );

    d += dd;

    if ( 0 == arg ) { //excel does that; according to the excel help it should be #NUM but it is not.
        switch ( return_type ) {
            case 1:
            case 17:
                return interpreter_variant( 0.0 );
            case 21:
                return interpreter_variant( 52.0 );
            case 2:
            case 11:
            case 12:
            case 13:
            case 14:
            case 15:
            case 16:
                return interpreter_variant( 1.0 );
            default:
                return interpreter_variant( variant::error_num );
        }

    }

    int doy = d.day_of_year();
    int y = d.year();
    boost::gregorian::date fdoy( y, 1, 1 );
    int fdow = fdoy.day_of_week();
    fdow = fdow ? fdow : 7;
    if ( 1900 == y ) {
        fdow = 7; //for some reason excel claims that 1st of January 1900 was Sunday
    }
    int weeknum = 0;
    unsigned long daysbegin = 0;
    switch ( return_type ) {
        case 1:
        case 17:
            //Sunday is the first day of the week, System 1
            daysbegin = fdow < 7 ? fdow : fdow - 7;
            weeknum = ( doy + daysbegin ) / 7 + ( ( doy + daysbegin ) % 7 ? 1 : 0 );
            break;
        case 2:
        case 11:
            //Monday is the first day of the week, System 1
            daysbegin = fdow < 1 ? 1 - fdow : fdow - 1;
            weeknum = ( doy + daysbegin ) / 7 + ( ( doy + daysbegin ) % 7 ? 1 : 0 );
            break;
        case 12:
            //Tuesday is the first day of the week, System 1
            daysbegin = fdow < 2 ? 7 - ( 2 - fdow ) : fdow - 2;
            weeknum = ( doy + daysbegin ) / 7 + ( ( doy + daysbegin ) % 7 ? 1 : 0 );
            break;
        case 13:
            //Wednesday is the first day of the week, System 1
            daysbegin = fdow < 3 ? 7 - ( 3 - fdow ) : fdow - 3;
            weeknum = ( doy + daysbegin ) / 7 + ( ( doy + daysbegin ) % 7 ? 1 : 0 );
            break;
        case 14:
            //Thursday is the first day of the week, System 1
            daysbegin = fdow < 4 ? 7 - ( 4 - fdow ) : fdow - 4;
            weeknum = ( doy + daysbegin ) / 7 + ( ( doy + daysbegin ) % 7 ? 1 : 0 );
            break;
        case 15:
            //Friday is the first day of the week, System 1
            daysbegin = fdow < 5 ? 7 - ( 5 - fdow ) : fdow - 5;
            weeknum = ( doy + daysbegin ) / 7 + ( ( doy + daysbegin ) % 7 ? 1 : 0 );
            break;
        case 16:
            //Saturday is the first day of the week, System 1
            daysbegin = fdow < 6 ? 7 - ( 6 - fdow ) : fdow - 6;
            weeknum = ( doy + daysbegin ) / 7 + ( ( doy + daysbegin ) % 7 ? 1 : 0 );
            break;
        case 21:
            //Monday is the first day of the week, System 2 ( ISO 8601 )
            weeknum = d.week_number();
            break;
        default:
            return interpreter_variant( variant::error_num );
            break;
    }

    return weeknum ? interpreter_variant( ( double )weeknum ) : interpreter_variant( 1.0 );

}
