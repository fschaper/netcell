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
*  Frieder Hofmann <frieder.hofmann@jedox.com>
*/

#include <boost/test/unit_test.hpp>

#include <wss/point.hpp>
#include <wss/rectangle.hpp>
#include <wss/variant.hpp>
#include <wss/definition.hpp>
#include <wss/application.hpp>
#include <wss/sheet_point.hpp>
#include <wss/type.hpp>
#include <wss/locale.hpp>
#include <wss/command.hpp>
#include <wss/session_handler.hpp>
#include <wss/session.hpp>
#include <wss/server.hpp>
#include <wss/execute_fetch.hpp>


struct reference_fixture {
    reference_fixture() {
        server::instance().startup();
        s = server::instance().session_handler().create( locale::create( "en-US" ) );

        create_application_command( *s, "my application" ).execute();
        select_application_command( *s, "my application" ).execute();
        create_workbook_command( *s, "wb1" ).execute();
        select_workbook_command( *s, "wb1" ).execute();
        create_worksheet_command( *s, "ws" ).execute();
        select_worksheet_command( *s, "ws" ).execute();

        ws = s->selected().worksheet().lock();
    }

    ~reference_fixture() {
        try {
            ws.reset();
            server::instance().session_handler().remove_session( s->uuid() );
            server::instance().shutdown();
        } catch ( const std::exception& /*e*/ ) {
            assert( !"this may never throw" );
        }
    }

    locked_session s;
    shared_worksheet_type ws;
};

BOOST_FIXTURE_TEST_SUITE( test_references, reference_fixture );

BOOST_AUTO_TEST_CASE( test_invalid_sheet_cell_reference )
{
    set_value_command( *s, sheet_range( sheet_point( 0, 0 ) ), "=Sheet2!a1" ).execute();
    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *s, sheet_range( sheet_point( 0, 0 ) ) ) ), variant( variant::error_ref ) );
    BOOST_CHECK_EQUAL( execute_fetch( get_formula_command( *s, sheet_range( sheet_point( 0, 0 ) ) ) ), variant( "=Sheet2!A1" ) );
}

BOOST_AUTO_TEST_CASE( test_invalid_sheet_range_reference )
{
    set_value_command( *s, sheet_range( sheet_point( 0, 0 ) ), "=Sheet2!a1:a2" ).execute();
    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *s, sheet_range( sheet_point( 0, 0 ) ) ) ), variant( variant::error_ref ) );
    BOOST_CHECK_EQUAL( execute_fetch( get_formula_command( *s, sheet_range( sheet_point( 0, 0 ) ) ) ), variant( "=Sheet2!A1:A2" ) );
}

BOOST_AUTO_TEST_CASE( test_invalid_book_and_sheet_cell_reference )
{
    set_value_command( *s, sheet_range( sheet_point( 0, 0 ) ), "=[book1]Sheet2!a1" ).execute();
    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *s, sheet_range( sheet_point( 0, 0 ) ) ) ), variant( variant::error_ref ) );
    BOOST_CHECK_EQUAL( execute_fetch( get_formula_command( *s, sheet_range( sheet_point( 0, 0 ) ) ) ), variant( "=[book1]Sheet2!A1" ) );
}

BOOST_AUTO_TEST_CASE( test_invalid_book_and_sheet_range_reference )
{
    set_value_command( *s, sheet_range( sheet_point( 0, 0 ) ), "=[book1]Sheet2!a1:a2" ).execute();
    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *s, sheet_range( sheet_point( 0, 0 ) ) ) ), variant( variant::error_ref ) );
    BOOST_CHECK_EQUAL( execute_fetch( get_formula_command( *s, sheet_range( sheet_point( 0, 0 ) ) ) ), variant( "=[book1]Sheet2!A1:A2" ) );
}

BOOST_AUTO_TEST_CASE( test_invalid_sheet_named_formula )
{
    set_value_command( *s, sheet_range( sheet_point( 0, 0 ) ), "=Sheet2!test" ).execute();
    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *s, sheet_range( sheet_point( 0, 0 ) ) ) ), variant( variant::error_name ) );
    BOOST_CHECK_EQUAL( execute_fetch( get_formula_command( *s, sheet_range( sheet_point( 0, 0 ) ) ) ), variant( "=Sheet2!test" ) );
}

BOOST_AUTO_TEST_CASE( test_invalid_book_and_sheet_named_formula )
{
    set_value_command( *s, sheet_range( sheet_point( 0, 0 ) ), "=[book1]Sheet2!test" ).execute();
    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *s, sheet_range( sheet_point( 0, 0 ) ) ) ), variant( variant::error_name ) );
    BOOST_CHECK_EQUAL( execute_fetch( get_formula_command( *s, sheet_range( sheet_point( 0, 0 ) ) ) ), variant( "=[book1]Sheet2!test" ) );
}

