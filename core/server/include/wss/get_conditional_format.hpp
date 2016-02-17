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
#include <wss/rectangle.hpp>
#include <wss/variant.hpp>
#include <wss/type.hpp>
#include <wss/border_types.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <boost/cstdint.hpp>
#   include <string>
#   include <list>
#   include <set>
#endif

struct WSS_MODULE get_conditional_format {
    typedef boost::int_fast32_t lookup_id_type;
    typedef geometry::rectangles_type selected_ranges_type;
    typedef std::vector<std::string> operand_vec_type;
    typedef std::map<border_types::type, std::string> border_map_type;
    typedef boost::optional<bool> optional_bool_type;

    get_conditional_format( lookup_id_type i, const std::string& r, const std::string& f, const std::string& s, const border_map_type& b,
                            const operand_vec_type& op, const std::string& area, const optional_bool_type& locked );

    inline bool operator<( const get_conditional_format& rhs ) const {
        return id < rhs.id;
    }

    inline bool operator==( const get_conditional_format& rhs ) const {
        return id == rhs.id;
    }

    lookup_id_type id;
    std::string rule;
    std::string format;
    std::string style;
    operand_vec_type operands;
    std::string applies_to;
    optional_bool_type lock_cells;
    border_map_type borders;
};

typedef std::list< get_conditional_format > get_conditionalformat_list_type;
typedef set_to_use< get_conditional_format > conditionalformat_set_type;
