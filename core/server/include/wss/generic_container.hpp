#/**
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
#include <wss/style_set.hpp>
#include <wss/reference_counted_indexed_mapping.hpp>
#include <wss/shift_direction.hpp>
#include <wss/copy_format_from.hpp>
#include <wss/simple_allocator.hpp>
#include <wss/contained_row.hpp>

               template < typename Value_T, class Allocator_T = simple_allocator<Value_T> >
class generic_container
{
private:
typedef std::map< size_t, contained_row > rows_data_type;
private:
Allocator_T& allocator() {
        static Allocator_T return_value;
        return return_value;
    }

    void clear();
    void set( const sheet_point& pos, const size_t& style );
    rows_data_type::iterator get_row( const size_t row_idx );
public:
    typedef Value_T value_type;

    //needed for undo
    typedef reference_counted_indexed_mapping< typename value_type::key_type> key_mapping_type;
    typedef reference_counted_indexed_mapping< typename value_type::value_type> value_mapping_type;
    typedef std::pair<typename key_mapping_type::index_type, typename value_mapping_type::index_type> index_type;
    typedef std::pair<geometry::rectangle_type, index_type> kv_pair_type;
    typedef std::list<kv_pair_type> kv_pair_list_type;
    typedef kv_pair_list_type undo_list_type ;

    void set( const sheet_range& area, const value_type& value );
    const value_type& get( const sheet_point& p ) const;
    void copy( const sheet_range& source_range, const sheet_range& target_range, generic_container& target, insert_shift_direction::type shift = insert_shift_direction::automatic );
    void move( const sheet_range& source_range, const sheet_range& target_range, generic_container& target, copy_format_from::type format_from = copy_format_from::left_or_above, insert_shift_direction::type shift = insert_shift_direction::automatic );
    void erase( const sheet_range& area, erase_shift_direction::type shift = erase_shift_direction::automatic );
    void shift_columns( const size_t column, const size_t column_count );
    void unshift_columns( const size_t column, const size_t column_count );
    void shift_rows( const size_t column, const size_t column_count );
    void unshift_rows( const size_t row, const size_t row_count );
    optional_sheet_range_type used_range( const bool include_fulls = true ) const;
    const value_type& get_row_background( const size_t row ) const;
    const value_type& get_col_background( const size_t col ) const;
    const sheet_point::integer_type min_row() const;
    const sheet_point::integer_type max_row() const;

    const size_t get_row_background_key( const size_t row ) const;
    const size_t get_col_background_key( const size_t col ) const;
    /*!
    * \brief
    * returns an undo_list for a given range
    *
    * \author
    */
    undo_list_type get_list_for_undo( const sheet_range& r ) const;

    /*!
    * \brief
    * applies an undo list to a given range
    *
    * \author
    */
    void apply_list_for_undo( const sheet_range& r, const undo_list_type& undo_list );

    static void release_memory( bool purge = false ) {};
private:
    rows_data_type m_rows;

    contained_row m_columns;

};
