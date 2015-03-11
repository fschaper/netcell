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

#include <boost/uuid/uuid.hpp>
#include <wss/a1conversion.hpp>
#include <wss/type.hpp>
#include <wss/set_conditional_format.hpp>
#include <wss/rectangle.hpp>
#include "conditional_format_rule.hpp"
#include <wss/translation_map.hpp>
#include <wss/translation_table.hpp>
#include <wss/variant_conversion_exception.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <boost/foreach.hpp>
#endif // HAS_PRECOMPILED_HEADER == 0

namespace cf
{
    class conditional_format_utils
    {

    public:
        static inline void add_free_formula( conditional_format_rule::operand_vec_type& operands_vec, session& s, const variant& v, const shared_worksheet_type& ws, const sheet_point& position, const bool is_relative = true ) {
            if ( v.type() == variant::type_string ) {
                if ( v.string().compare( 0, 1, "=" ) != 0 ) {
                    operands_vec.push_back( free_formula::create( s, "=" + v.string(), ws, position, !is_relative ) );
                } else {
                    operands_vec.push_back( free_formula::create( s, v, ws, position, !is_relative ) );
                }
            } else if ( v.is_numeric() ) {
                try {
                    //now we have to create a copy of the string
                    variant v_string( v.as_string( s.locale() ) );
                    if ( v_string.string().compare( 0, 1, "=" ) != 0 ) {
                        operands_vec.push_back( free_formula::create( s, "=" + v_string.string(), ws, position, !is_relative ) );
                    } else {
                        operands_vec.push_back( free_formula::create( s, v_string, ws, position, !is_relative ) );
                    }
                } catch ( const variant_conversion_exception& ) {}
            }
        }

        static inline shared_conditional_format_rule_type parse( session& s, const variant& operands, const std::string& rule, const shared_worksheet_type& ws, const geometry::rectangle_type& r, const sheet_point& position, const bool is_relative = true ) {
            conditional_format_rule::operand_vec_type operands_vec;
            if ( operands.type() != variant::type_empty ) {
                if ( !operands.is_array() && !operands.is_empty() ) {
                    add_free_formula( operands_vec, s, operands, ws, position, is_relative );
                } else {
                    foreach( const variant & v, operands.array() ) {
                        add_free_formula( operands_vec, s, v, ws, position, is_relative );
                    }
                }
            }
            return conditional_format_rule::create( s, rule, operands_vec, position, ws, r );
        }

        static inline std::string range_list_to_a1( const locale& l, const rectangle_list_type& ranges ) {
            const shared_translation_map_type&  tr_map = translation_table::instance()[ l ];

            std::string return_val;
            rectangle_list_type::const_iterator it( ranges.begin() ), end_it( ranges.end() );
            while ( it != end_it ) {
                return_val += range_to_a1( l, *it );
                ++it;
                if ( it != end_it ) {
                    return_val += tr_map->parameter_separator();
                }
            }
            return return_val;
        }

        static inline std::string range_to_a1( const locale& /*l*/, const sheet_point& position ) {
            return a1conversion::to_a1::from_point( position );
        }

        static inline std::string range_to_a1( const locale& /*l*/, const geometry::rectangle_type& range ) {
            return
                ( range.upper_left() != range.lower_right() )
                ?
                a1conversion::to_a1::from_point( sheet_point( range.upper_left(), reference::absolute ) )
                + ":" + a1conversion::to_a1::from_point( sheet_point( range.lower_right(), reference::absolute ) )
                : a1conversion::to_a1::from_point( sheet_point( range.upper_left(), reference::absolute ) );
        }
    };
}
