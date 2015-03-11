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

#ifndef SML_WORKBOOK_HPP
#define SML_WORKBOOK_HPP


#include "shared-relationshipReference.hpp"
#include "sml-baseTypes.hpp"

namespace spreadsheetml
{
	using namespace ::xio;
	using namespace ::xio::xml::schema;

	class CT_SheetBackgroundPicture;
	class CT_FileVersion;
	class CT_FileSharing;
	class CT_WorkbookPr;
	class CT_WorkbookProtection;
	class CT_BookView;
	class CT_BookViews;
	class CT_Sheet;
	class CT_Sheets;
	class CT_FunctionGroup;
	class CT_FunctionGroups;
	class CT_ExternalReference;
	class CT_ExternalReferences;
	class CT_DefinedName;
	class CT_DefinedNames;
	class CT_CalcPr;
	class CT_OleSize;
	class CT_CustomWorkbookView;
	class CT_CustomWorkbookViews;
	class CT_PivotCache;
	class CT_PivotCaches;
	class CT_SmartTagPr;
	class CT_SmartTagType;
	class CT_SmartTagTypes;
	class CT_WebPublishing;
	class CT_FileRecoveryPr;
	class CT_WebPublishObject;
	class CT_WebPublishObjects;
	class CT_Workbook;
	class sml_workbook;

	class ST_SheetState
	{
		static String _literals[];
		String _value;
	public:
		enum value { hidden, veryHidden, visible };

		static const String hidden_literal;
		static const String veryHidden_literal;
		static const String visible_literal;

		ST_SheetState() : _value(visible_literal) {}
		ST_SheetState(value val) : _value(convert(val)) {}
		ST_SheetState(const String& str) : _value(str) {}

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

	class CT_SheetBackgroundPicture
	{
	public:
		::relationships::ST_RelationshipId id;
	};

	class CT_FileVersion
	{
	public:
		optional< String > appName;
		optional< String > lastEdited;
		optional< String > lowestEdited;
		optional< String > rupBuild;
		poptional< ST_Guid > codeName;
	};

	class CT_FileSharing
	{
	public:
		CT_FileSharing() : readOnlyRecommended(false) {}
		Boolean readOnlyRecommended;
		poptional< ST_Xstring > userName;
		poptional< ST_UnsignedShortHex > reservationPassword;
	};

	class ST_Objects
	{
		static String _literals[];
		String _value;
	public:
		enum value { all, none, placeholders };

		static const String all_literal;
		static const String none_literal;
		static const String placeholders_literal;

		ST_Objects() : _value(all_literal) {}
		ST_Objects(value val) : _value(convert(val)) {}
		ST_Objects(const String& str) : _value(str) {}

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

	class ST_UpdateLinks
	{
		static String _literals[];
		String _value;
	public:
		enum value { always, never, userSet };

		static const String always_literal;
		static const String never_literal;
		static const String userSet_literal;

		ST_UpdateLinks() : _value(userSet_literal) {}
		ST_UpdateLinks(value val) : _value(convert(val)) {}
		ST_UpdateLinks(const String& str) : _value(str) {}

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

	class CT_WorkbookPr
	{
	public:
		CT_WorkbookPr() : date1904(false), showObjects(ST_Objects::all_literal), showBorderUnselectedTables(true), filterPrivacy(false), promptedSolutions(false), showInkAnnotation(true), backupFile(false), saveExternalLinkValues(true), updateLinks(ST_UpdateLinks::userSet_literal), hidePivotFieldList(false), showPivotChartFilter(false), allowRefreshQuery(false), publishItems(false), checkCompatibility(false), autoCompressPictures(true), refreshAllConnections(false) {}
		Boolean date1904;
		ST_Objects showObjects;
		Boolean showBorderUnselectedTables;
		Boolean filterPrivacy;
		Boolean promptedSolutions;
		Boolean showInkAnnotation;
		Boolean backupFile;
		Boolean saveExternalLinkValues;
		ST_UpdateLinks updateLinks;
		optional< String > codeName;
		Boolean hidePivotFieldList;
		Boolean showPivotChartFilter;
		Boolean allowRefreshQuery;
		Boolean publishItems;
		Boolean checkCompatibility;
		Boolean autoCompressPictures;
		Boolean refreshAllConnections;
		optional< UnsignedInt > defaultThemeVersion;
	};

