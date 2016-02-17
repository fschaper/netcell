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
#pragma once

#include <string>
#include <sstream>
#include <algorithm>

#include "css_utils.hpp"

namespace xlsx
{
    class oxml_utils : public string_utils
    {
    public:

        static const int default_char_max_width = 7;
        static bool parse_sheet_reference( const std::string& ref, std::string& sheet, int& c, int& r );
        static bool parse_reference( const std::string& ref, int& c, int& r );
        static bool parse_range( const std::string& ref, int& c1, int& r1, int& c2, int& r2 );
        static std::string cell_reference( int col, int row ) ;
        static std::string range2string( int col1, int row1, int col2, int row2 );
        static int pt2px( const double& d ) ;
        static double px2pt( int d ) ;
        static char char2hex( char c );
        static long string2color( const std::string& s );
        static long color( int index );
        static std::string format_code( size_t id, bool defaultToGeneral = true );

        static int format_id( std::string id );
        static long fix_color( long c ) {
            return c | 0xFF000000;
        }
        static long rgb( int r, int g, int b );
        static long tint( long l, double t );
        static int tint_part( int c, double t );

        static void color2hls( long c, double& h, double& l, double& s );
        static long hls2color( double h, double l, double s );
        static void split_ranges( const std::string& in_ranges, std::vector< std::string >& out_range );
        static const std::string color2hex( long color );
    };

}
