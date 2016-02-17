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
 * Returns the serial number of the current date.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the number of the current date
 *
 * \details
 * By default, January 1, 1900 is serial number 1, and January 1, 2008 is serial number 39448
 * because it is 39448 days after January 1, 1900.
 *
 * \see
 * function_now
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
interpreter_variant function_today( function_parameter& /*parameters*/ )
{
    std::time_t time = std::time( NULL );
    // number of days (include leap day 29feb 1900) until 01.01.1970 = 25569
    // plus number of days since 01.01.1970 (seconds since then divided by
    // seconds(60)*minutes(60)*hours(24) = 86400
    // see http://en.wikipedia.org/wiki/Epoch_%28reference_date%29
    // for comments about excel date calculation in the trivia section
    return interpreter_variant( variant( 25569.0 + time / 86400 ) );
}
