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

#include <cstdlib> // std::size_t
#include <cassert>
#include <vector>
#include <boost/test/unit_test.hpp>
#include <map>
#include <set>

#include <wss/point.hpp>
#include <wss/rectangle.hpp>
#include <wss/variant.hpp>
#include <wss/definition.hpp>
#include <wss/application.hpp>
#include <wss/sheet_point.hpp>
#include <wss/type.hpp>
#include <wss/locale.hpp>
#include <wss/command.hpp>
#include <wss/exception.hpp>
#include <wss/a1conversion.hpp>
#include <wss/i_named_formula_manager.hpp>
#include <wss/named_formula_accessor.hpp>
#include <wss/session_handler.hpp>
#include <wss/session.hpp>
#include <wss/server.hpp>
#include <wss/execute_fetch.hpp>
#include <wss/sheet_dimension.hpp>

/************************************************************************
 * tests for named formulas (nf):
 * the following tests need to be done for worksheet (ws1) scoped nfs and
 * workbook (wb1) scoped nfs
 *
 ***  - - - basic checks - - -
 * 1 reference a nf in a formula that doesn't exist
 * 2 reference a nf in a formula that does exist
 * 3 change value of nf and check if updates are done
 * 4 remove nf and check for #name errors
 * 5 create 2 references to 1 nf, then remove one and check updates/flag_dirty
 *
 ***  - - - basic scope checks - - -
 * 6 create nf of name "test" in ws1 and then in wb1 - reference without explicitly stating the scope - should reference ws1 one
 * 7 create nf of name "test" in ws1 and then in wb1 - reference with explicitly stating the scope (ws1/wb1)- should reference right one
 * 8 create nf of the same name in ws1 and wb1 remove nf in ws1/wb1 and check for #name errors if scope was explicitly stated
 * 9 create nf of the same name in ws1 and wb1 remove nf in ws1/wb1 and check for right values - remaining one should be used if
scope wasn't explicitly stated
 *
 ***  - - - basic copy/move checks (the cell containing the nf gets moved/copied) - - -
 * 10_1 move cell with nf (B1=2, B2=3, test=$B$1+$B$2, created at position A1, A1=test, move A1->A2 =>
A1:value=empty, A2:value=5  move A2->A1 => value=5)
 * 10_2 move cell with nf (B1=2, B2=3, test=B1+B2, created at position A1, A1=test, move A1->A2 =>
A1:value=empty, A2:value=5 move A2->A1 => A1:value=5, A2:value=empty)
 * 11_1 copy cell with nf (B1=2, B2=3, test=$B$1+$B$2, created at position A1, A1=test, copy A1->A2 =>
A1:value=5, A2:value=5 copy A2->A1 => A1:value=5, A2:value=5)
 * 11_2 copy cell with nf (B1=2, B2=3, test=B1+B2, created at position A1, A1=test, copy A1->A2 =>
A1:value=5, A2:value=3 copy A2->A1 => value=5)
 ***  - - - basic copy/move checks (the cell/area referenced in the nf gets moved/copied) - - -
 * 11_3 move cell inside nf (B1=2, B2=3, test=$B$1+$B$2, created at position A1, move B1:B2->B2:B3 => nf_value=5)
 * 11_4 move cell inside nf (B1=2, B2=3, test=B1+B2, created at position A1, move B1:B2->B2:B3 => nf_value=0)
 *
 ***  - - - basic standalone nf checks - - -
 * 12 create value of a nf outside of a cell
 * 13 create value of a nf that doesn't exist and check for exception
 * 14 create value of a nf that does exist but is in the wrong scope and check for exception
 * 15 change name of nf to a name that doesn't exist yet
 * 16_1 change name of nf to a name that does already exist
 * 16_2 check case sensitivity/insensitivity
 *
 ***  - - - basic absolute reference checks - - -
 * 17 create value of a nf that does have absolute references (A1=3, test=$A$1, created at position A1) => value=3
 * 18 create value of a nf that does have absolute references (A1=3, test=$A$1, created at position B2) => value=3
 * 19 create value of a nf that does have absolute references (B1=3, B2=3, test=$B$1+$B$2, created at position A1) => value=6
 *
 ***  - - - basic relative reference checks - - -
 * 20 create value of a nf that does have relative references (A1=3, test=A1, created at position A1) => value=3
 * 21 create value of a nf that does have relative references (A1=3, test=A1, created at position B2, evaluate at position B2 and A1) => value=3 / value=0
 * 22 create value of a nf that does have relative references (B1=2, B2=3, test=B1+B2, created at position A1, evaluate at position A1 and A2) => value=5 /value=3
 *
 ************************************************************************/

struct named_formula_fixture {
    named_formula_fixture() {
        server::instance().startup();
        active_session = server::instance().session_handler().create( locale::create( "en-US" ) );

        create_application_command( *active_session, "my application" ).execute();
        select_application_command( *active_session, "my application" ).execute();
        create_workbook_command( *active_session, "wb1" ).execute();
        select_workbook_command( *active_session, "wb1" ).execute();
        create_worksheet_command( *active_session, "ws1" ).execute();
        select_worksheet_command( *active_session, "ws1" ).execute();

        wb1 = active_session->selected().workbook().lock();
        ws1 = active_session->selected().worksheet().lock();

        create_worksheet_command( *active_session, "my_worksheet_2" ).execute();
        select_worksheet_command( *active_session, "my_worksheet_2" ).execute();

        ws2 = active_session->selected().worksheet().lock();


    }

    ~named_formula_fixture() {
        try {
            ws1.reset();
            ws2.reset();
            wb1.reset();
            active_session->revitalize();
            server::instance().shutdown();
        } catch ( const std::exception& e ) {
            e.what();
            assert( !"this may never throw" );
        }
    }

    locked_session active_session;
    shared_worksheet_type ws1;
    shared_worksheet_type ws2;
    shared_workbook_type wb1;
};

BOOST_FIXTURE_TEST_SUITE( test_named_formula, named_formula_fixture );

#define check_formula_and_value( s, r, expected_v, expected_formula ) { BOOST_CHECK_EQUAL( (expected_formula),  (r).formula( s ) ); BOOST_CHECK_EQUAL( (r).value( s ), (expected_v) ); }

#define REENABLE_PASSED_TESTS 1

#ifdef REENABLE_PASSED_TESTS

BOOST_AUTO_TEST_CASE( test1 )
{
    range A1 = ws1->range( sheet_range( sheet_point( 0, 0 ) ) );
    range B2 = ws1->range( sheet_range( sheet_point( 1, 1 ) ) );
    range c3 = ws1->range( sheet_range( sheet_point( 2, 2 ) ) );
    range d4 = ws1->range( sheet_range( sheet_point( 3, 3 ) ) );

    //1 reference a named formula that doesn't exist yet!
    BOOST_CHECK_NO_THROW( A1.value( *active_session, variant( "=test" ) ) );
    BOOST_CHECK_EQUAL( variant( "=test" ),  A1.formula( *active_session ) );
    BOOST_CHECK_EQUAL( A1.value( *active_session ),  variant( variant::error_name ) );
}

BOOST_AUTO_TEST_CASE( test2a )
{
    range A1 = ws1->range( sheet_range( sheet_point( 0, 0 ) ) );
    ws1->select( active_session->selected() );
    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=1+2" ), named_formula_scope::worksheet_scope, ws1  ) );
    BOOST_CHECK_NO_THROW( A1.value( *active_session, variant( "=test" ) ) );
    BOOST_CHECK_EQUAL( variant( "=test" ),  A1.formula( *active_session ) );
    BOOST_CHECK_EQUAL( A1.value( *active_session ),  variant( 3.0 ) );
}

BOOST_AUTO_TEST_CASE( test2b )
{
    range A1 = ws1->range( sheet_range( sheet_point( 0, 0 ) ) );

    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=1+2" ), named_formula_scope::workbook_scope, ws1  ) );
    BOOST_CHECK_NO_THROW( A1.value( *active_session, variant( "=test" ) ) );
    BOOST_CHECK_EQUAL( variant( "=test" ), A1.formula( *active_session ) );
    BOOST_CHECK_EQUAL( A1.value( *active_session ), variant( 3.0 ) );
}

BOOST_AUTO_TEST_CASE( test3a )
{
    range A1 = ws1->range( sheet_range( sheet_point( 0, 0 ) ) );

    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=1+2" ), named_formula_scope::worksheet_scope, ws1  ) );
    BOOST_CHECK_NO_THROW( A1.value( *active_session, variant( "=test" ) ) );
    check_formula_and_value( *active_session, A1, variant( 3.0 ), variant( "=test" ) );
    //change the value and check if it gets recalculated
    BOOST_CHECK_NO_THROW( wb1->named_formulas().value( *active_session, named_formula_identifier( "test", ws1->uuid() ), variant( "=1000" ) ) );
    BOOST_CHECK_EQUAL( variant( "=test" ),  A1.formula( *active_session ) );
    BOOST_CHECK_EQUAL( A1.value( *active_session ),   variant( 1000.0 ) );
}

BOOST_AUTO_TEST_CASE( test3b )
{
    range A1 = ws1->range( sheet_range( sheet_point( 0, 0 ) ) );

    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=1+2" ), named_formula_scope::workbook_scope, ws1  ) );
    BOOST_CHECK_NO_THROW( A1.value( *active_session, variant( "=test" ) ) );
    check_formula_and_value( *active_session, A1, variant( 3.0 ), variant( "=test" ) );
    //change the value and check if it gets recalculated
    BOOST_CHECK_NO_THROW( wb1->named_formulas().value( *active_session, named_formula_identifier( "test",  boost::uuids::nil_uuid() ), variant( "=1000" ) ) );
    BOOST_CHECK_EQUAL( variant( "=test" ),  A1.formula( *active_session ) );
    BOOST_CHECK_EQUAL( A1.value( *active_session ),   variant( 1000.0 ) );
}

BOOST_AUTO_TEST_CASE( test4a )
{
    range A1 = ws1->range( sheet_range( sheet_point( 0, 0 ) ) );

    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=1+2" ), named_formula_scope::worksheet_scope, ws1  ) );
    BOOST_CHECK_NO_THROW( A1.value( *active_session, variant( "=test" ) ) );
    check_formula_and_value( *active_session, A1, variant( 3.0 ), variant( "=test" ) );
    BOOST_CHECK_NO_THROW( wb1->named_formulas().remove( *active_session, named_formula_identifier( "test", ws1->uuid() ) ) );
    check_formula_and_value( *active_session, A1, variant( variant::error_name ), variant( "=test" ) );
}

