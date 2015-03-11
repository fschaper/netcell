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


#include "sml-autoFilter_writers.hpp"
#include "sml-autoFilter_literals.hpp"

namespace spreadsheetml
{
	namespace xio
	{
		void CT_Filter_writer::write_target_to(xml_writer& w) {
			if (t()->val.present())
				w.attribute(0, sml_autoFilter_val_literal, context()->serialize(t()->val.get()));
		}

		void CT_DateGroupItem_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_autoFilter_year_literal, context()->serialize(t()->year));
			if (t()->month.present())
				w.attribute(0, sml_autoFilter_month_literal, context()->serialize(t()->month.get()));
			if (t()->day.present())
				w.attribute(0, sml_autoFilter_day_literal, context()->serialize(t()->day.get()));
			if (t()->hour.present())
				w.attribute(0, sml_autoFilter_hour_literal, context()->serialize(t()->hour.get()));
			if (t()->minute.present())
				w.attribute(0, sml_autoFilter_minute_literal, context()->serialize(t()->minute.get()));
			if (t()->second.present())
				w.attribute(0, sml_autoFilter_second_literal, context()->serialize(t()->second.get()));
			w.attribute(0, sml_autoFilter_dateTimeGrouping_literal, context()->serialize(t()->dateTimeGrouping));
		}

		void CT_Filters_writer::write_target_to(xml_writer& w) {
			if (t()->blank != false)
				w.attribute(0, sml_autoFilter_blank_literal, context()->serialize(t()->blank));
			if (t()->calendarType != ST_CalendarType::none_literal)
				w.attribute(0, sml_autoFilter_calendarType_literal, context()->serialize(t()->calendarType));
			for (size_t sqi = 0; sqi<t()->filter.size(); ++sqi) {
				w.start_element(0, sml_autoFilter_filter_literal);
				_filter_writer.get_writer(context(), &t()->filter[sqi])->write_target_to(w);
				w.end_element(0, sml_autoFilter_filter_literal);
			}
			for (size_t sqi = 0; sqi<t()->dateGroupItem.size(); ++sqi) {
				w.start_element(0, sml_autoFilter_dateGroupItem_literal);
				_dateGroupItem_writer.get_writer(context(), &t()->dateGroupItem[sqi])->write_target_to(w);
				w.end_element(0, sml_autoFilter_dateGroupItem_literal);
			}
		}

		void CT_Top10_writer::write_target_to(xml_writer& w) {
			if (t()->top != true)
				w.attribute(0, sml_autoFilter_top_literal, context()->serialize(t()->top));
			if (t()->percent != false)
				w.attribute(0, sml_autoFilter_percent_literal, context()->serialize(t()->percent));
			w.attribute(0, sml_autoFilter_val_literal, context()->serialize(t()->val));
			if (t()->filterVal.present())
				w.attribute(0, sml_autoFilter_filterVal_literal, context()->serialize(t()->filterVal.get()));
		}

		void CT_CustomFilter_writer::write_target_to(xml_writer& w) {
			if (t()->_operator_ != ST_FilterOperator::equal_literal)
				w.attribute(0, sml_autoFilter__operator__literal, context()->serialize(t()->_operator_));
			if (t()->val.present())
				w.attribute(0, sml_autoFilter_val_literal, context()->serialize(t()->val.get()));
		}

		void CT_CustomFilters_writer::write_target_to(xml_writer& w) {
			if (t()->_and_ != false)
				w.attribute(0, sml_autoFilter__and__literal, context()->serialize(t()->_and_));
			for (size_t sqi = 0; sqi<t()->customFilter.size(); ++sqi) {
				w.start_element(0, sml_autoFilter_customFilter_literal);
				_customFilter_writer.get_writer(context(), &t()->customFilter[sqi])->write_target_to(w);
				w.end_element(0, sml_autoFilter_customFilter_literal);
			}
		}

		void CT_DynamicFilter_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_autoFilter_type_literal, context()->serialize(t()->type));
			if (t()->val.present())
				w.attribute(0, sml_autoFilter_val_literal, context()->serialize(t()->val.get()));
			if (t()->maxVal.present())
				w.attribute(0, sml_autoFilter_maxVal_literal, context()->serialize(t()->maxVal.get()));
		}

		void CT_ColorFilter_writer::write_target_to(xml_writer& w) {
			if (t()->dxfId.present())
				w.attribute(0, sml_autoFilter_dxfId_literal, context()->serialize(t()->dxfId.get()));
			if (t()->cellColor != true)
				w.attribute(0, sml_autoFilter_cellColor_literal, context()->serialize(t()->cellColor));
		}

		void CT_IconFilter_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_autoFilter_iconSet_literal, context()->serialize(t()->iconSet));
			if (t()->iconId.present())
				w.attribute(0, sml_autoFilter_iconId_literal, context()->serialize(t()->iconId.get()));
		}

		void CT_FilterColumn_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_autoFilter_colId_literal, context()->serialize(t()->colId));
			if (t()->hiddenButton != false)
				w.attribute(0, sml_autoFilter_hiddenButton_literal, context()->serialize(t()->hiddenButton));
			if (t()->showButton != true)
				w.attribute(0, sml_autoFilter_showButton_literal, context()->serialize(t()->showButton));
			if (t()->filters.present()) {
				w.start_element(0, sml_autoFilter_filters_literal);
				_filters_writer.get_writer(context(), &t()->filters.get())->write_target_to(w);
				w.end_element(0, sml_autoFilter_filters_literal);
			}
			if (t()->top10.present()) {
				w.start_element(0, sml_autoFilter_top10_literal);
				_top10_writer.get_writer(context(), &t()->top10.get())->write_target_to(w);
				w.end_element(0, sml_autoFilter_top10_literal);
			}
			if (t()->customFilters.present()) {
				w.start_element(0, sml_autoFilter_customFilters_literal);
				_customFilters_writer.get_writer(context(), &t()->customFilters.get())->write_target_to(w);
				w.end_element(0, sml_autoFilter_customFilters_literal);
			}
			if (t()->dynamicFilter.present()) {
				w.start_element(0, sml_autoFilter_dynamicFilter_literal);
				_dynamicFilter_writer.get_writer(context(), &t()->dynamicFilter.get())->write_target_to(w);
				w.end_element(0, sml_autoFilter_dynamicFilter_literal);
			}
			if (t()->colorFilter.present()) {
				w.start_element(0, sml_autoFilter_colorFilter_literal);
				_colorFilter_writer.get_writer(context(), &t()->colorFilter.get())->write_target_to(w);
				w.end_element(0, sml_autoFilter_colorFilter_literal);
			}
			if (t()->iconFilter.present()) {
				w.start_element(0, sml_autoFilter_iconFilter_literal);
				_iconFilter_writer.get_writer(context(), &t()->iconFilter.get())->write_target_to(w);
				w.end_element(0, sml_autoFilter_iconFilter_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, sml_autoFilter_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_autoFilter_extLst_literal);
			}
		}

		void CT_SortCondition_writer::write_target_to(xml_writer& w) {
			if (t()->descending != false)
				w.attribute(0, sml_autoFilter_descending_literal, context()->serialize(t()->descending));
			if (t()->sortBy != ST_SortBy::value_literal)
				w.attribute(0, sml_autoFilter_sortBy_literal, context()->serialize(t()->sortBy));
			w.attribute(0, sml_autoFilter_ref_literal, context()->serialize(t()->ref));
			if (t()->customList.present())
				w.attribute(0, sml_autoFilter_customList_literal, context()->serialize(t()->customList.get()));
			if (t()->dxfId.present())
				w.attribute(0, sml_autoFilter_dxfId_literal, context()->serialize(t()->dxfId.get()));
			if (t()->iconSet != ST_IconSetType::_3Arrows__literal)
				w.attribute(0, sml_autoFilter_iconSet_literal, context()->serialize(t()->iconSet));
			if (t()->iconId.present())
				w.attribute(0, sml_autoFilter_iconId_literal, context()->serialize(t()->iconId.get()));
		}

		void CT_SortState_writer::write_target_to(xml_writer& w) {
			if (t()->columnSort != false)
				w.attribute(0, sml_autoFilter_columnSort_literal, context()->serialize(t()->columnSort));
			if (t()->caseSensitive != false)
				w.attribute(0, sml_autoFilter_caseSensitive_literal, context()->serialize(t()->caseSensitive));
			if (t()->sortMethod != ST_SortMethod::none_literal)
				w.attribute(0, sml_autoFilter_sortMethod_literal, context()->serialize(t()->sortMethod));
			w.attribute(0, sml_autoFilter_ref_literal, context()->serialize(t()->ref));
			for (size_t sqi = 0; sqi<t()->sortCondition.size(); ++sqi) {
				w.start_element(0, sml_autoFilter_sortCondition_literal);
				_sortCondition_writer.get_writer(context(), &t()->sortCondition[sqi])->write_target_to(w);
				w.end_element(0, sml_autoFilter_sortCondition_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, sml_autoFilter_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_autoFilter_extLst_literal);
			}
		}

		void CT_AutoFilter_writer::write_target_to(xml_writer& w) {
			if (t()->ref.present())
				w.attribute(0, sml_autoFilter_ref_literal, context()->serialize(t()->ref.get()));
			for (size_t sqi = 0; sqi<t()->filterColumn.size(); ++sqi) {
				w.start_element(0, sml_autoFilter_filterColumn_literal);
				_filterColumn_writer.get_writer(context(), &t()->filterColumn[sqi])->write_target_to(w);
				w.end_element(0, sml_autoFilter_filterColumn_literal);
			}
			if (t()->sortState.present()) {
				w.start_element(0, sml_autoFilter_sortState_literal);
				_sortState_writer.get_writer(context(), &t()->sortState.get())->write_target_to(w);
				w.end_element(0, sml_autoFilter_sortState_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, sml_autoFilter_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_autoFilter_extLst_literal);
			}
		}

	}
}
