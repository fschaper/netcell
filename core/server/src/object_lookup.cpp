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
 *  Frieder Hofmann <frieder.hofmann@jedox.com>
 */

#include "precompiled_header.hpp"
#include "object_lookup.hpp"

#include "wss/worksheet.hpp"
#include "wss/workbook.hpp"
#include "wss/application.hpp"
#include "wss/server.hpp"
#include "wss/session.hpp"

shared_worksheet_type object_lookup::worksheet( session& s, const shared_worksheet_type& ws, const utf8_ci_string& name )
{
    return ws->parent()->get( s, name );
}

shared_worksheet_type object_lookup::worksheet( session& s, const shared_worksheet_type& ws, const utf8_ci_string& workbook_name, const utf8_ci_string& worksheet_name )
{
    return ws->parent()->parent()->get( s, workbook_name )->get( s, worksheet_name );
}

shared_worksheet_type object_lookup::worksheet( session& s, const shared_worksheet_type& ws, const uuid_type& worksheet_id )
{
    return ws->parent()->get( s, worksheet_id );
}

shared_worksheet_type object_lookup::worksheet( session& s, const shared_worksheet_type& ws, const utf8_ci_string& workbook_name, const uuid_type& worksheet_id )
{
    return ws->parent()->parent()->get( s, workbook_name )->get( s, worksheet_id );
}

shared_worksheet_type object_lookup::worksheet( session& s, const shared_worksheet_type& ws, const uuid_type& workbook_id, const uuid_type& worksheet_id )
{
    return ws->parent()->parent()->get( s, workbook_id )->get( s, worksheet_id );
}

shared_workbook_type object_lookup::workbook( session& s, const shared_worksheet_type& ws, const utf8_ci_string& workbook_name )
{
    return ws->parent()->parent()->get( s, workbook_name );
}

shared_workbook_type object_lookup::workbook( session& s, const shared_worksheet_type& ws, const uuid_type& workbook_id )
{
    return ws->parent()->parent()->get( s, workbook_id );
}

shared_workbook_type object_lookup::workbook( session& s, const shared_application_type& app, const utf8_ci_string& workbook_name )
{
    return app->get( s, workbook_name );
}
