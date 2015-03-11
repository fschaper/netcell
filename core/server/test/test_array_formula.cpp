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

#include "utils.hpp"

#include <wss/session_handler.hpp>
#include <wss/session.hpp>
#include <wss/command.hpp>
#include <wss/server.hpp>
#include <wss/type.hpp>
#include <wss/execute_fetch.hpp>
#include <wss/get_attribute_command.hpp>

struct array_formula_fixture {
    array_formula_fixture() {
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

    ~array_formula_fixture() {
        try {
            server::instance().shutdown();
        } catch ( const std::exception& ) {
            assert( !"this may never throw" );
        }
    }

    locked_session active_session;
};

BOOST_FIXTURE_TEST_SUITE( array_formula_test, array_formula_fixture );

/*!
 * \brief
 * test array formula creation.
 *
 * \author
 * Radu Racariu <radu@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( initialize_1d_array_formula )
{
    // formula setup test
    {
        command_chain chain;
        chain.add( set_array_value_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 1, 1 ) ) , "={1,2;3,4}" ) );
        chain.add( get_value_command( *active_session, sheet_point( 0, 0 ) ) );
        chain.add( get_value_command( *active_session, sheet_point( 0, 0 ) ) );
        chain.add( get_value_command( *active_session, sheet_point( 0, 1 ) ) );
        chain.add( get_value_command( *active_session, sheet_point( 1, 0 ) ) );
        chain.add( get_value_command( *active_session, sheet_point( 1, 1 ) ) );
        chain.execute();

        TEST_GET_VALUE( chain[2], variant( 1.0 ) );
        TEST_GET_VALUE( chain[3], variant( 2.0 ) );
        TEST_GET_VALUE( chain[4], variant( 3.0 ) );
        TEST_GET_VALUE( chain[5], variant( 4.0 ) );
    }
}

/*!
* \brief
* test array formula creation with invalid formula.
*
* \author
* Radu Racariu <radu@yalos-solutions.com>
*/
BOOST_AUTO_TEST_CASE( initialize_1d_array_invalid_formula )
{
    // formula setup test
    {
        BOOST_CHECK_THROW( execute_fetch( set_array_value_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 1, 1 ) ) , "={1" ) ), std::runtime_error );
    }
}
/*!
* \brief
* test array formula copy master cell.
*
* \author
* Radu Racariu <radu@yalos-solutions.com>
*/
BOOST_AUTO_TEST_CASE( array_formula_copy_paste_1_master_cell )
{
    // formula setup test
    {
        clipboard::clipboard_id_type id;
        command_chain chain;
        chain.add( set_array_value_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 1, 1 ) ) , "={1,2;3,4}" ) );
        chain.add( get_value_command( *active_session, sheet_point( 0, 0 ) ) );
        chain.execute();
        id = execute_fetch( copy_range_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 0, 0 ) ) ) );
        execute_fetch( paste_range_command( *active_session, sheet_range( sheet_point( 2, 0 ), sheet_point( 2, 0 ) ), id ) );
        variant v = execute_fetch( get_value_command( *active_session, sheet_point( 2, 0 ) ) );


        TEST_GET_VALUE( chain[1], variant( 1.0 ) );
        BOOST_CHECK_EQUAL( v, variant( 1.0 ) );
    }
}
/*!
* \brief
* test array formula copy slave cell.
*
* \author
* Radu Racariu <radu@yalos-solutions.com>
*/
BOOST_AUTO_TEST_CASE( array_formula_copy_paste_1_slave_cell )
{
    // formula setup test
    {
        clipboard::clipboard_id_type id;
        command_chain chain;
        chain.add( set_array_value_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 1, 1 ) ) , "={1,2;3,4}" ) );
        chain.add( get_value_command( *active_session, sheet_point( 0, 0 ) ) );
        chain.execute();
        id = execute_fetch( copy_range_command( *active_session, sheet_range( sheet_point( 0, 1 ), sheet_point( 0, 1 ) ) ) );
        execute_fetch( paste_range_command( *active_session, sheet_range( sheet_point( 2, 0 ), sheet_point( 2, 0 ) ), id ) );
        variant v = execute_fetch( get_value_command( *active_session, sheet_point( 2, 0 ) ) );


        TEST_GET_VALUE( chain[1], variant( 1.0 ) );
        BOOST_CHECK_EQUAL( v, variant( 1.0 ) );
    }
}
/*!
* \brief
* test array formula copy cell range.
*
* \author
* Radu Racariu <radu@yalos-solutions.com>
*/
BOOST_AUTO_TEST_CASE( array_formula_copy_paste_cell_range )
{
    // formula setup test
    {
        clipboard::clipboard_id_type id;
        command_chain chain;
        chain.add( set_array_value_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 1, 1 ) ) , "={1,2;3,4}" ) );
        chain.add( get_value_command( *active_session, sheet_point( 0, 0 ) ) );
        chain.execute();
        id = execute_fetch( copy_range_command( *active_session, sheet_range( sheet_point( 1, 0 ), sheet_point( 1, 1 ) ) ) );
        execute_fetch( paste_range_command( *active_session, sheet_range( sheet_point( 2, 0 ), sheet_point( 2, 0 ) ), id ) );
        variant v1 = execute_fetch( get_value_command( *active_session, sheet_point( 2, 0 ) ) );
        variant v2 = execute_fetch( get_value_command( *active_session, sheet_point( 2, 1 ) ) );

        TEST_GET_VALUE( chain[1], variant( 1.0 ) );
        BOOST_CHECK_EQUAL( v1, variant( 1.0 ) );
        BOOST_CHECK_EQUAL( v2, variant( 2.0 ) );
    }
}
/*!
* \brief
* test array formula copy cell range to another sheet.
*
* \author
* Radu Racariu <radu@yalos-solutions.com>
*/
BOOST_AUTO_TEST_CASE( array_formula_copy_paste_cell_range_to_sheet )
{
    // formula setup test
    {
        clipboard::clipboard_id_type id;
        command_chain chain;
        chain.add( set_array_value_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 1, 1 ) ) , "={1,2;3,4}" ) );
        chain.add( get_value_command( *active_session, sheet_point( 0, 0 ) ) );
        chain.execute();
        id = execute_fetch( copy_range_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 1, 1 ) ) ) );

        execute_fetch( select_worksheet_command( *active_session, "my_worksheet_2" ) );
        execute_fetch( paste_range_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 1, 1 ) ), id ) );

        variant v1 = execute_fetch( get_value_command( *active_session, sheet_point( 0, 0 ) ) );
        variant v2 = execute_fetch( get_value_command( *active_session, sheet_point( 0, 1 ) ) );
        variant v3 = execute_fetch( get_value_command( *active_session, sheet_point( 1, 0 ) ) );
        variant v4 = execute_fetch( get_value_command( *active_session, sheet_point( 1, 1 ) ) );
        variant attributes = execute_fetch( get_attribute_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 1, 1 ) ) ) );

        TEST_GET_VALUE( chain[1], variant( 1.0 ) );
        BOOST_CHECK_EQUAL( v1, variant( 1.0 ) );
        BOOST_CHECK_EQUAL( v2, variant( 2.0 ) );
        BOOST_CHECK_EQUAL( v3, variant( 3.0 ) );
        BOOST_CHECK_EQUAL( v4, variant( 4.0 ) );
        BOOST_CHECK_EQUAL( attributes.type(), variant::type_array );
    }
}
/*!
* \brief
* test array formula copy_move cell range.
*
* \author
* Radu Racariu <radu@yalos-solutions.com>
*/
BOOST_AUTO_TEST_CASE( array_formula_copy_move_cell_range )
{
    // formula setup test
    {
        clipboard::clipboard_id_type id;
        command_chain chain;
        chain.add( set_array_value_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 1, 1 ) ) , "={1,2;3,4}" ) );
        chain.add( get_value_command( *active_session, sheet_point( 0, 0 ) ) );
        chain.execute();
        id = execute_fetch( copy_move_range_command( *active_session, sheet_range( sheet_point( 1, 0 ), sheet_point( 1, 1 ) ) ) );

        BOOST_CHECK_THROW( execute_fetch( paste_range_command( *active_session, sheet_range( sheet_point( 2, 0 ), sheet_point( 2, 0 ) ), id ) ), std::runtime_error );
        TEST_GET_VALUE( chain[1], variant( 1.0 ) );
    }
}

