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
#   include <map>
#   include <algorithm>
#   include <boost/bind.hpp>
#endif

/*!
 * \brief
 * sparse indexed container for maintaining sheet layout information.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
template
<
typename integer_T
, typename value_T = integer_T
>
class sparse_indexed_integer_container
{
public:
    typedef integer_T index_type;
    typedef value_T value_type;
    typedef const value_type& const_reference;
    typedef std::map<index_type, value_type> defined_values_map_type;
    typedef typename defined_values_map_type::const_iterator const_iterator;
    typedef typename defined_values_map_type::size_type size_type;

public:
    sparse_indexed_integer_container()
        : m_default_value( 0 ) {}

    sparse_indexed_integer_container( value_type default_value )
        : m_default_value( default_value ) {}

    void set_default( value_type default_value ) {
        m_default_value = default_value;

        // erase all values if a new default value is set
        for ( typename defined_values_map_type::iterator it(
                    std::find_if( m_value_map.begin(), m_value_map.end(),
                                  boost::bind( &defined_values_map_type::value_type::second, _1 ) == m_default_value ) );
                it != m_value_map.end();
                it = std::find_if( m_value_map.begin(), m_value_map.end(), boost::bind( &defined_values_map_type::value_type::second, _1 ) == m_default_value ) ) {
            m_value_map.erase( it );
        }
    }

    //special version that will erase the whole map and set a new default value
    void clear_and_set_default( value_type default_value ) {
        m_value_map.clear();
        m_default_value = default_value;
    }

    value_type get_default() const {
        return m_default_value;
    }

    void set( index_type index, value_type value ) {
        if ( get_default() == value ) {
            m_value_map.erase( index );
        } else {
            m_value_map[ index ] = value;
        }
    }

    /*!
     * \brief
     * shift num_idxs to the right starting at index
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    void shift( index_type index, const int num_idxs ) {
        typename defined_values_map_type::iterator idx_it( m_value_map.lower_bound( index ) );
        const_iterator end_it( end() );
        if ( idx_it == end_it ) {
            return;
        }

        defined_values_map_type tmp_map( m_value_map.begin(), idx_it );

        while ( idx_it != end_it && idx_it->first + num_idxs < index  ) {
            ++idx_it;
        }
        for ( ; idx_it != end_it; ++idx_it ) {
            if ( static_cast< int >( idx_it->first ) + static_cast<int>( num_idxs )  >= static_cast<int>( index ) ) {
                tmp_map[ idx_it->first + num_idxs  ] = idx_it->second;
            }
        }
        m_value_map.swap( tmp_map );
    }

    value_type get( index_type index ) const {
        typename defined_values_map_type::const_iterator it( m_value_map.find( index ) );
        return ( it == m_value_map.end() ) ? get_default() : it->second;
    }

    size_type size() const {
        return m_value_map.size();
    }

    const_iterator begin() const {
        return m_value_map.begin();
    }

    const_iterator end() const {
        return m_value_map.end();
    }

private:
    value_type m_default_value;
    defined_values_map_type m_value_map;
};
