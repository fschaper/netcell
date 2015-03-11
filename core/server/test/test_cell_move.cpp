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


struct move_fixture {
    move_fixture() {
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

    ~move_fixture() {
        try {
            server::instance().shutdown();
        } catch ( const std::exception& ) {
            assert( !"this may never throw" );
        }
    }

    locked_session active_session;
};

BOOST_FIXTURE_TEST_SUITE( cell_move_test, move_fixture );

/*!
 * \brief
 * copy formula from one cell to another and check the formula rewriting.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
BOOST_AUTO_TEST_CASE( same_sheet_move_test )
{
    {
        execute_fetch( set_value_command( *active_session, sheet_point( 0, 0 ), "=b1" ) );
        execute_fetch( set_style_command( *active_session, sheet_point( 0, 0 ), "background-color: red;" ) );
        execute_fetch( paste_range_command( *active_session, sheet_point( 1, 1 ), execute_fetch( move_range_command( *active_session, sheet_point( 0, 0 ) ) ) ) );

        {
            const variant formula = execute_fetch( get_formula_command( *active_session, sheet_point( 1, 1 ) ) );
            BOOST_CHECK_EQUAL( formula, variant( "=B1" ) );
        }
        {
            const variant style_1 = execute_fetch( get_style_command( *active_session, sheet_point( 1, 1 ) ) );
            variant::sparse_array_type style_require_1;
            style_require_1.push_back( variant( "background-color:red;" ) );
            BOOST_CHECK_EQUAL( style_1, style_require_1 );
        }
        {
            const variant style_2 = execute_fetch( get_style_command( *active_session, sheet_point( 0, 0 ) ) );
            variant::sparse_array_type style_require_1( 1, variant() );
            BOOST_CHECK_EQUAL( style_2, style_require_1 );
        }
    }

    // style move test
    {
        execute_fetch( set_style_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 9, 9 ) ), "background-color: red;" ) );
        execute_fetch( set_style_command( *active_session, sheet_range( sheet_point( 2, 2 ) ), "background-color: yellow;" ) );
        execute_fetch( paste_range_command( *active_session, sheet_point( 20, 0 ), execute_fetch( move_range_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 4, 4 ) ) ) ) ) );

        {
            const variant style_1 = execute_fetch( get_style_command( *active_session, sheet_range( sheet_point( 20, 0 ), sheet_point( 24, 4 ) ) ) );
            variant::sparse_array_type style_require_1( 25, variant( "background-color:red;" ) );
            style_require_1[12] = "background-color:yellow;";
            variant::sparse_array_type result_array_1( style_1.array() );
            BOOST_CHECK_EQUAL_COLLECTIONS( style_require_1.begin(), style_require_1.end(), result_array_1.begin(), result_array_1.end() );
        }

        {
            const variant style_2 = execute_fetch( get_style_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 4, 4 ) ) ) );
            variant::sparse_array_type style_require_2( 25, variant() );
            variant::sparse_array_type result_array_2( style_2.array() );
            BOOST_CHECK_EQUAL_COLLECTIONS( style_require_2.begin(), style_require_2.end(), result_array_2.begin(), result_array_2.end() );
        }
    }
}

/*!
 * \brief
 * move formula from one cell on one sheet to another cell on another sheet
 * and check the formula rewriting.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
BOOST_AUTO_TEST_CASE( move_to_other_sheet_test )
{
    {
        select_worksheet_command( *active_session, "my_worksheet_1" ).execute();
        set_value_command( *active_session, sheet_point( 0, 0 ), "=b1:b2" ).execute();
        clipboard::clipboard_id_type id = execute_fetch( move_range_command( *active_session, sheet_point( 0, 0 ) ) );
        select_worksheet_command( *active_session, "my_worksheet_2" ).execute();
        paste_range_command( *active_session, sheet_point( 1, 1 ), id ).execute();
        get_formula_command gfc( *active_session, sheet_point( 1, 1 ) );
        gfc.execute();

        BOOST_CHECK_EQUAL( gfc.value(), "=my_worksheet_1!B1:B2" );
    }
}


BOOST_AUTO_TEST_SUITE_END()
