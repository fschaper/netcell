/**
 *  \file
 *  Copyright (C) 2006-2009 Jedox AG
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

#include <wss/sheet_dimension.hpp>
#include <wss/generic_point.hpp>

/*!
 * \brief
 * point that ensures it is withing a worksheets bounds
 * by wrapping at sheet boundaries.
 *
 * \see
 * point_base | sheet_point
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class cyclic_point
    : public geometry::generic_point<cyclic_point>
{
    typedef geometry::generic_point<cyclic_point> base_type;
public:
    cyclic_point( int row, int column )
        : base_type(
            static_cast<unsigned int>( ( ( row % sheet_dimension::max_row ) + sheet_dimension::max_row ) % sheet_dimension::max_row ),
            static_cast<unsigned int>( ( ( column % sheet_dimension::max_column ) + sheet_dimension::max_column )  % sheet_dimension::max_column )
        ) {}

    template<class other_T>
    cyclic_point( const other_T& p )
        : base_type( p ) {}

};