BOOST_AUTO_TEST_CASE( reference_area_to_cell )
{

    range A1 = ws->range( sheet_point( 0, 0 ) );
    A1.value( *s, variant( 1.0 ) );
    range B1 = ws->range( sheet_point( 0, 1 ) );
    B1.value( *s, variant( 2.0 ) );
    range C1 = ws->range( sheet_point( 0, 2 ) );
    C1.value( *s, variant( "=SUM(A1:B1)" ) );

    {
        BOOST_CHECK_EQUAL( C1.value( *s ), variant( 3.0 ) );
    }

    C1.value( *s, variant( "=A1" ) );

    {
        BOOST_CHECK_EQUAL( C1.value( *s ), variant( 1.0 ) );
    }
}

BOOST_AUTO_TEST_CASE( reference_cell_to_area )
{
    range A1 = ws->range( sheet_point( 0, 0 ) );
    A1.value( *s, variant( 1.0 ) );
    range B1 = ws->range( sheet_point( 0, 1 ) );
    B1.value( *s, variant( 2.0 ) );
    range C1 = ws->range( sheet_point( 0, 2 ) );

    C1.value( *s, variant( "=A1" ) );

    {
        BOOST_CHECK_EQUAL( C1.value( *s ), variant( 1.0 ) );
    }

    C1.value( *s, variant( "=SUM(A1:B1)" ) );

    {
        BOOST_CHECK_EQUAL( C1.value( *s ), variant( 3.0 ) );
    }
}

BOOST_AUTO_TEST_CASE( reference_cell_to_cell )
{
    range A1 = ws->range( sheet_point( 0, 0 ) );
    A1.value( *s, variant( 1.0 ) );
    range B1 = ws->range( sheet_point( 0, 1 ) );
    B1.value( *s, variant( 2.0 ) );
    range C1 = ws->range( sheet_point( 0, 2 ) );

    C1.value( *s, variant( "=SUM(A1;B1)" ) );

    {
        BOOST_CHECK_EQUAL( C1.value( *s ), variant( 3.0 ) );
    }

    C1.value( *s, variant( "=SUM(A1;B2)" ) );

    {
        BOOST_CHECK_EQUAL( C1.value( *s ), variant( 1.0 ) );
    }
}


BOOST_AUTO_TEST_CASE( reference_area_to_area )
{
    range A1 = ws->range( sheet_point( 0, 0 ) );
    A1.value( *s, variant( 1.0 ) );
    range B1 = ws->range( sheet_point( 0, 1 ) );
    B1.value( *s, variant( 2.0 ) );
    range C1 = ws->range( sheet_point( 0, 2 ) );

    C1.value( *s, variant( "=SUM(A1:B1;B2)" ) );

    {
        BOOST_CHECK_EQUAL( C1.value( *s ), variant( 3.0 ) );
    }

    C1.value( *s, variant( "=SUM(A1:B1;B3)" ) );
    B1.value( *s, variant( 1.0 ) );

    {
        BOOST_CHECK_EQUAL( C1.value( *s ), variant( 2.0 ) );
    }
}

BOOST_AUTO_TEST_CASE( reference_cell_then_overwrite_it )
{
    range A1 = ws->range( sheet_point( 0, 0 ) );
    A1.value( *s, variant( 1.0 ) );
    range B1 = ws->range( sheet_point( 0, 1 ) );
    B1.value( *s, variant( 2.0 ) );
    range C1 = ws->range( sheet_point( 0, 2 ) );

    C1.value( *s, variant( "=A1" ) );

    {
        BOOST_CHECK_EQUAL( C1.value( *s ), variant( 1.0 ) );
    }

    B1.move( *s, A1 );

    {
        BOOST_CHECK_EQUAL( C1.value( *s ), variant( variant::error_ref ) );
        BOOST_CHECK_EQUAL( C1.formula( *s ), variant( "=" + variant( variant::error_ref ).as_string( s->locale() ) ) );
    }
}

BOOST_AUTO_TEST_CASE( reference_area_then_overwrite_it_completely )
{
    range A1 = ws->range( sheet_point( 0, 0 ) );
    A1.value( *s, variant( 1.0 ) );
    range B1 = ws->range( sheet_point( 0, 1 ) );
    B1.value( *s, variant( 2.0 ) );
    range C1 = ws->range( sheet_point( 0, 2 ) );

    C1.value( *s, variant( "=sum(A1:B1)" ) );

    {
        BOOST_CHECK_EQUAL( C1.value( *s ), variant( 3.0 ) );
    }

    move_range_command::result_type id = execute_fetch( move_range_command( *s, sheet_range( sheet_point( 1, 0 ), sheet_point( 1, 1 ) ) ) );
    paste_range_command( *s, sheet_range( sheet_point( 0, 0 ), sheet_point( 0, 1 ) ), id ).execute();

    {
        BOOST_CHECK_EQUAL( C1.value( *s ), variant( variant::error_ref ) );
        BOOST_CHECK_EQUAL( C1.formula( *s ), variant( "=SUM(" + variant( variant::error_ref ).as_string( s->locale() ) + ")" ) );
    }
}

