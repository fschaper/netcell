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

#ifndef SML_WORKBOOK_WRITERS_HPP
#define SML_WORKBOOK_WRITERS_HPP

#include "sml-workbook.hpp"
#include "sml-workbook_literals.hpp"
#include "shared-relationshipReference_writers.hpp"
#include "sml-baseTypes_writers.hpp"

namespace spreadsheetml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_SheetBackgroundPicture_writer;
		class CT_FileVersion_writer;
		class CT_FileSharing_writer;
		class CT_WorkbookPr_writer;
		class CT_WorkbookProtection_writer;
		class CT_BookView_writer;
		class CT_BookViews_writer;
		class CT_Sheet_writer;
		class CT_Sheets_writer;
		class CT_FunctionGroup_writer;
		class CT_FunctionGroups_writer;
		class CT_ExternalReference_writer;
		class CT_ExternalReferences_writer;
		class CT_DefinedName_writer;
		class CT_DefinedNames_writer;
		class CT_CalcPr_writer;
		class CT_OleSize_writer;
		class CT_CustomWorkbookView_writer;
		class CT_CustomWorkbookViews_writer;
		class CT_PivotCache_writer;
		class CT_PivotCaches_writer;
		class CT_SmartTagPr_writer;
		class CT_SmartTagType_writer;
		class CT_SmartTagTypes_writer;
		class CT_WebPublishing_writer;
		class CT_FileRecoveryPr_writer;
		class CT_WebPublishObject_writer;
		class CT_WebPublishObjects_writer;
		class CT_Workbook_writer;
		class sml_workbook_writer;

		class CT_SheetBackgroundPicture_writer : public type_writer
		{
			CT_SheetBackgroundPicture* t() { return static_cast<CT_SheetBackgroundPicture*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_FileVersion_writer : public type_writer
		{
			CT_FileVersion* t() { return static_cast<CT_FileVersion*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_FileSharing_writer : public type_writer
		{
			CT_FileSharing* t() { return static_cast<CT_FileSharing*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_WorkbookPr_writer : public type_writer
		{
			CT_WorkbookPr* t() { return static_cast<CT_WorkbookPr*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_WorkbookProtection_writer : public type_writer
		{
			CT_WorkbookProtection* t() { return static_cast<CT_WorkbookProtection*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_BookView_writer : public type_writer
		{
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_BookView* t() { return static_cast<CT_BookView*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_BookViews_writer : public type_writer
		{
			auto_type_writer< CT_BookView_writer > _workbookView_writer;
			CT_BookViews* t() { return static_cast<CT_BookViews*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Sheet_writer : public type_writer
		{
			CT_Sheet* t() { return static_cast<CT_Sheet*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Sheets_writer : public type_writer
		{
			auto_type_writer< CT_Sheet_writer > _sheet_writer;
			CT_Sheets* t() { return static_cast<CT_Sheets*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_FunctionGroup_writer : public type_writer
		{
			CT_FunctionGroup* t() { return static_cast<CT_FunctionGroup*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_FunctionGroups_writer : public type_writer
		{
			auto_type_writer< CT_FunctionGroup_writer > _functionGroup_writer;
			CT_FunctionGroups* t() { return static_cast<CT_FunctionGroups*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_ExternalReference_writer : public type_writer
		{
			CT_ExternalReference* t() { return static_cast<CT_ExternalReference*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_ExternalReferences_writer : public type_writer
		{
			auto_type_writer< CT_ExternalReference_writer > _externalReference_writer;
			CT_ExternalReferences* t() { return static_cast<CT_ExternalReferences*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_DefinedName_writer : public ST_Formula_writer
		{
			CT_DefinedName* t() { return static_cast<CT_DefinedName*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_DefinedNames_writer : public type_writer
		{
			auto_type_writer< CT_DefinedName_writer > _definedName_writer;
			CT_DefinedNames* t() { return static_cast<CT_DefinedNames*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_CalcPr_writer : public type_writer
		{
			CT_CalcPr* t() { return static_cast<CT_CalcPr*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_OleSize_writer : public type_writer
		{
			CT_OleSize* t() { return static_cast<CT_OleSize*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_CustomWorkbookView_writer : public type_writer
		{
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_CustomWorkbookView* t() { return static_cast<CT_CustomWorkbookView*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_CustomWorkbookViews_writer : public type_writer
		{
			auto_type_writer< CT_CustomWorkbookView_writer > _customWorkbookView_writer;
			CT_CustomWorkbookViews* t() { return static_cast<CT_CustomWorkbookViews*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_PivotCache_writer : public type_writer
		{
			CT_PivotCache* t() { return static_cast<CT_PivotCache*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_PivotCaches_writer : public type_writer
		{
			auto_type_writer< CT_PivotCache_writer > _pivotCache_writer;
			CT_PivotCaches* t() { return static_cast<CT_PivotCaches*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_SmartTagPr_writer : public type_writer
		{
			CT_SmartTagPr* t() { return static_cast<CT_SmartTagPr*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_SmartTagType_writer : public type_writer
		{
			CT_SmartTagType* t() { return static_cast<CT_SmartTagType*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_SmartTagTypes_writer : public type_writer
		{
			auto_type_writer< CT_SmartTagType_writer > _smartTagType_writer;
			CT_SmartTagTypes* t() { return static_cast<CT_SmartTagTypes*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_WebPublishing_writer : public type_writer
		{
			CT_WebPublishing* t() { return static_cast<CT_WebPublishing*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_FileRecoveryPr_writer : public type_writer
		{
			CT_FileRecoveryPr* t() { return static_cast<CT_FileRecoveryPr*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_WebPublishObject_writer : public type_writer
		{
			CT_WebPublishObject* t() { return static_cast<CT_WebPublishObject*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_WebPublishObjects_writer : public type_writer
		{
			auto_type_writer< CT_WebPublishObject_writer > _webPublishObject_writer;
			CT_WebPublishObjects* t() { return static_cast<CT_WebPublishObjects*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Workbook_writer : public type_writer
		{
			auto_type_writer< CT_FileVersion_writer > _fileVersion_writer;
			auto_type_writer< CT_FileSharing_writer > _fileSharing_writer;
			auto_type_writer< CT_WorkbookPr_writer > _workbookPr_writer;
			auto_type_writer< CT_WorkbookProtection_writer > _workbookProtection_writer;
			auto_type_writer< CT_BookViews_writer > _bookViews_writer;
			auto_type_writer< CT_Sheets_writer > _sheets_writer;
			auto_type_writer< CT_FunctionGroups_writer > _functionGroups_writer;
			auto_type_writer< CT_ExternalReferences_writer > _externalReferences_writer;
			auto_type_writer< CT_DefinedNames_writer > _definedNames_writer;
			auto_type_writer< CT_CalcPr_writer > _calcPr_writer;
			auto_type_writer< CT_OleSize_writer > _oleSize_writer;
			auto_type_writer< CT_CustomWorkbookViews_writer > _customWorkbookViews_writer;
			auto_type_writer< CT_PivotCaches_writer > _pivotCaches_writer;
			auto_type_writer< CT_SmartTagPr_writer > _smartTagPr_writer;
			auto_type_writer< CT_SmartTagTypes_writer > _smartTagTypes_writer;
			auto_type_writer< CT_WebPublishing_writer > _webPublishing_writer;
			auto_type_writer< CT_FileRecoveryPr_writer > _fileRecoveryPr_writer;
			auto_type_writer< CT_WebPublishObjects_writer > _webPublishObjects_writer;
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_Workbook* t() { return static_cast<CT_Workbook*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class sml_workbook_writer : public type_writer
		{
			auto_type_writer< CT_Workbook_writer > _workbook_writer;
			sml_workbook* t() { return static_cast<sml_workbook*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

	}
}
#endif

