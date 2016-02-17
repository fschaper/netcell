/**
 *  \file
 *  Copyright (C) 2006-2009 Jedox AG
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
 */


// This file has been auto-generated. Don't change it by hand!

#ifndef FONT_CONFIG_HPP
#define FONT_CONFIG_HPP


#include <xio/optional.hpp>
#include <xio/xml/schema/types.hpp>
#include <xio/util/binary_search.hpp>

namespace text_metrics_cfg
{
    using namespace ::xio;
    using namespace ::xio::xml::schema;

    class CT_Font;
    class CT_FontList;
    class CT_dpi;
    class CT_path;
    class CT_textmetric;
    class CT_key_val;
    class CT_style;
    class CT_font_config;
    class font_config;

    class CT_Font
    {
    public:
        String font_name;
    };

    class CT_FontList
    {
    public:
        std::vector< CT_Font > font;
    };

    class CT_dpi
    {
    public:
        CT_dpi() : default_dpi( 96 ) {}
        Int default_dpi;
    };

    class CT_path
    {
    public:
        CT_path() : font_path( "C:\\WINDOWS\\Fonts" ) {}
        String font_path;
    };

    class CT_textmetric
    {
    public:
        poptional< CT_dpi > dpi;
        poptional< CT_path > font_path;
    };

    class CT_key_val
    {
    public:
        String key;
        String val;
    };

    class CT_style
    {
    public:
        std::vector< CT_key_val > key_val;
    };

    class CT_font_config
    {
    public:
        CT_FontList font_list;
        CT_textmetric textmetric;
        poptional< CT_style > default_style;
    };

    class font_config
    {
    public:
        poptional< CT_font_config > font_setting;
    };

}
#endif

