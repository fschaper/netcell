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
#pragma once

#include <boost/foreach.hpp>
#define foreach BOOST_FOREACH
#include "function_helper_internals.hpp"
#include <wss/interpreter_variant.hpp>

struct function_helper : non_instantiable {
    template <class transform_item_policy >
    static interpreter_variant create_array_or_return_single_value( const interpreter_variant& v ) {
        if ( v.is_array() ) {
            return interpreter_variant( function_helper_internals::template create_variant_array<transform_item_policy>::create_array( v.array() ) );
        }

        return interpreter_variant( transform_item_policy::transform( v ) );
    }
    template <class transform_item_policy >
    static interpreter_variant create_array_or_return_single_value( const interpreter_variant& v, const locale& l ) {
        typedef function_helper_internals::create_variant_array<transform_item_policy> array_creator;
        if ( v.is_array() ) {
            return interpreter_variant( variant( array_creator::create_array( v.array(), l ) ) );
        }

        return interpreter_variant( transform_item_policy::transform( v, l ) );
    }

    template< template<bool>class check_item_policy >
    static interpreter_variant create_array_or_return_single_value( const interpreter_variant& v ) {
        typedef typename function_helper_internals::create_bool_array<check_item_policy> array_creator;
        if ( v.is_array() ) {
            return  interpreter_variant( array_creator::create_array( v.array() ) );
        }

        return interpreter_variant( check_item_policy<false>::check_for_non_default( v ) );
    }

    template< template<bool>class check_item_policy >
    static interpreter_variant create_array_or_return_single_value( const interpreter_variant& v, const locale& l ) {
        typedef function_helper_internals::create_bool_array<check_item_policy> array_creator;
        if ( variant::type_array == v.type() ) {
            return interpreter_variant( array_creator::create_array( v.array(), l ) );
        }

        return interpreter_variant( check_item_policy<false>::check_for_non_default( v, l ) );
    }

    template<class lhs_T, class rhs_T, class transform_item_policy>
    static interpreter_variant create_array_or_return_single_value(
        typename function_helper_internals::reference_or_value<lhs_T>::type lhs,
        typename function_helper_internals::reference_or_value<rhs_T>::type rhs,
        const ::locale& l ) {
        typedef typename function_helper_internals::create_variant_array<transform_item_policy> array_creator;
        typedef variant::sparse_array_type array_type;
        const bool first_is_array = function_helper_internals::check_for_array::check( lhs );
        const bool second_is_array = function_helper_internals::check_for_array::check( rhs );

        if ( first_is_array ) {
            if ( second_is_array ) {
                return interpreter_variant( array_creator::template create_array<array_type, array_type>( lhs.array(), rhs.array(), l ) );
            } else {
                return interpreter_variant( array_creator::template create_array<array_type, rhs_T>( lhs.array(), rhs, l ) );
            }
        } else if ( second_is_array ) {
            return interpreter_variant( array_creator::template create_array<lhs_T, array_type>( lhs, rhs.array(), l ) );
        }
        return interpreter_variant( transform_item_policy::transform( lhs, rhs, l ) );
    }

    template<class first_T, class second_T, class third_T, class transform_item_policy>
    static interpreter_variant create_array_or_return_single_value(
        typename function_helper_internals::reference_or_value<first_T>::type first,
        typename function_helper_internals::reference_or_value<second_T>::type second,
        typename function_helper_internals::reference_or_value<third_T>::type third,
        const locale& l ) {
        typedef function_helper_internals::create_variant_array<transform_item_policy> array_creator;
        typedef variant::sparse_array_type array_type;
        const bool first_is_array = function_helper_internals::check_for_array::check( first );
        const bool second_is_array = function_helper_internals::check_for_array::check( second );
        const bool third_is_array = function_helper_internals::check_for_array::check( third );

        if ( first_is_array ) {
            if ( second_is_array ) {
                if ( third_is_array ) {
                    return interpreter_variant( array_creator::template create_array<array_type, array_type, array_type>( first.array(), second.array(), third.array(), l ) );
                } else {
                    return interpreter_variant( array_creator::template create_array<array_type, array_type, third_T>( first.array(), second.array(), third, l ) );
                }
            } else {
                if ( third_is_array ) {
                    return interpreter_variant( array_creator::template create_array<array_type, second_T, array_type>( first.array(), second, third.array(), l ) );
                } else {
                    return interpreter_variant( array_creator::template create_array<array_type, second_T, third_T>( first.array(), second, third, l ) );
                }
            }
        }
        if ( second_is_array ) {
            if ( third_is_array ) {
                return interpreter_variant( array_creator::template create_array<first_T, array_type, array_type>( first, second.array(), third.array(), l ) );
            } else {
                return interpreter_variant( array_creator::template create_array<first_T, array_type, third_T>( first, second.array(), third, l ) );
            }
        }
        if ( third_is_array ) {
            return interpreter_variant( array_creator::template create_array<first_T, second_T, array_type>( first, second, third.array(), l ) );
        }
        return interpreter_variant( transform_item_policy::transform( first, second, third, l ) );
    }
};


struct row_col_helper : non_instantiable {
    static inline const shared_dependency_type& initiator( const interpreter_context& ic ) {
        return ic.is_inside_named_formula()
               ? ic.named_formula_initiator() : ic.caller();
    }
};
