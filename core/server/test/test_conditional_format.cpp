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
#include <boost/enable_shared_from_this.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/assign.hpp>
#include <map>
#include <set>

#include <wss/point.hpp>
#include <wss/rectangle.hpp>
#include <wss/variant.hpp>
#include <wss/definition.hpp>
#include <wss/application.hpp>
#include <wss/i_dependency.hpp>
#include <wss/sheet_point.hpp>
#include <wss/cyclic_point.hpp>
#include <wss/type.hpp>
#include <wss/locale.hpp>
#include <wss/command.hpp>
#include <wss/exception.hpp>
#include <wss/worksheet_element_storage.hpp>
#include <wss/a1conversion.hpp>
#include <wss/session_handler.hpp>
#include <wss/session.hpp>
#include <wss/set_conditional_format.hpp>
#include <wss/style_set.hpp>
#include <wss/translation_map.hpp>
#include <wss/translation_table.hpp>
#include <wss/server.hpp>
#include <wss/command.hpp>
#include <wss/command_chain.hpp>
#include <wss/object_container.hpp>
#include "wss/execute_fetch.hpp"

//#define REENABLE_PASSED_TESTS 1
// #define FUNCTION_IF_WORKS_AGAIN
// #define TICKET_3636_DONE 1
#define TICKET_3637_DONE 1
#define TICKET_3639_DONE 1
// #define TICKET_3647_DONE 1

using namespace boost::assign;

struct conditional_format_fixture {
    conditional_format_fixture()  : a1( 0, 0 ),
        a2( 1, 0 ),
        a3( 2, 0 ),
        a4( 3, 0 ) {
        server::instance().startup();
        s = server::instance().session_handler().create( locale::create( "en-US" ) );


        create_application_command( *s, "my application" ).execute();
        select_application_command( *s, "my application" ).execute();
        create_workbook_command( *s, "wb1" ).execute();
        select_workbook_command( *s, "wb1" ).execute();
        create_worksheet_command( *s, "my_worksheet_2" ).execute();
        select_worksheet_command( *s, "my_worksheet_2" ).execute();
        ws2 = s->selected().worksheet().lock();
        create_worksheet_command( *s, "ws1" ).execute();
        select_worksheet_command( *s, "ws1" ).execute();

        ws1 = s->selected().worksheet().lock();
        wb1 = s->selected().workbook().lock();
        maximum_iterations = s->selected().application()->calculation_settings().maximum_iterations();
    }

    ~conditional_format_fixture() {
        try {
            ws1.reset();
            server::instance().shutdown();
        } catch ( const std::exception& /*e*/ ) {
            assert( !"this may never throw" );
        }
    }
    shared_worksheet_type ws2;
    locked_session s;
    shared_worksheet_type ws1;
    shared_workbook_type wb1;
    sheet_point a1;
    sheet_point a2;
    sheet_point a3;
    sheet_point a4;
    double maximum_iterations;
};

BOOST_FIXTURE_TEST_SUITE( test_conditional_format, conditional_format_fixture )

