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

#include <boost/test/unit_test.hpp>

#include <wss/cyclic_point.hpp>

BOOST_AUTO_TEST_SUITE( cyclic_point_test )

/*!
 * \brief
 * cyclic point must wrap at sheet borders.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
BOOST_AUTO_TEST_CASE( cyclic_point_constructor_test )
{
    cyclic_point p1( 0, 0 );
    cyclic_point p2( sheet_dimension::max_row, sheet_dimension::max_column );
    cyclic_point p3( sheet_dimension::max_row + 1, sheet_dimension::max_column + 1 );
    cyclic_point p4( sheet_dimension::max_row + 333, sheet_dimension::max_column + 100 );
    cyclic_point p5( ( sheet_dimension::max_row * 3 ) + 3, ( sheet_dimension::max_column * 10 ) + 10 );

    BOOST_ASSERT( p1.row() == 0 && p1.column() == 0 );
    BOOST_ASSERT( p2.row() == sheet_dimension::max_row && p2.column() == sheet_dimension::max_column );
    BOOST_ASSERT( p3.row() == 0 && p3.column() == 0 );
    BOOST_ASSERT( p4.row() == 332 && p4.column() == 99 );
    BOOST_ASSERT( p5.row() == 0 && p5.column() == 0 );
}

BOOST_AUTO_TEST_SUITE_END()