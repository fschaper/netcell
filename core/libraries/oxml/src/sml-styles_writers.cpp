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


#include "sml-styles_writers.hpp"
#include "sml-styles_literals.hpp"

namespace spreadsheetml
{
	namespace xio
	{
		void CT_FontName_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_styles_val_literal, context()->serialize(t()->val));
		}

		void CT_IntProperty_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_styles_val_literal, context()->serialize(t()->val));
		}

		void CT_BooleanProperty_writer::write_target_to(xml_writer& w) {
			if (t()->val != true)
				w.attribute(0, sml_styles_val_literal, context()->serialize(t()->val));
		}

		void CT_Color_writer::write_target_to(xml_writer& w) {
			if (t()->_auto_.present())
				w.attribute(0, sml_styles__auto__literal, context()->serialize(t()->_auto_.get()));
			if (t()->indexed.present())
				w.attribute(0, sml_styles_indexed_literal, context()->serialize(t()->indexed.get()));
			if (t()->rgb.present())
				w.attribute(0, sml_styles_rgb_literal, context()->serialize(t()->rgb.get()));
			if (t()->theme.present())
				w.attribute(0, sml_styles_theme_literal, context()->serialize(t()->theme.get()));
			if (t()->tint != 0.0)
				w.attribute(0, sml_styles_tint_literal, context()->serialize(t()->tint));
		}

		void CT_FontSize_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_styles_val_literal, context()->serialize(t()->val));
		}

		void CT_UnderlineProperty_writer::write_target_to(xml_writer& w) {
			if (t()->val != ST_UnderlineValues::single_literal)
				w.attribute(0, sml_styles_val_literal, context()->serialize(t()->val));
		}

		void CT_VerticalAlignFontProperty_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_styles_val_literal, context()->serialize(t()->val));
		}

		void CT_FontScheme_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_styles_val_literal, context()->serialize(t()->val));
		}

		void ST_FontId_writer::write_target_to(xml_writer& w) {
			w.write_element_value(context()->serialize(*t()));
		}

		void ST_NumFmtId_writer::write_target_to(xml_writer& w) {
			w.write_element_value(context()->serialize(*t()));
		}

		void ST_DxfId_writer::write_target_to(xml_writer& w) {
			w.write_element_value(context()->serialize(*t()));
		}

		void CT_Font_writer::write_target_to(xml_writer& w) {
			if (t()->name.present()) {
				w.start_element(0, sml_styles_name_literal);
				_name_writer.get_writer(context(), &t()->name.get())->write_target_to(w);
				w.end_element(0, sml_styles_name_literal);
			}
			if (t()->charset.present()) {
				w.start_element(0, sml_styles_charset_literal);
				_charset_writer.get_writer(context(), &t()->charset.get())->write_target_to(w);
				w.end_element(0, sml_styles_charset_literal);
			}
			if (t()->family.present()) {
				w.start_element(0, sml_styles_family_literal);
				_family_writer.get_writer(context(), &t()->family.get())->write_target_to(w);
				w.end_element(0, sml_styles_family_literal);
			}
			if (t()->b.present()) {
				w.start_element(0, sml_styles_b_literal);
				_b_writer.get_writer(context(), &t()->b.get())->write_target_to(w);
				w.end_element(0, sml_styles_b_literal);
			}
			if (t()->i.present()) {
				w.start_element(0, sml_styles_i_literal);
				_i_writer.get_writer(context(), &t()->i.get())->write_target_to(w);
				w.end_element(0, sml_styles_i_literal);
			}
			if (t()->strike.present()) {
				w.start_element(0, sml_styles_strike_literal);
				_strike_writer.get_writer(context(), &t()->strike.get())->write_target_to(w);
				w.end_element(0, sml_styles_strike_literal);
			}
			if (t()->outline.present()) {
				w.start_element(0, sml_styles_outline_literal);
				_outline_writer.get_writer(context(), &t()->outline.get())->write_target_to(w);
				w.end_element(0, sml_styles_outline_literal);
			}
			if (t()->shadow.present()) {
				w.start_element(0, sml_styles_shadow_literal);
				_shadow_writer.get_writer(context(), &t()->shadow.get())->write_target_to(w);
				w.end_element(0, sml_styles_shadow_literal);
			}
			if (t()->condense.present()) {
				w.start_element(0, sml_styles_condense_literal);
				_condense_writer.get_writer(context(), &t()->condense.get())->write_target_to(w);
				w.end_element(0, sml_styles_condense_literal);
			}
			if (t()->extend.present()) {
				w.start_element(0, sml_styles_extend_literal);
				_extend_writer.get_writer(context(), &t()->extend.get())->write_target_to(w);
				w.end_element(0, sml_styles_extend_literal);
			}
			if (t()->color.present()) {
				w.start_element(0, sml_styles_color_literal);
				_color_writer.get_writer(context(), &t()->color.get())->write_target_to(w);
				w.end_element(0, sml_styles_color_literal);
			}
			if (t()->sz.present()) {
				w.start_element(0, sml_styles_sz_literal);
				_sz_writer.get_writer(context(), &t()->sz.get())->write_target_to(w);
				w.end_element(0, sml_styles_sz_literal);
			}
			if (t()->u.present()) {
				w.start_element(0, sml_styles_u_literal);
				_u_writer.get_writer(context(), &t()->u.get())->write_target_to(w);
				w.end_element(0, sml_styles_u_literal);
			}
			if (t()->vertAlign.present()) {
				w.start_element(0, sml_styles_vertAlign_literal);
				_vertAlign_writer.get_writer(context(), &t()->vertAlign.get())->write_target_to(w);
				w.end_element(0, sml_styles_vertAlign_literal);
			}
			if (t()->scheme.present()) {
				w.start_element(0, sml_styles_scheme_literal);
				_scheme_writer.get_writer(context(), &t()->scheme.get())->write_target_to(w);
				w.end_element(0, sml_styles_scheme_literal);
			}
		}

		void CT_NumFmt_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_styles_numFmtId_literal, context()->serialize(t()->numFmtId));
			w.attribute(0, sml_styles_formatCode_literal, context()->serialize(t()->formatCode));
		}

		void CT_PatternFill_writer::write_target_to(xml_writer& w) {
			if (t()->patternType.present())
				w.attribute(0, sml_styles_patternType_literal, context()->serialize(t()->patternType.get()));
			if (t()->fgColor.present()) {
				w.start_element(0, sml_styles_fgColor_literal);
				_fgColor_writer.get_writer(context(), &t()->fgColor.get())->write_target_to(w);
				w.end_element(0, sml_styles_fgColor_literal);
			}
			if (t()->bgColor.present()) {
				w.start_element(0, sml_styles_bgColor_literal);
				_bgColor_writer.get_writer(context(), &t()->bgColor.get())->write_target_to(w);
				w.end_element(0, sml_styles_bgColor_literal);
			}
		}

		void CT_GradientStop_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_styles_position_literal, context()->serialize(t()->position));
			w.start_element(0, sml_styles_color_literal);
			_color_writer.get_writer(context(), &t()->color)->write_target_to(w);
			w.end_element(0, sml_styles_color_literal);
		}

		void CT_GradientFill_writer::write_target_to(xml_writer& w) {
			if (t()->type != ST_GradientType::linear_literal)
				w.attribute(0, sml_styles_type_literal, context()->serialize(t()->type));
			if (t()->degree != 0)
				w.attribute(0, sml_styles_degree_literal, context()->serialize(t()->degree));
			if (t()->left != 0)
				w.attribute(0, sml_styles_left_literal, context()->serialize(t()->left));
			if (t()->right != 0)
				w.attribute(0, sml_styles_right_literal, context()->serialize(t()->right));
			if (t()->top != 0)
				w.attribute(0, sml_styles_top_literal, context()->serialize(t()->top));
			if (t()->bottom != 0)
				w.attribute(0, sml_styles_bottom_literal, context()->serialize(t()->bottom));
			for (size_t sqi = 0; sqi<t()->stop.size(); ++sqi) {
				w.start_element(0, sml_styles_stop_literal);
				_stop_writer.get_writer(context(), &t()->stop[sqi])->write_target_to(w);
				w.end_element(0, sml_styles_stop_literal);
			}
		}

		void CT_Fill_writer::write_target_to(xml_writer& w) {
			if (t()->patternFill.present()) {
				w.start_element(0, sml_styles_patternFill_literal);
				_patternFill_writer.get_writer(context(), &t()->patternFill.get())->write_target_to(w);
				w.end_element(0, sml_styles_patternFill_literal);
			}
			if (t()->gradientFill.present()) {
				w.start_element(0, sml_styles_gradientFill_literal);
				_gradientFill_writer.get_writer(context(), &t()->gradientFill.get())->write_target_to(w);
				w.end_element(0, sml_styles_gradientFill_literal);
			}
		}

		void CT_CellAlignment_writer::write_target_to(xml_writer& w) {
			if (t()->horizontal.present())
				w.attribute(0, sml_styles_horizontal_literal, context()->serialize(t()->horizontal.get()));
			if (t()->vertical.present())
				w.attribute(0, sml_styles_vertical_literal, context()->serialize(t()->vertical.get()));
			if (t()->textRotation.present())
				w.attribute(0, sml_styles_textRotation_literal, context()->serialize(t()->textRotation.get()));
			if (t()->wrapText.present())
				w.attribute(0, sml_styles_wrapText_literal, context()->serialize(t()->wrapText.get()));
			if (t()->indent.present())
				w.attribute(0, sml_styles_indent_literal, context()->serialize(t()->indent.get()));
			if (t()->relativeIndent.present())
				w.attribute(0, sml_styles_relativeIndent_literal, context()->serialize(t()->relativeIndent.get()));
			if (t()->justifyLastLine.present())
				w.attribute(0, sml_styles_justifyLastLine_literal, context()->serialize(t()->justifyLastLine.get()));
			if (t()->shrinkToFit.present())
				w.attribute(0, sml_styles_shrinkToFit_literal, context()->serialize(t()->shrinkToFit.get()));
			if (t()->readingOrder.present())
				w.attribute(0, sml_styles_readingOrder_literal, context()->serialize(t()->readingOrder.get()));
		}

		void CT_BorderPr_writer::write_target_to(xml_writer& w) {
			if (t()->style != ST_BorderStyle::none_literal)
				w.attribute(0, sml_styles_style_literal, context()->serialize(t()->style));
			if (t()->color.present()) {
				w.start_element(0, sml_styles_color_literal);
				_color_writer.get_writer(context(), &t()->color.get())->write_target_to(w);
				w.end_element(0, sml_styles_color_literal);
			}
		}

		void CT_Border_writer::write_target_to(xml_writer& w) {
			if (t()->diagonalUp.present())
				w.attribute(0, sml_styles_diagonalUp_literal, context()->serialize(t()->diagonalUp.get()));
			if (t()->diagonalDown.present())
				w.attribute(0, sml_styles_diagonalDown_literal, context()->serialize(t()->diagonalDown.get()));
			if (t()->outline != true)
				w.attribute(0, sml_styles_outline_literal, context()->serialize(t()->outline));
			if (t()->left.present()) {
				w.start_element(0, sml_styles_left_literal);
				_left_writer.get_writer(context(), &t()->left.get())->write_target_to(w);
				w.end_element(0, sml_styles_left_literal);
			}
			if (t()->right.present()) {
				w.start_element(0, sml_styles_right_literal);
				_right_writer.get_writer(context(), &t()->right.get())->write_target_to(w);
				w.end_element(0, sml_styles_right_literal);
			}
			if (t()->top.present()) {
				w.start_element(0, sml_styles_top_literal);
				_top_writer.get_writer(context(), &t()->top.get())->write_target_to(w);
				w.end_element(0, sml_styles_top_literal);
			}
			if (t()->bottom.present()) {
				w.start_element(0, sml_styles_bottom_literal);
				_bottom_writer.get_writer(context(), &t()->bottom.get())->write_target_to(w);
				w.end_element(0, sml_styles_bottom_literal);
			}
			if (t()->diagonal.present()) {
				w.start_element(0, sml_styles_diagonal_literal);
				_diagonal_writer.get_writer(context(), &t()->diagonal.get())->write_target_to(w);
				w.end_element(0, sml_styles_diagonal_literal);
			}
			if (t()->vertical.present()) {
				w.start_element(0, sml_styles_vertical_literal);
				_vertical_writer.get_writer(context(), &t()->vertical.get())->write_target_to(w);
				w.end_element(0, sml_styles_vertical_literal);
			}
			if (t()->horizontal.present()) {
				w.start_element(0, sml_styles_horizontal_literal);
				_horizontal_writer.get_writer(context(), &t()->horizontal.get())->write_target_to(w);
				w.end_element(0, sml_styles_horizontal_literal);
			}
		}

		void CT_CellProtection_writer::write_target_to(xml_writer& w) {
			if (t()->locked.present())
				w.attribute(0, sml_styles_locked_literal, context()->serialize(t()->locked.get()));
			if (t()->hidden.present())
				w.attribute(0, sml_styles_hidden_literal, context()->serialize(t()->hidden.get()));
		}

		void CT_Dxf_writer::write_target_to(xml_writer& w) {
			if (t()->font.present()) {
				w.start_element(0, sml_styles_font_literal);
				_font_writer.get_writer(context(), &t()->font.get())->write_target_to(w);
				w.end_element(0, sml_styles_font_literal);
			}
			if (t()->numFmt.present()) {
				w.start_element(0, sml_styles_numFmt_literal);
				_numFmt_writer.get_writer(context(), &t()->numFmt.get())->write_target_to(w);
				w.end_element(0, sml_styles_numFmt_literal);
			}
			if (t()->fill.present()) {
				w.start_element(0, sml_styles_fill_literal);
				_fill_writer.get_writer(context(), &t()->fill.get())->write_target_to(w);
				w.end_element(0, sml_styles_fill_literal);
			}
			if (t()->alignment.present()) {
				w.start_element(0, sml_styles_alignment_literal);
				_alignment_writer.get_writer(context(), &t()->alignment.get())->write_target_to(w);
				w.end_element(0, sml_styles_alignment_literal);
			}
			if (t()->border.present()) {
				w.start_element(0, sml_styles_border_literal);
				_border_writer.get_writer(context(), &t()->border.get())->write_target_to(w);
				w.end_element(0, sml_styles_border_literal);
			}
			if (t()->protection.present()) {
				w.start_element(0, sml_styles_protection_literal);
				_protection_writer.get_writer(context(), &t()->protection.get())->write_target_to(w);
				w.end_element(0, sml_styles_protection_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, sml_styles_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_styles_extLst_literal);
			}
		}

		void CT_NumFmts_writer::write_target_to(xml_writer& w) {
			if (t()->count.present())
				w.attribute(0, sml_styles_count_literal, context()->serialize(t()->count.get()));
			for (size_t sqi = 0; sqi<t()->numFmt.size(); ++sqi) {
				w.start_element(0, sml_styles_numFmt_literal);
				_numFmt_writer.get_writer(context(), &t()->numFmt[sqi])->write_target_to(w);
				w.end_element(0, sml_styles_numFmt_literal);
			}
		}

		void CT_Fonts_writer::write_target_to(xml_writer& w) {
			if (t()->count.present())
				w.attribute(0, sml_styles_count_literal, context()->serialize(t()->count.get()));
			for (size_t sqi = 0; sqi<t()->font.size(); ++sqi) {
				w.start_element(0, sml_styles_font_literal);
				_font_writer.get_writer(context(), &t()->font[sqi])->write_target_to(w);
				w.end_element(0, sml_styles_font_literal);
			}
		}

		void CT_Fills_writer::write_target_to(xml_writer& w) {
			if (t()->count.present())
				w.attribute(0, sml_styles_count_literal, context()->serialize(t()->count.get()));
			for (size_t sqi = 0; sqi<t()->fill.size(); ++sqi) {
				w.start_element(0, sml_styles_fill_literal);
				_fill_writer.get_writer(context(), &t()->fill[sqi])->write_target_to(w);
				w.end_element(0, sml_styles_fill_literal);
			}
		}

		void CT_Borders_writer::write_target_to(xml_writer& w) {
			if (t()->count.present())
				w.attribute(0, sml_styles_count_literal, context()->serialize(t()->count.get()));
			for (size_t sqi = 0; sqi<t()->border.size(); ++sqi) {
				w.start_element(0, sml_styles_border_literal);
				_border_writer.get_writer(context(), &t()->border[sqi])->write_target_to(w);
				w.end_element(0, sml_styles_border_literal);
			}
		}

		void ST_FillId_writer::write_target_to(xml_writer& w) {
			w.write_element_value(context()->serialize(*t()));
		}

		void ST_BorderId_writer::write_target_to(xml_writer& w) {
			w.write_element_value(context()->serialize(*t()));
		}

		void ST_CellStyleXfId_writer::write_target_to(xml_writer& w) {
			w.write_element_value(context()->serialize(*t()));
		}

		void CT_Xf_writer::write_target_to(xml_writer& w) {
			if (t()->numFmtId.present())
				w.attribute(0, sml_styles_numFmtId_literal, context()->serialize(t()->numFmtId.get()));
			if (t()->fontId.present())
				w.attribute(0, sml_styles_fontId_literal, context()->serialize(t()->fontId.get()));
			if (t()->fillId.present())
				w.attribute(0, sml_styles_fillId_literal, context()->serialize(t()->fillId.get()));
			if (t()->borderId.present())
				w.attribute(0, sml_styles_borderId_literal, context()->serialize(t()->borderId.get()));
			if (t()->xfId.present())
				w.attribute(0, sml_styles_xfId_literal, context()->serialize(t()->xfId.get()));
			if (t()->quotePrefix != false)
				w.attribute(0, sml_styles_quotePrefix_literal, context()->serialize(t()->quotePrefix));
			if (t()->pivotButton != false)
				w.attribute(0, sml_styles_pivotButton_literal, context()->serialize(t()->pivotButton));
			if (t()->applyNumberFormat.present())
				w.attribute(0, sml_styles_applyNumberFormat_literal, context()->serialize(t()->applyNumberFormat.get()));
			if (t()->applyFont.present())
				w.attribute(0, sml_styles_applyFont_literal, context()->serialize(t()->applyFont.get()));
			if (t()->applyFill.present())
				w.attribute(0, sml_styles_applyFill_literal, context()->serialize(t()->applyFill.get()));
			if (t()->applyBorder.present())
				w.attribute(0, sml_styles_applyBorder_literal, context()->serialize(t()->applyBorder.get()));
			if (t()->applyAlignment.present())
				w.attribute(0, sml_styles_applyAlignment_literal, context()->serialize(t()->applyAlignment.get()));
			if (t()->applyProtection.present())
				w.attribute(0, sml_styles_applyProtection_literal, context()->serialize(t()->applyProtection.get()));
			if (t()->alignment.present()) {
				w.start_element(0, sml_styles_alignment_literal);
				_alignment_writer.get_writer(context(), &t()->alignment.get())->write_target_to(w);
				w.end_element(0, sml_styles_alignment_literal);
			}
			if (t()->protection.present()) {
				w.start_element(0, sml_styles_protection_literal);
				_protection_writer.get_writer(context(), &t()->protection.get())->write_target_to(w);
				w.end_element(0, sml_styles_protection_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, sml_styles_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_styles_extLst_literal);
			}
		}

		void CT_CellStyleXfs_writer::write_target_to(xml_writer& w) {
			if (t()->count.present())
				w.attribute(0, sml_styles_count_literal, context()->serialize(t()->count.get()));
			for (size_t sqi = 0; sqi<t()->xf.size(); ++sqi) {
				w.start_element(0, sml_styles_xf_literal);
				_xf_writer.get_writer(context(), &t()->xf[sqi])->write_target_to(w);
				w.end_element(0, sml_styles_xf_literal);
			}
		}

		void CT_CellXfs_writer::write_target_to(xml_writer& w) {
			if (t()->count.present())
				w.attribute(0, sml_styles_count_literal, context()->serialize(t()->count.get()));
			for (size_t sqi = 0; sqi<t()->xf.size(); ++sqi) {
				w.start_element(0, sml_styles_xf_literal);
				_xf_writer.get_writer(context(), &t()->xf[sqi])->write_target_to(w);
				w.end_element(0, sml_styles_xf_literal);
			}
		}

		void CT_CellStyle_writer::write_target_to(xml_writer& w) {
			if (t()->name.present())
				w.attribute(0, sml_styles_name_literal, context()->serialize(t()->name.get()));
			w.attribute(0, sml_styles_xfId_literal, context()->serialize(t()->xfId));
			if (t()->builtinId.present())
				w.attribute(0, sml_styles_builtinId_literal, context()->serialize(t()->builtinId.get()));
			if (t()->iLevel.present())
				w.attribute(0, sml_styles_iLevel_literal, context()->serialize(t()->iLevel.get()));
			if (t()->hidden.present())
				w.attribute(0, sml_styles_hidden_literal, context()->serialize(t()->hidden.get()));
			if (t()->customBuiltin.present())
				w.attribute(0, sml_styles_customBuiltin_literal, context()->serialize(t()->customBuiltin.get()));
			if (t()->extLst.present()) {
				w.start_element(0, sml_styles_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_styles_extLst_literal);
			}
		}

		void CT_CellStyles_writer::write_target_to(xml_writer& w) {
			if (t()->count.present())
				w.attribute(0, sml_styles_count_literal, context()->serialize(t()->count.get()));
			for (size_t sqi = 0; sqi<t()->cellStyle.size(); ++sqi) {
				w.start_element(0, sml_styles_cellStyle_literal);
				_cellStyle_writer.get_writer(context(), &t()->cellStyle[sqi])->write_target_to(w);
				w.end_element(0, sml_styles_cellStyle_literal);
			}
		}

		void CT_Dxfs_writer::write_target_to(xml_writer& w) {
			if (t()->count.present())
				w.attribute(0, sml_styles_count_literal, context()->serialize(t()->count.get()));
			for (size_t sqi = 0; sqi<t()->dxf.size(); ++sqi) {
				w.start_element(0, sml_styles_dxf_literal);
				_dxf_writer.get_writer(context(), &t()->dxf[sqi])->write_target_to(w);
				w.end_element(0, sml_styles_dxf_literal);
			}
		}

		void CT_TableStyleElement_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_styles_type_literal, context()->serialize(t()->type));
			if (t()->size != 1U)
				w.attribute(0, sml_styles_size_literal, context()->serialize(t()->size));
			if (t()->dxfId.present())
				w.attribute(0, sml_styles_dxfId_literal, context()->serialize(t()->dxfId.get()));
		}

		void CT_TableStyle_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_styles_name_literal, context()->serialize(t()->name));
			if (t()->pivot != true)
				w.attribute(0, sml_styles_pivot_literal, context()->serialize(t()->pivot));
			if (t()->table != true)
				w.attribute(0, sml_styles_table_literal, context()->serialize(t()->table));
			if (t()->count.present())
				w.attribute(0, sml_styles_count_literal, context()->serialize(t()->count.get()));
			for (size_t sqi = 0; sqi<t()->tableStyleElement.size(); ++sqi) {
				w.start_element(0, sml_styles_tableStyleElement_literal);
				_tableStyleElement_writer.get_writer(context(), &t()->tableStyleElement[sqi])->write_target_to(w);
				w.end_element(0, sml_styles_tableStyleElement_literal);
			}
		}

		void CT_TableStyles_writer::write_target_to(xml_writer& w) {
			if (t()->count.present())
				w.attribute(0, sml_styles_count_literal, context()->serialize(t()->count.get()));
			if (t()->defaultTableStyle.present())
				w.attribute(0, sml_styles_defaultTableStyle_literal, context()->serialize(t()->defaultTableStyle.get()));
			if (t()->defaultPivotStyle.present())
				w.attribute(0, sml_styles_defaultPivotStyle_literal, context()->serialize(t()->defaultPivotStyle.get()));
			for (size_t sqi = 0; sqi<t()->tableStyle.size(); ++sqi) {
				w.start_element(0, sml_styles_tableStyle_literal);
				_tableStyle_writer.get_writer(context(), &t()->tableStyle[sqi])->write_target_to(w);
				w.end_element(0, sml_styles_tableStyle_literal);
			}
		}

		void CT_RgbColor_writer::write_target_to(xml_writer& w) {
			if (t()->rgb.present())
				w.attribute(0, sml_styles_rgb_literal, context()->serialize(t()->rgb.get()));
		}

		void CT_IndexedColors_writer::write_target_to(xml_writer& w) {
			for (size_t sqi = 0; sqi<t()->rgbColor.size(); ++sqi) {
				w.start_element(0, sml_styles_rgbColor_literal);
				_rgbColor_writer.get_writer(context(), &t()->rgbColor[sqi])->write_target_to(w);
				w.end_element(0, sml_styles_rgbColor_literal);
			}
		}

		void CT_MRUColors_writer::write_target_to(xml_writer& w) {
			for (size_t sqi = 0; sqi<t()->color.size(); ++sqi) {
				w.start_element(0, sml_styles_color_literal);
				_color_writer.get_writer(context(), &t()->color[sqi])->write_target_to(w);
				w.end_element(0, sml_styles_color_literal);
			}
		}

		void CT_Colors_writer::write_target_to(xml_writer& w) {
			if (t()->indexedColors.present()) {
				w.start_element(0, sml_styles_indexedColors_literal);
				_indexedColors_writer.get_writer(context(), &t()->indexedColors.get())->write_target_to(w);
				w.end_element(0, sml_styles_indexedColors_literal);
			}
			if (t()->mruColors.present()) {
				w.start_element(0, sml_styles_mruColors_literal);
				_mruColors_writer.get_writer(context(), &t()->mruColors.get())->write_target_to(w);
				w.end_element(0, sml_styles_mruColors_literal);
			}
		}

		void CT_Stylesheet_writer::write_target_to(xml_writer& w) {
			if (t()->numFmts.present()) {
				w.start_element(0, sml_styles_numFmts_literal);
				_numFmts_writer.get_writer(context(), &t()->numFmts.get())->write_target_to(w);
				w.end_element(0, sml_styles_numFmts_literal);
			}
			if (t()->fonts.present()) {
				w.start_element(0, sml_styles_fonts_literal);
				_fonts_writer.get_writer(context(), &t()->fonts.get())->write_target_to(w);
				w.end_element(0, sml_styles_fonts_literal);
			}
			if (t()->fills.present()) {
				w.start_element(0, sml_styles_fills_literal);
				_fills_writer.get_writer(context(), &t()->fills.get())->write_target_to(w);
				w.end_element(0, sml_styles_fills_literal);
			}
			if (t()->borders.present()) {
				w.start_element(0, sml_styles_borders_literal);
				_borders_writer.get_writer(context(), &t()->borders.get())->write_target_to(w);
				w.end_element(0, sml_styles_borders_literal);
			}
			if (t()->cellStyleXfs.present()) {
				w.start_element(0, sml_styles_cellStyleXfs_literal);
				_cellStyleXfs_writer.get_writer(context(), &t()->cellStyleXfs.get())->write_target_to(w);
				w.end_element(0, sml_styles_cellStyleXfs_literal);
			}
			if (t()->cellXfs.present()) {
				w.start_element(0, sml_styles_cellXfs_literal);
				_cellXfs_writer.get_writer(context(), &t()->cellXfs.get())->write_target_to(w);
				w.end_element(0, sml_styles_cellXfs_literal);
			}
			if (t()->cellStyles.present()) {
				w.start_element(0, sml_styles_cellStyles_literal);
				_cellStyles_writer.get_writer(context(), &t()->cellStyles.get())->write_target_to(w);
				w.end_element(0, sml_styles_cellStyles_literal);
			}
			if (t()->dxfs.present()) {
				w.start_element(0, sml_styles_dxfs_literal);
				_dxfs_writer.get_writer(context(), &t()->dxfs.get())->write_target_to(w);
				w.end_element(0, sml_styles_dxfs_literal);
			}
			if (t()->tableStyles.present()) {
				w.start_element(0, sml_styles_tableStyles_literal);
				_tableStyles_writer.get_writer(context(), &t()->tableStyles.get())->write_target_to(w);
				w.end_element(0, sml_styles_tableStyles_literal);
			}
			if (t()->colors.present()) {
				w.start_element(0, sml_styles_colors_literal);
				_colors_writer.get_writer(context(), &t()->colors.get())->write_target_to(w);
				w.end_element(0, sml_styles_colors_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, sml_styles_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_styles_extLst_literal);
			}
		}

		void sml_styles_writer::write_target_to(xml_writer& w) {
			if (t()->styleSheet.present()) {
				w.start_element(0, sml_styles_styleSheet_literal);
					w.attribute(0, sml_styles_xmlns_literal, sml_styles_http_colon__slash__slash_schemas_dot_openxmlformats_dot_org_slash_spreadsheetml_slash_2006_slash_main_literal);
					w.attribute(sml_styles_xmlns_literal, sml_styles_xsd_literal, sml_styles_http_colon__slash__slash_www_dot_w3_dot_org_slash_2001_slash_XMLSchema_literal);
				_styleSheet_writer.get_writer(context(), &t()->styleSheet.get())->write_target_to(w);
				w.end_element(0, sml_styles_styleSheet_literal);
			}
		}

	}
}