BOOST_AUTO_TEST_CASE( test4b )
{
    range A1 = ws1->range( sheet_range( sheet_point( 0, 0 ) ) );

    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=1+2" ), named_formula_scope::workbook_scope, ws1  ) );
    BOOST_CHECK_NO_THROW( A1.value( *active_session, variant( "=test" ) ) );
    check_formula_and_value( *active_session, A1, variant( 3.0 ), variant( "=test" ) );
    BOOST_CHECK_NO_THROW( wb1->named_formulas().remove( *active_session, named_formula_identifier( "test", boost::uuids::nil_uuid() ) ) );
    check_formula_and_value( *active_session, A1, variant( variant::error_name ), variant( "=test" ) );
}
BOOST_AUTO_TEST_CASE( test5a )
{
    range A1 = ws1->range( sheet_range( sheet_point( 0, 0 ) ) );
    range B2 = ws1->range( sheet_range( sheet_point( 1, 1 ) ) );

    wb1->named_formulas().create( *active_session, "test", variant( "=1+2" ), named_formula_scope::worksheet_scope, ws1  );
    A1.value( *active_session, variant( "=test" ) );
    B2.value( *active_session, variant( "=test+3" ) );

    check_formula_and_value( *active_session, A1, variant( 3.0 ), variant( "=test" ) );
    check_formula_and_value( *active_session, B2, variant( 6.0 ), variant( "=test+3" ) );
    //change the value and check if it gets recalculated
    BOOST_CHECK_NO_THROW( B2.value( *active_session, variant( 21.0 ) ) );
    check_formula_and_value( *active_session, A1, variant( 3.0 ), variant( "=test" ) );
    check_formula_and_value( *active_session, B2, variant( 21.0 ), variant( 21.0 ) );
}
BOOST_AUTO_TEST_CASE( test5b )
{
    range A1 = ws1->range( sheet_range( sheet_point( 0, 0 ) ) );
    range B2 = ws1->range( sheet_range( sheet_point( 1, 1 ) ) );

    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=1+2" ), named_formula_scope::workbook_scope, ws1  ) );
    BOOST_CHECK_NO_THROW( A1.value( *active_session, variant( "=test" ) ) );
    BOOST_CHECK_NO_THROW( B2.value( *active_session, variant( "=test+3" ) ) );
    check_formula_and_value( *active_session, A1, variant( 3.0 ), variant( "=test" ) );
    check_formula_and_value( *active_session, B2, variant( 6.0 ), variant( "=test+3" ) );
    BOOST_CHECK_NO_THROW( B2.value( *active_session, variant( 21.0 ) ) );
    check_formula_and_value( *active_session, A1, variant( 3.0 ), variant( "=test" ) );
    check_formula_and_value( *active_session, B2, variant( 21.0 ), variant( 21.0 ) );
}

//*6 create nf of name "test" in ws1 and then in wb1 - reference without explicitly stating the scope - should reference ws1 one
BOOST_AUTO_TEST_CASE( test6a )
{
    range A1 = ws1->range( sheet_range( sheet_point( 0, 0 ) ) );

    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=1+2" ), named_formula_scope::worksheet_scope, ws1  ) );
    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=13" ), named_formula_scope::workbook_scope, ws1  ) );
    BOOST_CHECK_NO_THROW( A1.value( *active_session, variant( "=test" ) ) );
    check_formula_and_value( *active_session, A1, variant( 3.0 ), variant( "=test" ) );
}

BOOST_AUTO_TEST_CASE( test6b )
{
    range A1 = ws1->range( sheet_range( sheet_point( 0, 0 ) ) );

    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=13" ), named_formula_scope::workbook_scope, ws1  ) );
    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=1+2" ), named_formula_scope::worksheet_scope, ws1  ) );
    BOOST_CHECK_NO_THROW( A1.value( *active_session, variant( "=test" ) ) );
    check_formula_and_value( *active_session, A1, variant( 3.0 ), variant( "=test" ) );
}


//*7 create nf of name "test" in ws1 and then in wb1 - reference with explicitly stating the scope (ws1/wb1)- should reference right one
BOOST_AUTO_TEST_CASE( test7a )
{
    range A1 = ws1->range( sheet_range( sheet_point( 0, 0 ) ) );
    range B2 = ws1->range( sheet_range( sheet_point( 1, 1 ) ) );

    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=1+2" ), named_formula_scope::worksheet_scope, ws1  ) );
    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=13" ), named_formula_scope::workbook_scope, ws1  ) );
    BOOST_CHECK_NO_THROW( A1.value( *active_session, variant( "=test" ) ) );
    BOOST_CHECK_NO_THROW( B2.value( *active_session, variant( "=my_worksheet_2!test" ) ) );

    check_formula_and_value( *active_session, A1, variant( 3.0 ), variant( "=test" ) );
    check_formula_and_value( *active_session, B2, variant( 13.0 ), variant( "=ws1!test" ) );
}

BOOST_AUTO_TEST_CASE( test7b )
{
    range A1 = ws1->range( sheet_range( sheet_point( 0, 0 ) ) );
    range B2 = ws1->range( sheet_range( sheet_point( 1, 1 ) ) );

    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=13" ), named_formula_scope::workbook_scope, ws1  ) );
    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=1+2" ), named_formula_scope::worksheet_scope, ws1  ) );
    BOOST_CHECK_NO_THROW( B2.value( *active_session, variant( "=my_worksheet_2!test" ) ) );
    BOOST_CHECK_NO_THROW( A1.value( *active_session, variant( "=test" ) ) );

    check_formula_and_value( *active_session, A1, variant( 3.0 ), variant( "=test" ) );
    check_formula_and_value( *active_session, B2, variant( 13.0 ), variant( "=ws1!test" ) );
}

//*8 create nf of the same name in ws1 and wb1 remove nf in ws1/wb1 and check for #name errors if scope was explicitly stated
BOOST_AUTO_TEST_CASE( test8a )
{
    range A1 = ws1->range( sheet_range( sheet_point( 0, 0 ) ) );
    range B2 = ws1->range( sheet_range( sheet_point( 1, 1 ) ) );

    create_named_formula_command( *active_session, "test", variant( "=1+2" ), ws1->uuid(), sheet_point( 0, 0 ), "worksheet_scope" ).execute();
    create_named_formula_command( *active_session, "test", variant( "=13" ), sheet_point( 0, 0 ), "wb scope!" ).execute();
    BOOST_CHECK_NO_THROW( A1.value( *active_session, variant( "=test" ) ) );
    BOOST_CHECK_NO_THROW( B2.value( *active_session, variant( "=my_worksheet_2!test" ) ) );
    BOOST_CHECK_NO_THROW( wb1->named_formulas().remove( *active_session, named_formula_identifier( "test", ws1->uuid() ) ) );

    check_formula_and_value( *active_session, A1, variant( 13.0 ), variant( "=test" ) );
    check_formula_and_value( *active_session, B2, variant( 13.0 ), variant( "=my_worksheet_2!test" ) );
}

BOOST_AUTO_TEST_CASE( test8b )
{
    range A1 = ws1->range( sheet_range( sheet_point( 0, 0 ) ) );
    range B2 = ws1->range( sheet_range( sheet_point( 1, 1 ) ) );

    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=1+2" ), named_formula_scope::worksheet_scope, ws1  ) );
    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=13" ), named_formula_scope::workbook_scope, ws1  ) );
    BOOST_CHECK_NO_THROW( A1.value( *active_session, variant( "=test" ) ) );
    BOOST_CHECK_NO_THROW( B2.value( *active_session, variant( "=my_worksheet_2!test" ) ) );

    BOOST_CHECK_NO_THROW( wb1->named_formulas().remove( *active_session, named_formula_identifier( "test", boost::uuids::nil_uuid() ) ) );
    check_formula_and_value( *active_session, A1, variant( 3.0 ), variant( "=test" ) );
    check_formula_and_value( *active_session, B2, variant( variant::error_name ), variant( "=my_worksheet_2!test" ) );
}

//*9 create nf of the same name in ws1 and wb1 remove nf in ws1/wb1 and check for right values - remaining one should be used if scope wasn't explicitly stated
BOOST_AUTO_TEST_CASE( test9a )
{
    range A1 = ws1->range( sheet_range( sheet_point( 0, 0 ) ) );

    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=1+2" ), named_formula_scope::worksheet_scope, ws1  ) );
    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=13" ), named_formula_scope::workbook_scope, ws1  ) );
    BOOST_CHECK_NO_THROW( A1.value( *active_session, variant( "=test" ) ) );

    BOOST_CHECK_NO_THROW( wb1->named_formulas().remove( *active_session, named_formula_identifier( "test", ws1->uuid() ) ) );
    check_formula_and_value( *active_session, A1, variant( 13.0 ), variant( "=test" ) );
}

BOOST_AUTO_TEST_CASE( test9b )
{
    range A1 = ws1->range( sheet_range( sheet_point( 0, 0 ) ) );

    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=1+2" ), named_formula_scope::worksheet_scope, ws1  ) );
    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=13" ), named_formula_scope::workbook_scope, ws1  ) );
    BOOST_CHECK_NO_THROW( A1.value( *active_session, variant( "=test" ) ) );

    BOOST_CHECK_NO_THROW( wb1->named_formulas().remove( *active_session, named_formula_identifier( "test", boost::uuids::nil_uuid() ) ) );
    check_formula_and_value( *active_session, A1, variant( 3.0 ), variant( "=test" ) );
}

//* 10_1 move cell with nf (B1=2, B2=3, test=1+2, created at position A1, A1=test, move A1->A2 =>
// A1:value=empty, A2:value=5  move A2->A1 => value=5)
BOOST_AUTO_TEST_CASE( test10_1a )
{
    range A1 = ws1->range( sheet_range( sheet_point( 0, 0 ) ) );
    range A2 = ws1->range( sheet_range( sheet_point( 1, 0 ) ) );
    range B1 = ws1->range( sheet_range( sheet_point( 0, 1 ) ) );
    range B2 = ws1->range( sheet_range( sheet_point( 1, 1 ) ) );
    BOOST_CHECK_NO_THROW( B1.value( *active_session, variant( 2.0 ) ) );
    BOOST_CHECK_NO_THROW( B2.value( *active_session, variant( 3.0 ) ) );

    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=1+2" ), named_formula_scope::worksheet_scope, ws1  ) );
    BOOST_CHECK_NO_THROW( A1.value( *active_session, variant( "=test" ) ) );

    BOOST_CHECK_NO_THROW( A1.move( *active_session, A2 ) );
    check_formula_and_value( *active_session, A1, variant(), variant() );
    check_formula_and_value( *active_session, A2, variant( 3.0 ), variant( "=test" ) );
    BOOST_CHECK_NO_THROW( A2.move( *active_session, A1 ) );
    check_formula_and_value( *active_session, A2, variant(), variant() );
    check_formula_and_value( *active_session, A1, variant( 3.0 ), variant( "=test" ) );
}

BOOST_AUTO_TEST_CASE( test10_1b )
{
    range A1 = ws1->range( sheet_range( sheet_point( 0, 0 ) ) );
    range A2 = ws1->range( sheet_range( sheet_point( 1, 0 ) ) );
    range B1 = ws1->range( sheet_range( sheet_point( 0, 1 ) ) );
    range B2 = ws1->range( sheet_range( sheet_point( 1, 1 ) ) );
    BOOST_CHECK_NO_THROW( B1.value( *active_session, variant( 2.0 ) ) );
    BOOST_CHECK_NO_THROW( B2.value( *active_session, variant( 3.0 ) ) );

    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=1+2" ), named_formula_scope::workbook_scope, ws1  ) );
    BOOST_CHECK_NO_THROW( A1.value( *active_session, variant( "=test" ) ) );

    BOOST_CHECK_NO_THROW( A1.move( *active_session, A2 ) );
    check_formula_and_value( *active_session, A1, variant(), variant() );
    check_formula_and_value( *active_session, A2, variant( 3.0 ), variant( "=test" ) );
    BOOST_CHECK_NO_THROW( A2.move( *active_session, A1 ) );
    check_formula_and_value( *active_session, A2, variant(), variant() );
    check_formula_and_value( *active_session, A1, variant( 3.0 ), variant( "=test" ) );
}


//* 10_2 move cell with nf ( B1 = 2, B2 = 3, test = B1 + B2, created at position A1, A1 = test, move A1->A2 =>
/*
A1: value = empty, A2: value = 3

    move A2->A1 =>

A1: value = 5, A2: value = empty )*/

