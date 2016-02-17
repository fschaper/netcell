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

#include "persistent_border.hpp"
#include "css_utils.hpp"
#include <wss/border_manager.hpp>
#include <wss/border_types.hpp>
#include <wss/set_conditional_format.hpp>

namespace xlsx
{

    persistent_border::persistent_border( const ssmap& props )
    {
        persistent_border_side t, r, l, b;
        ssmap::const_iterator it;
        if ( ( it = props.find( "border-left" ) ) != props.end() ) {
            if ( css_utils::parse_border_side( it->second, l.width, l.type, l.color ) ) {
                left = l;
            }
        }
        if ( ( it = props.find( "border-right" ) ) != props.end() ) {
            if ( css_utils::parse_border_side( it->second, r.width, r.type, r.color ) ) {
                right = r;
            }
        }
        if ( ( it = props.find( "border-top" ) ) != props.end() ) {
            if ( css_utils::parse_border_side( it->second, t.width, t.type, t.color ) ) {
                top = t;
            }
        }
        if ( ( it = props.find( "border-bottom" ) ) != props.end() ) {
            if ( css_utils::parse_border_side( it->second, b.width, b.type, b.color ) ) {
                bottom = b;
            }
        }
    }

    void persistent_border::store( sml::CT_Border& ov ) const
    {
        if ( left.present() ) {
            left.get().store( ov.left.getset() );
        }
        if ( right.present() ) {
            right.get().store( ov.right.getset() );
        }
        if ( top.present() ) {
            top.get().store( ov.top.getset() );
        }
        if ( bottom.present() ) {
            bottom.get().store( ov.bottom.getset() );
        }

    }

    persistent_border::persistent_border( const sml::CT_Border& in_border, const persistent_theme& theme, const persistent_color_table& colors )
    {
        if ( in_border.left.present() ) {
            left    = persistent_border_side( in_border.left.get(), theme, colors );
        }
        if ( in_border.top.present() ) {
            top     = persistent_border_side( in_border.top.get(), theme, colors );
        }
        if ( in_border.right.present() ) {
            right   = persistent_border_side( in_border.right.get(), theme, colors );
        }
        if ( in_border.bottom.present() ) {
            bottom  = persistent_border_side( in_border.bottom.get(), theme, colors );
        }
    }

    void persistent_border::apply( border_manager& bm, const size_t row, const size_t col, const bool is_import /* = true */ ) const
    {
        if ( left.present() && left.get().type != "none" ) {
            bm.border( geometry::rectangle_type( geometry::point( ( boost::uint_fast32_t ) row, ( boost::uint_fast32_t ) col ) ), border_types::left, left.get().str(), is_import );
        }
        if ( top.present() && top.get().type != "none" ) {
            bm.border( geometry::rectangle_type( geometry::point( ( boost::uint_fast32_t ) row, ( boost::uint_fast32_t ) col ) ), border_types::top, top.get().str(), is_import );
        }
        if ( right.present() && right.get().type != "none" ) {
            bm.border( geometry::rectangle_type( geometry::point( ( boost::uint_fast32_t ) row, ( boost::uint_fast32_t ) col ) ), border_types::right, right.get().str(), is_import );
        }
        if ( bottom.present() && bottom.get().type != "none" ) {
            bm.border( geometry::rectangle_type( geometry::point( ( boost::uint_fast32_t ) row, ( boost::uint_fast32_t ) col ) ), border_types::bottom, bottom.get().str(), is_import );
        }
    }

    void persistent_border::apply( set_conditional_format& cf ) const
    {
        if ( left.present() && left.get().type != "none" ) {
            cf.add_border( conditional_format_border_types::left, left.get().str() );
        }
        if ( top.present() && top.get().type != "none" ) {
            cf.add_border( conditional_format_border_types::top, top.get().str() );
        }
        if ( right.present() && right.get().type != "none" ) {
            cf.add_border( conditional_format_border_types::right, right.get().str() );
        }
        if ( bottom.present() && bottom.get().type != "none" ) {
            cf.add_border( conditional_format_border_types::bottom, bottom.get().str() );
        }
    }

}
