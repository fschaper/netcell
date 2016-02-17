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
#include "wss/range_node.hpp"

range_node::range_node( const range_node& other )
    : reference_base_node( other )
    , m_range( other.m_range )
    , m_is_single_cell( other.m_is_single_cell )
    , m_is_ref_error( other.m_is_ref_error )
{}

range_node::range_node( const weak_worksheet_type& ws, const sheet_range& sr, bool is_single_cell, bool is_ref_error, const std::string& workbook, const std::string& worksheet )
    : reference_base_node( ws, workbook, worksheet )
    , m_range( sr )
    , m_is_single_cell( is_single_cell )
    , m_is_ref_error( is_ref_error )
{}

const sheet_range& range_node::range() const
{
    return m_range;
}

void range_node::range( sheet_range val )
{
    m_range = val;
}

bool range_node::is_single_cell() const
{
    return m_is_single_cell;
}

range_node::auto_type range_node::create( const weak_worksheet_type& ws, const sheet_range& sr, bool is_single_cell, bool is_ref_error, const std::string& workbook, const std::string& worksheet )
{
    return auto_type( memory::pooled_creator<range_node>::create( ws, sr, is_single_cell, is_ref_error, workbook, worksheet ) );
}

bool range_node::is_ref_error() const
{
    return m_is_ref_error;
}

// void range_node::is_ref_error( bool val )
// {
//  m_is_ref_error = val;
// }
