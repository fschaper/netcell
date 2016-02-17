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

#ifndef DML_TEXTCHARACTER_HPP
#define DML_TEXTCHARACTER_HPP


#include "dml-shapeLineProperties.hpp"
#include "dml-shapeEffects.hpp"
#include "dml-baseTypes.hpp"

namespace drawingml
{
	using namespace ::xio;
	using namespace ::xio::xml::schema;

	class ST_TextFontSize;
	class ST_TextTypeface;
	class ST_Panose;
	class CT_TextFont;
	class CT_TextUnderlineLineFollowText;
	class CT_TextUnderlineFillFollowText;
	class CT_TextUnderlineFillGroupWrapper;
	class ST_TextLanguageID;
	class ST_TextNonNegativePoint;
	class ST_TextPoint;
	class CT_TextCharacterProperties;

	class ST_TextFontSize : public simple_type<Int>
	{
	public:
		ST_TextFontSize() {}
		ST_TextFontSize(const Int& v) : simple_type<Int>(v) {}
		ST_TextFontSize(const String& v) { read(v); }
	};

	class ST_TextTypeface : public simple_type<String>
	{
	public:
		ST_TextTypeface() {}
		ST_TextTypeface(const String& v) : simple_type<String>(v) {}
	};

	class ST_Panose : public simple_type<HexBinary>
	{
	public:
		ST_Panose() {}
		ST_Panose(const HexBinary& v) : simple_type<HexBinary>(v) {}
		ST_Panose(const String& v) { read(v); }
	};

	class CT_TextFont
	{
	public:
		CT_TextFont() : pitchFamily(0), charset(1) {}
		poptional< ST_TextTypeface > typeface;
		poptional< ST_Panose > panose;
		Byte pitchFamily;
		Byte charset;
	};

	class CT_TextUnderlineLineFollowText
	{
	public:
	};

	class CT_TextUnderlineFillFollowText
	{
	public:
	};

	class CT_TextUnderlineFillGroupWrapper
	{
	public:
		poptional< CT_NoFillProperties > noFill;
		poptional< CT_SolidColorFillProperties > solidFill;
		poptional< CT_GradientFillProperties > gradFill;
		poptional< CT_BlipFillProperties > blipFill;
		poptional< CT_PatternFillProperties > pattFill;
		poptional< CT_GroupFillProperties > grpFill;
	};

	class ST_TextLanguageID : public simple_type<String>
	{
	public:
		ST_TextLanguageID() {}
		ST_TextLanguageID(const String& v) : simple_type<String>(v) {}
	};

	class ST_TextUnderlineType
	{
		static String _literals[];
		String _value;
	public:
		enum value { dash, dashHeavy, dashLong, dashLongHeavy, dbl, dotDash, dotDashHeavy, dotDotDash, dotDotDashHeavy, dotted, dottedHeavy, heavy, none, sng, wavy, wavyDbl, wavyHeavy, words };

		static const String dash_literal;
		static const String dashHeavy_literal;
		static const String dashLong_literal;
		static const String dashLongHeavy_literal;
		static const String dbl_literal;
		static const String dotDash_literal;
		static const String dotDashHeavy_literal;
		static const String dotDotDash_literal;
		static const String dotDotDashHeavy_literal;
		static const String dotted_literal;
		static const String dottedHeavy_literal;
		static const String heavy_literal;
		static const String none_literal;
		static const String sng_literal;
		static const String wavy_literal;
		static const String wavyDbl_literal;
		static const String wavyHeavy_literal;
		static const String words_literal;

		ST_TextUnderlineType() : _value(none_literal) {}
		ST_TextUnderlineType(value val) : _value(convert(val)) {}
		ST_TextUnderlineType(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 18, 0); }
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

	class ST_TextStrikeType
	{
		static String _literals[];
		String _value;
	public:
		enum value { dblStrike, noStrike, sngStrike };

		static const String dblStrike_literal;
		static const String noStrike_literal;
		static const String sngStrike_literal;

		ST_TextStrikeType() : _value(noStrike_literal) {}
		ST_TextStrikeType(value val) : _value(convert(val)) {}
		ST_TextStrikeType(const String& str) : _value(str) {}

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

	class ST_TextNonNegativePoint : public simple_type<Int>
	{
	public:
		ST_TextNonNegativePoint() {}
		ST_TextNonNegativePoint(const Int& v) : simple_type<Int>(v) {}
		ST_TextNonNegativePoint(const String& v) { read(v); }
	};

	class ST_TextCapsType
	{
		static String _literals[];
		String _value;
	public:
		enum value { all, none, small };

		static const String all_literal;
		static const String none_literal;
		static const String small_literal;

		ST_TextCapsType() : _value(none_literal) {}
		ST_TextCapsType(value val) : _value(convert(val)) {}
		ST_TextCapsType(const String& str) : _value(str) {}

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

	class ST_TextPoint : public simple_type<Int>
	{
	public:
		ST_TextPoint() {}
		ST_TextPoint(const Int& v) : simple_type<Int>(v) {}
		ST_TextPoint(const String& v) { read(v); }
	};

	class CT_TextCharacterProperties
	{
	public:
		CT_TextCharacterProperties() : dirty(true), err(false), smtClean(true), smtId(0U) {}
		poptional< CT_LineProperties > ln;
		poptional< CT_NoFillProperties > noFill;
		poptional< CT_SolidColorFillProperties > solidFill;
		poptional< CT_GradientFillProperties > gradFill;
		poptional< CT_BlipFillProperties > blipFill;
		poptional< CT_PatternFillProperties > pattFill;
		poptional< CT_GroupFillProperties > grpFill;
		poptional< CT_EffectList > effectLst;
		poptional< CT_EffectContainer > effectDag;
		poptional< CT_Color > highlight;
		poptional< CT_TextUnderlineLineFollowText > uLnTx;
		poptional< CT_LineProperties > uLn;
		poptional< CT_TextUnderlineFillFollowText > uFillTx;
		poptional< CT_TextUnderlineFillGroupWrapper > uFill;
		poptional< CT_TextFont > latin;
		poptional< CT_TextFont > ea;
		poptional< CT_TextFont > cs;
		poptional< CT_TextFont > sym;
		poptional< CT_Hyperlink > hlinkClick;
		poptional< CT_Hyperlink > hlinkMouseOver;
		poptional< CT_OfficeArtExtensionList > extLst;
		optional< Boolean > kumimoji;
		poptional< ST_TextLanguageID > lang;
		poptional< ST_TextLanguageID > altLang;
		poptional< ST_TextFontSize > sz;
		optional< Boolean > b;
		optional< Boolean > i;
		optional< ST_TextUnderlineType > u;
		optional< ST_TextStrikeType > strike;
		poptional< ST_TextNonNegativePoint > kern;
		optional< ST_TextCapsType > cap;
		poptional< ST_TextPoint > spc;
		optional< Boolean > normalizeH;
		poptional< ST_Percentage > baseline;
		optional< Boolean > noProof;
		Boolean dirty;
		Boolean err;
		Boolean smtClean;
		UnsignedInt smtId;
		optional< String > bmk;
	};

}
#endif

