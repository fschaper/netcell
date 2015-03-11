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
#include <vector>
#include <sstream>
#include <stdio.h>
#include "simple_types.hpp"

namespace xlsx
{

    class string_utils
    {
    public:
        static std::string int2string( int i );
        static bool parse( const std::string& s, int& res );
        static int string2int( const std::string& s );
        static double string2double( const std::string& s );
        static bool parse_hex( const std::string& s, int& res );
        static bool parse_hex( char c, int& res );

        static std::string trim_white( const std::string& s );
        static std::string trim_start( const std::string& s, char c );
        static std::vector<std::string> split( const std::string& s, const std::string& delim, bool remove_empty_entries = true );
        static bool starts_with( const std::string& s, const std::string& with );
        static std::string combine( const ssmap& m );
    };
}
