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

#include "wss/sparse_range.hpp"
#include "wss/interpreter_context.hpp"
#include "wss/range_reference.hpp"

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
# include <boost/foreach.hpp>
#endif

sparse_range_array::sparse_range_array( range_reference& rr, interpreter_context& ic )
    : m_ic( ic )
    , m_position( rr.actualize().position() )
{
    foreach( const shared_dependency_type & d, *rr.actualize()->lock() ) {
        m_sparse_map[ ( ( d->position().row() - m_position.upper_left().row() ) * m_position.column_count() ) + ( d->position().column() - m_position.upper_left().column() ) ] = d;
    }
}

sparse_range_array::sparse_range_array( const sparse_range_array& other )
    : m_sparse_map( other.m_sparse_map )
    , m_ic( other.m_ic )
    , m_position( other.m_position )
{}

sparse_range_array::size_type sparse_range_array::size() const
{
    return m_position.count();
}

sparse_range_array::size_type sparse_range_array::width() const
{
    return m_position.column_count();
}

const sheet_range& sparse_range_array::position() const
{
    return m_position;
}

variant sparse_range_array::operator ()( unsigned int x, unsigned int y ) const
{
    container_type::const_iterator it( m_sparse_map.find( ( ( y * m_position.column_count() ) +  x ) ) );
    if ( it == m_sparse_map.end() ) {
        return variant();
    } else {
        return it->second->value( m_ic );
    }
}

variant sparse_range_array::operator[]( unsigned int index ) const
{
    container_type::const_iterator it( m_sparse_map.find( index ) );
    if ( it == m_sparse_map.end() ) {
        return variant();
    } else {
        return it->second->value( m_ic );
    }
}
