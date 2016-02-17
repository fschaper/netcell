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

#include <boost/assign.hpp>

#include <wss/session_handler.hpp>
#include <wss/session.hpp>
#include <wss/command.hpp>
#include <wss/server.hpp>
#include <wss/type.hpp>
#include <wss/execute_fetch.hpp>
#include <wss/invalid_formula_exception.hpp>
#include <wss/invalid_formula_exception.hpp>
#include <wss/invalid_formula_exception.hpp>

struct interpreter_fixture {
    interpreter_fixture() : a1( 0, 0 ),
        a2( 1, 0 ),
        a3( 2, 0 ),
        a4( 3, 0 ) {
        server::instance().startup();
        active_session = server::instance().session_handler().create( locale::create( "en" ) );

        create_application_command( *active_session, "my application" ).execute();
        select_application_command( *active_session, "my application" ).execute();
        create_workbook_command( *active_session, "my_workbook_1" ).execute();
        select_workbook_command( *active_session, "my_workbook_1" ).execute();
        create_worksheet_command( *active_session, "my_worksheet_1" ).execute();
        select_worksheet_command( *active_session, "my_worksheet_1" ).execute();
        create_worksheet_command( *active_session, "my_worksheet_2" ).execute();
        select_worksheet_command( *active_session, "my_worksheet_2" ).execute();
        maximum_iterations = active_session->selected().application()->calculation_settings().maximum_iterations();
    }

    ~interpreter_fixture() {
        try {
            server::instance().shutdown();
        } catch ( const std::exception& ) {
            assert( !"this may never throw" );
        }
    }

    locked_session active_session;
    sheet_point a1;
    sheet_point a2;
    sheet_point a3;
    sheet_point a4;
    double maximum_iterations;
};

BOOST_FIXTURE_TEST_SUITE( interpreter_test, interpreter_fixture );

/*!
 * \brief
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
BOOST_AUTO_TEST_CASE( reference_list_test )
{
    BOOST_REQUIRE_NO_THROW( execute_fetch( set_value_command( *active_session, sheet_point( 0, 0 ) , "=a1;a2;b1:c6;test" ) ) );
    const variant formula = execute_fetch( get_formula_command( *active_session, sheet_point( 0, 0 ) ) );

    BOOST_CHECK_EQUAL( formula, "=A1;A2;B1:C6;test" );
}


/*!
 * \brief
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
BOOST_AUTO_TEST_CASE( brace_calculation_test )
{
    command_chain chain;
    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) , "=(1-768)*100" ) );
    chain.add( get_value_command( *active_session, sheet_point( 0, 0 ) ) );
    chain.execute();

    TEST_GET_VALUE( chain[1], -76700.0 );
}

/*!
 * \brief
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
BOOST_AUTO_TEST_CASE( comparison_less_then_test )
{
    command_chain chain;
    chain.add( set_value_command( *active_session, sheet_point( 0, 1 ) , "=1<2" ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 2 ) , "=2<1" ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 3 ) , "=2<2" ) );
    chain.add( get_value_command( *active_session, sheet_point( 0, 1 ) ) );
    chain.add( get_value_command( *active_session, sheet_point( 0, 2 ) ) );
    chain.add( get_value_command( *active_session, sheet_point( 0, 3 ) ) );
    chain.execute();

    TEST_GET_VALUE( chain[3], true );
    TEST_GET_VALUE( chain[4], false );
    TEST_GET_VALUE( chain[5], false );
}

/*!
 * \brief
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
BOOST_AUTO_TEST_CASE( multidimensional_array_test )
{
    command_chain chain;
    chain.add( set_value_command( *active_session, sheet_point( 0, 1 ) , "={1,2;3,2}" ) );
    chain.add( get_formula_command( *active_session, sheet_point( 0, 1 ) ) );
    chain.execute();

    TYPED_CHECK_EQUAL( get_formula_command, chain[1], "={1,2;3,2}" );
}


/*!
 * \brief
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
BOOST_AUTO_TEST_CASE( flag_dirty_test )
{
    command_chain chain;
    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) , "=A2" ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) , 10.0 ) );
    chain.add( get_value_command( *active_session, sheet_point( 0, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) , 20.0 ) );
    chain.add( get_value_command( *active_session, sheet_point( 0, 0 ) ) );
    chain.execute();

    TEST_GET_VALUE( chain[4], 20.0 );
}
BOOST_AUTO_TEST_CASE( strange_error )
{
    sheet_point b1( 0, 1 );
    sheet_point c1( 0, 2 );
    sheet_point d1( 0, 3 );
    sheet_point e1( 0, 4 );

    set_value_command( *active_session, a1 ,  variant( 1.0 ) ).execute();
    set_value_command( *active_session, b1 ,  variant( 0.0 ) ).execute();
    set_value_command( *active_session, c1 ,  "=A1/B1" ).execute();
    set_value_command( *active_session, d1 , "=ISERROR(C1)" ).execute();

    const variant check_val = execute_fetch( get_value_command( *active_session, d1 ) );
    BOOST_CHECK_EQUAL( check_val, variant( true ) );
}

BOOST_AUTO_TEST_CASE( circular_reference_self )
{
    set_value_command( *active_session, a1 , "=A1" ).execute();

    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *active_session, a1 ) ), variant( 0.0 ) );
}

BOOST_AUTO_TEST_CASE( circular_reference_self_plus_one )
{
    set_value_command( *active_session, a1 , "=A1+1" ).execute();
    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *active_session, a1 ) ), variant( maximum_iterations ) );
}

/*!
 * \brief
 * A1 = A1, A2 = A1 (get A1 first)
 */
