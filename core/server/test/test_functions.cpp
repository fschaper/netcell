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
 *  Radu Ialovoi <ialovoi@yahoo.com>
 */

#include "utils.hpp"

#include <boost/test/unit_test.hpp>
#include <boost/assign.hpp>

#include <wss/session_handler.hpp>
#include <wss/session.hpp>
#include <wss/command.hpp>
#include <wss/server.hpp>
#include <wss/type.hpp>
#include <wss/execute_fetch.hpp>

struct functions_fixture {
    functions_fixture() {
        server::instance().startup();
        active_session = server::instance().session_handler().create( locale::create( "en-US" ) );

        create_application_command( *active_session, "my application" ).execute();
        select_application_command( *active_session, "my application" ).execute();
        create_workbook_command( *active_session, "my_workbook_1" ).execute();
        select_workbook_command( *active_session, "my_workbook_1" ).execute();
        create_worksheet_command( *active_session, "my_worksheet_1" ).execute();
        select_worksheet_command( *active_session, "my_worksheet_1" ).execute();
    }

    ~functions_fixture() {
        try {
            server::instance().shutdown();
        } catch ( const std::exception& ) {
            assert( !"this may never throw" );
        }
    }

    locked_session active_session;
};

BOOST_FIXTURE_TEST_SUITE( functions_test, functions_fixture );

