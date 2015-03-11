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

#include "wss/sheet_range.hpp"
#include "wss/sheet_point.hpp"

/*!
 * \brief
 * perform fill operation on two ranges in a way that prevents
 * overwriting the source with the target area.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class fill_operation
{
public:
    fill_operation( const sheet_range& source, const sheet_range& target );

    template<class operation_T>
    inline void operator()( operation_T& cb ) const {
        cb.do_initial_cleanup();
        // loop for the number of times the source fits into the target-range
        sheet_point target_offset = ( m_source_offset ).offset( m_distance );
        if ( m_distance.column() == 0 ) {
            for ( unsigned int offset_row = 0; offset_row < m_row_multiplier; ++offset_row ) {
                for ( unsigned int offset_column = 0; offset_column < m_column_multiplier; ++offset_column ) {
                    // fill the target area with the source cells
                    const unsigned int absolute_row_offset = ( offset_row * m_row_count );
                    const unsigned int absolute_column_offset = ( offset_column * m_column_count );
                    for ( long current_row = m_start_row; current_row != m_end_row ; current_row += m_row_count_direction ) {
                        for ( long current_column = m_start_column; current_column != m_end_column ; current_column += m_column_count_direction ) {
                            cb( m_source_offset.checked_offset( current_row, current_column ), target_offset.checked_offset( ( absolute_row_offset + current_row ), ( absolute_column_offset + current_column ) ) );
                        }
                    }
                }
            }
        } else {
            for ( unsigned int offset_column = 0; offset_column < m_column_multiplier; ++offset_column ) {
                for ( unsigned int offset_row = 0; offset_row < m_row_multiplier; ++offset_row ) {
                    // fill the target area with the source cells
                    const unsigned int absolute_row_offset = ( offset_row * m_row_count );
                    const unsigned int absolute_column_offset = ( offset_column * m_column_count );
                    for ( long current_column = m_start_column; current_column != m_end_column ; current_column += m_column_count_direction ) {
                        for ( long current_row = m_start_row; current_row != m_end_row ; current_row += m_row_count_direction ) {
                            cb( m_source_offset.checked_offset( current_row, current_column ), target_offset.checked_offset( ( absolute_row_offset + current_row ), ( absolute_column_offset + current_column ) ) );
                        }
                    }
                }
            }
        }
        cb.do_postponed_stuff();
    }

private:
    long m_start_row, m_end_row;
    long m_start_column, m_end_column;
    long m_column_count_direction;
    long m_row_count_direction;
    unsigned int m_row_multiplier;
    unsigned int m_column_multiplier;
    unsigned int m_row_count;
    unsigned int m_column_count;
    sheet_point m_source_offset;
    geometry::point m_distance;
};
