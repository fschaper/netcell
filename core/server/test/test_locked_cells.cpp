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

#include <wss/session_handler.hpp>
#include <wss/execute_fetch.hpp>
#include <wss/session.hpp>
#include <wss/command.hpp>
#include <wss/server.hpp>
#include <wss/type.hpp>



struct locked_cell_fixture {
    locked_cell_fixture() {
        server::instance().startup();
        active_session = server::instance().session_handler().create( locale::create( "en-US" ) );

        create_application_command( *active_session, "my application" ).execute();
        select_application_command( *active_session, "my application" ).execute();
        create_workbook_command( *active_session, "my_workbook_1" ).execute();
        select_workbook_command( *active_session, "my_workbook_1" ).execute();
        create_worksheet_command( *active_session, "my_worksheet_1" ).execute();
        select_worksheet_command( *active_session, "my_worksheet_1" ).execute();
        create_worksheet_command( *active_session, "my_worksheet_2" ).execute();
        select_worksheet_command( *active_session, "my_worksheet_2" ).execute();
    }

    ~locked_cell_fixture() {
        try {
            server::instance().shutdown();
        } catch ( const std::exception& ) {
            assert( !"this may never throw" );
        }
    }

    locked_session active_session;
};

BOOST_FIXTURE_TEST_SUITE( locked_cells_test, locked_cell_fixture );

/*!
 * \brief
 * lock a range and do a query
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
BOOST_AUTO_TEST_CASE( lock_cells_test )
{
    set_cell_lock_command( *active_session, sheet_range( sheet_point( 1, 1 ), sheet_point( 3, 3 ) ), false ).execute();
    {
        variant::variant_array_type result_array = variant::variant_array_type();
        result_array.resize( 1 );
        result_array[0] =  variant( false );
        variant result( result_array );
        BOOST_CHECK_EQUAL( execute_fetch( get_server_query_command( *active_session, sheet_range( sheet_point( 1, 1 ) ), get_server_query_command::query_lock ) ), result );
    }
    {
        variant::variant_array_type result_array = variant::variant_array_type();
        result_array.resize( 1 );
        result_array[0] =  variant( false );
        variant result( result_array );
        BOOST_CHECK_EQUAL( execute_fetch( get_server_query_command( *active_session, sheet_range( sheet_point( 2, 2  ) ), get_server_query_command::query_lock ) ), result );
    }
    {
        variant::variant_array_type result_array = variant::variant_array_type();
        result_array.resize( 1 );
        variant result( result_array );
        BOOST_CHECK_EQUAL( execute_fetch( get_server_query_command( *active_session, sheet_range( sheet_point( 4, 4 ) ), get_server_query_command::query_lock ) ), result );
    }
}

BOOST_AUTO_TEST_SUITE_END()
