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


#include "sml-pivotTableShared_writers.hpp"
#include "sml-pivotTableShared_literals.hpp"

namespace spreadsheetml
{
	namespace xio
	{
		void CT_Index_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_pivotTableShared_v_literal, context()->serialize(t()->v));
		}

		void CT_PivotAreaReference_writer::write_target_to(xml_writer& w) {
			if (t()->field.present())
				w.attribute(0, sml_pivotTableShared_field_literal, context()->serialize(t()->field.get()));
			if (t()->count.present())
				w.attribute(0, sml_pivotTableShared_count_literal, context()->serialize(t()->count.get()));
			if (t()->selected != true)
				w.attribute(0, sml_pivotTableShared_selected_literal, context()->serialize(t()->selected));
			if (t()->byPosition != false)
				w.attribute(0, sml_pivotTableShared_byPosition_literal, context()->serialize(t()->byPosition));
			if (t()->relative != false)
				w.attribute(0, sml_pivotTableShared_relative_literal, context()->serialize(t()->relative));
			if (t()->defaultSubtotal != false)
				w.attribute(0, sml_pivotTableShared_defaultSubtotal_literal, context()->serialize(t()->defaultSubtotal));
			if (t()->sumSubtotal != false)
				w.attribute(0, sml_pivotTableShared_sumSubtotal_literal, context()->serialize(t()->sumSubtotal));
			if (t()->countASubtotal != false)
				w.attribute(0, sml_pivotTableShared_countASubtotal_literal, context()->serialize(t()->countASubtotal));
			if (t()->avgSubtotal != false)
				w.attribute(0, sml_pivotTableShared_avgSubtotal_literal, context()->serialize(t()->avgSubtotal));
			if (t()->maxSubtotal != false)
				w.attribute(0, sml_pivotTableShared_maxSubtotal_literal, context()->serialize(t()->maxSubtotal));
			if (t()->minSubtotal != false)
				w.attribute(0, sml_pivotTableShared_minSubtotal_literal, context()->serialize(t()->minSubtotal));
			if (t()->productSubtotal != false)
				w.attribute(0, sml_pivotTableShared_productSubtotal_literal, context()->serialize(t()->productSubtotal));
			if (t()->countSubtotal != false)
				w.attribute(0, sml_pivotTableShared_countSubtotal_literal, context()->serialize(t()->countSubtotal));
			if (t()->stdDevSubtotal != false)
				w.attribute(0, sml_pivotTableShared_stdDevSubtotal_literal, context()->serialize(t()->stdDevSubtotal));
			if (t()->stdDevPSubtotal != false)
				w.attribute(0, sml_pivotTableShared_stdDevPSubtotal_literal, context()->serialize(t()->stdDevPSubtotal));
			if (t()->varSubtotal != false)
				w.attribute(0, sml_pivotTableShared_varSubtotal_literal, context()->serialize(t()->varSubtotal));
			if (t()->varPSubtotal != false)
				w.attribute(0, sml_pivotTableShared_varPSubtotal_literal, context()->serialize(t()->varPSubtotal));
			for (size_t sqi = 0; sqi<t()->x.size(); ++sqi) {
				w.start_element(0, sml_pivotTableShared_x_literal);
				_x_writer.get_writer(context(), &t()->x[sqi])->write_target_to(w);
				w.end_element(0, sml_pivotTableShared_x_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, sml_pivotTableShared_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_pivotTableShared_extLst_literal);
			}
		}

		void CT_PivotAreaReferences_writer::write_target_to(xml_writer& w) {
			if (t()->count.present())
				w.attribute(0, sml_pivotTableShared_count_literal, context()->serialize(t()->count.get()));
			for (size_t sqi = 0; sqi<t()->reference.size(); ++sqi) {
				w.start_element(0, sml_pivotTableShared_reference_literal);
				_reference_writer.get_writer(context(), &t()->reference[sqi])->write_target_to(w);
				w.end_element(0, sml_pivotTableShared_reference_literal);
			}
		}

		void CT_PivotArea_writer::write_target_to(xml_writer& w) {
			if (t()->field.present())
				w.attribute(0, sml_pivotTableShared_field_literal, context()->serialize(t()->field.get()));
			if (t()->type != ST_PivotAreaType::normal_literal)
				w.attribute(0, sml_pivotTableShared_type_literal, context()->serialize(t()->type));
			if (t()->dataOnly != true)
				w.attribute(0, sml_pivotTableShared_dataOnly_literal, context()->serialize(t()->dataOnly));
			if (t()->labelOnly != false)
				w.attribute(0, sml_pivotTableShared_labelOnly_literal, context()->serialize(t()->labelOnly));
			if (t()->grandRow != false)
				w.attribute(0, sml_pivotTableShared_grandRow_literal, context()->serialize(t()->grandRow));
			if (t()->grandCol != false)
				w.attribute(0, sml_pivotTableShared_grandCol_literal, context()->serialize(t()->grandCol));
			if (t()->cacheIndex != false)
				w.attribute(0, sml_pivotTableShared_cacheIndex_literal, context()->serialize(t()->cacheIndex));
			if (t()->outline != true)
				w.attribute(0, sml_pivotTableShared_outline_literal, context()->serialize(t()->outline));
			if (t()->offset.present())
				w.attribute(0, sml_pivotTableShared_offset_literal, context()->serialize(t()->offset.get()));
			if (t()->collapsedLevelsAreSubtotals != false)
				w.attribute(0, sml_pivotTableShared_collapsedLevelsAreSubtotals_literal, context()->serialize(t()->collapsedLevelsAreSubtotals));
			if (t()->axis.present())
				w.attribute(0, sml_pivotTableShared_axis_literal, context()->serialize(t()->axis.get()));
			if (t()->fieldPosition.present())
				w.attribute(0, sml_pivotTableShared_fieldPosition_literal, context()->serialize(t()->fieldPosition.get()));
			if (t()->references.present()) {
				w.start_element(0, sml_pivotTableShared_references_literal);
				_references_writer.get_writer(context(), &t()->references.get())->write_target_to(w);
				w.end_element(0, sml_pivotTableShared_references_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, sml_pivotTableShared_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_pivotTableShared_extLst_literal);
			}
		}

	}
}
