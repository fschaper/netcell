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


#include "sml-pivotTable.hpp"
namespace spreadsheetml
{
	const String ST_SourceType::consolidation_literal = "consolidation";
	const String ST_SourceType::external_literal = "external";
	const String ST_SourceType::scenario_literal = "scenario";
	const String ST_SourceType::worksheet_literal = "worksheet";
	String ST_SourceType::_literals[] = { ST_SourceType::consolidation_literal, ST_SourceType::external_literal, ST_SourceType::scenario_literal, ST_SourceType::worksheet_literal };

	const String ST_GroupBy::days_literal = "days";
	const String ST_GroupBy::hours_literal = "hours";
	const String ST_GroupBy::minutes_literal = "minutes";
	const String ST_GroupBy::months_literal = "months";
	const String ST_GroupBy::quarters_literal = "quarters";
	const String ST_GroupBy::range_literal = "range";
	const String ST_GroupBy::seconds_literal = "seconds";
	const String ST_GroupBy::years_literal = "years";
	String ST_GroupBy::_literals[] = { ST_GroupBy::days_literal, ST_GroupBy::hours_literal, ST_GroupBy::minutes_literal, ST_GroupBy::months_literal, ST_GroupBy::quarters_literal, ST_GroupBy::range_literal, ST_GroupBy::seconds_literal, ST_GroupBy::years_literal };

	const String ST_SortType::ascending_literal = "ascending";
	const String ST_SortType::ascendingAlpha_literal = "ascendingAlpha";
	const String ST_SortType::ascendingNatural_literal = "ascendingNatural";
	const String ST_SortType::descending_literal = "descending";
	const String ST_SortType::descendingAlpha_literal = "descendingAlpha";
	const String ST_SortType::descendingNatural_literal = "descendingNatural";
	const String ST_SortType::none_literal = "none";
	String ST_SortType::_literals[] = { ST_SortType::ascending_literal, ST_SortType::ascendingAlpha_literal, ST_SortType::ascendingNatural_literal, ST_SortType::descending_literal, ST_SortType::descendingAlpha_literal, ST_SortType::descendingNatural_literal, ST_SortType::none_literal };

	const String ST_ItemType::avg_literal = "avg";
	const String ST_ItemType::blank_literal = "blank";
	const String ST_ItemType::count_literal = "count";
	const String ST_ItemType::countA_literal = "countA";
	const String ST_ItemType::data_literal = "data";
	const String ST_ItemType::_default__literal = "default";
	const String ST_ItemType::grand_literal = "grand";
	const String ST_ItemType::max_literal = "max";
	const String ST_ItemType::min_literal = "min";
	const String ST_ItemType::product_literal = "product";
	const String ST_ItemType::stdDev_literal = "stdDev";
	const String ST_ItemType::stdDevP_literal = "stdDevP";
	const String ST_ItemType::sum_literal = "sum";
	const String ST_ItemType::var_literal = "var";
	const String ST_ItemType::varP_literal = "varP";
	String ST_ItemType::_literals[] = { ST_ItemType::avg_literal, ST_ItemType::blank_literal, ST_ItemType::count_literal, ST_ItemType::countA_literal, ST_ItemType::data_literal, ST_ItemType::_default__literal, ST_ItemType::grand_literal, ST_ItemType::max_literal, ST_ItemType::min_literal, ST_ItemType::product_literal, ST_ItemType::stdDev_literal, ST_ItemType::stdDevP_literal, ST_ItemType::sum_literal, ST_ItemType::var_literal, ST_ItemType::varP_literal };

	const String ST_FieldSortType::ascending_literal = "ascending";
	const String ST_FieldSortType::descending_literal = "descending";
	const String ST_FieldSortType::manual_literal = "manual";
	String ST_FieldSortType::_literals[] = { ST_FieldSortType::ascending_literal, ST_FieldSortType::descending_literal, ST_FieldSortType::manual_literal };

	const String ST_ShowDataAs::difference_literal = "difference";
	const String ST_ShowDataAs::index_literal = "index";
	const String ST_ShowDataAs::normal_literal = "normal";
	const String ST_ShowDataAs::percent_literal = "percent";
	const String ST_ShowDataAs::percentDiff_literal = "percentDiff";
	const String ST_ShowDataAs::percentOfCol_literal = "percentOfCol";
	const String ST_ShowDataAs::percentOfRow_literal = "percentOfRow";
	const String ST_ShowDataAs::percentOfTotal_literal = "percentOfTotal";
	const String ST_ShowDataAs::runTotal_literal = "runTotal";
	String ST_ShowDataAs::_literals[] = { ST_ShowDataAs::difference_literal, ST_ShowDataAs::index_literal, ST_ShowDataAs::normal_literal, ST_ShowDataAs::percent_literal, ST_ShowDataAs::percentDiff_literal, ST_ShowDataAs::percentOfCol_literal, ST_ShowDataAs::percentOfRow_literal, ST_ShowDataAs::percentOfTotal_literal, ST_ShowDataAs::runTotal_literal };

