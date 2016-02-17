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

#ifndef SML_SHEET_HPP
#define SML_SHEET_HPP


#include "sml-baseTypes.hpp"
#include "sml-sharedStringTable.hpp"
#include "sml-styles.hpp"
#include "sml-pivotTableShared.hpp"
#include "shared-relationshipReference.hpp"
#include "sml-autoFilter.hpp"
#include "sml-workbook.hpp"

namespace spreadsheetml
{
	using namespace ::xio;
	using namespace ::xio::xml::schema;

	class CT_CellFormula;
	class CT_Cell;
	class CT_OutlinePr;
	class CT_PageSetUpPr;
	class CT_SheetPr;
	class CT_SheetDimension;
	class CT_Pane;
	class CT_Selection;
	class CT_PivotSelection;
	class CT_SheetView;
	class CT_SheetViews;
	class CT_SheetFormatPr;
	class CT_Col;
	class CT_Cols;
	class ST_CellSpan;
	class ST_CellSpans;
	class CT_Row;
	class CT_SheetData;
	class CT_SheetCalcPr;
	class CT_SheetProtection;
	class CT_ProtectedRange;
	class CT_ProtectedRanges;
	class CT_InputCells;
	class CT_Scenario;
	class CT_Scenarios;
	class CT_DataRef;
	class CT_DataRefs;
	class CT_DataConsolidate;
	class CT_Break;
	class CT_PageBreak;
	class CT_PageMargins;
	class CT_PrintOptions;
	class CT_PageSetup;
	class CT_HeaderFooter;
	class CT_CustomSheetView;
	class CT_CustomSheetViews;
	class CT_MergeCell;
	class CT_MergeCells;
	class CT_Cfvo;
	class CT_ColorScale;
	class CT_DataBar;
	class CT_IconSet;
	class CT_CfRule;
	class CT_ConditionalFormatting;
	class CT_DataValidation;
	class CT_DataValidations;
	class CT_Hyperlink;
	class CT_Hyperlinks;
	class CT_CustomProperty;
	class CT_CustomProperties;
	class CT_CellWatch;
	class CT_CellWatches;
	class CT_IgnoredError;
	class CT_IgnoredErrors;
	class CT_CellSmartTagPr;
	class CT_CellSmartTag;
	class CT_CellSmartTags;
	class CT_SmartTags;
	class CT_Drawing;
	class CT_LegacyDrawing;
	class CT_OleObject;
	class CT_OleObjects;
	class CT_Control;
	class CT_Controls;
	class CT_WebPublishItem;
	class CT_WebPublishItems;
	class CT_TablePart;
	class CT_TableParts;
	class CT_Worksheet;
	class CT_ChartsheetPr;
	class CT_ChartsheetView;
	class CT_ChartsheetViews;
	class CT_ChartsheetProtection;
	class CT_CsPageSetup;
	class CT_CustomChartsheetView;
	class CT_CustomChartsheetViews;
	class CT_Chartsheet;
	class CT_Dialogsheet;
	class sml_sheet;

	class ST_DataConsolidateFunction
	{
		static String _literals[];
		String _value;
	public:
		enum value { average, count, countNums, max, min, product, stdDev, stdDevp, sum, var, varp };

		static const String average_literal;
		static const String count_literal;
		static const String countNums_literal;
		static const String max_literal;
		static const String min_literal;
		static const String product_literal;
		static const String stdDev_literal;
		static const String stdDevp_literal;
		static const String sum_literal;
		static const String var_literal;
		static const String varp_literal;

		ST_DataConsolidateFunction() : _value(average_literal) {}
		ST_DataConsolidateFunction(value val) : _value(convert(val)) {}
		ST_DataConsolidateFunction(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 11, 0); }
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

	class ST_CellFormulaType
	{
		static String _literals[];
		String _value;
	public:
		enum value { array, dataTable, normal, shared };

		static const String array_literal;
		static const String dataTable_literal;
		static const String normal_literal;
		static const String shared_literal;

		ST_CellFormulaType() : _value(normal_literal) {}
		ST_CellFormulaType(value val) : _value(convert(val)) {}
		ST_CellFormulaType(const String& str) : _value(str) {}

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

	class CT_CellFormula : public ST_Formula
	{
	public:
		CT_CellFormula() : t(ST_CellFormulaType::normal_literal), aca(false), dt2D(false), dtr(false), del1(false), del2(false), ca(false), bx(false) {}
		CT_CellFormula(const String& v) : ST_Formula(v), t(ST_CellFormulaType::normal_literal), aca(false), dt2D(false), dtr(false), del1(false), del2(false), ca(false), bx(false) {}
		ST_CellFormulaType t;
		Boolean aca;
		poptional< ST_Ref > ref;
		Boolean dt2D;
		Boolean dtr;
		Boolean del1;
		Boolean del2;
		poptional< ST_CellRef > r1;
		poptional< ST_CellRef > r2;
		Boolean ca;
		optional< UnsignedInt > si;
		Boolean bx;
	};

	class ST_CellType
	{
		static String _literals[];
		String _value;
	public:
		enum value { b, e, inlineStr, n, s, str };

		static const String b_literal;
		static const String e_literal;
		static const String inlineStr_literal;
		static const String n_literal;
		static const String s_literal;
		static const String str_literal;

		ST_CellType() : _value(b_literal) {}
		ST_CellType(value val) : _value(convert(val)) {}
		ST_CellType(const String& str) : _value(str) {}

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

