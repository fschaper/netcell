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

#ifndef SML_SHAREDSTRINGTABLE_HPP
#define SML_SHAREDSTRINGTABLE_HPP


#include "sml-baseTypes.hpp"
#include "sml-styles.hpp"

namespace spreadsheetml
{
	using namespace ::xio;
	using namespace ::xio::xml::schema;

	class CT_RPrElt;
	class CT_RElt;
	class CT_PhoneticRun;
	class CT_PhoneticPr;
	class CT_Rst;
	class CT_Sst;
	class sml_sharedStringTable;

	class CT_RPrElt
	{
	public:
		poptional< CT_FontName > rFont;
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

	class CT_RElt
	{
	public:
		poptional< CT_RPrElt > rPr;
		ST_Xstring t;
	};

	class CT_PhoneticRun
	{
	public:
		ST_Xstring t;
		UnsignedInt sb;
		UnsignedInt eb;
	};

	class ST_PhoneticType
	{
		static String _literals[];
		String _value;
	public:
		enum value { fullwidthKatakana, halfwidthKatakana, Hiragana, noConversion };

		static const String fullwidthKatakana_literal;
		static const String halfwidthKatakana_literal;
		static const String Hiragana_literal;
		static const String noConversion_literal;

		ST_PhoneticType() : _value(halfwidthKatakana_literal) {}
		ST_PhoneticType(value val) : _value(convert(val)) {}
		ST_PhoneticType(const String& str) : _value(str) {}

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

	class ST_PhoneticAlignment
	{
		static String _literals[];
		String _value;
	public:
		enum value { center, distributed, left, noControl };

		static const String center_literal;
		static const String distributed_literal;
		static const String left_literal;
		static const String noControl_literal;

		ST_PhoneticAlignment() : _value(noControl_literal) {}
		ST_PhoneticAlignment(value val) : _value(convert(val)) {}
		ST_PhoneticAlignment(const String& str) : _value(str) {}

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

	class CT_PhoneticPr
	{
	public:
		CT_PhoneticPr() : type(ST_PhoneticType::fullwidthKatakana_literal), alignment(ST_PhoneticAlignment::left_literal) {}
		ST_FontId fontId;
		ST_PhoneticType type;
		ST_PhoneticAlignment alignment;
	};

	class CT_Rst
	{
	public:
		poptional< ST_Xstring > t;
		std::vector< CT_RElt > r;
		std::vector< CT_PhoneticRun > rPh;
		poptional< CT_PhoneticPr > phoneticPr;
	};

	class CT_Sst
	{
	public:
		std::vector< CT_Rst > si;
		poptional< CT_ExtensionList > extLst;
		optional< UnsignedInt > count;
		optional< UnsignedInt > uniqueCount;
	};

	class sml_sharedStringTable
	{
	public:
		poptional< CT_Sst > sst;
	};

}
#endif

