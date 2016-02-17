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

#include "wss/type.hpp"
//#include "rectangle_container.hpp"
#include "wss/set_conditional_format.hpp"
#include "wss/get_conditional_format.hpp"
#include "border.hpp"
#include "wss/conditional_format_manager.hpp"
#include "conditional_format_types.hpp"
#include "conditional_format_counter.hpp"

#include "wss/r_tree.hpp"

#ifndef _DEBUG
#include <boost/unordered/unordered_set.hpp>
#include <boost/unordered/unordered_map.hpp>
#endif

class conditional_format_manager;

namespace cf
{

    //class conditional_format_counter;
    struct conditional_format_reference;

    /*!
     * \brief conditional_format_storage class that stores the conditional formats
     *
     * \NOTE locks/thread safety are assumed to be done on a higher level!
     *
     * \NOTE for more documentation see conditional_format_manager
     *
     * \see conditional_format_manager
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    class conditional_format_storage
        : public boost::noncopyable
    {
    public:
        static void release_memory( bool purge = false );

        typedef boost::shared_ptr<conditional_format_reference> shared_conditional_format_reference_type;

        typedef map_to_use<internal_lookup_id_type, shared_conditional_format_reference_type>::type lookup_map_type;
        typedef map_to_use<conditional_format_lookup_id_type, internal_id_set_type >::type external_id_lookup_map_type;

        typedef lookup_map_type::const_iterator const_iterator;
        typedef lookup_map_type::iterator iterator;


        typedef conditional_format_manager::conditional_format_query_type conditional_format_query_type;
        typedef cf::cf_vec_type return_vec_type;


        typedef r::tree<internal_lookup_id_type> r_container_type;

    public:
        conditional_format_storage( conditional_format_manager& m );

        ~conditional_format_storage();

        /*!
        * \brief
        * return the range(s) a conditional format is applied on
        *
        * \param id - the internal id of the conditional format
        *
        * \return a vector that contains the affected rectangles
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        sheet_range::rectangles_type get_affected_range( const internal_lookup_id_type id );

        /*!
        * \brief
        * return the range(s) a conditional format is applied on
        *
        * \param id - the external id of the conditional formats
        *
        * \return a vector that contains the affected rectangles
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        rectangle_list_type  get_external_affected_ranges( const conditional_format_lookup_id_type id );

        /*!
        * \brief
        * return the range(s) conditional formats are applied on
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        inline id_affected_range_map_type get_affected_ranges( const internal_id_set_type& ids );

        /*!
        * \brief
        * insert a conditional format
        *
        * \param s - session context
        *
        * \param cf_format - the conditional format to insert
        *
        * \param format - the format that corresponds to the conditional format
        *
        * \param ws - the worksheet
        *
        * \param position
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        void insert( session& s, const set_conditional_format& cf_format, const conditional_format_lookup_id_type next_id, const shared_worksheet_type& ws, const sheet_point& position, const bool is_relative = false );

        /*!
        * \brief
        * update a conditional format
        *
        * \param s - session context
        *
        * \param id - the external id of the conditional format to update
        *
        * \param cf_format - the conditional format
        *
        * \param format - the format that corresponds to the conditional format
        *
        * \param ws - the worksheet
        *
        * \param position
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        void update( session& s, const conditional_format_lookup_id_type id, const set_conditional_format& cf_format, const shared_worksheet_type& ws, const sheet_point& position );

        /*!
         * \brief
        * remove a conditional format
        *
        * \param id - id of the conditional format
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        void remove( const conditional_format_lookup_id_type id );

        /*!
        * \brief
        * remove conditional formats
        *
        * \param ranges - areas to remove
        *
        * \param ids - ids to remove
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        void remove( session& s, const sheet_range::rectangles_type& ranges, const internal_id_list_type& ids = internal_id_list_type() );

        /*!
        * \brief
        * remove conditional formats
        *
        * \param range - area to remove
        *
        * \param ids - ids to remove
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        void remove( session& s, const sheet_range& range, const internal_id_list_type& ids );
        void remove( session& s, const sheet_range& range, const id_list_type& external_ids );

        /*!
        * \brief
        * \see conditional_format_manager::match
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        return_vec_type match( session& s, const sheet_range& range, const conditional_format_query_type query_type );

        /*!
        * \brief
        * \see conditional_format_manager::get
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        get_conditionalformat_list_type get( session& s, const sheet_range::rectangles_type& ranges );

        /*!
        * \brief
        * \see conditional_format_manager::get
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        void get( get_conditionalformat_list_type& return_val, session& s, const bool solve_formulas = false, const sheet_range::rectangles_type& ranges = sheet_range::rectangles_type() );

        /*!
        * \brief
        * \see conditional_format_manager::move
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        void move( session& s, const sheet_range& source, const sheet_point& target, shared_worksheet_type target_sheet = shared_worksheet_type() );

        /*!
        * \brief
        * \see conditional_format_manager::copy
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        void copy( session& s, const sheet_range& source, const sheet_range& target, const shared_workbook_type& wb, shared_worksheet_type target_sheet, const bool use_copy_move = false );

        /*!
         * \brief
         * \see conditional_format_manager::move_up
         *
         * \author
         * Frieder Hofmann <frieder.hofmann@jedox.com>
         */
        void move_up( session& /* s */, const conditional_format_lookup_id_type id, const sheet_range::rectangles_type& selected_region );