	class CT_Cell
	{
	public:
		CT_Cell() : s(0U), t(ST_CellType::n_literal), cm(0U), vm(0U), ph(false) {}
		poptional< CT_CellFormula > f;
		poptional< ST_Xstring > v;
		poptional< CT_Rst > is;
		poptional< CT_ExtensionList > extLst;
		poptional< ST_CellRef > r;
		UnsignedInt s;
		ST_CellType t;
		UnsignedInt cm;
		UnsignedInt vm;
		Boolean ph;
	};

	class CT_OutlinePr
	{
	public:
		CT_OutlinePr() : applyStyles(false), summaryBelow(true), summaryRight(true), showOutlineSymbols(true) {}
		Boolean applyStyles;
		Boolean summaryBelow;
		Boolean summaryRight;
		Boolean showOutlineSymbols;
	};

	class CT_PageSetUpPr
	{
	public:
		CT_PageSetUpPr() : autoPageBreaks(true), fitToPage(false) {}
		Boolean autoPageBreaks;
		Boolean fitToPage;
	};

	class CT_SheetPr
	{
	public:
		CT_SheetPr() : syncHorizontal(false), syncVertical(false), transitionEvaluation(false), transitionEntry(false), published(true), filterMode(false), enableFormatConditionsCalculation(true) {}
		poptional< CT_Color > tabColor;
		poptional< CT_OutlinePr > outlinePr;
		poptional< CT_PageSetUpPr > pageSetUpPr;
		Boolean syncHorizontal;
		Boolean syncVertical;
		poptional< ST_Ref > syncRef;
		Boolean transitionEvaluation;
		Boolean transitionEntry;
		Boolean published;
		optional< String > codeName;
		Boolean filterMode;
		Boolean enableFormatConditionsCalculation;
	};

	class CT_SheetDimension
	{
	public:
		ST_Ref ref;
	};

	class ST_Pane
	{
		static String _literals[];
		String _value;
	public:
		enum value { bottomLeft, bottomRight, topLeft, topRight };

		static const String bottomLeft_literal;
		static const String bottomRight_literal;
		static const String topLeft_literal;
		static const String topRight_literal;

		ST_Pane() : _value(bottomRight_literal) {}
		ST_Pane(value val) : _value(convert(val)) {}
		ST_Pane(const String& str) : _value(str) {}

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

	class ST_PaneState
	{
		static String _literals[];
		String _value;
	public:
		enum value { frozen, frozenSplit, split };

		static const String frozen_literal;
		static const String frozenSplit_literal;
		static const String split_literal;

		ST_PaneState() : _value(split_literal) {}
		ST_PaneState(value val) : _value(convert(val)) {}
		ST_PaneState(const String& str) : _value(str) {}

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

	class CT_Pane
	{
	public:
		CT_Pane() : xSplit(0), ySplit(0), activePane(ST_Pane::topLeft_literal), state(ST_PaneState::split_literal) {}
		Double xSplit;
		Double ySplit;
		poptional< ST_CellRef > topLeftCell;
		ST_Pane activePane;
		ST_PaneState state;
	};

	class CT_Selection
	{
	public:
		CT_Selection() : pane(ST_Pane::topLeft_literal), activeCellId(0U), sqref("A1") {}
		ST_Pane pane;
		poptional< ST_CellRef > activeCell;
		UnsignedInt activeCellId;
		ST_Sqref sqref;
	};

	class CT_PivotSelection
	{
	public:
		CT_PivotSelection() : pane(ST_Pane::topLeft_literal), showHeader(false), label(false), data(false), extendable(false), count(0U), dimension(0U), start(0U), min(0U), max(0U), activeRow(0U), activeCol(0U), previousRow(0U), previousCol(0U), click(0U) {}
		CT_PivotArea pivotArea;
		ST_Pane pane;
		Boolean showHeader;
		Boolean label;
		Boolean data;
		Boolean extendable;
		UnsignedInt count;
		optional< ST_Axis > axis;
		UnsignedInt dimension;
		UnsignedInt start;
		UnsignedInt min;
		UnsignedInt max;
		UnsignedInt activeRow;
		UnsignedInt activeCol;
		UnsignedInt previousRow;
		UnsignedInt previousCol;
		UnsignedInt click;
		poptional< ::relationships::ST_RelationshipId > id;
	};

	class ST_SheetViewType
	{
		static String _literals[];
		String _value;
	public:
		enum value { normal, pageBreakPreview, pageLayout };

		static const String normal_literal;
		static const String pageBreakPreview_literal;
		static const String pageLayout_literal;

		ST_SheetViewType() : _value(normal_literal) {}
		ST_SheetViewType(value val) : _value(convert(val)) {}
		ST_SheetViewType(const String& str) : _value(str) {}

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

	class CT_SheetView
	{
	public:
		CT_SheetView() : windowProtection(false), showFormulas(false), showGridLines(true), showRowColHeaders(true), showZeros(true), rightToLeft(false), tabSelected(false), showRuler(true), showOutlineSymbols(true), defaultGridColor(true), showWhiteSpace(true), view(ST_SheetViewType::normal_literal), colorId(64U), zoomScale(100U), zoomScaleNormal(0U), zoomScaleSheetLayoutView(0U), zoomScalePageLayoutView(0U) {}
		poptional< CT_Pane > pane;
		std::vector< CT_Selection > selection;
		std::vector< CT_PivotSelection > pivotSelection;
		poptional< CT_ExtensionList > extLst;
		Boolean windowProtection;
		Boolean showFormulas;
		Boolean showGridLines;
		Boolean showRowColHeaders;
		Boolean showZeros;
		Boolean rightToLeft;
		Boolean tabSelected;
		Boolean showRuler;
		Boolean showOutlineSymbols;
		Boolean defaultGridColor;
		Boolean showWhiteSpace;
		ST_SheetViewType view;
		poptional< ST_CellRef > topLeftCell;
		UnsignedInt colorId;
		UnsignedInt zoomScale;
		UnsignedInt zoomScaleNormal;
		UnsignedInt zoomScaleSheetLayoutView;
		UnsignedInt zoomScalePageLayoutView;
		UnsignedInt workbookViewId;
	};

