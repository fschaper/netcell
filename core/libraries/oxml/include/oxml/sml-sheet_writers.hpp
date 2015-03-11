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

#ifndef SML_SHEET_WRITERS_HPP
#define SML_SHEET_WRITERS_HPP

#include "sml-sheet.hpp"
#include "sml-sheet_literals.hpp"
#include "sml-baseTypes_writers.hpp"
#include "sml-sharedStringTable_writers.hpp"
#include "sml-styles_writers.hpp"
#include "sml-pivotTableShared_writers.hpp"
#include "shared-relationshipReference_writers.hpp"
#include "sml-autoFilter_writers.hpp"
#include "sml-workbook_writers.hpp"

namespace spreadsheetml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_CellFormula_writer;
		class CT_Cell_writer;
		class CT_OutlinePr_writer;
		class CT_PageSetUpPr_writer;
		class CT_SheetPr_writer;
		class CT_SheetDimension_writer;
		class CT_Pane_writer;
		class CT_Selection_writer;
		class CT_PivotSelection_writer;
		class CT_SheetView_writer;
		class CT_SheetViews_writer;
		class CT_SheetFormatPr_writer;
		class CT_Col_writer;
		class CT_Cols_writer;
		class ST_CellSpan_writer;
		class ST_CellSpans_writer;
		class CT_Row_writer;
		class CT_SheetData_writer;
		class CT_SheetCalcPr_writer;
		class CT_SheetProtection_writer;
		class CT_ProtectedRange_writer;
		class CT_ProtectedRanges_writer;
		class CT_InputCells_writer;
		class CT_Scenario_writer;
		class CT_Scenarios_writer;
		class CT_DataRef_writer;
		class CT_DataRefs_writer;
		class CT_DataConsolidate_writer;
		class CT_Break_writer;
		class CT_PageBreak_writer;
		class CT_PageMargins_writer;
		class CT_PrintOptions_writer;
		class CT_PageSetup_writer;
		class CT_HeaderFooter_writer;
		class CT_CustomSheetView_writer;
		class CT_CustomSheetViews_writer;
		class CT_MergeCell_writer;
		class CT_MergeCells_writer;
		class CT_Cfvo_writer;
		class CT_ColorScale_writer;
		class CT_DataBar_writer;
		class CT_IconSet_writer;
		class CT_CfRule_writer;
		class CT_ConditionalFormatting_writer;
		class CT_DataValidation_writer;
		class CT_DataValidations_writer;
		class CT_Hyperlink_writer;
		class CT_Hyperlinks_writer;
		class CT_CustomProperty_writer;
		class CT_CustomProperties_writer;
		class CT_CellWatch_writer;
		class CT_CellWatches_writer;
		class CT_IgnoredError_writer;
		class CT_IgnoredErrors_writer;
		class CT_CellSmartTagPr_writer;
		class CT_CellSmartTag_writer;
		class CT_CellSmartTags_writer;
		class CT_SmartTags_writer;
		class CT_Drawing_writer;
		class CT_LegacyDrawing_writer;
		class CT_OleObject_writer;
		class CT_OleObjects_writer;
		class CT_Control_writer;
		class CT_Controls_writer;
		class CT_WebPublishItem_writer;
		class CT_WebPublishItems_writer;
		class CT_TablePart_writer;
		class CT_TableParts_writer;
		class CT_Worksheet_writer;
		class CT_ChartsheetPr_writer;
		class CT_ChartsheetView_writer;
		class CT_ChartsheetViews_writer;
		class CT_ChartsheetProtection_writer;
		class CT_CsPageSetup_writer;
		class CT_CustomChartsheetView_writer;
		class CT_CustomChartsheetViews_writer;
		class CT_Chartsheet_writer;
		class CT_Dialogsheet_writer;
		class sml_sheet_writer;

		class CT_CellFormula_writer : public ST_Formula_writer
		{
			CT_CellFormula* t() { return static_cast<CT_CellFormula*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Cell_writer : public type_writer
		{
			auto_type_writer< CT_CellFormula_writer > _f_writer;
			auto_type_writer< ST_Xstring_writer > _v_writer;
			auto_type_writer< CT_Rst_writer > _is_writer;
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_Cell* t() { return static_cast<CT_Cell*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_OutlinePr_writer : public type_writer
		{
			CT_OutlinePr* t() { return static_cast<CT_OutlinePr*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_PageSetUpPr_writer : public type_writer
		{
			CT_PageSetUpPr* t() { return static_cast<CT_PageSetUpPr*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_SheetPr_writer : public type_writer
		{
			auto_type_writer< CT_Color_writer > _tabColor_writer;
			auto_type_writer< CT_OutlinePr_writer > _outlinePr_writer;
			auto_type_writer< CT_PageSetUpPr_writer > _pageSetUpPr_writer;
			CT_SheetPr* t() { return static_cast<CT_SheetPr*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_SheetDimension_writer : public type_writer
		{
			CT_SheetDimension* t() { return static_cast<CT_SheetDimension*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Pane_writer : public type_writer
		{
			CT_Pane* t() { return static_cast<CT_Pane*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Selection_writer : public type_writer
		{
			CT_Selection* t() { return static_cast<CT_Selection*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_PivotSelection_writer : public type_writer
		{
			auto_type_writer< CT_PivotArea_writer > _pivotArea_writer;
			CT_PivotSelection* t() { return static_cast<CT_PivotSelection*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_SheetView_writer : public type_writer
		{
			auto_type_writer< CT_Pane_writer > _pane_writer;
			auto_type_writer< CT_Selection_writer > _selection_writer;
			auto_type_writer< CT_PivotSelection_writer > _pivotSelection_writer;
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_SheetView* t() { return static_cast<CT_SheetView*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_SheetViews_writer : public type_writer
		{
			auto_type_writer< CT_SheetView_writer > _sheetView_writer;
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_SheetViews* t() { return static_cast<CT_SheetViews*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_SheetFormatPr_writer : public type_writer
		{
			CT_SheetFormatPr* t() { return static_cast<CT_SheetFormatPr*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Col_writer : public type_writer
		{
			CT_Col* t() { return static_cast<CT_Col*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Cols_writer : public type_writer
		{
			auto_type_writer< CT_Col_writer > _col_writer;
			CT_Cols* t() { return static_cast<CT_Cols*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class ST_CellSpan_writer : public type_writer
		{
			ST_CellSpan* t() { return static_cast<ST_CellSpan*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class ST_CellSpans_writer : public ST_CellSpan_writer
		{
			ST_CellSpans* t() { return static_cast<ST_CellSpans*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Row_writer : public type_writer
		{
			auto_type_writer< CT_Cell_writer > _c_writer;
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_Row* t() { return static_cast<CT_Row*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_SheetData_writer : public type_writer
		{
			auto_type_writer< CT_Row_writer > _row_writer;
			CT_SheetData* t() { return static_cast<CT_SheetData*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_SheetCalcPr_writer : public type_writer
		{
			CT_SheetCalcPr* t() { return static_cast<CT_SheetCalcPr*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_SheetProtection_writer : public type_writer
		{
			CT_SheetProtection* t() { return static_cast<CT_SheetProtection*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_ProtectedRange_writer : public type_writer
		{
			CT_ProtectedRange* t() { return static_cast<CT_ProtectedRange*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_ProtectedRanges_writer : public type_writer
		{
			auto_type_writer< CT_ProtectedRange_writer > _protectedRange_writer;
			CT_ProtectedRanges* t() { return static_cast<CT_ProtectedRanges*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_InputCells_writer : public type_writer
		{
			CT_InputCells* t() { return static_cast<CT_InputCells*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Scenario_writer : public type_writer
		{
			auto_type_writer< CT_InputCells_writer > _inputCells_writer;
			CT_Scenario* t() { return static_cast<CT_Scenario*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Scenarios_writer : public type_writer
		{
			auto_type_writer< CT_Scenario_writer > _scenario_writer;
			CT_Scenarios* t() { return static_cast<CT_Scenarios*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_DataRef_writer : public type_writer
		{
			CT_DataRef* t() { return static_cast<CT_DataRef*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_DataRefs_writer : public type_writer
		{
			auto_type_writer< CT_DataRef_writer > _dataRef_writer;
			CT_DataRefs* t() { return static_cast<CT_DataRefs*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_DataConsolidate_writer : public type_writer
		{
			auto_type_writer< CT_DataRefs_writer > _dataRefs_writer;
			CT_DataConsolidate* t() { return static_cast<CT_DataConsolidate*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Break_writer : public type_writer
		{
			CT_Break* t() { return static_cast<CT_Break*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_PageBreak_writer : public type_writer
		{
			auto_type_writer< CT_Break_writer > _brk_writer;
			CT_PageBreak* t() { return static_cast<CT_PageBreak*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_PageMargins_writer : public type_writer
		{
			CT_PageMargins* t() { return static_cast<CT_PageMargins*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_PrintOptions_writer : public type_writer
		{
			CT_PrintOptions* t() { return static_cast<CT_PrintOptions*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_PageSetup_writer : public type_writer
		{
			CT_PageSetup* t() { return static_cast<CT_PageSetup*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_HeaderFooter_writer : public type_writer
		{
			auto_type_writer< ST_Xstring_writer > _oddHeader_writer;
			auto_type_writer< ST_Xstring_writer > _oddFooter_writer;
			auto_type_writer< ST_Xstring_writer > _evenHeader_writer;
			auto_type_writer< ST_Xstring_writer > _evenFooter_writer;
			auto_type_writer< ST_Xstring_writer > _firstHeader_writer;
			auto_type_writer< ST_Xstring_writer > _firstFooter_writer;
			CT_HeaderFooter* t() { return static_cast<CT_HeaderFooter*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_CustomSheetView_writer : public type_writer
		{
			auto_type_writer< CT_Pane_writer > _pane_writer;
			auto_type_writer< CT_Selection_writer > _selection_writer;
			auto_type_writer< CT_PageBreak_writer > _rowBreaks_writer;
			auto_type_writer< CT_PageBreak_writer > _colBreaks_writer;
			auto_type_writer< CT_PageMargins_writer > _pageMargins_writer;
			auto_type_writer< CT_PrintOptions_writer > _printOptions_writer;
			auto_type_writer< CT_PageSetup_writer > _pageSetup_writer;
			auto_type_writer< CT_HeaderFooter_writer > _headerFooter_writer;
			auto_type_writer< CT_AutoFilter_writer > _autoFilter_writer;
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_CustomSheetView* t() { return static_cast<CT_CustomSheetView*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_CustomSheetViews_writer : public type_writer
		{
			auto_type_writer< CT_CustomSheetView_writer > _customSheetView_writer;
			CT_CustomSheetViews* t() { return static_cast<CT_CustomSheetViews*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_MergeCell_writer : public type_writer
		{
			CT_MergeCell* t() { return static_cast<CT_MergeCell*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_MergeCells_writer : public type_writer
		{
			auto_type_writer< CT_MergeCell_writer > _mergeCell_writer;
			CT_MergeCells* t() { return static_cast<CT_MergeCells*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Cfvo_writer : public type_writer
		{
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_Cfvo* t() { return static_cast<CT_Cfvo*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_ColorScale_writer : public type_writer
		{
			auto_type_writer< CT_Cfvo_writer > _cfvo_writer;
			auto_type_writer< CT_Color_writer > _color_writer;
			CT_ColorScale* t() { return static_cast<CT_ColorScale*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_DataBar_writer : public type_writer
		{
			auto_type_writer< CT_Cfvo_writer > _cfvo_writer;
			auto_type_writer< CT_Color_writer > _color_writer;
			CT_DataBar* t() { return static_cast<CT_DataBar*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_IconSet_writer : public type_writer
		{
			auto_type_writer< CT_Cfvo_writer > _cfvo_writer;
			CT_IconSet* t() { return static_cast<CT_IconSet*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_CfRule_writer : public type_writer
		{
			auto_type_writer< ST_Formula_writer > _formula_writer;
			auto_type_writer< CT_ColorScale_writer > _colorScale_writer;
			auto_type_writer< CT_DataBar_writer > _dataBar_writer;
			auto_type_writer< CT_IconSet_writer > _iconSet_writer;
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_CfRule* t() { return static_cast<CT_CfRule*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_ConditionalFormatting_writer : public type_writer
		{
			auto_type_writer< CT_CfRule_writer > _cfRule_writer;
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_ConditionalFormatting* t() { return static_cast<CT_ConditionalFormatting*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_DataValidation_writer : public type_writer
		{
			auto_type_writer< ST_Formula_writer > _formula1_writer;
			auto_type_writer< ST_Formula_writer > _formula2_writer;
			CT_DataValidation* t() { return static_cast<CT_DataValidation*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_DataValidations_writer : public type_writer
		{
			auto_type_writer< CT_DataValidation_writer > _dataValidation_writer;
			CT_DataValidations* t() { return static_cast<CT_DataValidations*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Hyperlink_writer : public type_writer
		{
			CT_Hyperlink* t() { return static_cast<CT_Hyperlink*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Hyperlinks_writer : public type_writer
		{
			auto_type_writer< CT_Hyperlink_writer > _hyperlink_writer;
			CT_Hyperlinks* t() { return static_cast<CT_Hyperlinks*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_CustomProperty_writer : public type_writer
		{
			CT_CustomProperty* t() { return static_cast<CT_CustomProperty*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_CustomProperties_writer : public type_writer
		{
			auto_type_writer< CT_CustomProperty_writer > _customPr_writer;
			CT_CustomProperties* t() { return static_cast<CT_CustomProperties*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_CellWatch_writer : public type_writer
		{
			CT_CellWatch* t() { return static_cast<CT_CellWatch*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_CellWatches_writer : public type_writer
		{
			auto_type_writer< CT_CellWatch_writer > _cellWatch_writer;
			CT_CellWatches* t() { return static_cast<CT_CellWatches*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_IgnoredError_writer : public type_writer
		{
			CT_IgnoredError* t() { return static_cast<CT_IgnoredError*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_IgnoredErrors_writer : public type_writer
		{
			auto_type_writer< CT_IgnoredError_writer > _ignoredError_writer;
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_IgnoredErrors* t() { return static_cast<CT_IgnoredErrors*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_CellSmartTagPr_writer : public type_writer
		{
			CT_CellSmartTagPr* t() { return static_cast<CT_CellSmartTagPr*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_CellSmartTag_writer : public type_writer
		{
			auto_type_writer< CT_CellSmartTagPr_writer > _cellSmartTagPr_writer;
			CT_CellSmartTag* t() { return static_cast<CT_CellSmartTag*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_CellSmartTags_writer : public type_writer
		{
			auto_type_writer< CT_CellSmartTag_writer > _cellSmartTag_writer;
			CT_CellSmartTags* t() { return static_cast<CT_CellSmartTags*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_SmartTags_writer : public type_writer
		{
			auto_type_writer< CT_CellSmartTags_writer > _cellSmartTags_writer;
			CT_SmartTags* t() { return static_cast<CT_SmartTags*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Drawing_writer : public type_writer
		{
			CT_Drawing* t() { return static_cast<CT_Drawing*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_LegacyDrawing_writer : public type_writer
		{
			CT_LegacyDrawing* t() { return static_cast<CT_LegacyDrawing*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_OleObject_writer : public type_writer
		{
			CT_OleObject* t() { return static_cast<CT_OleObject*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_OleObjects_writer : public type_writer
		{
			auto_type_writer< CT_OleObject_writer > _oleObject_writer;
			CT_OleObjects* t() { return static_cast<CT_OleObjects*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Control_writer : public type_writer
		{
			CT_Control* t() { return static_cast<CT_Control*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Controls_writer : public type_writer
		{
			auto_type_writer< CT_Control_writer > _control_writer;
			CT_Controls* t() { return static_cast<CT_Controls*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_WebPublishItem_writer : public type_writer
		{
			CT_WebPublishItem* t() { return static_cast<CT_WebPublishItem*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_WebPublishItems_writer : public type_writer
		{
			auto_type_writer< CT_WebPublishItem_writer > _webPublishItem_writer;
			CT_WebPublishItems* t() { return static_cast<CT_WebPublishItems*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_TablePart_writer : public type_writer
		{
			CT_TablePart* t() { return static_cast<CT_TablePart*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_TableParts_writer : public type_writer
		{
			auto_type_writer< CT_TablePart_writer > _tablePart_writer;
			CT_TableParts* t() { return static_cast<CT_TableParts*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Worksheet_writer : public type_writer
		{
			auto_type_writer< CT_SheetPr_writer > _sheetPr_writer;
			auto_type_writer< CT_SheetDimension_writer > _dimension_writer;
			auto_type_writer< CT_SheetViews_writer > _sheetViews_writer;
			auto_type_writer< CT_SheetFormatPr_writer > _sheetFormatPr_writer;
			auto_type_writer< CT_Cols_writer > _cols_writer;
			auto_type_writer< CT_SheetData_writer > _sheetData_writer;
			auto_type_writer< CT_SheetCalcPr_writer > _sheetCalcPr_writer;
			auto_type_writer< CT_SheetProtection_writer > _sheetProtection_writer;
			auto_type_writer< CT_ProtectedRanges_writer > _protectedRanges_writer;
			auto_type_writer< CT_Scenarios_writer > _scenarios_writer;
			auto_type_writer< CT_AutoFilter_writer > _autoFilter_writer;
			auto_type_writer< CT_SortState_writer > _sortState_writer;
			auto_type_writer< CT_DataConsolidate_writer > _dataConsolidate_writer;
			auto_type_writer< CT_CustomSheetViews_writer > _customSheetViews_writer;
			auto_type_writer< CT_MergeCells_writer > _mergeCells_writer;
			auto_type_writer< CT_PhoneticPr_writer > _phoneticPr_writer;
			auto_type_writer< CT_ConditionalFormatting_writer > _conditionalFormatting_writer;
			auto_type_writer< CT_DataValidations_writer > _dataValidations_writer;
			auto_type_writer< CT_Hyperlinks_writer > _hyperlinks_writer;
			auto_type_writer< CT_PrintOptions_writer > _printOptions_writer;
			auto_type_writer< CT_PageMargins_writer > _pageMargins_writer;
			auto_type_writer< CT_PageSetup_writer > _pageSetup_writer;
			auto_type_writer< CT_HeaderFooter_writer > _headerFooter_writer;
			auto_type_writer< CT_PageBreak_writer > _rowBreaks_writer;
			auto_type_writer< CT_PageBreak_writer > _colBreaks_writer;
			auto_type_writer< CT_CustomProperties_writer > _customProperties_writer;
			auto_type_writer< CT_CellWatches_writer > _cellWatches_writer;
			auto_type_writer< CT_IgnoredErrors_writer > _ignoredErrors_writer;
			auto_type_writer< CT_SmartTags_writer > _smartTags_writer;
			auto_type_writer< CT_Drawing_writer > _drawing_writer;
			auto_type_writer< CT_LegacyDrawing_writer > _legacyDrawing_writer;
			auto_type_writer< CT_LegacyDrawing_writer > _legacyDrawingHF_writer;
			auto_type_writer< CT_SheetBackgroundPicture_writer > _picture_writer;
			auto_type_writer< CT_OleObjects_writer > _oleObjects_writer;
			auto_type_writer< CT_Controls_writer > _controls_writer;
			auto_type_writer< CT_WebPublishItems_writer > _webPublishItems_writer;
			auto_type_writer< CT_TableParts_writer > _tableParts_writer;
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_Worksheet* t() { return static_cast<CT_Worksheet*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_ChartsheetPr_writer : public type_writer
		{
			auto_type_writer< CT_Color_writer > _tabColor_writer;
			CT_ChartsheetPr* t() { return static_cast<CT_ChartsheetPr*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_ChartsheetView_writer : public type_writer
		{
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_ChartsheetView* t() { return static_cast<CT_ChartsheetView*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_ChartsheetViews_writer : public type_writer
		{
			auto_type_writer< CT_ChartsheetView_writer > _sheetView_writer;
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_ChartsheetViews* t() { return static_cast<CT_ChartsheetViews*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_ChartsheetProtection_writer : public type_writer
		{
			CT_ChartsheetProtection* t() { return static_cast<CT_ChartsheetProtection*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_CsPageSetup_writer : public type_writer
		{
			CT_CsPageSetup* t() { return static_cast<CT_CsPageSetup*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_CustomChartsheetView_writer : public type_writer
		{
			auto_type_writer< CT_PageMargins_writer > _pageMargins_writer;
			auto_type_writer< CT_CsPageSetup_writer > _pageSetup_writer;
			auto_type_writer< CT_HeaderFooter_writer > _headerFooter_writer;
			CT_CustomChartsheetView* t() { return static_cast<CT_CustomChartsheetView*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_CustomChartsheetViews_writer : public type_writer
		{
			auto_type_writer< CT_CustomChartsheetView_writer > _customSheetView_writer;
			CT_CustomChartsheetViews* t() { return static_cast<CT_CustomChartsheetViews*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Chartsheet_writer : public type_writer
		{
			auto_type_writer< CT_ChartsheetPr_writer > _sheetPr_writer;
			auto_type_writer< CT_ChartsheetViews_writer > _sheetViews_writer;
			auto_type_writer< CT_ChartsheetProtection_writer > _sheetProtection_writer;
			auto_type_writer< CT_CustomChartsheetViews_writer > _customSheetViews_writer;
			auto_type_writer< CT_PageMargins_writer > _pageMargins_writer;
			auto_type_writer< CT_CsPageSetup_writer > _pageSetup_writer;
			auto_type_writer< CT_HeaderFooter_writer > _headerFooter_writer;
			auto_type_writer< CT_Drawing_writer > _drawing_writer;
			auto_type_writer< CT_LegacyDrawing_writer > _legacyDrawing_writer;
			auto_type_writer< CT_LegacyDrawing_writer > _legacyDrawingHF_writer;
			auto_type_writer< CT_SheetBackgroundPicture_writer > _picture_writer;
			auto_type_writer< CT_WebPublishItems_writer > _webPublishItems_writer;
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_Chartsheet* t() { return static_cast<CT_Chartsheet*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Dialogsheet_writer : public type_writer
		{
			auto_type_writer< CT_SheetPr_writer > _sheetPr_writer;
			auto_type_writer< CT_SheetViews_writer > _sheetViews_writer;
			auto_type_writer< CT_SheetFormatPr_writer > _sheetFormatPr_writer;
			auto_type_writer< CT_SheetProtection_writer > _sheetProtection_writer;
			auto_type_writer< CT_CustomSheetViews_writer > _customSheetViews_writer;
			auto_type_writer< CT_PrintOptions_writer > _printOptions_writer;
			auto_type_writer< CT_PageMargins_writer > _pageMargins_writer;
			auto_type_writer< CT_PageSetup_writer > _pageSetup_writer;
			auto_type_writer< CT_HeaderFooter_writer > _headerFooter_writer;
			auto_type_writer< CT_Drawing_writer > _drawing_writer;
			auto_type_writer< CT_LegacyDrawing_writer > _legacyDrawing_writer;
			auto_type_writer< CT_LegacyDrawing_writer > _legacyDrawingHF_writer;
			auto_type_writer< CT_OleObjects_writer > _oleObjects_writer;
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_Dialogsheet* t() { return static_cast<CT_Dialogsheet*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class sml_sheet_writer : public type_writer
		{
			auto_type_writer< CT_Worksheet_writer > _worksheet_writer;
			auto_type_writer< CT_Chartsheet_writer > _chartsheet_writer;
			auto_type_writer< CT_Dialogsheet_writer > _dialogsheet_writer;
			sml_sheet* t() { return static_cast<sml_sheet*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

	}
}
#endif

