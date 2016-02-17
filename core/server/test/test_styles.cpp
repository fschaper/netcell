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

struct style_fixture {
    style_fixture() {
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

    ~style_fixture() {
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

BOOST_FIXTURE_TEST_SUITE( style_test, style_fixture );


BOOST_AUTO_TEST_CASE( join_two_intervals )
{

    {
        execute_fetch( set_style_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 0, 9 ) ), style_1 ) );
        execute_fetch( set_style_command( *active_session, sheet_range( sheet_point( 0, 10 ), sheet_point( 0, 20 ) ), style_1 ) );
        const variant style = execute_fetch( get_style_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 0, 20 ) ) ) );

        std::vector<variant> style_require( 21, variant( style_1 ) );
        variant::sparse_array_type result_array( style.array() );

        BOOST_CHECK_EQUAL_COLLECTIONS( style_require.begin(), style_require.end(), result_array.begin(), result_array.end() );
    }
}



BOOST_AUTO_TEST_CASE( split_interval )
{

    {
        execute_fetch( set_style_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 0, 9 ) ), style_1 ) );
        execute_fetch( set_style_command( *active_session, sheet_range( sheet_point( 0, 6 ), sheet_point( 0, 9 ) ), style_2 ) );
        const variant style1 = execute_fetch( get_style_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 0, 5 ) ) ) );
        const variant style2 = execute_fetch( get_style_command( *active_session, sheet_range( sheet_point( 0, 6 ), sheet_point( 0, 9 ) ) ) );

        std::vector<variant> style_required1( 6, variant( style_1 ) );
        variant::sparse_array_type result_array1( style1.array() );

        std::vector<variant> style_required2( 4, variant( style_2 ) );
        variant::sparse_array_type result_array2( style2.array() );

        BOOST_CHECK_EQUAL_COLLECTIONS( style_required1.begin(), style_required1.end(), result_array1.begin(), result_array1.end() );
        BOOST_CHECK_EQUAL_COLLECTIONS( style_required2.begin(), style_required2.end(), result_array2.begin(), result_array2.end() );
    }
}




BOOST_AUTO_TEST_CASE( join_overlaping_intervals )
{

    {
        execute_fetch( set_style_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 0, 7 ) ), style_1 ) );
        execute_fetch( set_style_command( *active_session, sheet_range( sheet_point( 0, 4 ), sheet_point( 0, 20 ) ), style_1 ) );
        const variant style = execute_fetch( get_style_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 0, 20 ) ) ) );

        std::vector<variant> style_require( 21, variant( style_1 ) );
        variant::sparse_array_type result_array( style.array() );

        BOOST_CHECK_EQUAL_COLLECTIONS( style_require.begin(), style_require.end(), result_array.begin(), result_array.end() );
    }
}



BOOST_AUTO_TEST_CASE( join_three_intervals )
{

    {
        execute_fetch( set_style_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 0, 6 ) ), style_1 ) );
        execute_fetch( set_style_command( *active_session, sheet_range( sheet_point( 0, 7 ), sheet_point( 0, 7 ) ), style_1 ) );
        execute_fetch( set_style_command( *active_session, sheet_range( sheet_point( 0, 8 ), sheet_point( 0, 20 ) ), style_1 ) );
        const variant style = execute_fetch( get_style_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 0, 20 ) ) ) );

        std::vector<variant> style_required( 21, variant( style_1 ) );
        variant::sparse_array_type result_array( style.array() );

        BOOST_CHECK_EQUAL_COLLECTIONS( style_required.begin(), style_required.end(), result_array.begin(), result_array.end() );
    }
}



BOOST_AUTO_TEST_CASE( split_intervals_by_different_styles )
{

    {
        execute_fetch( set_style_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 0, 20 ) ), style_1 ) );
        execute_fetch( set_style_command( *active_session, sheet_range( sheet_point( 0, 7 ), sheet_point( 0, 7 ) ), style_2 ) );
        const variant style1 = execute_fetch( get_style_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 0, 6 ) ) ) );
        const variant style2 = execute_fetch( get_style_command( *active_session, sheet_range( sheet_point( 0, 8 ), sheet_point( 0, 20 ) ) ) );
        const variant style3 = execute_fetch( get_style_command( *active_session, sheet_range( sheet_point( 0, 7 ), sheet_point( 0, 7 ) ) ) );

        std::vector<variant> style_required1( 7, variant( style_1 ) );
        variant::sparse_array_type result_array1( style1.array() );

        std::vector<variant> style_required2( 13, variant( style_1 ) );
        variant::sparse_array_type result_array2( style2.array() );

        std::vector<variant> style_required3( 1, variant( style_2 ) );
        variant::sparse_array_type result_array3( style3.array() );

        BOOST_CHECK_EQUAL_COLLECTIONS( style_required1.begin(), style_required1.end(), result_array1.begin(), result_array1.end() );
        BOOST_CHECK_EQUAL_COLLECTIONS( style_required2.begin(), style_required2.end(), result_array2.begin(), result_array2.end() );
        BOOST_CHECK_EQUAL_COLLECTIONS( style_required3.begin(), style_required3.end(), result_array3.begin(), result_array3.end() );
    }
}