	class CT_SheetViews
	{
	public:
		std::vector< CT_SheetView > sheetView;
		poptional< CT_ExtensionList > extLst;
	};

	class CT_SheetFormatPr
	{
	public:
		CT_SheetFormatPr() : baseColWidth(8U), customHeight(false), zeroHeight(false), thickTop(false), thickBottom(false), outlineLevelRow(0), outlineLevelCol(0) {}
		UnsignedInt baseColWidth;
		optional< Double > defaultColWidth;
		Double defaultRowHeight;
		Boolean customHeight;
		Boolean zeroHeight;
		Boolean thickTop;
		Boolean thickBottom;
		UnsignedByte outlineLevelRow;
		UnsignedByte outlineLevelCol;
	};

	class CT_Col
	{
	public:
		CT_Col() : style(0U), hidden(false), bestFit(false), customWidth(false), phonetic(false), outlineLevel(0), collapsed(false) {}
		UnsignedInt min;
		UnsignedInt max;
		optional< Double > width;
		UnsignedInt style;
		Boolean hidden;
		Boolean bestFit;
		Boolean customWidth;
		Boolean phonetic;
		UnsignedByte outlineLevel;
		Boolean collapsed;
	};

	class CT_Cols
	{
	public:
		std::vector< CT_Col > col;
	};

	class ST_CellSpan : public simple_type<String>
	{
	public:
		ST_CellSpan() {}
		ST_CellSpan(const String& v) : simple_type<String>(v) {}
	};

	class ST_CellSpans : public list_type<ST_CellSpan >
	{
	public:
		ST_CellSpans() {}
		ST_CellSpans(const String& v) : list_type<ST_CellSpan >(v) {}
	};

	class CT_Row
	{
	public:
		CT_Row() : s(0U), customFormat(false), hidden(false), customHeight(false), outlineLevel(0), collapsed(false), thickTop(false), thickBot(false), ph(false) {}
		std::vector< CT_Cell > c;
		poptional< CT_ExtensionList > extLst;
		optional< UnsignedInt > r;
		poptional< ST_CellSpans > spans;
		UnsignedInt s;
		Boolean customFormat;
		optional< Double > ht;
		Boolean hidden;
		Boolean customHeight;
		UnsignedByte outlineLevel;
		Boolean collapsed;
		Boolean thickTop;
		Boolean thickBot;
		Boolean ph;
	};

	class CT_SheetData
	{
	public:
		std::vector< CT_Row > row;
	};

	class CT_SheetCalcPr
	{
	public:
		CT_SheetCalcPr() : fullCalcOnLoad(false) {}
		Boolean fullCalcOnLoad;
	};

	class CT_SheetProtection
	{
	public:
		CT_SheetProtection() : sheet(false), objects(false), scenarios(false), formatCells(true), formatColumns(true), formatRows(true), insertColumns(true), insertRows(true), insertHyperlinks(true), deleteColumns(true), deleteRows(true), selectLockedCells(false), sort(true), autoFilter(true), pivotTables(true), selectUnlockedCells(false) {}
		poptional< ST_UnsignedShortHex > password;
		Boolean sheet;
		Boolean objects;
		Boolean scenarios;
		Boolean formatCells;
		Boolean formatColumns;
		Boolean formatRows;
		Boolean insertColumns;
		Boolean insertRows;
		Boolean insertHyperlinks;
		Boolean deleteColumns;
		Boolean deleteRows;
		Boolean selectLockedCells;
		Boolean sort;
		Boolean autoFilter;
		Boolean pivotTables;
		Boolean selectUnlockedCells;
	};

	class CT_ProtectedRange
	{
	public:
		poptional< ST_UnsignedShortHex > password;
		ST_Sqref sqref;
		ST_Xstring name;
		optional< String > securityDescriptor;
	};

	class CT_ProtectedRanges
	{
	public:
		std::vector< CT_ProtectedRange > protectedRange;
	};

	class CT_InputCells
	{
	public:
		CT_InputCells() : deleted(false), undone(false) {}
		ST_CellRef r;
		Boolean deleted;
		Boolean undone;
		ST_Xstring val;
		poptional< ST_NumFmtId > numFmtId;
	};

	class CT_Scenario
	{
	public:
		CT_Scenario() : locked(false), hidden(false) {}
		std::vector< CT_InputCells > inputCells;
		ST_Xstring name;
		Boolean locked;
		Boolean hidden;
		optional< UnsignedInt > count;
		poptional< ST_Xstring > user;
		poptional< ST_Xstring > comment;
	};

	class CT_Scenarios
	{
	public:
		std::vector< CT_Scenario > scenario;
		optional< UnsignedInt > current;
		optional< UnsignedInt > show;
		poptional< ST_Sqref > sqref;
	};

	class CT_DataRef
	{
	public:
		poptional< ST_Ref > ref;
		poptional< ST_Xstring > name;
		poptional< ST_Xstring > sheet;
		poptional< ::relationships::ST_RelationshipId > id;
	};

	class CT_DataRefs
	{
	public:
		std::vector< CT_DataRef > dataRef;
		optional< UnsignedInt > count;
	};

