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

#include "wss/locale.hpp"

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <boost/noncopyable.hpp>
#   include <boost/algorithm/string.hpp>
#   include <boost/regex.hpp>
#endif // HAS_PRECOMPILED_HEADER == 0

locale::locale( const std::string& language, const std::string& region )
    : m_language( boost::to_lower_copy( language ) )
    , m_region( boost::to_upper_copy( region ) )
{}

std::string locale::code() const
{
    return std::string( m_language + ( !m_region.empty() ? "_" + m_region : "" ) );
}

const std::string& locale::language() const
{
    return m_language;
}

const std::string& locale::region() const
{
    return m_region;
}

bool locale::operator<( const locale& rhs ) const
{
    if ( m_language == rhs.m_language ) {
        if ( m_region == "*" || rhs.m_region == "*" ) {
            if ( ( m_region == "*" && rhs.m_region == "*" ) || m_region == "*" ) {
                return false;
            } else if ( rhs.m_region == "*" ) {
                return true;
            }
        } else {
            return m_region < rhs.m_region;
        }
    }
    return m_language < rhs.m_language;
}

bool locale::operator==( const locale& other ) const
{
    // (fschaper) support for language ranges. if the '*' character is used for
    // the region part it matches all regions. F.ex. en-* matches en, en-US, en-GB
    // (but not de or de-DE, ...).
    return m_language == other.m_language
           && ( m_region == "*" || other.m_region == "*" || m_region == other.m_region );
}

locale locale::create( const std::string& l )
{
    // (fschaper) regex to parse rfc3066 formatted language codes.
    // see http://www.ietf.org/rfc/rfc3066.txt for reference.
    // we only test for a well-formed string. no check for validity is made.
    // separation using '_' as an substitute for '-' also supported for backwards compatibility.
    static const boost::regex langtag_ex( "([[:alpha:]]{1,8})(?:[-_]([[:alnum:]]{1,8}|\\*))?", boost::regex::perl );

    boost::smatch results;
    bool success = boost::regex_match( l, results, langtag_ex );

    if ( ! success ) {
        throw invalid_locale_exception();
    }

    return locale( results[1], results[2] );
}

const locale& locale::neutral_server_locale()
{
    static const locale neutral_locale = create( neutral_locale_string );
    return neutral_locale;
}

const std::string locale::neutral_locale_string = "en-US";
