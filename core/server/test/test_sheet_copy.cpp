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
#include <wss/session.hpp>
#include <wss/command.hpp>
#include <wss/server.hpp>
#include <wss/type.hpp>


struct sheet_copy_fixture {
    sheet_copy_fixture() {
        server::instance().startup();
        active_session = server::instance().session_handler().create( locale::create( "en" ) );

        create_application_command( *active_session, "my application" ).execute();
        select_application_command( *active_session, "my application" ).execute();
        create_workbook_command( *active_session, "my_workbook_1" ).execute();
        select_workbook_command( *active_session, "my_workbook_1" ).execute();
        create_workbook_command( *active_session, "my_workbook_2" ).execute();
        create_worksheet_command( *active_session, "my_worksheet_1" ).execute();
        select_worksheet_command( *active_session, "my_worksheet_1" ).execute();
        create_worksheet_command( *active_session, "my_worksheet_2" ).execute();
        select_worksheet_command( *active_session, "my_worksheet_2" ).execute();
    }

    ~sheet_copy_fixture() {
        try {
            server::instance().shutdown();
        } catch ( const std::exception& ) {
            assert( !"this may never throw" );
        }
    }

    locked_session active_session;
};

BOOST_FIXTURE_TEST_SUITE( sheet_copy, sheet_copy_fixture );

/*!
* \brief
* copy a sheet and check style/value/named formulas etc
*
* \author
* Frieder Hofmann <frieder.hofmann@jedox.com>
*/
BOOST_AUTO_TEST_CASE( copy_sheet_same_workbook )
{
    select_worksheet_command( *active_session, "my_worksheet_1" ).execute();
    {
        command_chain chain;
        chain.add( set_value_command( *active_session, sheet_point( 0, 0 ), "=b1:b2" ) );
        chain.add( set_style_command( *active_session, sheet_point( 0, 0 ), "background-color:red;" ) );
        chain.add( copy_worksheet_command( *active_session, "", "", "" ) );
        chain.execute();
    }

    select_worksheet_command( *active_session, "my_worksheet_1 (2)" ).execute();
    {
        command_chain chain;
        chain.add( get_formula_command( *active_session, sheet_point( 0, 0 ) ) );
        chain.add( get_style_command( *active_session, sheet_point( 0, 0 ) ) );
        chain.execute();

        TYPED_CHECK_EQUAL( get_formula_command, chain[0], variant( "=B1:B2" ) );
        variant::sparse_array_type  array;
        array.push_back( variant( "background-color:red;" ) );
        TYPED_CHECK_EQUAL( get_style_command, chain[1], variant( array ) );
    }
}

/*!
* \brief
* copy a sheet and check style/value/named formulas etc
*
* \author
* Frieder Hofmann <frieder.hofmann@jedox.com>
*/
BOOST_AUTO_TEST_CASE( copy_sheet_other_workbook )
{
    select_workbook_command( *active_session, "my_workbook_2" ).execute();
    uuid_type target_wb_id = active_session->selected().workbook().lock()->uuid();
    select_workbook_command( *active_session, "my_workbook_1" ).execute();
    select_worksheet_command( *active_session, "my_worksheet_1" ).execute();

    {
        command_chain chain;
        chain.add( set_value_command( *active_session, sheet_point( 0, 0 ), "=b1:b2" ) );
        chain.add( set_style_command( *active_session, sheet_point( 0, 0 ), "background-color:red;" ) );
        chain.add( copy_worksheet_command( *active_session, "", "", boost::lexical_cast<std::string>( target_wb_id ) ) );
        chain.execute();
    }

    select_worksheet_command( *active_session, "my_worksheet_1 (2)" ).execute();
    {
        command_chain chain;
        chain.add( get_formula_command( *active_session, sheet_point( 0, 0 ) ) );
        chain.add( get_style_command( *active_session, sheet_point( 0, 0 ) ) );
        chain.execute();

        TYPED_CHECK_EQUAL( get_formula_command, chain[0], variant( "=B1:B2" ) );
        variant::sparse_array_type  array;
        array.push_back( variant( "background-color:red;" ) );
        TYPED_CHECK_EQUAL( get_style_command, chain[1], variant( array ) );
    }
}

BOOST_AUTO_TEST_SUITE_END()
