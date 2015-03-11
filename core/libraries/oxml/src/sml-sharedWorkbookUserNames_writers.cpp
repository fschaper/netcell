/**
 *  \file
 *  Copyright (C) 2006-2009 Jedox AG
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
 */


// This file has been auto-generated. Don't change it by hand!


#include "sml-sharedWorkbookUserNames_writers.hpp"
#include "sml-sharedWorkbookUserNames_literals.hpp"

namespace spreadsheetml
{
	namespace xio
	{
		void CT_SharedUser_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_sharedWorkbookUserNames_guid_literal, context()->serialize(t()->guid));
			w.attribute(0, sml_sharedWorkbookUserNames_name_literal, context()->serialize(t()->name));
			w.attribute(0, sml_sharedWorkbookUserNames_id_literal, context()->serialize(t()->id));
			w.attribute(0, sml_sharedWorkbookUserNames_dateTime_literal, context()->serialize(t()->dateTime));
			if (t()->extLst.present()) {
				w.start_element(0, sml_sharedWorkbookUserNames_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_sharedWorkbookUserNames_extLst_literal);
			}
		}

		void CT_Users_writer::write_target_to(xml_writer& w) {
			if (t()->count.present())
				w.attribute(0, sml_sharedWorkbookUserNames_count_literal, context()->serialize(t()->count.get()));
			for (size_t sqi = 0; sqi<t()->userInfo.size(); ++sqi) {
				w.start_element(0, sml_sharedWorkbookUserNames_userInfo_literal);
				_userInfo_writer.get_writer(context(), &t()->userInfo[sqi])->write_target_to(w);
				w.end_element(0, sml_sharedWorkbookUserNames_userInfo_literal);
			}
		}

		void sml_sharedWorkbookUserNames_writer::write_target_to(xml_writer& w) {
			if (t()->users.present()) {
				w.start_element(0, sml_sharedWorkbookUserNames_users_literal);
					w.attribute(0, sml_sharedWorkbookUserNames_xmlns_literal, sml_sharedWorkbookUserNames_http_colon__slash__slash_schemas_dot_openxmlformats_dot_org_slash_spreadsheetml_slash_2006_slash_main_literal);
					w.attribute(sml_sharedWorkbookUserNames_xmlns_literal, sml_sharedWorkbookUserNames_xsd_literal, sml_sharedWorkbookUserNames_http_colon__slash__slash_www_dot_w3_dot_org_slash_2001_slash_XMLSchema_literal);
				_users_writer.get_writer(context(), &t()->users.get())->write_target_to(w);
				w.end_element(0, sml_sharedWorkbookUserNames_users_literal);
			}
		}

	}
}
