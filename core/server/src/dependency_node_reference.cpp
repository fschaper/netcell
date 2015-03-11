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
#include "wss/dependency_node_reference.hpp"


dependency_node_reference::dependency_node_reference( const sheet_range& position, const weak_worksheet_type& ws )
    : m_position( position )
    , m_worksheet( ws )
{}

dependency_node_reference::~dependency_node_reference()
{
    ( *m_precedents.lock() ).clear();
}

shared_dependency_node_reference_type dependency_node_reference::create( const sheet_range& position, const weak_worksheet_type& ws )
{
    return boost::make_shared<dependency_node_reference>( position, ws );
}

sheet_range dependency_node_reference::position() const
{
    return ( * m_position.lock() );
}

void dependency_node_reference::position( const geometry::rectangle_type& r )
{
    // the position of the reference can change but not the reference type.
    locked_position_type::access p ( m_position );
    ( *p ) = sheet_range( sheet_point( r.upper_left(), ( *p ).upper_left().type() )
                          , sheet_point( r.lower_right(), ( *p ).lower_right().type() ) );
}

locked_dependency_set_type& dependency_node_reference::container()
{
    return m_precedents;
}

weak_worksheet_type dependency_node_reference::worksheet() const
{
    return m_worksheet;
}

void dependency_node_reference::worksheet( const weak_worksheet_type& ws )
{
    m_worksheet = ws;
}

