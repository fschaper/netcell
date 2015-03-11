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
#include <wss/border_types.hpp>


std::vector<std::string> convert_to_string_vec(  const std::vector<border_style_flyweight_type>& v )
{
    std::vector<std::string> return_val;
    if ( !v.empty() ) {
        assert( v.size() == 6 );
        size_t i = 0;
        if ( !v[i].get().empty() ) {
            return_val.push_back( "top:" + v[i].get() );
        }
        ++i;
        if ( !v[i].get().empty() ) {
            return_val.push_back( "bottom:" + v[i].get() );
        }
        ++i;
        if ( !v[i].get().empty() ) {
            return_val.push_back( "left:" + v[i].get() );
        }
        ++i;
        if ( !v[i].get().empty() ) {
            return_val.push_back( "right:" + v[i].get() );
        }
        ++i;
        if ( !v[i].get().empty() ) {
            return_val.push_back( "inside:" + v[i].get() );
        }
        ++i;
        if ( !v[i].get().empty() ) {
            return_val.push_back( "outside:" + v[i].get() );
        }
    }

    return return_val;
}


std::ostream& operator<<( std::ostream& os, const std::vector<std::string>& v )
{
    os << "{";
    if ( !v.empty() ) {
        BOOST_FOREACH( const std::string & s, v ) {
            os << s << ";";
        }
    }

    os << "}" << std::endl;

    return os;
}

struct border_fixture {
    typedef std::vector<border_style_flyweight_type> border_style_vec;

    border_fixture()
        : a1( 0, 0 ),
          a2( 1, 0 ),
          a3( 2, 0 ),
          a4( 3, 0 ),
          b1( 0, 1 ),
          c1( 0, 2 ),
          style_string( "bstyle" ) {
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
    }

