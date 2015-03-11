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
 *  Radu Ialovoi <ialovoi@yalos-solutions.com>
 */

#include "paste_view_adapter.hpp"
#include "oxml_utils.hpp"
#include <boost/lexical_cast.hpp>

#ifdef _MSC_VER
//inflate/deflate algorithms introduced through minizip
#ifdef _DEBUG
#define BOOST_ZLIB_BINARY "libminizip_d.lib"
#else
#define BOOST_ZLIB_BINARY "libminizip.lib"
#endif
#endif

#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/detail/config/zlib.hpp>
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/tokenizer.hpp>

namespace xlsx
{

    paste_view_adapter::paste_view_adapter( shared_strings& strings, const sml::CT_Workbook& in_book, const utf8_ci_string& sheet_name ) :
        m_state( ds_idle ),
        m_max_row( 0 ),
        m_max_col( 0 ),
        m_strings( strings ),
        m_fixed_width( "-1" )
    {
        if ( !in_book.definedNames.present() ) {
            return;
        }
        bool print_area_present = false;
        for ( std::vector<sml::CT_DefinedName>::const_iterator it = in_book.definedNames.get().definedName.begin(); it != in_book.definedNames.get().definedName.end(); ++it ) {
            if ( !it->localSheetId.present() ) {
                return;
            }
            const sml::CT_Sheet& sh = in_book.sheets.sheet.at( it->localSheetId.get() );
            if ( "_palopasteviewcolwidth" == it->name.get() && sheet_name == sh.name.get() ) {
                m_fixed_width = it->get();
            }
        }
    }

    bool paste_view_adapter::active()
    {
        return ds_fail != m_state;
    }

    paste_view_adapter::detection_state paste_view_adapter::advance_from_idle( const int row, const int col, const sml::CT_Cell& cell )
    {
        //this detects an "foo/bar" string.
        if ( 0 == row && 0 == col ) {
            if ( cell.t != sml::ST_CellType::s_literal || !cell.v.present() ) {
                return ds_fail;
            } else {
                const std::string label = m_strings.at( oxml_utils::string2int( cell.v.get() ) );
                size_t div_pos = label.find( '/' );
                if ( std::string::npos != div_pos ) {
                    m_connection = label.substr( 0, div_pos );
                    m_database = label.substr( div_pos + 1, label.size() );
                    return ds_data_source;
                } else {
                    return ds_fail;
                }
            }
        }
        return ds_idle;
    }

    paste_view_adapter::detection_state paste_view_adapter::advance_from_data_source( const int row, const int col, const sml::CT_Cell& cell )
    {
        //this detects a string literal.
        if ( 1 == row && 0 == col ) {
            if ( cell.t != sml::ST_CellType::s_literal || !cell.v.present() ) {
                return ds_fail;
            } else {
                m_cube = m_strings.at( oxml_utils::string2int( cell.v.get() ) );
                return ds_cube;
            }
        }
        return ds_data_source;
    }

    paste_view_adapter::detection_state paste_view_adapter::advance_from_cube( const int row, const int col, const sml::CT_Cell& cell )
    {
        //this logs ename calls
        if ( !cell.f.present() ) {
            return m_state;
        }
        if ( cell.f.get().t != sml::ST_CellFormulaType::normal_literal ) {
            return m_state;
        }
        const std::string fname = cell.f.get();

        if ( fname.substr( 0, 16 ) == "_xll.PALO.ENAME(" ) {
            if ( m_max_row < ( unsigned int )row ) {
                m_max_row = row;
            }
            if ( m_max_col < ( unsigned int )col ) {
                m_max_col = col;
            }
            m_enames.push_back( ename_with_pos( fname, row, col ) );
        }

        return ds_axes;
    }

    void paste_view_adapter::visit( const int row, const int col, const sml::CT_Cell& cell )
    {
        switch ( m_state ) {
            case ds_idle:
                m_state =  advance_from_idle ( row, col, cell );
                break;
            case ds_data_source:
                m_state =  advance_from_data_source ( row, col, cell );
                break;
            case ds_cube:
            case ds_axes:
                m_state =  advance_from_cube ( row, col, cell );
                break;
            default:
                break;
        }
    }


