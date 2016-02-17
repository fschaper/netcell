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

#include "precompiled_header.hpp"
#include "wss/a1conversion.hpp"

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
# include <cmath>
#pragma warning( push )
#pragma warning( disable : 4267 )
# include <boost/lexical_cast.hpp>
# include <boost/regex.hpp>
#pragma warning( pop )
#endif

namespace a1conversion
{

    unsigned int from_a1::column( const std::string& column )
    {
        unsigned int retval = 0;

        if ( false == column.empty() ) {
            const std::string::size_type length = column.size();

            for ( std::string::size_type cursor = 0; cursor < length; ++cursor ) {
                if ( ( length - cursor ) > 1  ) {
                    // calculate every character that is a multiple of 26, f.ex. in "IV", "I" (character 9) needs to be
                    // multiplied with 26 since AA, BA, CA, ... are it's predecessors.
                    retval += static_cast<unsigned int>(
                                  ( column[cursor] < 97 ) ?
                                  ( column[cursor] - 64 ) * std::pow( static_cast<float>( 26 ), static_cast<int>( length - cursor - 1 ) )    // character is in the range from A-Z
                                  : ( column[cursor] - 96 ) * std::pow( static_cast<float>( 26 ), static_cast<int>( length - cursor - 1 ) ) ); // character is from a-z
                } else {
                    // here we add only the last single digit remainder
                    retval += ( column[cursor] < 97 ) ? ( column[cursor] - 64 ) : ( column[cursor] - 96 );
                }
            }
        }

        return ( retval - 1 );
    }

    sheet_point from_a1::cell( const std::string& a1 )
    {
        const std::string a1_notation( boost::erase_all_copy( a1, "$" ) );
        std::string column_string( boost::trim_right_copy_if( a1_notation, boost::is_digit() ) );
        std::string row_string( boost::trim_left_copy_if( a1_notation, boost::is_alpha() ) );
        sheet_point::integer_type column = ( column_string.size() > 0 ) ? from_a1::column( column_string ) : sheet_dimension::max_column;
        sheet_point::integer_type row = ( row_string.size() > 0 ) ? ( boost::lexical_cast<sheet_point::integer_type>( row_string ) - 1 ) : sheet_dimension::max_row;
        return sheet_point( row, column );
    }

    sheet_range from_a1::range( const std::string& a1 )
    {
        static sheet_range default_range( sheet_point( 0, 0 ) );
        size_t pos = a1.find( ':' );
        if ( pos != std::string::npos ) {
            size_t end = a1.find( ',' );
            return sheet_range( cell( a1.substr( 0, pos ) ), cell( std::string( a1.begin() + pos + 1, end != a1.npos ? a1.begin() + end : a1.end() ) ) );
        }
        return default_range;
    }

    multi_rect_vector_type from_a1::ranges( const std::string& a1 )
    {
        typedef std::vector<std::string> split_vector_type;
        multi_rect_vector_type return_value;

        // remove whitespace from string
        const std::string a1_notation( boost::erase_all_copy( a1, " " ) );

        // separate ranges of the form "a1:a12,b1:c44,d31,e1" => "a1:a12","b1:c44", "d31", ...
        split_vector_type multi_ranges;
        boost::split( multi_ranges, a1_notation, boost::is_from_range( ',', ',' ) );

        // iterate for every range found
        split_vector_type::const_iterator range_it( multi_ranges.begin() );
        split_vector_type::const_iterator range_it_end( multi_ranges.end() );

        for ( ; range_it != range_it_end; ++range_it ) {
            // separate a range into it's cell parts "a1:a12" => "a1","a12"
            split_vector_type cells;
            boost::split( cells, *range_it, boost::is_from_range( ':', ':' ) );

            typedef boost::find_iterator<std::string::iterator> string_find_iterator_type;
            string_find_iterator_type find_iterator;
            static const unsigned int IS_RANGE = 2;
            static const unsigned int IS_SINGLE_CELL = 1;

            switch ( cells.size() ) {

                case IS_RANGE:
                    return_value.push_back( sheet_range( from_a1::cell( cells[0] ), from_a1::cell( cells[1] ) ) );
                    break;

                case IS_SINGLE_CELL:
                    return_value.push_back( sheet_range( from_a1::cell( cells[0] ) ) );
                    break;

                default:
                    assert( !"Invalid character string passed to A1 conversion" );
            }
        }

        return return_value;
    }

    std::string to_a1::from_point( const sheet_point& p )
    {
        return column( p.column(), p.type() ).append( row( p.row(), p.type() ) );
    }

    inline reference::type get_correct_reference_type( const reference::type current, const reference::type to_check )
    {
        if ( ( current & to_check )  == to_check ) {
            return to_check;
        }
        return reference::relative;
    }

    std::string to_a1::from_range( const sheet_range& p )
    {
        if ( ( 0 == p.upper_left().column() ) && ( sheet_dimension::max_column == ( unsigned int ) p.lower_right().column() ) ) {
            //have here full rows.
            return row( p.upper_left().row(), get_correct_reference_type( p.upper_left().type(), reference::absolute_row ) ).append( ":" ).append( row( p.lower_right().row(), get_correct_reference_type( p.lower_right().type(), reference::absolute_row ) ) );
            //have here full cols.
        } else if ( ( 0 == p.upper_left().row() ) && ( sheet_dimension::max_row == ( unsigned int ) p.lower_left().row() ) ) {
            return column( p.upper_left().column(), get_correct_reference_type( p.upper_left().type(), reference::absolute_column ) ).append( ":" ).append( column( p.lower_right().column(), get_correct_reference_type( p.lower_right().type(), reference::absolute_column ) ) );
        }
        return from_point( p.upper_left() ).append( ":" ).append( from_point( p.lower_right() ) );
    }

    std::string to_a1::column( unsigned int column, reference::type ref )
    {

        static const unsigned int base = 26;

        std::string column_string;
        column_string.reserve( 4 );
        while ( true  ) {

            column_string.insert( column_string.begin() , static_cast<char>( ( ( column ) % base ) + 'A' ) );

            column /= base;
            if ( column == 0 ) {
                break;
            }
            --column;
        }

        if ( ( ref & reference::absolute_column ) == reference::absolute_column ) {
            column_string.insert( column_string.begin() , '$' );
        }

        return column_string;

    }

    std::string to_a1::row( unsigned int row, reference::type ref )
    {
        std::string row_string;
        row_string.reserve( 7 );

        if ( ( ref & reference::absolute_row ) == reference::absolute_row ) {
            row_string.push_back( '$' );
        }

        return row_string.append( boost::lexical_cast<std::string>( row + 1 ) );
    }

    bool to_a1::needs_quotes( const utf8_ci_string& name )
    {
        static const boost::regex quote_test( "[[:alpha:]]+([[:alnum:]]|[_])*", boost::regex::perl );
        return boost::regex_match( convert_utf8_ci( name ), quote_test ) == false;
    }

    const int formatting::m_a1_stream_ident = std::ios_base::xalloc();


    formatting::formatting( type format )
        : m_format( format )
    {}

    formatting::type formatting::format() const
    {
        return m_format;
    }

    formatting& formatting::as_a1()
    {
        static formatting a1_format( a1 );
        return a1_format;
    }

    formatting& formatting::as_numeric()
    {
        static formatting numeric_format( numeric );
        return numeric_format;
    }

    int formatting::allocator()
    {
        return m_a1_stream_ident;
    }
}
