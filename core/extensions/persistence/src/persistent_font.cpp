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

#include "persistent_theme.hpp"
#include "persistent_color_table.hpp"
#include "persistent_font.hpp"
#include "persistent_color.hpp"
#include "css_utils.hpp"
#include "gen_utils.hpp"
#include <boost/lexical_cast.hpp>

namespace xlsx
{

    persistent_font::persistent_font( ssmap& src )
    {

        double                  size;
        long                    css_color;
        ssmap::const_iterator   it;
        ssmap::const_iterator   end = src.end();

        if ( ( it = src.find( "font-family" ) ) != end ) {
            name = it->second;
        }

        if ( ( it = src.find( "font-size" ) ) != end && css_utils::parse_font_size( it->second, size ) ) {
            sz = static_cast<int>( size );
        }

        bold        = ( ( it = src.find( "font-weight" ) ) != end && it->second == "bold" );
        italic      = ( ( it = src.find( "font-style" ) ) != end && it->second == "italic" );
        strike      = ( ( it = src.find( "text-decoration" ) ) != end && ( it->second.find( "line-through" ) != it->second.npos ) );
        underline   = ( ( it = src.find( "text-decoration" ) ) != end && ( it->second.find( "underline" ) != it->second.npos ) );

        if ( ( it = src.find( "color" ) ) != end && css_utils::parse_color( it->second, css_color ) ) {
            color = css_color;
        }

    }

    void persistent_font::store( spreadsheetml::CT_Font& font ) const
    {
        bool is_normal = true;
        if ( name.present() ) {
            spreadsheetml::CT_FontName fn;

            fn.val = name.get();
            font.name = fn;
        }
        //RIA: all the presents are already true by construction
        //        if ( bold.present() ) {
        if ( bold.get() )   {
            is_normal = false;
            font.b = spreadsheetml::CT_BooleanProperty();
        }
        //       }

        //        if ( italic.present() ) {
        if ( italic.get() ) {
            is_normal = false;
            font.i = spreadsheetml::CT_BooleanProperty();
        }
        //        }

        //        if ( underline.present() ) {
        if ( underline.get() ) {
            is_normal = false;
            spreadsheetml::CT_UnderlineProperty up;

            up.val = spreadsheetml::ST_UnderlineValues::single;
            font.u = up;
        }
        //        }

        //        if ( strike.present() ) {
        if ( strike.get() ) {
            is_normal = false;
            font.strike = spreadsheetml::CT_BooleanProperty();
        }
        //        }


        if ( is_normal ) {
            //special case for a regular font
            spreadsheetml::CT_BooleanProperty false_prop;
            false_prop.val = false;
            font.b = false_prop;
            font.i = false_prop;
        }

        if ( sz.present() ) {

            spreadsheetml::CT_FontSize sz;
            sz.val = this->sz.get();
            font.sz = sz;
        }

        if ( color.present() ) {

            persistent_color p_color( color.get() );
            p_color.store( font.color.getset() );
        }
    }

    persistent_font::persistent_font( const spreadsheetml::CT_Font& font, const persistent_theme& theme, const persistent_color_table& colors )
    {
        if ( font.b.present() ) {
            bold        = font.b.get().val;
        }
        if ( font.strike.present() ) {
            strike      = font.strike.get().val;
        }
        if ( font.i.present() ) {
            italic      = font.i.get().val;
        }
        if ( font.u.present() ) {
            underline   = ( font.u.get().val != sml::ST_UnderlineValues::none );
        }
        if ( font.name.present() ) {
            name        = font.name.get().val;
        }
        if ( font.sz.present() ) {
            sz          = font.sz.get().val;
        }
        if ( font.color.present() ) {
            color       = persistent_color( font.color.get(), theme, colors ).m_color;
        }

        if ( color.present() ) {
            style_set.add( std::string( "color" ), css_utils::color2string( color.get() ) );
        }
        if ( bold.present() && bold.get() == true ) {
            style_set.add( std::string( "font-weight" ), "bold" );
        }
        if ( italic.present() && italic.get() == true ) {
            style_set.add( std::string( "font-style" ), "italic" );
        }
        if ( underline.present() && underline.get() == true ) {
            if ( strike.present() && strike.get() == true ) {
                style_set.add( std::string( "text-decoration" ), "underline line-through" );
            } else {
                style_set.add( std::string( "text-decoration" ), "underline" );
            }
        }
        if ( strike.present() && strike.get() == true  && !( underline.present() && underline.get() == true ) ) {
            style_set.add( std::string( "text-decoration" ), "line-through" );
        }
        if ( name.present() ) {
            style_set.add( std::string( "font-family" ), name.get() );
        }
        if ( sz.present() ) {
            style_set.add( std::string( "font-size" ), boost::lexical_cast< std::string >( sz.get() ) + "pt" );
        }

        if ( !underline.present() && !strike.present() && bold.present() && bold.get() == false && italic.present() && italic.get() == false ) {
            //special case for a regular font
            style_set.add( std::string( "font-weight" ), "normal" );
        }
    }

    const std::string persistent_font::str() const
    {
        std::string result = "";

        if ( color.present() ) {
            result += ( "color: " + css_utils::color2string( color.get() ) + ";" );
        }
        if ( bold.present() && bold.get() == true ) {
            result += ( "font-weight: bold;" );
        }
        if ( italic.present() && italic.get() == true ) {
            result += ( "font-style: italic;" );
        }
        if ( underline.present() && underline.get() == true ) {
            if ( strike.present() && strike.get() ) {
                result += ( "text-decoration: underline line-through;" );
            } else {
                result += ( "text-decoration: underline;" );
            }
        }
        if ( strike.present() && strike.get() == true && !( underline.present() && underline.get() == true ) ) {
            result += ( "text-decoration: line-through;" );
        }
        if ( name.present() ) {
            result += ( "font-family: " + name.get() + ";" );
        }
        if ( sz.present() ) {
            std::stringstream ss;
            ss << sz.get() << "pt;";
            result += ( "font-size: " + ss.str() );
        }

        if ( !underline.present() && !strike.present() && bold.present() && bold.get() == false && italic.present() && italic.get() == false ) {
            //special case for a regular font
            result += ( "font-weight: normal;" );
        }

        return result;
    }
}