    ~border_fixture() {
        try {
            ws1.reset();
            ws2.reset();
            wb1.reset();
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
    sheet_point b1;
    sheet_point c1;
    const std::string style_string;
};

BOOST_FIXTURE_TEST_SUITE( border_tests, border_fixture );

BOOST_AUTO_TEST_CASE( set_border_test )
{
    set_border_command( *active_session, b1, border_types::top, style_string ).execute();
    get_style_command gsc( *active_session, b1 );
    get_style_command::result_type result = execute_fetch( gsc );
    std::string expected_result_string( "border-top:" + style_string + ";" );
    variant::sparse_array_type a;
    a.push_back( expected_result_string );
    BOOST_CHECK_EQUAL( result, variant( a ) );
}

BOOST_AUTO_TEST_CASE( get_border_command_test )
{
    set_border_command( *active_session, b1, border_types::top, style_string ).execute();
    get_border_command gbc( *active_session, b1 );
    std::vector<std::string> expected_result( 1, "" ), result_vec( convert_to_string_vec( execute_fetch( gbc ) ) );
    expected_result[0] = "top:" + style_string;
    BOOST_CHECK_EQUAL_COLLECTIONS( result_vec.begin(), result_vec.end(), expected_result.begin(), expected_result.end() );
}

BOOST_AUTO_TEST_CASE( move_border_test )
{
    set_border_command( *active_session, b1, border_types::top, style_string ).execute();
    move_range_command::result_type id = execute_fetch( move_range_command( *active_session, b1 ) );
    paste_range_command( *active_session, c1, id ).execute();
    {
        get_style_command gsc( *active_session, b1 );
        get_style_command::result_type result = execute_fetch( gsc );
        variant expected_result( variant::type_array );
        expected_result.array().push_back( variant() );
        BOOST_CHECK_EQUAL( result, expected_result );
    }
    {
        get_style_command gsc( *active_session, c1 );
        get_style_command::result_type result = execute_fetch( gsc );
        std::string expected_result_string( "border-top:" + style_string + ";" );
        variant::sparse_array_type a;
        a.push_back( expected_result_string );
        BOOST_CHECK_EQUAL( result, variant( a ) );
    }
}


BOOST_AUTO_TEST_CASE( move_border_other_sheet_test )
{
    set_border_command( *active_session, b1, border_types::top, style_string ).execute();
    move_range_command::result_type id = execute_fetch( move_range_command( *active_session, b1 ) );
    select_worksheet_command( *active_session, "my_worksheet_2" ).execute();
    paste_range_command( *active_session, c1, id ).execute();
    {
        select_worksheet_command( *active_session, "ws1" ).execute();
        get_style_command gsc( *active_session, b1 );
        get_style_command::result_type result = execute_fetch( gsc );
        variant expected_result( variant::type_array );
        expected_result.array().push_back( variant() );
        BOOST_CHECK_EQUAL( result, expected_result );
    }
    {
        select_worksheet_command( *active_session, "my_worksheet_2" ).execute();
        get_style_command gsc( *active_session, c1 );
        get_style_command::result_type result = execute_fetch( gsc );
        std::string expected_result_string( "border-top:" + style_string + ";" );
        variant::sparse_array_type a;
        a.push_back( expected_result_string );
        BOOST_CHECK_EQUAL( result, variant( a ) );
    }
}
BOOST_AUTO_TEST_CASE( copy_border_test )
{
    set_border_command( *active_session, b1, border_types::top, style_string ).execute();
    copy_range_command::result_type id = execute_fetch( copy_range_command( *active_session, b1 ) );
    paste_range_command( *active_session, c1, id ).execute();
    {
        get_style_command gsc( *active_session, b1 );
        get_style_command::result_type result = execute_fetch( gsc );
        std::string expected_result_string( "border-top:" + style_string + ";" );
        variant::sparse_array_type a;
        a.push_back( expected_result_string );
        BOOST_CHECK_EQUAL( result, variant( a ) );
    }
    {
        get_style_command gsc( *active_session, c1 );
        get_style_command::result_type result = execute_fetch( gsc );
        std::string expected_result_string( "border-top:" + style_string + ";" );
        variant::sparse_array_type a;
        a.push_back( expected_result_string );
        BOOST_CHECK_EQUAL( result, variant( a ) );

    }
}


BOOST_AUTO_TEST_CASE( copy_border_other_sheet_test )
{
    set_border_command( *active_session, b1, border_types::top, style_string ).execute();
    copy_range_command::result_type id = execute_fetch( copy_range_command( *active_session, b1 ) );
    select_worksheet_command( *active_session, "my_worksheet_2" ).execute();
    paste_range_command( *active_session, c1, id ).execute();
    {
        select_worksheet_command( *active_session, "ws1" ).execute();
        get_style_command gsc( *active_session, b1 );
        get_style_command::result_type result = execute_fetch( gsc );
        std::string expected_result_string( "border-top:" + style_string + ";" );
        variant::sparse_array_type a;
        a.push_back( expected_result_string );
        BOOST_CHECK_EQUAL( result, variant( a ) );

    }
    {
        select_worksheet_command( *active_session, "my_worksheet_2" ).execute();
        get_style_command gsc( *active_session, c1 );
        get_style_command::result_type result = execute_fetch( gsc );
        std::string expected_result_string( "border-top:" + style_string + ";" );
        variant::sparse_array_type a;
        a.push_back( expected_result_string );
        BOOST_CHECK_EQUAL( result, variant( a ) );

    }
}

BOOST_AUTO_TEST_CASE( overwrite_border_test )
{
    set_border_command( *active_session, b1, border_types::top, style_string ).execute();
    {
        get_style_command gsc( *active_session, b1 );
        get_style_command::result_type result = execute_fetch( gsc );
        std::string expected_result_string( "border-top:" + style_string + ";" );
        variant::sparse_array_type a;
        a.push_back( expected_result_string );
        BOOST_CHECK_EQUAL( result, variant( a ) );

    }
    set_border_command( *active_session, b1, border_types::left, style_string ).execute();
    {
        get_style_command gsc( *active_session, b1 );
        get_style_command::result_type result = execute_fetch( gsc );
        std::string expected_result_string(  "border-top:" + style_string + ";border-left:" + style_string + ";" );
        variant::sparse_array_type a;
        a.push_back( expected_result_string );
        BOOST_CHECK_EQUAL( result, variant( a ) );
    }
}

BOOST_AUTO_TEST_SUITE_END();