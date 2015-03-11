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
 *  Florian Schaper <florian.schaper@jedox.com>
 */

#pragma once

#include <wss/point.hpp>

#include <iterator>

namespace geometry
{
    /*!
     * \brief
     * iterates over the points of an rectangle.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    class rectangle_iterator
    {
    public:
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef point value_type;
        typedef int difference_type;
        typedef point pointer;
        typedef point reference;

    public:
        rectangle_iterator& operator ++() {
            next();
            return *this;
        }

        rectangle_iterator& operator --() {
            previous();
            return *this;
        }

        rectangle_iterator operator ++( int ) const {
            rectangle_iterator tmp( *this );
            ++tmp;
            return tmp;
        }

        rectangle_iterator& operator +=( const size_t i ) {
            jump_forward( i );
            return *this;
        }

        rectangle_iterator& operator +( const size_t i ) {
            jump_forward( i );
            return *this;
        }

        rectangle_iterator operator --( int ) const {
            rectangle_iterator tmp( *this );
            --tmp;
            return tmp;
        }

        point operator *() const {
            return current();
        }

        point operator ->() const {
            return current();
        }

        bool operator ==( const rectangle_iterator& other ) const {
            return equal( other );
        }

        bool operator !=( const rectangle_iterator& other ) const {
            return false == equal( other );
        }

        boost::uint_fast32_t key() const {
            return geometry::calculate_key::key( m_current_point / m_max_column + m_offset.row(), m_current_point % m_max_column + m_offset.column() );
        }

    public:
        rectangle_iterator( const point& offset, int current_index, int max_column  )
            : m_current_point( current_index )
            , m_max_column( max_column )
            , m_offset( offset ) {}

    protected:
        inline void next() {
            ++m_current_point;
        }

        inline void previous() {
            ++m_current_point;
        }

        inline void jump_forward( const size_t i ) {
            m_current_point += static_cast<int>( i );
        }

        inline point current() const {
            return point( m_current_point / m_max_column, m_current_point % m_max_column ).offset( m_offset );
        }

        inline bool equal( const rectangle_iterator& other ) const {
            return other.m_current_point == m_current_point
                   && other.m_max_column == m_max_column;
        }

        int m_current_point;
        int m_max_column;
        point m_offset;
    };
}
