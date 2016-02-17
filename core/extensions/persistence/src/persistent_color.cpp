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

#include <string>

#include "persistent_color.hpp"
#include "persistent_theme.hpp"
#include "persistent_color_table.hpp"
#include "gen_utils.hpp"
#include "oxml_utils.hpp"

namespace xlsx
{

    void persistent_color::store( sml::CT_Color& oc ) const
    {
        long cc = gen_utils::reverse_bytes( oxml_utils::fix_color( m_color ) );
        oc.rgb = sml::ST_UnsignedIntHex( sml::HexBinary( ( sml::UnsignedByte* ) & cc, sizeof( cc ) ) );
    }

    persistent_color::persistent_color( const sml::CT_Color& oc, const persistent_theme& theme, const persistent_color_table& colors )
    {
        if ( oc.rgb.present() ) {
            m_color = oxml_utils::string2color( oc.rgb.get().get().encode() );
        } else if ( oc.indexed.present() ) {
            m_color = colors.at( oc.indexed.get() );
        } else if ( oc.theme.present() ) {
            m_color = theme.get_color( oc.theme.get() );
        } else if ( oc._auto_.present() ) {
            m_color = theme.get_color( 1 );
        }
        m_color = oxml_utils::tint( m_color, oc.tint );
    }

    persistent_color::persistent_color( const dml::CT_Color& oc )
    {
        if ( oc.srgbClr.present() ) {
            m_color = oxml_utils::string2color( oc.srgbClr.get().val.get().encode() );
        } else if ( oc.sysClr.present() ) {
            std::string s = oc.sysClr.get().val;
            if ( s == "windowText" ) {
                m_color = 0x00000000;
            } else if ( s == "window" ) {
                m_color = 0x00FFFFFF;
            }
        } else {
            m_color = 0x00777777; //gray
        }
    }
}
