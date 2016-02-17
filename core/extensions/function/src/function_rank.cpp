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
#include <boost/foreach.hpp>
#define foreach BOOST_FOREACH

/*!
 * \brief
 * Returns the rank of a number in a list of numbers. helper for the rank call.
 *
 * \param double& target
 * the number to rank for
 *
 * \const variant& range
 * a range to for the number to rank withing.
 *
 * \const double& order
 * the sort order to use.
 *
 * \double& rank
 * the rank.
 *
 * \returns
 * false if an error ocured. true otherwise
 *
 * \details
 * The rank of a number is its size relative to other values in a list.
 * If you were to sort the list, the rank of the number would be its position.
 *
 * \see
 * function_rank
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
bool compute_rank( const double& target, const variant& range, const double& order, double& rank  )
{
    bool      target_found  = false;

    rank = 1;

    if ( 0 == order ) {
        foreach( const variant::sparse_array_type::mapping_type::value_type & v, range.array().direct() ) {
            if ( !v.second.is_double() ) {
                continue;
            }

            const double crt = v.second.as_double();

            if ( crt > target ) {
                rank++;
            } else if ( crt == target ) {
                target_found = true;
            }
        }
    } else {
        foreach( const variant::sparse_array_type::mapping_type::value_type & v, range.array().direct() ) {
            if ( !v.second.is_double() ) {
                continue;
            }
            const double crt = v.second.as_double();

            if ( crt < target ) {
                rank++;
            } else if ( crt == target ) {
                target_found = true;
            }
        }
    }

    return target_found;
}

/*!
 * \brief
 * Returns the rank of a number in a list of numbers.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the rank
 *
 * \details
 * The rank of a number is its size relative to other values in a list.
 * If you were to sort the list, the rank of the number would be its position.
 *
 * \see
 * function_percentrank
 *
 * \author
 * Radu Ialovoi <ialovoi@yalos-solutions.com>
 */
interpreter_variant function_rank( function_parameter& parameters )
{
    double      order = 0; // a number specifying how to rank the number.
    const size_t    param_count = parameters.count();

    if ( 2 > param_count || 3 < param_count ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    // If order is zero or omitted, Excel ranks number as if ref were a list sorted in descending order.
    if ( 3 == param_count ) {
        order = parameters[2].as_double();
        // If order is any nonzero value, Excel ranks number as if ref were a list sorted in ascending order.
    }

    if ( variant::type_array != parameters[1].type() ) {
        if ( parameters[0].as_double() == parameters[1].as_double() ) {
            return interpreter_variant( 1.0 );
        }
        return( interpreter_variant( variant::error_value ) );
    }

    if ( variant::type_array == parameters[0].type() ) {

        variant::sparse_array_type  result_array;
        double                      result;

        const variant::sparse_array_type& arr = parameters[0].array();
        range_reference& rref = range_reference_cast( parameters[0].reference() );
        unsigned int width =  rref.actualize().position().column_count();

        size_t n = arr.size();

        for ( size_t i = 0; i < n; i++ ) {
            if ( !arr[i].is_double() ) {
                if ( arr[i].is_string() ) {
                    result_array.push_back( variant( variant::error_value ) );
                } else {
                    result_array.push_back( variant( variant::error_n_a ) );
                }
            } else {
                double d = arr[i].as_double();
                if ( compute_rank( d, parameters[1], order, result ) ) {
                    result_array.push_back( variant( result ) );
                } else {
                    result_array.push_back( variant( variant::error_n_a ) );
                }
            }
        }

        return interpreter_variant( variant( result_array, width ) );
    } else {
        double      result;
        if ( compute_rank( parameters[0].as_double(), parameters[1], order, result ) ) {
            return interpreter_variant( result );
        } else {
            return interpreter_variant( variant::error_n_a );
        }
    }
}
