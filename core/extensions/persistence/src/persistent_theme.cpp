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

namespace xlsx
{

    void persistent_theme::load( package::ipackage& package )
    {
        if ( !package.exists( "xl/theme/theme1.xml" ) ) {
            return;
        }

        dml::dml_stylesheet doc;
        parse_doc( package.get( "xl/theme/theme1.xml" ), doc );
        if ( !doc.theme.present() ) {
            return;
        }
        const dml::CT_OfficeStyleSheet& sst = doc.theme.get();

        theme_colors.clear();

        theme_colors.push_back( persistent_color( sst.themeElements.clrScheme.lt1 ) );
        theme_colors.push_back( persistent_color( sst.themeElements.clrScheme.dk1 ) );
        theme_colors.push_back( persistent_color( sst.themeElements.clrScheme.lt2 ) );
        theme_colors.push_back( persistent_color( sst.themeElements.clrScheme.dk2 ) );
        theme_colors.push_back( persistent_color( sst.themeElements.clrScheme.accent1 ) );
        theme_colors.push_back( persistent_color( sst.themeElements.clrScheme.accent2 ) );
        theme_colors.push_back( persistent_color( sst.themeElements.clrScheme.accent3 ) );
        theme_colors.push_back( persistent_color( sst.themeElements.clrScheme.accent4 ) );
        theme_colors.push_back( persistent_color( sst.themeElements.clrScheme.accent5 ) );
        theme_colors.push_back( persistent_color( sst.themeElements.clrScheme.accent6 ) );
        theme_colors.push_back( persistent_color( sst.themeElements.clrScheme.hlink ) );
        theme_colors.push_back( persistent_color( sst.themeElements.clrScheme.folHlink ) );
    }

    long persistent_theme::get_color( int index ) const
    {
        if ( static_cast<unsigned>( index ) < theme_colors.size() ) {
            return theme_colors[index].m_color;
        }
        if ( index == 1 ) {
            return 0x00000000;    //window text
        }
        if ( index == 2 ) {
            return 0x00FFFFFF;    //window
        }
        return 0x00777777;//gray
    }

}
