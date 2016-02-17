/**
 *  \file
 *  Copyright (C) 2006-2010 Jedox AG, Freiburg i.Br., Germany
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
 *  \Author
 *  Florian Schaper <florian.schaper@jedox.com>
 *  Frieder Hofmann <frieder.hofmann@jedox.com>
 */

#pragma once

#include <wss/define.hpp>
#include <wss/sheet_range.hpp>
#include <wss/type.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <boost/thread/recursive_mutex.hpp>
#   include <list>
#endif

/*!
 * \brief
 * manager for merged cells.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
class merged_cell_manager
{
public:
    typedef std::list<sheet_range> merged_range_list_type;

    /*!
     * \brief
     * information block
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    struct merge_cell_info {
        bool is_origin;         // true when the current cell is the "seed" cell (upper left corner)
        unsigned int row;       // covered row
        unsigned int column;    // covered column
    };

    /*!
     * \brief
     * constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    merged_cell_manager();

    ~merged_cell_manager();

    /*!
     * \brief
     * copy a range from source to target.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
    * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    void copy( const sheet_range& source_range, const sheet_range& target_range, merged_cell_manager& other );

    /*!
     * \brief
     * move a range from source to target.
     *
     * \author
    * Florian Schaper <florian.schaper@jedox.com>
    * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    void move( const sheet_range& source_range, const sheet_range& target_range, merged_cell_manager& other, const bool whole_column_or_row /* = false */ );

    /*!
     * \brief
     * return true if the passed point cuts a merged region
     *
     * \author
    * Florian Schaper <florian.schaper@jedox.com>
     */
    bool is_covered( const sheet_point& bp, merge_cell_info& info );

    /*!
     * \brief
     * tries to extend a sheetpoint to the bottom_right of a
     * possible merged area that includes it.
     *
     * \author
    * Vali Nitu <vali@yalos-solutions.com>
     */
    bool extend_point( const sheet_point& bp, sheet_point& extension );

    /*!
        * \brief
     * return true if the passed rectangle intersects one of the merged regions
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    bool does_intersect( const sheet_range& r );

    /*!
     * \brief
     * create a new merged region on the sheet.
     *
     * \author
    * Florian Schaper <florian.schaper@jedox.com>
    * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    void create( const sheet_range& merge_range );

    /*!
     * \brief
     * erase a merged region from the sheet.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void erase( const sheet_range& merge_range );

    /*!
     * \brief
     * return the range of the sheet that is actually covered by this
     * manager.
     *
     * \author
    * Florian Schaper <florian.schaper@jedox.com>
     */
    const optional_sheet_range_type& used_range() const;

    /*!
     * \brief
     * return list of merged regions.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const merged_range_list_type& merged_range_list() const;

private:
    typedef boost::recursive_mutex mutex_type;
    typedef mutex_type::scoped_lock lock_type;

    void check_overlapping( const sheet_range& merge_range, std::vector<sheet_range>& overlap_list, std::list<sheet_range>& list );

    void erase( std::vector<sheet_range>& removal_list, std::list<sheet_range>& list );
    void internal_erase( lock_type& lock, const sheet_range& merge_range );
    void real_copy( lock_type& /*lock_this*/,  lock_type& /*lock_other*/, const sheet_range& source_range, const sheet_range& target_range, merged_cell_manager& other );

private:
    mutable mutex_type m_mutex;
    merged_range_list_type m_merged_ranges;
    mutable optional_sheet_range_type m_used_range;
};
