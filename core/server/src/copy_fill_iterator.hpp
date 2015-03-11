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
 *  Frieder Hofmann <frieder.hofmann@jedox.com>
 */


#pragma once

#include <wss/define.hpp>
#include <wss/sheet_range.hpp>
#include <wss/type.hpp>
#include <wss/position_out_of_range_exception.hpp>


class copy_fill_iterator
{
    struct auto_fill_direction {
        auto_fill_direction() : horizontal_fill( true ), vertical_fill( true ) {}
        bool horizontal_fill;
        bool vertical_fill;
    };

public:
    copy_fill_iterator( const sheet_range& source_range, const sheet_range& target_range )
        : m_source_range( source_range )
        , m_target_range( target_range )
        , m_distance( sheet_point(
                          source_range.row_count() > sheet_dimension::max_row ? sheet_dimension::max_row : source_range.row_count(),
                          source_range.column_count() > sheet_dimension::max_column ? sheet_dimension::max_column : source_range.column_count() ) )
        , m_current_distance( source_range.distance( target_range ) )
        , m_current_position( 1 ) {
        set_auto_fill_direction( source_range, target_range );
    }

    geometry::point operator *() {
        return m_current_distance;
    }

    geometry::point operator ->() {
        return m_current_distance;
    }

    const bool is_valid() {
        try {
            return m_target_range.covers( m_source_range.offset( m_current_distance ) );
        } catch ( const position_out_of_range_exception& ) {
            return false;
        }
    }

    const bool next_horizontal_would_be_valid() {
        try {
            return m_target_range.covers( m_source_range.offset( m_current_distance.offset( 0, m_distance.column() ) ) );
        } catch ( const position_out_of_range_exception& ) {
            return false;
        }
    }

    const bool next_vertical_would_be_valid() {
        try {
            return m_target_range.covers( m_source_range.offset( m_source_range.distance( m_target_range ).offset( m_distance.row() * m_current_position, 0 ) ) );
        } catch ( const position_out_of_range_exception& ) {
            return false;
        }
    }

    copy_fill_iterator& operator ++() {
        try {
            if ( m_fill_direction.horizontal_fill ) {
                if ( next_horizontal_would_be_valid() ) {
                    m_current_distance =  m_current_distance.offset( 0, m_source_range.column_count() );
                    return *this;
                }
            }
            if ( m_fill_direction.vertical_fill ) {
                if ( next_vertical_would_be_valid() ) {
                    m_current_distance =  m_source_range.distance( m_target_range ).offset( m_distance.row() * m_current_position, 0 );
                    ++m_current_position;
                    return *this;
                }
            }
        } catch ( const position_out_of_range_exception& ) {}
        m_current_distance = m_current_distance + m_distance;
        return *this;
    }

    template<class rect_T>
    inline std::list<sheet_range> whole_target_area( const rect_T& rect ) {
        std::list<sheet_range> return_val;
        const bool whole_source_range = rect == m_source_range;
        if ( whole_source_range ) {
            optional_sheet_range_type tmp_val;
            for ( ; is_valid(); ++( *this ) ) {
                if ( tmp_val ) {
                    tmp_val->enclose_into_self( rect.offset( m_current_distance ) );
                } else {
                    tmp_val.reset( rect.checked_offset( m_current_distance ) );
                }
            }
            assert( "something went wrong in copyfill_iterator! " && tmp_val );
            return_val.push_back( *tmp_val );
        } else {
            for ( ; is_valid(); ++( *this ) ) {
                return_val.push_back( rect.checked_offset( m_current_distance ) );
            }
        }
        assert( "something went wrong in copyfill_iterator! " && !return_val.empty() );
        return return_val;
    }

    inline void reset() {
        m_current_distance = m_source_range.distance( m_target_range );
        m_current_position = 1;
    }

private:

    inline void set_auto_fill_direction( const sheet_range& source_range, const sheet_range& target_range ) {

        if ( static_cast<unsigned int>( m_distance.column() ) == target_range.column_count() ) {
            m_fill_direction.horizontal_fill = false;
        }
        if ( static_cast<unsigned int>( m_distance.row() ) == target_range.row_count() ) {
            m_fill_direction.vertical_fill = false;
        }
    }

    sheet_range current() const {
        return m_source_range.offset( m_current_distance ).intersection( m_target_range );
    }

    const sheet_range& m_source_range;
    const sheet_range& m_target_range;
    geometry::point m_distance;
    geometry::point m_current_distance;
    auto_fill_direction m_fill_direction;
    unsigned int m_current_position;
};

