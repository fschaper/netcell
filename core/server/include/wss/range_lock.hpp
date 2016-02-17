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

#include <wss/type.hpp>
#include <wss/lock.hpp>
#include <wss/sheet_range.hpp>
#include <wss/lock_once.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <boost/noncopyable.hpp>
#endif

class cell_manager;

/*!
 * \brief
 * allows read/write access (depending on lock::type) to a worksheets cells.
 *
 * provide abstract locking of regions on a worksheet.
 *
 * some operations like cell movement or copy operate on regions rather than individual
 * cells. The range lock provides an abstract lock to all cells that will be affected
 * by such an operation so no two operations can interfere with the same range at any
 * one time.
 *
 * \remarks
 * do not hold more than one range_lock at a time!
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class range_lock
    : boost::noncopyable
{
    class perform_copy;
    class perform_move;

    friend class cell_manager;
    friend class perform_copy;
    friend class perform_move;
public:
    typedef std::list< std::pair<shared_dependency_type, sheet_point> > waiting_for_update_position_map_type;
    /*!
     * \brief
     * copy constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    range_lock( const range_lock& other );

    /*!
     * \brief
     * destructor.
     *
     * will release the lock on the region.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    ~range_lock();

    /*!
     * \brief
     * returns the area covered by the lock.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const sheet_range& coverage() const;

    /*!
     * \brief
     * returns the type of lock that is currently being held.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    lock::type type() const;

    /*!
     * \brief
     * creates a cell at the given position
     *
     * the position has to be inside the area covered by the lock
     * and the lock has to have exclusive access to the area.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    shared_dependency_type create( const sheet_point& position );

    /*!
     * \brief
     * creates a cell array that covers the whole area of the locked range.
     *
     * the lock has to have exclusive access to the range.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    shared_dependency_type create_array();

    /*!
    * \brief
    * removes array that covers the whole area of the locked range.
    *
    * the lock has to have exclusive access to the range.
    *
    * \author
    * Radu Racariu <radu@yalos-solutions.com>
    */
    void remove_array( const sheet_range& position );

    /*!
     * \brief
     * returns a shared pointer to the dependency covering that position
     * on the worksheet.
     *
     * in case the position is empty will return an empty reference. always
     * check for "empty".
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    shared_dependency_type get( const sheet_point& position );

    /*!
     * \brief
     * removes all cells from the covered area.
     *
     * the lock has to be in exclusive mode for this operation to be performed.
     * otherwise an exception will be thrown.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void erase( session& s );

    /*!
     * \brief
     * clears cells in this range, all cells will be removed, but no references will be invalidated
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    void clear( session& s );

    /*!
     * \brief
     * returns true in case the range_lock overlaps only partially with a cell array.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool contains_partially_intersecting_array() const;

    bool array_move_okay( const sheet_range& target_range ) const;

    /*!
     * \brief
     * will return true in case the range_lock completely encloses
     * an array of cells.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool contains_array() const;

    /*!
     * \brief
     * returns all dependents registered for the covered region of cells.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    dependency_set_type dependents();

private:
    range_lock( weak_worksheet_type ws, const shared_range_lock_keeper_type& lock );

    /*!
     * \brief
     * move cells to the target position.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void move( session& s, range_lock& target );

    /*!
     * \brief
     * copy cells to the target position.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void copy( session& s, range_lock& target, bool target_is_clone_sheet, bool use_copy_move );

    void erase( session& s, const sheet_point& position );
    void erase( session& s, const sheet_range& position );
    void clear( session& s, const sheet_point& position );
    void clear( session& s, const sheet_range& position );

    /*!
     * \brief
     * create a cell array at the specified position.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    shared_dependency_type create_array( const sheet_range& position );

    /*!
     * \brief
     * move a cell to the specified target position.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void move_cell( session& s, const shared_dependency_type& sd, const sheet_point& position );

    shared_dependency_type move_array( shared_cell_type old_array_master, const sheet_range& source, const sheet_range& target, waiting_for_update_position_map_type& update_position_map );

private:
    lock_once<worksheet> m_manager;
    shared_range_lock_keeper_type m_range_lock;
};
