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

#include <boost/uuid/uuid.hpp>
#include <boost/assign.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/test/unit_test.hpp>

#include <wss/type.hpp>
#include <wss/server.hpp>
#include <wss/command.hpp>
#include <wss/exception.hpp>
#include <wss/worksheet.hpp>
#include <wss/execute_fetch.hpp>
#include <wss/command_chain.hpp>
#include <wss/session_handler.hpp>
#include <wss/worksheet_element.hpp>
#include <wss/worksheet_element_storage.hpp>

using namespace boost::assign;

struct worksheet_elements_fixture {
    worksheet_elements_fixture() {

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

    ~worksheet_elements_fixture() {
        try {
            server::instance().shutdown();
        } catch ( const std::exception& ) {
            assert( !"this may never throw" );
        }
    }

    locked_session active_session;
};
template<class contained_T>
struct vector_from_value_T {
    vector_from_value_T( const contained_T& t ) : m_contained( t ) {}
    operator std::vector<contained_T> () const {
        std::vector<contained_T> return_val;
        return_val += m_contained;
        return return_val;
    }

    contained_T m_contained;
};
typedef vector_from_value_T<std::string> vector_from_string;
typedef vector_from_value_T<worksheet_element::key_value_type> vector_from_kv;

template<class ostream>
ostream& operator<<( ostream& os, const worksheet_element::key_value_type& kv )
{
    os << " { " << kv.first << ", " << kv.second << " } ";
    return os;
}

template<class ostream>
ostream& operator<<( ostream& os, const worksheet_element::key_value_vector_type& kv_vec )
{
    foreach( const worksheet_element::key_value_vector_type::value_type & kv, kv_vec ) {
        os << kv;
    }
    return os;
}

BOOST_FIXTURE_TEST_SUITE( worksheet_element_tests, worksheet_elements_fixture );

/*!
* \brief
* create a worksheet element
*
* \author
* Frieder Hofmann <frieder.hofmann@jedox.com>
*/
BOOST_AUTO_TEST_CASE( test_create_worksheet_element )
{
    {
        create_worksheet_element_command cwec( *active_session, "", worksheet_element::key_value_vector_type() );
        BOOST_CHECK_NE( execute_fetch( cwec ), std::string( "" ) );
    }

    {
        //should throw because we are trying to set a system key that can't be changed
        create_worksheet_element_command cwec( *active_session, "", vector_from_kv( worksheet_element::key_value_type( "n_get_val", variant( 5.0 ) ) ) );
        BOOST_CHECK_NO_THROW( cwec.execute(), worksheet_element_exception );
    }
}

BOOST_AUTO_TEST_CASE( test_worksheet_element_values )
{
    set_value_command( *active_session, sheet_range( sheet_point( 0, 0 ) ), 2.0 ).execute();
    worksheet_element::key_value_vector_type kv;
    kv += worksheet_element::key_value_type( "e_type", "my_special_type" ),
          worksheet_element::key_value_type( "blablub", "value assigned to blablub" ),
          worksheet_element::key_value_type( "n_refers_to", "=my_worksheet_2!A1" );

    worksheet_element::key_value_vector_type query_type;
    query_type += worksheet_element::key_value_type( "e_type", "my_special_type" );
    worksheet_element::key_value_vector_type query_n_gv;
    query_n_gv += worksheet_element::key_value_type( "n_get_val", 2.0 );
    worksheet_element::key_value_vector_type query_n_refers_to;
    query_n_refers_to += worksheet_element::key_value_type( "n_refers_to", "=my_worksheet_2!A1" );
    worksheet_element::key_value_vector_type query_blablub;
    query_blablub += worksheet_element::key_value_type( "blablub", "value assigned to blablub" );

    const std::string id = execute_fetch(
                               create_worksheet_element_command( *active_session, "", kv ) );
    get_worksheet_elements_command cmd1( *active_session, "",
                                         get_worksheet_elements_command::key_vec_type(),
                                         vector_from_string( "e_type" ),
                                         query_type );
    get_worksheet_elements_command::result_type r1 = execute_fetch( cmd1 );


    get_worksheet_elements_command cmd2( *active_session, "",
                                         get_worksheet_elements_command::key_vec_type(),
                                         vector_from_string( "n_get_val" ),
                                         query_n_gv );
    get_worksheet_elements_command::result_type r2 = execute_fetch( cmd2 );

    get_worksheet_elements_command cmd3( *active_session, "",
                                         get_worksheet_elements_command::id_vec_type(),
                                         vector_from_string( "n_refers_to" ),
                                         query_n_refers_to ) ;
    get_worksheet_elements_command::result_type r3 = execute_fetch( cmd3 );

    get_worksheet_elements_command cmd4( *active_session, "",
                                         get_worksheet_elements_command::id_vec_type(),
                                         vector_from_string( "blablub" ),
                                         query_blablub );
    get_worksheet_elements_command::result_type r4 = execute_fetch( cmd4 );

    BOOST_CHECK_NE( id, boost::lexical_cast< std::string >( boost::uuids::nil_uuid() ) );
    BOOST_CHECK_EQUAL( r1.size(), 1 );
    BOOST_CHECK_EQUAL( r2.size(), 1 );
    BOOST_CHECK_EQUAL( r3.size(), 1 );
    BOOST_CHECK_EQUAL( r4.size(), 1 );

    BOOST_CHECK_EQUAL( r1.at( 0 ), query_type );
    BOOST_CHECK_EQUAL( r2.at( 0 ), query_n_gv );
    BOOST_CHECK_EQUAL( r3.at( 0 ), query_n_refers_to );
    BOOST_CHECK_EQUAL( r4.at( 0 ), query_blablub );
}

BOOST_AUTO_TEST_CASE( test_change_worksheet_element_list )
{
    //first create a worksheet element with a formula "=A1"
    command_chain chain;
    chain.add( create_worksheet_element_command( *active_session, "", vector_from_kv( worksheet_element::key_value_type( "n_refers_to", "=a1" ) ) ) );
    chain.add( get_worksheet_elements_command( *active_session, "",
                                               get_worksheet_elements_command::id_vec_type(),
                                               vector_from_string( "n_get_val" ),
                                               vector_from_kv( worksheet_element::key_value_type( "n_get_val", variant() ) ) ) );

    BOOST_CHECK_NO_THROW( chain.execute() );

    //then change value of a1
    command_chain second_chain;
    second_chain.add( set_value_command( *active_session, sheet_range( sheet_point( 0, 0 ) ), variant( "doesn't matter" ) ) );
    BOOST_CHECK_NO_THROW( second_chain.execute() );
}

BOOST_AUTO_TEST_CASE( test_worksheet_element_volatile_value )
{
    create_worksheet_element_command( *active_session, "", vector_from_kv( worksheet_element::key_value_type( "n_refers_to", "=rand()" ) ) ).execute();
    get_worksheet_elements_command gwsec( *active_session, "",
                                          get_worksheet_elements_command::id_vec_type(),
                                          vector_from_string( "n_get_val" ), get_worksheet_elements_command::key_value_vector_type() );
    get_worksheet_elements_command::result_type result = execute_fetch( gwsec );

    BOOST_CHECK_EQUAL( result.size(), 1 );

    if ( result.size() == 1 ) {
        BOOST_CHECK_EQUAL( result[0].size(), 1 );
        if ( result[0].size() == 1 ) {
            BOOST_CHECK_LE( variant( 0.0 ), result[0][0].second );
            BOOST_CHECK_LT( result[0][0].second , variant( 1.0 ) );
        }
    }
}

BOOST_AUTO_TEST_CASE( test_tried_to_access_invalidated_range_reference_problem_on_clone_sheet )
{
    worksheet_element::key_value_vector_type query_dirty;
    query_dirty += worksheet_element::key_value_type( "n_is_dirty", true );
    create_worksheet_element_command( *active_session, "", vector_from_kv( worksheet_element::key_value_type( "n_refers_to", "=B3:D4" ) ) ).execute();
    clone_worksheet_command cwc( *active_session, boost::uuids::nil_uuid(), true );
    clone_worksheet_command::result_type res = execute_fetch( cwc );
    select_worksheet_command( *active_session, boost::lexical_cast<uuid_type>( res ) ).execute();
    {
        update_worksheet_elements_command::key_value_vector_vector_type val_vec;
        val_vec.push_back( vector_from_kv( worksheet_element::key_value_type( "n_refers_to", "=$b$3;$e$3;$b$5;$b$4" ) ) );
        update_worksheet_elements_command uwec( *active_session, "", update_worksheet_elements_command::key_vec_type(), val_vec );

        BOOST_CHECK_NO_THROW( uwec.execute() );

        get_worksheet_elements_command gwc( *active_session, "", get_worksheet_elements_command::id_vec_type(), get_worksheet_elements_command::key_vec_type(), query_dirty );
        get_worksheet_elements_command::result_type res = execute_fetch( gwc );
    }
    {
        update_worksheet_elements_command::key_value_vector_vector_type val_vec;
        val_vec.push_back( vector_from_kv( worksheet_element::key_value_type( "n_refers_to", "=$b$3;$e$3;$b$11;$b$4;$b$6;$b$8;$b$10" ) ) );
        update_worksheet_elements_command uwec( *active_session, "", update_worksheet_elements_command::key_vec_type(), val_vec );

        BOOST_CHECK_NO_THROW( uwec.execute() );

        get_worksheet_elements_command gwc( *active_session, "", get_worksheet_elements_command::id_vec_type(), get_worksheet_elements_command::key_vec_type(), query_dirty );
        get_worksheet_elements_command::result_type res = execute_fetch( gwc );
    }
}

BOOST_AUTO_TEST_CASE( test_dirty_state )
{
    worksheet_element::key_value_vector_type query_dirty;
    query_dirty += worksheet_element::key_value_type( "n_is_dirty", true );

    //create a name
    create_named_formula_command( *active_session, "test", "=\"old_value\"" ).execute();

    //create a ws element and refer to that name
    create_worksheet_element_command( *active_session, "", vector_from_kv( worksheet_element::key_value_type( "n_refers_to", "=test" ) ) ).execute();

    {
        //update the name
        update_named_formula_command::key_val_map_type kv_map;
        kv_map["refers_to"] = "=\"new_value\"";
        update_named_formula_command( *active_session, named_formula_identifier( "test" ), kv_map ).execute();
    }
    {

        //update the name
        get_worksheet_elements_command gwc( *active_session, "", get_worksheet_elements_command::id_vec_type(), get_worksheet_elements_command::key_vec_type(), query_dirty );
        get_worksheet_elements_command::result_type res = execute_fetch( gwc );
        BOOST_CHECK_EQUAL( res.size(), 1 );
        if ( !res.empty() ) {
            BOOST_CHECK_GE( res.begin()->size(), 1 );
        }
    }
    {
        //update again, just because we can
        update_named_formula_command::key_val_map_type kv_map;
        kv_map["refers_to"] = "=\"super_new_value\"";
        update_named_formula_command( *active_session, named_formula_identifier( "test" ), kv_map ).execute();
    }
    {
        //and check again
        get_worksheet_elements_command gwc( *active_session, "", get_worksheet_elements_command::id_vec_type(), get_worksheet_elements_command::key_vec_type(), query_dirty );
        get_worksheet_elements_command::result_type res = execute_fetch( gwc );
        BOOST_CHECK_EQUAL( res.size(), 1 );
        if ( !res.empty() ) {
            BOOST_CHECK_GE( res.begin()->size(), 1 );
        }
    }
    {
        //and check again - this time nothing should be dirty, since nothing changed
        get_worksheet_elements_command gwc( *active_session, "", get_worksheet_elements_command::id_vec_type(), get_worksheet_elements_command::key_vec_type(), query_dirty );
        get_worksheet_elements_command::result_type res = execute_fetch( gwc );
        BOOST_CHECK_EQUAL( res.size(), 0 );
    }
}

BOOST_AUTO_TEST_SUITE_END()
