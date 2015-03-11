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

#include "dml-spreadsheetDrawing_writers.hpp"
#include "dml-spreadsheetDrawing_literals.hpp"

namespace drawingml
{
	namespace xio
	{
		void ST_ColID_writer::write_target_to(xml_writer& w) {
			w.write_element_value(context()->serialize(*t()));
		}

		void ST_RowID_writer::write_target_to(xml_writer& w) {
			w.write_element_value(context()->serialize(*t()));
		}

		void CT_Marker_writer::write_target_to(xml_writer& w) {
			w.start_element(0, dml_spreadsheetDrawing_col_literal);
			_col_writer.get_writer(context(), &t()->col)->write_target_to(w);
			w.end_element(0, dml_spreadsheetDrawing_col_literal);
			w.start_element(0, dml_spreadsheetDrawing_colOff_literal);
			_colOff_writer.get_writer(context(), &t()->colOff)->write_target_to(w);
			w.end_element(0, dml_spreadsheetDrawing_colOff_literal);
			w.start_element(0, dml_spreadsheetDrawing_row_literal);
			_row_writer.get_writer(context(), &t()->row)->write_target_to(w);
			w.end_element(0, dml_spreadsheetDrawing_row_literal);
			w.start_element(0, dml_spreadsheetDrawing_rowOff_literal);
			_rowOff_writer.get_writer(context(), &t()->rowOff)->write_target_to(w);
			w.end_element(0, dml_spreadsheetDrawing_rowOff_literal);
		}

		void CT_ShapeNonVisual_writer::write_target_to(xml_writer& w) {
			w.start_element(0, dml_spreadsheetDrawing_cNvPr_literal);
			_cNvPr_writer.get_writer(context(), &t()->cNvPr)->write_target_to(w);
			w.end_element(0, dml_spreadsheetDrawing_cNvPr_literal);
			w.start_element(0, dml_spreadsheetDrawing_cNvSpPr_literal);
			_cNvSpPr_writer.get_writer(context(), &t()->cNvSpPr)->write_target_to(w);
			w.end_element(0, dml_spreadsheetDrawing_cNvSpPr_literal);
		}

		void CT_Shape_writer::write_target_to(xml_writer& w) {
			if (t()->macro.present())
				w.attribute(0, dml_spreadsheetDrawing_macro_literal, context()->serialize(t()->macro.get()));
			if (t()->textlink.present())
				w.attribute(0, dml_spreadsheetDrawing_textlink_literal, context()->serialize(t()->textlink.get()));
			if (t()->fLocksText != true)
				w.attribute(0, dml_spreadsheetDrawing_fLocksText_literal, context()->serialize(t()->fLocksText));
			if (t()->fPublished != false)
				w.attribute(0, dml_spreadsheetDrawing_fPublished_literal, context()->serialize(t()->fPublished));
			w.start_element(0, dml_spreadsheetDrawing_nvSpPr_literal);
			_nvSpPr_writer.get_writer(context(), &t()->nvSpPr)->write_target_to(w);
			w.end_element(0, dml_spreadsheetDrawing_nvSpPr_literal);
			w.start_element(0, dml_spreadsheetDrawing_spPr_literal);
			_spPr_writer.get_writer(context(), &t()->spPr)->write_target_to(w);
			w.end_element(0, dml_spreadsheetDrawing_spPr_literal);
			if (t()->style.present()) {
				w.start_element(0, dml_spreadsheetDrawing_style_literal);
				_style_writer.get_writer(context(), &t()->style.get())->write_target_to(w);
				w.end_element(0, dml_spreadsheetDrawing_style_literal);
			}
			if (t()->txBody.present()) {
				w.start_element(0, dml_spreadsheetDrawing_txBody_literal);
				_txBody_writer.get_writer(context(), &t()->txBody.get())->write_target_to(w);
				w.end_element(0, dml_spreadsheetDrawing_txBody_literal);
			}
		}

		void CT_GroupShapeNonVisual_writer::write_target_to(xml_writer& w) {
			w.start_element(0, dml_spreadsheetDrawing_cNvPr_literal);
			_cNvPr_writer.get_writer(context(), &t()->cNvPr)->write_target_to(w);
			w.end_element(0, dml_spreadsheetDrawing_cNvPr_literal);
			w.start_element(0, dml_spreadsheetDrawing_cNvGrpSpPr_literal);
			_cNvGrpSpPr_writer.get_writer(context(), &t()->cNvGrpSpPr)->write_target_to(w);
			w.end_element(0, dml_spreadsheetDrawing_cNvGrpSpPr_literal);
		}

