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

#include "precompiled_header.hpp"
#include <wss/generic_container.hpp>
#include <wss/simple_allocator.hpp>

template < class Value_T, typename Allocator_T >
void generic_container< Value_T, Allocator_T >::clear()
{
    m_rows.clear();
    m_columns.clear();
}

template < class Value_T, typename Allocator_T >
generic_container< Value_T, Allocator_T >::rows_data_type::iterator generic_container< Value_T, Allocator_T >::get_row( const size_t row_idx )
{
    rows_data_type::iterator row = m_rows.find( row_idx );
    if ( m_rows.end() != row ) {
        return row;
    } else {
        contained_row   new_row;
        m_rows[ row_idx ] = new_row;
        return  m_rows.find( row_idx );
    }
}

template < class Value_T, typename Allocator_T >
void generic_container< Value_T, Allocator_T >::set( const sheet_point& pos, const size_t& style )
{
    get_row( pos.row() )->second.set( pos.column(), style );
}

template < class Value_T, typename Allocator_T >
void generic_container< Value_T, Allocator_T >::set( const sheet_range& area, const value_type& value )
{
    for ( int row = area.upper_left().row(); row <= area.lower_right().row(); row++ ) {
        for ( int col = area.upper_left().column(); col <= area.lower_right().column(); col++ ) {
            set( sheet_point( row, col ), allocator().register_value( value ) );
        }
    }
}

template < class Value_T, typename Allocator_T >
const typename generic_container< Value_T, Allocator_T >::value_type& generic_container< Value_T, Allocator_T >::get( const sheet_point& p ) const
{
    size_t idx = Allocator_T::NOTHING;

    rows_data_type::const_iterator row = m_rows.find( p.row() );

    if ( m_rows.end() != row ) {
        idx = row->second.get( p.column() );
        if ( !row->second.last_result() ) {
            idx = m_columns.get( p.column() );
        }
    } else {
        idx = m_columns.get( p.column() );
    }

    return const_cast< generic_container< Value_T, Allocator_T >* >( this )->allocator().at( idx );
}

