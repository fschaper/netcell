/**
 *  \file
 *  Copyright (C) 2006-2010 Jedox AG, Freiburg i.Br., Germany
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
 *  Marko Stijak <marko.stijak@jedox.com>
 */

#include "css_utils.hpp"

namespace xlsx
{

    std::string css_utils::color2string( long color )
    {
        char c[16];
        // unused?
        //int rr = (color & 0x00FF0000);
        int r = ( color & 0x00FF0000 ) >> 16;
        int g = ( color & 0x0000FF00 ) >> 8;
        int b = ( color & 0x000000FF );
        sprintf( c, "#%02x%02x%02x", r, g, b );
        return c;
    }

    std::string css_utils::border( const std::string& side, const std::string& style, const std::string& thick, const long color )
    {
        std::stringstream ss;
        ss << "border-" << side << ": " << thick << " " << style;
        ss << " " << color2string( color );
        return ss.str();
    }

    std::string css_utils::border( const std::string& side, const std::string& style, const std::string& thick )
    {
        std::stringstream ss;
        ss << "border-" << side << ": " << thick << " " << style;
        return ss.str();
    }

    std::vector<std::string> css_utils::split_css_name_value( const std::string& combined )
    {

        size_t p = 0;
        size_t e = combined.size();
        std::vector<std::string> res;
        while ( p < e ) {
            size_t s = p;
            size_t c = combined.find( ":", p );
            while ( s < e && combined[s] == ';' ) {
                s++;
            }
            if ( c == ( size_t ) - 1 ) {
                break;
            }
            p = combined.find( ";", c + 1 );
            if ( p == ( size_t ) - 1 ) {
                p = e;
            }
            size_t i = 1;
            while ( ( p + i ) < e ) {
                if ( ':' == combined[p+i] ) {
                    break;
                } else if ( ';' == combined[p+i] ) {
                    p += i;
                    i = 1;
                }
                i++;
            }
            if ( c < p ) {
                res.push_back( trim_white( combined.substr( s, c - s ) ) );
                res.push_back( trim_white( combined.substr( c + 1, p - c - 1 ) ) );
            }
            ++p;
        }
        return res;
    }

    /// rgb(255, 255, 255) -> 0x00FFFFFF
    bool css_utils::parse_rgbcolor( const std::string& rgbs, long& color )
    {
        std::vector<std::string> elem = split( rgbs, " (),;" );
        if ( elem.size() != 4 || elem[0] != "rgb" ) {
            return false;
        }
        int r, g, b;
        if ( !parse( elem[1], r ) || !parse( elem[2], g ) || !parse( elem[3], b ) ) {
            return false;
        }
        if ( ( r & 255 ) != r || ( g & 255 ) != g || ( b & 255 ) != b ) {
            return false;
        }
        color = rgb( r, g, b );
        return true;
    }

    long css_utils::rgb( int r, int g, int b )
    {
        return ( r << 16 ) | ( g << 8 ) | b;
    }

    bool css_utils::parse_hexcolor( const std::string& rgbs, long& color )
    {
        if ( rgbs.length() < 4 || rgbs[0] != '#' ) {
            return false;
        }
        if ( rgbs.length() == 7 ) {
            int c;
            bool res = parse_hex( rgbs.substr( 1, 6 ), c );
            color = c;
            return res;
        }

        if ( rgbs.length() == 7 ) {
            int c;
            bool res = parse_hex( rgbs.substr( 1, 6 ), c );
            color = c;
            return res;
        }

        if ( rgbs.length() == 4 ) { //0xABC -> 0xAABBCC
            int c;
            bool res = parse_hex( rgbs.substr( 1, 6 ), c );
            c = ( c & 0xF ) | ( ( c & 0xF0 ) << 8 ) | ( ( c & 0xF00 ) << 16 );
            color = c | c << 8;
            return res;
        }

        return false;
    }

    bool css_utils::parse_color( const std::string& colors, long& color )
    {
        if ( colors.find_first_of( "#" ) == 0 ) {
            return parse_hexcolor( colors, color );
        }
        if ( colors.find_first_of( "rgb" ) == 0 ) {
            return parse_rgbcolor( colors, color );
        }
        return false;
    }

    bool css_utils::parse_font_size( const std::string& size, double& pts )
    {
        if ( size.length() < 3 ) {
            return false;
        }
        std::string units = size.substr( size.length() - 2, 2 );
        if ( units == "pt" ) {
            pts = string2double( trim_white( size.substr( 0, size.length() - 2 ) ) );
            return true;
        }
        if ( units == "px" ) {
            double px = string2double( trim_white( size.substr( 0, size.length() - 2 ) ) );
            pts = 4 * px / 3;
            return true;
        }
        return false;
    }

    bool css_utils::parse_border_side( const std::string& css, int& width, std::string& type, optional<long>& color )
    {
        std::vector<std::string> parts = split( css, " ;" );
        if ( parts.size() < 2 ) {
            return false;
        }
        int s = ( int )parts[0].size();
        while ( s > 0 && !isdigit( parts[0][s-1] ) ) {
            --s;
        }
        if ( !parse( parts[0].substr( 0, s ), width ) ) {
            return false;
        }
        type = parts[1];
        long c;
        if ( parts.size() > 2 )
            if ( parse_color( parts[2], c ) ) {
                color.getset() = c;
            }
        return true;
    }
}