BOOST_AUTO_TEST_CASE( test10_2a )
{
    range A1 = ws1->range( sheet_range( sheet_point( 0, 0 ) ) );
    range A2 = ws1->range( sheet_range( sheet_point( 1, 0 ) ) );
    range B1 = ws1->range( sheet_range( sheet_point( 0, 1 ) ) );
    range B2 = ws1->range( sheet_range( sheet_point( 1, 1 ) ) );
    BOOST_CHECK_NO_THROW( B1.value( *active_session, variant( 2.0 ) ) );
    BOOST_CHECK_NO_THROW( B2.value( *active_session, variant( 3.0 ) ) );

    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=B1+B2+b3+b4" ), named_formula_scope::worksheet_scope, ws1  ) );
    BOOST_CHECK_NO_THROW( A1.value( *active_session, variant( "=test" ) ) );

    check_formula_and_value( *active_session, A1, variant( 5.0 ), variant( "=test" ) );
    BOOST_CHECK_NO_THROW( A1.move( *active_session, A2 ) );
    check_formula_and_value( *active_session, A1, variant(), variant() );
    check_formula_and_value( *active_session, A2, variant( 3.0 ), variant( "=test" ) );
    BOOST_CHECK_NO_THROW( A2.move( *active_session, A1 ) );
    check_formula_and_value( *active_session, A2, variant(), variant() );
    start_new_calculation_command( *active_session ).execute();
    check_formula_and_value( *active_session, A1, variant( 5.0 ), variant( "=test" ) );
}

BOOST_AUTO_TEST_CASE( test10_2b )
{
    range A1 = ws1->range( sheet_range( sheet_point( 0, 0 ) ) );
    range A2 = ws1->range( sheet_range( sheet_point( 1, 0 ) ) );
    range B1 = ws1->range( sheet_range( sheet_point( 0, 1 ) ) );
    range B2 = ws1->range( sheet_range( sheet_point( 1, 1 ) ) );
    BOOST_CHECK_NO_THROW( B1.value( *active_session, variant( 2.0 ) ) );
    BOOST_CHECK_NO_THROW( B2.value( *active_session, variant( 3.0 ) ) );

    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=B1+B2" ), named_formula_scope::workbook_scope, ws1  ) );
    BOOST_CHECK_NO_THROW( A1.value( *active_session, variant( "=test" ) ) );

    BOOST_CHECK_NO_THROW( A1.move( *active_session, A2 ) );
    check_formula_and_value( *active_session, A1, variant(), variant() );
    check_formula_and_value( *active_session, A2, variant( 3.0 ), variant( "=test" ) );
    BOOST_CHECK_NO_THROW( A2.move( *active_session, A1 ) );
    check_formula_and_value( *active_session, A2, variant(), variant() );
    check_formula_and_value( *active_session, A1, variant( 5.0 ), variant( "=test" ) );
}

//*11_1 copy cell with nf (B1=2, B2=3, test=1+2, created at position A1, A1=test, copy A1->A2 =>
// A1:value=3, A2:value=3 copy A2->A1 => A1:value=3, A2:value=3)
BOOST_AUTO_TEST_CASE( test11_1a )
{
    range A1 = ws1->range( sheet_range( sheet_point( 0, 0 ) ) );
    range A2 = ws1->range( sheet_range( sheet_point( 1, 0 ) ) );
    range B1 = ws1->range( sheet_range( sheet_point( 0, 1 ) ) );
    range B2 = ws1->range( sheet_range( sheet_point( 1, 1 ) ) );
    BOOST_CHECK_NO_THROW( B1.value( *active_session, variant( 2.0 ) ) );
    BOOST_CHECK_NO_THROW( B2.value( *active_session, variant( 3.0 ) ) );

    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=1+2" ), named_formula_scope::worksheet_scope, ws1  ) );
    BOOST_CHECK_NO_THROW( A1.value( *active_session, variant( "=test" ) ) );

    BOOST_CHECK_NO_THROW( A1.copy( *active_session, A2 ) );
    check_formula_and_value( *active_session, A1, variant( 3.0 ), variant( "=test" ) );
    check_formula_and_value( *active_session, A2, variant( 3.0 ), variant( "=test" ) );
    BOOST_CHECK_NO_THROW( A2.copy( *active_session, A1 ) );
    check_formula_and_value( *active_session, A1, variant( 3.0 ), variant( "=test" ) );
    check_formula_and_value( *active_session, A2, variant( 3.0 ), variant( "=test" ) );
}

BOOST_AUTO_TEST_CASE( test11_1b )
{
    range A1 = ws1->range( sheet_range( sheet_point( 0, 0 ) ) );
    range A2 = ws1->range( sheet_range( sheet_point( 1, 0 ) ) );
    range B1 = ws1->range( sheet_range( sheet_point( 0, 1 ) ) );
    range B2 = ws1->range( sheet_range( sheet_point( 1, 1 ) ) );
    BOOST_CHECK_NO_THROW( B1.value( *active_session, variant( 2.0 ) ) );
    BOOST_CHECK_NO_THROW( B2.value( *active_session, variant( 3.0 ) ) );

    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=1+2" ), named_formula_scope::workbook_scope, ws1  ) );
    BOOST_CHECK_NO_THROW( A1.value( *active_session, variant( "=test" ) ) );

    BOOST_CHECK_NO_THROW( A1.copy( *active_session, A2 ) );
    check_formula_and_value( *active_session, A1, variant( 3.0 ), variant( "=test" ) );
    check_formula_and_value( *active_session, A2, variant( 3.0 ), variant( "=test" ) );
    BOOST_CHECK_NO_THROW( A2.copy( *active_session, A1 ) );
    check_formula_and_value( *active_session, A1, variant( 3.0 ), variant( "=test" ) );
    check_formula_and_value( *active_session, A2, variant( 3.0 ), variant( "=test" ) );
}

// // *11_2 copy cell with nf ( B1 = 2, B2 = 3, test = B1 + B2, created at position A1, A1 = test, copy A1->A2 =>
// A1:
// value = 5, A2:
//         value = 3 copy A2->A1 => value = 5 )
BOOST_AUTO_TEST_CASE( test11_2a )
{
    range A1 = ws1->range( sheet_range( sheet_point( 0, 0 ) ) );
    range A2 = ws1->range( sheet_range( sheet_point( 1, 0 ) ) );
    range B1 = ws1->range( sheet_range( sheet_point( 0, 1 ) ) );
    range B2 = ws1->range( sheet_range( sheet_point( 1, 1 ) ) );
    BOOST_CHECK_NO_THROW( B1.value( *active_session, variant( 2.0 ) ) );
    BOOST_CHECK_NO_THROW( B2.value( *active_session, variant( 3.0 ) ) );

    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=B1+B2" ), named_formula_scope::worksheet_scope, ws1  ) );
    BOOST_CHECK_NO_THROW( A1.value( *active_session, variant( "=test" ) ) );

    BOOST_CHECK_NO_THROW( A1.copy( *active_session, A2 ) );
    check_formula_and_value( *active_session, A1, variant( 5.0 ), variant( "=test" ) );
    check_formula_and_value( *active_session, A2, variant( 3.0 ), variant( "=test" ) );
    BOOST_CHECK_NO_THROW( A2.copy( *active_session, A1 ) );
    check_formula_and_value( *active_session, A1, variant( 5.0 ), variant( "=test" ) );
    check_formula_and_value( *active_session, A2, variant( 3.0 ), variant( "=test" ) );
}

BOOST_AUTO_TEST_CASE( test11_2b )
{
    range A1 = ws1->range( sheet_range( sheet_point( 0, 0 ) ) );
    range A2 = ws1->range( sheet_range( sheet_point( 1, 0 ) ) );
    range B1 = ws1->range( sheet_range( sheet_point( 0, 1 ) ) );
    range B2 = ws1->range( sheet_range( sheet_point( 1, 1 ) ) );
    BOOST_CHECK_NO_THROW( B1.value( *active_session, variant( 2.0 ) ) );
    BOOST_CHECK_NO_THROW( B2.value( *active_session, variant( 3.0 ) ) );

    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=B1+B2" ), named_formula_scope::workbook_scope, ws1  ) );
    BOOST_CHECK_NO_THROW( A1.value( *active_session, variant( "=test" ) ) );

    BOOST_CHECK_NO_THROW( A1.copy( *active_session, A2 ) );
    check_formula_and_value( *active_session, A1, variant( 5.0 ), variant( "=test" ) );
    check_formula_and_value( *active_session, A2, variant( 3.0 ), variant( "=test" ) );
    BOOST_CHECK_NO_THROW( A2.copy( *active_session, A1 ) );
    check_formula_and_value( *active_session, A1, variant( 5.0 ), variant( "=test" ) );
    check_formula_and_value( *active_session, A2, variant( 3.0 ), variant( "=test" ) );
}


//* 11_3 move cell inside nf (B1=2, B2=3, test=1+2, created at position A1, move B1:B2->B2:B3 => nf_value=5)
BOOST_AUTO_TEST_CASE( test11_3a )
{
    range B1 = ws1->range( sheet_range( sheet_point( 0, 1 ) ) );
    range B2 = ws1->range( sheet_range( sheet_point( 1, 1 ) ) );
    BOOST_CHECK_NO_THROW( B1.value( *active_session, variant( 2.0 ) ) );
    BOOST_CHECK_NO_THROW( B2.value( *active_session, variant( 3.0 ) ) );
    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=1+2" ), named_formula_scope::worksheet_scope, ws1  ) );
    range B1B2 = ws1->range( sheet_range( sheet_point( 0, 1 ),  sheet_point( 1, 1 ) ) );
    range B2B3 = ws1->range( sheet_range( sheet_point( 1, 1 ),  sheet_point( 2, 1 ) ) );
    BOOST_CHECK_NO_THROW( B1B2.move( *active_session, B2B3 ) );
    BOOST_CHECK_EQUAL( wb1->named_formulas().formula( active_session->locale(), named_formula_identifier( "test", ws1->uuid() ) ), variant( "=1+2" ) );
    BOOST_CHECK_EQUAL( wb1->named_formulas().value( *active_session, named_formula_identifier( "test", ws1->uuid() ) ), variant( 3.0 ) );
}

