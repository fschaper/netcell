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

#ifndef SML_WORKBOOK_READERS_HPP
#define SML_WORKBOOK_READERS_HPP

#include "sml-workbook.hpp"
#include "shared-relationshipReference_readers.hpp"
#include "sml-baseTypes_readers.hpp"

namespace spreadsheetml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_SheetBackgroundPicture_reader;
		class CT_FileVersion_reader;
		class CT_FileSharing_reader;
		class CT_WorkbookPr_reader;
		class CT_WorkbookProtection_reader;
		class CT_BookView_reader;
		class CT_BookViews_reader;
		class CT_Sheet_reader;
		class CT_Sheets_reader;
		class CT_FunctionGroup_reader;
		class CT_FunctionGroups_reader;
		class CT_ExternalReference_reader;
		class CT_ExternalReferences_reader;
		class CT_DefinedName_reader;
		class CT_DefinedNames_reader;
		class CT_CalcPr_reader;
		class CT_OleSize_reader;
		class CT_CustomWorkbookView_reader;
		class CT_CustomWorkbookViews_reader;
		class CT_PivotCache_reader;
		class CT_PivotCaches_reader;
		class CT_SmartTagPr_reader;
		class CT_SmartTagType_reader;
		class CT_SmartTagTypes_reader;
		class CT_WebPublishing_reader;
		class CT_FileRecoveryPr_reader;
		class CT_WebPublishObject_reader;
		class CT_WebPublishObjects_reader;
		class CT_Workbook_reader;
		class sml_workbook_reader;

		class CT_SheetBackgroundPicture_reader : public type_reader
		{
		protected:
			CT_SheetBackgroundPicture* t() { return static_cast<CT_SheetBackgroundPicture*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_FileVersion_reader : public type_reader
		{
		protected:
			CT_FileVersion* t() { return static_cast<CT_FileVersion*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_FileSharing_reader : public type_reader
		{
		protected:
			CT_FileSharing* t() { return static_cast<CT_FileSharing*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_WorkbookPr_reader : public type_reader
		{
		protected:
			CT_WorkbookPr* t() { return static_cast<CT_WorkbookPr*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_WorkbookProtection_reader : public type_reader
		{
		protected:
			CT_WorkbookProtection* t() { return static_cast<CT_WorkbookProtection*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_BookView_reader : public type_reader
		{
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_BookView* t() { return static_cast<CT_BookView*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_BookViews_reader : public type_reader
		{
			auto_type_reader< CT_BookView_reader > _workbookView_reader;
		protected:
			CT_BookViews* t() { return static_cast<CT_BookViews*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_Sheet_reader : public type_reader
		{
		protected:
			CT_Sheet* t() { return static_cast<CT_Sheet*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Sheets_reader : public type_reader
		{
			auto_type_reader< CT_Sheet_reader > _sheet_reader;
		protected:
			CT_Sheets* t() { return static_cast<CT_Sheets*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_FunctionGroup_reader : public type_reader
		{
		protected:
			CT_FunctionGroup* t() { return static_cast<CT_FunctionGroup*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_FunctionGroups_reader : public type_reader
		{
			auto_type_reader< CT_FunctionGroup_reader > _functionGroup_reader;
		protected:
			CT_FunctionGroups* t() { return static_cast<CT_FunctionGroups*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_ExternalReference_reader : public type_reader
		{
		protected:
			CT_ExternalReference* t() { return static_cast<CT_ExternalReference*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_ExternalReferences_reader : public type_reader
		{
			auto_type_reader< CT_ExternalReference_reader > _externalReference_reader;
		protected:
			CT_ExternalReferences* t() { return static_cast<CT_ExternalReferences*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_DefinedName_reader : public ST_Formula_reader
		{
		protected:
			CT_DefinedName* t() { return static_cast<CT_DefinedName*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_DefinedNames_reader : public type_reader
		{
			auto_type_reader< CT_DefinedName_reader > _definedName_reader;
		protected:
			CT_DefinedNames* t() { return static_cast<CT_DefinedNames*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_CalcPr_reader : public type_reader
		{
		protected:
			CT_CalcPr* t() { return static_cast<CT_CalcPr*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_OleSize_reader : public type_reader
		{
		protected:
			CT_OleSize* t() { return static_cast<CT_OleSize*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_CustomWorkbookView_reader : public type_reader
		{
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_CustomWorkbookView* t() { return static_cast<CT_CustomWorkbookView*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_CustomWorkbookViews_reader : public type_reader
		{
			auto_type_reader< CT_CustomWorkbookView_reader > _customWorkbookView_reader;
		protected:
			CT_CustomWorkbookViews* t() { return static_cast<CT_CustomWorkbookViews*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_PivotCache_reader : public type_reader
		{
		protected:
			CT_PivotCache* t() { return static_cast<CT_PivotCache*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_PivotCaches_reader : public type_reader
		{
			auto_type_reader< CT_PivotCache_reader > _pivotCache_reader;
		protected:
			CT_PivotCaches* t() { return static_cast<CT_PivotCaches*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_SmartTagPr_reader : public type_reader
		{
		protected:
			CT_SmartTagPr* t() { return static_cast<CT_SmartTagPr*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_SmartTagType_reader : public type_reader
		{
		protected:
			CT_SmartTagType* t() { return static_cast<CT_SmartTagType*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_SmartTagTypes_reader : public type_reader
		{
			auto_type_reader< CT_SmartTagType_reader > _smartTagType_reader;
		protected:
			CT_SmartTagTypes* t() { return static_cast<CT_SmartTagTypes*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_WebPublishing_reader : public type_reader
		{
		protected:
			CT_WebPublishing* t() { return static_cast<CT_WebPublishing*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_FileRecoveryPr_reader : public type_reader
		{
		protected:
			CT_FileRecoveryPr* t() { return static_cast<CT_FileRecoveryPr*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_WebPublishObject_reader : public type_reader
		{
		protected:
			CT_WebPublishObject* t() { return static_cast<CT_WebPublishObject*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_WebPublishObjects_reader : public type_reader
		{
			auto_type_reader< CT_WebPublishObject_reader > _webPublishObject_reader;
		protected:
			CT_WebPublishObjects* t() { return static_cast<CT_WebPublishObjects*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Workbook_reader : public type_reader
		{
			auto_type_reader< CT_FileVersion_reader > _fileVersion_reader;
			auto_type_reader< CT_FileSharing_reader > _fileSharing_reader;
			auto_type_reader< CT_WorkbookPr_reader > _workbookPr_reader;
			auto_type_reader< CT_WorkbookProtection_reader > _workbookProtection_reader;
			auto_type_reader< CT_BookViews_reader > _bookViews_reader;
			auto_type_reader< CT_Sheets_reader > _sheets_reader;
			auto_type_reader< CT_FunctionGroups_reader > _functionGroups_reader;
			auto_type_reader< CT_ExternalReferences_reader > _externalReferences_reader;
			auto_type_reader< CT_DefinedNames_reader > _definedNames_reader;
			auto_type_reader< CT_CalcPr_reader > _calcPr_reader;
			auto_type_reader< CT_OleSize_reader > _oleSize_reader;
			auto_type_reader< CT_CustomWorkbookViews_reader > _customWorkbookViews_reader;
			auto_type_reader< CT_PivotCaches_reader > _pivotCaches_reader;
			auto_type_reader< CT_SmartTagPr_reader > _smartTagPr_reader;
			auto_type_reader< CT_SmartTagTypes_reader > _smartTagTypes_reader;
			auto_type_reader< CT_WebPublishing_reader > _webPublishing_reader;
			auto_type_reader< CT_FileRecoveryPr_reader > _fileRecoveryPr_reader;
			auto_type_reader< CT_WebPublishObjects_reader > _webPublishObjects_reader;
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_Workbook* t() { return static_cast<CT_Workbook*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class sml_workbook_reader : public type_reader
		{
			auto_type_reader< CT_Workbook_reader > _workbook_reader;
		protected:
			sml_workbook* t() { return static_cast<sml_workbook*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

	}
}
#endif