BOOST_AUTO_TEST_CASE( join_intervals_by_adding_styles )
{

    {
        execute_fetch( set_style_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 0, 6 ) ), style_1 ) );
        execute_fetch( set_style_command( *active_session, sheet_range( sheet_point( 0, 7 ), sheet_point( 0, 7 ) ), style_2 ) );
        execute_fetch( set_style_command( *active_session, sheet_range( sheet_point( 0, 8 ), sheet_point( 0, 20 ) ), style_1 ) );
        execute_fetch( set_style_command( *active_session, sheet_range( sheet_point( 0, 7 ), sheet_point( 0, 7 ) ), style_1 ) );
        const variant style1 = execute_fetch( get_style_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 0, 20 ) ) ) );

        std::vector<variant> style_required1( 21, variant( style_1 ) );
        variant::sparse_array_type result_array1( style1.array() );

        BOOST_CHECK_EQUAL_COLLECTIONS( style_required1.begin(), style_required1.end(), result_array1.begin(), result_array1.end() );
    }
}


BOOST_AUTO_TEST_CASE( split_intervals_by_erasing_styles )
{

    {
        set_style_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 0, 20 ) ), style_1 ).execute();
        clear_cells_command( *active_session, sheet_range( sheet_point( 0, 7 ), sheet_point( 0, 7 ) ), content_type::style ).execute();
        const variant style1 = execute_fetch( get_style_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 0, 6 ) ) ) );
        const variant style2 = execute_fetch( get_style_command( *active_session, sheet_range( sheet_point( 0, 8 ), sheet_point( 0, 20 ) ) ) );
        const variant style3 = execute_fetch( get_style_command( *active_session, sheet_range( sheet_point( 0, 7 ), sheet_point( 0, 7 ) ) ) );

        std::vector<variant> style_required1( 7, variant( style_1 ) );
        variant::sparse_array_type result_array1( style1.array() );

        std::vector<variant> style_required2( 13, variant( style_1 ) );
        variant::sparse_array_type result_array2( style2.array() );

        std::vector<variant> style_required3( 1, variant() );
        variant::sparse_array_type result_array3( style3.array() );

        BOOST_CHECK_EQUAL_COLLECTIONS( style_required1.begin(), style_required1.end(), result_array1.begin(), result_array1.end() );
        BOOST_CHECK_EQUAL_COLLECTIONS( style_required2.begin(), style_required2.end(), result_array2.begin(), result_array2.end() );
        BOOST_CHECK_EQUAL_COLLECTIONS( style_required3.begin(), style_required3.end(), result_array3.begin(), result_array3.end() );
    }
}



BOOST_AUTO_TEST_CASE( copy_ranges_same_sheet )
{

    {
        set_style_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 4, 4 ) ), style_1 ).execute();
        clipboard::clipboard_id_type id = execute_fetch( copy_range_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 4, 4 ) ) ) );
        paste_range_command( *active_session, sheet_point( 5, 5 ), id ).execute();
        const variant style = execute_fetch( get_style_command( *active_session, sheet_range( sheet_point( 5, 5 ), sheet_point( 9, 9 ) ) ) );

        std::vector<variant> style_required( 25, variant( style_1 ) );
        variant::sparse_array_type result_array( style.array() );
        BOOST_CHECK_EQUAL_COLLECTIONS( style_required.begin(), style_required.end(), result_array.begin(), result_array.end() );

        set_style_command( *active_session, sheet_range( sheet_point( 10, 10 ), sheet_point( 16, 16 ) ), style_2 ).execute();
        id = execute_fetch( copy_range_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 3, 3 ) ) ) );
        paste_range_command( *active_session, sheet_point( 15, 8 ), id ).execute();

        const variant style1 = execute_fetch( get_style_command( *active_session, sheet_range( sheet_point( 14, 10 ), sheet_point( 14, 16 ) ) ) );
        std::vector<variant> style_required1( 7, variant( style_2 ) );
        variant::sparse_array_type result_array1( style1.array() );
        BOOST_CHECK_EQUAL_COLLECTIONS( style_required1.begin(), style_required1.end(), result_array1.begin(), result_array1.end() );

        const variant style2 = execute_fetch( get_style_command( *active_session, sheet_range( sheet_point( 15, 12 ), sheet_point( 15, 16 ) ) ) );
        std::vector<variant> style_required2( 5, variant( style_2 ) );
        variant::sparse_array_type result_array2( style2.array() );
        BOOST_CHECK_EQUAL_COLLECTIONS( style_required2.begin(), style_required2.end(), result_array2.begin(), result_array2.end() );

        const variant style3 = execute_fetch( get_style_command( *active_session, sheet_range( sheet_point( 15, 10 ), sheet_point( 15, 11 ) ) ) );
        std::vector<variant> style_required3( 2, variant( style_1 ) );
        variant::sparse_array_type result_array3( style3.array() );
        BOOST_CHECK_EQUAL_COLLECTIONS( style_required3.begin(), style_required3.end(), result_array3.begin(), result_array3.end() );



    }
}