	class CT_DataConsolidate
	{
	public:
		CT_DataConsolidate() : function(ST_DataConsolidateFunction::sum_literal), leftLabels(false), topLabels(false), link(false) {}
		poptional< CT_DataRefs > dataRefs;
		ST_DataConsolidateFunction function;
		Boolean leftLabels;
		Boolean topLabels;
		Boolean link;
	};

	class CT_Break
	{
	public:
		CT_Break() : id(0U), min(0U), max(0U), man(false), pt(false) {}
		UnsignedInt id;
		UnsignedInt min;
		UnsignedInt max;
		Boolean man;
		Boolean pt;
	};

	class CT_PageBreak
	{
	public:
		CT_PageBreak() : count(0U), manualBreakCount(0U) {}
		std::vector< CT_Break > brk;
		UnsignedInt count;
		UnsignedInt manualBreakCount;
	};

	class CT_PageMargins
	{
	public:
		Double left;
		Double right;
		Double top;
		Double bottom;
		Double header;
		Double footer;
	};

	class CT_PrintOptions
	{
	public:
		CT_PrintOptions() : horizontalCentered(false), verticalCentered(false), headings(false), gridLines(false), gridLinesSet(true) {}
		Boolean horizontalCentered;
		Boolean verticalCentered;
		Boolean headings;
		Boolean gridLines;
		Boolean gridLinesSet;
	};

	class ST_PageOrder
	{
		static String _literals[];
		String _value;
	public:
		enum value { downThenOver, overThenDown };

		static const String downThenOver_literal;
		static const String overThenDown_literal;

		ST_PageOrder() : _value(downThenOver_literal) {}
		ST_PageOrder(value val) : _value(convert(val)) {}
		ST_PageOrder(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 2, 0); }
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

	class ST_Orientation
	{
		static String _literals[];
		String _value;
	public:
		enum value { _default_, landscape, portrait };

		static const String _default__literal;
		static const String landscape_literal;
		static const String portrait_literal;

		ST_Orientation() : _value(_default__literal) {}
		ST_Orientation(value val) : _value(convert(val)) {}
		ST_Orientation(const String& str) : _value(str) {}

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

	class ST_CellComments
	{
		static String _literals[];
		String _value;
	public:
		enum value { asDisplayed, atEnd, none };

		static const String asDisplayed_literal;
		static const String atEnd_literal;
		static const String none_literal;

		ST_CellComments() : _value(none_literal) {}
		ST_CellComments(value val) : _value(convert(val)) {}
		ST_CellComments(const String& str) : _value(str) {}

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

	class ST_PrintError
	{
		static String _literals[];
		String _value;
	public:
		enum value { blank, dash, displayed, NA };

		static const String blank_literal;
		static const String dash_literal;
		static const String displayed_literal;
		static const String NA_literal;

		ST_PrintError() : _value(displayed_literal) {}
		ST_PrintError(value val) : _value(convert(val)) {}
		ST_PrintError(const String& str) : _value(str) {}

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

	class CT_PageSetup
	{
	public:
		CT_PageSetup() : paperSize(1U), scale(100U), firstPageNumber(1U), fitToWidth(1U), fitToHeight(1U), pageOrder(ST_PageOrder::downThenOver_literal), orientation(ST_Orientation::_default__literal), usePrinterDefaults(true), blackAndWhite(false), draft(false), cellComments(ST_CellComments::none_literal), useFirstPageNumber(false), errors(ST_PrintError::displayed_literal), horizontalDpi(600U), verticalDpi(600U), copies(1U) {}
		UnsignedInt paperSize;
		UnsignedInt scale;
		UnsignedInt firstPageNumber;
		UnsignedInt fitToWidth;
		UnsignedInt fitToHeight;
		ST_PageOrder pageOrder;
		ST_Orientation orientation;
		Boolean usePrinterDefaults;
		Boolean blackAndWhite;
		Boolean draft;
		ST_CellComments cellComments;
		Boolean useFirstPageNumber;
		ST_PrintError errors;
		UnsignedInt horizontalDpi;
		UnsignedInt verticalDpi;
		UnsignedInt copies;
		poptional< ::relationships::ST_RelationshipId > id;
	};

	class CT_HeaderFooter
	{
	public:
		CT_HeaderFooter() : differentOddEven(false), differentFirst(false), scaleWithDoc(true), alignWithMargins(true) {}
		poptional< ST_Xstring > oddHeader;
		poptional< ST_Xstring > oddFooter;
		poptional< ST_Xstring > evenHeader;
		poptional< ST_Xstring > evenFooter;
		poptional< ST_Xstring > firstHeader;
		poptional< ST_Xstring > firstFooter;
		Boolean differentOddEven;
		Boolean differentFirst;
		Boolean scaleWithDoc;
		Boolean alignWithMargins;
	};

	class CT_CustomSheetView
	{
	public:
		CT_CustomSheetView() : scale(100U), colorId(64U), showPageBreaks(false), showFormulas(false), showGridLines(true), showRowCol(true), outlineSymbols(true), zeroValues(true), fitToPage(false), printArea(false), filter(false), showAutoFilter(false), hiddenRows(false), hiddenColumns(false), state(ST_SheetState::visible_literal), filterUnique(false), view(ST_SheetViewType::normal_literal), showRuler(true) {}
		poptional< CT_Pane > pane;
		poptional< CT_Selection > selection;
		poptional< CT_PageBreak > rowBreaks;
		poptional< CT_PageBreak > colBreaks;
		poptional< CT_PageMargins > pageMargins;
		poptional< CT_PrintOptions > printOptions;
		poptional< CT_PageSetup > pageSetup;
		poptional< CT_HeaderFooter > headerFooter;
		poptional< CT_AutoFilter > autoFilter;
		poptional< CT_ExtensionList > extLst;
		ST_Guid guid;
		UnsignedInt scale;
		UnsignedInt colorId;
		Boolean showPageBreaks;
		Boolean showFormulas;
		Boolean showGridLines;
		Boolean showRowCol;
		Boolean outlineSymbols;
		Boolean zeroValues;
		Boolean fitToPage;
		Boolean printArea;
		Boolean filter;
		Boolean showAutoFilter;
		Boolean hiddenRows;
		Boolean hiddenColumns;
		ST_SheetState state;
		Boolean filterUnique;
		ST_SheetViewType view;
		Boolean showRuler;
		poptional< ST_CellRef > topLeftCell;
	};

