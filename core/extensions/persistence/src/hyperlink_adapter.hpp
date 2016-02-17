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
 *  Radu Ialovoi <ialovoi@yalos-solutions.com>
 */

#pragma once

#include <oxml/sml-sheet.hpp>
#include "zpackage.hpp"
#include "relations.hpp"
#include <wss/session.hpp>
#include <wss/range.hpp>

namespace xlsx
{
    namespace sml = spreadsheetml;

    class hyperlink_adapter
    {
    private:
        static bool load_relations( package::izpackage& package, const size_t idx, export_helpers::relations& relations );

        static void make_url( session& s, shared_worksheet_type& ws, const sheet_point& cell, const std::string& url, const std::string& tip );
        static void make_sheet( session& s, shared_worksheet_type& ws, const sheet_point& cell, const std::string& location, const std::string& tip );
    public:
        static void from_tags( session& s, const size_t idx, shared_worksheet_type& ws, package::izpackage& package, const sml::CT_Worksheet& in_sheet );
        static void to_tags( session& s, const size_t idx, const std::vector< range >& hyperlinks, const shared_worksheet_type& ws, package::opackage& package, sml::CT_Worksheet& out_sheet, export_helpers::relations& sheet_rels );
    };

}
