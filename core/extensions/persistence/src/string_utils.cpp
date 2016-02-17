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

#include "string_utils.hpp"

#include <cstdlib>

namespace xlsx
{

    int string_utils::string2int( const std::string& s )
    {
        return atoi( s.c_str() );
    }
    std::string string_utils::int2string( int i )
    {
        std::stringstream ss;
        ss << i;
        return ss.str();
    }
    double string_utils::string2double( const std::string& s )
    {
        return atof( s.c_str() );
    }

    bool string_utils::parse( const std::string& s, int& res )
    {
        res = 0;
        for ( size_t i = 0; i < s.length(); i++ )
            if ( isdigit( s[i] ) ) {
                res = res * 10 + s[i] - '0';
            } else {
                return false;
            }
        return true;
    }

    std::string string_utils::trim_white( const std::string& str )
    {
        int s = 0;
        int e = ( int )str.length();
        while ( s < e && str[s] == ' ' ) {
            s++;
        }
        while ( s < e && str[e-1] == ' ' ) {
            e--;
        }
        return str.substr( s, e - s );
    }

    std::vector<std::string> string_utils::split( const std::string& s, const std::string& delim, bool remove_empty_entries )
    {
        std::vector<std::string> res;
        size_t pp = 0;
        size_t p;
        while ( ( p = s.find_first_of( delim, pp ) ) != std::string::npos ) {
            if ( pp < p ) {
                res.push_back( s.substr( pp, p - pp ) );
            } else if ( !remove_empty_entries ) {
                res.push_back( std::string() );
            }
            pp = p + 1;
        }
        if ( pp < s.length() ) {
            res.push_back( s.substr( pp, s.length() - pp ) );
        }
        return res;
    }

    bool string_utils::parse_hex( const std::string& s, int& res )
    {
        res = 0;
        for ( size_t i = 0; i < s.length(); i++ ) {
            int v;
            if ( !parse_hex( s[i], v ) ) {
                return false;
            }
            res = ( res << 4 ) + v;
        }
        return true;
    }
    bool string_utils::parse_hex( char c, int& res )
    {
        if ( c >= 'a' ) {
            res = c - 'a' + 10;
        } else if ( c >= 'A' ) {
            res = c - 'A' + 10;
        } else {
            res = c - '0';
        }
        return ( res & 0xF ) == res;
    }

    bool string_utils::starts_with( const std::string& s, const std::string& with )
    {
        if ( s.size() < with.size() ) {
            return false;
        }
        for ( size_t i = 0; i < with.size(); i++ )
            if ( s[i] != with[i] ) {
                return false;
            }
        return true;
    }

    std::string string_utils::trim_start( const std::string& s, char c )
    {
        size_t i = 0;
        while ( i < s.size() && s[i] == c ) {
            i++;
        }
        return s.substr( i );
    }

    std::string string_utils::combine( const ssmap& m )
    {
        std::stringstream       ss;
        ssmap::const_iterator   it;
        for ( it = m.begin(); it != m.end(); it++ ) {
            ss << it->first << ":" << it->second << ";";
        }
        return ss.str();
    }
}
