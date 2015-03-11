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
 *  Radu Ialovoi <ialovoi@yalos-solutions.com>
 */

#pragma once

#include <string>
#include <vector>
#include <map>

#include <wss/variant.hpp>
#include <wss/locale.hpp>
#include <wss/singleton.hpp>

#include "ControlTokens.hpp"

#include "cell_format_data.hpp"

namespace cell_format
{
    class reverse_format   : public singleton< reverse_format >
    {
        FRIEND_CLASS singleton< reverse_format >;
    private:
        typedef std::pair< std::string, std::string >       val_type;
        typedef std::pair< std::string,  val_type >         key_val_type;
        typedef std::vector< key_val_type >                 map_type;
        typedef std::map< locale, map_type >                localized_reverse_format_type;

        map_type                                            m_generic_values;
        localized_reverse_format_type                       m_localized_values;

        void load_locale( const locale& l );
        void localize_rule( std::string& rule, const ControlTokens& ct, const std::string& type = "" );
        void localize_format( std::string& format, const ControlTokens& ct );
        void tokenize_rule( const std::string& str, std::vector<std::string>& tokens, const std::string& delimiters = " " );
    public:
        void process_xml( const cfd::CT_ReverseFormats& input );
        bool find_format( const locale& l, const std::string& formatted_value, variant& value, std::string& format );
    };
}
