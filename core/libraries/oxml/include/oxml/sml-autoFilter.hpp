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

#ifndef SML_AUTOFILTER_HPP
#define SML_AUTOFILTER_HPP


#include "sml-baseTypes.hpp"
#include "sml-styles.hpp"

namespace spreadsheetml
{
	using namespace ::xio;
	using namespace ::xio::xml::schema;

	class CT_Filter;
	class CT_DateGroupItem;
	class CT_Filters;
	class CT_Top10;
	class CT_CustomFilter;
	class CT_CustomFilters;
	class CT_DynamicFilter;
	class CT_ColorFilter;
	class CT_IconFilter;
	class CT_FilterColumn;
	class CT_SortCondition;
	class CT_SortState;
	class CT_AutoFilter;

	class CT_Filter
	{
	public:
		poptional< ST_Xstring > val;
	};

	class ST_DateTimeGrouping
	{
		static String _literals[];
		String _value;
	public:
		enum value { day, hour, minute, month, second, year };

		static const String day_literal;
		static const String hour_literal;
		static const String minute_literal;
		static const String month_literal;
		static const String second_literal;
		static const String year_literal;

		ST_DateTimeGrouping() : _value(year_literal) {}
		ST_DateTimeGrouping(value val) : _value(convert(val)) {}
		ST_DateTimeGrouping(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 6, 0); }
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

	class CT_DateGroupItem
	{
	public:
		UnsignedShort year;
		optional< UnsignedShort > month;
		optional< UnsignedShort > day;
		optional< UnsignedShort > hour;
		optional< UnsignedShort > minute;
		optional< UnsignedShort > second;
		ST_DateTimeGrouping dateTimeGrouping;
	};

	class ST_CalendarType
	{
		static String _literals[];
		String _value;
	public:
		enum value { gregorian, gregorianArabic, gregorianMeFrench, gregorianUs, gregorianXlitEnglish, gregorianXlitFrench, hebrew, hijri, japan, korea, none, taiwan, thai };

		static const String gregorian_literal;
		static const String gregorianArabic_literal;
		static const String gregorianMeFrench_literal;
		static const String gregorianUs_literal;
		static const String gregorianXlitEnglish_literal;
		static const String gregorianXlitFrench_literal;
		static const String hebrew_literal;
		static const String hijri_literal;
		static const String japan_literal;
		static const String korea_literal;
		static const String none_literal;
		static const String taiwan_literal;
		static const String thai_literal;

		ST_CalendarType() : _value(none_literal) {}
		ST_CalendarType(value val) : _value(convert(val)) {}
		ST_CalendarType(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 13, 0); }
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

	class CT_Filters
	{
	public:
		CT_Filters() : blank(false), calendarType(ST_CalendarType::none_literal) {}
		std::vector< CT_Filter > filter;
		std::vector< CT_DateGroupItem > dateGroupItem;
		Boolean blank;
		ST_CalendarType calendarType;
	};

	class CT_Top10
	{
	public:
		CT_Top10() : top(true), percent(false) {}
		Boolean top;
		Boolean percent;
		Double val;
		optional< Double > filterVal;
	};

	class ST_FilterOperator
	{
		static String _literals[];
		String _value;
	public:
		enum value { equal, greaterThan, greaterThanOrEqual, lessThan, lessThanOrEqual, notEqual };

		static const String equal_literal;
		static const String greaterThan_literal;
		static const String greaterThanOrEqual_literal;
		static const String lessThan_literal;
		static const String lessThanOrEqual_literal;
		static const String notEqual_literal;

		ST_FilterOperator() : _value(equal_literal) {}
		ST_FilterOperator(value val) : _value(convert(val)) {}
		ST_FilterOperator(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 6, 0); }
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

	class CT_CustomFilter
	{
	public:
		CT_CustomFilter() : _operator_(ST_FilterOperator::equal_literal) {}
		ST_FilterOperator _operator_;
		poptional< ST_Xstring > val;
	};

	class CT_CustomFilters
	{
	public:
		CT_CustomFilters() : _and_(false) {}
		std::vector< CT_CustomFilter > customFilter;
		Boolean _and_;
	};

	class ST_DynamicFilterType
	{
		static String _literals[];
		String _value;
	public:
		enum value { aboveAverage, belowAverage, lastMonth, lastQuarter, lastWeek, lastYear, M1, M10, M11, M12, M2, M3, M4, M5, M6, M7, M8, M9, nextMonth, nextQuarter, nextWeek, nextYear, null, Q1, Q2, Q3, Q4, thisMonth, thisQuarter, thisWeek, thisYear, today, tomorrow, yearToDate, yesterday };

		static const String aboveAverage_literal;
		static const String belowAverage_literal;
		static const String lastMonth_literal;
		static const String lastQuarter_literal;
		static const String lastWeek_literal;
		static const String lastYear_literal;
		static const String M1_literal;
		static const String M10_literal;
		static const String M11_literal;
		static const String M12_literal;
		static const String M2_literal;
		static const String M3_literal;
		static const String M4_literal;
		static const String M5_literal;
		static const String M6_literal;
		static const String M7_literal;
		static const String M8_literal;
		static const String M9_literal;
		static const String nextMonth_literal;
		static const String nextQuarter_literal;
		static const String nextWeek_literal;
		static const String nextYear_literal;
		static const String null_literal;
		static const String Q1_literal;
		static const String Q2_literal;
		static const String Q3_literal;
		static const String Q4_literal;
		static const String thisMonth_literal;
		static const String thisQuarter_literal;
		static const String thisWeek_literal;
		static const String thisYear_literal;
		static const String today_literal;
		static const String tomorrow_literal;
		static const String yearToDate_literal;
		static const String yesterday_literal;