BOOST_AUTO_TEST_CASE( join_intervals_by_adding_tiny_ranges )
{

    {
        execute_fetch( set_style_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 0, 0 ) ), style_1 ) );
        execute_fetch( set_style_command( *active_session, sheet_range( sheet_point( 0, 1 ), sheet_point( 0, 1 ) ), style_2 ) );
        execute_fetch( set_style_command( *active_session, sheet_range( sheet_point( 0, 2 ), sheet_point( 0, 2 ) ), style_1 ) );
        execute_fetch( set_style_command( *active_session, sheet_range( sheet_point( 0, 7 ), sheet_point( 0, 7 ) ), style_1 ) );
        execute_fetch( set_style_command( *active_session, sheet_range( sheet_point( 0, 3 ), sheet_point( 0, 3 ) ), style_1 ) );
        execute_fetch( set_style_command( *active_session, sheet_range( sheet_point( 0, 6 ), sheet_point( 0, 6 ) ), style_1 ) );

        const variant style1 = execute_fetch( get_style_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 0, 7 ) ) ) );

        std::vector<variant> style_required1( 8, variant( style_1 ) );
        style_required1[1] = style_2;
        style_required1[4] = variant();
        style_required1[5] = variant();
        variant::sparse_array_type result_array1( style1.array() );

        BOOST_CHECK_EQUAL_COLLECTIONS( style_required1.begin(), style_required1.end(), result_array1.begin(), result_array1.end() );
    }
}


