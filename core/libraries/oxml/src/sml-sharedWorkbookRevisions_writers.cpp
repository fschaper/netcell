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


#include "sml-sharedWorkbookRevisions_writers.hpp"
#include "sml-sharedWorkbookRevisions_literals.hpp"

namespace spreadsheetml
{
	namespace xio
	{
		void CT_SheetId_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_sharedWorkbookRevisions_val_literal, context()->serialize(t()->val));
		}

		void CT_SheetIdMap_writer::write_target_to(xml_writer& w) {
			if (t()->count.present())
				w.attribute(0, sml_sharedWorkbookRevisions_count_literal, context()->serialize(t()->count.get()));
			for (size_t sqi = 0; sqi<t()->sheetId.size(); ++sqi) {
				w.start_element(0, sml_sharedWorkbookRevisions_sheetId_literal);
				_sheetId_writer.get_writer(context(), &t()->sheetId[sqi])->write_target_to(w);
				w.end_element(0, sml_sharedWorkbookRevisions_sheetId_literal);
			}
		}

		void CT_Reviewed_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_sharedWorkbookRevisions_rId_literal, context()->serialize(t()->rId));
		}

		void CT_ReviewedRevisions_writer::write_target_to(xml_writer& w) {
			if (t()->count.present())
				w.attribute(0, sml_sharedWorkbookRevisions_count_literal, context()->serialize(t()->count.get()));
			for (size_t sqi = 0; sqi<t()->reviewed.size(); ++sqi) {
				w.start_element(0, sml_sharedWorkbookRevisions_reviewed_literal);
				_reviewed_writer.get_writer(context(), &t()->reviewed[sqi])->write_target_to(w);
				w.end_element(0, sml_sharedWorkbookRevisions_reviewed_literal);
			}
		}

		void CT_RevisionHeader_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_sharedWorkbookRevisions_guid_literal, context()->serialize(t()->guid));
			w.attribute(0, sml_sharedWorkbookRevisions_dateTime_literal, context()->serialize(t()->dateTime));
			w.attribute(0, sml_sharedWorkbookRevisions_maxSheetId_literal, context()->serialize(t()->maxSheetId));
			w.attribute(0, sml_sharedWorkbookRevisions_userName_literal, context()->serialize(t()->userName));
			w.attribute(sml_sharedWorkbookRevisions_r_literal, sml_sharedWorkbookRevisions_id_literal, context()->serialize(t()->id));
			if (t()->minRId.present())
				w.attribute(0, sml_sharedWorkbookRevisions_minRId_literal, context()->serialize(t()->minRId.get()));
			if (t()->maxRId.present())
				w.attribute(0, sml_sharedWorkbookRevisions_maxRId_literal, context()->serialize(t()->maxRId.get()));
			w.start_element(0, sml_sharedWorkbookRevisions_sheetIdMap_literal);
			_sheetIdMap_writer.get_writer(context(), &t()->sheetIdMap)->write_target_to(w);
			w.end_element(0, sml_sharedWorkbookRevisions_sheetIdMap_literal);
			if (t()->reviewedList.present()) {
				w.start_element(0, sml_sharedWorkbookRevisions_reviewedList_literal);
				_reviewedList_writer.get_writer(context(), &t()->reviewedList.get())->write_target_to(w);
				w.end_element(0, sml_sharedWorkbookRevisions_reviewedList_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, sml_sharedWorkbookRevisions_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_sharedWorkbookRevisions_extLst_literal);
			}
		}

		void CT_RevisionHeaders_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_sharedWorkbookRevisions_guid_literal, context()->serialize(t()->guid));
			if (t()->lastGuid.present())
				w.attribute(0, sml_sharedWorkbookRevisions_lastGuid_literal, context()->serialize(t()->lastGuid.get()));
			if (t()->shared != true)
				w.attribute(0, sml_sharedWorkbookRevisions_shared_literal, context()->serialize(t()->shared));
			if (t()->diskRevisions != false)
				w.attribute(0, sml_sharedWorkbookRevisions_diskRevisions_literal, context()->serialize(t()->diskRevisions));
			if (t()->history != true)
				w.attribute(0, sml_sharedWorkbookRevisions_history_literal, context()->serialize(t()->history));
			if (t()->trackRevisions != true)
				w.attribute(0, sml_sharedWorkbookRevisions_trackRevisions_literal, context()->serialize(t()->trackRevisions));
			if (t()->exclusive != false)
				w.attribute(0, sml_sharedWorkbookRevisions_exclusive_literal, context()->serialize(t()->exclusive));
			if (t()->revisionId != 0U)
				w.attribute(0, sml_sharedWorkbookRevisions_revisionId_literal, context()->serialize(t()->revisionId));
			if (t()->version != 1)
				w.attribute(0, sml_sharedWorkbookRevisions_version_literal, context()->serialize(t()->version));
			if (t()->keepChangeHistory != true)
				w.attribute(0, sml_sharedWorkbookRevisions_keepChangeHistory_literal, context()->serialize(t()->keepChangeHistory));
			if (t()->_protected_ != false)
				w.attribute(0, sml_sharedWorkbookRevisions__protected__literal, context()->serialize(t()->_protected_));
			if (t()->preserveHistory != 30U)
				w.attribute(0, sml_sharedWorkbookRevisions_preserveHistory_literal, context()->serialize(t()->preserveHistory));
			for (size_t sqi = 0; sqi<t()->header.size(); ++sqi) {
				w.start_element(0, sml_sharedWorkbookRevisions_header_literal);
				_header_writer.get_writer(context(), &t()->header[sqi])->write_target_to(w);
				w.end_element(0, sml_sharedWorkbookRevisions_header_literal);
			}
		}

		void CT_UndoInfo_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_sharedWorkbookRevisions_index_literal, context()->serialize(t()->index));
			w.attribute(0, sml_sharedWorkbookRevisions_exp_literal, context()->serialize(t()->exp));
			if (t()->ref3D != false)
				w.attribute(0, sml_sharedWorkbookRevisions_ref3D_literal, context()->serialize(t()->ref3D));
			if (t()->array != false)
				w.attribute(0, sml_sharedWorkbookRevisions_array_literal, context()->serialize(t()->array));
			if (t()->v != false)
				w.attribute(0, sml_sharedWorkbookRevisions_v_literal, context()->serialize(t()->v));
			if (t()->nf != false)
				w.attribute(0, sml_sharedWorkbookRevisions_nf_literal, context()->serialize(t()->nf));
			if (t()->cs != false)
				w.attribute(0, sml_sharedWorkbookRevisions_cs_literal, context()->serialize(t()->cs));
			w.attribute(0, sml_sharedWorkbookRevisions_dr_literal, context()->serialize(t()->dr));
			if (t()->dn.present())
				w.attribute(0, sml_sharedWorkbookRevisions_dn_literal, context()->serialize(t()->dn.get()));
			if (t()->r.present())
				w.attribute(0, sml_sharedWorkbookRevisions_r_literal, context()->serialize(t()->r.get()));
			if (t()->sId.present())
				w.attribute(0, sml_sharedWorkbookRevisions_sId_literal, context()->serialize(t()->sId.get()));
		}

		void CT_RevisionCellChange_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_sharedWorkbookRevisions_rId_literal, context()->serialize(t()->rId));
			if (t()->ua != false)
				w.attribute(0, sml_sharedWorkbookRevisions_ua_literal, context()->serialize(t()->ua));
			if (t()->ra != false)
				w.attribute(0, sml_sharedWorkbookRevisions_ra_literal, context()->serialize(t()->ra));
			w.attribute(0, sml_sharedWorkbookRevisions_sId_literal, context()->serialize(t()->sId));
			if (t()->odxf_attr != false)
				w.attribute(0, sml_sharedWorkbookRevisions_odxf_literal, context()->serialize(t()->odxf_attr));
			if (t()->xfDxf != false)
				w.attribute(0, sml_sharedWorkbookRevisions_xfDxf_literal, context()->serialize(t()->xfDxf));
			if (t()->s != false)
				w.attribute(0, sml_sharedWorkbookRevisions_s_literal, context()->serialize(t()->s));
			if (t()->dxf != false)
				w.attribute(0, sml_sharedWorkbookRevisions_dxf_literal, context()->serialize(t()->dxf));
			if (t()->numFmtId.present())
				w.attribute(0, sml_sharedWorkbookRevisions_numFmtId_literal, context()->serialize(t()->numFmtId.get()));
			if (t()->quotePrefix != false)
				w.attribute(0, sml_sharedWorkbookRevisions_quotePrefix_literal, context()->serialize(t()->quotePrefix));
			if (t()->oldQuotePrefix != false)
				w.attribute(0, sml_sharedWorkbookRevisions_oldQuotePrefix_literal, context()->serialize(t()->oldQuotePrefix));
			if (t()->ph != false)
				w.attribute(0, sml_sharedWorkbookRevisions_ph_literal, context()->serialize(t()->ph));
			if (t()->oldPh != false)
				w.attribute(0, sml_sharedWorkbookRevisions_oldPh_literal, context()->serialize(t()->oldPh));
			if (t()->endOfListFormulaUpdate != false)
				w.attribute(0, sml_sharedWorkbookRevisions_endOfListFormulaUpdate_literal, context()->serialize(t()->endOfListFormulaUpdate));
			if (t()->oc.present()) {
				w.start_element(0, sml_sharedWorkbookRevisions_oc_literal);
				_oc_writer.get_writer(context(), &t()->oc.get())->write_target_to(w);
				w.end_element(0, sml_sharedWorkbookRevisions_oc_literal);
			}
			w.start_element(0, sml_sharedWorkbookRevisions_nc_literal);
			_nc_writer.get_writer(context(), &t()->nc)->write_target_to(w);
			w.end_element(0, sml_sharedWorkbookRevisions_nc_literal);
			if (t()->odxf.present()) {
				w.start_element(0, sml_sharedWorkbookRevisions_odxf_literal);
				_odxf_writer.get_writer(context(), &t()->odxf.get())->write_target_to(w);
				w.end_element(0, sml_sharedWorkbookRevisions_odxf_literal);
			}
			if (t()->ndxf.present()) {
				w.start_element(0, sml_sharedWorkbookRevisions_ndxf_literal);
				_ndxf_writer.get_writer(context(), &t()->ndxf.get())->write_target_to(w);
				w.end_element(0, sml_sharedWorkbookRevisions_ndxf_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, sml_sharedWorkbookRevisions_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_sharedWorkbookRevisions_extLst_literal);
			}
		}

		void CT_RevisionFormatting_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_sharedWorkbookRevisions_sheetId_literal, context()->serialize(t()->sheetId));
			if (t()->xfDxf != false)
				w.attribute(0, sml_sharedWorkbookRevisions_xfDxf_literal, context()->serialize(t()->xfDxf));
			if (t()->s != false)
				w.attribute(0, sml_sharedWorkbookRevisions_s_literal, context()->serialize(t()->s));
			w.attribute(0, sml_sharedWorkbookRevisions_sqref_literal, context()->serialize(t()->sqref));
			if (t()->start.present())
				w.attribute(0, sml_sharedWorkbookRevisions_start_literal, context()->serialize(t()->start.get()));
			if (t()->length.present())
				w.attribute(0, sml_sharedWorkbookRevisions_length_literal, context()->serialize(t()->length.get()));
			if (t()->dxf.present()) {
				w.start_element(0, sml_sharedWorkbookRevisions_dxf_literal);
				_dxf_writer.get_writer(context(), &t()->dxf.get())->write_target_to(w);
				w.end_element(0, sml_sharedWorkbookRevisions_dxf_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, sml_sharedWorkbookRevisions_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_sharedWorkbookRevisions_extLst_literal);
			}
		}

		void CT_RevisionRowColumn_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_sharedWorkbookRevisions_rId_literal, context()->serialize(t()->rId));
			if (t()->ua != false)
				w.attribute(0, sml_sharedWorkbookRevisions_ua_literal, context()->serialize(t()->ua));
			if (t()->ra != false)
				w.attribute(0, sml_sharedWorkbookRevisions_ra_literal, context()->serialize(t()->ra));
			w.attribute(0, sml_sharedWorkbookRevisions_sId_literal, context()->serialize(t()->sId));
			if (t()->eol != false)
				w.attribute(0, sml_sharedWorkbookRevisions_eol_literal, context()->serialize(t()->eol));
			w.attribute(0, sml_sharedWorkbookRevisions_ref_literal, context()->serialize(t()->ref));
			w.attribute(0, sml_sharedWorkbookRevisions_action_literal, context()->serialize(t()->action));
			if (t()->edge != false)
				w.attribute(0, sml_sharedWorkbookRevisions_edge_literal, context()->serialize(t()->edge));
			if (t()->undo.present())
				for (size_t sqi = 0; sqi<t()->undo.get().size(); ++sqi) {
					w.start_element(0, sml_sharedWorkbookRevisions_undo_literal);
					_undo_writer.get_writer(context(), &t()->undo.get()[sqi])->write_target_to(w);
					w.end_element(0, sml_sharedWorkbookRevisions_undo_literal);
				}
			if (t()->rcc.present())
				for (size_t sqi = 0; sqi<t()->rcc.get().size(); ++sqi) {
					w.start_element(0, sml_sharedWorkbookRevisions_rcc_literal);
					_rcc_writer.get_writer(context(), &t()->rcc.get()[sqi])->write_target_to(w);
					w.end_element(0, sml_sharedWorkbookRevisions_rcc_literal);
				}
			if (t()->rfmt.present())
				for (size_t sqi = 0; sqi<t()->rfmt.get().size(); ++sqi) {
					w.start_element(0, sml_sharedWorkbookRevisions_rfmt_literal);
					_rfmt_writer.get_writer(context(), &t()->rfmt.get()[sqi])->write_target_to(w);
					w.end_element(0, sml_sharedWorkbookRevisions_rfmt_literal);
				}
		}

		void CT_RevisionMove_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_sharedWorkbookRevisions_rId_literal, context()->serialize(t()->rId));
			if (t()->ua != false)
				w.attribute(0, sml_sharedWorkbookRevisions_ua_literal, context()->serialize(t()->ua));
			if (t()->ra != false)
				w.attribute(0, sml_sharedWorkbookRevisions_ra_literal, context()->serialize(t()->ra));
			w.attribute(0, sml_sharedWorkbookRevisions_sheetId_literal, context()->serialize(t()->sheetId));
			w.attribute(0, sml_sharedWorkbookRevisions_source_literal, context()->serialize(t()->source));
			w.attribute(0, sml_sharedWorkbookRevisions_destination_literal, context()->serialize(t()->destination));
			if (t()->sourceSheetId != 0U)
				w.attribute(0, sml_sharedWorkbookRevisions_sourceSheetId_literal, context()->serialize(t()->sourceSheetId));
			if (t()->undo.present())
				for (size_t sqi = 0; sqi<t()->undo.get().size(); ++sqi) {
					w.start_element(0, sml_sharedWorkbookRevisions_undo_literal);
					_undo_writer.get_writer(context(), &t()->undo.get()[sqi])->write_target_to(w);
					w.end_element(0, sml_sharedWorkbookRevisions_undo_literal);
				}
			if (t()->rcc.present())
				for (size_t sqi = 0; sqi<t()->rcc.get().size(); ++sqi) {
					w.start_element(0, sml_sharedWorkbookRevisions_rcc_literal);
					_rcc_writer.get_writer(context(), &t()->rcc.get()[sqi])->write_target_to(w);
					w.end_element(0, sml_sharedWorkbookRevisions_rcc_literal);
				}
			if (t()->rfmt.present())
				for (size_t sqi = 0; sqi<t()->rfmt.get().size(); ++sqi) {
					w.start_element(0, sml_sharedWorkbookRevisions_rfmt_literal);
					_rfmt_writer.get_writer(context(), &t()->rfmt.get()[sqi])->write_target_to(w);
					w.end_element(0, sml_sharedWorkbookRevisions_rfmt_literal);
				}
		}

		void CT_RevisionCustomView_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_sharedWorkbookRevisions_guid_literal, context()->serialize(t()->guid));
			w.attribute(0, sml_sharedWorkbookRevisions_action_literal, context()->serialize(t()->action));
		}

		void CT_RevisionSheetRename_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_sharedWorkbookRevisions_rId_literal, context()->serialize(t()->rId));
			if (t()->ua != false)
				w.attribute(0, sml_sharedWorkbookRevisions_ua_literal, context()->serialize(t()->ua));
			if (t()->ra != false)
				w.attribute(0, sml_sharedWorkbookRevisions_ra_literal, context()->serialize(t()->ra));
			w.attribute(0, sml_sharedWorkbookRevisions_sheetId_literal, context()->serialize(t()->sheetId));
			w.attribute(0, sml_sharedWorkbookRevisions_oldName_literal, context()->serialize(t()->oldName));
			w.attribute(0, sml_sharedWorkbookRevisions_newName_literal, context()->serialize(t()->newName));
			if (t()->extLst.present()) {
				w.start_element(0, sml_sharedWorkbookRevisions_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_sharedWorkbookRevisions_extLst_literal);
			}
		}

		void CT_RevisionInsertSheet_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_sharedWorkbookRevisions_rId_literal, context()->serialize(t()->rId));
			if (t()->ua != false)
				w.attribute(0, sml_sharedWorkbookRevisions_ua_literal, context()->serialize(t()->ua));
			if (t()->ra != false)
				w.attribute(0, sml_sharedWorkbookRevisions_ra_literal, context()->serialize(t()->ra));
			w.attribute(0, sml_sharedWorkbookRevisions_sheetId_literal, context()->serialize(t()->sheetId));
			w.attribute(0, sml_sharedWorkbookRevisions_name_literal, context()->serialize(t()->name));
			w.attribute(0, sml_sharedWorkbookRevisions_sheetPosition_literal, context()->serialize(t()->sheetPosition));
		}

		void CT_RevisionAutoFormatting_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_sharedWorkbookRevisions_sheetId_literal, context()->serialize(t()->sheetId));
			if (t()->autoFormatId.present())
				w.attribute(0, sml_sharedWorkbookRevisions_autoFormatId_literal, context()->serialize(t()->autoFormatId.get()));
			if (t()->applyNumberFormats.present())
				w.attribute(0, sml_sharedWorkbookRevisions_applyNumberFormats_literal, context()->serialize(t()->applyNumberFormats.get()));
			if (t()->applyBorderFormats.present())
				w.attribute(0, sml_sharedWorkbookRevisions_applyBorderFormats_literal, context()->serialize(t()->applyBorderFormats.get()));
			if (t()->applyFontFormats.present())
				w.attribute(0, sml_sharedWorkbookRevisions_applyFontFormats_literal, context()->serialize(t()->applyFontFormats.get()));
			if (t()->applyPatternFormats.present())
				w.attribute(0, sml_sharedWorkbookRevisions_applyPatternFormats_literal, context()->serialize(t()->applyPatternFormats.get()));
			if (t()->applyAlignmentFormats.present())
				w.attribute(0, sml_sharedWorkbookRevisions_applyAlignmentFormats_literal, context()->serialize(t()->applyAlignmentFormats.get()));
			if (t()->applyWidthHeightFormats.present())
				w.attribute(0, sml_sharedWorkbookRevisions_applyWidthHeightFormats_literal, context()->serialize(t()->applyWidthHeightFormats.get()));
			w.attribute(0, sml_sharedWorkbookRevisions_ref_literal, context()->serialize(t()->ref));
		}

		void CT_RevisionDefinedName_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_sharedWorkbookRevisions_rId_literal, context()->serialize(t()->rId));
			if (t()->ua != false)
				w.attribute(0, sml_sharedWorkbookRevisions_ua_literal, context()->serialize(t()->ua));
			if (t()->ra != false)
				w.attribute(0, sml_sharedWorkbookRevisions_ra_literal, context()->serialize(t()->ra));
			if (t()->localSheetId.present())
				w.attribute(0, sml_sharedWorkbookRevisions_localSheetId_literal, context()->serialize(t()->localSheetId.get()));
			if (t()->customView != false)
				w.attribute(0, sml_sharedWorkbookRevisions_customView_literal, context()->serialize(t()->customView));
			w.attribute(0, sml_sharedWorkbookRevisions_name_literal, context()->serialize(t()->name));
			if (t()->function != false)
				w.attribute(0, sml_sharedWorkbookRevisions_function_literal, context()->serialize(t()->function));
			if (t()->oldFunction != false)
				w.attribute(0, sml_sharedWorkbookRevisions_oldFunction_literal, context()->serialize(t()->oldFunction));
			if (t()->functionGroupId.present())
				w.attribute(0, sml_sharedWorkbookRevisions_functionGroupId_literal, context()->serialize(t()->functionGroupId.get()));
			if (t()->oldFunctionGroupId.present())
				w.attribute(0, sml_sharedWorkbookRevisions_oldFunctionGroupId_literal, context()->serialize(t()->oldFunctionGroupId.get()));
			if (t()->shortcutKey.present())
				w.attribute(0, sml_sharedWorkbookRevisions_shortcutKey_literal, context()->serialize(t()->shortcutKey.get()));
			if (t()->oldShortcutKey.present())
				w.attribute(0, sml_sharedWorkbookRevisions_oldShortcutKey_literal, context()->serialize(t()->oldShortcutKey.get()));
			if (t()->hidden != false)
				w.attribute(0, sml_sharedWorkbookRevisions_hidden_literal, context()->serialize(t()->hidden));
			if (t()->oldHidden != false)
				w.attribute(0, sml_sharedWorkbookRevisions_oldHidden_literal, context()->serialize(t()->oldHidden));
			if (t()->customMenu.present())
				w.attribute(0, sml_sharedWorkbookRevisions_customMenu_literal, context()->serialize(t()->customMenu.get()));
			if (t()->oldCustomMenu.present())
				w.attribute(0, sml_sharedWorkbookRevisions_oldCustomMenu_literal, context()->serialize(t()->oldCustomMenu.get()));
			if (t()->description.present())
				w.attribute(0, sml_sharedWorkbookRevisions_description_literal, context()->serialize(t()->description.get()));
			if (t()->oldDescription.present())
				w.attribute(0, sml_sharedWorkbookRevisions_oldDescription_literal, context()->serialize(t()->oldDescription.get()));
			if (t()->help.present())
				w.attribute(0, sml_sharedWorkbookRevisions_help_literal, context()->serialize(t()->help.get()));
			if (t()->oldHelp.present())
				w.attribute(0, sml_sharedWorkbookRevisions_oldHelp_literal, context()->serialize(t()->oldHelp.get()));
			if (t()->statusBar.present())
				w.attribute(0, sml_sharedWorkbookRevisions_statusBar_literal, context()->serialize(t()->statusBar.get()));
			if (t()->oldStatusBar.present())
				w.attribute(0, sml_sharedWorkbookRevisions_oldStatusBar_literal, context()->serialize(t()->oldStatusBar.get()));
			if (t()->comment.present())
				w.attribute(0, sml_sharedWorkbookRevisions_comment_literal, context()->serialize(t()->comment.get()));
			if (t()->oldComment.present())
				w.attribute(0, sml_sharedWorkbookRevisions_oldComment_literal, context()->serialize(t()->oldComment.get()));
			if (t()->formula.present()) {
				w.start_element(0, sml_sharedWorkbookRevisions_formula_literal);
				_formula_writer.get_writer(context(), &t()->formula.get())->write_target_to(w);
				w.end_element(0, sml_sharedWorkbookRevisions_formula_literal);
			}
			if (t()->oldFormula.present()) {
				w.start_element(0, sml_sharedWorkbookRevisions_oldFormula_literal);
				_oldFormula_writer.get_writer(context(), &t()->oldFormula.get())->write_target_to(w);
				w.end_element(0, sml_sharedWorkbookRevisions_oldFormula_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, sml_sharedWorkbookRevisions_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_sharedWorkbookRevisions_extLst_literal);
			}
		}

		void CT_RevisionComment_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_sharedWorkbookRevisions_sheetId_literal, context()->serialize(t()->sheetId));
			w.attribute(0, sml_sharedWorkbookRevisions_cell_literal, context()->serialize(t()->cell));
			w.attribute(0, sml_sharedWorkbookRevisions_guid_literal, context()->serialize(t()->guid));
			if (t()->action != ST_RevisionAction::add_literal)
				w.attribute(0, sml_sharedWorkbookRevisions_action_literal, context()->serialize(t()->action));
			if (t()->alwaysShow != false)
				w.attribute(0, sml_sharedWorkbookRevisions_alwaysShow_literal, context()->serialize(t()->alwaysShow));
			if (t()->old != false)
				w.attribute(0, sml_sharedWorkbookRevisions_old_literal, context()->serialize(t()->old));
			if (t()->hiddenRow != false)
				w.attribute(0, sml_sharedWorkbookRevisions_hiddenRow_literal, context()->serialize(t()->hiddenRow));
			if (t()->hiddenColumn != false)
				w.attribute(0, sml_sharedWorkbookRevisions_hiddenColumn_literal, context()->serialize(t()->hiddenColumn));
			w.attribute(0, sml_sharedWorkbookRevisions_author_literal, context()->serialize(t()->author));
			if (t()->oldLength != 0U)
				w.attribute(0, sml_sharedWorkbookRevisions_oldLength_literal, context()->serialize(t()->oldLength));
			if (t()->newLength != 0U)
				w.attribute(0, sml_sharedWorkbookRevisions_newLength_literal, context()->serialize(t()->newLength));
		}

		void CT_RevisionQueryTableField_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_sharedWorkbookRevisions_sheetId_literal, context()->serialize(t()->sheetId));
			w.attribute(0, sml_sharedWorkbookRevisions_ref_literal, context()->serialize(t()->ref));
			w.attribute(0, sml_sharedWorkbookRevisions_fieldId_literal, context()->serialize(t()->fieldId));
		}

		void CT_RevisionConflict_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_sharedWorkbookRevisions_rId_literal, context()->serialize(t()->rId));
			if (t()->ua != false)
				w.attribute(0, sml_sharedWorkbookRevisions_ua_literal, context()->serialize(t()->ua));
			if (t()->ra != false)
				w.attribute(0, sml_sharedWorkbookRevisions_ra_literal, context()->serialize(t()->ra));
			if (t()->sheetId.present())
				w.attribute(0, sml_sharedWorkbookRevisions_sheetId_literal, context()->serialize(t()->sheetId.get()));
		}

		void CT_Revisions_writer::write_target_to(xml_writer& w) {
			if (t()->rrc.present())
				for (size_t sqi = 0; sqi<t()->rrc.get().size(); ++sqi) {
					w.start_element(0, sml_sharedWorkbookRevisions_rrc_literal);
					_rrc_writer.get_writer(context(), &t()->rrc.get()[sqi])->write_target_to(w);
					w.end_element(0, sml_sharedWorkbookRevisions_rrc_literal);
				}
			if (t()->rm.present())
				for (size_t sqi = 0; sqi<t()->rm.get().size(); ++sqi) {
					w.start_element(0, sml_sharedWorkbookRevisions_rm_literal);
					_rm_writer.get_writer(context(), &t()->rm.get()[sqi])->write_target_to(w);
					w.end_element(0, sml_sharedWorkbookRevisions_rm_literal);
				}
			if (t()->rcv.present())
				for (size_t sqi = 0; sqi<t()->rcv.get().size(); ++sqi) {
					w.start_element(0, sml_sharedWorkbookRevisions_rcv_literal);
					_rcv_writer.get_writer(context(), &t()->rcv.get()[sqi])->write_target_to(w);
					w.end_element(0, sml_sharedWorkbookRevisions_rcv_literal);
				}
			if (t()->rsnm.present())
				for (size_t sqi = 0; sqi<t()->rsnm.get().size(); ++sqi) {
					w.start_element(0, sml_sharedWorkbookRevisions_rsnm_literal);
					_rsnm_writer.get_writer(context(), &t()->rsnm.get()[sqi])->write_target_to(w);
					w.end_element(0, sml_sharedWorkbookRevisions_rsnm_literal);
				}
			if (t()->ris.present())
				for (size_t sqi = 0; sqi<t()->ris.get().size(); ++sqi) {
					w.start_element(0, sml_sharedWorkbookRevisions_ris_literal);
					_ris_writer.get_writer(context(), &t()->ris.get()[sqi])->write_target_to(w);
					w.end_element(0, sml_sharedWorkbookRevisions_ris_literal);
				}
			if (t()->rcc.present())
				for (size_t sqi = 0; sqi<t()->rcc.get().size(); ++sqi) {
					w.start_element(0, sml_sharedWorkbookRevisions_rcc_literal);
					_rcc_writer.get_writer(context(), &t()->rcc.get()[sqi])->write_target_to(w);
					w.end_element(0, sml_sharedWorkbookRevisions_rcc_literal);
				}
			if (t()->rfmt.present())
				for (size_t sqi = 0; sqi<t()->rfmt.get().size(); ++sqi) {
					w.start_element(0, sml_sharedWorkbookRevisions_rfmt_literal);
					_rfmt_writer.get_writer(context(), &t()->rfmt.get()[sqi])->write_target_to(w);
					w.end_element(0, sml_sharedWorkbookRevisions_rfmt_literal);
				}
			if (t()->raf.present())
				for (size_t sqi = 0; sqi<t()->raf.get().size(); ++sqi) {
					w.start_element(0, sml_sharedWorkbookRevisions_raf_literal);
					_raf_writer.get_writer(context(), &t()->raf.get()[sqi])->write_target_to(w);
					w.end_element(0, sml_sharedWorkbookRevisions_raf_literal);
				}
			if (t()->rdn.present())
				for (size_t sqi = 0; sqi<t()->rdn.get().size(); ++sqi) {
					w.start_element(0, sml_sharedWorkbookRevisions_rdn_literal);
					_rdn_writer.get_writer(context(), &t()->rdn.get()[sqi])->write_target_to(w);
					w.end_element(0, sml_sharedWorkbookRevisions_rdn_literal);
				}
			if (t()->rcmt.present())
				for (size_t sqi = 0; sqi<t()->rcmt.get().size(); ++sqi) {
					w.start_element(0, sml_sharedWorkbookRevisions_rcmt_literal);
					_rcmt_writer.get_writer(context(), &t()->rcmt.get()[sqi])->write_target_to(w);
					w.end_element(0, sml_sharedWorkbookRevisions_rcmt_literal);
				}
			if (t()->rqt.present())
				for (size_t sqi = 0; sqi<t()->rqt.get().size(); ++sqi) {
					w.start_element(0, sml_sharedWorkbookRevisions_rqt_literal);
					_rqt_writer.get_writer(context(), &t()->rqt.get()[sqi])->write_target_to(w);
					w.end_element(0, sml_sharedWorkbookRevisions_rqt_literal);
				}
			if (t()->rcft.present())
				for (size_t sqi = 0; sqi<t()->rcft.get().size(); ++sqi) {
					w.start_element(0, sml_sharedWorkbookRevisions_rcft_literal);
					_rcft_writer.get_writer(context(), &t()->rcft.get()[sqi])->write_target_to(w);
					w.end_element(0, sml_sharedWorkbookRevisions_rcft_literal);
				}
		}

		void sml_sharedWorkbookRevisions_writer::write_target_to(xml_writer& w) {
			if (t()->headers.present()) {
				w.start_element(0, sml_sharedWorkbookRevisions_headers_literal);
					w.attribute(0, sml_sharedWorkbookRevisions_xmlns_literal, sml_sharedWorkbookRevisions_http_colon__slash__slash_schemas_dot_openxmlformats_dot_org_slash_spreadsheetml_slash_2006_slash_main_literal);
					w.attribute(sml_sharedWorkbookRevisions_xmlns_literal, sml_sharedWorkbookRevisions_r_literal, sml_sharedWorkbookRevisions_http_colon__slash__slash_schemas_dot_openxmlformats_dot_org_slash_officeDocument_slash_2006_slash_relationships_literal);
					w.attribute(sml_sharedWorkbookRevisions_xmlns_literal, sml_sharedWorkbookRevisions_xsd_literal, sml_sharedWorkbookRevisions_http_colon__slash__slash_www_dot_w3_dot_org_slash_2001_slash_XMLSchema_literal);
				_headers_writer.get_writer(context(), &t()->headers.get())->write_target_to(w);
				w.end_element(0, sml_sharedWorkbookRevisions_headers_literal);
			}
			if (t()->revisions.present()) {
				w.start_element(0, sml_sharedWorkbookRevisions_revisions_literal);
					w.attribute(0, sml_sharedWorkbookRevisions_xmlns_literal, sml_sharedWorkbookRevisions_http_colon__slash__slash_schemas_dot_openxmlformats_dot_org_slash_spreadsheetml_slash_2006_slash_main_literal);
					w.attribute(sml_sharedWorkbookRevisions_xmlns_literal, sml_sharedWorkbookRevisions_r_literal, sml_sharedWorkbookRevisions_http_colon__slash__slash_schemas_dot_openxmlformats_dot_org_slash_officeDocument_slash_2006_slash_relationships_literal);
					w.attribute(sml_sharedWorkbookRevisions_xmlns_literal, sml_sharedWorkbookRevisions_xsd_literal, sml_sharedWorkbookRevisions_http_colon__slash__slash_www_dot_w3_dot_org_slash_2001_slash_XMLSchema_literal);
				_revisions_writer.get_writer(context(), &t()->revisions.get())->write_target_to(w);
				w.end_element(0, sml_sharedWorkbookRevisions_revisions_literal);
			}
		}

	}
}