	class CT_WorkbookProtection
	{
	public:
		CT_WorkbookProtection() : lockStructure(false), lockWindows(false), lockRevision(false) {}
		poptional< ST_UnsignedShortHex > workbookPassword;
		poptional< ST_UnsignedShortHex > revisionsPassword;
		Boolean lockStructure;
		Boolean lockWindows;
		Boolean lockRevision;
	};

	class ST_Visibility
	{
		static String _literals[];
		String _value;
	public:
		enum value { hidden, veryHidden, visible };

		static const String hidden_literal;
		static const String veryHidden_literal;
		static const String visible_literal;

		ST_Visibility() : _value(visible_literal) {}
		ST_Visibility(value val) : _value(convert(val)) {}
		ST_Visibility(const String& str) : _value(str) {}

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

	class CT_BookView
	{
	public:
		CT_BookView() : visibility(ST_Visibility::visible_literal), minimized(false), showHorizontalScroll(true), showVerticalScroll(true), showSheetTabs(true), tabRatio(600U), firstSheet(0U), activeTab(0U), autoFilterDateGrouping(true) {}
		poptional< CT_ExtensionList > extLst;
		ST_Visibility visibility;
		Boolean minimized;
		Boolean showHorizontalScroll;
		Boolean showVerticalScroll;
		Boolean showSheetTabs;
		optional< Int > xWindow;
		optional< Int > yWindow;
		optional< UnsignedInt > windowWidth;
		optional< UnsignedInt > windowHeight;
		UnsignedInt tabRatio;
		UnsignedInt firstSheet;
		UnsignedInt activeTab;
		Boolean autoFilterDateGrouping;
	};

	class CT_BookViews
	{
	public:
		std::vector< CT_BookView > workbookView;
	};

	class CT_Sheet
	{
	public:
		CT_Sheet() : state(ST_SheetState::visible_literal) {}
		ST_Xstring name;
		UnsignedInt sheetId;
		ST_SheetState state;
		::relationships::ST_RelationshipId id;
	};

	class CT_Sheets
	{
	public:
		std::vector< CT_Sheet > sheet;
	};

	class CT_FunctionGroup
	{
	public:
		poptional< ST_Xstring > name;
	};

	class CT_FunctionGroups
	{
	public:
		CT_FunctionGroups() : builtInGroupCount(16U) {}
		poptional< CT_FunctionGroup > functionGroup;
		UnsignedInt builtInGroupCount;
	};

	class CT_ExternalReference
	{
	public:
		::relationships::ST_RelationshipId id;
	};

	class CT_ExternalReferences
	{
	public:
		std::vector< CT_ExternalReference > externalReference;
	};

	class CT_DefinedName : public ST_Formula
	{
	public:
		CT_DefinedName() : hidden(false), function(false), vbProcedure(false), xlm(false), publishToServer(false), workbookParameter(false) {}
		CT_DefinedName(const String& v) : ST_Formula(v), hidden(false), function(false), vbProcedure(false), xlm(false), publishToServer(false), workbookParameter(false) {}
		ST_Xstring name;
		poptional< ST_Xstring > comment;
		poptional< ST_Xstring > customMenu;
		poptional< ST_Xstring > description;
		poptional< ST_Xstring > help;
		poptional< ST_Xstring > statusBar;
		optional< UnsignedInt > localSheetId;
		Boolean hidden;
		Boolean function;
		Boolean vbProcedure;
		Boolean xlm;
		optional< UnsignedInt > functionGroupId;
		poptional< ST_Xstring > shortcutKey;
		Boolean publishToServer;
		Boolean workbookParameter;
	};

	class CT_DefinedNames
	{
	public:
		std::vector< CT_DefinedName > definedName;
	};

	class ST_CalcMode
	{
		static String _literals[];
		String _value;
	public:
		enum value { _auto_, autoNoTable, manual };

