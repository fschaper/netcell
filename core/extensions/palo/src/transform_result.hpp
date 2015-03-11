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
 *  Frieder Hofmann <frieder.hofmann@jedox.com>
 */

#pragma once

#include <wss/define.hpp>
#include <wss/variant.hpp>
#include <wss/sheet_range.hpp>

/*!
 * \brief
 * transform palo results
 *
 * \TODO rewrite this using swap to do the transformation in place
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
class transform_result : public non_instantiable
{
public:
    static inline variant transform( const variant& input_value ) {
        if ( input_value.type() != variant::type_array ) {
            return input_value;
        }
        return transform( input_value, sheet_range( sheet_point( 0, 0 ), sheet_point( static_cast<unsigned int>( input_value.array().size() / 3 ) - 1, 2  ) ) );
    }

    static inline variant transform( const variant& input_value, const sheet_range& rect ) {
        bool vertical = true;                   // return as column
        unsigned int max_entries = 3;
        unsigned int num_entries = max_entries; // return everything
        size_t rows = rect.row_count();
        size_t cols = rect.column_count();
        size_t padding = 0;

        if ( cols > 3 && cols >= rows ) {
            vertical = false;
            num_entries = rect.row_count();
            padding = static_cast<size_t>( std::max<int>( 0, static_cast<int>( cols ) - 3 ) );
        } else {
            num_entries = rect.column_count();
            padding = static_cast<size_t>( std::max<int>( 0, static_cast<int>( cols ) - 3 ) );
        }
        if ( num_entries > max_entries ) {
            num_entries = max_entries;
        }

        const size_t rect_count = rect.count();

        variant::sparse_array_type array;
        array.resize( rect_count, variant( variant::type_empty )  );

        const variant::sparse_array_type& input_array = input_value.array();
        const std::size_t input_array_count = input_array.size();
        if ( vertical ) {

            size_t idx = 0;
            for ( size_t i = num_entries - 1; idx < rect_count && i < input_array_count; i += 3 ) {

                if ( num_entries >= 3 ) {
                    array.set( idx, input_array[i] );
                    ++idx;
                }

                array.set( idx, input_array[i - ( num_entries - 1 )] );
                ++idx;
                if ( num_entries >= 2 ) {
                    array.set( idx, input_array[i-( num_entries-2 )] );
                    ++idx;
                }
                idx += padding;
            }
        } else {
            size_t idx = 0;
            if ( num_entries >= 3 ) {
                for ( size_t i = 2; idx < rect_count && i < input_array_count; i += 3 ) {
                    array.set( idx, input_array[i] );
                    ++idx;
                }
            }
            idx = num_entries < 3 ? 0 : cols;
            for ( size_t i = 0; idx < rect_count && i < input_array_count; i += 3 ) {
                array.set( idx, input_array[i] );
                ++idx;
            }
            if ( num_entries >= 2 ) {
                idx = num_entries > 2 ? cols * 2 : cols;
                for ( size_t i = 1; idx < rect_count && i < input_array_count; i += 3 ) {
                    array.set( idx, input_array[i] );
                    ++idx;
                }
            }
        }
        return array;
    }

    static void fill( variant& to_fill, const sheet_range& rect ) {
        if ( to_fill.is_array() ) {
            to_fill.array().resize( rect.count(), variant( variant::type_empty ) );
        }
    }

    static void reorder_matrix( variant::variant_array_type& a, boost::int_fast32_t column_count ) {
        //TODO
#ifdef SKIP_FOR_NOW
        const size_t row_count = a.size() / column_count;
        //this will copy every element only once!
        for ( size_t i = 0; i < row_count; ++i ) {
            for ( size_t j = ( i == 0 ? 1 : 0 ); j < column_count; ++j ) {
                a[i* column_count+j] = a[i+j*row_count];
            }
        }
#endif // SKIP_FOR_NOW
    }
};
