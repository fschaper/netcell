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

#include "persistent_fills.hpp"
#include "persistent_color.hpp"
#include "persistent_theme.hpp"
#include "string_utils.hpp"
#include "css_utils.hpp"
#include <boost/foreach.hpp>

#define foreach BOOST_FOREACH

namespace xlsx
{
    bool persistent_fills::register_fill( const ssmap& props, int& fill_id )
    {
        key_type key = get_key( props );
        map_type::const_iterator       it = m_fill_map.find( key );
        if ( it != m_fill_map.end() ) {
            fill_id = it->second;
            return true;
        }

        //insert fill
        fill_id = ( int )m_fills.size();
        m_fills.push_back( persistent_fill( key.second, key.first ) );
        m_fill_map[ key ] = fill_id;
        return true;
    }

    persistent_fills::key_type persistent_fills::get_key( const ssmap& props )
    {
        long color = -1;
        std::string img = "";
        typedef std::pair< std::string, std::string> iterator_type;
        foreach( const iterator_type & crt, props ) {
            if ( "background" == crt.first ) {
                css_utils::parse_color( crt.second, color );
            }
            if ( "background-color" == crt.first ) {
                css_utils::parse_color( crt.second, color );
            }
            if ( "background-image" == crt.first ) {
                img = crt.second;
            }
        }

        return key_type( img, color );
    }

    void persistent_fills::clear()
    {
        m_fills.clear();
        m_fill_map.clear();
    }

    void persistent_fills::set_dummies()
    {
        m_fills.push_back( persistent_fill( 0xFFFFFFFF, "none" ) );//none
        m_fills.push_back( persistent_fill( 0xFFFFFFFF, "gray125" ) );//gray125
    }

    bool persistent_fills::empty() const
    {
        return m_fills.empty();
    }

    void persistent_fills::store( sml::CT_Fills& out_fills ) const
    {
        out_fills.count = ( int )m_fills.size();
        for ( size_t i = 0; i < m_fills.size(); i++ ) {
            sml::CT_Fill crt_fill;
            m_fills[i].store( crt_fill );
            out_fills.fill.push_back( crt_fill );
        }
    }

    void persistent_fills::load( const std::vector< sml::CT_Fill >& in_fills, const persistent_theme& theme, const persistent_color_table& colors )
    {
        for ( std::vector< sml::CT_Fill >::const_iterator it = in_fills.begin(); it != in_fills.end(); it++ ) {
            if ( !it->patternFill.present() ) {
                continue;
            }
            m_fills.push_back( persistent_fill( *it, theme, colors ) );
        }
    }

    const std::string persistent_fills::str( const size_t idx ) const
    {
        return m_fills.at( idx ).str();
    }

    const style_set_type& persistent_fills::style_set( const size_t idx ) const
    {
        return m_fills.at( idx ).style_set;
    }

}
