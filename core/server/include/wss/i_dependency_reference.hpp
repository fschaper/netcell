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

#include <wss/sheet_range.hpp>
#include <wss/type.hpp>

/*!
 * \brief
 * interface all references to dependencies must implement.
 *
 * a dependency_reference is a reference to a dependency that might in
 * itself not as of yet exist.
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
 *
 * \see
 * reference_operation | i_dependency | dependency_manager
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class i_dependency_reference
{
public:
    enum reference_type {
        range_reference
        , named_formula_reference
    };
    virtual ~i_dependency_reference() {}
    virtual reference_type type() const = 0;
    virtual weak_worksheet_type worksheet() const = 0;
};