/*!
 * \brief
 *
 * \author
 * Radu Ialovoi <ialovoi@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_vlookup_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) , variant( 0.457 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) , variant( 0.525 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) , variant( 0.616 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) , variant( 0.675 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) , variant( 0.746 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) , variant( 0.835 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) , variant( 0.946 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) , variant( 1.09 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 8, 0 ) , variant( 1.29 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 0, 1 ) , variant( false ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 1 ) , variant( 0.525 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 1 ) , variant( false ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 1 ) , variant( 0.675 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 1 ) , variant( 0.746 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 1 ) , variant( false ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 6, 1 ) , variant( 0.946 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 7, 1 ) , variant( true ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 8, 1 ) , variant( true ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 0, 2 ) , variant( "foo" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 2 ) , variant( 0.525 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 2 ) , variant( "bar" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 2 ) , variant( 0.675 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 2 ) , variant( 0.746 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 2 ) , variant( false ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 6, 2 ) , variant( 0.946 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 7, 2 ) , variant( "foobar" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 8, 2 ) , variant( true ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 0, 3 ) , variant( "line 0" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 3  ) , variant( "line 1" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 3  ) , variant( "line 2" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 3  ) , variant( "line 3" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 3  ) , variant( "line 4" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 3  ) , variant( "line 5" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 6, 3  ) , variant( "line 6" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 7, 3  ) , variant( "line 7" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 8, 3  ) , variant( "line 8" ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 0, 4 ) , "=VLOOKUP(1; A1:D9; 4)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 0, 4 )  ) );

    chain.add( set_value_command( *active_session, sheet_point( 1, 4 ) , "=VLOOKUP(.7;A1:D9;4;FALSE)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 4 )  ) );

    chain.add( set_value_command( *active_session, sheet_point( 2, 4 ) , "=VLOOKUP(2;A1:D9;4;TRUE)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 4 )  ) );

    chain.add( set_value_command( *active_session, sheet_point( 3, 4 ) , "=VLOOKUP(0.835;A1:D9;4;TRUE)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 4 )  ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 4 ) , "=VLOOKUP(1; B1:D9; 4)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 4 )  ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 4 ) , "=VLOOKUP(1; B1:D9; 3)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 4 )  ) );

    chain.add( set_value_command( *active_session, sheet_point( 6, 4 ) , "=VLOOKUP(TRUE; B1:D9; 3)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 4 )  ) );

    chain.add( set_value_command( *active_session, sheet_point( 8, 4 ) , "=VLOOKUP(0.1; B1:D9; 3)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 8, 4 )  ) );

    chain.add( set_value_command( *active_session, sheet_point( 9, 4 ) , "=VLOOKUP(\"fooBAr\"; C1:D9; 2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 9, 4 )  ) );

    chain.add( set_value_command( *active_session, sheet_point( 10, 4 ) , "=VLOOKUP(\"BAr\"; C1:D9; 2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 10, 4 )  ) );

    chain.add( set_value_command( *active_session, sheet_point( 11, 4 ) , "=VLOOKUP(\"BAr123\"; C1:D9; 2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 11, 4 )  ) );

    chain.add( set_value_command( *active_session, sheet_point( 12, 4 ) , "=VLOOKUP(\"BAr123\"; C1:D9; 2; FALSE)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 12, 4 )  ) );

    chain.add( set_value_command( *active_session, sheet_point( 13, 4 ) , "=VLOOKUP(\"nothere\"; C1:D9; 2; FALSE)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 13, 4 )  ) );

    chain.add( set_value_command( *active_session, sheet_point( 14, 4 ) , "=VLOOKUP(\"BAr123\"; C1:D10; 2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 14, 4 )  ) );

    chain.add( set_value_command( *active_session, sheet_point( 15, 4 ) , "=VLOOKUP(\"BAr123\"; C1:D10; 3)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 15, 4 )  ) );

    chain.execute();
    TYPED_CHECK_EQUAL( get_value_command, chain[37], variant( "line 6" ) );
    TYPED_CHECK_EQUAL( get_value_command, chain[39], variant( variant::error_n_a ) );
    TYPED_CHECK_EQUAL( get_value_command, chain[41], variant( "line 8" ) );
    TYPED_CHECK_EQUAL( get_value_command, chain[43], variant( "line 5" ) );
    TYPED_CHECK_EQUAL( get_value_command, chain[45], variant( variant::error_ref ) );
    TYPED_CHECK_EQUAL( get_value_command, chain[47], variant( "line 6" ) );
    TYPED_CHECK_EQUAL( get_value_command, chain[49], variant( "line 8" ) );
    TYPED_CHECK_EQUAL( get_value_command, chain[51], variant( variant::error_n_a ) );
    TYPED_CHECK_EQUAL( get_value_command, chain[53], variant( "line 7" ) );
    TYPED_CHECK_EQUAL( get_value_command, chain[55], variant( "line 2" ) );
    TYPED_CHECK_EQUAL( get_value_command, chain[57], variant( "line 2" ) );
    TYPED_CHECK_EQUAL( get_value_command, chain[59], variant( variant::error_n_a ) );
    TYPED_CHECK_EQUAL( get_value_command, chain[61], variant( variant::error_n_a ) );
    TYPED_CHECK_EQUAL( get_value_command, chain[63], variant( "line 2" ) );
    TYPED_CHECK_EQUAL( get_value_command, chain[65], variant( variant::error_ref ) );
}

/*!
 * \brief
 *
 * \author
 * Radu Ialovoi <ialovoi@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_hlookup_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) , variant( 0.457 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 1 ) , variant( 0.525 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 2 ) , variant( 0.616 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 3 ) , variant( 0.675 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 4 ) , variant( 0.746 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 5 ) , variant( 0.835 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 6 ) , variant( 0.946 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 7 ) , variant( 1.09 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 8 ) , variant( 1.29 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) , variant( false ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 1 ) , variant( 0.525 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 2 ) , variant( false ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 3 ) , variant( 0.675 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 4 ) , variant( 0.746 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 5 ) , variant( false ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 6 ) , variant( 0.946 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 7 ) , variant( true ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 8 ) , variant( true ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) , variant( "foo" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 1 ) , variant( 0.525 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 2 ) , variant( "bar" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 3 ) , variant( 0.675 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 4 ) , variant( 0.746 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 5 ) , variant( false ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 6 ) , variant( 0.946 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 7 ) , variant( "foobar" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 8 ) , variant( true ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) , variant( "line 0" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 1  ) , variant( "line 1" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 2  ) , variant( "line 2" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 3  ) , variant( "line 3" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 4  ) , variant( "line 4" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 5  ) , variant( "line 5" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 6  ) , variant( "line 6" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 7  ) , variant( "line 7" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 8  ) , variant( "line 8" ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 0, 24 ) , "=HLOOKUP(1; A1:I4; 4)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 0, 24 )  ) );

    chain.add( set_value_command( *active_session, sheet_point( 1, 24 ) , "=HLOOKUP(.7;A1:I4;4;FALSE)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 24 )  ) );

    chain.add( set_value_command( *active_session, sheet_point( 2, 24 ) , "=HLOOKUP(2;A1:I4;4;TRUE)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 24 )  ) );

    chain.add( set_value_command( *active_session, sheet_point( 3, 24 ) , "=HLOOKUP(0.835;A1:I4;4;TRUE)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 24 )  ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 24 ) , "=HLOOKUP(1; A2:I4; 4)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 24 )  ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 24 ) , "=HLOOKUP(1; A2:I4; 3)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 24 )  ) );

    chain.add( set_value_command( *active_session, sheet_point( 6, 24 ) , "=HLOOKUP(TRUE; A2:I4; 3)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 24 )  ) );

    chain.add( set_value_command( *active_session, sheet_point( 8, 24 ) , "=HLOOKUP(0.1; A2:I4; 3)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 8, 24 )  ) );

    chain.add( set_value_command( *active_session, sheet_point( 9, 24 ) , "=HLOOKUP(\"fooBAr\"; A3:I4; 2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 9, 24 )  ) );

    chain.add( set_value_command( *active_session, sheet_point( 10, 24 ) , "=HLOOKUP(\"BAr\"; A3:I4; 2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 10, 24 )  ) );

    chain.add( set_value_command( *active_session, sheet_point( 11, 24 ) , "=HLOOKUP(\"BAr123\"; A3:I4; 2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 11, 24 )  ) );

    chain.add( set_value_command( *active_session, sheet_point( 12, 24 ) , "=HLOOKUP(\"BAr123\"; A3:I4; 2; FALSE)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 12, 24 )  ) );

    chain.add( set_value_command( *active_session, sheet_point( 13, 24 ) , "=HLOOKUP(\"nothere\"; A3:I4; 2; FALSE)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 13, 24 )  ) );

    chain.add( set_value_command( *active_session, sheet_point( 14, 24 ) , "=HLOOKUP(\"BAr123\"; A3:J4; 2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 14, 24 )  ) );

    chain.add( set_value_command( *active_session, sheet_point( 15, 24 ) , "=HLOOKUP(\"BAr123\"; A3:J4; 3)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 15, 24 )  ) );

    chain.execute();
    TYPED_CHECK_EQUAL( get_value_command, chain[37], variant( "line 6" ) );
    TYPED_CHECK_EQUAL( get_value_command, chain[39], variant( variant::error_n_a ) );
    TYPED_CHECK_EQUAL( get_value_command, chain[41], variant( "line 8" ) );
    TYPED_CHECK_EQUAL( get_value_command, chain[43], variant( "line 5" ) );
    TYPED_CHECK_EQUAL( get_value_command, chain[45], variant( variant::error_ref ) );
    TYPED_CHECK_EQUAL( get_value_command, chain[47], variant( "line 6" ) );
    TYPED_CHECK_EQUAL( get_value_command, chain[49], variant( "line 8" ) );
    TYPED_CHECK_EQUAL( get_value_command, chain[51], variant( variant::error_n_a ) );
    TYPED_CHECK_EQUAL( get_value_command, chain[53], variant( "line 7" ) );
    TYPED_CHECK_EQUAL( get_value_command, chain[55], variant( "line 2" ) );
    TYPED_CHECK_EQUAL( get_value_command, chain[57], variant( "line 2" ) );
    TYPED_CHECK_EQUAL( get_value_command, chain[59], variant( variant::error_n_a ) );
    TYPED_CHECK_EQUAL( get_value_command, chain[61], variant( variant::error_n_a ) );
    TYPED_CHECK_EQUAL( get_value_command, chain[63], variant( "line 2" ) );
    TYPED_CHECK_EQUAL( get_value_command, chain[65], variant( variant::error_ref ) );
}

/*!
 * \brief
 *
 * \author
 * Radu Ialovoi <ialovoi@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_lookup_h_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) , variant( 0.457 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 1 ) , variant( 0.525 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 2 ) , variant( 0.616 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 3 ) , variant( 0.675 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 4 ) , variant( 0.746 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 5 ) , variant( 0.835 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 6 ) , variant( 0.946 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 7 ) , variant( 1.09 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 8 ) , variant( 1.29 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) , variant( false ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 1 ) , variant( 0.525 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 2 ) , variant( false ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 3 ) , variant( 0.675 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 4 ) , variant( 0.746 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 5 ) , variant( false ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 6 ) , variant( 0.946 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 7 ) , variant( true ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 8 ) , variant( true ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) , variant( "foo" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 1 ) , variant( 0.525 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 2 ) , variant( "bar" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 3 ) , variant( 0.675 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 4 ) , variant( 0.746 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 5 ) , variant( false ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 6 ) , variant( 0.946 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 7 ) , variant( "foobar" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 8 ) , variant( true ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) , variant( "line 0" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 1  ) , variant( "line 1" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 2  ) , variant( "line 2" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 3  ) , variant( "line 3" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 4  ) , variant( "line 4" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 5  ) , variant( "line 5" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 6  ) , variant( "line 6" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 7  ) , variant( "line 7" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 8  ) , variant( "line 8" ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 0, 24 ) , "=LOOKUP(1; A1:I4)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 0, 24 )  ) );

    chain.add( set_value_command( *active_session, sheet_point( 2, 24 ) , "=LOOKUP(2;A1:I4)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 24 )  ) );

    chain.add( set_value_command( *active_session, sheet_point( 3, 24 ) , "=LOOKUP(0.835;A1:I4)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 24 )  ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 24 ) , "=LOOKUP(1; A2:I4)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 24 )  ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 24 ) , "=LOOKUP(1; A2:I4)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 24 )  ) );

    chain.add( set_value_command( *active_session, sheet_point( 6, 24 ) , "=LOOKUP(TRUE; A2:I4)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 24 )  ) );

    chain.add( set_value_command( *active_session, sheet_point( 8, 24 ) , "=LOOKUP(0.1; A2:I4)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 8, 24 )  ) );

    chain.add( set_value_command( *active_session, sheet_point( 9, 24 ) , "=LOOKUP(\"fooBAr\"; A3:I4)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 9, 24 )  ) );

    chain.add( set_value_command( *active_session, sheet_point( 10, 24 ) , "=LOOKUP(\"BAr\"; A3:I4)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 10, 24 )  ) );

    chain.add( set_value_command( *active_session, sheet_point( 11, 24 ) , "=LOOKUP(\"BAr123\"; A3:I4)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 11, 24 )  ) );

    chain.execute();
    TEST_GET_VALUE( chain[37], variant( "line 6" ) );
    TEST_GET_VALUE( chain[39], variant( "line 8" ) );
    TEST_GET_VALUE( chain[41], variant( "line 5" ) );
    TEST_GET_VALUE( chain[37], variant( "line 6" ) );
    TEST_GET_VALUE( chain[45], variant( "line 6" ) );
    TEST_GET_VALUE( chain[47], variant( "line 8" ) );
    TEST_GET_VALUE( chain[49], variant( variant::error_n_a ) );
    TEST_GET_VALUE( chain[51], variant( "line 7" ) );
    TEST_GET_VALUE( chain[53], variant( "line 2" ) );
    TEST_GET_VALUE( chain[55], variant( "line 2" ) );
}

/*!
 * \brief
 *
 * \author
 * Radu Ialovoi <ialovoi@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_lookup_v_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) , variant( 0.457 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) , variant( 0.525 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) , variant( 0.616 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) , variant( 0.675 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) , variant( 0.746 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) , variant( 0.835 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) , variant( 0.946 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) , variant( 1.09 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 8, 0 ) , variant( 1.29 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 0, 1 ) , variant( false ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 1 ) , variant( 0.525 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 1 ) , variant( false ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 1 ) , variant( 0.675 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 1 ) , variant( 0.746 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 1 ) , variant( false ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 6, 1 ) , variant( 0.946 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 7, 1 ) , variant( true ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 8, 1 ) , variant( true ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 0, 2 ) , variant( "foo" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 2 ) , variant( 0.525 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 2 ) , variant( "bar" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 2 ) , variant( 0.675 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 2 ) , variant( 0.746 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 2 ) , variant( false ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 6, 2 ) , variant( 0.946 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 7, 2 ) , variant( "foobar" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 8, 2 ) , variant( true ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 0, 3 ) , variant( "line 0" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 3  ) , variant( "line 1" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 3  ) , variant( "line 2" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 3  ) , variant( "line 3" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 3  ) , variant( "line 4" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 3  ) , variant( "line 5" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 6, 3  ) , variant( "line 6" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 7, 3  ) , variant( "line 7" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 8, 3  ) , variant( "line 8" ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 0, 4 ) , "=LOOKUP(1; A1:D9)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 0, 4 )  ) );

    chain.add( set_value_command( *active_session, sheet_point( 2, 4 ) , "=LOOKUP(2;A1:D9)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 4 )  ) );

    chain.add( set_value_command( *active_session, sheet_point( 3, 4 ) , "=LOOKUP(0.835;A1:D9)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 4 )  ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 4 ) , "=LOOKUP(1; B1:D9)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 4 )  ) );

    chain.add( set_value_command( *active_session, sheet_point( 6, 4 ) , "=LOOKUP(TRUE; B1:D9)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 4 )  ) );

    chain.add( set_value_command( *active_session, sheet_point( 8, 4 ) , "=LOOKUP(0.1; B1:D9)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 8, 4 )  ) );

    chain.add( set_value_command( *active_session, sheet_point( 9, 4 ) , "=LOOKUP(\"fooBAr\"; C1:D9)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 9, 4 )  ) );

    chain.add( set_value_command( *active_session, sheet_point( 10, 4 ) , "=LOOKUP(\"BAr\"; C1:D9)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 10, 4 )  ) );

    chain.add( set_value_command( *active_session, sheet_point( 11, 4 ) , "=LOOKUP(\"BAr123\"; C1:D9)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 11, 4 )  ) );

    chain.add( set_value_command( *active_session, sheet_point( 14, 4 ) , "=LOOKUP(\"BAr123\"; C1:D10)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 14, 4 )  ) );

    chain.execute();
    TEST_GET_VALUE( chain[37], variant( "line 6" ) );
    TEST_GET_VALUE( chain[39], variant( "line 8" ) );
    TEST_GET_VALUE( chain[41], variant( "line 5" ) );
    TEST_GET_VALUE( chain[43], variant( "line 6" ) );
    TEST_GET_VALUE( chain[45], variant( "line 8" ) );
    TEST_GET_VALUE( chain[47], variant( variant::error_n_a ) );
    TEST_GET_VALUE( chain[49], variant( "line 7" ) );
    TEST_GET_VALUE( chain[51], variant( "line 2" ) );
    TEST_GET_VALUE( chain[53], variant( "line 2" ) );
    TEST_GET_VALUE( chain[55], variant( "line 2" ) );
}

/*!
 * \brief
 *
 * \author
 * Doru Paraschiv <doru@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_index_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) , variant( "Apples" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) , variant( "Bananas" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 1 ) , variant( "Lemons" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 1 ) , variant( "Pears" ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) , "=INDEX(A1:B2;2;2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) , "=INDEX(A1:B2;2;1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) , "=INDEX(A1:B2;0;1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.execute();

    TEST_GET_VALUE( chain[5], variant( "Pears" ) );
    TEST_GET_VALUE( chain[7], variant( "Bananas" ) );

    variant::sparse_array_type test_array;
    test_array.push_back( variant () );
    test_array.push_back( variant () );
    test_array.push_back( variant( "Apples" ) );
    test_array.push_back( variant( "Bananas" ) );

    TEST_GET_VALUE( chain[9], variant( test_array ) );
}

/*!
 * \brief
 *
 * \author
 * Radu Racariu <radu@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_rand_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) , "=RAND()" ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 1 ) , "=AND(A1>=0;A1<=1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 0, 1 ) ) );
    chain.execute();

    TEST_GET_VALUE( chain[2], variant( true ) );

}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_isblank_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 3 ) , "123" ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 4 ) , "FORMULA" ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) , "=ISBLANK(A1)" ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 1 ) , "=ISBLANK(D1)" ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 2 ) , "=ISBLANK(E1)" ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 3 ) , "=ISBLANK(A3)" ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 4 ) , "=ISBLANK(a2:a3)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 0 ) ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 1 ) ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 2 ) ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 3 ) ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 4 ) ) );
    chain.execute();

    TEST_GET_VALUE( chain[10], variant( false ) );
    TEST_GET_VALUE( chain[11], variant( false ) );
    TEST_GET_VALUE( chain[12], variant( false ) );
    TEST_GET_VALUE( chain[13], variant( true ) );

    variant::sparse_array_type test_array;
    test_array.push_back( variant( false  ) );
    test_array.push_back( variant( true ) );

    TEST_GET_VALUE( chain[14], variant( test_array ) );
}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_iserror_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 1 ) ,  variant( 0.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 2 ) ,  "=A1/B1" ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 3 ) , "=ISERROR(C1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 0, 3 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 4 ) , "=ISERROR(A1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 0, 4 ) ) );
    chain.execute();

    TEST_GET_VALUE( chain[4], variant( true ) );
    TEST_GET_VALUE( chain[6], variant( false ) );
}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_if_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 1 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 2 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 3 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 4 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 5 ) ,  variant( 3.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  "=if( A1 < B1; C1; D1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  "=if( A1 > B1; 1; D1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=if($A$1<=max($B$1;$C$1);$A$1;(min($B$1;$C$1)-1))" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=if($A$1:$F$1=$B$1;true;false)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );


    chain.execute();

    TEST_GET_VALUE( chain[7], variant( 3.0 ) );
    TEST_GET_VALUE( chain[9], variant( 1.0 ) );
    TEST_GET_VALUE( chain[11], variant( 5.0 ) );

    variant test_result( variant::type_array );
    variant::sparse_array_type& test_array = test_result.array();

    test_array.push_back( variant( false ) );
    test_array.push_back( variant( true ) );
    test_array.push_back( variant( false ) );
    test_array.push_back( variant( false ) );
    test_array.push_back( variant( false ) );
    test_array.push_back( variant( false ) );

    TEST_GET_VALUE( chain[13], test_result );
}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_not_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) ,  variant( true ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 1 ) ,  "=not( A1 )" ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 2 ) ,  "=not(1+1=2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 0, 1 ) ) );
    chain.add( get_value_command( *active_session, sheet_point( 0, 2 ) ) );
    chain.execute();

    TEST_GET_VALUE( chain[3], variant( false ) );
    TEST_GET_VALUE( chain[4], variant( false ) );
}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_average_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 3 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 4 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 5 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  "=AVERAGE(A1:G1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  "=AVERAGE( 1; 2; 3; 4; 5; 6; 7)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=AVERAGE( {1; 2; 3}; 4; 5; 6; 7)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 4 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  "=AVERAGE(A6:G6)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) ,  "=AVERAGE( TRUE; 2; 3; 4; 5; 6; 7)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 7, 0 ) ) );
    chain.add( get_formula_command( *active_session, sheet_point( 3, 0 ) ) );
    chain.execute();

    TYPED_CHECK_EQUAL( get_formula_command, chain[21], "=AVERAGE({1;2;3};4;5;6;7)" );
    TEST_GET_VALUE( chain[8], variant( 4.0 ) );
    TEST_GET_VALUE( chain[10], variant( 4.0 ) );
    TEST_GET_VALUE( chain[12], variant( 4.0 ) );
    TEST_GET_VALUE( chain[18], variant( 4.0 ) );
    TEST_GET_VALUE( chain[20], variant( 4.0 ) );
}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_max_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 3 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 4 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 5 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  "=MAX(A1:G1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  "=MAX( 1; 2; 3; 4; 5; 6; 7)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=MAX( {1; 2; 3}; 4; 5; 6; 7)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 4 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  "=MAX(A6:G6)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) ,  "=MAX( TRUE; 2; 3; 4; 5; 6; TRUE)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 7, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 9, 0 ) ,  "=MAX(A9:G9)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 9, 0 ) ) );
    chain.execute();

    TEST_GET_VALUE( chain[8], variant( 7.0 ) );
    TEST_GET_VALUE( chain[10], variant( 7.0 ) );
    TEST_GET_VALUE( chain[12], variant( 7.0 ) );
    TEST_GET_VALUE( chain[18], variant( 7.0 ) );
    TEST_GET_VALUE( chain[20], variant( 6.0 ) );
    TEST_GET_VALUE( chain[22], variant( 0.0 ) );
}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_min_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 3 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 4 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 5 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  "=MIN(A1:G1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  "=MIN( 1; 2; 3; 4; 5; 6; 7)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=MIN( {1; 2; 3}; 4; 5; 6; 7)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 4 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  "=MIN(A6:G6)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) ,  "=MIN( TRUE; 2; 3; 4; 5; 6; TRUE)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 7, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 9, 0 ) ,  "=MIN(A9:G9)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 9, 0 ) ) );
    chain.execute();

    TEST_GET_VALUE( chain[8], variant( 1.0 ) );
    TEST_GET_VALUE( chain[10], variant( 1.0 ) );
    TEST_GET_VALUE( chain[12], variant( 1.0 ) );
    TEST_GET_VALUE( chain[18], variant( 1.0 ) );
    TEST_GET_VALUE( chain[20], variant( 2.0 ) );
    TEST_GET_VALUE( chain[22], variant( 0.0 ) );
}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_rank_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 3 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 4 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 5 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 3 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 4 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 5 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  "=RANK(0;A1:G1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 1 ) ,  "=RANK(1;A1:G1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 1 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 2 ) ,  "=RANK(1;A1:G1;1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 2 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 3 ) ,  "=RANK(3;A1:G1;0)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 3 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 4 ) ,  "=RANK(3;A1:G1;1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 4 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=RANK(0;A3:G3)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 1 ) ,  "=RANK(1;A3:G3)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 1 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 2 ) ,  "=RANK(1;A3:G3;1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 2 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 3 ) ,  "=RANK(3;A3:G3;0)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 3 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 4 ) ,  "=RANK(3;A3:G3;1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 4 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 5 ) ,  "=RANK($A$1;$A$1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 5 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 6 ) ,  "=RANK($A$1:$B$1;$A$1:$B$1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 6 ) ) );
    chain.execute();

    TEST_GET_VALUE( chain[15], variant( variant::error_n_a ) );
    TEST_GET_VALUE( chain[17], variant( 7.0 ) );
    TEST_GET_VALUE( chain[19], variant( 1.0 ) );
    TEST_GET_VALUE( chain[21], variant( 5.0 ) );
    TEST_GET_VALUE( chain[23], variant( 3.0 ) );

    TEST_GET_VALUE( chain[25], variant( variant::error_n_a ) );
    TEST_GET_VALUE( chain[27], variant( 7.0 ) );
    TEST_GET_VALUE( chain[29], variant( 1.0 ) );
    TEST_GET_VALUE( chain[31], variant( 5.0 ) );
    TEST_GET_VALUE( chain[33], variant( 3.0 ) );
    TEST_GET_VALUE( chain[35], variant( 1.0 ) );

    variant test_result( variant::type_array );
    variant::sparse_array_type& test_array = test_result.array();

    test_array.push_back( variant( 2.0 ) );
    test_array.push_back( variant( 1.0 ) );

    TEST_GET_VALUE( chain[37], test_result );
}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_stdev_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 3 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 4 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 5 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  "=STDEV(A1:B1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  "=STDEV(A1:G1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=STDEV({1})" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=STDEV(1;2;3;4;5;6;7)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=STDEV({1;2;3;4;5;6;7})" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );         //this returns parser error

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 3 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 4 ) ,  variant( "aaa" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 5 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 6, 6 ) ,  "=STDEV(A2:G2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 6 ) ) );


    chain.execute();

    // checks that these values differ no more then 0.0001%
    const double tolerance = 0.0001;

    TEST_GET_CLOSE( chain[8], 0.707107, tolerance );
    TEST_GET_CLOSE( chain[10], 2.160246899, tolerance );
    TEST_GET_CLOSE( chain[14], 2.160246899, tolerance );
    TEST_GET_CLOSE( chain[16], 2.160246899, tolerance );
    TEST_GET_CLOSE( chain[25], 2.316606714, tolerance );
}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_var_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 3 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 4 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 5 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  "=VAR(A1:B1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  "=VAR(A1:G1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=VAR({1})" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=VAR(1;2;3;4;5;6;7)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=VAR({1;2;3;4;5;6;7})" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );         //this returns parser error

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 2 ) ,  variant( "aaa" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 3 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 4 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 5 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  "=VAR(A2:G2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );


    chain.execute();

    // checks that these values differ no more then 0.0001%
    const double tolerance = 0.0001;

    TEST_GET_CLOSE( chain[8], 0.5, tolerance );  //these testes actually don't fail.
    TEST_GET_CLOSE( chain[10], 4.666666667, tolerance ); //there are small precision errors.
    //    TEST_GET_VALUE( chain[12] ).value().error_code(), variant::error_div_null, tolerance ); //cannot test errors
    TEST_GET_CLOSE( chain[14], 4.666666667, tolerance ); //the same as the first two
    TEST_GET_CLOSE( chain[16], 4.666666667, tolerance ); //the same as the first two
    TEST_GET_CLOSE( chain[25], 5.366666667, tolerance ); //the same as the first two
}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_vara_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) ,  variant( 0.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 2 ) ,  variant( 0.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 3 ) ,  variant( 0.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 4 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 5 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  "=VARA(A1:B1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  "=VARA(A1:G1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=VARA({1})" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=VARA(1;2;0;4;5;6;7)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=VARA({1;2;TRUE;4;5;6;7})" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );         //this returns parser error

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 3 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 4 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 5 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  "=VARA(A2:G2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );


    chain.execute();

    // checks that these values differ no more then 0.0001%
    const double tolerance = 0.0001;

    TEST_GET_CLOSE( chain[8], 2.0, tolerance );  //these testes actually don't fail.
    TEST_GET_CLOSE( chain[10], 9.476190476, tolerance ); //there are small precision errors.
    //    TEST_GET_VALUE( chain[12] ).value().error_code(), variant::error_div_null, tolerance ); //cannot test errors
    TEST_GET_CLOSE( chain[14], 6.952380952, tolerance ); //the same as the first two
    TEST_GET_CLOSE( chain[16], 5.366666667, tolerance ); //the same as the first two
    TEST_GET_CLOSE( chain[25], 4.666666667, tolerance ); //the same as the first two

}


/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_stdeva_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 3 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 4 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 5 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  "=STDEVA(A1:B1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  "=STDEVA(A1:G1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=STDEVA({1})" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=STDEVA(1;2;3;4;5;6;7)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=STDEVA({1;2;3;4;5;6;7})" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );         //this returns parser error

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 3 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 4 ) ,  variant( "aaa" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 5 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  "=STDEVA(A2:G2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.0001%
    const double tolerance = 0.000001;

    TEST_GET_CLOSE( chain[8], 0.707106781, tolerance );  //these testes actually don't fail.
    TEST_GET_CLOSE( chain[10], 2.160246899, tolerance ); //there are small precision errors.
    //    TEST_GET_VALUE( chain[12] ).value().error_code(), variant::error_div_null, tolerance ); //cannot test errors
    TEST_GET_CLOSE( chain[14], 2.160246899, tolerance ); //the same as the first two
    TEST_GET_CLOSE( chain[16], 2.160246899, tolerance ); //the same as the first two
    TEST_GET_CLOSE( chain[25], 2.563479778, tolerance ); //the same as the first two

}




/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_stdevp_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 3 ) ,  variant( "test" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 4 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 5 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  "=STDEVP(A1:B1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  "=STDEVP(A1:G1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=STDEVP({1})" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=STDEVP(1;2;3;4;5;6;7)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=STDEVP({1;2;3;4;5;6;7})" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );         //this returns parser error
    chain.execute();

    // checks that these values differ no more then 0.0001%
    const double tolerance = 0.0001;

    TEST_GET_CLOSE( chain[8], 0.5, tolerance );  //these testes actually don't fail.
    TEST_GET_CLOSE( chain[10], 2.160246899, tolerance ); //there are small precision errors.
    // TEST_GET_VALUE( chain[12] ).value().error_code(), variant::error_div_null, tolerance ); //cannot test errors
    TEST_GET_CLOSE( chain[14], 2.0, tolerance ); //the same as the first two
    TEST_GET_CLOSE( chain[16], 2.0, tolerance ); //the same as the first two

}




/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_stdevpa_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 3 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 4 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 5 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  "=STDEVPA(A1:B1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  "=STDEVPA(A1:G1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=STDEVPA({1})" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=STDEVPA(1;2;""3.0"";4;5;6;7)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=STDEVPA({1;2;3;4;5;6;7})" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );         //this returns parser error

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 3 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 4 ) ,  variant( "aaa" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 5 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  "=STDEVPA(A2:G2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.0001%
    const double tolerance = 0.000001;

    TEST_GET_CLOSE( chain[8], 0.5, tolerance );
    TEST_GET_CLOSE( chain[10], 2.0, tolerance );
    //    TEST_GET_VALUE( chain[12] ).value().error_code(), variant::error_div_null, tolerance ); //cannot test errors
    TEST_GET_CLOSE( chain[14], 2.0, tolerance );
    TEST_GET_CLOSE( chain[16], 2.0, tolerance );
    TEST_GET_CLOSE( chain[25], 2.373321104, tolerance );

}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_covar_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 3 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 4 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 5 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 3 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 4 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 5 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  "=COVAR(A1:B1; A2:B2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );

    //chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  "=COVAR(A1:F1; A2:G2)" ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=COVAR(A1:G1; {1;2;3;4;5;6;7})" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=COVAR({1})" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=COVAR({1;2;3;4;5;6;7}; {1;2;3;4;5;6;7})" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );         //this returns parser error

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 3 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 4 ) ,  variant( "aaa" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 5 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 3 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 4 ) ,  variant( "aaa" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 5 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  "=COVAR(A4:G4; A5:G5)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.000001;

    TEST_GET_CLOSE( chain[15], 0.25, tolerance );
    //TEST_GET_VALUE( chain[17] ).value().is_error(), true );
    TEST_GET_CLOSE( chain[17], 4.0, tolerance );
    //TEST_GET_VALUE( chain[17], variant( variant::error_n_a ) ); // 6 = #N/A error
    TEST_GET_VALUE( chain[19], variant( variant::error_n_a ) );
    TEST_GET_CLOSE( chain[21], 4.0, tolerance );
    TEST_GET_CLOSE( chain[37], 4.472222222, tolerance );

}


/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_correl_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 3 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 4 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 5 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 3 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 4 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 5 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  "=CORREL(A1:B1; A2:B2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=CORREL(A1:G1; A2:G2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=CORREL({1;2;3;4;5;6;7}; {1;2;3;4;5;6;7})" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );         //this returns parser error

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 3 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 4 ) ,  variant( "aaa" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 5 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 3 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 4 ) ,  variant( "aaa" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 5 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=CORREL(A4:G4; A5:G5)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.000001;

    TEST_GET_CLOSE( chain[15], 1.0, tolerance );
    TEST_GET_CLOSE( chain[17], 0.985036563, tolerance );
    TEST_GET_CLOSE( chain[19], 1.0, tolerance );
    TEST_GET_CLOSE( chain[35], 1.0, tolerance );

}



/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_rsq_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 3 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 4 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 5 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 3 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 4 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 5 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  "=RSQ(A1:B1; A2:B2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=RSQ(A1:G1; A2:G2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=RSQ({1;2;3;4;5;6;7}; {1;2;3;4;5;6;7})" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );         //this returns parser error

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 3 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 4 ) ,  variant( "aaa" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 5 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 3 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 4 ) ,  variant( "aaa" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 5 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=RSQ(A4:G4; A5:G5)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.000001;

    TEST_GET_CLOSE( chain[15], 1.0, tolerance );
    TEST_GET_CLOSE( chain[17], 0.97029703, tolerance );
    TEST_GET_CLOSE( chain[19], 1.0, tolerance );
    TEST_GET_CLOSE( chain[35], 1.0, tolerance );

}


/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_pearson_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 3 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 4 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 5 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 3 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 4 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 5 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  "=PEARSON(A1:B1; A2:B2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=PEARSON(A1:G1; A2:G2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=PEARSON({1;2;3;4;5;6;7}; {1;2;3;4;5;6;7})" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );         //this returns parser error

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 3 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 4 ) ,  variant( "aaa" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 5 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 3 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 4 ) ,  variant( "aaa" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 5 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=PEARSON(A4:G4; A5:G5)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.000001;

    TEST_GET_CLOSE( chain[15], 1.0, tolerance );
    TEST_GET_CLOSE( chain[17], 0.985036563, tolerance );
    TEST_GET_CLOSE( chain[19], 1.0, tolerance );
    TEST_GET_CLOSE( chain[35], 1.0, tolerance );

}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_slope_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 3 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 4 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 5 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 3 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 4 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 5 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  "=SLOPE(A1:A1; A2:A2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=SLOPE(A1:G1; A2:G2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=SLOPE({1;2;3;4;5;6;7}; {1;2;3;4;5;6;7})" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );         //this returns parser error

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 3 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 4 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 5 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 3 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 4 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 5 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=SLOPE(A4:G4; A5:G5)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.000001;

    TEST_GET_VALUE( chain[15], variant( variant::error_div_null ) );
    TEST_GET_CLOSE( chain[17], 0.944444444, tolerance );
    TEST_GET_CLOSE( chain[19], 1.0, tolerance );
    TEST_GET_CLOSE( chain[35], 0.939814815, tolerance );

}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_intercept_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 3 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 4 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 5 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 3 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 4 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 5 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  "=INTERCEPT(A1:A1; A2:A2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=INTERCEPT(A1:G1; A2:G2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=INTERCEPT({1;2;3;4;5;6;7}; {1;2;3;4;5;6;7})" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );         //this returns parser error

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 3 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 4 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 5 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 3 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 4 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 5 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=INTERCEPT(A4:G4; A5:G5)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.000001;

    TEST_GET_VALUE( chain[15], variant( variant::error_div_null ) );
    TEST_GET_CLOSE( chain[17], -0.055555556, tolerance );
    TEST_GET_CLOSE( chain[19], 0.0, tolerance );
    TEST_GET_CLOSE( chain[35], 0.106481481, tolerance );

}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_steyx_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 3 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 4 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 5 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 3 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 4 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 5 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  "=STEYX(A1:A1; A2:A2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=STEYX(A1:G1; A2:G2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=STEYX({1;2;3;4;5;6;7}; {1;2;3;4;5;6;7})" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );         //this returns parser error

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 3 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 4 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 5 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 3 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 4 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 5 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=STEYX(A4:G4; A5:G5)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.000001;

    TEST_GET_VALUE( chain[15], variant( variant::error_div_null ) );
    TEST_GET_CLOSE( chain[17], 0.516397779, tolerance );
    TEST_GET_CLOSE( chain[19], 0.0, tolerance );
    TEST_GET_CLOSE( chain[35], 0.386101119, tolerance );

}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_sumx2py2_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 3 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 4 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 5 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 3 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 4 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 5 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  "=SUMX2PY2(A1:B1; A2:B2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=SUMX2PY2(A1:G1; A2:G2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=SUMX2PY2(A1:G1; {1;2;3;4;5;6;7})" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=SUMX2PY2({1})" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  "=SUMX2PY2({1;2;3;4;5;6;7}; {1;2;3;4;5;6;7})" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 0 ) ) );         //this returns parser error

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 3 ) ,  variant( "bbb" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 4 ) ,  variant( "aaa" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 5 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 3 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 4 ) ,  variant( "aaa" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 5 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) ,  "=SUMX2PY2(A4:G4; A5:G5)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 7, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.000001;

    TEST_GET_CLOSE( chain[15], 10.0, tolerance );
    TEST_GET_CLOSE( chain[17], 280.0, tolerance );
    TEST_GET_CLOSE( chain[19], 280.0, tolerance );
    TEST_GET_VALUE( chain[21], variant( variant::error_n_a ) ); // 6 = #N/A error
    TEST_GET_CLOSE( chain[23], 280.0, tolerance );
    TEST_GET_CLOSE( chain[39], 198.0, tolerance );

}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_sumx2my2_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 3 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 4 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 5 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 1 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 2 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 3 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 4 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 5 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 6 ) ,  variant( 8.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  "=SUMX2MY2(A1:B1; A2:B2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=SUMX2MY2(A1:G1; A2:G2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=SUMX2MY2(A1:G1; {1;3;4;5;6;7;8})" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=SUMX2MY2({1})" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  "=SUMX2MY2({1;2;3;4;5;6;7}; {1;4;5;6;7;8;9})" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 0 ) ) );         //this returns parser error

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 3 ) ,  variant( "bbb" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 4 ) ,  variant( "aaa" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 5 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 1 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 2 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 3 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 4 ) ,  variant( "aaa" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 5 ) ,  variant( 8.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 6 ) ,  variant( 9.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) ,  "=SUMX2MY2(A4:G4; A5:G5)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 7, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.000001;

    TEST_GET_CLOSE( chain[15], -5.0, tolerance );
    TEST_GET_CLOSE( chain[17], -60.0, tolerance );
    TEST_GET_CLOSE( chain[19], -60.0, tolerance );
    TEST_GET_VALUE( chain[21], variant( variant::error_n_a ) ); // 6 = #N/A error
    TEST_GET_CLOSE( chain[23], -132.0, tolerance );
    TEST_GET_CLOSE( chain[39], -88.0, tolerance );

}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_sumxmy2_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 3 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 4 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 5 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 1 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 2 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 3 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 4 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 5 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 6 ) ,  variant( 8.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  "=SUMXMY2(A1:B1; A2:B2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=SUMXMY2(A1:G1; A2:G2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=SUMXMY2(A1:G1; {1;3;4;5;6;7;8})" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=SUMXMY2({1})" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  "=SUMXMY2({1;2;3;4;5;6;7}; {1;4;5;6;7;8;9})" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 0 ) ) );         //this returns parser error

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 3 ) ,  variant( "bbb" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 4 ) ,  variant( "aaa" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 5 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 1 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 2 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 3 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 4 ) ,  variant( "aaa" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 5 ) ,  variant( 8.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 6 ) ,  variant( 9.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) ,  "=SUMXMY2(A4:G4; A5:G5)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 7, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.000001;

    TEST_GET_CLOSE( chain[15], 1.0, tolerance );
    TEST_GET_CLOSE( chain[17], 6.0, tolerance );
    TEST_GET_CLOSE( chain[19], 6.0, tolerance );
    TEST_GET_VALUE( chain[21], variant( variant::error_n_a ) ); // 6 = #N/A error
    TEST_GET_CLOSE( chain[23], 24.0, tolerance );
    TEST_GET_CLOSE( chain[39], 16.0, tolerance );

}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_ftest_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 3 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 4 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 5 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 1 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 2 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 3 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 4 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 5 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 6 ) ,  variant( 8.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  "=FTEST(A1:B1; A2:B2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=FTEST(A1:G1; A2:G2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=FTEST(A1:G1; {1;3;4;5;6;7;8;9})" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=FTEST({1}; {1})" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  "=FTEST({1;2;3;4;5;6;7}; {1;3;4;5;6;7;8;9})" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 0 ) ) );         //this returns parser error

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 3 ) ,  variant( "bbb" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 4 ) ,  variant( "aaa" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 5 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 1 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 2 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 3 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 4 ) ,  variant( "aaa" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 5 ) ,  variant( 8.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 6 ) ,  variant( 9.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) ,  "=FTEST(A4:G4; A5:G5)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 7, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.000001;

    TEST_GET_CLOSE( chain[15], 0.59033447, tolerance );
    TEST_GET_CLOSE( chain[17], 0.797071592, tolerance );
    TEST_GET_CLOSE( chain[19], 0.622363881, tolerance );
    TEST_GET_VALUE( chain[21], variant( variant::error_div_null ) ); //#DIV/0! error
    TEST_GET_CLOSE( chain[23], 0.622363881, tolerance );
    TEST_GET_CLOSE( chain[39], 0.859814349, tolerance );

}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_len_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) ,  variant( "1234567890" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 1 ) ,  variant( "W\xC3\xBCrfel" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 2 ) ,  variant( 10.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 3 ) ,  variant( "TRUE" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  "=LEN(A1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  "=LEN(B1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=LEN(C1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=LEN(D1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );
    chain.execute();

    TEST_GET_VALUE( chain[5], variant( 10.0 ) );
    TEST_GET_VALUE( chain[7], variant( 6.0 ) );
    TEST_GET_VALUE( chain[9], variant( 2.0 ) );
    TEST_GET_VALUE( chain[11], variant( 4.0 ) );

}


#define TYPED_CHECK_EQUAL( type, obj, val ) \
    try{\
        BOOST_CHECK_NO_THROW( dynamic_cast<const type&>( (obj) ); );\
        dynamic_cast<const type&>( (obj) );\
        BOOST_CHECK_EQUAL( dynamic_cast<const type&>( (obj) ).value(), ( val ) );\
    } catch (std::bad_cast&) {};

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_left_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) ,  variant( "Another W\xC3\xBCrfel" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 1 ) ,  variant( 10.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 2 ) ,  variant( false ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 3 ) ,  variant( variant::error_value ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 3 ) ,  variant( "{1;2;3}" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  "=LEFT(A1;0)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  "=LEFT(A1;7)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=LEFT(A1;10)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=LEFT(A1;14)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=LEFT(A1;20)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  "=LEFT(B1;1 )" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) ,  "=LEFT(C1;3 )" ) );
    chain.add( get_value_command( *active_session, sheet_point( 7, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 8, 0 ) ,  "=LEFT( {100;200;300};2 )" ) );
    chain.add( get_value_command( *active_session, sheet_point( 8, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 9, 0 ) ,  "=LEFT({100;200;300}; -1 )" ) );
    chain.add( get_value_command( *active_session, sheet_point( 9, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 10, 0 ) ,  "=LEFT(A1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 10, 0 ) ) );

    chain.execute();


    variant test_result( variant::type_array );
    variant::sparse_array_type& test_array = test_result.array();


    TEST_GET_VALUE( chain[6], variant( "" ) );
    TEST_GET_VALUE( chain[8], variant( "Another" ) );
    TEST_GET_VALUE( chain[10], variant( "Another W\xC3\xBC" ) );
    TEST_GET_VALUE( chain[12], variant( "Another W\xC3\xBCrfel" ) );
    TEST_GET_VALUE( chain[14], variant( "Another W\xC3\xBCrfel" ) );
    TEST_GET_VALUE( chain[16], variant( "1" ) );
    TEST_GET_VALUE( chain[18], variant( "FAL" ) );

    test_array.clear();
    test_array.push_back( variant( "10" ) );
    test_array.push_back( variant( "20" ) );
    test_array.push_back( variant( "30" ) );
    TEST_GET_VALUE( chain[20], test_result );

    test_array.clear();
    test_array.push_back( variant( variant::error_value ) );
    test_array.push_back( variant( variant::error_value ) );
    test_array.push_back( variant( variant::error_value ) );
    TEST_GET_VALUE( chain[22], test_result );


    TEST_GET_VALUE( chain[24], variant( "A" ) );


}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */

