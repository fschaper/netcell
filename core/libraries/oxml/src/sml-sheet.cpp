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


#include "sml-sheet.hpp"
namespace spreadsheetml
{
	const String ST_DataConsolidateFunction::average_literal = "average";
	const String ST_DataConsolidateFunction::count_literal = "count";
	const String ST_DataConsolidateFunction::countNums_literal = "countNums";
	const String ST_DataConsolidateFunction::max_literal = "max";
	const String ST_DataConsolidateFunction::min_literal = "min";
	const String ST_DataConsolidateFunction::product_literal = "product";
	const String ST_DataConsolidateFunction::stdDev_literal = "stdDev";
	const String ST_DataConsolidateFunction::stdDevp_literal = "stdDevp";
	const String ST_DataConsolidateFunction::sum_literal = "sum";
	const String ST_DataConsolidateFunction::var_literal = "var";
	const String ST_DataConsolidateFunction::varp_literal = "varp";
	String ST_DataConsolidateFunction::_literals[] = { ST_DataConsolidateFunction::average_literal, ST_DataConsolidateFunction::count_literal, ST_DataConsolidateFunction::countNums_literal, ST_DataConsolidateFunction::max_literal, ST_DataConsolidateFunction::min_literal, ST_DataConsolidateFunction::product_literal, ST_DataConsolidateFunction::stdDev_literal, ST_DataConsolidateFunction::stdDevp_literal, ST_DataConsolidateFunction::sum_literal, ST_DataConsolidateFunction::var_literal, ST_DataConsolidateFunction::varp_literal };

	const String ST_CellFormulaType::array_literal = "array";
	const String ST_CellFormulaType::dataTable_literal = "dataTable";
	const String ST_CellFormulaType::normal_literal = "normal";
	const String ST_CellFormulaType::shared_literal = "shared";
	String ST_CellFormulaType::_literals[] = { ST_CellFormulaType::array_literal, ST_CellFormulaType::dataTable_literal, ST_CellFormulaType::normal_literal, ST_CellFormulaType::shared_literal };

	const String ST_CellType::b_literal = "b";
	const String ST_CellType::e_literal = "e";
	const String ST_CellType::inlineStr_literal = "inlineStr";
	const String ST_CellType::n_literal = "n";
	const String ST_CellType::s_literal = "s";
	const String ST_CellType::str_literal = "str";
	String ST_CellType::_literals[] = { ST_CellType::b_literal, ST_CellType::e_literal, ST_CellType::inlineStr_literal, ST_CellType::n_literal, ST_CellType::s_literal, ST_CellType::str_literal };

	const String ST_Pane::bottomLeft_literal = "bottomLeft";
	const String ST_Pane::bottomRight_literal = "bottomRight";
	const String ST_Pane::topLeft_literal = "topLeft";
	const String ST_Pane::topRight_literal = "topRight";
	String ST_Pane::_literals[] = { ST_Pane::bottomLeft_literal, ST_Pane::bottomRight_literal, ST_Pane::topLeft_literal, ST_Pane::topRight_literal };

	const String ST_PaneState::frozen_literal = "frozen";
	const String ST_PaneState::frozenSplit_literal = "frozenSplit";
	const String ST_PaneState::split_literal = "split";
	String ST_PaneState::_literals[] = { ST_PaneState::frozen_literal, ST_PaneState::frozenSplit_literal, ST_PaneState::split_literal };

	const String ST_SheetViewType::normal_literal = "normal";
	const String ST_SheetViewType::pageBreakPreview_literal = "pageBreakPreview";
	const String ST_SheetViewType::pageLayout_literal = "pageLayout";
	String ST_SheetViewType::_literals[] = { ST_SheetViewType::normal_literal, ST_SheetViewType::pageBreakPreview_literal, ST_SheetViewType::pageLayout_literal };

	const String ST_PageOrder::downThenOver_literal = "downThenOver";
	const String ST_PageOrder::overThenDown_literal = "overThenDown";
	String ST_PageOrder::_literals[] = { ST_PageOrder::downThenOver_literal, ST_PageOrder::overThenDown_literal };

