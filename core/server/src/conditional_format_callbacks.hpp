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

#include "conditional_format_types.hpp"
#include "wss/rectangle.hpp"

using namespace geometry;

namespace cf
{
    /*!
    * \brief
    * small policy used when erasing specific ids
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */

    class with_ids_policy
    {
    protected:
        with_ids_policy( const internal_id_set_type& ids )
            : m_ids( internal_id_set_type( ids.begin(), ids.end() ) ) {}

        inline bool match_id( const internal_lookup_id_type id ) const {
            return m_ids.find( id ) != m_ids.end();
        }
    private:
        const internal_id_set_type m_ids;
    };

    /*!
    * \brief
    * optimization for only one id
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    class with_one_id_policy
    {
    protected:
        with_one_id_policy( const internal_lookup_id_type id )
            : m_id( id ) {}

        inline bool match_id( const internal_lookup_id_type id ) const {
            return m_id == id;
        }
    private:
        const internal_lookup_id_type m_id;
    };

    /*!
    * \brief
    * dummy policy used when not looking for specific ids
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    class without_ids_policy
    {
    protected:
        without_ids_policy( const lookup_id_type ) {}

        inline bool match_id( const lookup_id_type ) const {
            return true;
        }
    };

    /*!
       * \brief
       * small policy used when erasing a specific range
       *
       * \author
       * Frieder Hofmann <frieder.hofmann@jedox.com>
       */
    class with_rectangle_policy
    {
    protected:
        with_rectangle_policy( const geometry::rectangle_type& region_to_erase )
            : m_region( region_to_erase ) {}

        inline geometry::intersect_type intersection_type( const geometry::rectangle_type& r ) const {
            return m_region.intersection_type( r );
        }

    private:
        const geometry::rectangle_type m_region;
    };

    /*!
    * \brief
    * dummy policy used when not looking for a specific range
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    class without_rectangle_policy
    {
    protected:
        without_rectangle_policy() {}
        without_rectangle_policy( const geometry::rectangle_type& ) {}

        inline geometry::intersect_type intersection_type( const geometry::rectangle_type& ) const {
            return geometry::inside;
        }
    };

    struct erase_callback_defines : non_instantiable {
        typedef map_to_use<internal_lookup_id_type, geometry::rectangle_type>::type partially_erased_id_set_type;
        typedef set_to_use<internal_lookup_id_type>::type completely_erased_id_set_type;
    };


    /*!
    * \brief
    * small policy used if partially and completely erased ids have to be tracked
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    class with_id_tracking_policy
    {
    public:
        typedef erase_callback_defines::completely_erased_id_set_type completely_erased_id_set_type;
        typedef erase_callback_defines::partially_erased_id_set_type partially_erased_id_set_type;
    protected:

        with_id_tracking_policy(
            partially_erased_id_set_type& partially_erased_internal_ids
            , completely_erased_id_set_type& completely_erased_internal_ids )
            : m_partially_erased_internal_ids( partially_erased_internal_ids )
            , m_completely_erased_internal_ids( completely_erased_internal_ids ) {}

        inline void insert_partially_removed_id( const rectangle_type& r, const internal_lookup_id_type id ) const {
            insert( r, id, m_partially_erased_internal_ids );
        }

        inline void insert_completely_removed_id( const rectangle_type& r, const internal_lookup_id_type id ) const {
            insert( id, m_completely_erased_internal_ids );
        }

    private:
        template<class container_T>
        inline static void insert( const internal_lookup_id_type id, container_T& c ) {
            c.insert( id );
        }

        template<class container_T>
        inline static void insert( const rectangle_type& r, const internal_lookup_id_type id, container_T& c ) {
            c.insert( partially_erased_id_set_type::value_type( id, r )  );
        }

    private:
        mutable partially_erased_id_set_type& m_partially_erased_internal_ids;
        mutable completely_erased_id_set_type& m_completely_erased_internal_ids;
    };

    class with_id_tracking_policy_both_with_rectangle
    {
    public:
        typedef erase_callback_defines::partially_erased_id_set_type erased_id_set_type;
        typedef erased_id_set_type completely_erased_id_set_type;
        typedef erased_id_set_type partially_erased_id_set_type;
    protected:

        with_id_tracking_policy_both_with_rectangle(
            erased_id_set_type& partially_erased_internal_ids
            , erased_id_set_type& completely_erased_internal_ids )
            : m_partially_erased_internal_ids( partially_erased_internal_ids )
            , m_completely_erased_internal_ids( completely_erased_internal_ids ) {}

        inline void insert_partially_removed_id( const rectangle_type& r, const internal_lookup_id_type id ) const {
            m_partially_erased_internal_ids.insert( erased_id_set_type::value_type( id, r ) );
        }

        inline void insert_completely_removed_id( const rectangle_type& r, const internal_lookup_id_type id ) const {
            m_completely_erased_internal_ids.insert( erased_id_set_type::value_type( id, r ) );
        }

    private:
        mutable erased_id_set_type& m_partially_erased_internal_ids;
        mutable erased_id_set_type& m_completely_erased_internal_ids;
    };

    /*!
    * \brief
    * dummy policy used when no tracking is required
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    class without_id_tracking_policy
    {
    public:
        typedef erase_callback_defines::completely_erased_id_set_type completely_erased_id_set_type;
        typedef erase_callback_defines::completely_erased_id_set_type partially_erased_id_set_type;
    protected:
        without_id_tracking_policy() {}
        without_id_tracking_policy( partially_erased_id_set_type&, completely_erased_id_set_type& ) {}

        inline void insert_partially_removed_id( const rectangle_type&, const internal_lookup_id_type ) const {}

        inline void insert_completely_removed_id( const rectangle_type&, const internal_lookup_id_type ) const {}


    };

    /*!
    * \brief
    * use this if you want to actually erase nodes
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    class do_erase_policy : non_instantiable
    {
    public:
        inline static bool true_value() {
            return true;
        }
        inline static bool false_value() {
            return false;
        }
    };

    /*!
    * \brief
    * use this if you don't want to erase nodes
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    class no_erase_policy : non_instantiable
    {
    public:
        inline static bool true_value() {
            return false;
        }
        inline static bool false_value() {
            return false;
        }
    };


    /*!
    * \brief
    * erase callback that will erase given ids in a given region
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    template < class id_policy_T, class region_policy_T, class tracking_policy_T, class erase_policy_T = do_erase_policy >
    class conditional_format_erase_callback
        : protected id_policy_T
        , protected region_policy_T
        , protected tracking_policy_T
    {
    public:
        typedef typename tracking_policy_T::completely_erased_id_set_type completely_erased_id_set_type;
        typedef typename tracking_policy_T::partially_erased_id_set_type partially_erased_id_set_type;

        conditional_format_erase_callback(
            const geometry::rectangle_type& r
            , const internal_id_set_type& ids
            , partially_erased_id_set_type& partially_erased_internal_ids
            , completely_erased_id_set_type& completely_erased_internal_ids )
            : id_policy_T( ids )
            , region_policy_T( r )
            , tracking_policy_T( partially_erased_internal_ids, completely_erased_internal_ids ) {}

        conditional_format_erase_callback(
            const geometry::rectangle_type& r
            , const internal_lookup_id_type& id
            , partially_erased_id_set_type& partially_erased_internal_ids
            , completely_erased_id_set_type& completely_erased_internal_ids )
            : id_policy_T( id )
            , region_policy_T( r )
            , tracking_policy_T( partially_erased_internal_ids, completely_erased_internal_ids ) {}

    protected:
        conditional_format_erase_callback( const internal_id_set_type& ids )
            : id_policy_T( ids ) {}

    public:
        inline bool operator()( const rectangle_type& r, const internal_lookup_id_type id ) const {
            if ( id_policy_T::match_id( id ) ) {
                switch ( region_policy_T::intersection_type( r ) ) {
                    case geometry::inside: {
                        tracking_policy_T::insert_completely_removed_id( r, id );
                        return erase_policy_T::true_value();
                    }
                    case geometry::intersects: {
                        tracking_policy_T::insert_partially_removed_id( r, id );
                        return erase_policy_T::true_value();
                    }
                    case geometry::intersect_none:
                    default:
                        return erase_policy_T::false_value();
                }
            }
            return erase_policy_T::false_value();
        }
    };

    class conditional_format_erase_ids_callback
        : public conditional_format_erase_callback<with_ids_policy, without_rectangle_policy, without_id_tracking_policy>
    {
    public:
        conditional_format_erase_ids_callback( const internal_id_set_type& ids )
            : conditional_format_erase_callback<with_ids_policy, without_rectangle_policy, without_id_tracking_policy>( ids ) {}
    };

    /*!
    * \brief
    * lookup that will get all the all the rectangles, where a specific conditional format has been set
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */

