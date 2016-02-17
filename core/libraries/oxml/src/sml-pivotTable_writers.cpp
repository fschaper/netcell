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


#include "sml-pivotTable_writers.hpp"
#include "sml-pivotTable_literals.hpp"

namespace spreadsheetml
{
	namespace xio
	{
		void CT_WorksheetSource_writer::write_target_to(xml_writer& w) {
			if (t()->ref.present())
				w.attribute(0, sml_pivotTable_ref_literal, context()->serialize(t()->ref.get()));
			if (t()->name.present())
				w.attribute(0, sml_pivotTable_name_literal, context()->serialize(t()->name.get()));
			if (t()->sheet.present())
				w.attribute(0, sml_pivotTable_sheet_literal, context()->serialize(t()->sheet.get()));
			if (t()->id.present())
				w.attribute(sml_pivotTable_r_literal, sml_pivotTable_id_literal, context()->serialize(t()->id.get()));
		}

		void CT_PageItem_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_pivotTable_name_literal, context()->serialize(t()->name));
		}

		void CT_PCDSCPage_writer::write_target_to(xml_writer& w) {
			if (t()->count.present())
				w.attribute(0, sml_pivotTable_count_literal, context()->serialize(t()->count.get()));
			for (size_t sqi = 0; sqi<t()->pageItem.size(); ++sqi) {
				w.start_element(0, sml_pivotTable_pageItem_literal);
				_pageItem_writer.get_writer(context(), &t()->pageItem[sqi])->write_target_to(w);
				w.end_element(0, sml_pivotTable_pageItem_literal);
			}
		}

		void CT_Pages_writer::write_target_to(xml_writer& w) {
			if (t()->count.present())
				w.attribute(0, sml_pivotTable_count_literal, context()->serialize(t()->count.get()));
			for (size_t sqi = 0; sqi<t()->page.size(); ++sqi) {
				w.start_element(0, sml_pivotTable_page_literal);
				_page_writer.get_writer(context(), &t()->page[sqi])->write_target_to(w);
				w.end_element(0, sml_pivotTable_page_literal);
			}
		}

		void CT_RangeSet_writer::write_target_to(xml_writer& w) {
			if (t()->i1.present())
				w.attribute(0, sml_pivotTable_i1_literal, context()->serialize(t()->i1.get()));
			if (t()->i2.present())
				w.attribute(0, sml_pivotTable_i2_literal, context()->serialize(t()->i2.get()));
			if (t()->i3.present())
				w.attribute(0, sml_pivotTable_i3_literal, context()->serialize(t()->i3.get()));
			if (t()->i4.present())
				w.attribute(0, sml_pivotTable_i4_literal, context()->serialize(t()->i4.get()));
			if (t()->ref.present())
				w.attribute(0, sml_pivotTable_ref_literal, context()->serialize(t()->ref.get()));
			if (t()->name.present())
				w.attribute(0, sml_pivotTable_name_literal, context()->serialize(t()->name.get()));
			if (t()->sheet.present())
				w.attribute(0, sml_pivotTable_sheet_literal, context()->serialize(t()->sheet.get()));
			if (t()->id.present())
				w.attribute(sml_pivotTable_r_literal, sml_pivotTable_id_literal, context()->serialize(t()->id.get()));
		}

		void CT_RangeSets_writer::write_target_to(xml_writer& w) {
			if (t()->count.present())
				w.attribute(0, sml_pivotTable_count_literal, context()->serialize(t()->count.get()));
			for (size_t sqi = 0; sqi<t()->rangeSet.size(); ++sqi) {
				w.start_element(0, sml_pivotTable_rangeSet_literal);
				_rangeSet_writer.get_writer(context(), &t()->rangeSet[sqi])->write_target_to(w);
				w.end_element(0, sml_pivotTable_rangeSet_literal);
			}
		}

		void CT_Consolidation_writer::write_target_to(xml_writer& w) {
			if (t()->autoPage != true)
				w.attribute(0, sml_pivotTable_autoPage_literal, context()->serialize(t()->autoPage));
			if (t()->pages.present()) {
				w.start_element(0, sml_pivotTable_pages_literal);
				_pages_writer.get_writer(context(), &t()->pages.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_pages_literal);
			}
			w.start_element(0, sml_pivotTable_rangeSets_literal);
			_rangeSets_writer.get_writer(context(), &t()->rangeSets)->write_target_to(w);
			w.end_element(0, sml_pivotTable_rangeSets_literal);
		}

		void CT_CacheSource_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_pivotTable_type_literal, context()->serialize(t()->type));
			if (t()->connectionId != 0U)
				w.attribute(0, sml_pivotTable_connectionId_literal, context()->serialize(t()->connectionId));
			if (t()->worksheetSource.present()) {
				w.start_element(0, sml_pivotTable_worksheetSource_literal);
				_worksheetSource_writer.get_writer(context(), &t()->worksheetSource.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_worksheetSource_literal);
			}
			if (t()->consolidation.present()) {
				w.start_element(0, sml_pivotTable_consolidation_literal);
				_consolidation_writer.get_writer(context(), &t()->consolidation.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_consolidation_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, sml_pivotTable_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_extLst_literal);
			}
		}

		void CT_Tuple_writer::write_target_to(xml_writer& w) {
			if (t()->fld.present())
				w.attribute(0, sml_pivotTable_fld_literal, context()->serialize(t()->fld.get()));
			if (t()->hier.present())
				w.attribute(0, sml_pivotTable_hier_literal, context()->serialize(t()->hier.get()));
			w.attribute(0, sml_pivotTable_item_literal, context()->serialize(t()->item));
		}

		void CT_Tuples_writer::write_target_to(xml_writer& w) {
			if (t()->c.present())
				w.attribute(0, sml_pivotTable_c_literal, context()->serialize(t()->c.get()));
			for (size_t sqi = 0; sqi<t()->tpl.size(); ++sqi) {
				w.start_element(0, sml_pivotTable_tpl_literal);
				_tpl_writer.get_writer(context(), &t()->tpl[sqi])->write_target_to(w);
				w.end_element(0, sml_pivotTable_tpl_literal);
			}
		}

		void CT_X_writer::write_target_to(xml_writer& w) {
			if (t()->v != 0)
				w.attribute(0, sml_pivotTable_v_literal, context()->serialize(t()->v));
		}

		void CT_Missing_writer::write_target_to(xml_writer& w) {
			if (t()->u.present())
				w.attribute(0, sml_pivotTable_u_literal, context()->serialize(t()->u.get()));
			if (t()->f.present())
				w.attribute(0, sml_pivotTable_f_literal, context()->serialize(t()->f.get()));
			if (t()->c.present())
				w.attribute(0, sml_pivotTable_c_literal, context()->serialize(t()->c.get()));
			if (t()->cp.present())
				w.attribute(0, sml_pivotTable_cp_literal, context()->serialize(t()->cp.get()));
			if (t()->in.present())
				w.attribute(0, sml_pivotTable_in_literal, context()->serialize(t()->in.get()));
			if (t()->bc.present())
				w.attribute(0, sml_pivotTable_bc_literal, context()->serialize(t()->bc.get()));
			if (t()->fc.present())
				w.attribute(0, sml_pivotTable_fc_literal, context()->serialize(t()->fc.get()));
			if (t()->i != false)
				w.attribute(0, sml_pivotTable_i_literal, context()->serialize(t()->i));
			if (t()->un != false)
				w.attribute(0, sml_pivotTable_un_literal, context()->serialize(t()->un));
			if (t()->st != false)
				w.attribute(0, sml_pivotTable_st_literal, context()->serialize(t()->st));
			if (t()->b != false)
				w.attribute(0, sml_pivotTable_b_literal, context()->serialize(t()->b));
			for (size_t sqi = 0; sqi<t()->tpls.size(); ++sqi) {
				w.start_element(0, sml_pivotTable_tpls_literal);
				_tpls_writer.get_writer(context(), &t()->tpls[sqi])->write_target_to(w);
				w.end_element(0, sml_pivotTable_tpls_literal);
			}
			for (size_t sqi = 0; sqi<t()->x.size(); ++sqi) {
				w.start_element(0, sml_pivotTable_x_literal);
				_x_writer.get_writer(context(), &t()->x[sqi])->write_target_to(w);
				w.end_element(0, sml_pivotTable_x_literal);
			}
		}

		void CT_Number_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_pivotTable_v_literal, context()->serialize(t()->v));
			if (t()->u.present())
				w.attribute(0, sml_pivotTable_u_literal, context()->serialize(t()->u.get()));
			if (t()->f.present())
				w.attribute(0, sml_pivotTable_f_literal, context()->serialize(t()->f.get()));
			if (t()->c.present())
				w.attribute(0, sml_pivotTable_c_literal, context()->serialize(t()->c.get()));
			if (t()->cp.present())
				w.attribute(0, sml_pivotTable_cp_literal, context()->serialize(t()->cp.get()));
			if (t()->in.present())
				w.attribute(0, sml_pivotTable_in_literal, context()->serialize(t()->in.get()));
			if (t()->bc.present())
				w.attribute(0, sml_pivotTable_bc_literal, context()->serialize(t()->bc.get()));
			if (t()->fc.present())
				w.attribute(0, sml_pivotTable_fc_literal, context()->serialize(t()->fc.get()));
			if (t()->i != false)
				w.attribute(0, sml_pivotTable_i_literal, context()->serialize(t()->i));
			if (t()->un != false)
				w.attribute(0, sml_pivotTable_un_literal, context()->serialize(t()->un));
			if (t()->st != false)
				w.attribute(0, sml_pivotTable_st_literal, context()->serialize(t()->st));
			if (t()->b != false)
				w.attribute(0, sml_pivotTable_b_literal, context()->serialize(t()->b));
			for (size_t sqi = 0; sqi<t()->tpls.size(); ++sqi) {
				w.start_element(0, sml_pivotTable_tpls_literal);
				_tpls_writer.get_writer(context(), &t()->tpls[sqi])->write_target_to(w);
				w.end_element(0, sml_pivotTable_tpls_literal);
			}
			for (size_t sqi = 0; sqi<t()->x.size(); ++sqi) {
				w.start_element(0, sml_pivotTable_x_literal);
				_x_writer.get_writer(context(), &t()->x[sqi])->write_target_to(w);
				w.end_element(0, sml_pivotTable_x_literal);
			}
		}

		void CT_Boolean_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_pivotTable_v_literal, context()->serialize(t()->v));
			if (t()->u.present())
				w.attribute(0, sml_pivotTable_u_literal, context()->serialize(t()->u.get()));
			if (t()->f.present())
				w.attribute(0, sml_pivotTable_f_literal, context()->serialize(t()->f.get()));
			if (t()->c.present())
				w.attribute(0, sml_pivotTable_c_literal, context()->serialize(t()->c.get()));
			if (t()->cp.present())
				w.attribute(0, sml_pivotTable_cp_literal, context()->serialize(t()->cp.get()));
			for (size_t sqi = 0; sqi<t()->x.size(); ++sqi) {
				w.start_element(0, sml_pivotTable_x_literal);
				_x_writer.get_writer(context(), &t()->x[sqi])->write_target_to(w);
				w.end_element(0, sml_pivotTable_x_literal);
			}
		}

		void CT_Error_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_pivotTable_v_literal, context()->serialize(t()->v));
			if (t()->u.present())
				w.attribute(0, sml_pivotTable_u_literal, context()->serialize(t()->u.get()));
			if (t()->f.present())
				w.attribute(0, sml_pivotTable_f_literal, context()->serialize(t()->f.get()));
			if (t()->c.present())
				w.attribute(0, sml_pivotTable_c_literal, context()->serialize(t()->c.get()));
			if (t()->cp.present())
				w.attribute(0, sml_pivotTable_cp_literal, context()->serialize(t()->cp.get()));
			if (t()->in.present())
				w.attribute(0, sml_pivotTable_in_literal, context()->serialize(t()->in.get()));
			if (t()->bc.present())
				w.attribute(0, sml_pivotTable_bc_literal, context()->serialize(t()->bc.get()));
			if (t()->fc.present())
				w.attribute(0, sml_pivotTable_fc_literal, context()->serialize(t()->fc.get()));
			if (t()->i != false)
				w.attribute(0, sml_pivotTable_i_literal, context()->serialize(t()->i));
			if (t()->un != false)
				w.attribute(0, sml_pivotTable_un_literal, context()->serialize(t()->un));
			if (t()->st != false)
				w.attribute(0, sml_pivotTable_st_literal, context()->serialize(t()->st));
			if (t()->b != false)
				w.attribute(0, sml_pivotTable_b_literal, context()->serialize(t()->b));
			if (t()->tpls.present()) {
				w.start_element(0, sml_pivotTable_tpls_literal);
				_tpls_writer.get_writer(context(), &t()->tpls.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_tpls_literal);
			}
			for (size_t sqi = 0; sqi<t()->x.size(); ++sqi) {
				w.start_element(0, sml_pivotTable_x_literal);
				_x_writer.get_writer(context(), &t()->x[sqi])->write_target_to(w);
				w.end_element(0, sml_pivotTable_x_literal);
			}
		}

		void CT_String_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_pivotTable_v_literal, context()->serialize(t()->v));
			if (t()->u.present())
				w.attribute(0, sml_pivotTable_u_literal, context()->serialize(t()->u.get()));
			if (t()->f.present())
				w.attribute(0, sml_pivotTable_f_literal, context()->serialize(t()->f.get()));
			if (t()->c.present())
				w.attribute(0, sml_pivotTable_c_literal, context()->serialize(t()->c.get()));
			if (t()->cp.present())
				w.attribute(0, sml_pivotTable_cp_literal, context()->serialize(t()->cp.get()));
			if (t()->in.present())
				w.attribute(0, sml_pivotTable_in_literal, context()->serialize(t()->in.get()));
			if (t()->bc.present())
				w.attribute(0, sml_pivotTable_bc_literal, context()->serialize(t()->bc.get()));
			if (t()->fc.present())
				w.attribute(0, sml_pivotTable_fc_literal, context()->serialize(t()->fc.get()));
			if (t()->i != false)
				w.attribute(0, sml_pivotTable_i_literal, context()->serialize(t()->i));
			if (t()->un != false)
				w.attribute(0, sml_pivotTable_un_literal, context()->serialize(t()->un));
			if (t()->st != false)
				w.attribute(0, sml_pivotTable_st_literal, context()->serialize(t()->st));
			if (t()->b != false)
				w.attribute(0, sml_pivotTable_b_literal, context()->serialize(t()->b));
			for (size_t sqi = 0; sqi<t()->tpls.size(); ++sqi) {
				w.start_element(0, sml_pivotTable_tpls_literal);
				_tpls_writer.get_writer(context(), &t()->tpls[sqi])->write_target_to(w);
				w.end_element(0, sml_pivotTable_tpls_literal);
			}
			for (size_t sqi = 0; sqi<t()->x.size(); ++sqi) {
				w.start_element(0, sml_pivotTable_x_literal);
				_x_writer.get_writer(context(), &t()->x[sqi])->write_target_to(w);
				w.end_element(0, sml_pivotTable_x_literal);
			}
		}

		void CT_DateTime_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_pivotTable_v_literal, context()->serialize(t()->v));
			if (t()->u.present())
				w.attribute(0, sml_pivotTable_u_literal, context()->serialize(t()->u.get()));
			if (t()->f.present())
				w.attribute(0, sml_pivotTable_f_literal, context()->serialize(t()->f.get()));
			if (t()->c.present())
				w.attribute(0, sml_pivotTable_c_literal, context()->serialize(t()->c.get()));
			if (t()->cp.present())
				w.attribute(0, sml_pivotTable_cp_literal, context()->serialize(t()->cp.get()));
			for (size_t sqi = 0; sqi<t()->x.size(); ++sqi) {
				w.start_element(0, sml_pivotTable_x_literal);
				_x_writer.get_writer(context(), &t()->x[sqi])->write_target_to(w);
				w.end_element(0, sml_pivotTable_x_literal);
			}
		}

		void CT_SharedItems_writer::write_target_to(xml_writer& w) {
			if (t()->containsSemiMixedTypes != true)
				w.attribute(0, sml_pivotTable_containsSemiMixedTypes_literal, context()->serialize(t()->containsSemiMixedTypes));
			if (t()->containsNonDate != true)
				w.attribute(0, sml_pivotTable_containsNonDate_literal, context()->serialize(t()->containsNonDate));
			if (t()->containsDate != false)
				w.attribute(0, sml_pivotTable_containsDate_literal, context()->serialize(t()->containsDate));
			if (t()->containsString != true)
				w.attribute(0, sml_pivotTable_containsString_literal, context()->serialize(t()->containsString));
			if (t()->containsBlank != false)
				w.attribute(0, sml_pivotTable_containsBlank_literal, context()->serialize(t()->containsBlank));
			if (t()->containsMixedTypes != false)
				w.attribute(0, sml_pivotTable_containsMixedTypes_literal, context()->serialize(t()->containsMixedTypes));
			if (t()->containsNumber != false)
				w.attribute(0, sml_pivotTable_containsNumber_literal, context()->serialize(t()->containsNumber));
			if (t()->containsInteger != false)
				w.attribute(0, sml_pivotTable_containsInteger_literal, context()->serialize(t()->containsInteger));
			if (t()->minValue.present())
				w.attribute(0, sml_pivotTable_minValue_literal, context()->serialize(t()->minValue.get()));
			if (t()->maxValue.present())
				w.attribute(0, sml_pivotTable_maxValue_literal, context()->serialize(t()->maxValue.get()));
			if (t()->minDate.present())
				w.attribute(0, sml_pivotTable_minDate_literal, context()->serialize(t()->minDate.get()));
			if (t()->maxDate.present())
				w.attribute(0, sml_pivotTable_maxDate_literal, context()->serialize(t()->maxDate.get()));
			if (t()->count.present())
				w.attribute(0, sml_pivotTable_count_literal, context()->serialize(t()->count.get()));
			if (t()->longText != false)
				w.attribute(0, sml_pivotTable_longText_literal, context()->serialize(t()->longText));
			if (t()->m.present()) {
				w.start_element(0, sml_pivotTable_m_literal);
				_m_writer.get_writer(context(), &t()->m.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_m_literal);
			}
			if (t()->n.present()) {
				w.start_element(0, sml_pivotTable_n_literal);
				_n_writer.get_writer(context(), &t()->n.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_n_literal);
			}
			if (t()->b.present()) {
				w.start_element(0, sml_pivotTable_b_literal);
				_b_writer.get_writer(context(), &t()->b.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_b_literal);
			}
			if (t()->e.present()) {
				w.start_element(0, sml_pivotTable_e_literal);
				_e_writer.get_writer(context(), &t()->e.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_e_literal);
			}
			if (t()->s.present()) {
				w.start_element(0, sml_pivotTable_s_literal);
				_s_writer.get_writer(context(), &t()->s.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_s_literal);
			}
			if (t()->d.present()) {
				w.start_element(0, sml_pivotTable_d_literal);
				_d_writer.get_writer(context(), &t()->d.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_d_literal);
			}
		}

		void CT_RangePr_writer::write_target_to(xml_writer& w) {
			if (t()->autoStart != true)
				w.attribute(0, sml_pivotTable_autoStart_literal, context()->serialize(t()->autoStart));
			if (t()->autoEnd != true)
				w.attribute(0, sml_pivotTable_autoEnd_literal, context()->serialize(t()->autoEnd));
			if (t()->groupBy != ST_GroupBy::range_literal)
				w.attribute(0, sml_pivotTable_groupBy_literal, context()->serialize(t()->groupBy));
			if (t()->startNum.present())
				w.attribute(0, sml_pivotTable_startNum_literal, context()->serialize(t()->startNum.get()));
			if (t()->endNum.present())
				w.attribute(0, sml_pivotTable_endNum_literal, context()->serialize(t()->endNum.get()));
			if (t()->startDate.present())
				w.attribute(0, sml_pivotTable_startDate_literal, context()->serialize(t()->startDate.get()));
			if (t()->endDate.present())
				w.attribute(0, sml_pivotTable_endDate_literal, context()->serialize(t()->endDate.get()));
			if (t()->groupInterval != 1)
				w.attribute(0, sml_pivotTable_groupInterval_literal, context()->serialize(t()->groupInterval));
		}

		void CT_DiscretePr_writer::write_target_to(xml_writer& w) {
			if (t()->count.present())
				w.attribute(0, sml_pivotTable_count_literal, context()->serialize(t()->count.get()));
			for (size_t sqi = 0; sqi<t()->x.size(); ++sqi) {
				w.start_element(0, sml_pivotTable_x_literal);
				_x_writer.get_writer(context(), &t()->x[sqi])->write_target_to(w);
				w.end_element(0, sml_pivotTable_x_literal);
			}
		}

		void CT_GroupItems_writer::write_target_to(xml_writer& w) {
			if (t()->count.present())
				w.attribute(0, sml_pivotTable_count_literal, context()->serialize(t()->count.get()));
			if (t()->m.present()) {
				w.start_element(0, sml_pivotTable_m_literal);
				_m_writer.get_writer(context(), &t()->m.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_m_literal);
			}
			if (t()->n.present()) {
				w.start_element(0, sml_pivotTable_n_literal);
				_n_writer.get_writer(context(), &t()->n.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_n_literal);
			}
			if (t()->b.present()) {
				w.start_element(0, sml_pivotTable_b_literal);
				_b_writer.get_writer(context(), &t()->b.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_b_literal);
			}
			if (t()->e.present()) {
				w.start_element(0, sml_pivotTable_e_literal);
				_e_writer.get_writer(context(), &t()->e.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_e_literal);
			}
			if (t()->s.present()) {
				w.start_element(0, sml_pivotTable_s_literal);
				_s_writer.get_writer(context(), &t()->s.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_s_literal);
			}
			if (t()->d.present()) {
				w.start_element(0, sml_pivotTable_d_literal);
				_d_writer.get_writer(context(), &t()->d.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_d_literal);
			}
		}

		void CT_FieldGroup_writer::write_target_to(xml_writer& w) {
			if (t()->par.present())
				w.attribute(0, sml_pivotTable_par_literal, context()->serialize(t()->par.get()));
			if (t()->base.present())
				w.attribute(0, sml_pivotTable_base_literal, context()->serialize(t()->base.get()));
			if (t()->rangePr.present()) {
				w.start_element(0, sml_pivotTable_rangePr_literal);
				_rangePr_writer.get_writer(context(), &t()->rangePr.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_rangePr_literal);
			}
			if (t()->discretePr.present()) {
				w.start_element(0, sml_pivotTable_discretePr_literal);
				_discretePr_writer.get_writer(context(), &t()->discretePr.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_discretePr_literal);
			}
			if (t()->groupItems.present()) {
				w.start_element(0, sml_pivotTable_groupItems_literal);
				_groupItems_writer.get_writer(context(), &t()->groupItems.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_groupItems_literal);
			}
		}

		void CT_CacheField_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_pivotTable_name_literal, context()->serialize(t()->name));
			if (t()->caption.present())
				w.attribute(0, sml_pivotTable_caption_literal, context()->serialize(t()->caption.get()));
			if (t()->propertyName.present())
				w.attribute(0, sml_pivotTable_propertyName_literal, context()->serialize(t()->propertyName.get()));
			if (t()->serverField != false)
				w.attribute(0, sml_pivotTable_serverField_literal, context()->serialize(t()->serverField));
			if (t()->uniqueList != true)
				w.attribute(0, sml_pivotTable_uniqueList_literal, context()->serialize(t()->uniqueList));
			if (t()->numFmtId.present())
				w.attribute(0, sml_pivotTable_numFmtId_literal, context()->serialize(t()->numFmtId.get()));
			if (t()->formula.present())
				w.attribute(0, sml_pivotTable_formula_literal, context()->serialize(t()->formula.get()));
			if (t()->sqlType != 0)
				w.attribute(0, sml_pivotTable_sqlType_literal, context()->serialize(t()->sqlType));
			if (t()->hierarchy != 0)
				w.attribute(0, sml_pivotTable_hierarchy_literal, context()->serialize(t()->hierarchy));
			if (t()->level != 0U)
				w.attribute(0, sml_pivotTable_level_literal, context()->serialize(t()->level));
			if (t()->databaseField != true)
				w.attribute(0, sml_pivotTable_databaseField_literal, context()->serialize(t()->databaseField));
			if (t()->mappingCount.present())
				w.attribute(0, sml_pivotTable_mappingCount_literal, context()->serialize(t()->mappingCount.get()));
			if (t()->memberPropertyField != false)
				w.attribute(0, sml_pivotTable_memberPropertyField_literal, context()->serialize(t()->memberPropertyField));
			if (t()->sharedItems.present()) {
				w.start_element(0, sml_pivotTable_sharedItems_literal);
				_sharedItems_writer.get_writer(context(), &t()->sharedItems.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_sharedItems_literal);
			}
			if (t()->fieldGroup.present()) {
				w.start_element(0, sml_pivotTable_fieldGroup_literal);
				_fieldGroup_writer.get_writer(context(), &t()->fieldGroup.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_fieldGroup_literal);
			}
			for (size_t sqi = 0; sqi<t()->mpMap.size(); ++sqi) {
				w.start_element(0, sml_pivotTable_mpMap_literal);
				_mpMap_writer.get_writer(context(), &t()->mpMap[sqi])->write_target_to(w);
				w.end_element(0, sml_pivotTable_mpMap_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, sml_pivotTable_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_extLst_literal);
			}
		}

		void CT_CacheFields_writer::write_target_to(xml_writer& w) {
			if (t()->count.present())
				w.attribute(0, sml_pivotTable_count_literal, context()->serialize(t()->count.get()));
			for (size_t sqi = 0; sqi<t()->cacheField.size(); ++sqi) {
				w.start_element(0, sml_pivotTable_cacheField_literal);
				_cacheField_writer.get_writer(context(), &t()->cacheField[sqi])->write_target_to(w);
				w.end_element(0, sml_pivotTable_cacheField_literal);
			}
		}

		void CT_FieldUsage_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_pivotTable_x_literal, context()->serialize(t()->x));
		}

		void CT_FieldsUsage_writer::write_target_to(xml_writer& w) {
			if (t()->count.present())
				w.attribute(0, sml_pivotTable_count_literal, context()->serialize(t()->count.get()));
			for (size_t sqi = 0; sqi<t()->fieldUsage.size(); ++sqi) {
				w.start_element(0, sml_pivotTable_fieldUsage_literal);
				_fieldUsage_writer.get_writer(context(), &t()->fieldUsage[sqi])->write_target_to(w);
				w.end_element(0, sml_pivotTable_fieldUsage_literal);
			}
		}

		void CT_GroupMember_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_pivotTable_uniqueName_literal, context()->serialize(t()->uniqueName));
			if (t()->group != false)
				w.attribute(0, sml_pivotTable_group_literal, context()->serialize(t()->group));
		}

		void CT_GroupMembers_writer::write_target_to(xml_writer& w) {
			if (t()->count.present())
				w.attribute(0, sml_pivotTable_count_literal, context()->serialize(t()->count.get()));
			for (size_t sqi = 0; sqi<t()->groupMember.size(); ++sqi) {
				w.start_element(0, sml_pivotTable_groupMember_literal);
				_groupMember_writer.get_writer(context(), &t()->groupMember[sqi])->write_target_to(w);
				w.end_element(0, sml_pivotTable_groupMember_literal);
			}
		}

		void CT_LevelGroup_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_pivotTable_name_literal, context()->serialize(t()->name));
			w.attribute(0, sml_pivotTable_uniqueName_literal, context()->serialize(t()->uniqueName));
			w.attribute(0, sml_pivotTable_caption_literal, context()->serialize(t()->caption));
			if (t()->uniqueParent.present())
				w.attribute(0, sml_pivotTable_uniqueParent_literal, context()->serialize(t()->uniqueParent.get()));
			if (t()->id.present())
				w.attribute(0, sml_pivotTable_id_literal, context()->serialize(t()->id.get()));
			w.start_element(0, sml_pivotTable_groupMembers_literal);
			_groupMembers_writer.get_writer(context(), &t()->groupMembers)->write_target_to(w);
			w.end_element(0, sml_pivotTable_groupMembers_literal);
		}

		void CT_Groups_writer::write_target_to(xml_writer& w) {
			if (t()->count.present())
				w.attribute(0, sml_pivotTable_count_literal, context()->serialize(t()->count.get()));
			for (size_t sqi = 0; sqi<t()->group.size(); ++sqi) {
				w.start_element(0, sml_pivotTable_group_literal);
				_group_writer.get_writer(context(), &t()->group[sqi])->write_target_to(w);
				w.end_element(0, sml_pivotTable_group_literal);
			}
		}

		void CT_GroupLevel_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_pivotTable_uniqueName_literal, context()->serialize(t()->uniqueName));
			w.attribute(0, sml_pivotTable_caption_literal, context()->serialize(t()->caption));
			if (t()->user != false)
				w.attribute(0, sml_pivotTable_user_literal, context()->serialize(t()->user));
			if (t()->customRollUp != false)
				w.attribute(0, sml_pivotTable_customRollUp_literal, context()->serialize(t()->customRollUp));
			if (t()->groups.present()) {
				w.start_element(0, sml_pivotTable_groups_literal);
				_groups_writer.get_writer(context(), &t()->groups.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_groups_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, sml_pivotTable_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_extLst_literal);
			}
		}

		void CT_GroupLevels_writer::write_target_to(xml_writer& w) {
			if (t()->count.present())
				w.attribute(0, sml_pivotTable_count_literal, context()->serialize(t()->count.get()));
			for (size_t sqi = 0; sqi<t()->groupLevel.size(); ++sqi) {
				w.start_element(0, sml_pivotTable_groupLevel_literal);
				_groupLevel_writer.get_writer(context(), &t()->groupLevel[sqi])->write_target_to(w);
				w.end_element(0, sml_pivotTable_groupLevel_literal);
			}
		}

		void CT_CacheHierarchy_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_pivotTable_uniqueName_literal, context()->serialize(t()->uniqueName));
			if (t()->caption.present())
				w.attribute(0, sml_pivotTable_caption_literal, context()->serialize(t()->caption.get()));
			if (t()->measure != false)
				w.attribute(0, sml_pivotTable_measure_literal, context()->serialize(t()->measure));
			if (t()->set != false)
				w.attribute(0, sml_pivotTable_set_literal, context()->serialize(t()->set));
			if (t()->parentSet.present())
				w.attribute(0, sml_pivotTable_parentSet_literal, context()->serialize(t()->parentSet.get()));
			if (t()->iconSet != 0)
				w.attribute(0, sml_pivotTable_iconSet_literal, context()->serialize(t()->iconSet));
			if (t()->attribute != false)
				w.attribute(0, sml_pivotTable_attribute_literal, context()->serialize(t()->attribute));
			if (t()->time != false)
				w.attribute(0, sml_pivotTable_time_literal, context()->serialize(t()->time));
			if (t()->keyAttribute != false)
				w.attribute(0, sml_pivotTable_keyAttribute_literal, context()->serialize(t()->keyAttribute));
			if (t()->defaultMemberUniqueName.present())
				w.attribute(0, sml_pivotTable_defaultMemberUniqueName_literal, context()->serialize(t()->defaultMemberUniqueName.get()));
			if (t()->allUniqueName.present())
				w.attribute(0, sml_pivotTable_allUniqueName_literal, context()->serialize(t()->allUniqueName.get()));
			if (t()->allCaption.present())
				w.attribute(0, sml_pivotTable_allCaption_literal, context()->serialize(t()->allCaption.get()));
			if (t()->dimensionUniqueName.present())
				w.attribute(0, sml_pivotTable_dimensionUniqueName_literal, context()->serialize(t()->dimensionUniqueName.get()));
			if (t()->displayFolder.present())
				w.attribute(0, sml_pivotTable_displayFolder_literal, context()->serialize(t()->displayFolder.get()));
			if (t()->measureGroup.present())
				w.attribute(0, sml_pivotTable_measureGroup_literal, context()->serialize(t()->measureGroup.get()));
			if (t()->measures != false)
				w.attribute(0, sml_pivotTable_measures_literal, context()->serialize(t()->measures));
			w.attribute(0, sml_pivotTable_count_literal, context()->serialize(t()->count));
			if (t()->oneField != false)
				w.attribute(0, sml_pivotTable_oneField_literal, context()->serialize(t()->oneField));
			if (t()->memberValueDatatype.present())
				w.attribute(0, sml_pivotTable_memberValueDatatype_literal, context()->serialize(t()->memberValueDatatype.get()));
			if (t()->unbalanced.present())
				w.attribute(0, sml_pivotTable_unbalanced_literal, context()->serialize(t()->unbalanced.get()));
			if (t()->unbalancedGroup.present())
				w.attribute(0, sml_pivotTable_unbalancedGroup_literal, context()->serialize(t()->unbalancedGroup.get()));
			if (t()->hidden != false)
				w.attribute(0, sml_pivotTable_hidden_literal, context()->serialize(t()->hidden));
			if (t()->fieldsUsage.present()) {
				w.start_element(0, sml_pivotTable_fieldsUsage_literal);
				_fieldsUsage_writer.get_writer(context(), &t()->fieldsUsage.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_fieldsUsage_literal);
			}
			if (t()->groupLevels.present()) {
				w.start_element(0, sml_pivotTable_groupLevels_literal);
				_groupLevels_writer.get_writer(context(), &t()->groupLevels.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_groupLevels_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, sml_pivotTable_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_extLst_literal);
			}
		}

		void CT_CacheHierarchies_writer::write_target_to(xml_writer& w) {
			if (t()->count.present())
				w.attribute(0, sml_pivotTable_count_literal, context()->serialize(t()->count.get()));
			for (size_t sqi = 0; sqi<t()->cacheHierarchy.size(); ++sqi) {
				w.start_element(0, sml_pivotTable_cacheHierarchy_literal);
				_cacheHierarchy_writer.get_writer(context(), &t()->cacheHierarchy[sqi])->write_target_to(w);
				w.end_element(0, sml_pivotTable_cacheHierarchy_literal);
			}
		}

		void CT_PCDKPI_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_pivotTable_uniqueName_literal, context()->serialize(t()->uniqueName));
			if (t()->caption.present())
				w.attribute(0, sml_pivotTable_caption_literal, context()->serialize(t()->caption.get()));
			if (t()->displayFolder.present())
				w.attribute(0, sml_pivotTable_displayFolder_literal, context()->serialize(t()->displayFolder.get()));
			if (t()->measureGroup.present())
				w.attribute(0, sml_pivotTable_measureGroup_literal, context()->serialize(t()->measureGroup.get()));
			if (t()->parent.present())
				w.attribute(0, sml_pivotTable_parent_literal, context()->serialize(t()->parent.get()));
			w.attribute(0, sml_pivotTable_value_literal, context()->serialize(t()->value));
			if (t()->goal.present())
				w.attribute(0, sml_pivotTable_goal_literal, context()->serialize(t()->goal.get()));
			if (t()->status.present())
				w.attribute(0, sml_pivotTable_status_literal, context()->serialize(t()->status.get()));
			if (t()->trend.present())
				w.attribute(0, sml_pivotTable_trend_literal, context()->serialize(t()->trend.get()));
			if (t()->weight.present())
				w.attribute(0, sml_pivotTable_weight_literal, context()->serialize(t()->weight.get()));
			if (t()->time.present())
				w.attribute(0, sml_pivotTable_time_literal, context()->serialize(t()->time.get()));
		}

		void CT_PCDKPIs_writer::write_target_to(xml_writer& w) {
			if (t()->count.present())
				w.attribute(0, sml_pivotTable_count_literal, context()->serialize(t()->count.get()));
			for (size_t sqi = 0; sqi<t()->kpi.size(); ++sqi) {
				w.start_element(0, sml_pivotTable_kpi_literal);
				_kpi_writer.get_writer(context(), &t()->kpi[sqi])->write_target_to(w);
				w.end_element(0, sml_pivotTable_kpi_literal);
			}
		}

		void CT_PCDSDTCEntries_writer::write_target_to(xml_writer& w) {
			if (t()->count.present())
				w.attribute(0, sml_pivotTable_count_literal, context()->serialize(t()->count.get()));
			if (t()->m.present()) {
				w.start_element(0, sml_pivotTable_m_literal);
				_m_writer.get_writer(context(), &t()->m.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_m_literal);
			}
			if (t()->n.present()) {
				w.start_element(0, sml_pivotTable_n_literal);
				_n_writer.get_writer(context(), &t()->n.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_n_literal);
			}
			if (t()->e.present()) {
				w.start_element(0, sml_pivotTable_e_literal);
				_e_writer.get_writer(context(), &t()->e.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_e_literal);
			}
			if (t()->s.present()) {
				w.start_element(0, sml_pivotTable_s_literal);
				_s_writer.get_writer(context(), &t()->s.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_s_literal);
			}
		}

		void CT_Set_writer::write_target_to(xml_writer& w) {
			if (t()->count.present())
				w.attribute(0, sml_pivotTable_count_literal, context()->serialize(t()->count.get()));
			w.attribute(0, sml_pivotTable_maxRank_literal, context()->serialize(t()->maxRank));
			w.attribute(0, sml_pivotTable_setDefinition_literal, context()->serialize(t()->setDefinition));
			if (t()->sortType != ST_SortType::none_literal)
				w.attribute(0, sml_pivotTable_sortType_literal, context()->serialize(t()->sortType));
			if (t()->queryFailed != false)
				w.attribute(0, sml_pivotTable_queryFailed_literal, context()->serialize(t()->queryFailed));
			for (size_t sqi = 0; sqi<t()->tpls.size(); ++sqi) {
				w.start_element(0, sml_pivotTable_tpls_literal);
				_tpls_writer.get_writer(context(), &t()->tpls[sqi])->write_target_to(w);
				w.end_element(0, sml_pivotTable_tpls_literal);
			}
			if (t()->sortByTuple.present()) {
				w.start_element(0, sml_pivotTable_sortByTuple_literal);
				_sortByTuple_writer.get_writer(context(), &t()->sortByTuple.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_sortByTuple_literal);
			}
		}

		void CT_Sets_writer::write_target_to(xml_writer& w) {
			if (t()->count.present())
				w.attribute(0, sml_pivotTable_count_literal, context()->serialize(t()->count.get()));
			for (size_t sqi = 0; sqi<t()->set.size(); ++sqi) {
				w.start_element(0, sml_pivotTable_set_literal);
				_set_writer.get_writer(context(), &t()->set[sqi])->write_target_to(w);
				w.end_element(0, sml_pivotTable_set_literal);
			}
		}

		void CT_Query_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_pivotTable_mdx_literal, context()->serialize(t()->mdx));
			if (t()->tpls.present()) {
				w.start_element(0, sml_pivotTable_tpls_literal);
				_tpls_writer.get_writer(context(), &t()->tpls.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_tpls_literal);
			}
		}

		void CT_QueryCache_writer::write_target_to(xml_writer& w) {
			if (t()->count.present())
				w.attribute(0, sml_pivotTable_count_literal, context()->serialize(t()->count.get()));
			for (size_t sqi = 0; sqi<t()->query.size(); ++sqi) {
				w.start_element(0, sml_pivotTable_query_literal);
				_query_writer.get_writer(context(), &t()->query[sqi])->write_target_to(w);
				w.end_element(0, sml_pivotTable_query_literal);
			}
		}

		void CT_ServerFormat_writer::write_target_to(xml_writer& w) {
			if (t()->culture.present())
				w.attribute(0, sml_pivotTable_culture_literal, context()->serialize(t()->culture.get()));
			if (t()->format.present())
				w.attribute(0, sml_pivotTable_format_literal, context()->serialize(t()->format.get()));
		}

		void CT_ServerFormats_writer::write_target_to(xml_writer& w) {
			if (t()->count.present())
				w.attribute(0, sml_pivotTable_count_literal, context()->serialize(t()->count.get()));
			for (size_t sqi = 0; sqi<t()->serverFormat.size(); ++sqi) {
				w.start_element(0, sml_pivotTable_serverFormat_literal);
				_serverFormat_writer.get_writer(context(), &t()->serverFormat[sqi])->write_target_to(w);
				w.end_element(0, sml_pivotTable_serverFormat_literal);
			}
		}

		void CT_TupleCache_writer::write_target_to(xml_writer& w) {
			if (t()->entries.present()) {
				w.start_element(0, sml_pivotTable_entries_literal);
				_entries_writer.get_writer(context(), &t()->entries.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_entries_literal);
			}
			if (t()->sets.present()) {
				w.start_element(0, sml_pivotTable_sets_literal);
				_sets_writer.get_writer(context(), &t()->sets.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_sets_literal);
			}
			if (t()->queryCache.present()) {
				w.start_element(0, sml_pivotTable_queryCache_literal);
				_queryCache_writer.get_writer(context(), &t()->queryCache.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_queryCache_literal);
			}
			if (t()->serverFormats.present()) {
				w.start_element(0, sml_pivotTable_serverFormats_literal);
				_serverFormats_writer.get_writer(context(), &t()->serverFormats.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_serverFormats_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, sml_pivotTable_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_extLst_literal);
			}
		}

		void CT_CalculatedItem_writer::write_target_to(xml_writer& w) {
			if (t()->field.present())
				w.attribute(0, sml_pivotTable_field_literal, context()->serialize(t()->field.get()));
			if (t()->formula.present())
				w.attribute(0, sml_pivotTable_formula_literal, context()->serialize(t()->formula.get()));
			w.start_element(0, sml_pivotTable_pivotArea_literal);
			_pivotArea_writer.get_writer(context(), &t()->pivotArea)->write_target_to(w);
			w.end_element(0, sml_pivotTable_pivotArea_literal);
			if (t()->extLst.present()) {
				w.start_element(0, sml_pivotTable_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_extLst_literal);
			}
		}

		void CT_CalculatedItems_writer::write_target_to(xml_writer& w) {
			if (t()->count.present())
				w.attribute(0, sml_pivotTable_count_literal, context()->serialize(t()->count.get()));
			for (size_t sqi = 0; sqi<t()->calculatedItem.size(); ++sqi) {
				w.start_element(0, sml_pivotTable_calculatedItem_literal);
				_calculatedItem_writer.get_writer(context(), &t()->calculatedItem[sqi])->write_target_to(w);
				w.end_element(0, sml_pivotTable_calculatedItem_literal);
			}
		}

		void CT_CalculatedMember_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_pivotTable_name_literal, context()->serialize(t()->name));
			w.attribute(0, sml_pivotTable_mdx_literal, context()->serialize(t()->mdx));
			if (t()->memberName.present())
				w.attribute(0, sml_pivotTable_memberName_literal, context()->serialize(t()->memberName.get()));
			if (t()->hierarchy.present())
				w.attribute(0, sml_pivotTable_hierarchy_literal, context()->serialize(t()->hierarchy.get()));
			if (t()->parent.present())
				w.attribute(0, sml_pivotTable_parent_literal, context()->serialize(t()->parent.get()));
			if (t()->solveOrder != 0)
				w.attribute(0, sml_pivotTable_solveOrder_literal, context()->serialize(t()->solveOrder));
			if (t()->set != false)
				w.attribute(0, sml_pivotTable_set_literal, context()->serialize(t()->set));
			if (t()->extLst.present()) {
				w.start_element(0, sml_pivotTable_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_extLst_literal);
			}
		}

		void CT_CalculatedMembers_writer::write_target_to(xml_writer& w) {
			if (t()->count.present())
				w.attribute(0, sml_pivotTable_count_literal, context()->serialize(t()->count.get()));
			for (size_t sqi = 0; sqi<t()->calculatedMember.size(); ++sqi) {
				w.start_element(0, sml_pivotTable_calculatedMember_literal);
				_calculatedMember_writer.get_writer(context(), &t()->calculatedMember[sqi])->write_target_to(w);
				w.end_element(0, sml_pivotTable_calculatedMember_literal);
			}
		}

		void CT_PivotDimension_writer::write_target_to(xml_writer& w) {
			if (t()->measure != false)
				w.attribute(0, sml_pivotTable_measure_literal, context()->serialize(t()->measure));
			w.attribute(0, sml_pivotTable_name_literal, context()->serialize(t()->name));
			w.attribute(0, sml_pivotTable_uniqueName_literal, context()->serialize(t()->uniqueName));
			w.attribute(0, sml_pivotTable_caption_literal, context()->serialize(t()->caption));
		}

		void CT_Dimensions_writer::write_target_to(xml_writer& w) {
			if (t()->count.present())
				w.attribute(0, sml_pivotTable_count_literal, context()->serialize(t()->count.get()));
			for (size_t sqi = 0; sqi<t()->dimension.size(); ++sqi) {
				w.start_element(0, sml_pivotTable_dimension_literal);
				_dimension_writer.get_writer(context(), &t()->dimension[sqi])->write_target_to(w);
				w.end_element(0, sml_pivotTable_dimension_literal);
			}
		}

		void CT_MeasureGroup_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_pivotTable_name_literal, context()->serialize(t()->name));
			w.attribute(0, sml_pivotTable_caption_literal, context()->serialize(t()->caption));
		}

		void CT_MeasureGroups_writer::write_target_to(xml_writer& w) {
			if (t()->count.present())
				w.attribute(0, sml_pivotTable_count_literal, context()->serialize(t()->count.get()));
			for (size_t sqi = 0; sqi<t()->measureGroup.size(); ++sqi) {
				w.start_element(0, sml_pivotTable_measureGroup_literal);
				_measureGroup_writer.get_writer(context(), &t()->measureGroup[sqi])->write_target_to(w);
				w.end_element(0, sml_pivotTable_measureGroup_literal);
			}
		}

		void CT_MeasureDimensionMap_writer::write_target_to(xml_writer& w) {
			if (t()->measureGroup.present())
				w.attribute(0, sml_pivotTable_measureGroup_literal, context()->serialize(t()->measureGroup.get()));
			if (t()->dimension.present())
				w.attribute(0, sml_pivotTable_dimension_literal, context()->serialize(t()->dimension.get()));
		}

		void CT_MeasureDimensionMaps_writer::write_target_to(xml_writer& w) {
			if (t()->count.present())
				w.attribute(0, sml_pivotTable_count_literal, context()->serialize(t()->count.get()));
			for (size_t sqi = 0; sqi<t()->map.size(); ++sqi) {
				w.start_element(0, sml_pivotTable_map_literal);
				_map_writer.get_writer(context(), &t()->map[sqi])->write_target_to(w);
				w.end_element(0, sml_pivotTable_map_literal);
			}
		}

		void CT_PivotCacheDefinition_writer::write_target_to(xml_writer& w) {
			if (t()->id.present())
				w.attribute(sml_pivotTable_r_literal, sml_pivotTable_id_literal, context()->serialize(t()->id.get()));
			if (t()->invalid != false)
				w.attribute(0, sml_pivotTable_invalid_literal, context()->serialize(t()->invalid));
			if (t()->saveData != true)
				w.attribute(0, sml_pivotTable_saveData_literal, context()->serialize(t()->saveData));
			if (t()->refreshOnLoad != false)
				w.attribute(0, sml_pivotTable_refreshOnLoad_literal, context()->serialize(t()->refreshOnLoad));
			if (t()->optimizeMemory != false)
				w.attribute(0, sml_pivotTable_optimizeMemory_literal, context()->serialize(t()->optimizeMemory));
			if (t()->enableRefresh != true)
				w.attribute(0, sml_pivotTable_enableRefresh_literal, context()->serialize(t()->enableRefresh));
			if (t()->refreshedBy.present())
				w.attribute(0, sml_pivotTable_refreshedBy_literal, context()->serialize(t()->refreshedBy.get()));
			if (t()->refreshedDate.present())
				w.attribute(0, sml_pivotTable_refreshedDate_literal, context()->serialize(t()->refreshedDate.get()));
			if (t()->backgroundQuery != false)
				w.attribute(0, sml_pivotTable_backgroundQuery_literal, context()->serialize(t()->backgroundQuery));
			if (t()->missingItemsLimit.present())
				w.attribute(0, sml_pivotTable_missingItemsLimit_literal, context()->serialize(t()->missingItemsLimit.get()));
			if (t()->createdVersion != 0)
				w.attribute(0, sml_pivotTable_createdVersion_literal, context()->serialize(t()->createdVersion));
			if (t()->refreshedVersion != 0)
				w.attribute(0, sml_pivotTable_refreshedVersion_literal, context()->serialize(t()->refreshedVersion));
			if (t()->minRefreshableVersion != 0)
				w.attribute(0, sml_pivotTable_minRefreshableVersion_literal, context()->serialize(t()->minRefreshableVersion));
			if (t()->recordCount.present())
				w.attribute(0, sml_pivotTable_recordCount_literal, context()->serialize(t()->recordCount.get()));
			if (t()->upgradeOnRefresh != false)
				w.attribute(0, sml_pivotTable_upgradeOnRefresh_literal, context()->serialize(t()->upgradeOnRefresh));
			if (t()->tupleCache_attr != false)
				w.attribute(0, sml_pivotTable_tupleCache_literal, context()->serialize(t()->tupleCache_attr));
			if (t()->supportSubquery != false)
				w.attribute(0, sml_pivotTable_supportSubquery_literal, context()->serialize(t()->supportSubquery));
			if (t()->supportAdvancedDrill != false)
				w.attribute(0, sml_pivotTable_supportAdvancedDrill_literal, context()->serialize(t()->supportAdvancedDrill));
			w.start_element(0, sml_pivotTable_cacheSource_literal);
			_cacheSource_writer.get_writer(context(), &t()->cacheSource)->write_target_to(w);
			w.end_element(0, sml_pivotTable_cacheSource_literal);
			w.start_element(0, sml_pivotTable_cacheFields_literal);
			_cacheFields_writer.get_writer(context(), &t()->cacheFields)->write_target_to(w);
			w.end_element(0, sml_pivotTable_cacheFields_literal);
			if (t()->cacheHierarchies.present()) {
				w.start_element(0, sml_pivotTable_cacheHierarchies_literal);
				_cacheHierarchies_writer.get_writer(context(), &t()->cacheHierarchies.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_cacheHierarchies_literal);
			}
			if (t()->kpis.present()) {
				w.start_element(0, sml_pivotTable_kpis_literal);
				_kpis_writer.get_writer(context(), &t()->kpis.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_kpis_literal);
			}
			if (t()->tupleCache.present()) {
				w.start_element(0, sml_pivotTable_tupleCache_literal);
				_tupleCache_writer.get_writer(context(), &t()->tupleCache.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_tupleCache_literal);
			}
			if (t()->calculatedItems.present()) {
				w.start_element(0, sml_pivotTable_calculatedItems_literal);
				_calculatedItems_writer.get_writer(context(), &t()->calculatedItems.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_calculatedItems_literal);
			}
			if (t()->calculatedMembers.present()) {
				w.start_element(0, sml_pivotTable_calculatedMembers_literal);
				_calculatedMembers_writer.get_writer(context(), &t()->calculatedMembers.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_calculatedMembers_literal);
			}
			if (t()->dimensions.present()) {
				w.start_element(0, sml_pivotTable_dimensions_literal);
				_dimensions_writer.get_writer(context(), &t()->dimensions.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_dimensions_literal);
			}
			if (t()->measureGroups.present()) {
				w.start_element(0, sml_pivotTable_measureGroups_literal);
				_measureGroups_writer.get_writer(context(), &t()->measureGroups.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_measureGroups_literal);
			}
			if (t()->maps.present()) {
				w.start_element(0, sml_pivotTable_maps_literal);
				_maps_writer.get_writer(context(), &t()->maps.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_maps_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, sml_pivotTable_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_extLst_literal);
			}
		}

		void CT_Record_writer::write_target_to(xml_writer& w) {
			if (t()->m.present()) {
				w.start_element(0, sml_pivotTable_m_literal);
				_m_writer.get_writer(context(), &t()->m.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_m_literal);
			}
			if (t()->n.present()) {
				w.start_element(0, sml_pivotTable_n_literal);
				_n_writer.get_writer(context(), &t()->n.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_n_literal);
			}
			if (t()->b.present()) {
				w.start_element(0, sml_pivotTable_b_literal);
				_b_writer.get_writer(context(), &t()->b.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_b_literal);
			}
			if (t()->e.present()) {
				w.start_element(0, sml_pivotTable_e_literal);
				_e_writer.get_writer(context(), &t()->e.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_e_literal);
			}
			if (t()->s.present()) {
				w.start_element(0, sml_pivotTable_s_literal);
				_s_writer.get_writer(context(), &t()->s.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_s_literal);
			}
			if (t()->d.present()) {
				w.start_element(0, sml_pivotTable_d_literal);
				_d_writer.get_writer(context(), &t()->d.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_d_literal);
			}
			if (t()->x.present()) {
				w.start_element(0, sml_pivotTable_x_literal);
				_x_writer.get_writer(context(), &t()->x.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_x_literal);
			}
		}

		void CT_PivotCacheRecords_writer::write_target_to(xml_writer& w) {
			if (t()->count.present())
				w.attribute(0, sml_pivotTable_count_literal, context()->serialize(t()->count.get()));
			for (size_t sqi = 0; sqi<t()->r.size(); ++sqi) {
				w.start_element(0, sml_pivotTable_r_literal);
				_r_writer.get_writer(context(), &t()->r[sqi])->write_target_to(w);
				w.end_element(0, sml_pivotTable_r_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, sml_pivotTable_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_extLst_literal);
			}
		}

		void CT_Location_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_pivotTable_ref_literal, context()->serialize(t()->ref));
			w.attribute(0, sml_pivotTable_firstHeaderRow_literal, context()->serialize(t()->firstHeaderRow));
			w.attribute(0, sml_pivotTable_firstDataRow_literal, context()->serialize(t()->firstDataRow));
			w.attribute(0, sml_pivotTable_firstDataCol_literal, context()->serialize(t()->firstDataCol));
			if (t()->rowPageCount != 0U)
				w.attribute(0, sml_pivotTable_rowPageCount_literal, context()->serialize(t()->rowPageCount));
			if (t()->colPageCount != 0U)
				w.attribute(0, sml_pivotTable_colPageCount_literal, context()->serialize(t()->colPageCount));
		}

		void CT_Item_writer::write_target_to(xml_writer& w) {
			if (t()->n.present())
				w.attribute(0, sml_pivotTable_n_literal, context()->serialize(t()->n.get()));
			if (t()->t != ST_ItemType::data_literal)
				w.attribute(0, sml_pivotTable_t_literal, context()->serialize(t()->t));
			if (t()->h != false)
				w.attribute(0, sml_pivotTable_h_literal, context()->serialize(t()->h));
			if (t()->s != false)
				w.attribute(0, sml_pivotTable_s_literal, context()->serialize(t()->s));
			if (t()->sd != true)
				w.attribute(0, sml_pivotTable_sd_literal, context()->serialize(t()->sd));
			if (t()->f != false)
				w.attribute(0, sml_pivotTable_f_literal, context()->serialize(t()->f));
			if (t()->m != false)
				w.attribute(0, sml_pivotTable_m_literal, context()->serialize(t()->m));
			if (t()->c != false)
				w.attribute(0, sml_pivotTable_c_literal, context()->serialize(t()->c));
			if (t()->x.present())
				w.attribute(0, sml_pivotTable_x_literal, context()->serialize(t()->x.get()));
			if (t()->d != false)
				w.attribute(0, sml_pivotTable_d_literal, context()->serialize(t()->d));
			if (t()->e != true)
				w.attribute(0, sml_pivotTable_e_literal, context()->serialize(t()->e));
		}

		void CT_Items_writer::write_target_to(xml_writer& w) {
			if (t()->count.present())
				w.attribute(0, sml_pivotTable_count_literal, context()->serialize(t()->count.get()));
			for (size_t sqi = 0; sqi<t()->item.size(); ++sqi) {
				w.start_element(0, sml_pivotTable_item_literal);
				_item_writer.get_writer(context(), &t()->item[sqi])->write_target_to(w);
				w.end_element(0, sml_pivotTable_item_literal);
			}
		}

		void CT_AutoSortScope_writer::write_target_to(xml_writer& w) {
			w.start_element(0, sml_pivotTable_pivotArea_literal);
			_pivotArea_writer.get_writer(context(), &t()->pivotArea)->write_target_to(w);
			w.end_element(0, sml_pivotTable_pivotArea_literal);
		}

		void CT_PivotField_writer::write_target_to(xml_writer& w) {
			if (t()->name.present())
				w.attribute(0, sml_pivotTable_name_literal, context()->serialize(t()->name.get()));
			if (t()->axis.present())
				w.attribute(0, sml_pivotTable_axis_literal, context()->serialize(t()->axis.get()));
			if (t()->dataField != false)
				w.attribute(0, sml_pivotTable_dataField_literal, context()->serialize(t()->dataField));
			if (t()->subtotalCaption.present())
				w.attribute(0, sml_pivotTable_subtotalCaption_literal, context()->serialize(t()->subtotalCaption.get()));
			if (t()->showDropDowns != true)
				w.attribute(0, sml_pivotTable_showDropDowns_literal, context()->serialize(t()->showDropDowns));
			if (t()->hiddenLevel != false)
				w.attribute(0, sml_pivotTable_hiddenLevel_literal, context()->serialize(t()->hiddenLevel));
			if (t()->uniqueMemberProperty.present())
				w.attribute(0, sml_pivotTable_uniqueMemberProperty_literal, context()->serialize(t()->uniqueMemberProperty.get()));
			if (t()->compact != true)
				w.attribute(0, sml_pivotTable_compact_literal, context()->serialize(t()->compact));
			if (t()->allDrilled != false)
				w.attribute(0, sml_pivotTable_allDrilled_literal, context()->serialize(t()->allDrilled));
			if (t()->numFmtId.present())
				w.attribute(0, sml_pivotTable_numFmtId_literal, context()->serialize(t()->numFmtId.get()));
			if (t()->outline != true)
				w.attribute(0, sml_pivotTable_outline_literal, context()->serialize(t()->outline));
			if (t()->subtotalTop != true)
				w.attribute(0, sml_pivotTable_subtotalTop_literal, context()->serialize(t()->subtotalTop));
			if (t()->dragToRow != true)
				w.attribute(0, sml_pivotTable_dragToRow_literal, context()->serialize(t()->dragToRow));
			if (t()->dragToCol != true)
				w.attribute(0, sml_pivotTable_dragToCol_literal, context()->serialize(t()->dragToCol));
			if (t()->multipleItemSelectionAllowed != false)
				w.attribute(0, sml_pivotTable_multipleItemSelectionAllowed_literal, context()->serialize(t()->multipleItemSelectionAllowed));
			if (t()->dragToPage != true)
				w.attribute(0, sml_pivotTable_dragToPage_literal, context()->serialize(t()->dragToPage));
			if (t()->dragToData != true)
				w.attribute(0, sml_pivotTable_dragToData_literal, context()->serialize(t()->dragToData));
			if (t()->dragOff != true)
				w.attribute(0, sml_pivotTable_dragOff_literal, context()->serialize(t()->dragOff));
			if (t()->showAll != true)
				w.attribute(0, sml_pivotTable_showAll_literal, context()->serialize(t()->showAll));
			if (t()->insertBlankRow != false)
				w.attribute(0, sml_pivotTable_insertBlankRow_literal, context()->serialize(t()->insertBlankRow));
			if (t()->serverField != false)
				w.attribute(0, sml_pivotTable_serverField_literal, context()->serialize(t()->serverField));
			if (t()->insertPageBreak != false)
				w.attribute(0, sml_pivotTable_insertPageBreak_literal, context()->serialize(t()->insertPageBreak));
			if (t()->autoShow != false)
				w.attribute(0, sml_pivotTable_autoShow_literal, context()->serialize(t()->autoShow));
			if (t()->topAutoShow != true)
				w.attribute(0, sml_pivotTable_topAutoShow_literal, context()->serialize(t()->topAutoShow));
			if (t()->hideNewItems != false)
				w.attribute(0, sml_pivotTable_hideNewItems_literal, context()->serialize(t()->hideNewItems));
			if (t()->measureFilter != false)
				w.attribute(0, sml_pivotTable_measureFilter_literal, context()->serialize(t()->measureFilter));
			if (t()->includeNewItemsInFilter != false)
				w.attribute(0, sml_pivotTable_includeNewItemsInFilter_literal, context()->serialize(t()->includeNewItemsInFilter));
			if (t()->itemPageCount != 10U)
				w.attribute(0, sml_pivotTable_itemPageCount_literal, context()->serialize(t()->itemPageCount));
			if (t()->sortType != ST_FieldSortType::manual_literal)
				w.attribute(0, sml_pivotTable_sortType_literal, context()->serialize(t()->sortType));
			if (t()->dataSourceSort.present())
				w.attribute(0, sml_pivotTable_dataSourceSort_literal, context()->serialize(t()->dataSourceSort.get()));
			if (t()->nonAutoSortDefault != false)
				w.attribute(0, sml_pivotTable_nonAutoSortDefault_literal, context()->serialize(t()->nonAutoSortDefault));
			if (t()->rankBy.present())
				w.attribute(0, sml_pivotTable_rankBy_literal, context()->serialize(t()->rankBy.get()));
			if (t()->defaultSubtotal != true)
				w.attribute(0, sml_pivotTable_defaultSubtotal_literal, context()->serialize(t()->defaultSubtotal));
			if (t()->sumSubtotal != false)
				w.attribute(0, sml_pivotTable_sumSubtotal_literal, context()->serialize(t()->sumSubtotal));
			if (t()->countASubtotal != false)
				w.attribute(0, sml_pivotTable_countASubtotal_literal, context()->serialize(t()->countASubtotal));
			if (t()->avgSubtotal != false)
				w.attribute(0, sml_pivotTable_avgSubtotal_literal, context()->serialize(t()->avgSubtotal));
			if (t()->maxSubtotal != false)
				w.attribute(0, sml_pivotTable_maxSubtotal_literal, context()->serialize(t()->maxSubtotal));
			if (t()->minSubtotal != false)
				w.attribute(0, sml_pivotTable_minSubtotal_literal, context()->serialize(t()->minSubtotal));
			if (t()->productSubtotal != false)
				w.attribute(0, sml_pivotTable_productSubtotal_literal, context()->serialize(t()->productSubtotal));
			if (t()->countSubtotal != false)
				w.attribute(0, sml_pivotTable_countSubtotal_literal, context()->serialize(t()->countSubtotal));
			if (t()->stdDevSubtotal != false)
				w.attribute(0, sml_pivotTable_stdDevSubtotal_literal, context()->serialize(t()->stdDevSubtotal));
			if (t()->stdDevPSubtotal != false)
				w.attribute(0, sml_pivotTable_stdDevPSubtotal_literal, context()->serialize(t()->stdDevPSubtotal));
			if (t()->varSubtotal != false)
				w.attribute(0, sml_pivotTable_varSubtotal_literal, context()->serialize(t()->varSubtotal));
			if (t()->varPSubtotal != false)
				w.attribute(0, sml_pivotTable_varPSubtotal_literal, context()->serialize(t()->varPSubtotal));
			if (t()->showPropCell != false)
				w.attribute(0, sml_pivotTable_showPropCell_literal, context()->serialize(t()->showPropCell));
			if (t()->showPropTip != false)
				w.attribute(0, sml_pivotTable_showPropTip_literal, context()->serialize(t()->showPropTip));
			if (t()->showPropAsCaption != false)
				w.attribute(0, sml_pivotTable_showPropAsCaption_literal, context()->serialize(t()->showPropAsCaption));
			if (t()->defaultAttributeDrillState != false)
				w.attribute(0, sml_pivotTable_defaultAttributeDrillState_literal, context()->serialize(t()->defaultAttributeDrillState));
			if (t()->items.present()) {
				w.start_element(0, sml_pivotTable_items_literal);
				_items_writer.get_writer(context(), &t()->items.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_items_literal);
			}
			if (t()->autoSortScope.present()) {
				w.start_element(0, sml_pivotTable_autoSortScope_literal);
				_autoSortScope_writer.get_writer(context(), &t()->autoSortScope.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_autoSortScope_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, sml_pivotTable_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_extLst_literal);
			}
		}

		void CT_PivotFields_writer::write_target_to(xml_writer& w) {
			if (t()->count.present())
				w.attribute(0, sml_pivotTable_count_literal, context()->serialize(t()->count.get()));
			for (size_t sqi = 0; sqi<t()->pivotField.size(); ++sqi) {
				w.start_element(0, sml_pivotTable_pivotField_literal);
				_pivotField_writer.get_writer(context(), &t()->pivotField[sqi])->write_target_to(w);
				w.end_element(0, sml_pivotTable_pivotField_literal);
			}
		}

		void CT_Field_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_pivotTable_x_literal, context()->serialize(t()->x));
		}

		void CT_RowFields_writer::write_target_to(xml_writer& w) {
			if (t()->count != 0U)
				w.attribute(0, sml_pivotTable_count_literal, context()->serialize(t()->count));
			for (size_t sqi = 0; sqi<t()->field.size(); ++sqi) {
				w.start_element(0, sml_pivotTable_field_literal);
				_field_writer.get_writer(context(), &t()->field[sqi])->write_target_to(w);
				w.end_element(0, sml_pivotTable_field_literal);
			}
		}

		void CT_I_writer::write_target_to(xml_writer& w) {
			if (t()->t != ST_ItemType::data_literal)
				w.attribute(0, sml_pivotTable_t_literal, context()->serialize(t()->t));
			if (t()->r != 0U)
				w.attribute(0, sml_pivotTable_r_literal, context()->serialize(t()->r));
			if (t()->i != 0U)
				w.attribute(0, sml_pivotTable_i_literal, context()->serialize(t()->i));
			for (size_t sqi = 0; sqi<t()->x.size(); ++sqi) {
				w.start_element(0, sml_pivotTable_x_literal);
				_x_writer.get_writer(context(), &t()->x[sqi])->write_target_to(w);
				w.end_element(0, sml_pivotTable_x_literal);
			}
		}

		void CT_rowItems_writer::write_target_to(xml_writer& w) {
			if (t()->count.present())
				w.attribute(0, sml_pivotTable_count_literal, context()->serialize(t()->count.get()));
			for (size_t sqi = 0; sqi<t()->i.size(); ++sqi) {
				w.start_element(0, sml_pivotTable_i_literal);
				_i_writer.get_writer(context(), &t()->i[sqi])->write_target_to(w);
				w.end_element(0, sml_pivotTable_i_literal);
			}
		}

		void CT_ColFields_writer::write_target_to(xml_writer& w) {
			if (t()->count != 0U)
				w.attribute(0, sml_pivotTable_count_literal, context()->serialize(t()->count));
			for (size_t sqi = 0; sqi<t()->field.size(); ++sqi) {
				w.start_element(0, sml_pivotTable_field_literal);
				_field_writer.get_writer(context(), &t()->field[sqi])->write_target_to(w);
				w.end_element(0, sml_pivotTable_field_literal);
			}
		}

		void CT_colItems_writer::write_target_to(xml_writer& w) {
			if (t()->count.present())
				w.attribute(0, sml_pivotTable_count_literal, context()->serialize(t()->count.get()));
			for (size_t sqi = 0; sqi<t()->i.size(); ++sqi) {
				w.start_element(0, sml_pivotTable_i_literal);
				_i_writer.get_writer(context(), &t()->i[sqi])->write_target_to(w);
				w.end_element(0, sml_pivotTable_i_literal);
			}
		}

		void CT_PageField_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_pivotTable_fld_literal, context()->serialize(t()->fld));
			if (t()->item.present())
				w.attribute(0, sml_pivotTable_item_literal, context()->serialize(t()->item.get()));
			if (t()->hier.present())
				w.attribute(0, sml_pivotTable_hier_literal, context()->serialize(t()->hier.get()));
			if (t()->name.present())
				w.attribute(0, sml_pivotTable_name_literal, context()->serialize(t()->name.get()));
			if (t()->cap.present())
				w.attribute(0, sml_pivotTable_cap_literal, context()->serialize(t()->cap.get()));
			if (t()->extLst.present()) {
				w.start_element(0, sml_pivotTable_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_extLst_literal);
			}
		}

		void CT_PageFields_writer::write_target_to(xml_writer& w) {
			if (t()->count.present())
				w.attribute(0, sml_pivotTable_count_literal, context()->serialize(t()->count.get()));
			for (size_t sqi = 0; sqi<t()->pageField.size(); ++sqi) {
				w.start_element(0, sml_pivotTable_pageField_literal);
				_pageField_writer.get_writer(context(), &t()->pageField[sqi])->write_target_to(w);
				w.end_element(0, sml_pivotTable_pageField_literal);
			}
		}

		void CT_DataField_writer::write_target_to(xml_writer& w) {
			if (t()->name.present())
				w.attribute(0, sml_pivotTable_name_literal, context()->serialize(t()->name.get()));
			w.attribute(0, sml_pivotTable_fld_literal, context()->serialize(t()->fld));
			if (t()->subtotal != ST_DataConsolidateFunction::sum_literal)
				w.attribute(0, sml_pivotTable_subtotal_literal, context()->serialize(t()->subtotal));
			if (t()->showDataAs != ST_ShowDataAs::normal_literal)
				w.attribute(0, sml_pivotTable_showDataAs_literal, context()->serialize(t()->showDataAs));
			if (t()->baseField != -1)
				w.attribute(0, sml_pivotTable_baseField_literal, context()->serialize(t()->baseField));
			if (t()->baseItem != 1048832U)
				w.attribute(0, sml_pivotTable_baseItem_literal, context()->serialize(t()->baseItem));
			if (t()->numFmtId.present())
				w.attribute(0, sml_pivotTable_numFmtId_literal, context()->serialize(t()->numFmtId.get()));
			if (t()->extLst.present()) {
				w.start_element(0, sml_pivotTable_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_extLst_literal);
			}
		}

		void CT_DataFields_writer::write_target_to(xml_writer& w) {
			if (t()->count.present())
				w.attribute(0, sml_pivotTable_count_literal, context()->serialize(t()->count.get()));
			for (size_t sqi = 0; sqi<t()->dataField.size(); ++sqi) {
				w.start_element(0, sml_pivotTable_dataField_literal);
				_dataField_writer.get_writer(context(), &t()->dataField[sqi])->write_target_to(w);
				w.end_element(0, sml_pivotTable_dataField_literal);
			}
		}

		void CT_Format_writer::write_target_to(xml_writer& w) {
			if (t()->action != ST_FormatAction::formatting_literal)
				w.attribute(0, sml_pivotTable_action_literal, context()->serialize(t()->action));
			if (t()->dxfId.present())
				w.attribute(0, sml_pivotTable_dxfId_literal, context()->serialize(t()->dxfId.get()));
			w.start_element(0, sml_pivotTable_pivotArea_literal);
			_pivotArea_writer.get_writer(context(), &t()->pivotArea)->write_target_to(w);
			w.end_element(0, sml_pivotTable_pivotArea_literal);
			if (t()->extLst.present()) {
				w.start_element(0, sml_pivotTable_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_extLst_literal);
			}
		}

		void CT_Formats_writer::write_target_to(xml_writer& w) {
			if (t()->count != 0U)
				w.attribute(0, sml_pivotTable_count_literal, context()->serialize(t()->count));
			for (size_t sqi = 0; sqi<t()->format.size(); ++sqi) {
				w.start_element(0, sml_pivotTable_format_literal);
				_format_writer.get_writer(context(), &t()->format[sqi])->write_target_to(w);
				w.end_element(0, sml_pivotTable_format_literal);
			}
		}

		void CT_PivotAreas_writer::write_target_to(xml_writer& w) {
			if (t()->count.present())
				w.attribute(0, sml_pivotTable_count_literal, context()->serialize(t()->count.get()));
			for (size_t sqi = 0; sqi<t()->pivotArea.size(); ++sqi) {
				w.start_element(0, sml_pivotTable_pivotArea_literal);
				_pivotArea_writer.get_writer(context(), &t()->pivotArea[sqi])->write_target_to(w);
				w.end_element(0, sml_pivotTable_pivotArea_literal);
			}
		}

		void CT_ConditionalFormat_writer::write_target_to(xml_writer& w) {
			if (t()->scope != ST_Scope::selection_literal)
				w.attribute(0, sml_pivotTable_scope_literal, context()->serialize(t()->scope));
			if (t()->type != ST_Type::none_literal)
				w.attribute(0, sml_pivotTable_type_literal, context()->serialize(t()->type));
			w.attribute(0, sml_pivotTable_priority_literal, context()->serialize(t()->priority));
			w.start_element(0, sml_pivotTable_pivotAreas_literal);
			_pivotAreas_writer.get_writer(context(), &t()->pivotAreas)->write_target_to(w);
			w.end_element(0, sml_pivotTable_pivotAreas_literal);
			if (t()->extLst.present()) {
				w.start_element(0, sml_pivotTable_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_extLst_literal);
			}
		}

		void CT_ConditionalFormats_writer::write_target_to(xml_writer& w) {
			if (t()->count != 0U)
				w.attribute(0, sml_pivotTable_count_literal, context()->serialize(t()->count));
			for (size_t sqi = 0; sqi<t()->conditionalFormat.size(); ++sqi) {
				w.start_element(0, sml_pivotTable_conditionalFormat_literal);
				_conditionalFormat_writer.get_writer(context(), &t()->conditionalFormat[sqi])->write_target_to(w);
				w.end_element(0, sml_pivotTable_conditionalFormat_literal);
			}
		}

		void CT_ChartFormat_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_pivotTable_chart_literal, context()->serialize(t()->chart));
			w.attribute(0, sml_pivotTable_format_literal, context()->serialize(t()->format));
			if (t()->series != false)
				w.attribute(0, sml_pivotTable_series_literal, context()->serialize(t()->series));
			w.start_element(0, sml_pivotTable_pivotArea_literal);
			_pivotArea_writer.get_writer(context(), &t()->pivotArea)->write_target_to(w);
			w.end_element(0, sml_pivotTable_pivotArea_literal);
		}

		void CT_ChartFormats_writer::write_target_to(xml_writer& w) {
			if (t()->count != 0U)
				w.attribute(0, sml_pivotTable_count_literal, context()->serialize(t()->count));
			for (size_t sqi = 0; sqi<t()->chartFormat.size(); ++sqi) {
				w.start_element(0, sml_pivotTable_chartFormat_literal);
				_chartFormat_writer.get_writer(context(), &t()->chartFormat[sqi])->write_target_to(w);
				w.end_element(0, sml_pivotTable_chartFormat_literal);
			}
		}

		void CT_MemberProperty_writer::write_target_to(xml_writer& w) {
			if (t()->name.present())
				w.attribute(0, sml_pivotTable_name_literal, context()->serialize(t()->name.get()));
			if (t()->showCell != false)
				w.attribute(0, sml_pivotTable_showCell_literal, context()->serialize(t()->showCell));
			if (t()->showTip != false)
				w.attribute(0, sml_pivotTable_showTip_literal, context()->serialize(t()->showTip));
			if (t()->showAsCaption != false)
				w.attribute(0, sml_pivotTable_showAsCaption_literal, context()->serialize(t()->showAsCaption));
			if (t()->nameLen.present())
				w.attribute(0, sml_pivotTable_nameLen_literal, context()->serialize(t()->nameLen.get()));
			if (t()->pPos.present())
				w.attribute(0, sml_pivotTable_pPos_literal, context()->serialize(t()->pPos.get()));
			if (t()->pLen.present())
				w.attribute(0, sml_pivotTable_pLen_literal, context()->serialize(t()->pLen.get()));
			if (t()->level.present())
				w.attribute(0, sml_pivotTable_level_literal, context()->serialize(t()->level.get()));
			w.attribute(0, sml_pivotTable_field_literal, context()->serialize(t()->field));
		}

		void CT_MemberProperties_writer::write_target_to(xml_writer& w) {
			if (t()->count.present())
				w.attribute(0, sml_pivotTable_count_literal, context()->serialize(t()->count.get()));
			for (size_t sqi = 0; sqi<t()->mp.size(); ++sqi) {
				w.start_element(0, sml_pivotTable_mp_literal);
				_mp_writer.get_writer(context(), &t()->mp[sqi])->write_target_to(w);
				w.end_element(0, sml_pivotTable_mp_literal);
			}
		}

		void CT_Member_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_pivotTable_name_literal, context()->serialize(t()->name));
		}

		void CT_Members_writer::write_target_to(xml_writer& w) {
			if (t()->count.present())
				w.attribute(0, sml_pivotTable_count_literal, context()->serialize(t()->count.get()));
			if (t()->level.present())
				w.attribute(0, sml_pivotTable_level_literal, context()->serialize(t()->level.get()));
			for (size_t sqi = 0; sqi<t()->member.size(); ++sqi) {
				w.start_element(0, sml_pivotTable_member_literal);
				_member_writer.get_writer(context(), &t()->member[sqi])->write_target_to(w);
				w.end_element(0, sml_pivotTable_member_literal);
			}
		}

		void CT_PivotHierarchy_writer::write_target_to(xml_writer& w) {
			if (t()->outline != false)
				w.attribute(0, sml_pivotTable_outline_literal, context()->serialize(t()->outline));
			if (t()->multipleItemSelectionAllowed != false)
				w.attribute(0, sml_pivotTable_multipleItemSelectionAllowed_literal, context()->serialize(t()->multipleItemSelectionAllowed));
			if (t()->subtotalTop != false)
				w.attribute(0, sml_pivotTable_subtotalTop_literal, context()->serialize(t()->subtotalTop));
			if (t()->showInFieldList != true)
				w.attribute(0, sml_pivotTable_showInFieldList_literal, context()->serialize(t()->showInFieldList));
			if (t()->dragToRow != true)
				w.attribute(0, sml_pivotTable_dragToRow_literal, context()->serialize(t()->dragToRow));
			if (t()->dragToCol != true)
				w.attribute(0, sml_pivotTable_dragToCol_literal, context()->serialize(t()->dragToCol));
			if (t()->dragToPage != true)
				w.attribute(0, sml_pivotTable_dragToPage_literal, context()->serialize(t()->dragToPage));
			if (t()->dragToData != false)
				w.attribute(0, sml_pivotTable_dragToData_literal, context()->serialize(t()->dragToData));
			if (t()->dragOff != true)
				w.attribute(0, sml_pivotTable_dragOff_literal, context()->serialize(t()->dragOff));
			if (t()->includeNewItemsInFilter != false)
				w.attribute(0, sml_pivotTable_includeNewItemsInFilter_literal, context()->serialize(t()->includeNewItemsInFilter));
			if (t()->caption.present())
				w.attribute(0, sml_pivotTable_caption_literal, context()->serialize(t()->caption.get()));
			if (t()->mps.present()) {
				w.start_element(0, sml_pivotTable_mps_literal);
				_mps_writer.get_writer(context(), &t()->mps.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_mps_literal);
			}
			for (size_t sqi = 0; sqi<t()->members.size(); ++sqi) {
				w.start_element(0, sml_pivotTable_members_literal);
				_members_writer.get_writer(context(), &t()->members[sqi])->write_target_to(w);
				w.end_element(0, sml_pivotTable_members_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, sml_pivotTable_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_extLst_literal);
			}
		}

		void CT_PivotHierarchies_writer::write_target_to(xml_writer& w) {
			if (t()->count.present())
				w.attribute(0, sml_pivotTable_count_literal, context()->serialize(t()->count.get()));
			for (size_t sqi = 0; sqi<t()->pivotHierarchy.size(); ++sqi) {
				w.start_element(0, sml_pivotTable_pivotHierarchy_literal);
				_pivotHierarchy_writer.get_writer(context(), &t()->pivotHierarchy[sqi])->write_target_to(w);
				w.end_element(0, sml_pivotTable_pivotHierarchy_literal);
			}
		}

		void CT_PivotTableStyle_writer::write_target_to(xml_writer& w) {
			if (t()->name.present())
				w.attribute(0, sml_pivotTable_name_literal, context()->serialize(t()->name.get()));
			if (t()->showRowHeaders.present())
				w.attribute(0, sml_pivotTable_showRowHeaders_literal, context()->serialize(t()->showRowHeaders.get()));
			if (t()->showColHeaders.present())
				w.attribute(0, sml_pivotTable_showColHeaders_literal, context()->serialize(t()->showColHeaders.get()));
			if (t()->showRowStripes.present())
				w.attribute(0, sml_pivotTable_showRowStripes_literal, context()->serialize(t()->showRowStripes.get()));
			if (t()->showColStripes.present())
				w.attribute(0, sml_pivotTable_showColStripes_literal, context()->serialize(t()->showColStripes.get()));
			if (t()->showLastColumn.present())
				w.attribute(0, sml_pivotTable_showLastColumn_literal, context()->serialize(t()->showLastColumn.get()));
		}

		void CT_PivotFilter_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_pivotTable_fld_literal, context()->serialize(t()->fld));
			if (t()->mpFld.present())
				w.attribute(0, sml_pivotTable_mpFld_literal, context()->serialize(t()->mpFld.get()));
			w.attribute(0, sml_pivotTable_type_literal, context()->serialize(t()->type));
			if (t()->evalOrder != 0)
				w.attribute(0, sml_pivotTable_evalOrder_literal, context()->serialize(t()->evalOrder));
			w.attribute(0, sml_pivotTable_id_literal, context()->serialize(t()->id));
			if (t()->iMeasureHier.present())
				w.attribute(0, sml_pivotTable_iMeasureHier_literal, context()->serialize(t()->iMeasureHier.get()));
			if (t()->iMeasureFld.present())
				w.attribute(0, sml_pivotTable_iMeasureFld_literal, context()->serialize(t()->iMeasureFld.get()));
			if (t()->name.present())
				w.attribute(0, sml_pivotTable_name_literal, context()->serialize(t()->name.get()));
			if (t()->description.present())
				w.attribute(0, sml_pivotTable_description_literal, context()->serialize(t()->description.get()));
			if (t()->stringValue1.present())
				w.attribute(0, sml_pivotTable_stringValue1_literal, context()->serialize(t()->stringValue1.get()));
			if (t()->stringValue2.present())
				w.attribute(0, sml_pivotTable_stringValue2_literal, context()->serialize(t()->stringValue2.get()));
			w.start_element(0, sml_pivotTable_autoFilter_literal);
			_autoFilter_writer.get_writer(context(), &t()->autoFilter)->write_target_to(w);
			w.end_element(0, sml_pivotTable_autoFilter_literal);
			if (t()->extLst.present()) {
				w.start_element(0, sml_pivotTable_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_extLst_literal);
			}
		}

		void CT_PivotFilters_writer::write_target_to(xml_writer& w) {
			if (t()->count != 0U)
				w.attribute(0, sml_pivotTable_count_literal, context()->serialize(t()->count));
			for (size_t sqi = 0; sqi<t()->filter.size(); ++sqi) {
				w.start_element(0, sml_pivotTable_filter_literal);
				_filter_writer.get_writer(context(), &t()->filter[sqi])->write_target_to(w);
				w.end_element(0, sml_pivotTable_filter_literal);
			}
		}

		void CT_HierarchyUsage_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_pivotTable_hierarchyUsage_literal, context()->serialize(t()->hierarchyUsage));
		}

		void CT_RowHierarchiesUsage_writer::write_target_to(xml_writer& w) {
			if (t()->count.present())
				w.attribute(0, sml_pivotTable_count_literal, context()->serialize(t()->count.get()));
			for (size_t sqi = 0; sqi<t()->rowHierarchyUsage.size(); ++sqi) {
				w.start_element(0, sml_pivotTable_rowHierarchyUsage_literal);
				_rowHierarchyUsage_writer.get_writer(context(), &t()->rowHierarchyUsage[sqi])->write_target_to(w);
				w.end_element(0, sml_pivotTable_rowHierarchyUsage_literal);
			}
		}

		void CT_ColHierarchiesUsage_writer::write_target_to(xml_writer& w) {
			if (t()->count.present())
				w.attribute(0, sml_pivotTable_count_literal, context()->serialize(t()->count.get()));
			for (size_t sqi = 0; sqi<t()->colHierarchyUsage.size(); ++sqi) {
				w.start_element(0, sml_pivotTable_colHierarchyUsage_literal);
				_colHierarchyUsage_writer.get_writer(context(), &t()->colHierarchyUsage[sqi])->write_target_to(w);
				w.end_element(0, sml_pivotTable_colHierarchyUsage_literal);
			}
		}

		void CT_pivotTableDefinition_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_pivotTable_name_literal, context()->serialize(t()->name));
			w.attribute(0, sml_pivotTable_cacheId_literal, context()->serialize(t()->cacheId));
			if (t()->dataOnRows != false)
				w.attribute(0, sml_pivotTable_dataOnRows_literal, context()->serialize(t()->dataOnRows));
			if (t()->dataPosition.present())
				w.attribute(0, sml_pivotTable_dataPosition_literal, context()->serialize(t()->dataPosition.get()));
			if (t()->autoFormatId.present())
				w.attribute(0, sml_pivotTable_autoFormatId_literal, context()->serialize(t()->autoFormatId.get()));
			if (t()->applyNumberFormats.present())
				w.attribute(0, sml_pivotTable_applyNumberFormats_literal, context()->serialize(t()->applyNumberFormats.get()));
			if (t()->applyBorderFormats.present())
				w.attribute(0, sml_pivotTable_applyBorderFormats_literal, context()->serialize(t()->applyBorderFormats.get()));
			if (t()->applyFontFormats.present())
				w.attribute(0, sml_pivotTable_applyFontFormats_literal, context()->serialize(t()->applyFontFormats.get()));
			if (t()->applyPatternFormats.present())
				w.attribute(0, sml_pivotTable_applyPatternFormats_literal, context()->serialize(t()->applyPatternFormats.get()));
			if (t()->applyAlignmentFormats.present())
				w.attribute(0, sml_pivotTable_applyAlignmentFormats_literal, context()->serialize(t()->applyAlignmentFormats.get()));
			if (t()->applyWidthHeightFormats.present())
				w.attribute(0, sml_pivotTable_applyWidthHeightFormats_literal, context()->serialize(t()->applyWidthHeightFormats.get()));
			w.attribute(0, sml_pivotTable_dataCaption_literal, context()->serialize(t()->dataCaption));
			if (t()->grandTotalCaption.present())
				w.attribute(0, sml_pivotTable_grandTotalCaption_literal, context()->serialize(t()->grandTotalCaption.get()));
			if (t()->errorCaption.present())
				w.attribute(0, sml_pivotTable_errorCaption_literal, context()->serialize(t()->errorCaption.get()));
			if (t()->showError != false)
				w.attribute(0, sml_pivotTable_showError_literal, context()->serialize(t()->showError));
			if (t()->missingCaption.present())
				w.attribute(0, sml_pivotTable_missingCaption_literal, context()->serialize(t()->missingCaption.get()));
			if (t()->showMissing != true)
				w.attribute(0, sml_pivotTable_showMissing_literal, context()->serialize(t()->showMissing));
			if (t()->pageStyle.present())
				w.attribute(0, sml_pivotTable_pageStyle_literal, context()->serialize(t()->pageStyle.get()));
			if (t()->pivotTableStyle.present())
				w.attribute(0, sml_pivotTable_pivotTableStyle_literal, context()->serialize(t()->pivotTableStyle.get()));
			if (t()->vacatedStyle.present())
				w.attribute(0, sml_pivotTable_vacatedStyle_literal, context()->serialize(t()->vacatedStyle.get()));
			if (t()->tag.present())
				w.attribute(0, sml_pivotTable_tag_literal, context()->serialize(t()->tag.get()));
			if (t()->updatedVersion != 0)
				w.attribute(0, sml_pivotTable_updatedVersion_literal, context()->serialize(t()->updatedVersion));
			if (t()->minRefreshableVersion != 0)
				w.attribute(0, sml_pivotTable_minRefreshableVersion_literal, context()->serialize(t()->minRefreshableVersion));
			if (t()->asteriskTotals != false)
				w.attribute(0, sml_pivotTable_asteriskTotals_literal, context()->serialize(t()->asteriskTotals));
			if (t()->showItems != true)
				w.attribute(0, sml_pivotTable_showItems_literal, context()->serialize(t()->showItems));
			if (t()->editData != false)
				w.attribute(0, sml_pivotTable_editData_literal, context()->serialize(t()->editData));
			if (t()->disableFieldList != false)
				w.attribute(0, sml_pivotTable_disableFieldList_literal, context()->serialize(t()->disableFieldList));
			if (t()->showCalcMbrs != true)
				w.attribute(0, sml_pivotTable_showCalcMbrs_literal, context()->serialize(t()->showCalcMbrs));
			if (t()->visualTotals != true)
				w.attribute(0, sml_pivotTable_visualTotals_literal, context()->serialize(t()->visualTotals));
			if (t()->showMultipleLabel != true)
				w.attribute(0, sml_pivotTable_showMultipleLabel_literal, context()->serialize(t()->showMultipleLabel));
			if (t()->showDataDropDown != true)
				w.attribute(0, sml_pivotTable_showDataDropDown_literal, context()->serialize(t()->showDataDropDown));
			if (t()->showDrill != true)
				w.attribute(0, sml_pivotTable_showDrill_literal, context()->serialize(t()->showDrill));
			if (t()->printDrill != false)
				w.attribute(0, sml_pivotTable_printDrill_literal, context()->serialize(t()->printDrill));
			if (t()->showMemberPropertyTips != true)
				w.attribute(0, sml_pivotTable_showMemberPropertyTips_literal, context()->serialize(t()->showMemberPropertyTips));
			if (t()->showDataTips != true)
				w.attribute(0, sml_pivotTable_showDataTips_literal, context()->serialize(t()->showDataTips));
			if (t()->enableWizard != true)
				w.attribute(0, sml_pivotTable_enableWizard_literal, context()->serialize(t()->enableWizard));
			if (t()->enableDrill != true)
				w.attribute(0, sml_pivotTable_enableDrill_literal, context()->serialize(t()->enableDrill));
			if (t()->enableFieldProperties != true)
				w.attribute(0, sml_pivotTable_enableFieldProperties_literal, context()->serialize(t()->enableFieldProperties));
			if (t()->preserveFormatting != true)
				w.attribute(0, sml_pivotTable_preserveFormatting_literal, context()->serialize(t()->preserveFormatting));
			if (t()->useAutoFormatting != false)
				w.attribute(0, sml_pivotTable_useAutoFormatting_literal, context()->serialize(t()->useAutoFormatting));
			if (t()->pageWrap != 0U)
				w.attribute(0, sml_pivotTable_pageWrap_literal, context()->serialize(t()->pageWrap));
			if (t()->pageOverThenDown != false)
				w.attribute(0, sml_pivotTable_pageOverThenDown_literal, context()->serialize(t()->pageOverThenDown));
			if (t()->subtotalHiddenItems != false)
				w.attribute(0, sml_pivotTable_subtotalHiddenItems_literal, context()->serialize(t()->subtotalHiddenItems));
			if (t()->rowGrandTotals != true)
				w.attribute(0, sml_pivotTable_rowGrandTotals_literal, context()->serialize(t()->rowGrandTotals));
			if (t()->colGrandTotals != true)
				w.attribute(0, sml_pivotTable_colGrandTotals_literal, context()->serialize(t()->colGrandTotals));
			if (t()->fieldPrintTitles != false)
				w.attribute(0, sml_pivotTable_fieldPrintTitles_literal, context()->serialize(t()->fieldPrintTitles));
			if (t()->itemPrintTitles != false)
				w.attribute(0, sml_pivotTable_itemPrintTitles_literal, context()->serialize(t()->itemPrintTitles));
			if (t()->mergeItem != false)
				w.attribute(0, sml_pivotTable_mergeItem_literal, context()->serialize(t()->mergeItem));
			if (t()->showDropZones != true)
				w.attribute(0, sml_pivotTable_showDropZones_literal, context()->serialize(t()->showDropZones));
			if (t()->createdVersion != 0)
				w.attribute(0, sml_pivotTable_createdVersion_literal, context()->serialize(t()->createdVersion));
			if (t()->indent != 1U)
				w.attribute(0, sml_pivotTable_indent_literal, context()->serialize(t()->indent));
			if (t()->showEmptyRow != false)
				w.attribute(0, sml_pivotTable_showEmptyRow_literal, context()->serialize(t()->showEmptyRow));
			if (t()->showEmptyCol != false)
				w.attribute(0, sml_pivotTable_showEmptyCol_literal, context()->serialize(t()->showEmptyCol));
			if (t()->showHeaders != true)
				w.attribute(0, sml_pivotTable_showHeaders_literal, context()->serialize(t()->showHeaders));
			if (t()->compact != true)
				w.attribute(0, sml_pivotTable_compact_literal, context()->serialize(t()->compact));
			if (t()->outline != false)
				w.attribute(0, sml_pivotTable_outline_literal, context()->serialize(t()->outline));
			if (t()->outlineData != false)
				w.attribute(0, sml_pivotTable_outlineData_literal, context()->serialize(t()->outlineData));
			if (t()->compactData != true)
				w.attribute(0, sml_pivotTable_compactData_literal, context()->serialize(t()->compactData));
			if (t()->published != false)
				w.attribute(0, sml_pivotTable_published_literal, context()->serialize(t()->published));
			if (t()->gridDropZones != false)
				w.attribute(0, sml_pivotTable_gridDropZones_literal, context()->serialize(t()->gridDropZones));
			if (t()->immersive != true)
				w.attribute(0, sml_pivotTable_immersive_literal, context()->serialize(t()->immersive));
			if (t()->multipleFieldFilters != true)
				w.attribute(0, sml_pivotTable_multipleFieldFilters_literal, context()->serialize(t()->multipleFieldFilters));
			if (t()->chartFormat != 0U)
				w.attribute(0, sml_pivotTable_chartFormat_literal, context()->serialize(t()->chartFormat));
			if (t()->rowHeaderCaption.present())
				w.attribute(0, sml_pivotTable_rowHeaderCaption_literal, context()->serialize(t()->rowHeaderCaption.get()));
			if (t()->colHeaderCaption.present())
				w.attribute(0, sml_pivotTable_colHeaderCaption_literal, context()->serialize(t()->colHeaderCaption.get()));
			if (t()->fieldListSortAscending != false)
				w.attribute(0, sml_pivotTable_fieldListSortAscending_literal, context()->serialize(t()->fieldListSortAscending));
			if (t()->mdxSubqueries != false)
				w.attribute(0, sml_pivotTable_mdxSubqueries_literal, context()->serialize(t()->mdxSubqueries));
			if (t()->customListSort != true)
				w.attribute(0, sml_pivotTable_customListSort_literal, context()->serialize(t()->customListSort));
			w.start_element(0, sml_pivotTable_location_literal);
			_location_writer.get_writer(context(), &t()->location)->write_target_to(w);
			w.end_element(0, sml_pivotTable_location_literal);
			if (t()->pivotFields.present()) {
				w.start_element(0, sml_pivotTable_pivotFields_literal);
				_pivotFields_writer.get_writer(context(), &t()->pivotFields.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_pivotFields_literal);
			}
			if (t()->rowFields.present()) {
				w.start_element(0, sml_pivotTable_rowFields_literal);
				_rowFields_writer.get_writer(context(), &t()->rowFields.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_rowFields_literal);
			}
			if (t()->rowItems.present()) {
				w.start_element(0, sml_pivotTable_rowItems_literal);
				_rowItems_writer.get_writer(context(), &t()->rowItems.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_rowItems_literal);
			}
			if (t()->colFields.present()) {
				w.start_element(0, sml_pivotTable_colFields_literal);
				_colFields_writer.get_writer(context(), &t()->colFields.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_colFields_literal);
			}
			if (t()->colItems.present()) {
				w.start_element(0, sml_pivotTable_colItems_literal);
				_colItems_writer.get_writer(context(), &t()->colItems.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_colItems_literal);
			}
			if (t()->pageFields.present()) {
				w.start_element(0, sml_pivotTable_pageFields_literal);
				_pageFields_writer.get_writer(context(), &t()->pageFields.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_pageFields_literal);
			}
			if (t()->dataFields.present()) {
				w.start_element(0, sml_pivotTable_dataFields_literal);
				_dataFields_writer.get_writer(context(), &t()->dataFields.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_dataFields_literal);
			}
			if (t()->formats.present()) {
				w.start_element(0, sml_pivotTable_formats_literal);
				_formats_writer.get_writer(context(), &t()->formats.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_formats_literal);
			}
			if (t()->conditionalFormats.present()) {
				w.start_element(0, sml_pivotTable_conditionalFormats_literal);
				_conditionalFormats_writer.get_writer(context(), &t()->conditionalFormats.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_conditionalFormats_literal);
			}
			if (t()->chartFormats.present()) {
				w.start_element(0, sml_pivotTable_chartFormats_literal);
				_chartFormats_writer.get_writer(context(), &t()->chartFormats.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_chartFormats_literal);
			}
			if (t()->pivotHierarchies.present()) {
				w.start_element(0, sml_pivotTable_pivotHierarchies_literal);
				_pivotHierarchies_writer.get_writer(context(), &t()->pivotHierarchies.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_pivotHierarchies_literal);
			}
			if (t()->pivotTableStyleInfo.present()) {
				w.start_element(0, sml_pivotTable_pivotTableStyleInfo_literal);
				_pivotTableStyleInfo_writer.get_writer(context(), &t()->pivotTableStyleInfo.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_pivotTableStyleInfo_literal);
			}
			if (t()->filters.present()) {
				w.start_element(0, sml_pivotTable_filters_literal);
				_filters_writer.get_writer(context(), &t()->filters.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_filters_literal);
			}
			if (t()->rowHierarchiesUsage.present()) {
				w.start_element(0, sml_pivotTable_rowHierarchiesUsage_literal);
				_rowHierarchiesUsage_writer.get_writer(context(), &t()->rowHierarchiesUsage.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_rowHierarchiesUsage_literal);
			}
			if (t()->colHierarchiesUsage.present()) {
				w.start_element(0, sml_pivotTable_colHierarchiesUsage_literal);
				_colHierarchiesUsage_writer.get_writer(context(), &t()->colHierarchiesUsage.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_colHierarchiesUsage_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, sml_pivotTable_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_extLst_literal);
			}
		}

		void sml_pivotTable_writer::write_target_to(xml_writer& w) {
			if (t()->pivotCacheDefinition.present()) {
				w.start_element(0, sml_pivotTable_pivotCacheDefinition_literal);
					w.attribute(0, sml_pivotTable_xmlns_literal, sml_pivotTable_http_colon__slash__slash_schemas_dot_openxmlformats_dot_org_slash_spreadsheetml_slash_2006_slash_main_literal);
					w.attribute(sml_pivotTable_xmlns_literal, sml_pivotTable_r_literal, sml_pivotTable_http_colon__slash__slash_schemas_dot_openxmlformats_dot_org_slash_officeDocument_slash_2006_slash_relationships_literal);
					w.attribute(sml_pivotTable_xmlns_literal, sml_pivotTable_xsd_literal, sml_pivotTable_http_colon__slash__slash_www_dot_w3_dot_org_slash_2001_slash_XMLSchema_literal);
				_pivotCacheDefinition_writer.get_writer(context(), &t()->pivotCacheDefinition.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_pivotCacheDefinition_literal);
			}
			if (t()->pivotCacheRecords.present()) {
				w.start_element(0, sml_pivotTable_pivotCacheRecords_literal);
					w.attribute(0, sml_pivotTable_xmlns_literal, sml_pivotTable_http_colon__slash__slash_schemas_dot_openxmlformats_dot_org_slash_spreadsheetml_slash_2006_slash_main_literal);
					w.attribute(sml_pivotTable_xmlns_literal, sml_pivotTable_r_literal, sml_pivotTable_http_colon__slash__slash_schemas_dot_openxmlformats_dot_org_slash_officeDocument_slash_2006_slash_relationships_literal);
					w.attribute(sml_pivotTable_xmlns_literal, sml_pivotTable_xsd_literal, sml_pivotTable_http_colon__slash__slash_www_dot_w3_dot_org_slash_2001_slash_XMLSchema_literal);
				_pivotCacheRecords_writer.get_writer(context(), &t()->pivotCacheRecords.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_pivotCacheRecords_literal);
			}
			if (t()->pivotTableDefinition.present()) {
				w.start_element(0, sml_pivotTable_pivotTableDefinition_literal);
					w.attribute(0, sml_pivotTable_xmlns_literal, sml_pivotTable_http_colon__slash__slash_schemas_dot_openxmlformats_dot_org_slash_spreadsheetml_slash_2006_slash_main_literal);
					w.attribute(sml_pivotTable_xmlns_literal, sml_pivotTable_r_literal, sml_pivotTable_http_colon__slash__slash_schemas_dot_openxmlformats_dot_org_slash_officeDocument_slash_2006_slash_relationships_literal);
					w.attribute(sml_pivotTable_xmlns_literal, sml_pivotTable_xsd_literal, sml_pivotTable_http_colon__slash__slash_www_dot_w3_dot_org_slash_2001_slash_XMLSchema_literal);
				_pivotTableDefinition_writer.get_writer(context(), &t()->pivotTableDefinition.get())->write_target_to(w);
				w.end_element(0, sml_pivotTable_pivotTableDefinition_literal);
			}
		}

	}
}