BOOST_AUTO_TEST_CASE( circular_reference_test_1 )
{
    set_value_command( *active_session, a1, "=A1" ).execute();
    set_value_command( *active_session, a2, "=A1" ).execute();

    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *active_session, a1 ) ), variant( 0.0 ) );
    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *active_session, a2 ) ), variant( 0.0 ) );
}

/*!
 * \brief
 * A1 = A1, A2 = A1  (get A2 first)
 */
BOOST_AUTO_TEST_CASE( circular_reference_test_2 )
{
    set_value_command( *active_session, a1, "=A1" ).execute();
    set_value_command( *active_session, a2, "=A1" ).execute();

    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *active_session, a2 ) ), variant( 0.0 ) );
    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *active_session, a1 ) ), variant( 0.0 ) );
}

/*!
 * \brief
 * A1 = A1+1, A2 = A1+2 (get A1 first)
 */
BOOST_AUTO_TEST_CASE( circular_reference_test_3 )
{
    set_value_command( *active_session, a1, "=A1+1" ).execute();
    set_value_command( *active_session, a2, "=A1+2" ).execute();

    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *active_session, a1 ) ), variant( maximum_iterations ) );
    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *active_session, a2 ) ), variant( maximum_iterations + 2.0 ) );
}

/*!
 * \brief
 * A1 = A1+1, A2 = A1+2  (get A2 first)
 */
BOOST_AUTO_TEST_CASE( circular_reference_test_4 )
{
    set_value_command( *active_session, a1, "=A1+1" ).execute();
    set_value_command( *active_session, a2, "=A1+2" ).execute();

    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *active_session, a2 ) ), variant( maximum_iterations + 2.0 ) );
    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *active_session, a1 ) ), variant( maximum_iterations ) );
}

/*!
 * \brief
 * A1 = A2+1, A2 = A1+2  (get A1 first)
 */
BOOST_AUTO_TEST_CASE( circular_reference_test_5 )
{
    set_value_command( *active_session, a1, "=A2+1" ).execute();
    set_value_command( *active_session, a2, "=A1+1" ).execute();

    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *active_session, a1 ) ), variant( maximum_iterations * 2.0 - 1.0 ) );
    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *active_session, a2 ) ), variant( maximum_iterations * 2.0 ) );
}

/*!
 * \brief
 * A1 = A2+1, A2 = A1+2  (get A1 first)
 */
