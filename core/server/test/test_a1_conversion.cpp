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

#include "utils.hpp"
#include <wss/a1conversion.hpp>

BOOST_AUTO_TEST_SUITE( a1_conversion_test )

/*!
 * \brief
 * conversion from A1 column notation to numeric format.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
BOOST_AUTO_TEST_CASE( from_a1_column_test )
{
    // test-set in mixed letters.
    BOOST_CHECK_EQUAL( a1conversion::from_a1::column( "z" ), 25 );
    BOOST_CHECK_EQUAL( a1conversion::from_a1::column( "aZ" ), 51 );
    BOOST_CHECK_EQUAL( a1conversion::from_a1::column( "Ba" ), 52 );
    BOOST_CHECK_EQUAL( a1conversion::from_a1::column( "aa" ), 26 );
    BOOST_CHECK_EQUAL( a1conversion::from_a1::column( "Iv" ), 255 );
    BOOST_CHECK_EQUAL( a1conversion::from_a1::column( "AaA" ), 702 );
    BOOST_CHECK_EQUAL( a1conversion::from_a1::column( "Zz" ), 701 );
    BOOST_CHECK_EQUAL( a1conversion::from_a1::column( "XFD" ), 16383 );
}

/*!
 * \brief
 * conversion from numeric format to A1 column notation .
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
BOOST_AUTO_TEST_CASE( to_a1_column_test )
{
    BOOST_CHECK_EQUAL( a1conversion::to_a1::column( 25 ), "Z" );
    BOOST_CHECK_EQUAL( a1conversion::to_a1::column( 51 ),  "AZ" );
    BOOST_CHECK_EQUAL( a1conversion::to_a1::column( 52 ),  "BA" );
    BOOST_CHECK_EQUAL( a1conversion::to_a1::column( 26 ),  "AA" );
    BOOST_CHECK_EQUAL( a1conversion::to_a1::column( 255 ),  "IV" );
    BOOST_CHECK_EQUAL( a1conversion::to_a1::column( 702 ), "AAA" );
    BOOST_CHECK_EQUAL( a1conversion::to_a1::column( 701 ),  "ZZ" );
    BOOST_CHECK_EQUAL( a1conversion::to_a1::column( 16383 ), "XFD" );
}

BOOST_AUTO_TEST_SUITE_END()

