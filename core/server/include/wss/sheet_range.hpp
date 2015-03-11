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

#include <wss/rectangle.hpp>
#include <wss/sheet_point.hpp>
#include <wss/define.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <algorithm> // for std::min/std::max
#endif

/*!
 * \brief
 * a range within worksheet boundaries.
 *
 * \see
 * sheet_point
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
typedef geometry::generic_rectangle<sheet_point> sheet_range;

/*!
 * \brief
 * return the reference type for the sheet_range
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
inline reference::type reference_type( const sheet_range& sr )
{
    return static_cast<reference::type>( sr.upper_left().type() | sr.lower_right().type() );
}

namespace geometry
{
    /*!
     * \brief
     * special constructor to handle references points.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    template<>
    WSS_MODULE generic_rectangle<sheet_point>::generic_rectangle( const sheet_point& p1, const sheet_point& p2 );
}

/*!
 * \brief
 * supports output with formatting specific settings.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
WSS_MODULE std::ostream& operator <<( std::ostream& os, const sheet_range& p );