BOOST_AUTO_TEST_CASE( circular_reference_test_6 )
{
    set_value_command( *active_session, a1, "=A2+1" ).execute();
    set_value_command( *active_session, a2, "=A1+1" ).execute();

    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *active_session, a2 ) ), variant( maximum_iterations * 2.0 ) );
    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *active_session, a1 ) ), variant( maximum_iterations * 2.0 - 1.0 ) );
}
/*!
 * \brief
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
BOOST_AUTO_TEST_CASE( circular_reference_test2 )
{
    set_value_command( *active_session, a1, "=A2+1" ).execute();
    set_value_command( *active_session, a2, "=A1+1" ).execute();
    set_value_command( *active_session, a3, "=A2" ).execute();

    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *active_session, a3 ) ), variant( maximum_iterations * 2.0 ) );
}

BOOST_AUTO_TEST_CASE( circular_reference_test3 )
{
    set_value_command( *active_session, a1, "=A3+1" ).execute();
    set_value_command( *active_session, a2, "=A1+1" ).execute();
    set_value_command( *active_session, a3, "=A2+1" ).execute();

    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *active_session, a3 ) ), variant( maximum_iterations * 3.0 ) );
}


/*!
 * \brief
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
BOOST_AUTO_TEST_CASE( volatile_recursion_test )
{
    set_value_command( *active_session, a1, "=A1+1+rand()" ).execute();
    const variant value = execute_fetch( get_value_command( *active_session, a1 ) );
    BOOST_CHECK_LE( value, variant( maximum_iterations * 2.0 ) );
    BOOST_CHECK_LE( variant( maximum_iterations ), value );
}

/*!
 * \brief
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
BOOST_AUTO_TEST_CASE( volatile_recursion_reference_test )
{
    set_value_command( *active_session, a1, "=A1+1+rand()" ).execute();
    set_value_command( *active_session, a2, "=A1+2" ).execute();
    const variant value = execute_fetch( get_value_command( *active_session, a2 ) );
    BOOST_CHECK_LE( value, variant( maximum_iterations * 2 + 2.0 ) );
    BOOST_CHECK_LE( variant( maximum_iterations + 2.0 ), value );
}

/*!
 * \brief
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
BOOST_AUTO_TEST_CASE( volatile_circular_reference_test1 )
{
    set_value_command( *active_session, a1, "=A2+1+rand()" ).execute();
    set_value_command( *active_session, a2, "=A1+1" ).execute();
    const variant a1_value = execute_fetch( get_value_command( *active_session, a1 ) );
    const variant a2_value = execute_fetch( get_value_command( *active_session, a2 ) );

    BOOST_CHECK_LE( a1_value, variant( maximum_iterations * 3.0 + 2.0 - 1.0 ) );
    BOOST_CHECK_LE( variant( maximum_iterations * 2.0 + 2.0 - 1.0 ), a1_value );
    BOOST_CHECK_LE( a1_value, variant( maximum_iterations * 3.0 + 2.0 ) );
    BOOST_CHECK_LE( variant( maximum_iterations * 2.0 + 2.0 ), a2_value );
}

/*!
 * \brief
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
BOOST_AUTO_TEST_CASE( error_value_test )
{
    command_chain chain;
    chain.add( set_value_command( *active_session, sheet_point( 0, 1 ) , "=#NULL!" ) );
    chain.add( get_formula_command( *active_session, sheet_point( 0, 1 ) ) );
    chain.execute();

    TYPED_CHECK_EQUAL( get_formula_command, chain[1], "=#NULL!" );
}

/*!
 * \brief
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
BOOST_AUTO_TEST_CASE( comparison_greater_then_test )
{
    command_chain chain;
    chain.add( set_value_command( *active_session, sheet_point( 0, 1 ) , "=1>2" ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 2 ) , "=2>1" ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 3 ) , "=2>2" ) );
    chain.add( get_value_command( *active_session, sheet_point( 0, 1 ) ) );
    chain.add( get_value_command( *active_session, sheet_point( 0, 2 ) ) );
    chain.add( get_value_command( *active_session, sheet_point( 0, 3 ) ) );
    chain.execute();

    TEST_GET_VALUE( chain[3], false );
    TEST_GET_VALUE( chain[4], true );
    TEST_GET_VALUE( chain[5], false );
}

/*!
 * \brief
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
BOOST_AUTO_TEST_CASE( comparison_greater_equal_test )
{
    command_chain chain;
    chain.add( set_value_command( *active_session, sheet_point( 0, 1 ) , "=1>=2" ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 2 ) , "=2>=1" ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 3 ) , "=2>=2" ) );
    chain.add( get_value_command( *active_session, sheet_point( 0, 1 ) ) );
    chain.add( get_value_command( *active_session, sheet_point( 0, 2 ) ) );
    chain.add( get_value_command( *active_session, sheet_point( 0, 3 ) ) );
    chain.execute();

    TEST_GET_VALUE( chain[3], false );
    TEST_GET_VALUE( chain[4], true );
    TEST_GET_VALUE( chain[5], true );
}

/*!
 * \brief
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
BOOST_AUTO_TEST_CASE( comparison_less_equal_test )
{
    command_chain chain;
    chain.add( set_value_command( *active_session, sheet_point( 0, 1 ) , "=1<=2" ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 2 ) , "=2<=1" ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 3 ) , "=2<=2" ) );
    chain.add( get_value_command( *active_session, sheet_point( 0, 1 ) ) );
    chain.add( get_value_command( *active_session, sheet_point( 0, 2 ) ) );
    chain.add( get_value_command( *active_session, sheet_point( 0, 3 ) ) );
    chain.execute();

    TEST_GET_VALUE( chain[3], true );
    TEST_GET_VALUE( chain[4], false );
    TEST_GET_VALUE( chain[5], true );
}

/*!
 * \brief
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
BOOST_AUTO_TEST_CASE( comparison_equal_test )
{
    command_chain chain;
    chain.add( set_value_command( *active_session, sheet_point( 0, 1 ) , "=1=2" ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 2 ) , "=2=2" ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 3 ) , "=2=1" ) );
    chain.add( get_value_command( *active_session, sheet_point( 0, 1 ) ) );
    chain.add( get_value_command( *active_session, sheet_point( 0, 2 ) ) );
    chain.add( get_value_command( *active_session, sheet_point( 0, 3 ) ) );
    chain.execute();

    TEST_GET_VALUE( chain[3], false );
    TEST_GET_VALUE( chain[4], true );
    TEST_GET_VALUE( chain[5], false );
}

/*!
 * \brief
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
BOOST_AUTO_TEST_CASE( change_formula_test )
{
    command_chain chain;
    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) , "=10" ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) , "=20" ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) , "=A1+A2" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );
    chain.add( get_formula_command( *active_session, sheet_point( 2, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) , "=B1+B2" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );
    chain.add( get_formula_command( *active_session, sheet_point( 2, 0 ) ) );
    chain.add( set_value_command( *active_session, sheet_point( 2, 0 ) , "=B1+B2" ) );
    chain.add( get_value_command( *active_session, sheet_point( 2, 0 ) ) );
    chain.add( get_formula_command( *active_session, sheet_point( 2, 0 ) ) );
    chain.execute();

    TYPED_CHECK_EQUAL( get_value_command, chain[3], variant( 30.0 ) );
    TYPED_CHECK_EQUAL( get_formula_command, chain[4], "=A1+A2" );
    TYPED_CHECK_EQUAL( get_value_command, chain[6], variant( 0.0 ) );
    TYPED_CHECK_EQUAL( get_formula_command, chain[7], "=B1+B2" );
    TYPED_CHECK_EQUAL( get_value_command, chain[9], variant( 0.0 ) );
    TYPED_CHECK_EQUAL( get_formula_command, chain[10], "=B1+B2" );
}


//////////////////////////////////////////////////////////////////////////


/*!
 * \brief
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
BOOST_AUTO_TEST_CASE( comparison_array_less_then_test )
{
    command_chain chain;
    chain.add( set_array_value_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 0, 4 ) ),  "={1,2,3,4,5}<{2,3,4,5,6}" ) );
    chain.add( set_array_value_command( *active_session, sheet_range( sheet_point( 1, 0 ), sheet_point( 1, 4 ) ) , "={1,2,3,4,5}<{0,1,2,3,4}" ) );
    chain.add( set_array_value_command( *active_session, sheet_range( sheet_point( 2, 0 ), sheet_point( 2, 4 ) ) , "={1,2,3,4,5}<{1,2,3,4,5}" ) );
    chain.add( set_array_value_command( *active_session, sheet_range( sheet_point( 3, 0 ), sheet_point( 3, 4 ) ) , "={1,2,3,4,5}<{2,1,4,2,6}" ) );
    chain.add( set_array_value_command( *active_session, sheet_range( sheet_point( 4, 0 ), sheet_point( 4, 4 ) ) , "={1,2,3,4,5}<3" ) );
    chain.add( get_value_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 0, 4 ) ) ) );
    chain.add( get_value_command( *active_session, sheet_range( sheet_point( 1, 0 ), sheet_point( 1, 4 ) ) ) );
    chain.add( get_value_command( *active_session, sheet_range( sheet_point( 2, 0 ), sheet_point( 2, 4 ) ) ) );
    chain.add( get_value_command( *active_session, sheet_range( sheet_point( 3, 0 ), sheet_point( 3, 4 ) ) ) );
    chain.add( get_value_command( *active_session, sheet_range( sheet_point( 4, 0 ), sheet_point( 4, 4 ) ) ) );
    chain.execute();

    using namespace boost::assign;

    variant::sparse_array_type v1, v2, v3, v4, v5;
    v1 += true, true, true, true, true;
    v2 += false, false, false, false, false;
    v3 += false, false, false, false, false;
    v4 += true, false, true, false, true;
    v5 += true, true, false, false, false;

    TEST_GET_VALUE( chain[5], variant( v1 ) );
    TEST_GET_VALUE( chain[6], variant( v2 ) );
    TEST_GET_VALUE( chain[7], variant( v3 ) );
    TEST_GET_VALUE( chain[8], variant( v4 ) );
    TEST_GET_VALUE( chain[9], variant( v5 ) );
}

/*!
 * \brief
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
BOOST_AUTO_TEST_CASE( comparison_array_greater_then_test )
{
    command_chain chain;
    chain.add( set_array_value_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 0, 4 ) ), "={2,3,4,5,6}>{1,2,3,4,5}" ) );
    chain.add( set_array_value_command( *active_session, sheet_range( sheet_point( 1, 0 ), sheet_point( 1, 4 ) ) , "={0,1,2,3,4}>{1,2,3,4,5}" ) );
    chain.add( set_array_value_command( *active_session, sheet_range( sheet_point( 2, 0 ), sheet_point( 2, 4 ) ) , "={1,2,3,4,5}>{1,2,3,4,5}" ) );
    chain.add( set_array_value_command( *active_session, sheet_range( sheet_point( 3, 0 ), sheet_point( 3, 4 ) ) , "={2,1,4,2,6}>{1,2,3,4,5}" ) );
    chain.add( set_array_value_command( *active_session, sheet_range( sheet_point( 4, 0 ), sheet_point( 4, 4 ) ) , "={1,2,3,4,5}>3" ) );
    chain.add( get_value_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 0, 4 ) ) ) );
    chain.add( get_value_command( *active_session, sheet_range( sheet_point( 1, 0 ), sheet_point( 1, 4 ) ) ) );
    chain.add( get_value_command( *active_session, sheet_range( sheet_point( 2, 0 ), sheet_point( 2, 4 ) ) ) );
    chain.add( get_value_command( *active_session, sheet_range( sheet_point( 3, 0 ), sheet_point( 3, 4 ) ) ) );
    chain.add( get_value_command( *active_session, sheet_range( sheet_point( 4, 0 ), sheet_point( 4, 4 ) ) ) );
    chain.execute();

    using namespace boost::assign;

    variant::sparse_array_type v1, v2, v3, v4, v5;
    v1 += true, true, true, true, true;
    v2 += false, false, false, false, false;
    v3 += false, false, false, false, false;
    v4 += true, false, true, false, true;
    v5 += false, false, false, true, true;

    TEST_GET_VALUE( chain[5], variant( v1 ) );
    TEST_GET_VALUE( chain[6], variant( v2 ) );
    TEST_GET_VALUE( chain[7], variant( v3 ) );
    TEST_GET_VALUE( chain[8], variant( v4 ) );
    TEST_GET_VALUE( chain[9], variant( v5 ) );
}

/*!
 * \brief
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
BOOST_AUTO_TEST_CASE( comparison_array_greater_equal_test )
{
    command_chain chain;
    chain.add( set_array_value_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 0, 4 ) ), "={2,3,4,5,6}>={1,2,3,4,5}" ) );
    chain.add( set_array_value_command( *active_session, sheet_range( sheet_point( 1, 0 ), sheet_point( 1, 4 ) ) , "={0,1,2,3,4}>={1,2,3,4,5}" ) );
    chain.add( set_array_value_command( *active_session, sheet_range( sheet_point( 2, 0 ), sheet_point( 2, 4 ) ) , "={1,2,3,4,5}>={1,2,3,4,5}" ) );
    chain.add( set_array_value_command( *active_session, sheet_range( sheet_point( 3, 0 ), sheet_point( 3, 4 ) ) , "={2,1,4,2,5}>={1,2,3,4,5}" ) );
    chain.add( set_array_value_command( *active_session, sheet_range( sheet_point( 4, 0 ), sheet_point( 4, 4 ) ) , "={1,2,3,4,5}>=3" ) );
    chain.add( get_value_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 0, 4 ) ) ) );
    chain.add( get_value_command( *active_session, sheet_range( sheet_point( 1, 0 ), sheet_point( 1, 4 ) ) ) );
    chain.add( get_value_command( *active_session, sheet_range( sheet_point( 2, 0 ), sheet_point( 2, 4 ) ) ) );
    chain.add( get_value_command( *active_session, sheet_range( sheet_point( 3, 0 ), sheet_point( 3, 4 ) ) ) );
    chain.add( get_value_command( *active_session, sheet_range( sheet_point( 4, 0 ), sheet_point( 4, 4 ) ) ) );
    chain.execute();

    using namespace boost::assign;

    variant::sparse_array_type v1, v2, v3, v4, v5;
    v1 += true, true, true, true, true;
    v2 += false, false, false, false, false;
    v3 += true, true, true, true, true;
    v4 += true, false, true, false, true;
    v5 += false, false, true, true, true;

    TEST_GET_VALUE( chain[5], variant( v1 ) );
    TEST_GET_VALUE( chain[6], variant( v2 ) );
    TEST_GET_VALUE( chain[7], variant( v3 ) );
    TEST_GET_VALUE( chain[8], variant( v4 ) );
    TEST_GET_VALUE( chain[9], variant( v5 ) );
}

/*!
 * \brief
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
BOOST_AUTO_TEST_CASE( comparison_array_less_equal_test )
{
    command_chain chain;
    chain.add( set_array_value_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 0, 4 ) ), "={1,2,3,4,5}<={2,3,4,5,6}" ) );
    chain.add( set_array_value_command( *active_session, sheet_range( sheet_point( 1, 0 ), sheet_point( 1, 4 ) ) , "={1,2,3,4,5}<={0,1,2,3,4}" ) );
    chain.add( set_array_value_command( *active_session, sheet_range( sheet_point( 2, 0 ), sheet_point( 2, 4 ) ) , "={1,2,3,4,5}<={1,2,3,4,5}" ) );
    chain.add( set_array_value_command( *active_session, sheet_range( sheet_point( 3, 0 ), sheet_point( 3, 4 ) ) , "={1,2,3,4,5}<={2,1,4,2,5}" ) );
    chain.add( set_array_value_command( *active_session, sheet_range( sheet_point( 4, 0 ), sheet_point( 4, 4 ) ) , "={1,2,3,4,5}<=3" ) );
    chain.add( get_value_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 0, 4 ) ) ) );
    chain.add( get_value_command( *active_session, sheet_range( sheet_point( 1, 0 ), sheet_point( 1, 4 ) ) ) );
    chain.add( get_value_command( *active_session, sheet_range( sheet_point( 2, 0 ), sheet_point( 2, 4 ) ) ) );
    chain.add( get_value_command( *active_session, sheet_range( sheet_point( 3, 0 ), sheet_point( 3, 4 ) ) ) );
    chain.add( get_value_command( *active_session, sheet_range( sheet_point( 4, 0 ), sheet_point( 4, 4 ) ) ) );
    chain.execute();

    using namespace boost::assign;

    variant::sparse_array_type v1, v2, v3, v4, v5;
    v1 += true, true, true, true, true;
    v2 += false, false, false, false, false;
    v3 += true, true, true, true, true;
    v4 += true, false, true, false, true;
    v5 += true, true, true, false, false;

    TEST_GET_VALUE( chain[5], variant( v1 ) );
    TEST_GET_VALUE( chain[6], variant( v2 ) );
    TEST_GET_VALUE( chain[7], variant( v3 ) );
    TEST_GET_VALUE( chain[8], variant( v4 ) );
    TEST_GET_VALUE( chain[9], variant( v5 ) );
}

/*!
 * \brief
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
BOOST_AUTO_TEST_CASE( comparison_array_equal_test )
{
    command_chain chain;
    chain.add( set_array_value_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 0, 4 ) ), "={1,2,3,4,5}={2,3,4,5,6}" ) );
    chain.add( set_array_value_command( *active_session, sheet_range( sheet_point( 1, 0 ), sheet_point( 1, 4 ) ) , "={1,2,3,4,5}={0,1,2,3,4}" ) );
    chain.add( set_array_value_command( *active_session, sheet_range( sheet_point( 2, 0 ), sheet_point( 2, 4 ) ) , "={1,2,3,4,5}={1,2,3,4,5}" ) );
    chain.add( set_array_value_command( *active_session, sheet_range( sheet_point( 3, 0 ), sheet_point( 3, 4 ) ) , "={1,2,3,4,5}={2,1,4,2,5}" ) );
    chain.add( set_array_value_command( *active_session, sheet_range( sheet_point( 4, 0 ), sheet_point( 4, 4 ) ) , "={1,2,3,4,5}=3" ) );
    chain.add( get_value_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 0, 4 ) ) ) );
    chain.add( get_value_command( *active_session, sheet_range( sheet_point( 1, 0 ), sheet_point( 1, 4 ) ) ) );
    chain.add( get_value_command( *active_session, sheet_range( sheet_point( 2, 0 ), sheet_point( 2, 4 ) ) ) );
    chain.add( get_value_command( *active_session, sheet_range( sheet_point( 3, 0 ), sheet_point( 3, 4 ) ) ) );
    chain.add( get_value_command( *active_session, sheet_range( sheet_point( 4, 0 ), sheet_point( 4, 4 ) ) ) );
    chain.execute();

    using namespace boost::assign;

    variant::sparse_array_type v1, v2, v3, v4, v5;
    v1 += false, false, false, false, false;
    v2 += false, false, false, false, false;
    v3 += true, true, true, true, true;
    v4 += false, false, false, false, true;
    v5 += false, false, true, false, false;

    TEST_GET_VALUE( chain[5], variant( v1 ) );
    TEST_GET_VALUE( chain[6], variant( v2 ) );
    TEST_GET_VALUE( chain[7], variant( v3 ) );
    TEST_GET_VALUE( chain[8], variant( v4 ) );
    TEST_GET_VALUE( chain[9], variant( v5 ) );
}

/*!
 * \brief
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
BOOST_AUTO_TEST_CASE( comparison_array_range_equal_test )
{
    command_chain chain;
    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) , 1.0 ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 1 ) , 2.0 ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 2 ) , 3.0 ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 3 ) , 4.0 ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) , 1.0 ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 1 ) , 2.0 ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 2 ) , 3.0 ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 3 ) , 4.0 ) );
    chain.add( set_array_value_command( *active_session, sheet_range( sheet_point( 2, 0 ), sheet_point( 2, 3 ) ), "=a1:d1=a2:d2" ) );
    chain.add( get_value_command( *active_session, sheet_range( sheet_point( 2, 0 ), sheet_point( 2, 3 ) ) ) );
    chain.execute();

    using namespace boost::assign;

    variant::sparse_array_type v1;
    v1 += true, true, true, true;

    TEST_GET_VALUE( chain[9], variant( v1 ) );
}

/*!
 * \brief
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
BOOST_AUTO_TEST_CASE( comparison_array_range_equal_2_test )
{
    command_chain chain;
    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) , 1.0 ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 1 ) , 2.0 ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 2 ) , 3.0 ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 3 ) , 4.0 ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) , 2.0 ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 1 ) , 3.0 ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 2 ) , 1.0 ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 3 ) , 4.0 ) );
    chain.add( set_array_value_command( *active_session, sheet_range( sheet_point( 2, 0 ), sheet_point( 2, 3 ) ), "=a1:d1=a2:d2" ) );
    chain.add( get_value_command( *active_session, sheet_range( sheet_point( 2, 0 ), sheet_point( 2, 3 ) ) ) );
    chain.execute();

    using namespace boost::assign;

    variant::sparse_array_type v1;
    v1 += false, false, false, true;

    TEST_GET_VALUE( chain[9], variant( v1 ) );
}

/*!
 * \brief
 * test volatile values (this one relies on the spreadsheet function "=rand()" working and being volatile
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
BOOST_AUTO_TEST_CASE( simple_volatile_value_test )
{
    variant rand_val_1;
    {
        command_chain chain;
        chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) , "=rand()" ) );
        chain.add( get_value_command( *active_session, sheet_point( 0, 0 ) ) );
        chain.add( get_value_command( *active_session, sheet_point( 0, 0 ) ) );
        chain.add( get_value_command( *active_session, sheet_point( 0, 0 ) ) );
        chain.execute();
        BOOST_CHECK_NO_THROW( rand_val_1 = dynamic_cast<const get_value_command&>( chain[3] ).value() );
        BOOST_CHECK_GT( rand_val_1, variant( 0.0 ) );
        BOOST_CHECK_LT( rand_val_1, variant( 1.0 ) );
    }
    {
        command_chain chain;
        chain.add( get_value_command( *active_session, sheet_point( 0, 0 ) ) );
        chain.execute();
        BOOST_CHECK_NO_THROW( BOOST_CHECK_EQUAL( rand_val_1, dynamic_cast<const get_value_command&>( chain[0] ).value() ) );
    }
    {
        command_chain chain;
        chain.add( start_new_calculation_command( *active_session ) );
        chain.add( get_value_command( *active_session, sheet_point( 0, 0 ) ) );
        chain.execute();
        BOOST_CHECK_NO_THROW( BOOST_CHECK_NE( rand_val_1, dynamic_cast<const get_value_command&>( chain[1] ).value() ) );
    }
}

/*!
 * \brief
 * test referencing  volatile values (this one relies on the spreadsheet function "=rand()" working and being volatile
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
BOOST_AUTO_TEST_CASE( volatile_reference_value_test )
{
    command_chain chain;
    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) , "=rand()" ) );
    chain.add( set_value_command( *active_session, sheet_point( 1, 0 ) , "=a1" ) );
    chain.add( get_value_command( *active_session, sheet_point( 0, 0 ) ) );
    chain.add( get_value_command( *active_session, sheet_point( 1, 0 ) ) );
    chain.execute();

    BOOST_CHECK_NO_THROW(
        BOOST_CHECK_EQUAL( dynamic_cast<const get_value_command&>( chain[2] ).value(), dynamic_cast<const get_value_command&>( chain[3] ).value() )
    );
}

BOOST_AUTO_TEST_CASE( volatile_nf_then_delete_cell_test )
{
    command_chain chain;
    create_worksheet_element_command::key_value_vector_type vec;
    vec.push_back( worksheet_element::key_value_type( "n_location", "=$a$1;a2;c4;d3:d10" ) );
    chain.add( create_worksheet_element_command( *active_session, "", vec, false ) );
    chain.add( set_value_command( *active_session, sheet_point( 0, 0 ) , "=rand()" ) );
    chain.add( get_value_command( *active_session, sheet_point( 0, 0 ) ) );
    chain.add( remove_workbook_command( *active_session, active_session->selected().workbook().lock()->uuid() ) );
    BOOST_REQUIRE_NO_THROW( chain.execute() );
}

BOOST_AUTO_TEST_SUITE_END()
