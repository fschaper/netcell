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


#include "sml-sheet_writers.hpp"
#include "sml-sheet_literals.hpp"

namespace spreadsheetml
{
	namespace xio
	{
		void CT_CellFormula_writer::write_target_to(xml_writer& w) {
			if (t()->t != ST_CellFormulaType::normal_literal)
				w.attribute(0, sml_sheet_t_literal, context()->serialize(t()->t));
			if (t()->aca != false)
				w.attribute(0, sml_sheet_aca_literal, context()->serialize(t()->aca));
			if (t()->ref.present())
				w.attribute(0, sml_sheet_ref_literal, context()->serialize(t()->ref.get()));
			if (t()->dt2D != false)
				w.attribute(0, sml_sheet_dt2D_literal, context()->serialize(t()->dt2D));
			if (t()->dtr != false)
				w.attribute(0, sml_sheet_dtr_literal, context()->serialize(t()->dtr));
			if (t()->del1 != false)
				w.attribute(0, sml_sheet_del1_literal, context()->serialize(t()->del1));
			if (t()->del2 != false)
				w.attribute(0, sml_sheet_del2_literal, context()->serialize(t()->del2));
			if (t()->r1.present())
				w.attribute(0, sml_sheet_r1_literal, context()->serialize(t()->r1.get()));
			if (t()->r2.present())
				w.attribute(0, sml_sheet_r2_literal, context()->serialize(t()->r2.get()));
			if (t()->ca != false)
				w.attribute(0, sml_sheet_ca_literal, context()->serialize(t()->ca));
			if (t()->si.present())
				w.attribute(0, sml_sheet_si_literal, context()->serialize(t()->si.get()));
			if (t()->bx != false)
				w.attribute(0, sml_sheet_bx_literal, context()->serialize(t()->bx));
			ST_Formula_writer::write_target_to(w);
		}

		void CT_Cell_writer::write_target_to(xml_writer& w) {
			if (t()->r.present())
				w.attribute(0, sml_sheet_r_literal, context()->serialize(t()->r.get()));
			if (t()->s != 0U)
				w.attribute(0, sml_sheet_s_literal, context()->serialize(t()->s));
			if (t()->t != ST_CellType::n_literal)
				w.attribute(0, sml_sheet_t_literal, context()->serialize(t()->t));
			if (t()->cm != 0U)
				w.attribute(0, sml_sheet_cm_literal, context()->serialize(t()->cm));
			if (t()->vm != 0U)
				w.attribute(0, sml_sheet_vm_literal, context()->serialize(t()->vm));
			if (t()->ph != false)
				w.attribute(0, sml_sheet_ph_literal, context()->serialize(t()->ph));
			if (t()->f.present()) {
				w.start_element(0, sml_sheet_f_literal);
				_f_writer.get_writer(context(), &t()->f.get())->write_target_to(w);
				w.end_element(0, sml_sheet_f_literal);
			}
			if (t()->v.present()) {
				w.start_element(0, sml_sheet_v_literal);
				_v_writer.get_writer(context(), &t()->v.get())->write_target_to(w);
				w.end_element(0, sml_sheet_v_literal);
			}
			if (t()->is.present()) {
				w.start_element(0, sml_sheet_is_literal);
				_is_writer.get_writer(context(), &t()->is.get())->write_target_to(w);
				w.end_element(0, sml_sheet_is_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, sml_sheet_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_sheet_extLst_literal);
			}
		}

		void CT_OutlinePr_writer::write_target_to(xml_writer& w) {
			if (t()->applyStyles != false)
				w.attribute(0, sml_sheet_applyStyles_literal, context()->serialize(t()->applyStyles));
			if (t()->summaryBelow != true)
				w.attribute(0, sml_sheet_summaryBelow_literal, context()->serialize(t()->summaryBelow));
			if (t()->summaryRight != true)
				w.attribute(0, sml_sheet_summaryRight_literal, context()->serialize(t()->summaryRight));
			if (t()->showOutlineSymbols != true)
				w.attribute(0, sml_sheet_showOutlineSymbols_literal, context()->serialize(t()->showOutlineSymbols));
		}

		void CT_PageSetUpPr_writer::write_target_to(xml_writer& w) {
			if (t()->autoPageBreaks != true)
				w.attribute(0, sml_sheet_autoPageBreaks_literal, context()->serialize(t()->autoPageBreaks));
			if (t()->fitToPage != false)
				w.attribute(0, sml_sheet_fitToPage_literal, context()->serialize(t()->fitToPage));
		}

		void CT_SheetPr_writer::write_target_to(xml_writer& w) {
			if (t()->syncHorizontal != false)
				w.attribute(0, sml_sheet_syncHorizontal_literal, context()->serialize(t()->syncHorizontal));
			if (t()->syncVertical != false)
				w.attribute(0, sml_sheet_syncVertical_literal, context()->serialize(t()->syncVertical));
			if (t()->syncRef.present())
				w.attribute(0, sml_sheet_syncRef_literal, context()->serialize(t()->syncRef.get()));
			if (t()->transitionEvaluation != false)
				w.attribute(0, sml_sheet_transitionEvaluation_literal, context()->serialize(t()->transitionEvaluation));
			if (t()->transitionEntry != false)
				w.attribute(0, sml_sheet_transitionEntry_literal, context()->serialize(t()->transitionEntry));
			if (t()->published != true)
				w.attribute(0, sml_sheet_published_literal, context()->serialize(t()->published));
			if (t()->codeName.present())
				w.attribute(0, sml_sheet_codeName_literal, context()->serialize(t()->codeName.get()));
			if (t()->filterMode != false)
				w.attribute(0, sml_sheet_filterMode_literal, context()->serialize(t()->filterMode));
			if (t()->enableFormatConditionsCalculation != true)
				w.attribute(0, sml_sheet_enableFormatConditionsCalculation_literal, context()->serialize(t()->enableFormatConditionsCalculation));
			if (t()->tabColor.present()) {
				w.start_element(0, sml_sheet_tabColor_literal);
				_tabColor_writer.get_writer(context(), &t()->tabColor.get())->write_target_to(w);
				w.end_element(0, sml_sheet_tabColor_literal);
			}
			if (t()->outlinePr.present()) {
				w.start_element(0, sml_sheet_outlinePr_literal);
				_outlinePr_writer.get_writer(context(), &t()->outlinePr.get())->write_target_to(w);
				w.end_element(0, sml_sheet_outlinePr_literal);
			}
			if (t()->pageSetUpPr.present()) {
				w.start_element(0, sml_sheet_pageSetUpPr_literal);
				_pageSetUpPr_writer.get_writer(context(), &t()->pageSetUpPr.get())->write_target_to(w);
				w.end_element(0, sml_sheet_pageSetUpPr_literal);
			}
		}