template < class Value_T, typename Allocator_T >
void generic_container< Value_T, Allocator_T >::copy( const sheet_range& source_range, const sheet_range& target_range, generic_container& target, insert_shift_direction::type shift/* = insert_shift_direction::automatic*/ )
{
    const int src_row_start = source_range.upper_left().row();
    const int src_col_start = source_range.upper_left().column();
    const int tgt_row_start = target_range.upper_left().row();
    const int tgt_col_start = target_range.upper_left().column();

    const size_t src_width = source_range.column_count();
    const size_t src_height = source_range.row_count();

    const size_t tgt_width = target_range.column_count();
    const size_t tgt_height = target_range.row_count();

    bool direction_up_down = true;
    bool direction_left_right = true;

    if ( source_range.does_intersect( target_range ) && this == &target ) {
        if ( tgt_row_start > src_row_start ) {
            direction_up_down = false;
        } else if ( tgt_row_start == tgt_row_start ) {
            direction_left_right = tgt_col_start < src_col_start;
        }
    }

    //copy base
    if ( direction_up_down ) {
        for ( size_t row_idx = 0; row_idx < src_height; ++row_idx ) {
            rows_data_type::iterator src_row = m_rows.find( src_row_start + row_idx );
            if ( src_row != m_rows.end() ) {
                target.get_row( tgt_row_start + row_idx )->second.copy( src_row->second, src_col_start, tgt_col_start, src_width, direction_left_right );
            } else {
                rows_data_type::iterator dst_row = target.m_rows.find( tgt_row_start + row_idx );
                if ( target.m_rows.end() != dst_row ) {
                    size_t actual_end = tgt_col_start + src_width - 1;
                    if ( sheet_dimension::max_column < actual_end ) {
                        actual_end = sheet_dimension::max_column;
                    }
                    dst_row->second.unset( tgt_col_start, actual_end  );
                }

                dst_row = target.m_rows.end();
                for ( size_t col_idx = 0; col_idx < src_width; ++col_idx ) {
                    const size_t crt = m_columns.get( src_col_start + col_idx );
                    if ( Allocator_T::NOTHING != crt ) {
                        if ( target.m_rows.end() == dst_row ) {
                            dst_row = target.get_row( tgt_row_start + row_idx );
                            dst_row->second.set( tgt_col_start + col_idx, crt );
                        }
                    }
                }
            }
        }
    } else {
        for ( size_t row_idx = src_height; row_idx > 0; --row_idx ) {
            rows_data_type::iterator src_row = m_rows.find( src_row_start + row_idx - 1 );
            if ( src_row != m_rows.end() ) {
                target.get_row( tgt_row_start + row_idx - 1 )->second.copy( src_row->second, src_col_start, tgt_col_start, src_width, direction_left_right );
            } else {
                rows_data_type::iterator dst_row = target.m_rows.find( tgt_row_start + row_idx - 1 );
                if ( target.m_rows.end() != dst_row ) {
                    size_t actual_end = tgt_col_start + src_width - 1;
                    if ( sheet_dimension::max_column < actual_end ) {
                        actual_end = sheet_dimension::max_column;
                    }
                    dst_row->second.unset( tgt_col_start, actual_end  );
                }

                dst_row = target.m_rows.end();
                for ( size_t col_idx = 0; col_idx < src_width; ++col_idx ) {
                    const size_t crt = m_columns.get( src_col_start + col_idx );
                    if ( Allocator_T::NOTHING != crt ) {
                        if ( target.m_rows.end() == dst_row ) {
                            dst_row = target.get_row( tgt_row_start + row_idx - 1 );
                            dst_row->second.set( tgt_col_start + col_idx, crt );
                        }
                    }
                }

            }
        }
    }

    //enlarge if required
    if ( tgt_height > src_height ) {
        size_t dif = tgt_height - src_height;
        for ( size_t idx = 0; idx < dif; idx ++ ) {
            rows_data_type::iterator src_row = target.m_rows.find( tgt_row_start + idx % src_height );
            if ( src_row != target.m_rows.end() ) {
                contained_row& tgt =  target.get_row( tgt_row_start + src_height  + idx )->second;
                tgt.copy( src_row->second, tgt_col_start, tgt_col_start, src_width );
            }
        }
    }
    if ( tgt_width > src_width ) {
        for ( size_t idx = 0; idx < tgt_height; idx++ ) {
            rows_data_type::iterator src_row = target.m_rows.find( tgt_row_start + idx );
            if ( src_row != target.m_rows.end() ) {
                src_row->second.extend( tgt_col_start, src_width, tgt_width );
            }
        }
    }
}

template < class Value_T, typename Allocator_T >
void generic_container< Value_T, Allocator_T >::move( const sheet_range& source_range, const sheet_range& target_range, generic_container& target, copy_format_from::type format_from/* = copy_format_from::left_or_above*/, insert_shift_direction::type shift/* = insert_shift_direction::automatic */ )
{
    copy( source_range, source_range.coverage().checked_offset( target_range.upper_left() ), target, shift );
    // remove all regions from the source range that do not overlap with the target range
    if ( &target != this ) {
        // in case the target of the move operation is on another sheet
        // we have to remove the whole source region.
        erase( source_range );
    } else {
        // the target and the source are on the same sheet. we only delete the areas
        // of the source range that do not overlap with the moved area.
        foreach( const sheet_range & remove_rect, source_range.cut( source_range.coverage().checked_offset( target_range.upper_left() ) ) ) {
            erase( remove_rect );
        }
    }
}