		void CT_GraphicalObjectFrameNonVisual_writer::write_target_to(xml_writer& w) {
			w.start_element(0, dml_spreadsheetDrawing_cNvPr_literal);
			_cNvPr_writer.get_writer(context(), &t()->cNvPr)->write_target_to(w);
			w.end_element(0, dml_spreadsheetDrawing_cNvPr_literal);
			w.start_element(0, dml_spreadsheetDrawing_cNvGraphicFramePr_literal);
			_cNvGraphicFramePr_writer.get_writer(context(), &t()->cNvGraphicFramePr)->write_target_to(w);
			w.end_element(0, dml_spreadsheetDrawing_cNvGraphicFramePr_literal);
		}

		void CT_GraphicalObjectFrame_writer::write_target_to(xml_writer& w) {
			if (t()->macro.present())
				w.attribute(0, dml_spreadsheetDrawing_macro_literal, context()->serialize(t()->macro.get()));
			if (t()->fPublished != false)
				w.attribute(0, dml_spreadsheetDrawing_fPublished_literal, context()->serialize(t()->fPublished));
			w.start_element(0, dml_spreadsheetDrawing_nvGraphicFramePr_literal);
			_nvGraphicFramePr_writer.get_writer(context(), &t()->nvGraphicFramePr)->write_target_to(w);
			w.end_element(0, dml_spreadsheetDrawing_nvGraphicFramePr_literal);
			w.start_element(0, dml_spreadsheetDrawing_xfrm_literal);
			_xfrm_writer.get_writer(context(), &t()->xfrm)->write_target_to(w);
			w.end_element(0, dml_spreadsheetDrawing_xfrm_literal);
			w.start_element(0, dml_spreadsheetDrawing_graphic_literal);
			_graphic_writer.get_writer(context(), &t()->graphic)->write_target_to(w);
			w.end_element(0, dml_spreadsheetDrawing_graphic_literal);
		}

		void CT_ConnectorNonVisual_writer::write_target_to(xml_writer& w) {
			w.start_element(0, dml_spreadsheetDrawing_cNvPr_literal);
			_cNvPr_writer.get_writer(context(), &t()->cNvPr)->write_target_to(w);
			w.end_element(0, dml_spreadsheetDrawing_cNvPr_literal);
			w.start_element(0, dml_spreadsheetDrawing_cNvCxnSpPr_literal);
			_cNvCxnSpPr_writer.get_writer(context(), &t()->cNvCxnSpPr)->write_target_to(w);
			w.end_element(0, dml_spreadsheetDrawing_cNvCxnSpPr_literal);
		}

		void CT_Connector_writer::write_target_to(xml_writer& w) {
			if (t()->macro.present())
				w.attribute(0, dml_spreadsheetDrawing_macro_literal, context()->serialize(t()->macro.get()));
			if (t()->fPublished != false)
				w.attribute(0, dml_spreadsheetDrawing_fPublished_literal, context()->serialize(t()->fPublished));
			w.start_element(0, dml_spreadsheetDrawing_nvCxnSpPr_literal);
			_nvCxnSpPr_writer.get_writer(context(), &t()->nvCxnSpPr)->write_target_to(w);
			w.end_element(0, dml_spreadsheetDrawing_nvCxnSpPr_literal);
			w.start_element(0, dml_spreadsheetDrawing_spPr_literal);
			_spPr_writer.get_writer(context(), &t()->spPr)->write_target_to(w);
			w.end_element(0, dml_spreadsheetDrawing_spPr_literal);
			if (t()->style.present()) {
				w.start_element(0, dml_spreadsheetDrawing_style_literal);
				_style_writer.get_writer(context(), &t()->style.get())->write_target_to(w);
				w.end_element(0, dml_spreadsheetDrawing_style_literal);
			}
		}

		void CT_PictureNonVisual_writer::write_target_to(xml_writer& w) {
			w.start_element(0, dml_spreadsheetDrawing_cNvPr_literal);
			_cNvPr_writer.get_writer(context(), &t()->cNvPr)->write_target_to(w);
			w.end_element(0, dml_spreadsheetDrawing_cNvPr_literal);
			w.start_element(0, dml_spreadsheetDrawing_cNvPicPr_literal);
			_cNvPicPr_writer.get_writer(context(), &t()->cNvPicPr)->write_target_to(w);
			w.end_element(0, dml_spreadsheetDrawing_cNvPicPr_literal);
		}

