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
namespace function_helper_internals
{

    template<class T>
    class array_helper;

    /*!
    * \brief
    * little helper templates
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    template<typename T>
    struct reference_or_valueT {
        typedef const T type;
    };

    template<>
    struct reference_or_valueT<std::string> {
        typedef const std::string& type;
    };

    template<>
    struct reference_or_valueT<utf8_ci_string> {
        typedef const utf8_ci_string& type;
    };

    template<>
    struct reference_or_valueT<variant> {
        typedef const variant& type;
    };

    template<>
    struct reference_or_valueT<interpreter_variant> {
        typedef const interpreter_variant& type;
    };

    template<>
    struct reference_or_valueT<variant::sparse_array_type> {
        typedef const variant::sparse_array_type& type;
    };

    template<typename T>
    struct reference_or_value {
        typedef typename reference_or_valueT<T>::type type;
    };

    //typedef boost::optional<size_t> optional_size_type;
    typedef size_t optional_size_type;

    template<class T>
    class array_helper
    {
    public:
        typedef typename reference_or_value<T>::type value_type;

        array_helper( value_type a )
            : m_value( a ) {}

        inline const variant& get() const {
            return m_value;
        }


        inline value_type default_value() const {
            return m_value;
        }

        //needed to ensure the interface is correct
        inline operator bool () const {
            return true;
        }

        inline void operator++() const {}

        static inline const size_t idx() {
            return 0;
        }

        static inline bool has_idx() {
            return false;
        }


    private:
        value_type m_value;
    };


    template<>
    class array_helper<variant::sparse_array_type>
    {
        typedef variant::sparse_array_type::mapping_type::const_iterator const_iterator;
        typedef bool array_type;

    public:
        array_helper( const variant::sparse_array_type& a )
            : m_current( a.direct().begin() )
            , m_end( a.direct().end() )
            , m_default_value( a.default_value() )
            , m_size( a.size() ) {}

        inline operator bool () const {
            return m_current != m_end;
        }

        inline const variant& get() const {
            return m_current->second;
        }

        inline const size_t idx() const {
            return m_current->first;
        }

        static inline bool has_idx() {
            return true;
        }

        inline void operator++() {
            ++m_current;
        }

        inline const variant& default_value() const {
            return m_default_value;
        }

        inline const size_t size()const {
            return m_size;
        }

    private:
        const_iterator m_current;
        const_iterator m_end;
        const variant& m_default_value;
        const size_t m_size;
    };


    template<typename T>
    struct size_extractorT : non_instantiable {
        typedef typename reference_or_value<T>::type argument_type;
        static const bool can_have_size() {
            return false;
        }
        static const optional_size_type size( argument_type t ) {
            return 1;
        }
    };

    template<>
    struct size_extractorT<variant::sparse_array_type> : non_instantiable {
        static const bool can_have_size() {
            return true;
        }
        static const optional_size_type size( const variant::sparse_array_type& t ) {
            return t.size();
        }
    };

    template<>
    struct size_extractorT<array_helper<variant::sparse_array_type> > : non_instantiable {
        static const bool can_have_size() {
            return true;
        }
        static const optional_size_type size( const array_helper<variant::sparse_array_type>& t ) {
            return t.size();
        }
    };



    struct size_extractor {

        template<class A, class B, class C>
        static size_t size( typename reference_or_value<A>::type a, typename reference_or_value<B>::type b, typename reference_or_value<C>::type c ) {
            if ( !( size_extractorT<C>::can_have_size() || size_extractorT<C>::can_have_size() || size_extractorT<C>::can_have_size() ) ) {
                return 1;
            } else {
                optional_size_type return_size = 1;
                if ( size_extractorT<A>::can_have_size() ) {
                    const optional_size_type size_of_a = size_extractorT<A>::size( a );
                    return_size = size_of_a;
                }
                if ( size_extractorT<B>::can_have_size() ) {
                    const optional_size_type size_of_b( size_extractorT<B>::size( b ) );
                    if ( size_extractorT<A>::can_have_size() ) {
                        return_size = std::min<size_t>( return_size, size_of_b );
                    } else {
                        return_size = size_of_b;
                    }
                }
                if ( size_extractorT<C>::can_have_size() ) {
                    const optional_size_type size_of_c( size_extractorT<C>::size( c ) );
                    if ( size_extractorT<B>::can_have_size() || size_extractorT<A>::can_have_size() ) {
                        return_size = std::min<size_t>( return_size, size_of_c );
                    } else {
                        return_size = size_of_c;
                    }
                }
                return return_size;
            }
        }

        template<class A, class B>
        static size_t size( typename reference_or_value<A>::type a, typename reference_or_value<B>::type b ) {
            return size<A, B, int>( a, b, 1 );
        }
    };


    template<class lhs_T, class rhs_T>
    struct check_not_both_non_arrays {
        typedef bool value;
    };

    template<>
    struct check_not_both_non_arrays<variant, variant> {
        typedef bool not_value;
    };

    struct calculate_current_idx : non_instantiable {

        template< class T, class U>
        static size_t idx( const T& t, const U& u ) {
            if ( t.has_idx() ) {
                return t.idx();
            } else {
                return u.idx();
            }
        }

        template< class T, class U, class V>
        static size_t idx( const T& t, const U& u, const V& v ) {
            if ( t.has_idx() ) {
                return t.idx();
            } else if ( u.has_idx() ) {
                return u.idx();
            } else {
                return v.idx();
            }
        }
    };

    struct check_for_array : non_instantiable {
        static bool check( const variant& v ) {
            return v.is_array();
        }

        static bool check( const interpreter_variant& v ) {
            return v.is_array();
        }

        template<class T>
        static bool check( const T& /*t*/ ) {
            return false;
        }
    };

    template<bool default_value, template<bool>class check_item_policy>
    struct create_bool_arrayT
            : non_instantiable
            , check_item_policy<default_value> {

        typedef create_bool_arrayT<default_value, check_item_policy> self_type;

        static variant::sparse_array_type create_array( const variant::sparse_array_type& a ) {
            variant::sparse_array_type result_array( a.size(), default_value );
            foreach( const variant::sparse_array_type::mapping_type::value_type & v, a.direct() ) {
                if ( self_type::check_for_non_default( v.second ) ) {
                    result_array.set( v.first, !default_value );
                }
            }
            return result_array;
        }

        static variant::sparse_array_type create_array( const variant::sparse_array_type& a, const locale& l ) {
            variant::sparse_array_type result_array( a.size(), default_value );
            foreach( const variant::sparse_array_type::mapping_type::value_type & v, a.direct() ) {
                if ( self_type::check_for_non_default( v.second, l ) ) {
                    result_array.set( v.first, !default_value );
                }
            }
            return result_array;
        }
    };

    template< template<bool>class check_item_policy >
    struct create_bool_array : non_instantiable {
        static variant::sparse_array_type create_array( const variant::sparse_array_type& a ) {
            if ( check_item_policy<true>::check_for_non_default( a.default_value() ) ) {
                return create_bool_arrayT<false, check_item_policy>::create_array( a );
            } else {
                return create_bool_arrayT<true, check_item_policy>::create_array( a );
            }
        }

        static variant::sparse_array_type create_array( const variant::sparse_array_type& a, const locale& l ) {
            if ( check_item_policy<true>::check_for_non_default( a.default_value(), l ) ) {
                return create_bool_arrayT<false, check_item_policy>::create_array( a, l );
            } else {
                return create_bool_arrayT<true, check_item_policy>::create_array( a, l );
            }
        }
    };



    struct no_check {
        template<class T>
        static bool check( const T& /*v*/ ) {
            return true;
        }
    };

    template < class transform_item_policy, class check_item_policy = no_check >
    struct create_variant_array
            : non_instantiable
            , check_item_policy
            , transform_item_policy
    {
        typedef create_variant_array<transform_item_policy, check_item_policy> self_type;

        template<class first_T, class second_T>
        static variant::sparse_array_type create_array(
            typename reference_or_value<first_T>::type first,
            typename reference_or_value<second_T>::type second,
            const locale& l ) {
            array_helper<first_T> first_array( first );
            array_helper<second_T> second_array( second );

            const size_t max_size = size_extractor::size<array_helper<first_T>, array_helper<second_T> >( first_array, second_array );

            variant::sparse_array_type result_array( max_size, transform_item_policy::transform( first_array.default_value(), second_array.default_value(), l ) );
            while ( first_array && second_array ) {
                result_array.set( calculate_current_idx::idx( first_array, second_array ), transform_item_policy::transform( first_array.get(), second_array.get(), l ) );
                ++first_array;
                ++second_array;
            }

            return result_array;
        }

        template<class first_T, class second_T, class third_T>
        static variant::sparse_array_type create_array(
            typename reference_or_value<first_T>::type first,
            typename reference_or_value<second_T>::type second,
            typename reference_or_value<third_T>::type third,
            const locale& l ) {
            array_helper<first_T> first_array( first );
            array_helper<second_T> second_array( second );
            array_helper<third_T> third_array( third );

            const size_t max_size = size_extractor::size<array_helper<first_T>, array_helper<second_T>, array_helper<third_T> >( first_array, second_array, third_array );

            variant::sparse_array_type result_array( max_size, transform_item_policy::transform( first_array.default_value(), second_array.default_value(), third_array.default_value(), l ) );

            while ( first_array && second_array && third_array ) {
                result_array.set( calculate_current_idx::idx( first_array, second_array, third_array ), transform_item_policy::transform( first_array.get(), second_array.get(), third_array.get(), l ) );
                ++first_array;
                ++second_array;
                ++third_array;
            }

            return result_array;
        }
        static variant::sparse_array_type create_array( const variant::sparse_array_type& a ) {
            variant::sparse_array_type result_array( a.size(), self_type::transform( a.default_value() ) );
            foreach( const variant::sparse_array_type::mapping_type::value_type & v, a.direct() ) {
                result_array.set( v.first, self_type::transform( v.second ) );
            }
            return result_array;
        }

        static variant::sparse_array_type create_array( const variant::sparse_array_type& a, const locale& l ) {
            variant::sparse_array_type result_array( a.size(), self_type::transform( a.default_value(), l ) );
            foreach( const variant::sparse_array_type::mapping_type::value_type & v, a.direct() ) {
                result_array.set( v.first, self_type::transform( v.second, l ) );
            }
            return result_array;
        }

    };
}
