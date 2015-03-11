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

#include "utils.hpp"

#include <wss/can_not_change_merged_cell_exception.hpp>
#include <wss/session_handler.hpp>
#include <wss/execute_fetch.hpp>
#include <wss/session.hpp>
#include <wss/command.hpp>
#include <wss/server.hpp>
#include <wss/type.hpp>


struct merged_cells_fixture {
    merged_cells_fixture() {
        server::instance().startup();
        active_session = server::instance().session_handler().create( locale::create( "en" ) );

        create_application_command( *active_session, "my application" ).execute();
        select_application_command( *active_session, "my application" ).execute();
        create_workbook_command( *active_session, "my_workbook_1" ).execute();
        select_workbook_command( *active_session, "my_workbook_1" ).execute();
        create_worksheet_command( *active_session, "my_worksheet_1" ).execute();
        select_worksheet_command( *active_session, "my_worksheet_1" ).execute();
        create_worksheet_command( *active_session, "my_worksheet_2" ).execute();
        //select_worksheet_command( *active_session, "my_worksheet_2" ).execute();
    }

    ~merged_cells_fixture() {
        try {
            server::instance().shutdown();
        } catch ( const std::exception& ) {
            assert( !"this may never throw" );
        }
    }

    locked_session active_session;
};

BOOST_FIXTURE_TEST_SUITE( merged_cells_test, merged_cells_fixture );

