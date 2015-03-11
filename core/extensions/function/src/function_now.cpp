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
 * Returns the serial number of the current date and time.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the number of the current date and time
 *
 * \details
 * Numbers to the right of the decimal point in the serial number represent the time;
 * numbers to the left represent the date. For example, the serial number 0.5 represents the time 12:00 noon.
 * By default, January 1, 1900 is serial number 1, and January 1, 2008 is serial number 39448
 * because it is 39448 days after January 1, 1900.
 * The NOW function changes only when the worksheet is calculated or when a macro
 * that contains the function is run.
 *
 * \see
 * function_today
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
interpreter_variant function_now( function_parameter& /*parameters*/ )
{
    std::time_t time = std::time ( NULL );
    // ifdefs are workarounds for boost bugs that cause crashes on linux and bogus times on win32
#ifdef _WIN32
    ::std::tm* ts =  boost::date_time::c_time::localtime( &time, NULL );
#else
    std::tm ts;
    boost::date_time::c_time::localtime( &time, &ts );
#endif


    // number of days (include leap day 29feb 1900) until 01.01.1970 = 25569
    // plus number of days since 01.01.1970 (seconds since then divided by
    // seconds(60)*minutes(60)*hours(24) = 86400
    // see http://en.wikipedia.org/wiki/Epoch_%28reference_date%29
    // for comments about excel date calculation in the trivia section
    //return interpreter_variant( variant( 25569.0 + time / 86400.0 ) );
#ifdef _WIN32
    double date_time = 25569 + time / 86400 + ( ( ( ts->tm_hour % 24 ) * 3600 ) + ( ts->tm_min * 60 ) + ts->tm_sec ) / 86400.0;
#else
    double date_time = 25569 + time / 86400 + ( ( ( ts.tm_hour % 24 ) * 3600 ) + ( ts.tm_min * 60 ) + ts.tm_sec ) / 86400.0;
#endif
    return interpreter_variant( variant( date_time ) );

    // Numbers to the right of the decimal point represent the time.
    // Numbers to the left represent the date.
    // The NOW function changes only when the worksheet is calculated,
    // or when a macro that contains the function is run. It is not updated continuously.
}
