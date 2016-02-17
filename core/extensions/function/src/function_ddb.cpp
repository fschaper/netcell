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
 * Returns the depreciation of an asset for a specified period
 * using the double-declining balance method or some other method you specify.
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
 * All five arguments must be positive numbers.
 * The double-declining balance method computes depreciation at an accelerated rate.
 * Depreciation is highest in the first period and decreases in successive periods.
 * DDB uses the following formula to calculate depreciation for a period:
 * ((cost-salvage) - total depreciation from prior periods)*(factor/life)
 * Change factor if you do not want to use the double-declining balance method.
 * Use the VDB function if you want to switch to the straight-line depreciation method
 * when depreciation is greater than the declining balance calculation.
 *
 * \see
 * function_sln | function_syd | function_vdb
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
interpreter_variant function_ddb( function_parameter& parameters )
{
    if ( parameters.count() < 4 || parameters.count() > 5 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    double cost     = parameters[0].numeric(); // the initial cost of the asset.
    double salvage  = parameters[1].numeric(); // the value at the end of the depreciation (sometimes called the salvage value of the asset).
    double life     = parameters[2].numeric(); // the number of periods over which the asset is being depreciated (sometimes called the useful life of the asset).
    double period   = parameters[3].numeric(); // the period for which you want to calculate the depreciation. period must use the same units as life.
    double factor   = 2; // the rate at which the balance declines. If factor is omitted, it is assumed to be 2 (the double-declining balance method).
    if ( parameters.count() > 4 ) {
        factor = parameters[4].numeric();
    }

    if ( cost < 0.0 || salvage < 0.0 || life <= 0.0 || period < 0.0 || factor < 0.0 ) {
        return interpreter_variant( variant::error_num );
    }
    double result = 0.0;
    for ( size_t i = 0; i < life - 1; ++i ) {
        double tmpRes = ( cost - result ) * ( factor / life );
        if ( i == period - 1 ) {
            return interpreter_variant( variant( tmpRes ) );
        } else {
            result += tmpRes;
        }
    }
    return interpreter_variant( variant( cost - result - salvage ) );
    // Returns the depreciation of an asset for a specified period
    // using the double-declining balance method or some other method you specify.
}
