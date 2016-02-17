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
 *  Marko Stijak <marko.stijak@jedox.com>
 *  Vali Nitu <vali@yalos-solutions.com>
 *  Radu Ialovoi <ialovoi@yalos-solutions.com>
 */

#pragma once

#include <string>
#include <vector>
#include <map>

#include <oxml/sml-sheet.hpp>

#include "persistent_conditional_format.hpp"
#include <wss/type.hpp>

class conditional_format_manager;
class session;
namespace xlsx
{
    namespace sml = spreadsheetml;

    class persistent_theme;
    class persistent_styles;
    class persistent_color_table;
    class persistent_conditional_formats
    {
    private:
        std::map< std::string, std::vector< persistent_conditional_format > >   cf_map;
    public:
        void register_cf( const std::string& key, persistent_conditional_format& map );

        void store( std::vector< sml::CT_ConditionalFormatting >& out_map );

        static void load_rule(
            const std::vector <sml::CT_CfRule >& in_rule_map,
            const persistent_theme& theme,
            conditional_format_manager& cf_manager,
            session& s,
            const rectangle_list_type& range,
            const persistent_styles& styles,
            const bool is_core3,
            const std::string additional_param = ""
        );
    };

}
