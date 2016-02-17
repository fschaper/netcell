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


#include "sml-queryTable_writers.hpp"
#include "sml-queryTable_literals.hpp"

namespace spreadsheetml
{
	namespace xio
	{
		void CT_QueryTableField_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_queryTable_id_literal, context()->serialize(t()->id));
			if (t()->name.present())
				w.attribute(0, sml_queryTable_name_literal, context()->serialize(t()->name.get()));
			if (t()->dataBound != true)
				w.attribute(0, sml_queryTable_dataBound_literal, context()->serialize(t()->dataBound));
			if (t()->rowNumbers != false)
				w.attribute(0, sml_queryTable_rowNumbers_literal, context()->serialize(t()->rowNumbers));
			if (t()->fillFormulas != false)
				w.attribute(0, sml_queryTable_fillFormulas_literal, context()->serialize(t()->fillFormulas));
			if (t()->clipped != false)
				w.attribute(0, sml_queryTable_clipped_literal, context()->serialize(t()->clipped));
			if (t()->tableColumnId != 0U)
				w.attribute(0, sml_queryTable_tableColumnId_literal, context()->serialize(t()->tableColumnId));
			if (t()->extLst.present()) {
				w.start_element(0, sml_queryTable_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_queryTable_extLst_literal);
			}
		}

		void CT_QueryTableFields_writer::write_target_to(xml_writer& w) {
			if (t()->count != 0U)
				w.attribute(0, sml_queryTable_count_literal, context()->serialize(t()->count));
			for (size_t sqi = 0; sqi<t()->queryTableField.size(); ++sqi) {
				w.start_element(0, sml_queryTable_queryTableField_literal);
				_queryTableField_writer.get_writer(context(), &t()->queryTableField[sqi])->write_target_to(w);
				w.end_element(0, sml_queryTable_queryTableField_literal);
			}
		}

		void CT_DeletedField_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_queryTable_name_literal, context()->serialize(t()->name));
		}

		void CT_QueryTableDeletedFields_writer::write_target_to(xml_writer& w) {
			if (t()->count.present())
				w.attribute(0, sml_queryTable_count_literal, context()->serialize(t()->count.get()));
			for (size_t sqi = 0; sqi<t()->deletedField.size(); ++sqi) {
				w.start_element(0, sml_queryTable_deletedField_literal);
				_deletedField_writer.get_writer(context(), &t()->deletedField[sqi])->write_target_to(w);
				w.end_element(0, sml_queryTable_deletedField_literal);
			}
		}

		void CT_QueryTableRefresh_writer::write_target_to(xml_writer& w) {
			if (t()->preserveSortFilterLayout != true)
				w.attribute(0, sml_queryTable_preserveSortFilterLayout_literal, context()->serialize(t()->preserveSortFilterLayout));
			if (t()->fieldIdWrapped != false)
				w.attribute(0, sml_queryTable_fieldIdWrapped_literal, context()->serialize(t()->fieldIdWrapped));
			if (t()->headersInLastRefresh != true)
				w.attribute(0, sml_queryTable_headersInLastRefresh_literal, context()->serialize(t()->headersInLastRefresh));
			if (t()->minimumVersion != 0)
				w.attribute(0, sml_queryTable_minimumVersion_literal, context()->serialize(t()->minimumVersion));
			if (t()->nextId != 1U)
				w.attribute(0, sml_queryTable_nextId_literal, context()->serialize(t()->nextId));
			if (t()->unboundColumnsLeft != 0U)
				w.attribute(0, sml_queryTable_unboundColumnsLeft_literal, context()->serialize(t()->unboundColumnsLeft));
			if (t()->unboundColumnsRight != 0U)
				w.attribute(0, sml_queryTable_unboundColumnsRight_literal, context()->serialize(t()->unboundColumnsRight));
			w.start_element(0, sml_queryTable_queryTableFields_literal);
			_queryTableFields_writer.get_writer(context(), &t()->queryTableFields)->write_target_to(w);
			w.end_element(0, sml_queryTable_queryTableFields_literal);
			if (t()->queryTableDeletedFields.present()) {
				w.start_element(0, sml_queryTable_queryTableDeletedFields_literal);
				_queryTableDeletedFields_writer.get_writer(context(), &t()->queryTableDeletedFields.get())->write_target_to(w);
				w.end_element(0, sml_queryTable_queryTableDeletedFields_literal);
			}
			if (t()->sortState.present()) {
				w.start_element(0, sml_queryTable_sortState_literal);
				_sortState_writer.get_writer(context(), &t()->sortState.get())->write_target_to(w);
				w.end_element(0, sml_queryTable_sortState_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, sml_queryTable_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_queryTable_extLst_literal);
			}
		}

		void CT_QueryTable_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_queryTable_name_literal, context()->serialize(t()->name));
			if (t()->headers != true)
				w.attribute(0, sml_queryTable_headers_literal, context()->serialize(t()->headers));
			if (t()->rowNumbers != false)
				w.attribute(0, sml_queryTable_rowNumbers_literal, context()->serialize(t()->rowNumbers));
			if (t()->disableRefresh != false)
				w.attribute(0, sml_queryTable_disableRefresh_literal, context()->serialize(t()->disableRefresh));
			if (t()->backgroundRefresh != true)
				w.attribute(0, sml_queryTable_backgroundRefresh_literal, context()->serialize(t()->backgroundRefresh));
			if (t()->firstBackgroundRefresh != false)
				w.attribute(0, sml_queryTable_firstBackgroundRefresh_literal, context()->serialize(t()->firstBackgroundRefresh));
			if (t()->refreshOnLoad != false)
				w.attribute(0, sml_queryTable_refreshOnLoad_literal, context()->serialize(t()->refreshOnLoad));
			if (t()->growShrinkType != ST_GrowShrinkType::insertDelete_literal)
				w.attribute(0, sml_queryTable_growShrinkType_literal, context()->serialize(t()->growShrinkType));
			if (t()->fillFormulas != false)
				w.attribute(0, sml_queryTable_fillFormulas_literal, context()->serialize(t()->fillFormulas));
			if (t()->removeDataOnSave != false)
				w.attribute(0, sml_queryTable_removeDataOnSave_literal, context()->serialize(t()->removeDataOnSave));
			if (t()->disableEdit != false)
				w.attribute(0, sml_queryTable_disableEdit_literal, context()->serialize(t()->disableEdit));
			if (t()->preserveFormatting != true)
				w.attribute(0, sml_queryTable_preserveFormatting_literal, context()->serialize(t()->preserveFormatting));
			if (t()->adjustColumnWidth != true)
				w.attribute(0, sml_queryTable_adjustColumnWidth_literal, context()->serialize(t()->adjustColumnWidth));
			if (t()->intermediate != false)
				w.attribute(0, sml_queryTable_intermediate_literal, context()->serialize(t()->intermediate));
			w.attribute(0, sml_queryTable_connectionId_literal, context()->serialize(t()->connectionId));
			if (t()->autoFormatId.present())
				w.attribute(0, sml_queryTable_autoFormatId_literal, context()->serialize(t()->autoFormatId.get()));
			if (t()->applyNumberFormats.present())
				w.attribute(0, sml_queryTable_applyNumberFormats_literal, context()->serialize(t()->applyNumberFormats.get()));
			if (t()->applyBorderFormats.present())
				w.attribute(0, sml_queryTable_applyBorderFormats_literal, context()->serialize(t()->applyBorderFormats.get()));
			if (t()->applyFontFormats.present())
				w.attribute(0, sml_queryTable_applyFontFormats_literal, context()->serialize(t()->applyFontFormats.get()));
			if (t()->applyPatternFormats.present())
				w.attribute(0, sml_queryTable_applyPatternFormats_literal, context()->serialize(t()->applyPatternFormats.get()));
			if (t()->applyAlignmentFormats.present())
				w.attribute(0, sml_queryTable_applyAlignmentFormats_literal, context()->serialize(t()->applyAlignmentFormats.get()));
			if (t()->applyWidthHeightFormats.present())
				w.attribute(0, sml_queryTable_applyWidthHeightFormats_literal, context()->serialize(t()->applyWidthHeightFormats.get()));
			if (t()->queryTableRefresh.present()) {
				w.start_element(0, sml_queryTable_queryTableRefresh_literal);
				_queryTableRefresh_writer.get_writer(context(), &t()->queryTableRefresh.get())->write_target_to(w);
				w.end_element(0, sml_queryTable_queryTableRefresh_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, sml_queryTable_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_queryTable_extLst_literal);
			}
		}

		void sml_queryTable_writer::write_target_to(xml_writer& w) {
			if (t()->queryTable.present()) {
				w.start_element(0, sml_queryTable_queryTable_literal);
					w.attribute(0, sml_queryTable_xmlns_literal, sml_queryTable_http_colon__slash__slash_schemas_dot_openxmlformats_dot_org_slash_spreadsheetml_slash_2006_slash_main_literal);
					w.attribute(sml_queryTable_xmlns_literal, sml_queryTable_xsd_literal, sml_queryTable_http_colon__slash__slash_www_dot_w3_dot_org_slash_2001_slash_XMLSchema_literal);
				_queryTable_writer.get_writer(context(), &t()->queryTable.get())->write_target_to(w);
				w.end_element(0, sml_queryTable_queryTable_literal);
			}
		}

	}
}
