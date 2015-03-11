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

#include "wss/sheet_range.hpp"
#include "wss/type.hpp"
#include "wss/range_reference.hpp"
#include "wss/r_tree.hpp"

#include "wss/dependency_node_reference.hpp"

class dependency_node;
typedef boost::shared_ptr<dependency_node> shared_dependency_node_type;

/*!
 * \brief
 * maintainer of dependency information that might in itself not as of yet exist.
 *
 * to give an example:
 * Cell A1 with the formula "=B1+C1+SUM(D1:D1000)" references
 * the Cell B1, C1 and all cells from D1 to D1000. If dependencies
 * would be connected directly all these 1001 dependencies would
 * need to be intatiated.
 * Instead of intatiating the dependency we maintain a "region of interest"
 * in the dependency_manager class where we connect the dependency_reference to.
 * If now a cell (or named formula) would be intatiated in a position that
 * is covered by one of these regions we would add the cell/named formula
 * to a set that is queries by the dependency_reference uppon call.
 * So let's say we write a value into cell D999. If D999 was not intatiated
 * before it will be created by the cell_manager. The cell_manager will
 * in turn inform the dependency_manager that a cell got created and it's position.
 * The dependency manager will then go through his list of entries and
 * add the cell dependency to all entries that are listed as being "interested" in
 * that area.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class dependency_manager
{
    friend class release_pooled_memory;
    static void release_memory( bool purge = false );
    class register_cell_callback;
    class register_array_master_cell_callback;
    class unregister_cell_callback;
    class register_dependent_callback;
    class unregister_dependency_node_callback;
    class erase_matching_or_covered_region_callback;
    class erase_matching_or_covered_region_callback_for_nfs;
    class erase_node_callback;
    class erase_moved_dependency_callback;
    class handle_named_formula_move_callback;
    class query_dependents_callback;
    class move_callback;

    struct dependency_manager_helper;

    typedef boost::mutex mutex_type;
    typedef mutex_type::scoped_lock lock_type;
    typedef r::tree<shared_dependency_node_type> container_type;
public:
    dependency_manager( worksheet& ws );

    /*!
     * \brief
     * register a region to be observed.
     *
     * \param d
     * observer that is interested in the region.
     *
     * \param region
     * region that is of interest for the observer.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    shared_dependency_node_reference_type register_dependency( const shared_dependency_type& d, const sheet_range& region, const bool inside_nf );

    /*!
     * \brief
     * erase the passed region from the dependency manager.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void unregister_dependency( const shared_dependency_type& sd, const sheet_range& region );

    /*!
     * \brief
     * for a given cell returns a list of observers (dependents)
     * and registers the passed cell as a precedent.
     *
     * \param const sheet_point & p
     * position of the new cell
     *
     * \param shared_dependency_type c
     * the precedent that needs to be includes in the reference table.
     *
     * \return locked_dependency_type
     * list of all observers (dependents) of the current cell.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    dependency_set_type update_precedents_get_dependents( const sheet_point& p, const shared_dependency_type& c );
    dependency_set_type update_precedents_get_dependents_for_array_master( const sheet_range& r, const shared_dependency_type& c );

    /*!
     * \brief
     * erase_precedent a cell from an region.
     *
     * \param const geometry::rectangle_type& r
     * position of the cell to be erased.
     *
     * \param shared_dependency_type c
     * cell to be erased.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void erase_precedent( const geometry::rectangle_type& r, const shared_dependency_type& c );
    /*!
     * \brief
     * return a list of dependents for the passed position on the sheet.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    dependency_set_type query_dependents( const sheet_point& sp );

    /*!
     * \brief
     * dump information about the current tree state to the passed output stream.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void dump( std::ostream& os ) const;

    /*!
     * \brief
     * this method modifies range information in case of a cell move operation.
     *
     * \remarks
     * ranges can extend or contract depending on the respective move operation
     * this method modifies the dependency tree according to the movement rules.
     * In case the target of the move operation is not the same sheet, nodes will
     * be passed along to the responsible target dependency manager.
     * see add_cell_move_node for further information
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void move( const sheet_range& selection_range, const sheet_point& target, cell_manager& target_manager, bool is_whole_column_or_row_operation );

    /*!
     * \brief
     * erase region from the dependency manager.
     * the operation will affect only the "cell" dependencies.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void erase( const sheet_range& selected_range );

    /*!
     * \brief
     * in case cells where moved from one worksheet/workbook to another this
     * method will be used to pass along the dependency information to the new
     * owning dependency manager.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void add_cell_move_node( const shared_dependency_node_type& element );

    /*!
     * \brief
     * in case named formulas where moved from one worksheet/workbook to another this
     * method will be used to pass along the dependency information to the new
     * owning dependency manager.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void add_named_formula_move_node( const shared_dependency_node_type& element );

    /*!
     * \brief
     * used_range
     * return the used range on the worksheet.
     *
     * \return optional_sheet_range_type
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    optional_sheet_range_type used_range() const;
private:
    mutable mutex_type m_mutex;
    container_type m_cell_dependencies;
    container_type m_named_formula_dependencies;
    worksheet& m_worksheet;
};

/*!
 * \brief
 * debug output to an ostream.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
std::ostream& operator <<( std::ostream& os, const dependency_manager& d );
