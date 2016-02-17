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

#ifndef SML_SHEET_READERS_HPP
#define SML_SHEET_READERS_HPP

#include "sml-sheet.hpp"
#include "sml-baseTypes_readers.hpp"
#include "sml-sharedStringTable_readers.hpp"
#include "sml-styles_readers.hpp"
#include "sml-pivotTableShared_readers.hpp"
#include "shared-relationshipReference_readers.hpp"
#include "sml-autoFilter_readers.hpp"
#include "sml-workbook_readers.hpp"

namespace spreadsheetml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_CellFormula_reader;
		class CT_Cell_reader;
		class CT_OutlinePr_reader;
		class CT_PageSetUpPr_reader;
		class CT_SheetPr_reader;
		class CT_SheetDimension_reader;
		class CT_Pane_reader;
		class CT_Selection_reader;
		class CT_PivotSelection_reader;
		class CT_SheetView_reader;
		class CT_SheetViews_reader;
		class CT_SheetFormatPr_reader;
		class CT_Col_reader;
		class CT_Cols_reader;
		class ST_CellSpan_reader;
		class ST_CellSpans_reader;
		class CT_Row_reader;
		class CT_SheetData_reader;
		class CT_SheetCalcPr_reader;
		class CT_SheetProtection_reader;
		class CT_ProtectedRange_reader;
		class CT_ProtectedRanges_reader;
		class CT_InputCells_reader;
		class CT_Scenario_reader;
		class CT_Scenarios_reader;
		class CT_DataRef_reader;
		class CT_DataRefs_reader;
		class CT_DataConsolidate_reader;
		class CT_Break_reader;
		class CT_PageBreak_reader;
		class CT_PageMargins_reader;
		class CT_PrintOptions_reader;
		class CT_PageSetup_reader;
		class CT_HeaderFooter_reader;
		class CT_CustomSheetView_reader;
		class CT_CustomSheetViews_reader;
		class CT_MergeCell_reader;
		class CT_MergeCells_reader;
		class CT_Cfvo_reader;
		class CT_ColorScale_reader;
		class CT_DataBar_reader;
		class CT_IconSet_reader;
		class CT_CfRule_reader;
		class CT_ConditionalFormatting_reader;
		class CT_DataValidation_reader;
		class CT_DataValidations_reader;
		class CT_Hyperlink_reader;
		class CT_Hyperlinks_reader;
		class CT_CustomProperty_reader;
		class CT_CustomProperties_reader;
		class CT_CellWatch_reader;
		class CT_CellWatches_reader;
		class CT_IgnoredError_reader;
		class CT_IgnoredErrors_reader;
		class CT_CellSmartTagPr_reader;
		class CT_CellSmartTag_reader;
		class CT_CellSmartTags_reader;
		class CT_SmartTags_reader;
		class CT_Drawing_reader;
		class CT_LegacyDrawing_reader;
		class CT_OleObject_reader;
		class CT_OleObjects_reader;
		class CT_Control_reader;
		class CT_Controls_reader;
		class CT_WebPublishItem_reader;
		class CT_WebPublishItems_reader;
		class CT_TablePart_reader;
		class CT_TableParts_reader;
		class CT_Worksheet_reader;
		class CT_ChartsheetPr_reader;
		class CT_ChartsheetView_reader;
		class CT_ChartsheetViews_reader;
		class CT_ChartsheetProtection_reader;
		class CT_CsPageSetup_reader;
		class CT_CustomChartsheetView_reader;
		class CT_CustomChartsheetViews_reader;
		class CT_Chartsheet_reader;
		class CT_Dialogsheet_reader;
		class sml_sheet_reader;

		class CT_CellFormula_reader : public ST_Formula_reader
		{
		protected:
			CT_CellFormula* t() { return static_cast<CT_CellFormula*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Cell_reader : public type_reader
		{
			auto_type_reader< CT_CellFormula_reader > _f_reader;
			auto_type_reader< ST_Xstring_reader > _v_reader;
			auto_type_reader< CT_Rst_reader > _is_reader;
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_Cell* t() { return static_cast<CT_Cell*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_OutlinePr_reader : public type_reader
		{
		protected:
			CT_OutlinePr* t() { return static_cast<CT_OutlinePr*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_PageSetUpPr_reader : public type_reader
		{
		protected:
			CT_PageSetUpPr* t() { return static_cast<CT_PageSetUpPr*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_SheetPr_reader : public type_reader
		{
			auto_type_reader< CT_Color_reader > _tabColor_reader;
			auto_type_reader< CT_OutlinePr_reader > _outlinePr_reader;
			auto_type_reader< CT_PageSetUpPr_reader > _pageSetUpPr_reader;
		protected:
			CT_SheetPr* t() { return static_cast<CT_SheetPr*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_SheetDimension_reader : public type_reader
		{
		protected:
			CT_SheetDimension* t() { return static_cast<CT_SheetDimension*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Pane_reader : public type_reader
		{
		protected:
			CT_Pane* t() { return static_cast<CT_Pane*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Selection_reader : public type_reader
		{
		protected:
			CT_Selection* t() { return static_cast<CT_Selection*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_PivotSelection_reader : public type_reader
		{
			auto_type_reader< CT_PivotArea_reader > _pivotArea_reader;
		protected:
			CT_PivotSelection* t() { return static_cast<CT_PivotSelection*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_SheetView_reader : public type_reader
		{
			auto_type_reader< CT_Pane_reader > _pane_reader;
			auto_type_reader< CT_Selection_reader > _selection_reader;
			auto_type_reader< CT_PivotSelection_reader > _pivotSelection_reader;
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_SheetView* t() { return static_cast<CT_SheetView*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_SheetViews_reader : public type_reader
		{
			auto_type_reader< CT_SheetView_reader > _sheetView_reader;
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_SheetViews* t() { return static_cast<CT_SheetViews*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_SheetFormatPr_reader : public type_reader
		{
		protected:
			CT_SheetFormatPr* t() { return static_cast<CT_SheetFormatPr*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Col_reader : public type_reader
		{
		protected:
			CT_Col* t() { return static_cast<CT_Col*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Cols_reader : public type_reader
		{
			auto_type_reader< CT_Col_reader > _col_reader;
		protected:
			CT_Cols* t() { return static_cast<CT_Cols*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class ST_CellSpan_reader : public type_reader
		{
		protected:
			ST_CellSpan* t() { return static_cast<ST_CellSpan*>(target()); }
			void read_value(const xstring& val);
		};

		class ST_CellSpans_reader : public ST_CellSpan_reader
		{
		protected:
			ST_CellSpans* t() { return static_cast<ST_CellSpans*>(target()); }
		};

		class CT_Row_reader : public type_reader
		{
			auto_type_reader< CT_Cell_reader > _c_reader;
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_Row* t() { return static_cast<CT_Row*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_SheetData_reader : public type_reader
		{
			auto_type_reader< CT_Row_reader > _row_reader;
		protected:
			CT_SheetData* t() { return static_cast<CT_SheetData*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_SheetCalcPr_reader : public type_reader
		{
		protected:
			CT_SheetCalcPr* t() { return static_cast<CT_SheetCalcPr*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_SheetProtection_reader : public type_reader
		{
		protected:
			CT_SheetProtection* t() { return static_cast<CT_SheetProtection*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_ProtectedRange_reader : public type_reader
		{
		protected:
			CT_ProtectedRange* t() { return static_cast<CT_ProtectedRange*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_ProtectedRanges_reader : public type_reader
		{
			auto_type_reader< CT_ProtectedRange_reader > _protectedRange_reader;
		protected:
			CT_ProtectedRanges* t() { return static_cast<CT_ProtectedRanges*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_InputCells_reader : public type_reader
		{
		protected:
			CT_InputCells* t() { return static_cast<CT_InputCells*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Scenario_reader : public type_reader
		{
			auto_type_reader< CT_InputCells_reader > _inputCells_reader;
		protected:
			CT_Scenario* t() { return static_cast<CT_Scenario*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Scenarios_reader : public type_reader
		{
			auto_type_reader< CT_Scenario_reader > _scenario_reader;
		protected:
			CT_Scenarios* t() { return static_cast<CT_Scenarios*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_DataRef_reader : public type_reader
		{
		protected:
			CT_DataRef* t() { return static_cast<CT_DataRef*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_DataRefs_reader : public type_reader
		{
			auto_type_reader< CT_DataRef_reader > _dataRef_reader;
		protected:
			CT_DataRefs* t() { return static_cast<CT_DataRefs*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_DataConsolidate_reader : public type_reader
		{
			auto_type_reader< CT_DataRefs_reader > _dataRefs_reader;
		protected:
			CT_DataConsolidate* t() { return static_cast<CT_DataConsolidate*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Break_reader : public type_reader
		{
		protected:
			CT_Break* t() { return static_cast<CT_Break*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_PageBreak_reader : public type_reader
		{
			auto_type_reader< CT_Break_reader > _brk_reader;
		protected:
			CT_PageBreak* t() { return static_cast<CT_PageBreak*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_PageMargins_reader : public type_reader
		{
		protected:
			CT_PageMargins* t() { return static_cast<CT_PageMargins*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_PrintOptions_reader : public type_reader
		{
		protected:
			CT_PrintOptions* t() { return static_cast<CT_PrintOptions*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_PageSetup_reader : public type_reader
		{
		protected:
			CT_PageSetup* t() { return static_cast<CT_PageSetup*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_HeaderFooter_reader : public type_reader
		{
			auto_type_reader< ST_Xstring_reader > _oddHeader_reader;
			auto_type_reader< ST_Xstring_reader > _oddFooter_reader;
			auto_type_reader< ST_Xstring_reader > _evenHeader_reader;
			auto_type_reader< ST_Xstring_reader > _evenFooter_reader;
			auto_type_reader< ST_Xstring_reader > _firstHeader_reader;
			auto_type_reader< ST_Xstring_reader > _firstFooter_reader;
		protected:
			CT_HeaderFooter* t() { return static_cast<CT_HeaderFooter*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_CustomSheetView_reader : public type_reader
		{
			auto_type_reader< CT_Pane_reader > _pane_reader;
			auto_type_reader< CT_Selection_reader > _selection_reader;
			auto_type_reader< CT_PageBreak_reader > _rowBreaks_reader;
			auto_type_reader< CT_PageBreak_reader > _colBreaks_reader;
			auto_type_reader< CT_PageMargins_reader > _pageMargins_reader;
			auto_type_reader< CT_PrintOptions_reader > _printOptions_reader;
			auto_type_reader< CT_PageSetup_reader > _pageSetup_reader;
			auto_type_reader< CT_HeaderFooter_reader > _headerFooter_reader;
			auto_type_reader< CT_AutoFilter_reader > _autoFilter_reader;
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_CustomSheetView* t() { return static_cast<CT_CustomSheetView*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_CustomSheetViews_reader : public type_reader
		{
			auto_type_reader< CT_CustomSheetView_reader > _customSheetView_reader;
		protected:
			CT_CustomSheetViews* t() { return static_cast<CT_CustomSheetViews*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_MergeCell_reader : public type_reader
		{
		protected:
			CT_MergeCell* t() { return static_cast<CT_MergeCell*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_MergeCells_reader : public type_reader
		{
			auto_type_reader< CT_MergeCell_reader > _mergeCell_reader;
		protected:
			CT_MergeCells* t() { return static_cast<CT_MergeCells*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Cfvo_reader : public type_reader
		{
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_Cfvo* t() { return static_cast<CT_Cfvo*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_ColorScale_reader : public type_reader
		{
			auto_type_reader< CT_Cfvo_reader > _cfvo_reader;
			auto_type_reader< CT_Color_reader > _color_reader;
		protected:
			CT_ColorScale* t() { return static_cast<CT_ColorScale*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_DataBar_reader : public type_reader
		{
			auto_type_reader< CT_Cfvo_reader > _cfvo_reader;
			auto_type_reader< CT_Color_reader > _color_reader;
		protected:
			CT_DataBar* t() { return static_cast<CT_DataBar*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_IconSet_reader : public type_reader
		{
			auto_type_reader< CT_Cfvo_reader > _cfvo_reader;
		protected:
			CT_IconSet* t() { return static_cast<CT_IconSet*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_CfRule_reader : public type_reader
		{
			auto_type_reader< ST_Formula_reader > _formula_reader;
			auto_type_reader< CT_ColorScale_reader > _colorScale_reader;
			auto_type_reader< CT_DataBar_reader > _dataBar_reader;
			auto_type_reader< CT_IconSet_reader > _iconSet_reader;
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_CfRule* t() { return static_cast<CT_CfRule*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_ConditionalFormatting_reader : public type_reader
		{
			auto_type_reader< CT_CfRule_reader > _cfRule_reader;
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_ConditionalFormatting* t() { return static_cast<CT_ConditionalFormatting*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_DataValidation_reader : public type_reader
		{
			auto_type_reader< ST_Formula_reader > _formula1_reader;
			auto_type_reader< ST_Formula_reader > _formula2_reader;
		protected:
			CT_DataValidation* t() { return static_cast<CT_DataValidation*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_DataValidations_reader : public type_reader
		{
			auto_type_reader< CT_DataValidation_reader > _dataValidation_reader;
		protected:
			CT_DataValidations* t() { return static_cast<CT_DataValidations*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Hyperlink_reader : public type_reader
		{
		protected:
			CT_Hyperlink* t() { return static_cast<CT_Hyperlink*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Hyperlinks_reader : public type_reader
		{
			auto_type_reader< CT_Hyperlink_reader > _hyperlink_reader;
		protected:
			CT_Hyperlinks* t() { return static_cast<CT_Hyperlinks*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_CustomProperty_reader : public type_reader
		{
		protected:
			CT_CustomProperty* t() { return static_cast<CT_CustomProperty*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_CustomProperties_reader : public type_reader
		{
			auto_type_reader< CT_CustomProperty_reader > _customPr_reader;
		protected:
			CT_CustomProperties* t() { return static_cast<CT_CustomProperties*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_CellWatch_reader : public type_reader
		{
		protected:
			CT_CellWatch* t() { return static_cast<CT_CellWatch*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_CellWatches_reader : public type_reader
		{
			auto_type_reader< CT_CellWatch_reader > _cellWatch_reader;
		protected:
			CT_CellWatches* t() { return static_cast<CT_CellWatches*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_IgnoredError_reader : public type_reader
		{
		protected:
			CT_IgnoredError* t() { return static_cast<CT_IgnoredError*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_IgnoredErrors_reader : public type_reader
		{
			auto_type_reader< CT_IgnoredError_reader > _ignoredError_reader;
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_IgnoredErrors* t() { return static_cast<CT_IgnoredErrors*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_CellSmartTagPr_reader : public type_reader
		{
		protected:
			CT_CellSmartTagPr* t() { return static_cast<CT_CellSmartTagPr*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_CellSmartTag_reader : public type_reader
		{
			auto_type_reader< CT_CellSmartTagPr_reader > _cellSmartTagPr_reader;
		protected:
			CT_CellSmartTag* t() { return static_cast<CT_CellSmartTag*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_CellSmartTags_reader : public type_reader
		{
			auto_type_reader< CT_CellSmartTag_reader > _cellSmartTag_reader;
		protected:
			CT_CellSmartTags* t() { return static_cast<CT_CellSmartTags*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_SmartTags_reader : public type_reader
		{
			auto_type_reader< CT_CellSmartTags_reader > _cellSmartTags_reader;
		protected:
			CT_SmartTags* t() { return static_cast<CT_SmartTags*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_Drawing_reader : public type_reader
		{
		protected:
			CT_Drawing* t() { return static_cast<CT_Drawing*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_LegacyDrawing_reader : public type_reader
		{
		protected:
			CT_LegacyDrawing* t() { return static_cast<CT_LegacyDrawing*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_OleObject_reader : public type_reader
		{
		protected:
			CT_OleObject* t() { return static_cast<CT_OleObject*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_OleObjects_reader : public type_reader
		{
			auto_type_reader< CT_OleObject_reader > _oleObject_reader;
		protected:
			CT_OleObjects* t() { return static_cast<CT_OleObjects*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_Control_reader : public type_reader
		{
		protected:
			CT_Control* t() { return static_cast<CT_Control*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Controls_reader : public type_reader
		{
			auto_type_reader< CT_Control_reader > _control_reader;
		protected:
			CT_Controls* t() { return static_cast<CT_Controls*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_WebPublishItem_reader : public type_reader
		{
		protected:
			CT_WebPublishItem* t() { return static_cast<CT_WebPublishItem*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_WebPublishItems_reader : public type_reader
		{
			auto_type_reader< CT_WebPublishItem_reader > _webPublishItem_reader;
		protected:
			CT_WebPublishItems* t() { return static_cast<CT_WebPublishItems*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_TablePart_reader : public type_reader
		{
		protected:
			CT_TablePart* t() { return static_cast<CT_TablePart*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_TableParts_reader : public type_reader
		{
			auto_type_reader< CT_TablePart_reader > _tablePart_reader;
		protected:
			CT_TableParts* t() { return static_cast<CT_TableParts*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Worksheet_reader : public type_reader
		{
			auto_type_reader< CT_SheetPr_reader > _sheetPr_reader;
			auto_type_reader< CT_SheetDimension_reader > _dimension_reader;
			auto_type_reader< CT_SheetViews_reader > _sheetViews_reader;
			auto_type_reader< CT_SheetFormatPr_reader > _sheetFormatPr_reader;
			auto_type_reader< CT_Cols_reader > _cols_reader;
			auto_type_reader< CT_SheetData_reader > _sheetData_reader;
			auto_type_reader< CT_SheetCalcPr_reader > _sheetCalcPr_reader;
			auto_type_reader< CT_SheetProtection_reader > _sheetProtection_reader;
			auto_type_reader< CT_ProtectedRanges_reader > _protectedRanges_reader;
			auto_type_reader< CT_Scenarios_reader > _scenarios_reader;
			auto_type_reader< CT_AutoFilter_reader > _autoFilter_reader;
			auto_type_reader< CT_SortState_reader > _sortState_reader;
			auto_type_reader< CT_DataConsolidate_reader > _dataConsolidate_reader;
			auto_type_reader< CT_CustomSheetViews_reader > _customSheetViews_reader;
			auto_type_reader< CT_MergeCells_reader > _mergeCells_reader;
			auto_type_reader< CT_PhoneticPr_reader > _phoneticPr_reader;
			auto_type_reader< CT_ConditionalFormatting_reader > _conditionalFormatting_reader;
			auto_type_reader< CT_DataValidations_reader > _dataValidations_reader;
			auto_type_reader< CT_Hyperlinks_reader > _hyperlinks_reader;
			auto_type_reader< CT_PrintOptions_reader > _printOptions_reader;
			auto_type_reader< CT_PageMargins_reader > _pageMargins_reader;
			auto_type_reader< CT_PageSetup_reader > _pageSetup_reader;
			auto_type_reader< CT_HeaderFooter_reader > _headerFooter_reader;
			auto_type_reader< CT_PageBreak_reader > _rowBreaks_reader;
			auto_type_reader< CT_PageBreak_reader > _colBreaks_reader;
			auto_type_reader< CT_CustomProperties_reader > _customProperties_reader;
			auto_type_reader< CT_CellWatches_reader > _cellWatches_reader;
			auto_type_reader< CT_IgnoredErrors_reader > _ignoredErrors_reader;
			auto_type_reader< CT_SmartTags_reader > _smartTags_reader;
			auto_type_reader< CT_Drawing_reader > _drawing_reader;
			auto_type_reader< CT_LegacyDrawing_reader > _legacyDrawing_reader;
			auto_type_reader< CT_LegacyDrawing_reader > _legacyDrawingHF_reader;
			auto_type_reader< CT_SheetBackgroundPicture_reader > _picture_reader;
			auto_type_reader< CT_OleObjects_reader > _oleObjects_reader;
			auto_type_reader< CT_Controls_reader > _controls_reader;
			auto_type_reader< CT_WebPublishItems_reader > _webPublishItems_reader;
			auto_type_reader< CT_TableParts_reader > _tableParts_reader;
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_Worksheet* t() { return static_cast<CT_Worksheet*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_ChartsheetPr_reader : public type_reader
		{
			auto_type_reader< CT_Color_reader > _tabColor_reader;
		protected:
			CT_ChartsheetPr* t() { return static_cast<CT_ChartsheetPr*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_ChartsheetView_reader : public type_reader
		{
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_ChartsheetView* t() { return static_cast<CT_ChartsheetView*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_ChartsheetViews_reader : public type_reader
		{
			auto_type_reader< CT_ChartsheetView_reader > _sheetView_reader;
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_ChartsheetViews* t() { return static_cast<CT_ChartsheetViews*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_ChartsheetProtection_reader : public type_reader
		{
		protected:
			CT_ChartsheetProtection* t() { return static_cast<CT_ChartsheetProtection*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_CsPageSetup_reader : public type_reader
		{
		protected:
			CT_CsPageSetup* t() { return static_cast<CT_CsPageSetup*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_CustomChartsheetView_reader : public type_reader
		{
			auto_type_reader< CT_PageMargins_reader > _pageMargins_reader;
			auto_type_reader< CT_CsPageSetup_reader > _pageSetup_reader;
			auto_type_reader< CT_HeaderFooter_reader > _headerFooter_reader;
		protected:
			CT_CustomChartsheetView* t() { return static_cast<CT_CustomChartsheetView*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_CustomChartsheetViews_reader : public type_reader
		{
			auto_type_reader< CT_CustomChartsheetView_reader > _customSheetView_reader;
		protected:
			CT_CustomChartsheetViews* t() { return static_cast<CT_CustomChartsheetViews*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_Chartsheet_reader : public type_reader
		{
			auto_type_reader< CT_ChartsheetPr_reader > _sheetPr_reader;
			auto_type_reader< CT_ChartsheetViews_reader > _sheetViews_reader;
			auto_type_reader< CT_ChartsheetProtection_reader > _sheetProtection_reader;
			auto_type_reader< CT_CustomChartsheetViews_reader > _customSheetViews_reader;
			auto_type_reader< CT_PageMargins_reader > _pageMargins_reader;
			auto_type_reader< CT_CsPageSetup_reader > _pageSetup_reader;
			auto_type_reader< CT_HeaderFooter_reader > _headerFooter_reader;
			auto_type_reader< CT_Drawing_reader > _drawing_reader;
			auto_type_reader< CT_LegacyDrawing_reader > _legacyDrawing_reader;
			auto_type_reader< CT_LegacyDrawing_reader > _legacyDrawingHF_reader;
			auto_type_reader< CT_SheetBackgroundPicture_reader > _picture_reader;
			auto_type_reader< CT_WebPublishItems_reader > _webPublishItems_reader;
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_Chartsheet* t() { return static_cast<CT_Chartsheet*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_Dialogsheet_reader : public type_reader
		{
			auto_type_reader< CT_SheetPr_reader > _sheetPr_reader;
			auto_type_reader< CT_SheetViews_reader > _sheetViews_reader;
			auto_type_reader< CT_SheetFormatPr_reader > _sheetFormatPr_reader;
			auto_type_reader< CT_SheetProtection_reader > _sheetProtection_reader;
			auto_type_reader< CT_CustomSheetViews_reader > _customSheetViews_reader;
			auto_type_reader< CT_PrintOptions_reader > _printOptions_reader;
			auto_type_reader< CT_PageMargins_reader > _pageMargins_reader;
			auto_type_reader< CT_PageSetup_reader > _pageSetup_reader;
			auto_type_reader< CT_HeaderFooter_reader > _headerFooter_reader;
			auto_type_reader< CT_Drawing_reader > _drawing_reader;
			auto_type_reader< CT_LegacyDrawing_reader > _legacyDrawing_reader;
			auto_type_reader< CT_LegacyDrawing_reader > _legacyDrawingHF_reader;
			auto_type_reader< CT_OleObjects_reader > _oleObjects_reader;
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_Dialogsheet* t() { return static_cast<CT_Dialogsheet*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class sml_sheet_reader : public type_reader
		{
			auto_type_reader< CT_Worksheet_reader > _worksheet_reader;
			auto_type_reader< CT_Chartsheet_reader > _chartsheet_reader;
			auto_type_reader< CT_Dialogsheet_reader > _dialogsheet_reader;
		protected:
			sml_sheet* t() { return static_cast<sml_sheet*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

	}
}
#endif

