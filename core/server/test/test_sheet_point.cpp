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

#include <boost/test/unit_test.hpp>

#include <wss/sheet_point.hpp>

BOOST_AUTO_TEST_SUITE( sheet_point_test )

/*!
 * \brief
 * test sheet_point construction.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
BOOST_AUTO_TEST_CASE( sheet_point_constructor_test )
{
    {
        // test that the initialization matches the expected result.
        sheet_point p1( 0, 0 );
        sheet_point p2( 100, 100 );
        sheet_point p3( 1000, 200 );

        BOOST_ASSERT( p1.row() == 0 && p1.column() == 0 );
        BOOST_ASSERT( p2.row() == 100 && p2.column() == 100 );
        BOOST_ASSERT( p3.row() == 1000 && p3.column() == 200 );
    }

    {
        // test exceptions for border cases
        BOOST_REQUIRE_NO_THROW( sheet_point( sheet_dimension::max_row, sheet_dimension::max_column ) );
        BOOST_REQUIRE_THROW( sheet_point( sheet_dimension::max_row + 1, sheet_dimension::max_column ), position_out_of_range_exception );
        BOOST_REQUIRE_THROW( sheet_point( sheet_dimension::max_row, sheet_dimension::max_column + 1 ), position_out_of_range_exception );
    }
}

BOOST_AUTO_TEST_SUITE_END()