	const String ST_FormatAction::blank_literal = "blank";
	const String ST_FormatAction::drill_literal = "drill";
	const String ST_FormatAction::formatting_literal = "formatting";
	const String ST_FormatAction::formula_literal = "formula";
	String ST_FormatAction::_literals[] = { ST_FormatAction::blank_literal, ST_FormatAction::drill_literal, ST_FormatAction::formatting_literal, ST_FormatAction::formula_literal };

	const String ST_Scope::data_literal = "data";
	const String ST_Scope::field_literal = "field";
	const String ST_Scope::selection_literal = "selection";
	String ST_Scope::_literals[] = { ST_Scope::data_literal, ST_Scope::field_literal, ST_Scope::selection_literal };

	const String ST_Type::all_literal = "all";
	const String ST_Type::column_literal = "column";
	const String ST_Type::none_literal = "none";
	const String ST_Type::row_literal = "row";
	String ST_Type::_literals[] = { ST_Type::all_literal, ST_Type::column_literal, ST_Type::none_literal, ST_Type::row_literal };

	const String ST_PivotFilterType::captionBeginsWith_literal = "captionBeginsWith";
	const String ST_PivotFilterType::captionBetween_literal = "captionBetween";
	const String ST_PivotFilterType::captionContains_literal = "captionContains";
	const String ST_PivotFilterType::captionEndsWith_literal = "captionEndsWith";
	const String ST_PivotFilterType::captionEqual_literal = "captionEqual";
	const String ST_PivotFilterType::captionGreaterThan_literal = "captionGreaterThan";
	const String ST_PivotFilterType::captionGreaterThanOrEqual_literal = "captionGreaterThanOrEqual";
	const String ST_PivotFilterType::captionLessThan_literal = "captionLessThan";
	const String ST_PivotFilterType::captionLessThanOrEqual_literal = "captionLessThanOrEqual";
	const String ST_PivotFilterType::captionNotBeginsWith_literal = "captionNotBeginsWith";
	const String ST_PivotFilterType::captionNotBetween_literal = "captionNotBetween";
	const String ST_PivotFilterType::captionNotContains_literal = "captionNotContains";
	const String ST_PivotFilterType::captionNotEndsWith_literal = "captionNotEndsWith";
	const String ST_PivotFilterType::captionNotEqual_literal = "captionNotEqual";
	const String ST_PivotFilterType::count_literal = "count";
	const String ST_PivotFilterType::dateBetween_literal = "dateBetween";
	const String ST_PivotFilterType::dateEqual_literal = "dateEqual";
	const String ST_PivotFilterType::dateNewerThan_literal = "dateNewerThan";
	const String ST_PivotFilterType::dateNewerThanOrEqual_literal = "dateNewerThanOrEqual";
	const String ST_PivotFilterType::dateNotBetween_literal = "dateNotBetween";
	const String ST_PivotFilterType::dateNotEqual_literal = "dateNotEqual";
	const String ST_PivotFilterType::dateOlderThan_literal = "dateOlderThan";
	const String ST_PivotFilterType::dateOlderThanOrEqual_literal = "dateOlderThanOrEqual";
	const String ST_PivotFilterType::lastMonth_literal = "lastMonth";
	const String ST_PivotFilterType::lastQuarter_literal = "lastQuarter";
	const String ST_PivotFilterType::lastWeek_literal = "lastWeek";
	const String ST_PivotFilterType::lastYear_literal = "lastYear";
	const String ST_PivotFilterType::M1_literal = "M1";
	const String ST_PivotFilterType::M10_literal = "M10";
	const String ST_PivotFilterType::M11_literal = "M11";
	const String ST_PivotFilterType::M12_literal = "M12";
	const String ST_PivotFilterType::M2_literal = "M2";
	const String ST_PivotFilterType::M3_literal = "M3";
	const String ST_PivotFilterType::M4_literal = "M4";
	const String ST_PivotFilterType::M5_literal = "M5";
	const String ST_PivotFilterType::M6_literal = "M6";
	const String ST_PivotFilterType::M7_literal = "M7";
	const String ST_PivotFilterType::M8_literal = "M8";
	const String ST_PivotFilterType::M9_literal = "M9";
	const String ST_PivotFilterType::nextMonth_literal = "nextMonth";
	const String ST_PivotFilterType::nextQuarter_literal = "nextQuarter";
	const String ST_PivotFilterType::nextWeek_literal = "nextWeek";
	const String ST_PivotFilterType::nextYear_literal = "nextYear";
	const String ST_PivotFilterType::percent_literal = "percent";
	const String ST_PivotFilterType::Q1_literal = "Q1";
	const String ST_PivotFilterType::Q2_literal = "Q2";
	const String ST_PivotFilterType::Q3_literal = "Q3";
	const String ST_PivotFilterType::Q4_literal = "Q4";
	const String ST_PivotFilterType::sum_literal = "sum";
	const String ST_PivotFilterType::thisMonth_literal = "thisMonth";
	const String ST_PivotFilterType::thisQuarter_literal = "thisQuarter";
	const String ST_PivotFilterType::thisWeek_literal = "thisWeek";
	const String ST_PivotFilterType::thisYear_literal = "thisYear";
	const String ST_PivotFilterType::today_literal = "today";
	const String ST_PivotFilterType::tomorrow_literal = "tomorrow";
	const String ST_PivotFilterType::unknown_literal = "unknown";
	const String ST_PivotFilterType::valueBetween_literal = "valueBetween";
	const String ST_PivotFilterType::valueEqual_literal = "valueEqual";
	const String ST_PivotFilterType::valueGreaterThan_literal = "valueGreaterThan";
	const String ST_PivotFilterType::valueGreaterThanOrEqual_literal = "valueGreaterThanOrEqual";
	const String ST_PivotFilterType::valueLessThan_literal = "valueLessThan";
	const String ST_PivotFilterType::valueLessThanOrEqual_literal = "valueLessThanOrEqual";
	const String ST_PivotFilterType::valueNotBetween_literal = "valueNotBetween";
	const String ST_PivotFilterType::valueNotEqual_literal = "valueNotEqual";
	const String ST_PivotFilterType::yearToDate_literal = "yearToDate";
	const String ST_PivotFilterType::yesterday_literal = "yesterday";
	String ST_PivotFilterType::_literals[] = { ST_PivotFilterType::captionBeginsWith_literal, ST_PivotFilterType::captionBetween_literal, ST_PivotFilterType::captionContains_literal, ST_PivotFilterType::captionEndsWith_literal, ST_PivotFilterType::captionEqual_literal, ST_PivotFilterType::captionGreaterThan_literal, ST_PivotFilterType::captionGreaterThanOrEqual_literal, ST_PivotFilterType::captionLessThan_literal, ST_PivotFilterType::captionLessThanOrEqual_literal, ST_PivotFilterType::captionNotBeginsWith_literal, ST_PivotFilterType::captionNotBetween_literal, ST_PivotFilterType::captionNotContains_literal, ST_PivotFilterType::captionNotEndsWith_literal, ST_PivotFilterType::captionNotEqual_literal, ST_PivotFilterType::count_literal, ST_PivotFilterType::dateBetween_literal, ST_PivotFilterType::dateEqual_literal, ST_PivotFilterType::dateNewerThan_literal, ST_PivotFilterType::dateNewerThanOrEqual_literal, ST_PivotFilterType::dateNotBetween_literal, ST_PivotFilterType::dateNotEqual_literal, ST_PivotFilterType::dateOlderThan_literal, ST_PivotFilterType::dateOlderThanOrEqual_literal, ST_PivotFilterType::lastMonth_literal, ST_PivotFilterType::lastQuarter_literal, ST_PivotFilterType::lastWeek_literal, ST_PivotFilterType::lastYear_literal, ST_PivotFilterType::M1_literal, ST_PivotFilterType::M10_literal, ST_PivotFilterType::M11_literal, ST_PivotFilterType::M12_literal, ST_PivotFilterType::M2_literal, ST_PivotFilterType::M3_literal, ST_PivotFilterType::M4_literal, ST_PivotFilterType::M5_literal, ST_PivotFilterType::M6_literal, ST_PivotFilterType::M7_literal, ST_PivotFilterType::M8_literal, ST_PivotFilterType::M9_literal, ST_PivotFilterType::nextMonth_literal, ST_PivotFilterType::nextQuarter_literal, ST_PivotFilterType::nextWeek_literal, ST_PivotFilterType::nextYear_literal, ST_PivotFilterType::percent_literal, ST_PivotFilterType::Q1_literal, ST_PivotFilterType::Q2_literal, ST_PivotFilterType::Q3_literal, ST_PivotFilterType::Q4_literal, ST_PivotFilterType::sum_literal, ST_PivotFilterType::thisMonth_literal, ST_PivotFilterType::thisQuarter_literal, ST_PivotFilterType::thisWeek_literal, ST_PivotFilterType::thisYear_literal, ST_PivotFilterType::today_literal, ST_PivotFilterType::tomorrow_literal, ST_PivotFilterType::unknown_literal, ST_PivotFilterType::valueBetween_literal, ST_PivotFilterType::valueEqual_literal, ST_PivotFilterType::valueGreaterThan_literal, ST_PivotFilterType::valueGreaterThanOrEqual_literal, ST_PivotFilterType::valueLessThan_literal, ST_PivotFilterType::valueLessThanOrEqual_literal, ST_PivotFilterType::valueNotBetween_literal, ST_PivotFilterType::valueNotEqual_literal, ST_PivotFilterType::yearToDate_literal, ST_PivotFilterType::yesterday_literal };

}