/*!
 * \brief
 * test case for ticket:
 * 7928: Reference in CF formula not correctly updated after inserting row
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
BOOST_AUTO_TEST_CASE( cf_move_test )
{
    sheet_point b1 = sheet_point( 0, 1 );
    sheet_point b2 = sheet_point( 1, 1 );
    sheet_point b3 = sheet_point( 2, 1 );
    sheet_point b4 = sheet_point( 3, 1 );
    sheet_point c3 = sheet_point( 2, 2 );
    sheet_point c4 = sheet_point( 3, 2 );
    set_conditional_format::selected_ranges_type ranges;
    ranges.push_back( c3 );
    set_conditional_format set_cf_format( variant( "=$b3=$c3" ), "FORMULA_TRUE(;1;)"
                                          , "fg:green;"
                                          , ranges, set_conditional_format::border_map_type() );

    set_conditional_format_command( *s, set_cf_format ).execute();

    {
        variant::variant_array_type result_if_match;
        result_if_match.push_back( variant( "fg:green;" ) );
        variant res = execute_fetch( get_style_command( *s, c3 ) );
        BOOST_CHECK_EQUAL( res, result_if_match );
    }

    set_value_command( *s, b3 , 1.0 ).execute();
    {
        variant::variant_array_type result_if_no_match;
        result_if_no_match.push_back( variant() );
        variant res = execute_fetch( get_style_command( *s, c3 ) );
        BOOST_CHECK_EQUAL( res, result_if_no_match );
    }
    set_value_command( *s, c3 , 1.0 ).execute();
    {
        variant::variant_array_type result_if_match;
        result_if_match.push_back( variant( "fg:green;" ) );
        variant res = execute_fetch( get_style_command( *s, c3 ) );
        BOOST_CHECK_EQUAL( res, result_if_match );
    }

    {
        move_range_command::result_type id = execute_fetch( move_range_command( *s, b3 ) );
        paste_range_command( *s, b4, id ).execute();
        variant::variant_array_type result_if_match;
        result_if_match.push_back( variant( "fg:green;" ) );
        get_conditionalformat_list_type list =  execute_fetch( get_all_conditional_formats_command( *s, s->selected().worksheet().lock() ) );
        std::string operand;
        if ( !list.empty() ) {
            if ( ! list.begin()->operands.empty() ) {
                operand = *list.begin()->operands.begin();
            }
        }
        //TODO set to warning for now (see ticket 8463)
        BOOST_WARN_EQUAL( std::string( "=$B4=$C3" ), operand );
        variant res = execute_fetch( get_style_command( *s, c3 ) );
        //TODO set to warning for now (see ticket 8463)
        BOOST_WARN_EQUAL( res, result_if_match );
    }

    {
        move_range_command::result_type id = execute_fetch( move_range_command( *s, c3 ) );
        paste_range_command( *s, c4, id ).execute();
        variant::variant_array_type result_if_match;
        result_if_match.push_back( variant( "fg:green;" ) );
        get_conditionalformat_list_type list =  execute_fetch( get_all_conditional_formats_command( *s, s->selected().worksheet().lock() ) );
        std::string operand;
        if ( !list.empty() ) {
            if ( ! list.begin()->operands.empty() ) {
                operand = *list.begin()->operands.begin();
            }
        }
        BOOST_CHECK_EQUAL( std::string( "=$B4=$C4" ), operand );
        variant res = execute_fetch( get_style_command( *s, c4 ) );
        BOOST_CHECK_EQUAL( res, result_if_match );
    }
}

BOOST_AUTO_TEST_CASE( cf_move_test2 )
{
    sheet_point b1 = sheet_point( 0, 1 );
    sheet_point b2 = sheet_point( 1, 1 );
    sheet_point b3 = sheet_point( 2, 1 );
    sheet_point b4 = sheet_point( 3, 1 );
    sheet_point c3 = sheet_point( 2, 2 );
    sheet_point c4 = sheet_point( 3, 2 );
    set_conditional_format::selected_ranges_type ranges;
    ranges.push_back( c3 );
    set_conditional_format set_cf_format( variant( "=$b3=c3" ), "FORMULA_TRUE(;1;)"
                                          , "fg:green;"
                                          , ranges, set_conditional_format::border_map_type() );

    set_conditional_format_command( *s, set_cf_format ).execute();

    {
        variant::variant_array_type result_if_match;
        result_if_match.push_back( variant( "fg:green;" ) );
        variant res = execute_fetch( get_style_command( *s, c3 ) );
        BOOST_CHECK_EQUAL( res, result_if_match );
    }

    set_value_command( *s, b3 , 1.0 ).execute();
    {
        variant::variant_array_type result_if_no_match;
        result_if_no_match.push_back( variant() );
        variant res = execute_fetch( get_style_command( *s, c3 ) );
        BOOST_CHECK_EQUAL( res, result_if_no_match );
    }
    set_value_command( *s, c3 , 1.0 ).execute();
    {
        variant::variant_array_type result_if_match;
        result_if_match.push_back( variant( "fg:green;" ) );
        variant res = execute_fetch( get_style_command( *s, c3 ) );
        BOOST_CHECK_EQUAL( res, result_if_match );
    }

    {
        move_range_command::result_type id = execute_fetch( move_range_command( *s, sheet_range( b3, c3 ) ) );
        paste_range_command( *s, sheet_range( b4, c4 ), id ).execute();
        variant::variant_array_type result_if_match;
        result_if_match.push_back( variant( "fg:green;" ) );
        get_conditionalformat_list_type list =  execute_fetch( get_all_conditional_formats_command( *s, s->selected().worksheet().lock() ) );
        std::string operand;
        if ( !list.empty() ) {
            if ( ! list.begin()->operands.empty() ) {
                operand = *list.begin()->operands.begin();
            }
        }
        BOOST_CHECK_EQUAL( std::string( "=$B4=C4" ), operand );
        variant res = execute_fetch( get_style_command( *s, c4 ) );
        BOOST_CHECK_EQUAL( res, result_if_match );
    }
}

#if 0 //old stuff from here on


inline set_conditional_format set_cf_format( const variant& operands, const std::string& rule, const std::string& style, const set_conditional_format::selected_ranges_type& selected_range )
{
    return set_conditional_format( operands, rule, style, selected_range, false, set_conditional_format::border_map_type() );
}

BOOST_AUTO_TEST_CASE( test_value_rule_one_cell_equal )
{
    {
        const sheet_range& range_to_use = one_point_range[0];

        command_chain chain;
        chain.add( set_conditional_format_command( *s
                                                   , set_cf_format(
                                                       variant( "=B1" )
                                                       , "CELL_VALUE(=;1;)"
                                                       , style_str
                                                       , one_point_range ) ) );

        chain.add( set_value_command( *s, A1, variant( 5.0 ) ) );
        chain.add( set_value_command( *s, B1, variant( 5.0 ) ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, A1, variant( 4.0 ) ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, B1, variant( 4.0 ) ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, A1, variant( 3.0 ) ) );
        chain.add( get_style_command( *s, range_to_use ) );

        BOOST_CHECK_NO_THROW( chain.execute() );
        {
            variant::variant_array_type expected_value( one_point_range[0].count(), style_str );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[3] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( one_point_range[0].count(), "" );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[5] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( one_point_range[0].count(), style_str );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[7] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( one_point_range[0].count(), "" );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[9] ).value(), variant( expected_value ) );
        }
    }

    {
        const sheet_range& range_to_use = real_range[0];

        command_chain chain;
        set_conditional_format_command( *s
                                        , set_cf_format(
                                            variant( "=b1" )
                                            , "CELL_VALUE(=;1;)"
                                            , style_str
                                            , real_range ) ).execute();

        set_value_command( *s, A1, variant( 5.0 ) ).execute();
        set_value_command( *s, B1, variant( 5.0 ) ).execute();


        BOOST_CHECK_NO_THROW( chain.execute() );
        {
            variant actual_value = execute_fetch( get_style_command( *s, range_to_use ) );
            variant::variant_array_type expected_value;
            expected_value.push_back( style_str );
            expected_value.push_back( "" );
            expected_value.push_back( style_str );
            expected_value.push_back( style_str );
            BOOST_CHECK_EQUAL( actual_value, variant( expected_value ) );
        }
        set_value_command( *s, C1, variant( 4.0 ) ).execute();
        {
            variant actual_value = execute_fetch( get_style_command( *s, range_to_use ) );
            variant::variant_array_type expected_value;
            expected_value.push_back( style_str );
            expected_value.push_back( "" );
            expected_value.push_back( style_str );
            expected_value.push_back( style_str );
            BOOST_CHECK_EQUAL( actual_value, variant( expected_value ) );
        }
        set_value_command( *s, B1, variant( 4.0 ) ).execute();
        {
            variant actual_value = execute_fetch( get_style_command( *s, range_to_use ) );
            variant::variant_array_type expected_value;
            expected_value.push_back( "" );
            expected_value.push_back( style_str );
            expected_value.push_back( style_str );
            expected_value.push_back( style_str );
            BOOST_CHECK_EQUAL( actual_value, variant( expected_value ) );
        }
        set_value_command( *s, A1, variant( 3.0 ) ).execute();
        {
            variant actual_value = execute_fetch( get_style_command( *s, range_to_use ) );
            variant::variant_array_type expected_value;
            expected_value.push_back( "" );
            expected_value.push_back( style_str );
            expected_value.push_back( style_str );
            expected_value.push_back( style_str );
            BOOST_CHECK_EQUAL( actual_value, variant( expected_value ) );
        }
    }
}



BOOST_AUTO_TEST_CASE( test_value_rule_one_cell_greater )
{
    const std::string rule_type = "CELL_VALUE";
    const std::string op = ">";
    {
        const sheet_range& range_to_use = one_point_range[0];

        command_chain chain;
        chain.add( set_conditional_format_command( *s
                                                   , set_cf_format(
                                                       variant( "=B1" )
                                                       , rule_type + "(" + op + ";1;)"
                                                       , style_str
                                                       , one_point_range ) ) );

        chain.add( set_value_command( *s, A1, variant( 5.0 ) ) );
        chain.add( set_value_command( *s, B1, variant( 4.0 ) ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, A1, variant( 4.0 ) ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, B1, variant( 3.0 ) ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, B1, variant( 6.0 ) ) );
        chain.add( get_style_command( *s, range_to_use ) );

        BOOST_CHECK_NO_THROW( chain.execute() );
        {
            variant::variant_array_type expected_value( one_point_range[0].count(), style_str );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[3] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( one_point_range[0].count(), "" );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[5] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( one_point_range[0].count(), style_str );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[7] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( one_point_range[0].count(), "" );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[9] ).value(), variant( expected_value ) );
        }
    }

    clear_cells_command( *s, sheet_range( sheet_point( 0, 0 ), sheet_point( 20, 20 ) ), content_type::all_plus_cf ).execute();

    {
        const sheet_range& range_to_use = real_range[0];

        set_conditional_format_command( *s
                                        , set_cf_format(
                                            variant( "=B1" )
                                            , rule_type + "(" + op + ";1;)"
                                            , style_str
                                            , real_range ) ).execute();

        set_value_command( *s, A1, variant( 5.0 ) ).execute();
        set_value_command( *s, B1, variant( 4.0 ) ).execute();

        {
            variant::variant_array_type expected_value( 2, style_str );
            expected_value.push_back( "" );
            expected_value.push_back( "" );
            BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, range_to_use ) ), variant( expected_value ) );
        }
        set_value_command( *s, A1, variant( 4.0 ) ).execute( );
        {
            variant::variant_array_type expected_value( range_to_use.count(), "" );
            expected_value[1] = style_str;
            BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, range_to_use ) ), variant( expected_value ) );
        }
        set_value_command( *s, B1, variant( 3.0 ) ).execute();
        {
            variant::variant_array_type expected_value( 2, style_str );
            expected_value.push_back( "" );
            expected_value.push_back( "" );
            BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, range_to_use ) ), variant( expected_value ) );
        }
        set_value_command( *s, B1, variant( 6.0 ) ).execute();
        {
            variant::variant_array_type expected_value( range_to_use.count(), "" );
            expected_value[1] = style_str;
            BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, range_to_use ) ), variant( expected_value ) );
        }
    }
}

BOOST_AUTO_TEST_CASE( test_value_rule_one_cell_less )
{
    const std::string rule_type = "CELL_VALUE";
    const std::string op = "<";
    {
        const sheet_range& range_to_use = one_point_range[0];

        command_chain chain;
        chain.add( set_conditional_format_command( *s
                                                   , set_cf_format(
                                                       variant( "=B1" )
                                                       , rule_type + "(" + op + ";1;)"
                                                       , style_str
                                                       , one_point_range ) ) );

        chain.add( set_value_command( *s, A1, variant( 5.0 ) ) );
        chain.add( set_value_command( *s, B1, variant( 6.0 ) ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, A1, variant( 7.0 ) ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, B1, variant( 8.0 ) ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, B1, variant( 1.0 ) ) );
        chain.add( get_style_command( *s, range_to_use ) );

        BOOST_CHECK_NO_THROW( chain.execute() );
        {
            variant::variant_array_type expected_value( one_point_range[0].count(), style_str );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[3] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( one_point_range[0].count(), "" );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[5] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( one_point_range[0].count(), style_str );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[7] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( one_point_range[0].count(), "" );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[9] ).value(), variant( expected_value ) );
        }
    }

    {
        const sheet_range& range_to_use = real_range[0];

        clear_cells_command( *s, sheet_range( sheet_point( 0, 0 ), sheet_point( 20, 20 ) ), content_type::all_plus_cf ).execute();

        command_chain chain;
        chain.add( set_conditional_format_command( *s
                                                   , set_cf_format(
                                                       variant( "=B1" )
                                                       , rule_type + "(" + op + ";1;)"
                                                       , style_str
                                                       , real_range ) ) );

        chain.add( set_value_command( *s, A1, variant( 5.0 ) ) );
        chain.add( set_value_command( *s, B1, variant( 6.0 ) ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, A1, variant( 7.0 ) ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, B1, variant( 8.0 ) ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, B1, variant( 1.0 ) ) );
        chain.add( get_style_command( *s, range_to_use ) );

        BOOST_CHECK_NO_THROW( chain.execute() );
        {
            variant::variant_array_type expected_value;
            expected_value.push_back( style_str );
            expected_value.push_back( variant( "" ) );
            expected_value.push_back( "" );
            expected_value.push_back( "" );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[3] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( range_to_use.count(), "" );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[5] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value;
            expected_value.push_back( style_str );
            expected_value.push_back( variant( "" ) );
            expected_value.push_back( "" );
            expected_value.push_back( "" );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[7] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( range_to_use.count(), "" );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[9] ).value(), variant( expected_value ) );
        }
    }
}

BOOST_AUTO_TEST_CASE( test_value_rule_one_cell_greater_equal )
{
    const std::string rule_type = "CELL_VALUE";
    const std::string op = ">=";
    {
        const sheet_range& range_to_use = one_point_range[0];

        command_chain chain;
        chain.add( set_conditional_format_command( *s
                                                   , set_cf_format(
                                                       variant( "=B1" )
                                                       , rule_type + "(" + op + ";1;)"
                                                       , style_str
                                                       , one_point_range ) ) );

        chain.add( set_value_command( *s, A1, variant( 5.0 ) ) );
        chain.add( set_value_command( *s, B1, variant( 5.0 ) ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, A1, variant( 4.0 ) ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, B1, variant( 1.0 ) ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, B1, variant( "42" ) ) );
        chain.add( get_style_command( *s, range_to_use ) );

        BOOST_CHECK_NO_THROW( chain.execute() );
        {
            variant::variant_array_type expected_value( one_point_range[0].count(), style_str );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[3] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( one_point_range[0].count(), "" );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[5] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( one_point_range[0].count(), style_str );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[7] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( one_point_range[0].count(), "" );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[9] ).value(), variant( expected_value ) );
        }
    }

    {
        const sheet_range& range_to_use = real_range[0];

        clear_cells_command( *s, sheet_range( sheet_point( 0, 0 ), sheet_point( 20, 20 ) ), content_type::all_plus_cf ).execute();

        command_chain chain;
        chain.add( set_conditional_format_command( *s
                                                   , set_cf_format(
                                                       variant( "=B1" )
                                                       , rule_type + "(" + op + ";1;)"
                                                       , style_str
                                                       , real_range ) ) );

        chain.add( set_value_command( *s, A1, variant( 5.0 ) ) );
        chain.add( set_value_command( *s, B1, variant( 5.0 ) ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, A1, variant( 4.0 ) ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, B1, variant( 1.0 ) ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, B1, variant( "42" ) ) );
        chain.add( get_style_command( *s, range_to_use ) );

        BOOST_CHECK_NO_THROW( chain.execute() );
        {
            variant::variant_array_type expected_value( range_to_use.count(), style_str );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[3] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value;
            expected_value.push_back( variant( "" ) );
            expected_value.push_back( style_str );
            expected_value.push_back( style_str );
            expected_value.push_back( style_str );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[5] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( range_to_use.count(), style_str );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[7] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value;
            expected_value.push_back( variant( "" ) );
            expected_value.push_back( style_str );
            expected_value.push_back( style_str );
            expected_value.push_back( style_str );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[9] ).value(), variant( expected_value ) );
        }
    }
}

BOOST_AUTO_TEST_CASE( test_value_rule_one_cell_less_equal )
{
    const std::string rule_type = "CELL_VALUE";
    const std::string op = "<=";
    {
        const sheet_range& range_to_use = one_point_range[0];

        command_chain chain;
        chain.add( set_conditional_format_command( *s
                                                   , set_cf_format(
                                                       variant( "=B1" )
                                                       , rule_type + "(" + op + ";1;)"
                                                       , style_str
                                                       , one_point_range ) ) );

        chain.add( set_value_command( *s, A1, variant( 5.0 ) ) );
        chain.add( set_value_command( *s, B1, variant( 5.0 ) ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, A1, variant( 6.0 ) ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, B1, variant( "42" ) ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, B1, variant( -1.0 ) ) );
        chain.add( get_style_command( *s, range_to_use ) );

        BOOST_CHECK_NO_THROW( chain.execute() );
        {
            variant::variant_array_type expected_value( one_point_range[0].count(), style_str );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[3] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( one_point_range[0].count(), "" );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[5] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( one_point_range[0].count(), style_str );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[7] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( one_point_range[0].count(), "" );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[9] ).value(), variant( expected_value ) );
        }
    }

    {
        const sheet_range& range_to_use = real_range[0];

        clear_cells_command( *s, sheet_range( sheet_point( 0, 0 ), sheet_point( 20, 20 ) ), content_type::all_plus_cf ).execute();

        command_chain chain;
        chain.add( set_conditional_format_command( *s
                                                   , set_cf_format(
                                                       variant( "=B1" )
                                                       , rule_type + "(" + op + ";1;)"
                                                       , style_str
                                                       , real_range ) ) );

        chain.add( set_value_command( *s, A1, variant( 5.0 ) ) );
        chain.add( set_value_command( *s, B1, variant( 5.0 ) ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, A1, variant( 6.0 ) ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, B1, variant( "42" ) ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, B1, variant( -1.0 ) ) );
        chain.add( get_style_command( *s, range_to_use ) );

        BOOST_CHECK_NO_THROW( chain.execute() );
        {
            variant::variant_array_type expected_value;
            expected_value.push_back( style_str );
            expected_value.push_back( variant( "" ) );
            expected_value.push_back( style_str );
            expected_value.push_back( style_str );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[3] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value;
            expected_value.push_back( variant( "" ) );
            expected_value.push_back( variant( "" ) );
            expected_value.push_back( style_str );
            expected_value.push_back( style_str );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[5] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value;
            expected_value.push_back( style_str );
            expected_value.push_back( variant( "" ) );
            expected_value.push_back( style_str );
            expected_value.push_back( style_str );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[7] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value;
            expected_value.push_back( variant( "" ) );
            expected_value.push_back( style_str );
            expected_value.push_back( style_str );
            expected_value.push_back( style_str );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[9] ).value(), variant( expected_value ) );
        }
    }
}

BOOST_AUTO_TEST_CASE( test_value_rule_one_cell_not_equal )
{
    const std::string rule_type = "CELL_VALUE";
    const std::string op = "<>";
    {
        const sheet_range& range_to_use = one_point_range[0];

        command_chain chain;
        chain.add( set_conditional_format_command( *s
                                                   , set_cf_format(
                                                       variant( "=B1" )
                                                       , rule_type + "(" + op + ";1;)"
                                                       , style_str
                                                       , one_point_range ) ) );

        chain.add( set_value_command( *s, A1, variant() ) );
        chain.add( set_value_command( *s, B1, variant( 5.0 ) ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, A1, variant( 5.0 ) ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, B1, variant( "42" ) ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, A1, variant( "42" ) ) );
        chain.add( get_style_command( *s, range_to_use ) );

        BOOST_CHECK_NO_THROW( chain.execute() );
        {
            variant::variant_array_type expected_value( one_point_range[0].count(), style_str );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[3] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( one_point_range[0].count(), "" );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[5] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( one_point_range[0].count(), style_str );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[7] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( one_point_range[0].count(), "" );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[9] ).value(), variant( expected_value ) );
        }
    }

    {
        const sheet_range& range_to_use = real_range[0];

        clear_cells_command( *s, sheet_range( sheet_point( 0, 0 ), sheet_point( 20, 20 ) ), content_type::all_plus_cf ).execute();

        command_chain chain;
        chain.add( set_conditional_format_command( *s
                                                   , set_cf_format(
                                                       variant( "=B1" )
                                                       , rule_type + "(" + op + ";1;)"
                                                       , style_str
                                                       , real_range ) ) );

        chain.add( set_value_command( *s, A1, variant() ) );
        chain.add( set_value_command( *s, B1, variant( 5.0 ) ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, A1, variant( 5.0 ) ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, B1, variant( "42" ) ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, A1, variant( "42" ) ) );
        chain.add( get_style_command( *s, range_to_use ) );
        BOOST_CHECK_NO_THROW( chain.execute() );
        {
            variant::variant_array_type expected_value( range_to_use.count(), "" );
            expected_value[0] = style_str;
            expected_value[1] = style_str;
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[3] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( range_to_use.count(), "" );
            expected_value[1] = style_str;
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[5] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( range_to_use.count(), "" );
            expected_value[0] = style_str;
            expected_value[1] = style_str;
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[7] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( range_to_use.count(), "" );
            expected_value[1] = style_str;
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[9] ).value(), variant( expected_value ) );
        }
    }
}

BOOST_AUTO_TEST_CASE( test_value_rule_one_cell_between )
{
    const std::string rule_type = "CELL_VALUE";
    const std::string op = "between";
    {
        const sheet_range& range_to_use = one_point_range[0];

        variant::variant_array_type operands;
        operands.push_back( variant( "=B1" ) );
        operands.push_back( variant( "=C1" ) );
        command_chain chain;
        chain.add( set_conditional_format_command( *s
                                                   , set_cf_format(
                                                       variant( operands )
                                                       , rule_type + "(" + op + ";1;)"
                                                       , style_str
                                                       , one_point_range ) ) );

        chain.add( set_value_command( *s, A1, variant() ) );
        chain.add( set_value_command( *s, B1, variant( 5.0 ) ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, A1, variant( 5.0 ) ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, B1, variant( "=\"42\"" ) ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, A1, variant( -1.0 ) ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, C1, variant( -1.0 ) ) );
        chain.add( get_style_command( *s, range_to_use ) );

        BOOST_CHECK_NO_THROW( chain.execute() );
        {
            variant::variant_array_type expected_value( range_to_use.count(), style_str );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[3] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( range_to_use.count(), style_str );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[5] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( range_to_use.count(), style_str );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[7] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( range_to_use.count(), "" );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[9] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( range_to_use.count(), style_str );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[7] ).value(), variant( expected_value ) );
        }
    }

    clear_cells_command( *s, sheet_range( sheet_point( 0, 0 ), sheet_point( 20, 20 ) ), content_type::all_plus_cf ).execute();

    {
        const sheet_range& range_to_use = real_range[0];

        variant::variant_array_type operands;
        operands.push_back( variant( "=B1" ) );
        operands.push_back( variant( "=C1" ) );
        command_chain chain;
        chain.add( set_conditional_format_command( *s
                                                   , set_cf_format(
                                                       variant( operands )
                                                       , rule_type + "(" + op + ";1;)"
                                                       , style_str
                                                       , real_range ) ) );

        chain.add( set_value_command( *s, A1, variant() ) );
        chain.add( set_value_command( *s, B1, variant( 5.0 ) ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, A1, variant( 5.0 ) ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, C1, variant( 5.0 ) ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, B1, variant( "=\"42\"" ) ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, A1, variant( "=\"42\"" ) ) );
        chain.add( get_style_command( *s, range_to_use ) );
        BOOST_CHECK_NO_THROW( chain.execute() );
        {
            variant::variant_array_type expected_value( range_to_use.count(), style_str );
            expected_value[1] = "";
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[3] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( range_to_use.count(), style_str );
            expected_value[1] = "";
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[5] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( range_to_use.count(), style_str );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[7] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( range_to_use.count(), style_str );
            expected_value[1] = "";
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[9] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( range_to_use.count(), style_str );
            expected_value[1] = "";
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[11] ).value(), variant( expected_value ) );
        }
    }
}

BOOST_AUTO_TEST_CASE( test_value_rule_one_cell_not_between )
{
    const std::string rule_type = "CELL_VALUE";
    const std::string op = "not_between";
    {
        const sheet_range& range_to_use = one_point_range[0];

        variant::variant_array_type operands;
        operands.push_back( variant( "=B1" ) );
        operands.push_back( variant( "=C1" ) );
        command_chain chain;
        chain.add( set_conditional_format_command( *s
                                                   , set_cf_format(
                                                       variant( operands )
                                                       , rule_type + "(" + op + ";1;)"
                                                       , style_str
                                                       , one_point_range ) ) );

        chain.add( set_value_command( *s, A1, variant() ) );
        chain.add( set_value_command( *s, B1, variant( 5.0 ) ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, A1, variant( 5.0 ) ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, B1, variant( "=\"42\"" ) ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, A1, variant( -1.0 ) ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, C1, variant( -1.0 ) ) );
        chain.add( get_style_command( *s, range_to_use ) );

        BOOST_CHECK_NO_THROW( chain.execute() );
        {
            variant::variant_array_type expected_value( range_to_use.count(), "" );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[3] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( range_to_use.count(), "" );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[5] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( range_to_use.count(), "" );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[7] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( range_to_use.count(), style_str );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[9] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( range_to_use.count(), "" );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[7] ).value(), variant( expected_value ) );
        }
    }

    clear_cells_command( *s, sheet_range( sheet_point( 0, 0 ), sheet_point( 20, 20 ) ), content_type::all_plus_cf ).execute();

    {
        const sheet_range& range_to_use = real_range[0];


        variant::variant_array_type operands;
        operands.push_back( variant( "=B1" ) );
        operands.push_back( variant( "=C1" ) );
        command_chain chain;
        chain.add( set_conditional_format_command( *s
                                                   , set_cf_format(
                                                       variant( operands )
                                                       , rule_type + "(" + op + ";1;)"
                                                       , style_str
                                                       , real_range ) ) );

        chain.add( set_value_command( *s, A1, variant() ) );
        chain.add( set_value_command( *s, B1, variant( 5.0 ) ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, A1, variant( 5.0 ) ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, C1, variant( 5.0 ) ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, B1, variant( "=\"42\"" ) ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, A1, variant( "=\"42\"" ) ) );
        chain.add( get_style_command( *s, range_to_use ) );
        BOOST_CHECK_NO_THROW( chain.execute() );
        {
            variant::variant_array_type expected_value( range_to_use.count(), "" );
            expected_value[1] = style_str;
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[3] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( range_to_use.count(), "" );
            expected_value[1] = style_str;
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[5] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( range_to_use.count(), "" );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[7] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( range_to_use.count(), "" );
            expected_value[1] = style_str;
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[9] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( range_to_use.count(), "" );
            expected_value[1] = style_str;
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[11] ).value(), variant( expected_value ) );
        }
    }
}

BOOST_AUTO_TEST_CASE( test_text_rule_contained )
{
    const std::string rule_type = "TEXT";
    const std::string op = "contained";
    const sheet_range& range_to_use = one_point_range[0];

    variant::variant_array_type operands;
    operands.push_back( variant( "llo" ) );
    set_conditional_format_command( *s
                                    , set_cf_format(
                                        variant( operands )
                                        , rule_type + "(" + op + ";1;)"
                                        , style_str
                                        , one_point_range ) ).execute();

    set_value_command( *s, A1, variant( "hello there" ) ).execute();
    set_value_command( *s, B1, variant( "llo" ) ).execute();

    {
        variant::variant_array_type expected_value( range_to_use.count(), style_str );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, range_to_use ) ), variant( expected_value ) );
    }
    set_value_command( *s, A1, variant( "WHATS_up" ) ).execute();
    {
        variant::variant_array_type expected_value( range_to_use.count(), "" );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, range_to_use ) ), variant( expected_value ) );
    }
}

BOOST_AUTO_TEST_CASE( test_text_rule_not_contained_reference_as_operand )
{
    const std::string rule_type = "TEXT";
    const std::string op = "not_contained";
    const sheet_range& range_to_use = one_point_range[0];

    variant::variant_array_type operands;
    operands.push_back( variant( "=B1" ) );
    set_conditional_format_command( *s
                                    , set_cf_format(
                                        variant( operands )
                                        , rule_type + "(" + op + ";1;)"
                                        , style_str
                                        , one_point_range ) ).execute();

    set_value_command( *s, A1, variant( "hello there" ) ).execute();
    set_value_command( *s, B1, variant( "what" ) ).execute();

    {
        variant::variant_array_type expected_value( range_to_use.count(), style_str );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, range_to_use ) ), variant( expected_value ) );
    }
    set_value_command( *s, A1, variant( "WHATS_up" ) ).execute();
    {
        variant::variant_array_type expected_value( range_to_use.count(), "" );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, range_to_use ) ), variant( expected_value ) );
    }
    set_value_command( *s, B1, variant( "llo" ) ).execute();
    {
        variant::variant_array_type expected_value( range_to_use.count(), style_str );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, range_to_use ) ), variant( expected_value ) );
    }
}

BOOST_AUTO_TEST_CASE( test_text_rule_not_contained_string_as_operand )
{
    const std::string rule_type = "TEXT";
    const std::string op = "not_contained";
    const sheet_range& range_to_use = one_point_range[0];

    variant::variant_array_type operands;
    operands.push_back( variant( "what" ) );
    set_conditional_format_command( *s
                                    , set_cf_format(
                                        variant( operands )
                                        , rule_type + "(" + op + ";1;)"
                                        , style_str
                                        , one_point_range ) ).execute();

    set_value_command( *s, A1, variant( "hello there" ) ).execute();
    set_value_command( *s, B1, variant( "llo" ) ).execute();

    {
        variant::variant_array_type expected_value( range_to_use.count(), style_str );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, range_to_use ) ), variant( expected_value ) );
    }
    set_value_command( *s, A1, variant( "WHATS_up" ) ).execute();
    {
        variant::variant_array_type expected_value( range_to_use.count(), "" );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, range_to_use ) ), variant( expected_value ) );
    }
}

BOOST_AUTO_TEST_CASE( test_text_rule_begins_with_reference_as_operand )
{
    const std::string rule_type = "TEXT";
    const std::string op = "begins_with";
    const sheet_range& range_to_use = one_point_range[0];

    variant::variant_array_type operands;
    operands.push_back( variant( "=B1" ) );
    set_conditional_format_command( *s
                                    , set_cf_format(
                                        variant( operands )
                                        , rule_type + "(" + op + ";1;)"
                                        , style_str
                                        , one_point_range ) ).execute();

    set_value_command( *s, A1, variant( "hello there" ) ).execute();
    set_value_command( *s, B1, variant( "hell" ) ).execute();

    {
        variant::variant_array_type expected_value( range_to_use.count(), style_str );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, range_to_use ) ), variant( expected_value ) );
    }
    set_value_command( *s, A1, variant( "WHATS_up" ) ).execute();
    {
        variant::variant_array_type expected_value( range_to_use.count(), "" );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, range_to_use ) ), variant( expected_value ) );
    }
    set_value_command( *s, B1, variant( "wHats" ) ).execute();
    {
        variant::variant_array_type expected_value( range_to_use.count(), style_str );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, range_to_use ) ), variant( expected_value ) );
    }
}
BOOST_AUTO_TEST_CASE( test_text_rule_begins_with_string_as_operand )
{

    const std::string rule_type = "TEXT";
    const std::string op = "begins_with";
    const sheet_range& range_to_use = one_point_range[0];

    variant::variant_array_type operands;
    operands.push_back( variant( "hell" ) );
    set_conditional_format_command( *s
                                    , set_cf_format(
                                        variant( operands )
                                        , rule_type + "(" + op + ";1;)"
                                        , style_str
                                        , one_point_range ) ).execute();

    set_value_command( *s, A1, variant( "hello there" ) ).execute();

    {
        variant::variant_array_type expected_value( range_to_use.count(), style_str );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, range_to_use ) ), variant( expected_value ) );
    }
    set_value_command( *s, A1, variant( "WHATS_up" ) ).execute();
    {
        variant::variant_array_type expected_value( range_to_use.count(), "" );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, range_to_use ) ), variant( expected_value ) );
    }
}

BOOST_AUTO_TEST_CASE( test_text_rule_ends_with_reference_as_operand )
{
    const std::string rule_type = "TEXT";
    const std::string op = "ends_with";
    const sheet_range& range_to_use = one_point_range[0];

    variant::variant_array_type operands;
    operands.push_back( variant( "=B1" ) );
    set_conditional_format_command( *s
                                    , set_cf_format(
                                        variant( operands )
                                        , rule_type + "(" + op + ";1;)"
                                        , style_str
                                        , one_point_range ) ).execute();

    set_value_command( *s, A1, variant( "hello there" ) ).execute();
    set_value_command( *s, B1, variant( "ere" ) ).execute();

    {
        variant::variant_array_type expected_value( range_to_use.count(), style_str );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, range_to_use ) ), variant( expected_value ) );
    }
    set_value_command( *s, A1, variant( "WHATS_up" ) ).execute();
    {
        variant::variant_array_type expected_value( range_to_use.count(), "" );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, range_to_use ) ), variant( expected_value ) );
    }
    set_value_command( *s, B1, variant( "whATS_up" ) ).execute();
    {
        variant::variant_array_type expected_value( range_to_use.count(), style_str );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, range_to_use ) ), variant( expected_value ) );
    }
}

BOOST_AUTO_TEST_CASE( test_text_rule_ends_with_string_as_operand )
{
    const std::string rule_type = "TEXT";
    const std::string op = "ends_with";
    const sheet_range& range_to_use = one_point_range[0];

    variant::variant_array_type operands;
    operands.push_back( variant( "ere" ) );
    set_conditional_format_command( *s
                                    , set_cf_format(
                                        variant( operands )
                                        , rule_type + "(" + op + ";1;)"
                                        , style_str
                                        , one_point_range ) ).execute();

    set_value_command( *s, A1, variant( "hello there" ) ).execute();

    {
        variant::variant_array_type expected_value( range_to_use.count(), style_str );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, range_to_use ) ), variant( expected_value ) );
    }
    set_value_command( *s, A1, variant( "WHATS_up" ) ).execute();
    {
        variant::variant_array_type expected_value( range_to_use.count(), "" );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, range_to_use ) ), variant( expected_value ) );
    }
}

BOOST_AUTO_TEST_CASE( test_blanks )
{
    const std::string rule_type = "blanks";
    {
        const sheet_range& range_to_use = one_point_range[0];

        command_chain chain;
        chain.add( set_conditional_format_command( *s
                                                   , set_cf_format(
                                                       variant()
                                                       , rule_type + "(;1;)"
                                                       , style_str
                                                       , one_point_range ) ) );

        chain.add( set_value_command( *s, A1, variant() ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, A1, variant( 5.0 ) ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, A1, variant( " " ) ) );
        chain.add( get_style_command( *s, range_to_use ) );

        BOOST_CHECK_NO_THROW( chain.execute() );
        {
            variant::variant_array_type expected_value( one_point_range[0].count(), style_str );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[2] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( one_point_range[0].count(), "" );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[4] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( one_point_range[0].count(), "" );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[6] ).value(), variant( expected_value ) );
        }
    }

    clear_cells_command( *s, sheet_range( sheet_point( 0, 0 ), sheet_point( 20, 20 ) ), content_type::all_plus_cf ).execute();

    {
        const sheet_range& range_to_use = real_range[0];

        set_conditional_format_command( *s
                                        , set_cf_format(
                                            variant()
                                            , rule_type + "(;1;)"
                                            , style_str
                                            , real_range ) ).execute();

        {
            variant::variant_array_type expected_value( real_range[0].count(), style_str );
            BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, range_to_use ) ), variant( expected_value ) );
        }
        set_value_command( *s, A1, variant( 5.0 ) ).execute();
        {
            variant::variant_array_type expected_value( real_range[0].count(), style_str );
            expected_value.set( 0, "" );
            BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, range_to_use ) ), variant( expected_value ) );
        }
        set_value_command( *s, A1, variant( " " ) ).execute();
        {
            variant::variant_array_type expected_value( real_range[0].count(), style_str );
            expected_value.set( 0, "" );
            BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, range_to_use ) ), variant( expected_value ) );
        }
    }
}

BOOST_AUTO_TEST_CASE( test_no_blanks )
{
    const std::string rule_type = "no_blanks";
    {
        const sheet_range& range_to_use = one_point_range[0];

        command_chain chain;
        chain.add( set_conditional_format_command( *s
                                                   , set_cf_format(
                                                       variant()
                                                       , rule_type + "(;1;)"
                                                       , style_str
                                                       , one_point_range ) ) );

        chain.add( set_value_command( *s, A1, variant() ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, A1, variant( 5.0 ) ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, A1, variant( " " ) ) );
        chain.add( get_style_command( *s, range_to_use ) );

        BOOST_CHECK_NO_THROW( chain.execute() );
        {
            variant::variant_array_type expected_value( one_point_range[0].count(), "" );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[2] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( one_point_range[0].count(), style_str );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[4] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( one_point_range[0].count(), style_str );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[6] ).value(), variant( expected_value ) );
        }
    }

    clear_cells_command( *s, sheet_range( sheet_point( 0, 0 ), sheet_point( 20, 20 ) ), content_type::all_plus_cf ).execute();

    {
        const sheet_range& range_to_use = real_range[0];

        command_chain chain;
        chain.add( set_conditional_format_command( *s
                                                   , set_cf_format(
                                                       variant()
                                                       , rule_type + "(;1;)"
                                                       , style_str
                                                       , real_range ) ) );

        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, A1, variant( 5.0 ) ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, A1, variant( " " ) ) );
        chain.add( get_style_command( *s, range_to_use ) );

        BOOST_CHECK_NO_THROW( chain.execute() );
        {
            variant::variant_array_type expected_value( real_range[0].count(), "" );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[1] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( real_range[0].count(), "" );
            expected_value.set( 0, style_str );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[3] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( real_range[0].count(), "" );
            expected_value.set( 0, style_str );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[5] ).value(), variant( expected_value ) );
        }
    }
}


BOOST_AUTO_TEST_CASE( test_error )
{
    const std::string rule_type = "errors";
    {
        const sheet_range& range_to_use = one_point_range[0];

        command_chain chain;
        chain.add( set_conditional_format_command( *s
                                                   , set_cf_format(
                                                       variant( "=B1" )
                                                       , rule_type + "(;1;)"
                                                       , style_str
                                                       , one_point_range ) ) );

        chain.add( set_value_command( *s, A1, variant() ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, A1, variant( "=5/0" ) ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, A1, variant( "=test" ) ) );
        chain.add( get_style_command( *s, range_to_use ) );

        BOOST_CHECK_NO_THROW( chain.execute() );
        {
            variant::variant_array_type expected_value( one_point_range[0].count(), "" );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[2] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( one_point_range[0].count(), style_str );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[4] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( one_point_range[0].count(), style_str );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[6] ).value(), variant( expected_value ) );
        }
    }

    clear_cells_command( *s, sheet_range( sheet_point( 0, 0 ), sheet_point( 20, 20 ) ), content_type::all_plus_cf ).execute();

    {
        const sheet_range& range_to_use = real_range[0];

        command_chain chain;
        chain.add( set_conditional_format_command( *s
                                                   , set_cf_format(
                                                       variant( "=B1" )
                                                       , rule_type + "(;1;)"
                                                       , style_str
                                                       , real_range ) ) );

        chain.add( set_value_command( *s, A1, variant() ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, A1, variant( "=5/0" ) ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, A1, variant( "=test" ) ) );
        chain.add( get_style_command( *s, range_to_use ) );

        BOOST_CHECK_NO_THROW( chain.execute() );
        {
            variant::variant_array_type expected_value( real_range[0].count(), "" );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[2] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( real_range[0].count(), "" );
            expected_value.set( 0, style_str );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[4] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( real_range[0].count(), "" );
            expected_value.set( 0, style_str );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[6] ).value(), variant( expected_value ) );
        }
    }
}

BOOST_AUTO_TEST_CASE( test_no_error )
{
    const std::string rule_type = "no_errors";
    {
        const sheet_range& range_to_use = one_point_range[0];

        command_chain chain;
        chain.add( set_conditional_format_command( *s
                                                   , set_cf_format(
                                                       variant( "=B1" )
                                                       , rule_type + "(;1;)"
                                                       , style_str
                                                       , one_point_range ) ) );

        chain.add( set_value_command( *s, A1, variant() ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, A1, variant( "=5/0" ) ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, A1, variant( "=test" ) ) );
        chain.add( get_style_command( *s, range_to_use ) );

        BOOST_CHECK_NO_THROW( chain.execute() );
        {
            variant::variant_array_type expected_value( one_point_range[0].count(), style_str );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[2] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( one_point_range[0].count(), "" );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[4] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( one_point_range[0].count(), "" );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[6] ).value(), variant( expected_value ) );
        }
    }

    clear_cells_command( *s, sheet_range( sheet_point( 0, 0 ), sheet_point( 20, 20 ) ), content_type::all_plus_cf ).execute();

    {
        const sheet_range& range_to_use = real_range[0];

        command_chain chain;
        chain.add( set_conditional_format_command( *s
                                                   , set_cf_format(
                                                       variant( "=B1" )
                                                       , rule_type + "(;1;)"
                                                       , style_str
                                                       , real_range ) ) );

        chain.add( set_value_command( *s, A1, variant() ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, A1, variant( "=5/0" ) ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, A1, variant( "=test" ) ) );
        chain.add( get_style_command( *s, range_to_use ) );

        BOOST_CHECK_NO_THROW( chain.execute() );
        {
            variant::variant_array_type expected_value( real_range[0].count(), style_str );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[2] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( real_range[0].count(), style_str );
            expected_value.set( 0, "" );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[4] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( real_range[0].count(), style_str );
            expected_value.set( 0, "" );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[6] ).value(), variant( expected_value ) );
        }
    }
}



#ifdef TICKET_3647_DONE
//test cases need to be reviewed once this works!
BOOST_AUTO_TEST_CASE( test_top )
{
    test_top_bottom_rules( "top", variant( static_cast<double>( 5 ) ), variant( "bla" ), variant( static_cast<double>( 1 ) ), variant( "1" ) );
    test_top_bottom_rules( "top", variant( static_cast<double>( 5 ) ), variant( "bla" ), variant( static_cast<double>( 1 ) ), variant( static_cast<double>( 1 ) ) );
}

BOOST_AUTO_TEST_CASE( test_bottom )
{
    test_top_bottom_rules( "bottom", variant( static_cast<double>( 5 ) ), variant( "=3/0" ) );
}

BOOST_AUTO_TEST_CASE( test_top_percent )
{
    test_top_bottom_rules( "top_percent", variant( static_cast<double>( 5 ) ), variant( "bla" ), variant( static_cast<double>( 1 ) ), variant( "1" ) );
}

BOOST_AUTO_TEST_CASE( test_bottom_percent )
{
    test_top_bottom_rules( "bottom_percent", variant( static_cast<double>( 5 ) ), variant( "=3/0" ) );
}

#endif

BOOST_AUTO_TEST_CASE( test_unique_value )
{
    const std::string rule_type = "unique_value";
    {
        const sheet_range& range_to_use = one_point_range[0];

        command_chain chain;
        chain.add( set_conditional_format_command( *s
                                                   , set_cf_format(
                                                       variant()
                                                       , rule_type + "(;1;)"
                                                       , style_str
                                                       , one_point_range ) ) );

        chain.add( set_value_command( *s, A1, variant() ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, A1, variant( "=5/0" ) ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, A1, variant( 12.0 ) ) );
        chain.add( get_style_command( *s, range_to_use ) );

        BOOST_CHECK_NO_THROW( chain.execute() );
        {
            variant::variant_array_type expected_value( one_point_range[0].count(), "" );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[2] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( one_point_range[0].count(), style_str );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[4] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( one_point_range[0].count(), style_str );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[6] ).value(), variant( expected_value ) );
        }
    }

    clear_cells_command( *s, sheet_range( sheet_point( 0, 0 ), sheet_point( 20, 20 ) ), content_type::all_plus_cf ).execute();

    {
        const sheet_range& range_to_use = real_range[0];


        set_conditional_format_command( *s
                                        , set_cf_format(
                                            variant()
                                            , rule_type + "(;1;)"
                                            , style_str
                                            , real_range ) ).execute();

        set_value_command( *s, A1, variant() ).execute();
        {
            variant::variant_array_type expected_value( real_range[0].count(), "" );
            BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, range_to_use ) ), variant( expected_value ) );
        }
        set_value_command( *s, A1, variant( "=5/0" ) ).execute();
        {
            variant::variant_array_type expected_value( real_range[0].count(), "" );
            expected_value.set( 0, style_str );
            BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, range_to_use ) ), variant( expected_value ) );
        }
        set_value_command( *s, B1, variant( "=10/0" ) ).execute();
        {
            variant::variant_array_type expected_value( real_range[0].count(), "" );
            BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, range_to_use ) ), variant( expected_value ) );
        }
    }
}


BOOST_AUTO_TEST_CASE( test_duplicates )
{
    const std::string rule_type = "duplicate_value";
    {
        const sheet_range& range_to_use = one_point_range[0];

        command_chain chain;
        chain.add( set_conditional_format_command( *s
                                                   , set_cf_format(
                                                       variant()
                                                       , rule_type + "(;1;)"
                                                       , style_str
                                                       , one_point_range ) ) );

        chain.add( set_value_command( *s, A1, variant() ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, A1, variant( "=5/0" ) ) );
        chain.add( get_style_command( *s, range_to_use ) );

        BOOST_CHECK_NO_THROW( chain.execute() );
        {
            variant::variant_array_type expected_value( one_point_range[0].count(), "" );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[2] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( one_point_range[0].count(), "" );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[4] ).value(), variant( expected_value ) );
        }
    }

    clear_cells_command( *s, sheet_range( sheet_point( 0, 0 ), sheet_point( 20, 20 ) ), content_type::all_plus_cf ).execute();

    {
        const sheet_range& range_to_use = real_range[0];

        command_chain chain;
        chain.add( set_conditional_format_command( *s
                                                   , set_cf_format(
                                                       variant()
                                                       , rule_type + "(;1;)"
                                                       , style_str
                                                       , real_range ) ) );

        chain.add( set_value_command( *s, A1, variant() ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, A1, variant( "=5/0" ) ) );
        chain.add( get_style_command( *s, range_to_use ) );
        chain.add( set_value_command( *s, B1, variant( "=10/0" ) ) );
        chain.add( get_style_command( *s, range_to_use ) );

        BOOST_CHECK_NO_THROW( chain.execute() );
        {
            variant::variant_array_type expected_value( real_range[0].count(), "" );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[2] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( real_range[0].count(), "" );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[4] ).value(), variant( expected_value ) );
        }
        {
            variant::variant_array_type expected_value( real_range[0].count(), "" );
            expected_value.set( 0, style_str );
            expected_value.set( 1, style_str );
            BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[6] ).value(), variant( expected_value ) );
        }
    }
}

#ifdef TICKET_3639_DONE
BOOST_AUTO_TEST_CASE( test_average_value_equal )
{
    const std::string rule_type = "AVERAGE_VALUE";
    const std::string op = "=";

    const sheet_range& range_to_use = real_range[0];

    command_chain chain;
    chain.add( set_conditional_format_command( *s
                                               , set_cf_format(
                                                   variant( "=B1" )
                                                   , rule_type + "(" + op + ";1;)"
                                                   , style_str
                                                   , real_range ) ) );

    chain.add( set_value_command( *s, A1, variant( 4.0 ) ) );
    chain.add( set_value_command( *s, B1, variant( 4.0 ) ) );
    chain.add( get_style_command( *s, range_to_use ) );
    chain.add( set_value_command( *s, A1, variant( 5.0 ) ) );
    chain.add( get_style_command( *s, range_to_use ) );
    chain.add( set_value_command( *s, B1, variant( 5.0 ) ) );
    chain.add( get_style_command( *s, range_to_use ) );
    chain.add( set_value_command( *s, B1, variant( "=test" ) ) );
    chain.add( get_style_command( *s, range_to_use ) );

    BOOST_CHECK_NO_THROW( chain.execute() );
    {
        variant::variant_array_type expected_value( real_range[0].count(), "" );
        expected_value.set( 0, style_str );
        expected_value.set( 1, style_str );
        BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[3] ).value(), variant( expected_value ) );
    }
    {
        variant::variant_array_type expected_value( real_range[0].count(), "" );
        BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[5] ).value(), variant( expected_value ) );
    }
    {
        variant::variant_array_type expected_value( real_range[0].count(), "" );
        expected_value.set( 0, style_str );
        expected_value.set( 1, style_str );
        BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[7] ).value(), variant( expected_value ) );
    }
    {
        variant::variant_array_type expected_value( real_range[0].count(), "" );
        expected_value.set( 0, style_str );
        BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[9] ).value(), variant( expected_value ) );
    }
}


BOOST_AUTO_TEST_CASE( test_average_value_greater )
{
    const std::string rule_type = "AVERAGE_VALUE";
    const std::string op = ">";

    const sheet_range& range_to_use = real_range[0];

    command_chain chain;
    chain.add( set_conditional_format_command( *s
                                               , set_cf_format(
                                                   variant( "=B1" )
                                                   , rule_type + "(" + op + ";1;)"
                                                   , style_str
                                                   , real_range ) ) );

    chain.add( set_value_command( *s, A1, variant( 5.0 ) ) );
    chain.add( set_value_command( *s, B1, variant( 4.0 ) ) );
    chain.add( get_style_command( *s, range_to_use ) );
    chain.add( set_value_command( *s, A1, variant( 4.0 ) ) );
    chain.add( get_style_command( *s, range_to_use ) );
    chain.add( set_value_command( *s, B1, variant( 3.0 ) ) );
    chain.add( get_style_command( *s, range_to_use ) );
    chain.add( set_value_command( *s, B1, variant( "=test" ) ) );
    chain.add( get_style_command( *s, range_to_use ) );

    BOOST_CHECK_NO_THROW( chain.execute() );
    {
        variant::variant_array_type expected_value( real_range[0].count(), "" );
        expected_value.set( 0, style_str );
        BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[3] ).value(), variant( expected_value ) );
    }
    {
        variant::variant_array_type expected_value( real_range[0].count(), "" );
        BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[5] ).value(), variant( expected_value ) );
    }
    {
        variant::variant_array_type expected_value( real_range[0].count(), "" );
        expected_value.set( 0, style_str );
        BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[7] ).value(), variant( expected_value ) );
    }
    {
        variant::variant_array_type expected_value( real_range[0].count(), "" );
        BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[9] ).value(), variant( expected_value ) );
    }
}

BOOST_AUTO_TEST_CASE( test_average_value_less )
{
    const std::string rule_type = "AVERAGE_VALUE";
    const std::string op = "<";

    const sheet_range& range_to_use = real_range[0];

    command_chain chain;
    chain.add( set_conditional_format_command( *s
                                               , set_cf_format(
                                                   variant( "=B1" )
                                                   , rule_type + "(" + op + ";1;)"
                                                   , style_str
                                                   , real_range ) ) );

    chain.add( set_value_command( *s, A1, variant( 5.0 ) ) );
    chain.add( set_value_command( *s, B1, variant( 4.0 ) ) );
    chain.add( get_style_command( *s, range_to_use ) );
    chain.add( set_value_command( *s, A1, variant( 4.0 ) ) );
    chain.add( get_style_command( *s, range_to_use ) );
    chain.add( set_value_command( *s, B1, variant( 6.0 ) ) );
    chain.add( get_style_command( *s, range_to_use ) );
    chain.add( set_value_command( *s, B1, variant( "=test" ) ) );
    chain.add( get_style_command( *s, range_to_use ) );

    BOOST_CHECK_NO_THROW( chain.execute() );
    {
        variant::variant_array_type expected_value( real_range[0].count(), "" );
        expected_value.set( 1, style_str );
        BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[3] ).value(), variant( expected_value ) );
    }
    {
        variant::variant_array_type expected_value( real_range[0].count(), "" );
        BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[5] ).value(), variant( expected_value ) );
    }
    {
        variant::variant_array_type expected_value( real_range[0].count(), "" );
        expected_value.set( 0, style_str );
        BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[7] ).value(), variant( expected_value ) );
    }
    {
        variant::variant_array_type expected_value( real_range[0].count(), "" );
        BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[9] ).value(), variant( expected_value ) );
    }
}

BOOST_AUTO_TEST_CASE( test_average_value_greater_equal )
{
    const std::string rule_type = "AVERAGE_VALUE";
    const std::string op = ">=";

    const sheet_range& range_to_use = real_range[0];

    command_chain chain;
    chain.add( set_conditional_format_command( *s
                                               , set_cf_format(
                                                   variant( "=B1" )
                                                   , rule_type + "(" + op + ";1;)"
                                                   , style_str
                                                   , real_range ) ) );

    chain.add( set_value_command( *s, A1, variant( 5.0 ) ) );
    chain.add( set_value_command( *s, B1, variant( 4.0 ) ) );
    chain.add( get_style_command( *s, range_to_use ) );
    chain.add( set_value_command( *s, A1, variant( 4.0 ) ) );
    chain.add( get_style_command( *s, range_to_use ) );
    chain.add( set_value_command( *s, B1, variant( 6.0 ) ) );
    chain.add( get_style_command( *s, range_to_use ) );
    chain.add( set_value_command( *s, B1, variant( "=test" ) ) );
    chain.add( get_style_command( *s, range_to_use ) );

    BOOST_CHECK_NO_THROW( chain.execute() );
    {
        variant::variant_array_type expected_value( real_range[0].count(), "" );
        expected_value.set( 0, style_str );
        BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[3] ).value(), variant( expected_value ) );
    }
    {
        variant::variant_array_type expected_value( real_range[0].count(), "" );
        expected_value.set( 0, style_str );
        expected_value.set( 1, style_str );
        BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[5] ).value(), variant( expected_value ) );
    }
    {
        variant::variant_array_type expected_value( real_range[0].count(), "" );
        expected_value.set( 1, style_str );
        BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[7] ).value(), variant( expected_value ) );
    }
    {
        variant::variant_array_type expected_value( real_range[0].count(), "" );
        expected_value.set( 0, style_str );
        BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[9] ).value(), variant( expected_value ) );
    }
}

BOOST_AUTO_TEST_CASE( test_average_value_less_equal )
{
    const std::string rule_type = "AVERAGE_VALUE";
    const std::string op = "<=";

    const sheet_range& range_to_use = real_range[0];

    command_chain chain;
    chain.add( set_conditional_format_command( *s
                                               , set_cf_format(
                                                   variant( "=B1" )
                                                   , rule_type + "(" + op + ";1;)"
                                                   , style_str
                                                   , real_range ) ) );

    chain.add( set_value_command( *s, A1, variant( 5.0 ) ) );
    chain.add( set_value_command( *s, B1, variant( 4.0 ) ) );
    chain.add( get_style_command( *s, range_to_use ) );
    chain.add( set_value_command( *s, A1, variant( 4.0 ) ) );
    chain.add( get_style_command( *s, range_to_use ) );
    chain.add( set_value_command( *s, B1, variant( 6.0 ) ) );
    chain.add( get_style_command( *s, range_to_use ) );
    chain.add( set_value_command( *s, B1, variant( "=test" ) ) );
    chain.add( get_style_command( *s, range_to_use ) );

    BOOST_CHECK_NO_THROW( chain.execute() );
    {
        variant::variant_array_type expected_value( real_range[0].count(), "" );
        expected_value.set( 1, style_str );
        BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[3] ).value(), variant( expected_value ) );
    }
    {
        variant::variant_array_type expected_value( real_range[0].count(), "" );
        expected_value.set( 0, style_str );
        expected_value.set( 1, style_str );
        BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[5] ).value(), variant( expected_value ) );
    }
    {
        variant::variant_array_type expected_value( real_range[0].count(), "" );
        expected_value.set( 0, style_str );
        BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[7] ).value(), variant( expected_value ) );
    }
    {
        variant::variant_array_type expected_value( real_range[0].count(), "" );
        expected_value.set( 0, style_str );
        BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[9] ).value(), variant( expected_value ) );
    }
}
#endif
BOOST_AUTO_TEST_CASE( test_average_value_not_equal )
{
    const std::string rule_type = "AVERAGE_VALUE";
    const std::string op = "<>";
    sheet_range A2 = sheet_range( sheet_point( 1, 0 ), sheet_point( 1, 0 ) );
    const sheet_range& range_to_use = real_range[0];

    command_chain chain;
    chain.add( set_conditional_format_command( *s
                                               , set_cf_format(
                                                   variant()
                                                   , rule_type + "(" + op + ";1;)"
                                                   , style_str
                                                   , real_range ) ) );

    chain.add( set_value_command( *s, A1, variant( 5.0 ) ) );
    chain.add( set_value_command( *s, B1, variant( 4.0 ) ) );
    chain.add( get_style_command( *s, range_to_use ) );
    chain.add( set_value_command( *s, A1, variant( 4.0 ) ) );
    chain.add( get_style_command( *s, range_to_use ) );
    chain.add( set_value_command( *s, B1, variant( 6.0 ) ) );
    chain.add( get_style_command( *s, range_to_use ) );

    BOOST_CHECK_NO_THROW( chain.execute() );
    {
        variant::variant_array_type expected_value( real_range[0].count(), "" );
        expected_value.set( 0, style_str );
        expected_value.set( 1, style_str );
        BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[3] ).value(), variant( expected_value ) );
    }
    {
        variant::variant_array_type expected_value( real_range[0].count(), "" );
        BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[5] ).value(), variant( expected_value ) );
    }
    {
        variant::variant_array_type expected_value( real_range[0].count(), "" );
        expected_value.set( 0, style_str );
        expected_value.set( 1, style_str );
        BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[7] ).value(), variant( expected_value ) );
    }
}


BOOST_AUTO_TEST_CASE( test_formula_true )
{
    const std::string rule_type = "FORMULA_TRUE";
    const std::string op = "";
    sheet_range A2 = sheet_range( sheet_point( 1, 0 ), sheet_point( 1, 0 ) );
    const sheet_range& range_to_use = real_range[0];

    command_chain chain;
    chain.add( set_conditional_format_command( *s
                                               , set_cf_format(
                                                   variant( "=a1" )
                                                   , rule_type + "(" + op + ";1;)"
                                                   , style_str
                                                   , real_range ) ) );

    chain.add( set_value_command( *s, A1, variant( 1.0 ) ) );
    chain.add( get_style_command( *s, range_to_use ) );
    chain.add( set_value_command( *s, A1, variant( 0.0 ) ) );
    chain.add( get_style_command( *s, range_to_use ) );

    BOOST_CHECK_NO_THROW( chain.execute() );
    {
        variant::variant_array_type expected_value( real_range[0].count(), "" );
        expected_value.set( 0, style_str );
        BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[2] ).value(), variant( expected_value ) );
    }
    {
        variant::variant_array_type expected_value( real_range[0].count(), "" );
        BOOST_CHECK_EQUAL( static_cast<const get_style_command&>( chain[4] ).value(), variant( expected_value ) );
    }
}

BOOST_AUTO_TEST_CASE( test_move_one_cell )
{
    set_conditional_format::selected_ranges_type ranges;
    ranges.push_back( A1 );


    variant operands = variant( variant::type_array );
    operands.array().push_back( static_cast<double>( 0 ) );

    set_conditional_format_command( *s
                                    , set_cf_format(
                                        variant( 0.0 )
                                        , "CELL_VALUE(>;1;)"
                                        , style_str
                                        , ranges ) ).execute();

    set_value_command( *s, A1, variant( 1.0 ) ).execute();

    {
        variant::variant_array_type expected_value( 1, style_str );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, A1 ) ), variant( expected_value ) );

        shared_worksheet_type selected_ws = s->selected().worksheet().lock();
        sheet_range::rectangles_type ranges_for_query = sheet_range::rectangles_type( 1, A1 );

        get_conditionalformat_list_type result = execute_fetch( get_conditional_format_command( *s, selected_ws, ranges_for_query ) );
        const std::string expected_applies_to = "$A$1";
        BOOST_CHECK_NE( true, result.empty() );
        if ( !result.empty() ) {
            BOOST_CHECK_EQUAL( result.begin()->applies_to, expected_applies_to );
        }
    }

    const clipboard::clipboard_id_type id = execute_fetch( move_range_command( *s, A1 ) );
    paste_range_command( *s, B1, id ).execute();

    {
        variant::variant_array_type expected_value( 1, "" );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, A1 ) ), variant( expected_value ) );
    }

    {
        variant::variant_array_type expected_value( 1, style_str );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, B1 ) ), variant( expected_value ) );
    }
    {
        shared_worksheet_type selected_ws = s->selected().worksheet().lock();
        sheet_range::rectangles_type ranges_for_query = sheet_range::rectangles_type( 1, B1 );

        get_conditionalformat_list_type result = execute_fetch( get_conditional_format_command( *s, selected_ws, ranges_for_query ) );
        const std::string expected_applies_to = "$B$1";
        BOOST_CHECK_NE( true, result.empty() );
        if ( !result.empty() ) {
            BOOST_CHECK_EQUAL( result.begin()->applies_to, expected_applies_to );
        }
    }
}

BOOST_AUTO_TEST_CASE( test_move_range )
{

    variant operands = variant( variant::type_array );
    operands.array().push_back( static_cast<double>( 0 ) );

    set_conditional_format_command( *s
                                    , set_cf_format(
                                        variant( 0.0 )
                                        , "CELL_VALUE(>;1;)"
                                        , style_str
                                        , real_range ) ).execute();

    set_value_command( *s, A1, variant( 1.0 ) ).execute();

    {
        variant::variant_array_type expected_value( 1, style_str );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, A1 ) ), variant( expected_value ) );

        shared_worksheet_type selected_ws = s->selected().worksheet().lock();
        sheet_range::rectangles_type ranges_for_query = sheet_range::rectangles_type( 1, A1 );

        get_conditionalformat_list_type result = execute_fetch( get_conditional_format_command( *s, selected_ws, ranges_for_query ) );
        const std::string expected_applies_to = "$A$1:$B$2";
        BOOST_CHECK_NE( true, result.empty() );
        if ( !result.empty() ) {
            BOOST_CHECK_EQUAL( result.begin()->applies_to, expected_applies_to );
        }
    }

    const clipboard::clipboard_id_type id = execute_fetch( move_range_command( *s, real_range[0] ) );
    const sheet_range target_range( real_range[0].offset( 3, 3 ) );

    paste_range_command( *s, target_range, id ).execute();

    {
        variant::variant_array_type expected_value( real_range[0].count(), "" );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, real_range[0] ) ), variant( expected_value ) );
    }

    {
        variant::variant_array_type expected_value( real_range[0].count(), "" );
        expected_value.set( 0, style_str );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, target_range ) ), variant( expected_value ) );
    }
    {
        shared_worksheet_type selected_ws = s->selected().worksheet().lock();
        sheet_range::rectangles_type ranges_for_query = sheet_range::rectangles_type( 1, target_range );

        get_conditionalformat_list_type result = execute_fetch( get_conditional_format_command( *s, selected_ws, ranges_for_query ) );
        const std::string expected_applies_to = "$D$4:$E$5";
        BOOST_CHECK_NE( true, result.empty() );
        if ( !result.empty() ) {
            BOOST_CHECK_EQUAL( result.begin()->applies_to, expected_applies_to );
        }
    }
}

BOOST_AUTO_TEST_CASE( test_move_range2 )
{

    variant operands = variant( variant::type_array );
    operands.array().push_back( "=a1" );

    set_conditional_format_command( *s
                                    , set_cf_format(
                                        variant( 0.0 )
                                        , "CELL_VALUE(=;1;)"
                                        , style_str
                                        , real_range ) ).execute();

    set_value_command( *s, A1, variant( 1.0 ) ).execute();

    {
        variant::variant_array_type expected_value( 1, style_str );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, A1 ) ), variant( expected_value ) );

        shared_worksheet_type selected_ws = s->selected().worksheet().lock();
        sheet_range::rectangles_type ranges_for_query = sheet_range::rectangles_type( 1, A1 );

        get_conditionalformat_list_type result = execute_fetch( get_conditional_format_command( *s, selected_ws, ranges_for_query ) );
        const std::string expected_applies_to = "$A$1:$B$2";
        BOOST_CHECK_NE( true, result.empty() );
        if ( !result.empty() ) {
            BOOST_CHECK_EQUAL( result.begin()->applies_to, expected_applies_to );
        }
    }

    const clipboard::clipboard_id_type id = execute_fetch( move_range_command( *s, real_range[0] ) );
    const sheet_range target_range( real_range[0].offset( 3, 3 ) );

    paste_range_command( *s, target_range, id ).execute();

    {
        variant::variant_array_type expected_value( real_range[0].count(), "" );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, real_range[0] ) ), variant( expected_value ) );
    }

    {
        variant::variant_array_type expected_value( real_range[0].count(), "" );
        expected_value.set( 0, style_str );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, target_range ) ), variant( expected_value ) );
    }
    {
        shared_worksheet_type selected_ws = s->selected().worksheet().lock();
        sheet_range::rectangles_type ranges_for_query = sheet_range::rectangles_type( 1, target_range );

        get_conditionalformat_list_type result = execute_fetch( get_conditional_format_command( *s, selected_ws, ranges_for_query ) );
        const std::string expected_applies_to = "$D$4:$E$5";
        BOOST_CHECK_NE( true, result.empty() );
        if ( !result.empty() ) {
            BOOST_CHECK_EQUAL( result.begin()->applies_to, expected_applies_to );
        }
    }
}


BOOST_AUTO_TEST_CASE( test_move_overlapping )
{

    variant operands = variant( variant::type_array );
    operands.array().push_back( static_cast<double>( 0 ) );

    set_conditional_format_command( *s
                                    , set_cf_format(
                                        variant( 0.0 )
                                        , "CELL_VALUE(>;1;)"
                                        , style_str
                                        , real_range ) ).execute();

    set_value_command( *s, A1, variant( 1.0 ) ).execute();

    {
        variant::variant_array_type expected_value( 1, style_str );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, A1 ) ), variant( expected_value ) );

        shared_worksheet_type selected_ws = s->selected().worksheet().lock();
        sheet_range::rectangles_type ranges_for_query = sheet_range::rectangles_type( 1, A1 );

        get_conditionalformat_list_type result = execute_fetch( get_conditional_format_command( *s, selected_ws, ranges_for_query ) );
        const std::string expected_applies_to = "$A$1:$B$2";
        BOOST_CHECK_NE( true, result.empty() );
        if ( !result.empty() ) {
            BOOST_CHECK_EQUAL( result.begin()->applies_to, expected_applies_to );
        }
    }

    const clipboard::clipboard_id_type id = execute_fetch( move_range_command( *s, real_range[0] ) );
    const sheet_range target_range( real_range[0].offset( 1, 1 ) );

    paste_range_command( *s, target_range, id ).execute();

    {
        variant::variant_array_type expected_value( real_range[0].count(), "" );
        expected_value.set( 3, style_str );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, real_range[0] ) ), variant( expected_value ) );
    }

    {
        variant::variant_array_type expected_value( real_range[0].count(), "" );
        expected_value.set( 0, style_str );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, target_range ) ), variant( expected_value ) );
    }
    {
        shared_worksheet_type selected_ws = s->selected().worksheet().lock();
        sheet_range::rectangles_type ranges_for_query = sheet_range::rectangles_type( 1, target_range );

        get_conditionalformat_list_type result = execute_fetch( get_conditional_format_command( *s, selected_ws, ranges_for_query ) );
        const std::string expected_applies_to = "$B$2:$C$3";
        BOOST_CHECK_NE( true, result.empty() );
        if ( !result.empty() ) {
            BOOST_CHECK_EQUAL( result.begin()->applies_to, expected_applies_to );
        }
    }
}
//////
BOOST_AUTO_TEST_CASE( test_move_one_cell_to_other_sheet )
{
    shared_worksheet_type other_sheet = ws1->parent()->add( "other_sheet" );

    set_conditional_format::selected_ranges_type ranges;
    ranges.push_back( A1 );


    variant operands = variant( variant::type_array );
    operands.array().push_back( static_cast<double>( 0 ) );

    set_conditional_format_command( *s
                                    , set_cf_format(
                                        variant( 0.0 )
                                        , "CELL_VALUE(>;1;)"
                                        , style_str
                                        , ranges ) ).execute();

    set_value_command( *s, A1, variant( 1.0 ) ).execute();

    {
        variant::variant_array_type expected_value( 1, style_str );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, A1 ) ), variant( expected_value ) );

        shared_worksheet_type selected_ws = s->selected().worksheet().lock();
        sheet_range::rectangles_type ranges_for_query = sheet_range::rectangles_type( 1, A1 );

        get_conditionalformat_list_type result = execute_fetch( get_conditional_format_command( *s, selected_ws, ranges_for_query ) );
        const std::string expected_applies_to = "$A$1";
        BOOST_CHECK_NE( true, result.empty() );
        if ( !result.empty() ) {
            BOOST_CHECK_EQUAL( result.begin()->applies_to, expected_applies_to );
        }
    }

    const clipboard::clipboard_id_type id = execute_fetch( move_range_command( *s, A1 ) );

    other_sheet->select( s->selected() );

    paste_range_command( *s, B1, id ).execute();

    {
        ws1->select( s->selected() );
        variant::variant_array_type expected_value( 1, "" );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, A1 ) ), variant( expected_value ) );
    }

    {
        other_sheet->select( s->selected() );
        variant::variant_array_type expected_value( 1, style_str );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, B1 ) ), variant( expected_value ) );
    }
    {
        shared_worksheet_type selected_ws = s->selected().worksheet().lock();
        sheet_range::rectangles_type ranges_for_query = sheet_range::rectangles_type( 1, B1 );

        get_conditionalformat_list_type result = execute_fetch( get_conditional_format_command( *s, selected_ws, ranges_for_query ) );
        const std::string expected_applies_to = "$B$1";
        BOOST_CHECK_NE( true, result.empty() );
        if ( !result.empty() ) {
            BOOST_CHECK_EQUAL( result.begin()->applies_to, expected_applies_to );
        }
    }
}

BOOST_AUTO_TEST_CASE( test_move_range_to_other_sheet )
{

    shared_worksheet_type other_sheet = ws1->parent()->add( "other_sheet" );

    variant operands = variant( variant::type_array );
    operands.array().push_back( static_cast<double>( 0 ) );

    set_conditional_format_command( *s
                                    , set_cf_format(
                                        variant( 0.0 )
                                        , "CELL_VALUE(>;1;)"
                                        , style_str
                                        , real_range ) ).execute();

    set_value_command( *s, A1, variant( 1.0 ) ).execute();

    {
        variant::variant_array_type expected_value( 1, style_str );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, A1 ) ), variant( expected_value ) );

        shared_worksheet_type selected_ws = s->selected().worksheet().lock();
        sheet_range::rectangles_type ranges_for_query = sheet_range::rectangles_type( 1, A1 );

        get_conditionalformat_list_type result = execute_fetch( get_conditional_format_command( *s, selected_ws, ranges_for_query ) );
        const std::string expected_applies_to = "$A$1:$B$2";
        BOOST_CHECK_NE( true, result.empty() );
        if ( !result.empty() ) {
            BOOST_CHECK_EQUAL( result.begin()->applies_to, expected_applies_to );
        }
    }

    const clipboard::clipboard_id_type id = execute_fetch( move_range_command( *s, real_range[0] ) );
    const sheet_range target_range( real_range[0].offset( 3, 3 ) );

    other_sheet->select( s->selected() );

    paste_range_command( *s, target_range, id ).execute();

    {
        ws1->select( s->selected() );
        variant::variant_array_type expected_value( real_range[0].count(), "" );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, real_range[0] ) ), variant( expected_value ) );
    }

    {
        other_sheet->select( s->selected() );
        variant::variant_array_type expected_value( real_range[0].count(), "" );
        expected_value.set( 0, style_str );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, target_range ) ), variant( expected_value ) );
    }
    {
        shared_worksheet_type selected_ws = s->selected().worksheet().lock();
        sheet_range::rectangles_type ranges_for_query = sheet_range::rectangles_type( 1, target_range );

        get_conditionalformat_list_type result = execute_fetch( get_conditional_format_command( *s, selected_ws, ranges_for_query ) );
        const std::string expected_applies_to = "$D$4:$E$5";
        BOOST_CHECK_NE( true, result.empty() );
        if ( !result.empty() ) {
            BOOST_CHECK_EQUAL( result.begin()->applies_to, expected_applies_to );
        }
    }
}


BOOST_AUTO_TEST_CASE( test_move_overlapping_to_other_sheet )
{

    shared_worksheet_type other_sheet = ws1->parent()->add( "other_sheet" );
    variant operands = variant( variant::type_array );
    operands.array().push_back( static_cast<double>( 0 ) );

    set_conditional_format_command( *s
                                    , set_cf_format(
                                        variant( 0.0 )
                                        , "CELL_VALUE(>;1;)"
                                        , style_str
                                        , real_range ) ).execute();

    set_value_command( *s, A1, variant( 1.0 ) ).execute();

    {
        variant::variant_array_type expected_value( 1, style_str );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, A1 ) ), variant( expected_value ) );

        shared_worksheet_type selected_ws = s->selected().worksheet().lock();
        sheet_range::rectangles_type ranges_for_query = sheet_range::rectangles_type( 1, A1 );

        get_conditionalformat_list_type result = execute_fetch( get_conditional_format_command( *s, selected_ws, ranges_for_query ) );
        const std::string expected_applies_to = "$A$1:$B$2";
        BOOST_CHECK_NE( true, result.empty() );
        if ( !result.empty() ) {
            BOOST_CHECK_EQUAL( result.begin()->applies_to, expected_applies_to );
        }
    }

    const clipboard::clipboard_id_type id = execute_fetch( move_range_command( *s, real_range[0] ) );
    const sheet_range target_range( real_range[0].offset( 1, 1 ) );

    other_sheet->select( s->selected() );

    paste_range_command( *s, target_range, id ).execute();

    {
        ws1->select( s->selected() );
        variant::variant_array_type expected_value( real_range[0].count(), "" );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, real_range[0] ) ), variant( expected_value ) );
    }

    {
        other_sheet->select( s->selected() );

        variant::variant_array_type expected_value( real_range[0].count(), "" );
        expected_value.set( 0, style_str );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, target_range ) ), variant( expected_value ) );
    }
    {
        shared_worksheet_type selected_ws = s->selected().worksheet().lock();
        sheet_range::rectangles_type ranges_for_query = sheet_range::rectangles_type( 1, target_range );

        get_conditionalformat_list_type result = execute_fetch( get_conditional_format_command( *s, selected_ws, ranges_for_query ) );
        const std::string expected_applies_to = "$B$2:$C$3";
        BOOST_CHECK_NE( true, result.empty() );
        if ( !result.empty() ) {
            BOOST_CHECK_EQUAL( result.begin()->applies_to, expected_applies_to );
        }
    }
}

//copy tests

BOOST_AUTO_TEST_CASE( test_copy_one_cell )
{
    set_conditional_format::selected_ranges_type ranges;
    ranges.push_back( A1 );


    variant operands = variant( variant::type_array );
    operands.array().push_back( static_cast<double>( 0 ) );

    set_conditional_format_command( *s
                                    , set_cf_format(
                                        variant( 0.0 )
                                        , "CELL_VALUE(>;1;)"
                                        , style_str
                                        , ranges ) ).execute();

    set_value_command( *s, A1, variant( 1.0 ) ).execute();

    {
        variant::variant_array_type expected_value( 1, style_str );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, A1 ) ), variant( expected_value ) );

        shared_worksheet_type selected_ws = s->selected().worksheet().lock();
        sheet_range::rectangles_type ranges_for_query = sheet_range::rectangles_type( 1, A1 );

        get_conditionalformat_list_type result = execute_fetch( get_conditional_format_command( *s, selected_ws, ranges_for_query ) );
        const std::string expected_applies_to = "$A$1";
        BOOST_CHECK_NE( true, result.empty() );
        if ( !result.empty() ) {
            BOOST_CHECK_EQUAL( result.begin()->applies_to, expected_applies_to );
        }
    }

    const clipboard::clipboard_id_type id = execute_fetch( copy_range_command( *s, A1 ) );
    paste_range_command( *s, B1, id ).execute();

    {
        shared_worksheet_type selected_ws = s->selected().worksheet().lock();
        sheet_range::rectangles_type ranges_for_query = sheet_range::rectangles_type( 1, A1 );

        get_conditionalformat_list_type result = execute_fetch( get_conditional_format_command( *s, selected_ws, ranges_for_query ) );
        const std::string expected_applies_to = "$A$1:$B$1";
        BOOST_CHECK_NE( true, result.empty() );
        if ( !result.empty() ) {
            BOOST_CHECK_EQUAL( result.begin()->applies_to, expected_applies_to );
        }
    }

    {
        variant::variant_array_type expected_value( 1, style_str );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, B1 ) ), variant( expected_value ) );
    }
    {
        shared_worksheet_type selected_ws = s->selected().worksheet().lock();
        sheet_range::rectangles_type ranges_for_query = sheet_range::rectangles_type( 1, B1 );

        get_conditionalformat_list_type result = execute_fetch( get_conditional_format_command( *s, selected_ws, ranges_for_query ) );
        const std::string expected_applies_to = "$A$1:$B$1";
        BOOST_CHECK_NE( true, result.empty() );
        if ( !result.empty() ) {
            BOOST_CHECK_EQUAL( result.begin()->applies_to, expected_applies_to );
        }
    }
}

BOOST_AUTO_TEST_CASE( test_copy_range )
{

    variant operands = variant( variant::type_array );
    operands.array().push_back( static_cast<double>( 0 ) );

    set_conditional_format_command( *s
                                    , set_cf_format(
                                        variant( 0.0 )
                                        , "CELL_VALUE(>;1;)"
                                        , style_str
                                        , real_range ) ).execute();

    set_value_command( *s, A1, variant( 1.0 ) ).execute();

    {
        variant::variant_array_type expected_value( 1, style_str );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, A1 ) ), variant( expected_value ) );

        shared_worksheet_type selected_ws = s->selected().worksheet().lock();
        sheet_range::rectangles_type ranges_for_query = sheet_range::rectangles_type( 1, A1 );

        get_conditionalformat_list_type result = execute_fetch( get_conditional_format_command( *s, selected_ws, ranges_for_query ) );
        const std::string expected_applies_to = "$A$1:$B$2";
        BOOST_CHECK_NE( true, result.empty() );
        if ( !result.empty() ) {
            BOOST_CHECK_EQUAL( result.begin()->applies_to, expected_applies_to );
        }
    }

    const clipboard::clipboard_id_type id = execute_fetch( copy_range_command( *s, real_range[0] ) );
    const sheet_range target_range( real_range[0].offset( 3, 3 ) );

    paste_range_command( *s, target_range, id ).execute();

    {
        variant::variant_array_type expected_value( 1, style_str );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, A1 ) ), variant( expected_value ) );

        shared_worksheet_type selected_ws = s->selected().worksheet().lock();
        sheet_range::rectangles_type ranges_for_query = sheet_range::rectangles_type( 1, A1 );

        get_conditionalformat_list_type result = execute_fetch( get_conditional_format_command( *s, selected_ws, ranges_for_query ) );
        const std::string expected_applies_to = "$A$1:$B$2;$D$4:$E$5";
        BOOST_CHECK_NE( true, result.empty() );
        if ( !result.empty() ) {
            BOOST_CHECK_EQUAL( result.begin()->applies_to, expected_applies_to );
        }
    }

    {
        variant::variant_array_type expected_value( real_range[0].count(), "" );
        expected_value.set( 0, style_str );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, target_range ) ), variant( expected_value ) );

        shared_worksheet_type selected_ws = s->selected().worksheet().lock();
        sheet_range::rectangles_type ranges_for_query = sheet_range::rectangles_type( 1, target_range );

        get_conditionalformat_list_type result = execute_fetch( get_conditional_format_command( *s, selected_ws, ranges_for_query ) );
        const std::string expected_applies_to = "$A$1:$B$2;$D$4:$E$5";
        BOOST_CHECK_NE( true, result.empty() );
        if ( !result.empty() ) {
            BOOST_CHECK_EQUAL( result.begin()->applies_to, expected_applies_to );
        }
    }
}


BOOST_AUTO_TEST_CASE( test_copy_overlapping )
{

    variant operands = variant( variant::type_array );
    operands.array().push_back( static_cast<double>( 0 ) );

    set_conditional_format_command( *s
                                    , set_cf_format(
                                        variant( 0.0 )
                                        , "CELL_VALUE(>;1;)"
                                        , style_str
                                        , real_range ) ).execute();

    set_value_command( *s, A1, variant( 1.0 ) ).execute();

    {
        variant::variant_array_type expected_value( 1, style_str );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, A1 ) ), variant( expected_value ) );

        shared_worksheet_type selected_ws = s->selected().worksheet().lock();
        sheet_range::rectangles_type ranges_for_query = sheet_range::rectangles_type( 1, A1 );

        get_conditionalformat_list_type result = execute_fetch( get_conditional_format_command( *s, selected_ws, ranges_for_query ) );
        const std::string expected_applies_to = "$A$1:$B$2";
        BOOST_CHECK_NE( true, result.empty() );
        if ( !result.empty() ) {
            BOOST_CHECK_EQUAL( result.begin()->applies_to, expected_applies_to );
        }
    }

    const clipboard::clipboard_id_type id = execute_fetch( copy_range_command( *s, real_range[0] ) );
    const sheet_range target_range( real_range[0].offset( 1, 1 ) );

    paste_range_command( *s, target_range, id ).execute();

    {
        variant::variant_array_type expected_value( real_range[0].count(), "" );
        expected_value.set( 0, style_str );
        expected_value.set( 3, style_str );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, real_range[0] ) ), variant( expected_value ) );
    }

    {
        variant::variant_array_type expected_value( real_range[0].count(), "" );
        expected_value.set( 0, style_str );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, target_range ) ), variant( expected_value ) );
    }
    {
        shared_worksheet_type selected_ws = s->selected().worksheet().lock();
        sheet_range::rectangles_type ranges_for_query = sheet_range::rectangles_type( 1, target_range );

        get_conditionalformat_list_type result = execute_fetch( get_conditional_format_command( *s, selected_ws, ranges_for_query ) );
        const std::string expected_applies_to = "$A$1:$B$2;$C$2:$C$3;$B$3";
        BOOST_CHECK_NE( true, result.empty() );
        if ( !result.empty() ) {
            BOOST_CHECK_EQUAL( result.begin()->applies_to, expected_applies_to );
        }
    }
}
//////TODO
BOOST_AUTO_TEST_CASE( test_copy_one_cell_to_other_sheet )
{
    shared_worksheet_type other_sheet = ws1->parent()->add( "other_sheet" );

    set_conditional_format::selected_ranges_type ranges;
    ranges.push_back( A1 );


    variant operands = variant( variant::type_array );
    operands.array().push_back( static_cast<double>( 0 ) );

    set_conditional_format_command( *s
                                    , set_cf_format(
                                        variant( 0.0 )
                                        , "CELL_VALUE(>;1;)"
                                        , style_str
                                        , ranges ) ).execute();

    set_value_command( *s, A1, variant( 1.0 ) ).execute();

    {
        variant::variant_array_type expected_value( 1, style_str );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, A1 ) ), variant( expected_value ) );

        shared_worksheet_type selected_ws = s->selected().worksheet().lock();
        sheet_range::rectangles_type ranges_for_query = sheet_range::rectangles_type( 1, A1 );

        get_conditionalformat_list_type result = execute_fetch( get_conditional_format_command( *s, selected_ws, ranges_for_query ) );
        const std::string expected_applies_to = "$A$1";
        BOOST_CHECK_NE( true, result.empty() );
        if ( !result.empty() ) {
            BOOST_CHECK_EQUAL( result.begin()->applies_to, expected_applies_to );
        }
    }

    const clipboard::clipboard_id_type id = execute_fetch( copy_range_command( *s, A1 ) );

    other_sheet->select( s->selected() );

    paste_range_command( *s, B1, id ).execute();

    {
        ws1->select( s->selected() );
        variant::variant_array_type expected_value( 1, "" );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, A1 ) ), variant( expected_value ) );
    }

    {
        other_sheet->select( s->selected() );
        variant::variant_array_type expected_value( 1, style_str );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, B1 ) ), variant( expected_value ) );
    }
    {
        shared_worksheet_type selected_ws = s->selected().worksheet().lock();
        sheet_range::rectangles_type ranges_for_query = sheet_range::rectangles_type( 1, B1 );

        get_conditionalformat_list_type result = execute_fetch( get_conditional_format_command( *s, selected_ws, ranges_for_query ) );
        const std::string expected_applies_to = "$B$1";
        BOOST_CHECK_NE( true, result.empty() );
        if ( !result.empty() ) {
            BOOST_CHECK_EQUAL( result.begin()->applies_to, expected_applies_to );
        }
    }
}

BOOST_AUTO_TEST_CASE( test_copy_range_to_other_sheet )
{

    shared_worksheet_type other_sheet = ws1->parent()->add( "other_sheet" );

    variant operands = variant( variant::type_array );
    operands.array().push_back( static_cast<double>( 0 ) );

    set_conditional_format_command( *s
                                    , set_cf_format(
                                        variant( 0.0 )
                                        , "CELL_VALUE(>;1;)"
                                        , style_str
                                        , real_range ) ).execute();

    set_value_command( *s, A1, variant( 1.0 ) ).execute();

    {
        variant::variant_array_type expected_value( 1, style_str );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, A1 ) ), variant( expected_value ) );

        shared_worksheet_type selected_ws = s->selected().worksheet().lock();
        sheet_range::rectangles_type ranges_for_query = sheet_range::rectangles_type( 1, A1 );

        get_conditionalformat_list_type result = execute_fetch( get_conditional_format_command( *s, selected_ws, ranges_for_query ) );
        const std::string expected_applies_to = "$A$1:$B$2";
        BOOST_CHECK_NE( true, result.empty() );
        if ( !result.empty() ) {
            BOOST_CHECK_EQUAL( result.begin()->applies_to, expected_applies_to );
        }
    }

    const clipboard::clipboard_id_type id = execute_fetch( copy_range_command( *s, real_range[0] ) );
    const sheet_range target_range( real_range[0].offset( 3, 3 ) );

    other_sheet->select( s->selected() );

    paste_range_command( *s, target_range, id ).execute();

    {
        ws1->select( s->selected() );
        variant::variant_array_type expected_value( real_range[0].count(), "" );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, real_range[0] ) ), variant( expected_value ) );
    }

    {
        other_sheet->select( s->selected() );
        variant::variant_array_type expected_value( real_range[0].count(), "" );
        expected_value.set( 0, style_str );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, target_range ) ), variant( expected_value ) );
    }
    {
        shared_worksheet_type selected_ws = s->selected().worksheet().lock();
        sheet_range::rectangles_type ranges_for_query = sheet_range::rectangles_type( 1, target_range );

        get_conditionalformat_list_type result = execute_fetch( get_conditional_format_command( *s, selected_ws, ranges_for_query ) );
        const std::string expected_applies_to = "$D$4:$E$5";
        BOOST_CHECK_NE( true, result.empty() );
        if ( !result.empty() ) {
            BOOST_CHECK_EQUAL( result.begin()->applies_to, expected_applies_to );
        }
    }
}


BOOST_AUTO_TEST_CASE( test_copy_overlapping_to_other_sheet )
{

    shared_worksheet_type other_sheet = ws1->parent()->add( "other_sheet" );
    variant operands = variant( variant::type_array );
    operands.array().push_back( static_cast<double>( 0 ) );

    set_conditional_format_command( *s
                                    , set_cf_format(
                                        variant( 0.0 )
                                        , "CELL_VALUE(>;1;)"
                                        , style_str
                                        , real_range ) ).execute();

    set_value_command( *s, A1, variant( 1.0 ) ).execute();

    {
        variant::variant_array_type expected_value( 1, style_str );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, A1 ) ), variant( expected_value ) );

        shared_worksheet_type selected_ws = s->selected().worksheet().lock();
        sheet_range::rectangles_type ranges_for_query = sheet_range::rectangles_type( 1, A1 );

        get_conditionalformat_list_type result = execute_fetch( get_conditional_format_command( *s, selected_ws, ranges_for_query ) );
        const std::string expected_applies_to = "$A$1:$B$2";
        BOOST_CHECK_NE( true, result.empty() );
        if ( !result.empty() ) {
            BOOST_CHECK_EQUAL( result.begin()->applies_to, expected_applies_to );
        }
    }

    const clipboard::clipboard_id_type id = execute_fetch( copy_range_command( *s, real_range[0] ) );
    const sheet_range target_range( real_range[0].offset( 1, 1 ) );

    other_sheet->select( s->selected() );

    paste_range_command( *s, target_range, id ).execute();

    {
        ws1->select( s->selected() );
        variant::variant_array_type expected_value( real_range[0].count(), "" );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, real_range[0] ) ), variant( expected_value ) );
    }

    {
        other_sheet->select( s->selected() );

        variant::variant_array_type expected_value( real_range[0].count(), "" );
        expected_value.set( 0, style_str );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, target_range ) ), variant( expected_value ) );
    }
    {
        shared_worksheet_type selected_ws = s->selected().worksheet().lock();
        sheet_range::rectangles_type ranges_for_query = sheet_range::rectangles_type( 1, target_range );

        get_conditionalformat_list_type result = execute_fetch( get_conditional_format_command( *s, selected_ws, ranges_for_query ) );
        const std::string expected_applies_to = "$B$2:$C$3";
        BOOST_CHECK_NE( true, result.empty() );
        if ( !result.empty() ) {
            BOOST_CHECK_EQUAL( result.begin()->applies_to, expected_applies_to );
        }
    }
}

BOOST_AUTO_TEST_CASE( test_ranks )
{

    const std::string style_red_bg = "background:red;";
    const std::string style_blue_bg = "background:blue;";
    const std::string style_yellow_fg = "foreground:yellow;";

    variant operands = variant( variant::type_array );
    operands.array().push_back( 0.0 );
    set_conditional_format::selected_ranges_type ranges = one_point_range;

    ws2->select( s->selected() );
    //add all 3
    // this one should create id 2
    set_conditional_format_command( *s
                                    , set_cf_format( operands , "CELL_VALUE(>;0;)", style_red_bg, ranges ) ).execute();
    // this one should create id 3
    set_conditional_format_command( *s
                                    , set_cf_format( operands , "CELL_VALUE(>;0;)", style_blue_bg, ranges ) ).execute();
    // this one should create id 4
    set_conditional_format_command( *s
                                    , set_cf_format( operands , "CELL_VALUE(>;0;)", style_yellow_fg, ranges ) ).execute();

    set_value_command( *s, one_point_range[0], variant( 1.0 ) ).execute();

    {
        style_set_type tmp_style_set = style_set_type::unserialize( style_yellow_fg );
        tmp_style_set.combine( style_set_type::unserialize( style_blue_bg ) );
        tmp_style_set.combine( style_set_type::unserialize( style_red_bg ) );
        variant::variant_array_type expected_value( 1, tmp_style_set.serialize() );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, one_point_range[0] ) ), variant( expected_value ) );
    }
    move_conditional_format_rank_command( *s, 2, 1, ws2, ranges ).execute();
    {
        style_set_type tmp_style_set;
        tmp_style_set.combine( style_set_type::unserialize( style_yellow_fg  ) );
        tmp_style_set.combine( style_set_type::unserialize( style_red_bg ) );
        tmp_style_set.combine( style_set_type::unserialize( style_blue_bg ) );
        variant::variant_array_type expected_value( 1, tmp_style_set.serialize() );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, one_point_range[0] ) ), variant( expected_value ) );
    }
    move_conditional_format_rank_command( *s, 2, 1, ws2, ranges ).execute();
    {
        style_set_type tmp_style_set;
        tmp_style_set.combine( style_set_type::unserialize( style_red_bg ) );
        tmp_style_set.combine( style_set_type::unserialize( style_yellow_fg ) );
        tmp_style_set.combine( style_set_type::unserialize( style_blue_bg  ) );
        variant::variant_array_type expected_value( 1, tmp_style_set.serialize() );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, one_point_range[0] ) ), variant( expected_value ) );
    }
    move_conditional_format_rank_command( *s, 3, 1, ws2, ranges ).execute();
    {
        style_set_type tmp_style_set;
        tmp_style_set.combine( style_set_type::unserialize( style_red_bg ) );
        tmp_style_set.combine( style_set_type::unserialize( style_blue_bg ) );
        tmp_style_set.combine( style_set_type::unserialize( style_yellow_fg ) );
        variant::variant_array_type expected_value( 1, tmp_style_set.serialize() );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, one_point_range[0] ) ), variant( expected_value ) );
    }
    move_conditional_format_rank_command( *s, 3, -1, ws2, ranges ).execute();
    {
        style_set_type tmp_style_set;
        tmp_style_set.combine( style_set_type::unserialize( style_red_bg ) );
        tmp_style_set.combine( style_set_type::unserialize( style_yellow_fg ) );
        tmp_style_set.combine( style_set_type::unserialize( style_blue_bg ) );
        variant::variant_array_type expected_value( 1, tmp_style_set.serialize() );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, one_point_range[0] ) ), variant( expected_value ) );
    }
}

BOOST_AUTO_TEST_CASE( test_stop_if_true )
{

    const std::string style_red_bg = "background:red;";
    const std::string style_blue_bg = "background:blue;";
    const std::string style_yellow_fg = "foreground:yellow;";

    variant operands = variant( variant::type_array );
    operands.array().push_back( 0.0 );
    set_conditional_format::selected_ranges_type ranges = one_point_range;

    ws2->select( s->selected() );
    //add all 3
    // this one should create id 2
    set_conditional_format_command( *s
                                    , set_cf_format( operands , "CELL_VALUE(>;1;)", style_red_bg, ranges ) ).execute();
    // this one should create id 3
    set_conditional_format_command( *s
                                    , set_cf_format( operands , "CELL_VALUE(>;1;)", style_blue_bg, ranges ) ).execute();
    // this one should create id 4
    set_conditional_format_command( *s
                                    , set_cf_format( operands , "CELL_VALUE(>;0;)", style_yellow_fg, ranges ) ).execute();

    set_value_command( *s, one_point_range[0], variant( 1.0 ) ).execute();

    {
        style_set_type tmp_style_set;
        tmp_style_set.combine( style_set_type::unserialize( style_blue_bg ) );
        tmp_style_set.combine( style_set_type::unserialize( style_yellow_fg ) );
        variant::variant_array_type expected_value( 1, tmp_style_set.serialize() );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, one_point_range[0] ) ), variant( expected_value ) );
    }
    move_conditional_format_rank_command( *s, 2, 1, ws2, ranges ).execute();
    {
        style_set_type tmp_style_set;
        tmp_style_set.combine( style_set_type::unserialize( style_red_bg ) );
        tmp_style_set.combine( style_set_type::unserialize( style_yellow_fg ) );
        variant::variant_array_type expected_value( 1, tmp_style_set.serialize() );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, one_point_range[0] ) ), variant( expected_value ) );
    }
    move_conditional_format_rank_command( *s, 2, 1, ws2, ranges ).execute();
    {
        style_set_type tmp_style_set;
        tmp_style_set.combine( style_set_type::unserialize( style_red_bg ) );
        variant::variant_array_type expected_value( 1, tmp_style_set.serialize() );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, one_point_range[0] ) ), variant( expected_value ) );
    }
    move_conditional_format_rank_command( *s, 3, 1, ws2, ranges ).execute();
    {
        style_set_type tmp_style_set;
        tmp_style_set.combine( style_set_type::unserialize( style_red_bg ) );
        variant::variant_array_type expected_value( 1, tmp_style_set.serialize() );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, one_point_range[0] ) ), variant( expected_value ) );
    }
    move_conditional_format_rank_command( *s, 3, -1, ws2, ranges ).execute();
    {
        style_set_type tmp_style_set;
        tmp_style_set.combine( style_set_type::unserialize( style_red_bg ) );
        variant::variant_array_type expected_value( 1, tmp_style_set.serialize() );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, one_point_range[0] ) ), variant( expected_value ) );
    }
}

BOOST_AUTO_TEST_CASE( test_locked_cells )
{

    shared_worksheet_type other_sheet = ws1->parent()->add( "other_sheet" );
    variant operands = variant( variant::type_array );
    operands.array().push_back( 0.0 );

    set_conditional_format_command( *s
                                    , set_conditional_format(
                                        variant( 0.0 )
                                        , "CELL_VALUE(>;1;)"
                                        , style_str
                                        , real_range, true, set_conditional_format::border_map_type() ) ).execute();

    {

        variant::sparse_array_type expected_result( 1, false );
        BOOST_CHECK_EQUAL( execute_fetch( get_server_query_command( *s, A1, get_server_query_command::query_lock ) ), variant( expected_result ) );
    }
    set_value_command( *s, A1, variant( 1.0 ) ).execute();
    {

        variant::sparse_array_type expected_result( 1, true );
        BOOST_CHECK_EQUAL( execute_fetch( get_server_query_command( *s, A1, get_server_query_command::query_lock ) ), variant( expected_result ) );
    }
}

BOOST_AUTO_TEST_CASE( test_insert_one_column )
{
    variant operands = variant( variant::type_array );
    operands.array().push_back( "=a1" );
    const sheet_range range_to_use( sheet_point( 1, 1 ), sheet_point( 2, 2 ) );
    const sheet_range::rectangles_type r_list( 1, range_to_use );
    set_conditional_format_command( *s
                                    , set_cf_format(
                                        variant( 0.0 )
                                        , "CELL_VALUE(>;1;)"
                                        , style_str
                                        , r_list ) ).execute();

    const sheet_range B2 = sheet_range( sheet_point( 1, 1 ) );
    set_value_command( *s, A1, variant( 1.0 ) ).execute();
    set_value_command( *s, B2, variant( 2.0 ) ).execute();

    {
        variant::sparse_array_type expected_value( 1, style_str );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, B2 ) ), variant( expected_value ) );
    }
    insert_column_command( *s, 2, 1 ).execute();
    {
        variant::sparse_array_type expected_value( 1, style_str );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, B2 ) ), variant( expected_value ) );
    }
    {
        variant::sparse_array_type expected_value( 1, style_str );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, sheet_range( sheet_point( 1, 2 ) ) ) ), variant( expected_value ) );
    }
    set_value_command( *s, A1, variant( 2.0 ) ).execute();
    {
        variant::sparse_array_type expected_value( 1, style_str );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, B2 ) ), variant( expected_value ) );
    }
    {
        variant::sparse_array_type expected_value( 1, style_str );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, sheet_range( sheet_point( 1, 2 ) ) ) ), variant( expected_value ) );
    }

}

//TODO
BOOST_AUTO_TEST_CASE( test_insert_multiple_columns )
{
    variant operands = variant( variant::type_array );
    operands.array().push_back( "=a1" );

    const sheet_range range_to_use( sheet_point( 1, 1 ), sheet_point( 2, 2 ) );
    const sheet_range::rectangles_type r_list( 1, range_to_use );
    set_conditional_format_command( *s
                                    , set_cf_format(
                                        variant( 0.0 )
                                        , "CELL_VALUE(>;1;)"
                                        , style_str
                                        , r_list ) ).execute();

    const sheet_range B2 = sheet_range( sheet_point( 1, 1 ) );
    set_value_command( *s, A1, variant( 1.0 ) ).execute();
    set_value_command( *s, B2, variant( 2.0 ) ).execute();

    {
        variant::sparse_array_type expected_value( 1, style_str );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, B2 ) ), variant( expected_value ) );
    }
    insert_column_command( *s, 2, 5 ).execute();
    {
        variant::sparse_array_type expected_value( 1, "" );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, B2 ) ), variant( expected_value ) );
    }
    {
        variant::sparse_array_type expected_value( 1, "" );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, sheet_range( sheet_point( 1, 2 ) ) ) ), variant( expected_value ) );
    }
    set_value_command( *s, A1, variant( 2.0 ) ).execute();
    {
        variant::sparse_array_type expected_value( 1, "" );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, B2 ) ), variant( expected_value ) );
    }
    {
        variant::sparse_array_type expected_value( 1, "" );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, sheet_range( sheet_point( 1, 2 ) ) ) ), variant( expected_value ) );
    }

}

BOOST_AUTO_TEST_CASE( test_insert_row )
{
    variant operands = variant( variant::type_array );
    operands.array().push_back( "=a1" );

    const sheet_range range_to_use( sheet_point( 1, 1 ), sheet_point( 2, 2 ) );
    const sheet_range::rectangles_type r_list( 1, range_to_use );
    set_conditional_format_command( *s
                                    , set_cf_format(
                                        variant( 0.0 )
                                        , "CELL_VALUE(>;1;)"
                                        , style_str
                                        , r_list ) ).execute();

    const sheet_range B2 = sheet_range( sheet_point( 1, 1 ) );
    set_value_command( *s, A1, variant( 1.0 ) ).execute();
    set_value_command( *s, B2, variant( 2.0 ) ).execute();

    {
        variant::sparse_array_type expected_value( 1, style_str );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, B2 ) ), variant( expected_value ) );
    }
    insert_row_command( *s, 2, 1 ).execute();
    {
        variant::sparse_array_type expected_value( 1, style_str );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, B2 ) ), variant( expected_value ) );
    }
    {
        variant::sparse_array_type expected_value( 1, style_str );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, sheet_range( sheet_point( 1, 2 ) ) ) ), variant( expected_value ) );
    }
    set_value_command( *s, A1, variant( 2.0 ) ).execute();
    {
        variant::sparse_array_type expected_value( 1, style_str );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, B2 ) ), variant( expected_value ) );
    }
    {
        variant::sparse_array_type expected_value( 1, style_str );
        BOOST_CHECK_EQUAL( execute_fetch( get_style_command( *s, sheet_range( sheet_point( 1, 2 ) ) ) ), variant( expected_value ) );
    }

}
#endif

BOOST_AUTO_TEST_SUITE_END()
