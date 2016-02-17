/**
 *  \file
 *  Copyright (C) 2008 - 2009 Jedox AG, Freiburg i.Br., Germany
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
 *  <a href="http://www.jedox.com/license_worksheetserver.txt">
 *    http://www.jedox.com/license_worksheetserver.txt
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
#include "cell_container.hpp"

#include "wss/sheet_point.hpp"
#include "wss/worksheet.hpp"
#include "cell.hpp"

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
# include <boost/foreach.hpp>
#endif // HAS_PRECOMPILED_HEADER == 0

cell_container::cell_container( worksheet& ws )
    : m_worksheet( ws )
{}

bool cell_container::has( const sheet_point& sp ) const
{
    return m_cell_container.find( sp.key() ) != m_cell_container.end();
}

shared_dependency_type cell_container::get( const sheet_point& sp ) const
{
    lookup_type::const_iterator it = m_cell_container.find( sp.key() );
    if ( m_cell_container.end() == it ) {
        return shared_dependency_type();
    }
    return it->second;
}

shared_dependency_type cell_container::create( const sheet_point& sp )
{
    shared_dependency_type sd = cell::create( m_worksheet.shared_from_this(), sp );
    m_cell_container[ sp.key() ] = sd;
    return sd;
}

void cell_container::clear( const sheet_range& sr )
{
    foreach( const sheet_point & sp, sr ) {
        m_cell_container.erase( sp.key() );
    }
}

void cell_container::place( const shared_dependency_type& sd, const sheet_point& sp )
{
    boost::shared_polymorphic_downcast<cell>( sd )->update_position( sp );
    m_cell_container[ sp.key() ] = sd;
}

