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

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
# include <list>
#endif // HAS_PRECOMPILED_HEADER == 0

/*!
 * \brief
 * handles the informations about arrays on a worksheet.
 *
 * \see
 * cell_manager
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class array_manager
{
public:
    /*!
     * \brief
     * registers the passed range as being covered by an array.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool add( const sheet_range& coverage );

    /*!
     * \brief
     * removes the passed range from the list of registered arrays.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool remove( const sheet_range& to_remove );

    /*!
     * \brief
     * returns true in case the area is completely covered by an array.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool contains_array( const sheet_range& coverage ) const;

    /*!
     * \brief
     * returns true even if the passed area is only partly covered by an array.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool is_partially_intersecting( const sheet_range& coverage ) const;
    bool array_move_okay( const sheet_range& source, const sheet_range& target ) const;

    /*!
     * \brief
     * return the list of regions covered by array cells on the sheet.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    rectangle_list_type list() const;

private:
    rectangle_list_type m_container;
};
