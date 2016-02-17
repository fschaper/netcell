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
 *  Marek Pikulski <marek.pikulski@jedox.com>
 */

#pragma once

// stl
#include <map>

#include <wss/locale.hpp>
#include <wss/singleton.hpp>

#include "ControlTokens.hpp"

namespace cell_format
{

    /*! \brief Provides access to build-in locale data.
    *
    *  \author Marek Pikulski <marek.pikulski@jedox.com>
    */
    class i18n  : public singleton< i18n >
    {
        FRIEND_CLASS singleton< i18n >;
    private:
        typedef std::map<locale, ControlTokens> locale_map_type;
        locale_map_type m_lm;

        typedef std::map< unsigned int, std::string > default_format_type;
        typedef std::map< locale, default_format_type > default_format_map_type;
        default_format_map_type m_default_formats;

        i18n();
        virtual ~i18n();

        void create_default();
    public:

        const ControlTokens& get_english();

        const ControlTokens& operator[] ( const locale& lang_code );

        void process_xml( const std::string& filename );

        std::string default_format( const locale& lang_code, unsigned int f_id );
    };
}
