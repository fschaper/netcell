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
#include "wss/i_dependency.hpp"
#include "wss/worksheet.hpp"
#include "wss/range_reference.hpp"
#include "wss/invalid_reference_exception.hpp"
#include "cell_manager.hpp"

range_reference::range_reference( const shared_dependency_type& dependent, const sheet_range& r, const shared_dependency_node_reference_type& sld )
    : m_precedents( sld )
    , m_dependent( dependent )
#if defined(_DEBUG)
    , m_debug_position( r )
#endif // _DEBUG
{}

range_reference::~range_reference()
{
    shared_dependency_type reference_holder = m_dependent.lock();
    if ( reference_holder ) {
        shared_dependency_node_reference_type precedents = m_precedents.lock();
        if ( precedents ) {
            shared_worksheet_type sw = precedents->worksheet().lock();
            if ( sw ) {
                sw->cells().unregister_dependency( reference_holder, precedents->position() );
            }
        }
    }
}

i_dependency_reference::reference_type range_reference::type() const
{
    return i_dependency_reference::range_reference;
}

weak_worksheet_type range_reference::worksheet() const
{
    actual a( actualize() );
    return a.is_valid() ? a.worksheet() : weak_worksheet_type();
}

shared_reference_type range_reference::create( const shared_dependency_type& dependent, const sheet_range& r, const shared_dependency_node_reference_type& sld )
{
    return boost::make_shared<range_reference>( dependent, r, sld );
}

range_reference::actual range_reference::actualize() const
{
    return actual( m_precedents.lock() );
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

range_reference::actual::actual( const shared_dependency_node_reference_type& sdn )
    : m_precedents( sdn )
{}

range_reference::actual::actual( const actual& other )
    : m_precedents( other.m_precedents )
{}

bool range_reference::actual::is_valid() const
{
    return m_precedents;
}

locked_dependency_set_type* range_reference::actual::operator->()
{
    if ( ! is_valid() ) {
        throw invalid_reference_exception();
    }
    return &( m_precedents->container() );
}

locked_dependency_set_type& range_reference::actual::operator*()
{
    if ( ! is_valid() ) {
        throw invalid_reference_exception();
    }
    return m_precedents->container();
}

weak_worksheet_type range_reference::actual::worksheet() const
{
    if ( ! is_valid() ) {
        throw invalid_reference_exception();
    }
    return m_precedents->worksheet();
}

void range_reference::actual::worksheet( const weak_worksheet_type& ws )
{
    m_precedents->worksheet( ws );
}

sheet_range range_reference::actual::position() const
{
    if ( ! is_valid() ) {
        throw invalid_reference_exception();
    }
    return m_precedents->position();
}
