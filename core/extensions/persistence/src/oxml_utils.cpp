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

#include "oxml_utils.hpp"

#include <map>

namespace xlsx
{

    bool oxml_utils::parse_sheet_reference( const std::string& ref, std::string& sheet, int& c, int& r )
    {
        std::vector<std::string> p = split( ref, "!" );
        if ( p.size() != 2 ) {
            return false;
        }
        sheet = p[0];
        return parse_reference( p[1], c, r );
    }

    bool oxml_utils::parse_reference( const std::string& ref, int& c, int& r )
    {
        r = 0;
        c = 0;
        for ( size_t i = 0; i < ref.size(); i++ )
            if ( ref[i] == '$' ) {
                continue;
            } else if ( isdigit( ref[i] ) ) {
                r = r * 10 + ref[i] - '0';
            } else {
                c = c * 26 + ref[i] - 'A' + 1;
            }
        --c;
        return c >= 0 && r > 0;
    }

    bool oxml_utils::parse_range( const std::string& ref, int& c1, int& r1, int& c2, int& r2 )
    {
        std::vector<std::string> p = split( ref, ":" );
        if ( p.size() != 2 ) {
            return false;
        }
        if ( !parse_reference( p[0], c1, r1 ) ) {
            return false;
        }
        if ( !parse_reference( p[1], c2, r2 ) ) {
            return false;
        }
        return true;
    }
    std::string oxml_utils::cell_reference( int col, int row )
    {
        std::stringstream res;
        while ( row > 0 ) {
            res << ( char )( '0' + row % 10 );
            row /= 10;
        }
        col++;
        do {
            col--;
            res << ( char )( 'A' + col % 26 );
            col /= 26;
        } while ( col > 0 );
        std::string s = res.str();
        std::reverse( s.begin(), s.end() );
        return s;
    }
    std::string oxml_utils::range2string( int col1, int row1, int col2, int row2 )
    {
        return cell_reference( col1, row1 ) + ":" + cell_reference( col2, row2 );
    }
    int oxml_utils::pt2px( const double& d )
    {
        return ( int )( d * 1.333333333 + 0.4999999 );
    }
    double oxml_utils::px2pt( int d )
    {
        return d / 1.333333333;
    }

    char oxml_utils::char2hex( char c )
    {
        if ( islower( c ) ) {
            if ( c >= 'a' ) {
                return 10 + c - 'a';
            }
        } else if ( c >= 'A' ) {
            return 10 + c - 'A';
        }
        return c - '0';
    }

    long oxml_utils::string2color( const std::string& s )
    {
        long v = 0;
        // unused?
        //int l = s.length();
        int i = 0;
        for ( std::string::const_reverse_iterator it = s.rbegin(); it != s.rend(); it++ ) {
            v |= char2hex( *it ) << ( 4 * i );
            i++;
        }
        return v & 0x00FFFFFF;
    }

    long oxml_utils::rgb( int r, int g, int b )
    {
        return ( r << 16 ) | ( g << 8 ) | b;
    }

    long oxml_utils::tint( long c, double t )
    {
        if ( t == 0 ) {
            return c;
        }
        double h, l, s;
        color2hls( c, h, l, s );
        if ( t < 0 ) {
            l = l * ( 1 + t );
        } else {
            l = l + ( 1 - l ) * t;
        }
        return hls2color( h, l, s );

        //aprox method
        //return t == 0 ? c : rgb(tint_part((l & 0xFF0000) >> 16,t), tint_part((l & 0x00FF00) >> 8,t), tint_part(l & 0xFF,t));
    }

    int oxml_utils::tint_part( int c, double t )
    {
        return static_cast<int>( ( t < 0 ) ? ( c * ( 1 + t ) + 0.499999999 ) : ( 0.499999999 + c + t * ( 255 - c ) ) );
    }

