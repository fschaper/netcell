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

#ifndef SML_STYLES_WRITERS_HPP
#define SML_STYLES_WRITERS_HPP

#include "sml-styles.hpp"
#include "sml-styles_literals.hpp"
#include "sml-baseTypes_writers.hpp"

namespace spreadsheetml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_FontName_writer;
		class CT_IntProperty_writer;
		class CT_BooleanProperty_writer;
		class CT_Color_writer;
		class CT_FontSize_writer;
		class CT_UnderlineProperty_writer;
		class CT_VerticalAlignFontProperty_writer;
		class CT_FontScheme_writer;
		class ST_FontId_writer;
		class ST_NumFmtId_writer;
		class ST_DxfId_writer;
		class CT_Font_writer;
		class CT_NumFmt_writer;
		class CT_PatternFill_writer;
		class CT_GradientStop_writer;
		class CT_GradientFill_writer;
		class CT_Fill_writer;
		class CT_CellAlignment_writer;
		class CT_BorderPr_writer;
		class CT_Border_writer;
		class CT_CellProtection_writer;
		class CT_Dxf_writer;
		class CT_NumFmts_writer;
		class CT_Fonts_writer;
		class CT_Fills_writer;
		class CT_Borders_writer;
		class ST_FillId_writer;
		class ST_BorderId_writer;
		class ST_CellStyleXfId_writer;
		class CT_Xf_writer;
		class CT_CellStyleXfs_writer;
		class CT_CellXfs_writer;
		class CT_CellStyle_writer;
		class CT_CellStyles_writer;
		class CT_Dxfs_writer;
		class CT_TableStyleElement_writer;
		class CT_TableStyle_writer;
		class CT_TableStyles_writer;
		class CT_RgbColor_writer;
		class CT_IndexedColors_writer;
		class CT_MRUColors_writer;
		class CT_Colors_writer;
		class CT_Stylesheet_writer;
		class sml_styles_writer;

		class CT_FontName_writer : public type_writer
		{
			CT_FontName* t() { return static_cast<CT_FontName*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_IntProperty_writer : public type_writer
		{
			CT_IntProperty* t() { return static_cast<CT_IntProperty*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_BooleanProperty_writer : public type_writer
		{
			CT_BooleanProperty* t() { return static_cast<CT_BooleanProperty*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Color_writer : public type_writer
		{
			CT_Color* t() { return static_cast<CT_Color*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_FontSize_writer : public type_writer
		{
			CT_FontSize* t() { return static_cast<CT_FontSize*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_UnderlineProperty_writer : public type_writer
		{
			CT_UnderlineProperty* t() { return static_cast<CT_UnderlineProperty*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_VerticalAlignFontProperty_writer : public type_writer
		{
			CT_VerticalAlignFontProperty* t() { return static_cast<CT_VerticalAlignFontProperty*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_FontScheme_writer : public type_writer
		{
			CT_FontScheme* t() { return static_cast<CT_FontScheme*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class ST_FontId_writer : public type_writer
		{
			ST_FontId* t() { return static_cast<ST_FontId*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class ST_NumFmtId_writer : public type_writer
		{
			ST_NumFmtId* t() { return static_cast<ST_NumFmtId*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class ST_DxfId_writer : public type_writer
		{
			ST_DxfId* t() { return static_cast<ST_DxfId*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Font_writer : public type_writer
		{
			auto_type_writer< CT_FontName_writer > _name_writer;
			auto_type_writer< CT_IntProperty_writer > _charset_writer;
			auto_type_writer< CT_IntProperty_writer > _family_writer;
			auto_type_writer< CT_BooleanProperty_writer > _b_writer;
			auto_type_writer< CT_BooleanProperty_writer > _i_writer;
			auto_type_writer< CT_BooleanProperty_writer > _strike_writer;
			auto_type_writer< CT_BooleanProperty_writer > _outline_writer;
			auto_type_writer< CT_BooleanProperty_writer > _shadow_writer;
			auto_type_writer< CT_BooleanProperty_writer > _condense_writer;
			auto_type_writer< CT_BooleanProperty_writer > _extend_writer;
			auto_type_writer< CT_Color_writer > _color_writer;
			auto_type_writer< CT_FontSize_writer > _sz_writer;
			auto_type_writer< CT_UnderlineProperty_writer > _u_writer;
			auto_type_writer< CT_VerticalAlignFontProperty_writer > _vertAlign_writer;
			auto_type_writer< CT_FontScheme_writer > _scheme_writer;
			CT_Font* t() { return static_cast<CT_Font*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_NumFmt_writer : public type_writer
		{
			CT_NumFmt* t() { return static_cast<CT_NumFmt*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_PatternFill_writer : public type_writer
		{
			auto_type_writer< CT_Color_writer > _fgColor_writer;
			auto_type_writer< CT_Color_writer > _bgColor_writer;
			CT_PatternFill* t() { return static_cast<CT_PatternFill*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_GradientStop_writer : public type_writer
		{
			auto_type_writer< CT_Color_writer > _color_writer;
			CT_GradientStop* t() { return static_cast<CT_GradientStop*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_GradientFill_writer : public type_writer
		{
			auto_type_writer< CT_GradientStop_writer > _stop_writer;
			CT_GradientFill* t() { return static_cast<CT_GradientFill*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Fill_writer : public type_writer
		{
			auto_type_writer< CT_PatternFill_writer > _patternFill_writer;
			auto_type_writer< CT_GradientFill_writer > _gradientFill_writer;
			CT_Fill* t() { return static_cast<CT_Fill*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_CellAlignment_writer : public type_writer
		{
			CT_CellAlignment* t() { return static_cast<CT_CellAlignment*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_BorderPr_writer : public type_writer
		{
			auto_type_writer< CT_Color_writer > _color_writer;
			CT_BorderPr* t() { return static_cast<CT_BorderPr*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Border_writer : public type_writer
		{
			auto_type_writer< CT_BorderPr_writer > _left_writer;
			auto_type_writer< CT_BorderPr_writer > _right_writer;
			auto_type_writer< CT_BorderPr_writer > _top_writer;
			auto_type_writer< CT_BorderPr_writer > _bottom_writer;
			auto_type_writer< CT_BorderPr_writer > _diagonal_writer;
			auto_type_writer< CT_BorderPr_writer > _vertical_writer;
			auto_type_writer< CT_BorderPr_writer > _horizontal_writer;
			CT_Border* t() { return static_cast<CT_Border*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_CellProtection_writer : public type_writer
		{
			CT_CellProtection* t() { return static_cast<CT_CellProtection*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Dxf_writer : public type_writer
		{
			auto_type_writer< CT_Font_writer > _font_writer;
			auto_type_writer< CT_NumFmt_writer > _numFmt_writer;
			auto_type_writer< CT_Fill_writer > _fill_writer;
			auto_type_writer< CT_CellAlignment_writer > _alignment_writer;
			auto_type_writer< CT_Border_writer > _border_writer;
			auto_type_writer< CT_CellProtection_writer > _protection_writer;
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_Dxf* t() { return static_cast<CT_Dxf*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_NumFmts_writer : public type_writer
		{
			auto_type_writer< CT_NumFmt_writer > _numFmt_writer;
			CT_NumFmts* t() { return static_cast<CT_NumFmts*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Fonts_writer : public type_writer
		{
			auto_type_writer< CT_Font_writer > _font_writer;
			CT_Fonts* t() { return static_cast<CT_Fonts*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Fills_writer : public type_writer
		{
			auto_type_writer< CT_Fill_writer > _fill_writer;
			CT_Fills* t() { return static_cast<CT_Fills*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Borders_writer : public type_writer
		{
			auto_type_writer< CT_Border_writer > _border_writer;
			CT_Borders* t() { return static_cast<CT_Borders*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class ST_FillId_writer : public type_writer
		{
			ST_FillId* t() { return static_cast<ST_FillId*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class ST_BorderId_writer : public type_writer
		{
			ST_BorderId* t() { return static_cast<ST_BorderId*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class ST_CellStyleXfId_writer : public type_writer
		{
			ST_CellStyleXfId* t() { return static_cast<ST_CellStyleXfId*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Xf_writer : public type_writer
		{
			auto_type_writer< CT_CellAlignment_writer > _alignment_writer;
			auto_type_writer< CT_CellProtection_writer > _protection_writer;
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_Xf* t() { return static_cast<CT_Xf*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_CellStyleXfs_writer : public type_writer
		{
			auto_type_writer< CT_Xf_writer > _xf_writer;
			CT_CellStyleXfs* t() { return static_cast<CT_CellStyleXfs*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_CellXfs_writer : public type_writer
		{
			auto_type_writer< CT_Xf_writer > _xf_writer;
			CT_CellXfs* t() { return static_cast<CT_CellXfs*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_CellStyle_writer : public type_writer
		{
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_CellStyle* t() { return static_cast<CT_CellStyle*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_CellStyles_writer : public type_writer
		{
			auto_type_writer< CT_CellStyle_writer > _cellStyle_writer;
			CT_CellStyles* t() { return static_cast<CT_CellStyles*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Dxfs_writer : public type_writer
		{
			auto_type_writer< CT_Dxf_writer > _dxf_writer;
			CT_Dxfs* t() { return static_cast<CT_Dxfs*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_TableStyleElement_writer : public type_writer
		{
			CT_TableStyleElement* t() { return static_cast<CT_TableStyleElement*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_TableStyle_writer : public type_writer
		{
			auto_type_writer< CT_TableStyleElement_writer > _tableStyleElement_writer;
			CT_TableStyle* t() { return static_cast<CT_TableStyle*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_TableStyles_writer : public type_writer
		{
			auto_type_writer< CT_TableStyle_writer > _tableStyle_writer;
			CT_TableStyles* t() { return static_cast<CT_TableStyles*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_RgbColor_writer : public type_writer
		{
			CT_RgbColor* t() { return static_cast<CT_RgbColor*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_IndexedColors_writer : public type_writer
		{
			auto_type_writer< CT_RgbColor_writer > _rgbColor_writer;
			CT_IndexedColors* t() { return static_cast<CT_IndexedColors*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_MRUColors_writer : public type_writer
		{
			auto_type_writer< CT_Color_writer > _color_writer;
			CT_MRUColors* t() { return static_cast<CT_MRUColors*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Colors_writer : public type_writer
		{
			auto_type_writer< CT_IndexedColors_writer > _indexedColors_writer;
			auto_type_writer< CT_MRUColors_writer > _mruColors_writer;
			CT_Colors* t() { return static_cast<CT_Colors*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Stylesheet_writer : public type_writer
		{
			auto_type_writer< CT_NumFmts_writer > _numFmts_writer;
			auto_type_writer< CT_Fonts_writer > _fonts_writer;
			auto_type_writer< CT_Fills_writer > _fills_writer;
			auto_type_writer< CT_Borders_writer > _borders_writer;
			auto_type_writer< CT_CellStyleXfs_writer > _cellStyleXfs_writer;
			auto_type_writer< CT_CellXfs_writer > _cellXfs_writer;
			auto_type_writer< CT_CellStyles_writer > _cellStyles_writer;
			auto_type_writer< CT_Dxfs_writer > _dxfs_writer;
			auto_type_writer< CT_TableStyles_writer > _tableStyles_writer;
			auto_type_writer< CT_Colors_writer > _colors_writer;
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_Stylesheet* t() { return static_cast<CT_Stylesheet*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class sml_styles_writer : public type_writer
		{
			auto_type_writer< CT_Stylesheet_writer > _styleSheet_writer;
			sml_styles* t() { return static_cast<sml_styles*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

	}
}
#endif