    class conditional_format_affected_range_lookup_callback : protected with_one_id_policy
    {
    public:
        conditional_format_affected_range_lookup_callback( sheet_range::rectangles_type& affected_range, const internal_lookup_id_type& id )
            : with_one_id_policy( id )
            , m_affected_range( affected_range ) {}

        inline bool operator()( const rectangle_type& r, const internal_lookup_id_type id ) {
            if ( match_id( id ) ) {
                m_affected_range.push_back( r );
            }
            return true;
        }

    private:
        sheet_range::rectangles_type& m_affected_range;
    };

    /*!
    * \brief
    * lookup that will get all the ids of conditional formats for a given range
    *
    * \author
    * Frieder Hofmann <frieder.hofmann@jedox.com>
    */
    class conditional_format_id_lookup_callback
    {
    public:
        conditional_format_id_lookup_callback( internal_id_set_type& ids )
            : m_ids( ids ) {}

        inline bool operator()( const rectangle_type&, const internal_lookup_id_type id ) {
            m_ids.insert( id );
            return true;
        }

    private:
        internal_id_set_type& m_ids;
    };

    /*
        class conditional_format_move_callback
        {
        public:
            typedef std::vector<conditional_format_node*> move_node_set_type;

            conditional_format_move_callback( const geometry::rectangle_type& source, move_node_set_type& nodes_to_move )
                    : m_region( source )
                    , m_nodes_to_move( nodes_to_move ) {}

            inline bool operator()( const rectangle_type& r, const internal_lookup_id_type id ) {
                   m_nodes_to_move.push_back( r, id );
                }
                return true;
            }

        private:
            const geometry::rectangle_type m_region;
            move_node_set_type& m_nodes_to_move;
        };*/


    typedef conditional_format_erase_callback<with_ids_policy, with_rectangle_policy, with_id_tracking_policy > conditional_format_erase_ids_in_region_callback;
    typedef conditional_format_erase_callback<without_ids_policy, with_rectangle_policy, with_id_tracking_policy > conditional_format_erase_region_callback;
    typedef conditional_format_erase_callback<without_ids_policy, with_rectangle_policy, with_id_tracking_policy_both_with_rectangle > conditional_format_move_callback;
    typedef conditional_format_erase_callback<without_ids_policy, with_rectangle_policy, with_id_tracking_policy_both_with_rectangle, no_erase_policy > conditional_format_copy_callback;
}