BOOST_AUTO_TEST_CASE( copy_ranges_same_sheet2 )
{

    set_style_command( *active_session, sheet_range( sheet_point( 8, 6 ), sheet_point( 8, 7 ) ), style_1 ).execute();
    set_style_command( *active_session, sheet_range( sheet_point( 8, 8 ), sheet_point( 8, 9 ) ), style_2 ).execute();
    set_style_command( *active_session, sheet_range( sheet_point( 8, 10 ), sheet_point( 9, 13 ) ), style_1 ).execute();
    set_style_command( *active_session, sheet_range( sheet_point( 9, 6 ), sheet_point( 9, 6 ) ), style_2 ).execute();
    set_style_command( *active_session, sheet_range( sheet_point( 9, 7 ), sheet_point( 9, 9 ) ), style_1 ).execute();
    const variant style = execute_fetch( get_style_command( *active_session, sheet_range( sheet_point( 8, 6 ), sheet_point( 9, 13 ) ) ) );

    std::vector<variant> style_required( 16, variant( style_1 ) );
    style_required[2] = style_2;
    style_required[3] = style_2;
    style_required[8] = style_2;
    variant::sparse_array_type result_array( style.array() );
    BOOST_CHECK_EQUAL_COLLECTIONS( style_required.begin(), style_required.end(), result_array.begin(), result_array.end() );

    clipboard::clipboard_id_type id = execute_fetch( copy_range_command( *active_session, sheet_range( sheet_point( 8, 6 ), sheet_point( 9, 13 ) ) ) );
    paste_range_command( *active_session, sheet_point( 0, 0 ), id ).execute();
    const variant style1 = execute_fetch( get_style_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 1, 7 ) ) ) );
    variant::sparse_array_type result_array1( style1.array() );
    BOOST_CHECK_EQUAL_COLLECTIONS( style_required.begin(), style_required.end(), result_array1.begin(), result_array1.end() );

    id = execute_fetch( copy_range_command( *active_session, sheet_range( sheet_point( 8, 6 ), sheet_point( 9, 13 ) ) ) );
    paste_range_command( *active_session, sheet_point( 6, 6 ), id ).execute();
    const variant style2 = execute_fetch( get_style_command( *active_session, sheet_range( sheet_point( 6, 6 ), sheet_point( 7, 13 ) ) ) );
    variant::sparse_array_type result_array2( style2.array() );
    BOOST_CHECK_EQUAL_COLLECTIONS( style_required.begin(), style_required.end(), result_array2.begin(), result_array2.end() );

    id = execute_fetch( copy_range_command( *active_session, sheet_range( sheet_point( 8, 6 ), sheet_point( 9, 13 ) ) ) );
    paste_range_command( *active_session, sheet_point( 7, 6 ), id ).execute();
    const variant style3 = execute_fetch( get_style_command( *active_session, sheet_range( sheet_point( 7, 6 ), sheet_point( 9, 13 ) ) ) );
    variant::sparse_array_type result_array3( style3.array() );

    std::vector<variant> style_required3( 24, variant( style_1 ) );
    style_required3[2] = style_2;
    style_required3[3] = style_2;
    style_required3[8] = style_2;
    style_required3[16] = style_2;
    BOOST_CHECK_EQUAL_COLLECTIONS( style_required3.begin(), style_required3.end(), result_array3.begin(), result_array3.end() );

    set_style_command( *active_session, sheet_range( sheet_point( 8, 6 ), sheet_point( 8, 7 ) ), style_1 ).execute();
    set_style_command( *active_session, sheet_range( sheet_point( 8, 8 ), sheet_point( 8, 9 ) ), style_2 ).execute();
    set_style_command( *active_session, sheet_range( sheet_point( 8, 10 ), sheet_point( 9, 13 ) ), style_1 ).execute();
    set_style_command( *active_session, sheet_range( sheet_point( 9, 6 ), sheet_point( 9, 6 ) ), style_2 ).execute();
    set_style_command( *active_session, sheet_range( sheet_point( 9, 7 ), sheet_point( 9, 9 ) ), style_1 ).execute();
    id = execute_fetch( copy_range_command( *active_session, sheet_range( sheet_point( 8, 6 ), sheet_point( 9, 13 ) ) ) );
    paste_range_command( *active_session, sheet_point( 8, 14 ), id ).execute();
    const variant style4 = execute_fetch( get_style_command( *active_session, sheet_range( sheet_point( 8, 6 ), sheet_point( 9, 21 ) ) ) );
    variant::sparse_array_type result_array4( style4.array() );
    std::vector<variant> style_required4( 32, variant( style_1 ) );
    style_required4[2] = style_2;
    style_required4[3] = style_2;
    style_required4[10] = style_2;
    style_required4[11] = style_2;
    style_required4[16] = style_2;
    style_required4[24] = style_2;
    BOOST_CHECK_EQUAL_COLLECTIONS( style_required4.begin(), style_required4.end(), result_array4.begin(), result_array4.end() );

    set_style_command( *active_session, sheet_range( sheet_point( 8, 6 ), sheet_point( 8, 7 ) ), style_1 ).execute();
    set_style_command( *active_session, sheet_range( sheet_point( 8, 8 ), sheet_point( 8, 9 ) ), style_2 ).execute();
    set_style_command( *active_session, sheet_range( sheet_point( 8, 10 ), sheet_point( 9, 13 ) ), style_1 ).execute();
    set_style_command( *active_session, sheet_range( sheet_point( 9, 6 ), sheet_point( 9, 6 ) ), style_2 ).execute();
    set_style_command( *active_session, sheet_range( sheet_point( 9, 7 ), sheet_point( 9, 9 ) ), style_1 ).execute();
    id = execute_fetch( copy_range_command( *active_session, sheet_range( sheet_point( 8, 6 ), sheet_point( 9, 13 ) ) ) );
    paste_range_command( *active_session, sheet_point( 9, 6 ), id ).execute();
    const variant style5 = execute_fetch( get_style_command( *active_session, sheet_range( sheet_point( 8, 6 ), sheet_point( 10, 13 ) ) ) );
    variant::sparse_array_type result_array5( style5.array() );
    std::vector<variant> style_required5( 24, variant( style_1 ) );
    style_required5[2] = style_2;
    style_required5[3] = style_2;
    style_required5[10] = style_2;
    style_required5[11] = style_2;
    style_required5[16] = style_2;
    BOOST_CHECK_EQUAL_COLLECTIONS( style_required5.begin(), style_required5.end(), result_array5.begin(), result_array5.end() );


}




BOOST_AUTO_TEST_SUITE_END()
