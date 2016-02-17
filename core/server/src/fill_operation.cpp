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

#include "precompiled_header.hpp"
#include "fill_operation.hpp"

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <cmath>
#endif // HAS_PRECOMPILED_HEADER == 0

fill_operation::fill_operation( const sheet_range& source, const sheet_range& target )
    : m_source_offset( source.upper_left() )
    , m_distance( source.distance( target ) )
{
    const bool row_fill_top_to_down = m_distance.row() > 0;
    const bool column_fill_left_to_right = m_distance.column() < 0;

    m_row_count = source.row_count();
    m_column_count = source.column_count();

    m_row_multiplier = static_cast<unsigned int>( std::ceil( target.row_count() / static_cast<double>( m_row_count ) ) );
    m_column_multiplier = static_cast<unsigned int>( std::ceil( target.column_count() / static_cast<double>( m_column_count ) ) );

    if ( row_fill_top_to_down ) {
        m_start_row = m_row_count - 1;
        m_end_row = -1;
        m_row_count_direction = -1;
    } else {
        m_start_row = 0;
        m_end_row = m_row_count;
        m_row_count_direction = + 1;
    }

    if ( column_fill_left_to_right ) {
        m_start_column = 0;
        m_end_column = m_column_count;
        m_column_count_direction = + 1;
    } else {
        m_start_column = m_column_count - 1;
        m_end_column = -1;
        m_column_count_direction = -1;
    }
}


