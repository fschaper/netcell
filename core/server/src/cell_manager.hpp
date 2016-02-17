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

#pragma once

#include "wss/can_not_change_part_of_an_array_exception.hpp"
#include "wss/copy_format_from.hpp"
#include "wss/range_reference.hpp"
#include "wss/shift_direction.hpp"
#include "range_lock_handler.hpp"
#include "wss/content_type.hpp"
#include "wss/range_lock.hpp"
#include "wss/used_range.hpp"
#include "wss/used_range.hpp"

#include "dependency_manager.hpp"
#include "array_manager.hpp"

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
# include <boost/thread/recursive_mutex.hpp>
# include <map>
#endif // HAS_PRECOMPILED_HEADER == 0

class worksheet;

/*!
 * \brief
 * wraps cell dependency management and cell storage.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class cell_manager
    : boost::noncopyable
{
    friend class range_reference;
    friend class range_lock;
    friend class dependency_manager;
    friend class cell;
    class perform_array_move;

    typedef boost::recursive_mutex mutex_type;
    typedef mutex_type::scoped_lock lock_type;
#ifdef _DEBUG
    typedef std::map<sheet_point::unsigned_integer_type, shared_dependency_type> cell_container_type;
#else
    typedef boost::unordered_map<sheet_point::unsigned_integer_type, shared_dependency_type> cell_container_type;
#endif // _DEBUG
public:
    /*!
     * \brief
     * constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    cell_manager( worksheet& ws );

    /*!
     * \brief
     * destructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    ~cell_manager();

    /*!
     * \brief
     * returns a shared_reference which keeps track of all cells in the "position" area for the
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    shared_reference_type register_dependency( const shared_dependency_type& d, const sheet_range& position, const bool inside_nf );

    /*!
     * \brief
     * debug dump.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void dump( std::ostream& ) const;

    /*!
     * \brief
     * lock the passed range on the cell manager
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    range_lock lock( const sheet_range& coverage, lock::type type );

    /*!
     * \brief
     * used_range
     * return the used range on the worksheet.
     *
     * \param include_unrealized_precedents
     * when set to true will return the used range including dependencies to
     * cells that are as of yet unrealized.
     *
     * \return optional_sheet_range_type
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    optional_sheet_range_type used_range( bool include_unrealized_precedents = false ) const;

    /*!
     * \brief
     * perform copy operation
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void copy( session& s, const sheet_range& source_range, const sheet_range& target_range, const shared_worksheet_type& target_sheet, bool use_copy_move = false, insert_shift_direction::type shift = insert_shift_direction::automatic );

    /*!
     * \brief
     * perform a move operation
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void move( session& /* s */, const sheet_range& source_range, const sheet_range& target_range, const shared_worksheet_type& target_sheet, copy_format_from::type format_from, insert_shift_direction::type shift );

    /*!
     * \brief
     * perform a erase operation
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void erase( session& s, const sheet_range& source_range, erase_shift_direction::type shift );

    /*!
     * \brief
     * return the associated worksheet object.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    shared_worksheet_type associated_worksheet() const;

    /*!
     * \brief
     * return the list of dependents for the given range
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    dependency_set_type dependents( const sheet_range& source_range );

    /*!
     * \brief
     * return a list of array cells
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    rectangle_list_type array_list() const;

    typedef std::vector<sheet_point> existing_cell_list_type;
    existing_cell_list_type existing_cells() const;

private:
    /*!
     * \brief
     * create a new cell on the sheet
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    shared_dependency_type create( const sheet_point& position );

    /*!
     * \brief
     * create a new cell array on the sheet
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    shared_dependency_type create_array( const sheet_range& coverage );

    /*!
    * \brief
    * remove array from the sheet
    *
    * \author
    * Radu Racariu <radu@yalos-solutions.com>
    */
    void remove_array( const sheet_range& coverage );

    /*!
     * \brief
     * get the cell at the passed position
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    shared_dependency_type get( const sheet_point& position );

    /*!
     * \brief
     * erase the range on the sheet.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void erase( session& s, const sheet_range& r );

    /*!
     * \brief
     * erase the range on the sheet
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void erase( lock_type&, session& s, const sheet_range& r );

    /*!
     * \brief
     * clear the range on the sheet, all cells will be removed,
     * but no references will be invalidated
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    void clear( session& s, const sheet_range& r );

    /*!
     * \brief
     * clear the range on the sheet, all cells will be removed,
     * but no references will be invalidated
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    void clear( lock_type&, session& s, const sheet_range& r );
    /*!
    * \brief
    * release a lock on the region
    *
    * \author
    * Florian Schaper <florian.schaper@jedox.com>
    */
    void release_lock( const shared_range_lock_keeper_type& lock );

    /*!
     * \brief
     * unregister a dependency at the passed position for the passed object.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void unregister_dependency( const shared_dependency_type& sd, const sheet_range& position );

    /*!
     * \brief
     * create a new cell at the passed position.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    shared_dependency_type create( lock_type& lock, const sheet_point& position );
    shared_dependency_type create_array_master( lock_type& lock, const sheet_range& r );
    shared_dependency_type create_array_slave( lock_type& lock, const sheet_point& position, const shared_dependency_type& master_cell );

    /*!
     * \brief
     * returns true in case the passed range does intersect with an cell array
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool contains_partially_intersecting_array( const sheet_range& coverage ) const;

    bool array_move_okay( const sheet_range& source, const sheet_range& target ) const;

    /*!
     * \brief
     * does return true in case the passed range completely encloses one or more cell arrays.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool contains_array( const sheet_range& coverage ) const;

    /*!
     * \brief
     * move a cell to a new position
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void move_cell( session& s, const shared_dependency_type& sd, const sheet_point& position );

    /*!
     * \brief
     * release a cell from the passed position
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void release( const sheet_point& position );

    /*!
     * \brief
     * fill the passed dependency set with all cells that do exist in the passed range.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void fill_range( const sheet_range& sr, dependency_set_type& sdr );

    /*!
     * \brief
     * add a dependency manager node from another cell container.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void add_cell_move_node( const shared_dependency_node_type& element );

    /*!
     * \brief
     * add a named formula dependency manager node from another cell container.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void add_named_formula_move_node( const shared_dependency_node_type& element );

    shared_dependency_type move_array( shared_cell_type old_array_master, const sheet_range& source, const sheet_range& target, range_lock::waiting_for_update_position_map_type& update_position_map );

private:
    inline void internal_move_cell( lock_type& lock, const shared_worksheet_type& sw, const shared_dependency_type& sd, const sheet_point& position );

    mutable mutex_type m_mutex;
    ::worksheet& m_worksheet;
    struct cell_manager_helper;
    cell_container_type m_container;
    mutable optional_sheet_range_type m_used_range;
    dependency_manager m_dependency_manager;
    array_manager m_array_manager;
    range_lock_handler m_range_lock_handler;
};

