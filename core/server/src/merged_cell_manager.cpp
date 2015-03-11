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
 *  Frieder Hofmann <frieder.hofmann@jedox.com>
 */

#include "precompiled_header.hpp"
#include "wss/merged_cell_manager.hpp"
#include "wss/can_not_change_merged_cell_exception.hpp"
#include "copy_fill_iterator.hpp"
#include "wss/sheet_range.hpp"
#include "wss/point.hpp"


#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <boost/foreach.hpp>
#   include <boost/thread/recursive_mutex.hpp>
#   include <vector>
#   include <list>
#endif

merged_cell_manager::merged_cell_manager()
    : m_mutex()
{}

struct merged_cells_helper
        : public non_instantiable {
    static inline void check_overlapping( const sheet_range& merge_range, std::vector<sheet_range>& overlap_list, std::list<sheet_range>& list ) {
        for ( std::list<sheet_range>::const_iterator it = list.begin(), end_it = list.end(); it != end_it; ++it ) {
            //foreach( const sheet_range & current, list ) {
            if ( merge_range.covers( *it ) ) {
                overlap_list.push_back( *it );
            } else if ( merge_range.does_intersect( *it ) ) {
                throw can_not_change_merged_cell_exception();
            }
        }
    }

    static inline void check_overlapping_and_scale_down( const sheet_range& merge_range, const geometry::point& distance, std::vector<sheet_range>& overlap_list, std::list<sheet_range>& list ) {
        for ( std::list<sheet_range>::iterator it = list.begin(), end_it = list.end(); it != end_it; ++it ) {
            //foreach( sheet_range & current, list ) {
            if ( merge_range.does_intersect( *it ) ) {
                bool delete_current = false;
                switch ( ( *it ).border_match_type( merge_range.intersection( *it ) ) ) {
                    case geometry::border_none:
                        *it = sheet_range( ( *it ).upper_left(), sheet_point( ( *it ).lower_right().offset( distance ) ) );
                        break;
                    case geometry::border_top:
                    case geometry::border_left:
                        *it = ( *it ).subtract( merge_range )->offset( distance );
                        break;
                    case geometry::border_bottom:
                    case geometry::border_right:
                        *it = *( *it ).subtract( merge_range );
                        break;
                    case geometry::border_all:
                        delete_current = true;
                        break;
                }
                if ( delete_current || ( *it ).count() == 1 ) {
                    overlap_list.push_back( *it );
                }

            }
        }
    }

    static inline void remove( const std::vector<sheet_range>& removal_list, std::list<sheet_range>& list ) {
        for ( std::vector<sheet_range>::const_iterator it = removal_list.begin(), end_it = removal_list.end(); it != end_it; ++it ) {
            //foreach( const sheet_range & current, removal_list ) {
            list.remove( *it );
        }
    }

    static inline void check_overlapping_and_scale_up( const size_t index, const geometry::point& distance, const bool is_row_operation, std::list<sheet_range>& list ) {
        for ( std::list<sheet_range>::iterator it = list.begin(), end_it = list.end(); it != end_it; ++it ) {
            //foreach( sheet_range & current, list ) {
            if ( is_row_operation ) {
                if ( ( static_cast<size_t>( ( *it ).upper_left().row() ) < index )
                        &&
                        ( static_cast<size_t>( ( *it ).lower_right().row() ) > index ) ) {
                    *it = sheet_range( ( *it ).upper_left(), sheet_point( ( *it ).lower_right().offset( distance ) ) );
                }
            } else {
                if ( ( static_cast<size_t>( ( *it ).upper_left().column() ) < index )
                        &&
                        ( static_cast<size_t>( ( *it ).lower_right().column() ) > index ) ) {
                    *it = sheet_range( ( *it ).upper_left(), sheet_point( ( *it ).lower_right().offset( distance ) ) );
                }
            }
        }
    }

    static inline void recalc_used_range( const sheet_range& r, optional_sheet_range_type& used_range ) {
        if ( used_range ) {
            used_range = ( *used_range ).enclose( r );
        } else {
            used_range.reset( r );
        }
    }

    template<class ContainerT>
    static inline void recalc_used_range( const ContainerT& ranges, optional_sheet_range_type& used_range ) {
        for ( typename ContainerT::const_iterator it = ranges.begin(), end_it = ranges.end(); it != end_it; ++it ) {
            //foreach( const sheet_range & r, ranges ) {
            recalc_used_range( *it, used_range );
        }
    }
};