BOOST_AUTO_TEST_CASE( test11_3b )
{
    range B1 = ws1->range( sheet_range( sheet_point( 0, 1 ) ) );
    range B2 = ws1->range( sheet_range( sheet_point( 1, 1 ) ) );
    BOOST_CHECK_NO_THROW( B1.value( *active_session, variant( 2.0 ) ) );
    BOOST_CHECK_NO_THROW( B2.value( *active_session, variant( 3.0 ) ) );
    range B1B2 = ws1->range( sheet_range( sheet_point( 0, 1 ),  sheet_point( 1, 1 ) ) );
    range B2B3 = ws1->range( sheet_range( sheet_point( 1, 1 ),  sheet_point( 2, 1 ) ) );
    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=1+2" ), named_formula_scope::workbook_scope, ws1  ) );

    BOOST_CHECK_NO_THROW( B1B2.move( *active_session, B2B3 ) );
    BOOST_CHECK_EQUAL( wb1->named_formulas().formula( active_session->locale(), named_formula_identifier( "test", boost::uuids::nil_uuid() ) ), variant( "=1+2" ) );
    BOOST_CHECK_EQUAL( wb1->named_formulas().value( *active_session, named_formula_identifier( "test", boost::uuids::nil_uuid() ) ), variant( 3.0 ) );
}
#endif //REENABLE_PASSED_TESTS
//* 11_4 move cell inside nf (B1=2, B2=3, test=B1+B2, created at position A1, move B1:B2->B2:B3 => nf_value=2)
BOOST_AUTO_TEST_CASE( test11_4a )
{
    select_worksheet_command( *active_session, "ws1" ).execute();
    range B1 = ws1->range( sheet_range( sheet_point( 0, 1 ) ) );
    range B2 = ws1->range( sheet_range( sheet_point( 1, 1 ) ) );
    BOOST_CHECK_NO_THROW( B1.value( *active_session, variant( 2.0 ) ) );
    BOOST_CHECK_NO_THROW( B2.value( *active_session, variant( 3.0 ) ) );
    range B1B2 = ws1->range( sheet_range( sheet_point( 0, 1 ),  sheet_point( 1, 1 ) ) );
    range B2B3 = ws1->range( sheet_range( sheet_point( 1, 1 ),  sheet_point( 2, 1 ) ) );
    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=B1+B2" ), named_formula_scope::worksheet_scope, ws1  ) );

    BOOST_CHECK_EQUAL( wb1->named_formulas().value( *active_session, named_formula_identifier( "test", ws1->uuid() ) ), variant( 5.0 ) );
    BOOST_CHECK_NO_THROW( B1B2.move( *active_session, B2B3 ) );
    BOOST_CHECK_EQUAL( wb1->named_formulas().value( *active_session, named_formula_identifier( "test", ws1->uuid() ) ), variant( 2.0 ) );
}
#ifdef REENABLE_PASSED_TESTS

BOOST_AUTO_TEST_CASE( test11_4b )
{
    select_worksheet_command( *active_session, "ws1" ).execute();
    range B1 = ws1->range( sheet_range( sheet_point( 0, 1 ) ) );
    range B2 = ws1->range( sheet_range( sheet_point( 1, 1 ) ) );
    BOOST_CHECK_NO_THROW( B1.value( *active_session, variant( 2.0 ) ) );
    BOOST_CHECK_NO_THROW( B2.value( *active_session, variant( 3.0 ) ) );
    range B1B2 = ws1->range( sheet_range( sheet_point( 0, 1 ),  sheet_point( 1, 1 ) ) );
    range B2B3 = ws1->range( sheet_range( sheet_point( 1, 1 ),  sheet_point( 2, 1 ) ) );

    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=B1+B2" ), named_formula_scope::workbook_scope, ws1  ) );
    BOOST_CHECK_EQUAL( wb1->named_formulas().value( *active_session, named_formula_identifier( "test", boost::uuids::nil_uuid() ) ), variant( 5.0 ) );
    BOOST_CHECK_NO_THROW( B1B2.move( *active_session, B2B3 ) );
    BOOST_CHECK_EQUAL( wb1->named_formulas().value( *active_session, named_formula_identifier( "test", boost::uuids::nil_uuid() ) ), variant( 2.0 ) );
}

//*12 create value of a nf outside of a cell
BOOST_AUTO_TEST_CASE( test12a )
{

    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=1+2" ), named_formula_scope::worksheet_scope, ws1  ) );
    BOOST_CHECK_EQUAL( wb1->named_formulas().value( *active_session, named_formula_identifier( "test", ws1->uuid() ) ), variant( 3.0 ) );
}

BOOST_AUTO_TEST_CASE( test12b )
{
    range A1 = ws1->range( sheet_range( sheet_point( 0, 0 ) ) );

    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=14" ), named_formula_scope::workbook_scope, ws1  ) );
    BOOST_CHECK_EQUAL( wb1->named_formulas().value( *active_session, named_formula_identifier( "test", boost::uuids::nil_uuid() ) ), variant( 14.0 ) );
}

//*13 try to set value of a nf that doesn't exist and check for exception
BOOST_AUTO_TEST_CASE( test13a )
{
    BOOST_CHECK_THROW( wb1->named_formulas().value( *active_session, named_formula_identifier( "test", ws1->uuid() ) ), named_formula_not_found_exception );
}

BOOST_AUTO_TEST_CASE( test13b )
{
    range A1 = ws1->range( sheet_range( sheet_point( 0, 0 ) ) );

    BOOST_CHECK_THROW( wb1->named_formulas().value( *active_session, named_formula_identifier( "test", boost::uuids::nil_uuid() ) ), named_formula_not_found_exception );
}

//*14 try to create value of a nf that does exist but is in the wrong scope and check for exception
BOOST_AUTO_TEST_CASE( test14a )
{

    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=1+2" ), named_formula_scope::workbook_scope, ws1  ) );
    BOOST_CHECK_THROW( wb1->named_formulas().value( *active_session, named_formula_identifier( "test", ws1->uuid() ) ), named_formula_not_found_exception );
}

BOOST_AUTO_TEST_CASE( test14b )
{

    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=1+2" ), named_formula_scope::worksheet_scope, ws1  ) );
    BOOST_CHECK_THROW( wb1->named_formulas().value( *active_session, named_formula_identifier( "test", boost::uuids::nil_uuid() ) ), named_formula_not_found_exception );
}

//*15 change name of nf to a name that doesn't exist yet
BOOST_AUTO_TEST_CASE( test15a )
{
    range A1 = ws1->range( sheet_range( sheet_point( 0, 0 ) ) );

    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=1+2" ), named_formula_scope::worksheet_scope, ws1  ) );
    BOOST_CHECK_NO_THROW( A1.value( *active_session, variant( "=test" ) ) );
    BOOST_CHECK_NO_THROW( wb1->named_formulas().rename( *active_session, named_formula_identifier( "test", ws1->uuid() ), "new_test" ) );
    BOOST_CHECK_EQUAL( wb1->named_formulas().value( *active_session, named_formula_identifier( "new_test", ws1->uuid() ) ), variant( 3.0 ) );
    check_formula_and_value( *active_session, A1, variant( 3.0 ), "=new_test" );
    BOOST_CHECK_THROW( wb1->named_formulas().value( *active_session, named_formula_identifier( "test", ws1->uuid() ) ), named_formula_not_found_exception );
}

BOOST_AUTO_TEST_CASE( test15b )
{
    range A1 = ws1->range( sheet_range( sheet_point( 0, 0 ) ) );

    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=1+2" ), named_formula_scope::workbook_scope, ws1  ) );
    BOOST_CHECK_NO_THROW( A1.value( *active_session, variant( "=test" ) ) );
    BOOST_CHECK_NO_THROW( wb1->named_formulas().rename( *active_session, named_formula_identifier( "test", boost::uuids::nil_uuid() ), "new_test" ) );
    BOOST_CHECK_EQUAL( wb1->named_formulas().value( *active_session, named_formula_identifier( "new_test", boost::uuids::nil_uuid() ) ), variant( 3.0 ) );
    check_formula_and_value( *active_session, A1, variant( 3.0 ), "=new_test" );
    BOOST_CHECK_THROW( wb1->named_formulas().value( *active_session, named_formula_identifier( "test", boost::uuids::nil_uuid() ) ), named_formula_not_found_exception );
}

//* 16_1 change name of nf to a name that does already exist
BOOST_AUTO_TEST_CASE( test16_1a )
{
    range A1 = ws1->range( sheet_range( sheet_point( 0, 0 ) ) );

    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=1+2" ), named_formula_scope::worksheet_scope, ws1  ) );
    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "new_test", variant( "=1+2" ), named_formula_scope::worksheet_scope, ws1  ) );
    BOOST_CHECK_THROW( wb1-> named_formulas().rename( *active_session, named_formula_identifier( "test", ws1->uuid() ), "new_test" ), named_formula_exception );
}

BOOST_AUTO_TEST_CASE( test16_1b )
{
    range A1 = ws1->range( sheet_range( sheet_point( 0, 0 ) ) );

    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=1+2" ), named_formula_scope::workbook_scope, ws1  ) );
    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "new_test", variant( "=1+2" ), named_formula_scope::workbook_scope, ws1  ) );
    BOOST_CHECK_THROW( wb1-> named_formulas().rename( *active_session, named_formula_identifier( "test", boost::uuids::nil_uuid() ), "new_test" ), named_formula_exception );
}
//* 16_2 check case sensitivity/insensitivity
BOOST_AUTO_TEST_CASE( test16_2a )
{
    range A1 = ws1->range( sheet_range( sheet_point( 0, 0 ) ) );

    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=1+2" ), named_formula_scope::worksheet_scope, ws1  ) );
    BOOST_CHECK_NO_THROW( A1.value( *active_session, variant( "=test" ) ) );
    BOOST_CHECK_NO_THROW( wb1-> named_formulas().rename( *active_session, named_formula_identifier( "test", ws1->uuid() ), "Test" ) );
    BOOST_CHECK_EQUAL( wb1->named_formulas().value( *active_session, named_formula_identifier( "Test", ws1->uuid() ) ), variant( 3.0 ) );
    check_formula_and_value( *active_session, A1, variant( 3.0 ), "=Test" );
    BOOST_CHECK_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=12" ), named_formula_scope::worksheet_scope, ws1  ), named_formula_exception );
}

BOOST_AUTO_TEST_CASE( test16_2b )
{
    range A1 = ws1->range( sheet_range( sheet_point( 0, 0 ) ) );

    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=1+2" ), named_formula_scope::workbook_scope, ws1  ) );
    BOOST_CHECK_NO_THROW( A1.value( *active_session, variant( "=test" ) ) );
    BOOST_CHECK_NO_THROW( wb1-> named_formulas().rename( *active_session, named_formula_identifier( "test", boost::uuids::nil_uuid() ), "Test" ) );
    BOOST_CHECK_EQUAL( wb1->named_formulas().value( *active_session, named_formula_identifier( "Test", boost::uuids::nil_uuid() ) ), variant( 3.0 ) );
    check_formula_and_value( *active_session, A1, variant( 3.0 ), "=Test" );
    BOOST_CHECK_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=12" ), named_formula_scope::workbook_scope, ws1  ), named_formula_exception );
}

//*17 try to create value of a nf that does have absolute references (A1=3, test=$A$1, created at position A1) => value=3
BOOST_AUTO_TEST_CASE( test17a )
{
    range A1 = ws1->range( sheet_range( sheet_point( 0, 0 ) ) );
    ws1->select( active_session->selected() );
    BOOST_CHECK_NO_THROW( A1.value( *active_session, variant( 3.0 ) ) );

    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=$A$1" ), named_formula_scope::worksheet_scope, ws1  ) );
    BOOST_CHECK_EQUAL( wb1->named_formulas().value( *active_session, named_formula_identifier( "test", ws1->uuid() ) ), variant( 3.0 ) );
}

BOOST_AUTO_TEST_CASE( test17b )
{
    range A1 = ws1->range( sheet_range( sheet_point( 0, 0 ) ) );
    BOOST_CHECK_NO_THROW( A1.value( *active_session, variant( 3.0 ) ) );

    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=$A$1" ), named_formula_scope::workbook_scope, ws1  ) );
    BOOST_CHECK_EQUAL( wb1->named_formulas().value( *active_session, named_formula_identifier( "test", boost::uuids::nil_uuid() ) ), variant( 3.0 ) );
}

//*18 try to create value of a nf that does have absolute references (A1=3, test=$A$1, created at position B2) => value=3
BOOST_AUTO_TEST_CASE( test18a )
{
    range A1 = ws1->range( sheet_range( sheet_point( 0, 0 ) ) );
    ws1->select( active_session->selected() );
    BOOST_CHECK_NO_THROW( A1.value( *active_session, variant( 3.0 ) ) );

    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=$A$1" ), named_formula_scope::worksheet_scope, ws1, sheet_point( 1, 1 )  ) );
    BOOST_CHECK_EQUAL( wb1->named_formulas().value( *active_session, named_formula_identifier( "test", ws1->uuid() ) ), variant( 3.0 ) );
}

