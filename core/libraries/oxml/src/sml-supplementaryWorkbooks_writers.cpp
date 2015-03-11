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


#include "sml-supplementaryWorkbooks_writers.hpp"
#include "sml-supplementaryWorkbooks_literals.hpp"

namespace spreadsheetml
{
	namespace xio
	{
		void CT_ExternalSheetName_writer::write_target_to(xml_writer& w) {
			if (t()->val.present())
				w.attribute(0, sml_supplementaryWorkbooks_val_literal, context()->serialize(t()->val.get()));
		}

		void CT_ExternalSheetNames_writer::write_target_to(xml_writer& w) {
			for (size_t sqi = 0; sqi<t()->sheetName.size(); ++sqi) {
				w.start_element(0, sml_supplementaryWorkbooks_sheetName_literal);
				_sheetName_writer.get_writer(context(), &t()->sheetName[sqi])->write_target_to(w);
				w.end_element(0, sml_supplementaryWorkbooks_sheetName_literal);
			}
		}

		void CT_ExternalDefinedName_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_supplementaryWorkbooks_name_literal, context()->serialize(t()->name));
			if (t()->refersTo.present())
				w.attribute(0, sml_supplementaryWorkbooks_refersTo_literal, context()->serialize(t()->refersTo.get()));
			if (t()->sheetId.present())
				w.attribute(0, sml_supplementaryWorkbooks_sheetId_literal, context()->serialize(t()->sheetId.get()));
		}

		void CT_ExternalDefinedNames_writer::write_target_to(xml_writer& w) {
			for (size_t sqi = 0; sqi<t()->definedName.size(); ++sqi) {
				w.start_element(0, sml_supplementaryWorkbooks_definedName_literal);
				_definedName_writer.get_writer(context(), &t()->definedName[sqi])->write_target_to(w);
				w.end_element(0, sml_supplementaryWorkbooks_definedName_literal);
			}
		}

		void CT_ExternalCell_writer::write_target_to(xml_writer& w) {
			if (t()->r.present())
				w.attribute(0, sml_supplementaryWorkbooks_r_literal, context()->serialize(t()->r.get()));
			if (t()->t != ST_CellType::n_literal)
				w.attribute(0, sml_supplementaryWorkbooks_t_literal, context()->serialize(t()->t));
			if (t()->vm != 0U)
				w.attribute(0, sml_supplementaryWorkbooks_vm_literal, context()->serialize(t()->vm));
			if (t()->v.present()) {
				w.start_element(0, sml_supplementaryWorkbooks_v_literal);
				_v_writer.get_writer(context(), &t()->v.get())->write_target_to(w);
				w.end_element(0, sml_supplementaryWorkbooks_v_literal);
			}
		}

		void CT_ExternalRow_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_supplementaryWorkbooks_r_literal, context()->serialize(t()->r));
			for (size_t sqi = 0; sqi<t()->cell.size(); ++sqi) {
				w.start_element(0, sml_supplementaryWorkbooks_cell_literal);
				_cell_writer.get_writer(context(), &t()->cell[sqi])->write_target_to(w);
				w.end_element(0, sml_supplementaryWorkbooks_cell_literal);
			}
		}

		void CT_ExternalSheetData_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_supplementaryWorkbooks_sheetId_literal, context()->serialize(t()->sheetId));
			if (t()->refreshError != false)
				w.attribute(0, sml_supplementaryWorkbooks_refreshError_literal, context()->serialize(t()->refreshError));
			for (size_t sqi = 0; sqi<t()->row.size(); ++sqi) {
				w.start_element(0, sml_supplementaryWorkbooks_row_literal);
				_row_writer.get_writer(context(), &t()->row[sqi])->write_target_to(w);
				w.end_element(0, sml_supplementaryWorkbooks_row_literal);
			}
		}

		void CT_ExternalSheetDataSet_writer::write_target_to(xml_writer& w) {
			for (size_t sqi = 0; sqi<t()->sheetData.size(); ++sqi) {
				w.start_element(0, sml_supplementaryWorkbooks_sheetData_literal);
				_sheetData_writer.get_writer(context(), &t()->sheetData[sqi])->write_target_to(w);
				w.end_element(0, sml_supplementaryWorkbooks_sheetData_literal);
			}
		}

		void CT_ExternalBook_writer::write_target_to(xml_writer& w) {
			w.attribute(sml_supplementaryWorkbooks_r_literal, sml_supplementaryWorkbooks_id_literal, context()->serialize(t()->id));
			if (t()->sheetNames.present()) {
				w.start_element(0, sml_supplementaryWorkbooks_sheetNames_literal);
				_sheetNames_writer.get_writer(context(), &t()->sheetNames.get())->write_target_to(w);
				w.end_element(0, sml_supplementaryWorkbooks_sheetNames_literal);
			}
			if (t()->definedNames.present()) {
				w.start_element(0, sml_supplementaryWorkbooks_definedNames_literal);
				_definedNames_writer.get_writer(context(), &t()->definedNames.get())->write_target_to(w);
				w.end_element(0, sml_supplementaryWorkbooks_definedNames_literal);
			}
			if (t()->sheetDataSet.present()) {
				w.start_element(0, sml_supplementaryWorkbooks_sheetDataSet_literal);
				_sheetDataSet_writer.get_writer(context(), &t()->sheetDataSet.get())->write_target_to(w);
				w.end_element(0, sml_supplementaryWorkbooks_sheetDataSet_literal);
			}
		}

		void CT_DdeValue_writer::write_target_to(xml_writer& w) {
			if (t()->t != ST_DdeValueType::n_literal)
				w.attribute(0, sml_supplementaryWorkbooks_t_literal, context()->serialize(t()->t));
			w.start_element(0, sml_supplementaryWorkbooks_val_literal);
			_val_writer.get_writer(context(), &t()->val)->write_target_to(w);
			w.end_element(0, sml_supplementaryWorkbooks_val_literal);
		}

		void CT_DdeValues_writer::write_target_to(xml_writer& w) {
			if (t()->rows != 1U)
				w.attribute(0, sml_supplementaryWorkbooks_rows_literal, context()->serialize(t()->rows));
			if (t()->cols != 1U)
				w.attribute(0, sml_supplementaryWorkbooks_cols_literal, context()->serialize(t()->cols));
			for (size_t sqi = 0; sqi<t()->value.size(); ++sqi) {
				w.start_element(0, sml_supplementaryWorkbooks_value_literal);
				_value_writer.get_writer(context(), &t()->value[sqi])->write_target_to(w);
				w.end_element(0, sml_supplementaryWorkbooks_value_literal);
			}
		}

		void CT_DdeItem_writer::write_target_to(xml_writer& w) {
			if (t()->name != "0")
				w.attribute(0, sml_supplementaryWorkbooks_name_literal, context()->serialize(t()->name));
			if (t()->ole != false)
				w.attribute(0, sml_supplementaryWorkbooks_ole_literal, context()->serialize(t()->ole));
			if (t()->advise != false)
				w.attribute(0, sml_supplementaryWorkbooks_advise_literal, context()->serialize(t()->advise));
			if (t()->preferPic != false)
				w.attribute(0, sml_supplementaryWorkbooks_preferPic_literal, context()->serialize(t()->preferPic));
			if (t()->values.present()) {
				w.start_element(0, sml_supplementaryWorkbooks_values_literal);
				_values_writer.get_writer(context(), &t()->values.get())->write_target_to(w);
				w.end_element(0, sml_supplementaryWorkbooks_values_literal);
			}
		}

		void CT_DdeItems_writer::write_target_to(xml_writer& w) {
			for (size_t sqi = 0; sqi<t()->ddeItem.size(); ++sqi) {
				w.start_element(0, sml_supplementaryWorkbooks_ddeItem_literal);
				_ddeItem_writer.get_writer(context(), &t()->ddeItem[sqi])->write_target_to(w);
				w.end_element(0, sml_supplementaryWorkbooks_ddeItem_literal);
			}
		}

		void CT_DdeLink_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_supplementaryWorkbooks_ddeService_literal, context()->serialize(t()->ddeService));
			w.attribute(0, sml_supplementaryWorkbooks_ddeTopic_literal, context()->serialize(t()->ddeTopic));
			if (t()->ddeItems.present()) {
				w.start_element(0, sml_supplementaryWorkbooks_ddeItems_literal);
				_ddeItems_writer.get_writer(context(), &t()->ddeItems.get())->write_target_to(w);
				w.end_element(0, sml_supplementaryWorkbooks_ddeItems_literal);
			}
		}

		void CT_OleItem_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_supplementaryWorkbooks_name_literal, context()->serialize(t()->name));
			if (t()->icon != false)
				w.attribute(0, sml_supplementaryWorkbooks_icon_literal, context()->serialize(t()->icon));
			if (t()->advise != false)
				w.attribute(0, sml_supplementaryWorkbooks_advise_literal, context()->serialize(t()->advise));
			if (t()->preferPic != false)
				w.attribute(0, sml_supplementaryWorkbooks_preferPic_literal, context()->serialize(t()->preferPic));
		}

		void CT_OleItems_writer::write_target_to(xml_writer& w) {
			for (size_t sqi = 0; sqi<t()->oleItem.size(); ++sqi) {
				w.start_element(0, sml_supplementaryWorkbooks_oleItem_literal);
				_oleItem_writer.get_writer(context(), &t()->oleItem[sqi])->write_target_to(w);
				w.end_element(0, sml_supplementaryWorkbooks_oleItem_literal);
			}
		}

		void CT_OleLink_writer::write_target_to(xml_writer& w) {
			w.attribute(sml_supplementaryWorkbooks_r_literal, sml_supplementaryWorkbooks_id_literal, context()->serialize(t()->id));
			w.attribute(0, sml_supplementaryWorkbooks_progId_literal, context()->serialize(t()->progId));
			if (t()->oleItems.present()) {
				w.start_element(0, sml_supplementaryWorkbooks_oleItems_literal);
				_oleItems_writer.get_writer(context(), &t()->oleItems.get())->write_target_to(w);
				w.end_element(0, sml_supplementaryWorkbooks_oleItems_literal);
			}
		}

		void CT_ExternalLink_writer::write_target_to(xml_writer& w) {
			if (t()->externalBook.present()) {
				w.start_element(0, sml_supplementaryWorkbooks_externalBook_literal);
				_externalBook_writer.get_writer(context(), &t()->externalBook.get())->write_target_to(w);
				w.end_element(0, sml_supplementaryWorkbooks_externalBook_literal);
			}
			if (t()->ddeLink.present()) {
				w.start_element(0, sml_supplementaryWorkbooks_ddeLink_literal);
				_ddeLink_writer.get_writer(context(), &t()->ddeLink.get())->write_target_to(w);
				w.end_element(0, sml_supplementaryWorkbooks_ddeLink_literal);
			}
			if (t()->oleLink.present()) {
				w.start_element(0, sml_supplementaryWorkbooks_oleLink_literal);
				_oleLink_writer.get_writer(context(), &t()->oleLink.get())->write_target_to(w);
				w.end_element(0, sml_supplementaryWorkbooks_oleLink_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, sml_supplementaryWorkbooks_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_supplementaryWorkbooks_extLst_literal);
			}
		}

		void sml_supplementaryWorkbooks_writer::write_target_to(xml_writer& w) {
			if (t()->externalLink.present()) {
				w.start_element(0, sml_supplementaryWorkbooks_externalLink_literal);
					w.attribute(0, sml_supplementaryWorkbooks_xmlns_literal, sml_supplementaryWorkbooks_http_colon__slash__slash_schemas_dot_openxmlformats_dot_org_slash_spreadsheetml_slash_2006_slash_main_literal);
					w.attribute(sml_supplementaryWorkbooks_xmlns_literal, sml_supplementaryWorkbooks_r_literal, sml_supplementaryWorkbooks_http_colon__slash__slash_schemas_dot_openxmlformats_dot_org_slash_officeDocument_slash_2006_slash_relationships_literal);
					w.attribute(sml_supplementaryWorkbooks_xmlns_literal, sml_supplementaryWorkbooks_xsd_literal, sml_supplementaryWorkbooks_http_colon__slash__slash_www_dot_w3_dot_org_slash_2001_slash_XMLSchema_literal);
				_externalLink_writer.get_writer(context(), &t()->externalLink.get())->write_target_to(w);
				w.end_element(0, sml_supplementaryWorkbooks_externalLink_literal);
			}
		}

	}
}
