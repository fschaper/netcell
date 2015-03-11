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
 *  Radu Ialovoi <ialovoi@yahoo.com>
 */
#include "utils.hpp"

#include <boost/test/unit_test.hpp>
#include <boost/assign.hpp>

#include <wss/session_handler.hpp>
#include <wss/session.hpp>
#include <wss/command.hpp>
#include <wss/server.hpp>
#include <wss/type.hpp>

struct persistence_fixture {


    uuid_type   m_wb_id;

    persistence_fixture() {
        server::instance().startup();
        active_session = server::instance().session_handler().create( locale::create( "en" ) );


        create_application_command( *active_session, "my application" ).execute();
        select_application_command( *active_session, "my application" ).execute();
        create_workbook_command( *active_session, "my_workbook_1" ).execute();
        select_workbook_command( *active_session, "my_workbook_1" ).execute();
        create_worksheet_command( *active_session, "my_worksheet_1" ).execute();
        select_worksheet_command( *active_session, "my_worksheet_1" ).execute();

        m_wb_id = active_session->selected().workbook().lock()->uuid();

    }

    ~persistence_fixture() {
        try {
            server::instance().shutdown();
        } catch ( const std::exception& ) {
            assert( !"this may never throw" );
        }
    }

    locked_session active_session;
};

BOOST_FIXTURE_TEST_SUITE( persistence_test, persistence_fixture );

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( persistence_test )
{
    command_chain chain;

    boost::filesystem::path src_target = "test_src.wss";
    boost::filesystem::path dst_target = "test_dst.wss";
    chain.add( load_workbook_command( *active_session, src_target, "", true ) );
    chain.add( get_workbook_version_command( *active_session, boost::uuids::nil_uuid() ) );
    chain.add( save_workbook_command( *active_session, boost::uuids::nil_uuid(), dst_target ) );
    chain.execute();

    TYPED_CHECK_EQUAL( get_workbook_version_command, chain[1], "WSS workbook, version 1.6" );

}


BOOST_AUTO_TEST_SUITE_END()
