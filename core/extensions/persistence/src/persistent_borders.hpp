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

#pragma once

#include "persistent_border.hpp"
#include <oxml/sml-styles.hpp>

class border_manager;
namespace xlsx
{

    class persistent_theme;
    class persistent_color_table;
    class persistent_borders
    {
    private:
        std::vector<persistent_border>      m_borders;
        std::map<std::string, int>          m_border_map;
    public:
        int register_border( const ssmap& props );
        void clear();
        void set_dummies();
        bool empty() const;
        void load( const std::vector< sml::CT_Border > in_borders, const persistent_theme& theme, const persistent_color_table& colors );
        void store( sml::CT_Borders& out_borders ) const;
        //is_import should be true for xlsx import, false for loading wss files...
        void apply( border_manager& bm, const size_t idx, const size_t row, const size_t col, const bool is_import = true ) const;
    };

}
