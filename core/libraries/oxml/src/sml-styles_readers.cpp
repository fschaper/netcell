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


#include "sml-styles_readers.hpp"
#include "sml-styles_literals.hpp"
#include <xio/xml/binding/driver.hpp>

namespace spreadsheetml
{
	namespace xio
	{
		void CT_FontName_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_styles_val_literal))
			{
				driver()->context()->parse(value, t()->val);
				return;
			}
		}
		void CT_IntProperty_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_styles_val_literal))
			{
				driver()->context()->parse(value, t()->val);
				return;
			}
		}
		void CT_BooleanProperty_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_styles_val_literal))
			{
				driver()->context()->parse(value, t()->val);
				return;
			}
		}
		void CT_Color_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_styles__auto__literal))
			{
				driver()->context()->parse(value, t()->_auto_.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_indexed_literal))
			{
				driver()->context()->parse(value, t()->indexed.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_rgb_literal))
			{
				driver()->context()->parse(value, t()->rgb.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_theme_literal))
			{
				driver()->context()->parse(value, t()->theme.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_tint_literal))
			{
				driver()->context()->parse(value, t()->tint);
				return;
			}
		}
		void CT_FontSize_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_styles_val_literal))
			{
				driver()->context()->parse(value, t()->val);
				return;
			}
		}
		void CT_UnderlineProperty_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_styles_val_literal))
			{
				driver()->context()->parse(value, t()->val);
				return;
			}
		}
		void CT_VerticalAlignFontProperty_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_styles_val_literal))
			{
				driver()->context()->parse(value, t()->val);
				return;
			}
		}
		void CT_FontScheme_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_styles_val_literal))
			{
				driver()->context()->parse(value, t()->val);
				return;
			}
		}
		void ST_FontId_reader::read_value(const xstring& val) {{ driver()->context()->parse(val, *t()); }}
		void ST_NumFmtId_reader::read_value(const xstring& val) {{ driver()->context()->parse(val, *t()); }}
		void ST_DxfId_reader::read_value(const xstring& val) {{ driver()->context()->parse(val, *t()); }}
		void CT_Font_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_styles_name_literal))
			{
				driver()->push(localname, _name_reader.get_reader(&t()->name.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_charset_literal))
			{
				driver()->push(localname, _charset_reader.get_reader(&t()->charset.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_family_literal))
			{
				driver()->push(localname, _family_reader.get_reader(&t()->family.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_b_literal))
			{
				driver()->push(localname, _b_reader.get_reader(&t()->b.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_i_literal))
			{
				driver()->push(localname, _i_reader.get_reader(&t()->i.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_strike_literal))
			{
				driver()->push(localname, _strike_reader.get_reader(&t()->strike.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_outline_literal))
			{
				driver()->push(localname, _outline_reader.get_reader(&t()->outline.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_shadow_literal))
			{
				driver()->push(localname, _shadow_reader.get_reader(&t()->shadow.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_condense_literal))
			{
				driver()->push(localname, _condense_reader.get_reader(&t()->condense.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_extend_literal))
			{
				driver()->push(localname, _extend_reader.get_reader(&t()->extend.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_color_literal))
			{
				driver()->push(localname, _color_reader.get_reader(&t()->color.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_sz_literal))
			{
				driver()->push(localname, _sz_reader.get_reader(&t()->sz.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_u_literal))
			{
				driver()->push(localname, _u_reader.get_reader(&t()->u.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_vertAlign_literal))
			{
				driver()->push(localname, _vertAlign_reader.get_reader(&t()->vertAlign.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_scheme_literal))
			{
				driver()->push(localname, _scheme_reader.get_reader(&t()->scheme.getset()));
				return;
			}
		}
		void CT_NumFmt_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_styles_numFmtId_literal))
			{
				driver()->context()->parse(value, t()->numFmtId);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_formatCode_literal))
			{
				driver()->context()->parse(value, t()->formatCode);
				return;
			}
		}
		void CT_PatternFill_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_styles_fgColor_literal))
			{
				driver()->push(localname, _fgColor_reader.get_reader(&t()->fgColor.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_bgColor_literal))
			{
				driver()->push(localname, _bgColor_reader.get_reader(&t()->bgColor.getset()));
				return;
			}
		}
		void CT_PatternFill_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_styles_patternType_literal))
			{
				driver()->context()->parse(value, t()->patternType.getset());
				return;
			}
		}
		void CT_GradientStop_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_styles_color_literal))
			{
				driver()->push(localname, _color_reader.get_reader(&t()->color));
				return;
			}
		}
		void CT_GradientStop_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_styles_position_literal))
			{
				driver()->context()->parse(value, t()->position);
				return;
			}
		}
		void CT_GradientFill_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_styles_stop_literal))
			{
				t()->stop.resize(t()->stop.size()+1);
				driver()->push(localname, _stop_reader.get_reader(&t()->stop.back()));
				return;
			}
		}
		void CT_GradientFill_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_styles_type_literal))
			{
				driver()->context()->parse(value, t()->type);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_degree_literal))
			{
				driver()->context()->parse(value, t()->degree);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_left_literal))
			{
				driver()->context()->parse(value, t()->left);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_right_literal))
			{
				driver()->context()->parse(value, t()->right);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_top_literal))
			{
				driver()->context()->parse(value, t()->top);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_bottom_literal))
			{
				driver()->context()->parse(value, t()->bottom);
				return;
			}
		}
		void CT_Fill_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_styles_patternFill_literal))
			{
				driver()->push(localname, _patternFill_reader.get_reader(&t()->patternFill.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_gradientFill_literal))
			{
				driver()->push(localname, _gradientFill_reader.get_reader(&t()->gradientFill.getset()));
				return;
			}
		}
		void CT_CellAlignment_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_styles_horizontal_literal))
			{
				driver()->context()->parse(value, t()->horizontal.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_vertical_literal))
			{
				driver()->context()->parse(value, t()->vertical.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_textRotation_literal))
			{
				driver()->context()->parse(value, t()->textRotation.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_wrapText_literal))
			{
				driver()->context()->parse(value, t()->wrapText.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_indent_literal))
			{
				driver()->context()->parse(value, t()->indent.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_relativeIndent_literal))
			{
				driver()->context()->parse(value, t()->relativeIndent.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_justifyLastLine_literal))
			{
				driver()->context()->parse(value, t()->justifyLastLine.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_shrinkToFit_literal))
			{
				driver()->context()->parse(value, t()->shrinkToFit.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_readingOrder_literal))
			{
				driver()->context()->parse(value, t()->readingOrder.getset());
				return;
			}
		}
		void CT_BorderPr_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_styles_color_literal))
			{
				driver()->push(localname, _color_reader.get_reader(&t()->color.getset()));
				return;
			}
		}
		void CT_BorderPr_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_styles_style_literal))
			{
				driver()->context()->parse(value, t()->style);
				return;
			}
		}
		void CT_Border_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_styles_left_literal))
			{
				driver()->push(localname, _left_reader.get_reader(&t()->left.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_right_literal))
			{
				driver()->push(localname, _right_reader.get_reader(&t()->right.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_top_literal))
			{
				driver()->push(localname, _top_reader.get_reader(&t()->top.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_bottom_literal))
			{
				driver()->push(localname, _bottom_reader.get_reader(&t()->bottom.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_diagonal_literal))
			{
				driver()->push(localname, _diagonal_reader.get_reader(&t()->diagonal.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_vertical_literal))
			{
				driver()->push(localname, _vertical_reader.get_reader(&t()->vertical.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_horizontal_literal))
			{
				driver()->push(localname, _horizontal_reader.get_reader(&t()->horizontal.getset()));
				return;
			}
		}
		void CT_Border_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_styles_diagonalUp_literal))
			{
				driver()->context()->parse(value, t()->diagonalUp.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_diagonalDown_literal))
			{
				driver()->context()->parse(value, t()->diagonalDown.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_outline_literal))
			{
				driver()->context()->parse(value, t()->outline);
				return;
			}
		}
		void CT_CellProtection_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_styles_locked_literal))
			{
				driver()->context()->parse(value, t()->locked.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_hidden_literal))
			{
				driver()->context()->parse(value, t()->hidden.getset());
				return;
			}
		}
		void CT_Dxf_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_styles_font_literal))
			{
				driver()->push(localname, _font_reader.get_reader(&t()->font.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_numFmt_literal))
			{
				driver()->push(localname, _numFmt_reader.get_reader(&t()->numFmt.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_fill_literal))
			{
				driver()->push(localname, _fill_reader.get_reader(&t()->fill.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_alignment_literal))
			{
				driver()->push(localname, _alignment_reader.get_reader(&t()->alignment.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_border_literal))
			{
				driver()->push(localname, _border_reader.get_reader(&t()->border.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_protection_literal))
			{
				driver()->push(localname, _protection_reader.get_reader(&t()->protection.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_NumFmts_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_styles_numFmt_literal))
			{
				t()->numFmt.resize(t()->numFmt.size()+1);
				driver()->push(localname, _numFmt_reader.get_reader(&t()->numFmt.back()));
				return;
			}
		}
		void CT_NumFmts_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_styles_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
		}
		void CT_Fonts_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_styles_font_literal))
			{
				t()->font.resize(t()->font.size()+1);
				driver()->push(localname, _font_reader.get_reader(&t()->font.back()));
				return;
			}
		}
		void CT_Fonts_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_styles_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
		}
		void CT_Fills_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_styles_fill_literal))
			{
				t()->fill.resize(t()->fill.size()+1);
				driver()->push(localname, _fill_reader.get_reader(&t()->fill.back()));
				return;
			}
		}
		void CT_Fills_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_styles_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
		}
		void CT_Borders_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_styles_border_literal))
			{
				t()->border.resize(t()->border.size()+1);
				driver()->push(localname, _border_reader.get_reader(&t()->border.back()));
				return;
			}
		}
		void CT_Borders_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_styles_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
		}
		void ST_FillId_reader::read_value(const xstring& val) {{ driver()->context()->parse(val, *t()); }}
		void ST_BorderId_reader::read_value(const xstring& val) {{ driver()->context()->parse(val, *t()); }}
		void ST_CellStyleXfId_reader::read_value(const xstring& val) {{ driver()->context()->parse(val, *t()); }}
		void CT_Xf_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_styles_alignment_literal))
			{
				driver()->push(localname, _alignment_reader.get_reader(&t()->alignment.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_protection_literal))
			{
				driver()->push(localname, _protection_reader.get_reader(&t()->protection.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_Xf_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_styles_numFmtId_literal))
			{
				driver()->context()->parse(value, t()->numFmtId.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_fontId_literal))
			{
				driver()->context()->parse(value, t()->fontId.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_fillId_literal))
			{
				driver()->context()->parse(value, t()->fillId.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_borderId_literal))
			{
				driver()->context()->parse(value, t()->borderId.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_xfId_literal))
			{
				driver()->context()->parse(value, t()->xfId.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_quotePrefix_literal))
			{
				driver()->context()->parse(value, t()->quotePrefix);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_pivotButton_literal))
			{
				driver()->context()->parse(value, t()->pivotButton);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_applyNumberFormat_literal))
			{
				driver()->context()->parse(value, t()->applyNumberFormat.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_applyFont_literal))
			{
				driver()->context()->parse(value, t()->applyFont.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_applyFill_literal))
			{
				driver()->context()->parse(value, t()->applyFill.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_applyBorder_literal))
			{
				driver()->context()->parse(value, t()->applyBorder.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_applyAlignment_literal))
			{
				driver()->context()->parse(value, t()->applyAlignment.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_applyProtection_literal))
			{
				driver()->context()->parse(value, t()->applyProtection.getset());
				return;
			}
		}
		void CT_CellStyleXfs_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_styles_xf_literal))
			{
				t()->xf.resize(t()->xf.size()+1);
				driver()->push(localname, _xf_reader.get_reader(&t()->xf.back()));
				return;
			}
		}
		void CT_CellStyleXfs_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_styles_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
		}
		void CT_CellXfs_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_styles_xf_literal))
			{
				t()->xf.resize(t()->xf.size()+1);
				driver()->push(localname, _xf_reader.get_reader(&t()->xf.back()));
				return;
			}
		}
		void CT_CellXfs_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_styles_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
		}
		void CT_CellStyle_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_styles_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_CellStyle_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_styles_name_literal))
			{
				driver()->context()->parse(value, t()->name.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_xfId_literal))
			{
				driver()->context()->parse(value, t()->xfId);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_builtinId_literal))
			{
				driver()->context()->parse(value, t()->builtinId.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_iLevel_literal))
			{
				driver()->context()->parse(value, t()->iLevel.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_hidden_literal))
			{
				driver()->context()->parse(value, t()->hidden.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_customBuiltin_literal))
			{
				driver()->context()->parse(value, t()->customBuiltin.getset());
				return;
			}
		}
		void CT_CellStyles_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_styles_cellStyle_literal))
			{
				t()->cellStyle.resize(t()->cellStyle.size()+1);
				driver()->push(localname, _cellStyle_reader.get_reader(&t()->cellStyle.back()));
				return;
			}
		}
		void CT_CellStyles_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_styles_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
		}
		void CT_Dxfs_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_styles_dxf_literal))
			{
				t()->dxf.resize(t()->dxf.size()+1);
				driver()->push(localname, _dxf_reader.get_reader(&t()->dxf.back()));
				return;
			}
		}
		void CT_Dxfs_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_styles_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
		}
		void CT_TableStyleElement_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_styles_type_literal))
			{
				driver()->context()->parse(value, t()->type);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_size_literal))
			{
				driver()->context()->parse(value, t()->size);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_dxfId_literal))
			{
				driver()->context()->parse(value, t()->dxfId.getset());
				return;
			}
		}
		void CT_TableStyle_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_styles_tableStyleElement_literal))
			{
				t()->tableStyleElement.resize(t()->tableStyleElement.size()+1);
				driver()->push(localname, _tableStyleElement_reader.get_reader(&t()->tableStyleElement.back()));
				return;
			}
		}
		void CT_TableStyle_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_styles_name_literal))
			{
				driver()->context()->parse(value, t()->name);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_pivot_literal))
			{
				driver()->context()->parse(value, t()->pivot);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_table_literal))
			{
				driver()->context()->parse(value, t()->table);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
		}
		void CT_TableStyles_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_styles_tableStyle_literal))
			{
				t()->tableStyle.resize(t()->tableStyle.size()+1);
				driver()->push(localname, _tableStyle_reader.get_reader(&t()->tableStyle.back()));
				return;
			}
		}
		void CT_TableStyles_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_styles_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_defaultTableStyle_literal))
			{
				driver()->context()->parse(value, t()->defaultTableStyle.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_defaultPivotStyle_literal))
			{
				driver()->context()->parse(value, t()->defaultPivotStyle.getset());
				return;
			}
		}
		void CT_RgbColor_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_styles_rgb_literal))
			{
				driver()->context()->parse(value, t()->rgb.getset());
				return;
			}
		}
		void CT_IndexedColors_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_styles_rgbColor_literal))
			{
				t()->rgbColor.resize(t()->rgbColor.size()+1);
				driver()->push(localname, _rgbColor_reader.get_reader(&t()->rgbColor.back()));
				return;
			}
		}
		void CT_MRUColors_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_styles_color_literal))
			{
				t()->color.resize(t()->color.size()+1);
				driver()->push(localname, _color_reader.get_reader(&t()->color.back()));
				return;
			}
		}
		void CT_Colors_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_styles_indexedColors_literal))
			{
				driver()->push(localname, _indexedColors_reader.get_reader(&t()->indexedColors.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_mruColors_literal))
			{
				driver()->push(localname, _mruColors_reader.get_reader(&t()->mruColors.getset()));
				return;
			}
		}
		void CT_Stylesheet_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_styles_numFmts_literal))
			{
				driver()->push(localname, _numFmts_reader.get_reader(&t()->numFmts.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_fonts_literal))
			{
				driver()->push(localname, _fonts_reader.get_reader(&t()->fonts.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_fills_literal))
			{
				driver()->push(localname, _fills_reader.get_reader(&t()->fills.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_borders_literal))
			{
				driver()->push(localname, _borders_reader.get_reader(&t()->borders.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_cellStyleXfs_literal))
			{
				driver()->push(localname, _cellStyleXfs_reader.get_reader(&t()->cellStyleXfs.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_cellXfs_literal))
			{
				driver()->push(localname, _cellXfs_reader.get_reader(&t()->cellXfs.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_cellStyles_literal))
			{
				driver()->push(localname, _cellStyles_reader.get_reader(&t()->cellStyles.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_dxfs_literal))
			{
				driver()->push(localname, _dxfs_reader.get_reader(&t()->dxfs.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_tableStyles_literal))
			{
				driver()->push(localname, _tableStyles_reader.get_reader(&t()->tableStyles.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_colors_literal))
			{
				driver()->push(localname, _colors_reader.get_reader(&t()->colors.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_styles_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void sml_styles_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_styles_styleSheet_literal))
			{
				driver()->push(localname, _styleSheet_reader.get_reader(&t()->styleSheet.getset()));
				return;
			}
		}
	}
}
