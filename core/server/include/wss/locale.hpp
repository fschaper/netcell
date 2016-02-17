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
#include <wss/invalid_locale_exception.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <string>
#endif
#ifdef WIN32
# pragma warning( disable : 4251 ) // ignore warnings about std::basic_string having no dll-interface
#endif

/*!
 * \brief
 * represents an valid user locale for the system.
 *
 * based on rfc3066.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class WSS_MODULE locale
{
public:
    /*!
     * \brief
     * returns a POSIX formed string.
     *
     * f.ex. en_US or en.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    std::string code() const;

    /*!
     * \brief
     * language part of the locale.
     *
     * f.ex. "en" in en-GB or en-US.
     * always returns a lowercase value.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const std::string& language() const;

    /*!
     * \brief
     * region part of the locale.
     *
     * f.ex. "GB" in en-GB or "US" in en-US.
     * always returns an uppercase value.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const std::string& region() const;

    /*!
     * \brief
     * lexicographical comparison for lesser as.
     *
     * compares by first executing language lhs < rhs and in case
     * language lhs == rhs also compares region lhs < rhs.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool operator <( const locale& rhs ) const;

    /*!
     * \brief
     * compares one locale object with another.
     *
     * if one of the operands has the kleene star set for
     * the region part the region comparison will always return
     * true. So f.ex. de-DE == de-* will result in true
     * de == de-* will also result in true.

     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool operator ==( const locale& rhs ) const;

    /*!
     * \brief
     * compares one locale object with another for inequality.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool operator !=( const locale& rhs ) const {
        return !( *this == rhs );
    }

    /*!
     * \brief
     * create a locale object.
     *
     * you can pass any string that conforms to rfc3066. f.ex.
     * de, de-DE, de-de, en-US, en-*
     * if you pass '*' for the region that locale will match
     * any other locale for that region ( de-* == [de, de-DE, de-CH].
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    static locale create( const std::string& l );

    static const locale& neutral_server_locale();

    /*!
     * \brief
     * neutral locale string used for instance for save/load
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    static const std::string neutral_locale_string;

private:
    /*!
     * \brief
     * constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    locale( const std::string& language, const std::string& region );

private:
    std::string m_language;
    std::string m_region;
};

