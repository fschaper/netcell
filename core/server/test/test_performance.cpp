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
 *  Radu Racariu <radu@yalos-solutions.com>
 */

#include "utils.hpp"


#include <boost/assign.hpp>
#include <boost/filesystem/operations.hpp>

#include <wss/session_handler.hpp>
#include <wss/session.hpp>
#include <wss/command.hpp>
#include <wss/server.hpp>
#include <wss/type.hpp>
#include <wss/a1conversion.hpp>

struct performance_fixture {


    performance_fixture() {
        server::instance().startup();
        active_session = server::instance().session_handler().create( locale::create( "en" ) );


        create_application_command( *active_session, "my application" ).execute();
        select_application_command( *active_session, "my application" ).execute();
        create_workbook_command( *active_session, "performance" ).execute();
        select_workbook_command( *active_session, "performance" ).execute();
        create_worksheet_command( *active_session, "performance" ).execute();
        select_worksheet_command( *active_session, "performance" ).execute();

    }

    ~performance_fixture() {
        try {
            server::instance().shutdown();
        } catch ( const std::exception& ) {
            assert( !"this may never throw" );
        }
    }

    locked_session active_session;
};

BOOST_FIXTURE_TEST_SUITE( performance_test, performance_fixture );

/*!
 * \brief
 *
 * \author
 *  Radu Racariu <radu@yalos-solutions.com>
 */
/*
BOOST_AUTO_TEST_CASE( create_complex_wb )
{
    TIMED_COMMAND_EXEC( select_worksheet_command( *active_session, "performance" ) );

    char num[2];
    BOOST_TEST_MESSAGE( "Calling @set_value_command with chain of dependant formulas" );
    boost::high_resolution_timer t;
    for ( int i  = 1; i < 32; i++  ) {
        for ( int j  = 1; j < 100; j++  ) {
            _itoa( i + 64, num, 10 );
            set_value_command( *active_session, sheet_range( sheet_point( i, j ) ),
                               variant( "=" + std::string( num )
                                        + "" + boost::lexical_cast<std::string>( j - 1 == 0 ? 1 :  j - 1  )
                                        + " *" + boost::lexical_cast<std::string>( j * i ) + "" ) );
        }

    }
    BOOST_TEST_MESSAGE( "executed in: ~" << t.elapsed() << " seconds" );
    TIMED_COMMAND_EXEC( get_value_command( *active_session, a1conversion::from_a1::range( "A1X500" ) ) );
}
*/
/*!
 * \brief
 *
 * \author
 *  Radu Racariu <radu@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( import_excel_big )
{
    boost::filesystem::path file ( "files/big+troubles.xlsx" );
    if ( boost::filesystem::exists( file ) ) {
        TIMED_COMMAND_EXEC( select_worksheet_command( *active_session, "performance" ) );
        TIMED_COMMAND_EXEC( load_workbook_command( *active_session, "files/big+troubles.xlsx", "", true ) );
        TIMED_COMMAND_EXEC( get_value_command( *active_session, a1conversion::from_a1::range( "A1X100" ) ) );
    }
}

/*!
 * \brief
 *
 * \author
 *  Radu Racariu <radu@yalos-solutions.com>
 */
/*
BOOST_AUTO_TEST_CASE( import_google_v2 )
{
    boost::filesystem::path file ( "files/Google_V2.wss" );
    if ( boost::filesystem::exists( file ) ) {
        TIMED_COMMAND_EXEC( select_worksheet_command( *active_session, "performance" ) );

        uuid_type wb_uuid = active_session->selected().workbook().lock()->uuid();

        TIMED_COMMAND_EXEC( remove_workbook_command( *active_session, wb_uuid ) );
        TIMED_COMMAND_EXEC( create_workbook_command( *active_session, "performance" ) );
        TIMED_COMMAND_EXEC( select_workbook_command( *active_session, "performance" ) );
        TIMED_COMMAND_EXEC( load_workbook_command( *active_session, "files/Google_V2.wss", "", true ) );
        TIMED_COMMAND_EXEC( get_value_command( *active_session, a1conversion::from_a1::range( "A1X100" ) ) );
    }
}
*/
BOOST_AUTO_TEST_SUITE_END()
