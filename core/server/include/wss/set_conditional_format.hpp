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
 *  Frieder Hofmann <frieder.hofmann@jedox.com>
 */

#pragma once

#include <wss/define.hpp>
#include <wss/rectangle.hpp>
#include <wss/variant.hpp>
#include <wss/type.hpp>
#include <wss/border_types.hpp>
#include <wss/conditional_format_manager.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <boost/cstdint.hpp>
#endif

namespace cf
{
    struct format_style_unlock_type;
    typedef boost::shared_ptr<format_style_unlock_type> shared_format_style_unlock_type;
}

/*!
 * \brief
 *  struct to set a conditional format rule
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
class WSS_MODULE set_conditional_format
{
public:
    typedef boost::int_fast32_t lookup_id_type;
    typedef sheet_range::rectangles_type selected_ranges_type;
    typedef std::map<conditional_format_border_types::type, border_style_flyweight_type> border_map_type;

    set_conditional_format();

    set_conditional_format( const variant& operands, const std::string& rule, const std::string& s, const set_conditional_format::selected_ranges_type& selected_ranges, border_map_type& borders );

    inline const variant& operands() const {
        return m_operands;
    }

    inline void operands( const variant& val ) {
        m_operands = val;
    }

    inline const std::string& rule() const {
        return m_rule;
    }

    inline void rule( const std::string& val ) {
        m_rule = val;
    }

    inline const selected_ranges_type& selected_range() const {
        return m_selected_range;
    }

    inline void selected_range( const set_conditional_format::selected_ranges_type& val ) {
        m_selected_range = val;
    }

    inline void selected_range( const set_conditional_format::selected_ranges_type::value_type& val ) {
        m_selected_range.push_back( val );
    }

    bool unlock_cells() const;

    void unlock_cells( const bool unlock );

    inline const sheet_point& position() const {
        static const sheet_point dummy = sheet_point( 0, 0 );
        return !selected_range().empty() ? selected_range().begin()->upper_left() : dummy;
    }

    const cf::shared_format_style_unlock_type& format_style_unlock_information() const;

    void format( const std::string& f );
    void style( const std::string& s );
    void add_border( const conditional_format_border_types::type t, const std::string& style );

    void format_style_unlock_information( const cf::shared_format_style_unlock_type& val );

private:
    variant m_operands;
    std::string m_rule;
    selected_ranges_type m_selected_range;
    cf::shared_format_style_unlock_type m_format_style_unlock_information;
};