	class CT_CustomSheetViews
	{
	public:
		std::vector< CT_CustomSheetView > customSheetView;
	};

	class CT_MergeCell
	{
	public:
		ST_Ref ref;
	};

	class CT_MergeCells
	{
	public:
		std::vector< CT_MergeCell > mergeCell;
		optional< UnsignedInt > count;
	};

	class ST_CfvoType
	{
		static String _literals[];
		String _value;
	public:
		enum value { formula, max, min, num, percent, percentile };

		static const String formula_literal;
		static const String max_literal;
		static const String min_literal;
		static const String num_literal;
		static const String percent_literal;
		static const String percentile_literal;

		ST_CfvoType() : _value(num_literal) {}
		ST_CfvoType(value val) : _value(convert(val)) {}
		ST_CfvoType(const String& str) : _value(str) {}

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

	class CT_Cfvo
	{
	public:
		CT_Cfvo() : gte(true) {}
		poptional< CT_ExtensionList > extLst;
		ST_CfvoType type;
		poptional< ST_Xstring > val;
		Boolean gte;
	};

	class CT_ColorScale
	{
	public:
		std::vector< CT_Cfvo > cfvo;
		std::vector< CT_Color > color;
	};

	class CT_DataBar
	{
	public:
		CT_DataBar() : minLength(10U), maxLength(90U), showValue(true) {}
		std::vector< CT_Cfvo > cfvo;
		CT_Color color;
		UnsignedInt minLength;
		UnsignedInt maxLength;
		Boolean showValue;
	};

	class CT_IconSet
	{
	public:
		CT_IconSet() : iconSet(ST_IconSetType::_3TrafficLights1__literal), showValue(true), percent(true), reverse(false) {}
		std::vector< CT_Cfvo > cfvo;
		ST_IconSetType iconSet;
		Boolean showValue;
		Boolean percent;
		Boolean reverse;
	};

	class ST_CfType
	{
		static String _literals[];
		String _value;
	public:
		enum value { aboveAverage, beginsWith, cellIs, colorScale, containsBlanks, containsErrors, containsText, dataBar, duplicateValues, endsWith, expression, iconSet, notContainsBlanks, notContainsErrors, notContainsText, timePeriod, top10, uniqueValues };

		static const String aboveAverage_literal;
		static const String beginsWith_literal;
		static const String cellIs_literal;
		static const String colorScale_literal;
		static const String containsBlanks_literal;
		static const String containsErrors_literal;
		static const String containsText_literal;
		static const String dataBar_literal;
		static const String duplicateValues_literal;
		static const String endsWith_literal;
		static const String expression_literal;
		static const String iconSet_literal;
		static const String notContainsBlanks_literal;
		static const String notContainsErrors_literal;
		static const String notContainsText_literal;
		static const String timePeriod_literal;
		static const String top10_literal;
		static const String uniqueValues_literal;

		ST_CfType() : _value(expression_literal) {}
		ST_CfType(value val) : _value(convert(val)) {}
		ST_CfType(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 18, 0); }
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

	class ST_ConditionalFormattingOperator
	{
		static String _literals[];
		String _value;
	public:
		enum value { beginsWith, between, containsText, endsWith, equal, greaterThan, greaterThanOrEqual, lessThan, lessThanOrEqual, notBetween, notContains, notEqual };

		static const String beginsWith_literal;
		static const String between_literal;
		static const String containsText_literal;
		static const String endsWith_literal;
		static const String equal_literal;
		static const String greaterThan_literal;
		static const String greaterThanOrEqual_literal;
		static const String lessThan_literal;
		static const String lessThanOrEqual_literal;
		static const String notBetween_literal;
		static const String notContains_literal;
		static const String notEqual_literal;

		ST_ConditionalFormattingOperator() : _value(lessThan_literal) {}
		ST_ConditionalFormattingOperator(value val) : _value(convert(val)) {}
		ST_ConditionalFormattingOperator(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 12, 0); }
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

	class ST_TimePeriod
	{
		static String _literals[];
		String _value;
	public:
		enum value { last7Days, lastMonth, lastWeek, nextMonth, nextWeek, thisMonth, thisWeek, today, tomorrow, yesterday };

		static const String last7Days_literal;
		static const String lastMonth_literal;
		static const String lastWeek_literal;
		static const String nextMonth_literal;
		static const String nextWeek_literal;
		static const String thisMonth_literal;
		static const String thisWeek_literal;
		static const String today_literal;
		static const String tomorrow_literal;
		static const String yesterday_literal;

		ST_TimePeriod() : _value(today_literal) {}
		ST_TimePeriod(value val) : _value(convert(val)) {}
		ST_TimePeriod(const String& str) : _value(str) {}

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

