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


#include "sml-table_writers.hpp"
#include "sml-table_literals.hpp"

namespace spreadsheetml
{
	namespace xio
	{
		void CT_TableFormula_writer::write_target_to(xml_writer& w) {
			if (t()->array != false)
				w.attribute(0, sml_table_array_literal, context()->serialize(t()->array));
			ST_Formula_writer::write_target_to(w);
		}

		void CT_XmlColumnPr_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_table_mapId_literal, context()->serialize(t()->mapId));
			w.attribute(0, sml_table_xpath_literal, context()->serialize(t()->xpath));
			if (t()->denormalized != false)
				w.attribute(0, sml_table_denormalized_literal, context()->serialize(t()->denormalized));
			w.attribute(0, sml_table_xmlDataType_literal, context()->serialize(t()->xmlDataType));
			if (t()->extLst.present()) {
				w.start_element(0, sml_table_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_table_extLst_literal);
			}
		}

		void CT_TableColumn_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_table_id_literal, context()->serialize(t()->id));
			if (t()->uniqueName.present())
				w.attribute(0, sml_table_uniqueName_literal, context()->serialize(t()->uniqueName.get()));
			w.attribute(0, sml_table_name_literal, context()->serialize(t()->name));
			if (t()->totalsRowFunction != ST_TotalsRowFunction::none_literal)
				w.attribute(0, sml_table_totalsRowFunction_literal, context()->serialize(t()->totalsRowFunction));
			if (t()->totalsRowLabel.present())
				w.attribute(0, sml_table_totalsRowLabel_literal, context()->serialize(t()->totalsRowLabel.get()));
			if (t()->queryTableFieldId.present())
				w.attribute(0, sml_table_queryTableFieldId_literal, context()->serialize(t()->queryTableFieldId.get()));
			if (t()->headerRowDxfId.present())
				w.attribute(0, sml_table_headerRowDxfId_literal, context()->serialize(t()->headerRowDxfId.get()));
			if (t()->dataDxfId.present())
				w.attribute(0, sml_table_dataDxfId_literal, context()->serialize(t()->dataDxfId.get()));
			if (t()->totalsRowDxfId.present())
				w.attribute(0, sml_table_totalsRowDxfId_literal, context()->serialize(t()->totalsRowDxfId.get()));
			if (t()->headerRowCellStyle.present())
				w.attribute(0, sml_table_headerRowCellStyle_literal, context()->serialize(t()->headerRowCellStyle.get()));
			if (t()->dataCellStyle.present())
				w.attribute(0, sml_table_dataCellStyle_literal, context()->serialize(t()->dataCellStyle.get()));
			if (t()->totalsRowCellStyle.present())
				w.attribute(0, sml_table_totalsRowCellStyle_literal, context()->serialize(t()->totalsRowCellStyle.get()));
			if (t()->calculatedColumnFormula.present()) {
				w.start_element(0, sml_table_calculatedColumnFormula_literal);
				_calculatedColumnFormula_writer.get_writer(context(), &t()->calculatedColumnFormula.get())->write_target_to(w);
				w.end_element(0, sml_table_calculatedColumnFormula_literal);
			}
			if (t()->totalsRowFormula.present()) {
				w.start_element(0, sml_table_totalsRowFormula_literal);
				_totalsRowFormula_writer.get_writer(context(), &t()->totalsRowFormula.get())->write_target_to(w);
				w.end_element(0, sml_table_totalsRowFormula_literal);
			}
			if (t()->xmlColumnPr.present()) {
				w.start_element(0, sml_table_xmlColumnPr_literal);
				_xmlColumnPr_writer.get_writer(context(), &t()->xmlColumnPr.get())->write_target_to(w);
				w.end_element(0, sml_table_xmlColumnPr_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, sml_table_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_table_extLst_literal);
			}
		}

		void CT_TableColumns_writer::write_target_to(xml_writer& w) {
			if (t()->count.present())
				w.attribute(0, sml_table_count_literal, context()->serialize(t()->count.get()));
			for (size_t sqi = 0; sqi<t()->tableColumn.size(); ++sqi) {
				w.start_element(0, sml_table_tableColumn_literal);
				_tableColumn_writer.get_writer(context(), &t()->tableColumn[sqi])->write_target_to(w);
				w.end_element(0, sml_table_tableColumn_literal);
			}
		}

		void CT_TableStyleInfo_writer::write_target_to(xml_writer& w) {
			if (t()->name.present())
				w.attribute(0, sml_table_name_literal, context()->serialize(t()->name.get()));
			if (t()->showFirstColumn.present())
				w.attribute(0, sml_table_showFirstColumn_literal, context()->serialize(t()->showFirstColumn.get()));
			if (t()->showLastColumn.present())
				w.attribute(0, sml_table_showLastColumn_literal, context()->serialize(t()->showLastColumn.get()));
			if (t()->showRowStripes.present())
				w.attribute(0, sml_table_showRowStripes_literal, context()->serialize(t()->showRowStripes.get()));
			if (t()->showColumnStripes.present())
				w.attribute(0, sml_table_showColumnStripes_literal, context()->serialize(t()->showColumnStripes.get()));
		}

		void CT_Table_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_table_id_literal, context()->serialize(t()->id));
			if (t()->name.present())
				w.attribute(0, sml_table_name_literal, context()->serialize(t()->name.get()));
			w.attribute(0, sml_table_displayName_literal, context()->serialize(t()->displayName));
			if (t()->comment.present())
				w.attribute(0, sml_table_comment_literal, context()->serialize(t()->comment.get()));
			w.attribute(0, sml_table_ref_literal, context()->serialize(t()->ref));
			if (t()->tableType != ST_TableType::worksheet_literal)
				w.attribute(0, sml_table_tableType_literal, context()->serialize(t()->tableType));
			if (t()->headerRowCount != 1U)
				w.attribute(0, sml_table_headerRowCount_literal, context()->serialize(t()->headerRowCount));
			if (t()->insertRow != false)
				w.attribute(0, sml_table_insertRow_literal, context()->serialize(t()->insertRow));
			if (t()->insertRowShift != false)
				w.attribute(0, sml_table_insertRowShift_literal, context()->serialize(t()->insertRowShift));
			if (t()->totalsRowCount != 0U)
				w.attribute(0, sml_table_totalsRowCount_literal, context()->serialize(t()->totalsRowCount));
			if (t()->totalsRowShown != true)
				w.attribute(0, sml_table_totalsRowShown_literal, context()->serialize(t()->totalsRowShown));
			if (t()->published != false)
				w.attribute(0, sml_table_published_literal, context()->serialize(t()->published));
			if (t()->headerRowDxfId.present())
				w.attribute(0, sml_table_headerRowDxfId_literal, context()->serialize(t()->headerRowDxfId.get()));
			if (t()->dataDxfId.present())
				w.attribute(0, sml_table_dataDxfId_literal, context()->serialize(t()->dataDxfId.get()));
			if (t()->totalsRowDxfId.present())
				w.attribute(0, sml_table_totalsRowDxfId_literal, context()->serialize(t()->totalsRowDxfId.get()));
			if (t()->headerRowBorderDxfId.present())
				w.attribute(0, sml_table_headerRowBorderDxfId_literal, context()->serialize(t()->headerRowBorderDxfId.get()));
			if (t()->tableBorderDxfId.present())
				w.attribute(0, sml_table_tableBorderDxfId_literal, context()->serialize(t()->tableBorderDxfId.get()));
			if (t()->totalsRowBorderDxfId.present())
				w.attribute(0, sml_table_totalsRowBorderDxfId_literal, context()->serialize(t()->totalsRowBorderDxfId.get()));
			if (t()->headerRowCellStyle.present())
				w.attribute(0, sml_table_headerRowCellStyle_literal, context()->serialize(t()->headerRowCellStyle.get()));
			if (t()->dataCellStyle.present())
				w.attribute(0, sml_table_dataCellStyle_literal, context()->serialize(t()->dataCellStyle.get()));
			if (t()->totalsRowCellStyle.present())
				w.attribute(0, sml_table_totalsRowCellStyle_literal, context()->serialize(t()->totalsRowCellStyle.get()));
			if (t()->connectionId.present())
				w.attribute(0, sml_table_connectionId_literal, context()->serialize(t()->connectionId.get()));
			if (t()->autoFilter.present()) {
				w.start_element(0, sml_table_autoFilter_literal);
				_autoFilter_writer.get_writer(context(), &t()->autoFilter.get())->write_target_to(w);
				w.end_element(0, sml_table_autoFilter_literal);
			}
			if (t()->sortState.present()) {
				w.start_element(0, sml_table_sortState_literal);
				_sortState_writer.get_writer(context(), &t()->sortState.get())->write_target_to(w);
				w.end_element(0, sml_table_sortState_literal);
			}
			w.start_element(0, sml_table_tableColumns_literal);
			_tableColumns_writer.get_writer(context(), &t()->tableColumns)->write_target_to(w);
			w.end_element(0, sml_table_tableColumns_literal);
			if (t()->tableStyleInfo.present()) {
				w.start_element(0, sml_table_tableStyleInfo_literal);
				_tableStyleInfo_writer.get_writer(context(), &t()->tableStyleInfo.get())->write_target_to(w);
				w.end_element(0, sml_table_tableStyleInfo_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, sml_table_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_table_extLst_literal);
			}
		}

		void sml_table_writer::write_target_to(xml_writer& w) {
			if (t()->table.present()) {
				w.start_element(0, sml_table_table_literal);
					w.attribute(0, sml_table_xmlns_literal, sml_table_http_colon__slash__slash_schemas_dot_openxmlformats_dot_org_slash_spreadsheetml_slash_2006_slash_main_literal);
					w.attribute(sml_table_xmlns_literal, sml_table_xsd_literal, sml_table_http_colon__slash__slash_www_dot_w3_dot_org_slash_2001_slash_XMLSchema_literal);
				_table_writer.get_writer(context(), &t()->table.get())->write_target_to(w);
				w.end_element(0, sml_table_table_literal);
			}
		}

	}
}