		void CT_SheetDimension_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_sheet_ref_literal, context()->serialize(t()->ref));
		}

		void CT_Pane_writer::write_target_to(xml_writer& w) {
			if (t()->xSplit != 0)
				w.attribute(0, sml_sheet_xSplit_literal, context()->serialize(t()->xSplit));
			if (t()->ySplit != 0)
				w.attribute(0, sml_sheet_ySplit_literal, context()->serialize(t()->ySplit));
			if (t()->topLeftCell.present())
				w.attribute(0, sml_sheet_topLeftCell_literal, context()->serialize(t()->topLeftCell.get()));
			if (t()->activePane != ST_Pane::topLeft_literal)
				w.attribute(0, sml_sheet_activePane_literal, context()->serialize(t()->activePane));
			if (t()->state != ST_PaneState::split_literal)
				w.attribute(0, sml_sheet_state_literal, context()->serialize(t()->state));
		}

		void CT_Selection_writer::write_target_to(xml_writer& w) {
			if (t()->pane != ST_Pane::topLeft_literal)
				w.attribute(0, sml_sheet_pane_literal, context()->serialize(t()->pane));
			if (t()->activeCell.present())
				w.attribute(0, sml_sheet_activeCell_literal, context()->serialize(t()->activeCell.get()));
			if (t()->activeCellId != 0U)
				w.attribute(0, sml_sheet_activeCellId_literal, context()->serialize(t()->activeCellId));
			if (t()->sqref != "A1")
				w.attribute(0, sml_sheet_sqref_literal, context()->serialize(t()->sqref));
		}

		void CT_PivotSelection_writer::write_target_to(xml_writer& w) {
			if (t()->pane != ST_Pane::topLeft_literal)
				w.attribute(0, sml_sheet_pane_literal, context()->serialize(t()->pane));
			if (t()->showHeader != false)
				w.attribute(0, sml_sheet_showHeader_literal, context()->serialize(t()->showHeader));
			if (t()->label != false)
				w.attribute(0, sml_sheet_label_literal, context()->serialize(t()->label));
			if (t()->data != false)
				w.attribute(0, sml_sheet_data_literal, context()->serialize(t()->data));
			if (t()->extendable != false)
				w.attribute(0, sml_sheet_extendable_literal, context()->serialize(t()->extendable));
			if (t()->count != 0U)
				w.attribute(0, sml_sheet_count_literal, context()->serialize(t()->count));
			if (t()->axis.present())
				w.attribute(0, sml_sheet_axis_literal, context()->serialize(t()->axis.get()));
			if (t()->dimension != 0U)
				w.attribute(0, sml_sheet_dimension_literal, context()->serialize(t()->dimension));
			if (t()->start != 0U)
				w.attribute(0, sml_sheet_start_literal, context()->serialize(t()->start));
			if (t()->min != 0U)
				w.attribute(0, sml_sheet_min_literal, context()->serialize(t()->min));
			if (t()->max != 0U)
				w.attribute(0, sml_sheet_max_literal, context()->serialize(t()->max));
			if (t()->activeRow != 0U)
				w.attribute(0, sml_sheet_activeRow_literal, context()->serialize(t()->activeRow));
			if (t()->activeCol != 0U)
				w.attribute(0, sml_sheet_activeCol_literal, context()->serialize(t()->activeCol));
			if (t()->previousRow != 0U)
				w.attribute(0, sml_sheet_previousRow_literal, context()->serialize(t()->previousRow));
			if (t()->previousCol != 0U)
				w.attribute(0, sml_sheet_previousCol_literal, context()->serialize(t()->previousCol));
			if (t()->click != 0U)
				w.attribute(0, sml_sheet_click_literal, context()->serialize(t()->click));
			if (t()->id.present())
				w.attribute(sml_sheet_r_literal, sml_sheet_id_literal, context()->serialize(t()->id.get()));
			w.start_element(0, sml_sheet_pivotArea_literal);
			_pivotArea_writer.get_writer(context(), &t()->pivotArea)->write_target_to(w);
			w.end_element(0, sml_sheet_pivotArea_literal);
		}

		void CT_SheetView_writer::write_target_to(xml_writer& w) {
			if (t()->windowProtection != false)
				w.attribute(0, sml_sheet_windowProtection_literal, context()->serialize(t()->windowProtection));
			if (t()->showFormulas != false)
				w.attribute(0, sml_sheet_showFormulas_literal, context()->serialize(t()->showFormulas));
			if (t()->showGridLines != true)
				w.attribute(0, sml_sheet_showGridLines_literal, context()->serialize(t()->showGridLines));
			if (t()->showRowColHeaders != true)
				w.attribute(0, sml_sheet_showRowColHeaders_literal, context()->serialize(t()->showRowColHeaders));
			if (t()->showZeros != true)
				w.attribute(0, sml_sheet_showZeros_literal, context()->serialize(t()->showZeros));
			if (t()->rightToLeft != false)
				w.attribute(0, sml_sheet_rightToLeft_literal, context()->serialize(t()->rightToLeft));
			if (t()->tabSelected != false)
				w.attribute(0, sml_sheet_tabSelected_literal, context()->serialize(t()->tabSelected));
			if (t()->showRuler != true)
				w.attribute(0, sml_sheet_showRuler_literal, context()->serialize(t()->showRuler));
			if (t()->showOutlineSymbols != true)
				w.attribute(0, sml_sheet_showOutlineSymbols_literal, context()->serialize(t()->showOutlineSymbols));
			if (t()->defaultGridColor != true)
				w.attribute(0, sml_sheet_defaultGridColor_literal, context()->serialize(t()->defaultGridColor));
			if (t()->showWhiteSpace != true)
				w.attribute(0, sml_sheet_showWhiteSpace_literal, context()->serialize(t()->showWhiteSpace));
			if (t()->view != ST_SheetViewType::normal_literal)
				w.attribute(0, sml_sheet_view_literal, context()->serialize(t()->view));
			if (t()->topLeftCell.present())
				w.attribute(0, sml_sheet_topLeftCell_literal, context()->serialize(t()->topLeftCell.get()));
			if (t()->colorId != 64U)
				w.attribute(0, sml_sheet_colorId_literal, context()->serialize(t()->colorId));
			if (t()->zoomScale != 100U)
				w.attribute(0, sml_sheet_zoomScale_literal, context()->serialize(t()->zoomScale));
			if (t()->zoomScaleNormal != 0U)
				w.attribute(0, sml_sheet_zoomScaleNormal_literal, context()->serialize(t()->zoomScaleNormal));
			if (t()->zoomScaleSheetLayoutView != 0U)
				w.attribute(0, sml_sheet_zoomScaleSheetLayoutView_literal, context()->serialize(t()->zoomScaleSheetLayoutView));
			if (t()->zoomScalePageLayoutView != 0U)
				w.attribute(0, sml_sheet_zoomScalePageLayoutView_literal, context()->serialize(t()->zoomScalePageLayoutView));
			w.attribute(0, sml_sheet_workbookViewId_literal, context()->serialize(t()->workbookViewId));
			if (t()->pane.present()) {
				w.start_element(0, sml_sheet_pane_literal);
				_pane_writer.get_writer(context(), &t()->pane.get())->write_target_to(w);
				w.end_element(0, sml_sheet_pane_literal);
			}
			for (size_t sqi = 0; sqi<t()->selection.size(); ++sqi) {
				w.start_element(0, sml_sheet_selection_literal);
				_selection_writer.get_writer(context(), &t()->selection[sqi])->write_target_to(w);
				w.end_element(0, sml_sheet_selection_literal);
			}
			for (size_t sqi = 0; sqi<t()->pivotSelection.size(); ++sqi) {
				w.start_element(0, sml_sheet_pivotSelection_literal);
				_pivotSelection_writer.get_writer(context(), &t()->pivotSelection[sqi])->write_target_to(w);
				w.end_element(0, sml_sheet_pivotSelection_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, sml_sheet_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_sheet_extLst_literal);
			}
		}

		void CT_SheetViews_writer::write_target_to(xml_writer& w) {
			for (size_t sqi = 0; sqi<t()->sheetView.size(); ++sqi) {
				w.start_element(0, sml_sheet_sheetView_literal);
				_sheetView_writer.get_writer(context(), &t()->sheetView[sqi])->write_target_to(w);
				w.end_element(0, sml_sheet_sheetView_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, sml_sheet_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_sheet_extLst_literal);
			}
		}

		void CT_SheetFormatPr_writer::write_target_to(xml_writer& w) {
			if (t()->baseColWidth != 8U)
				w.attribute(0, sml_sheet_baseColWidth_literal, context()->serialize(t()->baseColWidth));
			if (t()->defaultColWidth.present())
				w.attribute(0, sml_sheet_defaultColWidth_literal, context()->serialize(t()->defaultColWidth.get()));
			w.attribute(0, sml_sheet_defaultRowHeight_literal, context()->serialize(t()->defaultRowHeight));
			if (t()->customHeight != false)
				w.attribute(0, sml_sheet_customHeight_literal, context()->serialize(t()->customHeight));
			if (t()->zeroHeight != false)
				w.attribute(0, sml_sheet_zeroHeight_literal, context()->serialize(t()->zeroHeight));
			if (t()->thickTop != false)
				w.attribute(0, sml_sheet_thickTop_literal, context()->serialize(t()->thickTop));
			if (t()->thickBottom != false)
				w.attribute(0, sml_sheet_thickBottom_literal, context()->serialize(t()->thickBottom));
			if (t()->outlineLevelRow != 0)
				w.attribute(0, sml_sheet_outlineLevelRow_literal, context()->serialize(t()->outlineLevelRow));
			if (t()->outlineLevelCol != 0)
				w.attribute(0, sml_sheet_outlineLevelCol_literal, context()->serialize(t()->outlineLevelCol));
		}

		void CT_Col_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_sheet_min_literal, context()->serialize(t()->min));
			w.attribute(0, sml_sheet_max_literal, context()->serialize(t()->max));
			if (t()->width.present())
				w.attribute(0, sml_sheet_width_literal, context()->serialize(t()->width.get()));
			if (t()->style != 0U)
				w.attribute(0, sml_sheet_style_literal, context()->serialize(t()->style));
			if (t()->hidden != false)
				w.attribute(0, sml_sheet_hidden_literal, context()->serialize(t()->hidden));
			if (t()->bestFit != false)
				w.attribute(0, sml_sheet_bestFit_literal, context()->serialize(t()->bestFit));
			if (t()->customWidth != false)
				w.attribute(0, sml_sheet_customWidth_literal, context()->serialize(t()->customWidth));
			if (t()->phonetic != false)
				w.attribute(0, sml_sheet_phonetic_literal, context()->serialize(t()->phonetic));
			if (t()->outlineLevel != 0)
				w.attribute(0, sml_sheet_outlineLevel_literal, context()->serialize(t()->outlineLevel));
			if (t()->collapsed != false)
				w.attribute(0, sml_sheet_collapsed_literal, context()->serialize(t()->collapsed));
		}

		void CT_Cols_writer::write_target_to(xml_writer& w) {
			for (size_t sqi = 0; sqi<t()->col.size(); ++sqi) {
				w.start_element(0, sml_sheet_col_literal);
				_col_writer.get_writer(context(), &t()->col[sqi])->write_target_to(w);
				w.end_element(0, sml_sheet_col_literal);
			}
		}

		void ST_CellSpan_writer::write_target_to(xml_writer& w) {
			w.write_element_value(context()->serialize(*t()));
		}

		void ST_CellSpans_writer::write_target_to(xml_writer& w) {
			ST_CellSpan_writer::write_target_to(w);
		}

		void CT_Row_writer::write_target_to(xml_writer& w) {
			if (t()->r.present())
				w.attribute(0, sml_sheet_r_literal, context()->serialize(t()->r.get()));
			if (t()->spans.present())
				w.attribute(0, sml_sheet_spans_literal, context()->serialize(t()->spans.get()));
			if (t()->s != 0U)
				w.attribute(0, sml_sheet_s_literal, context()->serialize(t()->s));
			if (t()->customFormat != false)
				w.attribute(0, sml_sheet_customFormat_literal, context()->serialize(t()->customFormat));
			if (t()->ht.present())
				w.attribute(0, sml_sheet_ht_literal, context()->serialize(t()->ht.get()));
			if (t()->hidden != false)
				w.attribute(0, sml_sheet_hidden_literal, context()->serialize(t()->hidden));
			if (t()->customHeight != false)
				w.attribute(0, sml_sheet_customHeight_literal, context()->serialize(t()->customHeight));
			if (t()->outlineLevel != 0)
				w.attribute(0, sml_sheet_outlineLevel_literal, context()->serialize(t()->outlineLevel));
			if (t()->collapsed != false)
				w.attribute(0, sml_sheet_collapsed_literal, context()->serialize(t()->collapsed));
			if (t()->thickTop != false)
				w.attribute(0, sml_sheet_thickTop_literal, context()->serialize(t()->thickTop));
			if (t()->thickBot != false)
				w.attribute(0, sml_sheet_thickBot_literal, context()->serialize(t()->thickBot));
			if (t()->ph != false)
				w.attribute(0, sml_sheet_ph_literal, context()->serialize(t()->ph));
			for (size_t sqi = 0; sqi<t()->c.size(); ++sqi) {
				w.start_element(0, sml_sheet_c_literal);
				_c_writer.get_writer(context(), &t()->c[sqi])->write_target_to(w);
				w.end_element(0, sml_sheet_c_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, sml_sheet_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_sheet_extLst_literal);
			}
		}

		void CT_SheetData_writer::write_target_to(xml_writer& w) {
			for (size_t sqi = 0; sqi<t()->row.size(); ++sqi) {
				w.start_element(0, sml_sheet_row_literal);
				_row_writer.get_writer(context(), &t()->row[sqi])->write_target_to(w);
				w.end_element(0, sml_sheet_row_literal);
			}
		}

		void CT_SheetCalcPr_writer::write_target_to(xml_writer& w) {
			if (t()->fullCalcOnLoad != false)
				w.attribute(0, sml_sheet_fullCalcOnLoad_literal, context()->serialize(t()->fullCalcOnLoad));
		}

		void CT_SheetProtection_writer::write_target_to(xml_writer& w) {
			if (t()->password.present())
				w.attribute(0, sml_sheet_password_literal, context()->serialize(t()->password.get()));
			if (t()->sheet != false)
				w.attribute(0, sml_sheet_sheet_literal, context()->serialize(t()->sheet));
			if (t()->objects != false)
				w.attribute(0, sml_sheet_objects_literal, context()->serialize(t()->objects));
			if (t()->scenarios != false)
				w.attribute(0, sml_sheet_scenarios_literal, context()->serialize(t()->scenarios));
			if (t()->formatCells != true)
				w.attribute(0, sml_sheet_formatCells_literal, context()->serialize(t()->formatCells));
			if (t()->formatColumns != true)
				w.attribute(0, sml_sheet_formatColumns_literal, context()->serialize(t()->formatColumns));
			if (t()->formatRows != true)
				w.attribute(0, sml_sheet_formatRows_literal, context()->serialize(t()->formatRows));
			if (t()->insertColumns != true)
				w.attribute(0, sml_sheet_insertColumns_literal, context()->serialize(t()->insertColumns));
			if (t()->insertRows != true)
				w.attribute(0, sml_sheet_insertRows_literal, context()->serialize(t()->insertRows));
			if (t()->insertHyperlinks != true)
				w.attribute(0, sml_sheet_insertHyperlinks_literal, context()->serialize(t()->insertHyperlinks));
			if (t()->deleteColumns != true)
				w.attribute(0, sml_sheet_deleteColumns_literal, context()->serialize(t()->deleteColumns));
			if (t()->deleteRows != true)
				w.attribute(0, sml_sheet_deleteRows_literal, context()->serialize(t()->deleteRows));
			if (t()->selectLockedCells != false)
				w.attribute(0, sml_sheet_selectLockedCells_literal, context()->serialize(t()->selectLockedCells));
			if (t()->sort != true)
				w.attribute(0, sml_sheet_sort_literal, context()->serialize(t()->sort));
			if (t()->autoFilter != true)
				w.attribute(0, sml_sheet_autoFilter_literal, context()->serialize(t()->autoFilter));
			if (t()->pivotTables != true)
				w.attribute(0, sml_sheet_pivotTables_literal, context()->serialize(t()->pivotTables));
			if (t()->selectUnlockedCells != false)
				w.attribute(0, sml_sheet_selectUnlockedCells_literal, context()->serialize(t()->selectUnlockedCells));
		}

		void CT_ProtectedRange_writer::write_target_to(xml_writer& w) {
			if (t()->password.present())
				w.attribute(0, sml_sheet_password_literal, context()->serialize(t()->password.get()));
			w.attribute(0, sml_sheet_sqref_literal, context()->serialize(t()->sqref));
			w.attribute(0, sml_sheet_name_literal, context()->serialize(t()->name));
			if (t()->securityDescriptor.present())
				w.attribute(0, sml_sheet_securityDescriptor_literal, context()->serialize(t()->securityDescriptor.get()));
		}

		void CT_ProtectedRanges_writer::write_target_to(xml_writer& w) {
			for (size_t sqi = 0; sqi<t()->protectedRange.size(); ++sqi) {
				w.start_element(0, sml_sheet_protectedRange_literal);
				_protectedRange_writer.get_writer(context(), &t()->protectedRange[sqi])->write_target_to(w);
				w.end_element(0, sml_sheet_protectedRange_literal);
			}
		}

		void CT_InputCells_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_sheet_r_literal, context()->serialize(t()->r));
			if (t()->deleted != false)
				w.attribute(0, sml_sheet_deleted_literal, context()->serialize(t()->deleted));
			if (t()->undone != false)
				w.attribute(0, sml_sheet_undone_literal, context()->serialize(t()->undone));
			w.attribute(0, sml_sheet_val_literal, context()->serialize(t()->val));
			if (t()->numFmtId.present())
				w.attribute(0, sml_sheet_numFmtId_literal, context()->serialize(t()->numFmtId.get()));
		}

		void CT_Scenario_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_sheet_name_literal, context()->serialize(t()->name));
			if (t()->locked != false)
				w.attribute(0, sml_sheet_locked_literal, context()->serialize(t()->locked));
			if (t()->hidden != false)
				w.attribute(0, sml_sheet_hidden_literal, context()->serialize(t()->hidden));
			if (t()->count.present())
				w.attribute(0, sml_sheet_count_literal, context()->serialize(t()->count.get()));
			if (t()->user.present())
				w.attribute(0, sml_sheet_user_literal, context()->serialize(t()->user.get()));
			if (t()->comment.present())
				w.attribute(0, sml_sheet_comment_literal, context()->serialize(t()->comment.get()));
			for (size_t sqi = 0; sqi<t()->inputCells.size(); ++sqi) {
				w.start_element(0, sml_sheet_inputCells_literal);
				_inputCells_writer.get_writer(context(), &t()->inputCells[sqi])->write_target_to(w);
				w.end_element(0, sml_sheet_inputCells_literal);
			}
		}

		void CT_Scenarios_writer::write_target_to(xml_writer& w) {
			if (t()->current.present())
				w.attribute(0, sml_sheet_current_literal, context()->serialize(t()->current.get()));
			if (t()->show.present())
				w.attribute(0, sml_sheet_show_literal, context()->serialize(t()->show.get()));
			if (t()->sqref.present())
				w.attribute(0, sml_sheet_sqref_literal, context()->serialize(t()->sqref.get()));
			for (size_t sqi = 0; sqi<t()->scenario.size(); ++sqi) {
				w.start_element(0, sml_sheet_scenario_literal);
				_scenario_writer.get_writer(context(), &t()->scenario[sqi])->write_target_to(w);
				w.end_element(0, sml_sheet_scenario_literal);
			}
		}

		void CT_DataRef_writer::write_target_to(xml_writer& w) {
			if (t()->ref.present())
				w.attribute(0, sml_sheet_ref_literal, context()->serialize(t()->ref.get()));
			if (t()->name.present())
				w.attribute(0, sml_sheet_name_literal, context()->serialize(t()->name.get()));
			if (t()->sheet.present())
				w.attribute(0, sml_sheet_sheet_literal, context()->serialize(t()->sheet.get()));
			if (t()->id.present())
				w.attribute(sml_sheet_r_literal, sml_sheet_id_literal, context()->serialize(t()->id.get()));
		}

		void CT_DataRefs_writer::write_target_to(xml_writer& w) {
			if (t()->count.present())
				w.attribute(0, sml_sheet_count_literal, context()->serialize(t()->count.get()));
			for (size_t sqi = 0; sqi<t()->dataRef.size(); ++sqi) {
				w.start_element(0, sml_sheet_dataRef_literal);
				_dataRef_writer.get_writer(context(), &t()->dataRef[sqi])->write_target_to(w);
				w.end_element(0, sml_sheet_dataRef_literal);
			}
		}

		void CT_DataConsolidate_writer::write_target_to(xml_writer& w) {
			if (t()->function != ST_DataConsolidateFunction::sum_literal)
				w.attribute(0, sml_sheet_function_literal, context()->serialize(t()->function));
			if (t()->leftLabels != false)
				w.attribute(0, sml_sheet_leftLabels_literal, context()->serialize(t()->leftLabels));
			if (t()->topLabels != false)
				w.attribute(0, sml_sheet_topLabels_literal, context()->serialize(t()->topLabels));
			if (t()->link != false)
				w.attribute(0, sml_sheet_link_literal, context()->serialize(t()->link));
			if (t()->dataRefs.present()) {
				w.start_element(0, sml_sheet_dataRefs_literal);
				_dataRefs_writer.get_writer(context(), &t()->dataRefs.get())->write_target_to(w);
				w.end_element(0, sml_sheet_dataRefs_literal);
			}
		}

		void CT_Break_writer::write_target_to(xml_writer& w) {
			if (t()->id != 0U)
				w.attribute(0, sml_sheet_id_literal, context()->serialize(t()->id));
			if (t()->min != 0U)
				w.attribute(0, sml_sheet_min_literal, context()->serialize(t()->min));
			if (t()->max != 0U)
				w.attribute(0, sml_sheet_max_literal, context()->serialize(t()->max));
			if (t()->man != false)
				w.attribute(0, sml_sheet_man_literal, context()->serialize(t()->man));
			if (t()->pt != false)
				w.attribute(0, sml_sheet_pt_literal, context()->serialize(t()->pt));
		}

		void CT_PageBreak_writer::write_target_to(xml_writer& w) {
			if (t()->count != 0U)
				w.attribute(0, sml_sheet_count_literal, context()->serialize(t()->count));
			if (t()->manualBreakCount != 0U)
				w.attribute(0, sml_sheet_manualBreakCount_literal, context()->serialize(t()->manualBreakCount));
			for (size_t sqi = 0; sqi<t()->brk.size(); ++sqi) {
				w.start_element(0, sml_sheet_brk_literal);
				_brk_writer.get_writer(context(), &t()->brk[sqi])->write_target_to(w);
				w.end_element(0, sml_sheet_brk_literal);
			}
		}

		void CT_PageMargins_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_sheet_left_literal, context()->serialize(t()->left));
			w.attribute(0, sml_sheet_right_literal, context()->serialize(t()->right));
			w.attribute(0, sml_sheet_top_literal, context()->serialize(t()->top));
			w.attribute(0, sml_sheet_bottom_literal, context()->serialize(t()->bottom));
			w.attribute(0, sml_sheet_header_literal, context()->serialize(t()->header));
			w.attribute(0, sml_sheet_footer_literal, context()->serialize(t()->footer));
		}

		void CT_PrintOptions_writer::write_target_to(xml_writer& w) {
			if (t()->horizontalCentered != false)
				w.attribute(0, sml_sheet_horizontalCentered_literal, context()->serialize(t()->horizontalCentered));
			if (t()->verticalCentered != false)
				w.attribute(0, sml_sheet_verticalCentered_literal, context()->serialize(t()->verticalCentered));
			if (t()->headings != false)
				w.attribute(0, sml_sheet_headings_literal, context()->serialize(t()->headings));
			if (t()->gridLines != false)
				w.attribute(0, sml_sheet_gridLines_literal, context()->serialize(t()->gridLines));
			if (t()->gridLinesSet != true)
				w.attribute(0, sml_sheet_gridLinesSet_literal, context()->serialize(t()->gridLinesSet));
		}

		void CT_PageSetup_writer::write_target_to(xml_writer& w) {
			if (t()->paperSize != 1U)
				w.attribute(0, sml_sheet_paperSize_literal, context()->serialize(t()->paperSize));
			if (t()->scale != 100U)
				w.attribute(0, sml_sheet_scale_literal, context()->serialize(t()->scale));
			if (t()->firstPageNumber != 1U)
				w.attribute(0, sml_sheet_firstPageNumber_literal, context()->serialize(t()->firstPageNumber));
			if (t()->fitToWidth != 1U)
				w.attribute(0, sml_sheet_fitToWidth_literal, context()->serialize(t()->fitToWidth));
			if (t()->fitToHeight != 1U)
				w.attribute(0, sml_sheet_fitToHeight_literal, context()->serialize(t()->fitToHeight));
			if (t()->pageOrder != ST_PageOrder::downThenOver_literal)
				w.attribute(0, sml_sheet_pageOrder_literal, context()->serialize(t()->pageOrder));
			if (t()->orientation != ST_Orientation::_default__literal)
				w.attribute(0, sml_sheet_orientation_literal, context()->serialize(t()->orientation));
			if (t()->usePrinterDefaults != true)
				w.attribute(0, sml_sheet_usePrinterDefaults_literal, context()->serialize(t()->usePrinterDefaults));
			if (t()->blackAndWhite != false)
				w.attribute(0, sml_sheet_blackAndWhite_literal, context()->serialize(t()->blackAndWhite));
			if (t()->draft != false)
				w.attribute(0, sml_sheet_draft_literal, context()->serialize(t()->draft));
			if (t()->cellComments != ST_CellComments::none_literal)
				w.attribute(0, sml_sheet_cellComments_literal, context()->serialize(t()->cellComments));
			if (t()->useFirstPageNumber != false)
				w.attribute(0, sml_sheet_useFirstPageNumber_literal, context()->serialize(t()->useFirstPageNumber));
			if (t()->errors != ST_PrintError::displayed_literal)
				w.attribute(0, sml_sheet_errors_literal, context()->serialize(t()->errors));
			if (t()->horizontalDpi != 600U)
				w.attribute(0, sml_sheet_horizontalDpi_literal, context()->serialize(t()->horizontalDpi));
			if (t()->verticalDpi != 600U)
				w.attribute(0, sml_sheet_verticalDpi_literal, context()->serialize(t()->verticalDpi));
			if (t()->copies != 1U)
				w.attribute(0, sml_sheet_copies_literal, context()->serialize(t()->copies));
			if (t()->id.present())
				w.attribute(sml_sheet_r_literal, sml_sheet_id_literal, context()->serialize(t()->id.get()));
		}

		void CT_HeaderFooter_writer::write_target_to(xml_writer& w) {
			if (t()->differentOddEven != false)
				w.attribute(0, sml_sheet_differentOddEven_literal, context()->serialize(t()->differentOddEven));
			if (t()->differentFirst != false)
				w.attribute(0, sml_sheet_differentFirst_literal, context()->serialize(t()->differentFirst));
			if (t()->scaleWithDoc != true)
				w.attribute(0, sml_sheet_scaleWithDoc_literal, context()->serialize(t()->scaleWithDoc));
			if (t()->alignWithMargins != true)
				w.attribute(0, sml_sheet_alignWithMargins_literal, context()->serialize(t()->alignWithMargins));
			if (t()->oddHeader.present()) {
				w.start_element(0, sml_sheet_oddHeader_literal);
				_oddHeader_writer.get_writer(context(), &t()->oddHeader.get())->write_target_to(w);
				w.end_element(0, sml_sheet_oddHeader_literal);
			}
			if (t()->oddFooter.present()) {
				w.start_element(0, sml_sheet_oddFooter_literal);
				_oddFooter_writer.get_writer(context(), &t()->oddFooter.get())->write_target_to(w);
				w.end_element(0, sml_sheet_oddFooter_literal);
			}
			if (t()->evenHeader.present()) {
				w.start_element(0, sml_sheet_evenHeader_literal);
				_evenHeader_writer.get_writer(context(), &t()->evenHeader.get())->write_target_to(w);
				w.end_element(0, sml_sheet_evenHeader_literal);
			}
			if (t()->evenFooter.present()) {
				w.start_element(0, sml_sheet_evenFooter_literal);
				_evenFooter_writer.get_writer(context(), &t()->evenFooter.get())->write_target_to(w);
				w.end_element(0, sml_sheet_evenFooter_literal);
			}
			if (t()->firstHeader.present()) {
				w.start_element(0, sml_sheet_firstHeader_literal);
				_firstHeader_writer.get_writer(context(), &t()->firstHeader.get())->write_target_to(w);
				w.end_element(0, sml_sheet_firstHeader_literal);
			}
			if (t()->firstFooter.present()) {
				w.start_element(0, sml_sheet_firstFooter_literal);
				_firstFooter_writer.get_writer(context(), &t()->firstFooter.get())->write_target_to(w);
				w.end_element(0, sml_sheet_firstFooter_literal);
			}
		}

		void CT_CustomSheetView_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_sheet_guid_literal, context()->serialize(t()->guid));
			if (t()->scale != 100U)
				w.attribute(0, sml_sheet_scale_literal, context()->serialize(t()->scale));
			if (t()->colorId != 64U)
				w.attribute(0, sml_sheet_colorId_literal, context()->serialize(t()->colorId));
			if (t()->showPageBreaks != false)
				w.attribute(0, sml_sheet_showPageBreaks_literal, context()->serialize(t()->showPageBreaks));
			if (t()->showFormulas != false)
				w.attribute(0, sml_sheet_showFormulas_literal, context()->serialize(t()->showFormulas));
			if (t()->showGridLines != true)
				w.attribute(0, sml_sheet_showGridLines_literal, context()->serialize(t()->showGridLines));
			if (t()->showRowCol != true)
				w.attribute(0, sml_sheet_showRowCol_literal, context()->serialize(t()->showRowCol));
			if (t()->outlineSymbols != true)
				w.attribute(0, sml_sheet_outlineSymbols_literal, context()->serialize(t()->outlineSymbols));
			if (t()->zeroValues != true)
				w.attribute(0, sml_sheet_zeroValues_literal, context()->serialize(t()->zeroValues));
			if (t()->fitToPage != false)
				w.attribute(0, sml_sheet_fitToPage_literal, context()->serialize(t()->fitToPage));
			if (t()->printArea != false)
				w.attribute(0, sml_sheet_printArea_literal, context()->serialize(t()->printArea));
			if (t()->filter != false)
				w.attribute(0, sml_sheet_filter_literal, context()->serialize(t()->filter));
			if (t()->showAutoFilter != false)
				w.attribute(0, sml_sheet_showAutoFilter_literal, context()->serialize(t()->showAutoFilter));
			if (t()->hiddenRows != false)
				w.attribute(0, sml_sheet_hiddenRows_literal, context()->serialize(t()->hiddenRows));
			if (t()->hiddenColumns != false)
				w.attribute(0, sml_sheet_hiddenColumns_literal, context()->serialize(t()->hiddenColumns));
			if (t()->state != ST_SheetState::visible_literal)
				w.attribute(0, sml_sheet_state_literal, context()->serialize(t()->state));
			if (t()->filterUnique != false)
				w.attribute(0, sml_sheet_filterUnique_literal, context()->serialize(t()->filterUnique));
			if (t()->view != ST_SheetViewType::normal_literal)
				w.attribute(0, sml_sheet_view_literal, context()->serialize(t()->view));
			if (t()->showRuler != true)
				w.attribute(0, sml_sheet_showRuler_literal, context()->serialize(t()->showRuler));
			if (t()->topLeftCell.present())
				w.attribute(0, sml_sheet_topLeftCell_literal, context()->serialize(t()->topLeftCell.get()));
			if (t()->pane.present()) {
				w.start_element(0, sml_sheet_pane_literal);
				_pane_writer.get_writer(context(), &t()->pane.get())->write_target_to(w);
				w.end_element(0, sml_sheet_pane_literal);
			}
			if (t()->selection.present()) {
				w.start_element(0, sml_sheet_selection_literal);
				_selection_writer.get_writer(context(), &t()->selection.get())->write_target_to(w);
				w.end_element(0, sml_sheet_selection_literal);
			}
			if (t()->rowBreaks.present()) {
				w.start_element(0, sml_sheet_rowBreaks_literal);
				_rowBreaks_writer.get_writer(context(), &t()->rowBreaks.get())->write_target_to(w);
				w.end_element(0, sml_sheet_rowBreaks_literal);
			}
			if (t()->colBreaks.present()) {
				w.start_element(0, sml_sheet_colBreaks_literal);
				_colBreaks_writer.get_writer(context(), &t()->colBreaks.get())->write_target_to(w);
				w.end_element(0, sml_sheet_colBreaks_literal);
			}
			if (t()->pageMargins.present()) {
				w.start_element(0, sml_sheet_pageMargins_literal);
				_pageMargins_writer.get_writer(context(), &t()->pageMargins.get())->write_target_to(w);
				w.end_element(0, sml_sheet_pageMargins_literal);
			}
			if (t()->printOptions.present()) {
				w.start_element(0, sml_sheet_printOptions_literal);
				_printOptions_writer.get_writer(context(), &t()->printOptions.get())->write_target_to(w);
				w.end_element(0, sml_sheet_printOptions_literal);
			}
			if (t()->pageSetup.present()) {
				w.start_element(0, sml_sheet_pageSetup_literal);
				_pageSetup_writer.get_writer(context(), &t()->pageSetup.get())->write_target_to(w);
				w.end_element(0, sml_sheet_pageSetup_literal);
			}
			if (t()->headerFooter.present()) {
				w.start_element(0, sml_sheet_headerFooter_literal);
				_headerFooter_writer.get_writer(context(), &t()->headerFooter.get())->write_target_to(w);
				w.end_element(0, sml_sheet_headerFooter_literal);
			}
			if (t()->autoFilter.present()) {
				w.start_element(0, sml_sheet_autoFilter_literal);
				_autoFilter_writer.get_writer(context(), &t()->autoFilter.get())->write_target_to(w);
				w.end_element(0, sml_sheet_autoFilter_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, sml_sheet_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_sheet_extLst_literal);
			}
		}

		void CT_CustomSheetViews_writer::write_target_to(xml_writer& w) {
			for (size_t sqi = 0; sqi<t()->customSheetView.size(); ++sqi) {
				w.start_element(0, sml_sheet_customSheetView_literal);
				_customSheetView_writer.get_writer(context(), &t()->customSheetView[sqi])->write_target_to(w);
				w.end_element(0, sml_sheet_customSheetView_literal);
			}
		}

		void CT_MergeCell_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_sheet_ref_literal, context()->serialize(t()->ref));
		}

		void CT_MergeCells_writer::write_target_to(xml_writer& w) {
			if (t()->count.present())
				w.attribute(0, sml_sheet_count_literal, context()->serialize(t()->count.get()));
			for (size_t sqi = 0; sqi<t()->mergeCell.size(); ++sqi) {
				w.start_element(0, sml_sheet_mergeCell_literal);
				_mergeCell_writer.get_writer(context(), &t()->mergeCell[sqi])->write_target_to(w);
				w.end_element(0, sml_sheet_mergeCell_literal);
			}
		}

		void CT_Cfvo_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_sheet_type_literal, context()->serialize(t()->type));
			if (t()->val.present())
				w.attribute(0, sml_sheet_val_literal, context()->serialize(t()->val.get()));
			if (t()->gte != true)
				w.attribute(0, sml_sheet_gte_literal, context()->serialize(t()->gte));
			if (t()->extLst.present()) {
				w.start_element(0, sml_sheet_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_sheet_extLst_literal);
			}
		}

		void CT_ColorScale_writer::write_target_to(xml_writer& w) {
			for (size_t sqi = 0; sqi<t()->cfvo.size(); ++sqi) {
				w.start_element(0, sml_sheet_cfvo_literal);
				_cfvo_writer.get_writer(context(), &t()->cfvo[sqi])->write_target_to(w);
				w.end_element(0, sml_sheet_cfvo_literal);
			}
			for (size_t sqi = 0; sqi<t()->color.size(); ++sqi) {
				w.start_element(0, sml_sheet_color_literal);
				_color_writer.get_writer(context(), &t()->color[sqi])->write_target_to(w);
				w.end_element(0, sml_sheet_color_literal);
			}
		}

		void CT_DataBar_writer::write_target_to(xml_writer& w) {
			if (t()->minLength != 10U)
				w.attribute(0, sml_sheet_minLength_literal, context()->serialize(t()->minLength));
			if (t()->maxLength != 90U)
				w.attribute(0, sml_sheet_maxLength_literal, context()->serialize(t()->maxLength));
			if (t()->showValue != true)
				w.attribute(0, sml_sheet_showValue_literal, context()->serialize(t()->showValue));
			for (size_t sqi = 0; sqi<t()->cfvo.size(); ++sqi) {
				w.start_element(0, sml_sheet_cfvo_literal);
				_cfvo_writer.get_writer(context(), &t()->cfvo[sqi])->write_target_to(w);
				w.end_element(0, sml_sheet_cfvo_literal);
			}
			w.start_element(0, sml_sheet_color_literal);
			_color_writer.get_writer(context(), &t()->color)->write_target_to(w);
			w.end_element(0, sml_sheet_color_literal);
		}

		void CT_IconSet_writer::write_target_to(xml_writer& w) {
			if (t()->iconSet != ST_IconSetType::_3TrafficLights1__literal)
				w.attribute(0, sml_sheet_iconSet_literal, context()->serialize(t()->iconSet));
			if (t()->showValue != true)
				w.attribute(0, sml_sheet_showValue_literal, context()->serialize(t()->showValue));
			if (t()->percent != true)
				w.attribute(0, sml_sheet_percent_literal, context()->serialize(t()->percent));
			if (t()->reverse != false)
				w.attribute(0, sml_sheet_reverse_literal, context()->serialize(t()->reverse));
			for (size_t sqi = 0; sqi<t()->cfvo.size(); ++sqi) {
				w.start_element(0, sml_sheet_cfvo_literal);
				_cfvo_writer.get_writer(context(), &t()->cfvo[sqi])->write_target_to(w);
				w.end_element(0, sml_sheet_cfvo_literal);
			}
		}

		void CT_CfRule_writer::write_target_to(xml_writer& w) {
			if (t()->type.present())
				w.attribute(0, sml_sheet_type_literal, context()->serialize(t()->type.get()));
			if (t()->dxfId.present())
				w.attribute(0, sml_sheet_dxfId_literal, context()->serialize(t()->dxfId.get()));
			w.attribute(0, sml_sheet_priority_literal, context()->serialize(t()->priority));
			if (t()->stopIfTrue != false)
				w.attribute(0, sml_sheet_stopIfTrue_literal, context()->serialize(t()->stopIfTrue));
			if (t()->aboveAverage != true)
				w.attribute(0, sml_sheet_aboveAverage_literal, context()->serialize(t()->aboveAverage));
			if (t()->percent != false)
				w.attribute(0, sml_sheet_percent_literal, context()->serialize(t()->percent));
			if (t()->bottom != false)
				w.attribute(0, sml_sheet_bottom_literal, context()->serialize(t()->bottom));
			if (t()->_operator_.present())
				w.attribute(0, sml_sheet__operator__literal, context()->serialize(t()->_operator_.get()));
			if (t()->text.present())
				w.attribute(0, sml_sheet_text_literal, context()->serialize(t()->text.get()));
			if (t()->timePeriod.present())
				w.attribute(0, sml_sheet_timePeriod_literal, context()->serialize(t()->timePeriod.get()));
			if (t()->rank.present())
				w.attribute(0, sml_sheet_rank_literal, context()->serialize(t()->rank.get()));
			if (t()->stdDev.present())
				w.attribute(0, sml_sheet_stdDev_literal, context()->serialize(t()->stdDev.get()));
			if (t()->equalAverage != false)
				w.attribute(0, sml_sheet_equalAverage_literal, context()->serialize(t()->equalAverage));
			for (size_t sqi = 0; sqi<t()->formula.size(); ++sqi) {
				w.start_element(0, sml_sheet_formula_literal);
				_formula_writer.get_writer(context(), &t()->formula[sqi])->write_target_to(w);
				w.end_element(0, sml_sheet_formula_literal);
			}
			if (t()->colorScale.present()) {
				w.start_element(0, sml_sheet_colorScale_literal);
				_colorScale_writer.get_writer(context(), &t()->colorScale.get())->write_target_to(w);
				w.end_element(0, sml_sheet_colorScale_literal);
			}
			if (t()->dataBar.present()) {
				w.start_element(0, sml_sheet_dataBar_literal);
				_dataBar_writer.get_writer(context(), &t()->dataBar.get())->write_target_to(w);
				w.end_element(0, sml_sheet_dataBar_literal);
			}
			if (t()->iconSet.present()) {
				w.start_element(0, sml_sheet_iconSet_literal);
				_iconSet_writer.get_writer(context(), &t()->iconSet.get())->write_target_to(w);
				w.end_element(0, sml_sheet_iconSet_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, sml_sheet_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_sheet_extLst_literal);
			}
		}

		void CT_ConditionalFormatting_writer::write_target_to(xml_writer& w) {
			if (t()->pivot != false)
				w.attribute(0, sml_sheet_pivot_literal, context()->serialize(t()->pivot));
			if (t()->sqref.present())
				w.attribute(0, sml_sheet_sqref_literal, context()->serialize(t()->sqref.get()));
			for (size_t sqi = 0; sqi<t()->cfRule.size(); ++sqi) {
				w.start_element(0, sml_sheet_cfRule_literal);
				_cfRule_writer.get_writer(context(), &t()->cfRule[sqi])->write_target_to(w);
				w.end_element(0, sml_sheet_cfRule_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, sml_sheet_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_sheet_extLst_literal);
			}
		}

		void CT_DataValidation_writer::write_target_to(xml_writer& w) {
			if (t()->type != ST_DataValidationType::none_literal)
				w.attribute(0, sml_sheet_type_literal, context()->serialize(t()->type));
			if (t()->errorStyle != ST_DataValidationErrorStyle::stop_literal)
				w.attribute(0, sml_sheet_errorStyle_literal, context()->serialize(t()->errorStyle));
			if (t()->imeMode != ST_DataValidationImeMode::noControl_literal)
				w.attribute(0, sml_sheet_imeMode_literal, context()->serialize(t()->imeMode));
			if (t()->_operator_ != ST_DataValidationOperator::between_literal)
				w.attribute(0, sml_sheet__operator__literal, context()->serialize(t()->_operator_));
			if (t()->allowBlank != false)
				w.attribute(0, sml_sheet_allowBlank_literal, context()->serialize(t()->allowBlank));
			if (t()->showDropDown != false)
				w.attribute(0, sml_sheet_showDropDown_literal, context()->serialize(t()->showDropDown));
			if (t()->showInputMessage != false)
				w.attribute(0, sml_sheet_showInputMessage_literal, context()->serialize(t()->showInputMessage));
			if (t()->showErrorMessage != false)
				w.attribute(0, sml_sheet_showErrorMessage_literal, context()->serialize(t()->showErrorMessage));
			if (t()->errorTitle.present())
				w.attribute(0, sml_sheet_errorTitle_literal, context()->serialize(t()->errorTitle.get()));
			if (t()->error.present())
				w.attribute(0, sml_sheet_error_literal, context()->serialize(t()->error.get()));
			if (t()->promptTitle.present())
				w.attribute(0, sml_sheet_promptTitle_literal, context()->serialize(t()->promptTitle.get()));
			if (t()->prompt.present())
				w.attribute(0, sml_sheet_prompt_literal, context()->serialize(t()->prompt.get()));
			w.attribute(0, sml_sheet_sqref_literal, context()->serialize(t()->sqref));
			if (t()->formula1.present()) {
				w.start_element(0, sml_sheet_formula1_literal);
				_formula1_writer.get_writer(context(), &t()->formula1.get())->write_target_to(w);
				w.end_element(0, sml_sheet_formula1_literal);
			}
			if (t()->formula2.present()) {
				w.start_element(0, sml_sheet_formula2_literal);
				_formula2_writer.get_writer(context(), &t()->formula2.get())->write_target_to(w);
				w.end_element(0, sml_sheet_formula2_literal);
			}
		}

		void CT_DataValidations_writer::write_target_to(xml_writer& w) {
			if (t()->disablePrompts != false)
				w.attribute(0, sml_sheet_disablePrompts_literal, context()->serialize(t()->disablePrompts));
			if (t()->xWindow.present())
				w.attribute(0, sml_sheet_xWindow_literal, context()->serialize(t()->xWindow.get()));
			if (t()->yWindow.present())
				w.attribute(0, sml_sheet_yWindow_literal, context()->serialize(t()->yWindow.get()));
			if (t()->count.present())
				w.attribute(0, sml_sheet_count_literal, context()->serialize(t()->count.get()));
			for (size_t sqi = 0; sqi<t()->dataValidation.size(); ++sqi) {
				w.start_element(0, sml_sheet_dataValidation_literal);
				_dataValidation_writer.get_writer(context(), &t()->dataValidation[sqi])->write_target_to(w);
				w.end_element(0, sml_sheet_dataValidation_literal);
			}
		}

		void CT_Hyperlink_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_sheet_ref_literal, context()->serialize(t()->ref));
			if (t()->id.present())
				w.attribute(sml_sheet_r_literal, sml_sheet_id_literal, context()->serialize(t()->id.get()));
			if (t()->location.present())
				w.attribute(0, sml_sheet_location_literal, context()->serialize(t()->location.get()));
			if (t()->tooltip.present())
				w.attribute(0, sml_sheet_tooltip_literal, context()->serialize(t()->tooltip.get()));
			if (t()->display.present())
				w.attribute(0, sml_sheet_display_literal, context()->serialize(t()->display.get()));
		}

		void CT_Hyperlinks_writer::write_target_to(xml_writer& w) {
			for (size_t sqi = 0; sqi<t()->hyperlink.size(); ++sqi) {
				w.start_element(0, sml_sheet_hyperlink_literal);
				_hyperlink_writer.get_writer(context(), &t()->hyperlink[sqi])->write_target_to(w);
				w.end_element(0, sml_sheet_hyperlink_literal);
			}
		}

		void CT_CustomProperty_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_sheet_name_literal, context()->serialize(t()->name));
			w.attribute(sml_sheet_r_literal, sml_sheet_id_literal, context()->serialize(t()->id));
		}

		void CT_CustomProperties_writer::write_target_to(xml_writer& w) {
			for (size_t sqi = 0; sqi<t()->customPr.size(); ++sqi) {
				w.start_element(0, sml_sheet_customPr_literal);
				_customPr_writer.get_writer(context(), &t()->customPr[sqi])->write_target_to(w);
				w.end_element(0, sml_sheet_customPr_literal);
			}
		}

		void CT_CellWatch_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_sheet_r_literal, context()->serialize(t()->r));
		}

		void CT_CellWatches_writer::write_target_to(xml_writer& w) {
			for (size_t sqi = 0; sqi<t()->cellWatch.size(); ++sqi) {
				w.start_element(0, sml_sheet_cellWatch_literal);
				_cellWatch_writer.get_writer(context(), &t()->cellWatch[sqi])->write_target_to(w);
				w.end_element(0, sml_sheet_cellWatch_literal);
			}
		}

		void CT_IgnoredError_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_sheet_sqref_literal, context()->serialize(t()->sqref));
			if (t()->evalError != false)
				w.attribute(0, sml_sheet_evalError_literal, context()->serialize(t()->evalError));
			if (t()->twoDigitTextYear != false)
				w.attribute(0, sml_sheet_twoDigitTextYear_literal, context()->serialize(t()->twoDigitTextYear));
			if (t()->numberStoredAsText != false)
				w.attribute(0, sml_sheet_numberStoredAsText_literal, context()->serialize(t()->numberStoredAsText));
			if (t()->formula != false)
				w.attribute(0, sml_sheet_formula_literal, context()->serialize(t()->formula));
			if (t()->formulaRange != false)
				w.attribute(0, sml_sheet_formulaRange_literal, context()->serialize(t()->formulaRange));
			if (t()->unlockedFormula != false)
				w.attribute(0, sml_sheet_unlockedFormula_literal, context()->serialize(t()->unlockedFormula));
			if (t()->emptyCellReference != false)
				w.attribute(0, sml_sheet_emptyCellReference_literal, context()->serialize(t()->emptyCellReference));
			if (t()->listDataValidation != false)
				w.attribute(0, sml_sheet_listDataValidation_literal, context()->serialize(t()->listDataValidation));
			if (t()->calculatedColumn != false)
				w.attribute(0, sml_sheet_calculatedColumn_literal, context()->serialize(t()->calculatedColumn));
		}

		void CT_IgnoredErrors_writer::write_target_to(xml_writer& w) {
			for (size_t sqi = 0; sqi<t()->ignoredError.size(); ++sqi) {
				w.start_element(0, sml_sheet_ignoredError_literal);
				_ignoredError_writer.get_writer(context(), &t()->ignoredError[sqi])->write_target_to(w);
				w.end_element(0, sml_sheet_ignoredError_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, sml_sheet_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_sheet_extLst_literal);
			}
		}

		void CT_CellSmartTagPr_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_sheet_key_literal, context()->serialize(t()->key));
			w.attribute(0, sml_sheet_val_literal, context()->serialize(t()->val));
		}

		void CT_CellSmartTag_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_sheet_type_literal, context()->serialize(t()->type));
			if (t()->deleted != false)
				w.attribute(0, sml_sheet_deleted_literal, context()->serialize(t()->deleted));
			if (t()->xmlBased != false)
				w.attribute(0, sml_sheet_xmlBased_literal, context()->serialize(t()->xmlBased));
			for (size_t sqi = 0; sqi<t()->cellSmartTagPr.size(); ++sqi) {
				w.start_element(0, sml_sheet_cellSmartTagPr_literal);
				_cellSmartTagPr_writer.get_writer(context(), &t()->cellSmartTagPr[sqi])->write_target_to(w);
				w.end_element(0, sml_sheet_cellSmartTagPr_literal);
			}
		}

		void CT_CellSmartTags_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_sheet_r_literal, context()->serialize(t()->r));
			for (size_t sqi = 0; sqi<t()->cellSmartTag.size(); ++sqi) {
				w.start_element(0, sml_sheet_cellSmartTag_literal);
				_cellSmartTag_writer.get_writer(context(), &t()->cellSmartTag[sqi])->write_target_to(w);
				w.end_element(0, sml_sheet_cellSmartTag_literal);
			}
		}

		void CT_SmartTags_writer::write_target_to(xml_writer& w) {
			for (size_t sqi = 0; sqi<t()->cellSmartTags.size(); ++sqi) {
				w.start_element(0, sml_sheet_cellSmartTags_literal);
				_cellSmartTags_writer.get_writer(context(), &t()->cellSmartTags[sqi])->write_target_to(w);
				w.end_element(0, sml_sheet_cellSmartTags_literal);
			}
		}

		void CT_Drawing_writer::write_target_to(xml_writer& w) {
			w.attribute(sml_sheet_r_literal, sml_sheet_id_literal, context()->serialize(t()->id));
		}

		void CT_LegacyDrawing_writer::write_target_to(xml_writer& w) {
			w.attribute(sml_sheet_r_literal, sml_sheet_id_literal, context()->serialize(t()->id));
		}

		void CT_OleObject_writer::write_target_to(xml_writer& w) {
			if (t()->progId.present())
				w.attribute(0, sml_sheet_progId_literal, context()->serialize(t()->progId.get()));
			if (t()->dvAspect != ST_DvAspect::DVASPECT_CONTENT_literal)
				w.attribute(0, sml_sheet_dvAspect_literal, context()->serialize(t()->dvAspect));
			if (t()->link.present())
				w.attribute(0, sml_sheet_link_literal, context()->serialize(t()->link.get()));
			if (t()->oleUpdate.present())
				w.attribute(0, sml_sheet_oleUpdate_literal, context()->serialize(t()->oleUpdate.get()));
			if (t()->autoLoad != false)
				w.attribute(0, sml_sheet_autoLoad_literal, context()->serialize(t()->autoLoad));
			w.attribute(0, sml_sheet_shapeId_literal, context()->serialize(t()->shapeId));
			if (t()->id.present())
				w.attribute(sml_sheet_r_literal, sml_sheet_id_literal, context()->serialize(t()->id.get()));
		}

		void CT_OleObjects_writer::write_target_to(xml_writer& w) {
			for (size_t sqi = 0; sqi<t()->oleObject.size(); ++sqi) {
				w.start_element(0, sml_sheet_oleObject_literal);
				_oleObject_writer.get_writer(context(), &t()->oleObject[sqi])->write_target_to(w);
				w.end_element(0, sml_sheet_oleObject_literal);
			}
		}

		void CT_Control_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_sheet_shapeId_literal, context()->serialize(t()->shapeId));
			w.attribute(sml_sheet_r_literal, sml_sheet_id_literal, context()->serialize(t()->id));
			if (t()->name.present())
				w.attribute(0, sml_sheet_name_literal, context()->serialize(t()->name.get()));
		}

		void CT_Controls_writer::write_target_to(xml_writer& w) {
			for (size_t sqi = 0; sqi<t()->control.size(); ++sqi) {
				w.start_element(0, sml_sheet_control_literal);
				_control_writer.get_writer(context(), &t()->control[sqi])->write_target_to(w);
				w.end_element(0, sml_sheet_control_literal);
			}
		}

		void CT_WebPublishItem_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_sheet_id_literal, context()->serialize(t()->id));
			w.attribute(0, sml_sheet_divId_literal, context()->serialize(t()->divId));
			w.attribute(0, sml_sheet_sourceType_literal, context()->serialize(t()->sourceType));
			if (t()->sourceRef.present())
				w.attribute(0, sml_sheet_sourceRef_literal, context()->serialize(t()->sourceRef.get()));
			if (t()->sourceObject.present())
				w.attribute(0, sml_sheet_sourceObject_literal, context()->serialize(t()->sourceObject.get()));
			w.attribute(0, sml_sheet_destinationFile_literal, context()->serialize(t()->destinationFile));
			if (t()->title.present())
				w.attribute(0, sml_sheet_title_literal, context()->serialize(t()->title.get()));
			if (t()->autoRepublish != false)
				w.attribute(0, sml_sheet_autoRepublish_literal, context()->serialize(t()->autoRepublish));
		}

		void CT_WebPublishItems_writer::write_target_to(xml_writer& w) {
			if (t()->count.present())
				w.attribute(0, sml_sheet_count_literal, context()->serialize(t()->count.get()));
			for (size_t sqi = 0; sqi<t()->webPublishItem.size(); ++sqi) {
				w.start_element(0, sml_sheet_webPublishItem_literal);
				_webPublishItem_writer.get_writer(context(), &t()->webPublishItem[sqi])->write_target_to(w);
				w.end_element(0, sml_sheet_webPublishItem_literal);
			}
		}

		void CT_TablePart_writer::write_target_to(xml_writer& w) {
			w.attribute(sml_sheet_r_literal, sml_sheet_id_literal, context()->serialize(t()->id));
		}

		void CT_TableParts_writer::write_target_to(xml_writer& w) {
			if (t()->count.present())
				w.attribute(0, sml_sheet_count_literal, context()->serialize(t()->count.get()));
			for (size_t sqi = 0; sqi<t()->tablePart.size(); ++sqi) {
				w.start_element(0, sml_sheet_tablePart_literal);
				_tablePart_writer.get_writer(context(), &t()->tablePart[sqi])->write_target_to(w);
				w.end_element(0, sml_sheet_tablePart_literal);
			}
		}

		void CT_Worksheet_writer::write_target_to(xml_writer& w) {
			if (t()->sheetPr.present()) {
				w.start_element(0, sml_sheet_sheetPr_literal);
				_sheetPr_writer.get_writer(context(), &t()->sheetPr.get())->write_target_to(w);
				w.end_element(0, sml_sheet_sheetPr_literal);
			}
			if (t()->dimension.present()) {
				w.start_element(0, sml_sheet_dimension_literal);
				_dimension_writer.get_writer(context(), &t()->dimension.get())->write_target_to(w);
				w.end_element(0, sml_sheet_dimension_literal);
			}
			if (t()->sheetViews.present()) {
				w.start_element(0, sml_sheet_sheetViews_literal);
				_sheetViews_writer.get_writer(context(), &t()->sheetViews.get())->write_target_to(w);
				w.end_element(0, sml_sheet_sheetViews_literal);
			}
			if (t()->sheetFormatPr.present()) {
				w.start_element(0, sml_sheet_sheetFormatPr_literal);
				_sheetFormatPr_writer.get_writer(context(), &t()->sheetFormatPr.get())->write_target_to(w);
				w.end_element(0, sml_sheet_sheetFormatPr_literal);
			}
			for (size_t sqi = 0; sqi<t()->cols.size(); ++sqi) {
				w.start_element(0, sml_sheet_cols_literal);
				_cols_writer.get_writer(context(), &t()->cols[sqi])->write_target_to(w);
				w.end_element(0, sml_sheet_cols_literal);
			}
			w.start_element(0, sml_sheet_sheetData_literal);
			_sheetData_writer.get_writer(context(), &t()->sheetData)->write_target_to(w);
			w.end_element(0, sml_sheet_sheetData_literal);
			if (t()->sheetCalcPr.present()) {
				w.start_element(0, sml_sheet_sheetCalcPr_literal);
				_sheetCalcPr_writer.get_writer(context(), &t()->sheetCalcPr.get())->write_target_to(w);
				w.end_element(0, sml_sheet_sheetCalcPr_literal);
			}
			if (t()->sheetProtection.present()) {
				w.start_element(0, sml_sheet_sheetProtection_literal);
				_sheetProtection_writer.get_writer(context(), &t()->sheetProtection.get())->write_target_to(w);
				w.end_element(0, sml_sheet_sheetProtection_literal);
			}
			if (t()->protectedRanges.present()) {
				w.start_element(0, sml_sheet_protectedRanges_literal);
				_protectedRanges_writer.get_writer(context(), &t()->protectedRanges.get())->write_target_to(w);
				w.end_element(0, sml_sheet_protectedRanges_literal);
			}
			if (t()->scenarios.present()) {
				w.start_element(0, sml_sheet_scenarios_literal);
				_scenarios_writer.get_writer(context(), &t()->scenarios.get())->write_target_to(w);
				w.end_element(0, sml_sheet_scenarios_literal);
			}
			if (t()->autoFilter.present()) {
				w.start_element(0, sml_sheet_autoFilter_literal);
				_autoFilter_writer.get_writer(context(), &t()->autoFilter.get())->write_target_to(w);
				w.end_element(0, sml_sheet_autoFilter_literal);
			}
			if (t()->sortState.present()) {
				w.start_element(0, sml_sheet_sortState_literal);
				_sortState_writer.get_writer(context(), &t()->sortState.get())->write_target_to(w);
				w.end_element(0, sml_sheet_sortState_literal);
			}
			if (t()->dataConsolidate.present()) {
				w.start_element(0, sml_sheet_dataConsolidate_literal);
				_dataConsolidate_writer.get_writer(context(), &t()->dataConsolidate.get())->write_target_to(w);
				w.end_element(0, sml_sheet_dataConsolidate_literal);
			}
			if (t()->customSheetViews.present()) {
				w.start_element(0, sml_sheet_customSheetViews_literal);
				_customSheetViews_writer.get_writer(context(), &t()->customSheetViews.get())->write_target_to(w);
				w.end_element(0, sml_sheet_customSheetViews_literal);
			}
			if (t()->mergeCells.present()) {
				w.start_element(0, sml_sheet_mergeCells_literal);
				_mergeCells_writer.get_writer(context(), &t()->mergeCells.get())->write_target_to(w);
				w.end_element(0, sml_sheet_mergeCells_literal);
			}
			if (t()->phoneticPr.present()) {
				w.start_element(0, sml_sheet_phoneticPr_literal);
				_phoneticPr_writer.get_writer(context(), &t()->phoneticPr.get())->write_target_to(w);
				w.end_element(0, sml_sheet_phoneticPr_literal);
			}
			for (size_t sqi = 0; sqi<t()->conditionalFormatting.size(); ++sqi) {
				w.start_element(0, sml_sheet_conditionalFormatting_literal);
				_conditionalFormatting_writer.get_writer(context(), &t()->conditionalFormatting[sqi])->write_target_to(w);
				w.end_element(0, sml_sheet_conditionalFormatting_literal);
			}
			if (t()->dataValidations.present()) {
				w.start_element(0, sml_sheet_dataValidations_literal);
				_dataValidations_writer.get_writer(context(), &t()->dataValidations.get())->write_target_to(w);
				w.end_element(0, sml_sheet_dataValidations_literal);
			}
			if (t()->hyperlinks.present()) {
				w.start_element(0, sml_sheet_hyperlinks_literal);
				_hyperlinks_writer.get_writer(context(), &t()->hyperlinks.get())->write_target_to(w);
				w.end_element(0, sml_sheet_hyperlinks_literal);
			}
			if (t()->printOptions.present()) {
				w.start_element(0, sml_sheet_printOptions_literal);
				_printOptions_writer.get_writer(context(), &t()->printOptions.get())->write_target_to(w);
				w.end_element(0, sml_sheet_printOptions_literal);
			}
			if (t()->pageMargins.present()) {
				w.start_element(0, sml_sheet_pageMargins_literal);
				_pageMargins_writer.get_writer(context(), &t()->pageMargins.get())->write_target_to(w);
				w.end_element(0, sml_sheet_pageMargins_literal);
			}
			if (t()->pageSetup.present()) {
				w.start_element(0, sml_sheet_pageSetup_literal);
				_pageSetup_writer.get_writer(context(), &t()->pageSetup.get())->write_target_to(w);
				w.end_element(0, sml_sheet_pageSetup_literal);
			}
			if (t()->headerFooter.present()) {
				w.start_element(0, sml_sheet_headerFooter_literal);
				_headerFooter_writer.get_writer(context(), &t()->headerFooter.get())->write_target_to(w);
				w.end_element(0, sml_sheet_headerFooter_literal);
			}
			if (t()->rowBreaks.present()) {
				w.start_element(0, sml_sheet_rowBreaks_literal);
				_rowBreaks_writer.get_writer(context(), &t()->rowBreaks.get())->write_target_to(w);
				w.end_element(0, sml_sheet_rowBreaks_literal);
			}
			if (t()->colBreaks.present()) {
				w.start_element(0, sml_sheet_colBreaks_literal);
				_colBreaks_writer.get_writer(context(), &t()->colBreaks.get())->write_target_to(w);
				w.end_element(0, sml_sheet_colBreaks_literal);
			}
			if (t()->customProperties.present()) {
				w.start_element(0, sml_sheet_customProperties_literal);
				_customProperties_writer.get_writer(context(), &t()->customProperties.get())->write_target_to(w);
				w.end_element(0, sml_sheet_customProperties_literal);
			}
			if (t()->cellWatches.present()) {
				w.start_element(0, sml_sheet_cellWatches_literal);
				_cellWatches_writer.get_writer(context(), &t()->cellWatches.get())->write_target_to(w);
				w.end_element(0, sml_sheet_cellWatches_literal);
			}
			if (t()->ignoredErrors.present()) {
				w.start_element(0, sml_sheet_ignoredErrors_literal);
				_ignoredErrors_writer.get_writer(context(), &t()->ignoredErrors.get())->write_target_to(w);
				w.end_element(0, sml_sheet_ignoredErrors_literal);
			}
			if (t()->smartTags.present()) {
				w.start_element(0, sml_sheet_smartTags_literal);
				_smartTags_writer.get_writer(context(), &t()->smartTags.get())->write_target_to(w);
				w.end_element(0, sml_sheet_smartTags_literal);
			}
			if (t()->drawing.present()) {
				w.start_element(0, sml_sheet_drawing_literal);
				_drawing_writer.get_writer(context(), &t()->drawing.get())->write_target_to(w);
				w.end_element(0, sml_sheet_drawing_literal);
			}
			if (t()->legacyDrawing.present()) {
				w.start_element(0, sml_sheet_legacyDrawing_literal);
				_legacyDrawing_writer.get_writer(context(), &t()->legacyDrawing.get())->write_target_to(w);
				w.end_element(0, sml_sheet_legacyDrawing_literal);
			}
			if (t()->legacyDrawingHF.present()) {
				w.start_element(0, sml_sheet_legacyDrawingHF_literal);
				_legacyDrawingHF_writer.get_writer(context(), &t()->legacyDrawingHF.get())->write_target_to(w);
				w.end_element(0, sml_sheet_legacyDrawingHF_literal);
			}
			if (t()->picture.present()) {
				w.start_element(0, sml_sheet_picture_literal);
				_picture_writer.get_writer(context(), &t()->picture.get())->write_target_to(w);
				w.end_element(0, sml_sheet_picture_literal);
			}
			if (t()->oleObjects.present()) {
				w.start_element(0, sml_sheet_oleObjects_literal);
				_oleObjects_writer.get_writer(context(), &t()->oleObjects.get())->write_target_to(w);
				w.end_element(0, sml_sheet_oleObjects_literal);
			}
			if (t()->controls.present()) {
				w.start_element(0, sml_sheet_controls_literal);
				_controls_writer.get_writer(context(), &t()->controls.get())->write_target_to(w);
				w.end_element(0, sml_sheet_controls_literal);
			}
			if (t()->webPublishItems.present()) {
				w.start_element(0, sml_sheet_webPublishItems_literal);
				_webPublishItems_writer.get_writer(context(), &t()->webPublishItems.get())->write_target_to(w);
				w.end_element(0, sml_sheet_webPublishItems_literal);
			}
			if (t()->tableParts.present()) {
				w.start_element(0, sml_sheet_tableParts_literal);
				_tableParts_writer.get_writer(context(), &t()->tableParts.get())->write_target_to(w);
				w.end_element(0, sml_sheet_tableParts_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, sml_sheet_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_sheet_extLst_literal);
			}
		}

		void CT_ChartsheetPr_writer::write_target_to(xml_writer& w) {
			if (t()->published != true)
				w.attribute(0, sml_sheet_published_literal, context()->serialize(t()->published));
			if (t()->codeName.present())
				w.attribute(0, sml_sheet_codeName_literal, context()->serialize(t()->codeName.get()));
			if (t()->tabColor.present()) {
				w.start_element(0, sml_sheet_tabColor_literal);
				_tabColor_writer.get_writer(context(), &t()->tabColor.get())->write_target_to(w);
				w.end_element(0, sml_sheet_tabColor_literal);
			}
		}

		void CT_ChartsheetView_writer::write_target_to(xml_writer& w) {
			if (t()->tabSelected != false)
				w.attribute(0, sml_sheet_tabSelected_literal, context()->serialize(t()->tabSelected));
			if (t()->zoomScale != 100U)
				w.attribute(0, sml_sheet_zoomScale_literal, context()->serialize(t()->zoomScale));
			w.attribute(0, sml_sheet_workbookViewId_literal, context()->serialize(t()->workbookViewId));
			if (t()->zoomToFit != false)
				w.attribute(0, sml_sheet_zoomToFit_literal, context()->serialize(t()->zoomToFit));
			if (t()->extLst.present()) {
				w.start_element(0, sml_sheet_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_sheet_extLst_literal);
			}
		}

		void CT_ChartsheetViews_writer::write_target_to(xml_writer& w) {
			for (size_t sqi = 0; sqi<t()->sheetView.size(); ++sqi) {
				w.start_element(0, sml_sheet_sheetView_literal);
				_sheetView_writer.get_writer(context(), &t()->sheetView[sqi])->write_target_to(w);
				w.end_element(0, sml_sheet_sheetView_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, sml_sheet_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_sheet_extLst_literal);
			}
		}

		void CT_ChartsheetProtection_writer::write_target_to(xml_writer& w) {
			if (t()->password.present())
				w.attribute(0, sml_sheet_password_literal, context()->serialize(t()->password.get()));
			if (t()->content != false)
				w.attribute(0, sml_sheet_content_literal, context()->serialize(t()->content));
			if (t()->objects != false)
				w.attribute(0, sml_sheet_objects_literal, context()->serialize(t()->objects));
		}

		void CT_CsPageSetup_writer::write_target_to(xml_writer& w) {
			if (t()->paperSize != 1U)
				w.attribute(0, sml_sheet_paperSize_literal, context()->serialize(t()->paperSize));
			if (t()->firstPageNumber != 1U)
				w.attribute(0, sml_sheet_firstPageNumber_literal, context()->serialize(t()->firstPageNumber));
			if (t()->orientation != ST_Orientation::_default__literal)
				w.attribute(0, sml_sheet_orientation_literal, context()->serialize(t()->orientation));
			if (t()->usePrinterDefaults != true)
				w.attribute(0, sml_sheet_usePrinterDefaults_literal, context()->serialize(t()->usePrinterDefaults));
			if (t()->blackAndWhite != false)
				w.attribute(0, sml_sheet_blackAndWhite_literal, context()->serialize(t()->blackAndWhite));
			if (t()->draft != false)
				w.attribute(0, sml_sheet_draft_literal, context()->serialize(t()->draft));
			if (t()->useFirstPageNumber != false)
				w.attribute(0, sml_sheet_useFirstPageNumber_literal, context()->serialize(t()->useFirstPageNumber));
			if (t()->horizontalDpi != 600U)
				w.attribute(0, sml_sheet_horizontalDpi_literal, context()->serialize(t()->horizontalDpi));
			if (t()->verticalDpi != 600U)
				w.attribute(0, sml_sheet_verticalDpi_literal, context()->serialize(t()->verticalDpi));
			if (t()->copies != 1U)
				w.attribute(0, sml_sheet_copies_literal, context()->serialize(t()->copies));
			if (t()->id.present())
				w.attribute(sml_sheet_r_literal, sml_sheet_id_literal, context()->serialize(t()->id.get()));
		}

		void CT_CustomChartsheetView_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_sheet_guid_literal, context()->serialize(t()->guid));
			if (t()->scale != 100U)
				w.attribute(0, sml_sheet_scale_literal, context()->serialize(t()->scale));
			if (t()->state != ST_SheetState::visible_literal)
				w.attribute(0, sml_sheet_state_literal, context()->serialize(t()->state));
			if (t()->zoomToFit != false)
				w.attribute(0, sml_sheet_zoomToFit_literal, context()->serialize(t()->zoomToFit));
			if (t()->pageMargins.present()) {
				w.start_element(0, sml_sheet_pageMargins_literal);
				_pageMargins_writer.get_writer(context(), &t()->pageMargins.get())->write_target_to(w);
				w.end_element(0, sml_sheet_pageMargins_literal);
			}
			if (t()->pageSetup.present()) {
				w.start_element(0, sml_sheet_pageSetup_literal);
				_pageSetup_writer.get_writer(context(), &t()->pageSetup.get())->write_target_to(w);
				w.end_element(0, sml_sheet_pageSetup_literal);
			}
			if (t()->headerFooter.present()) {
				w.start_element(0, sml_sheet_headerFooter_literal);
				_headerFooter_writer.get_writer(context(), &t()->headerFooter.get())->write_target_to(w);
				w.end_element(0, sml_sheet_headerFooter_literal);
			}
		}

		void CT_CustomChartsheetViews_writer::write_target_to(xml_writer& w) {
			for (size_t sqi = 0; sqi<t()->customSheetView.size(); ++sqi) {
				w.start_element(0, sml_sheet_customSheetView_literal);
				_customSheetView_writer.get_writer(context(), &t()->customSheetView[sqi])->write_target_to(w);
				w.end_element(0, sml_sheet_customSheetView_literal);
			}
		}

		void CT_Chartsheet_writer::write_target_to(xml_writer& w) {
			if (t()->sheetPr.present()) {
				w.start_element(0, sml_sheet_sheetPr_literal);
				_sheetPr_writer.get_writer(context(), &t()->sheetPr.get())->write_target_to(w);
				w.end_element(0, sml_sheet_sheetPr_literal);
			}
			w.start_element(0, sml_sheet_sheetViews_literal);
			_sheetViews_writer.get_writer(context(), &t()->sheetViews)->write_target_to(w);
			w.end_element(0, sml_sheet_sheetViews_literal);
			if (t()->sheetProtection.present()) {
				w.start_element(0, sml_sheet_sheetProtection_literal);
				_sheetProtection_writer.get_writer(context(), &t()->sheetProtection.get())->write_target_to(w);
				w.end_element(0, sml_sheet_sheetProtection_literal);
			}
			if (t()->customSheetViews.present()) {
				w.start_element(0, sml_sheet_customSheetViews_literal);
				_customSheetViews_writer.get_writer(context(), &t()->customSheetViews.get())->write_target_to(w);
				w.end_element(0, sml_sheet_customSheetViews_literal);
			}
			if (t()->pageMargins.present()) {
				w.start_element(0, sml_sheet_pageMargins_literal);
				_pageMargins_writer.get_writer(context(), &t()->pageMargins.get())->write_target_to(w);
				w.end_element(0, sml_sheet_pageMargins_literal);
			}
			if (t()->pageSetup.present()) {
				w.start_element(0, sml_sheet_pageSetup_literal);
				_pageSetup_writer.get_writer(context(), &t()->pageSetup.get())->write_target_to(w);
				w.end_element(0, sml_sheet_pageSetup_literal);
			}
			if (t()->headerFooter.present()) {
				w.start_element(0, sml_sheet_headerFooter_literal);
				_headerFooter_writer.get_writer(context(), &t()->headerFooter.get())->write_target_to(w);
				w.end_element(0, sml_sheet_headerFooter_literal);
			}
			w.start_element(0, sml_sheet_drawing_literal);
			_drawing_writer.get_writer(context(), &t()->drawing)->write_target_to(w);
			w.end_element(0, sml_sheet_drawing_literal);
			if (t()->legacyDrawing.present()) {
				w.start_element(0, sml_sheet_legacyDrawing_literal);
				_legacyDrawing_writer.get_writer(context(), &t()->legacyDrawing.get())->write_target_to(w);
				w.end_element(0, sml_sheet_legacyDrawing_literal);
			}
			if (t()->legacyDrawingHF.present()) {
				w.start_element(0, sml_sheet_legacyDrawingHF_literal);
				_legacyDrawingHF_writer.get_writer(context(), &t()->legacyDrawingHF.get())->write_target_to(w);
				w.end_element(0, sml_sheet_legacyDrawingHF_literal);
			}
			if (t()->picture.present()) {
				w.start_element(0, sml_sheet_picture_literal);
				_picture_writer.get_writer(context(), &t()->picture.get())->write_target_to(w);
				w.end_element(0, sml_sheet_picture_literal);
			}
			if (t()->webPublishItems.present()) {
				w.start_element(0, sml_sheet_webPublishItems_literal);
				_webPublishItems_writer.get_writer(context(), &t()->webPublishItems.get())->write_target_to(w);
				w.end_element(0, sml_sheet_webPublishItems_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, sml_sheet_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_sheet_extLst_literal);
			}
		}

		void CT_Dialogsheet_writer::write_target_to(xml_writer& w) {
			if (t()->sheetPr.present()) {
				w.start_element(0, sml_sheet_sheetPr_literal);
				_sheetPr_writer.get_writer(context(), &t()->sheetPr.get())->write_target_to(w);
				w.end_element(0, sml_sheet_sheetPr_literal);
			}
			if (t()->sheetViews.present()) {
				w.start_element(0, sml_sheet_sheetViews_literal);
				_sheetViews_writer.get_writer(context(), &t()->sheetViews.get())->write_target_to(w);
				w.end_element(0, sml_sheet_sheetViews_literal);
			}
			if (t()->sheetFormatPr.present()) {
				w.start_element(0, sml_sheet_sheetFormatPr_literal);
				_sheetFormatPr_writer.get_writer(context(), &t()->sheetFormatPr.get())->write_target_to(w);
				w.end_element(0, sml_sheet_sheetFormatPr_literal);
			}
			if (t()->sheetProtection.present()) {
				w.start_element(0, sml_sheet_sheetProtection_literal);
				_sheetProtection_writer.get_writer(context(), &t()->sheetProtection.get())->write_target_to(w);
				w.end_element(0, sml_sheet_sheetProtection_literal);
			}
			if (t()->customSheetViews.present()) {
				w.start_element(0, sml_sheet_customSheetViews_literal);
				_customSheetViews_writer.get_writer(context(), &t()->customSheetViews.get())->write_target_to(w);
				w.end_element(0, sml_sheet_customSheetViews_literal);
			}
			if (t()->printOptions.present()) {
				w.start_element(0, sml_sheet_printOptions_literal);
				_printOptions_writer.get_writer(context(), &t()->printOptions.get())->write_target_to(w);
				w.end_element(0, sml_sheet_printOptions_literal);
			}
			if (t()->pageMargins.present()) {
				w.start_element(0, sml_sheet_pageMargins_literal);
				_pageMargins_writer.get_writer(context(), &t()->pageMargins.get())->write_target_to(w);
				w.end_element(0, sml_sheet_pageMargins_literal);
			}
			if (t()->pageSetup.present()) {
				w.start_element(0, sml_sheet_pageSetup_literal);
				_pageSetup_writer.get_writer(context(), &t()->pageSetup.get())->write_target_to(w);
				w.end_element(0, sml_sheet_pageSetup_literal);
			}
			if (t()->headerFooter.present()) {
				w.start_element(0, sml_sheet_headerFooter_literal);
				_headerFooter_writer.get_writer(context(), &t()->headerFooter.get())->write_target_to(w);
				w.end_element(0, sml_sheet_headerFooter_literal);
			}
			if (t()->drawing.present()) {
				w.start_element(0, sml_sheet_drawing_literal);
				_drawing_writer.get_writer(context(), &t()->drawing.get())->write_target_to(w);
				w.end_element(0, sml_sheet_drawing_literal);
			}
			if (t()->legacyDrawing.present()) {
				w.start_element(0, sml_sheet_legacyDrawing_literal);
				_legacyDrawing_writer.get_writer(context(), &t()->legacyDrawing.get())->write_target_to(w);
				w.end_element(0, sml_sheet_legacyDrawing_literal);
			}
			if (t()->legacyDrawingHF.present()) {
				w.start_element(0, sml_sheet_legacyDrawingHF_literal);
				_legacyDrawingHF_writer.get_writer(context(), &t()->legacyDrawingHF.get())->write_target_to(w);
				w.end_element(0, sml_sheet_legacyDrawingHF_literal);
			}
			if (t()->oleObjects.present()) {
				w.start_element(0, sml_sheet_oleObjects_literal);
				_oleObjects_writer.get_writer(context(), &t()->oleObjects.get())->write_target_to(w);
				w.end_element(0, sml_sheet_oleObjects_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, sml_sheet_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_sheet_extLst_literal);
			}
		}

		void sml_sheet_writer::write_target_to(xml_writer& w) {
			if (t()->worksheet.present()) {
				w.start_element(0, sml_sheet_worksheet_literal);
					w.attribute(0, sml_sheet_xmlns_literal, sml_sheet_http_colon__slash__slash_schemas_dot_openxmlformats_dot_org_slash_spreadsheetml_slash_2006_slash_main_literal);
					w.attribute(sml_sheet_xmlns_literal, sml_sheet_r_literal, sml_sheet_http_colon__slash__slash_schemas_dot_openxmlformats_dot_org_slash_officeDocument_slash_2006_slash_relationships_literal);
					w.attribute(sml_sheet_xmlns_literal, sml_sheet_xsd_literal, sml_sheet_http_colon__slash__slash_www_dot_w3_dot_org_slash_2001_slash_XMLSchema_literal);
				_worksheet_writer.get_writer(context(), &t()->worksheet.get())->write_target_to(w);
				w.end_element(0, sml_sheet_worksheet_literal);
			}
			if (t()->chartsheet.present()) {
				w.start_element(0, sml_sheet_chartsheet_literal);
					w.attribute(0, sml_sheet_xmlns_literal, sml_sheet_http_colon__slash__slash_schemas_dot_openxmlformats_dot_org_slash_spreadsheetml_slash_2006_slash_main_literal);
					w.attribute(sml_sheet_xmlns_literal, sml_sheet_r_literal, sml_sheet_http_colon__slash__slash_schemas_dot_openxmlformats_dot_org_slash_officeDocument_slash_2006_slash_relationships_literal);
					w.attribute(sml_sheet_xmlns_literal, sml_sheet_xsd_literal, sml_sheet_http_colon__slash__slash_www_dot_w3_dot_org_slash_2001_slash_XMLSchema_literal);
				_chartsheet_writer.get_writer(context(), &t()->chartsheet.get())->write_target_to(w);
				w.end_element(0, sml_sheet_chartsheet_literal);
			}
			if (t()->dialogsheet.present()) {
				w.start_element(0, sml_sheet_dialogsheet_literal);
					w.attribute(0, sml_sheet_xmlns_literal, sml_sheet_http_colon__slash__slash_schemas_dot_openxmlformats_dot_org_slash_spreadsheetml_slash_2006_slash_main_literal);
					w.attribute(sml_sheet_xmlns_literal, sml_sheet_r_literal, sml_sheet_http_colon__slash__slash_schemas_dot_openxmlformats_dot_org_slash_officeDocument_slash_2006_slash_relationships_literal);
					w.attribute(sml_sheet_xmlns_literal, sml_sheet_xsd_literal, sml_sheet_http_colon__slash__slash_www_dot_w3_dot_org_slash_2001_slash_XMLSchema_literal);
				_dialogsheet_writer.get_writer(context(), &t()->dialogsheet.get())->write_target_to(w);
				w.end_element(0, sml_sheet_dialogsheet_literal);
			}
		}

	}
}