BOOST_AUTO_TEST_CASE( function_right_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) ,  variant( "Another W\xC3\xBCrfel" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 1 ) ,  variant( 10.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 2 ) ,  variant( false ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 3 ) ,  variant( variant::error_value ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 3 ) ,  variant( "{1;2;3}" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  "=RIGHT(A1;0)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  "=RIGHT(A1;4)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=RIGHT(A1; 6 )" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=RIGHT(A1;14)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=RIGHT(A1;20 )" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  "=RIGHT(B1;1  )" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) ,  "=RIGHT(C1;3 )" ) );
    chain.add( get_value_command( *active_session, sheet_point( 7, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 8, 0 ) ,  "=RIGHT( {100;200;300};2 )" ) );
    chain.add( get_value_command( *active_session, sheet_point( 8, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 9, 0 ) ,  "=RIGHT({100;200;300};-1 )" ) );
    chain.add( get_value_command( *active_session, sheet_point( 9, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 10, 0 ) ,  "=RIGHT(A1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 10, 0 ) ) );

    chain.execute();

    variant test_result( variant::type_array );
    variant::sparse_array_type& test_array = test_result.array();

    TEST_GET_VALUE( chain[6], variant( "" ) );
    TEST_GET_VALUE( chain[8], variant( "rfel" ) );
    TEST_GET_VALUE( chain[10], variant( "W\xC3\xBCrfel" ) );
    TEST_GET_VALUE( chain[12], variant( "Another W\xC3\xBCrfel" ) );
    TEST_GET_VALUE( chain[14], variant( "Another W\xC3\xBCrfel" ) );
    TEST_GET_VALUE( chain[16], variant( "0" ) );
    TEST_GET_VALUE( chain[18], variant( "LSE" ) );

    test_array.clear();
    test_array.push_back( variant( "00" ) );
    test_array.push_back( variant( "00" ) );
    test_array.push_back( variant( "00" ) );
    TEST_GET_VALUE( chain[20], test_result );

    test_array.clear();
    test_array.push_back( variant( variant::error_value ) );
    test_array.push_back( variant( variant::error_value ) );
    test_array.push_back( variant( variant::error_value ) );
    TEST_GET_VALUE( chain[22], test_result );

    TEST_GET_VALUE( chain[24], variant( "l" ) );


}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_isunique_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 3 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 4 ) ,  "=ISUNIQUE(A1:D1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 0, 4 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 1 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 3 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 4 ) ,  "=ISUNIQUE(A2:D2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 4 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 3 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 4 ) ,  "=ISUNIQUE(A3:D3)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 4 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 3 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 4 ) ,  "=ISUNIQUE(A4:D4)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 4 ) ) );
    chain.execute();

    variant test_result( variant::type_array );
    variant::sparse_array_type& test_array = test_result.array();

    test_array.push_back( variant( true ) );
    test_array.push_back( variant( true ) );
    test_array.push_back( variant( true ) );
    test_array.push_back( variant( true ) );
    //test_array.push_back( variant( false ) );

    TEST_GET_VALUE( chain[5], test_result );

    test_array.clear();
    test_array.push_back( variant( false ) );
    test_array.push_back( variant( false ) );
    test_array.push_back( variant( true ) );
    test_array.push_back( variant( false ) );
    TEST_GET_VALUE( chain[11], test_result );

    test_array.clear();
    test_array.push_back( variant( true ) );
    test_array.push_back( variant( true ) );
    test_array.push_back( variant( false ) );
    test_array.push_back( variant( false ) );
    TEST_GET_VALUE( chain[17], test_result );

    test_array.clear();
    test_array.push_back( variant( false ) );
    test_array.push_back( variant( true ) );
    test_array.push_back( variant( true ) );
    test_array.push_back( variant( false ) );
    TEST_GET_VALUE( chain[23], test_result );
}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_isduplicate_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 3 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 4 ) ,  "=ISDUPLICATE(A1:D1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 0, 4 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 1 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 3 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 4 ) ,  "=ISDUPLICATE(A2:D2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 4 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 3 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 4 ) ,  "=ISDUPLICATE(A3:D3)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 4 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 3 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 4 ) ,  "=ISDUPLICATE(A4:D4)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 4 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 3 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 4 ) ,  "=ISDUPLICATE(A5:D5)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 4 ) ) );
    chain.execute();

    variant test_result( variant::type_array );
    variant::sparse_array_type& test_array = test_result.array();

    test_array.push_back( variant( false ) );
    test_array.push_back( variant( false ) );
    test_array.push_back( variant( false ) );
    test_array.push_back( variant( false ) );

    TEST_GET_VALUE( chain[5], test_result );

    test_array.clear();
    test_array.push_back( variant( true ) );
    test_array.push_back( variant( true ) );
    test_array.push_back( variant( false ) );
    test_array.push_back( variant( true ) );
    TEST_GET_VALUE( chain[11], test_result );

    test_array.clear();
    test_array.push_back( variant( false ) );
    test_array.push_back( variant( false ) );
    test_array.push_back( variant( true ) );
    test_array.push_back( variant( true ) );
    TEST_GET_VALUE( chain[17], test_result );

    test_array.clear();
    test_array.push_back( variant( true ) );
    test_array.push_back( variant( false ) );
    test_array.push_back( variant( false ) );
    test_array.push_back( variant( true ) );
    TEST_GET_VALUE( chain[23], test_result );

    test_array.clear();
    test_array.push_back( variant( true ) );
    test_array.push_back( variant( false ) );
    test_array.push_back( variant( false ) );
    test_array.push_back( variant( true ) );
    TEST_GET_VALUE( chain[27], test_result );
}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_percentrank_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 3 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 4 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 5 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 2 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 3 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 4 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 5 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 6 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  "=PERCENTRANK(A1:G1;0)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 1 ) ,  "=PERCENTRANK(A1:G1;1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 1 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 2 ) ,  "=PERCENTRANK(A1:G1;1.3)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 2 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 3 ) ,  "=PERCENTRANK(A1:G1;3)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 3 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 4 ) ,  "=PERCENTRANK(A1:G1;8)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 4 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=PERCENTRANK(A3:G3;0)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 1 ) ,  "=PERCENTRANK(A3:G3;1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 1 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 2 ) ,  "=PERCENTRANK(A3:G3;1.3)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 2 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 3 ) ,  "=PERCENTRANK(A3:G3;3)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 3 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 4 ) ,  "=PERCENTRANK(A3:G3; 8)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 4 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 5 ) ,  "=PERCENTRANK(A3:G3;1.4;5)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 5 ) ) );
    chain.execute();

    TEST_GET_VALUE( chain[15], variant( variant::error_n_a ) );
    TEST_GET_VALUE( chain[17], variant( 0.0 ) );
    TEST_GET_VALUE( chain[19], variant( 0.05 ) );
    TEST_GET_VALUE( chain[21], variant( 0.333 ) );
    TEST_GET_VALUE( chain[23], variant( variant::error_n_a ) );

    TEST_GET_VALUE( chain[25], variant( variant::error_n_a ) );
    TEST_GET_VALUE( chain[27], variant( 0.0 ) );
    TEST_GET_VALUE( chain[29], variant( 0.05 ) );
    TEST_GET_VALUE( chain[31], variant( 0.333 ) );
    TEST_GET_VALUE( chain[33], variant( variant::error_n_a ) );
    TEST_GET_CLOSE( chain[35], 0.06666, 0.0001 );
}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_betadist_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 8.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( 10.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  "=BETADIST(A2;A3;A4;A5;A6)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 8, 0 ) ,  variant( 8.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 9, 0 ) ,  variant( 10.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 10, 0 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 11, 0 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 12, 0 ) ,  "=BETADIST(A8;A9;A10;A11;A12)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 12, 0 ) ) );


    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.000001;

    TEST_GET_CLOSE( chain[6], 0.685470581, tolerance );
    TEST_GET_VALUE( chain[13], variant( variant::error_num ) );

}


