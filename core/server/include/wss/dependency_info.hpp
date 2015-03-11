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

#pragma once

#include <wss/sheet_range.hpp>
#include <wss/type.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <boost/uuid/uuid.hpp>
#   include <vector>
#endif

/*!
 * \brief
 * dependency information.
 *
 * for every dependency provides information about the exact
 * position on a application!workbook!worksheet level.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
struct dependency_info {
    dependency_info( const uuid_type& ws_id, const uuid_type& wb_id, const uuid_type& a_id, const sheet_range& c )
        : worksheet_id( ws_id )
        , workbook_id( wb_id )
        , application_id( a_id )
        , coverage( c ) {}

    uuid_type worksheet_id;
    uuid_type workbook_id;
    uuid_type application_id;
    sheet_range coverage;
};

typedef std::vector<dependency_info> dependency_info_list_type;

