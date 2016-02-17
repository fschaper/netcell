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
#include <boost/foreach.hpp>

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
#include <wss/logger.hpp>
#include <wss/i_loggable.hpp>
#include <wss/logger_factory.hpp>
#include <wss/log_level_factory.hpp>
#include <wss/range.hpp>
#include <wss/locked_session.hpp>
#include <wss/command.hpp>

struct sandbox_fixture {
    sandbox_fixture()  : a1( 0, 0 ),
        a2( 1, 0 ),
        a3( 2, 0 ),
        a4( 3, 0 ) {
        server::instance().startup();
        active_session = server::instance().session_handler().create( locale::create( "en-US" ) );


        create_application_command( *active_session, "my application" ).execute();
        select_application_command( *active_session, "my application" ).execute();
        create_workbook_command( *active_session, "wb1" ).execute();
        select_workbook_command( *active_session, "wb1" ).execute();
        create_worksheet_command( *active_session, "my_worksheet_2" ).execute();
        select_worksheet_command( *active_session, "my_worksheet_2" ).execute();
        ws2 = active_session->selected().worksheet().lock();
        create_worksheet_command( *active_session, "ws1" ).execute();
        select_worksheet_command( *active_session, "ws1" ).execute();

        ws1 = active_session->selected().worksheet().lock();
        wb1 = active_session->selected().workbook().lock();
        maximum_iterations = active_session->selected().application()->calculation_settings().maximum_iterations();
    }

    ~sandbox_fixture() {
        try {
            ws1.reset();
            server::instance().shutdown();
        } catch ( const std::exception& /*e*/ ) {
            assert( !"this may never throw" );
        }
    }
    shared_worksheet_type ws2;
    locked_session active_session;
    shared_worksheet_type ws1;
    shared_workbook_type wb1;
    sheet_point a1;
    sheet_point a2;
    sheet_point a3;
    sheet_point a4;
    double maximum_iterations;
};

BOOST_FIXTURE_TEST_SUITE( sandbox_tests, sandbox_fixture );

variant create_var_array( const size_t s, const variant& d, const size_t column_count )
{
    variant::sparse_array_type return_array( s, d );
    return variant( return_array, column_count );
}

BOOST_AUTO_TEST_CASE( overwrite_move_test )
{
    sheet_point b1 = sheet_point( 0, 1 );
    sheet_point b2 = sheet_point( 1, 1 );
    sheet_point b3 = sheet_point( 2, 1 );
    sheet_point b4 = sheet_point( 3, 1 );
    sheet_point b5 = sheet_point( 4, 1 );
    sheet_point b6 = sheet_point( 5, 1 );
    sheet_point b7 = sheet_point( 6, 1 );
    sheet_point b8 = sheet_point( 7, 1 );

    typedef create_worksheet_element_command::key_value_vector_type kv_vec_type;
    kv_vec_type kv_vec;
    kv_vec.push_back( std::make_pair( "n_refers_to", "=$A$1:$B$10" ) );

    create_worksheet_element_command( *active_session, "", kv_vec ).execute();

    set_value_command( *active_session, b1 ,  "=@var" ).execute();
    set_value_command( *active_session, b2 , "=b1" ).execute();
    set_value_command( *active_session, b3 , "=b2" ).execute();
    set_value_command( *active_session, b4 , "=b3" ).execute();
    set_value_command( *active_session, b5 , "=b4" ).execute();
    set_value_command( *active_session, b6 , "=b5" ).execute();
    set_value_command( *active_session, b7 , "=b6" ).execute();
    set_value_command( *active_session, b8 , "=b7" ).execute();

    {
        const variant val1 = execute_fetch( get_value_command( *active_session, sheet_range( b1 ).enclose_point( b8 ) ) );
        variant::sparse_array_type expected_val1( 8, variant( variant::error_value ) );
        BOOST_CHECK_EQUAL_COLLECTIONS( val1.array().begin(), val1.array().end(), expected_val1.begin(), expected_val1.end() );

    }
    get_worksheet_elements_command( *active_session, "", get_worksheet_elements_command::id_vec_type(), get_worksheet_elements_command::key_vec_type(), get_worksheet_elements_command::key_value_vector_type() ).execute();
    active_session->variable().variable( "var", "first_val" );
    active_session->clear_cache();
    {
        const variant val1 = execute_fetch( get_value_command( *active_session, sheet_range( b1 ).enclose_point( b8 ) ) );
        variant::sparse_array_type expected_val1( 8, variant( "first_val" ) );
        BOOST_CHECK_EQUAL_COLLECTIONS( val1.array().begin(), val1.array().end(), expected_val1.begin(), expected_val1.end() );

    }

    active_session->variable().variable( "var", "second_val" );
    active_session->clear_cache();
    {
        const variant val1 = execute_fetch( get_value_command( *active_session, sheet_range( b1 ).enclose_point( b8 ) ) );
        variant::sparse_array_type expected_val1( 8, variant( "second_val" ) );
        BOOST_CHECK_EQUAL_COLLECTIONS( val1.array().begin(), val1.array().end(), expected_val1.begin(), expected_val1.end() );

    }

}

BOOST_AUTO_TEST_SUITE_END();
