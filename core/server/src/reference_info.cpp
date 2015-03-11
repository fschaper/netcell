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
#include "wss/reference_info.hpp"

reference_info::reference_info()
    : m_relative_worksheet( true )
    , m_is_single_cell( true )
    , m_is_ref_error( false )
    , m_worksheet_given( false )
    , m_workbook_given( false )
{}

reference_info::reference_info( const shared_reference_type& r, bool worksheet_is_relative, bool is_single_cell, bool worksheet_given, bool workbook_given, const shared_worksheet_type& ws, const shared_workbook_type& wb )
    : m_relative_worksheet( worksheet_is_relative )
    , m_is_single_cell( is_single_cell )
    , m_is_ref_error( r )
    , m_reference( r )
    , m_worksheet_given( worksheet_given )
    , m_workbook_given( workbook_given )
    , m_worksheet( ws )
    , m_workbook( wb )
{}

reference_info::reference_info( const reference_info& other )
    : m_relative_worksheet( other.m_relative_worksheet )
    , m_is_single_cell( other.m_is_single_cell )
    , m_is_ref_error( other.m_is_ref_error )
    , m_reference( other.m_reference )
    , m_worksheet_given( other.m_worksheet_given )
    , m_workbook_given( other.m_workbook_given )
    , m_worksheet( m_worksheet_given ? other.m_worksheet : weak_worksheet_type() )
    , m_workbook( m_workbook_given ? other.m_workbook : weak_workbook_type() )
{}

bool reference_info::operator==( const reference_info& rhs ) const
{
    if ( m_relative_worksheet != rhs.m_relative_worksheet
            || m_is_single_cell != rhs.m_is_single_cell
            || m_reference != rhs.m_reference
            || m_is_ref_error != rhs.m_is_ref_error ) {
        return false;
    }
    if ( m_workbook_given && rhs.m_workbook_given ) {
        shared_workbook_type wb = m_workbook.lock();
        shared_workbook_type rhs_wb = rhs.m_workbook.lock();
        if ( wb != rhs_wb ) {
            return false;
        }
    }
    if ( m_worksheet_given && rhs.m_worksheet_given ) {
        shared_worksheet_type ws = m_worksheet.lock();
        shared_worksheet_type rhs_ws = rhs.m_worksheet.lock();
        if ( ws != rhs_ws ) {
            return false;
        }
    }
    return true;
}