		static const String _auto__literal;
		static const String autoNoTable_literal;
		static const String manual_literal;

		ST_CalcMode() : _value(manual_literal) {}
		ST_CalcMode(value val) : _value(convert(val)) {}
		ST_CalcMode(const String& str) : _value(str) {}

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

	class ST_RefMode
	{
		static String _literals[];
		String _value;
	public:
		enum value { A1, R1C1 };

		static const String A1_literal;
		static const String R1C1_literal;

		ST_RefMode() : _value(A1_literal) {}
		ST_RefMode(value val) : _value(convert(val)) {}
		ST_RefMode(const String& str) : _value(str) {}

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

	class CT_CalcPr
	{
	public:
		CT_CalcPr() : calcMode(ST_CalcMode::_auto__literal), fullCalcOnLoad(false), refMode(ST_RefMode::A1_literal), iterate(false), iterateCount(100U), iterateDelta(0.001), fullPrecision(true), calcCompleted(true), calcOnSave(true), concurrentCalc(true) {}
		optional< UnsignedInt > calcId;
		ST_CalcMode calcMode;
		Boolean fullCalcOnLoad;
		ST_RefMode refMode;
		Boolean iterate;
		UnsignedInt iterateCount;
		Double iterateDelta;
		Boolean fullPrecision;
		Boolean calcCompleted;
		Boolean calcOnSave;
		Boolean concurrentCalc;
		optional< UnsignedInt > concurrentManualCount;
		optional< Boolean > forceFullCalc;
	};

	class CT_OleSize
	{
	public:
		ST_Ref ref;
	};

	class ST_Comments
	{
		static String _literals[];
		String _value;
	public:
		enum value { commIndAndComment, commIndicator, commNone };

		static const String commIndAndComment_literal;
		static const String commIndicator_literal;
		static const String commNone_literal;

		ST_Comments() : _value(commNone_literal) {}
		ST_Comments(value val) : _value(convert(val)) {}
		ST_Comments(const String& str) : _value(str) {}

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

	class CT_CustomWorkbookView
	{
	public:
		CT_CustomWorkbookView() : autoUpdate(false), changesSavedWin(false), onlySync(false), personalView(false), includePrintSettings(true), includeHiddenRowCol(true), maximized(false), minimized(false), showHorizontalScroll(true), showVerticalScroll(true), showSheetTabs(true), xWindow(0), yWindow(0), tabRatio(600U), showFormulaBar(true), showStatusbar(true), showComments(ST_Comments::commIndicator_literal), showObjects(ST_Objects::all_literal) {}
		poptional< CT_ExtensionList > extLst;
		ST_Xstring name;
		ST_Guid guid;
		Boolean autoUpdate;
		optional< UnsignedInt > mergeInterval;
		Boolean changesSavedWin;
		Boolean onlySync;
		Boolean personalView;
		Boolean includePrintSettings;
		Boolean includeHiddenRowCol;
		Boolean maximized;
		Boolean minimized;
		Boolean showHorizontalScroll;
		Boolean showVerticalScroll;
		Boolean showSheetTabs;
		Int xWindow;
		Int yWindow;
		UnsignedInt windowWidth;
		UnsignedInt windowHeight;
		UnsignedInt tabRatio;
		UnsignedInt activeSheetId;
		Boolean showFormulaBar;
		Boolean showStatusbar;
		ST_Comments showComments;
		ST_Objects showObjects;
	};

	class CT_CustomWorkbookViews
	{
	public:
		std::vector< CT_CustomWorkbookView > customWorkbookView;
	};

	class CT_PivotCache
	{
	public:
		UnsignedInt cacheId;
		::relationships::ST_RelationshipId id;
	};

	class CT_PivotCaches
	{
	public:
		std::vector< CT_PivotCache > pivotCache;
	};

	class ST_SmartTagShow
	{
		static String _literals[];
		String _value;
	public:
		enum value { all, noIndicator, none };

		static const String all_literal;
		static const String noIndicator_literal;
		static const String none_literal;

