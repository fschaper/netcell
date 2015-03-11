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

#include <wss/define.hpp>
#include <wss/type.hpp>
#include <wss/shift_direction.hpp>
#include <wss/sheet_range.hpp>
#include <wss/copy_format_from.hpp>
#include <wss/used_range.hpp>

class session;

/*!
 * \brief
 * interface for managers that have to handle copy/move
 * operations of worksheet elements.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class i_range_operation
{
public:
    /*!
     * \brief
     * destructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual ~i_range_operation() {}

    /*!
     * \brief
     * copy operation
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void copy( session& s, const sheet_range& source_range, const sheet_range& target_range, const shared_worksheet_type& target_sheet, insert_shift_direction::type shift = insert_shift_direction::automatic ) = 0;

    /*!
     * \brief
     * move operation
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void move( session& s, const sheet_range& source_range, const sheet_range& target_range, const shared_worksheet_type& target_sheet, copy_format_from::type format_from = copy_format_from::left_or_above, insert_shift_direction::type shift = insert_shift_direction::automatic ) = 0;

    /*!
     * \brief
     * erase operation
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void erase( session& s, const sheet_range& source_range, erase_shift_direction::type shift = erase_shift_direction::automatic ) = 0;

    /*!
     * \brief
     * used range
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual optional_sheet_range_type used_range() const = 0;
};
