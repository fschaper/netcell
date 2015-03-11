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

#ifndef SML_TABLE_HPP
#define SML_TABLE_HPP


#include "sml-autoFilter.hpp"
#include "sml-baseTypes.hpp"
#include "sml-styles.hpp"

namespace spreadsheetml
{
	using namespace ::xio;
	using namespace ::xio::xml::schema;

	class CT_TableFormula;
	class CT_XmlColumnPr;
	class CT_TableColumn;
	class CT_TableColumns;
	class CT_TableStyleInfo;
	class CT_Table;
	class sml_table;

	class ST_XmlDataType
	{
		static String _literals[];
		String _value;
	public:
		enum value { anyType, anyURI, base64Binary, boolean, byte, date, dateTime, decimal, _double_, duration, ENTITIES, ENTITY, _float_, gDay, gMonth, gMonthDay, gYear, gYearMonth, hexBinary, ID, IDREF, IDREFS, _int_, integer, language, _long_, Name, NCName, negativeInteger, NMTOKEN, NMTOKENS, nonNegativeInteger, nonPositiveInteger, normalizedString, NOTATION, positiveInteger, QName, _short_, _string_, time, token, unsignedByte, unsignedInt, unsignedLong, unsignedShort };

		static const String anyType_literal;
		static const String anyURI_literal;
		static const String base64Binary_literal;
		static const String boolean_literal;
		static const String byte_literal;
		static const String date_literal;
		static const String dateTime_literal;
		static const String decimal_literal;
		static const String _double__literal;
		static const String duration_literal;
		static const String ENTITIES_literal;
		static const String ENTITY_literal;
		static const String _float__literal;
		static const String gDay_literal;
		static const String gMonth_literal;
		static const String gMonthDay_literal;
		static const String gYear_literal;
		static const String gYearMonth_literal;
		static const String hexBinary_literal;
		static const String ID_literal;
		static const String IDREF_literal;
		static const String IDREFS_literal;
		static const String _int__literal;
		static const String integer_literal;
		static const String language_literal;
		static const String _long__literal;
		static const String Name_literal;
		static const String NCName_literal;
		static const String negativeInteger_literal;
		static const String NMTOKEN_literal;
		static const String NMTOKENS_literal;
		static const String nonNegativeInteger_literal;
		static const String nonPositiveInteger_literal;
		static const String normalizedString_literal;
		static const String NOTATION_literal;
		static const String positiveInteger_literal;
		static const String QName_literal;
		static const String _short__literal;
		static const String _string__literal;
		static const String time_literal;
		static const String token_literal;
		static const String unsignedByte_literal;
		static const String unsignedInt_literal;
		static const String unsignedLong_literal;
		static const String unsignedShort_literal;

		ST_XmlDataType() : _value(_string__literal) {}
		ST_XmlDataType(value val) : _value(convert(val)) {}
		ST_XmlDataType(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 45, 0); }
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

	class CT_TableFormula : public ST_Formula
	{
	public:
		CT_TableFormula() : array(false) {}
		CT_TableFormula(const String& v) : ST_Formula(v), array(false) {}
		Boolean array;
	};

	class CT_XmlColumnPr
	{
	public:
		CT_XmlColumnPr() : denormalized(false) {}
		poptional< CT_ExtensionList > extLst;
		UnsignedInt mapId;
		ST_Xstring xpath;
		Boolean denormalized;
		ST_XmlDataType xmlDataType;
	};

	class ST_TotalsRowFunction
	{
		static String _literals[];
		String _value;
	public:
		enum value { average, count, countNums, custom, max, min, none, stdDev, sum, var };

		static const String average_literal;
		static const String count_literal;
		static const String countNums_literal;
		static const String custom_literal;
		static const String max_literal;
		static const String min_literal;
		static const String none_literal;
		static const String stdDev_literal;
		static const String sum_literal;
		static const String var_literal;

		ST_TotalsRowFunction() : _value(none_literal) {}
		ST_TotalsRowFunction(value val) : _value(convert(val)) {}
		ST_TotalsRowFunction(const String& str) : _value(str) {}

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

	class CT_TableColumn
	{
	public:
		CT_TableColumn() : totalsRowFunction(ST_TotalsRowFunction::none_literal) {}
		poptional< CT_TableFormula > calculatedColumnFormula;
		poptional< CT_TableFormula > totalsRowFormula;
		poptional< CT_XmlColumnPr > xmlColumnPr;
		poptional< CT_ExtensionList > extLst;
		UnsignedInt id;
		poptional< ST_Xstring > uniqueName;
		ST_Xstring name;
		ST_TotalsRowFunction totalsRowFunction;
		poptional< ST_Xstring > totalsRowLabel;
		optional< UnsignedInt > queryTableFieldId;
		poptional< ST_DxfId > headerRowDxfId;
		poptional< ST_DxfId > dataDxfId;
		poptional< ST_DxfId > totalsRowDxfId;
		poptional< ST_Xstring > headerRowCellStyle;
		poptional< ST_Xstring > dataCellStyle;
		poptional< ST_Xstring > totalsRowCellStyle;
	};

	class CT_TableColumns
	{
	public:
		std::vector< CT_TableColumn > tableColumn;
		optional< UnsignedInt > count;
	};

	class CT_TableStyleInfo
	{
	public:
		poptional< ST_Xstring > name;
		optional< Boolean > showFirstColumn;
		optional< Boolean > showLastColumn;
		optional< Boolean > showRowStripes;
		optional< Boolean > showColumnStripes;
	};

	class ST_TableType
	{
		static String _literals[];
		String _value;
	public:
		enum value { queryTable, worksheet, xml };

		static const String queryTable_literal;
		static const String worksheet_literal;
		static const String xml_literal;

		ST_TableType() : _value(worksheet_literal) {}
		ST_TableType(value val) : _value(convert(val)) {}
		ST_TableType(const String& str) : _value(str) {}

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

	class CT_Table
	{
	public:
		CT_Table() : tableType(ST_TableType::worksheet_literal), headerRowCount(1U), insertRow(false), insertRowShift(false), totalsRowCount(0U), totalsRowShown(true), published(false) {}
		poptional< CT_AutoFilter > autoFilter;
		poptional< CT_SortState > sortState;
		CT_TableColumns tableColumns;
		poptional< CT_TableStyleInfo > tableStyleInfo;
		poptional< CT_ExtensionList > extLst;
		UnsignedInt id;
		poptional< ST_Xstring > name;
		ST_Xstring displayName;
		poptional< ST_Xstring > comment;
		ST_Ref ref;
		ST_TableType tableType;
		UnsignedInt headerRowCount;
		Boolean insertRow;
		Boolean insertRowShift;
		UnsignedInt totalsRowCount;
		Boolean totalsRowShown;
		Boolean published;
		poptional< ST_DxfId > headerRowDxfId;
		poptional< ST_DxfId > dataDxfId;
		poptional< ST_DxfId > totalsRowDxfId;
		poptional< ST_DxfId > headerRowBorderDxfId;
		poptional< ST_DxfId > tableBorderDxfId;
		poptional< ST_DxfId > totalsRowBorderDxfId;
		poptional< ST_Xstring > headerRowCellStyle;
		poptional< ST_Xstring > dataCellStyle;
		poptional< ST_Xstring > totalsRowCellStyle;
		optional< UnsignedInt > connectionId;
	};

	class sml_table
	{
	public:
		poptional< CT_Table > table;
	};

}
#endif

