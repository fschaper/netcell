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

#include <wss/non_instantiable.hpp>
#include <wss/worksheet_element.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <set>
#endif

/*!
* \brief
* change tracker for worksheet elements
*
* \author
* Frieder Hofmann <frieder.hofmann@jedox.com>
*/

namespace bmi = boost::multi_index;
/*!
* \brief
* little helper templates
*
* \author
* Frieder Hofmann <frieder.hofmann@jedox.com>
*/
template<typename T>
struct reference_or_value {
    typedef const T type;
};

template<>
struct reference_or_value<std::string> {
    typedef const std::string& type;
};

template<>
struct reference_or_value<utf8_ci_string> {
    typedef const utf8_ci_string& type;
};

/*!
* \brief
* struct that combines a key, value and token when the last change happened
*
* \author
* Frieder Hofmann <frieder.hofmann@jedox.com>
*/
template<typename key_T, bool with_value >
struct map_value_T {
    typedef key_T k_type;
    typedef variant v_type;
    typedef typename reference_or_value<k_type>::type how_to_pass_key_type;
    typedef std::pair<k_type, v_type> key_val_type;

    map_value_T( how_to_pass_key_type k, const v_type& v )
        : key( k )
        , val ( v ) {}

    operator key_val_type() const {
        return key_val_type( key, val );
    }
    operator k_type() const {
        return key;
    }
    k_type key;
    v_type val;
};

/*!
* \brief
* specialization without value
*
* \author
* Frieder Hofmann <frieder.hofmann@jedox.com>
*/
template<typename key_T>
struct map_value_T<key_T, false> {
    typedef key_T k_type;
    typedef typename reference_or_value<k_type>::type how_to_pass_key_type;

    map_value_T( how_to_pass_key_type k )
        : key( k ) {}
    operator k_type() const {
        return key;
    }
    k_type key;
};

/*!
* \brief
* wrapper for a few typedefs and static functions
*
* \author
* Frieder Hofmann <frieder.hofmann@jedox.com>
*/
template<typename key_T, bool with_value>
struct worksheet_element_key_value_map : public non_instantiable {

    typedef key_T k_type;
    typedef typename reference_or_value<k_type>::type how_to_pass_key_type;
    typedef map_value_T<k_type, with_value> map_value_type;
    typedef worksheet_element::value_type v_type;

    struct key_tag {};

    typedef bmi::multi_index_container < map_value_type,
            bmi::indexed_by <
            bmi::ordered_unique<bmi::tag<key_tag>, bmi::member<map_value_type, k_type, &map_value_type::key> >
            >
            > container_type;

    typedef std::set<k_type> change_list_type;

    static inline typename container_type::const_iterator my_find( how_to_pass_key_type k, container_type& c ) {
        return bmi::get<key_tag>( c ).find( k );
    }
};