    bool paste_view_adapter::validate()
    {
        if ( m_state != ds_axes ) {
            return false;
        }

        std::vector< unsigned int > column_0;
        column_0.push_back( 1 );

        for ( unsigned int row = 2; row <= m_max_row ; row++ ) {
            std::vector< ename_with_pos >::const_iterator match = std::find_if( m_enames.begin(), m_enames.end(), match_point( row, 0 ) );
            if ( match != m_enames.end() ) {
                column_0.push_back( row );
            }
        }

        if ( column_0.size() < 2 ) {
            return false;
        }

        unsigned int y_axis_pos = 0;                        //this is on colummn 0
        unsigned int x_axis_count = 0;

        m_right = 0;
        m_bottom = 0;

        for ( size_t i = 1; i < column_0.size(); i++ ) {
            if ( column_0[i] != column_0[i-1] + 1 ) {
                y_axis_pos = column_0[i];
                x_axis_count = column_0[i] - column_0[i-1] - 2;
                break;
            }
        }

        if ( 0 == y_axis_pos ) {
            return false;
        }

        unsigned int y_axis_count = 1;
        for ( unsigned int col = 1; ; col++ ) {
            if ( std::find_if( m_enames.begin(), m_enames.end(), match_point( y_axis_pos, col ) ) != m_enames.end() ) {
                y_axis_count++;
            } else {
                break;
            }
        }

        for ( unsigned int x = 0; x < x_axis_count; x++ ) {
            std::vector< ename_with_pos >   axis;
            for ( unsigned int col = y_axis_count; col <= m_max_col; col++ ) {
                std::vector< ename_with_pos >::const_iterator crt = std::find_if( m_enames.begin(), m_enames.end(), match_point( y_axis_pos - x_axis_count + x , col ) );
                if (  crt != m_enames.end() ) {
                    axis.push_back( *crt );
                    if ( m_right < col ) {
                        m_right = col;
                    }
                }
            }
            if ( axis.empty() ) {
                return false;
            }
            m_x_axis.push_back( axis );
        }

        for ( unsigned int y = 0; y < y_axis_count; y++ ) {
            std::vector< ename_with_pos >   axis;
            for ( unsigned int row = y_axis_pos; row <= m_max_row; row++ ) {
                std::vector< ename_with_pos >::const_iterator crt = std::find_if( m_enames.begin(), m_enames.end(), match_point( row , y ) );
                if (  crt != m_enames.end() ) {
                    axis.push_back( *crt );
                    if ( m_bottom < row ) {
                        m_bottom = row;
                    }
                }
            }
            if ( axis.empty() ) {
                return false;
            }
            m_y_axis.push_back( axis );
        }

        for ( unsigned i = 2; i < y_axis_pos; i++ ) {
            std::vector< ename_with_pos >::const_iterator crt = std::find_if( m_enames.begin(), m_enames.end(), match_point( i , 0 ) );
            if (  crt != m_enames.end() ) {
                m_page.push_back( *crt );
            }
        }

        return true;
    }

    const std::string paste_view_adapter::quote( const std::string& label )
    {
        return "s:" + boost::lexical_cast < std::string >( label.size() ) + ":\"" + label + "\"";
    }

    const std::string paste_view_adapter::serialize_label( const ename_with_pos& label )
    {
        static const std::string empty = "a:0:{}";
        std::string text = label.name;
        size_t first = text.find( '"' );
        if ( std::string::npos == first ) {
            return empty;
        }
        size_t second = text.find( '"', first + 1 );
        if ( std::string::npos == second ) {
            return empty;
        }
        size_t third = text.find( '"', second + 1 );
        if ( std::string::npos == third ) {
            return empty;
        }
        if ( std::string::npos == first ) {
            return empty;
        }
        return "a:2:{i:0;" + quote( text.substr( first + 1, second - first - 1 ) ) + ";i:1;N;}";
    }

    const std::string paste_view_adapter::serialize_pages( const std::vector< ename_with_pos >& axis )
    {
        std::string result = "a:" + boost::lexical_cast < std::string >( axis.size() ) + ":{";
        for ( size_t i = 0; i < axis.size(); i++ ) {
            result += "i:";
            result += boost::lexical_cast < std::string >( i );
            result += ";";
            result += serialize_label( axis[i] );
        }
        return result + "}";
    }


    const std::string paste_view_adapter::serialize_axis( const std::vector< std::vector< ename_with_pos > >& meta_axis )
    {
        //don't have empty
        std::vector< std::string > previous_list;

        std::string result = "a:" + boost::lexical_cast < std::string >( meta_axis.size() ) + ":{";
        for ( size_t cnt = 0; cnt < meta_axis.size(); cnt++ ) {
            result +=  "i:";
            result += boost::lexical_cast < std::string >( cnt );
            result += ";a:2:{i:0;";
            previous_list.clear();

            std::string header;
            std::string content;
            header.clear();
            content.clear();
            for ( size_t i = 0; i < meta_axis[cnt].size(); i++ ) {
                std::string text = meta_axis[cnt][i].name;

                if ( previous_list.end() != std::find( previous_list.begin(), previous_list.end(), text ) ) {
                    break;
                }
                previous_list.push_back( text );


                size_t first = text.find( '"' );
                if ( std::string::npos == first ) {
                    continue;
                }
                size_t second = text.find( '"', first + 1 );
                if ( std::string::npos == second ) {
                    continue;
                }
                size_t third = text.find( '"', second + 1 );
                if ( std::string::npos == third ) {
                    continue;
                }
                size_t fourth = text.find( '"', third + 1 );
                if ( std::string::npos == first ) {
                    continue;
                }

                if ( 0 == i ) {
                    header += quote( text.substr( first + 1, second - first - 1 ) );
                    header += ";i:1;a:";
                }

                content += "i:";
                content += boost::lexical_cast < std::string >( i );
                content += ";a:3:{i:0;";
                content += quote( text.substr( third + 1, fourth - third - 1 ) );
                content += ";i:1;N;i:2;";
                switch ( text[ fourth + 2 ] ) {
                    case '3':
                        content += "s:1:\"C\";";
                        break;
                    default:
                        content += "s:0:\"\";";
                        break;
                }

                content += "}";
            }
            header += boost::lexical_cast < std::string >( previous_list.size() );
            header += ":{";

            result += header;
            result += content;
            result += "}}";
        }
        return result += "}";
    }

