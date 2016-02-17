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

#ifndef SML_STYLES_HPP
#define SML_STYLES_HPP


#include "sml-baseTypes.hpp"

namespace spreadsheetml
{
	using namespace ::xio;
	using namespace ::xio::xml::schema;

	class CT_FontName;
	class CT_IntProperty;
	class CT_BooleanProperty;
	class CT_Color;
	class CT_FontSize;
	class CT_UnderlineProperty;
	class CT_VerticalAlignFontProperty;
	class CT_FontScheme;
	class ST_FontId;
	class ST_NumFmtId;
	class ST_DxfId;
	class CT_Font;
	class CT_NumFmt;
	class CT_PatternFill;
	class CT_GradientStop;
	class CT_GradientFill;
	class CT_Fill;
	class CT_CellAlignment;
	class CT_BorderPr;
	class CT_Border;
	class CT_CellProtection;
	class CT_Dxf;
	class CT_NumFmts;
	class CT_Fonts;
	class CT_Fills;
	class CT_Borders;
	class ST_FillId;
	class ST_BorderId;
	class ST_CellStyleXfId;
	class CT_Xf;
	class CT_CellStyleXfs;
	class CT_CellXfs;
	class CT_CellStyle;
	class CT_CellStyles;
	class CT_Dxfs;
	class CT_TableStyleElement;
	class CT_TableStyle;
	class CT_TableStyles;
	class CT_RgbColor;
	class CT_IndexedColors;
	class CT_MRUColors;
	class CT_Colors;
	class CT_Stylesheet;
	class sml_styles;

	class CT_FontName
	{
	public:
		ST_Xstring val;
	};

	class CT_IntProperty
	{
	public:
		Int val;
	};

	class CT_BooleanProperty
	{
	public:
		CT_BooleanProperty() : val(true) {}
		Boolean val;
	};

	class CT_Color
	{
	public:
		CT_Color() : tint(0.0) {}
		optional< Boolean > _auto_;
		optional< UnsignedInt > indexed;
		poptional< ST_UnsignedIntHex > rgb;
		optional< UnsignedInt > theme;
		Double tint;
	};

	class CT_FontSize
	{
	public:
		Double val;
	};

	class ST_UnderlineValues
	{
		static String _literals[];
		String _value;
	public:
		enum value { _double_, doubleAccounting, none, single, singleAccounting };

		static const String _double__literal;
		static const String doubleAccounting_literal;
		static const String none_literal;
		static const String single_literal;
		static const String singleAccounting_literal;

		ST_UnderlineValues() : _value(single_literal) {}
		ST_UnderlineValues(value val) : _value(convert(val)) {}
		ST_UnderlineValues(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 5, 0); }
		static String convert(value v) { return _literals[(int)v]; }

		bool operator == (const String& str) const { return str == _value; }
		bool operator == (value val) const {return convert(val) == _value; }
		bool operator != (const String& str) const { return str != _value; }
		bool operator != (value val) const {return convert(val) != _value; }

		const String& operator = (const String& str) { _value = str; return str; }
		const value& operator = (const value& val) { _value = convert(val); return val; }

