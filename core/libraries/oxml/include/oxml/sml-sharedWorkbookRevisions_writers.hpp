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

#ifndef SML_SHAREDWORKBOOKREVISIONS_WRITERS_HPP
#define SML_SHAREDWORKBOOKREVISIONS_WRITERS_HPP

#include "sml-sharedWorkbookRevisions.hpp"
#include "sml-sharedWorkbookRevisions_literals.hpp"
#include "sml-baseTypes_writers.hpp"
#include "shared-relationshipReference_writers.hpp"
#include "sml-sheet_writers.hpp"
#include "sml-styles_writers.hpp"

namespace spreadsheetml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_SheetId_writer;
		class CT_SheetIdMap_writer;
		class CT_Reviewed_writer;
		class CT_ReviewedRevisions_writer;
		class CT_RevisionHeader_writer;
		class CT_RevisionHeaders_writer;
		class CT_UndoInfo_writer;
		class CT_RevisionCellChange_writer;
		class CT_RevisionFormatting_writer;
		class CT_RevisionRowColumn_writer;
		class CT_RevisionMove_writer;
		class CT_RevisionCustomView_writer;
		class CT_RevisionSheetRename_writer;
		class CT_RevisionInsertSheet_writer;
		class CT_RevisionAutoFormatting_writer;
		class CT_RevisionDefinedName_writer;
		class CT_RevisionComment_writer;
		class CT_RevisionQueryTableField_writer;
		class CT_RevisionConflict_writer;
		class CT_Revisions_writer;
		class sml_sharedWorkbookRevisions_writer;

		class CT_SheetId_writer : public type_writer
		{
			CT_SheetId* t() { return static_cast<CT_SheetId*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_SheetIdMap_writer : public type_writer
		{
			auto_type_writer< CT_SheetId_writer > _sheetId_writer;
			CT_SheetIdMap* t() { return static_cast<CT_SheetIdMap*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Reviewed_writer : public type_writer
		{
			CT_Reviewed* t() { return static_cast<CT_Reviewed*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_ReviewedRevisions_writer : public type_writer
		{
			auto_type_writer< CT_Reviewed_writer > _reviewed_writer;
			CT_ReviewedRevisions* t() { return static_cast<CT_ReviewedRevisions*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_RevisionHeader_writer : public type_writer
		{
			auto_type_writer< CT_SheetIdMap_writer > _sheetIdMap_writer;
			auto_type_writer< CT_ReviewedRevisions_writer > _reviewedList_writer;
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_RevisionHeader* t() { return static_cast<CT_RevisionHeader*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_RevisionHeaders_writer : public type_writer
		{
			auto_type_writer< CT_RevisionHeader_writer > _header_writer;
			CT_RevisionHeaders* t() { return static_cast<CT_RevisionHeaders*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_UndoInfo_writer : public type_writer
		{
			CT_UndoInfo* t() { return static_cast<CT_UndoInfo*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_RevisionCellChange_writer : public type_writer
		{
			auto_type_writer< CT_Cell_writer > _oc_writer;
			auto_type_writer< CT_Cell_writer > _nc_writer;
			auto_type_writer< CT_Dxf_writer > _odxf_writer;
			auto_type_writer< CT_Dxf_writer > _ndxf_writer;
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_RevisionCellChange* t() { return static_cast<CT_RevisionCellChange*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_RevisionFormatting_writer : public type_writer
		{
			auto_type_writer< CT_Dxf_writer > _dxf_writer;
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_RevisionFormatting* t() { return static_cast<CT_RevisionFormatting*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_RevisionRowColumn_writer : public type_writer
		{
			auto_type_writer< CT_UndoInfo_writer > _undo_writer;
			auto_type_writer< CT_RevisionCellChange_writer > _rcc_writer;
			auto_type_writer< CT_RevisionFormatting_writer > _rfmt_writer;
			CT_RevisionRowColumn* t() { return static_cast<CT_RevisionRowColumn*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_RevisionMove_writer : public type_writer
		{
			auto_type_writer< CT_UndoInfo_writer > _undo_writer;
			auto_type_writer< CT_RevisionCellChange_writer > _rcc_writer;
			auto_type_writer< CT_RevisionFormatting_writer > _rfmt_writer;
			CT_RevisionMove* t() { return static_cast<CT_RevisionMove*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_RevisionCustomView_writer : public type_writer
		{
			CT_RevisionCustomView* t() { return static_cast<CT_RevisionCustomView*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_RevisionSheetRename_writer : public type_writer
		{
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_RevisionSheetRename* t() { return static_cast<CT_RevisionSheetRename*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_RevisionInsertSheet_writer : public type_writer
		{
			CT_RevisionInsertSheet* t() { return static_cast<CT_RevisionInsertSheet*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_RevisionAutoFormatting_writer : public type_writer
		{
			CT_RevisionAutoFormatting* t() { return static_cast<CT_RevisionAutoFormatting*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_RevisionDefinedName_writer : public type_writer
		{
			auto_type_writer< ST_Formula_writer > _formula_writer;
			auto_type_writer< ST_Formula_writer > _oldFormula_writer;
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_RevisionDefinedName* t() { return static_cast<CT_RevisionDefinedName*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_RevisionComment_writer : public type_writer
		{
			CT_RevisionComment* t() { return static_cast<CT_RevisionComment*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_RevisionQueryTableField_writer : public type_writer
		{
			CT_RevisionQueryTableField* t() { return static_cast<CT_RevisionQueryTableField*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_RevisionConflict_writer : public type_writer
		{
			CT_RevisionConflict* t() { return static_cast<CT_RevisionConflict*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Revisions_writer : public type_writer
		{
			auto_type_writer< CT_RevisionRowColumn_writer > _rrc_writer;
			auto_type_writer< CT_RevisionMove_writer > _rm_writer;
			auto_type_writer< CT_RevisionCustomView_writer > _rcv_writer;
			auto_type_writer< CT_RevisionSheetRename_writer > _rsnm_writer;
			auto_type_writer< CT_RevisionInsertSheet_writer > _ris_writer;
			auto_type_writer< CT_RevisionCellChange_writer > _rcc_writer;
			auto_type_writer< CT_RevisionFormatting_writer > _rfmt_writer;
			auto_type_writer< CT_RevisionAutoFormatting_writer > _raf_writer;
			auto_type_writer< CT_RevisionDefinedName_writer > _rdn_writer;
			auto_type_writer< CT_RevisionComment_writer > _rcmt_writer;
			auto_type_writer< CT_RevisionQueryTableField_writer > _rqt_writer;
			auto_type_writer< CT_RevisionConflict_writer > _rcft_writer;
			CT_Revisions* t() { return static_cast<CT_Revisions*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class sml_sharedWorkbookRevisions_writer : public type_writer
		{
			auto_type_writer< CT_RevisionHeaders_writer > _headers_writer;
			auto_type_writer< CT_Revisions_writer > _revisions_writer;
			sml_sharedWorkbookRevisions* t() { return static_cast<sml_sharedWorkbookRevisions*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

	}
}
#endif