    long oxml_utils::color( int index )
    {
        switch ( index ) {
            case 0:
                return 0x00000000;
            case 1:
                return 0x00FFFFFF;
            case 2:
                return 0x00FF0000;
            case 3:
                return 0x0000FF00;
            case 4:
                return 0x000000FF;
            case 5:
                return 0x00FFFF00;
            case 6:
                return 0x00FF00FF;
            case 7:
                return 0x0000FFFF;
            case 8:
                return 0x00000000;
            case 9:
                return 0x00FFFFFF;
            case 10:
                return 0x00FF0000;
            case 11:
                return 0x0000FF00;
            case 12:
                return 0x000000FF;
            case 13:
                return 0x00FFFF00;
            case 14:
                return 0x00FF00FF;
            case 15:
                return 0x0000FFFF;
            case 16:
                return 0x00800000;
            case 17:
                return 0x00008000;
            case 18:
                return 0x00000080;
            case 19:
                return 0x00808000;
            case 20:
                return 0x00800080;
            case 21:
                return 0x00008080;
            case 22:
                return 0x00C0C0C0;
            case 23:
                return 0x00808080;
            case 24:
                return 0x009999FF;
            case 25:
                return 0x00993366;
            case 26:
                return 0x00FFFFCC;
            case 27:
                return 0x00CCFFFF;
            case 28:
                return 0x00660066;
            case 29:
                return 0x00FF8080;
            case 30:
                return 0x000066CC;
            case 31:
                return 0x00CCCCFF;
            case 32:
                return 0x00000080;
            case 33:
                return 0x00FF00FF;
            case 34:
                return 0x00FFFF00;
            case 35:
                return 0x0000FFFF;
            case 36:
                return 0x00800080;
            case 37:
                return 0x00800000;
            case 38:
                return 0x00008080;
            case 39:
                return 0x000000FF;
            case 40:
                return 0x0000CCFF;
            case 41:
                return 0x00CCFFFF;
            case 42:
                return 0x00CCFFCC;
            case 43:
                return 0x00FFFF99;
            case 44:
                return 0x0099CCFF;
            case 45:
                return 0x00FF99CC;
            case 46:
                return 0x00CC99FF;
            case 47:
                return 0x00FFCC99;
            case 48:
                return 0x003366FF;
            case 49:
                return 0x0033CCCC;
            case 50:
                return 0x0099CC00;
            case 51:
                return 0x00FFCC00;
            case 52:
                return 0x00FF9900;
            case 53:
                return 0x00FF6600;
            case 54:
                return 0x00666699;
            case 55:
                return 0x00969696;
            case 56:
                return 0x00003366;
            case 57:
                return 0x00339966;
            case 58:
                return 0x00003300;
            case 59:
                return 0x00333300;
            case 60:
                return 0x00993300;
            case 61:
                return 0x00993366;
            case 62:
                return 0x00333399;
            case 63:
                return 0x00333333;
            case 64:
                return 0x00000000;
            case 65:
                return 0x00FFFFFF;
            default:
                return 0x00000000;
        }
    }

    std::string oxml_utils::format_code( size_t id, bool defaultToGeneral )
    {
        switch ( id ) {
            case 0:
                return  "General";
            case 1:
                return  " 0";
            case 2:
                return  " 0.00";
            case 3:
                return  " #,##0";
            case 4:
                return  " #,##0.00";
            case 9:
                return  " 0%";
            case 10 :
                return  "0.00%";
            case 11 :
                return  "0.00E+00";
            case 12 :
                return  "# ?/?";
            case 13 :
                return  "# ?\?/??";
            case 14 :
                return  "mm-dd-yy";
            case 15 :
                return  "d-mmm-yy";
            case 16 :
                return  "d-mmm";
            case 17 :
                return  "mmm-yy";
            case 18 :
                return  "h:mm AM/PM";
            case 19 :
                return  "h:mm:ss AM/PM";
            case 20 :
                return  "h:mm";
            case 21 :
                return  "h:mm:ss";
            case 22 :
                return  "m/d/yy h:mm";
            case 37 :
                return  "#,##0 ;(#,##0)";
            case 38 :
                return  "#,##0 ;[Red](#,##0)";
            case 39 :
                return  "#,##0.00;(#,##0.00)";
            case 40 :
                return  "#,##0.00;[Red](#,##0.00)";
            case 45 :
                return  "mm:ss";
            case 46 :
                return  "[h]:mm:ss";
            case 47 :
                return  "mmss.0";
            case 48 :
                return  "##0.0E+0";
            case 49 :
                return  "@";
        }
        return defaultToGeneral ? "General" : "";
    }