		operator const String& () const { return _value; }
		operator String& () { return _value; }
		operator value () const { return convert(_value); }
		String serialize() const { return _value; }
	};

	class CT_UnderlineProperty
	{
	public:
		CT_UnderlineProperty() : val(ST_UnderlineValues::single_literal) {}
		ST_UnderlineValues val;
	};

	class ST_VerticalAlignRun
	{
		static String _literals[];
		String _value;
	public:
		enum value { baseline, subscript, superscript };

		static const String baseline_literal;
		static const String subscript_literal;
		static const String superscript_literal;

		ST_VerticalAlignRun() : _value(baseline_literal) {}
		ST_VerticalAlignRun(value val) : _value(convert(val)) {}
		ST_VerticalAlignRun(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 3, 0); }
		static String convert(value v) { return _literals[(int)v]; }

		bool operator == (const String& str) const { return str == _value; }
		bool operator == (value val) const {return convert(val) == _value; }
		bool operator != (const String& str) const { return str != _value; }
		bool operator != (value val) const {return convert(val) != _value; }

		const String& operator = (const String& str) { _value = str; return str; }
		const value& operator = (const value& val) { _value = convert(val); return val; }

		operator const String& () const { return _value; }
		operator String& () { return _value; }
		operator value () const { return convert(_value); }
		String serialize() const { return _value; }
	};

	class CT_VerticalAlignFontProperty
	{
	public:
		ST_VerticalAlignRun val;
	};

	class ST_FontScheme
	{
		static String _literals[];
		String _value;
	public:
		enum value { major, minor, none };

		static const String major_literal;
		static const String minor_literal;
		static const String none_literal;

		ST_FontScheme() : _value(none_literal) {}
		ST_FontScheme(value val) : _value(convert(val)) {}
		ST_FontScheme(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 3, 0); }
		static String convert(value v) { return _literals[(int)v]; }

		bool operator == (const String& str) const { return str == _value; }
		bool operator == (value val) const {return convert(val) == _value; }
		bool operator != (const String& str) const { return str != _value; }
		bool operator != (value val) const {return convert(val) != _value; }

		const String& operator = (const String& str) { _value = str; return str; }
		const value& operator = (const value& val) { _value = convert(val); return val; }

		operator const String& () const { return _value; }
		operator String& () { return _value; }
		operator value () const { return convert(_value); }
		String serialize() const { return _value; }
	};

	class CT_FontScheme
	{
	public:
		ST_FontScheme val;
	};

	class ST_FontId : public simple_type<UnsignedInt>
	{
	public:
		ST_FontId() {}
		ST_FontId(const UnsignedInt& v) : simple_type<UnsignedInt>(v) {}
		ST_FontId(const String& v) { read(v); }
	};

	class ST_NumFmtId : public simple_type<UnsignedInt>
	{
	public:
		ST_NumFmtId() {}
		ST_NumFmtId(const UnsignedInt& v) : simple_type<UnsignedInt>(v) {}
		ST_NumFmtId(const String& v) { read(v); }
	};

	class ST_DxfId : public simple_type<UnsignedInt>
	{
	public:
		ST_DxfId() {}
		ST_DxfId(const UnsignedInt& v) : simple_type<UnsignedInt>(v) {}
		ST_DxfId(const String& v) { read(v); }
	};

	class CT_Font
	{
	public:
		poptional< CT_FontName > name;
		poptional< CT_IntProperty > charset;
		poptional< CT_IntProperty > family;
		poptional< CT_BooleanProperty > b;
		poptional< CT_BooleanProperty > i;
		poptional< CT_BooleanProperty > strike;
		poptional< CT_BooleanProperty > outline;
		poptional< CT_BooleanProperty > shadow;
		poptional< CT_BooleanProperty > condense;
		poptional< CT_BooleanProperty > extend;
		poptional< CT_Color > color;
		poptional< CT_FontSize > sz;
		poptional< CT_UnderlineProperty > u;
		poptional< CT_VerticalAlignFontProperty > vertAlign;
		poptional< CT_FontScheme > scheme;
	};

	class CT_NumFmt
	{
	public:
		ST_NumFmtId numFmtId;
		ST_Xstring formatCode;
	};

	class ST_PatternType
	{
		static String _literals[];
		String _value;
	public:
		enum value { darkDown, darkGray, darkGrid, darkHorizontal, darkTrellis, darkUp, darkVertical, gray0625, gray125, lightDown, lightGray, lightGrid, lightHorizontal, lightTrellis, lightUp, lightVertical, mediumGray, none, solid };

		static const String darkDown_literal;
		static const String darkGray_literal;
		static const String darkGrid_literal;
		static const String darkHorizontal_literal;
		static const String darkTrellis_literal;
		static const String darkUp_literal;
		static const String darkVertical_literal;
		static const String gray0625_literal;
		static const String gray125_literal;
		static const String lightDown_literal;
		static const String lightGray_literal;
		static const String lightGrid_literal;
		static const String lightHorizontal_literal;
		static const String lightTrellis_literal;
		static const String lightUp_literal;
		static const String lightVertical_literal;
		static const String mediumGray_literal;
		static const String none_literal;
		static const String solid_literal;

		ST_PatternType() : _value(none_literal) {}
		ST_PatternType(value val) : _value(convert(val)) {}
		ST_PatternType(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 19, 0); }
		static String convert(value v) { return _literals[(int)v]; }

		bool operator == (const String& str) const { return str == _value; }
		bool operator == (value val) const {return convert(val) == _value; }
		bool operator != (const String& str) const { return str != _value; }
		bool operator != (value val) const {return convert(val) != _value; }

		const String& operator = (const String& str) { _value = str; return str; }
		const value& operator = (const value& val) { _value = convert(val); return val; }

		operator const String& () const { return _value; }
		operator String& () { return _value; }
		operator value () const { return convert(_value); }
		String serialize() const { return _value; }
	};

	class CT_PatternFill
	{
	public:
		poptional< CT_Color > fgColor;
		poptional< CT_Color > bgColor;
		optional< ST_PatternType > patternType;
	};

	class CT_GradientStop
	{
	public:
		CT_Color color;
		Double position;
	};

	class ST_GradientType
	{
		static String _literals[];
		String _value;
	public:
		enum value { linear, path };

		static const String linear_literal;
		static const String path_literal;

		ST_GradientType() : _value(linear_literal) {}
		ST_GradientType(value val) : _value(convert(val)) {}
		ST_GradientType(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 2, 0); }
		static String convert(value v) { return _literals[(int)v]; }

		bool operator == (const String& str) const { return str == _value; }
		bool operator == (value val) const {return convert(val) == _value; }
		bool operator != (const String& str) const { return str != _value; }
		bool operator != (value val) const {return convert(val) != _value; }

		const String& operator = (const String& str) { _value = str; return str; }
		const value& operator = (const value& val) { _value = convert(val); return val; }

		operator const String& () const { return _value; }
		operator String& () { return _value; }
		operator value () const { return convert(_value); }
		String serialize() const { return _value; }
	};

	class CT_GradientFill
	{
	public:
		CT_GradientFill() : type(ST_GradientType::linear_literal), degree(0), left(0), right(0), top(0), bottom(0) {}
		std::vector< CT_GradientStop > stop;
		ST_GradientType type;
		Double degree;
		Double left;
		Double right;
		Double top;
		Double bottom;
	};

	class CT_Fill
	{
	public:
		poptional< CT_PatternFill > patternFill;
		poptional< CT_GradientFill > gradientFill;
	};

	class ST_HorizontalAlignment
	{
		static String _literals[];
		String _value;
	public:
		enum value { center, centerContinuous, distributed, fill, general, justify, left, right };

		static const String center_literal;
		static const String centerContinuous_literal;
		static const String distributed_literal;
		static const String fill_literal;
		static const String general_literal;
		static const String justify_literal;
		static const String left_literal;
		static const String right_literal;

		ST_HorizontalAlignment() : _value(general_literal) {}
		ST_HorizontalAlignment(value val) : _value(convert(val)) {}
		ST_HorizontalAlignment(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 8, 0); }
		static String convert(value v) { return _literals[(int)v]; }

		bool operator == (const String& str) const { return str == _value; }
		bool operator == (value val) const {return convert(val) == _value; }
		bool operator != (const String& str) const { return str != _value; }
		bool operator != (value val) const {return convert(val) != _value; }

		const String& operator = (const String& str) { _value = str; return str; }
		const value& operator = (const value& val) { _value = convert(val); return val; }

		operator const String& () const { return _value; }
		operator String& () { return _value; }
		operator value () const { return convert(_value); }
		String serialize() const { return _value; }
	};

	class ST_VerticalAlignment
	{
		static String _literals[];
		String _value;
	public:
		enum value { bottom, center, distributed, justify, top };

		static const String bottom_literal;
		static const String center_literal;
		static const String distributed_literal;
		static const String justify_literal;
		static const String top_literal;

		ST_VerticalAlignment() : _value(top_literal) {}
		ST_VerticalAlignment(value val) : _value(convert(val)) {}
		ST_VerticalAlignment(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 5, 0); }
		static String convert(value v) { return _literals[(int)v]; }

		bool operator == (const String& str) const { return str == _value; }
		bool operator == (value val) const {return convert(val) == _value; }
		bool operator != (const String& str) const { return str != _value; }
		bool operator != (value val) const {return convert(val) != _value; }

		const String& operator = (const String& str) { _value = str; return str; }
		const value& operator = (const value& val) { _value = convert(val); return val; }

		operator const String& () const { return _value; }
		operator String& () { return _value; }
		operator value () const { return convert(_value); }
		String serialize() const { return _value; }
	};

	class CT_CellAlignment
	{
	public:
		optional< ST_HorizontalAlignment > horizontal;
		optional< ST_VerticalAlignment > vertical;
		optional< UnsignedInt > textRotation;
		optional< Boolean > wrapText;
		optional< UnsignedInt > indent;
		optional< Int > relativeIndent;
		optional< Boolean > justifyLastLine;
		optional< Boolean > shrinkToFit;
		optional< UnsignedInt > readingOrder;
	};

	class ST_BorderStyle
	{
		static String _literals[];
		String _value;
	public:
		enum value { dashDot, dashDotDot, dashed, dotted, _double_, hair, medium, mediumDashDot, mediumDashDotDot, mediumDashed, none, slantDashDot, thick, thin };

		static const String dashDot_literal;
		static const String dashDotDot_literal;
		static const String dashed_literal;
		static const String dotted_literal;
		static const String _double__literal;
		static const String hair_literal;
		static const String medium_literal;
		static const String mediumDashDot_literal;
		static const String mediumDashDotDot_literal;
		static const String mediumDashed_literal;
		static const String none_literal;
		static const String slantDashDot_literal;
		static const String thick_literal;
		static const String thin_literal;

		ST_BorderStyle() : _value(none_literal) {}
		ST_BorderStyle(value val) : _value(convert(val)) {}
		ST_BorderStyle(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 14, 0); }
		static String convert(value v) { return _literals[(int)v]; }

		bool operator == (const String& str) const { return str == _value; }
		bool operator == (value val) const {return convert(val) == _value; }
		bool operator != (const String& str) const { return str != _value; }
		bool operator != (value val) const {return convert(val) != _value; }

		const String& operator = (const String& str) { _value = str; return str; }
		const value& operator = (const value& val) { _value = convert(val); return val; }

		operator const String& () const { return _value; }
		operator String& () { return _value; }
		operator value () const { return convert(_value); }
		String serialize() const { return _value; }
	};

	class CT_BorderPr
	{
	public:
		CT_BorderPr() : style(ST_BorderStyle::none_literal) {}
		poptional< CT_Color > color;
		ST_BorderStyle style;
	};

	class CT_Border
	{
	public:
		CT_Border() : outline(true) {}
		poptional< CT_BorderPr > left;
		poptional< CT_BorderPr > right;
		poptional< CT_BorderPr > top;
		poptional< CT_BorderPr > bottom;
		poptional< CT_BorderPr > diagonal;
		poptional< CT_BorderPr > vertical;
		poptional< CT_BorderPr > horizontal;
		optional< Boolean > diagonalUp;
		optional< Boolean > diagonalDown;
		Boolean outline;
	};

	class CT_CellProtection
	{
	public:
		optional< Boolean > locked;
		optional< Boolean > hidden;
	};

	class CT_Dxf
	{
	public:
		poptional< CT_Font > font;
		poptional< CT_NumFmt > numFmt;
		poptional< CT_Fill > fill;
		poptional< CT_CellAlignment > alignment;
		poptional< CT_Border > border;
		poptional< CT_CellProtection > protection;
		poptional< CT_ExtensionList > extLst;
	};

	class CT_NumFmts
	{
	public:
		std::vector< CT_NumFmt > numFmt;
		optional< UnsignedInt > count;
	};

	class CT_Fonts
	{
	public:
		std::vector< CT_Font > font;
		optional< UnsignedInt > count;
	};

	class CT_Fills
	{
	public:
		std::vector< CT_Fill > fill;
		optional< UnsignedInt > count;
	};

	class CT_Borders
	{
	public:
		std::vector< CT_Border > border;
		optional< UnsignedInt > count;
	};

	class ST_FillId : public simple_type<UnsignedInt>
	{
	public:
		ST_FillId() {}
		ST_FillId(const UnsignedInt& v) : simple_type<UnsignedInt>(v) {}
		ST_FillId(const String& v) { read(v); }
	};

	class ST_BorderId : public simple_type<UnsignedInt>
	{
	public:
		ST_BorderId() {}
		ST_BorderId(const UnsignedInt& v) : simple_type<UnsignedInt>(v) {}
		ST_BorderId(const String& v) { read(v); }
	};

	class ST_CellStyleXfId : public simple_type<UnsignedInt>
	{
	public:
		ST_CellStyleXfId() {}
		ST_CellStyleXfId(const UnsignedInt& v) : simple_type<UnsignedInt>(v) {}
		ST_CellStyleXfId(const String& v) { read(v); }
	};

	class CT_Xf
	{
	public:
		CT_Xf() : quotePrefix(false), pivotButton(false) {}
		poptional< CT_CellAlignment > alignment;
		poptional< CT_CellProtection > protection;
		poptional< CT_ExtensionList > extLst;
		poptional< ST_NumFmtId > numFmtId;
		poptional< ST_FontId > fontId;
		poptional< ST_FillId > fillId;
		poptional< ST_BorderId > borderId;
		poptional< ST_CellStyleXfId > xfId;
		Boolean quotePrefix;
		Boolean pivotButton;
		optional< Boolean > applyNumberFormat;
		optional< Boolean > applyFont;
		optional< Boolean > applyFill;
		optional< Boolean > applyBorder;
		optional< Boolean > applyAlignment;
		optional< Boolean > applyProtection;
	};

	class CT_CellStyleXfs
	{
	public:
		std::vector< CT_Xf > xf;
		optional< UnsignedInt > count;
	};

	class CT_CellXfs
	{
	public:
		std::vector< CT_Xf > xf;
		optional< UnsignedInt > count;
	};

	class CT_CellStyle
	{
	public:
		poptional< CT_ExtensionList > extLst;
		poptional< ST_Xstring > name;
		ST_CellStyleXfId xfId;
		optional< UnsignedInt > builtinId;
		optional< UnsignedInt > iLevel;
		optional< Boolean > hidden;
		optional< Boolean > customBuiltin;
	};

	class CT_CellStyles
	{
	public:
		std::vector< CT_CellStyle > cellStyle;
		optional< UnsignedInt > count;
	};

	class CT_Dxfs
	{
	public:
		std::vector< CT_Dxf > dxf;
		optional< UnsignedInt > count;
	};

	class ST_TableStyleType
	{
		static String _literals[];
		String _value;
	public:
		enum value { blankRow, firstColumn, firstColumnStripe, firstColumnSubheading, firstHeaderCell, firstRowStripe, firstRowSubheading, firstSubtotalColumn, firstSubtotalRow, firstTotalCell, headerRow, lastColumn, lastHeaderCell, lastTotalCell, pageFieldLabels, pageFieldValues, secondColumnStripe, secondColumnSubheading, secondRowStripe, secondRowSubheading, secondSubtotalColumn, secondSubtotalRow, thirdColumnSubheading, thirdRowSubheading, thirdSubtotalColumn, thirdSubtotalRow, totalRow, wholeTable };

		static const String blankRow_literal;
		static const String firstColumn_literal;
		static const String firstColumnStripe_literal;
		static const String firstColumnSubheading_literal;
		static const String firstHeaderCell_literal;
		static const String firstRowStripe_literal;
		static const String firstRowSubheading_literal;
		static const String firstSubtotalColumn_literal;
		static const String firstSubtotalRow_literal;
		static const String firstTotalCell_literal;
		static const String headerRow_literal;
		static const String lastColumn_literal;
		static const String lastHeaderCell_literal;
		static const String lastTotalCell_literal;
		static const String pageFieldLabels_literal;
		static const String pageFieldValues_literal;
		static const String secondColumnStripe_literal;
		static const String secondColumnSubheading_literal;
		static const String secondRowStripe_literal;
		static const String secondRowSubheading_literal;
		static const String secondSubtotalColumn_literal;
		static const String secondSubtotalRow_literal;
		static const String thirdColumnSubheading_literal;
		static const String thirdRowSubheading_literal;
		static const String thirdSubtotalColumn_literal;
		static const String thirdSubtotalRow_literal;
		static const String totalRow_literal;
		static const String wholeTable_literal;

		ST_TableStyleType() : _value(wholeTable_literal) {}
		ST_TableStyleType(value val) : _value(convert(val)) {}
		ST_TableStyleType(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 28, 0); }
		static String convert(value v) { return _literals[(int)v]; }

		bool operator == (const String& str) const { return str == _value; }
		bool operator == (value val) const {return convert(val) == _value; }
		bool operator != (const String& str) const { return str != _value; }
		bool operator != (value val) const {return convert(val) != _value; }

		const String& operator = (const String& str) { _value = str; return str; }
		const value& operator = (const value& val) { _value = convert(val); return val; }

		operator const String& () const { return _value; }
		operator String& () { return _value; }
		operator value () const { return convert(_value); }
		String serialize() const { return _value; }
	};

	class CT_TableStyleElement
	{
	public:
		CT_TableStyleElement() : size(1U) {}
		ST_TableStyleType type;
		UnsignedInt size;
		poptional< ST_DxfId > dxfId;
	};

	class CT_TableStyle
	{
	public:
		CT_TableStyle() : pivot(true), table(true) {}
		std::vector< CT_TableStyleElement > tableStyleElement;
		String name;
		Boolean pivot;
		Boolean table;
		optional< UnsignedInt > count;
	};

	class CT_TableStyles
	{
	public:
		std::vector< CT_TableStyle > tableStyle;
		optional< UnsignedInt > count;
		optional< String > defaultTableStyle;
		optional< String > defaultPivotStyle;
	};

	class CT_RgbColor
	{
	public:
		poptional< ST_UnsignedIntHex > rgb;
	};

	class CT_IndexedColors
	{
	public:
		std::vector< CT_RgbColor > rgbColor;
	};

	class CT_MRUColors
	{
	public:
		std::vector< CT_Color > color;
	};

	class CT_Colors
	{
	public:
		poptional< CT_IndexedColors > indexedColors;
		poptional< CT_MRUColors > mruColors;
	};

	class CT_Stylesheet
	{
	public:
		poptional< CT_NumFmts > numFmts;
		poptional< CT_Fonts > fonts;
		poptional< CT_Fills > fills;
		poptional< CT_Borders > borders;
		poptional< CT_CellStyleXfs > cellStyleXfs;
		poptional< CT_CellXfs > cellXfs;
		poptional< CT_CellStyles > cellStyles;
		poptional< CT_Dxfs > dxfs;
		poptional< CT_TableStyles > tableStyles;
		poptional< CT_Colors > colors;
		poptional< CT_ExtensionList > extLst;
	};

	class sml_styles
	{
	public:
		poptional< CT_Stylesheet > styleSheet;
	};

}
#endif