		ST_SmartTagShow() : _value(all_literal) {}
		ST_SmartTagShow(value val) : _value(convert(val)) {}
		ST_SmartTagShow(const String& str) : _value(str) {}

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

	class CT_SmartTagPr
	{
	public:
		CT_SmartTagPr() : embed(false), show(ST_SmartTagShow::all_literal) {}
		Boolean embed;
		ST_SmartTagShow show;
	};

	class CT_SmartTagType
	{
	public:
		poptional< ST_Xstring > namespaceUri;
		poptional< ST_Xstring > name;
		poptional< ST_Xstring > url;
	};

	class CT_SmartTagTypes
	{
	public:
		std::vector< CT_SmartTagType > smartTagType;
	};

	class ST_TargetScreenSize
	{
		static String _literals[];
		String _value;
	public:
		enum value { _1024x768_, _1152x882_, _1152x900_, _1280x1024_, _1600x1200_, _1800x1440_, _1920x1200_, _544x376_, _640x480_, _720x512_, _800x600_ };

		static const String _1024x768__literal;
		static const String _1152x882__literal;
		static const String _1152x900__literal;
		static const String _1280x1024__literal;
		static const String _1600x1200__literal;
		static const String _1800x1440__literal;
		static const String _1920x1200__literal;
		static const String _544x376__literal;
		static const String _640x480__literal;
		static const String _720x512__literal;
		static const String _800x600__literal;

		ST_TargetScreenSize() : _value(_544x376__literal) {}
		ST_TargetScreenSize(value val) : _value(convert(val)) {}
		ST_TargetScreenSize(const String& str) : _value(str) {}

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

	class CT_WebPublishing
	{
	public:
		CT_WebPublishing() : css(true), thicket(true), longFileNames(true), vml(false), allowPng(false), targetScreenSize(ST_TargetScreenSize::_800x600__literal), dpi(96U) {}
		Boolean css;
		Boolean thicket;
		Boolean longFileNames;
		Boolean vml;
		Boolean allowPng;
		ST_TargetScreenSize targetScreenSize;
		UnsignedInt dpi;
		optional< UnsignedInt > codePage;
	};

	class CT_FileRecoveryPr
	{
	public:
		CT_FileRecoveryPr() : autoRecover(true), crashSave(false), dataExtractLoad(false), repairLoad(false) {}
		Boolean autoRecover;
		Boolean crashSave;
		Boolean dataExtractLoad;
		Boolean repairLoad;
	};

	class CT_WebPublishObject
	{
	public:
		CT_WebPublishObject() : autoRepublish(false) {}
		UnsignedInt id;
		ST_Xstring divId;
		poptional< ST_Xstring > sourceObject;
		ST_Xstring destinationFile;
		poptional< ST_Xstring > title;
		Boolean autoRepublish;
	};

	class CT_WebPublishObjects
	{
	public:
		std::vector< CT_WebPublishObject > webPublishObject;
		optional< UnsignedInt > count;
	};

	class CT_Workbook
	{
	public:
		poptional< CT_FileVersion > fileVersion;
		poptional< CT_FileSharing > fileSharing;
		poptional< CT_WorkbookPr > workbookPr;
		poptional< CT_WorkbookProtection > workbookProtection;
		poptional< CT_BookViews > bookViews;
		CT_Sheets sheets;
		poptional< CT_FunctionGroups > functionGroups;
		poptional< CT_ExternalReferences > externalReferences;
		poptional< CT_DefinedNames > definedNames;
		poptional< CT_CalcPr > calcPr;
		poptional< CT_OleSize > oleSize;
		poptional< CT_CustomWorkbookViews > customWorkbookViews;
		poptional< CT_PivotCaches > pivotCaches;
		poptional< CT_SmartTagPr > smartTagPr;
		poptional< CT_SmartTagTypes > smartTagTypes;
		poptional< CT_WebPublishing > webPublishing;
		std::vector< CT_FileRecoveryPr > fileRecoveryPr;
		poptional< CT_WebPublishObjects > webPublishObjects;
		poptional< CT_ExtensionList > extLst;
	};

	class sml_workbook
	{
	public:
		poptional< CT_Workbook > workbook;
	};

}
#endif

