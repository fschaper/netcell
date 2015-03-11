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
 *  Vali Nitu <vali@yalos-solutions.com>
 */

#include "utils.hpp"

#include <wss/session_handler.hpp>
#include <wss/session.hpp>
#include <wss/command.hpp>
#include <wss/server.hpp>
#include <wss/type.hpp>
#include <wss/execute_fetch.hpp>
#include <wss/sheet_dimension.hpp>

struct style_fixture_9051 {
    style_fixture_9051() {
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

        style_1 = "background-color:red;";
        style_2 = "background-color:black;";
        style_3 = "background-color:yellow;";
        style_4 = "background-color:white;";
    }

    ~style_fixture_9051() {
        try {
            server::instance().shutdown();
        } catch ( const std::exception& ) {
            assert( !"this may never throw" );
        }
    }

    locked_session active_session;

    std::string style_1;
    std::string style_2;
    std::string style_3;
    std::string style_4;

};

BOOST_FIXTURE_TEST_SUITE( style_test_9051, style_fixture_9051 );


BOOST_AUTO_TEST_CASE( clear_style_9051 )
{

    {

        execute_fetch( set_style_command( *active_session, sheet_range( sheet_point( 2, 0 ), sheet_point( 2, sheet_dimension::max_column ) ), style_1 ) );
        execute_fetch( set_style_command( *active_session, sheet_range( sheet_point( 3, 0 ), sheet_point( 3, sheet_dimension::max_column ) ), style_1 ) );
        execute_fetch( set_style_command( *active_session, sheet_range( sheet_point( 4, 0 ), sheet_point( 4, sheet_dimension::max_column ) ), style_1 ) );
        execute_fetch( set_style_command( *active_session, sheet_range( sheet_point( 5, 0 ), sheet_point( 5, sheet_dimension::max_column ) ), style_1 ) );
        execute_fetch( set_style_command( *active_session, sheet_range( sheet_point( 6, 0 ), sheet_point( 6, sheet_dimension::max_column ) ), style_1 ) );
        execute_fetch( set_style_command( *active_session, sheet_range( sheet_point( 7, 0 ), sheet_point( 7, sheet_dimension::max_column ) ), style_1 ) );
        execute_fetch( set_style_command( *active_session, sheet_range( sheet_point( 8, 0 ), sheet_point( 8, sheet_dimension::max_column ) ), style_1 ) );

        execute_fetch( set_style_command( *active_session, sheet_range( sheet_point( 2, 1 ), sheet_point( 2, 3 ) ), style_3 ) );
        execute_fetch( set_style_command( *active_session, sheet_range( sheet_point( 2, 7 ), sheet_point( 2, 9 ) ), style_3 ) );
        execute_fetch( set_style_command( *active_session, sheet_range( sheet_point( 2, 11 ), sheet_point( 2, 13 ) ), style_3 ) );
        execute_fetch( set_style_command( *active_session, sheet_range( sheet_point( 3, 4 ), sheet_point( 3, 6 ) ), style_3 ) );
        execute_fetch( set_style_command( *active_session, sheet_range( sheet_point( 4, 0 ), sheet_point( 4, 4 ) ), style_3 ) );
        execute_fetch( set_style_command( *active_session, sheet_range( sheet_point( 5, 11 ), sheet_point( 5, 15 ) ), style_3 ) );
        execute_fetch( set_style_command( *active_session, sheet_range( sheet_point( 6, 2 ), sheet_point( 6, 15 ) ), style_3 ) );
        execute_fetch( set_style_command( *active_session, sheet_range( sheet_point( 7, 1 ), sheet_point( 7, 3 ) ), style_3 ) );
        execute_fetch( set_style_command( *active_session, sheet_range( sheet_point( 7, 7 ), sheet_point( 7, 9 ) ), style_3 ) );
        execute_fetch( set_style_command( *active_session, sheet_range( sheet_point( 7, 11 ), sheet_point( 7, 15 ) ), style_3 ) );


        clear_cells_command( *active_session, sheet_range( sheet_point( 2, 3 ), sheet_point( 8, 14 ) ), 86 ).execute();

        {
            const variant style = execute_fetch( get_style_command( *active_session, sheet_range( sheet_point( 2, 0 ), sheet_point( 2, 16 ) ) ) );

            std::vector<variant> style_required( 17, variant( style_1 ) );
            style_required[1] = style_3;
            style_required[2] = style_3;
            for( unsigned int i = 3; i < 15; i++ ) {
                style_required[i] = variant();
            }

            style_required[15] = style_1;
            style_required[16] = style_1;

            variant::sparse_array_type result_array( style.array() );

            BOOST_CHECK_EQUAL_COLLECTIONS( style_required.begin(), style_required.end(), result_array.begin(), result_array.end() );

        }
        {
            const variant style = execute_fetch( get_style_command( *active_session, sheet_range( sheet_point( 3, 0 ), sheet_point( 3, 16 ) ) ) );

            std::vector<variant> style_required( 17, variant( style_1 ) );
            for( unsigned int i = 3; i < 15; i++ ) {
                style_required[i] = variant();
            }


            variant::sparse_array_type result_array( style.array() );

            BOOST_CHECK_EQUAL_COLLECTIONS( style_required.begin(), style_required.end(), result_array.begin(), result_array.end() );
        }
        {
            const variant style = execute_fetch( get_style_command( *active_session, sheet_range( sheet_point( 4, 0 ), sheet_point( 4, 16 ) ) ) );

            std::vector<variant> style_required( 17, variant( style_1 ) );
            style_required[0] = style_3;
            style_required[1] = style_3;
            style_required[2] = style_3;
            for( unsigned int i = 3; i < 15; i++ ) {
                style_required[i] = variant();
            }


            variant::sparse_array_type result_array( style.array() );

            BOOST_CHECK_EQUAL_COLLECTIONS( style_required.begin(), style_required.end(), result_array.begin(), result_array.end() );

        }

        {
            const variant style = execute_fetch( get_style_command( *active_session, sheet_range( sheet_point( 5, 0 ), sheet_point( 5, 16 ) ) ) );

            std::vector<variant> style_required( 17, variant( style_1 ) );
            for( unsigned int i = 3; i < 15; i++ ) {
                style_required[i] = variant();
            }

            style_required[15] = style_3;

            variant::sparse_array_type result_array( style.array() );

            BOOST_CHECK_EQUAL_COLLECTIONS( style_required.begin(), style_required.end(), result_array.begin(), result_array.end() );

        }

        {
            const variant style = execute_fetch( get_style_command( *active_session, sheet_range( sheet_point( 6, 0 ), sheet_point( 6, 16 ) ) ) );

            std::vector<variant> style_required( 17, variant( style_1 ) );

            style_required[2] = style_3;
            for( unsigned int i = 3; i < 15; i++ ) {
                style_required[i] = variant();
            }

            style_required[15] = style_3;

            variant::sparse_array_type result_array( style.array() );

            BOOST_CHECK_EQUAL_COLLECTIONS( style_required.begin(), style_required.end(), result_array.begin(), result_array.end() );

        }

        {
            const variant style = execute_fetch( get_style_command( *active_session, sheet_range( sheet_point( 7, 0 ), sheet_point( 7, 16 ) ) ) );

            std::vector<variant> style_required( 17, variant( style_1 ) );

            style_required[1] = style_3;
            style_required[2] = style_3;
            for( unsigned int i = 3; i < 15; i++ ) {
                style_required[i] = variant();
            }

            style_required[15] = style_3;

            variant::sparse_array_type result_array( style.array() );

            BOOST_CHECK_EQUAL_COLLECTIONS( style_required.begin(), style_required.end(), result_array.begin(), result_array.end() );

        }

        {
            const variant style = execute_fetch( get_style_command( *active_session, sheet_range( sheet_point( 8, 0 ), sheet_point( 8, 16 ) ) ) );

            std::vector<variant> style_required( 17, variant( style_1 ) );

            for( unsigned int i = 3; i < 15; i++ ) {
                style_required[i] = variant();
            }

            variant::sparse_array_type result_array( style.array() );

            BOOST_CHECK_EQUAL_COLLECTIONS( style_required.begin(), style_required.end(), result_array.begin(), result_array.end() );

        }

    }
}




BOOST_AUTO_TEST_SUITE_END()