template < class Value_T, typename Allocator_T >
void generic_container< Value_T, Allocator_T >::erase( const sheet_range& area, erase_shift_direction::type shift/* = erase_shift_direction::automatic */ )
{
    if ( area.upper_left().row() == 0 && area.upper_left().column() == 0 && area.lower_right().row() == ( sheet_dimension::max_row - 1 ) && area.lower_right().column() == ( sheet_dimension::max_column - 1 ) ) {
        clear();
        return;
    }
    const size_t row_start = area.upper_left().row();
    const size_t row_stop = area.lower_right().row();

    const size_t col_start = area.upper_left().column();
    const size_t col_stop = area.lower_right().column();

    if ( 0 == row_start && sheet_dimension::max_row == row_stop ) {

        for ( size_t col = col_start; col <= col_stop; ++col ) {
            if ( Allocator_T::NOTHING != m_columns.get( col ) ) {
                m_columns.unset(  col );
            }
        }

        rows_data_type::iterator crt = m_rows.begin();
        while ( crt != m_rows.end() ) {
            crt->second.unset( col_start, col_stop );
            if ( Allocator_T::NOTHING != crt->second.background() ) {
                crt->second.set( col_start, col_stop, Allocator_T::NOTHING );
            }
            if ( crt->second.empty() && Allocator_T::NOTHING == crt->second.background() ) {
                m_rows.erase( crt++ );
            } else {
                ++crt;
            }
        }

        return;
    }

    if ( 0 == col_start && sheet_dimension::max_column == col_stop ) {
        for ( size_t row = row_start; row <= row_stop; ++row ) {
            rows_data_type::iterator crt = m_rows.find( row );
            if ( crt != m_rows.end() ) {
                m_rows.erase( crt );
            }
            for ( size_t col = col_start; col <= col_stop; ++col ) {
                if ( Allocator_T::NOTHING != m_columns.get( col ) ) {
                    get_row( row )->second.set( col, Allocator_T::NOTHING );
                }
            }

        }
        return;
    }


    for ( size_t row = row_start; row <= row_stop; ++row ) {
        rows_data_type::iterator crt = m_rows.find( row );
        if ( crt != m_rows.end() ) {
            crt->second.unset( col_start, col_stop );
            if ( crt->second.empty() && Allocator_T::NOTHING == crt->second.background() ) {
                m_rows.erase( crt );
            }
        }
        for ( size_t col = col_start; col <= col_stop; ++col ) {
            if ( Allocator_T::NOTHING != m_columns.get( col ) ) {
                get_row( row )->second.set( col, Allocator_T::NOTHING );
            }
        }
    }
}

template < class Value_T, typename Allocator_T >
optional_sheet_range_type generic_container< Value_T, Allocator_T >::used_range( const bool include_fulls ) const
{
    if ( m_rows.empty() && m_columns.empty() ) {
        return optional_sheet_range_type();
    }

    size_t min_row = sheet_dimension::max_row + 1;
    size_t max_row = 0;
    size_t min_col = sheet_dimension::max_column + 1;
    size_t max_col = 0;

    for ( rows_data_type::const_iterator i = m_rows.begin(), e = m_rows.end(); i != e; ++i ) {
        if ( include_fulls && Allocator_T::NOTHING != i->second.background() ) {
            min_col = 0;
            max_col = sheet_dimension::max_column;
        }
        if ( i->second.empty() ) {
            continue;
        }
        if ( i->second.min() < min_col ) {
            min_col = i->second.min();
        }
        if ( i->second.max() > max_col ) {
            max_col = i->second.max();
        }
        size_t row = i->first;
        if ( row < min_row ) {
            min_row = row;
        }
        if ( row > max_row ) {
            max_row = row;
        }
    }

    if ( include_fulls && !m_columns.empty() ) {
        min_row = 0;
        max_row = sheet_dimension::max_row;
        if ( min_col > m_columns.min() ) {
            min_col = m_columns.min();
        }
        if ( max_col < m_columns.max() ) {
            max_col = m_columns.max();
        }
    }

    if ( sheet_dimension::max_row + 1 == min_row ) {
        min_row = 0;
    }

    if ( sheet_dimension::max_column + 1 == min_col ) {
        min_col = 0;
    }

    return optional_sheet_range_type( sheet_range( sheet_point( min_row, min_col ), sheet_point( max_row, max_col ) ) );
}

template < class Value_T, typename Allocator_T >
typename generic_container< Value_T, Allocator_T >::undo_list_type generic_container< Value_T, Allocator_T >::get_list_for_undo( const sheet_range& r ) const
{
    return undo_list_type();
}

template < class Value_T, typename Allocator_T >
void generic_container< Value_T, Allocator_T >::apply_list_for_undo( const sheet_range& r, const undo_list_type& undo_list )
{
}

