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
 *  Florian Schaper <florian.schaper@jedox.com>
 */

#include "precompiled_header.hpp"
#include "wss/sheet_range.hpp"
#include "wss/a1conversion.hpp"

namespace geometry
{
    template<>
    generic_rectangle<sheet_point>::generic_rectangle( const sheet_point& p1, const sheet_point& p2 )
        : m_upper_left( std::min( p1.row(), p2.row() ), std::min( p1.column(), p2.column() ), p1.type() )
        , m_lower_right( std::max( p1.row(), p2.row() ), std::max( p1.column(), p2.column() ), p2.type() )
    {
        if ( m_lower_right != m_upper_left
                && ( m_upper_left.type() != reference::relative || m_lower_right.type() != reference::relative ) ) {
            int upper_left_reference = reference::relative;
            int lower_right_reference = reference::relative;

            if ( p1.row() <= p2.row() ) {
                upper_left_reference |= ( p1.type() & reference::absolute_row );
                lower_right_reference |= ( p2.type() & reference::absolute_row );
            } else {
                upper_left_reference |= ( p2.type() & reference::absolute_row );
                lower_right_reference |= ( p1.type() & reference::absolute_row );
            }

            if ( p1.column() <= p2.column() ) {
                upper_left_reference |= ( p1.type() & reference::absolute_column );
                lower_right_reference |= ( p2.type() & reference::absolute_column );
            } else {
                upper_left_reference |= ( p2.type() & reference::absolute_column );
                lower_right_reference |= ( p1.type() & reference::absolute_column );
            }

            m_upper_left = sheet_point( m_upper_left.row(), m_upper_left.column(), static_cast<reference::type>( upper_left_reference ) );
            m_lower_right = sheet_point( m_lower_right.row(), m_lower_right.column(), static_cast<reference::type>( lower_right_reference ) );
        }
    }
}

// force template instantiation for win32 linkage
template class geometry::generic_rectangle<sheet_point>;

std::ostream& operator <<( std::ostream& os, const sheet_range& r )
{
    if ( !os.good() ) {
        return os;
    }

    std::ostream::sentry sentry( os );
    if ( sentry ) {
        switch ( os.iword( a1conversion::formatting::allocator() ) ) {
            case a1conversion::formatting::a1:
                os << a1conversion::to_a1::from_range( r );
                break;
            default:
                os << "{" << r.upper_left() << "," << r.lower_right() << "}";
                break;
        }
    }
    return os;
}
