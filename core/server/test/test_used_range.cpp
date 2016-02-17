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
#include <boost/assign.hpp>

#include <wss/server.hpp>
#include <wss/command.hpp>
#include <wss/exception.hpp>
#include <wss/session_handler.hpp>

struct used_range_fixture {
    used_range_fixture() {
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

    ~used_range_fixture() {
        try {
            server::instance().shutdown();
        } catch ( const std::exception& ) {
            assert( !"this may never throw" );
        }
    }

    locked_session active_session;
};

BOOST_FIXTURE_TEST_SUITE( used_range_test, used_range_fixture );

/*!
 * \brief
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
BOOST_AUTO_TEST_CASE( cell_used_range_test )
{
    {
        command_chain chain;
        chain.add( set_value_command( *active_session, sheet_point( 0, 0 ), 10.0 ) );
        chain.add( get_used_range_command( *active_session ) );
        chain.execute();

        TYPED_CHECK_EQUAL( get_used_range_command, chain[1], optional_sheet_range_type( sheet_range( sheet_point( 0, 0 ) ) ) );
    }

    {
        command_chain chain;
        chain.add( set_value_command( *active_session, sheet_point( 10, 10 ), 10.0 ) );
        chain.add( get_used_range_command( *active_session ) );
        chain.execute();

        TYPED_CHECK_EQUAL( get_used_range_command, chain[1], optional_sheet_range_type( sheet_range( sheet_point( 0, 0 ), sheet_point( 10, 10 ) ) ) );
    }
}

/*!
 * \brief
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
BOOST_AUTO_TEST_CASE( style_used_range_test )
{
    {
        command_chain chain;
        chain.add( set_style_command( *active_session, sheet_point( 0, 0 ), "background-color:red;" ) );
        chain.add( get_used_range_command( *active_session ) );
        chain.execute();

        TYPED_CHECK_EQUAL( get_used_range_command, chain[1] , sheet_range( sheet_point( 0, 0 ) ) );
    }

    {
        command_chain chain;
        chain.add( set_style_command( *active_session, sheet_point( 10, 10 ), "background-color:red;" ) );
        chain.add( get_used_range_command( *active_session ) );
        chain.execute();

        TYPED_CHECK_EQUAL( get_used_range_command, chain[1], sheet_range( sheet_point( 0, 0 ), sheet_point( 10, 10 ) ) );
    }
}

BOOST_AUTO_TEST_SUITE_END()
