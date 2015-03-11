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

#include "persistent_color_table.hpp"
#include <xio/xml/schema/types.hpp>

namespace xlsx
{
    persistent_color_table::persistent_color_table()
    {
        m_colors.push_back( 0x00000000 );
        m_colors.push_back( 0x00FFFFFF );
        m_colors.push_back( 0x00FF0000 );
        m_colors.push_back( 0x0000FF00 );
        m_colors.push_back( 0x000000FF );
        m_colors.push_back( 0x00FFFF00 );
        m_colors.push_back( 0x00FF00FF );
        m_colors.push_back( 0x0000FFFF );
        m_colors.push_back( 0x00000000 );
        m_colors.push_back( 0x00FFFFFF );
        m_colors.push_back( 0x00FF0000 );
        m_colors.push_back( 0x0000FF00 );
        m_colors.push_back( 0x000000FF );
        m_colors.push_back( 0x00FFFF00 );
        m_colors.push_back( 0x00FF00FF );
        m_colors.push_back( 0x0000FFFF );
        m_colors.push_back( 0x00800000 );
        m_colors.push_back( 0x00008000 );
        m_colors.push_back( 0x00000080 );
        m_colors.push_back( 0x00808000 );
        m_colors.push_back( 0x00800080 );
        m_colors.push_back( 0x00008080 );
        m_colors.push_back( 0x00C0C0C0 );
        m_colors.push_back( 0x00808080 );
        m_colors.push_back( 0x009999FF );
        m_colors.push_back( 0x00993366 );
        m_colors.push_back( 0x00FFFFCC );
        m_colors.push_back( 0x00CCFFFF );
        m_colors.push_back( 0x00660066 );
        m_colors.push_back( 0x00FF8080 );
        m_colors.push_back( 0x000066CC );
        m_colors.push_back( 0x00CCCCFF );
        m_colors.push_back( 0x00000080 );
        m_colors.push_back( 0x00FF00FF );
        m_colors.push_back( 0x00FFFF00 );
        m_colors.push_back( 0x0000FFFF );
        m_colors.push_back( 0x00800080 );
        m_colors.push_back( 0x00800000 );
        m_colors.push_back( 0x00008080 );
        m_colors.push_back( 0x000000FF );
        m_colors.push_back( 0x0000CCFF );
        m_colors.push_back( 0x00CCFFFF );
        m_colors.push_back( 0x00CCFFCC );
        m_colors.push_back( 0x00FFFF99 );
        m_colors.push_back( 0x0099CCFF );
        m_colors.push_back( 0x00FF99CC );
        m_colors.push_back( 0x00CC99FF );
        m_colors.push_back( 0x00FFCC99 );
        m_colors.push_back( 0x003366FF );
        m_colors.push_back( 0x0033CCCC );
        m_colors.push_back( 0x0099CC00 );
        m_colors.push_back( 0x00FFCC00 );
        m_colors.push_back( 0x00FF9900 );
        m_colors.push_back( 0x00FF6600 );
        m_colors.push_back( 0x00666699 );
        m_colors.push_back( 0x00969696 );
        m_colors.push_back( 0x00003366 );
        m_colors.push_back( 0x00339966 );
        m_colors.push_back( 0x00003300 );
        m_colors.push_back( 0x00333300 );
        m_colors.push_back( 0x00993300 );
        m_colors.push_back( 0x00993366 );
        m_colors.push_back( 0x00333399 );
        m_colors.push_back( 0x00333333 );
        m_colors.push_back( 0x00000000 );
        m_colors.push_back( 0x00FFFFFF );
    }

    void persistent_color_table::load( const sml::CT_Colors& colors )
    {
        if ( !colors.indexedColors.present() ) {
            return;
        }
        m_colors.clear();
        for ( std::vector< sml::CT_RgbColor >::const_iterator i = colors.indexedColors.get().rgbColor.begin(), e = colors.indexedColors.get().rgbColor.end(); i != e; i++ ) {
            if ( i->rgb.present() ) {
                const std::vector< unsigned char >& data = ( ( xio::xml::schema::HexBinary& )( i->rgb.get() ) ).data();
                long value = 0;
                for ( std::vector< unsigned char >::const_iterator i = data.begin(), e = data.end(); i != e; i++ ) {
                    value *= 256;
                    value += *i;
                }
                m_colors.push_back( value );
            } else {
                //TODO: this is just a whild guess. the idea is to keep indexes in order.
                //we don't know what to do but at least we pad.
                m_colors.push_back( 0 );
            }
        }
    }

    long persistent_color_table::at( const size_t idx ) const
    {
        if ( idx >= m_colors.size() ) {
            return 0;
        } else {
            return m_colors.at( idx );
        }
    }
}
