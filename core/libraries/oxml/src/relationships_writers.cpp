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

#include "relationships_writers.hpp"
#include "relationships_literals.hpp"

namespace rels_ns
{
	namespace xio
	{
		void CT_Relationship_writer::write_target_to(xml_writer& w) {
			if (t()->Id.present())
				w.attribute(0, relationships_Id_literal, context()->serialize(t()->Id.get()));
			if (t()->Type.present())
				w.attribute(0, relationships_Type_literal, context()->serialize(t()->Type.get()));
			if (t()->Target.present())
				w.attribute(0, relationships_Target_literal, context()->serialize(t()->Target.get()));
			if (t()->TargetMode.present())
				w.attribute(0, relationships_TargetMode_literal, context()->serialize(t()->TargetMode.get()));
		}

		void CT_Relationships_writer::write_target_to(xml_writer& w) {
			for (size_t sqi = 0; sqi<t()->Relationship.size(); ++sqi) {
				w.start_element(0, relationships_Relationship_literal);
				_Relationship_writer.get_writer(context(), &t()->Relationship[sqi])->write_target_to(w);
				w.end_element(0, relationships_Relationship_literal);
			}
		}

		void relationships_writer::write_target_to(xml_writer& w) {
			if (t()->Relationships.present()) {
				w.start_element(0, relationships_Relationships_literal);
					w.attribute(0, relationships_xmlns_literal, relationships_http_colon__slash__slash_schemas_dot_openxmlformats_dot_org_slash_package_slash_2006_slash_relationships_literal);
					w.attribute(relationships_xmlns_literal, relationships_xsd_literal, relationships_http_colon__slash__slash_www_dot_w3_dot_org_slash_2001_slash_XMLSchema_literal);
				_Relationships_writer.get_writer(context(), &t()->Relationships.get())->write_target_to(w);
				w.end_element(0, relationships_Relationships_literal);
			}
		}

	}
}
