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

#include <wss/session_handler.hpp>
#include <wss/content_type.hpp>
#include <wss/session.hpp>
#include <wss/command.hpp>
#include <wss/server.hpp>
#include <wss/type.hpp>
#include <wss/execute_fetch.hpp>

struct content_type_fixture {
    content_type_fixture() {
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
    }

    ~content_type_fixture() {
        try {
            server::instance().shutdown();
        } catch ( const std::exception& ) {
            assert( !"this may never throw" );
        }
    }

    locked_session active_session;
};

BOOST_FIXTURE_TEST_SUITE( content_type_test, content_type_fixture );

/*!
 * \brief
 * copy different types of content from one cell to another
 *
 *  \author
 *  Frieder Hofmann <frieder.hofmann@jedox.com>
 */
BOOST_AUTO_TEST_CASE( same_sheet_copy_test_style )
{
    //check style

    set_style_command( *active_session, sheet_point( 0, 0 ), "background-color: red;" ).execute();
    set_value_command( *active_session, sheet_point( 0, 0 ), "=4+3" ).execute();
    copy_range_command::result_type id = execute_fetch( copy_range_command( *active_session, sheet_point( 0, 0 ) ) );
    paste_range_command( *active_session, sheet_point( 1, 1 ), id, content_type::style ).execute();
    variant formula = execute_fetch( get_formula_command( *active_session, sheet_point( 1, 1 ) ) );
    variant style = execute_fetch( get_style_command( *active_session, sheet_point( 1, 1 ) ) );

    // check for correct formula
    BOOST_CHECK_EQUAL( formula, variant() );
    // check for correct style information
    BOOST_CHECK_EQUAL( style.is_array(), true );
    if ( style.is_array() && ! style.array().empty() ) {
        variant style_result = style.array()[0];
        BOOST_CHECK_EQUAL( style_result.as_string( active_session->locale() ), "background-color:red;" );
    }
}
BOOST_AUTO_TEST_CASE( same_sheet_copy_test_value )
{
    set_style_command( *active_session, sheet_point( 0, 0 ), "background-color: red;" ).execute();
    set_value_command( *active_session, sheet_point( 0, 0 ), "=4+3" ).execute();
    copy_range_command::result_type id = execute_fetch( copy_range_command( *active_session, sheet_point( 0, 0 ) ) );
    paste_range_command( *active_session, sheet_point( 1, 1 ), id, content_type::value ).execute();

    variant formula = execute_fetch( get_formula_command( *active_session, sheet_point( 1, 1 ) ) );
    variant value = execute_fetch( get_value_command( *active_session, sheet_point( 1, 1 ) ) );
    variant style = execute_fetch( get_style_command( *active_session, sheet_point( 1, 1 ) ) );

    // check for correct formula
    BOOST_CHECK_EQUAL( formula,  variant( 7.0 ) );
    // check for correct value
    BOOST_CHECK_EQUAL( value, variant( 7.0 ) );
    // check for correct style information
    BOOST_CHECK_EQUAL( style.is_array(), true );
    if ( style.is_array() && ! style.array().empty() ) {
        variant style_result = style.array()[0];
        BOOST_CHECK_EQUAL( style_result.as_string( active_session->locale() ), "" );
    }
}

BOOST_AUTO_TEST_CASE( different_sheet_copy_test_style )
{

    set_style_command( *active_session, sheet_point( 0, 0 ), "background-color: red;" ).execute();
    set_value_command( *active_session, sheet_point( 0, 0 ), "=4+3" ).execute();
    copy_range_command::result_type id = execute_fetch( copy_range_command( *active_session, sheet_point( 0, 0 ) ) );
    select_worksheet_command( *active_session, "my_worksheet_2" ).execute();
    paste_range_command( *active_session, sheet_point( 1, 1 ), id, content_type::style ).execute();
    variant formula = execute_fetch( get_formula_command( *active_session, sheet_point( 1, 1 ) ) );
    variant style = execute_fetch( get_style_command( *active_session, sheet_point( 1, 1 ) ) );

    // check for correct formula
    BOOST_CHECK_EQUAL( formula, variant() );
    // check for correct style information
    BOOST_CHECK_EQUAL( style.is_array(), true );
    if ( style.is_array() && ! style.array().empty() ) {
        variant style_result = style.array()[0];
        BOOST_CHECK_EQUAL( style_result.as_string( active_session->locale() ), "background-color:red;" );
    }
}
BOOST_AUTO_TEST_CASE( different_sheet_copy_test_value )
{
    set_style_command( *active_session, sheet_point( 0, 0 ), "background-color: red;" ).execute();
    set_value_command( *active_session, sheet_point( 0, 0 ), "=4+3" ).execute();
    copy_range_command::result_type id = execute_fetch( copy_range_command( *active_session, sheet_point( 0, 0 ) ) );
    paste_range_command( *active_session, sheet_point( 1, 1 ), id, content_type::value ).execute();
    select_worksheet_command( *active_session, "my_worksheet_2" ).execute();

    variant formula = execute_fetch( get_formula_command( *active_session, sheet_point( 1, 1 ) ) );
    variant value = execute_fetch( get_value_command( *active_session, sheet_point( 1, 1 ) ) );
    variant style = execute_fetch( get_style_command( *active_session, sheet_point( 1, 1 ) ) );

    // check for correct formula
    BOOST_CHECK_EQUAL( formula,  variant( 7.0 ) );
    // check for correct value
    BOOST_CHECK_EQUAL( value, variant( 7.0 ) );
    // check for correct style information
    BOOST_CHECK_EQUAL( style.is_array(), true );
    if ( style.is_array() && ! style.array().empty() ) {
        variant style_result = style.array()[0];
        BOOST_CHECK_EQUAL( style_result.as_string( active_session->locale() ), "" );
    }
}

BOOST_AUTO_TEST_SUITE_END()