		ST_DynamicFilterType() : _value(null_literal) {}
		ST_DynamicFilterType(value val) : _value(convert(val)) {}
		ST_DynamicFilterType(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 35, 0); }
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

	class CT_DynamicFilter
	{
	public:
		ST_DynamicFilterType type;
		optional< Double > val;
		optional< Double > maxVal;
	};

	class CT_ColorFilter
	{
	public:
		CT_ColorFilter() : cellColor(true) {}
		poptional< ST_DxfId > dxfId;
		Boolean cellColor;
	};

	class ST_IconSetType
	{
		static String _literals[];
		String _value;
	public:
		enum value { _3Arrows_, _3ArrowsGray_, _3Flags_, _3Signs_, _3Symbols_, _3Symbols2_, _3TrafficLights1_, _3TrafficLights2_, _4Arrows_, _4ArrowsGray_, _4Rating_, _4RedToBlack_, _4TrafficLights_, _5Arrows_, _5ArrowsGray_, _5Quarters_, _5Rating_ };

		static const String _3Arrows__literal;
		static const String _3ArrowsGray__literal;
		static const String _3Flags__literal;
		static const String _3Signs__literal;
		static const String _3Symbols__literal;
		static const String _3Symbols2__literal;
		static const String _3TrafficLights1__literal;
		static const String _3TrafficLights2__literal;
		static const String _4Arrows__literal;
		static const String _4ArrowsGray__literal;
		static const String _4Rating__literal;
		static const String _4RedToBlack__literal;
		static const String _4TrafficLights__literal;
		static const String _5Arrows__literal;
		static const String _5ArrowsGray__literal;
		static const String _5Quarters__literal;
		static const String _5Rating__literal;

		ST_IconSetType() : _value(_3Arrows__literal) {}
		ST_IconSetType(value val) : _value(convert(val)) {}
		ST_IconSetType(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 17, 0); }
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

	class CT_IconFilter
	{
	public:
		ST_IconSetType iconSet;
		optional< UnsignedInt > iconId;
	};

	class CT_FilterColumn
	{
	public:
		CT_FilterColumn() : hiddenButton(false), showButton(true) {}
		poptional< CT_Filters > filters;
		poptional< CT_Top10 > top10;
		poptional< CT_CustomFilters > customFilters;
		poptional< CT_DynamicFilter > dynamicFilter;
		poptional< CT_ColorFilter > colorFilter;
		poptional< CT_IconFilter > iconFilter;
		poptional< CT_ExtensionList > extLst;
		UnsignedInt colId;
		Boolean hiddenButton;
		Boolean showButton;
	};

	class ST_SortBy
	{
		static String _literals[];
		String _value;
	public:
		enum Value { cellColor, fontColor, icon, value };

		static const String cellColor_literal;
		static const String fontColor_literal;
		static const String icon_literal;
		static const String value_literal;

		ST_SortBy() : _value(value_literal) {}
		ST_SortBy(Value val) : _value(convert(val)) {}
		ST_SortBy(const String& str) : _value(str) {}

		static Value convert(const String& str) { return (Value)::xio::util::binary_search(str, _literals, 4, 0); }
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

	class CT_SortCondition
	{
	public:
		CT_SortCondition() : descending(false), sortBy(ST_SortBy::value_literal), iconSet(ST_IconSetType::_3Arrows__literal) {}
		Boolean descending;
		ST_SortBy sortBy;
		ST_Ref ref;
		poptional< ST_Xstring > customList;
		poptional< ST_DxfId > dxfId;
		ST_IconSetType iconSet;
		optional< UnsignedInt > iconId;
	};

	class ST_SortMethod
	{
		static String _literals[];
		String _value;
	public:
		enum value { none, pinYin, stroke };

		static const String none_literal;
		static const String pinYin_literal;
		static const String stroke_literal;

		ST_SortMethod() : _value(stroke_literal) {}
		ST_SortMethod(value val) : _value(convert(val)) {}
		ST_SortMethod(const String& str) : _value(str) {}

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

	class CT_SortState
	{
	public:
		CT_SortState() : columnSort(false), caseSensitive(false), sortMethod(ST_SortMethod::none_literal) {}
		std::vector< CT_SortCondition > sortCondition;
		poptional< CT_ExtensionList > extLst;
		Boolean columnSort;
		Boolean caseSensitive;
		ST_SortMethod sortMethod;
		ST_Ref ref;
	};

	class CT_AutoFilter
	{
	public:
		std::vector< CT_FilterColumn > filterColumn;
		poptional< CT_SortState > sortState;
		poptional< CT_ExtensionList > extLst;
		poptional< ST_Ref > ref;
	};

}
#endif