		void CT_Picture_writer::write_target_to(xml_writer& w) {
			if (t()->macro != "")
				w.attribute(0, dml_spreadsheetDrawing_macro_literal, context()->serialize(t()->macro));
			if (t()->fPublished != false)
				w.attribute(0, dml_spreadsheetDrawing_fPublished_literal, context()->serialize(t()->fPublished));
			w.start_element(0, dml_spreadsheetDrawing_nvPicPr_literal);
			_nvPicPr_writer.get_writer(context(), &t()->nvPicPr)->write_target_to(w);
			w.end_element(0, dml_spreadsheetDrawing_nvPicPr_literal);
			w.start_element(0, dml_spreadsheetDrawing_blipFill_literal);
			_blipFill_writer.get_writer(context(), &t()->blipFill)->write_target_to(w);
			w.end_element(0, dml_spreadsheetDrawing_blipFill_literal);
			w.start_element(0, dml_spreadsheetDrawing_spPr_literal);
			_spPr_writer.get_writer(context(), &t()->spPr)->write_target_to(w);
			w.end_element(0, dml_spreadsheetDrawing_spPr_literal);
			if (t()->style.present()) {
				w.start_element(0, dml_spreadsheetDrawing_style_literal);
				_style_writer.get_writer(context(), &t()->style.get())->write_target_to(w);
				w.end_element(0, dml_spreadsheetDrawing_style_literal);
			}
		}

		void CT_GroupShape_writer::write_target_to(xml_writer& w) {
			w.start_element(0, dml_spreadsheetDrawing_nvGrpSpPr_literal);
			_nvGrpSpPr_writer.get_writer(context(), &t()->nvGrpSpPr)->write_target_to(w);
			w.end_element(0, dml_spreadsheetDrawing_nvGrpSpPr_literal);
			w.start_element(0, dml_spreadsheetDrawing_grpSpPr_literal);
			_grpSpPr_writer.get_writer(context(), &t()->grpSpPr)->write_target_to(w);
			w.end_element(0, dml_spreadsheetDrawing_grpSpPr_literal);
			if (t()->sp.present()) {
				w.start_element(0, dml_spreadsheetDrawing_sp_literal);
				_sp_writer.get_writer(context(), &t()->sp.get())->write_target_to(w);
				w.end_element(0, dml_spreadsheetDrawing_sp_literal);
			}
			if (t()->grpSp.present()) {
				w.start_element(0, dml_spreadsheetDrawing_grpSp_literal);
				_grpSp_writer.get_writer(context(), &t()->grpSp.get())->write_target_to(w);
				w.end_element(0, dml_spreadsheetDrawing_grpSp_literal);
			}
			if (t()->graphicFrame.present()) {
				w.start_element(0, dml_spreadsheetDrawing_graphicFrame_literal);
				_graphicFrame_writer.get_writer(context(), &t()->graphicFrame.get())->write_target_to(w);
				w.end_element(0, dml_spreadsheetDrawing_graphicFrame_literal);
			}
			if (t()->cxnSp.present()) {
				w.start_element(0, dml_spreadsheetDrawing_cxnSp_literal);
				_cxnSp_writer.get_writer(context(), &t()->cxnSp.get())->write_target_to(w);
				w.end_element(0, dml_spreadsheetDrawing_cxnSp_literal);
			}
			if (t()->pic.present()) {
				w.start_element(0, dml_spreadsheetDrawing_pic_literal);
				_pic_writer.get_writer(context(), &t()->pic.get())->write_target_to(w);
				w.end_element(0, dml_spreadsheetDrawing_pic_literal);
			}
		}

		void CT_AnchorClientData_writer::write_target_to(xml_writer& w) {
			if (t()->fLocksWithSheet != true)
				w.attribute(0, dml_spreadsheetDrawing_fLocksWithSheet_literal, context()->serialize(t()->fLocksWithSheet));
			if (t()->fPrintsWithSheet != true)
				w.attribute(0, dml_spreadsheetDrawing_fPrintsWithSheet_literal, context()->serialize(t()->fPrintsWithSheet));
		}

