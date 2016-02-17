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

#pragma once

#include <deque>

class contained_row
{
private:
    static const size_t NOTHING = ( size_t ) - 1;
    struct closed_interval {
        size_t left;
        size_t right;
        size_t style;

        closed_interval( const size_t point, const size_t style );
        closed_interval( const size_t left, const size_t right, const size_t style );

        inline const bool contains( const size_t point ) const {
            return left <= point && right >= point;
        }

        inline const bool is_point() const {
            return left == right;
        }
    };
    typedef std::deque< closed_interval > row_data_type;
public:
    contained_row();
    void clear();
    void set( const size_t pos, const size_t style );
    void set( const size_t start, const size_t stop, const size_t style );
    void unset( const size_t pos );
    void unset( const size_t start, const size_t stop );
    const size_t get( const size_t pos ) const;
    void copy( const contained_row& src, const size_t from, const size_t to, const size_t width, const bool left_to_right = true );
    void extend( const size_t from, const size_t from_width, const size_t to_width );
    bool empty() const;

    //undefined on empty
    inline const size_t min() const {
        if ( m_row_data.empty() ) {
            return 0;
        }
        return m_row_data.front().left;
    }

    //undefined on empty
    inline const size_t max() const {
        if ( m_row_data.empty() ) {
            return 0;
        }
        return m_row_data.back().right;
    }

    inline const size_t max_not_of( std::vector< size_t >& set ) const {
        if ( m_row_data.empty() ) {
            return NOTHING;
        }

        for ( row_data_type::const_reverse_iterator i = m_row_data.rbegin(); i != m_row_data.rend(); ++i ) {
            if ( set.end() == std::find( set.begin(), set.end(), i->style ) ) {
                return i->right;
            }
        }

        return NOTHING;
    }

    inline const size_t min_not_of(  std::vector< size_t >& set  ) const {
        if ( m_row_data.empty() ) {
            return NOTHING;
        }

        for ( row_data_type::const_iterator i = m_row_data.begin(); i != m_row_data.end(); ++i ) {
            if ( set.end() == std::find( set.begin(), set.end(), i->style ) ) {
                return i->left;
            }
        }

        return NOTHING;
    }

    void shift( const size_t column, const size_t column_count );
    void unshift( const size_t column, const size_t column_count );

    void background( const size_t value ) {
        m_background = value;
    }

    const size_t background() const {
        return m_background;
    }

    const bool last_result() const {
        return m_last_result;
    }
private:
    size_t m_background;
    row_data_type m_row_data;
    mutable bool m_last_result;
};
