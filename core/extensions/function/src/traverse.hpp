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
#include "wss/function_parameters.hpp"
#include <wss/variant_conversion_exception.hpp>
#include <boost/foreach.hpp>
#define foreach BOOST_FOREACH

#pragma once

class error_handling_alg
{
public:
    inline error_handling_alg() {}
    virtual ~error_handling_alg() {}

    void error( const variant& e ) {
        m_error = e;
    }


    const variant& error() {
        assert( "error value not set!" && m_error.is_error() );
        return m_error;
    }
private:
    variant m_error;
};

template<class T, bool skip_nan_values>
bool handle_variant_and_return_success( const variant& i, T& algorithm )
{
    switch ( i.type() ) {
        case variant::type_empty:
            //nothing to do.. move along
            break;
        case variant::type_array:
            //TODO do we handle non empty default values correctly?
            //but of course we are...
            foreach( const variant::sparse_array_type::mapping_type::value_type & v, i.array().direct() ) {
                const bool success = handle_variant_and_return_success<T, skip_nan_values>( v.second, algorithm );
                if ( !success ) {
                    return false;
                }
            }
            break;
        case variant::type_double:
            algorithm( i );
            break;
        case variant::type_bool:
            if ( !skip_nan_values ) {
                algorithm( i );
            }
            break;
        case variant::type_string:
            if ( !skip_nan_values ) {
                try {
                    //check for numeric string
                    algorithm( i.as_double() );
                } catch ( const variant_conversion_exception& ) {
                    if ( !skip_nan_values ) {
                        algorithm.error( variant( variant::error_value ) );
                        return false;
                    }
                }
            }
            break;
        case variant::type_error:
            algorithm.error( i );
            return false;
            break;

        default:
            throw std::runtime_error( "invalid case " );
    }
    return true;
}

template < class T >
variant traverse( function_parameter& parameters, T& algorithm )
{
    foreach( const interpreter_variant & i, parameters ) {
        const bool skip_nan = i.i_type() ==  interpreter_variant::type_range ? true : false;
        bool success = false;
        if ( skip_nan ) {
            success = handle_variant_and_return_success<T, true>( i, algorithm );
        } else {
            success = handle_variant_and_return_success<T, false>( i, algorithm );
        }
        if ( !success ) {
            return algorithm.error();
        }
    }

    return algorithm;
}