/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_betainv_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 0.685470581 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 8.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( 10.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  "=BETAINV(A2;A3;A4;A5;A6)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) ,  variant( 0.685470581 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 8, 0 ) ,  variant( 8.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 9, 0 ) ,  variant( 10.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 10, 0 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 11, 0 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 12, 0 ) ,  "=BETAINV(A8;A9;A10;A11;A12)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 12, 0 ) ) );


    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.000001;

    TEST_GET_CLOSE( chain[6], 2.0, tolerance );
    TEST_GET_VALUE( chain[13], variant( variant::error_num ) );

}


/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_binomdist_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 10.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( 0.5 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=BINOMDIST(A2;A3;A4;FALSE)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=BINOMDIST(A2;A3;A4)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  variant( 11.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  variant( 10.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) ,  variant( 0.5 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 8, 0 ) ,  "=BINOMDIST(A6;A7;A8;FALSE)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 8, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 9, 0 ) ,  variant( -1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 10, 0 ) ,  variant( 10.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 11, 0 ) ,  variant( 0.5 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 12, 0 ) ,  "=BINOMDIST(A10;A11;A12;FALSE)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 12, 0 ) ) );


    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.000001;

    TEST_GET_CLOSE( chain[4], 0.205078125, tolerance );
    TEST_GET_VALUE( chain[6], variant( variant::error_n_a ) );
    TEST_GET_VALUE( chain[11], variant( variant::error_num ) );
    TEST_GET_VALUE( chain[16], variant( variant::error_num ) );

}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_chidist_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 18.307 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 10.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=CHIDIST(A2;A3)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  variant( -1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  variant( 10.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  "=CHIDIST(A5;A6)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 0 ) ) );


    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.000001;

    TEST_GET_CLOSE( chain[3], 0.050000589, tolerance );
    TEST_GET_VALUE( chain[7], variant( variant::error_num ) );

}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_chiinv_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 0.050001 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 10.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=CHIINV(A2;A3)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  variant( -1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  variant( 10.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  "=CHIINV(A5;A6)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 0 ) ) );


    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.000001;

    TEST_GET_CLOSE( chain[3], 18.30697346, tolerance );
    TEST_GET_VALUE( chain[7], variant( variant::error_num ) );

}


/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_chitest_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 58.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 11.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( 10.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  variant( 45.35 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  variant( 17.56 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) ,  variant( 16.09 ) ) );


    chain.add( set_value_command( *active_session, sheet_point( 1, 1 ) ,  variant( 35.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 1 ) ,  variant( 25.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 1 ) ,  variant( 23.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 1 ) ,  variant( 47.65 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 6, 1 ) ,  variant( 18.44 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 7, 1 ) ,  variant( 16.91 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 10, 0 ) ,  "=CHITEST(A2:B4;A6:B8)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 10, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 11, 0 ) ,  "=CHITEST(A2:B4;A6:B7)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 11, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 12, 0 ) ,  variant( 58.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 13, 0 ) ,  variant( 11.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 14, 0 ) ,  variant( 10.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 16, 0 ) ,  variant( 45.35 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 17, 0 ) ,  variant( 17.56 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 18, 0 ) ,  variant( "aaa" ) ) );


    chain.add( set_value_command( *active_session, sheet_point( 12, 1 ) ,  variant( 35.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 13, 1 ) ,  variant( 25.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 14, 1 ) ,  variant( 23.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 16, 1 ) ,  variant( 47.65 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 17, 1 ) ,  variant( 18.44 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 18, 1 ) ,  variant( 16.91 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 20, 0 ) ,  "=CHITEST(A13:B15;A17:B19)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 20, 0 ) ) );


    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[13], 0.000308192, tolerance );
    TEST_GET_VALUE( chain[15], variant( variant::error_n_a ) );
    TEST_GET_CLOSE( chain[29], 0.000975786, tolerance );

}


/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_combin_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 8.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 2.0 ) ) );


    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=COMBIN(A2;A3)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=COMBIN(A4;2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=COMBIN(8;10)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );



    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[3], 28.0, tolerance );
    TEST_GET_CLOSE( chain[5], 378.0, tolerance );
    TEST_GET_VALUE( chain[7], variant( variant::error_num ) );

}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_critbinom_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 0.5 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( 0.75 ) ) );


    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=CRITBINOM(A2;A3;A4)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  variant( 0.5 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) ,  variant( "aaa" ) ) );


    chain.add( set_value_command( *active_session, sheet_point( 8, 0 ) ,  "=CRITBINOM(A6;A7;A8)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 8, 0 ) ) );



    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[4], 4.0, tolerance );
    TEST_GET_VALUE( chain[9], variant( variant::error_value ) );

}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_expondist_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 0.2 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 10.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=EXPONDIST(A2;A3;TRUE)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=EXPONDIST(A2;A3;FALSE)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  variant( 0.2 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  variant( "aaa" ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) ,  "=EXPONDIST(A6;A7;TRUE)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 7, 0 ) ) );




    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[3], 0.864664717, tolerance );
    TEST_GET_CLOSE( chain[5], 1.353352832, tolerance );
    TEST_GET_VALUE( chain[9], variant( variant::error_value ) );

}


/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_fdist_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 15.20686486 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( 4.0 ) ) );


    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=FDIST(A2;A3;A4)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  variant( 15.20686486 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) ,  variant( "aaa" ) ) );


    chain.add( set_value_command( *active_session, sheet_point( 8, 0 ) ,  "=FDIST(A6;A7;A8)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 8, 0 ) ) );



    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[4], 0.01, tolerance );
    TEST_GET_VALUE( chain[9], variant( variant::error_value ) );

}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_finv_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 0.01 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( 4.0 ) ) );


    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=FINV(A2;A3;A4)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  variant( 0.01 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) ,  variant( "aaa" ) ) );


    chain.add( set_value_command( *active_session, sheet_point( 8, 0 ) ,  "=FINV(A6;A7;A8)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 8, 0 ) ) );



    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[4], 15.20686486, tolerance );
    TEST_GET_VALUE( chain[9], variant( variant::error_value ) );

}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_fisher_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 0.75 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  "=FISHER(A2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=FISHER(0.75)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=FISHER(A3)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "aaa" ) );

    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  "=FISHER(A6)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 0 ) ) );




    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[2], 0.972955075, tolerance );
    TEST_GET_CLOSE( chain[4], 0.972955075, tolerance );
    TEST_GET_CLOSE( chain[6], 2.144894173, tolerance );
    TEST_GET_VALUE( chain[9], variant( variant::error_value ) );

}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_fisherinv_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 0.972955075 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  "=FISHERINV(A2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=FISHERINV(0.972955075)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=FISHERINV(A3)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "aaa" ) );

    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  "=FISHERINV(A6)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 0 ) ) );




    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[2], 0.749999967, tolerance );
    TEST_GET_CLOSE( chain[4], 0.749999967, tolerance );
    TEST_GET_CLOSE( chain[6], 0.635148933, tolerance );
    TEST_GET_VALUE( chain[9], variant( variant::error_value ) );

}


/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_gammadist_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 10.00001131 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 9.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( 2.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=GAMMADIST(A2;A3;A4;FALSE)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=GAMMADIST(A2;A3;A4;TRUE)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  variant( 10.00001131 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) ,  variant( 9.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 8, 0 ) ,  variant( "aaa" ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 9, 0 ) ,  "=GAMMADIST(A7;A8;A9;TRUE)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 9, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 10, 0 ) ,  "=GAMMADIST(A7;A8;A9;FALSE)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 10, 0 ) ) );




    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[4], 0.03263913, tolerance );
    TEST_GET_CLOSE( chain[6], 0.068094, tolerance );
    TEST_GET_VALUE( chain[11], variant( variant::error_value ) );
    TEST_GET_VALUE( chain[13], variant( variant::error_value ) );

}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_gammainv_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 0.068094 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 9.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( 2.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=GAMMAINV(A2;A3;A4)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  variant( 0.068094 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) ,  variant( 9.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 8, 0 ) ,  variant( "aaa" ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 9, 0 ) ,  "=GAMMAINV(A7;A8;A9)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 9, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[4], 10.00001131, tolerance );
    TEST_GET_VALUE( chain[9], variant( variant::error_value ) );

}


