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

#ifndef SML_EXTERNALCONNECTIONS_HPP
#define SML_EXTERNALCONNECTIONS_HPP


#include "sml-baseTypes.hpp"
#include "sml-pivotTableShared.hpp"

namespace spreadsheetml
{
	using namespace ::xio;
	using namespace ::xio::xml::schema;

	class CT_DbPr;
	class CT_OlapPr;
	class CT_TableMissing;
	class CT_Tables;
	class CT_WebPr;
	class CT_TextField;
	class CT_TextFields;
	class CT_TextPr;
	class CT_Parameter;
	class CT_Parameters;
	class CT_Connection;
	class CT_Connections;
	class sml_externalConnections;

	class CT_DbPr
	{
	public:
		CT_DbPr() : commandType(2U) {}
		ST_Xstring connection;
		poptional< ST_Xstring > command;
		poptional< ST_Xstring > serverCommand;
		UnsignedInt commandType;
	};

	class CT_OlapPr
	{
	public:
		CT_OlapPr() : local(false), localRefresh(true), sendLocale(false), serverFill(true), serverNumberFormat(true), serverFont(true), serverFontColor(true) {}
		Boolean local;
		poptional< ST_Xstring > localConnection;
		Boolean localRefresh;
		Boolean sendLocale;
		optional< UnsignedInt > rowDrillCount;
		Boolean serverFill;
		Boolean serverNumberFormat;
		Boolean serverFont;
		Boolean serverFontColor;
	};

	class CT_TableMissing
	{
	public:
	};

	class CT_Tables
	{
	public:
		poptional< CT_TableMissing > m;
		poptional< CT_XStringElement > s;
		poptional< CT_Index > x;
		optional< UnsignedInt > count;
	};

	class ST_HtmlFmt
	{
		static String _literals[];
		String _value;
	public:
		enum value { all, none, rtf };

		static const String all_literal;
		static const String none_literal;
		static const String rtf_literal;

		ST_HtmlFmt() : _value(none_literal) {}
		ST_HtmlFmt(value val) : _value(convert(val)) {}
		ST_HtmlFmt(const String& str) : _value(str) {}

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

	class CT_WebPr
	{
	public:
		CT_WebPr() : xml(false), sourceData(false), parsePre(false), consecutive(false), firstRow(false), xl97(false), textDates(false), xl2000(false), htmlTables(false), htmlFormat(ST_HtmlFmt::none_literal) {}
		poptional< CT_Tables > tables;
		Boolean xml;
		Boolean sourceData;
		Boolean parsePre;
		Boolean consecutive;
		Boolean firstRow;
		Boolean xl97;
		Boolean textDates;
		Boolean xl2000;
		poptional< ST_Xstring > url;
		poptional< ST_Xstring > post;
		Boolean htmlTables;
		ST_HtmlFmt htmlFormat;
		poptional< ST_Xstring > editPage;
	};

	class ST_ExternalConnectionType
	{
		static String _literals[];
		String _value;
	public:
		enum value { DMY, DYM, EMD, general, MDY, MYD, skip, text, YDM, YMD };

		static const String DMY_literal;
		static const String DYM_literal;
		static const String EMD_literal;
		static const String general_literal;
		static const String MDY_literal;
		static const String MYD_literal;
		static const String skip_literal;
		static const String text_literal;
		static const String YDM_literal;
		static const String YMD_literal;

		ST_ExternalConnectionType() : _value(general_literal) {}
		ST_ExternalConnectionType(value val) : _value(convert(val)) {}
		ST_ExternalConnectionType(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 10, 0); }
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

	class CT_TextField
	{
	public:
		CT_TextField() : type(ST_ExternalConnectionType::general_literal), position(0U) {}
		ST_ExternalConnectionType type;
		UnsignedInt position;
	};

	class CT_TextFields
	{
	public:
		CT_TextFields() : count(1U) {}
		std::vector< CT_TextField > textField;
		UnsignedInt count;
	};

	class ST_FileType
	{
		static String _literals[];
		String _value;
	public:
		enum value { dos, mac, win };

		static const String dos_literal;
		static const String mac_literal;
		static const String win_literal;

		ST_FileType() : _value(mac_literal) {}
		ST_FileType(value val) : _value(convert(val)) {}
		ST_FileType(const String& str) : _value(str) {}

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

	class ST_Qualifier
	{
		static String _literals[];
		String _value;
	public:
		enum value { doubleQuote, none, singleQuote };

		static const String doubleQuote_literal;
		static const String none_literal;
		static const String singleQuote_literal;

		ST_Qualifier() : _value(doubleQuote_literal) {}
		ST_Qualifier(value val) : _value(convert(val)) {}
		ST_Qualifier(const String& str) : _value(str) {}

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

