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
#include "wss/reference_base_node.hpp"

reference_base_node::reference_base_node( const reference_base_node& other )
    : m_worksheet_object( other.m_worksheet_object )
    , m_workbook()
    , m_worksheet()
    , m_workbook_given( other.m_workbook_given )
    , m_worksheet_given( other.m_worksheet_given )
{
    if ( other.m_worksheet.get() != NULL ) {
        if ( other.m_workbook.get() != NULL ) {
            m_workbook.reset( new std::string( other.ref_error_workbook() ) );
        }
        m_worksheet.reset( new std::string( other.ref_error_worksheet() ) );
    }
}

reference_base_node::reference_base_node( const weak_worksheet_type& ws, const std::string& workbook, const std::string& worksheet )
    : m_worksheet_object( ws )
    , m_workbook_given( false )
    , m_worksheet_given( false )
{
    if ( !workbook.empty() ) {
        m_workbook_given = true;
        m_workbook.reset( new std::string( workbook ) );
    }
    if ( !worksheet.empty() ) {
        m_worksheet_given = true;
        m_worksheet.reset( new std::string( worksheet ) );
    }
}

const weak_worksheet_type& reference_base_node::worksheet() const
{
    return m_worksheet_object;
}

reference_base_node::~reference_base_node()
{}

bool reference_base_node::has_workbook() const
{
    return m_workbook_given;
}

bool reference_base_node::has_worksheet() const
{
    return m_worksheet_given;
}

std::string reference_base_node::ref_error_worksheet() const
{
    static const std::string empty;
    return ( m_worksheet.get() != NULL ) ? *m_worksheet : empty;
}

std::string reference_base_node::ref_error_workbook() const
{
    static const std::string empty;
    return ( m_workbook.get() != NULL ) ? *m_workbook : empty;
}
