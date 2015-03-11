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

#ifndef DML_TEXT_HPP
#define DML_TEXT_HPP


#include "dml-shapeGeometry.hpp"
#include "dml-baseTypes.hpp"
#include "dml-textParagraph.hpp"
#include "dml-shape3DScene.hpp"
#include "dml-shape3DStyles.hpp"
#include "dml-textRun.hpp"
#include "dml-textCharacter.hpp"

namespace drawingml
{
	using namespace ::xio;
	using namespace ::xio::xml::schema;

	class CT_TextNoAutofit;
	class ST_TextFontScalePercent;
	class CT_TextNormalAutofit;
	class CT_TextShapeAutofit;
	class ST_TextColumnCount;
	class CT_TextBodyProperties;
	class CT_TextListStyle;
	class CT_TextParagraph;
	class CT_TextBody;

	class CT_TextNoAutofit
	{
	public:
	};

	class ST_TextFontScalePercent : public ST_Percentage
	{
	public:
		ST_TextFontScalePercent() {}
		ST_TextFontScalePercent(const Int& v) : ST_Percentage(v) {}
		ST_TextFontScalePercent(const String& v) { read(v); }
	};

	class CT_TextNormalAutofit
	{
	public:
		CT_TextNormalAutofit() : fontScale(100000), lnSpcReduction(0) {}
		ST_TextFontScalePercent fontScale;
		ST_TextSpacingPercent lnSpcReduction;
	};

	class CT_TextShapeAutofit
	{
	public:
	};

	class ST_TextVertOverflowType
	{
		static String _literals[];
		String _value;
	public:
		enum value { clip, ellipsis, overflow };

		static const String clip_literal;
		static const String ellipsis_literal;
		static const String overflow_literal;

		ST_TextVertOverflowType() : _value(overflow_literal) {}
		ST_TextVertOverflowType(value val) : _value(convert(val)) {}
		ST_TextVertOverflowType(const String& str) : _value(str) {}

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

	class ST_TextHorzOverflowType
	{
		static String _literals[];
		String _value;
	public:
		enum value { clip, overflow };

		static const String clip_literal;
		static const String overflow_literal;

		ST_TextHorzOverflowType() : _value(overflow_literal) {}
		ST_TextHorzOverflowType(value val) : _value(convert(val)) {}
		ST_TextHorzOverflowType(const String& str) : _value(str) {}

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

	class ST_TextVerticalType
	{
		static String _literals[];
		String _value;
	public:
		enum value { eaVert, horz, mongolianVert, vert, vert270, wordArtVert, wordArtVertRtl };

		static const String eaVert_literal;
		static const String horz_literal;
		static const String mongolianVert_literal;
		static const String vert_literal;
		static const String vert270_literal;
		static const String wordArtVert_literal;
		static const String wordArtVertRtl_literal;

		ST_TextVerticalType() : _value(horz_literal) {}
		ST_TextVerticalType(value val) : _value(convert(val)) {}
		ST_TextVerticalType(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 7, 0); }
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

	class ST_TextWrappingType
	{
		static String _literals[];
		String _value;
	public:
		enum value { none, square };

		static const String none_literal;
		static const String square_literal;

		ST_TextWrappingType() : _value(none_literal) {}
		ST_TextWrappingType(value val) : _value(convert(val)) {}
		ST_TextWrappingType(const String& str) : _value(str) {}

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

	class ST_TextColumnCount : public simple_type<Int>
	{
	public:
		ST_TextColumnCount() {}
		ST_TextColumnCount(const Int& v) : simple_type<Int>(v) {}
		ST_TextColumnCount(const String& v) { read(v); }
	};

	class ST_TextAnchoringType
	{
		static String _literals[];
		String _value;
	public:
		enum value { b, ctr, dist, just, t };

		static const String b_literal;
		static const String ctr_literal;
		static const String dist_literal;
		static const String just_literal;
		static const String t_literal;

		ST_TextAnchoringType() : _value(t_literal) {}
		ST_TextAnchoringType(value val) : _value(convert(val)) {}
		ST_TextAnchoringType(const String& str) : _value(str) {}

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

	class CT_TextBodyProperties
	{
	public:
		CT_TextBodyProperties() : upright(false) {}
		poptional< CT_PresetTextShape > prstTxWarp;
		poptional< CT_TextNoAutofit > noAutofit;
		poptional< CT_TextNormalAutofit > normAutofit;
		poptional< CT_TextShapeAutofit > spAutoFit;
		poptional< CT_Scene3D > scene3d;
		poptional< CT_Shape3D > sp3d;
		poptional< CT_FlatText > flatTx;
		poptional< CT_OfficeArtExtensionList > extLst;
		poptional< ST_Angle > rot;
		optional< Boolean > spcFirstLastPara;
		optional< ST_TextVertOverflowType > vertOverflow;
		optional< ST_TextHorzOverflowType > horzOverflow;
		optional< ST_TextVerticalType > vert;
		optional< ST_TextWrappingType > wrap;
		poptional< ST_Coordinate32 > lIns;
		poptional< ST_Coordinate32 > tIns;
		poptional< ST_Coordinate32 > rIns;
		poptional< ST_Coordinate32 > bIns;
		poptional< ST_TextColumnCount > numCol;
		poptional< ST_PositiveCoordinate32 > spcCol;
		optional< Boolean > rtlCol;
		optional< Boolean > fromWordArt;
		optional< ST_TextAnchoringType > anchor;
		optional< Boolean > anchorCtr;
		optional< Boolean > forceAA;
		Boolean upright;
		optional< Boolean > compatLnSpc;
	};

	class CT_TextListStyle
	{
	public:
		poptional< CT_TextParagraphProperties > defPPr;
		poptional< CT_TextParagraphProperties > lvl1pPr;
		poptional< CT_TextParagraphProperties > lvl2pPr;
		poptional< CT_TextParagraphProperties > lvl3pPr;
		poptional< CT_TextParagraphProperties > lvl4pPr;
		poptional< CT_TextParagraphProperties > lvl5pPr;
		poptional< CT_TextParagraphProperties > lvl6pPr;
		poptional< CT_TextParagraphProperties > lvl7pPr;
		poptional< CT_TextParagraphProperties > lvl8pPr;
		poptional< CT_TextParagraphProperties > lvl9pPr;
		poptional< CT_OfficeArtExtensionList > extLst;
	};

	class CT_TextParagraph
	{
	public:
		poptional< CT_TextParagraphProperties > pPr;
		poptional< CT_RegularTextRun > r;
		poptional< CT_TextLineBreak > br;
		poptional< CT_TextField > fld;
		poptional< CT_TextCharacterProperties > endParaRPr;
	};

	class CT_TextBody
	{
	public:
		CT_TextBodyProperties bodyPr;
		poptional< CT_TextListStyle > lstStyle;
		std::vector< CT_TextParagraph > p;
	};

}
#endif