	class CT_CfRule
	{
	public:
		CT_CfRule() : stopIfTrue(false), aboveAverage(true), percent(false), bottom(false), equalAverage(false) {}
		std::vector< ST_Formula > formula;
		poptional< CT_ColorScale > colorScale;
		poptional< CT_DataBar > dataBar;
		poptional< CT_IconSet > iconSet;
		poptional< CT_ExtensionList > extLst;
		optional< ST_CfType > type;
		poptional< ST_DxfId > dxfId;
		Int priority;
		Boolean stopIfTrue;
		Boolean aboveAverage;
		Boolean percent;
		Boolean bottom;
		optional< ST_ConditionalFormattingOperator > _operator_;
		optional< String > text;
		optional< ST_TimePeriod > timePeriod;
		optional< UnsignedInt > rank;
		optional< Int > stdDev;
		Boolean equalAverage;
	};

	class CT_ConditionalFormatting
	{
	public:
		CT_ConditionalFormatting() : pivot(false) {}
		std::vector< CT_CfRule > cfRule;
		poptional< CT_ExtensionList > extLst;
		Boolean pivot;
		poptional< ST_Sqref > sqref;
	};

	class ST_DataValidationType
	{
		static String _literals[];
		String _value;
	public:
		enum value { custom, date, decimal, list, none, textLength, time, whole };

		static const String custom_literal;
		static const String date_literal;
		static const String decimal_literal;
		static const String list_literal;
		static const String none_literal;
		static const String textLength_literal;
		static const String time_literal;
		static const String whole_literal;

		ST_DataValidationType() : _value(none_literal) {}
		ST_DataValidationType(value val) : _value(convert(val)) {}
		ST_DataValidationType(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 8, 0); }
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

	class ST_DataValidationErrorStyle
	{
		static String _literals[];
		String _value;
	public:
		enum value { information, stop, warning };

		static const String information_literal;
		static const String stop_literal;
		static const String warning_literal;

		ST_DataValidationErrorStyle() : _value(stop_literal) {}
		ST_DataValidationErrorStyle(value val) : _value(convert(val)) {}
		ST_DataValidationErrorStyle(const String& str) : _value(str) {}

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

	class ST_DataValidationImeMode
	{
		static String _literals[];
		String _value;
	public:
		enum value { disabled, fullAlpha, fullHangul, fullKatakana, halfAlpha, halfHangul, halfKatakana, hiragana, noControl, off, on };

		static const String disabled_literal;
		static const String fullAlpha_literal;
		static const String fullHangul_literal;
		static const String fullKatakana_literal;
		static const String halfAlpha_literal;
		static const String halfHangul_literal;
		static const String halfKatakana_literal;
		static const String hiragana_literal;
		static const String noControl_literal;
		static const String off_literal;
		static const String on_literal;

		ST_DataValidationImeMode() : _value(noControl_literal) {}
		ST_DataValidationImeMode(value val) : _value(convert(val)) {}
		ST_DataValidationImeMode(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 11, 0); }
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

	class ST_DataValidationOperator
	{
		static String _literals[];
		String _value;
	public:
		enum value { between, equal, greaterThan, greaterThanOrEqual, lessThan, lessThanOrEqual, notBetween, notEqual };

		static const String between_literal;
		static const String equal_literal;
		static const String greaterThan_literal;
		static const String greaterThanOrEqual_literal;
		static const String lessThan_literal;
		static const String lessThanOrEqual_literal;
		static const String notBetween_literal;
		static const String notEqual_literal;

		ST_DataValidationOperator() : _value(between_literal) {}
		ST_DataValidationOperator(value val) : _value(convert(val)) {}
		ST_DataValidationOperator(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 8, 0); }
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

	class CT_DataValidation
	{
	public:
		CT_DataValidation() : type(ST_DataValidationType::none_literal), errorStyle(ST_DataValidationErrorStyle::stop_literal), imeMode(ST_DataValidationImeMode::noControl_literal), _operator_(ST_DataValidationOperator::between_literal), allowBlank(false), showDropDown(false), showInputMessage(false), showErrorMessage(false) {}
		poptional< ST_Formula > formula1;
		poptional< ST_Formula > formula2;
		ST_DataValidationType type;
		ST_DataValidationErrorStyle errorStyle;
		ST_DataValidationImeMode imeMode;
		ST_DataValidationOperator _operator_;
		Boolean allowBlank;
		Boolean showDropDown;
		Boolean showInputMessage;
		Boolean showErrorMessage;
		poptional< ST_Xstring > errorTitle;
		poptional< ST_Xstring > error;
		poptional< ST_Xstring > promptTitle;
		poptional< ST_Xstring > prompt;
		ST_Sqref sqref;
	};

	class CT_DataValidations
	{
	public:
		CT_DataValidations() : disablePrompts(false) {}
		std::vector< CT_DataValidation > dataValidation;
		Boolean disablePrompts;
		optional< UnsignedInt > xWindow;
		optional< UnsignedInt > yWindow;
		optional< UnsignedInt > count;
	};

	class CT_Hyperlink
	{
	public:
		ST_Ref ref;
		poptional< ::relationships::ST_RelationshipId > id;
		poptional< ST_Xstring > location;
		poptional< ST_Xstring > tooltip;
		poptional< ST_Xstring > display;
	};

	class CT_Hyperlinks
	{
	public:
		std::vector< CT_Hyperlink > hyperlink;
	};

	class CT_CustomProperty
	{
	public:
		ST_Xstring name;
		::relationships::ST_RelationshipId id;
	};

	class CT_CustomProperties
	{
	public:
		std::vector< CT_CustomProperty > customPr;
	};

	class CT_CellWatch
	{
	public:
		ST_CellRef r;
	};

	class CT_CellWatches
	{
	public:
		std::vector< CT_CellWatch > cellWatch;
	};

