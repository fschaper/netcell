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

struct cell_array_fixture {
    cell_array_fixture() {
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

    ~cell_array_fixture() {
        try {
            server::instance().shutdown();
        } catch ( const std::exception& ) {
            assert( !"this may never throw" );
        }
    }

    locked_session active_session;
};

BOOST_FIXTURE_TEST_SUITE( cell_array_test, cell_array_fixture );

/*!
 * \brief
 * copy formula from one cell to another and check the formula rewriting.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
#if 0
BOOST_AUTO_TEST_CASE( initialize_cell_array )
{
    // formula & style copy test
    {
        set_value_command( *active_session, sheet_point( 0, 0 ), "=b1:b2" ).execute();
        set_style_command( *active_session, sheet_point( 0, 0 ), "background-color: red;" ).execute();
        copy_range_command::result_type id = execute_fetch( copy_range_command( *active_session, sheet_point( 0, 0 ) ) );
        paste_range_command( *active_session, sheet_point( 1, 1 ), id ).execute();


        // create the current changeset of the worksheet.
        shared_worksheet_type swt( active_session->selected().worksheet().lock() );

        dependency_info_list_type precedents_a1, precedents_b2;
        dependency_info_list_type dependents_b1, dependents_b2;
        dependency_info_list_type dependents_c1, dependents_c2;
        dependency_info_list_type all_precedents, all_dependents;
        precedents_a1 = execute_fetch( get_precedents_command( *active_session, sheet_point( 0, 0 ) ) );
        precedents_b2 = execute_fetch( get_precedents_command( *active_session, sheet_point( 1, 1 ) ) );
        dependents_b1 =  execute_fetch( get_dependents_command( *active_session, sheet_point( 0, 1 ) ) );
        dependents_b2 = execute_fetch( get_dependents_command( *active_session, sheet_point( 1, 1 ) ) );
        all_dependents = execute_fetch( get_dependents_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 100, 100 ) ) ) );
        all_precedents = execute_fetch( get_precedents_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 100, 100 ) ) ) );

        // check for correct formula
        BOOST_CHECK_EQUAL( execute_fetch( get_formula_command( *active_session, sheet_point( 1, 1 ) ) ), variant( "=C2:C3" ) );
        // check for correct style information
        variant::sparse_array_type style;
        style.push_back( variant( "background-color:red;" ) );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *active_session, sheet_point( 1, 1 ) ) ), variant( style ) );
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
}
#endif // 0

BOOST_AUTO_TEST_SUITE_END()
