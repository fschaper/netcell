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
#include "precompiled_header.hpp"
#include <wss/set_conditional_format.hpp>
#include "conditional_format_style_unlock_type.hpp"

set_conditional_format::set_conditional_format()
    : m_format_style_unlock_information( new cf::format_style_unlock_type() ) {}

set_conditional_format::set_conditional_format( const variant& operands, const std::string& rule, const std::string& s, const set_conditional_format::selected_ranges_type& selected_ranges, border_map_type& borders )
    : m_operands( operands )
    , m_rule( rule )
    , m_selected_range( selected_ranges )
    , m_format_style_unlock_information( new cf::format_style_unlock_type() )
{
    style( s );
    if ( !  borders.empty() ) {
        m_format_style_unlock_information->border.reset( borders );
    }
}

const cf::shared_format_style_unlock_type& set_conditional_format::format_style_unlock_information() const
{
    return m_format_style_unlock_information;
}

void set_conditional_format::format_style_unlock_information( const cf::shared_format_style_unlock_type& val )
{
    m_format_style_unlock_information = val;
}
void set_conditional_format::format( const std::string& f )
{
    if ( ! f.empty() ) {
        m_format_style_unlock_information->format.reset( cf::format_type( f ) );
    }
}

void set_conditional_format::style( const std::string& s )
{
    if ( ! s.empty() ) {
        m_format_style_unlock_information->style.reset( style_set_type::unserialize( s ) );
    }
}

bool set_conditional_format::unlock_cells() const
{
    return m_format_style_unlock_information->unlocked && *m_format_style_unlock_information->unlocked;
}

void set_conditional_format::unlock_cells( const bool unlock )
{
    m_format_style_unlock_information->unlocked.reset( unlock );
}

void set_conditional_format::add_border( const conditional_format_border_types::type t, const std::string& style )
{
    if ( !m_format_style_unlock_information->border ) {
        m_format_style_unlock_information->border.reset( conditional_format_border_type() );
    }
    m_format_style_unlock_information->border->insert_into_map( t, border_style_flyweight_type( style ) );
}