	class CT_IgnoredError
	{
	public:
		CT_IgnoredError() : evalError(false), twoDigitTextYear(false), numberStoredAsText(false), formula(false), formulaRange(false), unlockedFormula(false), emptyCellReference(false), listDataValidation(false), calculatedColumn(false) {}
		ST_Sqref sqref;
		Boolean evalError;
		Boolean twoDigitTextYear;
		Boolean numberStoredAsText;
		Boolean formula;
		Boolean formulaRange;
		Boolean unlockedFormula;
		Boolean emptyCellReference;
		Boolean listDataValidation;
		Boolean calculatedColumn;
	};

	class CT_IgnoredErrors
	{
	public:
		std::vector< CT_IgnoredError > ignoredError;
		poptional< CT_ExtensionList > extLst;
	};

	class CT_CellSmartTagPr
	{
	public:
		ST_Xstring key;
		ST_Xstring val;
	};

	class CT_CellSmartTag
	{
	public:
		CT_CellSmartTag() : deleted(false), xmlBased(false) {}
		std::vector< CT_CellSmartTagPr > cellSmartTagPr;
		UnsignedInt type;
		Boolean deleted;
		Boolean xmlBased;
	};

	class CT_CellSmartTags
	{
	public:
		std::vector< CT_CellSmartTag > cellSmartTag;
		ST_CellRef r;
	};

	class CT_SmartTags
	{
	public:
		std::vector< CT_CellSmartTags > cellSmartTags;
	};

	class CT_Drawing
	{
	public:
		::relationships::ST_RelationshipId id;
	};

	class CT_LegacyDrawing
	{
	public:
		::relationships::ST_RelationshipId id;
	};

	class ST_DvAspect
	{
		static String _literals[];
		String _value;
	public:
		enum value { DVASPECT_CONTENT, DVASPECT_ICON };

		static const String DVASPECT_CONTENT_literal;
		static const String DVASPECT_ICON_literal;

		ST_DvAspect() : _value(DVASPECT_CONTENT_literal) {}
		ST_DvAspect(value val) : _value(convert(val)) {}
		ST_DvAspect(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 2, 0); }
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

	class ST_OleUpdate
	{
		static String _literals[];
		String _value;
	public:
		enum value { OLEUPDATE_ALWAYS, OLEUPDATE_ONCALL };

		static const String OLEUPDATE_ALWAYS_literal;
		static const String OLEUPDATE_ONCALL_literal;

		ST_OleUpdate() : _value(OLEUPDATE_ALWAYS_literal) {}
		ST_OleUpdate(value val) : _value(convert(val)) {}
		ST_OleUpdate(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 2, 0); }
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

	class CT_OleObject
	{
	public:
		CT_OleObject() : dvAspect(ST_DvAspect::DVASPECT_CONTENT_literal), autoLoad(false) {}
		optional< String > progId;
		ST_DvAspect dvAspect;
		poptional< ST_Xstring > link;
		optional< ST_OleUpdate > oleUpdate;
		Boolean autoLoad;
		UnsignedInt shapeId;
		poptional< ::relationships::ST_RelationshipId > id;
	};

	class CT_OleObjects
	{
	public:
		std::vector< CT_OleObject > oleObject;
	};

	class CT_Control
	{
	public:
		UnsignedInt shapeId;
		::relationships::ST_RelationshipId id;
		optional< String > name;
	};

	class CT_Controls
	{
	public:
		std::vector< CT_Control > control;
	};

	class ST_WebSourceType
	{
		static String _literals[];
		String _value;
	public:
		enum value { autoFilter, chart, label, pivotTable, printArea, query, range, sheet };

		static const String autoFilter_literal;
		static const String chart_literal;
		static const String label_literal;
		static const String pivotTable_literal;
		static const String printArea_literal;
		static const String query_literal;
		static const String range_literal;
		static const String sheet_literal;

		ST_WebSourceType() : _value(sheet_literal) {}
		ST_WebSourceType(value val) : _value(convert(val)) {}
		ST_WebSourceType(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 8, 0); }
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

	class CT_WebPublishItem
	{
	public:
		CT_WebPublishItem() : autoRepublish(false) {}
		UnsignedInt id;
		ST_Xstring divId;
		ST_WebSourceType sourceType;
		poptional< ST_Ref > sourceRef;
		poptional< ST_Xstring > sourceObject;
		ST_Xstring destinationFile;
		poptional< ST_Xstring > title;
		Boolean autoRepublish;
	};

	class CT_WebPublishItems
	{
	public:
		std::vector< CT_WebPublishItem > webPublishItem;
		optional< UnsignedInt > count;
	};

	class CT_TablePart
	{
	public:
		::relationships::ST_RelationshipId id;
	};

	class CT_TableParts
	{
	public:
		std::vector< CT_TablePart > tablePart;
		optional< UnsignedInt > count;
	};

