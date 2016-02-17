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

#include "wss/define.hpp"
#include "wss/type.hpp"
#include "wss/worksheet_element_storage.hpp"
#include "wss/worksheet_element.hpp"
#include "uuid_adjust.hpp"

class worksheet_element_filter
    : public non_instantiable
{
public:
    typedef worksheet_element::key_vec_type key_vec_type;
    typedef worksheet_element::key_value_vector_type key_value_vector_type;
    typedef worksheet_element::key_value_vector_vector_type key_value_vector_vector_type;
    typedef std::vector< std::string > id_vec_type;

    static inline void get_values_filter(
        session& s,
        key_value_vector_vector_type& return_vec,
        const worksheet_element_storage::insertion_order_list_type& ws_elems,
        const key_vec_type& keys,
        const key_value_vector_type& vals
    ) {
        key_value_vector_vector_type tmp_vec;
        tmp_vec.reserve( ws_elems.size() );
        typedef worksheet_element_storage::insertion_order_list_type::const_iterator const_iterator;
        const_iterator it( ws_elems.begin() ), end_it( ws_elems.end() );
        for ( ; it != end_it; ++it ) {
            key_value_vector_type tmp( ( *it )->properties( s, keys, vals ) );
            if ( !tmp.empty() ) {
                return_vec.push_back( tmp );
            }
        }
    }

    static inline void get_values_filter(
        session& s,
        key_value_vector_vector_type& return_vec,
        const worksheet_element_storage::worksheet_element_vec_type& ws_elems,
        const id_vec_type& elem_id_vec,
        const key_vec_type& keys,
        const key_value_vector_type& vals
    ) {
        key_value_vector_vector_type tmp_vec;
        tmp_vec.reserve( ws_elems.size() );
        typedef worksheet_element_storage::worksheet_element_vec_type::const_iterator const_iterator;
        const_iterator end_it( ws_elems.end() );
        for ( id_vec_type::const_iterator id_it = elem_id_vec.begin(), id_end = elem_id_vec.end(); id_end != id_it; ++id_it ) {
            const_iterator it( ws_elems.find( uuid_adjust::cast_uuid( *id_it ) ) );
            if ( it != end_it ) {
                key_value_vector_type tmp( it->second->properties( s, keys, vals ) );
                return_vec.push_back( tmp );
            } else {
                return_vec.push_back( key_value_vector_type() );
            }
        }
    }

    static inline void get_values(
        session& s,
        key_value_vector_vector_type& return_vec,
        const worksheet_element_storage::insertion_order_list_type& ws_elems
    ) {
        get_values_filter( s, return_vec, ws_elems, key_vec_type(), key_value_vector_type() );
    }
};
