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


#include "sml-sheet_readers.hpp"
#include "sml-sheet_literals.hpp"
#include <xio/xml/binding/driver.hpp>

namespace spreadsheetml
{
	namespace xio
	{
		void CT_CellFormula_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_t_literal))
			{
				driver()->context()->parse(value, t()->t);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_aca_literal))
			{
				driver()->context()->parse(value, t()->aca);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_ref_literal))
			{
				driver()->context()->parse(value, t()->ref.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_dt2D_literal))
			{
				driver()->context()->parse(value, t()->dt2D);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_dtr_literal))
			{
				driver()->context()->parse(value, t()->dtr);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_del1_literal))
			{
				driver()->context()->parse(value, t()->del1);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_del2_literal))
			{
				driver()->context()->parse(value, t()->del2);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_r1_literal))
			{
				driver()->context()->parse(value, t()->r1.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_r2_literal))
			{
				driver()->context()->parse(value, t()->r2.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_ca_literal))
			{
				driver()->context()->parse(value, t()->ca);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_si_literal))
			{
				driver()->context()->parse(value, t()->si.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_bx_literal))
			{
				driver()->context()->parse(value, t()->bx);
				return;
			}
			ST_Formula_reader::read_attribute(uri, localname, qname, value);
		}
		void CT_Cell_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_f_literal))
			{
				driver()->push(localname, _f_reader.get_reader(&t()->f.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_v_literal))
			{
				driver()->push(localname, _v_reader.get_reader(&t()->v.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_is_literal))
			{
				driver()->push(localname, _is_reader.get_reader(&t()->is.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_Cell_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_r_literal))
			{
				driver()->context()->parse(value, t()->r.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_s_literal))
			{
				driver()->context()->parse(value, t()->s);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_t_literal))
			{
				driver()->context()->parse(value, t()->t);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_cm_literal))
			{
				driver()->context()->parse(value, t()->cm);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_vm_literal))
			{
				driver()->context()->parse(value, t()->vm);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_ph_literal))
			{
				driver()->context()->parse(value, t()->ph);
				return;
			}
		}
		void CT_OutlinePr_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_applyStyles_literal))
			{
				driver()->context()->parse(value, t()->applyStyles);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_summaryBelow_literal))
			{
				driver()->context()->parse(value, t()->summaryBelow);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_summaryRight_literal))
			{
				driver()->context()->parse(value, t()->summaryRight);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_showOutlineSymbols_literal))
			{
				driver()->context()->parse(value, t()->showOutlineSymbols);
				return;
			}
		}
		void CT_PageSetUpPr_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_autoPageBreaks_literal))
			{
				driver()->context()->parse(value, t()->autoPageBreaks);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_fitToPage_literal))
			{
				driver()->context()->parse(value, t()->fitToPage);
				return;
			}
		}
		void CT_SheetPr_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_tabColor_literal))
			{
				driver()->push(localname, _tabColor_reader.get_reader(&t()->tabColor.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_outlinePr_literal))
			{
				driver()->push(localname, _outlinePr_reader.get_reader(&t()->outlinePr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_pageSetUpPr_literal))
			{
				driver()->push(localname, _pageSetUpPr_reader.get_reader(&t()->pageSetUpPr.getset()));
				return;
			}
		}
		void CT_SheetPr_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_syncHorizontal_literal))
			{
				driver()->context()->parse(value, t()->syncHorizontal);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_syncVertical_literal))
			{
				driver()->context()->parse(value, t()->syncVertical);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_syncRef_literal))
			{
				driver()->context()->parse(value, t()->syncRef.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_transitionEvaluation_literal))
			{
				driver()->context()->parse(value, t()->transitionEvaluation);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_transitionEntry_literal))
			{
				driver()->context()->parse(value, t()->transitionEntry);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_published_literal))
			{
				driver()->context()->parse(value, t()->published);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_codeName_literal))
			{
				driver()->context()->parse(value, t()->codeName.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_filterMode_literal))
			{
				driver()->context()->parse(value, t()->filterMode);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_enableFormatConditionsCalculation_literal))
			{
				driver()->context()->parse(value, t()->enableFormatConditionsCalculation);
				return;
			}
		}
		void CT_SheetDimension_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_ref_literal))
			{
				driver()->context()->parse(value, t()->ref);
				return;
			}
		}
		void CT_Pane_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_xSplit_literal))
			{
				driver()->context()->parse(value, t()->xSplit);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_ySplit_literal))
			{
				driver()->context()->parse(value, t()->ySplit);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_topLeftCell_literal))
			{
				driver()->context()->parse(value, t()->topLeftCell.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_activePane_literal))
			{
				driver()->context()->parse(value, t()->activePane);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_state_literal))
			{
				driver()->context()->parse(value, t()->state);
				return;
			}
		}
		void CT_Selection_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_pane_literal))
			{
				driver()->context()->parse(value, t()->pane);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_activeCell_literal))
			{
				driver()->context()->parse(value, t()->activeCell.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_activeCellId_literal))
			{
				driver()->context()->parse(value, t()->activeCellId);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_sqref_literal))
			{
				driver()->context()->parse(value, t()->sqref);
				return;
			}
		}
		void CT_PivotSelection_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_pivotArea_literal))
			{
				driver()->push(localname, _pivotArea_reader.get_reader(&t()->pivotArea));
				return;
			}
		}
		void CT_PivotSelection_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_pane_literal))
			{
				driver()->context()->parse(value, t()->pane);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_showHeader_literal))
			{
				driver()->context()->parse(value, t()->showHeader);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_label_literal))
			{
				driver()->context()->parse(value, t()->label);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_data_literal))
			{
				driver()->context()->parse(value, t()->data);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_extendable_literal))
			{
				driver()->context()->parse(value, t()->extendable);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_count_literal))
			{
				driver()->context()->parse(value, t()->count);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_axis_literal))
			{
				driver()->context()->parse(value, t()->axis.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_dimension_literal))
			{
				driver()->context()->parse(value, t()->dimension);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_start_literal))
			{
				driver()->context()->parse(value, t()->start);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_min_literal))
			{
				driver()->context()->parse(value, t()->min);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_max_literal))
			{
				driver()->context()->parse(value, t()->max);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_activeRow_literal))
			{
				driver()->context()->parse(value, t()->activeRow);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_activeCol_literal))
			{
				driver()->context()->parse(value, t()->activeCol);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_previousRow_literal))
			{
				driver()->context()->parse(value, t()->previousRow);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_previousCol_literal))
			{
				driver()->context()->parse(value, t()->previousCol);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_click_literal))
			{
				driver()->context()->parse(value, t()->click);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_id_literal))
			{
				driver()->context()->parse(value, t()->id.getset());
				return;
			}
		}
		void CT_SheetView_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_pane_literal))
			{
				driver()->push(localname, _pane_reader.get_reader(&t()->pane.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_selection_literal))
			{
				t()->selection.resize(t()->selection.size()+1);
				driver()->push(localname, _selection_reader.get_reader(&t()->selection.back()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_pivotSelection_literal))
			{
				t()->pivotSelection.resize(t()->pivotSelection.size()+1);
				driver()->push(localname, _pivotSelection_reader.get_reader(&t()->pivotSelection.back()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_SheetView_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_windowProtection_literal))
			{
				driver()->context()->parse(value, t()->windowProtection);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_showFormulas_literal))
			{
				driver()->context()->parse(value, t()->showFormulas);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_showGridLines_literal))
			{
				driver()->context()->parse(value, t()->showGridLines);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_showRowColHeaders_literal))
			{
				driver()->context()->parse(value, t()->showRowColHeaders);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_showZeros_literal))
			{
				driver()->context()->parse(value, t()->showZeros);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_rightToLeft_literal))
			{
				driver()->context()->parse(value, t()->rightToLeft);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_tabSelected_literal))
			{
				driver()->context()->parse(value, t()->tabSelected);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_showRuler_literal))
			{
				driver()->context()->parse(value, t()->showRuler);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_showOutlineSymbols_literal))
			{
				driver()->context()->parse(value, t()->showOutlineSymbols);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_defaultGridColor_literal))
			{
				driver()->context()->parse(value, t()->defaultGridColor);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_showWhiteSpace_literal))
			{
				driver()->context()->parse(value, t()->showWhiteSpace);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_view_literal))
			{
				driver()->context()->parse(value, t()->view);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_topLeftCell_literal))
			{
				driver()->context()->parse(value, t()->topLeftCell.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_colorId_literal))
			{
				driver()->context()->parse(value, t()->colorId);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_zoomScale_literal))
			{
				driver()->context()->parse(value, t()->zoomScale);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_zoomScaleNormal_literal))
			{
				driver()->context()->parse(value, t()->zoomScaleNormal);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_zoomScaleSheetLayoutView_literal))
			{
				driver()->context()->parse(value, t()->zoomScaleSheetLayoutView);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_zoomScalePageLayoutView_literal))
			{
				driver()->context()->parse(value, t()->zoomScalePageLayoutView);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_workbookViewId_literal))
			{
				driver()->context()->parse(value, t()->workbookViewId);
				return;
			}
		}
		void CT_SheetViews_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_sheetView_literal))
			{
				t()->sheetView.resize(t()->sheetView.size()+1);
				driver()->push(localname, _sheetView_reader.get_reader(&t()->sheetView.back()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_SheetFormatPr_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_baseColWidth_literal))
			{
				driver()->context()->parse(value, t()->baseColWidth);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_defaultColWidth_literal))
			{
				driver()->context()->parse(value, t()->defaultColWidth.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_defaultRowHeight_literal))
			{
				driver()->context()->parse(value, t()->defaultRowHeight);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_customHeight_literal))
			{
				driver()->context()->parse(value, t()->customHeight);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_zeroHeight_literal))
			{
				driver()->context()->parse(value, t()->zeroHeight);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_thickTop_literal))
			{
				driver()->context()->parse(value, t()->thickTop);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_thickBottom_literal))
			{
				driver()->context()->parse(value, t()->thickBottom);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_outlineLevelRow_literal))
			{
				driver()->context()->parse(value, t()->outlineLevelRow);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_outlineLevelCol_literal))
			{
				driver()->context()->parse(value, t()->outlineLevelCol);
				return;
			}
		}
		void CT_Col_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_min_literal))
			{
				driver()->context()->parse(value, t()->min);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_max_literal))
			{
				driver()->context()->parse(value, t()->max);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_width_literal))
			{
				driver()->context()->parse(value, t()->width.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_style_literal))
			{
				driver()->context()->parse(value, t()->style);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_hidden_literal))
			{
				driver()->context()->parse(value, t()->hidden);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_bestFit_literal))
			{
				driver()->context()->parse(value, t()->bestFit);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_customWidth_literal))
			{
				driver()->context()->parse(value, t()->customWidth);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_phonetic_literal))
			{
				driver()->context()->parse(value, t()->phonetic);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_outlineLevel_literal))
			{
				driver()->context()->parse(value, t()->outlineLevel);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_collapsed_literal))
			{
				driver()->context()->parse(value, t()->collapsed);
				return;
			}
		}
		void CT_Cols_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_col_literal))
			{
				t()->col.resize(t()->col.size()+1);
				driver()->push(localname, _col_reader.get_reader(&t()->col.back()));
				return;
			}
		}
		void ST_CellSpan_reader::read_value(const xstring& val) {{ driver()->context()->parse(val, *t()); }}
		void CT_Row_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_c_literal))
			{
				t()->c.resize(t()->c.size()+1);
				driver()->push(localname, _c_reader.get_reader(&t()->c.back()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_Row_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_r_literal))
			{
				driver()->context()->parse(value, t()->r.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_spans_literal))
			{
				driver()->context()->parse(value, t()->spans.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_s_literal))
			{
				driver()->context()->parse(value, t()->s);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_customFormat_literal))
			{
				driver()->context()->parse(value, t()->customFormat);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_ht_literal))
			{
				driver()->context()->parse(value, t()->ht.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_hidden_literal))
			{
				driver()->context()->parse(value, t()->hidden);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_customHeight_literal))
			{
				driver()->context()->parse(value, t()->customHeight);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_outlineLevel_literal))
			{
				driver()->context()->parse(value, t()->outlineLevel);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_collapsed_literal))
			{
				driver()->context()->parse(value, t()->collapsed);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_thickTop_literal))
			{
				driver()->context()->parse(value, t()->thickTop);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_thickBot_literal))
			{
				driver()->context()->parse(value, t()->thickBot);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_ph_literal))
			{
				driver()->context()->parse(value, t()->ph);
				return;
			}
		}
		void CT_SheetData_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_row_literal))
			{
				t()->row.resize(t()->row.size()+1);
				driver()->push(localname, _row_reader.get_reader(&t()->row.back()));
				return;
			}
		}
		void CT_SheetCalcPr_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_fullCalcOnLoad_literal))
			{
				driver()->context()->parse(value, t()->fullCalcOnLoad);
				return;
			}
		}
		void CT_SheetProtection_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_password_literal))
			{
				driver()->context()->parse(value, t()->password.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_sheet_literal))
			{
				driver()->context()->parse(value, t()->sheet);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_objects_literal))
			{
				driver()->context()->parse(value, t()->objects);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_scenarios_literal))
			{
				driver()->context()->parse(value, t()->scenarios);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_formatCells_literal))
			{
				driver()->context()->parse(value, t()->formatCells);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_formatColumns_literal))
			{
				driver()->context()->parse(value, t()->formatColumns);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_formatRows_literal))
			{
				driver()->context()->parse(value, t()->formatRows);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_insertColumns_literal))
			{
				driver()->context()->parse(value, t()->insertColumns);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_insertRows_literal))
			{
				driver()->context()->parse(value, t()->insertRows);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_insertHyperlinks_literal))
			{
				driver()->context()->parse(value, t()->insertHyperlinks);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_deleteColumns_literal))
			{
				driver()->context()->parse(value, t()->deleteColumns);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_deleteRows_literal))
			{
				driver()->context()->parse(value, t()->deleteRows);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_selectLockedCells_literal))
			{
				driver()->context()->parse(value, t()->selectLockedCells);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_sort_literal))
			{
				driver()->context()->parse(value, t()->sort);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_autoFilter_literal))
			{
				driver()->context()->parse(value, t()->autoFilter);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_pivotTables_literal))
			{
				driver()->context()->parse(value, t()->pivotTables);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_selectUnlockedCells_literal))
			{
				driver()->context()->parse(value, t()->selectUnlockedCells);
				return;
			}
		}
		void CT_ProtectedRange_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_password_literal))
			{
				driver()->context()->parse(value, t()->password.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_sqref_literal))
			{
				driver()->context()->parse(value, t()->sqref);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_name_literal))
			{
				driver()->context()->parse(value, t()->name);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_securityDescriptor_literal))
			{
				driver()->context()->parse(value, t()->securityDescriptor.getset());
				return;
			}
		}
		void CT_ProtectedRanges_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_protectedRange_literal))
			{
				t()->protectedRange.resize(t()->protectedRange.size()+1);
				driver()->push(localname, _protectedRange_reader.get_reader(&t()->protectedRange.back()));
				return;
			}
		}
		void CT_InputCells_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_r_literal))
			{
				driver()->context()->parse(value, t()->r);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_deleted_literal))
			{
				driver()->context()->parse(value, t()->deleted);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_undone_literal))
			{
				driver()->context()->parse(value, t()->undone);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_val_literal))
			{
				driver()->context()->parse(value, t()->val);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_numFmtId_literal))
			{
				driver()->context()->parse(value, t()->numFmtId.getset());
				return;
			}
		}
		void CT_Scenario_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_inputCells_literal))
			{
				t()->inputCells.resize(t()->inputCells.size()+1);
				driver()->push(localname, _inputCells_reader.get_reader(&t()->inputCells.back()));
				return;
			}
		}
		void CT_Scenario_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_name_literal))
			{
				driver()->context()->parse(value, t()->name);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_locked_literal))
			{
				driver()->context()->parse(value, t()->locked);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_hidden_literal))
			{
				driver()->context()->parse(value, t()->hidden);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_user_literal))
			{
				driver()->context()->parse(value, t()->user.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_comment_literal))
			{
				driver()->context()->parse(value, t()->comment.getset());
				return;
			}
		}
		void CT_Scenarios_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_scenario_literal))
			{
				t()->scenario.resize(t()->scenario.size()+1);
				driver()->push(localname, _scenario_reader.get_reader(&t()->scenario.back()));
				return;
			}
		}
		void CT_Scenarios_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_current_literal))
			{
				driver()->context()->parse(value, t()->current.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_show_literal))
			{
				driver()->context()->parse(value, t()->show.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_sqref_literal))
			{
				driver()->context()->parse(value, t()->sqref.getset());
				return;
			}
		}
		void CT_DataRef_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_ref_literal))
			{
				driver()->context()->parse(value, t()->ref.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_name_literal))
			{
				driver()->context()->parse(value, t()->name.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_sheet_literal))
			{
				driver()->context()->parse(value, t()->sheet.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_id_literal))
			{
				driver()->context()->parse(value, t()->id.getset());
				return;
			}
		}
		void CT_DataRefs_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_dataRef_literal))
			{
				t()->dataRef.resize(t()->dataRef.size()+1);
				driver()->push(localname, _dataRef_reader.get_reader(&t()->dataRef.back()));
				return;
			}
		}
		void CT_DataRefs_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
		}
		void CT_DataConsolidate_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_dataRefs_literal))
			{
				driver()->push(localname, _dataRefs_reader.get_reader(&t()->dataRefs.getset()));
				return;
			}
		}
		void CT_DataConsolidate_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_function_literal))
			{
				driver()->context()->parse(value, t()->function);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_leftLabels_literal))
			{
				driver()->context()->parse(value, t()->leftLabels);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_topLabels_literal))
			{
				driver()->context()->parse(value, t()->topLabels);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_link_literal))
			{
				driver()->context()->parse(value, t()->link);
				return;
			}
		}
		void CT_Break_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_id_literal))
			{
				driver()->context()->parse(value, t()->id);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_min_literal))
			{
				driver()->context()->parse(value, t()->min);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_max_literal))
			{
				driver()->context()->parse(value, t()->max);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_man_literal))
			{
				driver()->context()->parse(value, t()->man);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_pt_literal))
			{
				driver()->context()->parse(value, t()->pt);
				return;
			}
		}
		void CT_PageBreak_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_brk_literal))
			{
				t()->brk.resize(t()->brk.size()+1);
				driver()->push(localname, _brk_reader.get_reader(&t()->brk.back()));
				return;
			}
		}
		void CT_PageBreak_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_count_literal))
			{
				driver()->context()->parse(value, t()->count);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_manualBreakCount_literal))
			{
				driver()->context()->parse(value, t()->manualBreakCount);
				return;
			}
		}
		void CT_PageMargins_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_left_literal))
			{
				driver()->context()->parse(value, t()->left);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_right_literal))
			{
				driver()->context()->parse(value, t()->right);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_top_literal))
			{
				driver()->context()->parse(value, t()->top);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_bottom_literal))
			{
				driver()->context()->parse(value, t()->bottom);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_header_literal))
			{
				driver()->context()->parse(value, t()->header);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_footer_literal))
			{
				driver()->context()->parse(value, t()->footer);
				return;
			}
		}
		void CT_PrintOptions_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_horizontalCentered_literal))
			{
				driver()->context()->parse(value, t()->horizontalCentered);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_verticalCentered_literal))
			{
				driver()->context()->parse(value, t()->verticalCentered);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_headings_literal))
			{
				driver()->context()->parse(value, t()->headings);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_gridLines_literal))
			{
				driver()->context()->parse(value, t()->gridLines);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_gridLinesSet_literal))
			{
				driver()->context()->parse(value, t()->gridLinesSet);
				return;
			}
		}
		void CT_PageSetup_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_paperSize_literal))
			{
				driver()->context()->parse(value, t()->paperSize);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_scale_literal))
			{
				driver()->context()->parse(value, t()->scale);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_firstPageNumber_literal))
			{
				driver()->context()->parse(value, t()->firstPageNumber);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_fitToWidth_literal))
			{
				driver()->context()->parse(value, t()->fitToWidth);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_fitToHeight_literal))
			{
				driver()->context()->parse(value, t()->fitToHeight);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_pageOrder_literal))
			{
				driver()->context()->parse(value, t()->pageOrder);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_orientation_literal))
			{
				driver()->context()->parse(value, t()->orientation);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_usePrinterDefaults_literal))
			{
				driver()->context()->parse(value, t()->usePrinterDefaults);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_blackAndWhite_literal))
			{
				driver()->context()->parse(value, t()->blackAndWhite);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_draft_literal))
			{
				driver()->context()->parse(value, t()->draft);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_cellComments_literal))
			{
				driver()->context()->parse(value, t()->cellComments);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_useFirstPageNumber_literal))
			{
				driver()->context()->parse(value, t()->useFirstPageNumber);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_errors_literal))
			{
				driver()->context()->parse(value, t()->errors);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_horizontalDpi_literal))
			{
				driver()->context()->parse(value, t()->horizontalDpi);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_verticalDpi_literal))
			{
				driver()->context()->parse(value, t()->verticalDpi);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_copies_literal))
			{
				driver()->context()->parse(value, t()->copies);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_id_literal))
			{
				driver()->context()->parse(value, t()->id.getset());
				return;
			}
		}
		void CT_HeaderFooter_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_oddHeader_literal))
			{
				driver()->push(localname, _oddHeader_reader.get_reader(&t()->oddHeader.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_oddFooter_literal))
			{
				driver()->push(localname, _oddFooter_reader.get_reader(&t()->oddFooter.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_evenHeader_literal))
			{
				driver()->push(localname, _evenHeader_reader.get_reader(&t()->evenHeader.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_evenFooter_literal))
			{
				driver()->push(localname, _evenFooter_reader.get_reader(&t()->evenFooter.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_firstHeader_literal))
			{
				driver()->push(localname, _firstHeader_reader.get_reader(&t()->firstHeader.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_firstFooter_literal))
			{
				driver()->push(localname, _firstFooter_reader.get_reader(&t()->firstFooter.getset()));
				return;
			}
		}
		void CT_HeaderFooter_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_differentOddEven_literal))
			{
				driver()->context()->parse(value, t()->differentOddEven);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_differentFirst_literal))
			{
				driver()->context()->parse(value, t()->differentFirst);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_scaleWithDoc_literal))
			{
				driver()->context()->parse(value, t()->scaleWithDoc);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_alignWithMargins_literal))
			{
				driver()->context()->parse(value, t()->alignWithMargins);
				return;
			}
		}
		void CT_CustomSheetView_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_pane_literal))
			{
				driver()->push(localname, _pane_reader.get_reader(&t()->pane.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_selection_literal))
			{
				driver()->push(localname, _selection_reader.get_reader(&t()->selection.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_rowBreaks_literal))
			{
				driver()->push(localname, _rowBreaks_reader.get_reader(&t()->rowBreaks.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_colBreaks_literal))
			{
				driver()->push(localname, _colBreaks_reader.get_reader(&t()->colBreaks.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_pageMargins_literal))
			{
				driver()->push(localname, _pageMargins_reader.get_reader(&t()->pageMargins.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_printOptions_literal))
			{
				driver()->push(localname, _printOptions_reader.get_reader(&t()->printOptions.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_pageSetup_literal))
			{
				driver()->push(localname, _pageSetup_reader.get_reader(&t()->pageSetup.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_headerFooter_literal))
			{
				driver()->push(localname, _headerFooter_reader.get_reader(&t()->headerFooter.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_autoFilter_literal))
			{
				driver()->push(localname, _autoFilter_reader.get_reader(&t()->autoFilter.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_CustomSheetView_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_guid_literal))
			{
				driver()->context()->parse(value, t()->guid);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_scale_literal))
			{
				driver()->context()->parse(value, t()->scale);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_colorId_literal))
			{
				driver()->context()->parse(value, t()->colorId);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_showPageBreaks_literal))
			{
				driver()->context()->parse(value, t()->showPageBreaks);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_showFormulas_literal))
			{
				driver()->context()->parse(value, t()->showFormulas);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_showGridLines_literal))
			{
				driver()->context()->parse(value, t()->showGridLines);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_showRowCol_literal))
			{
				driver()->context()->parse(value, t()->showRowCol);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_outlineSymbols_literal))
			{
				driver()->context()->parse(value, t()->outlineSymbols);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_zeroValues_literal))
			{
				driver()->context()->parse(value, t()->zeroValues);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_fitToPage_literal))
			{
				driver()->context()->parse(value, t()->fitToPage);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_printArea_literal))
			{
				driver()->context()->parse(value, t()->printArea);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_filter_literal))
			{
				driver()->context()->parse(value, t()->filter);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_showAutoFilter_literal))
			{
				driver()->context()->parse(value, t()->showAutoFilter);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_hiddenRows_literal))
			{
				driver()->context()->parse(value, t()->hiddenRows);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_hiddenColumns_literal))
			{
				driver()->context()->parse(value, t()->hiddenColumns);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_state_literal))
			{
				driver()->context()->parse(value, t()->state);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_filterUnique_literal))
			{
				driver()->context()->parse(value, t()->filterUnique);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_view_literal))
			{
				driver()->context()->parse(value, t()->view);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_showRuler_literal))
			{
				driver()->context()->parse(value, t()->showRuler);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_topLeftCell_literal))
			{
				driver()->context()->parse(value, t()->topLeftCell.getset());
				return;
			}
		}
		void CT_CustomSheetViews_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_customSheetView_literal))
			{
				t()->customSheetView.resize(t()->customSheetView.size()+1);
				driver()->push(localname, _customSheetView_reader.get_reader(&t()->customSheetView.back()));
				return;
			}
		}
		void CT_MergeCell_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_ref_literal))
			{
				driver()->context()->parse(value, t()->ref);
				return;
			}
		}
		void CT_MergeCells_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_mergeCell_literal))
			{
				t()->mergeCell.resize(t()->mergeCell.size()+1);
				driver()->push(localname, _mergeCell_reader.get_reader(&t()->mergeCell.back()));
				return;
			}
		}
		void CT_MergeCells_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
		}
		void CT_Cfvo_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_Cfvo_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_type_literal))
			{
				driver()->context()->parse(value, t()->type);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_val_literal))
			{
				driver()->context()->parse(value, t()->val.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_gte_literal))
			{
				driver()->context()->parse(value, t()->gte);
				return;
			}
		}
		void CT_ColorScale_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_cfvo_literal))
			{
				t()->cfvo.resize(t()->cfvo.size()+1);
				driver()->push(localname, _cfvo_reader.get_reader(&t()->cfvo.back()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_color_literal))
			{
				t()->color.resize(t()->color.size()+1);
				driver()->push(localname, _color_reader.get_reader(&t()->color.back()));
				return;
			}
		}
		void CT_DataBar_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_cfvo_literal))
			{
				t()->cfvo.resize(t()->cfvo.size()+1);
				driver()->push(localname, _cfvo_reader.get_reader(&t()->cfvo.back()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_color_literal))
			{
				driver()->push(localname, _color_reader.get_reader(&t()->color));
				return;
			}
		}
		void CT_DataBar_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_minLength_literal))
			{
				driver()->context()->parse(value, t()->minLength);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_maxLength_literal))
			{
				driver()->context()->parse(value, t()->maxLength);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_showValue_literal))
			{
				driver()->context()->parse(value, t()->showValue);
				return;
			}
		}
		void CT_IconSet_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_cfvo_literal))
			{
				t()->cfvo.resize(t()->cfvo.size()+1);
				driver()->push(localname, _cfvo_reader.get_reader(&t()->cfvo.back()));
				return;
			}
		}
		void CT_IconSet_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_iconSet_literal))
			{
				driver()->context()->parse(value, t()->iconSet);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_showValue_literal))
			{
				driver()->context()->parse(value, t()->showValue);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_percent_literal))
			{
				driver()->context()->parse(value, t()->percent);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_reverse_literal))
			{
				driver()->context()->parse(value, t()->reverse);
				return;
			}
		}
		void CT_CfRule_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_formula_literal))
			{
				t()->formula.resize(t()->formula.size()+1);
				driver()->push(localname, _formula_reader.get_reader(&t()->formula.back()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_colorScale_literal))
			{
				driver()->push(localname, _colorScale_reader.get_reader(&t()->colorScale.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_dataBar_literal))
			{
				driver()->push(localname, _dataBar_reader.get_reader(&t()->dataBar.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_iconSet_literal))
			{
				driver()->push(localname, _iconSet_reader.get_reader(&t()->iconSet.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_CfRule_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_type_literal))
			{
				driver()->context()->parse(value, t()->type.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_dxfId_literal))
			{
				driver()->context()->parse(value, t()->dxfId.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_priority_literal))
			{
				driver()->context()->parse(value, t()->priority);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_stopIfTrue_literal))
			{
				driver()->context()->parse(value, t()->stopIfTrue);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_aboveAverage_literal))
			{
				driver()->context()->parse(value, t()->aboveAverage);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_percent_literal))
			{
				driver()->context()->parse(value, t()->percent);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_bottom_literal))
			{
				driver()->context()->parse(value, t()->bottom);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet__operator__literal))
			{
				driver()->context()->parse(value, t()->_operator_.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_text_literal))
			{
				driver()->context()->parse(value, t()->text.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_timePeriod_literal))
			{
				driver()->context()->parse(value, t()->timePeriod.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_rank_literal))
			{
				driver()->context()->parse(value, t()->rank.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_stdDev_literal))
			{
				driver()->context()->parse(value, t()->stdDev.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_equalAverage_literal))
			{
				driver()->context()->parse(value, t()->equalAverage);
				return;
			}
		}
		void CT_ConditionalFormatting_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_cfRule_literal))
			{
				t()->cfRule.resize(t()->cfRule.size()+1);
				driver()->push(localname, _cfRule_reader.get_reader(&t()->cfRule.back()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_ConditionalFormatting_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_pivot_literal))
			{
				driver()->context()->parse(value, t()->pivot);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_sqref_literal))
			{
				driver()->context()->parse(value, t()->sqref.getset());
				return;
			}
		}
		void CT_DataValidation_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_formula1_literal))
			{
				driver()->push(localname, _formula1_reader.get_reader(&t()->formula1.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_formula2_literal))
			{
				driver()->push(localname, _formula2_reader.get_reader(&t()->formula2.getset()));
				return;
			}
		}
		void CT_DataValidation_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_type_literal))
			{
				driver()->context()->parse(value, t()->type);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_errorStyle_literal))
			{
				driver()->context()->parse(value, t()->errorStyle);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_imeMode_literal))
			{
				driver()->context()->parse(value, t()->imeMode);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet__operator__literal))
			{
				driver()->context()->parse(value, t()->_operator_);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_allowBlank_literal))
			{
				driver()->context()->parse(value, t()->allowBlank);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_showDropDown_literal))
			{
				driver()->context()->parse(value, t()->showDropDown);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_showInputMessage_literal))
			{
				driver()->context()->parse(value, t()->showInputMessage);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_showErrorMessage_literal))
			{
				driver()->context()->parse(value, t()->showErrorMessage);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_errorTitle_literal))
			{
				driver()->context()->parse(value, t()->errorTitle.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_error_literal))
			{
				driver()->context()->parse(value, t()->error.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_promptTitle_literal))
			{
				driver()->context()->parse(value, t()->promptTitle.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_prompt_literal))
			{
				driver()->context()->parse(value, t()->prompt.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_sqref_literal))
			{
				driver()->context()->parse(value, t()->sqref);
				return;
			}
		}
		void CT_DataValidations_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_dataValidation_literal))
			{
				t()->dataValidation.resize(t()->dataValidation.size()+1);
				driver()->push(localname, _dataValidation_reader.get_reader(&t()->dataValidation.back()));
				return;
			}
		}
		void CT_DataValidations_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_disablePrompts_literal))
			{
				driver()->context()->parse(value, t()->disablePrompts);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_xWindow_literal))
			{
				driver()->context()->parse(value, t()->xWindow.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_yWindow_literal))
			{
				driver()->context()->parse(value, t()->yWindow.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
		}
		void CT_Hyperlink_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_ref_literal))
			{
				driver()->context()->parse(value, t()->ref);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_id_literal))
			{
				driver()->context()->parse(value, t()->id.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_location_literal))
			{
				driver()->context()->parse(value, t()->location.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_tooltip_literal))
			{
				driver()->context()->parse(value, t()->tooltip.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_display_literal))
			{
				driver()->context()->parse(value, t()->display.getset());
				return;
			}
		}
		void CT_Hyperlinks_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_hyperlink_literal))
			{
				t()->hyperlink.resize(t()->hyperlink.size()+1);
				driver()->push(localname, _hyperlink_reader.get_reader(&t()->hyperlink.back()));
				return;
			}
		}
		void CT_CustomProperty_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_name_literal))
			{
				driver()->context()->parse(value, t()->name);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_id_literal))
			{
				driver()->context()->parse(value, t()->id);
				return;
			}
		}
		void CT_CustomProperties_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_customPr_literal))
			{
				t()->customPr.resize(t()->customPr.size()+1);
				driver()->push(localname, _customPr_reader.get_reader(&t()->customPr.back()));
				return;
			}
		}
		void CT_CellWatch_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_r_literal))
			{
				driver()->context()->parse(value, t()->r);
				return;
			}
		}
		void CT_CellWatches_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_cellWatch_literal))
			{
				t()->cellWatch.resize(t()->cellWatch.size()+1);
				driver()->push(localname, _cellWatch_reader.get_reader(&t()->cellWatch.back()));
				return;
			}
		}
		void CT_IgnoredError_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_sqref_literal))
			{
				driver()->context()->parse(value, t()->sqref);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_evalError_literal))
			{
				driver()->context()->parse(value, t()->evalError);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_twoDigitTextYear_literal))
			{
				driver()->context()->parse(value, t()->twoDigitTextYear);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_numberStoredAsText_literal))
			{
				driver()->context()->parse(value, t()->numberStoredAsText);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_formula_literal))
			{
				driver()->context()->parse(value, t()->formula);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_formulaRange_literal))
			{
				driver()->context()->parse(value, t()->formulaRange);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_unlockedFormula_literal))
			{
				driver()->context()->parse(value, t()->unlockedFormula);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_emptyCellReference_literal))
			{
				driver()->context()->parse(value, t()->emptyCellReference);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_listDataValidation_literal))
			{
				driver()->context()->parse(value, t()->listDataValidation);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_calculatedColumn_literal))
			{
				driver()->context()->parse(value, t()->calculatedColumn);
				return;
			}
		}
		void CT_IgnoredErrors_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_ignoredError_literal))
			{
				t()->ignoredError.resize(t()->ignoredError.size()+1);
				driver()->push(localname, _ignoredError_reader.get_reader(&t()->ignoredError.back()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_CellSmartTagPr_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_key_literal))
			{
				driver()->context()->parse(value, t()->key);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_val_literal))
			{
				driver()->context()->parse(value, t()->val);
				return;
			}
		}
		void CT_CellSmartTag_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_cellSmartTagPr_literal))
			{
				t()->cellSmartTagPr.resize(t()->cellSmartTagPr.size()+1);
				driver()->push(localname, _cellSmartTagPr_reader.get_reader(&t()->cellSmartTagPr.back()));
				return;
			}
		}
		void CT_CellSmartTag_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_type_literal))
			{
				driver()->context()->parse(value, t()->type);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_deleted_literal))
			{
				driver()->context()->parse(value, t()->deleted);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_xmlBased_literal))
			{
				driver()->context()->parse(value, t()->xmlBased);
				return;
			}
		}
		void CT_CellSmartTags_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_cellSmartTag_literal))
			{
				t()->cellSmartTag.resize(t()->cellSmartTag.size()+1);
				driver()->push(localname, _cellSmartTag_reader.get_reader(&t()->cellSmartTag.back()));
				return;
			}
		}
		void CT_CellSmartTags_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_r_literal))
			{
				driver()->context()->parse(value, t()->r);
				return;
			}
		}
		void CT_SmartTags_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_cellSmartTags_literal))
			{
				t()->cellSmartTags.resize(t()->cellSmartTags.size()+1);
				driver()->push(localname, _cellSmartTags_reader.get_reader(&t()->cellSmartTags.back()));
				return;
			}
		}
		void CT_Drawing_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_id_literal))
			{
				driver()->context()->parse(value, t()->id);
				return;
			}
		}
		void CT_LegacyDrawing_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_id_literal))
			{
				driver()->context()->parse(value, t()->id);
				return;
			}
		}
		void CT_OleObject_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_progId_literal))
			{
				driver()->context()->parse(value, t()->progId.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_dvAspect_literal))
			{
				driver()->context()->parse(value, t()->dvAspect);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_link_literal))
			{
				driver()->context()->parse(value, t()->link.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_oleUpdate_literal))
			{
				driver()->context()->parse(value, t()->oleUpdate.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_autoLoad_literal))
			{
				driver()->context()->parse(value, t()->autoLoad);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_shapeId_literal))
			{
				driver()->context()->parse(value, t()->shapeId);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_id_literal))
			{
				driver()->context()->parse(value, t()->id.getset());
				return;
			}
		}
		void CT_OleObjects_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_oleObject_literal))
			{
				t()->oleObject.resize(t()->oleObject.size()+1);
				driver()->push(localname, _oleObject_reader.get_reader(&t()->oleObject.back()));
				return;
			}
		}
		void CT_Control_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_shapeId_literal))
			{
				driver()->context()->parse(value, t()->shapeId);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_id_literal))
			{
				driver()->context()->parse(value, t()->id);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_name_literal))
			{
				driver()->context()->parse(value, t()->name.getset());
				return;
			}
		}
		void CT_Controls_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_control_literal))
			{
				t()->control.resize(t()->control.size()+1);
				driver()->push(localname, _control_reader.get_reader(&t()->control.back()));
				return;
			}
		}
		void CT_WebPublishItem_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_id_literal))
			{
				driver()->context()->parse(value, t()->id);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_divId_literal))
			{
				driver()->context()->parse(value, t()->divId);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_sourceType_literal))
			{
				driver()->context()->parse(value, t()->sourceType);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_sourceRef_literal))
			{
				driver()->context()->parse(value, t()->sourceRef.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_sourceObject_literal))
			{
				driver()->context()->parse(value, t()->sourceObject.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_destinationFile_literal))
			{
				driver()->context()->parse(value, t()->destinationFile);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_title_literal))
			{
				driver()->context()->parse(value, t()->title.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_autoRepublish_literal))
			{
				driver()->context()->parse(value, t()->autoRepublish);
				return;
			}
		}
		void CT_WebPublishItems_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_webPublishItem_literal))
			{
				t()->webPublishItem.resize(t()->webPublishItem.size()+1);
				driver()->push(localname, _webPublishItem_reader.get_reader(&t()->webPublishItem.back()));
				return;
			}
		}
		void CT_WebPublishItems_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
		}
		void CT_TablePart_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_id_literal))
			{
				driver()->context()->parse(value, t()->id);
				return;
			}
		}
		void CT_TableParts_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_tablePart_literal))
			{
				t()->tablePart.resize(t()->tablePart.size()+1);
				driver()->push(localname, _tablePart_reader.get_reader(&t()->tablePart.back()));
				return;
			}
		}
		void CT_TableParts_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
		}
		void CT_Worksheet_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_sheetPr_literal))
			{
				driver()->push(localname, _sheetPr_reader.get_reader(&t()->sheetPr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_dimension_literal))
			{
				driver()->push(localname, _dimension_reader.get_reader(&t()->dimension.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_sheetViews_literal))
			{
				driver()->push(localname, _sheetViews_reader.get_reader(&t()->sheetViews.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_sheetFormatPr_literal))
			{
				driver()->push(localname, _sheetFormatPr_reader.get_reader(&t()->sheetFormatPr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_cols_literal))
			{
				t()->cols.resize(t()->cols.size()+1);
				driver()->push(localname, _cols_reader.get_reader(&t()->cols.back()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_sheetData_literal))
			{
				driver()->push(localname, _sheetData_reader.get_reader(&t()->sheetData));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_sheetCalcPr_literal))
			{
				driver()->push(localname, _sheetCalcPr_reader.get_reader(&t()->sheetCalcPr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_sheetProtection_literal))
			{
				driver()->push(localname, _sheetProtection_reader.get_reader(&t()->sheetProtection.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_protectedRanges_literal))
			{
				driver()->push(localname, _protectedRanges_reader.get_reader(&t()->protectedRanges.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_scenarios_literal))
			{
				driver()->push(localname, _scenarios_reader.get_reader(&t()->scenarios.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_autoFilter_literal))
			{
				driver()->push(localname, _autoFilter_reader.get_reader(&t()->autoFilter.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_sortState_literal))
			{
				driver()->push(localname, _sortState_reader.get_reader(&t()->sortState.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_dataConsolidate_literal))
			{
				driver()->push(localname, _dataConsolidate_reader.get_reader(&t()->dataConsolidate.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_customSheetViews_literal))
			{
				driver()->push(localname, _customSheetViews_reader.get_reader(&t()->customSheetViews.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_mergeCells_literal))
			{
				driver()->push(localname, _mergeCells_reader.get_reader(&t()->mergeCells.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_phoneticPr_literal))
			{
				driver()->push(localname, _phoneticPr_reader.get_reader(&t()->phoneticPr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_conditionalFormatting_literal))
			{
				t()->conditionalFormatting.resize(t()->conditionalFormatting.size()+1);
				driver()->push(localname, _conditionalFormatting_reader.get_reader(&t()->conditionalFormatting.back()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_dataValidations_literal))
			{
				driver()->push(localname, _dataValidations_reader.get_reader(&t()->dataValidations.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_hyperlinks_literal))
			{
				driver()->push(localname, _hyperlinks_reader.get_reader(&t()->hyperlinks.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_printOptions_literal))
			{
				driver()->push(localname, _printOptions_reader.get_reader(&t()->printOptions.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_pageMargins_literal))
			{
				driver()->push(localname, _pageMargins_reader.get_reader(&t()->pageMargins.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_pageSetup_literal))
			{
				driver()->push(localname, _pageSetup_reader.get_reader(&t()->pageSetup.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_headerFooter_literal))
			{
				driver()->push(localname, _headerFooter_reader.get_reader(&t()->headerFooter.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_rowBreaks_literal))
			{
				driver()->push(localname, _rowBreaks_reader.get_reader(&t()->rowBreaks.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_colBreaks_literal))
			{
				driver()->push(localname, _colBreaks_reader.get_reader(&t()->colBreaks.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_customProperties_literal))
			{
				driver()->push(localname, _customProperties_reader.get_reader(&t()->customProperties.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_cellWatches_literal))
			{
				driver()->push(localname, _cellWatches_reader.get_reader(&t()->cellWatches.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_ignoredErrors_literal))
			{
				driver()->push(localname, _ignoredErrors_reader.get_reader(&t()->ignoredErrors.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_smartTags_literal))
			{
				driver()->push(localname, _smartTags_reader.get_reader(&t()->smartTags.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_drawing_literal))
			{
				driver()->push(localname, _drawing_reader.get_reader(&t()->drawing.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_legacyDrawing_literal))
			{
				driver()->push(localname, _legacyDrawing_reader.get_reader(&t()->legacyDrawing.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_legacyDrawingHF_literal))
			{
				driver()->push(localname, _legacyDrawingHF_reader.get_reader(&t()->legacyDrawingHF.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_picture_literal))
			{
				driver()->push(localname, _picture_reader.get_reader(&t()->picture.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_oleObjects_literal))
			{
				driver()->push(localname, _oleObjects_reader.get_reader(&t()->oleObjects.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_controls_literal))
			{
				driver()->push(localname, _controls_reader.get_reader(&t()->controls.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_webPublishItems_literal))
			{
				driver()->push(localname, _webPublishItems_reader.get_reader(&t()->webPublishItems.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_tableParts_literal))
			{
				driver()->push(localname, _tableParts_reader.get_reader(&t()->tableParts.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_ChartsheetPr_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_tabColor_literal))
			{
				driver()->push(localname, _tabColor_reader.get_reader(&t()->tabColor.getset()));
				return;
			}
		}
		void CT_ChartsheetPr_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_published_literal))
			{
				driver()->context()->parse(value, t()->published);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_codeName_literal))
			{
				driver()->context()->parse(value, t()->codeName.getset());
				return;
			}
		}
		void CT_ChartsheetView_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_ChartsheetView_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_tabSelected_literal))
			{
				driver()->context()->parse(value, t()->tabSelected);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_zoomScale_literal))
			{
				driver()->context()->parse(value, t()->zoomScale);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_workbookViewId_literal))
			{
				driver()->context()->parse(value, t()->workbookViewId);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_zoomToFit_literal))
			{
				driver()->context()->parse(value, t()->zoomToFit);
				return;
			}
		}
		void CT_ChartsheetViews_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_sheetView_literal))
			{
				t()->sheetView.resize(t()->sheetView.size()+1);
				driver()->push(localname, _sheetView_reader.get_reader(&t()->sheetView.back()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_ChartsheetProtection_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_password_literal))
			{
				driver()->context()->parse(value, t()->password.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_content_literal))
			{
				driver()->context()->parse(value, t()->content);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_objects_literal))
			{
				driver()->context()->parse(value, t()->objects);
				return;
			}
		}
		void CT_CsPageSetup_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_paperSize_literal))
			{
				driver()->context()->parse(value, t()->paperSize);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_firstPageNumber_literal))
			{
				driver()->context()->parse(value, t()->firstPageNumber);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_orientation_literal))
			{
				driver()->context()->parse(value, t()->orientation);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_usePrinterDefaults_literal))
			{
				driver()->context()->parse(value, t()->usePrinterDefaults);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_blackAndWhite_literal))
			{
				driver()->context()->parse(value, t()->blackAndWhite);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_draft_literal))
			{
				driver()->context()->parse(value, t()->draft);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_useFirstPageNumber_literal))
			{
				driver()->context()->parse(value, t()->useFirstPageNumber);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_horizontalDpi_literal))
			{
				driver()->context()->parse(value, t()->horizontalDpi);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_verticalDpi_literal))
			{
				driver()->context()->parse(value, t()->verticalDpi);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_copies_literal))
			{
				driver()->context()->parse(value, t()->copies);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_id_literal))
			{
				driver()->context()->parse(value, t()->id.getset());
				return;
			}
		}
		void CT_CustomChartsheetView_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_pageMargins_literal))
			{
				driver()->push(localname, _pageMargins_reader.get_reader(&t()->pageMargins.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_pageSetup_literal))
			{
				driver()->push(localname, _pageSetup_reader.get_reader(&t()->pageSetup.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_headerFooter_literal))
			{
				driver()->push(localname, _headerFooter_reader.get_reader(&t()->headerFooter.getset()));
				return;
			}
		}
		void CT_CustomChartsheetView_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_guid_literal))
			{
				driver()->context()->parse(value, t()->guid);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_scale_literal))
			{
				driver()->context()->parse(value, t()->scale);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_state_literal))
			{
				driver()->context()->parse(value, t()->state);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_zoomToFit_literal))
			{
				driver()->context()->parse(value, t()->zoomToFit);
				return;
			}
		}
		void CT_CustomChartsheetViews_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_customSheetView_literal))
			{
				t()->customSheetView.resize(t()->customSheetView.size()+1);
				driver()->push(localname, _customSheetView_reader.get_reader(&t()->customSheetView.back()));
				return;
			}
		}
		void CT_Chartsheet_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_sheetPr_literal))
			{
				driver()->push(localname, _sheetPr_reader.get_reader(&t()->sheetPr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_sheetViews_literal))
			{
				driver()->push(localname, _sheetViews_reader.get_reader(&t()->sheetViews));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_sheetProtection_literal))
			{
				driver()->push(localname, _sheetProtection_reader.get_reader(&t()->sheetProtection.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_customSheetViews_literal))
			{
				driver()->push(localname, _customSheetViews_reader.get_reader(&t()->customSheetViews.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_pageMargins_literal))
			{
				driver()->push(localname, _pageMargins_reader.get_reader(&t()->pageMargins.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_pageSetup_literal))
			{
				driver()->push(localname, _pageSetup_reader.get_reader(&t()->pageSetup.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_headerFooter_literal))
			{
				driver()->push(localname, _headerFooter_reader.get_reader(&t()->headerFooter.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_drawing_literal))
			{
				driver()->push(localname, _drawing_reader.get_reader(&t()->drawing));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_legacyDrawing_literal))
			{
				driver()->push(localname, _legacyDrawing_reader.get_reader(&t()->legacyDrawing.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_legacyDrawingHF_literal))
			{
				driver()->push(localname, _legacyDrawingHF_reader.get_reader(&t()->legacyDrawingHF.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_picture_literal))
			{
				driver()->push(localname, _picture_reader.get_reader(&t()->picture.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_webPublishItems_literal))
			{
				driver()->push(localname, _webPublishItems_reader.get_reader(&t()->webPublishItems.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_Dialogsheet_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_sheetPr_literal))
			{
				driver()->push(localname, _sheetPr_reader.get_reader(&t()->sheetPr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_sheetViews_literal))
			{
				driver()->push(localname, _sheetViews_reader.get_reader(&t()->sheetViews.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_sheetFormatPr_literal))
			{
				driver()->push(localname, _sheetFormatPr_reader.get_reader(&t()->sheetFormatPr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_sheetProtection_literal))
			{
				driver()->push(localname, _sheetProtection_reader.get_reader(&t()->sheetProtection.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_customSheetViews_literal))
			{
				driver()->push(localname, _customSheetViews_reader.get_reader(&t()->customSheetViews.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_printOptions_literal))
			{
				driver()->push(localname, _printOptions_reader.get_reader(&t()->printOptions.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_pageMargins_literal))
			{
				driver()->push(localname, _pageMargins_reader.get_reader(&t()->pageMargins.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_pageSetup_literal))
			{
				driver()->push(localname, _pageSetup_reader.get_reader(&t()->pageSetup.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_headerFooter_literal))
			{
				driver()->push(localname, _headerFooter_reader.get_reader(&t()->headerFooter.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_drawing_literal))
			{
				driver()->push(localname, _drawing_reader.get_reader(&t()->drawing.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_legacyDrawing_literal))
			{
				driver()->push(localname, _legacyDrawing_reader.get_reader(&t()->legacyDrawing.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_legacyDrawingHF_literal))
			{
				driver()->push(localname, _legacyDrawingHF_reader.get_reader(&t()->legacyDrawingHF.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_oleObjects_literal))
			{
				driver()->push(localname, _oleObjects_reader.get_reader(&t()->oleObjects.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void sml_sheet_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheet_worksheet_literal))
			{
				driver()->push(localname, _worksheet_reader.get_reader(&t()->worksheet.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_chartsheet_literal))
			{
				driver()->push(localname, _chartsheet_reader.get_reader(&t()->chartsheet.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheet_dialogsheet_literal))
			{
				driver()->push(localname, _dialogsheet_reader.get_reader(&t()->dialogsheet.getset()));
				return;
			}
		}
	}
}
