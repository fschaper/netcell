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

#include "persistent_conditional_format.hpp"
#include "string_utils.hpp"

namespace xlsx
{

    bool persistent_conditional_format::parse_rule( const std::string& rule )
    {
        std::vector<std::string> aa = string_utils::split( rule, "();", false );
        if ( aa.size() < 2 ) {
            return false;
        }
        this->rule = aa[0];
        op = aa[1];
        stop_if_true = ( aa[2].size() > 0 && aa[2][0] == '1' ) ? true : false;
        return true;
    }

    std::string persistent_conditional_format::get_style_string( const std::string& style, const std::string& format )
    {
        return style + ( style.size() > 0 && style[style.size()-1] == ';' ? "" : ";" ) + ( format.empty() ? "" : "__number-format:" + format );
    }
}
