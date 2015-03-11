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
 * TRIMMEAN calculates the mean taken by excluding a percentage of data points from the top and bottom tails of a data set.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the trimmed mean
 *
 * \details
 * TRIMMEAN rounds the number of excluded data points down to the nearest multiple of 2.
 * If percent = 0.1, 10 percent of 30 data points equals 3 points.
 * For symmetry, TRIMMEAN excludes a single value from the top and bottom of the data set.
 *
 * \see
 * function_average | function_geomean | function_harmean | function_median | function_mode
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
interpreter_variant function_trimmean( function_parameter& parameters )
{
    if ( parameters.count() != 2 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    // Error values cause errors.
    if ( parameters[1].type() == variant::type_error ) {
        return parameters[1];
    }
    double percent = 0.0; // the fractional number of data points to exclude from calculation.
    if ( parameters[1].type() == variant::type_string ) {
        try { // text representation of numbers or logical values are counted.
            percent = boost::lexical_cast<double>( parameters[1].string() );
        } catch ( boost::bad_lexical_cast& ) { // text that cannot be translated into numbers causes the #VALUE! error value.
            return interpreter_variant( variant::error_value );
        }
    } else {
        percent = parameters[1].numeric();
    }
    // If percent < 0 or percent >= 1, TRIMMEAN returns the #NUM! error value.
    if ( percent < 0.0 || percent >= 1.0 ) {
        return interpreter_variant( variant::error_num );
    }

    double result = 0.0;
    std::vector<double> vx;
    if ( parameters[0].i_type() == interpreter_variant::type_range || parameters[0].type() == variant::type_array ) {
        variant::sparse_array_type arr;
        if ( parameters[0].i_type() == interpreter_variant::type_range ) {
            range_reference& rref = range_reference_cast( parameters[0].reference() );
            sparse_range_array sra( rref, parameters.context() );
            size_t imax = sra.size();
            arr = variant::sparse_array_type( imax );
            for ( unsigned int i = 0; i < imax; i++ ) {
                arr[i] = sra[i];
            }
        } else {
            arr = parameters[0].array();
        }
        size_t arraySize = arr.size();
        for ( unsigned long int i = 0; i < arraySize; i++ ) {
            variant xi = arr[i];
            // error values cause errors.
            if ( xi.type() == variant::type_error ) {
                return interpreter_variant( xi );
            }
            // If the array or reference contains empty cells, logical values, or text, those values are ignored.
            if ( xi.type() == variant::type_double ) {
                vx.push_back( xi.numeric() );
            }

        }
        // If the array or reference contains no counted value, TRIMMEAN returns the #NUM! error value.
        if ( vx.size() == 0 ) {
            return interpreter_variant( variant::error_num );
        }
        std::sort( vx.begin(), vx.end() );
        unsigned long int exclude = static_cast<unsigned long int>( 0.5 * percent * vx.size() );
        for ( unsigned long int i = 0; i < exclude; i++ ) {
            vx.pop_back();
            vx.erase( vx.begin() );
        }
        size_t vcount = vx.size();
        double summe = 0;
        for ( unsigned long int i = 0; i < vcount; i++ ) {
            summe += vx[i];
        }
        result = summe / vcount;
    } else {
        // error values cause errors.
        if ( parameters[0].type() == variant::type_error ) {
            return parameters[0];
        }

        if ( parameters[0].type() == variant::type_string ) {
            try { // text representation of numbers or logical values are counted.
                result = boost::lexical_cast<double>( parameters[0].string() );
            } catch ( boost::bad_lexical_cast& ) { // text that cannot be translated into numbers causes the #VALUE! error value.
                return interpreter_variant( variant::error_value );
            }
        } else {
            result = parameters[0].numeric();
        }
    }
    return interpreter_variant( variant( result ) );
    // Returns the mean of the interior of a data set.
    // TRIMMEAN calculates the mean taken by excluding a percentage of data points
    // from the top and bottom tails of a data set.
}

