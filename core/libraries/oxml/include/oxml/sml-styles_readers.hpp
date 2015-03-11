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

#ifndef SML_STYLES_READERS_HPP
#define SML_STYLES_READERS_HPP

#include "sml-styles.hpp"
#include "sml-baseTypes_readers.hpp"

namespace spreadsheetml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_FontName_reader;
		class CT_IntProperty_reader;
		class CT_BooleanProperty_reader;
		class CT_Color_reader;
		class CT_FontSize_reader;
		class CT_UnderlineProperty_reader;
		class CT_VerticalAlignFontProperty_reader;
		class CT_FontScheme_reader;
		class ST_FontId_reader;
		class ST_NumFmtId_reader;
		class ST_DxfId_reader;
		class CT_Font_reader;
		class CT_NumFmt_reader;
		class CT_PatternFill_reader;
		class CT_GradientStop_reader;
		class CT_GradientFill_reader;
		class CT_Fill_reader;
		class CT_CellAlignment_reader;
		class CT_BorderPr_reader;
		class CT_Border_reader;
		class CT_CellProtection_reader;
		class CT_Dxf_reader;
		class CT_NumFmts_reader;
		class CT_Fonts_reader;
		class CT_Fills_reader;
		class CT_Borders_reader;
		class ST_FillId_reader;
		class ST_BorderId_reader;
		class ST_CellStyleXfId_reader;
		class CT_Xf_reader;
		class CT_CellStyleXfs_reader;
		class CT_CellXfs_reader;
		class CT_CellStyle_reader;
		class CT_CellStyles_reader;
		class CT_Dxfs_reader;
		class CT_TableStyleElement_reader;
		class CT_TableStyle_reader;
		class CT_TableStyles_reader;
		class CT_RgbColor_reader;
		class CT_IndexedColors_reader;
		class CT_MRUColors_reader;
		class CT_Colors_reader;
		class CT_Stylesheet_reader;
		class sml_styles_reader;

		class CT_FontName_reader : public type_reader
		{
		protected:
			CT_FontName* t() { return static_cast<CT_FontName*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_IntProperty_reader : public type_reader
		{
		protected:
			CT_IntProperty* t() { return static_cast<CT_IntProperty*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_BooleanProperty_reader : public type_reader
		{
		protected:
			CT_BooleanProperty* t() { return static_cast<CT_BooleanProperty*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Color_reader : public type_reader
		{
		protected:
			CT_Color* t() { return static_cast<CT_Color*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_FontSize_reader : public type_reader
		{
		protected:
			CT_FontSize* t() { return static_cast<CT_FontSize*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_UnderlineProperty_reader : public type_reader
		{
		protected:
			CT_UnderlineProperty* t() { return static_cast<CT_UnderlineProperty*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_VerticalAlignFontProperty_reader : public type_reader
		{
		protected:
			CT_VerticalAlignFontProperty* t() { return static_cast<CT_VerticalAlignFontProperty*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_FontScheme_reader : public type_reader
		{
		protected:
			CT_FontScheme* t() { return static_cast<CT_FontScheme*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class ST_FontId_reader : public type_reader
		{
		protected:
			ST_FontId* t() { return static_cast<ST_FontId*>(target()); }
			void read_value(const xstring& val);
		};

		class ST_NumFmtId_reader : public type_reader
		{
		protected:
			ST_NumFmtId* t() { return static_cast<ST_NumFmtId*>(target()); }
			void read_value(const xstring& val);
		};

		class ST_DxfId_reader : public type_reader
		{
		protected:
			ST_DxfId* t() { return static_cast<ST_DxfId*>(target()); }
			void read_value(const xstring& val);
		};

		class CT_Font_reader : public type_reader
		{
			auto_type_reader< CT_FontName_reader > _name_reader;
			auto_type_reader< CT_IntProperty_reader > _charset_reader;
			auto_type_reader< CT_IntProperty_reader > _family_reader;
			auto_type_reader< CT_BooleanProperty_reader > _b_reader;
			auto_type_reader< CT_BooleanProperty_reader > _i_reader;
			auto_type_reader< CT_BooleanProperty_reader > _strike_reader;
			auto_type_reader< CT_BooleanProperty_reader > _outline_reader;
			auto_type_reader< CT_BooleanProperty_reader > _shadow_reader;
			auto_type_reader< CT_BooleanProperty_reader > _condense_reader;
			auto_type_reader< CT_BooleanProperty_reader > _extend_reader;
			auto_type_reader< CT_Color_reader > _color_reader;
			auto_type_reader< CT_FontSize_reader > _sz_reader;
			auto_type_reader< CT_UnderlineProperty_reader > _u_reader;
			auto_type_reader< CT_VerticalAlignFontProperty_reader > _vertAlign_reader;
			auto_type_reader< CT_FontScheme_reader > _scheme_reader;
		protected:
			CT_Font* t() { return static_cast<CT_Font*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_NumFmt_reader : public type_reader
		{
		protected:
			CT_NumFmt* t() { return static_cast<CT_NumFmt*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_PatternFill_reader : public type_reader
		{
			auto_type_reader< CT_Color_reader > _fgColor_reader;
			auto_type_reader< CT_Color_reader > _bgColor_reader;
		protected:
			CT_PatternFill* t() { return static_cast<CT_PatternFill*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_GradientStop_reader : public type_reader
		{
			auto_type_reader< CT_Color_reader > _color_reader;
		protected:
			CT_GradientStop* t() { return static_cast<CT_GradientStop*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_GradientFill_reader : public type_reader
		{
			auto_type_reader< CT_GradientStop_reader > _stop_reader;
		protected:
			CT_GradientFill* t() { return static_cast<CT_GradientFill*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Fill_reader : public type_reader
		{
			auto_type_reader< CT_PatternFill_reader > _patternFill_reader;
			auto_type_reader< CT_GradientFill_reader > _gradientFill_reader;
		protected:
			CT_Fill* t() { return static_cast<CT_Fill*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_CellAlignment_reader : public type_reader
		{
		protected:
			CT_CellAlignment* t() { return static_cast<CT_CellAlignment*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_BorderPr_reader : public type_reader
		{
			auto_type_reader< CT_Color_reader > _color_reader;
		protected:
			CT_BorderPr* t() { return static_cast<CT_BorderPr*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Border_reader : public type_reader
		{
			auto_type_reader< CT_BorderPr_reader > _left_reader;
			auto_type_reader< CT_BorderPr_reader > _right_reader;
			auto_type_reader< CT_BorderPr_reader > _top_reader;
			auto_type_reader< CT_BorderPr_reader > _bottom_reader;
			auto_type_reader< CT_BorderPr_reader > _diagonal_reader;
			auto_type_reader< CT_BorderPr_reader > _vertical_reader;
			auto_type_reader< CT_BorderPr_reader > _horizontal_reader;
		protected:
			CT_Border* t() { return static_cast<CT_Border*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_CellProtection_reader : public type_reader
		{
		protected:
			CT_CellProtection* t() { return static_cast<CT_CellProtection*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Dxf_reader : public type_reader
		{
			auto_type_reader< CT_Font_reader > _font_reader;
			auto_type_reader< CT_NumFmt_reader > _numFmt_reader;
			auto_type_reader< CT_Fill_reader > _fill_reader;
			auto_type_reader< CT_CellAlignment_reader > _alignment_reader;
			auto_type_reader< CT_Border_reader > _border_reader;
			auto_type_reader< CT_CellProtection_reader > _protection_reader;
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_Dxf* t() { return static_cast<CT_Dxf*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_NumFmts_reader : public type_reader
		{
			auto_type_reader< CT_NumFmt_reader > _numFmt_reader;
		protected:
			CT_NumFmts* t() { return static_cast<CT_NumFmts*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Fonts_reader : public type_reader
		{
			auto_type_reader< CT_Font_reader > _font_reader;
		protected:
			CT_Fonts* t() { return static_cast<CT_Fonts*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Fills_reader : public type_reader
		{
			auto_type_reader< CT_Fill_reader > _fill_reader;
		protected:
			CT_Fills* t() { return static_cast<CT_Fills*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Borders_reader : public type_reader
		{
			auto_type_reader< CT_Border_reader > _border_reader;
		protected:
			CT_Borders* t() { return static_cast<CT_Borders*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class ST_FillId_reader : public type_reader
		{
		protected:
			ST_FillId* t() { return static_cast<ST_FillId*>(target()); }
			void read_value(const xstring& val);
		};

		class ST_BorderId_reader : public type_reader
		{
		protected:
			ST_BorderId* t() { return static_cast<ST_BorderId*>(target()); }
			void read_value(const xstring& val);
		};

		class ST_CellStyleXfId_reader : public type_reader
		{
		protected:
			ST_CellStyleXfId* t() { return static_cast<ST_CellStyleXfId*>(target()); }
			void read_value(const xstring& val);
		};

		class CT_Xf_reader : public type_reader
		{
			auto_type_reader< CT_CellAlignment_reader > _alignment_reader;
			auto_type_reader< CT_CellProtection_reader > _protection_reader;
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_Xf* t() { return static_cast<CT_Xf*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_CellStyleXfs_reader : public type_reader
		{
			auto_type_reader< CT_Xf_reader > _xf_reader;
		protected:
			CT_CellStyleXfs* t() { return static_cast<CT_CellStyleXfs*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_CellXfs_reader : public type_reader
		{
			auto_type_reader< CT_Xf_reader > _xf_reader;
		protected:
			CT_CellXfs* t() { return static_cast<CT_CellXfs*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_CellStyle_reader : public type_reader
		{
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_CellStyle* t() { return static_cast<CT_CellStyle*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_CellStyles_reader : public type_reader
		{
			auto_type_reader< CT_CellStyle_reader > _cellStyle_reader;
		protected:
			CT_CellStyles* t() { return static_cast<CT_CellStyles*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Dxfs_reader : public type_reader
		{
			auto_type_reader< CT_Dxf_reader > _dxf_reader;
		protected:
			CT_Dxfs* t() { return static_cast<CT_Dxfs*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_TableStyleElement_reader : public type_reader
		{
		protected:
			CT_TableStyleElement* t() { return static_cast<CT_TableStyleElement*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_TableStyle_reader : public type_reader
		{
			auto_type_reader< CT_TableStyleElement_reader > _tableStyleElement_reader;
		protected:
			CT_TableStyle* t() { return static_cast<CT_TableStyle*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_TableStyles_reader : public type_reader
		{
			auto_type_reader< CT_TableStyle_reader > _tableStyle_reader;
		protected:
			CT_TableStyles* t() { return static_cast<CT_TableStyles*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_RgbColor_reader : public type_reader
		{
		protected:
			CT_RgbColor* t() { return static_cast<CT_RgbColor*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_IndexedColors_reader : public type_reader
		{
			auto_type_reader< CT_RgbColor_reader > _rgbColor_reader;
		protected:
			CT_IndexedColors* t() { return static_cast<CT_IndexedColors*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_MRUColors_reader : public type_reader
		{
			auto_type_reader< CT_Color_reader > _color_reader;
		protected:
			CT_MRUColors* t() { return static_cast<CT_MRUColors*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_Colors_reader : public type_reader
		{
			auto_type_reader< CT_IndexedColors_reader > _indexedColors_reader;
			auto_type_reader< CT_MRUColors_reader > _mruColors_reader;
		protected:
			CT_Colors* t() { return static_cast<CT_Colors*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_Stylesheet_reader : public type_reader
		{
			auto_type_reader< CT_NumFmts_reader > _numFmts_reader;
			auto_type_reader< CT_Fonts_reader > _fonts_reader;
			auto_type_reader< CT_Fills_reader > _fills_reader;
			auto_type_reader< CT_Borders_reader > _borders_reader;
			auto_type_reader< CT_CellStyleXfs_reader > _cellStyleXfs_reader;
			auto_type_reader< CT_CellXfs_reader > _cellXfs_reader;
			auto_type_reader< CT_CellStyles_reader > _cellStyles_reader;
			auto_type_reader< CT_Dxfs_reader > _dxfs_reader;
			auto_type_reader< CT_TableStyles_reader > _tableStyles_reader;
			auto_type_reader< CT_Colors_reader > _colors_reader;
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_Stylesheet* t() { return static_cast<CT_Stylesheet*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class sml_styles_reader : public type_reader
		{
			auto_type_reader< CT_Stylesheet_reader > _styleSheet_reader;
		protected:
			sml_styles* t() { return static_cast<sml_styles*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

	}
}
#endif