	const String ST_Orientation::_default__literal = "default";
	const String ST_Orientation::landscape_literal = "landscape";
	const String ST_Orientation::portrait_literal = "portrait";
	String ST_Orientation::_literals[] = { ST_Orientation::_default__literal, ST_Orientation::landscape_literal, ST_Orientation::portrait_literal };

	const String ST_CellComments::asDisplayed_literal = "asDisplayed";
	const String ST_CellComments::atEnd_literal = "atEnd";
	const String ST_CellComments::none_literal = "none";
	String ST_CellComments::_literals[] = { ST_CellComments::asDisplayed_literal, ST_CellComments::atEnd_literal, ST_CellComments::none_literal };

	const String ST_PrintError::blank_literal = "blank";
	const String ST_PrintError::dash_literal = "dash";
	const String ST_PrintError::displayed_literal = "displayed";
	const String ST_PrintError::NA_literal = "NA";
	String ST_PrintError::_literals[] = { ST_PrintError::blank_literal, ST_PrintError::dash_literal, ST_PrintError::displayed_literal, ST_PrintError::NA_literal };

	const String ST_CfvoType::formula_literal = "formula";
	const String ST_CfvoType::max_literal = "max";
	const String ST_CfvoType::min_literal = "min";
	const String ST_CfvoType::num_literal = "num";
	const String ST_CfvoType::percent_literal = "percent";
	const String ST_CfvoType::percentile_literal = "percentile";
	String ST_CfvoType::_literals[] = { ST_CfvoType::formula_literal, ST_CfvoType::max_literal, ST_CfvoType::min_literal, ST_CfvoType::num_literal, ST_CfvoType::percent_literal, ST_CfvoType::percentile_literal };

	const String ST_CfType::aboveAverage_literal = "aboveAverage";
	const String ST_CfType::beginsWith_literal = "beginsWith";
	const String ST_CfType::cellIs_literal = "cellIs";
	const String ST_CfType::colorScale_literal = "colorScale";
	const String ST_CfType::containsBlanks_literal = "containsBlanks";
	const String ST_CfType::containsErrors_literal = "containsErrors";
	const String ST_CfType::containsText_literal = "containsText";
	const String ST_CfType::dataBar_literal = "dataBar";
	const String ST_CfType::duplicateValues_literal = "duplicateValues";
	const String ST_CfType::endsWith_literal = "endsWith";
	const String ST_CfType::expression_literal = "expression";
	const String ST_CfType::iconSet_literal = "iconSet";
	const String ST_CfType::notContainsBlanks_literal = "notContainsBlanks";
	const String ST_CfType::notContainsErrors_literal = "notContainsErrors";
	const String ST_CfType::notContainsText_literal = "notContainsText";
	const String ST_CfType::timePeriod_literal = "timePeriod";
	const String ST_CfType::top10_literal = "top10";
	const String ST_CfType::uniqueValues_literal = "uniqueValues";
	String ST_CfType::_literals[] = { ST_CfType::aboveAverage_literal, ST_CfType::beginsWith_literal, ST_CfType::cellIs_literal, ST_CfType::colorScale_literal, ST_CfType::containsBlanks_literal, ST_CfType::containsErrors_literal, ST_CfType::containsText_literal, ST_CfType::dataBar_literal, ST_CfType::duplicateValues_literal, ST_CfType::endsWith_literal, ST_CfType::expression_literal, ST_CfType::iconSet_literal, ST_CfType::notContainsBlanks_literal, ST_CfType::notContainsErrors_literal, ST_CfType::notContainsText_literal, ST_CfType::timePeriod_literal, ST_CfType::top10_literal, ST_CfType::uniqueValues_literal };