	class CT_Worksheet
	{
	public:
		poptional< CT_SheetPr > sheetPr;
		poptional< CT_SheetDimension > dimension;
		poptional< CT_SheetViews > sheetViews;
		poptional< CT_SheetFormatPr > sheetFormatPr;
		std::vector< CT_Cols > cols;
		CT_SheetData sheetData;
		poptional< CT_SheetCalcPr > sheetCalcPr;
		poptional< CT_SheetProtection > sheetProtection;
		poptional< CT_ProtectedRanges > protectedRanges;
		poptional< CT_Scenarios > scenarios;
		poptional< CT_AutoFilter > autoFilter;
		poptional< CT_SortState > sortState;
		poptional< CT_DataConsolidate > dataConsolidate;
		poptional< CT_CustomSheetViews > customSheetViews;
		poptional< CT_MergeCells > mergeCells;
		poptional< CT_PhoneticPr > phoneticPr;
		std::vector< CT_ConditionalFormatting > conditionalFormatting;
		poptional< CT_DataValidations > dataValidations;
		poptional< CT_Hyperlinks > hyperlinks;
		poptional< CT_PrintOptions > printOptions;
		poptional< CT_PageMargins > pageMargins;
		poptional< CT_PageSetup > pageSetup;
		poptional< CT_HeaderFooter > headerFooter;
		poptional< CT_PageBreak > rowBreaks;
		poptional< CT_PageBreak > colBreaks;
		poptional< CT_CustomProperties > customProperties;
		poptional< CT_CellWatches > cellWatches;
		poptional< CT_IgnoredErrors > ignoredErrors;
		poptional< CT_SmartTags > smartTags;
		poptional< CT_Drawing > drawing;
		poptional< CT_LegacyDrawing > legacyDrawing;
		poptional< CT_LegacyDrawing > legacyDrawingHF;
		poptional< CT_SheetBackgroundPicture > picture;
		poptional< CT_OleObjects > oleObjects;
		poptional< CT_Controls > controls;
		poptional< CT_WebPublishItems > webPublishItems;
		poptional< CT_TableParts > tableParts;
		poptional< CT_ExtensionList > extLst;
	};

	class CT_ChartsheetPr
	{
	public:
		CT_ChartsheetPr() : published(true) {}
		poptional< CT_Color > tabColor;
		Boolean published;
		optional< String > codeName;
	};

	class CT_ChartsheetView
	{
	public:
		CT_ChartsheetView() : tabSelected(false), zoomScale(100U), zoomToFit(false) {}
		poptional< CT_ExtensionList > extLst;
		Boolean tabSelected;
		UnsignedInt zoomScale;
		UnsignedInt workbookViewId;
		Boolean zoomToFit;
	};

	class CT_ChartsheetViews
	{
	public:
		std::vector< CT_ChartsheetView > sheetView;
		poptional< CT_ExtensionList > extLst;
	};

	class CT_ChartsheetProtection
	{
	public:
		CT_ChartsheetProtection() : content(false), objects(false) {}
		poptional< ST_UnsignedShortHex > password;
		Boolean content;
		Boolean objects;
	};

	class CT_CsPageSetup
	{
	public:
		CT_CsPageSetup() : paperSize(1U), firstPageNumber(1U), orientation(ST_Orientation::_default__literal), usePrinterDefaults(true), blackAndWhite(false), draft(false), useFirstPageNumber(false), horizontalDpi(600U), verticalDpi(600U), copies(1U) {}
		UnsignedInt paperSize;
		UnsignedInt firstPageNumber;
		ST_Orientation orientation;
		Boolean usePrinterDefaults;
		Boolean blackAndWhite;
		Boolean draft;
		Boolean useFirstPageNumber;
		UnsignedInt horizontalDpi;
		UnsignedInt verticalDpi;
		UnsignedInt copies;
		poptional< ::relationships::ST_RelationshipId > id;
	};

	class CT_CustomChartsheetView
	{
	public:
		CT_CustomChartsheetView() : scale(100U), state(ST_SheetState::visible_literal), zoomToFit(false) {}
		poptional< CT_PageMargins > pageMargins;
		poptional< CT_CsPageSetup > pageSetup;
		poptional< CT_HeaderFooter > headerFooter;
		ST_Guid guid;
		UnsignedInt scale;
		ST_SheetState state;
		Boolean zoomToFit;
	};

	class CT_CustomChartsheetViews
	{
	public:
		std::vector< CT_CustomChartsheetView > customSheetView;
	};

	class CT_Chartsheet
	{
	public:
		poptional< CT_ChartsheetPr > sheetPr;
		CT_ChartsheetViews sheetViews;
		poptional< CT_ChartsheetProtection > sheetProtection;
		poptional< CT_CustomChartsheetViews > customSheetViews;
		poptional< CT_PageMargins > pageMargins;
		poptional< CT_CsPageSetup > pageSetup;
		poptional< CT_HeaderFooter > headerFooter;
		CT_Drawing drawing;
		poptional< CT_LegacyDrawing > legacyDrawing;
		poptional< CT_LegacyDrawing > legacyDrawingHF;
		poptional< CT_SheetBackgroundPicture > picture;
		poptional< CT_WebPublishItems > webPublishItems;
		poptional< CT_ExtensionList > extLst;
	};

	class CT_Dialogsheet
	{
	public:
		poptional< CT_SheetPr > sheetPr;
		poptional< CT_SheetViews > sheetViews;
		poptional< CT_SheetFormatPr > sheetFormatPr;
		poptional< CT_SheetProtection > sheetProtection;
		poptional< CT_CustomSheetViews > customSheetViews;
		poptional< CT_PrintOptions > printOptions;
		poptional< CT_PageMargins > pageMargins;
		poptional< CT_PageSetup > pageSetup;
		poptional< CT_HeaderFooter > headerFooter;
		poptional< CT_Drawing > drawing;
		poptional< CT_LegacyDrawing > legacyDrawing;
		poptional< CT_LegacyDrawing > legacyDrawingHF;
		poptional< CT_OleObjects > oleObjects;
		poptional< CT_ExtensionList > extLst;
	};

	class sml_sheet
	{
	public:
		poptional< CT_Worksheet > worksheet;
		poptional< CT_Chartsheet > chartsheet;
		poptional< CT_Dialogsheet > dialogsheet;
	};

}
#endif

