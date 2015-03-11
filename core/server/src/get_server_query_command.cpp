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
#include "wss/get_server_query_command.hpp"
#include "wss/invalid_worksheet_exception.hpp"
#include "wss/bitcount.hpp"
#include "wss/worksheet.hpp"
#include "wss/range.hpp"
#include "wss/core2_compatibility.hpp"
#include "wss/conditional_format_manager.hpp"
#include "wss/merged_cell_manager.hpp"

get_server_query_command::get_server_query_command( session& s, const sheet_range& area, int query_flags )
    : base_command<i_command>::base_command( s )
    , m_area( area )
    , m_flags( query_flags )
    , m_result( variant::type_array )
{}

inline variant __unarrayize_variant( const variant& value )
{
    if ( value.is_array() ) {
        if ( value.array().size() ) {
            return __unarrayize_variant( value.array()[ 0 ] );
        } else {
            return variant();
        }
    }

    return value;

}

inline bool need_cf( const int flags )
{
    return
        ( ( flags & get_server_query_command::query_format ) == get_server_query_command::query_format )
        ||
        ( ( flags & get_server_query_command::query_formatted_value ) == get_server_query_command::query_formatted_value )
        ||
        ( ( flags & get_server_query_command::query_style ) == get_server_query_command::query_style )
        ||
        ( ( flags & get_server_query_command::query_lock ) == get_server_query_command::query_lock );
}