BOOST_AUTO_TEST_CASE( test18b )
{
    range A1 = ws1->range( sheet_range( sheet_point( 0, 0 ) ) );
    BOOST_CHECK_NO_THROW( A1.value( *active_session, variant( 3.0 ) ) );

    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=$A$1" ), named_formula_scope::workbook_scope, ws1, sheet_point( 1, 1 )  ) );
    BOOST_CHECK_EQUAL( wb1->named_formulas().value( *active_session, named_formula_identifier( "test", boost::uuids::nil_uuid() ) ), variant( 3.0 ) );
}

//*19 try to create value of a nf that does have absolute references (B1=3, B2=3, test=$B$1+$B$2, created at position A1) => value=6
BOOST_AUTO_TEST_CASE( test19a )
{
    range B1 = ws1->range( sheet_range( sheet_point( 0, 1 ) ) );
    BOOST_CHECK_NO_THROW( B1.value( *active_session, variant( 3.0 ) ) );
    range B2 = ws1->range( sheet_range( sheet_point( 1, 1 ) ) );
    BOOST_CHECK_NO_THROW( B2.value( *active_session, variant( 3.0 ) ) );

    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=$B$1+$B$2" ), named_formula_scope::worksheet_scope, ws1  ) );
    BOOST_CHECK_EQUAL( wb1->named_formulas().value( *active_session, named_formula_identifier( "test", ws1->uuid() ) ), variant( 6.0 ) );
}

BOOST_AUTO_TEST_CASE( test19b )
{
    range B1 = ws1->range( sheet_range( sheet_point( 0, 1 ) ) );
    BOOST_CHECK_NO_THROW( B1.value( *active_session, variant( 3.0 ) ) );
    range B2 = ws1->range( sheet_range( sheet_point( 1, 1 ) ) );
    BOOST_CHECK_NO_THROW( B2.value( *active_session, variant( 3.0 ) ) );

    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=$B$1+$B$2" ), named_formula_scope::workbook_scope, ws1  ) );
    BOOST_CHECK_EQUAL( wb1->named_formulas().value( *active_session, named_formula_identifier( "test", boost::uuids::nil_uuid() ) ), variant( 6.0 ) );
}

//*20 create value of a nf that does have relative references (A1=3, test=A1, created at position A1) => value=3
BOOST_AUTO_TEST_CASE( test20a )
{
    range A1 = ws1->range( sheet_range( sheet_point( 0, 0 ) ) );
    ws1->select( active_session->selected() );
    BOOST_CHECK_NO_THROW( A1.value( *active_session, variant( 3.0 ) ) );

    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=A1" ), named_formula_scope::worksheet_scope, ws1  ) );
    BOOST_CHECK_EQUAL( wb1->named_formulas().value( *active_session, named_formula_identifier( "test", ws1->uuid() ) ), variant( 3.0 ) );
}

BOOST_AUTO_TEST_CASE( test20b )
{
    range A1 = ws1->range( sheet_range( sheet_point( 0, 0 ) ) );
    BOOST_CHECK_NO_THROW( A1.value( *active_session, variant( 3.0 ) ) );

    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=A1" ), named_formula_scope::workbook_scope, ws1  ) );
    BOOST_CHECK_EQUAL( wb1->named_formulas().value( *active_session, named_formula_identifier( "test", boost::uuids::nil_uuid() ) ), variant( 3.0 ) );
}

//*21 create value of a nf that does have relative references (A1=3, test=A1, created at position B2, evaluate at position B2 and A1) => value=3 / value=0
BOOST_AUTO_TEST_CASE( test21a )
{
    range A1 = ws1->range( sheet_range( sheet_point( 0, 0 ) ) );
    ws1->select( active_session->selected() );
    BOOST_CHECK_NO_THROW( A1.value( *active_session, variant( 3.0 ) ) );

    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=A1" ), named_formula_scope::worksheet_scope, ws1, sheet_point( 1, 1 )  ) );
    BOOST_CHECK_EQUAL( wb1->named_formulas().value( *active_session, named_formula_identifier( "test", ws1->uuid() ), sheet_point( 1, 1 )  ), variant( 3.0 ) );
    BOOST_CHECK_EQUAL( wb1->named_formulas().value( *active_session, named_formula_identifier( "test", ws1->uuid() ) ), variant( 0.0 ) );
}

BOOST_AUTO_TEST_CASE( test21b )
{
    range A1 = ws1->range( sheet_range( sheet_point( 0, 0 ) ) );
    BOOST_CHECK_NO_THROW( A1.value( *active_session, variant( 3.0 ) ) );

    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=A1" ), named_formula_scope::workbook_scope, ws1, sheet_point( 1, 1 )  ) );
    BOOST_CHECK_EQUAL( wb1->named_formulas().value( *active_session, named_formula_identifier( "test", boost::uuids::nil_uuid() ), sheet_point( 1, 1 )  ), variant( 3.0 ) );
    BOOST_CHECK_EQUAL( wb1->named_formulas().value( *active_session, named_formula_identifier( "test", boost::uuids::nil_uuid() ) ), variant( 0.0 ) );
}

//*22 create value of a nf that does have relative references (B1=2, B2=3, test=B1+B2, created at position A1, evaluate at position A1 and A2) => value=5 /value=3
BOOST_AUTO_TEST_CASE( test22a )
{
    range B1 = ws1->range( sheet_range( sheet_point( 0, 1 ) ) );
    BOOST_CHECK_NO_THROW( B1.value( *active_session, variant( 2.0 ) ) );
    range B2 = ws1->range( sheet_range( sheet_point( 1, 1 ) ) );
    BOOST_CHECK_NO_THROW( B2.value( *active_session, variant( 3.0 ) ) );

    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=B1+B2" ), named_formula_scope::worksheet_scope, ws1  ) );
    BOOST_CHECK_EQUAL( wb1->named_formulas().value( *active_session, named_formula_identifier( "test", ws1->uuid() ) ), variant( 5.0 ) );
    BOOST_CHECK_EQUAL( wb1->named_formulas().value( *active_session, named_formula_identifier( "test", ws1->uuid() ), sheet_point( 1, 0 ) ), variant( 3.0 ) );
}

BOOST_AUTO_TEST_CASE( test22b )
{
    range B1 = ws1->range( sheet_range( sheet_point( 0, 1 ) ) );
    BOOST_CHECK_NO_THROW( B1.value( *active_session, variant( 2.0 ) ) );
    range B2 = ws1->range( sheet_range( sheet_point( 1, 1 ) ) );
    BOOST_CHECK_NO_THROW( B2.value( *active_session, variant( 3.0 ) ) );

    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=B1+B2" ), named_formula_scope::workbook_scope, ws1  ) );
    BOOST_CHECK_EQUAL( wb1->named_formulas().value( *active_session, named_formula_identifier( "test", boost::uuids::nil_uuid() ) ), variant( 5.0 ) );
    BOOST_CHECK_EQUAL( wb1->named_formulas().value( *active_session, named_formula_identifier( "test", boost::uuids::nil_uuid() ), sheet_point( 1, 0 ) ), variant( 3.0 ) );
}


BOOST_AUTO_TEST_CASE( test_cyclic_named_formula_ws )
{
    ws1->select( active_session->selected() );
    range B1 = ws1->range( sheet_range( sheet_point( 0, 1 ) ) );
    BOOST_CHECK_NO_THROW( B1.value( *active_session, variant( 2.0 ) ) );
    range B2 = ws1->range( sheet_range( sheet_point( 1, 1 ) ) );
    BOOST_CHECK_NO_THROW( B2.value( *active_session, variant( 3.0 ) ) );

    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=test+1" ), named_formula_scope::worksheet_scope, ws1  ) );
    BOOST_CHECK_EQUAL( wb1->named_formulas().value( *active_session, named_formula_identifier( "test", ws1->uuid() ) ), variant( variant::error_name /*static_cast<double>( active_session->selected().application()->calculation_settings().maximum_iterations() )*/ ) );
}


BOOST_AUTO_TEST_CASE( test_cyclic_named_formula_wb )
{
    ws1->select( active_session->selected() );
    range B1 = ws1->range( sheet_range( sheet_point( 0, 1 ) ) );
    BOOST_CHECK_NO_THROW( B1.value( *active_session, variant( 2.0 ) ) );
    range B2 = ws1->range( sheet_range( sheet_point( 1, 1 ) ) );
    BOOST_CHECK_NO_THROW( B2.value( *active_session, variant( 3.0 ) ) );

    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=test+1" ), named_formula_scope::workbook_scope, ws1  ) );
    BOOST_CHECK_EQUAL( wb1->named_formulas().value( *active_session, named_formula_identifier( "test", boost::uuids::nil_uuid() ) ), variant( variant::error_name /*static_cast<double>( active_session->selected().application()->calculation_settings().maximum_iterations() )*/ ) );
}

BOOST_AUTO_TEST_CASE( test_cyclic_references_ws1 )
{
    ws1->select( active_session->selected() );
    range B1 = ws1->range( sheet_range( sheet_point( 0, 1 ) ) );
    BOOST_CHECK_NO_THROW( B1.value( *active_session, variant( 2.0 ) ) );
    range B2 = ws1->range( sheet_range( sheet_point( 1, 1 ) ) );
    BOOST_CHECK_NO_THROW( B2.value( *active_session, variant( static_cast<double>( 3 ) ) ) );

    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=a1" ), named_formula_scope::workbook_scope, ws1, sheet_point( 1, 1 )  ) );
    std::string expected_string = "=" + a1conversion::to_a1::from_point( sheet_point( sheet_dimension::max_row, sheet_dimension::max_column ) );
    BOOST_CHECK_EQUAL( wb1->named_formulas().formula( active_session->locale(), named_formula_identifier( "test", boost::uuids::nil_uuid() ), sheet_point( 0, 0 ) ), variant( expected_string ) );
}

BOOST_AUTO_TEST_CASE( test_cyclic_references_ws2 )
{
    ws1->select( active_session->selected() );
    range B1 = ws1->range( sheet_range( sheet_point( 0, 1 ) ) );
    BOOST_CHECK_NO_THROW( B1.value( *active_session, variant( 2.0 ) ) );
    range B2 = ws1->range( sheet_range( sheet_point( 1, 1 ) ) );
    BOOST_CHECK_NO_THROW( B2.value( *active_session, variant( static_cast<double>( 3 ) ) ) );
    std::string max_cell_string = "=ws1!" + a1conversion::to_a1::from_point( sheet_point( sheet_dimension::max_row, sheet_dimension::max_column ) );
    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( max_cell_string ), named_formula_scope::workbook_scope, ws1, sheet_point( 0, 0 )  ) );
    BOOST_CHECK_EQUAL( wb1->named_formulas().formula( active_session->locale(), named_formula_identifier( "test", boost::uuids::nil_uuid() ), sheet_point( 1, 1 ) ), variant( "=ws1!A1" ) );
}