		void CT_TwoCellAnchor_writer::write_target_to(xml_writer& w) {
			if (t()->editAs != ST_EditAs::twoCell_literal)
				w.attribute(0, dml_spreadsheetDrawing_editAs_literal, context()->serialize(t()->editAs));
			w.start_element(0, dml_spreadsheetDrawing_from_literal);
			_from_writer.get_writer(context(), &t()->from)->write_target_to(w);
			w.end_element(0, dml_spreadsheetDrawing_from_literal);
			w.start_element(0, dml_spreadsheetDrawing_to_literal);
			_to_writer.get_writer(context(), &t()->to)->write_target_to(w);
			w.end_element(0, dml_spreadsheetDrawing_to_literal);
			if (t()->sp.present()) {
				w.start_element(0, dml_spreadsheetDrawing_sp_literal);
				_sp_writer.get_writer(context(), &t()->sp.get())->write_target_to(w);
				w.end_element(0, dml_spreadsheetDrawing_sp_literal);
			}
			if (t()->grpSp.present()) {
				w.start_element(0, dml_spreadsheetDrawing_grpSp_literal);
				_grpSp_writer.get_writer(context(), &t()->grpSp.get())->write_target_to(w);
				w.end_element(0, dml_spreadsheetDrawing_grpSp_literal);
			}
			if (t()->graphicFrame.present()) {
				w.start_element(0, dml_spreadsheetDrawing_graphicFrame_literal);
				_graphicFrame_writer.get_writer(context(), &t()->graphicFrame.get())->write_target_to(w);
				w.end_element(0, dml_spreadsheetDrawing_graphicFrame_literal);
			}
			if (t()->cxnSp.present()) {
				w.start_element(0, dml_spreadsheetDrawing_cxnSp_literal);
				_cxnSp_writer.get_writer(context(), &t()->cxnSp.get())->write_target_to(w);
				w.end_element(0, dml_spreadsheetDrawing_cxnSp_literal);
			}
			if (t()->pic.present()) {
				w.start_element(0, dml_spreadsheetDrawing_pic_literal);
				_pic_writer.get_writer(context(), &t()->pic.get())->write_target_to(w);
				w.end_element(0, dml_spreadsheetDrawing_pic_literal);
			}
			w.start_element(0, dml_spreadsheetDrawing_clientData_literal);
			_clientData_writer.get_writer(context(), &t()->clientData)->write_target_to(w);
			w.end_element(0, dml_spreadsheetDrawing_clientData_literal);
		}

		void CT_Drawings_writer::write_target_to(xml_writer& w) {
			for (size_t sqi = 0; sqi<t()->twoCellAnchor.size(); ++sqi) {
				w.start_element(0, dml_spreadsheetDrawing_twoCellAnchor_literal);
				_twoCellAnchor_writer.get_writer(context(), &t()->twoCellAnchor[sqi])->write_target_to(w);
				w.end_element(0, dml_spreadsheetDrawing_twoCellAnchor_literal);
			}
		}

		void dml_spreadsheetDrawing_writer::write_target_to(xml_writer& w) {
			if (t()->wsDr.present()) {
				w.start_element(0, dml_spreadsheetDrawing_wsDr_literal);
					w.attribute(0, dml_spreadsheetDrawing_xmlns_literal, dml_spreadsheetDrawing_http_colon__slash__slash_schemas_dot_openxmlformats_dot_org_slash_drawingml_slash_2006_slash_spreadsheetDrawing_literal);
					w.attribute(dml_spreadsheetDrawing_xmlns_literal, dml_spreadsheetDrawing_a_literal, dml_spreadsheetDrawing_http_colon__slash__slash_schemas_dot_openxmlformats_dot_org_slash_drawingml_slash_2006_slash_main_literal);
                    w.attribute(dml_spreadsheetDrawing_xmlns_literal, dml_spreadsheetDrawing_r_literal, dml_spreadsheetDrawing_http_colon__slash__slash_schemas_dot_openxmlformats_dot_org_slash_officeDocument_slash_2006_slash_relationships_literal);
					w.attribute(dml_spreadsheetDrawing_xmlns_literal, dml_spreadsheetDrawing_xsd_literal, dml_spreadsheetDrawing_http_colon__slash__slash_www_dot_w3_dot_org_slash_2001_slash_XMLSchema_literal);
				_wsDr_writer.get_writer(context(), &t()->wsDr.get())->write_target_to(w);
				w.end_element(0, dml_spreadsheetDrawing_wsDr_literal);
			}
		}

	}
}