	const String ST_ConditionalFormattingOperator::beginsWith_literal = "beginsWith";
	const String ST_ConditionalFormattingOperator::between_literal = "between";
	const String ST_ConditionalFormattingOperator::containsText_literal = "containsText";
	const String ST_ConditionalFormattingOperator::endsWith_literal = "endsWith";
	const String ST_ConditionalFormattingOperator::equal_literal = "equal";
	const String ST_ConditionalFormattingOperator::greaterThan_literal = "greaterThan";
	const String ST_ConditionalFormattingOperator::greaterThanOrEqual_literal = "greaterThanOrEqual";
	const String ST_ConditionalFormattingOperator::lessThan_literal = "lessThan";
	const String ST_ConditionalFormattingOperator::lessThanOrEqual_literal = "lessThanOrEqual";
	const String ST_ConditionalFormattingOperator::notBetween_literal = "notBetween";
	const String ST_ConditionalFormattingOperator::notContains_literal = "notContains";
	const String ST_ConditionalFormattingOperator::notEqual_literal = "notEqual";
	String ST_ConditionalFormattingOperator::_literals[] = { ST_ConditionalFormattingOperator::beginsWith_literal, ST_ConditionalFormattingOperator::between_literal, ST_ConditionalFormattingOperator::containsText_literal, ST_ConditionalFormattingOperator::endsWith_literal, ST_ConditionalFormattingOperator::equal_literal, ST_ConditionalFormattingOperator::greaterThan_literal, ST_ConditionalFormattingOperator::greaterThanOrEqual_literal, ST_ConditionalFormattingOperator::lessThan_literal, ST_ConditionalFormattingOperator::lessThanOrEqual_literal, ST_ConditionalFormattingOperator::notBetween_literal, ST_ConditionalFormattingOperator::notContains_literal, ST_ConditionalFormattingOperator::notEqual_literal };

	const String ST_TimePeriod::last7Days_literal = "last7Days";
	const String ST_TimePeriod::lastMonth_literal = "lastMonth";
	const String ST_TimePeriod::lastWeek_literal = "lastWeek";
	const String ST_TimePeriod::nextMonth_literal = "nextMonth";
	const String ST_TimePeriod::nextWeek_literal = "nextWeek";
	const String ST_TimePeriod::thisMonth_literal = "thisMonth";
	const String ST_TimePeriod::thisWeek_literal = "thisWeek";
	const String ST_TimePeriod::today_literal = "today";
	const String ST_TimePeriod::tomorrow_literal = "tomorrow";
	const String ST_TimePeriod::yesterday_literal = "yesterday";
	String ST_TimePeriod::_literals[] = { ST_TimePeriod::last7Days_literal, ST_TimePeriod::lastMonth_literal, ST_TimePeriod::lastWeek_literal, ST_TimePeriod::nextMonth_literal, ST_TimePeriod::nextWeek_literal, ST_TimePeriod::thisMonth_literal, ST_TimePeriod::thisWeek_literal, ST_TimePeriod::today_literal, ST_TimePeriod::tomorrow_literal, ST_TimePeriod::yesterday_literal };

	const String ST_DataValidationType::custom_literal = "custom";
	const String ST_DataValidationType::date_literal = "date";
	const String ST_DataValidationType::decimal_literal = "decimal";
	const String ST_DataValidationType::list_literal = "list";
	const String ST_DataValidationType::none_literal = "none";
	const String ST_DataValidationType::textLength_literal = "textLength";
	const String ST_DataValidationType::time_literal = "time";
	const String ST_DataValidationType::whole_literal = "whole";
	String ST_DataValidationType::_literals[] = { ST_DataValidationType::custom_literal, ST_DataValidationType::date_literal, ST_DataValidationType::decimal_literal, ST_DataValidationType::list_literal, ST_DataValidationType::none_literal, ST_DataValidationType::textLength_literal, ST_DataValidationType::time_literal, ST_DataValidationType::whole_literal };

	const String ST_DataValidationErrorStyle::information_literal = "information";
	const String ST_DataValidationErrorStyle::stop_literal = "stop";
	const String ST_DataValidationErrorStyle::warning_literal = "warning";
	String ST_DataValidationErrorStyle::_literals[] = { ST_DataValidationErrorStyle::information_literal, ST_DataValidationErrorStyle::stop_literal, ST_DataValidationErrorStyle::warning_literal };