	class CT_TextPr
	{
	public:
		CT_TextPr() : prompt(true), fileType(ST_FileType::win_literal), codePage(1252U), firstRow(1U), sourceFile(""), delimited(true), decimal("."), thousands(","), tab(true), space(false), comma(false), semicolon(false), consecutive(false), qualifier(ST_Qualifier::doubleQuote_literal) {}
		poptional< CT_TextFields > textFields;
		Boolean prompt;
		ST_FileType fileType;
		UnsignedInt codePage;
		UnsignedInt firstRow;
		ST_Xstring sourceFile;
		Boolean delimited;
		ST_Xstring decimal;
		ST_Xstring thousands;
		Boolean tab;
		Boolean space;
		Boolean comma;
		Boolean semicolon;
		Boolean consecutive;
		ST_Qualifier qualifier;
		poptional< ST_Xstring > delimiter;
	};

	class ST_ParameterType
	{
		static String _literals[];
		String _value;
	public:
		enum Value { cell, prompt, value };

		static const String cell_literal;
		static const String prompt_literal;
		static const String value_literal;

		ST_ParameterType() : _value(prompt_literal) {}
		ST_ParameterType(Value val) : _value(convert(val)) {}
		ST_ParameterType(const String& str) : _value(str) {}

		static Value convert(const String& str) { return (Value)::xio::util::binary_search(str, _literals, 3, 0); }
		static String convert(Value v) { return _literals[(int)v]; }

		bool operator == (const String& str) const { return str == _value; }
		bool operator == (Value val) const {return convert(val) == _value; }
		bool operator != (const String& str) const { return str != _value; }
		bool operator != (Value val) const {return convert(val) != _value; }

		const String& operator = (const String& str) { _value = str; return str; }
		const Value& operator = (const Value& val) { _value = convert(val); return val; }

		operator const String& () const { return _value; }
		operator String& () { return _value; }
		operator Value () const { return convert(_value); }
		String serialize() const { return _value; }
	};

	class CT_Parameter
	{
	public:
		CT_Parameter() : sqlType(0), parameterType(ST_ParameterType::prompt_literal), refreshOnChange(false) {}
		poptional< ST_Xstring > name;
		Int sqlType;
		ST_ParameterType parameterType;
		Boolean refreshOnChange;
		poptional< ST_Xstring > prompt;
		optional< Boolean > boolean;
		optional< Double > _double_;
		optional< Int > integer;
		poptional< ST_Xstring > _string_;
		poptional< ST_Xstring > cell;
	};

	class CT_Parameters
	{
	public:
		std::vector< CT_Parameter > parameter;
		optional< UnsignedInt > count;
	};

	class ST_CredMethod
	{
		static String _literals[];
		String _value;
	public:
		enum value { integrated, none, prompt, stored };

		static const String integrated_literal;
		static const String none_literal;
		static const String prompt_literal;
		static const String stored_literal;

		ST_CredMethod() : _value(integrated_literal) {}
		ST_CredMethod(value val) : _value(convert(val)) {}
		ST_CredMethod(const String& str) : _value(str) {}

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

	class CT_Connection
	{
	public:
		CT_Connection() : keepAlive(false), interval(0U), reconnectionMethod(1U), minRefreshableVersion(0), savePassword(false), _new_(false), deleted(false), onlyUseConnectionFile(false), background(false), refreshOnLoad(false), saveData(false), credentials(ST_CredMethod::integrated_literal) {}
		poptional< CT_DbPr > dbPr;
		poptional< CT_OlapPr > olapPr;
		poptional< CT_WebPr > webPr;
		poptional< CT_TextPr > textPr;
		poptional< CT_Parameters > parameters;
		poptional< CT_ExtensionList > extLst;
		UnsignedInt id;
		poptional< ST_Xstring > sourceFile;
		poptional< ST_Xstring > odcFile;
		Boolean keepAlive;
		UnsignedInt interval;
		poptional< ST_Xstring > name;
		poptional< ST_Xstring > description;
		optional< UnsignedInt > type;
		UnsignedInt reconnectionMethod;
		UnsignedByte refreshedVersion;
		UnsignedByte minRefreshableVersion;
		Boolean savePassword;
		Boolean _new_;
		Boolean deleted;
		Boolean onlyUseConnectionFile;
		Boolean background;
		Boolean refreshOnLoad;
		Boolean saveData;
		ST_CredMethod credentials;
		poptional< ST_Xstring > singleSignOnId;
	};

	class CT_Connections
	{
	public:
		std::vector< CT_Connection > connection;
	};

	class sml_externalConnections
	{
	public:
		poptional< CT_Connections > connections;
	};

}
#endif

