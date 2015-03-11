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
 *  Frieder Hofmann <frieder.hofmann@jedox.com>
 *  Radu Ialovoi <ialovoi@yalos-solutions.com>
 */

#include "precompiled_header.hpp"


/*!
 * \brief
 * Returns the number of periods for an investment based on periodic, constant payments and a constant interest rate.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the number of periods
 *
 * \details
 * pv*(1+rate)^nper + pmt*(1+rate*type)*((1+rate)^nper -1)/rate + fv = 0
 * If rate is 0, then: (pmt*nper) + pv + fv = 0
 *
 * \see
 * function_fv | function_ipmt | function_pmt | function_pv | function_rate
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */

interpreter_variant function_nper( function_parameter& parameters )
{
    if ( parameters.count() < 3 || parameters.count() > 5 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    double rate = parameters[0].numeric(); // the interest rate per period.
    double pmt = parameters[1].numeric(); // the payment made each period; it cannot change over the life of the annuity.
    // Typically, pmt contains principal and interest but no other fees or taxes.
    double pv = parameters[2].numeric(); // the present value, or the lump-sum amount that a series of future payments is worth right now.
    double fv = 0.0; // the future value, or cash balance you want to attain after the last payment is made.
    if ( parameters.count() > 3 && parameters[3].type() != variant::type_empty ) {
        fv = parameters[3].numeric();
    }
    double type = 0.0; // indicates when payments are due.
    // 0 or omitted: payments are due at the end of the period.
    // 1: payments are due at the beginning of the period.
    if ( parameters.count() > 4 ) {
        type = parameters[4].numeric();
    }
    double result;
    if ( rate == 0.0 ) {
        return interpreter_variant( variant( -( pv + fv ) / pmt ) );
    }

    if ( type == 0.0 ) {
        result = log( ( pmt - fv * rate ) / ( pmt + pv * rate ) ) / log( 1.0 + rate );
    } else {
        result = log( ( -fv * rate + pmt * ( 1.0 + rate ) ) / ( pv * rate + pmt * ( 1.0 + rate ) ) ) / log( 1.0 + rate );
    }
    return interpreter_variant( variant( result ) );
    // Returns the number of periods for an investment based on periodic, constant payments and a constant interest rate.
}
