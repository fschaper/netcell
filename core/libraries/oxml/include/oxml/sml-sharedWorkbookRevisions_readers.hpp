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

#ifndef SML_SHAREDWORKBOOKREVISIONS_READERS_HPP
#define SML_SHAREDWORKBOOKREVISIONS_READERS_HPP

#include "sml-sharedWorkbookRevisions.hpp"
#include "sml-baseTypes_readers.hpp"
#include "shared-relationshipReference_readers.hpp"
#include "sml-sheet_readers.hpp"
#include "sml-styles_readers.hpp"

namespace spreadsheetml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_SheetId_reader;
		class CT_SheetIdMap_reader;
		class CT_Reviewed_reader;
		class CT_ReviewedRevisions_reader;
		class CT_RevisionHeader_reader;
		class CT_RevisionHeaders_reader;
		class CT_UndoInfo_reader;
		class CT_RevisionCellChange_reader;
		class CT_RevisionFormatting_reader;
		class CT_RevisionRowColumn_reader;
		class CT_RevisionMove_reader;
		class CT_RevisionCustomView_reader;
		class CT_RevisionSheetRename_reader;
		class CT_RevisionInsertSheet_reader;
		class CT_RevisionAutoFormatting_reader;
		class CT_RevisionDefinedName_reader;
		class CT_RevisionComment_reader;
		class CT_RevisionQueryTableField_reader;
		class CT_RevisionConflict_reader;
		class CT_Revisions_reader;
		class sml_sharedWorkbookRevisions_reader;

		class CT_SheetId_reader : public type_reader
		{
		protected:
			CT_SheetId* t() { return static_cast<CT_SheetId*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_SheetIdMap_reader : public type_reader
		{
			auto_type_reader< CT_SheetId_reader > _sheetId_reader;
		protected:
			CT_SheetIdMap* t() { return static_cast<CT_SheetIdMap*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Reviewed_reader : public type_reader
		{
		protected:
			CT_Reviewed* t() { return static_cast<CT_Reviewed*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_ReviewedRevisions_reader : public type_reader
		{
			auto_type_reader< CT_Reviewed_reader > _reviewed_reader;
		protected:
			CT_ReviewedRevisions* t() { return static_cast<CT_ReviewedRevisions*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_RevisionHeader_reader : public type_reader
		{
			auto_type_reader< CT_SheetIdMap_reader > _sheetIdMap_reader;
			auto_type_reader< CT_ReviewedRevisions_reader > _reviewedList_reader;
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_RevisionHeader* t() { return static_cast<CT_RevisionHeader*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_RevisionHeaders_reader : public type_reader
		{
			auto_type_reader< CT_RevisionHeader_reader > _header_reader;
		protected:
			CT_RevisionHeaders* t() { return static_cast<CT_RevisionHeaders*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_UndoInfo_reader : public type_reader
		{
		protected:
			CT_UndoInfo* t() { return static_cast<CT_UndoInfo*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_RevisionCellChange_reader : public type_reader
		{
			auto_type_reader< CT_Cell_reader > _oc_reader;
			auto_type_reader< CT_Cell_reader > _nc_reader;
			auto_type_reader< CT_Dxf_reader > _odxf_reader;
			auto_type_reader< CT_Dxf_reader > _ndxf_reader;
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_RevisionCellChange* t() { return static_cast<CT_RevisionCellChange*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_RevisionFormatting_reader : public type_reader
		{
			auto_type_reader< CT_Dxf_reader > _dxf_reader;
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_RevisionFormatting* t() { return static_cast<CT_RevisionFormatting*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_RevisionRowColumn_reader : public type_reader
		{
			auto_type_reader< CT_UndoInfo_reader > _undo_reader;
			auto_type_reader< CT_RevisionCellChange_reader > _rcc_reader;
			auto_type_reader< CT_RevisionFormatting_reader > _rfmt_reader;
		protected:
			CT_RevisionRowColumn* t() { return static_cast<CT_RevisionRowColumn*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_RevisionMove_reader : public type_reader
		{
			auto_type_reader< CT_UndoInfo_reader > _undo_reader;
			auto_type_reader< CT_RevisionCellChange_reader > _rcc_reader;
			auto_type_reader< CT_RevisionFormatting_reader > _rfmt_reader;
		protected:
			CT_RevisionMove* t() { return static_cast<CT_RevisionMove*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_RevisionCustomView_reader : public type_reader
		{
		protected:
			CT_RevisionCustomView* t() { return static_cast<CT_RevisionCustomView*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_RevisionSheetRename_reader : public type_reader
		{
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_RevisionSheetRename* t() { return static_cast<CT_RevisionSheetRename*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_RevisionInsertSheet_reader : public type_reader
		{
		protected:
			CT_RevisionInsertSheet* t() { return static_cast<CT_RevisionInsertSheet*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_RevisionAutoFormatting_reader : public type_reader
		{
		protected:
			CT_RevisionAutoFormatting* t() { return static_cast<CT_RevisionAutoFormatting*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_RevisionDefinedName_reader : public type_reader
		{
			auto_type_reader< ST_Formula_reader > _formula_reader;
			auto_type_reader< ST_Formula_reader > _oldFormula_reader;
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_RevisionDefinedName* t() { return static_cast<CT_RevisionDefinedName*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_RevisionComment_reader : public type_reader
		{
		protected:
			CT_RevisionComment* t() { return static_cast<CT_RevisionComment*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_RevisionQueryTableField_reader : public type_reader
		{
		protected:
			CT_RevisionQueryTableField* t() { return static_cast<CT_RevisionQueryTableField*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_RevisionConflict_reader : public type_reader
		{
		protected:
			CT_RevisionConflict* t() { return static_cast<CT_RevisionConflict*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Revisions_reader : public type_reader
		{
			auto_type_reader< CT_RevisionRowColumn_reader > _rrc_reader;
			auto_type_reader< CT_RevisionMove_reader > _rm_reader;
			auto_type_reader< CT_RevisionCustomView_reader > _rcv_reader;
			auto_type_reader< CT_RevisionSheetRename_reader > _rsnm_reader;
			auto_type_reader< CT_RevisionInsertSheet_reader > _ris_reader;
			auto_type_reader< CT_RevisionCellChange_reader > _rcc_reader;
			auto_type_reader< CT_RevisionFormatting_reader > _rfmt_reader;
			auto_type_reader< CT_RevisionAutoFormatting_reader > _raf_reader;
			auto_type_reader< CT_RevisionDefinedName_reader > _rdn_reader;
			auto_type_reader< CT_RevisionComment_reader > _rcmt_reader;
			auto_type_reader< CT_RevisionQueryTableField_reader > _rqt_reader;
			auto_type_reader< CT_RevisionConflict_reader > _rcft_reader;
		protected:
			CT_Revisions* t() { return static_cast<CT_Revisions*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class sml_sharedWorkbookRevisions_reader : public type_reader
		{
			auto_type_reader< CT_RevisionHeaders_reader > _headers_reader;
			auto_type_reader< CT_Revisions_reader > _revisions_reader;
		protected:
			sml_sharedWorkbookRevisions* t() { return static_cast<sml_sharedWorkbookRevisions*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

	}
}
#endif

