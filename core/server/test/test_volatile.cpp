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

#include <wss/session_handler.hpp>
#include <wss/session.hpp>
#include <wss/command.hpp>
#include <wss/server.hpp>
#include <wss/type.hpp>
#include <wss/execute_fetch.hpp>

struct volatile_test_fixture {
    volatile_test_fixture() {
        server::instance().startup();
        s = server::instance().session_handler().create( locale::create( "en" ) );

        create_application_command( *s, "my application" ).execute();
        select_application_command( *s, "my application" ).execute();
        create_workbook_command( *s, "my_workbook_1" ).execute();
        select_workbook_command( *s, "my_workbook_1" ).execute();
        create_worksheet_command( *s, "my_worksheet_1" ).execute();
        select_worksheet_command( *s, "my_worksheet_1" ).execute();
        create_worksheet_command( *s, "my_worksheet_2" ).execute();
        select_worksheet_command( *s, "my_worksheet_2" ).execute();
        ws = s->selected().worksheet().lock();
    }

    ~volatile_test_fixture() {
        try {
            ws.reset();
            server::instance().shutdown();
        } catch ( const std::exception& ) {
            assert( !"this may never throw" );
        }
    }

    shared_worksheet_type ws;
    locked_session s;
};

BOOST_FIXTURE_TEST_SUITE( volatile_test, volatile_test_fixture );