void merged_cell_manager::copy( const sheet_range& source_range, const sheet_range& target_range, merged_cell_manager& other )
{
    lock_type lock_this( m_mutex );
    lock_type lock_other( other.m_mutex );

    copy_fill_iterator it( source_range, target_range );
    while ( it.is_valid() ) {
        real_copy( lock_this, lock_other, source_range, source_range.offset( *it ), other );
        ++it;
    }
}

void merged_cell_manager::real_copy( lock_type& lock, lock_type& other_lock,  const sheet_range& source_range, const sheet_range& target_range, merged_cell_manager& other )
{
    //clear the target range first
    other.internal_erase( other_lock, target_range );

    const geometry::point distance( source_range.distance( target_range ) );

    // get the list of all merged cell ranges that are part of the copy
    // procedure and add them (with the applied movement) to the copy_list
    std::vector<sheet_range> copy_list;
    for ( merged_range_list_type::const_iterator it = m_merged_ranges.begin(), end_it = m_merged_ranges.end(); it != end_it; ++it ) {
        //foreach( const sheet_range & current, m_merged_ranges ) {
        if ( source_range.covers( ( *it ).upper_left() ) ) {
            copy_list.push_back( ( *it ).offset( distance ) );
        }
    }

    // test for every element of the copy_list if the movement would be legal
    std::vector<sheet_range> removal_list;
    for ( std::vector<sheet_range>::const_iterator it = copy_list.begin(), end_it = copy_list.end(); it != end_it; ++it ) {
        //foreach( const sheet_range & current_copy_element, copy_list ) {
        merged_cells_helper::check_overlapping( *it, removal_list, other.m_merged_ranges );
    }

    merged_cells_helper::remove( removal_list, other.m_merged_ranges );
    for ( std::vector<sheet_range>::const_iterator it = copy_list.begin(), end_it = copy_list.end(); it != end_it; ++it ) {
        //foreach( const sheet_range & current_copy_element, copy_list ) {
        other.m_merged_ranges.push_back( *it );
    }

    m_used_range.reset();
}

