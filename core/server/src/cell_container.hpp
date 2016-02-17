/**
 *  \file
 *  Copyright (C) 2008 - 2009 Jedox AG, Freiburg i.Br., Germany
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
 *  <a href="http://www.jedox.com/license_worksheetserver.txt">
 *    http://www.jedox.com/license_worksheetserver.txt
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

#include "wss/sheet_point.hpp"
#include "wss/sheet_range.hpp"
#include "wss/type.hpp"

#include <cstdlib> // std::size_t
#include <map>

/*!
 * \brief
 * container for cells on a worksheet.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class cell_container
{
public:
    cell_container( worksheet& ws );

    bool has( const sheet_point& sp ) const;

    shared_dependency_type get( const sheet_point& sp ) const;

    shared_dependency_type create( const sheet_point& sp );

    void clear( const sheet_range& sr );

    void place( const shared_dependency_type& sd, const sheet_point& sp );

private:
    worksheet& m_worksheet;
    typedef std::map<std::size_t, shared_dependency_type> lookup_type;
    lookup_type m_cell_container;
};

