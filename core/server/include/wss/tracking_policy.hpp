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


#include <wss/generic_rectangle.hpp>
#include <wss/change_map.hpp>

namespace rectangle_container
{
    namespace policy
    {

        namespace internal
        {
            class tracking_base
            {
            public:
                change_map::change_list_type changeset( token_id_type token_id ) const {
                    return m_map.changeset( token_id );
                }

                token_id_type token_id() const {
                    return m_map.token_id();
                }

            protected:
                tracking_base() {}

                change_map& change() {
                    return m_map;
                }

            private:
                change_map m_map;
            };
        }

        template
        <
        template<class> class policy_T
        >
        struct tracking
        {
            template
            <
            class base_T
            >
            class insert_policy
                : virtual public internal::tracking_base
                , public policy_T<base_T>
            {
            public:
                typedef policy_T<base_T> base_type;

                void add( rectangle_node::auto_type add_node, rectangle_node& current_node ) {
                    if ( ! current_node.is_bounding_rect() ) {
                        change().track( current_node.rectangle() );
                    }
                    base_type::add( add_node, current_node );
                }
            };

            template
            <
            class base_T
            >
            class remove_policy
                : virtual public internal::tracking_base
                , public policy_T<base_T>
            {
            public:
                typedef policy_T<base_T> base_type;

                void remove( const typename geometry::rectangle_type& remove_rect, rectangle_node& current_node ) {
                    if ( ! current_node.is_bounding_rect() ) {
                        change().track( current_node.rectangle() );
                    }
                    base_type::remove( remove_rect, current_node );
                }
            };
        };

    }
}

