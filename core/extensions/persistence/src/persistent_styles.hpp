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

#include <vector>
#include <map>
#include <string>
#include <ostream>

#include "zpackage.hpp"
#include <oxml/sml-styles.hpp>
#include <oxml/sml-styles_serializer.hpp>
#include <oxml/sml-styles_parser.hpp>

#include "simple_types.hpp"
#include "persistent_fonts.hpp"
#include "persistent_alignments.hpp"
#include "persistent_borders.hpp"
#include "persistent_fills.hpp"
#include "persistent_nfmts.hpp"
#include "persistent_style.hpp"
#include "persistent_protection.hpp"
#include "persistent_dxf.hpp"
#include "persistent_xfs.hpp"
#include "persistent_color_table.hpp"


#include <wss/style_set.hpp>

class border_manager;
namespace xlsx
{

    namespace sml = spreadsheetml;

    class persistent_theme;
    class persistent_styles : private
        ::xio::xml::binding::serializer,
         ::xio::xml::binding::parser
    {
    private:
        typedef std::map< size_t, style_set_type >  style_set_cache_type;
        std::vector<persistent_style>   m_styles;
        std::map<std::string, int>      m_style_map;

        std::vector<persistent_dxf>     m_dxfs;
        std::map<std::string, int>      m_dxf_map;

        persistent_color_table          m_color_table;
        persistent_fonts                m_fonts;
        persistent_alignments           m_alignments;
        persistent_borders              m_borders;
        persistent_fills                m_fills;
        persistent_nfmts                m_nfmts;
        persistent_xfs                  m_xfs;
        persistent_xfs                  m_cell_style_xfs;

        std::string                     m_last_registered_string;
        int                             m_last_registered_idx;

        int                             m_empty_style_id;

        style_set_cache_type            m_style_sets;
        bool separate_styles(
            const std::string& style_string,
            ssmap& align_rules,
            ssmap& font_rules,
            ssmap& border_rules,
            ssmap& fill_rules,
            ssmap& protection_rules,
            ssmap& format_rules,
            ssmap& quote_rules );

        void load_dxfs( const sml::CT_Dxfs& in_dxfs, const persistent_theme& theme );
    public:
        style_set_type      ss;
        persistent_styles();
        int register_style( const std::string& style_string );
        int register_dxf( const std::string& style_string, bool flip_fg_bg = false );
        int get_empty_style();
        void clear();
        void set_dummies();
        void store( std::ostream& os ) const;
        void load( package::ipackage& package, const persistent_theme& theme );

        const persistent_alignment& align_at( const size_t idx ) const;

        const std::string nf_at( const size_t idx ) const;
        //is_import should be true for xlsx import, false for loading wss files...
        void  apply_border_at( border_manager& bm, const size_t idx, const size_t row, const size_t col, const bool is_import = true ) const;
        const bool protected_at( const size_t idx ) const;
        const persistent_dxf& dxf_at( const size_t idx ) const;
        const bool has_dxf( const size_t idx ) const;
        const persistent_color_table& color_table() const;

        const style_set_type& cs_xf_at( size_t idx );

        const bool quote_prefix_at ( const size_t idx ) const;

        static const bool is_empty_style( const style_set_type& style_set ) {
            if ( 1 != style_set.size() ) {
                return false;
            }

            style_set_type::const_iterator all = style_set.begin();

            return all->first == "background-color" && all->second.empty();
        }
    };

}