/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_gammaln_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 4.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  "=GAMMALN(A2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=GAMMALN(4)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  variant( "aaa" ) ) );


    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=GAMMALN(A5)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[2], 1.791759469, tolerance );
    TEST_GET_CLOSE( chain[4], 1.791759469, tolerance );
    TEST_GET_VALUE( chain[7], variant( variant::error_value ) );

}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_hypgeomdist_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( 8.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  variant( 20.0 ) ) );


    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=HYPGEOMDIST(A2;A3;A4;A5)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 8, 0 ) ,  variant( 8.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 9, 0 ) ,  variant( "aaa" ) ) );


    chain.add( set_value_command( *active_session, sheet_point( 10, 0 ) ,  "=HYPGEOMDIST(A7;A8;A9;A10)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 10, 0 ) ) );



    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[5], 0.363261094, tolerance );
    TEST_GET_VALUE( chain[11], variant( variant::error_value ) );

}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_negbinomdist_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 10.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( 0.25 ) ) );


    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=NEGBINOMDIST(A2;A3;A4)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) ,  variant( "aaa" ) ) );


    chain.add( set_value_command( *active_session, sheet_point( 8, 0 ) ,  "=NEGBINOMDIST(A6;A7;A8)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 8, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 9, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 10, 0 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 11, 0 ) ,  variant( 2.0 ) ) );


    chain.add( set_value_command( *active_session, sheet_point( 12, 0 ) ,  "=NEGBINOMDIST(A10;A11;A12)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 12, 0 ) ) );


    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[4], 0.05504866, tolerance );
    TEST_GET_VALUE( chain[9], variant( variant::error_value ) );
    TEST_GET_VALUE( chain[14], variant( variant::error_num ) );

}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_poisson_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 5.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=POISSON(A2;A3;TRUE)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=POISSON(A2;A3;FALSE)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  variant( "aaa" ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) ,  "=POISSON(A6;A7;TRUE)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 7, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 8, 0 ) ,  "=POISSON(A6;A7;FALSE)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 8, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 9, 0 ) ,  variant( -2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 10, 0 ) ,  variant( 5.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 11, 0 ) ,  "=POISSON(A10;A11;TRUE)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 11, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 12, 0 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 13, 0 ) ,  variant( -5.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 14, 0 ) ,  "=POISSON(A13;A14;FALSE)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 14, 0 ) ) );


    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[3], 0.124652019, tolerance );
    TEST_GET_CLOSE( chain[5], 0.084224337, tolerance );
    TEST_GET_VALUE( chain[9], variant( variant::error_value ) );
    TEST_GET_VALUE( chain[11], variant( variant::error_value ) );
    TEST_GET_VALUE( chain[15], variant( variant::error_num ) );
    TEST_GET_VALUE( chain[19], variant( variant::error_num ) );

}