template < class Value_T, typename Allocator_T >
void generic_container< Value_T, Allocator_T >::shift_columns( const size_t column, const size_t column_count )
{
    for ( rows_data_type::iterator i = m_rows.begin(), e = m_rows.end(); i != e; ++i ) {
        i->second.shift( column, column_count );
    }
    m_columns.shift( column, column_count );
}

template < class Value_T, typename Allocator_T >
void generic_container< Value_T, Allocator_T >::unshift_columns( const size_t column, const size_t column_count )
{
    for ( rows_data_type::iterator i = m_rows.begin(), e = m_rows.end(); i != e; ++i ) {
        i->second.unshift( column, column_count );
    }
    m_columns.unshift( column, column_count );
}

template < class Value_T, typename Allocator_T >
void generic_container< Value_T, Allocator_T >::shift_rows( const size_t row, const size_t row_count )
{
    rows_data_type copy;
    for ( rows_data_type::iterator i = m_rows.begin(), e = m_rows.end(); i != e; ++i ) {
        if ( i->first >= row ) {
            if ( i->first + row_count <= sheet_dimension::max_row ) {
                copy[ i->first + row_count ] = i->second;
            }
        } else {
            copy[ i->first ] = i->second;
        }
    }

    if ( row > 0 ) {
        rows_data_type::iterator root = m_rows.find( row - 1 );
        if ( m_rows.end() != root ) {
            for ( size_t i = 0; i < row_count; ++i ) {
                copy[ row + i ] = root->second;
            }
        }
    }

    m_rows.swap( copy );
}

template < class Value_T, typename Allocator_T >
void generic_container< Value_T, Allocator_T >::unshift_rows( const size_t row, const size_t row_count )
{
    rows_data_type copy;
    for ( rows_data_type::iterator i = m_rows.begin(), e = m_rows.end(); i != e; ++i ) {
        if ( i->first >= row ) {
            if ( i->first > row + row_count - 1 ) {
                copy[ i->first - row_count ] = i->second;
            }
        } else {
            copy[ i->first ] = i->second;
        }
    }

    m_rows.swap( copy );
}

template < class Value_T, typename Allocator_T >
const typename generic_container< Value_T, Allocator_T >::value_type& generic_container< Value_T, Allocator_T >::get_row_background( const size_t row ) const
{
    rows_data_type::const_iterator there = m_rows.find( row );
    if ( m_rows.end() != there ) {
        return const_cast< generic_container< Value_T, Allocator_T >* >( this )->allocator().at( there->second.background() );
    }
    static const value_type empty;
    return empty;
}

template < class Value_T, typename Allocator_T >
const typename generic_container< Value_T, Allocator_T >::value_type& generic_container< Value_T, Allocator_T >::get_col_background( const size_t col ) const
{
    return const_cast< generic_container< Value_T, Allocator_T >* >( this )->allocator().at( m_columns.get( col ) );
}

template < class Value_T, typename Allocator_T >
const size_t generic_container< Value_T, Allocator_T >::get_row_background_key( const size_t row ) const
{
    rows_data_type::const_iterator there = m_rows.find( row );
    if ( m_rows.end() != there ) {
        return there->second.background();
    }
    return Allocator_T::NOTHING;
}

template < class Value_T, typename Allocator_T >
const size_t generic_container< Value_T, Allocator_T >::get_col_background_key( const size_t col ) const
{
    return m_columns.get( col );
}

template < class Value_T, typename Allocator_T >
const sheet_point::integer_type generic_container< Value_T, Allocator_T >::min_row() const
{
    sheet_point::integer_type result = sheet_dimension::max_column + 1;
    for ( rows_data_type::const_iterator i = m_rows.begin(), e = m_rows.end(); i != e; ++i ) {
        if ( static_cast<sheet_point::integer_type>( i->first ) < result ) {
            result = i->first;
        }
    }

    return result;
}

template < class Value_T, typename Allocator_T >
const sheet_point::integer_type generic_container< Value_T, Allocator_T >::max_row() const
{
    sheet_point::integer_type result = 0;
    for ( rows_data_type::const_iterator i = m_rows.begin(), e = m_rows.end(); i != e; ++i ) {
        if ( static_cast<sheet_point::integer_type>( i->first ) > result ) {
            result = i->first;
        }
    }

    return result;
}
