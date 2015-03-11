/**
*  \file
*  Copyright (C) 2006-2009 Jedox AG, Freiburg i.Br., Germany
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
*  \Author
*  Florian Schaper <florian.schaper@jedox.com>
*/

#include "stdafx.h"
#include "command_line_handler.hpp"

command_line_handler::command_line_handler()
    : m_argument_count( 0 )
{}

void command_line_handler::ParseParam( const TCHAR* pszParam, BOOL bFlag, BOOL bLast )
{
    USES_CONVERSION;

    switch ( m_argument_count++ ) {
        case 0:
            m_crash_dump_file_path = pszParam;
            break;

        case 1:
            m_product_version = W2A( pszParam );
            break;

        default:
            break;
    }
}

unsigned int command_line_handler::get_argument_count() const
{
    return m_argument_count;
}

const CString& command_line_handler::get_crash_dump_file_path() const
{
    return m_crash_dump_file_path;
}

const std::string& command_line_handler::get_product_version() const
{
    return m_product_version;
}