//another cyclic reference check test = a1+1, a1 = 1, b1 = test, b2 = test
BOOST_AUTO_TEST_CASE( test_cyclic_problem )
{
    range A1 = ws1->range( sheet_range( sheet_point( 0, 0 ) ) );
    ws1->select( active_session->selected() );
    BOOST_CHECK_NO_THROW( A1.value( *active_session, variant( 1.0 ) ) );

    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=a1+1" ), named_formula_scope::worksheet_scope, ws1, sheet_point( 1, 0 )  ) );

    range A2 = ws1->range( sheet_range( sheet_point( 1, 0 ) ) );
    BOOST_CHECK_NO_THROW( A2.value( *active_session, variant( "=test" ) ) );

    range A3 = ws1->range( sheet_range( sheet_point( 2, 0 ) ) );
    BOOST_CHECK_NO_THROW( A3.value( *active_session, variant( "=test" ) ) );

    BOOST_CHECK_EQUAL( A2.value( *active_session ), variant( 2.0 ) );
    BOOST_CHECK_EQUAL( A2.formula( *active_session ), variant( "=test" ) );
    BOOST_CHECK_EQUAL( A3.value( *active_session ), variant( 3.0 ) );
    BOOST_CHECK_EQUAL( A3.formula( *active_session ), variant( "=test" ) );
}

//another reference/dependency check test "=b1", then change formula of test to "=b1 + c1"
BOOST_AUTO_TEST_CASE( test_tried_to_access_invalidated_range_reference_problem )
{
    ws1->select( active_session->selected() );
    range B1 = ws1->range( sheet_range( sheet_point( 0, 1 ) ) );
    range C1 = ws1->range( sheet_range( sheet_point( 0, 2 ) ) );
    B1.value( *active_session, 3.0 );
    C1.value( *active_session, 5.0 );
    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=b1" ), named_formula_scope::worksheet_scope, ws1  ) );
    BOOST_CHECK_EQUAL( wb1->named_formulas().value( *active_session, named_formula_identifier( "test", ws1->uuid() ) ), variant( 3.0 ) );
    BOOST_CHECK_NO_THROW( wb1->named_formulas().value( *active_session, named_formula_identifier( "test", ws1->uuid()  ), variant( "=b1+c1" ) ) );
    BOOST_CHECK_EQUAL( wb1->named_formulas().value( *active_session, named_formula_identifier( "test", ws1->uuid() ) ), variant( 8.0 ) );
}

//another reference/dependency check test "=b1", then change formula of test to "=b1 + c1"
BOOST_AUTO_TEST_CASE( test_tried_to_access_invalidated_range_reference_problem2 )
{
    ws1->select( active_session->selected() );
    range A1 = ws1->range( sheet_range( sheet_point( 0, 0 ) ) );
    range B1 = ws1->range( sheet_range( sheet_point( 0, 1 ) ) );
    range C1 = ws1->range( sheet_range( sheet_point( 0, 2 ) ) );
    B1.value( *active_session, 3.0 );
    C1.value( *active_session, 5.0 );
    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=b1" ), named_formula_scope::worksheet_scope, ws1  ) );
    A1.value( *active_session, "=test" );
    BOOST_CHECK_EQUAL( wb1->named_formulas().value( *active_session, named_formula_identifier( "test", ws1->uuid() ) ), variant( 3.0 ) );
    BOOST_CHECK_NO_THROW( wb1->named_formulas().value( *active_session, named_formula_identifier( "test", ws1->uuid()  ), variant( "=b1+c1" ) ) );
    BOOST_CHECK_EQUAL( wb1->named_formulas().value( *active_session, named_formula_identifier( "test", ws1->uuid() ) ), variant( 8.0 ) );
}

BOOST_AUTO_TEST_CASE( test_tried_to_access_invalidated_range_reference_problem3 )
{
    ws1->select( active_session->selected() );
    range A1 = ws1->range( sheet_range( sheet_point( 0, 0 ) ) );
    range B1 = ws1->range( sheet_range( sheet_point( 0, 1 ) ) );
    range C1 = ws1->range( sheet_range( sheet_point( 0, 2 ) ) );
    B1.value( *active_session, 3.0 );
    C1.value( *active_session, 5.0 );
    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=b1" ), named_formula_scope::worksheet_scope, ws1  ) );
    A1.value( *active_session, "=test" );
    BOOST_CHECK_EQUAL( wb1->named_formulas().value( *active_session, named_formula_identifier( "test", ws1->uuid() ) ), variant( 3.0 ) );
    BOOST_CHECK_NO_THROW( wb1->named_formulas().value( *active_session, named_formula_identifier( "test", ws1->uuid()  ), variant( "=sum(b1:c1)" ) ) );
    BOOST_CHECK_EQUAL( wb1->named_formulas().value( *active_session, named_formula_identifier( "test", ws1->uuid() ) ), variant( 8.0 ) );
}


// what the name suggests
BOOST_AUTO_TEST_CASE( test_named_formula_reference_volatile_cell_ws_scope )
{
    range A1 = ws1->range( sheet_range( sheet_point( 0, 0 ) ) );
    ws1->select( active_session->selected() );
    BOOST_CHECK_NO_THROW( A1.value( *active_session, variant( "=rand()" ) ) );
    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=$A$1" ), named_formula_scope::worksheet_scope, ws1  ) );
    range B1 = ws1->range( sheet_range( sheet_point( 0, 1 ) ) );
    BOOST_CHECK_NO_THROW( B1.value( *active_session, variant( "=test" ) ) );
    variant value_of_test = wb1->named_formulas().value( *active_session, named_formula_identifier( "test", ws1->uuid() ) );
    BOOST_CHECK_LE( variant( 0.0 ), value_of_test );
    BOOST_CHECK_LT( value_of_test, variant( 1.0 ) );
    BOOST_CHECK_EQUAL( A1.value( *active_session ), B1.value( *active_session ) );
}

// what the name suggests
BOOST_AUTO_TEST_CASE( test_named_formula_reference_volatile_cell_wb_scope )
{
    range A1 = ws1->range( sheet_range( sheet_point( 0, 0 ) ) );
    ws1->select( active_session->selected() );
    BOOST_CHECK_NO_THROW( A1.value( *active_session, variant( "=rand()" ) ) );
    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=$A$1" ), named_formula_scope::workbook_scope, ws1  ) );
    range B1 = ws1->range( sheet_range( sheet_point( 0, 1 ) ) );
    BOOST_CHECK_NO_THROW( B1.value( *active_session, variant( "=test" ) ) );
    variant value_of_test = wb1->named_formulas().value( *active_session, named_formula_identifier( "test", boost::uuids::nil_uuid() ) );

    BOOST_CHECK_LE( variant( 0.0 ), value_of_test );
    BOOST_CHECK_LT( value_of_test, variant( 1.0 ) );
    BOOST_CHECK_EQUAL( A1.value( *active_session ), B1.value( *active_session ) );
}

// what the name suggests
BOOST_AUTO_TEST_CASE( test_named_formula_with_volatile_value_ws_scope )
{
    ws1->select( active_session->selected() );
    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=rand()" ), named_formula_scope::worksheet_scope, ws1  ) );
    range A1 = ws1->range( sheet_range( sheet_point( 0, 0 ) ) );
    BOOST_CHECK_NO_THROW( A1.value( *active_session, variant( "=test" ) ) );
    range B1 = ws1->range( sheet_range( sheet_point( 0, 1 ) ) );
    BOOST_CHECK_NO_THROW( B1.value( *active_session, variant( "=test" ) ) );
    variant value_of_test = wb1->named_formulas().value( *active_session, named_formula_identifier( "test", ws1->uuid() ) );

    const variant value_of_a1 = A1.value( *active_session );
    const variant value_of_b1 = B1.value( *active_session );
    BOOST_CHECK_LE( variant( 0.0 ), value_of_test );
    BOOST_CHECK_LT( value_of_test, variant( 1.0 ) );
    BOOST_CHECK_LE( variant( 0.0 ), value_of_a1 );
    BOOST_CHECK_LT( value_of_a1, variant( 1.0 ) );
    BOOST_CHECK_LE( variant( 0.0 ), value_of_b1 );
    BOOST_CHECK_LT( value_of_b1, variant( 1.0 ) );
}

// what the name suggests
BOOST_AUTO_TEST_CASE( test_named_formula_with_volatile_value_wb_scope )
{
    ws1->select( active_session->selected() );
    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test", variant( "=rand()" ), named_formula_scope::workbook_scope, ws1  ) );
    range A1 = ws1->range( sheet_range( sheet_point( 0, 0 ) ) );
    BOOST_CHECK_NO_THROW( A1.value( *active_session, variant( "=test" ) ) );
    range B1 = ws1->range( sheet_range( sheet_point( 0, 1 ) ) );
    BOOST_CHECK_NO_THROW( B1.value( *active_session, variant( "=test" ) ) );
    variant value_of_test = wb1->named_formulas().value( *active_session, named_formula_identifier( "test", boost::uuids::nil_uuid() ) );

    const variant value_of_a1 = A1.value( *active_session );
    const variant value_of_b1 = B1.value( *active_session );
    BOOST_CHECK_LE( variant( 0.0 ), value_of_test );
    BOOST_CHECK_LT( value_of_test, variant( 1.0 ) );
    BOOST_CHECK_LE( variant( 0.0 ), value_of_a1 );
    BOOST_CHECK_LT( value_of_a1, variant( 1.0 ) );
    BOOST_CHECK_LE( variant( 0.0 ), value_of_b1 );
    BOOST_CHECK_LT( value_of_b1, variant( 1.0 ) );
}

// what the name suggests
BOOST_AUTO_TEST_CASE( test_named_formula_with_numbers_in_name )
{
    ws1->select( active_session->selected() );
    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "test123", variant( "=12" ), named_formula_scope::worksheet_scope, ws1  ) );
    range A1 = ws1->range( sheet_range( sheet_point( 0, 0 ) ) );
    BOOST_CHECK_NO_THROW( A1.value( *active_session, variant( "=test123" ) ) );

    BOOST_CHECK_EQUAL( variant( "=test123" ), A1.formula( *active_session ) );
    BOOST_CHECK_EQUAL( variant( 12.0 ), A1.value( *active_session ) );
}

// what the name suggests
BOOST_AUTO_TEST_CASE( test_rename_named_formula )
{
    ws1->select( active_session->selected() );
    BOOST_CHECK_NO_THROW( wb1->named_formulas().create( *active_session, "testabc", variant( "=12" ), named_formula_scope::worksheet_scope, ws1  ) );
    range A1 = ws1->range( sheet_range( sheet_point( 0, 0 ) ) );
    BOOST_CHECK_NO_THROW( A1.value( *active_session, variant( "=testabc" ) ) );
    BOOST_CHECK_EQUAL( variant( "=testabc" ), A1.formula( *active_session ) );
    BOOST_CHECK_EQUAL( variant( 12.0 ), A1.value( *active_session ) );
    wb1->named_formulas().rename( *active_session, named_formula_identifier( "testabc", ws1->uuid() ), "test" );

    BOOST_CHECK_EQUAL( variant( "=test" ), A1.formula( *active_session ) );
    BOOST_CHECK_EQUAL( variant( 12.0 ), A1.value( *active_session ) );
}


// what the name suggests
BOOST_AUTO_TEST_CASE( test_reference_named_formula_before_its_there_ws )
{
    ws1->select( active_session->selected() );
    range A1 = ws1->range( sheet_range( sheet_point( 0, 0 ) ) );
    A1.value( *active_session, variant( "=test" ) );
    BOOST_CHECK_EQUAL( variant( "=test" ), A1.formula( *active_session ) );
    BOOST_CHECK_EQUAL( variant( variant::error_name ), A1.value( *active_session ) );
    wb1->named_formulas().create( *active_session, "test", variant( "=12" ), named_formula_scope::worksheet_scope, ws1 );
    BOOST_CHECK_EQUAL( variant( "=test" ), A1.formula( *active_session ) );
    BOOST_CHECK_EQUAL( variant( 12.0 ), A1.value( *active_session ) );
}

