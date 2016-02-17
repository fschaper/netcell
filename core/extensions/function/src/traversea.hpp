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
 *  Radu Ialovoi <ialovoi@yalos-solutions.com>
 */

#include <wss/variant.hpp>
#include <wss/function_parameters.hpp>
#include <boost/foreach.hpp>
#define foreach BOOST_FOREACH

#pragma once

template < class T >
inline variant traversea( const function_parameter& parameters, T& algorithm )
{
    foreach( const interpreter_variant & i, parameters ) {
        switch ( i.type() ) {
            case variant::type_empty:
                //nothing to do in that case
                break;
            case variant::type_array:
                if ( /*interpreter_variant::type_range == i.i_type*/ i.is_range() ) {
                    foreach( const variant::sparse_array_type::mapping_type::value_type & v, i.array().direct() ) {
                        if ( v.second.is_error() ) {
                            algorithm.error( v.second );
                            return algorithm.error();
                        }
                        if ( v.second.is_string() ) {
                            algorithm( variant( 0.0 ) );
                        } else {
                            algorithm( v.second );
                        }
                    }
                } else {
                    foreach( const variant::sparse_array_type::mapping_type::value_type & v, i.array().direct() ) {
                        if ( !v.second.is_double() ) {
                            continue;
                        }
                        algorithm( v.second );
                    }
                }
                break;
            case variant::type_double:
            case variant::type_bool:
                algorithm( i );
                break;
            case variant::type_string:
                try {
                    //i.as_double();          //check for numeric string
                    double newDouble = boost::lexical_cast<double>( static_cast<const std::string&>( i.string() ) );
                    algorithm( newDouble );
                } catch ( boost::bad_lexical_cast& ) {
                    return variant( variant::error_value );
                }
                break;
            case variant::type_error:
                algorithm.error( i );
                return algorithm.error();
                break;
            default:
                throw std::runtime_error( "invalid case " );
        }
    }

    return algorithm;
}

