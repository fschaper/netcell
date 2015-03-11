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


#include "sml-sharedWorkbookRevisions_readers.hpp"
#include "sml-sharedWorkbookRevisions_literals.hpp"
#include <xio/xml/binding/driver.hpp>

namespace spreadsheetml
{
	namespace xio
	{
		void CT_SheetId_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_val_literal))
			{
				driver()->context()->parse(value, t()->val);
				return;
			}
		}
		void CT_SheetIdMap_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_sheetId_literal))
			{
				t()->sheetId.resize(t()->sheetId.size()+1);
				driver()->push(localname, _sheetId_reader.get_reader(&t()->sheetId.back()));
				return;
			}
		}
		void CT_SheetIdMap_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
		}
		void CT_Reviewed_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_rId_literal))
			{
				driver()->context()->parse(value, t()->rId);
				return;
			}
		}
		void CT_ReviewedRevisions_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_reviewed_literal))
			{
				t()->reviewed.resize(t()->reviewed.size()+1);
				driver()->push(localname, _reviewed_reader.get_reader(&t()->reviewed.back()));
				return;
			}
		}
		void CT_ReviewedRevisions_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
		}
		void CT_RevisionHeader_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_sheetIdMap_literal))
			{
				driver()->push(localname, _sheetIdMap_reader.get_reader(&t()->sheetIdMap));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_reviewedList_literal))
			{
				driver()->push(localname, _reviewedList_reader.get_reader(&t()->reviewedList.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_RevisionHeader_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_guid_literal))
			{
				driver()->context()->parse(value, t()->guid);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_dateTime_literal))
			{
				driver()->context()->parse(value, t()->dateTime);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_maxSheetId_literal))
			{
				driver()->context()->parse(value, t()->maxSheetId);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_userName_literal))
			{
				driver()->context()->parse(value, t()->userName);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_id_literal))
			{
				driver()->context()->parse(value, t()->id);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_minRId_literal))
			{
				driver()->context()->parse(value, t()->minRId.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_maxRId_literal))
			{
				driver()->context()->parse(value, t()->maxRId.getset());
				return;
			}
		}
		void CT_RevisionHeaders_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_header_literal))
			{
				t()->header.resize(t()->header.size()+1);
				driver()->push(localname, _header_reader.get_reader(&t()->header.back()));
				return;
			}
		}
		void CT_RevisionHeaders_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_guid_literal))
			{
				driver()->context()->parse(value, t()->guid);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_lastGuid_literal))
			{
				driver()->context()->parse(value, t()->lastGuid.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_shared_literal))
			{
				driver()->context()->parse(value, t()->shared);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_diskRevisions_literal))
			{
				driver()->context()->parse(value, t()->diskRevisions);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_history_literal))
			{
				driver()->context()->parse(value, t()->history);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_trackRevisions_literal))
			{
				driver()->context()->parse(value, t()->trackRevisions);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_exclusive_literal))
			{
				driver()->context()->parse(value, t()->exclusive);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_revisionId_literal))
			{
				driver()->context()->parse(value, t()->revisionId);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_version_literal))
			{
				driver()->context()->parse(value, t()->version);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_keepChangeHistory_literal))
			{
				driver()->context()->parse(value, t()->keepChangeHistory);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions__protected__literal))
			{
				driver()->context()->parse(value, t()->_protected_);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_preserveHistory_literal))
			{
				driver()->context()->parse(value, t()->preserveHistory);
				return;
			}
		}
		void CT_UndoInfo_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_index_literal))
			{
				driver()->context()->parse(value, t()->index);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_exp_literal))
			{
				driver()->context()->parse(value, t()->exp);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_ref3D_literal))
			{
				driver()->context()->parse(value, t()->ref3D);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_array_literal))
			{
				driver()->context()->parse(value, t()->array);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_v_literal))
			{
				driver()->context()->parse(value, t()->v);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_nf_literal))
			{
				driver()->context()->parse(value, t()->nf);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_cs_literal))
			{
				driver()->context()->parse(value, t()->cs);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_dr_literal))
			{
				driver()->context()->parse(value, t()->dr);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_dn_literal))
			{
				driver()->context()->parse(value, t()->dn.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_r_literal))
			{
				driver()->context()->parse(value, t()->r.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_sId_literal))
			{
				driver()->context()->parse(value, t()->sId.getset());
				return;
			}
		}
		void CT_RevisionCellChange_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_oc_literal))
			{
				driver()->push(localname, _oc_reader.get_reader(&t()->oc.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_nc_literal))
			{
				driver()->push(localname, _nc_reader.get_reader(&t()->nc));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_odxf_literal))
			{
				driver()->push(localname, _odxf_reader.get_reader(&t()->odxf.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_ndxf_literal))
			{
				driver()->push(localname, _ndxf_reader.get_reader(&t()->ndxf.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_RevisionCellChange_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_rId_literal))
			{
				driver()->context()->parse(value, t()->rId);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_ua_literal))
			{
				driver()->context()->parse(value, t()->ua);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_ra_literal))
			{
				driver()->context()->parse(value, t()->ra);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_sId_literal))
			{
				driver()->context()->parse(value, t()->sId);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_odxf_literal))
			{
				driver()->context()->parse(value, t()->odxf_attr);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_xfDxf_literal))
			{
				driver()->context()->parse(value, t()->xfDxf);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_s_literal))
			{
				driver()->context()->parse(value, t()->s);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_dxf_literal))
			{
				driver()->context()->parse(value, t()->dxf);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_numFmtId_literal))
			{
				driver()->context()->parse(value, t()->numFmtId.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_quotePrefix_literal))
			{
				driver()->context()->parse(value, t()->quotePrefix);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_oldQuotePrefix_literal))
			{
				driver()->context()->parse(value, t()->oldQuotePrefix);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_ph_literal))
			{
				driver()->context()->parse(value, t()->ph);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_oldPh_literal))
			{
				driver()->context()->parse(value, t()->oldPh);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_endOfListFormulaUpdate_literal))
			{
				driver()->context()->parse(value, t()->endOfListFormulaUpdate);
				return;
			}
		}
		void CT_RevisionFormatting_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_dxf_literal))
			{
				driver()->push(localname, _dxf_reader.get_reader(&t()->dxf.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_RevisionFormatting_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_sheetId_literal))
			{
				driver()->context()->parse(value, t()->sheetId);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_xfDxf_literal))
			{
				driver()->context()->parse(value, t()->xfDxf);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_s_literal))
			{
				driver()->context()->parse(value, t()->s);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_sqref_literal))
			{
				driver()->context()->parse(value, t()->sqref);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_start_literal))
			{
				driver()->context()->parse(value, t()->start.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_length_literal))
			{
				driver()->context()->parse(value, t()->length.getset());
				return;
			}
		}
		void CT_RevisionRowColumn_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_undo_literal))
			{
				t()->undo.getset().resize(t()->undo.getset().size()+1);
				driver()->push(localname, _undo_reader.get_reader(&t()->undo.getset().back()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_rcc_literal))
			{
				t()->rcc.getset().resize(t()->rcc.getset().size()+1);
				driver()->push(localname, _rcc_reader.get_reader(&t()->rcc.getset().back()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_rfmt_literal))
			{
				t()->rfmt.getset().resize(t()->rfmt.getset().size()+1);
				driver()->push(localname, _rfmt_reader.get_reader(&t()->rfmt.getset().back()));
				return;
			}
		}
		void CT_RevisionRowColumn_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_rId_literal))
			{
				driver()->context()->parse(value, t()->rId);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_ua_literal))
			{
				driver()->context()->parse(value, t()->ua);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_ra_literal))
			{
				driver()->context()->parse(value, t()->ra);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_sId_literal))
			{
				driver()->context()->parse(value, t()->sId);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_eol_literal))
			{
				driver()->context()->parse(value, t()->eol);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_ref_literal))
			{
				driver()->context()->parse(value, t()->ref);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_action_literal))
			{
				driver()->context()->parse(value, t()->action);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_edge_literal))
			{
				driver()->context()->parse(value, t()->edge);
				return;
			}
		}
		void CT_RevisionMove_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_undo_literal))
			{
				t()->undo.getset().resize(t()->undo.getset().size()+1);
				driver()->push(localname, _undo_reader.get_reader(&t()->undo.getset().back()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_rcc_literal))
			{
				t()->rcc.getset().resize(t()->rcc.getset().size()+1);
				driver()->push(localname, _rcc_reader.get_reader(&t()->rcc.getset().back()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_rfmt_literal))
			{
				t()->rfmt.getset().resize(t()->rfmt.getset().size()+1);
				driver()->push(localname, _rfmt_reader.get_reader(&t()->rfmt.getset().back()));
				return;
			}
		}
		void CT_RevisionMove_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_rId_literal))
			{
				driver()->context()->parse(value, t()->rId);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_ua_literal))
			{
				driver()->context()->parse(value, t()->ua);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_ra_literal))
			{
				driver()->context()->parse(value, t()->ra);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_sheetId_literal))
			{
				driver()->context()->parse(value, t()->sheetId);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_source_literal))
			{
				driver()->context()->parse(value, t()->source);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_destination_literal))
			{
				driver()->context()->parse(value, t()->destination);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_sourceSheetId_literal))
			{
				driver()->context()->parse(value, t()->sourceSheetId);
				return;
			}
		}
		void CT_RevisionCustomView_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_guid_literal))
			{
				driver()->context()->parse(value, t()->guid);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_action_literal))
			{
				driver()->context()->parse(value, t()->action);
				return;
			}
		}
		void CT_RevisionSheetRename_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_RevisionSheetRename_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_rId_literal))
			{
				driver()->context()->parse(value, t()->rId);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_ua_literal))
			{
				driver()->context()->parse(value, t()->ua);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_ra_literal))
			{
				driver()->context()->parse(value, t()->ra);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_sheetId_literal))
			{
				driver()->context()->parse(value, t()->sheetId);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_oldName_literal))
			{
				driver()->context()->parse(value, t()->oldName);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_newName_literal))
			{
				driver()->context()->parse(value, t()->newName);
				return;
			}
		}
		void CT_RevisionInsertSheet_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_rId_literal))
			{
				driver()->context()->parse(value, t()->rId);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_ua_literal))
			{
				driver()->context()->parse(value, t()->ua);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_ra_literal))
			{
				driver()->context()->parse(value, t()->ra);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_sheetId_literal))
			{
				driver()->context()->parse(value, t()->sheetId);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_name_literal))
			{
				driver()->context()->parse(value, t()->name);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_sheetPosition_literal))
			{
				driver()->context()->parse(value, t()->sheetPosition);
				return;
			}
		}
		void CT_RevisionAutoFormatting_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_sheetId_literal))
			{
				driver()->context()->parse(value, t()->sheetId);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_autoFormatId_literal))
			{
				driver()->context()->parse(value, t()->autoFormatId.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_applyNumberFormats_literal))
			{
				driver()->context()->parse(value, t()->applyNumberFormats.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_applyBorderFormats_literal))
			{
				driver()->context()->parse(value, t()->applyBorderFormats.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_applyFontFormats_literal))
			{
				driver()->context()->parse(value, t()->applyFontFormats.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_applyPatternFormats_literal))
			{
				driver()->context()->parse(value, t()->applyPatternFormats.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_applyAlignmentFormats_literal))
			{
				driver()->context()->parse(value, t()->applyAlignmentFormats.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_applyWidthHeightFormats_literal))
			{
				driver()->context()->parse(value, t()->applyWidthHeightFormats.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_ref_literal))
			{
				driver()->context()->parse(value, t()->ref);
				return;
			}
		}
		void CT_RevisionDefinedName_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_formula_literal))
			{
				driver()->push(localname, _formula_reader.get_reader(&t()->formula.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_oldFormula_literal))
			{
				driver()->push(localname, _oldFormula_reader.get_reader(&t()->oldFormula.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_RevisionDefinedName_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_rId_literal))
			{
				driver()->context()->parse(value, t()->rId);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_ua_literal))
			{
				driver()->context()->parse(value, t()->ua);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_ra_literal))
			{
				driver()->context()->parse(value, t()->ra);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_localSheetId_literal))
			{
				driver()->context()->parse(value, t()->localSheetId.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_customView_literal))
			{
				driver()->context()->parse(value, t()->customView);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_name_literal))
			{
				driver()->context()->parse(value, t()->name);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_function_literal))
			{
				driver()->context()->parse(value, t()->function);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_oldFunction_literal))
			{
				driver()->context()->parse(value, t()->oldFunction);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_functionGroupId_literal))
			{
				driver()->context()->parse(value, t()->functionGroupId.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_oldFunctionGroupId_literal))
			{
				driver()->context()->parse(value, t()->oldFunctionGroupId.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_shortcutKey_literal))
			{
				driver()->context()->parse(value, t()->shortcutKey.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_oldShortcutKey_literal))
			{
				driver()->context()->parse(value, t()->oldShortcutKey.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_hidden_literal))
			{
				driver()->context()->parse(value, t()->hidden);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_oldHidden_literal))
			{
				driver()->context()->parse(value, t()->oldHidden);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_customMenu_literal))
			{
				driver()->context()->parse(value, t()->customMenu.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_oldCustomMenu_literal))
			{
				driver()->context()->parse(value, t()->oldCustomMenu.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_description_literal))
			{
				driver()->context()->parse(value, t()->description.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_oldDescription_literal))
			{
				driver()->context()->parse(value, t()->oldDescription.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_help_literal))
			{
				driver()->context()->parse(value, t()->help.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_oldHelp_literal))
			{
				driver()->context()->parse(value, t()->oldHelp.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_statusBar_literal))
			{
				driver()->context()->parse(value, t()->statusBar.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_oldStatusBar_literal))
			{
				driver()->context()->parse(value, t()->oldStatusBar.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_comment_literal))
			{
				driver()->context()->parse(value, t()->comment.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_oldComment_literal))
			{
				driver()->context()->parse(value, t()->oldComment.getset());
				return;
			}
		}
		void CT_RevisionComment_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_sheetId_literal))
			{
				driver()->context()->parse(value, t()->sheetId);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_cell_literal))
			{
				driver()->context()->parse(value, t()->cell);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_guid_literal))
			{
				driver()->context()->parse(value, t()->guid);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_action_literal))
			{
				driver()->context()->parse(value, t()->action);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_alwaysShow_literal))
			{
				driver()->context()->parse(value, t()->alwaysShow);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_old_literal))
			{
				driver()->context()->parse(value, t()->old);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_hiddenRow_literal))
			{
				driver()->context()->parse(value, t()->hiddenRow);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_hiddenColumn_literal))
			{
				driver()->context()->parse(value, t()->hiddenColumn);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_author_literal))
			{
				driver()->context()->parse(value, t()->author);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_oldLength_literal))
			{
				driver()->context()->parse(value, t()->oldLength);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_newLength_literal))
			{
				driver()->context()->parse(value, t()->newLength);
				return;
			}
		}
		void CT_RevisionQueryTableField_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_sheetId_literal))
			{
				driver()->context()->parse(value, t()->sheetId);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_ref_literal))
			{
				driver()->context()->parse(value, t()->ref);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_fieldId_literal))
			{
				driver()->context()->parse(value, t()->fieldId);
				return;
			}
		}
		void CT_RevisionConflict_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_rId_literal))
			{
				driver()->context()->parse(value, t()->rId);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_ua_literal))
			{
				driver()->context()->parse(value, t()->ua);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_ra_literal))
			{
				driver()->context()->parse(value, t()->ra);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_sheetId_literal))
			{
				driver()->context()->parse(value, t()->sheetId.getset());
				return;
			}
		}
		void CT_Revisions_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_rrc_literal))
			{
				t()->rrc.getset().resize(t()->rrc.getset().size()+1);
				driver()->push(localname, _rrc_reader.get_reader(&t()->rrc.getset().back()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_rm_literal))
			{
				t()->rm.getset().resize(t()->rm.getset().size()+1);
				driver()->push(localname, _rm_reader.get_reader(&t()->rm.getset().back()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_rcv_literal))
			{
				t()->rcv.getset().resize(t()->rcv.getset().size()+1);
				driver()->push(localname, _rcv_reader.get_reader(&t()->rcv.getset().back()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_rsnm_literal))
			{
				t()->rsnm.getset().resize(t()->rsnm.getset().size()+1);
				driver()->push(localname, _rsnm_reader.get_reader(&t()->rsnm.getset().back()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_ris_literal))
			{
				t()->ris.getset().resize(t()->ris.getset().size()+1);
				driver()->push(localname, _ris_reader.get_reader(&t()->ris.getset().back()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_rcc_literal))
			{
				t()->rcc.getset().resize(t()->rcc.getset().size()+1);
				driver()->push(localname, _rcc_reader.get_reader(&t()->rcc.getset().back()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_rfmt_literal))
			{
				t()->rfmt.getset().resize(t()->rfmt.getset().size()+1);
				driver()->push(localname, _rfmt_reader.get_reader(&t()->rfmt.getset().back()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_raf_literal))
			{
				t()->raf.getset().resize(t()->raf.getset().size()+1);
				driver()->push(localname, _raf_reader.get_reader(&t()->raf.getset().back()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_rdn_literal))
			{
				t()->rdn.getset().resize(t()->rdn.getset().size()+1);
				driver()->push(localname, _rdn_reader.get_reader(&t()->rdn.getset().back()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_rcmt_literal))
			{
				t()->rcmt.getset().resize(t()->rcmt.getset().size()+1);
				driver()->push(localname, _rcmt_reader.get_reader(&t()->rcmt.getset().back()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_rqt_literal))
			{
				t()->rqt.getset().resize(t()->rqt.getset().size()+1);
				driver()->push(localname, _rqt_reader.get_reader(&t()->rqt.getset().back()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_rcft_literal))
			{
				t()->rcft.getset().resize(t()->rcft.getset().size()+1);
				driver()->push(localname, _rcft_reader.get_reader(&t()->rcft.getset().back()));
				return;
			}
		}
		void sml_sharedWorkbookRevisions_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_headers_literal))
			{
				driver()->push(localname, _headers_reader.get_reader(&t()->headers.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookRevisions_revisions_literal))
			{
				driver()->push(localname, _revisions_reader.get_reader(&t()->revisions.getset()));
				return;
			}
		}
	}
}
