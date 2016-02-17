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

#include "persistent_fill.hpp"
#include "persistent_color.hpp"
#include "persistent_theme.hpp"
#include "persistent_color_table.hpp"
#include "persistent_color_table.hpp"
#include "pattern_translate.hpp"
#include "css_utils.hpp"

namespace xlsx
{

    persistent_fill::persistent_fill( const long fill_color, const std::string pattern_type ) : flip_fg_bg( false )
    {
        if ( -1 != fill_color ) {
            bg_color = fill_color;
        }
        if ( !pattern_type.empty() ) {
            this->pattern_type = pattern_translate::instance().external_patern( pattern_type );
        }
    }

    void persistent_fill::store( sml::CT_Fill& out_fill ) const
    {
        sml::CT_PatternFill& out_patternFill = out_fill.patternFill.getset();


        if ( bg_color.present() ) {
            persistent_color color( bg_color.get() );
            sml::CT_Color c2;
            c2.indexed = 64;
            if ( flip_fg_bg ) {
                out_patternFill.fgColor = c2;
                color.store( out_patternFill.bgColor.getset() );
            } else {
                out_patternFill.bgColor = c2;
                color.store( out_patternFill.fgColor.getset() );
            }
        }
        if ( !pattern_type.empty() ) {
            out_patternFill.patternType = pattern_type;
        } else {
            out_patternFill.patternType = sml::ST_PatternType::solid;
        }
    }

    persistent_fill::persistent_fill( const sml::CT_Fill& in_fill, const persistent_theme& theme, const persistent_color_table& colors  ) : flip_fg_bg( false )
    {
        bool is_empty = true;

        if ( in_fill.patternFill.get().patternType.present() ) {
            pattern_type = ( std::string )in_fill.patternFill.get().patternType.get();
            is_empty = "none" == pattern_type;
        } else {
            pattern_type = "solid";
        }

        if ( in_fill.patternFill.get().bgColor.present() ) {
            bg_color = persistent_color( in_fill.patternFill.get().bgColor.get(), theme, colors ).m_color;
            is_empty = false;
        }
        if ( in_fill.patternFill.get().fgColor.present() ) {
            fg_color = persistent_color( in_fill.patternFill.get().fgColor.get(), theme, colors ).m_color;
            is_empty = false;
        }

        if ( is_empty ) {
            pattern_type = "none";
        }

        if ( "none" == pattern_type || pattern_type.empty() ) {
            return;
        }

        if ( flip_fg_bg  ) {
            if ( bg_color.present() ) {
                style_set.add( std::string( "background-color" ), css_utils::color2string( bg_color.get() )  );
                //return_val =  "background-color: " + css_utils::color2string( bg_color.get() ) + ";";
            } else if ( fg_color.present() ) {
                style_set.add( std::string( "background-color" ), css_utils::color2string( fg_color.get() )  );
                //return_val =  "background-color: " + css_utils::color2string( fg_color.get() ) + ";";
            }
        } else {
            if ( fg_color.present() ) {
                style_set.add( std::string( "background-color" ), css_utils::color2string( fg_color.get() )  );
                //return_val =  "background-color: " + css_utils::color2string( fg_color.get() ) + ";";
            } else if ( bg_color.present() ) {
                style_set.add( std::string( "background-color" ), css_utils::color2string( bg_color.get() )  );
                //return_val =  "background-color: " + css_utils::color2string( bg_color.get() ) + ";";
            }

        }

        const std::string& img = pattern_translate::instance().internal_patern_val( pattern_type );

        if ( !img.empty() ) {
            style_set.add( std::string( "background-image" ), img  );
        }
    }

    const std::string persistent_fill::str() const
    {
        std::string return_val = "";

        if ( "none" == pattern_type || pattern_type.empty() ) {
            return return_val;
        }

        if ( flip_fg_bg  ) {
            if ( bg_color.present() ) {
                return_val =  "background-color: " + css_utils::color2string( bg_color.get() ) + ";";
            } else if ( fg_color.present() ) {
                return_val =  "background-color: " + css_utils::color2string( fg_color.get() ) + ";";
            }
        } else {
            if ( fg_color.present() ) {
                return_val =  "background-color: " + css_utils::color2string( fg_color.get() ) + ";";
            } else if ( bg_color.present() ) {
                return_val =  "background-color: " + css_utils::color2string( bg_color.get() ) + ";";
            }

        }

        return pattern_translate::instance().internal_patern( pattern_type ) + return_val;
    }

}
