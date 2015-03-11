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


variant compute_percentrank( const double& target, const variant& range, int& significance )
{


    double max_smaller = std::numeric_limits<double>::min();
    double min_greater = std::numeric_limits<double>::max();

    size_t smaller_cnt = 0;
    size_t greater_cnt = 0;
    size_t count = 0;

    double percentrank = 1;

    foreach( const variant::sparse_array_type::mapping_type::value_type & i, range.array().direct() ) {
        if ( variant::type_array == i.second.type() ) {
            foreach( const variant::sparse_array_type::mapping_type::value_type & v, i.second.array().direct() ) {
                if ( !v.second.is_double() ) {
                    continue;
                }
                double crt = v.second.as_double();
                count++;
                if ( crt >= target ) {
                    greater_cnt++;
                    if ( crt < min_greater ) {
                        min_greater = crt;
                    }
                }
                if ( crt <= target ) {
                    smaller_cnt++;
                    if ( crt > max_smaller ) {
                        max_smaller = crt;
                    }
                }
            }
        } else {
            if ( !i.second.is_double() ) {
                continue;
            }
            double crt = i.second.as_double();
            count++;
            if ( crt >= target ) {
                greater_cnt++;
                if ( crt < min_greater ) {
                    min_greater = crt;
                }
            }
            if ( crt <= target ) {
                smaller_cnt++;
                if ( crt > max_smaller ) {
                    max_smaller = crt;
                }
            }
        }
    }

    if ( max_smaller == target ) {
        double pRank = static_cast<double>( smaller_cnt - 1 ) / ( count - 1 );
        percentrank = static_cast<long long int>( pRank * pow( 10.0, significance ) ) * pow( 10.0, -significance );
        return variant( percentrank );
    }

    if ( 0 == smaller_cnt || 0 == greater_cnt ) {
        return interpreter_variant( variant::error_n_a );
    }

    double rank_smaller = static_cast<double>( smaller_cnt - 1 ) / ( count - 1 );
    double rank_greater = static_cast<double>( count - greater_cnt ) / ( count - 1 );

    double pRank = ( target - max_smaller ) / ( min_greater - max_smaller ) * ( rank_greater - rank_smaller ) + rank_smaller;
    percentrank = static_cast<long long int>( pRank * pow( 10.0, significance ) ) * pow( 10.0, -significance );

    return variant( percentrank );
}


/*!
 * \brief
 * Returns the rank of a value in a data set as a percentage of the data set.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the rank of the value in the data set as a percentage of the data set
 *
 * \details
 *
 *
 * \see
 * function_large | function_max | function_median | function_min | function_percentile | function_quartile | function_small
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 * Vali Nitu <vali@yalos-solutions.com>
 */
interpreter_variant function_percentrank( function_parameter& parameters )
{
    if ( parameters.count() < 2 || parameters.count() > 3 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }


    int significance = 3; // the number of significant digits for the returned percentage value.
    // If significance is omitted, PERCENTRANK uses 3 digits.
    if ( parameters.count() > 2 ) {
        significance = static_cast<int>( parameters[2].as_double() );
    }
    // If significance < 1, PERCENTRANK returns the #NUM! error value.
    if ( significance < 1 ) {
        return interpreter_variant( variant::error_num );
    }

    if ( variant::type_array != parameters[0].type() ) {
        if ( !parameters[0].is_double() ) {
            return( interpreter_variant( variant::error_n_a ) );
        }
        if ( !parameters[1].is_double() ) {
            return( interpreter_variant( variant::error_value ) );
        }

        if ( parameters[0].as_double() == parameters[1].as_double() ) {
            return interpreter_variant( 1.0 );
        }
        return( interpreter_variant( variant::error_value ) );
    }


    if ( variant::type_array == parameters[1].type() ) {

        variant::sparse_array_type  result_array;

        const variant::sparse_array_type& arr = parameters[1].array();
        range_reference& rref = range_reference_cast( parameters[1].reference() );
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
                result_array.push_back( compute_percentrank( d, parameters[0], significance ) );
            }
        }

        return interpreter_variant( variant( result_array, width ) );

    } else {
        return interpreter_variant( compute_percentrank( parameters[1].as_double(), parameters[0], significance ) );
    }


}