/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_tdist_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 1.959999998 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 60.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=TDIST(A2;A3;2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=TDIST(A2;A3;1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=TDIST(A2;A3;3)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  variant( 1.959999998 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) ,  variant( "aaa" ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 8, 0 ) ,  "=TDIST(A7;A8;2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 8, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 9, 0 ) ,  variant( 1.959999998 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 10, 0 ) ,  variant( -60.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 11, 0 ) ,  "=TDIST(A10;A11;2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 11, 0 ) ) );


    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[3], 0.054644927, tolerance );
    TEST_GET_CLOSE( chain[5], 0.027322464, tolerance );
    TEST_GET_VALUE( chain[7], variant( variant::error_num ) );
    TEST_GET_VALUE( chain[11], variant( variant::error_value ) );
    TEST_GET_VALUE( chain[15], variant( variant::error_num ) );

}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_tinv_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 0.054644927 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 60.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=TINV(A2;A3)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  variant( 0.054644927 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  variant( "aaa" ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  "=TINV(A5;A6)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) ,  variant( 0.054644927 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 8, 0 ) ,  variant( -60.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 9, 0 ) ,  "=TINV(A8;A9)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 9, 0 ) ) );


    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[3], 1.959999998, tolerance );
    TEST_GET_VALUE( chain[7], variant( variant::error_value ) );
    TEST_GET_VALUE( chain[11], variant( variant::error_num ) );

}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_ttest_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  variant( 8.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  variant( 9.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 8, 0 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 9, 0 ) ,  variant( 5.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 1, 1 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 1 ) ,  variant( 19.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 1 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 1 ) ,  variant( 14.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 6, 1 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 7, 1 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 8, 1 ) ,  variant( 17.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 9, 1 ) ,  variant( 1.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 10, 0 ) ,  "=TTEST(A2:A10;B2:B10;2;1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 10, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 11, 0 ) ,  "=TTEST(A2:A10;B2:B10;4;1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 11, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 11, 0 ) ,  "=TTEST(A2:A10;B2:B10;2;-1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 11, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 12, 0 ) ,  "=TTEST(A2:A10;B2:B9;2;1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 12, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 13, 0 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 14, 0 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 15, 0 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 16, 0 ) ,  variant( 8.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 17, 0 ) ,  variant( 9.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 18, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 19, 0 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 20, 0 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 21, 0 ) ,  variant( "aaa" ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 13, 1 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 14, 1 ) ,  variant( 19.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 15, 1 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 16, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 17, 1 ) ,  variant( 14.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 18, 1 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 19, 1 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 20, 1 ) ,  variant( 17.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 21, 1 ) ,  variant( 1.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 22, 0 ) ,  "=TTEST(A14:A22;B14:B22;2;1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 22, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[19], 0.196015785, tolerance );
    TEST_GET_VALUE( chain[21], variant( variant::error_num ) );
    TEST_GET_VALUE( chain[23], variant( variant::error_num ) );
    TEST_GET_VALUE( chain[25], variant( variant::error_n_a ) );

    TEST_GET_CLOSE( chain[45], 0.12892407, tolerance );

}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_sum_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( -5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 15.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( 30.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  variant( true ) ) );



    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  "=SUM(3;2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) ,  "=SUM(5;15;TRUE)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 7, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 8, 0 ) ,  "=SUM(A2:A4)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 8, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 9, 0 ) ,  "=SUM(A2:A4;15)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 9, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 10, 0 ) ,  "=SUM(A5:A6;2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 10, 0 ) ) );


    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[6], 5.0, tolerance );
    TEST_GET_CLOSE( chain[8], 21.0, tolerance );
    TEST_GET_CLOSE( chain[10], 40.0, tolerance );
    TEST_GET_CLOSE( chain[12], 55.0, tolerance );
    TEST_GET_CLOSE( chain[14], 7.0, tolerance );


}
/*!
 * \brief
 *
 * \author
 * Radu Racariu <radu@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_standardize )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) , variant( 42.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) , variant( 40.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) , variant( 1.5 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) , "=standardize(A1;A2;A3)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );
    chain.execute();

    const double tolerance = 0.0001;
    TEST_GET_CLOSE( chain[4], 1.333333, tolerance );

}
/*!
 * \brief
 *
 * \author
 * Radu Racariu <radu@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_round )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) , "=ROUND(2.15; 1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 0, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) , "=ROUND(2.149; 1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) , "=ROUND(-1.475; 2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) , "=ROUND(21.5; -1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );
    chain.execute();

    const double tolerance = 0.1;
    TEST_GET_CLOSE( chain[1], 2.2, tolerance );
    TEST_GET_CLOSE( chain[3], 2.1, tolerance );
    TEST_GET_CLOSE( chain[5], -1.48, tolerance );
    TEST_GET_CLOSE( chain[7], 20.0, tolerance );

}

/*!
 * \brief
 *
 * \author
 * Radu Racariu <radu@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_syd )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) , variant( 30000.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) , variant( 7500.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) , variant( 10.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) , "=SYD(A1;A2;A3;1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) , "=SYD(A1;A2;A3;10)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );
    chain.execute();

    const double tolerance = 0.01;
    TEST_GET_CLOSE( chain[4], 4090.91, tolerance );
    TEST_GET_CLOSE( chain[6], 409.09, tolerance );
}

/*!
 * \brief
 *
 * \author
 * Radu Racariu <radu@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_sln )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) , variant( 30000.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) , variant( 7500.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) , variant( 10.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) , "=SLN(A1;A2;A3)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );
    chain.execute();

    const double tolerance = 0.01;
    TEST_GET_CLOSE( chain[4], 2250.0, tolerance );
}

/*!
 * \brief
 *
 * \author
 * Radu Racariu <radu@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_ddb )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) , variant( 2400.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) , variant( 300.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) , variant( 10.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) , "=DDB(A1;A2;A3*365;1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) , "=DDB(A1;A2;A3*12;1;2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) , "=DDB(A1;A2;A3;1;2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) , "=DDB(A1;A2;A3;2;1.5)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) , "=DDB(A1;A2;A3;10)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 7, 0 ) ) );

    chain.execute();

    const double tolerance = 0.1;
    TEST_GET_CLOSE( chain[4], 1.315, tolerance );
    TEST_GET_CLOSE( chain[6], 40.00, tolerance );
    TEST_GET_CLOSE( chain[8], 480.00, tolerance );
    TEST_GET_CLOSE( chain[10], 306.00, tolerance );
    TEST_GET_CLOSE( chain[12], 22.12, tolerance );
}

/*!
 * \brief
 *
 * \author
 * Radu Racariu <radu@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_db )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) , variant( 1000000.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) , variant( 100000.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) , variant( 6.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) , "=DB(A1;A2;A3;1;7)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) , "=DB(A1;A2;A3;2;7)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) , "=DB(A1;A2;A3;3;7)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) , "=DB(A1;A2;A3;4;7)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) , "=DB(A1;A2;A3;5;7)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 7, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 8, 0 ) , "=DB(A1;A2;A3;6;7)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 8, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 9, 0 ) , "=DB(A1;A2;A3;7;7)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 9, 0 ) ) );

    chain.execute();

    const double tolerance = 0.1;
    TEST_GET_CLOSE( chain[4], 186083.33, tolerance );
    TEST_GET_CLOSE( chain[6], 259639.42, tolerance );
    TEST_GET_CLOSE( chain[8], 176814.44, tolerance );
    TEST_GET_CLOSE( chain[10], 120410.64, tolerance );
    TEST_GET_CLOSE( chain[12], 81999.64, tolerance );
    TEST_GET_CLOSE( chain[14], 55841.76, tolerance );
    TEST_GET_CLOSE( chain[16], 15845.10, tolerance );
}

/*!
 * \brief
 *
 * \author
 * Radu Racariu <radu@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_atanh )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) , "=ATANH(0.76159416)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 0, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) , "=ATANH(-0.1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 0 ) ) );

    chain.execute();

    const double tolerance = 0.001;
    TEST_GET_CLOSE( chain[1], 1.0, tolerance );
    TEST_GET_CLOSE( chain[3], -0.1003353, tolerance );
}

/*!
 * \brief
 *
 * \author
 * Radu Racariu <radu@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_asinh )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) , "=ASINH(-2.5)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 0, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) , "=ASINH(10)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 0 ) ) );

    chain.execute();

    const double tolerance = 0.001;
    TEST_GET_CLOSE( chain[1], -1.64723, tolerance );
    TEST_GET_CLOSE( chain[3], 2.998223, tolerance );
}

/*!
 * \brief
 *
 * \author
 * Radu Racariu <radu@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_acosh )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) , "=ACOSH(1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 0, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) , "=ACOSH(10)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 0 ) ) );

    chain.execute();

    const double tolerance = 0.001;
    TEST_GET_CLOSE( chain[1], 0.0, tolerance );
    TEST_GET_CLOSE( chain[3], 2.9932, tolerance );
}

/*!
 * \brief
 *
 * \author
 * Radu Racariu <radu@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_fv )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) , variant( 0.005 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) , variant( 10.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) , variant( -200.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) , variant( -500.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) , variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) , "=FV(A1; A2; A3; A4; A5)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.execute();

    const double tolerance = 0.01;
    TEST_GET_CLOSE( chain[6], 2581.40, tolerance );
}

/*!
 * \brief
 *
 * \author
 * Radu Racariu <radu@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_address )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) , "=ADDRESS(2;3)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 0, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) , "=ADDRESS(2;3;2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) , "=ADDRESS(2;3;2;FALSE)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) , "=ADDRESS(2;3;1;FALSE;\"[Book1]Sheet1\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) , "=ADDRESS(2;3;1;FALSE;\"EXCEL SHEET\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.execute();

    TEST_GET_VALUE( chain[1], variant( "$C$2" ) );
    TEST_GET_VALUE( chain[3], variant( "C$2" ) );
    TEST_GET_VALUE( chain[5], variant( "R2C[3]" ) );
    TEST_GET_VALUE( chain[7], variant( "[Book1]Sheet1!R2C3" ) );
    TEST_GET_VALUE( chain[9], variant( "EXCEL SHEET!R2C3" ) );
}

/*!
 * \brief
 *
 * \author
 * Radu Racariu <radu@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_tanh )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) , "=TANH(-2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 0, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) , "=TANH(0)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) , "=TANH(0.5)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 0 ) ) );

    chain.execute();

    const double tolerance = 0.001;
    TEST_GET_CLOSE( chain[1], -0.96403, tolerance );
    TEST_GET_CLOSE( chain[3], 0.0, tolerance );
    TEST_GET_CLOSE( chain[5], 0.462117, tolerance );
}

/*!
 * \brief
 *
 * \author
 * Radu Racariu <radu@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_sinh )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) , "=SINH(1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 0, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) , "=SINH(-1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 0 ) ) );

    chain.execute();

    const double tolerance = 0.001;
    TEST_GET_CLOSE( chain[1], 1.175201194, tolerance );
    TEST_GET_CLOSE( chain[3], -1.175201194, tolerance );
}

/*!
 * \brief
 *
 * \author
 * Radu Racariu <radu@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_cosh )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) , "=COSH(4)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 0, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) , "=COSH(EXP(1))" ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 0 ) ) );

    chain.execute();

    const double tolerance = 0.001;
    TEST_GET_CLOSE( chain[1], 27.30823, tolerance );
    TEST_GET_CLOSE( chain[3], 7.610125, tolerance );
}

/*!
 * \brief
 *
 * \author
 * Radu Racariu <radu@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_type )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) , variant( "foo" ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) , "=TYPE(A1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) , "=TYPE(\"bar \" & A1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) , "=TYPE(2.0 + A1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) , "=TYPE({1.0,2.0;3.0,4.0} )" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.execute();

    TEST_GET_VALUE( chain[2], variant( 2.0 ) );
    TEST_GET_VALUE( chain[4], variant( 2.0 ) );
    TEST_GET_VALUE( chain[6], variant( 16.0 ) );
    TEST_GET_VALUE( chain[8], variant( 64.0 ) );

}
/*!
 * \brief
 *
 * \author
 * Radu Racariu <radu@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_permut )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) , variant( 100.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) , variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) , "=PERMUT(A1;A2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );

    chain.execute();

    TEST_GET_VALUE( chain[3], variant( 970200.0 ) );
}

/*!
 * \brief
 *
 * \author
 * Radu Racariu <radu@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_fact )
{

    command_chain chain;


    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) , "=FACT(5.0)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 0, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) , "=FACT(1.9)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) , "=FACT(0.0)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) , "=FACT(-1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) , "=FACT(1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.execute();

    TEST_GET_VALUE( chain[1], variant( 120.0 ) );
    TEST_GET_VALUE( chain[3], variant( 1.0 ) );
    TEST_GET_VALUE( chain[5], variant( 1.0 ) );
    TEST_GET_VALUE( chain[7], variant( variant::error_num ) );
    TEST_GET_VALUE( chain[9], variant( 1.0 ) );
}

/*!
 * \brief
 *
 * \author
 * Radu Racariu <radu@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_radians )
{

    command_chain chain;


    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) , "=RADIANS(270.0)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 0, 0 ) ) );

    chain.execute();

    const double tolerance = 0.00001;
    TEST_GET_CLOSE( chain[1], 4.712389, tolerance );
}

/*!
 * \brief
 *
 * \author
 * Radu Racariu <radu@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_degrees )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) , "=DEGREES(3.14159265)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 0, 0 ) ) );

    chain.execute();

    const double tolerance = 0.01;
    TEST_GET_CLOSE( chain[1], 180.0, tolerance );
}

/*!
 * \brief
 *
 * \author
 * Radu Racariu <radu@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_frequency )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) , variant( 79.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) , variant( 85.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) , variant( 78.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) , variant( 85.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) , variant( 50.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) , variant( 81.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) , variant( 95.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) , variant( 88.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 8, 0 ) , variant( 97.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 0, 1 ) , variant( 70.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 1 ) , variant( 79.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 1 ) , variant( 89.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 9, 0 ) , "=FREQUENCY(A1:A9;B1:B3)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 9, 0 ) ) );

    chain.execute();

    variant test_result( variant::type_array );
    variant::sparse_array_type& test_array = test_result.array();

    test_array.push_back( variant( 1.0 ) );
    test_array.push_back( variant( 2.0 ) );
    test_array.push_back( variant( 4.0 ) );
    test_array.push_back( variant( 2.0 ) );

    TEST_GET_VALUE( chain[13], test_result );
}
/*!
 * \brief
 *
 * \author
 * Radu Racariu <radu@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_choose )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) , variant( "foo" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) , variant( "bar" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) , variant( "baz" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) , variant( "booze" ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 0, 1 ) , variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 1 ) , variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 1 ) , variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 1 ) , variant( 4.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) , "=CHOOSE(2;A1;A2;A3;A4)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) , "=CHOOSE(4;B1;B2;B3;B4)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.execute();

    TEST_GET_VALUE( chain[9], variant( "bar" ) );
    TEST_GET_VALUE( chain[11], variant( 4.0 ) );
}
/*!
 * \brief
 *
 * \author
 * Radu Racariu <radu@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_row )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) , "=ROW()" ) );
    chain.add( get_value_command( *active_session, sheet_point( 0, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) , "=ROW(C10)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 0 ) ) );

    chain.execute();

    TEST_GET_VALUE( chain[1], variant( 1.0 ) );
    TEST_GET_VALUE( chain[3], variant( 10.0 ) );
}
/*!
 * \brief
 *
 * \author
 * Radu Racariu <radu@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_column )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) , "=COLUMN()" ) );
    chain.add( get_value_command( *active_session, sheet_point( 0, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) , "=COLUMN(C10)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 0 ) ) );

    chain.execute();

    TEST_GET_VALUE( chain[1], variant( 1.0 ) );
    TEST_GET_VALUE( chain[3], variant( 3.0 ) );

}
/*!
 * \brief
 *
 * \author
 * Radu Racariu <radu@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_columns )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) , "=COLUMNS(C1:E4)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 0, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) , "=COLUMNS( {1,2;4,5} )" ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 0 ) ) );

    chain.execute();

    TEST_GET_VALUE( chain[1], variant( 3.0 ) );
    TEST_GET_VALUE( chain[3], variant( 2.0 ) );

}
/*!
 * \brief
 *
 * \author
 * Radu Racariu <radu@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_rows )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) , "=ROWS(C1:E4)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 0, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) , "=ROWS({1,2;4,5})" ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 0 ) ) );

    chain.execute();

    TEST_GET_VALUE( chain[1], variant( 4.0 ) );
    TEST_GET_VALUE( chain[3], variant( 2.0 ) );
}
/*!
 * \brief
 *
 * \author
 * Radu Racariu <radu@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_isref )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) , "= C1 + C2" ) );
    chain.add( get_value_command( *active_session, sheet_point( 0, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) , "=ISREF(A1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) , "=ISREF(1+2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );

    chain.execute();

    TEST_GET_VALUE( chain[3], variant( true ) );
    TEST_GET_VALUE( chain[5], variant( false ) );
}
/*!
 * \brief
 *
 * \author
 * Radu Racariu <radu@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_countif )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) , variant( "foo" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) , variant( "bar" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) , variant( "bar" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) , variant( "booze" ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 0, 1 ) , variant( "1" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 1 ) , variant( "2" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 1 ) , variant( "3" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 1 ) , variant( "1" ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) , "=COUNTIF( A1:A4;\"bar\" )" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) , "=COUNTIF( A1:A4; A4 )" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) , "=COUNTIF(B1:B4;\">1\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) , "=COUNTIF(B1:B4;\"<>\"&B4)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 7, 0 ) ) );

    chain.execute();

    TEST_GET_VALUE( chain[9], variant( 2.0 ) );
    TEST_GET_VALUE( chain[11], variant( 1.0 ) );
    TEST_GET_VALUE( chain[13], variant( 2.0 ) );
    TEST_GET_VALUE( chain[15], variant( 2.0 ) );
}
/*!
 * \brief
 *
 * \author
 * Radu Racariu <radu@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_sumif )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) , variant( 100000.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) , variant( 200000.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) , variant( 300000.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) , variant( 400000.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 0, 1 ) , variant( 7000.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 1 ) , variant( 14000.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 1 ) , variant( 21000.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 1 ) , variant( 28000.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) , "=SUMIF(A1:A4; \">160000.0\";B1:B4)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) , "=SUMIF(A1:A4;\">160000.0\" )" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) , "=SUMIF(A1:A4;300000.0;B1:B4)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) , "=SUMIF(A1:A4;\">\" & 250000.0;B1:B4)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 7, 0 ) ) );

    chain.execute();

    TEST_GET_VALUE( chain[9], variant( 63000.0 ) );
    TEST_GET_VALUE( chain[11], variant( 900000.0 ) );
    TEST_GET_VALUE( chain[13], variant( 21000.0 ) );
    TEST_GET_VALUE( chain[15], variant( 49000.0 ) );
}
/*!
 * \brief
 *
 * \author
 * Radu Racariu <radu@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_code )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) , "=CODE(\"A\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) , "=CODE(\"!\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );

    chain.execute();

    TEST_GET_VALUE( chain[1], variant( 65.0 ) );
    TEST_GET_VALUE( chain[3], variant( 33.0 ) );
}
/*!
 * \brief
 *
 * \author
 * Radu Racariu <radu@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_char )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) , "=CHAR(65)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) , "=CHAR(33)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );

    chain.execute();

    TEST_GET_VALUE( chain[1], variant( "A" ) );
    TEST_GET_VALUE( chain[3], variant( "!" ) );
}
/*!
 * \brief
 *
 * \author
 * Radu Racariu <radu@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_percentile )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 1 ) , variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 1 ) , variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 1 ) , variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 1 ) , variant( 4.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) , "=PERCENTILE(B1:B4;0.3)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.execute();

    const double tolerance = 0.01;
    TEST_GET_CLOSE( chain[5], 1.9, tolerance );
}
/*!
 * \brief
 *
 * \author
 * Radu Racariu <radu@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_quartile )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 1 ) , variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 1 ) , variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 1 ) , variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 1 ) , variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 1 ) , variant( 8.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 1 ) , variant( 9.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 6, 1 ) , variant( 10.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 7, 1 ) , variant( 12.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) , "=QUARTILE(B1:B8;1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.execute();

    TEST_GET_VALUE( chain[9], 3.5 );
}
/*!
 * \brief
 *
 * \author
 * Radu Racariu <radu@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_median )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 1 ) , variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 1 ) , variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 1 ) , variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 1 ) , variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 1 ) , variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 1 ) , variant( 6.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) , "=MEDIAN(B1:B5)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) , "=MEDIAN(B1:B6)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.execute();

    TEST_GET_VALUE( chain[7], 3.0 );
    TEST_GET_VALUE( chain[9], 3.5 );
}
/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_sumsq_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( -5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 15.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( 30.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  variant( "'5" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  variant( true ) ) );



    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  "=SUMSQ(3;2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) ,  "=SUMSQ(5;15;TRUE)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 7, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 8, 0 ) ,  "=SUMSQ(A2:A4)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 8, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 9, 0 ) ,  "=SUMSQ(A2:A4;15)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 9, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 10, 0 ) ,  "=SUMSQ(A5:A6;2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 10, 0 ) ) );


    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[6], 13.0, tolerance );
    TEST_GET_CLOSE( chain[8], 251.0, tolerance );
    TEST_GET_CLOSE( chain[10], 1150.0, tolerance );
    TEST_GET_CLOSE( chain[12], 1375.0, tolerance );
    TEST_GET_CLOSE( chain[14], 4.0, tolerance );


}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_sumproduct_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 8.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 1 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 1 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 1 ) ,  variant( 9.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 1, 2 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 2 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 2 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 3 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 3 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 3 ) ,  variant( 3.0 ) ) );


    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=SUMPRODUCT(A2:B4;C2:D4)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );



    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[13], 156.0, tolerance );


}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_maxa_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 0.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 0.2 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( 0.5 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  variant( 0.4 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  variant( true ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  variant( false ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) ,  "=MAXA(A2:A7)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 7, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[7], 1.0, tolerance );


}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_mina_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 0.1 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 0.2 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( 0.5 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  variant( 0.4 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  variant( false ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  variant( true ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) ,  "=MINA(A2:A7)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 7, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[7], 0.0, tolerance );

}


/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_product_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 8.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 1 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 1 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 1 ) ,  variant( 9.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 1, 2 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 2 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 2 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 3 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 3 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 3 ) ,  variant( 3.0 ) ) );


    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=PRODUCT(A2:B4;C2:D4)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=PRODUCT(A2:B4;C2:D4;2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  "=PRODUCT(2;3;\"ss\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) ,  "=PRODUCT(2;3;\"4\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 7, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[13], 45722880.0, tolerance );
    TEST_GET_CLOSE( chain[15], 91445760.0, tolerance );
    TEST_GET_VALUE( chain[17], variant( variant::error_value ) );
    TEST_GET_CLOSE( chain[19], 24.0, tolerance );

}


/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_geomean_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 8.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 1 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 1 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 1 ) ,  variant( 9.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 1, 2 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 2 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 2 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 3 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 3 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 3 ) ,  variant( 3.0 ) ) );


    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=GEOMEAN(A2:B4;C2:D4)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=GEOMEAN(A2:B4;C2:D4;2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  "=GEOMEAN(2;3;\"ss\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) ,  "=GEOMEAN(2;3;\"4\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 7, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[13], 4.348549968, tolerance );
    TEST_GET_CLOSE( chain[15], 4.096351334, tolerance );
    TEST_GET_VALUE( chain[17], variant( variant::error_value ) );
    TEST_GET_CLOSE( chain[19], 2.884499141, tolerance );

}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_harmean_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 8.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 1 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 1 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 1 ) ,  variant( 9.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 1, 2 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 2 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 2 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 3 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 3 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 3 ) ,  variant( 3.0 ) ) );


    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=HARMEAN(A2:B4;C2:D4)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=HARMEAN(A2:B4;C2:D4;2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  "=HARMEAN(2;3;\"ss\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) ,  "=HARMEAN(2;3;\"4\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 7, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[13], 3.456395017, tolerance );
    TEST_GET_CLOSE( chain[15], 3.273054251, tolerance );
    TEST_GET_VALUE( chain[17], variant( variant::error_value ) );
    TEST_GET_CLOSE( chain[19], 2.769230769, tolerance );

}


/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_devsq_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( 8.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  variant( 11.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) ,  variant( 3.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 1, 1 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 1 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 1 ) ,  variant( 8.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 1 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 1 ) ,  variant( 11.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 6, 1 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 7, 1 ) ,  variant( 3.0 ) ) );


    chain.add( set_value_command( *active_session, sheet_point( 8, 0 ) ,  "=DEVSQ(A2:A8)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 8, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 9, 0 ) ,  "=DEVSQ(A2:A8;2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 9, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 10, 0 ) ,  "=DEVSQ(2;3;\"ss\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 10, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 11, 0 ) ,  "=DEVSQ(2;3;\"4\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 11, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[15], 48.0, tolerance );
    TEST_GET_CLOSE( chain[17], 62.0, tolerance );
    TEST_GET_VALUE( chain[19], variant( variant::error_value ) );
    TEST_GET_CLOSE( chain[21], 2.0, tolerance );

}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_skew_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 8, 0 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 9, 0 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 10, 0 ) ,  variant( 7.0 ) ) );



    chain.add( set_value_command( *active_session, sheet_point( 11, 0 ) ,  "=SKEW(A2:A11)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 11, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 12, 0 ) ,  "=SKEW(A2:A11;2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 12, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 13, 0 ) ,  "=SKEW(A2:A11;\"hello\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 13, 0 ) ) );


    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[11], 0.359543071, tolerance );
    TEST_GET_CLOSE( chain[13], 0.379240182, tolerance );
    TEST_GET_VALUE( chain[15], variant( variant::error_value ) );

}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_avedev_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) ,  variant( 3.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 8, 0 ) ,  "=AVEDEV(A2:A8)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 8, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 9, 0 ) ,  "=AVEDEV(A2:A8;2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 9, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 10, 0 ) ,  "=AVEDEV(A2:A8;\"hello\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 10, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[8], 1.020408163, tolerance );
    TEST_GET_CLOSE( chain[10], 1.25, tolerance );
    TEST_GET_VALUE( chain[12], variant( variant::error_value ) );


}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_mode_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 5.6 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  variant( 4.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) ,  "=MODE(A2:A7)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 7, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 8, 0 ) ,  "=MODE(A2:A7;3;3;3;2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 8, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 9, 0 ) ,  "=MODE(A2:A7;\"hello\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 9, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[7], 4.0, tolerance );
    TEST_GET_CLOSE( chain[9], 3.0, tolerance );
    TEST_GET_VALUE( chain[11], variant( variant::error_value ) );


}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_prob_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 0.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  variant( 3.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 1, 1 ) ,  variant( 0.2 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 1 ) ,  variant( 0.3 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 1 ) ,  variant( 0.1 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 1 ) ,  variant( 0.4 ) ) );


    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=PROB(A2:A5;B2:B5;2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  "=PROB(A2:A5;B2:B5;\"aaa\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) ,  "=PROB(A2:A5;B2:B5;1;\"3\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 7, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[9], 0.1, tolerance );
    TEST_GET_VALUE( chain[11], variant( variant::error_value ) );
    TEST_GET_CLOSE( chain[13], 0.8, tolerance );

}



/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_normsdist_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 1.23 ) ) );


    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  "=NORMSDIST(A2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=NORMSDIST(1.333333)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=NORMSDIST(\"1.24\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=NORMSDIST(\"aaa\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[2], 0.890651448, tolerance );
    TEST_GET_CLOSE( chain[4], 0.908788726, tolerance );
    TEST_GET_CLOSE( chain[6], 0.892512303, tolerance );
    TEST_GET_VALUE( chain[8], variant( variant::error_value ) );

}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_normdist_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 42.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 40.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( 1.5 ) ) );


    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=NORMDIST(A2;A3;A4;TRUE)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=NORMDIST(A2;A3;A4;FALSE)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  "=NORMDIST(A2;0;1;TRUE)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) ,  "=NORMDIST(A2;A3;A4;\"aaa\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 7, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[4], 0.90878878, tolerance );
    TEST_GET_CLOSE( chain[6], 0.10934005, tolerance );
    TEST_GET_CLOSE( chain[8], 1.0, tolerance );
    TEST_GET_VALUE( chain[10], variant( variant::error_value ) );

}


/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_lognormdist_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 3.5 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( 1.2 ) ) );


    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=LOGNORMDIST(A2;A3;A4)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=LOGNORMDIST(A2;0;-1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  "=LOGNORMDIST(-3;3.5;1.2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) ,  "=LOGNORMDIST(A2;A3;\"1.2\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 7, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[4], 0.039083556, tolerance );
    TEST_GET_VALUE( chain[6], variant( variant::error_num ) );
    TEST_GET_VALUE( chain[8], variant( variant::error_num ) );
    TEST_GET_CLOSE( chain[10], 0.039083556, tolerance );

}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_normsinv_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 0.908789 ) ) );


    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  "=NORMSINV(A2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=NORMSINV(1.333333)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=NORMSINV(\"aaa\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=NORMSINV(\"0.908789\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[2], 1.333334673, tolerance );
    TEST_GET_VALUE( chain[4], variant( variant::error_num ) );
    TEST_GET_VALUE( chain[6], variant( variant::error_value ) );
    TEST_GET_CLOSE( chain[8], 1.333334673, tolerance );

}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_norminv_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 0.908789 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 40.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( 1.5 ) ) );


    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=NORMINV(A2;A3;A4)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=NORMINV(A2;0;-1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  "=NORMINV(-3;3.5;1.2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) ,  "=NORMINV(A2;0;\"1\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 7, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[4], 42.00000201, tolerance );
    TEST_GET_VALUE( chain[6], variant( variant::error_num ) );
    TEST_GET_VALUE( chain[8], variant( variant::error_num ) );
    TEST_GET_CLOSE( chain[10], 1.333334673, tolerance );

}


/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_confidence_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 0.05 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 2.5 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( 50.0 ) ) );


    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=CONFIDENCE(A2;A3;A4)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=CONFIDENCE(A2;2.5;-1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  "=CONFIDENCE(0.05;-2.5;50)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) ,  "=CONFIDENCE(-0.05;2.5;50 )" ) );
    chain.add( get_value_command( *active_session, sheet_point( 7, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[4], 0.692951912, tolerance );
    TEST_GET_VALUE( chain[6], variant( variant::error_num ) );
    TEST_GET_VALUE( chain[8], variant( variant::error_num ) );
    TEST_GET_VALUE( chain[10], variant( variant::error_num ) );

}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_exp_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  "=EXP(1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  "=EXP(2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=EXP(\"-1\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=EXP(A2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=EXP(\"aaa\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[1], 2.718281828, tolerance );
    TEST_GET_CLOSE( chain[3], 7.389056099, tolerance );
    TEST_GET_CLOSE( chain[5], 0.367879441, tolerance );
    TEST_GET_CLOSE( chain[7], 15.15426224, tolerance );
    TEST_GET_VALUE( chain[9], variant( variant::error_value ) );

}


/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_loginv_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 0.039084 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 3.5 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( 1.2 ) ) );


    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=LOGINV(A2;A3;A4)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=LOGINV(A2;\"3.5\";A4)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  "=LOGINV(0.039084;3.5;1.2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) ,  "=LOGINV(-0.39;0;\"1\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 7, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 8, 0 ) ,  "=LOGINV(A2;3.5;-1.2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 8, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[4], 4.000025219, tolerance );
    TEST_GET_CLOSE( chain[6], 4.000025219, tolerance );
    TEST_GET_CLOSE( chain[8], 4.000025219, tolerance );
    TEST_GET_VALUE( chain[10], variant( variant::error_num ) );
    TEST_GET_VALUE( chain[12], variant( variant::error_num ) );


}


/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_countblank_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant() ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant() ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  variant( 4.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 1, 1 ) ,  variant() ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 1 ) ,  variant() ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 1 ) ,  variant( 27.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 1 ) ,  variant( 34.0 ) ) );


    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=COUNTBLANK(A2:B5)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  "=COUNTBLANK(A2;B5)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[9], 4.0, tolerance );
    TEST_GET_VALUE( chain[11], variant( variant::error_ref ) );

}


/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_sqrt_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 16.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( -16.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=SQRT(A2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=SQRT(\"16\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=SQRT(A3)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  "=SQRT(A2;A3)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) ,  "=SQRT(\"aaa\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 7, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[3], 4.0, tolerance );
    TEST_GET_CLOSE( chain[5], 4.0, tolerance );
    TEST_GET_VALUE( chain[7], variant( variant::error_num ) );
    TEST_GET_VALUE( chain[9], variant( variant::error_n_a ) );
    TEST_GET_VALUE( chain[11], variant( variant::error_value ) );

}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_log_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 10.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  "=LOG(A2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=LOG(8; -2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=LOG(86; 2.7182818)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=LOG(\"86\";\"2.7182818\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  "=LOG(86; \"2.sss\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) ,  "=LOG(\"86\"; \"-2.7182818\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 7, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 8, 0 ) ,  "=LOG(-8; 2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 8, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[2], 1.0, tolerance );
    TEST_GET_VALUE( chain[4], variant( variant::error_num ) );
    TEST_GET_CLOSE( chain[6], 4.454347343, tolerance );
    TEST_GET_CLOSE( chain[8], 4.454347343, tolerance );
    TEST_GET_VALUE( chain[10], variant( variant::error_value ) );
    TEST_GET_VALUE( chain[12], variant( variant::error_num ) );
    TEST_GET_VALUE( chain[14], variant( variant::error_num ) );


}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_ln_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 86.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  "=LN(A2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=LN(2.7182818)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=LN(EXP(3))" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=LN(\"2.7182818\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  "=LN(\"2.sss\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) ,  "=LN(-3)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 7, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[2], 4.454347296, tolerance );
    TEST_GET_CLOSE( chain[4], 0.99999999, tolerance );
    TEST_GET_CLOSE( chain[6], 3.0, tolerance );
    TEST_GET_CLOSE( chain[8], 0.99999999, tolerance );
    TEST_GET_VALUE( chain[10], variant( variant::error_value ) );
    TEST_GET_VALUE( chain[12], variant( variant::error_num ) );


}


/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_log10_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 86.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  "=LOG10(A2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=LOG10(10)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=LOG10(100000)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=LOG10(\"100000\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  "=LOG10(\"2.sss\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) ,  "=LOG10(-100000)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 7, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[2], 1.934498451, tolerance );
    TEST_GET_CLOSE( chain[4], 1.0, tolerance );
    TEST_GET_CLOSE( chain[6], 5.0, tolerance );
    TEST_GET_CLOSE( chain[8], 5.0, tolerance );
    TEST_GET_VALUE( chain[10], variant( variant::error_value ) );
    TEST_GET_VALUE( chain[12], variant( variant::error_num ) );

}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_sign_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 86.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  "=SIGN(A2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=SIGN(10)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=SIGN(-0.000001)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=SIGN(4-4)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  "=SIGN(\"2.sss\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[2], 1.0, tolerance );
    TEST_GET_CLOSE( chain[4], 1.0, tolerance );
    TEST_GET_CLOSE( chain[6], -1.0, tolerance );
    TEST_GET_CLOSE( chain[8], 0.0, tolerance );
    TEST_GET_VALUE( chain[10], variant( variant::error_value ) );


}


/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_cos_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 1.047 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  "=COS(A2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=COS(180)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=COS(\"1.047\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=COS(\"2.sss\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  "=PI()" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[2], 0.500171075, tolerance );
    TEST_GET_CLOSE( chain[4], -0.598460069, tolerance );
    TEST_GET_CLOSE( chain[6], 0.500171075, tolerance );
    TEST_GET_VALUE( chain[8], variant( variant::error_value ) );
    TEST_GET_CLOSE( chain[10], 3.141592654, tolerance );



}


/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_sin_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 1.047 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  "=SIN(A2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=SIN(180)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=SIN(\"1.047\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=SIN(\"2.sss\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[2], 0.865926611, tolerance );
    TEST_GET_CLOSE( chain[4], -0.801152636, tolerance );
    TEST_GET_CLOSE( chain[2], 0.865926611, tolerance );
    TEST_GET_VALUE( chain[8], variant( variant::error_value ) );


}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_abs_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( -4.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  "=ABS(A2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=ABS(-2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=ABS(\"-2\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=ABS(\"2.sss\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[2], 4.0, tolerance );
    TEST_GET_CLOSE( chain[4], 2.0, tolerance );
    TEST_GET_CLOSE( chain[6], 2.0, tolerance );
    TEST_GET_VALUE( chain[8], variant( variant::error_value ) );


}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_tan_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 0.785 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  "=TAN(A2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=TAN(180)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=TAN(\"sss\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[2], 0.99920399, tolerance );
    TEST_GET_CLOSE( chain[4], 1.33869021, tolerance );
    TEST_GET_VALUE( chain[6], variant( variant::error_value ) );


}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_acos_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( -0.5 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  "=ACOS(A2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=ACOS(0.5)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=ACOS(\"sss\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[2], 2.094395102, tolerance );
    TEST_GET_CLOSE( chain[4], 1.047197551, tolerance );
    TEST_GET_VALUE( chain[6], variant( variant::error_value ) );


}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_asin_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( -0.5 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  "=ASIN(A2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=ASIN(0.5)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=ASIN(\"sss\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[2], -0.523598776, tolerance );
    TEST_GET_CLOSE( chain[4], 0.523598776, tolerance );
    TEST_GET_VALUE( chain[6], variant( variant::error_value ) );


}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_atan_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 1.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  "=ATAN(A2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=ATAN(-1.0)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=ATAN(\"sss\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[2], 0.785398163, tolerance );
    TEST_GET_CLOSE( chain[4], -0.785398163, tolerance );
    TEST_GET_VALUE( chain[6], variant( variant::error_value ) );


}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_atan2_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 1.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=ATAN2(A2;A3)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=ATAN2(-1.0;-1.0)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=ATAN2(\"sss\"; 1.0)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[3], 0.785398163, tolerance );
    TEST_GET_CLOSE( chain[5], -2.35619449, tolerance );
    TEST_GET_VALUE( chain[7], variant( variant::error_value ) );

}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_mod_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 2.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=MOD(A2;A3)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=MOD(-3;2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=MOD(\"sss\"; 1.0)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[3], 1.0, tolerance );
    TEST_GET_CLOSE( chain[5], 1.0, tolerance );
    TEST_GET_VALUE( chain[7], variant( variant::error_value ) );


}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_power_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 2.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=POWER(A2;A3)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=POWER(98.6;3.2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=POWER(4;5/4)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  "=POWER(\"ddd\";5/4)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[3], 25.0, tolerance );
    TEST_GET_CLOSE( chain[5], 2401077.222, tolerance );
    TEST_GET_CLOSE( chain[7], 5.656854249, tolerance );
    TEST_GET_VALUE( chain[9], variant( variant::error_value ) );


}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_int_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 19.5 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 2.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=INT(A2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=INT(8.9)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=INT(-8.9)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  "=INT(\"ddd\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[3], 19.0, tolerance );
    TEST_GET_CLOSE( chain[5], 8.0, tolerance );
    TEST_GET_CLOSE( chain[7], -9.0, tolerance );
    TEST_GET_VALUE( chain[9], variant( variant::error_value ) );


}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_isnumber_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 19.5 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( "sss" ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=ISNUMBER(A2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=ISNUMBER(A3)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_VALUE( chain[3], variant( true ) );
    TEST_GET_VALUE( chain[5], variant( false ) );


}


/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_istext_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 19.5 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( "sss" ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=ISTEXT(A2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=ISTEXT(A3)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_VALUE( chain[3], variant( false ) );
    TEST_GET_VALUE( chain[5], variant( true ) );


}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_proper_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( "this is a TITLE" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( "2-cent's worth" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( "76BudGet" ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=PROPER(A2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=PROPER(A3)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=PROPER(A4)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_VALUE( chain[4], variant( "This Is A Title" ) );
    TEST_GET_VALUE( chain[6], variant( "2-Cent'S Worth" ) );
    TEST_GET_VALUE( chain[8], variant( "76Budget" ) );


}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_upper_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( "total" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( "Yield" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( "76BudGet" ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=UPPER(A2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=UPPER(A3)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=UPPER(A4)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_VALUE( chain[4], variant( "TOTAL" ) );
    TEST_GET_VALUE( chain[6], variant( "YIELD" ) );
    TEST_GET_VALUE( chain[8], variant( "76BUDGET" ) );


}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_lower_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( "E. E. Cummings" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( "Apt. 2B" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( "76BudGet" ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=LOWER(A2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=LOWER(A3)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=LOWER(A4)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_VALUE( chain[4], variant( "e. e. cummings" ) );
    TEST_GET_VALUE( chain[6], variant( "apt. 2b" ) );
    TEST_GET_VALUE( chain[8], variant( "76budget" ) );


}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_even_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 1.5 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( 2.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=EVEN(A2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=EVEN(A3)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  "=EVEN(A4)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[4], 2.0, tolerance );
    TEST_GET_CLOSE( chain[6], 4.0, tolerance );
    TEST_GET_CLOSE( chain[8], 2.0, tolerance );


}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_odd_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 1.5 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( 2.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=ODD(A2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=ODD(A3)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  "=ODD(A4)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[4], 3.0, tolerance );
    TEST_GET_CLOSE( chain[6], 3.0, tolerance );
    TEST_GET_CLOSE( chain[8], 3.0, tolerance );


}




/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_roundup_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  "=ROUNDUP(3.2;0)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  "=ROUNDUP(76.9;0)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=ROUNDUP(3.14159;3)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=ROUNDUP(-3.14159;1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=ROUNDUP(31415.92654;-2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  "=ROUNDUP(\"ssss\";1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[1], 4.0, tolerance );
    TEST_GET_CLOSE( chain[3], 77.0, tolerance );
    TEST_GET_CLOSE( chain[5], 3.142, tolerance );
    TEST_GET_CLOSE( chain[7], -3.2, tolerance );
    TEST_GET_CLOSE( chain[9], 31500.0, tolerance );
    TEST_GET_VALUE( chain[11], variant( variant::error_value ) );


}


/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_rounddown_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  "=ROUNDDOWN(3.2;0)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  "=ROUNDDOWN(76.9;0)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=ROUNDDOWN(3.14159;3)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=ROUNDDOWN(-3.14159;1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=ROUNDDOWN(31415.92654;-2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  "=ROUNDDOWN(\"ssss\";1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[1], 3.0, tolerance );
    TEST_GET_CLOSE( chain[3], 76.0, tolerance );
    TEST_GET_CLOSE( chain[5], 3.141, tolerance );
    TEST_GET_CLOSE( chain[7], -3.1, tolerance );
    TEST_GET_CLOSE( chain[9], 31400.0, tolerance );
    TEST_GET_VALUE( chain[11], variant( variant::error_value ) );


}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_trunc_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  "=TRUNC(8.9)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  "=TRUNC(-8.9)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=TRUNC(0.1+LOG10(10))" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=TRUNC(\"sss\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[1], 8.0, tolerance );
    TEST_GET_CLOSE( chain[3], -8.0, tolerance );
    TEST_GET_CLOSE( chain[5], 1.0, tolerance );
    TEST_GET_VALUE( chain[7], variant( variant::error_value ) );


}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_count_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( "Sales" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 40197.66 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant() ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  variant( 19.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  variant( 22.24 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  variant( true ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) ,  variant( variant::error_div_null ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 8, 0 ) ,  "=COUNT(A2:A8)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 8, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 9, 0 ) ,  "=COUNT(A5:A8)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 9, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 10, 0 ) ,  "=COUNT(A2:A8;2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 10, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[8], 3.0, tolerance );
    TEST_GET_CLOSE( chain[10], 2.0, tolerance );
    TEST_GET_CLOSE( chain[12], 4.0, tolerance );


}


/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_counta_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) ,  variant( "Data" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( "Sales" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 40197.66 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant() ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  variant( 19.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  variant( 22.24 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  variant( true ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) ,  variant( variant::error_div_null ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 8, 0 ) ,  "=COUNTA(A2:A8)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 8, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 9, 0 ) ,  "=COUNTA(A5:A8)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 9, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 10, 0 ) ,  "=COUNTA(A1:A7;2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 10, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 11, 0 ) ,  "=COUNTA(A1:A7;\"Two\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 11, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[9], 6.0, tolerance );
    TEST_GET_CLOSE( chain[11], 4.0, tolerance );
    TEST_GET_CLOSE( chain[13], 7.0, tolerance );
    TEST_GET_CLOSE( chain[15], 7.0, tolerance );


}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_trimmean_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 8, 0 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 9, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 10, 0 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 11, 0 ) ,  variant( 3.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 12, 0 ) ,  "=TRIMMEAN(A2:A12;0.2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 12, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 13, 0 ) ,  "=TRIMMEAN(A2:B12;0.2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 13, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 14, 0 ) ,  "=TRIMMEAN(A2:B12;\"aaa\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 14, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[12], 3.777777778, tolerance );
    TEST_GET_CLOSE( chain[14], 3.777777778, tolerance );
    TEST_GET_VALUE( chain[16], variant( variant::error_value ) );

}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_exact_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( "word" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( "Word" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( "w ord" ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 1, 1 ) ,  variant( "word" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 1 ) ,  variant( "word" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 1 ) ,  variant( "word" ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=EXACT(A2;B2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  "=EXACT(A3;B3)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) ,  "=EXACT(A4;B4)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 7, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 8, 0 ) ,  "=EXACT(UPPER(A3);UPPER(B3))" ) );
    chain.add( get_value_command( *active_session, sheet_point( 8, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_VALUE( chain[7], variant( true ) );
    TEST_GET_VALUE( chain[9], variant( false ) );
    TEST_GET_VALUE( chain[11], variant( false ) );
    TEST_GET_VALUE( chain[13], variant( true ) );


}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_large_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  variant( 4.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 1, 1 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 1 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 1 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 1 ) ,  variant( 7.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  "=LARGE(A2:B6;7)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) ,  "=LARGE(A2:B6;3)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 7, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 8, 0 ) ,  "=LARGE(A2:B6;-3)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 8, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 9, 0 ) ,  "=LARGE(A2:B6;12)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 9, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[11], 4.0, tolerance );
    TEST_GET_CLOSE( chain[13], 5.0, tolerance );
    TEST_GET_VALUE( chain[15], variant( variant::error_num ) );
    TEST_GET_VALUE( chain[17], variant( variant::error_num ) );


}


/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_small_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 8, 0 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 9, 0 ) ,  variant( 7.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 1, 1 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 1 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 1 ) ,  variant( 8.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 1 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 1 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 6, 1 ) ,  variant( 12.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 7, 1 ) ,  variant( 54.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 8, 1 ) ,  variant( 8.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 9, 1 ) ,  variant( 23.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 10, 0 ) ,  "=SMALL(A2:A10;4)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 10, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 11, 0 ) ,  "=SMALL(B2:B10;2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 11, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 12, 0 ) ,  "=SMALL(A2:A10;-3)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 12, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 13, 0 ) ,  "=SMALL(B2:B10;12)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 13, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[19], 4.0, tolerance );
    TEST_GET_CLOSE( chain[21], 3.0, tolerance );
    TEST_GET_VALUE( chain[23], variant( variant::error_num ) );
    TEST_GET_VALUE( chain[25], variant( variant::error_num ) );


}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_t_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( "Rainfall" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 19.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( true ) ) );


    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=T(A2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=T(A3)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  "=T(A4)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_VALUE( chain[4], variant( "Rainfall" ) );
    TEST_GET_VALUE( chain[6], variant( "" ) );
    TEST_GET_VALUE( chain[8], variant( "" ) );


}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_floor_test )
{

    command_chain chain;


    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  "=FLOOR(2.5; 1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  "=FLOOR(-2.5; -2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=FLOOR(-2.5; 2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=FLOOR(1.5; 0.1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=FLOOR(0.234; 0.01)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[1], 2.0, tolerance );
    TEST_GET_CLOSE( chain[3], -2.0, tolerance );
    TEST_GET_VALUE( chain[5], variant( variant::error_num ) );
    TEST_GET_CLOSE( chain[7], 1.5, tolerance );
    TEST_GET_CLOSE( chain[9], 0.23, tolerance );


}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_mround_test )
{

    command_chain chain;


    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  "=MROUND(10; 3)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  "=MROUND(-10; -3)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=MROUND(1.3; 0.2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=MROUND(5; -2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[1], 9.0, tolerance );
    TEST_GET_CLOSE( chain[3], -9.0, tolerance );
    TEST_GET_CLOSE( chain[5], 1.4, tolerance );
    TEST_GET_VALUE( chain[7], variant( variant::error_num ) );


}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_trim_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  "=TRIM(\" First Quarter Earnings \")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_VALUE( chain[1], variant( "First Quarter Earnings" ) );

}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_substitute_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( "Sales Data" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( "Quarter 1, 2008" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( "Quarter 1, 2011" ) ) );


    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=SUBSTITUTE(A2; \"Sales\"; \"Cost\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=SUBSTITUTE(A3; \"1\"; \"2\"; 1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  "=SUBSTITUTE(A4; \"1\"; \"2\"; 3)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_VALUE( chain[4], variant( "Cost Data" ) );
    TEST_GET_VALUE( chain[6], variant( "Quarter 2, 2008" ) );
    TEST_GET_VALUE( chain[8], variant( "Quarter 1, 2012" ) );


}


/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_find_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( "Miriam McGovern" ) ) );


    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=FIND(\"M\";A2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=FIND(\"m\";A2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=FIND(\"M\";A2;3)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[2], 1.0, tolerance );
    TEST_GET_CLOSE( chain[4], 6.0, tolerance );
    TEST_GET_CLOSE( chain[6], 8.0, tolerance );


}


/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_mid_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( "Fluid Flow" ) ) );


    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=MID(A2;1;5)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=MID(A2;7;20)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_VALUE( chain[2], variant( "Fluid" ) );
    TEST_GET_VALUE( chain[4], variant( "Flow" ) );


}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_leftb_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( "Sale Price" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( "Sweden" ) ) );


    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=LEFT(A2;4)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=LEFT(A3)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_VALUE( chain[3], variant( "Sale" ) );
    TEST_GET_VALUE( chain[5], variant( "S" ) );


}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_replace_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( "abcdefghijk" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( "2009" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( "123456" ) ) );


    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=REPLACE(A2;6;5;\"*\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=REPLACE(A3;3;2;\"10\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  "=REPLACE(A4;1;3;\"@\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_VALUE( chain[4], variant( "abcde*k" ) );
    TEST_GET_VALUE( chain[6], variant( "2010" ) );
    TEST_GET_VALUE( chain[8], variant( "@456" ) );


}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_rept_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  "=REPT(\"*-\"; 3)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  "=REPT(\"-\";10)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_VALUE( chain[1], variant( "*-*-*-" ) );
    TEST_GET_VALUE( chain[3], variant( "----------" ) );


}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_and_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  "=AND(TRUE; TRUE)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  "=AND(TRUE; FALSE)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=AND(2+2=4; 2+3=5)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_VALUE( chain[1], variant( true ) );
    TEST_GET_VALUE( chain[3], variant( false ) );
    TEST_GET_VALUE( chain[5], variant( true ) );

}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_or_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  "=OR(TRUE)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  "=OR(1+1=1;2+2=5)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  "=OR(TRUE;FALSE;TRUE)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 3, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_VALUE( chain[1], variant( true ) );
    TEST_GET_VALUE( chain[3], variant( false ) );
    TEST_GET_VALUE( chain[5], variant( true ) );

}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_ztest_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  variant( 8.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 8, 0 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 9, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 10, 0 ) ,  variant( 9.0 ) ) );


    chain.add( set_value_command( *active_session, sheet_point( 11, 0 ) ,  "=ZTEST(A2:A11;4)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 11, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 12, 0 ) ,  "=2 * MIN(ZTEST(A2:A11;4); 1 - ZTEST(A2:A11;4))" ) );
    chain.add( get_value_command( *active_session, sheet_point( 12, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 13, 0 ) ,  "=ZTEST(A2:A11;6)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 13, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 14, 0 ) ,  "=PI() * MIN(ZTEST(A2:A11;6); 1 - ZTEST(A2:A11;6))" ) );
    chain.add( get_value_command( *active_session, sheet_point( 14, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[11], 0.090574197, tolerance );
    TEST_GET_CLOSE( chain[13], 0.181148394, tolerance );
    TEST_GET_CLOSE( chain[15], 0.863043389, tolerance );
    TEST_GET_CLOSE( chain[17], 0.430261883, tolerance );

}


/*!
* \brief
*
* \author
* Vali Nitu <vali@yalos-solutions.com>
*/
BOOST_AUTO_TEST_CASE( function_forecast_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( 9.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  variant( 15.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  variant( 21.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 1, 1 ) ,  variant( 20.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 1 ) ,  variant( 28.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 1 ) ,  variant( 31.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 1 ) ,  variant( 38.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 1 ) ,  variant( 40.0 ) ) );


    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  "=FORECAST(30;A2:A6;B2:B6)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) ,  "=FORECAST(\"30\"; A2:A6;B2:B6)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 7, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 8, 0 ) ,  "=FORECAST(\"hhh\";A2:A6;B2:B6)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 8, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[11], 10.60725309, tolerance );
    TEST_GET_CLOSE( chain[13], 10.60725309, tolerance );
    TEST_GET_VALUE( chain[15], variant( variant::error_value ) );

}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_kurt_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 8, 0 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 9, 0 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 10, 0 ) ,  variant( 7.0 ) ) );



    chain.add( set_value_command( *active_session, sheet_point( 11, 0 ) ,  "=KURT(A2:A11)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 11, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 12, 0 ) ,  "=KURT(A2:A11;2)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 12, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 13, 0 ) ,  "=KURT(A2:A11;\"hello\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 13, 0 ) ) );


    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[11], -0.151799637, tolerance );
    TEST_GET_CLOSE( chain[13], -0.404390218, tolerance );
    TEST_GET_VALUE( chain[15], variant( variant::error_value ) );

}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_concat_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( "brook trout" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( "species" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( 32.0 ) ) );


    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=CONCATENATE(\"Stream population for \";A2;\" \";A3;\" is \";A4;\"/mile\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=CONCATENATE(\"Stream population for \";A2:E2;\" \";A3;\" is \";A4;\"/mile\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.execute();


    TEST_GET_VALUE( chain[4], variant( "Stream population for brook trout species is 32/mile" ) );
    TEST_GET_VALUE( chain[6], variant( "Stream population for brook trout species is 32/mile" ) );


}


