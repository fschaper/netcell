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

#include <boost/assign.hpp>

#include <wss/session_handler.hpp>
#include <wss/session.hpp>
#include <wss/command.hpp>
#include <wss/server.hpp>
#include <wss/type.hpp>

struct formatting_fixture {

    formatting_fixture() {
        server::instance().startup();
        german_session = server::instance().session_handler().create( locale::create( "de-de" ) );
        english_session = server::instance().session_handler().create( locale::create( "en-en" ) );
        french_session = server::instance().session_handler().create( locale::create( "nl-nl" ) );

    }

    ~formatting_fixture() {
        try {
            server::instance().shutdown();
        } catch ( const std::exception& ) {
            assert( !"this may never throw" );
        }
    }

    locked_session english_session;
    locked_session german_session;
    locked_session french_session;
};

BOOST_FIXTURE_TEST_SUITE( formatting_test, formatting_fixture );

/*!
 * \brief
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( formatting_test )
{
    command_chain chain;
    chain.add( get_formatted_value_command( *german_session, "#,##0.00" ,  variant( 1234.12 ) ) );
    chain.add( get_formatted_value_command( *english_session, "#,##0.00" ,  variant( 1234.12 ) ) );
    chain.execute();

    TYPED_CHECK_EQUAL( get_formatted_value_command, chain[0], "1.234,12" );
    TYPED_CHECK_EQUAL( get_formatted_value_command, chain[1], "1,234.12" );
}


BOOST_AUTO_TEST_SUITE_END()
