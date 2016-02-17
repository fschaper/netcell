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

#ifndef DML_TEXTBULLET_HPP
#define DML_TEXTBULLET_HPP


#include "dml-baseTypes.hpp"
#include "dml-textCharacter.hpp"
#include "dml-shapeEffects.hpp"

namespace drawingml
{
	using namespace ::xio;
	using namespace ::xio::xml::schema;

	class CT_TextBulletColorFollowText;
	class CT_TextBulletSizeFollowText;
	class ST_TextBulletSizePercent;
	class CT_TextBulletSizePercent;
	class CT_TextBulletSizePoint;
	class CT_TextBulletTypefaceFollowText;
	class CT_TextNoBullet;
	class ST_TextBulletStartAtNum;
	class CT_TextAutonumberBullet;
	class CT_TextCharBullet;
	class CT_TextBlipBullet;

	class CT_TextBulletColorFollowText
	{
	public:
	};

	class CT_TextBulletSizeFollowText
	{
	public:
	};

	class ST_TextBulletSizePercent : public ST_Percentage
	{
	public:
		ST_TextBulletSizePercent() {}
		ST_TextBulletSizePercent(const Int& v) : ST_Percentage(v) {}
		ST_TextBulletSizePercent(const String& v) { read(v); }
	};

	class CT_TextBulletSizePercent
	{
	public:
		poptional< ST_TextBulletSizePercent > val;
	};

	class CT_TextBulletSizePoint
	{
	public:
		poptional< ST_TextFontSize > val;
	};

	class CT_TextBulletTypefaceFollowText
	{
	public:
	};

	class CT_TextNoBullet
	{
	public:
	};

	class ST_TextAutonumberScheme
	{
		static String _literals[];
		String _value;
	public:
		enum value { alphaLcParenBoth, alphaLcParenR, alphaLcPeriod, alphaUcParenBoth, alphaUcParenR, alphaUcPeriod, arabic1Minus, arabic2Minus, arabicDbPeriod, arabicDbPlain, arabicParenBoth, arabicParenR, arabicPeriod, arabicPlain, circleNumDbPlain, circleNumWdBlackPlain, circleNumWdWhitePlain, ea1ChsPeriod, ea1ChsPlain, ea1ChtPeriod, ea1ChtPlain, ea1JpnChsDbPeriod, ea1JpnKorPeriod, ea1JpnKorPlain, hebrew2Minus, hindiAlpha1Period, hindiAlphaPeriod, hindiNumParenR, hindiNumPeriod, romanLcParenBoth, romanLcParenR, romanLcPeriod, romanUcParenBoth, romanUcParenR, romanUcPeriod, thaiAlphaParenBoth, thaiAlphaParenR, thaiAlphaPeriod, thaiNumParenBoth, thaiNumParenR, thaiNumPeriod };

		static const String alphaLcParenBoth_literal;
		static const String alphaLcParenR_literal;
		static const String alphaLcPeriod_literal;
		static const String alphaUcParenBoth_literal;
		static const String alphaUcParenR_literal;
		static const String alphaUcPeriod_literal;
		static const String arabic1Minus_literal;
		static const String arabic2Minus_literal;
		static const String arabicDbPeriod_literal;
		static const String arabicDbPlain_literal;
		static const String arabicParenBoth_literal;
		static const String arabicParenR_literal;
		static const String arabicPeriod_literal;
		static const String arabicPlain_literal;
		static const String circleNumDbPlain_literal;
		static const String circleNumWdBlackPlain_literal;
		static const String circleNumWdWhitePlain_literal;
		static const String ea1ChsPeriod_literal;
		static const String ea1ChsPlain_literal;
		static const String ea1ChtPeriod_literal;
		static const String ea1ChtPlain_literal;
		static const String ea1JpnChsDbPeriod_literal;
		static const String ea1JpnKorPeriod_literal;
		static const String ea1JpnKorPlain_literal;
		static const String hebrew2Minus_literal;
		static const String hindiAlpha1Period_literal;
		static const String hindiAlphaPeriod_literal;
		static const String hindiNumParenR_literal;
		static const String hindiNumPeriod_literal;
		static const String romanLcParenBoth_literal;
		static const String romanLcParenR_literal;
		static const String romanLcPeriod_literal;
		static const String romanUcParenBoth_literal;
		static const String romanUcParenR_literal;
		static const String romanUcPeriod_literal;
		static const String thaiAlphaParenBoth_literal;
		static const String thaiAlphaParenR_literal;
		static const String thaiAlphaPeriod_literal;
		static const String thaiNumParenBoth_literal;
		static const String thaiNumParenR_literal;
		static const String thaiNumPeriod_literal;

		ST_TextAutonumberScheme() : _value(alphaLcParenBoth_literal) {}
		ST_TextAutonumberScheme(value val) : _value(convert(val)) {}
		ST_TextAutonumberScheme(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 41, 0); }
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

	class ST_TextBulletStartAtNum : public simple_type<Int>
	{
	public:
		ST_TextBulletStartAtNum() {}
		ST_TextBulletStartAtNum(const Int& v) : simple_type<Int>(v) {}
		ST_TextBulletStartAtNum(const String& v) { read(v); }
	};

	class CT_TextAutonumberBullet
	{
	public:
		CT_TextAutonumberBullet() : startAt(1) {}
		ST_TextAutonumberScheme type;
		ST_TextBulletStartAtNum startAt;
	};

	class CT_TextCharBullet
	{
	public:
		String _char_;
	};

	class CT_TextBlipBullet
	{
	public:
		CT_Blip blip;
	};

}
#endif