	const String ST_DataValidationImeMode::disabled_literal = "disabled";
	const String ST_DataValidationImeMode::fullAlpha_literal = "fullAlpha";
	const String ST_DataValidationImeMode::fullHangul_literal = "fullHangul";
	const String ST_DataValidationImeMode::fullKatakana_literal = "fullKatakana";
	const String ST_DataValidationImeMode::halfAlpha_literal = "halfAlpha";
	const String ST_DataValidationImeMode::halfHangul_literal = "halfHangul";
	const String ST_DataValidationImeMode::halfKatakana_literal = "halfKatakana";
	const String ST_DataValidationImeMode::hiragana_literal = "hiragana";
	const String ST_DataValidationImeMode::noControl_literal = "noControl";
	const String ST_DataValidationImeMode::off_literal = "off";
	const String ST_DataValidationImeMode::on_literal = "on";
	String ST_DataValidationImeMode::_literals[] = { ST_DataValidationImeMode::disabled_literal, ST_DataValidationImeMode::fullAlpha_literal, ST_DataValidationImeMode::fullHangul_literal, ST_DataValidationImeMode::fullKatakana_literal, ST_DataValidationImeMode::halfAlpha_literal, ST_DataValidationImeMode::halfHangul_literal, ST_DataValidationImeMode::halfKatakana_literal, ST_DataValidationImeMode::hiragana_literal, ST_DataValidationImeMode::noControl_literal, ST_DataValidationImeMode::off_literal, ST_DataValidationImeMode::on_literal };

	const String ST_DataValidationOperator::between_literal = "between";
	const String ST_DataValidationOperator::equal_literal = "equal";
	const String ST_DataValidationOperator::greaterThan_literal = "greaterThan";
	const String ST_DataValidationOperator::greaterThanOrEqual_literal = "greaterThanOrEqual";
	const String ST_DataValidationOperator::lessThan_literal = "lessThan";
	const String ST_DataValidationOperator::lessThanOrEqual_literal = "lessThanOrEqual";
	const String ST_DataValidationOperator::notBetween_literal = "notBetween";
	const String ST_DataValidationOperator::notEqual_literal = "notEqual";
	String ST_DataValidationOperator::_literals[] = { ST_DataValidationOperator::between_literal, ST_DataValidationOperator::equal_literal, ST_DataValidationOperator::greaterThan_literal, ST_DataValidationOperator::greaterThanOrEqual_literal, ST_DataValidationOperator::lessThan_literal, ST_DataValidationOperator::lessThanOrEqual_literal, ST_DataValidationOperator::notBetween_literal, ST_DataValidationOperator::notEqual_literal };

	const String ST_DvAspect::DVASPECT_CONTENT_literal = "DVASPECT_CONTENT";
	const String ST_DvAspect::DVASPECT_ICON_literal = "DVASPECT_ICON";
	String ST_DvAspect::_literals[] = { ST_DvAspect::DVASPECT_CONTENT_literal, ST_DvAspect::DVASPECT_ICON_literal };

	const String ST_OleUpdate::OLEUPDATE_ALWAYS_literal = "OLEUPDATE_ALWAYS";
	const String ST_OleUpdate::OLEUPDATE_ONCALL_literal = "OLEUPDATE_ONCALL";
	String ST_OleUpdate::_literals[] = { ST_OleUpdate::OLEUPDATE_ALWAYS_literal, ST_OleUpdate::OLEUPDATE_ONCALL_literal };

	const String ST_WebSourceType::autoFilter_literal = "autoFilter";
	const String ST_WebSourceType::chart_literal = "chart";
	const String ST_WebSourceType::label_literal = "label";
	const String ST_WebSourceType::pivotTable_literal = "pivotTable";
	const String ST_WebSourceType::printArea_literal = "printArea";
	const String ST_WebSourceType::query_literal = "query";
	const String ST_WebSourceType::range_literal = "range";
	const String ST_WebSourceType::sheet_literal = "sheet";
	String ST_WebSourceType::_literals[] = { ST_WebSourceType::autoFilter_literal, ST_WebSourceType::chart_literal, ST_WebSourceType::label_literal, ST_WebSourceType::pivotTable_literal, ST_WebSourceType::printArea_literal, ST_WebSourceType::query_literal, ST_WebSourceType::range_literal, ST_WebSourceType::sheet_literal };

}
