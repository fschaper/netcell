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
 * \author
 * Radu Racariu <radu@yalos-solutions.com>
 */

#include <boost/test/unit_test.hpp>

#include <wss/session_handler.hpp>
#include <wss/session.hpp>
#include <wss/command.hpp>
#include <wss/server.hpp>
#include <wss/type.hpp>
#include <wss/execute_fetch.hpp>
#include <wss/get_attribute_command.hpp>


struct undo_redo_fixture {
    undo_redo_fixture() {
        server::instance().startup();
        active_session = server::instance().session_handler().create( locale::create( "en" ) );

        create_application_command( *active_session, "my application" ).execute();
        select_application_command( *active_session, "my application" ).execute();
        create_workbook_command( *active_session, "my_workbook_1" ).execute();
        select_workbook_command( *active_session, "my_workbook_1" ).execute();
        create_worksheet_command( *active_session, "my_worksheet_1" ).execute();
        create_worksheet_command( *active_session, "my_worksheet_2" ).execute();
        select_worksheet_command( *active_session, "my_worksheet_1" ).execute();
    }

    ~undo_redo_fixture() {
        try {
            server::instance().shutdown();
        } catch ( const std::exception& ) {
            assert( !"this may never throw" );
        }
    }

    locked_session active_session;
};

BOOST_FIXTURE_TEST_SUITE( undo_redo_test, undo_redo_fixture );

/*!
 * \brief
 * undo_redo_simple_set_value.
 *
 * \author
 * Radu Racariu <radu@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( undo_redo_simple_set_value )
{
    {
        transaction_wrapper& log = active_session->undo_redo_log();
        log.execute( set_value_command( *active_session, sheet_point( 0, 0 ), variant( 0.0 ) ) );
        log.execute( set_value_command( *active_session, sheet_point( 1, 0 ), variant( 1.0 ) ) );
        log.execute( set_value_command( *active_session, sheet_range( sheet_point( 2, 0 ), sheet_point( 2, 1 ) ), variant( 2.0 ) ) );
        log.execute( set_value_command( *active_session, sheet_point( 3, 0 ), variant( 3.0 ) ) );

        while ( log.can_undo() ) {
            log.undo();
        }

        variant v = execute_fetch( get_value_command( *active_session, sheet_point( 0, 0 ) ) );

        BOOST_CHECK_EQUAL( v.is_empty(), true );

        while ( log.can_redo() ) {
            log.redo();
        }

        v = execute_fetch( get_value_command( *active_session, sheet_point( 3, 0 ) ) );
        BOOST_CHECK_EQUAL( v, variant( 3.0 ) );
        v = execute_fetch( get_value_command( *active_session, sheet_point( 2, 1 ) ) );
        BOOST_CHECK_EQUAL( v, variant( 2.0 ) );
    }
}

/*!
* \brief
* undo_redo_simple_set_value and border.
*
* \author
* Radu Racariu <radu@yalos-solutions.com>
*/
BOOST_AUTO_TEST_CASE( undo_redo_simple_set_border )
{
    {
        transaction_wrapper& log = active_session->undo_redo_log();
        log.execute( set_value_command( *active_session, sheet_point( 0, 0 ), variant( 0.0 ) ) );
        log.execute( set_border_command( *active_session, sheet_range( sheet_point( 2, 0 ), sheet_point( 2, 1 ) ), 1, "test" ) );


        while ( log.can_undo() ) {
            log.undo();
        }

        variant v = execute_fetch( get_value_command( *active_session, sheet_point( 0, 0 ) ) );

        BOOST_CHECK_EQUAL( v.is_empty(), true );

        while ( log.can_redo() ) {
            log.redo();
        }

        std::vector<border_style_flyweight_type> style_vec = execute_fetch( get_border_command( *active_session, sheet_range( sheet_point( 2, 0 ), sheet_point( 2, 1 ) ) ) );
        std::string s = style_vec[0].get();
        BOOST_CHECK_EQUAL( s, "test" );
    }
}

/*!
* \brief
* undo_redo_comosite
*
* \author
* Radu Racariu <radu@yalos-solutions.com>
*/
BOOST_AUTO_TEST_CASE( undo_redo_composite )
{
    {
        transaction_wrapper& log = active_session->undo_redo_log();
        log.execute( set_value_command( *active_session, sheet_point( 0, 0 ), variant( 0.0 ) ) );
        log.execute( set_border_command( *active_session, sheet_range( sheet_point( 2, 0 ), sheet_point( 2, 1 ) ), 1, "test" ) );

        log.execute( select_worksheet_command ( *active_session, "my_worksheet_2" ) );

        log.start_transaction();
        log.execute( set_value_command( *active_session, sheet_point( 0, 0 ), variant( 7.0 ) ) );
        log.execute( set_style_command ( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 10, 10 ) ), "color:green;" ) );
        log.end_transaction();

        log.execute( set_value_command( *active_session, sheet_point( 10, 10 ), variant( 90.0 ) ) );


        while ( log.can_undo() ) {
            log.undo();
        }

        variant v = execute_fetch( get_value_command( *active_session, sheet_point( 0, 0 ) ) );

        BOOST_CHECK_EQUAL( v.is_empty(), true );

        while ( log.can_redo() ) {
            log.redo();
        }

        v = execute_fetch( get_value_command( *active_session, sheet_point( 0, 0 ) ) );
        BOOST_CHECK_EQUAL( v, variant( 7.0 ) );

        v = execute_fetch( get_value_command( *active_session, sheet_point( 10, 10 ) ) );
        BOOST_CHECK_EQUAL( v, variant( 90.0 ) );

        v = execute_fetch( get_style_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 10, 10 ) ) ) );
        BOOST_CHECK_EQUAL( ( v.array()[0] ), "color:green;" );
    }
}

}
