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

#pragma once

#include <wss/define.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <cctype>       // for std::toupper
#   include <string>       // for std::basic_string, std::allocator
#   include <iosfwd>
#   include <functional>   // for std::binary_comparison
#   include <ostream>
#   if defined( WIN32 )
#       include <cstring>   // for memicmp
#   else
#       include <strings.h> // for strcasecmp
#   endif
#endif

#if defined( WIN32 )
#   define JDX_STRCMP( x, y ) _stricmp( x, y )
#else
#   define JDX_STRCMP( x, y ) strcasecmp( x, y )
#endif

/*!
 * \brief
 * case insensitive string char trait
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 *
 * \reference
 * Sutter, Herb. Exceptional C++. 2. Amsterdam: Addison-Wesley Longman, 2004.
 * Sutter, Herb. "GotW.ca: Herb Sutter." GotW #29: Strings. 16 Nov 2008 <http://www.gotw.ca/gotw/029.htm>.
 */
struct WSS_MODULE ci_char_traits
#if defined(USING_VS_2010)
        : public std::_Char_traits<char, long> {
#else
        :
    public std::char_traits<char> {
#endif

    inline static bool eq( const char c1, const char c2 ) {
        return std::toupper( c1 ) == std::toupper( c2 );
    }

    inline static bool ne( const char c1, const char c2 ) {
        return !eq( c1, c2 );
    }

    inline static bool lt( const char c1, const char c2 ) {
        return std::toupper( c1 ) <  std::toupper( c2 );
    }

    inline static int compare( const char* s1, const char* s2, size_t n ) {
#if defined( WIN32 )
        return _memicmp( s1, s2, n );
#else
        while ( n-- && eq( *s1, *s2 ) ) {
            s1++, s2++;
        }
        return lt( *s2, *s1 ) - lt( *s1, *s2 );
#endif // WIN32
    }

    inline static const char* find( const char* s, int n, const char a ) {
        while ( n-- && ne( *s, a ) ) {
            ++s;
        }
        return s;
    }
};

/*!
 * \brief
 * utf8 aware case insensitive string char trait.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
struct WSS_MODULE utf8_ci_char_traits
#if defined(USING_VS_2010)
        : public std::_Char_traits<char, long> {
#else
        :
    public std::char_traits<char> {
#endif
    static bool _CLRCALL_OR_CDECL_DEFINE_ eq( const char c1, const char c2 );

    static bool _CLRCALL_OR_CDECL_DEFINE_ ne( const char c1, const char c2 );

    static bool _CLRCALL_OR_CDECL_DEFINE_ lt( const char c1, const char c2 );

    static int _CLRCALL_OR_CDECL_DEFINE_ compare( const char* s1, const char* s2, size_t n );

    static const char* _CLRCALL_OR_CDECL_DEFINE_ find( const char* s, size_t n, const char a );
};

/*!
 * \brief
 * convert an utf8 string to uppercase.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
template<class string_T>
WSS_MODULE string_T to_upper_copy_utf8( const string_T& s );

/*!
* \brief
* convert an utf8 string to lowercase.
*
* \author
* Florian Schaper <florian.schaper@jedox.com>
*/
template<class string_T>
WSS_MODULE string_T to_lower_copy_utf8( const string_T& s );

/*!
 * \brief
 * case-insensitive string template.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
typedef std::basic_string<char, ci_char_traits, std::allocator<char> > ci_string;

/*!
 * \brief
 * case-insensitive utf8 string.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
typedef std::basic_string<char, utf8_ci_char_traits> utf8_ci_string;

/*!
 * \brief
 * output stream conversion for the ci_string.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
inline std::ostream& operator <<( std::ostream& os, const ci_string& s )
{
    return os.write( s.c_str(), static_cast<std::streamsize>( s.size() ) );
}

/*!
 * \brief
 * output stream conversion for the utf8_ci_string.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
inline std::ostream& operator <<( std::ostream& os, const utf8_ci_string& s )
{
    return os.write( s.c_str(), static_cast<std::streamsize>( s.size() ) );
}

/*!
 * \brief
 * comparison operator for std::string == ci_string.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
inline bool operator ==( const std::string& lhs, const ci_string& rhs )
{
    return JDX_STRCMP( lhs.c_str(), rhs.c_str() ) == 0;
}

/*!
 * \brief
 * comparison operator for ci_string == std::string.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
inline bool operator ==( const ci_string& lhs, const std::string& rhs )
{
    return JDX_STRCMP( lhs.c_str(), rhs.c_str() ) == 0;
}

/*!
 * \brief
 * comparison for inequality
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
inline bool operator !=( const std::string& lhs, const ci_string& rhs )
{
    return !( lhs == rhs );
}

/*!
 * \brief
 * comparison for inequality
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
inline bool operator !=( const ci_string& lhs, const std::string& rhs )
{
    return !( lhs == rhs );
}

/*!
 * \brief
 * comparison operator for std::string == utf8_ci_string.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
bool WSS_MODULE operator ==( const std::string& lhs, const utf8_ci_string& rhs );

/*!
 * \brief
 * comparison operator for std::string == utf8_ci_string.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
inline bool operator ==( const utf8_ci_string& lhs, const std::string& rhs )
{
    return ( rhs == lhs );
}

/*!
 * \brief
 * comparison for inequality
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
inline bool operator !=( const std::string& lhs, const utf8_ci_string& rhs )
{
    return !( lhs == rhs );
}

/*!
 * \brief
 * comparison for inequality
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
inline bool operator !=( const utf8_ci_string& lhs, const std::string& rhs )
{
    return !( lhs == rhs );
}

/*!
 * \brief
 * convert std::string to ci_string
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
inline ci_string convert_ci( const std::string& o )
{
    return ci_string( o.c_str(), o.size() );
}

/*!
 * \brief
 * convert ci_string to std::string
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
inline std::string convert_ci( const ci_string& o )
{
    return std::string( o.c_str(), o.size() );
}

/*!
 * \brief
 * convert std::string to utf8_ci_string
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
inline utf8_ci_string convert_utf8_ci( const std::string& o )
{
    return utf8_ci_string( o.c_str(), o.size() );
}

/*!
 * \brief
 * convert utf8_ci_string to std::string
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
inline std::string convert_utf8_ci( const utf8_ci_string& o )
{
    return std::string( o.c_str(), o.size() );
}

/*!
 * \brief
 * case insensitive comparison if string1 is 'less' than string2
 *
 * \remarks
 * does not take either locale or \0's into account
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
struct string_less_case_insensitive
        : public std::binary_function<const std::string&, const std::string&, bool> {
    bool operator()( const std::string& p1, const std::string& p2 ) const {
        return JDX_STRCMP( p1.c_str(), p2.c_str() ) < 0;
    }
};