        /*!
        * \brief
        * \see conditional_format_manager::move_down
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        void move_down( session& /* s */, const conditional_format_lookup_id_type id, const sheet_range::rectangles_type& selected_region );

        /*!
        * \brief
        * \see conditional_format_manager::move_down
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        void external_remove( session& s, const sheet_range& range, const id_list_type& external_ids );

        /*!
        * \brief
        * \see conditional_format_manager::move_down
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        void external_remove( session& s, const sheet_range::rectangles_type& ranges, const id_list_type& external_ids );

        inline optional_sheet_range_type used_range() const {
            const r_container_type::optional_rectangle_type optional_used_range = m_rect_container.used_range();
            return optional_used_range ? optional_sheet_range_type( *optional_used_range ) : optional_sheet_range_type();
        }

    private:
        /*!
        * \brief
        * return the ids of all the conditional formats that are set on a rectangle
        *
        * \param r - the rectangle
        *
        * \return all ids in this area as a set and a vector that contains a set of ids for every point in the rectangle
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        inline all_ids_plus_cell_ids_type sorted_ids_plus_cell_lookup( const sheet_range& r );

        /*!
        * \brief
        * return the ids of all the conditional formats that are set on a rectangle
        *
        * \param r - the rectangle
        *
        * \return a set of ids
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        inline internal_id_set_type ids( const sheet_range& r );

        /*!
        * \brief
        * return the ids of all the conditional formats that are set on multiple ranges
        * if ranges is empty, all ids are returned!
        *
        * \param ranges - the rectangles
        *
        * \return a set of ids
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        inline internal_id_set_type ids( const sheet_range::rectangles_type& ranges = sheet_range::rectangles_type() );

        /*!
        * \brief
        * convenience internally used only
        *
        * \param id - id of the conditional format to get
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        inline const shared_conditional_format_reference_type& get( const internal_lookup_id_type internal_id ) const;

        /*!
        * \brief
        * convenience internally used only
        * return the internal ids given an external id
        *
        * \param id - id of the conditional format to get
        *
        * \return set of ids
        *
        * \author
        * Frieder Hofmann <frieder.hofmann@jedox.com>
        */
        inline const internal_id_set_type& get_internal_ids( const conditional_format_lookup_id_type id ) const;

        inline bool fill_cache( session& s, const all_ids_plus_cell_ids_type& ids_vec, const conditional_format_query_type query_type, const sheet_range& range );

        inline void internal_create_clone_and_insert_for_move( session& s, const sheet_range& r, const sheet_range& old_range, const shared_conditional_format_reference_type& old_ref, const conditional_format_lookup_id_type new_id, const shared_worksheet_type& target_ws );

        inline void internal_create_clone_and_insert_for_copy_move( session& s, const sheet_range& r, const sheet_range& old_range, const shared_conditional_format_reference_type& old_ref, const conditional_format_lookup_id_type new_id, const geometry::point& distance, const sheet_range& source_range );

        inline void internal_insert( const sheet_range& r, const internal_lookup_id_type internal_id, const conditional_format_lookup_id_type external_id, const shared_conditional_format_reference_type& new_ref );

        inline void internal_remove( const internal_id_set_type& ids );
        inline void internal_remove_from_maps( const internal_lookup_id_type i );
    private:
        /*!
         * \brief
         * the rectangle container that holds all the rectangles conditional formats are applied on
         * with information about the internal ids that used in that area
         *
         * \author
         * Frieder Hofmann <frieder.hofmann@jedox.com>
         */
        r_container_type m_rect_container;

        /*!
         * \brief
         * the manager we work for, i.e. our boss!
         *
         * \author
         * Frieder Hofmann <frieder.hofmann@jedox.com>
         */

        conditional_format_manager& m_manager;
        /*!
         * \brief
         * mapping from one (externally used) external_id to a set of internally used internal_ids
         *
         * \author
         * Frieder Hofmann <frieder.hofmann@jedox.com>
         */
        external_id_lookup_map_type m_external_id_lookup;

        /*!
         * \brief
         * lookup from internal ids to the actual cf rule
         *
         * \author
         * Frieder Hofmann <frieder.hofmann@jedox.com>
         */
        lookup_map_type m_lookup_map;

        /*!
         * \brief
         * just a cache that speeds up retrieval
         *
         * \author
         * Frieder Hofmann <frieder.hofmann@jedox.com>
         */
        struct cache_struct;
        typedef boost::scoped_ptr< cache_struct > cache_type;
        mutable cache_type m_cache;

        internal_counter_type m_counter;
        boost::scoped_ptr<conditional_format_rank> m_ranks;
    };
}
