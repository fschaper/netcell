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


#include "sml-autoFilter.hpp"
namespace spreadsheetml
{
	const String ST_DateTimeGrouping::day_literal = "day";
	const String ST_DateTimeGrouping::hour_literal = "hour";
	const String ST_DateTimeGrouping::minute_literal = "minute";
	const String ST_DateTimeGrouping::month_literal = "month";
	const String ST_DateTimeGrouping::second_literal = "second";
	const String ST_DateTimeGrouping::year_literal = "year";
	String ST_DateTimeGrouping::_literals[] = { ST_DateTimeGrouping::day_literal, ST_DateTimeGrouping::hour_literal, ST_DateTimeGrouping::minute_literal, ST_DateTimeGrouping::month_literal, ST_DateTimeGrouping::second_literal, ST_DateTimeGrouping::year_literal };

	const String ST_CalendarType::gregorian_literal = "gregorian";
	const String ST_CalendarType::gregorianArabic_literal = "gregorianArabic";
	const String ST_CalendarType::gregorianMeFrench_literal = "gregorianMeFrench";
	const String ST_CalendarType::gregorianUs_literal = "gregorianUs";
	const String ST_CalendarType::gregorianXlitEnglish_literal = "gregorianXlitEnglish";
	const String ST_CalendarType::gregorianXlitFrench_literal = "gregorianXlitFrench";
	const String ST_CalendarType::hebrew_literal = "hebrew";
	const String ST_CalendarType::hijri_literal = "hijri";
	const String ST_CalendarType::japan_literal = "japan";
	const String ST_CalendarType::korea_literal = "korea";
	const String ST_CalendarType::none_literal = "none";
	const String ST_CalendarType::taiwan_literal = "taiwan";
	const String ST_CalendarType::thai_literal = "thai";
	String ST_CalendarType::_literals[] = { ST_CalendarType::gregorian_literal, ST_CalendarType::gregorianArabic_literal, ST_CalendarType::gregorianMeFrench_literal, ST_CalendarType::gregorianUs_literal, ST_CalendarType::gregorianXlitEnglish_literal, ST_CalendarType::gregorianXlitFrench_literal, ST_CalendarType::hebrew_literal, ST_CalendarType::hijri_literal, ST_CalendarType::japan_literal, ST_CalendarType::korea_literal, ST_CalendarType::none_literal, ST_CalendarType::taiwan_literal, ST_CalendarType::thai_literal };

	const String ST_FilterOperator::equal_literal = "equal";
	const String ST_FilterOperator::greaterThan_literal = "greaterThan";
	const String ST_FilterOperator::greaterThanOrEqual_literal = "greaterThanOrEqual";
	const String ST_FilterOperator::lessThan_literal = "lessThan";
	const String ST_FilterOperator::lessThanOrEqual_literal = "lessThanOrEqual";
	const String ST_FilterOperator::notEqual_literal = "notEqual";
	String ST_FilterOperator::_literals[] = { ST_FilterOperator::equal_literal, ST_FilterOperator::greaterThan_literal, ST_FilterOperator::greaterThanOrEqual_literal, ST_FilterOperator::lessThan_literal, ST_FilterOperator::lessThanOrEqual_literal, ST_FilterOperator::notEqual_literal };

