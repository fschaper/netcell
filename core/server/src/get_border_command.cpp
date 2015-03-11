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
#include "wss/get_border_command.hpp"
#include "wss/worksheet.hpp"
#include "wss/border_manager.hpp"
#include "wss/invalid_worksheet_exception.hpp"
#include "border.hpp"
#include "wss/non_instantiable.hpp"
#include "wss/session.hpp"

DEFINE_CLONEABLE( get_border_command )

struct result_converter : non_instantiable {
    typedef std::vector<border_style_flyweight_type> return_vec_type;
    static inline return_vec_type convert( const border_vec_type& b_vec ) {
        return_vec_type return_vec;
        return_vec.reserve( b_vec.size() );
        foreach( const border & b, b_vec ) {
            return_vec.push_back( b.style( static_cast<border::border_type::type>( b.type() ) ) );
        }
        return return_vec;
    }
};

get_border_command::result_type get_border_command::value() const
{
    return m_value;
}

void get_border_command::execute()
{
    shared_worksheet_type ws = m_worksheet.lock();
    if ( ! ws ) {
        throw invalid_worksheet_exception();
    }
    result_converter::return_vec_type vec = result_converter::convert( ws->borders().border( m_rect, cf::cf_vec_type(), true, true, true ) );
    m_value.swap( vec );
}

get_border_command::get_border_command( session& s, const sheet_range rect )
    : base_command<i_command>::base_command( s )
    , m_rect( rect )
{
    m_worksheet = s.selected().worksheet();
}