    const std::string& paste_view_adapter::serialize()
    {
        m_payload = std::string( "a:2:{i:0;a:4:{i:0;i:1;i:1;i:1;i:2;i:" ) +
                    boost::lexical_cast < std::string >( m_max_col + 2 ) + ";i:3;i:" +
                    boost::lexical_cast < std::string >( m_max_row + 2 ) + ";}i:1;a:4:{i:0;a:14:{i:0;i:1;i:1;i:" + boost::lexical_cast < std::string >( m_page.size() + 3 ) + ";i:2;" +
                    quote( m_connection ) + ";i:3;" +
                    quote( m_database ) + ";i:4;" +
                    quote( m_cube ) + ";i:5;b:1;i:6;i:" + m_fixed_width + ";i:7;b:1;i:8;b:0;i:9;i:0;i:10;b:0;i:11;a:0:{}i:12;b:0;i:13;b:0;}i:1;" +
                    serialize_pages( m_page ) + "i:2;" +
                    serialize_axis( m_x_axis ) + "i:3;" +
                    serialize_axis( m_y_axis ) + "}}";

#ifdef _DEBUG
        std::ofstream x( "C:\\log\\me.txt" );

        x << m_payload;

        x.flush();

        x.close();
#endif

        return m_payload;
    }

    const variant& paste_view_adapter::encoded_payload()
    {
        using namespace boost::iostreams;
        using namespace boost::archive::iterators;

        serialize();

        std::stringstream input_stream;
        input_stream << m_payload;

        filtering_streambuf< input > binary_input;
        binary_input.push( zlib_compressor() );
        binary_input.push( input_stream );

        std::stringstream compressed_output;
        copy( binary_input, compressed_output );

        std::string payload = compressed_output.str();

        typedef
        base64_from_binary  <
        transform_width <    std::string::iterator, 6, sizeof( char ) * 8  >
        >   base64_t;

        switch ( payload.length() % 3 ) {
            case 1:
                payload += char ( 0 );
            case 2:
                payload += char ( 0 );
            default:
                break;
        }


        m_encoded_payload = variant( std::string( base64_t( payload.begin() ), base64_t( payload.end() ) ) );

        return m_encoded_payload;
    }

    const std::string paste_view_adapter::location()
    {
        const sheet_point   top_left = sheet_point( m_page.size() + 2, 0, reference::absolute );
        const sheet_point   botom_right( m_max_row, m_max_col, reference::absolute );

        std::string result =  "=" + a1conversion::to_a1::from_range( sheet_range( top_left, botom_right ) );
        for ( size_t i = 0; i < m_page.size() + 2; i++ ) {
            result = result + "," + a1conversion::to_a1::from_point( sheet_point( i, 0, reference::absolute ) );
        }

        return result;
    }

    const sheet_range paste_view_adapter::pivot()
    {
        const sheet_point   top_left = sheet_point( m_page.size() + 3, 0, reference::absolute );

        unsigned int row;
        if ( 0 == m_x_axis.size() ) {
            row = m_page.size() + 3;
        } else {
            row = m_page.size() + 3 + m_x_axis.size() - 1;
        }

        unsigned int col;
        if ( 0 == m_y_axis.size() ) {
            col = 0;
        } else {
            col = m_y_axis.size() - 1;
        }

        const sheet_point   botom_right( row, col, reference::absolute );

        return sheet_range( top_left, botom_right );
    }

    const std::vector< sheet_point > paste_view_adapter::enames() const
    {
        std::vector< sheet_point > result;

        for ( std::vector< std::vector< ename_with_pos >  >::const_iterator axis = m_x_axis.begin(); axis != m_x_axis.end(); ++axis ) {
            for ( std::vector< ename_with_pos >::const_iterator pos = axis->begin(); pos != axis->end(); ++pos ) {
                result.push_back( sheet_point( pos->row, pos->col ) );
            }
        }

        for ( std::vector< std::vector< ename_with_pos >  >::const_iterator axis = m_y_axis.begin(); axis != m_y_axis.end(); ++axis ) {
            for ( std::vector< ename_with_pos >::const_iterator pos = axis->begin(); pos != axis->end(); ++pos ) {
                result.push_back( sheet_point( pos->row, pos->col ) );
            }
        }

        for ( std::vector< ename_with_pos >::const_iterator pos = m_page.begin(); pos != m_page.end(); ++pos ) {
            result.push_back( sheet_point( pos->row, pos->col ) );
        }

        return result;
    }

}
