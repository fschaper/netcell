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
#include "wss/ci_string.hpp"
#include "wss/not_implemented_exception.hpp"

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <unicode/uchar.h>
#   include <unicode/ustring.h>
#   include <unicode/unistr.h>
#endif

int _CLRCALL_OR_CDECL_DEFINE_ utf8_ci_char_traits::compare( const char* s1, const char* s2, size_t n )
{
    return icu::UnicodeString::fromUTF8( s1 ).caseCompare( icu::UnicodeString::fromUTF8( s2 ), U_FOLD_CASE_DEFAULT );
}

const char* _CLRCALL_OR_CDECL_DEFINE_ utf8_ci_char_traits::find( const char* s, size_t n, const char a )
{
    throw not_implemented_exception( "utf8_ci_char_traits::find - not implemented!" );
    return NULL;
}

bool _CLRCALL_OR_CDECL_DEFINE_ utf8_ci_char_traits::lt( const char c1, const char c2 )
{
    throw not_implemented_exception( "utf8_ci_char_traits::lt - not implemented!" );
    return false;
}

bool _CLRCALL_OR_CDECL_DEFINE_ utf8_ci_char_traits::ne( const char c1, const char c2 )
{
    throw not_implemented_exception( "utf8_ci_char_traits::ne - not implemented!" );
    return false;
}

bool _CLRCALL_OR_CDECL_DEFINE_ utf8_ci_char_traits::eq( const char c1, const char c2 )
{
    throw not_implemented_exception( "utf8_ci_char_traits::eq - not implemented!" );
    return false;
}

bool operator ==( const std::string& lhs, const utf8_ci_string& rhs )
{
    return icu::UnicodeString::fromUTF8( lhs.c_str() ).caseCompare( icu::UnicodeString::fromUTF8( rhs.c_str() ), U_FOLD_CASE_DEFAULT ) == 0;
}

template<class string_T>
string_T to_upper_copy_utf8( const string_T& s )
{
    string_T return_value;
    icu::UnicodeString::fromUTF8( s.c_str() ).toUpper().toUTF8String( return_value );
    return return_value;
}

template<class string_T>
string_T to_lower_copy_utf8( const string_T& s )
{
    string_T return_value;
    icu::UnicodeString::fromUTF8( s.c_str() ).toLower().toUTF8String( return_value );
    return return_value;
}

template std::string to_upper_copy_utf8<std::string>( const std::string& );
template ci_string to_upper_copy_utf8<ci_string>( const ci_string& );
template utf8_ci_string to_upper_copy_utf8<utf8_ci_string>( const utf8_ci_string& );

template std::string to_lower_copy_utf8<std::string>( const std::string& );
template ci_string to_lower_copy_utf8<ci_string>( const ci_string& );
template utf8_ci_string to_lower_copy_utf8<utf8_ci_string>( const utf8_ci_string& );

