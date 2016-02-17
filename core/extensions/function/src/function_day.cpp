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
 * Returns the day of a date represented by a serial number.
 *
 * \param function_parameter& parameters
 * Serial_number   is the date of the month you are trying to find.
 *
 * \returns
 * the number of the day of a date represented by a serial number.
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
interpreter_variant function_day( function_parameter& parameters )
{

    if ( parameters.count() != 1 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    long int arg = 0;

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

    boost::gregorian::date d( 1900, 1, 1 );
    boost::gregorian::date_duration dd( arg - 2 );
    d += dd;

    return interpreter_variant( ( double )d.day() );

}