    int oxml_utils::format_id( std::string id )
    {
        static std::map<std::string, int> m;
        if ( m.empty() )
            for ( int i = 0; i < 50; i++ ) {
                std::string code = format_code( i, false );
                if ( !code.empty() ) {
                    m[code] = i;
                }
            }
        std::map<std::string, int>::iterator it = m.find( id );
        if ( it != m.end() ) {
            return it->second;
        }
        return -1;
    }

    void oxml_utils::color2hls( long c, double& h, double& l, double& s )
    {
        int r = ( c & 0xFF0000 ) >> 16;
        int g = ( c & 0xFF00 ) >> 8;
        int b = ( c & 0xFF );

        int mx = std::max( r, std::max( g, b ) );
        int mn = std::min( r, std::min( g, b ) );

        if ( mx == mn ) {
            h = 0;
        } else if ( mx == r ) {
            h = ( g - b ) * 60.0 / ( mx - mn ) + ( b > g ? 360 : 0 );
        } else if ( mx == g ) {
            h = ( b - r ) * 60.0 / ( mx - mn ) + 120;
        } else if ( mx == b ) {
            h = ( r - g ) * 60.0 / ( mx - mn ) + 240;
        }
        l = ( mx + mn ) / ( 2 * 255.0 );
        if ( mx == mn ) {
            s = 0;
        } else if ( l <= 0.5 ) {
            s = ( mx - mn ) * 1.0 / ( mx + mn );
        } else {
            s = ( mx - mn ) / ( 2.0 * 255 - mx - mn );
        }
    }
    long oxml_utils::hls2color( double h, double l, double s )
    {
        double q = ( l < 0.5 ) ? l * ( 1 + s ) : l + s - s * l;
        double p = 2 * l - q;
        double hk = h / 360.0;
        double t[3];
        t[0] = hk + 1 / 3.0;
        t[1] = hk;
        t[2] = hk - 1 / 3.0;
        double c[3];
        for ( int i = 0; i < 3; i++ ) {
            if ( t[i] > 1 ) {
                t[i] -= 1;
            }
            if ( t[i] < 0 ) {
                t[i] += 1;
            }
            if ( 6 * t[i] < 1 ) {
                c[i] = p + ( ( q - p ) * 6 * t[i] );
            } else if ( 2 * t[i] < 1 ) {
                c[i] = q;
            } else if ( 3 * t[i] < 2 ) {
                c[i] = p + ( ( q - p ) * 6 * ( 2 / 3.0 - t[i] ) );
            } else {
                c[i] = p;
            }
        }
        return rgb( ( int )( c[0] * 255 + 0.49999 ), ( int )( c[1] * 255 + 0.49999 ), ( int )( c[2] * 255 + 0.49999 ) );
    }

    void oxml_utils::split_ranges( const std::string& in_ranges, std::vector< std::string >& out_range )
    {
        std::vector<std::string> p = split( in_ranges, "," );

        for ( std::vector<std::string>::const_iterator i = p.begin(); i != p.end(); i++ ) {
            std::string crt( "" );
            for ( size_t j = 0; j < i->size(); j++ ) {
                if ( '$' != ( *i )[j] ) {
                    crt += ( *i )[j];
                }
            }
            if ( ! crt.empty() ) {
                out_range.push_back( crt );
            }
        }
    }

    const std::string oxml_utils::color2hex( long color )
    {
        char        buf[8];
        buf[0] = '#';
        unsigned char converter = ( unsigned char )( ( color & 0x00FF0000 ) >> 16 );
        sprintf( buf + 1, "%02X", converter );
        converter = ( unsigned char )( ( color & 0x0000FF00 ) >> 8 );
        sprintf( buf + 3, "%02X", converter );
        converter =  ( unsigned char )( color & 0x000000FF );
        sprintf( buf + 5, "%02X", converter );
        buf[7] = 0;

        return buf;
    }

} //ns xlsx
