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

struct copy_fixture {
    copy_fixture() {
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

    ~copy_fixture() {
        try {
            server::instance().shutdown();
        } catch ( const std::exception& ) {
            assert( !"this may never throw" );
        }
    }

    locked_session active_session;
};

BOOST_FIXTURE_TEST_SUITE( cell_copy_test, copy_fixture );

/*!
 * \brief
 * copy formula from one cell to another and check the formula rewriting.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
#if 0

BOOST_AUTO_TEST_CASE( same_sheet_copy_test )
{
    // formula & style copy test
    {
        dependency_info_list_type precedents_a1, precedents_b2;
        dependency_info_list_type dependents_b1, dependents_b2;
        dependency_info_list_type dependents_c1, dependents_c2;
        dependency_info_list_type all_precedents, all_dependents;

        execute_fetch( set_value_command( *active_session, sheet_point( 0, 0 ), "=b1:b2" ) );
        execute_fetch( set_style_command( *active_session, sheet_point( 0, 0 ), "background-color: red;" ) );
        execute_fetch( paste_range_command( *active_session, sheet_point( 1, 1 ), execute_fetch( copy_range_command( *active_session, sheet_point( 0, 0 ) ) ) ) );
        const variant formula = execute_fetch( get_formula_command( *active_session, sheet_point( 1, 1 ) ) );
        const variant style = execute_fetch( get_style_command( *active_session, sheet_point( 1, 1 ) ) );
        precedents_a1 = execute_fetch( get_precedents_command( *active_session, sheet_point( 0, 0 ) ) );
        precedents_b2 = execute_fetch( get_precedents_command( *active_session, sheet_point( 1, 1 ) ) );
        dependents_b1 = execute_fetch( get_dependents_command( *active_session, sheet_point( 0, 1 ) ) );
        dependents_b2 = execute_fetch( get_dependents_command( *active_session, sheet_point( 1, 1 ) ) );
        all_dependents = execute_fetch( get_dependents_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 100, 100 ) ) ) );
        all_precedents = execute_fetch( get_precedents_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 100, 100 ) ) ) );

        // create the current changeset of the worksheet.
        shared_worksheet_type swt( active_session->selected().worksheet().lock() );

        // check for correct formula
        BOOST_CHECK_EQUAL( formula.string(), "=C2:C3" );
        // check for correct style information
        variant::sparse_array_type style_vector;
        style_vector.push_back( variant( "background-color:red;" ) );
        BOOST_CHECK_EQUAL( style, variant( style_vector ) );
        // check for correct dependency information
        if ( 0 == precedents_a1.size() ) {
            BOOST_ERROR( "precedents_a1 is empty" );
        } else {
            BOOST_CHECK_EQUAL( precedents_a1[0].coverage, sheet_range( sheet_point( 0, 1 ), sheet_point( 1, 1 ) ) );
        }
        if ( 0 == precedents_b2.size() ) {
            BOOST_ERROR( "precedents_b2 is empty" );
        } else {
            BOOST_CHECK_EQUAL( precedents_b2[0].coverage, sheet_range( sheet_point( 1, 2 ), sheet_point( 2, 2 ) ) );
        }
        if ( 0 == dependents_b1.size() ) {
            BOOST_ERROR( "dependents_b1 is empty" );
        } else {
            BOOST_CHECK_EQUAL( dependents_b1[0].coverage, sheet_range( sheet_point( 0, 0 ) ) );
        }
        if ( 0 == dependents_b2.size() ) {
            BOOST_ERROR( "dependents_b2 is empty" );
        } else {
            BOOST_CHECK_EQUAL( dependents_b2[0].coverage, sheet_range( sheet_point( 0, 0 ) ) );
        }
        BOOST_CHECK_EQUAL( all_dependents.size(), 2 );
        BOOST_CHECK_EQUAL( all_precedents.size(), 2 );
    }

    // style copy test
    {
        execute_fetch( set_style_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 9, 9 ) ), "background-color: red;" ) );
        execute_fetch( set_style_command( *active_session, sheet_range( sheet_point( 2, 2 ) ), "background-color: yellow;" ) );
        execute_fetch( paste_range_command( *active_session, sheet_point( 20, 0 ), execute_fetch( copy_range_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 4, 4 ) ) ) ) ) );
        const variant style = execute_fetch( get_style_command( *active_session, sheet_range( sheet_point( 20, 0 ), sheet_point( 24, 4 ) ) ) );

        std::vector<variant> style_require( 25, variant( "background-color:red;" ) );
        style_require[12] = "background-color:yellow;";
        variant::sparse_array_type result_array( style.array() );

        BOOST_CHECK_EQUAL_COLLECTIONS( style_require.begin(), style_require.end(), result_array.begin(), result_array.end() );
    }
}

/*!
 * \brief
 * copy formula from one cell on one sheet to another cell on another sheet
 * and check the formula rewriting.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
BOOST_AUTO_TEST_CASE( copy_to_other_sheet_test )
{
    {
        clipboard::clipboard_id_type id;
        {
            execute_fetch( set_value_command( *active_session, sheet_point( 0, 0 ), "=b1:b2" ) );
            execute_fetch( set_style_command( *active_session, sheet_point( 0, 0 ), "background-color:red;" ) );
            id = execute_fetch( copy_range_command( *active_session, sheet_point( 0, 0 ) ) );
        }
        select_worksheet_command( *active_session, "my_worksheet_2" ).execute();
        {
            execute_fetch( paste_range_command( *active_session, sheet_point( 1, 1 ), id ) );
            const variant formula = execute_fetch( get_formula_command( *active_session, sheet_point( 1, 1 ) ) );
            const variant style = execute_fetch( get_style_command( *active_session, sheet_point( 1, 1 ) ) );
            BOOST_CHECK_EQUAL( formula.string(), "=C2:C3" );
            BOOST_CHECK_EQUAL( style.array()[0].string(), "background-color:red;" );
        }

    }

    // style copy test
    {
        clipboard::clipboard_id_type copy_id;
        {
            execute_fetch( set_style_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 9, 9 ) ), "background-color: red;" ) );
            execute_fetch( set_style_command( *active_session, sheet_range( sheet_point( 2, 2 ) ), "background-color: yellow;" ) );
            copy_id = execute_fetch( copy_range_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 4, 4 ) ) ) );
        }
        select_worksheet_command( *active_session, "my_worksheet_2" ).execute();
        {
            command_chain chain;
            execute_fetch( paste_range_command( *active_session, sheet_point( 20, 0 ), copy_id ) );
            const variant style = execute_fetch( get_style_command( *active_session, sheet_range( sheet_point( 20, 0 ), sheet_point( 24, 4 ) ) ) );

            std::vector<variant> style_require( 25, variant( "background-color:red;" ) );
            style_require[12] = "background-color:yellow;";
            variant::sparse_array_type result_array( style.array() );

            BOOST_CHECK_EQUAL_COLLECTIONS( style_require.begin(), style_require.end(), result_array.begin(), result_array.end() );
        }
    }

    // style copy test II
    {
        set_style_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 9, 9 ) ), "background-color: red;" ).execute();
        set_style_command( *active_session, sheet_range( sheet_point( 0, 7 ), sheet_point( 9, 9 ) ), "background-color: yellow;" ).execute();
        clipboard::clipboard_id_type id = execute_fetch( copy_range_command( *active_session, sheet_range( sheet_point( 0, 7 ), sheet_point( 10, 10 ) ) ) );
        select_worksheet_command( *active_session, "my_worksheet_2" ).execute();
        paste_range_command( *active_session, sheet_point( 0, 5 ), id ).execute();
        get_style_command gsc( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 0, 10 ) ) );
        gsc.execute();

        std::vector<variant> style_require( 11, variant( "background-color:red;" ) );
        style_require[5] = "background-color:yellow;";
        style_require[6] = "background-color:yellow;";
        style_require[7] = "background-color:yellow;";
        style_require[8] = variant();
        style_require[9] = "background-color:yellow;";
        style_require[10] = variant();

        variant::sparse_array_type result_array( gsc.value().array() );
        BOOST_CHECK_EQUAL_COLLECTIONS( style_require.begin(), style_require.end(), result_array.begin(), result_array.end() );
    }
}
#endif // 0

BOOST_AUTO_TEST_SUITE_END()
