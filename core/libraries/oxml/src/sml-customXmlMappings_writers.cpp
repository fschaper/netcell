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


#include "sml-customXmlMappings_writers.hpp"
#include "sml-customXmlMappings_literals.hpp"

namespace spreadsheetml
{
	namespace xio
	{
		void CT_Schema_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_customXmlMappings_ID_literal, context()->serialize(t()->ID));
			if (t()->SchemaRef.present())
				w.attribute(0, sml_customXmlMappings_SchemaRef_literal, context()->serialize(t()->SchemaRef.get()));
			if (t()->Namespace.present())
				w.attribute(0, sml_customXmlMappings_Namespace_literal, context()->serialize(t()->Namespace.get()));
		}

		void CT_DataBinding_writer::write_target_to(xml_writer& w) {
			if (t()->DataBindingName.present())
				w.attribute(0, sml_customXmlMappings_DataBindingName_literal, context()->serialize(t()->DataBindingName.get()));
			if (t()->FileBinding.present())
				w.attribute(0, sml_customXmlMappings_FileBinding_literal, context()->serialize(t()->FileBinding.get()));
			if (t()->ConnectionID.present())
				w.attribute(0, sml_customXmlMappings_ConnectionID_literal, context()->serialize(t()->ConnectionID.get()));
			if (t()->FileBindingName.present())
				w.attribute(0, sml_customXmlMappings_FileBindingName_literal, context()->serialize(t()->FileBindingName.get()));
			w.attribute(0, sml_customXmlMappings_DataBindingLoadMode_literal, context()->serialize(t()->DataBindingLoadMode));
		}

		void CT_Map_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_customXmlMappings_ID_literal, context()->serialize(t()->ID));
			w.attribute(0, sml_customXmlMappings_Name_literal, context()->serialize(t()->Name));
			w.attribute(0, sml_customXmlMappings_RootElement_literal, context()->serialize(t()->RootElement));
			w.attribute(0, sml_customXmlMappings_SchemaID_literal, context()->serialize(t()->SchemaID));
			w.attribute(0, sml_customXmlMappings_ShowImportExportValidationErrors_literal, context()->serialize(t()->ShowImportExportValidationErrors));
			w.attribute(0, sml_customXmlMappings_AutoFit_literal, context()->serialize(t()->AutoFit));
			w.attribute(0, sml_customXmlMappings_Append_literal, context()->serialize(t()->Append));
			w.attribute(0, sml_customXmlMappings_PreserveSortAFLayout_literal, context()->serialize(t()->PreserveSortAFLayout));
			w.attribute(0, sml_customXmlMappings_PreserveFormat_literal, context()->serialize(t()->PreserveFormat));
			if (t()->DataBinding.present()) {
				w.start_element(0, sml_customXmlMappings_DataBinding_literal);
				_DataBinding_writer.get_writer(context(), &t()->DataBinding.get())->write_target_to(w);
				w.end_element(0, sml_customXmlMappings_DataBinding_literal);
			}
		}

		void CT_MapInfo_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_customXmlMappings_SelectionNamespaces_literal, context()->serialize(t()->SelectionNamespaces));
			for (size_t sqi = 0; sqi<t()->Schema.size(); ++sqi) {
				w.start_element(0, sml_customXmlMappings_Schema_literal);
				_Schema_writer.get_writer(context(), &t()->Schema[sqi])->write_target_to(w);
				w.end_element(0, sml_customXmlMappings_Schema_literal);
			}
			for (size_t sqi = 0; sqi<t()->Map.size(); ++sqi) {
				w.start_element(0, sml_customXmlMappings_Map_literal);
				_Map_writer.get_writer(context(), &t()->Map[sqi])->write_target_to(w);
				w.end_element(0, sml_customXmlMappings_Map_literal);
			}
		}

		void sml_customXmlMappings_writer::write_target_to(xml_writer& w) {
			if (t()->MapInfo.present()) {
				w.start_element(0, sml_customXmlMappings_MapInfo_literal);
					w.attribute(0, sml_customXmlMappings_xmlns_literal, sml_customXmlMappings_http_colon__slash__slash_schemas_dot_openxmlformats_dot_org_slash_spreadsheetml_slash_2006_slash_main_literal);
					w.attribute(sml_customXmlMappings_xmlns_literal, sml_customXmlMappings_xsd_literal, sml_customXmlMappings_http_colon__slash__slash_www_dot_w3_dot_org_slash_2001_slash_XMLSchema_literal);
				_MapInfo_writer.get_writer(context(), &t()->MapInfo.get())->write_target_to(w);
				w.end_element(0, sml_customXmlMappings_MapInfo_literal);
			}
		}

	}
}