void merged_cell_manager::move( const sheet_range& source_range, const sheet_range& target_range, merged_cell_manager& other, const bool whole_column_or_row /* = false */ )
{
    lock_type lock_this( m_mutex );
    lock_type lock_other( other.m_mutex );

    const geometry::point distance( source_range.distance( target_range ) );

    if ( whole_column_or_row && ( this == &other ) ) {
        merged_range_list_type adjusted_range;
        const bool is_row_operation = distance.row() != 0;
        if ( is_row_operation ) {
            const boost::int_fast32_t delta = distance.row();
            const boost::int_fast32_t start = delta > 0 ? source_range.upper_left().row() : target_range.upper_left().row();
            if ( delta >= 0 ) {
                for ( merged_range_list_type::const_iterator i = m_merged_ranges.begin(), e = m_merged_ranges.end(); i != e; ++i ) {
                    const int top_delta = i->upper_left().row() >= start ? delta : 0;
                    const int bottom_delta = i->lower_right().row() >= start ? delta : 0;

                    adjusted_range.push_back( sheet_range( i->upper_left().offset( top_delta, 0 ), i->lower_right().offset( bottom_delta, 0 ) ) );
                }
            } else {
                for ( merged_range_list_type::const_iterator i = m_merged_ranges.begin(), e = m_merged_ranges.end(); i != e; ++i ) {
                    const boost::int_fast32_t top_row = i->upper_left().row();
                    const boost::int_fast32_t bottom_row = i->lower_right().row();
                    if ( bottom_row < start ) {
                        //copy
                        adjusted_range.push_back( *i );
                        continue;
                    }
                    if ( top_row >= start && bottom_row <= start - delta ) {
                        //delete
                        continue;
                    }

                    //adjust
                    const boost::int_fast32_t bottom_delta = delta;
                    boost::int_fast32_t top_delta = 0;
                    if ( top_row >= start ) {
                        if ( top_row < start - delta ) {
                            top_delta = start - top_row;
                        } else {
                            top_delta = delta;
                        }
                    }
                    adjusted_range.push_back(  sheet_range( i->upper_left().offset( top_delta, 0 ), i->lower_right().offset( bottom_delta, 0 ) ) );
                }
            }
        } else {
            const int delta = distance.column();
            const boost::int_fast32_t start = delta > 0 ? source_range.upper_left().column() : target_range.upper_left().column();
            if ( delta >= 0 ) {
                for ( merged_range_list_type::const_iterator i = m_merged_ranges.begin(), e = m_merged_ranges.end(); i != e; ++i ) {
                    const int top_delta = i->upper_left().column() >= start ? delta : 0;
                    const int bottom_delta = i->lower_right().column() >= start ? delta : 0;

                    adjusted_range.push_back( sheet_range( i->upper_left().offset( 0, top_delta ), i->lower_right().offset( 0, bottom_delta ) ) );
                }
            } else {
                for ( merged_range_list_type::const_iterator i = m_merged_ranges.begin(), e = m_merged_ranges.end(); i != e; ++i ) {
                    const boost::int_fast32_t top_column = i->upper_left().column();
                    const boost::int_fast32_t bottom_column = i->lower_right().column();
                    if ( bottom_column < start ) {
                        //copy
                        adjusted_range.push_back( *i );
                        continue;
                    }
                    if ( top_column >= start && bottom_column <= start - delta ) {
                        //delete
                        continue;
                    }

                    //adjust
                    const int bottom_delta = delta;
                    int top_delta = 0;
                    if ( top_column >= start ) {
                        if ( top_column < start - delta ) {
                            top_delta = start - top_column;
                        } else {
                            top_delta = delta;
                        }
                    }
                    adjusted_range.push_back(  sheet_range( i->upper_left().offset( 0, top_delta ), i->lower_right().offset( 0, bottom_delta ) ) );
                }
            }
        }
        m_merged_ranges.swap( adjusted_range );
        return;
    }


    // get the list of all merged cell ranges that are part of the move
    // procedure and add them (with the applied movement) to the move_list
    std::vector<sheet_range> move_list;
    std::vector<sheet_range> remove_list;
    for ( merged_range_list_type::const_iterator it = m_merged_ranges.begin(), end_it = m_merged_ranges.end(); it != end_it; ++it ) {
        //foreach( const sheet_range & current, m_merged_ranges ) {
        if ( source_range.covers( ( *it ).upper_left() ) ) {
            move_list.push_back( ( *it ).offset( distance ) );
            remove_list.push_back( *it );
        }
    }
    if ( whole_column_or_row ) {
        const bool is_row_operation = distance.row() != 0;
        const bool is_insert = is_row_operation ? distance.row() > 0 : distance.column() > 0;
        if ( is_insert ) {
            const sheet_range::integer_type index = is_row_operation ? target_range.upper_left().row() : target_range.upper_left().column();
            merged_cells_helper::check_overlapping_and_scale_up( index - 1, distance, is_row_operation, m_merged_ranges );
        } else {
            const sheet_range removed_cols_or_rows = is_row_operation
                                                     ?
                                                     sheet_range(
                                                         sheet_point( target_range.upper_left().row(), 0 ), sheet_point( source_range.upper_left().row() - 1, sheet_dimension::max_column )
                                                     )
                                                     : sheet_range(
                                                         sheet_point( 0, target_range.upper_left().column() ), sheet_point( sheet_dimension::max_row, source_range.upper_left().column() - 1 )
                                                     );
            merged_cells_helper::check_overlapping_and_scale_down( removed_cols_or_rows , distance, remove_list, m_merged_ranges );
        }
    } else {

        //clear the target range first
        other.internal_erase( lock_other, target_range );
    }

    std::list<sheet_range> merged_ranges_safe_copy( m_merged_ranges );
    merged_cells_helper::remove( remove_list, m_merged_ranges );

    try {
        std::vector<sheet_range> removal_list;
        for ( std::vector<sheet_range>::const_iterator it = move_list.begin(), end_it = move_list.end(); it != end_it; ++it ) {
            //foreach( const sheet_range & current_move_element, move_list ) {
            merged_cells_helper::check_overlapping( *it, removal_list, other.m_merged_ranges );
        }

        merged_cells_helper::remove( removal_list, other.m_merged_ranges );

        for ( std::vector<sheet_range>::const_iterator it = move_list.begin(), end_it = move_list.end(); it != end_it; ++it ) {
            //foreach( const sheet_range & current_move_element, move_list ) {
            other.m_merged_ranges.push_back( *it );
        }
    } catch ( const can_not_change_merged_cell_exception& e ) {
        m_merged_ranges.swap( merged_ranges_safe_copy );
        throw e;
    }
    m_used_range.reset();
    if ( &other != this ) {
        other.m_used_range.reset();

    }
}

