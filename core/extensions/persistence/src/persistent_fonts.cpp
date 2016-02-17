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
#include "persistent_fonts.hpp"
#include "string_utils.hpp"

namespace xlsx
{

    int persistent_fonts::register_font( ssmap& props )
    {
        std::string                             key = string_utils::combine( props );
        std::map<std::string, int>::iterator    fit = m_font_map.find( key );
        if ( fit != m_font_map.end() ) {
            return fit->second;
        }

        int i = ( int )m_fonts.size();
        m_fonts.push_back( persistent_font( props ) );
        m_font_map[key] = i;
        return i;
    }

    void persistent_fonts::clear()
    {
        m_fonts.clear();
        m_font_map.clear();
    }

    void persistent_fonts::set_dummies()
    {
        persistent_font font;
        font.name = "Calibri";
        font.sz = 11;
        font.color = 0;
        font.bold = font.italic = font.underline = font.strike = false;
        m_fonts.push_back( font );
    }

    bool persistent_fonts::empty() const
    {
        return m_fonts.empty();
    }

    void persistent_fonts::load( const sml::CT_Fonts& in_fonts, const persistent_theme& theme, const persistent_color_table& colors  )
    {
        clear();
        for ( std::vector< sml::CT_Font >::const_iterator it = in_fonts.font.begin(); it != in_fonts.font.end(); it++ ) {
            m_fonts.push_back( persistent_font( *it, theme, colors ) );
        }
    }

    void persistent_fonts::store( sml::CT_Fonts& out_fonts ) const
    {
        out_fonts.count = ( int )m_fonts.size();
        for ( size_t i = 0; i < m_fonts.size(); i++ ) {
            sml::CT_Font crt_font;
            m_fonts[ i ].store( crt_font );
            out_fonts.font.push_back( crt_font );
        }
    }

    const std::string persistent_fonts::str( const size_t idx ) const
    {
        return m_fonts.at( idx ).str();
    }

    const style_set_type& persistent_fonts::style_set( const size_t idx ) const
    {
        return m_fonts.at( idx ).style_set;
    }

}
