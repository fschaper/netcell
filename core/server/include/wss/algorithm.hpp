/**
 *  \file
 *  Copyright (C) 2006-2010 Jedox AG, Freiburg i.Br., Germany
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
 *  \Author
 *  Florian Schaper <florian.schaper@jedox.com>
 */

#pragma once

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <algorithm>
#   include <functional>
#endif

/*!
 * \brief
 * returns true if the value is between the passed arguments.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
template
<
class argument_T
>
struct between
        : std::unary_function<argument_T, bool>
{
    typedef typename std::unary_function<argument_T, bool>::argument_type argument_type;
    typedef typename std::unary_function<argument_T, bool>::result_type result_type;

    between( const argument_type& a, const argument_type& b )
        : m_min( std::min( a, b ) )
        , m_max( std::max( a, b ) ) {}

    result_type operator()( const argument_type& arg ) const {
        return arg >= m_min && arg <= m_max;
    }

    const argument_type m_min;
    const argument_type m_max;
};

/*!
 * \brief
 * returns true if the value is between or equal to the passed arguments.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
template
<
class argument_T
>
struct between_equal
        : std::unary_function<argument_T, bool>
{
    typedef typename std::unary_function<argument_T, bool>::argument_type argument_type;
    typedef typename std::unary_function<argument_T, bool>::result_type result_type;

    between_equal( const argument_type& a, const argument_type& b )
        : m_min( std::min( a, b ) )
        , m_max( std::max( a, b ) ) {}

    result_type operator()( const argument_type& arg ) const {
        return arg >= m_min && arg <= m_max;
    }

    const argument_type m_min;
    const argument_type m_max;
};

/*!
 * \brief
 * delete functor
 *
 * free's the passed pointer
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
struct free_pointer {
    template<typename argument_T>
    void operator()( argument_T* ptr ) {
        delete ptr;
    }
};

/*!
 * \brief
 * returns the first argument of an std::pair
 *
 * Sample usage:
 * typedef std::map<std::string,int> SomeMap;
 * typedef boost::transform_iterator<get_first<SomeMap>, typename SomeMap::iterator > map_key_iterator;
 *
 * \see
 * get_first
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
template
<
class argument_T
>
struct get_first
{
    typedef typename argument_T::value_type::first_type result_type;
    const result_type& operator()( const typename argument_T::value_type& e ) const {
        return e.first;
    }

    result_type operator()( const typename argument_T::value_type& e ) {
        return e.first;
    }
};

/*!
 * \brief
 * returns the second argument of an std::pair
 *
 * Sample usage:
 * typedef std::map<std::string,int> SomeMap;
 * typedef boost::transform_iterator<get_second<SomeMap>, typename SomeMap::iterator > map_value_iterator;
 *
 * \see
 * get_first
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
template
<
class argument_T
>
struct get_second
{
    typedef typename argument_T::value_type::second_type result_type;

    const result_type& operator()( const typename argument_T::value_type& e ) const {
        return e.second;
    }

    result_type operator()( const typename argument_T::value_type& e ) {
        return e.second;
    }
};

/*!
 * \brief
 * returns a pointer to the passed reference
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
template
<
class argument_T
>
struct pointer_of : std::unary_function<argument_T&, argument_T*>
{
    typedef typename std::unary_function<argument_T&, argument_T*>::result_type result_type;
    typedef typename std::unary_function<argument_T&, argument_T*>::argument_type argument_type;

    result_type operator()( argument_type v ) const {
        return &v;
    }
};

/*!
 * \brief
 * dereferences a pointer
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
template
<
class argument_T
>
struct reference_of : std::unary_function<argument_T*, argument_T&>
{
    typedef typename std::unary_function<argument_T*, argument_T&>::result_type result_type;
    typedef typename std::unary_function<argument_T*, argument_T&>::argument_type argument_type;

    result_type operator()( argument_type v ) const {
        return *v;
    }
};
