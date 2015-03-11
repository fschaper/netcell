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
 * CHITEST returns the value from the chi-squared distribution for the statistic as test for independence.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the value from the chi-squared distribution for the statistic as test for independence
 *
 * \details
 *
 * \see
 * function_chidist | function_chiinv
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 */
interpreter_variant function_chitest( function_parameter& parameters )
{
    if ( parameters.count() != 2 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    interpreter_variant actual_range = parameters[0];
    interpreter_variant expected_range = parameters[1];
    if ( ( actual_range.i_type() != interpreter_variant::type_range && actual_range.type() != variant::type_array )
            || ( expected_range.i_type() != interpreter_variant::type_range && expected_range.type() != variant::type_array ) ) {
        return interpreter_variant( variant::error_n_a );
    }
    variant::sparse_array_type actual_arr, expected_arr;
    if ( actual_range.i_type() == interpreter_variant::type_range ) {
        range_reference& rrefa = range_reference_cast( actual_range.reference() );
        sparse_range_array sraa( rrefa, parameters.context() );
        size_t imaxa = sraa.size();
        actual_arr = variant::sparse_array_type( imaxa );
        for ( unsigned int i = 0; i < imaxa; i++ ) {
            actual_arr[i] = sraa[i];
        }
    } else {
        actual_arr = actual_range.array();
    }
    boost::int_fast32_t expectedColumnWidth;
    if ( expected_range.i_type() == interpreter_variant::type_range ) {
        range_reference& rrefe = range_reference_cast( expected_range.reference() );
        sparse_range_array srae( rrefe, parameters.context() );
        size_t imaxe = srae.size();
        expected_arr = variant::sparse_array_type( imaxe );
        for ( unsigned int i = 0; i < imaxe; i++ ) {
            expected_arr[i] = srae[i];
        }
        expectedColumnWidth = rrefe.actualize().position().column_count();
    } else {
        expected_arr = expected_range.array();
        expectedColumnWidth = expected_range.column_width();
    }
    size_t actualArraySize = actual_arr.size();
    size_t expectedArraySize = expected_arr.size();
    if ( actualArraySize != expectedArraySize || actualArraySize == 1 ) {
        return interpreter_variant( variant::error_n_a );
    }
    double x = 0.0;
    bool found = false;
    variant actVali, expVali;
    double diff;
    for ( size_t i = 0; i < expectedArraySize; i++ ) {
        actVali = actual_arr[i];
        if ( actVali.type() == variant::type_error ) {
            return interpreter_variant( actVali );
        }
        expVali = expected_arr[i];
        if ( expVali.type() == variant::type_error ) {
            return interpreter_variant( expVali );
        }
        if ( actVali.type() != variant::type_double || expVali.type() != variant::type_double ) {
            continue;
        }
        diff = actVali.numeric() - expVali.numeric();
        x += diff * diff / expVali.numeric();
        found = true;
    }
    if ( !found ) {
        return interpreter_variant( variant::error_div_null );
    }
    // boost::int_fast32_t actualColumnWidth = actual_value.column_width();
    // boost::int_fast32_t actualRows = actualArraySize / actualColumnWidth;
    size_t expectedRows = expectedArraySize / expectedColumnWidth;
    double degrees_freedom;
    if ( expectedRows == 1 ) {
        degrees_freedom = expectedColumnWidth - 1.0;
    } else if ( expectedColumnWidth == 1 ) {
        degrees_freedom = expectedRows - 1.0;
    } else {
        degrees_freedom = ( expectedRows - 1.0 ) * ( expectedColumnWidth - 1.0 );
    }
    boost::math::chi_squared dist( degrees_freedom );
    double result = cdf( complement( dist, x ) );
    return interpreter_variant( variant( result ) );
    // Returns the test for independence.
    // CHITEST returns the value from the chi-squared distribution for the statistic
    // and the appropriate degrees of freedom.
}

