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

#include "persistent_border_side.hpp"
#include "persistent_color.hpp"
#include "persistent_theme.hpp"
#include "persistent_color_table.hpp"
#include "oxml_utils.hpp"

namespace xlsx
{

    void persistent_border_side::store( sml::CT_BorderPr& obs ) const
    {
        if ( type == "none" ) {
            obs.style = sml::ST_BorderStyle::none;
        } else if ( type == "double" ) {
            obs.style = sml::ST_BorderStyle::_double_;
        } else if ( type == "solid" ) {
            switch ( width ) {
                case 0:
                    obs.style = sml::ST_BorderStyle::none;
                    break;
                case 1:
                    obs.style = sml::ST_BorderStyle::thin;
                    break;
                case 2:
                    obs.style = sml::ST_BorderStyle::medium;
                    break;
                default:
                case 3:
                    obs.style = sml::ST_BorderStyle::thick;
                    break;
            }
        } else if ( type == "dashed" ) {
            switch ( width ) {
                case 0:
                    obs.style = sml::ST_BorderStyle::none;
                    break;
                case 1:
                    obs.style = sml::ST_BorderStyle::dashed;
                    break;
                case 2:
                    obs.style = sml::ST_BorderStyle::mediumDashed;
                    break;
                default:
                case 3:
                    obs.style = sml::ST_BorderStyle::mediumDashed;
                    break;
            }
        } else if ( type == "dotted" ) {
            switch ( width ) {
                case 0:
                    obs.style = sml::ST_BorderStyle::none;
                    break;
                case 1:
                    obs.style = sml::ST_BorderStyle::dotted;
                    break;
                case 2:
                    obs.style = sml::ST_BorderStyle::mediumDashDotDot;
                    break;
                default:
                case 3:
                    obs.style = sml::ST_BorderStyle::mediumDashDot;
                    break;
            }
        }
        if ( color.present() ) {
            sml::CT_Color oc;
            persistent_color p_color( color.get() );
            p_color.store( oc );
            obs.color = oc;
        }
    }

    persistent_border_side::persistent_border_side( const sml::CT_BorderPr& in_border_side, const persistent_theme& theme, const persistent_color_table& colors )
    {
        switch ( in_border_side.style ) {
            default:
            case sml::ST_BorderStyle::none:
                type = "none";
                break;
            case sml::ST_BorderStyle::dashDot:
                type = "dashed";
                width = 1;
                break;
            case sml::ST_BorderStyle::dashDotDot:
                type = "dotted";
                width = 1;
                break;
            case sml::ST_BorderStyle::hair:
            case sml::ST_BorderStyle::dotted:
                type = "dotted";
                width = 1;
                break;
            case sml::ST_BorderStyle::_double_:
                type = "double";
                width = 3;
                break;
            case sml::ST_BorderStyle::thin:
                type = "solid";
                width = 1;
                break;
            case sml::ST_BorderStyle::medium:
                type = "solid";
                width = 2;
                break;
            case sml::ST_BorderStyle::mediumDashDot:
                type = "dashed";
                width = 2;
                break;
            case sml::ST_BorderStyle::mediumDashDotDot:
                type = "dotted";
                width = 2;
                break;
            case sml::ST_BorderStyle::dashed:
            case sml::ST_BorderStyle::slantDashDot:
                type = "dashed";
                width = 1;
                break;
            case sml::ST_BorderStyle::thick:
                type = "solid";
                width = 3;
                break;
        }

        if ( in_border_side.color.present() ) {
            color = persistent_color( in_border_side.color.get(), theme, colors ).m_color;
        }
    }

    const std::string persistent_border_side::str() const
    {
        if ( "none" != type ) {
            std::stringstream ss;
            ss << width;
            std::string     border_style    = ss.str() + "px " + type;
            if ( color.present() ) {
                border_style = border_style + " " + oxml_utils::color2hex( color.get() );
            } else {
                border_style = border_style + " ;";
            }

            return border_style;
        }

        return "";
    }
}