BOOST_AUTO_TEST_CASE( reference_area_then_overwrite_it_partially )
{
    range A1 = ws->range( sheet_point( 0, 0 ) );
    A1.value( *s, variant( 1.0 ) );
    range B1 = ws->range( sheet_point( 0, 1 ) );
    B1.value( *s, variant( 2.0 ) );
    range C1 = ws->range( sheet_point( 0, 2 ) );

    C1.value( *s, variant( "=sum(A1:B1)" ) );

    {
        BOOST_CHECK_EQUAL( C1.value( *s ), variant( 3.0 ) );
        BOOST_CHECK_EQUAL( C1.formula( *s ), variant( "=SUM(A1:B1)" ) );
    }

    move_range_command::result_type id = execute_fetch( move_range_command( *s, sheet_range( sheet_point( 1, 0 ) ) ) );
    paste_range_command( *s, sheet_range( sheet_point( 0, 0 ) ), id ).execute();

    {
        BOOST_CHECK_EQUAL( C1.value( *s ), variant( 2.0 ) );
        BOOST_CHECK_EQUAL( C1.formula( *s ), variant( "=SUM(A1:B1)" ) );
    }
}

/*!
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
BOOST_AUTO_TEST_CASE( overwrite_referenced_region_test )
{
    {
        execute_fetch( set_value_command( *s, sheet_point( 0, 0 ), 10.0 ) );
        execute_fetch( set_value_command( *s, sheet_point( 1, 0 ), 20.0 ) );
        execute_fetch( set_value_command( *s, sheet_point( 2, 0 ), 30.0 ) );
        execute_fetch( set_value_command( *s, sheet_point( 3, 0 ), 40.0 ) );
        execute_fetch( set_value_command( *s, sheet_point( 4, 0 ), "=SUM(a1:a4)" ) );
        execute_fetch( paste_range_command( *s, sheet_point( 0, 0 ), execute_fetch( move_range_command( *s, sheet_range( sheet_point( 2, 0 ), sheet_point( 4, 0 ) ) ) ) ) );
        const variant formula = execute_fetch( get_formula_command( *s, sheet_point( 2, 0 ) ) );

        BOOST_CHECK_EQUAL( formula, "=SUM(A1:A2)" );
    }
}


/*!
 * (fschaper) this move operation practically overwrites C4 and C5, invalidating all
 * references to these cells since they are now practically deleted. C6 and C7 of the
 * range now create rewritten to become the 'new' C4 and C5. C3 didn't change and remains
 * as it was.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
BOOST_AUTO_TEST_CASE( overwrite_referenced_region_partially_with_formula_test )
{
    {
        execute_fetch( set_value_command( *s, sheet_point( 2, 2 ), 1.0 ) );
        execute_fetch( set_value_command( *s, sheet_point( 3, 2 ), 2.0 ) );
        execute_fetch( set_value_command( *s, sheet_point( 4, 2 ), 3.0 ) );
        execute_fetch( set_value_command( *s, sheet_point( 5, 2 ), 4.0 ) );
        execute_fetch( set_value_command( *s, sheet_point( 6, 2 ), 5.0 ) );
        execute_fetch( set_value_command( *s, sheet_point( 7, 2 ), "=SUM(C3;C4;C5;C6;C7)" ) );
        const variant value = execute_fetch( get_value_command( *s, sheet_point( 7, 2 ) ) );
        BOOST_CHECK_EQUAL( value, variant( 15.0 ) );
        execute_fetch( paste_range_command( *s, sheet_point( 3, 2 ), execute_fetch( move_range_command( *s, sheet_range( sheet_point( 5, 2 ), sheet_point( 7, 2 ) ) ) ) ) );
        const variant formula = execute_fetch( get_formula_command( *s, sheet_point( 5, 2 ) ) );

        BOOST_CHECK_EQUAL( formula, "=SUM(C3;#REF!;#REF!;C4;C5)" );
    }
}

/*!
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
BOOST_AUTO_TEST_CASE( overwrite_complete_referenced_region_with_formula_test )
{
    {
        execute_fetch( set_value_command( *s, sheet_point( 0, 0 ), 10.0 ) );
        execute_fetch( set_value_command( *s, sheet_point( 1, 0 ), "=SUM(a1)" ) );
        execute_fetch( paste_range_command( *s, sheet_point( 0, 0 ), execute_fetch( move_range_command( *s, sheet_point( 1, 0 ) ) ) ) );
        const variant formula = execute_fetch( get_formula_command( *s, sheet_point( 0, 0 ) ) );

        BOOST_CHECK_EQUAL( formula, "=SUM(#REF!)" );
    }
}

/*!
 * \brief
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
BOOST_AUTO_TEST_CASE( overwrite_referenced_test )
{
    {
        execute_fetch( set_value_command( *s, sheet_point( 0, 0 ), "=a2" ) );
        execute_fetch( delete_row_command( *s, 1, 1 ) );
        const variant formula = execute_fetch( get_formula_command( *s, sheet_point( 0, 0 ) ) );

        BOOST_CHECK_EQUAL( formula, "=#REF!" );
    }
}

/*!
 * \brief
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
BOOST_AUTO_TEST_CASE( overwrite_referenced_2_test )
{
    {
        execute_fetch( set_value_command( *s, sheet_point( 7, 2 ), "11" ) );
        execute_fetch( set_value_command( *s, sheet_point( 3, 1 ), "=c8" ) );
        execute_fetch( delete_row_command( *s, 7, 1 ) );
        const variant formula = execute_fetch( get_formula_command( *s, sheet_point( 3, 1 ) ) );

        BOOST_CHECK_EQUAL( formula, "=#REF!" );
    }
}

/*!
 * \brief
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
BOOST_AUTO_TEST_CASE( overwrite_referenced_3_test )
{
    execute_fetch( set_value_command( *s, sheet_point( 0, 0 ), "=A2:B10" ) );
    execute_fetch( delete_row_command( *s, 1, 3 ) );
    const variant formula = execute_fetch( get_formula_command( *s, sheet_point( 0, 0 ) ) );

    BOOST_CHECK_EQUAL( formula, "=A2:B7" );
}

/*!
 * \brief
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
BOOST_AUTO_TEST_CASE( delete_precedents_by_delete_column_and_check_formula_test )
{
    {
        execute_fetch( set_value_command( *s, sheet_point( 1, 0 ), 0.0 ) );
        execute_fetch( set_value_command( *s, sheet_point( 1, 1 ), 1.0 ) );
        execute_fetch( set_value_command( *s, sheet_point( 1, 2 ), 2.0 ) );
        execute_fetch( set_value_command( *s, sheet_point( 1, 3 ), 3.0 ) );
        execute_fetch( set_value_command( *s, sheet_point( 1, 4 ), "=SUM(b2;c2;d2)" ) );
        execute_fetch( delete_column_command( *s, 1, 3 ) );
        const variant formula = execute_fetch( get_formula_command( *s, sheet_point( 1, 1 ) ) );

        BOOST_CHECK_EQUAL( formula, "=SUM(#REF!;#REF!;#REF!)" );
    }
}

/*!
 * \brief
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
BOOST_AUTO_TEST_CASE( delete_precedents_by_delete_row_and_check_formula_test )
{
    {
        execute_fetch( set_value_command( *s, sheet_point( 0, 1 ), 0.0 ) );
        execute_fetch( set_value_command( *s, sheet_point( 1, 1 ), 1.0 ) );
        execute_fetch( set_value_command( *s, sheet_point( 2, 1 ), 2.0 ) );
        execute_fetch( set_value_command( *s, sheet_point( 3, 1 ), 3.0 ) );
        execute_fetch( set_value_command( *s, sheet_point( 4, 1 ), "=SUM(b2;b3;b4)" ) );
        execute_fetch( delete_row_command( *s, 1, 3 ) );
        const variant formula = execute_fetch( get_formula_command( *s, sheet_point( 1, 1 ) ) );

        BOOST_CHECK_EQUAL( formula, "=SUM(#REF!;#REF!;#REF!)" );
    }
}

/*!
 * \brief
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
BOOST_AUTO_TEST_CASE( overwrite_referenced_5_test )
{
    {
        execute_fetch( set_value_command( *s, sheet_point( 0, 0 ), "=b1" ) );
        execute_fetch( delete_column_command( *s, 1, 1 ) );
        const variant formula = execute_fetch( get_formula_command( *s, sheet_point( 0, 0 ) ) );

        BOOST_CHECK_EQUAL( formula, "=#REF!" );
    }
}

BOOST_AUTO_TEST_CASE( reference_area_then_move_one_column_over_it )
{
    range B2 = ws->range( sheet_point( 1, 1 ) );
    B2.value( *s, variant( "=D3:E4" ) );

    move_range_command::result_type id = execute_fetch( move_range_command( *s, sheet_range( sheet_point( 0, 5 ), sheet_point( 12, 5 ) ) ) );
    paste_range_command( *s, sheet_range( sheet_point( 0, 4 ) ), id ).execute();

    {
        BOOST_CHECK_EQUAL( B2.formula( *s ), variant( "=D3:E4" ) );
    }
}

BOOST_AUTO_TEST_CASE( reference_area_then_move_two_columns_over_it )
{
    range B2 = ws->range( sheet_point( 1, 1 ) );
    B2.value( *s, variant( "=D3:E4" ) );

    move_range_command::result_type id =  execute_fetch( move_range_command( *s, sheet_range( sheet_point( 0, 5 ), sheet_point( 12, 6 ) ) ) );
    paste_range_command( *s, sheet_range( sheet_point( 0, 4 ) ), id ).execute();

    {
        BOOST_CHECK_EQUAL( B2.formula( *s ), variant( "=D3:D4" ) );
    }
}

//same as above, but bigger used range
BOOST_AUTO_TEST_CASE( reference_area_then_move_two_columns_over_it_bigger_used_range )
{
    range B2 = ws->range( sheet_point( 1, 1 ) );
    B2.value( *s, variant( "=D3:E4" ) );
    //this is done to get a bigger used range
    ws->range( sheet_point( 12, 12 ) ).value( *s, variant( 4.0 ) );

    move_range_command::result_type id =  execute_fetch( move_range_command( *s, sheet_range( sheet_point( 0, 5 ), sheet_point( 12, 6 ) ) ) );
    paste_range_command( *s, sheet_range( sheet_point( 0, 4 ) ), id ).execute();

    {
        BOOST_CHECK_EQUAL( B2.formula( *s ), variant( "=D3:D4" ) );
    }
}

BOOST_AUTO_TEST_CASE( reference_area_then_enlarge_it_by_moving_part_of_the_last_column )
{
    range B2 = ws->range( sheet_point( 1, 1 ) );
    B2.value( *s, variant( "=D3:E4" ) );

    move_range_command::result_type id =  execute_fetch( move_range_command( *s, sheet_range( sheet_point( 1, 4 ), sheet_point( 5, 4 ) ) ) );
    paste_range_command( *s, sheet_range( sheet_point( 1, 6 ) ), id ).execute();

    {
        BOOST_CHECK_EQUAL( B2.formula( *s ), variant( "=D3:G4" ) );
    }
}

BOOST_AUTO_TEST_CASE( reference_cell_then_delete_its_row )
{
    range A1 = ws->range( sheet_point( 0, 0 ) );
    A1.value( *s, variant( 1.0 ) );
    range B1 = ws->range( sheet_point( 0, 1 ) );
    B1.value( *s, variant( 2.0 ) );
    range C1 = ws->range( sheet_point( 0, 2 ) );
    range C2 = ws->range( sheet_point( 1, 2 ) );

    C2.value( *s, variant( "=A1" ) );

    {
        BOOST_CHECK_EQUAL( C1.value( *s ), variant() );
        BOOST_CHECK_EQUAL( C2.value( *s ), variant( 1.0 ) );
    }

    delete_row_command( *s, 0, 1 ).execute();

    {
        BOOST_CHECK_EQUAL( C1.value( *s ), variant( variant::error_ref ) );
        BOOST_CHECK_EQUAL( C1.formula( *s ), variant( "=" + variant( variant::error_ref ).as_string( s->locale() ) ) );
        BOOST_CHECK_EQUAL( C2.value( *s ), variant() );
    }
}

BOOST_AUTO_TEST_CASE( reference_cell_then_delete_its_column )
{
    range A1 = ws->range( sheet_point( 0, 0 ) );
    A1.value( *s, variant( 1.0 ) );
    range B1 = ws->range( sheet_point( 0, 1 ) );

    range C1 = ws->range( sheet_point( 0, 2 ) );

    C1.value( *s, variant( "=A1" ) );

    {
        BOOST_CHECK_EQUAL( B1.value( *s ), variant() );
        BOOST_CHECK_EQUAL( C1.value( *s ), variant( 1.0 ) );
    }

    delete_column_command( *s, 0, 1 ).execute();

    {

        BOOST_CHECK_EQUAL( B1.value( *s ), variant( variant::error_ref ) );
        BOOST_CHECK_EQUAL( B1.formula( *s ), variant( "=" + variant( variant::error_ref ).as_string( s->locale() ) ) );
        BOOST_CHECK_EQUAL( C1.value( *s ), variant() );
    }
}

BOOST_AUTO_TEST_CASE( reference_cell_then_delete_its_row2 )
{
    range C8 = ws->range( sheet_point( 7, 2 ) );
    C8.value( *s, variant( 1.0 ) );

    range B4 = ws->range( sheet_point( 3, 1 ) );

    B4.value( *s, variant( "=C8" ) );

    {
        BOOST_CHECK_EQUAL( B4.value( *s ), variant( 1.0 ) );
    }

    delete_row_command( *s, 7, 1 ).execute();

    {
        BOOST_CHECK_EQUAL( B4.value( *s ), variant( variant::error_ref ) );
        BOOST_CHECK_EQUAL( B4.formula( *s ), variant( "=" + variant( variant::error_ref ).as_string( s->locale() ) ) );
    }
}

BOOST_AUTO_TEST_CASE( reference_area_then_delete_last_column )
{
    range B2 = ws->range( sheet_point( 1, 1 ) );

    B2.value( *s, variant( "=C5:E6" ) );

    delete_column_command( *s, 4, 1 ).execute();

    {
        BOOST_CHECK_EQUAL( B2.formula( *s ), variant( "=C5:D6" ) );
    }
}

BOOST_AUTO_TEST_CASE( reference_area_then_insert_columns )
{
    range B2 = ws->range( sheet_point( 1, 1 ) );

    B2.value( *s, variant( "=C5:E6" ) );

    insert_column_command( *s, 4, 3 ).execute();

    {
        BOOST_CHECK_EQUAL( B2.formula( *s ), variant( "=C5:H6" ) );
    }
}

BOOST_AUTO_TEST_CASE( reference_area_then_insert_rows )
{
    range B2 = ws->range( sheet_point( 1, 1 ) );

    B2.value( *s, variant( "=C5:D7" ) );

    insert_row_command( *s, 6, 3 ).execute();

    {
        BOOST_CHECK_EQUAL( B2.formula( *s ), variant( "=C5:D10" ) );
    }
}

BOOST_AUTO_TEST_CASE( copy_reference_to_other_sheet_create_ref_error_there )
{
    //we need two worksheets!
    create_worksheet_command( *s, "Sheet2" ).execute();
    sheet_range b2 = sheet_range( sheet_point( 1, 1 ) );
    sheet_range a1 = sheet_range( sheet_point( 0, 0 ) );
    set_value_command( *s, b2, "=sheet2!a1" ).execute();

    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *s, b2 ) ), variant( 0.0 ) );
    BOOST_CHECK_EQUAL( execute_fetch( get_formula_command( *s, b2 ) ), variant( "=Sheet2!A1" ) );

    copy_range_command::result_type id = execute_fetch( copy_range_command( *s, b2 ) );
    select_worksheet_command( *s, "Sheet2" ).execute();
    paste_range_command( *s, a1, id ).execute();

    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *s, a1 ) ), variant( variant::error_ref ) );
    BOOST_CHECK_EQUAL( execute_fetch( get_formula_command( *s, a1 ) ), variant( "=Sheet2!" + variant( variant::error_ref ).as_string( s->locale() ) ) );

}

BOOST_AUTO_TEST_CASE( reference_other_sheet_then_delete_other_sheet )
{
    //we need two worksheets!
    create_worksheet_command( *s, "Sheet2" ).execute();
    sheet_range b2 = sheet_range( sheet_point( 1, 1 ) );
    sheet_range a1 = sheet_range( sheet_point( 0, 0 ) );
    set_value_command( *s, b2, "=sheet2!a1" ).execute();

    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *s, b2 ) ), variant( 0.0 ) );
    BOOST_CHECK_EQUAL( execute_fetch( get_formula_command( *s, b2 ) ), variant( "=Sheet2!A1" ) );

    select_worksheet_command( *s, "Sheet2" ).execute();
    set_value_command( *s, a1, 5.0 ).execute();
    remove_worksheet_command( *s, s->selected().worksheet().lock()->uuid() ).execute();
    select_worksheet_command( *s, "ws" ).execute();

    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *s, b2 ) ), variant( variant::error_ref ) );
    BOOST_CHECK_EQUAL( execute_fetch( get_formula_command( *s, b2 ) ), variant( "=" + variant( variant::error_ref ).as_string( s->locale() ) ) );
}

BOOST_AUTO_TEST_CASE( reference_empty_cell_on_other_sheet_then_delete_other_sheet )
{
    //we need two worksheets!
    create_worksheet_command( *s, "Sheet2" ).execute();
    select_worksheet_command( *s, "ws" ).execute();
    sheet_range b2 = sheet_range( sheet_point( 1, 1 ) );
    sheet_range a1 = sheet_range( sheet_point( 0, 0 ) );
    set_value_command( *s, b2, "=sheet2!a1" ).execute();

    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *s, b2 ) ), variant( 0.0 ) );
    BOOST_CHECK_EQUAL( execute_fetch( get_formula_command( *s, b2 ) ), variant( "=Sheet2!A1" ) );

    select_worksheet_command( *s, "Sheet2" ).execute();
    remove_worksheet_command( *s, s->selected().worksheet().lock()->uuid() ).execute();
    select_worksheet_command( *s, "ws" ).execute();

    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *s, b2 ) ), variant( variant::error_ref ) );
    BOOST_CHECK_EQUAL( execute_fetch( get_formula_command( *s, b2 ) ), variant( "=" + variant( variant::error_ref ).as_string( s->locale() ) ) );
}

BOOST_AUTO_TEST_CASE( relative_reference_cell_test )
{
    sheet_range b2 = sheet_range( sheet_point( 1, 1 ) );
    set_value_command( *s, b2, "=a1" ).execute();
    BOOST_CHECK_EQUAL( execute_fetch( get_formula_command( *s, b2 ) ), variant( "=A1" ) );
}

BOOST_AUTO_TEST_CASE( relative_row_reference_cell_test )
{
    sheet_range b2 = sheet_range( sheet_point( 1, 1 ) );
    set_value_command( *s, b2, "=$a1" ).execute();
    BOOST_CHECK_EQUAL( execute_fetch( get_formula_command( *s, b2 ) ), variant( "=$A1" ) );
}

BOOST_AUTO_TEST_CASE( relative_column_reference_cell_test )
{
    sheet_range b2 = sheet_range( sheet_point( 1, 1 ) );
    set_value_command( *s, b2, "=a$1" ).execute();
    BOOST_CHECK_EQUAL( execute_fetch( get_formula_command( *s, b2 ) ), variant( "=A$1" ) );
}

BOOST_AUTO_TEST_CASE( absolute_reference_cell_test )
{
    sheet_range b2 = sheet_range( sheet_point( 1, 1 ) );
    set_value_command( *s, b2, "=$a$1" ).execute();
    BOOST_CHECK_EQUAL( execute_fetch( get_formula_command( *s, b2 ) ), variant( "=$A$1" ) );
}

BOOST_AUTO_TEST_CASE( change_reference_type_cell_test )
{
    sheet_range b2 = sheet_range( sheet_point( 1, 1 ) );
    set_value_command( *s, b2, "=a1" ).execute();
    BOOST_CHECK_EQUAL( execute_fetch( get_formula_command( *s, b2 ) ), variant( "=A1" ) );
    set_value_command( *s, b2, "=$a1" ).execute();
    BOOST_CHECK_EQUAL( execute_fetch( get_formula_command( *s, b2 ) ), variant( "=$A1" ) );
    set_value_command( *s, b2, "=a$1" ).execute();
    BOOST_CHECK_EQUAL( execute_fetch( get_formula_command( *s, b2 ) ), variant( "=A$1" ) );
    set_value_command( *s, b2, "=$a$1" ).execute();
    BOOST_CHECK_EQUAL( execute_fetch( get_formula_command( *s, b2 ) ), variant( "=$A$1" ) );
}

BOOST_AUTO_TEST_CASE( relative_reference_range_test )
{
    sheet_range b2 = sheet_range( sheet_point( 1, 1 ) );
    set_value_command( *s, b2, "=a1:a2" ).execute();
    BOOST_CHECK_EQUAL( execute_fetch( get_formula_command( *s, b2 ) ), variant( "=A1:A2" ) );
}

BOOST_AUTO_TEST_CASE( relative_row_reference_range_test1 )
{
    sheet_range b2 = sheet_range( sheet_point( 1, 1 ) );
    set_value_command( *s, b2, "=$a1:$a2" ).execute();
    BOOST_CHECK_EQUAL( execute_fetch( get_formula_command( *s, b2 ) ), variant( "=$A1:$A2" ) );
}

BOOST_AUTO_TEST_CASE( relative_row_reference_range_test2 )
{
    sheet_range b2 = sheet_range( sheet_point( 1, 1 ) );
    set_value_command( *s, b2, "=a1:$a2" ).execute();
    BOOST_CHECK_EQUAL( execute_fetch( get_formula_command( *s, b2 ) ), variant( "=A1:$A2" ) );
}

BOOST_AUTO_TEST_CASE( relative_column_reference_range_test1 )
{
    sheet_range b2 = sheet_range( sheet_point( 1, 1 ) );
    set_value_command( *s, b2, "=a$1:a2" ).execute();
    BOOST_CHECK_EQUAL( execute_fetch( get_formula_command( *s, b2 ) ), variant( "=A$1:A2" ) );
}

BOOST_AUTO_TEST_CASE( relative_column_reference_range_test2 )
{
    sheet_range b2 = sheet_range( sheet_point( 1, 1 ) );
    set_value_command( *s, b2, "=a$1:a$2" ).execute();
    BOOST_CHECK_EQUAL( execute_fetch( get_formula_command( *s, b2 ) ), variant( "=A$1:A$2" ) );
}

BOOST_AUTO_TEST_CASE( absolute_reference_range_test1 )
{
    sheet_range b2 = sheet_range( sheet_point( 1, 1 ) );
    set_value_command( *s, b2, "=$a$1:a2" ).execute();
    BOOST_CHECK_EQUAL( execute_fetch( get_formula_command( *s, b2 ) ), variant( "=$A$1:A2" ) );
}

BOOST_AUTO_TEST_CASE( absolute_reference_range_test2 )
{
    sheet_range b2 = sheet_range( sheet_point( 1, 1 ) );
    set_value_command( *s, b2, "=$a$1:$a$2" ).execute();
    BOOST_CHECK_EQUAL( execute_fetch( get_formula_command( *s, b2 ) ), variant( "=$A$1:$A$2" ) );
}

BOOST_AUTO_TEST_CASE( change_reference_type_range_test )
{
    sheet_range b2 = sheet_range( sheet_point( 1, 1 ) );
    set_value_command( *s, b2, "=a1:a2" ).execute();
    BOOST_CHECK_EQUAL( execute_fetch( get_formula_command( *s, b2 ) ), variant( "=A1:A2" ) );
    set_value_command( *s, b2, "=$a1:a2" ).execute();
    BOOST_CHECK_EQUAL( execute_fetch( get_formula_command( *s, b2 ) ), variant( "=$A1:A2" ) );
    set_value_command( *s, b2, "=a$1:a2" ).execute();
    BOOST_CHECK_EQUAL( execute_fetch( get_formula_command( *s, b2 ) ), variant( "=A$1:A2" ) );
    set_value_command( *s, b2, "=$a$1:a$2" ).execute();
    BOOST_CHECK_EQUAL( execute_fetch( get_formula_command( *s, b2 ) ), variant( "=$A$1:A$2" ) );
}

/*!
 * \brief
 * test case for ticket 7457
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
BOOST_AUTO_TEST_CASE( crash_on_drill_down_test )
{
    sheet_point a1 = sheet_point( 0, 0 );
    sheet_point b1 = sheet_point( 0, 1 );
    sheet_point c1 = sheet_point( 0, 2 );

    set_value_command( *s, a1 ,  "=rand()" ).execute();
    set_value_command( *s, c1 ,  "=$A1" ).execute();
    set_value_command( *s, b1 ,  "=a1" ).execute();
    clear_cells_command( *s, sheet_range( a1, c1 ), content_type::all ).execute();
    BOOST_CHECK_NO_THROW( set_value_command( *s, a1 ,  "=rand()" ).execute() );
}

BOOST_AUTO_TEST_CASE( reference_whole_column )
{
    sheet_point a1 = sheet_point( 0, 0 );
    sheet_point b1 = sheet_point( 0, 1 );
    sheet_point c1 = sheet_point( 0, 2 );

    set_value_command( *s, a1 ,  "=sum($2:$3)" ).execute();
    set_value_command( *s, c1 ,  "=4" ).execute();
    set_value_command( *s, b1 ,  "=2" ).execute();
    get_value_command gvc( *s, a1 );
    BOOST_CHECK_NO_THROW( set_value_command( *s, a1 ,  "=rand()" ).execute() );
}

/*!
 * \brief
 * tests for ticket 7924
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
BOOST_AUTO_TEST_CASE( reference_array_test )
{
    sheet_point a1 = sheet_point( 0, 0 );
    sheet_point a2 = sheet_point( 1, 0 );
    sheet_point a3 = sheet_point( 2, 0 );
    sheet_point a4 = sheet_point( 3, 0 );
    sheet_point b1 = sheet_point( 0, 1 );
    sheet_point b2 = sheet_point( 1, 1 );
    sheet_point b3 = sheet_point( 2, 1 );
    sheet_point b4 = sheet_point( 3, 1 );
    sheet_point c1 = sheet_point( 0, 2 );
    sheet_point c2 = sheet_point( 1, 2 );
    sheet_point c3 = sheet_point( 2, 2 );
    sheet_point c4 = sheet_point( 3, 2 );
    sheet_point d1 = sheet_point( 0, 3 );
    sheet_point d2 = sheet_point( 1, 3 );
    set_array_value_command( *s, sheet_range( b1, b3 ), "=c1:c4" ).execute();
    set_value_command( *s, a1, 1.0 ).execute();
    set_value_command( *s, a2, 2.0 ).execute();
    set_value_command( *s, a3, 3.0 ).execute();
    set_value_command( *s, c1, "c1_val" ).execute();
    set_value_command( *s, c2, "c2_val" ).execute();
    set_value_command( *s, c3, "c3_val" ).execute();

    set_value_command( *s, d1, "=VLOOKUP(d2;a1:b3;2;FALSE)" ).execute();
    set_value_command( *s, d2, 1.0 ).execute();

    get_value_command gvc_d1( *s, d1 );
    get_value_command gvc_b1( *s, b1 );
    variant check = execute_fetch( gvc_b1 );
    BOOST_CHECK_EQUAL( execute_fetch( gvc_d1 ), execute_fetch( gvc_b1 ) );
}

BOOST_AUTO_TEST_CASE( reference_array_test2 )
{
    sheet_point a1 = sheet_point( 0, 0 );
    sheet_point a2 = sheet_point( 1, 0 );
    sheet_point a3 = sheet_point( 2, 0 );
    sheet_point a4 = sheet_point( 3, 0 );
    sheet_point b1 = sheet_point( 0, 1 );
    sheet_point b2 = sheet_point( 1, 1 );
    sheet_point b3 = sheet_point( 2, 1 );
    sheet_point b4 = sheet_point( 3, 1 );
    sheet_point c1 = sheet_point( 0, 2 );
    sheet_point c2 = sheet_point( 1, 2 );
    sheet_point c3 = sheet_point( 2, 2 );
    sheet_point c4 = sheet_point( 3, 2 );
    sheet_point d1 = sheet_point( 0, 3 );
    sheet_point d2 = sheet_point( 1, 3 );
    set_value_command( *s, a1, 1.0 ).execute();
    set_value_command( *s, a2, 2.0 ).execute();
    set_value_command( *s, a3, 3.0 ).execute();
    set_value_command( *s, c1, "=rand()" ).execute();
    set_value_command( *s, c2, "c2_val" ).execute();
    set_value_command( *s, c3, "c3_val" ).execute();

    set_value_command( *s, d1, "=VLOOKUP(d2;a1:b3;2;FALSE)" ).execute();
    set_value_command( *s, d2, 1.0 ).execute();
    set_array_value_command( *s, sheet_range( b1, b3 ), "=c1:c4" ).execute();

    get_value_command gvc_d1( *s, d1 );
    get_value_command gvc_b1( *s, b1 );
    BOOST_CHECK_EQUAL( execute_fetch( gvc_d1 ), execute_fetch( gvc_b1 ) );
}

BOOST_AUTO_TEST_SUITE_END()