/*!
 * \brief
 * merge a range and do a query
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
BOOST_AUTO_TEST_CASE( create_merge_cell_test )
{
    command_chain chain;
    chain.add( merge_cells_command( *active_session, sheet_range( sheet_point( 1, 1 ), sheet_point( 3, 3 ) ) ) );
    chain.add( get_server_query_command( *active_session, sheet_range( sheet_point( 1, 1 ) ), get_server_query_command::query_merge ) );
    chain.add( get_server_query_command( *active_session, sheet_range( sheet_point( 2, 2 ) ), get_server_query_command::query_merge ) );
    chain.execute();

    {
        variant::variant_array_type result_array = variant::variant_array_type();
        result_array.resize( 3 );
        result_array[0] =  variant( true );
        result_array[1] =  variant( 3.0 );
        result_array[2] =  variant( 3.0 );
        variant result( result_array );
        variant::sparse_array_type total;
        total.push_back( result );
        TYPED_CHECK_EQUAL( get_server_query_command, chain[1], variant( total ) );
    }
    {
        variant::variant_array_type result_array = variant::variant_array_type();
        result_array.resize( 3 );
        result_array[0] =  variant( false );
        result_array[1] =  variant( 1.0 );
        result_array[2] =  variant( 1.0 );
        variant result( result_array );
        variant::sparse_array_type total;
        total.push_back( result );
        TYPED_CHECK_EQUAL( get_server_query_command, chain[2], variant( total ) );
    }
}

/*!
 * \brief
 * merge a range, then try to merge an overlapping area
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
BOOST_AUTO_TEST_CASE( can_not_change_merge_cell_test )
{
    command_chain chain;
    chain.add( merge_cells_command( *active_session, sheet_range( sheet_point( 1, 1 ), sheet_point( 10, 10 ) ) ) );
    chain.add( merge_cells_command( *active_session, sheet_range( sheet_point( 5, 5 ), sheet_point( 30, 30 ) ) ) );

    BOOST_REQUIRE_THROW( chain.execute(), can_not_change_merged_cell_exception );
}

/*!
 * \brief
 * merge a range, copy on same sheet
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
BOOST_AUTO_TEST_CASE( same_sheet_copy_merged_range_test )
{
    merge_cells_command( *active_session, sheet_range( sheet_point( 1, 1 ), sheet_point( 3, 3 ) ) ).execute();
    clipboard::clipboard_id_type id = execute_fetch( copy_range_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 5, 5 ) ) ) );
    paste_range_command( *active_session, sheet_range( sheet_point( 4, 4 ), sheet_point( 9, 9 ) ), id ).execute();
    command_chain chain;
    chain.add( get_server_query_command( *active_session, sheet_range( sheet_point( 1, 1 ) ), get_server_query_command::query_merge ) );
    chain.add( get_server_query_command( *active_session, sheet_range( sheet_point( 2, 2 ) ), get_server_query_command::query_merge ) );
    chain.add( get_server_query_command( *active_session, sheet_range( sheet_point( 4, 4 ) ), get_server_query_command::query_merge ) );
    chain.add( get_server_query_command( *active_session, sheet_range( sheet_point( 6, 6 ) ), get_server_query_command::query_merge ) );
    chain.execute();

    {
        variant::variant_array_type result_array = variant::variant_array_type();
        result_array.resize( 3 );
        result_array[0] =  variant( true );
        result_array[1] =  variant( 3.0 );
        result_array[2] =  variant( 3.0 );
        variant result( result_array );
        variant::sparse_array_type total;
        total.push_back( result );
        TYPED_CHECK_EQUAL( get_server_query_command, chain[0], variant( total ) );
    }
    {
        variant::variant_array_type result_array = variant::variant_array_type();
        result_array.resize( 3 );
        result_array[0] =  variant( false );
        result_array[1] =  variant( 1.0 );
        result_array[2] =  variant( 1.0 );
        variant result( result_array );
        variant::sparse_array_type total;
        total.push_back( result );
        TYPED_CHECK_EQUAL( get_server_query_command, chain[1], variant( total ) );
    }


    {
        BOOST_CHECK_EQUAL( static_cast<const get_server_query_command&>( chain[2] ).value().array()[0], variant() );
    }
    {
        variant::variant_array_type result_array = variant::variant_array_type();
        result_array.resize( 3 );
        result_array[0] =  variant( false );
        result_array[1] =  variant( 5.0 );
        result_array[2] =  variant( 5.0 );
        variant result( result_array );
        variant::sparse_array_type total;
        total.push_back( result );
        TYPED_CHECK_EQUAL( get_server_query_command, chain[3], variant( total ) );
    }
}

/*!
 * \brief
 * merge a range, copy on different sheet
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
BOOST_AUTO_TEST_CASE( other_sheet_copy_merged_range_test )
{
    merge_cells_command( *active_session, sheet_range( sheet_point( 1, 1 ), sheet_point( 3, 3 ) ) ).execute();
    clipboard::clipboard_id_type id = execute_fetch( copy_range_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 5, 5 ) ) ) );
    select_worksheet_command( *active_session, "my_worksheet_2" ).execute();
    paste_range_command( *active_session, sheet_range( sheet_point( 4, 4 ) ), id ).execute();

    {
        select_worksheet_command( *active_session, "my_worksheet_1" ).execute();
        variant res1 = execute_fetch( get_server_query_command( *active_session, sheet_range( sheet_point( 1, 1 ) ), get_server_query_command::query_merge ) );
        variant::variant_array_type result_array = variant::variant_array_type();
        result_array.resize( 3 );
        result_array[0] =  variant( true );
        result_array[1] =  variant( 3.0 );
        result_array[2] =  variant( 3.0 );
        variant result( result_array );
        variant::sparse_array_type total;
        total.push_back( result );
        BOOST_CHECK_EQUAL( res1, variant( total ) );
    }
    {
        variant res2 = execute_fetch( get_server_query_command( *active_session, sheet_range( sheet_point( 2, 2 ) ), get_server_query_command::query_merge ) );
        variant::variant_array_type result_array = variant::variant_array_type();
        result_array.resize( 3 );
        result_array[0] =  variant( false );
        result_array[1] =  variant( 1.0 );
        result_array[2] =  variant( 1.0 );
        variant result( result_array );
        variant::sparse_array_type total;
        total.push_back( result );
        BOOST_CHECK_EQUAL( res2, variant( total ) );
    }


    {
        select_worksheet_command( *active_session, "my_worksheet_2" ).execute();
        variant res3 = execute_fetch( get_server_query_command( *active_session, sheet_range( sheet_point( 4, 4 ) ), get_server_query_command::query_merge ) );
        variant::variant_array_type result_array = variant::variant_array_type();
        result_array.resize( 1 );
        BOOST_CHECK_EQUAL( res3, variant( result_array ) );
    }
    {
        variant res4 = execute_fetch( get_server_query_command( *active_session, sheet_range( sheet_point( 6, 6 ) ), get_server_query_command::query_merge ) );
        variant::variant_array_type result_array = variant::variant_array_type();
        result_array.resize( 1 );
        BOOST_CHECK_EQUAL( res4, variant( result_array ) );
    }
}

/*!
 * \brief
 * merge a range, check size/position after insert column/row
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
BOOST_AUTO_TEST_CASE( insert_column_merged_range_test )
{
    command_chain chain;
    chain.add( merge_cells_command( *active_session, sheet_range( sheet_point( 1, 1 ), sheet_point( 3, 3 ) ) ) );
    chain.add( insert_column_command( *active_session, 2, 1 ) );
    chain.add( get_server_query_command( *active_session, sheet_range( sheet_point( 1, 1 ) ), get_server_query_command::query_merge ) );
    chain.execute();

    {
        variant::variant_array_type result_array = variant::variant_array_type();
        result_array.resize( 3 );
        result_array[0] =  variant( true );
        result_array[1] =  variant( 3.0 );
        result_array[2] =  variant( 4.0 );
        variant result( result_array );
        variant::sparse_array_type total;
        total.push_back( result );
        TYPED_CHECK_EQUAL( get_server_query_command, chain[2], variant( total ) );
    }
}

/*!
 * \brief
 * merge a range, check size/position after insert column/row
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
BOOST_AUTO_TEST_CASE( insert_row_merged_range_test )
{
    command_chain chain;
    chain.add( merge_cells_command( *active_session, sheet_range( sheet_point( 1, 1 ), sheet_point( 3, 3 ) ) ) );
    chain.add( insert_row_command( *active_session, 2, 1 ) );
    chain.add( get_server_query_command( *active_session, sheet_range( sheet_point( 1, 1 ) ), get_server_query_command::query_merge ) );
    chain.execute();

    {
        variant::variant_array_type result_array = variant::variant_array_type();
        result_array.resize( 3 );
        result_array[0] =  variant( true );
        result_array[1] =  variant( 4.0 );
        result_array[2] =  variant( 3.0 );
        variant result( result_array );
        variant::sparse_array_type total;
        total.push_back( result );
        TYPED_CHECK_EQUAL( get_server_query_command, chain[2], variant( total ) );
    }
}

/*!
 * \brief
 * merge a range, check size/position after delete column/row
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
BOOST_AUTO_TEST_CASE( delete_row_merged_range_test )
{
    command_chain chain;
    chain.add( merge_cells_command( *active_session, sheet_range( sheet_point( 1, 1 ), sheet_point( 4, 3 ) ) ) );
    chain.add( delete_row_command( *active_session, 2, 1 ) );
    chain.add( get_server_query_command( *active_session, sheet_range( sheet_point( 1, 1 ) ), get_server_query_command::query_merge ) );
    chain.execute();

    {
        variant::variant_array_type result_array = variant::variant_array_type();
        result_array.resize( 3 );
        result_array[0] =  variant( true );
        result_array[1] =  variant( 3.0 );
        result_array[2] =  variant( 3.0 );
        variant result( result_array );
        variant::sparse_array_type total;
        total.push_back( result );
        TYPED_CHECK_EQUAL( get_server_query_command, chain[2], variant( total ) );
    }
}

/*!
 * \brief
 * merge a range, check size/position after delete column/row
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
BOOST_AUTO_TEST_CASE( delete_column_merged_range_test )
{
    command_chain chain;
    chain.add( merge_cells_command( *active_session, sheet_range( sheet_point( 1, 1 ), sheet_point( 3, 4 ) ) ) );
    chain.add( delete_column_command( *active_session, 2, 1 ) );
    chain.add( get_server_query_command( *active_session, sheet_range( sheet_point( 1, 1 ) ), get_server_query_command::query_merge ) );
    BOOST_REQUIRE_NO_THROW( chain.execute() );

    {
        variant::variant_array_type result_array = variant::variant_array_type();
        result_array.resize( 3 );
        result_array[0] =  variant( true );
        result_array[1] =  variant( 3.0 );
        result_array[2] =  variant( 3.0 );
        variant result( result_array );
        variant::sparse_array_type total;
        total.push_back( result );
        TYPED_CHECK_EQUAL( get_server_query_command, chain[2], variant( total ) );
    }
}

BOOST_AUTO_TEST_SUITE_END()