void get_server_query_command::execute()
{
    shared_worksheet_type current_worksheet = m_session.selected().worksheet().lock();
    if ( ! current_worksheet ) {
        throw invalid_worksheet_exception();
    }

    // size of one block of information.
    // f.ex. when value and formula are queried the block_size would be two.
    const std::size_t block_size = bitcount( m_flags );

    // for a query (formula | value) the resulting array will look like
    // { value, formula, value, formula, ... }
    // the number of value, formula pairs depending on the covered area.
    variant::sparse_array_type& result_array = m_result.array();
    m_result.array().resize( block_size * m_area.count() );

    // defines the cursor position in the result array
    variant::sparse_array_type::size_type block_offset = 0;

    cf::cf_vec_type cf_vec;
    if ( need_cf( m_flags ) ) {
        cf_vec = current_worksheet->conditional_formats().match( m_session, m_area );
    }
    if ( ( m_flags & query_value ) == query_value ) {
        const variant value_result = current_worksheet->range( m_area ).value( m_session );
        if ( value_result.is_array() ) {
            // since the result is an array fill up the result set.
            const variant::sparse_array_type::mapping_type& v = value_result.array().direct();
            for ( variant::sparse_array_type::mapping_type::const_iterator it = v.begin(), end_it = v.end(); it != end_it; ++it ) {
                //foreach( const variant::sparse_array_type::mapping_type::value_type & v, value_result.array().direct() ) {
                const size_t current_idx =  ( *it ).first * block_size + block_offset;
                result_array[ current_idx ] = ::__unarrayize_variant( ( *it ).second );
            }
        } else {
            result_array[ block_offset ] = value_result;
        }
        ++block_offset;
    }

    if ( ( m_flags & query_formula ) == query_formula ) {
        const variant value_result = current_worksheet->range( m_area ).formula( m_session );
        if ( value_result.is_array() ) {
            assert( "formula should return empty as default array return value!" && value_result.array().default_value() == variant() );

            const variant::sparse_array_type::mapping_type& v = value_result.array().direct();
            for ( variant::sparse_array_type::mapping_type::const_iterator it = v.begin(), end_it = v.end(); it != end_it; ++it ) {
                //foreach( const variant::sparse_array_type::mapping_type::value_type & v, value_result.array().direct() ) {
                const size_t current_idx =  ( *it ).first * block_size + block_offset;
                result_array[ current_idx ] = ( *it ).second;
            }
        } else {
            result_array[ block_offset ] = value_result;
        }
        ++block_offset;
    }

    if ( ( m_flags & query_style ) == query_style ) {
        // the result here will always be of array type.
        variant value_result( current_worksheet->range( m_area ).style( m_session, false, cf_vec, true ) );
        const variant::sparse_array_type::mapping_type& v = value_result.array().direct();
        for ( variant::sparse_array_type::mapping_type::const_iterator it = v.begin(), end_it = v.end(); it != end_it; ++it ) {
            //foreach( const variant::sparse_array_type::mapping_type::value_type & v, value_result.array().direct() ) {
            const size_t current_idx =  ( *it ).first * block_size + block_offset;
            result_array[ current_idx ] = ( *it ).second;
        }
        ++block_offset;
    }

    if ( ( m_flags & query_formula_where_exists ) == query_formula_where_exists ) {
        const variant value_result = current_worksheet->range( m_area ).formula( m_session, true );
        if ( value_result.is_array() ) {
            assert( "formula should return empty as default array return value!" && value_result.array().default_value() == variant() );

            const variant::sparse_array_type::mapping_type& v = value_result.array().direct();
            for ( variant::sparse_array_type::mapping_type::const_iterator it = v.begin(), end_it = v.end(); it != end_it; ++it ) {
                //foreach( const variant::sparse_array_type::mapping_type::value_type & v, value_result.array().direct() ) {
                const size_t current_idx =  ( *it ).first * block_size + block_offset;
                result_array[ current_idx ] = ( *it ).second;
            }
        } else {
            result_array[ block_offset ] = value_result;
        }
        ++block_offset;
    }

    if ( ( m_flags & query_attribute ) == query_attribute ) {
        // the result here will always be of array type.
        const variant value_result = current_worksheet->range( m_area ).attribute();
        assert( "attribute manager should return empty as default array return value!" && value_result.array().default_value() == variant() );

        const variant::sparse_array_type::mapping_type& v = value_result.array().direct();
        for ( variant::sparse_array_type::mapping_type::const_iterator it = v.begin(), end_it = v.end(); it != end_it; ++it ) {
            //foreach( const variant::sparse_array_type::mapping_type::value_type & v, value_result.array().direct() ) {
            const size_t current_idx =  ( *it ).first * block_size + block_offset;
            result_array[ current_idx ] = ( *it ).second;
        }

        ++block_offset;
    }

    if ( ( m_flags & query_dimensions ) == query_dimensions ) {
        ++block_offset;
    }

    if ( ( m_flags & query_formatted_value ) == query_formatted_value ) {
        // the result here will always be of array type.
        const variant value_result = current_worksheet->range( m_area ).formatted_value( m_session, cf_vec, true );
        assert( "format manager should return empty as default array return value!" && value_result.array().default_value() == variant() );

        const variant::sparse_array_type::mapping_type& v = value_result.array().direct();
        for ( variant::sparse_array_type::mapping_type::const_iterator it = v.begin(), end_it = v.end(); it != end_it; ++it ) {
            //foreach( const variant::sparse_array_type::mapping_type::value_type & v, value_result.array().direct() ) {
            const size_t current_idx =  ( *it ).first * block_size + block_offset;
            result_array[ current_idx ] = ( *it ).second;
        }
        ++block_offset;
    }

    if ( ( m_flags & query_format ) == query_format ) {
        // the result here will always be of array type.
        const variant value_result = current_worksheet->range( m_area ).format( m_session, cf_vec, true );
        assert( "format should return empty as default array return value!" && value_result.array().default_value() == variant() );

        variant::sparse_array_type::mapping_type v = value_result.array().direct();
        for ( variant::sparse_array_type::mapping_type::const_iterator it = v.begin(), end_it = v.end(); it != end_it; ++it ) {
            //foreach( const variant::sparse_array_type::mapping_type::value_type & v, value_result.array().direct() ) {
            const size_t current_idx =  ( *it ).first * block_size + block_offset;
#ifdef _CORE2_COMPATIBILITY_ON_FORMATS_
            if ( "@" == ( *it ).second.string() ) {
                result_array[ current_idx ] = "general;@";
            } else {
                result_array[ current_idx ] = ( *it ).second;
            }
#else
            result_array[ current_idx ] = ( *it ).second;
#endif
        }

        ++block_offset;
    }

    if ( ( m_flags & query_merge ) == query_merge ) {
        merged_cell_manager& m = current_worksheet->merge();
        variant::sparse_array_type::size_type offset = 0;
        for ( sheet_range::const_iterator it = m_area.begin(), end_it = m_area.end(); it != end_it; ++it ) {
            //foreach( const sheet_point & p, m_area ) {
            merged_cell_manager::merge_cell_info merge_info;
            if ( m.is_covered( ( *it ), merge_info ) ) {
                variant::variant_array_type dim_array = variant::variant_array_type();
                dim_array.resize( 3 );
                dim_array[0] =  variant( merge_info.is_origin );
                dim_array[1] =  variant( static_cast<double>( merge_info.row ) );
                dim_array[2] =  variant( static_cast<double>( merge_info.column ) );
                result_array[ offset + block_offset ] = dim_array;
            }
            offset += block_size;
        }
        ++block_offset;
    }

    if ( ( m_flags & query_formula_with_named_ranges ) == query_formula_with_named_ranges ) {
        ++block_offset;
    }

    if ( ( m_flags & query_lock ) == query_lock ) {
        // the result here will always be of array type.
        const unlocked_cells_vec_type result_vec = current_worksheet->range( m_area ).un_locked( m_session, cf_vec, true );
        assert( "locked cell manager should return false as default array return value!" && result_vec.default_value() == false );

        const unlocked_cells_vec_type::mapping_type& v = result_vec.direct();
        for ( unlocked_cells_vec_type::mapping_type::const_iterator it = v.begin(), end_it = v.end(); it != end_it; ++it ) {
            //foreach( const unlocked_cells_vec_type::mapping_type::value_type & v, result_vec.direct() ) {
            const size_t current_idx =  ( *it ).first * block_size + block_offset;
            result_array[ current_idx ] = !( *it ).second;
        }
        ++block_offset;
    }
}

get_server_query_command::result_type get_server_query_command::value() const
{
    return m_result;
}

DEFINE_CLONEABLE( get_server_query_command );