	const String ST_DynamicFilterType::aboveAverage_literal = "aboveAverage";
	const String ST_DynamicFilterType::belowAverage_literal = "belowAverage";
	const String ST_DynamicFilterType::lastMonth_literal = "lastMonth";
	const String ST_DynamicFilterType::lastQuarter_literal = "lastQuarter";
	const String ST_DynamicFilterType::lastWeek_literal = "lastWeek";
	const String ST_DynamicFilterType::lastYear_literal = "lastYear";
	const String ST_DynamicFilterType::M1_literal = "M1";
	const String ST_DynamicFilterType::M10_literal = "M10";
	const String ST_DynamicFilterType::M11_literal = "M11";
	const String ST_DynamicFilterType::M12_literal = "M12";
	const String ST_DynamicFilterType::M2_literal = "M2";
	const String ST_DynamicFilterType::M3_literal = "M3";
	const String ST_DynamicFilterType::M4_literal = "M4";
	const String ST_DynamicFilterType::M5_literal = "M5";
	const String ST_DynamicFilterType::M6_literal = "M6";
	const String ST_DynamicFilterType::M7_literal = "M7";
	const String ST_DynamicFilterType::M8_literal = "M8";
	const String ST_DynamicFilterType::M9_literal = "M9";
	const String ST_DynamicFilterType::nextMonth_literal = "nextMonth";
	const String ST_DynamicFilterType::nextQuarter_literal = "nextQuarter";
	const String ST_DynamicFilterType::nextWeek_literal = "nextWeek";
	const String ST_DynamicFilterType::nextYear_literal = "nextYear";
	const String ST_DynamicFilterType::null_literal = "null";
	const String ST_DynamicFilterType::Q1_literal = "Q1";
	const String ST_DynamicFilterType::Q2_literal = "Q2";
	const String ST_DynamicFilterType::Q3_literal = "Q3";
	const String ST_DynamicFilterType::Q4_literal = "Q4";
	const String ST_DynamicFilterType::thisMonth_literal = "thisMonth";
	const String ST_DynamicFilterType::thisQuarter_literal = "thisQuarter";
	const String ST_DynamicFilterType::thisWeek_literal = "thisWeek";
	const String ST_DynamicFilterType::thisYear_literal = "thisYear";
	const String ST_DynamicFilterType::today_literal = "today";
	const String ST_DynamicFilterType::tomorrow_literal = "tomorrow";
	const String ST_DynamicFilterType::yearToDate_literal = "yearToDate";
	const String ST_DynamicFilterType::yesterday_literal = "yesterday";
	String ST_DynamicFilterType::_literals[] = { ST_DynamicFilterType::aboveAverage_literal, ST_DynamicFilterType::belowAverage_literal, ST_DynamicFilterType::lastMonth_literal, ST_DynamicFilterType::lastQuarter_literal, ST_DynamicFilterType::lastWeek_literal, ST_DynamicFilterType::lastYear_literal, ST_DynamicFilterType::M1_literal, ST_DynamicFilterType::M10_literal, ST_DynamicFilterType::M11_literal, ST_DynamicFilterType::M12_literal, ST_DynamicFilterType::M2_literal, ST_DynamicFilterType::M3_literal, ST_DynamicFilterType::M4_literal, ST_DynamicFilterType::M5_literal, ST_DynamicFilterType::M6_literal, ST_DynamicFilterType::M7_literal, ST_DynamicFilterType::M8_literal, ST_DynamicFilterType::M9_literal, ST_DynamicFilterType::nextMonth_literal, ST_DynamicFilterType::nextQuarter_literal, ST_DynamicFilterType::nextWeek_literal, ST_DynamicFilterType::nextYear_literal, ST_DynamicFilterType::null_literal, ST_DynamicFilterType::Q1_literal, ST_DynamicFilterType::Q2_literal, ST_DynamicFilterType::Q3_literal, ST_DynamicFilterType::Q4_literal, ST_DynamicFilterType::thisMonth_literal, ST_DynamicFilterType::thisQuarter_literal, ST_DynamicFilterType::thisWeek_literal, ST_DynamicFilterType::thisYear_literal, ST_DynamicFilterType::today_literal, ST_DynamicFilterType::tomorrow_literal, ST_DynamicFilterType::yearToDate_literal, ST_DynamicFilterType::yesterday_literal };

	const String ST_IconSetType::_3Arrows__literal = "3Arrows";
	const String ST_IconSetType::_3ArrowsGray__literal = "3ArrowsGray";
	const String ST_IconSetType::_3Flags__literal = "3Flags";
	const String ST_IconSetType::_3Signs__literal = "3Signs";
	const String ST_IconSetType::_3Symbols__literal = "3Symbols";
	const String ST_IconSetType::_3Symbols2__literal = "3Symbols2";
	const String ST_IconSetType::_3TrafficLights1__literal = "3TrafficLights1";
	const String ST_IconSetType::_3TrafficLights2__literal = "3TrafficLights2";
	const String ST_IconSetType::_4Arrows__literal = "4Arrows";
	const String ST_IconSetType::_4ArrowsGray__literal = "4ArrowsGray";
	const String ST_IconSetType::_4Rating__literal = "4Rating";
	const String ST_IconSetType::_4RedToBlack__literal = "4RedToBlack";
	const String ST_IconSetType::_4TrafficLights__literal = "4TrafficLights";
	const String ST_IconSetType::_5Arrows__literal = "5Arrows";
	const String ST_IconSetType::_5ArrowsGray__literal = "5ArrowsGray";
	const String ST_IconSetType::_5Quarters__literal = "5Quarters";
	const String ST_IconSetType::_5Rating__literal = "5Rating";
	String ST_IconSetType::_literals[] = { ST_IconSetType::_3Arrows__literal, ST_IconSetType::_3ArrowsGray__literal, ST_IconSetType::_3Flags__literal, ST_IconSetType::_3Signs__literal, ST_IconSetType::_3Symbols__literal, ST_IconSetType::_3Symbols2__literal, ST_IconSetType::_3TrafficLights1__literal, ST_IconSetType::_3TrafficLights2__literal, ST_IconSetType::_4Arrows__literal, ST_IconSetType::_4ArrowsGray__literal, ST_IconSetType::_4Rating__literal, ST_IconSetType::_4RedToBlack__literal, ST_IconSetType::_4TrafficLights__literal, ST_IconSetType::_5Arrows__literal, ST_IconSetType::_5ArrowsGray__literal, ST_IconSetType::_5Quarters__literal, ST_IconSetType::_5Rating__literal };

	const String ST_SortBy::cellColor_literal = "cellColor";
	const String ST_SortBy::fontColor_literal = "fontColor";
	const String ST_SortBy::icon_literal = "icon";
	const String ST_SortBy::value_literal = "value";
	String ST_SortBy::_literals[] = { ST_SortBy::cellColor_literal, ST_SortBy::fontColor_literal, ST_SortBy::icon_literal, ST_SortBy::value_literal };

	const String ST_SortMethod::none_literal = "none";
	const String ST_SortMethod::pinYin_literal = "pinYin";
	const String ST_SortMethod::stroke_literal = "stroke";
	String ST_SortMethod::_literals[] = { ST_SortMethod::none_literal, ST_SortMethod::pinYin_literal, ST_SortMethod::stroke_literal };

}
