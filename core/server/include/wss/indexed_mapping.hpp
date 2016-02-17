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
 *  <a href=<wss/http://www.jedox.com/license_palo_bi_suite.txt>>
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
 *  Florian Schaper <florian.schaper@jedox.com>
 */

#pragma once

#include <wss/algorithm.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <stdexcept>
#   include <boost/bind.hpp>
#   include <boost/iterator/transform_iterator.hpp>
#   include <algorithm>
#   include <map>
#endif

namespace policy
{
    class default_index
    {
    public:
        typedef std::size_t index_type;
        default_index() : m_counter( 0 ) {}

        index_type create_new_index() {
            return ++m_counter;
        }

    private:
        index_type m_counter;
    };
}

/*!
 * \brief
 * maps an index to an value type.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
template < class type_T, class index_T = policy::default_index >
class indexed_mapping
    : protected index_T
{
public:
    typedef type_T value_type;
    typedef typename index_T::index_type index_type;
    typedef std::map<index_type, value_type> container_type;
    typedef typename container_type::size_type size_type;
    typedef typename container_type::key_type key_type;

    typedef boost::transform_iterator<get_second<container_type>, typename container_type::const_iterator > const_iterator;
    typedef boost::transform_iterator<get_second<container_type>, typename container_type::iterator > iterator;

    using index_T::create_new_index;

    value_type& operator[]( const index_type& index ) {
        typename container_type::iterator it( m_container.find( index ) );
        if ( it == m_container.end() ) {
            throw std::out_of_range( "invalid index for indexed_mapping" );
        }
        return it->second;
    }

    const value_type& operator[]( const index_type& index ) const {
        typename container_type::const_iterator it( m_container.find( index ) );
        if ( it == m_container.end() ) {
            throw std::out_of_range( "invalid index for indexed_mapping" );
        }
        return it->second;
    }

    index_type set( const value_type& v ) {
        typename container_type::const_iterator it( std::find_if( m_container.begin(), m_container.end(), boost::bind( &container_type::value_type::second, _1 ) == boost::ref( v ) ) );
        if ( it != m_container.end() ) {
            return it->first;
        }
        index_type new_index( index_T::create_new_index() );
        m_container.insert( typename container_type::value_type( new_index, v ) );
        return new_index;
    }

    size_type size() const {
        return m_container.size();
    }

    bool empty() const {
        return m_container.empty();
    }

    void erase( iterator it ) {
        m_container.erase( it );
    }

    void erase( iterator first, iterator last ) {
        m_container.erase( first, last );
    }

    size_type erase( const key_type& key ) {
        return m_container.erase( key );
    }

    const_iterator begin() const {
        return const_iterator( m_container.begin() );
    }

    const_iterator end() const {
        return const_iterator( m_container.end() );
    }

    iterator begin() {
        return iterator( m_container.begin() );
    }

    iterator end() {
        return iterator( m_container.end() );
    }

private:
    container_type m_container;
};

