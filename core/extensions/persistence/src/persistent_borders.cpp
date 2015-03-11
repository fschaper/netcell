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

#include "persistent_borders.hpp"
#include "persistent_theme.hpp"
#include "string_utils.hpp"
#include <wss/border_manager.hpp>

namespace xlsx
{
    int persistent_borders::register_border( const ssmap& props )
    {
        std::string key = string_utils::combine( props );
        std::map<std::string, int>::iterator fit = m_border_map.find( key );
        if ( fit != m_border_map.end() ) {
            return fit->second;
        }

        int i = ( int )m_borders.size();
        m_borders.push_back( persistent_border( props ) );
        m_border_map[key] = i;
        return i;
    }

    void persistent_borders::clear()
    {
        m_borders.clear();
        m_border_map.clear();
    }

    void persistent_borders::set_dummies()
    {
        m_borders.push_back( persistent_border() );
    }

    bool persistent_borders::empty() const
    {
        return m_borders.empty();
    }

    void persistent_borders::load( const std::vector< sml::CT_Border > in_borders, const persistent_theme& theme, const persistent_color_table& colors )
    {
        m_borders.clear();
        m_border_map.clear();
        for ( std::vector< sml::CT_Border >::const_iterator i = in_borders.begin(); i != in_borders.end(); i++ ) {
            m_borders.push_back( persistent_border( *i, theme, colors ) );
        }
    }

    void persistent_borders::store( sml::CT_Borders& out_borders ) const
    {
        out_borders.count = ( int )m_borders.size();
        for ( unsigned i = 0; i < m_borders.size(); i++ ) {
            sml::CT_Border out_border;
            m_borders[i].store( out_border );
            out_borders.border.push_back( out_border );
        }
    }

    void  persistent_borders::apply( border_manager& bm, const size_t idx, const size_t row, const size_t col, const bool is_import /* = true */ ) const
    {
        try {
            m_borders.at( idx ).apply( bm, row, col, is_import );
        } catch ( const std::exception& ) {
            // TODO why is the vector out of range?
        }
    }
}