/*!
* \brief
* test array formula modification of elements.
*
* \author
* Radu Racariu <radu@yalos-solutions.com>
*/
BOOST_AUTO_TEST_CASE( array_formula_override_array_elements )
{
    // formula setup test
    {
        command_chain chain;
        chain.add( set_array_value_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 1, 1 ) ) , "={1,2;3,4}" ) );
        chain.execute();
        // master cell
        BOOST_CHECK_THROW( execute_fetch( set_value_command( *active_session, sheet_point( 0, 0 ) , variant( ( double )0xdeadbeaf ) ) ), std::runtime_error );
        // slave cell
        BOOST_CHECK_THROW( execute_fetch( set_value_command( *active_session, sheet_point( 1, 1 ) , variant( ( double )0xcafebabe ) ) ), std::runtime_error );
    }
}
/*!
* \brief
* test array formula copy cell range inside itself.
*
* \author
* Radu Racariu <radu@yalos-solutions.com>
*/
BOOST_AUTO_TEST_CASE( array_formula_copy_paste_cell_range_itself )
{
    // formula setup test
    {
        clipboard::clipboard_id_type id;
        command_chain chain;
        chain.add( set_array_value_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 1, 1 ) ) , "={1,2;3,4}" ) );
        chain.add( get_value_command( *active_session, sheet_point( 0, 0 ) ) );
        chain.execute();
        id = execute_fetch( copy_range_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 1, 1 ) ) ) );

        // override whole array
        execute_fetch( paste_range_command( *active_session, sheet_range( sheet_point( 0, 0 ), sheet_point( 1, 1 ) ), id ) );

        // override part of array
        BOOST_CHECK_THROW( execute_fetch( paste_range_command( *active_session, sheet_range( sheet_point( 1, 0 ), sheet_point( 1, 1 ) ), id ) ), std::runtime_error );

    }
}


BOOST_AUTO_TEST_SUITE_END()
