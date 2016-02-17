/**
 *  \file
 *  Copyright (container_T) 2006-2010 Jedox AG, Freiburg i.Br., Germany
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

#include "precompiled_header.hpp"
#include "wss/sheet_layout_manager.hpp"
#include "wss/algorithm.hpp"
#include "wss/layout_coord.hpp"
#include "wss/calculation_context.hpp"

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
# include <boost/iterator/filter_iterator.hpp>
# include <boost/iterator/transform_iterator.hpp>
# include <cassert>
#endif

#define UI_OFFSET 5

template
<
class container_T
>
struct indexed_container_container_list_transformer
{
    typedef container_T sparse_container_type;

    typedef typename sparse_container_type::index_type index_type;
    typedef typename sparse_container_type::value_type value_type;

    typedef boost::tuple<index_type, index_type> rect_type;

    template<class retval_container_T>
    void transform_to_list( const rect_type& from_to, const sparse_container_type& container, retval_container_T& retval_container  ) const {
        assert( "'index_type' and 'value_type' have to be of the same type"
                && sizeof( index_type ) == sizeof( value_type ) );

        // create iterator that iterates over the maps keys
        typedef boost::transform_iterator<get_first<typename sparse_container_type::defined_values_map_type>, typename sparse_container_type::const_iterator > map_key_iterator_type;
        // create iterator from the transform iterator which only iterates over elements matches by the filter
        typedef boost::filter_iterator<between_equal<index_type>, map_key_iterator_type> filter_iterator_type;

        // filter to apply against the map. defines range to match against from [start, end]
        // TODO: strange, VS8 compiles "... from_to.get<n>() ..." cleanly, but g++ doesn't?
        between_equal<index_type> predicate( boost::tuples::get<0>( from_to ), boost::tuples::get<1>( from_to ) );

        std::back_insert_iterator<retval_container_T> bit( retval_container );

        // vector which will
        filter_iterator_type it_end( predicate, map_key_iterator_type( container.end() ), map_key_iterator_type( container.end() ) );
        for ( filter_iterator_type it( predicate, map_key_iterator_type( container.begin() ), map_key_iterator_type( container.end() ) );
                it != it_end; ++it ) {
            const typename sparse_container_type::defined_values_map_type::value_type& pair( *it.base().base() );
            *bit = pair.first;
            *bit = pair.second;
        }
    }
};

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

sheet_layout_manager::sheet_layout_manager()
    : m_column_map( column_default_width )
    , m_row_map( row_default_height )
{}

void  sheet_layout_manager::worksheet( weak_worksheet_type ws )
{
    m_worksheet = ws;
    for ( sizes_type::const_iterator it = m_row_heights.begin(), end_it = m_row_heights.end(); it != end_it; ++it ) {
        //foreach( key_val_type & crt, m_row_heights ) {
        boost::shared_static_cast< layout_coord >( ( *it ).second )->worksheet( ws );
    }
    for ( sizes_type::const_iterator it = m_col_widths.begin(), end_it = m_col_widths.end(); it != end_it; ++it ) {
        //foreach( key_val_type & crt, m_col_widths ) {
        boost::shared_static_cast< layout_coord >( ( *it ).second )->worksheet( ws );
    }
}

sheet_layout_manager::integer_type sheet_layout_manager::row_height( integer_type row_index ) const
{
    return m_row_map.get( row_index );
}

sheet_layout_manager::integer_type sheet_layout_manager::column_width( integer_type column_index ) const
{
    return m_column_map.get( column_index );
}

void sheet_layout_manager::row_height( integer_type row_index, integer_type height )
{
    m_row_map.set( row_index, height );
}
void sheet_layout_manager::row_height( const line_type& from_to, integer_type height )
{
    for ( integer_type current_row = from_to.get<0>(); current_row < from_to.get<1>(); ++current_row ) {
        m_row_map.set( current_row, height );
    }
}

void sheet_layout_manager::column_width( integer_type column_index, integer_type width )
{
    m_column_map.set( column_index, width );
}
void sheet_layout_manager::column_width( const line_type& from_to, integer_type width )
{
    for ( integer_type current_col = from_to.get<0>(); current_col < from_to.get<1>(); ++current_col ) {
        m_column_map.set( current_col, width );
    }
}

void sheet_layout_manager::default_column_width( integer_type default_width )
{
    m_column_map.clear_and_set_default( default_width );
}

void sheet_layout_manager::default_row_height( integer_type default_height )
{
    m_row_map.clear_and_set_default( default_height );
}

sheet_layout_manager::integer_type sheet_layout_manager::default_column_width() const
{
    return m_column_map.get_default();
}

sheet_layout_manager::integer_type sheet_layout_manager::default_row_height() const
{
    return m_row_map.get_default();
}

sheet_layout_manager::sparse_value_range_type sheet_layout_manager::sparse_column_range( const line_type& from_to ) const
{
    sparse_indexed_vector_type retval;
    retval.reserve( m_column_map.size() * 2 );
    // get all elements from the column map that fit into the passed range and
    // insert them into 'retval' with "(column index, column width), ..."
    indexed_container_container_list_transformer<sparse_indexed_container_type> tr;
    tr.transform_to_list<sparse_indexed_vector_type>( from_to, m_column_map, retval );
    return retval;
}

sheet_layout_manager::sparse_value_range_type sheet_layout_manager::sparse_row_range( const line_type& from_to ) const
{
    sparse_indexed_vector_type retval;
    retval.reserve( m_row_map.size() * 2 );
    // get all elements from the column map that fit into the passed range and
    // insert them into 'retval' with "(row index, row height), ..."
    indexed_container_container_list_transformer<sparse_indexed_container_type> tr;
    tr.transform_to_list<sparse_indexed_vector_type>( from_to, m_row_map, retval );
    return retval;
}

sheet_layout_manager::sparse_value_range_type sheet_layout_manager::sparse_max_cell_width( session& s, const line_type& from_to )
{
    sparse_value_range_type return_value;
    return_value.reserve( from_to.get<0>() * from_to.get<1>() * 3 );
    for ( integer_type i = from_to.get<0>(); i <= from_to.get<1>(); i++ ) {
        integer_type crt = measure( s, m_col_widths, i );
        if ( 0 == crt ) {
            crt = column_width( i ) - UI_OFFSET;
        }
        return_value.push_back( i );
        return_value.push_back( crt );
        return_value.push_back( i );
    }
    return return_value;
}

sheet_layout_manager::sparse_value_range_type sheet_layout_manager::sparse_max_cell_height( session& s, const line_type& from_to )
{
    sparse_value_range_type return_value;
    return_value.reserve( from_to.get<0>() * from_to.get<1>() * 3 );
    for ( integer_type i = from_to.get<0>(); i <= from_to.get<1>(); i++ ) {
        integer_type crt = measure( s, m_row_heights, i );
        if ( 0 == crt ) {
            crt = row_height( i ) - UI_OFFSET;
        }
        return_value.push_back( i );
        return_value.push_back( crt );
        return_value.push_back( i );
    }
    return return_value;
}

void sheet_layout_manager::shift_columns( integer_type start_column, const int column_count )
{
    m_column_map.shift( start_column, column_count );
    m_hidden_column_map.shift( start_column, column_count );
    shift_holder( m_col_widths, start_column, column_count  );
}

void sheet_layout_manager::shift_rows( integer_type start_row, const int row_count )
{
    m_row_map.shift( start_row, row_count );
    m_hidden_row_map.shift( start_row, row_count );
    shift_holder( m_row_heights, start_row, row_count  );
}

void sheet_layout_manager::copy_everything_to_other( sheet_layout_manager& other ) const
{
    other.m_column_map = m_column_map;
    other.m_row_map = m_row_map;
    other.m_hidden_column_map = m_hidden_column_map;
    other.m_hidden_row_map = m_hidden_row_map;
    other.m_row_heights = m_row_heights;
    other.m_col_widths = m_col_widths;

    other.m_worksheet = m_worksheet;
}

const sheet_layout_manager::sparse_indexed_container_type& sheet_layout_manager::columns()
{
    return m_column_map;
}

const sheet_layout_manager::sparse_indexed_container_type& sheet_layout_manager::rows()
{
    return m_row_map;
}


sheet_layout_manager::integer_type sheet_layout_manager::hidden_row_height( integer_type row_index ) const
{
    return m_hidden_row_map.get( row_index );
}

sheet_layout_manager::integer_type sheet_layout_manager::hidden_column_width( integer_type column_index ) const
{
    return m_hidden_column_map.get( column_index );
}

void sheet_layout_manager::hide_row( integer_type row_index )
{
    if ( m_row_map.get( row_index ) != 0 ) {
        m_hidden_row_map.set( row_index, m_row_map.get( row_index ) );
        m_row_map.set( row_index, 0 );
    }
}
void sheet_layout_manager::unhide_row( integer_type row_index )
{
    if ( m_row_map.get( row_index ) == 0 ) {
        m_row_map.set( row_index, m_hidden_row_map.get( row_index ) );
        m_hidden_row_map.set( row_index, m_hidden_row_map.get_default() );
    }
}

void sheet_layout_manager::hide_column( integer_type column_index )
{
    if ( m_column_map.get( column_index ) != 0 ) {
        m_hidden_column_map.set( column_index, m_column_map.get( column_index ) );
        m_column_map.set( column_index, 0 );
    }
}

void sheet_layout_manager::unhide_column( integer_type column_index )
{
    if ( m_column_map.get( column_index ) == 0 ) {
        m_column_map.set( column_index, m_hidden_column_map.get( column_index ) );
        m_hidden_column_map.set( column_index, m_hidden_column_map.get_default() );
    }
}

shared_dependency_type sheet_layout_manager::get_holder( sizes_type& src, integer_type pos )
{
    for ( sizes_type::const_iterator it = src.begin(), end_it = src.end(); it != end_it; ++it ) {
        //foreach( key_val_type & crt, src ) {
        if ( ( * it ).first == pos ) {
            return ( *it ).second;
        }
    }

    shared_dependency_type  new_item;
    if ( &m_row_heights == &src ) {
        new_item = layout_coord::create( m_worksheet, true  );
    } else {
        new_item = layout_coord::create( m_worksheet, false  );
    }

    src.push_back( key_val_type( pos, new_item ) );
    return new_item;
}

shared_dependency_type sheet_layout_manager::get_row_height_holder( integer_type row_index )
{
    return get_holder( m_row_heights, row_index );
}

shared_dependency_type sheet_layout_manager::get_col_width_holder( integer_type col_index )
{
    return get_holder( m_col_widths, col_index );
}

void sheet_layout_manager::shift_holder( sizes_type& what,  integer_type start, const int count )
{
    for ( sizes_type::iterator it = what.begin(), end_it = what.end(); it != end_it; ++it ) {
        //foreach( key_val_type & crt, what ) {
        if ( ( *it ).first >= start ) {
            ( *it ).first += count;
        }
    }
}

void sheet_layout_manager::register_new_cell( shared_dependency_type& sd, const sheet_point& p )
{
    shared_dependency_type col = get_col_width_holder( p.column() );
    col->register_dependent( sd );
    sd->register_dependent( col );
    shared_dependency_type row = get_row_height_holder( p.row() );
    row->register_dependent( sd );
    sd->register_dependent( row );
}

sheet_layout_manager::integer_type sheet_layout_manager::measure( session& s, sizes_type& what, integer_type pos )
{
    for ( sizes_type::const_iterator it = what.begin(), end_it = what.end(); it != end_it; ++it ) {
        //foreach( key_val_type & crt, what ) {
        if ( ( *it ).first == pos ) {
            calculation_context cc( s );
            return ( integer_type ) ( *it ).second->value( cc ).numeric();
        }
    }
    return 0;
}

void sheet_layout_manager::invalidate_rect( sheet_range& rect )
{
    integer_type left = rect.upper_left().column();
    integer_type right = rect.lower_right().column();
    integer_type top = rect.upper_left().row();
    integer_type bottom = rect.lower_right().row();

    for ( sizes_type::const_iterator it = m_row_heights.begin(), end_it = m_row_heights.end(); it != end_it; ++it ) {
        //foreach( key_val_type & crt, m_row_heights ) {
        if ( top <= ( *it ).first && bottom >= ( *it ).first ) {
            ( *it ).second->internal_flag_dirty();
        }
    }

    for ( sizes_type::const_iterator it = m_col_widths.begin(), end_it = m_col_widths.end(); it != end_it; ++it ) {
        //foreach( key_val_type & crt, m_col_widths ) {
        if ( left <= ( *it ).first && right >= ( *it ).first ) {
            ( *it ).second->internal_flag_dirty();
        }
    }
}
