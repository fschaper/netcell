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
 *  Radu Racariu <radu@yalos-solutions.com>
 */

#include "precompiled_header.hpp"

/*!
 * \brief
 * Returns the depreciation of an asset for a specified period using the fixed-declining balance method.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the depreciation
 *
 * \details
 * The fixed-declining balance method computes depreciation at a fixed rate.
 * DB uses the following formulas to calculate depreciation for a period:
 * (cost - total depreciation from prior periods) * rate
 * rate = 1 - ((salvage/cost)^(1/life)), rounded to three decimal places
 * Depreciation for the first and last periods is a special case.
 * For the first period, DB uses this formula:
 * cost * rate * month/12
 * For the last period, DB uses this formula:
 * ((cost - total depreciation from prior periods)*rate*(12-month))/12
 *
 * \see
 * function_ddb | function_sln | function_syd | function_vdb
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
interpreter_variant function_db( function_parameter& parameters )
{
    if ( parameters.count() < 4 || parameters.count() > 5 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    double cost     = parameters[0].numeric(); // the initial cost of the asset.
    double salvage  = parameters[1].numeric(); // the value at the end of the depreciation (sometimes called the salvage value of the asset).
    double life     = parameters[2].numeric(); // the number of periods over which the asset is being depreciated (sometimes called the useful life of the asset).
    int period   = static_cast<int>( parameters[3].numeric() ); // the period for which you want to calculate the depreciation. period must use the same units as life.
    int month = 12; // the number of months in the first year. If month is omitted, it is assumed to be 12.
    if ( parameters.count() > 4 ) {
        month = static_cast<int>( parameters[4].numeric() );
    }

    if ( cost < 0.0 || salvage < 0.0 || life <= 0.0 || period < 1 || month < 1 ) {
        return interpreter_variant( variant::error_num );
    }
    double rate = 1000.0 * ( 1.0 - pow( salvage / cost, 1.0 / life ) );
    rate = floor( rate + 0.5 )  / 1000.0; // rounded to three decimal places
    // For the first period, DB uses:
    double result = cost * rate * month / 12.0;

    if ( period == 1 ) {
        return interpreter_variant( variant( result ) );
    }

    for ( int i = 1; i < life; ++i ) {
        if ( i == period - 1 ) {
            return interpreter_variant( variant( ( cost - result ) * rate ) ); // depreciation for a period
        } else {
            result += ( cost - result ) * rate;
        }
    }
    // For the last period, DB uses:
    return interpreter_variant( variant( ( cost - result ) * rate * ( 12.0 - month ) / 12.0 ) );
    // Returns the depreciation of an asset for a specified period using the fixed-declining balance method.
}
