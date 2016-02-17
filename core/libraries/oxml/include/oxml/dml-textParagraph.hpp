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

#ifndef DML_TEXTPARAGRAPH_HPP
#define DML_TEXTPARAGRAPH_HPP


#include "dml-baseTypes.hpp"
#include "dml-textBullet.hpp"
#include "dml-textCharacter.hpp"

namespace drawingml
{
	using namespace ::xio;
	using namespace ::xio::xml::schema;

	class ST_TextSpacingPercent;
	class CT_TextSpacingPercent;
	class ST_TextSpacingPoint;
	class CT_TextSpacingPoint;
	class CT_TextSpacing;
	class CT_TextTabStop;
	class CT_TextTabStopList;
	class ST_TextMargin;
	class ST_TextIndentLevelType;
	class ST_TextIndent;
	class CT_TextParagraphProperties;
	class CT_TextLineBreak;
	class CT_TextField;

	class ST_TextSpacingPercent : public ST_Percentage
	{
	public:
		ST_TextSpacingPercent() {}
		ST_TextSpacingPercent(const Int& v) : ST_Percentage(v) {}
		ST_TextSpacingPercent(const String& v) { read(v); }
	};

	class CT_TextSpacingPercent
	{
	public:
		ST_TextSpacingPercent val;
	};

	class ST_TextSpacingPoint : public simple_type<Int>
	{
	public:
		ST_TextSpacingPoint() {}
		ST_TextSpacingPoint(const Int& v) : simple_type<Int>(v) {}
		ST_TextSpacingPoint(const String& v) { read(v); }
	};

	class CT_TextSpacingPoint
	{
	public:
		ST_TextSpacingPoint val;
	};

	class CT_TextSpacing
	{
	public:
		poptional< CT_TextSpacingPercent > spcPct;
		poptional< CT_TextSpacingPoint > spcPts;
	};

	class ST_TextTabAlignType
	{
		static String _literals[];
		String _value;
	public:
		enum value { ctr, dec, l, r };

		static const String ctr_literal;
		static const String dec_literal;
		static const String l_literal;
		static const String r_literal;

		ST_TextTabAlignType() : _value(l_literal) {}
		ST_TextTabAlignType(value val) : _value(convert(val)) {}
		ST_TextTabAlignType(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 4, 0); }
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

	class CT_TextTabStop
	{
	public:
		poptional< ST_Coordinate32 > pos;
		optional< ST_TextTabAlignType > algn;
	};

	class CT_TextTabStopList
	{
	public:
		std::vector< CT_TextTabStop > tab;
	};

	class ST_TextMargin : public ST_Coordinate32
	{
	public:
		ST_TextMargin() {}
		ST_TextMargin(const Int& v) : ST_Coordinate32(v) {}
		ST_TextMargin(const String& v) { read(v); }
	};

	class ST_TextIndentLevelType : public simple_type<Int>
	{
	public:
		ST_TextIndentLevelType() {}
		ST_TextIndentLevelType(const Int& v) : simple_type<Int>(v) {}
		ST_TextIndentLevelType(const String& v) { read(v); }
	};

	class ST_TextIndent : public ST_Coordinate32
	{
	public:
		ST_TextIndent() {}
		ST_TextIndent(const Int& v) : ST_Coordinate32(v) {}
		ST_TextIndent(const String& v) { read(v); }
	};

	class ST_TextAlignType
	{
		static String _literals[];
		String _value;
	public:
		enum value { ctr, dist, just, justLow, l, r, thaiDist };

		static const String ctr_literal;
		static const String dist_literal;
		static const String just_literal;
		static const String justLow_literal;
		static const String l_literal;
		static const String r_literal;
		static const String thaiDist_literal;

		ST_TextAlignType() : _value(l_literal) {}
		ST_TextAlignType(value val) : _value(convert(val)) {}
		ST_TextAlignType(const String& str) : _value(str) {}

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

	class ST_TextFontAlignType
	{
		static String _literals[];
		String _value;
	public:
		enum value { _auto_, b, base, ctr, t };

		static const String _auto__literal;
		static const String b_literal;
		static const String base_literal;
		static const String ctr_literal;
		static const String t_literal;

		ST_TextFontAlignType() : _value(_auto__literal) {}
		ST_TextFontAlignType(value val) : _value(convert(val)) {}
		ST_TextFontAlignType(const String& str) : _value(str) {}

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

	class CT_TextParagraphProperties
	{
	public:
		poptional< CT_TextSpacing > lnSpc;
		poptional< CT_TextSpacing > spcBef;
		poptional< CT_TextSpacing > spcAft;
		poptional< CT_TextBulletColorFollowText > buClrTx;
		poptional< CT_Color > buClr;
		poptional< CT_TextBulletSizeFollowText > buSzTx;
		poptional< CT_TextBulletSizePercent > buSzPct;
		poptional< CT_TextBulletSizePoint > buSzPts;
		poptional< CT_TextBulletTypefaceFollowText > buFontTx;
		poptional< CT_TextFont > buFont;
		poptional< CT_TextNoBullet > buNone;
		poptional< CT_TextAutonumberBullet > buAutoNum;
		poptional< CT_TextCharBullet > buChar;
		poptional< CT_TextBlipBullet > buBlip;
		poptional< CT_TextTabStopList > tabLst;
		poptional< CT_TextCharacterProperties > defRPr;
		poptional< CT_OfficeArtExtensionList > extLst;
		poptional< ST_TextMargin > marL;
		poptional< ST_TextMargin > marR;
		poptional< ST_TextIndentLevelType > lvl;
		poptional< ST_TextIndent > indent;
		optional< ST_TextAlignType > algn;
		poptional< ST_Coordinate32 > defTabSz;
		optional< Boolean > rtl;
		optional< Boolean > eaLnBrk;
		optional< ST_TextFontAlignType > fontAlgn;
		optional< Boolean > latinLnBrk;
		optional< Boolean > hangingPunct;
	};

	class CT_TextLineBreak
	{
	public:
		poptional< CT_TextCharacterProperties > rPr;
	};

	class CT_TextField
	{
	public:
		poptional< CT_TextCharacterProperties > rPr;
		poptional< CT_TextParagraphProperties > pPr;
		optional< String > t;
		ST_Guid id;
		optional< String > type;
	};

}
#endif