// what the name suggests
BOOST_AUTO_TEST_CASE( test_reference_named_formula_before_its_there_wb )
{
    ws1->select( active_session->selected() );
    range A1 = ws1->range( sheet_range( sheet_point( 0, 0 ) ) );
    A1.value( *active_session, variant( "=test" ) );
    BOOST_CHECK_EQUAL( variant( "=test" ), A1.formula( *active_session ) );
    BOOST_CHECK_EQUAL( variant( variant::error_name ), A1.value( *active_session ) );
    wb1->named_formulas().create( *active_session, "test", variant( "=12" ), named_formula_scope::workbook_scope, ws1 );
    BOOST_CHECK_EQUAL( variant( "=test" ), A1.formula( *active_session ) );
    BOOST_CHECK_EQUAL( variant( 12.0 ), A1.value( *active_session ) );
}

BOOST_AUTO_TEST_CASE( test_volatile_count_wb )
{
    range A1 = ws1->range( sheet_range( sheet_point( 0, 0 ) ) );
    range A2 = ws1->range( sheet_range( sheet_point( 1, 0 ) ) );

    wb1->named_formulas().create( *active_session, "test", variant( "=@hide" ), named_formula_scope::workbook_scope, ws1  );
    A1.value( *active_session, variant( "=test" ) );
    A2.value( *active_session, variant( "=volatile_count(A1)" ) );

    active_session->variable().variable( *active_session, "hide", "1" );
    check_formula_and_value( *active_session, A1, variant( "1" ), variant( "=test" ) );
    check_formula_and_value( *active_session, A2, variant( 1.0 ), variant( "=VOLATILE_COUNT(A1)" ) );
}

BOOST_AUTO_TEST_CASE( test_volatile_count_ws )
{
    range A1 = ws1->range( sheet_range( sheet_point( 0, 0 ) ) );
    range A2 = ws1->range( sheet_range( sheet_point( 1, 0 ) ) );

    wb1->named_formulas().create( *active_session, "test", variant( "=@hide" ), named_formula_scope::worksheet_scope, ws1  );
    A1.value( *active_session, variant( "=test" ) );
    A2.value( *active_session, variant( "=volatile_count(A1)" ) );

    active_session->variable().variable( *active_session, "hide", "1" );
    check_formula_and_value( *active_session, A1, variant( "1" ), variant( "=test" ) );
    check_formula_and_value( *active_session, A2, variant( 1.0 ), variant( "=VOLATILE_COUNT(A1)" ) );
}

// what the name suggests
BOOST_AUTO_TEST_CASE( test_named_formula_accessor_wb_scope )
{
    ws1->select( active_session->selected() );
    range A1 = ws1->range( sheet_range( sheet_point( 1, 1 ) ) );
    range B3 = ws1->range( sheet_range( sheet_point( 2, 1 ) ) );
    B3.value( *active_session, variant( 5.0 ) );
    A1.value( *active_session, variant( "=test" ) );

    //creation
    shared_named_formula_accessor_type nf_accessor = wb1->named_formulas().create_and_get_accessor( *active_session, "test", "=b3", named_formula_scope::workbook_scope, ws1, sheet_point( 1, 1 ) );

    BOOST_CHECK_THROW( wb1->named_formulas().create_and_get_accessor( *active_session, "test", "=b3", named_formula_scope::workbook_scope, ws1, sheet_point( 1, 1 ) ), named_formula_exception );

    const bool nf_accessor_exists = nf_accessor && nf_accessor->is_valid();
    BOOST_CHECK_EQUAL( nf_accessor_exists, true );
    BOOST_CHECK_EQUAL( wb1->named_formulas().value( *active_session, named_formula_identifier( std::string( "test" ) ), sheet_point( 1, 1 ) ), variant( 5.0 ) );
    if ( nf_accessor_exists ) {
        //value retrieval
        BOOST_CHECK_EQUAL( nf_accessor->value( *active_session, sheet_point( 1, 1 ) ), variant( 5.0 ) );
        BOOST_CHECK_EQUAL( nf_accessor->value( *active_session, sheet_point( 0, 0 ) ), variant( 0.0 ) );

        //formula
        BOOST_CHECK_EQUAL( nf_accessor->formula( active_session->locale(), sheet_point( 1, 1 ) ), variant( "=B3" ) );
        BOOST_CHECK_EQUAL( nf_accessor->formula( active_session->locale(), sheet_point( 0, 0 ) ), variant( "=A2" ) );

        //comment
        const std::string comment_string( "this is my new comment in the formula" );
        nf_accessor->comment( comment_string );
        BOOST_CHECK_EQUAL( nf_accessor->comment(), comment_string );

        //name
        BOOST_CHECK_EQUAL( nf_accessor->name(), std::string( "test" ) );

        //rename
        nf_accessor->name( *active_session, "new_name" );
        BOOST_CHECK_EQUAL( nf_accessor->name(), std::string( "new_name" ) );
        BOOST_CHECK_THROW( wb1->named_formulas().value( *active_session, named_formula_identifier( std::string( "test" )  ) ), named_formula_not_found_exception );

        //value setting
        nf_accessor->value( *active_session, variant( "=12+13" ) );
        BOOST_CHECK_EQUAL( nf_accessor->value( *active_session, sheet_point( 1, 1 ) ), variant( 25.0 ) );
        BOOST_CHECK_EQUAL( nf_accessor->formula( active_session->locale(), sheet_point( 1, 1 ) ), variant( "=12+13" ) );

        //getting multiple accessors
        shared_named_formula_accessor_type nf_accessor2 = wb1->named_formulas().get_accessor( *active_session, named_formula_identifier( std::string( "new_name" ) ) );
        nf_accessor2->value( *active_session, variant( "=500" ) );
        BOOST_CHECK_EQUAL( nf_accessor->value( *active_session, sheet_point( 1, 1 ) ), variant( 500.0 ) );


        //check removal
        nf_accessor->remove( *active_session );
        BOOST_CHECK_EQUAL( nf_accessor->is_valid(), false );
        BOOST_CHECK_EQUAL( nf_accessor2->is_valid(), false );
        BOOST_CHECK_THROW( wb1->named_formulas().value( *active_session, named_formula_identifier( std::string( "new_name" )  ) ), named_formula_not_found_exception );
    }
}

BOOST_AUTO_TEST_CASE( test_named_formula_accessor_ws_scope )
{
    ws1->select( active_session->selected() );
    range B3 = ws1->range( sheet_range( sheet_point( 2, 1 ) ) );
    B3.value( *active_session, variant( 5.0 ) );

    //creation
    shared_named_formula_accessor_type nf_accessor = wb1->named_formulas().create_and_get_accessor( *active_session, "test", "=b3", named_formula_scope::worksheet_scope, ws1, sheet_point( 1, 1 ) );

    BOOST_CHECK_THROW( wb1->named_formulas().create_and_get_accessor( *active_session, "test", "=b3", named_formula_scope::worksheet_scope, ws1, sheet_point( 1, 1 ) ), named_formula_exception );

    const bool nf_accessor_exists = nf_accessor && nf_accessor->is_valid();
    BOOST_CHECK_EQUAL( nf_accessor_exists, true );
    BOOST_CHECK_EQUAL( wb1->named_formulas().value( *active_session, named_formula_identifier( std::string( "test" ), ws1->uuid() ), sheet_point( 1, 1 ) ), variant( 5.0 ) );
    if ( nf_accessor_exists ) {
        //value retrieval
        BOOST_CHECK_EQUAL( nf_accessor->value( *active_session, sheet_point( 1, 1 ) ), variant( 5.0 ) );
        // BOOST_CHECK_EQUAL( nf_accessor->value( *active_session, sheet_point( 0, 0 ) ), variant() );

        //formula
        BOOST_CHECK_EQUAL( nf_accessor->formula( active_session->locale(), sheet_point( 1, 1 ) ), variant( "=B3" ) );
        //        BOOST_CHECK_EQUAL( nf_accessor->formula( active_session->locale(), sheet_point( 0, 0 ) ), variant( "=ws1!A2" ) );

        //comment
        const std::string comment_string( "this is my new comment in the formula" );
        nf_accessor->comment( comment_string );
        BOOST_CHECK_EQUAL( nf_accessor->comment(), comment_string );

        //name
        BOOST_CHECK_EQUAL( nf_accessor->name(), std::string( "test" ) );

        //rename
        nf_accessor->name( *active_session, "new_name" );
        BOOST_CHECK_EQUAL( nf_accessor->name(), std::string( "new_name" ) );
        BOOST_CHECK_THROW( wb1->named_formulas().value( *active_session, named_formula_identifier( std::string( "test" ), ws1->uuid() ) ), named_formula_not_found_exception );

        //value setting
        nf_accessor->value( *active_session, variant( "=12+13" ) );
        BOOST_CHECK_EQUAL( nf_accessor->value( *active_session, sheet_point( 1, 1 ) ), variant( 25.0 ) );
        BOOST_CHECK_EQUAL( nf_accessor->formula( active_session->locale(), sheet_point( 1, 1 ) ), variant( "=12+13" ) );

        //getting multiple accessors
        shared_named_formula_accessor_type nf_accessor2 = wb1->named_formulas().get_accessor( *active_session, named_formula_identifier( std::string( "new_name" ), ws1->uuid() ) );
        nf_accessor2->value( *active_session, variant( "=500" ), sheet_point( 1, 1 ) );
        BOOST_CHECK_EQUAL( nf_accessor->value( *active_session, sheet_point( 1, 1 ) ), variant( 500.0 ) );


        //check removal
        nf_accessor->remove( *active_session );
        BOOST_CHECK_EQUAL( nf_accessor->is_valid(), false );
        BOOST_CHECK_EQUAL( nf_accessor2->is_valid(), false );
        BOOST_CHECK_THROW( wb1->named_formulas().value( *active_session, named_formula_identifier( std::string( "new_name" ), ws1->uuid() ) ), named_formula_not_found_exception );
    }
}