/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_mmult_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 7.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 1 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 1 ) ,  variant( 2.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  variant( 0.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 1 ) ,  variant( 0.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 5, 1 ) ,  variant( 2.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) , "=MMULT(A2:B3;A5:B6)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 7, 0 ) ) );


    chain.execute();


    variant::sparse_array_type test_array;
    test_array.push_back( variant( 2.0  ) );
    test_array.push_back( variant( 6.0  ) );
    test_array.push_back( variant( 14.0  ) );
    test_array.push_back( variant( 4.0  ) );

    TEST_GET_VALUE( chain[9], variant( test_array ) );

}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_minverse_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( 0.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 1 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 1 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 2 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 2 ) ,  variant( -1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 2 ) ,  variant( 0.0 ) ) );


    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) , "=MINVERSE(A2:C4)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 7, 0 ) ) );


    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    variant::sparse_array_type test_array;
    test_array.push_back( variant( 0.25  ) );
    test_array.push_back( variant( 0.25  ) );
    test_array.push_back( variant( -0.75  ) );
    test_array.push_back( variant( 0.0  ) );
    test_array.push_back( variant( 0.0  ) );
    test_array.push_back( variant( 0.5  ) );
    test_array.push_back( variant( 0.75  ) );
    test_array.push_back( variant( -0.25  ) );
    test_array.push_back( variant( -0.25  ) );

    variant::sparse_array_type result_array = static_cast<const get_value_command&>( chain[10] ).value().array();

    BOOST_CHECK_EQUAL( result_array.size(), test_array.size() );

    size_t imax = result_array.size();
    for ( size_t i = 0; i < imax; i++ ) {
        variant r = result_array[i];
        variant t = test_array[i];

        BOOST_CHECK_CLOSE( r.numeric(), t.numeric(), tolerance );

    }

}


