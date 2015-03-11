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

#ifndef DML_BASESTYLESHEET_HPP
#define DML_BASESTYLESHEET_HPP


#include "dml-baseTypes.hpp"
#include "dml-textCharacter.hpp"
#include "dml-shapeEffects.hpp"
#include "dml-shapeLineProperties.hpp"
#include "dml-shape3DScene.hpp"
#include "dml-shape3DStyles.hpp"

namespace drawingml
{
	using namespace ::xio;
	using namespace ::xio::xml::schema;

	class ST_StyleMatrixColumnIndex;
	class CT_ColorScheme;
	class CT_SupplementalFont;
	class CT_FontCollection;
	class CT_FontScheme;
	class CT_FillStyleList;
	class CT_LineStyleList;
	class CT_EffectStyleItem;
	class CT_EffectStyleList;
	class CT_BackgroundFillStyleList;
	class CT_StyleMatrix;
	class CT_BaseStyles;
	class CT_CustomColor;
	class CT_CustomColorList;

	class ST_ColorSchemeIndex
	{
		static String _literals[];
		String _value;
	public:
		enum value { accent1, accent2, accent3, accent4, accent5, accent6, dk1, dk2, folHlink, hlink, lt1, lt2 };

		static const String accent1_literal;
		static const String accent2_literal;
		static const String accent3_literal;
		static const String accent4_literal;
		static const String accent5_literal;
		static const String accent6_literal;
		static const String dk1_literal;
		static const String dk2_literal;
		static const String folHlink_literal;
		static const String hlink_literal;
		static const String lt1_literal;
		static const String lt2_literal;

		ST_ColorSchemeIndex() : _value(dk1_literal) {}
		ST_ColorSchemeIndex(value val) : _value(convert(val)) {}
		ST_ColorSchemeIndex(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 12, 0); }
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

	class ST_StyleMatrixColumnIndex : public simple_type<UnsignedInt>
	{
	public:
		ST_StyleMatrixColumnIndex() {}
		ST_StyleMatrixColumnIndex(const UnsignedInt& v) : simple_type<UnsignedInt>(v) {}
		ST_StyleMatrixColumnIndex(const String& v) { read(v); }
	};

	class ST_FontCollectionIndex
	{
		static String _literals[];
		String _value;
	public:
		enum value { major, minor, none };

		static const String major_literal;
		static const String minor_literal;
		static const String none_literal;

		ST_FontCollectionIndex() : _value(major_literal) {}
		ST_FontCollectionIndex(value val) : _value(convert(val)) {}
		ST_FontCollectionIndex(const String& str) : _value(str) {}

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

	class CT_ColorScheme
	{
	public:
		CT_Color dk1;
		CT_Color lt1;
		CT_Color dk2;
		CT_Color lt2;
		CT_Color accent1;
		CT_Color accent2;
		CT_Color accent3;
		CT_Color accent4;
		CT_Color accent5;
		CT_Color accent6;
		CT_Color hlink;
		CT_Color folHlink;
		poptional< CT_OfficeArtExtensionList > extLst;
		String name;
	};

	class CT_SupplementalFont
	{
	public:
		String script;
		ST_TextTypeface typeface;
	};

	class CT_FontCollection
	{
	public:
		CT_TextFont latin;
		CT_TextFont ea;
		CT_TextFont cs;
		std::vector< CT_SupplementalFont > font;
		poptional< CT_OfficeArtExtensionList > extLst;
	};

	class CT_FontScheme
	{
	public:
		CT_FontCollection majorFont;
		CT_FontCollection minorFont;
		poptional< CT_OfficeArtExtensionList > extLst;
		String name;
	};

	class CT_FillStyleList
	{
	public:
		poptional< CT_NoFillProperties > noFill;
		poptional< CT_SolidColorFillProperties > solidFill;
		poptional< CT_GradientFillProperties > gradFill;
		poptional< CT_BlipFillProperties > blipFill;
		poptional< CT_PatternFillProperties > pattFill;
		poptional< CT_GroupFillProperties > grpFill;
	};

	class CT_LineStyleList
	{
	public:
		std::vector< CT_LineProperties > ln;
	};

	class CT_EffectStyleItem
	{
	public:
		poptional< CT_EffectList > effectLst;
		poptional< CT_EffectContainer > effectDag;
		poptional< CT_Scene3D > scene3d;
		poptional< CT_Shape3D > sp3d;
	};

	class CT_EffectStyleList
	{
	public:
		std::vector< CT_EffectStyleItem > effectStyle;
	};

	class CT_BackgroundFillStyleList
	{
	public:
		poptional< CT_NoFillProperties > noFill;
		poptional< CT_SolidColorFillProperties > solidFill;
		poptional< CT_GradientFillProperties > gradFill;
		poptional< CT_BlipFillProperties > blipFill;
		poptional< CT_PatternFillProperties > pattFill;
		poptional< CT_GroupFillProperties > grpFill;
	};

	class CT_StyleMatrix
	{
	public:
		CT_StyleMatrix() : name("") {}
		CT_FillStyleList fillStyleLst;
		CT_LineStyleList lnStyleLst;
		CT_EffectStyleList effectStyleLst;
		CT_BackgroundFillStyleList bgFillStyleLst;
		String name;
	};

	class CT_BaseStyles
	{
	public:
		CT_ColorScheme clrScheme;
		CT_FontScheme fontScheme;
		CT_StyleMatrix fmtScheme;
		poptional< CT_OfficeArtExtensionList > extLst;
	};

	class CT_CustomColor
	{
	public:
		CT_CustomColor() : name("") {}
		poptional< CT_ScRgbColor > scrgbClr;
		poptional< CT_SRgbColor > srgbClr;
		poptional< CT_HslColor > hslClr;
		poptional< CT_SystemColor > sysClr;
		poptional< CT_SchemeColor > schemeClr;
		poptional< CT_PresetColor > prstClr;
		String name;
	};

	class CT_CustomColorList
	{
	public:
		std::vector< CT_CustomColor > custClr;
	};

}
#endif