BOOST_AUTO_TEST_CASE( test_multiple_named_formula_accessors )
{
    ws1->select( active_session->selected() );
    range B3 = ws1->range( sheet_range( sheet_point( 2, 1 ) ) );
    B3.value( *active_session, variant( 5.0 ) );

    //creation
    shared_named_formula_accessor_type nf_accessor_ws = wb1->named_formulas().create_and_get_accessor( *active_session, "test", "=b3", named_formula_scope::worksheet_scope, ws1, sheet_point( 1, 1 ) );
    shared_named_formula_accessor_type nf_accessor_ws2 = wb1->named_formulas().get_accessor( *active_session, named_formula_identifier( std::string( "test" ), ws1->uuid()  ) );
    shared_named_formula_accessor_type nf_accessor_wb =  wb1->named_formulas().create_and_get_accessor( *active_session, "test", "=b3", named_formula_scope::workbook_scope, ws1, sheet_point( 1, 1 ) );
    shared_named_formula_accessor_type nf_accessor_wb2 = wb1->named_formulas().get_accessor( *active_session,  named_formula_identifier( std::string( "test" ) ) );
    const bool all_nf_accessors_exists
    = nf_accessor_ws && nf_accessor_ws2 && nf_accessor_wb && nf_accessor_wb2
      && nf_accessor_ws->is_valid() && nf_accessor_ws2->is_valid() && nf_accessor_wb->is_valid() && nf_accessor_wb2->is_valid();

    BOOST_CHECK_EQUAL( all_nf_accessors_exists, true );
    if ( all_nf_accessors_exists ) {

        //value retrieval
        BOOST_CHECK_EQUAL( nf_accessor_ws->value( *active_session, sheet_point( 1, 1 ) ), variant( 5.0 ) );
        BOOST_CHECK_EQUAL( nf_accessor_ws2->value( *active_session, sheet_point( 0, 0 ) ), variant( 0.0 ) );

        //rename
        nf_accessor_ws->name( *active_session, "new_name" );
        nf_accessor_wb->name( *active_session, "new_wb_nf_name" );
        BOOST_CHECK_EQUAL( nf_accessor_ws->name(), std::string( "new_name" ) );
        BOOST_CHECK_EQUAL( nf_accessor_wb->name(), std::string( "new_wb_nf_name" ) );
        BOOST_CHECK_EQUAL( nf_accessor_ws2->name(), std::string( "new_name" ) );
        BOOST_CHECK_EQUAL( nf_accessor_wb2->name(), std::string( "new_wb_nf_name" ) );

        //check removal
        nf_accessor_ws->remove( *active_session );
        BOOST_CHECK_EQUAL( nf_accessor_ws->is_valid(), false );
        BOOST_CHECK_EQUAL( nf_accessor_ws2->is_valid(), false );
        BOOST_CHECK_EQUAL( nf_accessor_wb->is_valid(), true );
        BOOST_CHECK_EQUAL( nf_accessor_wb2->is_valid(), true );
        nf_accessor_wb->remove( *active_session );
        BOOST_CHECK_EQUAL( nf_accessor_wb2->is_valid(), false );
        BOOST_CHECK_THROW( wb1->named_formulas().value( *active_session, named_formula_identifier( std::string( "new_name" ), ws1->uuid() ) ), named_formula_not_found_exception );
        BOOST_CHECK_THROW( wb1->named_formulas().value( *active_session, named_formula_identifier( std::string( "new_wb_nf_name" ), boost::uuids::nil_uuid() ) ), named_formula_not_found_exception );
    }
}

BOOST_AUTO_TEST_CASE( test_named_formula_accessor_plus_reference_in_cell )
{
    ws1->select( active_session->selected() );
    range A1 = ws1->range( sheet_range( sheet_point( 0, 0 ) ) );
    A1.value( *active_session, variant( "=test" ) );

    shared_named_formula_accessor_type nf_accessor = wb1->named_formulas().create_and_get_accessor( *active_session, "test", "=rand()", named_formula_scope::worksheet_scope, ws1, sheet_point( 1, 1 ) );

    nf_accessor->remove( *active_session );

    BOOST_CHECK_EQUAL( nf_accessor->is_valid(), false );
}

BOOST_AUTO_TEST_CASE( test_named_formula_accessor_plus_reference_in_cell1 )
{
    ws1->select( active_session->selected() );

    shared_named_formula_accessor_type nf_accessor = wb1->named_formulas().create_and_get_accessor( *active_session, "test", "=1", named_formula_scope::worksheet_scope, ws1, sheet_point( 1, 1 ) );

    range A1 = ws1->range( sheet_range( sheet_point( 0, 0 ) ) );
    A1.value( *active_session, variant( "=test" ) );

    nf_accessor->remove( *active_session );

    BOOST_CHECK_EQUAL( nf_accessor->is_valid(), false );
}

BOOST_AUTO_TEST_CASE( test_named_formula_accessor_retrieval_by_uuid )
{
    ws1->select( active_session->selected() );
    uuid_type nf_id;
    {
        shared_named_formula_accessor_type nf_accessor = wb1->named_formulas().create_and_get_accessor( *active_session, "test", "=1", named_formula_scope::worksheet_scope, ws1, sheet_point( 1, 1 ) );
        nf_id = nf_accessor->uuid();
    }

    shared_named_formula_accessor_type nf_accessor2 = wb1->named_formulas().get_accessor( *active_session, nf_id );

    BOOST_CHECK_EQUAL( nf_accessor2->is_valid(), true );

    nf_accessor2->remove( *active_session );

    BOOST_CHECK_EQUAL( nf_accessor2->is_valid(), false );
}

BOOST_AUTO_TEST_CASE( test_multiple_named_formula_accessors_retrieval_by_uuid )
{
    ws1->select( active_session->selected() );

    shared_named_formula_accessor_type nf_accessor = wb1->named_formulas().create_and_get_accessor( *active_session, "test", "=1", named_formula_scope::worksheet_scope, ws1, sheet_point( 1, 1 ) );
    uuid_type nf_id = nf_accessor->uuid();

    shared_named_formula_accessor_type nf_accessor2 = wb1->named_formulas().get_accessor( *active_session, nf_id );

    BOOST_CHECK_EQUAL( nf_accessor->is_valid(), true );
    BOOST_CHECK_EQUAL( nf_accessor2->is_valid(), true );

    nf_accessor2->name( *active_session, "new_name" );

    BOOST_CHECK_EQUAL( nf_accessor->name(), "new_name" );
    BOOST_CHECK_EQUAL( nf_accessor2->name(), "new_name" );
}

// what the name suggests
BOOST_AUTO_TEST_CASE( test1_described_in_ticket_5958 )
{
    ws1->select( active_session->selected() );

    set_value_command( *active_session, sheet_range( sheet_point( 0, 0 ) ), variant( "ws1!A1" ) ).execute();
    set_value_command( *active_session, sheet_range( sheet_point( 2, 3 ) ), variant( "=test1" ) ).execute();
    set_value_command( *active_session, sheet_range( sheet_point( 3, 3 ) ), variant( "=test2" ) ).execute();
    set_value_command( *active_session, sheet_range( sheet_point( 4, 2 ) ), variant( "=bla" ) ).execute();
    set_value_command( *active_session, sheet_range( sheet_point( 4, 3 ) ), variant( "=test3" ) ).execute();
    set_value_command( *active_session, sheet_range( sheet_point( 5, 2 ) ), variant( "hallo" ) ).execute();
    set_value_command( *active_session, sheet_range( sheet_point( 5, 3 ) ), variant( "=test4" ) ).execute();

    select_worksheet_command( *active_session, "my_worksheet_2" ).execute();
    set_value_command( *active_session, sheet_range( sheet_point( 0, 0 ) ), variant( "my_worksheet_2!A1" ) ).execute();

    ws1->select( active_session->selected() );

    create_named_formula_command( *active_session, "test1", variant( "=ws1!$A$1" ) ).execute();
    create_named_formula_command( *active_session, "test2", variant( "=my_worksheet_2!$A$1" ) ).execute();
    create_named_formula_command( *active_session, "test3", variant( "=ws1!$C$5" ) ).execute();
    create_named_formula_command( *active_session, "test4", variant( "=ws1!$C$6" ) ).execute();

    delete_column_command( *active_session, 0, 1 ).execute();

    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *active_session, sheet_range( sheet_point( 2, 2 ) ) ) ), variant( variant::error_ref ) );
    BOOST_CHECK_EQUAL( execute_fetch( get_formula_command( *active_session, sheet_range( sheet_point( 2, 2 ) ) ) ), variant( "=test1" ) );
    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *active_session, sheet_range( sheet_point( 3, 2 ) ) ) ), variant( "my_worksheet_2!A1" ) );
    BOOST_CHECK_EQUAL( execute_fetch( get_formula_command( *active_session, sheet_range( sheet_point( 3, 2 ) ) ) ), variant( "=test2" ) );
    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *active_session, sheet_range( sheet_point( 4, 2 ) ) ) ), variant( variant::error_name ) );
    BOOST_CHECK_EQUAL( execute_fetch( get_formula_command( *active_session, sheet_range( sheet_point( 4, 2 ) ) ) ), variant( "=test3" ) );
    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *active_session, sheet_range( sheet_point( 5, 2 ) ) ) ), variant( "hallo" ) );
    BOOST_CHECK_EQUAL( execute_fetch( get_formula_command( *active_session, sheet_range( sheet_point( 5, 2 ) ) ) ), variant( "=test4" ) );
}


// what the name suggests
BOOST_AUTO_TEST_CASE( test2_described_in_ticket_5958 )
{
    ws1->select( active_session->selected() );

    set_value_command( *active_session, sheet_range( sheet_point( 0, 0 ) ), variant( "ws1!A1" ) ).execute();
    set_value_command( *active_session, sheet_range( sheet_point( 2, 3 ) ), variant( "=test1" ) ).execute();
    set_value_command( *active_session, sheet_range( sheet_point( 3, 3 ) ), variant( "=test2" ) ).execute();
    set_value_command( *active_session, sheet_range( sheet_point( 4, 2 ) ), variant( "=bla" ) ).execute();
    set_value_command( *active_session, sheet_range( sheet_point( 4, 3 ) ), variant( "=test3" ) ).execute();
    set_value_command( *active_session, sheet_range( sheet_point( 5, 2 ) ), variant( "hallo" ) ).execute();
    set_value_command( *active_session, sheet_range( sheet_point( 5, 3 ) ), variant( "=test4" ) ).execute();

    select_worksheet_command( *active_session, "my_worksheet_2" ).execute();
    set_value_command( *active_session, sheet_range( sheet_point( 0, 0 ) ), variant( "my_worksheet_2!A1" ) ).execute();
    const uuid_type my_worksheet_2_id = active_session->selected().worksheet().lock()->uuid();

    create_named_formula_command( *active_session, "test1", variant( "=ws1!$A$1" ) ).execute();
    create_named_formula_command( *active_session, "test2", variant( "=my_worksheet_2!$A$1" ) ).execute();
    create_named_formula_command( *active_session, "test3", variant( "=ws1!$C$5" ) ).execute();
    create_named_formula_command( *active_session, "test4", variant( "=ws1!$C$6" ) ).execute();
    ws1->select( active_session->selected() );

    delete_column_command( *active_session, 0, 1 ).execute();
    remove_worksheet_command( *active_session, my_worksheet_2_id ).execute();
    //needed because otherwise ws2 would still be there
    ws2.reset();

    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *active_session, sheet_range( sheet_point( 2, 2 ) ) ) ), variant( variant::error_ref ) );
    BOOST_CHECK_EQUAL( execute_fetch( get_formula_command( *active_session, sheet_range( sheet_point( 2, 2 ) ) ) ), variant( "=test1" ) );
    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *active_session, sheet_range( sheet_point( 3, 2 ) ) ) ),  variant( variant::error_ref ) );
    BOOST_CHECK_EQUAL( execute_fetch( get_formula_command( *active_session, sheet_range( sheet_point( 3, 2 ) ) ) ), variant( "=test2" ) );
    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *active_session, sheet_range( sheet_point( 4, 2 ) ) ) ), variant( variant::error_name ) );
    BOOST_CHECK_EQUAL( execute_fetch( get_formula_command( *active_session, sheet_range( sheet_point( 4, 2 ) ) ) ), variant( "=test3" ) );
    BOOST_CHECK_EQUAL( execute_fetch( get_value_command( *active_session, sheet_range( sheet_point( 5, 2 ) ) ) ), variant( "hallo" ) );
    BOOST_CHECK_EQUAL( execute_fetch( get_formula_command( *active_session, sheet_range( sheet_point( 5, 2 ) ) ) ), variant( "=test4" ) );
}
#endif // REENABLE_PASSED_TESTS
BOOST_AUTO_TEST_SUITE_END()