/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_mdeterm_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  variant( 7.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 1, 1 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 1 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 1 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 1 ) ,  variant( 3.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 1, 2 ) ,  variant( 8.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 2 ) ,  variant( 6.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 2 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 2 ) ,  variant( 10.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 1, 3 ) ,  variant( 5.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 3 ) ,  variant( 1.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 3 ) ,  variant( 0.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 3 ) ,  variant( 2.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) , "=MDETERM(A2:D5)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 7, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 8, 0 ) , "=MDETERM(A2:C5)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 8, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[17], 88.0, tolerance );
    TEST_GET_VALUE( chain[19], variant( variant::error_value ) );


}

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_text_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( "abcdefghijk" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( 2009.00 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( "123456.65" ) ) );


    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  "=TEXT(A2;\"###,###.##\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 4, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=TEXT(A3;\"###,##0.00\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  "=TEXT(A4;\"###,###.##\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) ,  "=TEXT(4123.88;\"###,###.##\")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 7, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_VALUE( chain[4], variant( "abcdefghijk" ) );
    TEST_GET_VALUE( chain[6], variant( "2,009.00" ) );
    TEST_GET_VALUE( chain[8], variant( "123,456.65" ) );
    TEST_GET_VALUE( chain[10], variant( "4,123.88" ) );


}


/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */

BOOST_AUTO_TEST_CASE( function_match_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( "Bananas" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  variant( "Oranges" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 0 ) ,  variant( "Apples" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 0 ) ,  variant( "Pears" ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 1, 1 ) ,  variant( 25.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 1 ) ,  variant( 38.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 1 ) ,  variant( 40.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 1 ) ,  variant( 41.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 1, 2 ) ,  variant( 41.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 2 ) ,  variant( 40.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 2 ) ,  variant( 38.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 2 ) ,  variant( 25.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 5, 0 ) ,  "=MATCH(39;B2:B5;1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 5, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  "=MATCH(41;B2:B5;0)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) ,  "=MATCH(40;B2:B5;-1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 7, 0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 8, 0 ) ,  "=MATCH(25;B2:B5;-1)" ) );
    chain.add( get_value_command( *active_session, sheet_point( 8, 0 ) ) );

    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[13], 2.0, tolerance );
    TEST_GET_CLOSE( chain[15], 4.0, tolerance );
    TEST_GET_VALUE( chain[17], variant( variant::error_n_a ) );
    TEST_GET_CLOSE( chain[19], 1.0, tolerance );


}


/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */

BOOST_AUTO_TEST_CASE( function_offset_test )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 2, 2 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 2 ) ,  variant( 2.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 2 ) ,  variant( 5.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 2, 3 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 3 ) ,  variant( 3.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 3 ) ,  variant( 4.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 2, 4 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 3, 4 ) ,  variant( 4.0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 4, 4 ) ,  variant( 3.0 ) ) );

    chain.add( set_value_command( *active_session, sheet_point( 6, 0 ) ,  "=SUM(OFFSET(C3:E5;-1;-1;3;3))" ) );
    chain.add( get_value_command( *active_session, sheet_point( 6, 0 ) ) );

    //chain.add( set_value_command( *active_session, sheet_point( 7, 0 ) ,  "=SUM(OFFSET(C3:E5;-100;0;3;3))" ) );
    //chain.add( get_value_command( *active_session, sheet_point( 7, 0 ) ) );


    chain.execute();

    // checks that these values differ no more then 0.000001%
    const double tolerance = 0.00001;

    TEST_GET_CLOSE( chain[10], 10.0, tolerance );


}


/*!
 * \brief
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
BOOST_AUTO_TEST_CASE( function_between_test )
{
    const sheet_point b1( 0, 1 );
    set_value_command( *active_session, sheet_point( 0, 0  ) ,  1.0 ).execute();
    set_value_command( *active_session, sheet_point( 1, 0  ) ,  2.0 ).execute();
    set_value_command( *active_session, sheet_point( 2, 0  ) ,  3.0 ).execute();
    set_value_command( *active_session, b1,  "=between(a1;a2;a3)" ).execute();
    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *active_session, b1 ) ), variant( true ) );
    set_value_command( *active_session, sheet_point( 0, 0 ) ,  2.0 ).execute();
    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *active_session, b1 ) ), variant( true ) );
    set_value_command( *active_session, sheet_point( 0, 0 ) ,  3.0 ).execute();
    set_value_command( *active_session, sheet_point( 2, 0 ) ,  1.0 ).execute();
    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *active_session, b1 ) ), variant( true ) );
    set_value_command( *active_session, sheet_point( 0, 0 ) ,  4.0 ).execute();
    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *active_session, b1 ) ), variant( true ) );
    set_value_command( *active_session, sheet_point( 0, 0 ) ,  0.0 ).execute();
    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *active_session, b1 ) ), variant( false ) );
}


/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( function_concat_range )
{

    command_chain chain;

    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) ,  variant( "Hello" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 1 ) ,  variant( "I'm" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) ,  variant( "World" ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 1 ) ,  variant( "Great" ) ) );


    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) ,  "=CONCATENATE.RANGE(A1:B2;\" \")" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );

    chain.execute();


    TEST_GET_VALUE( chain[5], variant( "Hello World I'm Great" ) );


}


BOOST_AUTO_TEST_SUITE_END()