bool merged_cell_manager::is_covered( const sheet_point& bp, merge_cell_info& info )
{
    lock_type lock_this( m_mutex );
    for ( merged_range_list_type::const_iterator it = m_merged_ranges.begin(), end_it = m_merged_ranges.end(); it != end_it; ++it ) {
        //foreach( const sheet_range & current, m_merged_ranges ) {
        if ( ( *it ).covers( bp ) ) {
            if ( ( *it ).upper_left() == bp ) {
                info.is_origin = true;
                info.column = ( *it ).column_count();
                info.row = ( *it ).row_count();
                return true;
            } else {
                info.is_origin = false;
                info.column = ( *it ).upper_left().column();
                info.row = ( *it ).upper_left().row();
                return true;
            }
        }
    }
    return false;
}

bool merged_cell_manager::extend_point( const sheet_point& bp, sheet_point& extension )
{
    lock_type lock_this( m_mutex );
    for ( merged_range_list_type::const_iterator it = m_merged_ranges.begin(), end_it = m_merged_ranges.end(); it != end_it; ++it ) {
        //foreach( const sheet_range & current, m_merged_ranges ) {
        if ( ( *it ).covers( bp ) ) {
            extension = ( *it ).lower_right();
            return true;
        }
    }
    return false;
}

void merged_cell_manager::create( const sheet_range& merge_range )
{
    lock_type lock_this( m_mutex );
    std::vector<sheet_range> removal_list;
    merged_cells_helper::check_overlapping( merge_range, removal_list, m_merged_ranges );
    merged_cells_helper::remove( removal_list, m_merged_ranges );
    m_merged_ranges.push_back( merge_range );
    m_used_range.reset();
}

void merged_cell_manager::internal_erase( lock_type& lock, const sheet_range& merge_range )
{
    std::vector<sheet_range> removal_list;
    merged_cells_helper::check_overlapping( merge_range, removal_list, m_merged_ranges );
    merged_cells_helper::remove( removal_list, m_merged_ranges );
    m_used_range.reset();
}

void merged_cell_manager::erase( const sheet_range& merge_range )
{
    lock_type lock_this( m_mutex );
    internal_erase( lock_this, merge_range );
}

const merged_cell_manager::merged_range_list_type& merged_cell_manager::merged_range_list() const
{
    lock_type lock_this( m_mutex );
    return m_merged_ranges;
}

const optional_sheet_range_type& merged_cell_manager::used_range() const
{
    lock_type lock( m_mutex );
    if ( !m_used_range ) {
        merged_cells_helper::recalc_used_range( m_merged_ranges, m_used_range );
    }
    return m_used_range;
}

bool merged_cell_manager::does_intersect( const sheet_range& r )
{
    lock_type lock_this( m_mutex );
    for ( merged_range_list_type::const_iterator it = m_merged_ranges.begin(), end_it = m_merged_ranges.end(); it != end_it; ++it ) {
        //foreach( const sheet_range & current, m_merged_ranges ) {
        if ( ( *it ).does_intersect( r ) ) {
            return true;
        }
    }
    return false;
}

merged_cell_manager::~merged_cell_manager()
{
    lock_type lock( m_mutex );
    m_merged_ranges.clear();
    m_used_range.reset();
}