/*!
 * \brief
 * test for volatile flag inheritance
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
BOOST_AUTO_TEST_CASE( inherit_volatile_flag_test )
{
    set_value_command( *s, sheet_point( 0, 0 ), "=rand()" ).execute();
    set_value_command( *s, sheet_point( 0, 1 ), "=A1" ).execute();
    set_value_command( *s, sheet_point( 0, 2 ), "=B1" ).execute();
    set_value_command( *s, sheet_point( 1, 0 ), "=volatile_count(a1)" ).execute();
    set_value_command( *s, sheet_point( 1, 1 ), "=volatile_count(b1)" ).execute();
    set_value_command( *s, sheet_point( 1, 2 ), "=volatile_count(c1)" ).execute();

    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *s, sheet_point( 1, 0 ) ) ), 1.0 );
    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *s, sheet_point( 1, 1 ) ) ), 1.0 );
    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *s, sheet_point( 1, 2 ) ) ), 1.0 );
}

/*!
 * \brief
 * test for un setting the volatile flags
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
BOOST_AUTO_TEST_CASE( disinherit_volatile_flag_test )
{
    command_chain chain;
    chain.add( set_value_command( *s, sheet_point( 0, 0 ), "=rand()" ) );
    chain.add( set_value_command( *s, sheet_point( 0, 1 ), "=A1" ) );
    chain.add( set_value_command( *s, sheet_point( 1, 0 ), "=volatile_count(a1)" ) );
    chain.add( set_value_command( *s, sheet_point( 1, 1 ), "=volatile_count(b1)" ) );
    chain.add( get_value_command( *s, sheet_point( 1, 0 ) ) );
    chain.add( get_value_command( *s, sheet_point( 1, 1 ) ) );
    chain.add( set_value_command( *s, sheet_point( 0, 0 ), "" ) );
    chain.add( get_value_command( *s, sheet_point( 1, 0 ) ) );
    chain.add( get_value_command( *s, sheet_point( 1, 1 ) ) );
    chain.execute();

    TEST_GET_VALUE( chain[4], 1.0 );
    TEST_GET_VALUE( chain[5], 1.0 );
    TEST_GET_VALUE( chain[7], 0.0 );
    TEST_GET_VALUE( chain[8], 0.0 );
}

/*!
 * \brief
 * test for un setting the volatile flags
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
BOOST_AUTO_TEST_CASE( disinherit_volatile_flag_2_test )
{
    set_value_command( *s, sheet_point( 0, 0 ), "=rand()" ).execute();
    set_value_command( *s, sheet_point( 0, 1 ), "=A1" ).execute();
    set_value_command( *s, sheet_point( 1, 0 ), "=volatile_count(a1)" ).execute();
    set_value_command( *s, sheet_point( 1, 1 ), "=volatile_count(b1)" ).execute();
    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *s, sheet_point( 1, 0 ) ) ), 1.0 );
    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *s, sheet_point( 1, 1 ) ) ), 1.0 );

    set_value_command( *s, sheet_point( 0, 1 ), "" ).execute();
    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *s, sheet_point( 1, 0 ) ) ), 1.0 );
    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *s, sheet_point( 1, 1 ) ) ), 0.0 );
}

/*!
 * \brief
 * test for un setting the volatile flags
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
BOOST_AUTO_TEST_CASE( disinherit_volatile_flag_3_test )
{
    set_value_command( *s, sheet_point( 0, 0 ), "=rand()" ).execute();
    set_value_command( *s, sheet_point( 0, 1 ), "=rand()" ).execute();
    set_value_command( *s, sheet_point( 0, 2 ), "=A1+B1" ).execute();
    set_value_command( *s, sheet_point( 0, 3 ), "=C1" ).execute();
    set_value_command( *s, sheet_point( 1, 0 ), "=volatile_count(c1)" ).execute();
    set_value_command( *s, sheet_point( 1, 1 ), "=volatile_count(d1)" ).execute();
    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *s, sheet_point( 1, 0 ) ) ), 2.0 );
    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *s, sheet_point( 1, 1 ) ) ), 1.0 );
    set_value_command( *s, sheet_point( 0, 1 ), "" ).execute();
    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *s, sheet_point( 1, 0 ) ) ), 1.0 );
    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *s, sheet_point( 1, 1 ) ) ), 1.0 );
    set_value_command( *s, sheet_point( 0, 0 ), "" ).execute();
    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *s, sheet_point( 1, 1 ) ) ), 0.0 );
    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *s, sheet_point( 1, 0 ) ) ), 0.0 );
}

/*!
 * \brief
 * test copy construction of volatile formulas
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
BOOST_AUTO_TEST_CASE( copy_construct_volatile_formula1 )
{
    sheet_point a1( 0, 0 );
    sheet_point a2( 1, 0 );
    range volatile_cell = ws->range( a1 );
    range reference_cell = ws->range( a2 );
    volatile_cell.value( *s, variant( "=rand()" ) );
    reference_cell.value( *s, variant( "=a1" ) );

    sheet_range source_range( sheet_point( 0, 0 ), sheet_point( 1, 0 ) );
    sheet_range target_range( sheet_point( 0, 1 ), sheet_point( 1, 1 ) );

    clipboard::clipboard_id_type id = execute_fetch( copy_range_command( *s, source_range ) );
    BOOST_CHECK_NO_THROW( paste_range_command( *s, target_range, id ).execute() );
    BOOST_CHECK_NO_THROW( clear_cells_command( *s, target_range, content_type::all ).execute() );
    BOOST_CHECK_NO_THROW( paste_range_command( *s, target_range, id ).execute() );
    BOOST_CHECK_NO_THROW( clear_cells_command( *s, target_range, content_type::all ).execute() );
    BOOST_CHECK_NO_THROW( paste_range_command( *s, target_range, id ).execute() );
    BOOST_CHECK_NO_THROW( clear_cells_command( *s, target_range, content_type::all ).execute() );
}

/*!
 * \brief
 * test copy construction of volatile formulas
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
BOOST_AUTO_TEST_CASE( copy_construct_volatile_formula2 )
{
    sheet_point a1( 0, 0 );
    sheet_point a2( 1, 0 );
    range volatile_cell = ws->range( a1 );
    range reference_cell = ws->range( a2 );
    reference_cell.value( *s, variant( "=a1" ) );
    volatile_cell.value( *s, variant( "=rand()" ) );

    sheet_range source_range( sheet_point( 0, 0 ), sheet_point( 1, 0 ) );
    sheet_range target_range( sheet_point( 0, 1 ), sheet_point( 1, 1 ) );

    clipboard::clipboard_id_type id = execute_fetch( copy_range_command( *s, source_range ) );
    BOOST_CHECK_NO_THROW( paste_range_command( *s, target_range, id ).execute() );
    BOOST_CHECK_NO_THROW( clear_cells_command( *s, target_range, content_type::all ).execute() );
    BOOST_CHECK_NO_THROW( paste_range_command( *s, target_range, id ).execute() );
    BOOST_CHECK_NO_THROW( clear_cells_command( *s, target_range, content_type::all ).execute() );
    BOOST_CHECK_NO_THROW( paste_range_command( *s, target_range, id ).execute() );
    BOOST_CHECK_NO_THROW( clear_cells_command( *s, target_range, content_type::all ).execute() );
}

/*!
 * \brief
 * test cyclic and volatile reference
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
BOOST_AUTO_TEST_CASE( cyclic_and_volatile_formula1 )
{
    sheet_point a1( 0, 0 );
    sheet_point a2( 1, 0 );
    range volatile_cell = ws->range( a1 );
    range reference_cell = ws->range( a2 );
    volatile_cell.value( *s, variant( "=rand()+a1" ) );
    //reference_cell.value( *s, variant( "=a1" ) );

    sheet_range source_range( sheet_point( 0, 0 ) );
    //sheet_range target_range( sheet_point( 0, 1 ), sheet_point( 1, 1 ) );

    //clipboard::clipboard_id_type id = execute_fetch( copy_range_command( *s, source_range ) );
    BOOST_CHECK_NO_THROW( get_value_command( *s, source_range ).execute() );
}

BOOST_AUTO_TEST_CASE( array_formula_volatile_count_problem_reference_master_cell )
{
    //set array cells to some volatile value
    set_array_value_command( *s, sheet_range( sheet_point( 0, 0 ), sheet_point( 1, 1 ) ) , "=rand()" ).execute();

    //reference the master cell
    set_value_command( *s, sheet_range( sheet_point( 2, 2 ) ), "=a1" ).execute();

    //copy the reference
    clipboard::clipboard_id_type id = execute_fetch( copy_range_command( *s, sheet_range( sheet_point( 2, 2 ), sheet_point( 2, 2 ) ) ) );

    //paste it and clear the cell after that
    paste_range_command( *s, sheet_range( sheet_point( 3, 3 ), sheet_point( 3, 3 ) ), id ).execute();
    clear_cells_command( *s, sheet_range( sheet_point( 3, 3 ), sheet_point( 3, 3 ) ), content_type::all ).execute();

    //clear the whole used range
    BOOST_CHECK_NO_THROW( clear_cells_command( *s, sheet_range( sheet_point( 0, 0 ), sheet_point( 3, 3 ) ), content_type::all ).execute() );
}

BOOST_AUTO_TEST_CASE( array_formula_volatile_count_problem_reference_slave_cell )
{
    //set array cells to some volatile value
    set_array_value_command( *s, sheet_range( sheet_point( 0, 0 ), sheet_point( 1, 1 ) ) , "=rand()" ).execute();

    //reference a slave cell
    set_value_command( *s, sheet_range( sheet_point( 2, 2 ) ), "=b1" ).execute();

    //copy the reference
    clipboard::clipboard_id_type id = execute_fetch( copy_range_command( *s, sheet_range( sheet_point( 2, 2 ), sheet_point( 2, 2 ) ) ) );

    //paste it and clear the cell after that
    paste_range_command( *s, sheet_range( sheet_point( 3, 3 ), sheet_point( 3, 3 ) ), id ).execute();
    clear_cells_command( *s, sheet_range( sheet_point( 3, 3 ), sheet_point( 3, 3 ) ), content_type::all ).execute();

    //clear the whole used range -> boom
    BOOST_CHECK_NO_THROW( clear_cells_command( *s, sheet_range( sheet_point( 0, 0 ), sheet_point( 3, 3 ) ), content_type::all ).execute() );
}

BOOST_AUTO_TEST_CASE( array_formula_references_volatile_array_formula )
{
    //set array cells to some volatile value
    set_array_value_command( *s, sheet_range( sheet_point( 0, 0 ), sheet_point( 1, 1 ) ) , "=rand()" ).execute();
    //set array cells to some volatile value
    set_array_value_command( *s, sheet_range( sheet_point( 2, 2 ), sheet_point( 3, 3 ) ) , "=A1:b2" ).execute();

    {
        variant first_val = execute_fetch( get_value_command( *s, sheet_range( sheet_point( 0, 0 ), sheet_point( 1, 1 ) )  ) );
        variant second_val = execute_fetch( get_value_command( *s, sheet_range( sheet_point( 2, 2 ), sheet_point( 3, 3 ) )  ) );

        BOOST_CHECK_EQUAL( first_val, second_val );
    }

    clear_cells_command( *s, sheet_range( sheet_point( 0, 0 ), sheet_point( 1, 1 ) ), content_type::all ).execute();

    {
        variant first_val = execute_fetch( get_value_command( *s, sheet_range( sheet_point( 0, 0 ), sheet_point( 1, 1 ) )  ) );
        variant second_val = execute_fetch( get_value_command( *s, sheet_range( sheet_point( 2, 2 ), sheet_point( 3, 3 ) )  ) );

        variant::variant_array_type expected_first_val( 4, variant() );
        variant::variant_array_type expected_second_val( 4, variant( 0.0 ) );

        BOOST_CHECK_EQUAL( variant( expected_first_val ), first_val );
        BOOST_CHECK_EQUAL( variant( expected_second_val ), second_val );
    }

    clear_cells_command( *s, sheet_range( sheet_point( 0, 0 ), sheet_point( 3, 3 ) ), content_type::all ).execute();
}

BOOST_AUTO_TEST_CASE( array_formula_references_volatile_array_formula2 )
{
    //set array cells to some volatile value
    set_array_value_command( *s, sheet_range( sheet_point( 0, 0 ), sheet_point( 1, 1 ) ) , "=rand()" ).execute();
    //set array cells to some volatile value
    set_array_value_command( *s, sheet_range( sheet_point( 2, 2 ), sheet_point( 3, 3 ) ) , "=A1:b2" ).execute();

    {
        variant first_val = execute_fetch( get_value_command( *s, sheet_range( sheet_point( 0, 0 ), sheet_point( 1, 1 ) )  ) );
        variant second_val = execute_fetch( get_value_command( *s, sheet_range( sheet_point( 2, 2 ), sheet_point( 3, 3 ) )  ) );

        BOOST_CHECK_EQUAL( first_val, second_val );
    }

    BOOST_CHECK_NO_THROW( clear_cells_command( *s, sheet_range( sheet_point( 2, 2 ), sheet_point( 3, 3 ) ), content_type::all ).execute() );

    {
        variant first_val = execute_fetch( get_value_command( *s, sheet_range( sheet_point( 0, 0 ), sheet_point( 1, 1 ) )  ) );
        variant second_val = execute_fetch( get_value_command( *s, sheet_range( sheet_point( 2, 2 ), sheet_point( 3, 3 ) )  ) );
        BOOST_CHECK_NE( first_val, second_val );
    }

    BOOST_CHECK_NO_THROW( clear_cells_command( *s, sheet_range( sheet_point( 0, 0 ), sheet_point( 1, 1 ) ), content_type::all ).execute() );
}

BOOST_AUTO_TEST_CASE( reference_same_cell_via_two_paths1 )
{
    set_value_command( *s, sheet_range( sheet_point( 0, 0 ) ), "=rand()" ).execute();
    set_value_command( *s, sheet_range( sheet_point( 1, 0 ) ), "=A1" ).execute();
    set_value_command( *s, sheet_range( sheet_point( 2, 0 ) ), "=A1+A2" ).execute();
    set_value_command( *s, sheet_range( sheet_point( 3, 0 ) ), "=volatile_count(a3)" ).execute();
    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *s, sheet_range( sheet_point( 3, 0 ) ) ) ), variant( 2.0 )  );
}

BOOST_AUTO_TEST_CASE( reference_same_cell_via_two_paths2 )
{
    set_value_command( *s, sheet_range( sheet_point( 1, 0 ) ), "=A1" ).execute();
    set_value_command( *s, sheet_range( sheet_point( 2, 0 ) ), "=A1+A2" ).execute();
    set_value_command( *s, sheet_range( sheet_point( 3, 0 ) ), "=volatile_count(a3)" ).execute();
    set_value_command( *s, sheet_range( sheet_point( 0, 0 ) ), "=rand()" ).execute();
    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *s, sheet_range( sheet_point( 3, 0 ) ) ) ), variant( 2.0 ) );
}

BOOST_AUTO_TEST_CASE( reference_volatile_then_volatile_plus_other )
{
    set_value_command( *s, sheet_range( sheet_point( 0, 0 ) ) , "=rand()" ).execute();
    set_value_command( *s, sheet_range( sheet_point( 3, 0 ) ), "=volatile_count(a3)" ).execute();
    set_value_command( *s, sheet_range( sheet_point( 2, 0 ) ), "=A1" ).execute();
    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *s, sheet_range( sheet_point( 3, 0 ) ) ) ), variant( 1.0 ) );
    set_value_command( *s, sheet_range( sheet_point( 2, 0 ) ), "=A1+A2" ).execute();
    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *s, sheet_range( sheet_point( 3, 0 ) ) ) ), variant( 1.0 ) );
}

BOOST_AUTO_TEST_CASE( reference_slave_then_slave_and_master1 )
{
    set_array_value_command( *s, sheet_range( sheet_point( 0, 0 ), sheet_point( 1, 1 ) ) , "=rand()" ).execute();
    set_value_command( *s, sheet_range( sheet_point( 3, 0 ) ), "=volatile_count(a3)" ).execute();
    set_value_command( *s, sheet_range( sheet_point( 2, 0 ) ), "=A2" ).execute();
    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *s, sheet_range( sheet_point( 3, 0 ) ) ) ), variant( 1.0 ) );
    set_value_command( *s, sheet_range( sheet_point( 2, 0 ) ), "=A1+A2" ).execute();
    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *s, sheet_range( sheet_point( 3, 0 ) ) ) ), variant( 1.0 ) );
}

BOOST_AUTO_TEST_CASE( reference_slave_then_slave_and_master2 )
{
    set_value_command( *s, sheet_range( sheet_point( 3, 0 ) ), "=volatile_count(a3)" ).execute();
    set_value_command( *s, sheet_range( sheet_point( 2, 0 ) ), "=A1+A2" ).execute();
    set_array_value_command( *s, sheet_range( sheet_point( 0, 0 ), sheet_point( 1, 1 ) ) , "=rand()" ).execute();
    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *s, sheet_range( sheet_point( 3, 0 ) ) ) ), variant( 1.0 ) );
}
BOOST_AUTO_TEST_SUITE_END()
