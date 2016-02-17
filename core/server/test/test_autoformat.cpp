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
 *  Radu Ialovoi <ialovoi@yahoo.com>
 */
#include "utils.hpp"

#include <boost/test/unit_test.hpp>
#include <boost/assign.hpp>

#include <wss/session_handler.hpp>
#include <wss/session.hpp>
#include <wss/command.hpp>
#include <wss/server.hpp>
#include <wss/formatter.hpp>

struct persistence_fixture {


    boost::uuids::uuid   m_wb_id;

    persistence_fixture() {

        server::instance().startup();

        english_session = server::instance().session_handler().create( locale::create( "en" ) );
        german_session = server::instance().session_handler().create( locale::create( "de" ) );

        fmt_engine = formatter::instance().engine();
    }

    ~persistence_fixture() {
        try {
            server::instance().shutdown();
        } catch ( const std::exception& ) {
            assert( !"this may never throw" );
        }
    }

    locked_session english_session;
    locked_session german_session;
    formatter::shared_format_engine_type    fmt_engine;
};

BOOST_FIXTURE_TEST_SUITE( persistence_test, persistence_fixture );

/*!
 * \brief
 *
 * \author
 * Radu Ialovoi <ialovoi@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( detect_numeric )
{

    variant             value;
    std::string         format;

    BOOST_CHECK_EQUAL( fmt_engine->find_format( *english_session, "(123.0)", value, format ), true );
    BOOST_CHECK_EQUAL( value, variant( -123.0 ) );
    BOOST_CHECK_EQUAL( format, "0.00" );

    BOOST_CHECK_EQUAL( fmt_engine->find_format( *english_session, "123.0", value, format ), true );
    BOOST_CHECK_EQUAL( value, variant( 123.0 ) );
    BOOST_CHECK_EQUAL( format, "0.00" );

    BOOST_CHECK_EQUAL( fmt_engine->find_format( *english_session, "123456.0", value, format ), true );
    BOOST_CHECK_EQUAL( value, variant( 123456.0 ) );
    BOOST_CHECK_EQUAL( format, "0.00" );

    BOOST_CHECK_EQUAL( fmt_engine->find_format( *english_session, "-123,123.", value, format ), true );
    BOOST_CHECK_EQUAL( value, variant( -123123.00 ) );
    BOOST_CHECK_EQUAL( format, "#,##0.00" );

    BOOST_CHECK_EQUAL( fmt_engine->find_format( *german_session, "-123.123,0", value, format ), true );
    BOOST_CHECK_EQUAL( value, variant( -123123.00 ) );
    BOOST_CHECK_EQUAL( format, "#,##0.00" );

    BOOST_CHECK_EQUAL( fmt_engine->find_format( *german_session, "(123.123,0)", value, format ), true );
    BOOST_CHECK_EQUAL( value, variant( -123123.00 ) );
    BOOST_CHECK_EQUAL( format, "#,##0.00" );

}

/*!
 * \brief
 *
 * \author
 * Radu Ialovoi <ialovoi@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( detect_currency )
{

    variant             value;
    std::string         format;


    BOOST_CHECK_EQUAL( fmt_engine->find_format( *english_session, "$123.0", value, format ), true );
    BOOST_CHECK_EQUAL( value, variant( 123.0 ) );
    BOOST_CHECK_EQUAL( format, "[$]#,##0_);[Red]($#,##0)" );

    BOOST_CHECK_EQUAL( fmt_engine->find_format( *english_session, "$123456.0", value, format ), true );
    BOOST_CHECK_EQUAL( value, variant( 123456.0 ) );
    BOOST_CHECK_EQUAL( format, "[$]#,##0_);[Red]($#,##0)" );

    BOOST_CHECK_EQUAL( fmt_engine->find_format( *english_session, "-$123,123.", value, format ), true );
    BOOST_CHECK_EQUAL( value, variant( -123123.00 ) );
    BOOST_CHECK_EQUAL( format, "[$]#,##0_);[Red]($#,##0)" );

    BOOST_CHECK_EQUAL( fmt_engine->find_format( *english_session, "-$123,123.0", value, format ), true );
    BOOST_CHECK_EQUAL( value, variant( -123123.00 ) );
    BOOST_CHECK_EQUAL( format, "[$]#,##0_);[Red]($#,##0)" );

    BOOST_CHECK_EQUAL( fmt_engine->find_format( *english_session, "($123,123.0)", value, format ), true );
    BOOST_CHECK_EQUAL( value, variant( -123123.00 ) );
    BOOST_CHECK_EQUAL( format, "[$]#,##0_);[Red]($#,##0)" );

    std::string euro;
    unsigned char crt = 0xe2;
    euro.push_back( crt );
    crt = 0x82;
    euro.push_back( crt );
    crt = 0xac;
    euro.push_back( crt );

    BOOST_CHECK_EQUAL( fmt_engine->find_format( *german_session, euro + "123,345", value, format ), true );
    BOOST_CHECK_EQUAL( value, variant( 123.345 ) );
    BOOST_CHECK_EQUAL( format, "[$]#,##0_);[Red]($#,##0)" );

}

/*!
 * \brief
 *
 * \author
 * Radu Ialovoi <ialovoi@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( detect_date )
{

    variant             value;
    std::string         format;

    BOOST_CHECK_EQUAL( fmt_engine->find_format( *english_session, "12/15", value, format ), true );
    BOOST_CHECK_EQUAL( value, variant( 40527.0 ) );
    BOOST_CHECK_EQUAL( format, "d-mmm" );

    BOOST_CHECK_EQUAL( fmt_engine->find_format( *english_session, "12-15", value, format ), true );
    BOOST_CHECK_EQUAL( value, variant( 40527.0 ) );
    BOOST_CHECK_EQUAL( format, "d-mmm" );

    BOOST_CHECK_EQUAL( fmt_engine->find_format( *english_session, "15-12", value, format ), false );
    BOOST_CHECK_EQUAL( fmt_engine->find_format( *english_session, "2-29", value, format ), false );

    BOOST_CHECK_EQUAL( fmt_engine->find_format( *english_session, "Dec-15", value, format ), true );
    BOOST_CHECK_EQUAL( value, variant( 40527.0 ) );
    BOOST_CHECK_EQUAL( format, "d-mmm" );

    BOOST_CHECK_EQUAL( fmt_engine->find_format( *english_session, "DeCeMbEr-15", value, format ), true );
    BOOST_CHECK_EQUAL( value, variant( 40527.0 ) );
    BOOST_CHECK_EQUAL( format, "d-mmm" );

    BOOST_CHECK_EQUAL( fmt_engine->find_format( *english_session, "12/15/10", value, format ), true );
    BOOST_CHECK_EQUAL( value, variant( 40527.0 ) );
    BOOST_CHECK_EQUAL( format, "m/d/yyyy" );

    BOOST_CHECK_EQUAL( fmt_engine->find_format( *english_session, "12-15-10", value, format ), true );
    BOOST_CHECK_EQUAL( value, variant( 40527.0 ) );
    BOOST_CHECK_EQUAL( format, "m/d/yyyy" );

    BOOST_CHECK_EQUAL( fmt_engine->find_format( *english_session, "15-12-10", value, format ), false );
    BOOST_CHECK_EQUAL( fmt_engine->find_format( *english_session, "2-29-10", value, format ), false );

    BOOST_CHECK_EQUAL( fmt_engine->find_format( *english_session, "Dec-15-10", value, format ), true );
    BOOST_CHECK_EQUAL( value, variant( 40527.0 ) );
    BOOST_CHECK_EQUAL( format, "m/d/yyyy" );

    BOOST_CHECK_EQUAL( fmt_engine->find_format( *english_session, "DeCeMbEr-15-10", value, format ), true );
    BOOST_CHECK_EQUAL( value, variant( 40527.0 ) );
    BOOST_CHECK_EQUAL( format, "m/d/yyyy" );

    BOOST_CHECK_EQUAL( fmt_engine->find_format( *english_session, "DeCeMbEr-15-2010", value, format ), true );
    BOOST_CHECK_EQUAL( value, variant( 40527.0 ) );
    BOOST_CHECK_EQUAL( format, "m/d/yyyy" );

    BOOST_CHECK_EQUAL( fmt_engine->find_format( *english_session, "DeCeMbEr-15-101", value, format ), false );

}

/*!
 * \brief
 *
 * \author
 * Radu Ialovoi <ialovoi@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( detect_time )
{

    variant             value;
    std::string         format;

    BOOST_CHECK_EQUAL( fmt_engine->find_format( *english_session, "12:15", value, format ), true );
    BOOST_CHECK_CLOSE( value.as_double(), 0.5104166666666667, 0.1 );
    BOOST_CHECK_EQUAL( format, "h:mm" );

    BOOST_CHECK_EQUAL( fmt_engine->find_format( *english_session, "12:15 PM", value, format ), true );
    BOOST_CHECK_CLOSE( value.as_double(), 0.5104166666666667, 0.1 );
    BOOST_CHECK_EQUAL( format, "h:mm AM/PM" );

    BOOST_CHECK_EQUAL( fmt_engine->find_format( *english_session, "13:15 PM", value, format ), false );
    BOOST_CHECK_EQUAL( fmt_engine->find_format( *english_session, "13:15 AM", value, format ), false );

    BOOST_CHECK_EQUAL( fmt_engine->find_format( *english_session, "23:15", value, format ), true );
    BOOST_CHECK_CLOSE( value.as_double(), 0.96875, 0.1 );
    BOOST_CHECK_EQUAL( format, "h:mm" );

}

/*!
 * \brief
 *
 * \author
 * Radu Ialovoi <ialovoi@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( detect_date_time )
{

    variant             value;
    std::string         format;

    BOOST_CHECK_EQUAL( fmt_engine->find_format( *english_session, "12:15 12/15", value, format ), true );
    BOOST_CHECK_CLOSE( value.as_double(), 40527.510416, 0.1 );
    BOOST_CHECK_EQUAL( format, "m/d/yyyy h:mm" );

    BOOST_CHECK_EQUAL( fmt_engine->find_format( *english_session, "12:15 12/15/10", value, format ), true );
    BOOST_CHECK_CLOSE( value.as_double(), 40527.510416, 0.1 );
    BOOST_CHECK_EQUAL( format, "m/d/yyyy h:mm" );

    BOOST_CHECK_EQUAL( fmt_engine->find_format( *english_session, "12:15 12/15/2010", value, format ), true );
    BOOST_CHECK_CLOSE( value.as_double(), 40527.510416, 0.1 );
    BOOST_CHECK_EQUAL( format, "m/d/yyyy h:mm" );

    BOOST_CHECK_EQUAL( fmt_engine->find_format( *english_session, "12:15 AM 12/15", value, format ), true );
    BOOST_CHECK_CLOSE( value.as_double(), 40527.510416, 0.1 );
    BOOST_CHECK_EQUAL( format, "m/d/yyyy h:mm" );

    BOOST_CHECK_EQUAL( fmt_engine->find_format( *english_session, "12:15 AM Dec/15", value, format ), true );
    BOOST_CHECK_CLOSE( value.as_double(), 40527.510416, 0.1 );
    BOOST_CHECK_EQUAL( format, "m/d/yyyy h:mm" );

    BOOST_CHECK_EQUAL( fmt_engine->find_format( *english_session, "12:15 AM DecemBER/15", value, format ), true );
    BOOST_CHECK_CLOSE( value.as_double(), 40527.510416, 0.1 );
    BOOST_CHECK_EQUAL( format, "m/d/yyyy h:mm" );

}

/*!
 * \brief
 *
 * \author
 * Radu Ialovoi <ialovoi@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( detect_bool )
{

    variant             value;
    std::string         format;

    BOOST_CHECK_EQUAL( fmt_engine->find_format( *english_session, "True", value, format ), true );
    BOOST_CHECK_EQUAL( value.as_boolean( english_session->locale() ), true );
    BOOST_CHECK_EQUAL( format, "" );

    BOOST_CHECK_EQUAL( fmt_engine->find_format( *english_session, "FaLse", value, format ), true );
    BOOST_CHECK_EQUAL( value.as_boolean( english_session->locale() ), false );
    BOOST_CHECK_EQUAL( format, "" );

}

/*!
 * \brief
 *
 * \author
 * Radu Ialovoi <ialovoi@yalos-solutions.com>
 */
BOOST_AUTO_TEST_CASE( detect_string )
{

    variant             value;
    std::string         format;

    BOOST_CHECK_EQUAL( fmt_engine->find_format( *english_session, "True1", value, format ), false );
}

BOOST_AUTO_TEST_SUITE_END()
