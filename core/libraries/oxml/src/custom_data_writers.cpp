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

#include "custom_data_writers.hpp"
#include "custom_data_literals.hpp"

namespace spreadsheetml
{
	namespace xio
	{
		void CT_version_writer::write_target_to(xml_writer& w) {
			w.start_element(0, custom_data_major_literal);
			w.write_element_value(context()->serialize(t()->major));
			w.end_element(0, custom_data_major_literal);
			w.start_element(0, custom_data_minor_literal);
			w.write_element_value(context()->serialize(t()->minor));
			w.end_element(0, custom_data_minor_literal);
		}

		void CT_vt_array_writer::write_target_to(xml_writer& w) {
			for (size_t sqi = 0; sqi<t()->vt_value.size(); ++sqi) {
				w.start_element(0, custom_data_vt_value_literal);
				_vt_value_writer.get_writer(context(), &t()->vt_value[sqi])->write_target_to(w);
				w.end_element(0, custom_data_vt_value_literal);
			}
		}

		void CT_vt_value_writer::write_target_to(xml_writer& w) {
			if (t()->vt_empty.present()) {
				w.start_element(0, custom_data_vt_empty_literal);
				w.write_element_value(context()->serialize(t()->vt_empty.get()));
				w.end_element(0, custom_data_vt_empty_literal);
			}
			if (t()->vt_bool.present()) {
				w.start_element(0, custom_data_vt_bool_literal);
				w.write_element_value(context()->serialize(t()->vt_bool.get()));
				w.end_element(0, custom_data_vt_bool_literal);
			}
			if (t()->vt_number.present()) {
				w.start_element(0, custom_data_vt_number_literal);
				w.write_element_value(context()->serialize(t()->vt_number.get()));
				w.end_element(0, custom_data_vt_number_literal);
			}
			if (t()->vt_string.present()) {
				w.start_element(0, custom_data_vt_string_literal);
				w.write_element_value(context()->serialize(t()->vt_string.get()));
				w.end_element(0, custom_data_vt_string_literal);
			}
			if (t()->vt_error.present()) {
				w.start_element(0, custom_data_vt_error_literal);
				w.write_element_value(context()->serialize(t()->vt_error.get()));
				w.end_element(0, custom_data_vt_error_literal);
			}
			if (t()->vt_array.present()) {
				w.start_element(0, custom_data_vt_array_literal);
				_vt_array_writer.get_writer(context(), &t()->vt_array.get())->write_target_to(w);
				w.end_element(0, custom_data_vt_array_literal);
			}
		}

		void CT_wse_property_writer::write_target_to(xml_writer& w) {
			if (t()->key.present())
				w.attribute(0, custom_data_key_literal, context()->serialize(t()->key.get()));
			w.start_element(0, custom_data_vt_value_literal);
			_vt_value_writer.get_writer(context(), &t()->vt_value)->write_target_to(w);
			w.end_element(0, custom_data_vt_value_literal);
		}

		void CT_wse_properties_writer::write_target_to(xml_writer& w) {
			for (size_t sqi = 0; sqi<t()->wse_property.size(); ++sqi) {
				w.start_element(0, custom_data_wse_property_literal);
				_wse_property_writer.get_writer(context(), &t()->wse_property[sqi])->write_target_to(w);
				w.end_element(0, custom_data_wse_property_literal);
			}
		}

		void CT_bounded_point_writer::write_target_to(xml_writer& w) {
			if (t()->row.present())
				w.attribute(0, custom_data_row_literal, context()->serialize(t()->row.get()));
			if (t()->col.present())
				w.attribute(0, custom_data_col_literal, context()->serialize(t()->col.get()));
		}

		void CT_named_formula_writer::write_target_to(xml_writer& w) {
			if (t()->name.present())
				w.attribute(0, custom_data_name_literal, context()->serialize(t()->name.get()));
			if (t()->comment.present())
				w.attribute(0, custom_data_comment_literal, context()->serialize(t()->comment.get()));
			if (t()->scope.present())
				w.attribute(0, custom_data_scope_literal, context()->serialize(t()->scope.get()));
			if (t()->wb_name.present())
				w.attribute(0, custom_data_wb_name_literal, context()->serialize(t()->wb_name.get()));
			if (t()->ws_name.present())
				w.attribute(0, custom_data_ws_name_literal, context()->serialize(t()->ws_name.get()));
			w.start_element(0, custom_data_vt_value_literal);
			_vt_value_writer.get_writer(context(), &t()->vt_value)->write_target_to(w);
			w.end_element(0, custom_data_vt_value_literal);
			w.start_element(0, custom_data_bounded_point_literal);
			_bounded_point_writer.get_writer(context(), &t()->bounded_point)->write_target_to(w);
			w.end_element(0, custom_data_bounded_point_literal);
		}

		void CT_wse_id_writer::write_target_to(xml_writer& w) {
			if (t()->value.present())
				w.attribute(0, custom_data_value_literal, context()->serialize(t()->value.get()));
		}

		void CT_wse_type_writer::write_target_to(xml_writer& w) {
			if (t()->value.present())
				w.attribute(0, custom_data_value_literal, context()->serialize(t()->value.get()));
		}

		void CT_worksheet_element_writer::write_target_to(xml_writer& w) {
			if (t()->wse_scope != false)
				w.attribute(0, custom_data_wse_scope_literal, context()->serialize(t()->wse_scope));
			if (t()->wse_use_locale != false)
				w.attribute(0, custom_data_wse_use_locale_literal, context()->serialize(t()->wse_use_locale));
			w.start_element(0, custom_data_wse_properties_literal);
			_wse_properties_writer.get_writer(context(), &t()->wse_properties)->write_target_to(w);
			w.end_element(0, custom_data_wse_properties_literal);
			if (t()->wse_named_formula.present()) {
				w.start_element(0, custom_data_wse_named_formula_literal);
				_wse_named_formula_writer.get_writer(context(), &t()->wse_named_formula.get())->write_target_to(w);
				w.end_element(0, custom_data_wse_named_formula_literal);
			}
			if (t()->wse_target_named_formula.present()) {
				w.start_element(0, custom_data_wse_target_named_formula_literal);
				_wse_target_named_formula_writer.get_writer(context(), &t()->wse_target_named_formula.get())->write_target_to(w);
				w.end_element(0, custom_data_wse_target_named_formula_literal);
			}
			if (t()->wse_location_named_formula.present()) {
				w.start_element(0, custom_data_wse_location_named_formula_literal);
				_wse_location_named_formula_writer.get_writer(context(), &t()->wse_location_named_formula.get())->write_target_to(w);
				w.end_element(0, custom_data_wse_location_named_formula_literal);
			}
			w.start_element(0, custom_data_wse_id_literal);
			_wse_id_writer.get_writer(context(), &t()->wse_id)->write_target_to(w);
			w.end_element(0, custom_data_wse_id_literal);
			w.start_element(0, custom_data_wse_type_literal);
			_wse_type_writer.get_writer(context(), &t()->wse_type)->write_target_to(w);
			w.end_element(0, custom_data_wse_type_literal);
		}

		void CT_worksheet_elements_writer::write_target_to(xml_writer& w) {
			for (size_t sqi = 0; sqi<t()->worksheet_element.size(); ++sqi) {
				w.start_element(0, custom_data_worksheet_element_literal);
				_worksheet_element_writer.get_writer(context(), &t()->worksheet_element[sqi])->write_target_to(w);
				w.end_element(0, custom_data_worksheet_element_literal);
			}
		}

		void CT_attribute_writer::write_target_to(xml_writer& w) {
			if (t()->name.present())
				w.attribute(0, custom_data_name_literal, context()->serialize(t()->name.get()));
			if (t()->value.present())
				w.attribute(0, custom_data_value_literal, context()->serialize(t()->value.get()));
		}

		void CT_attributes_writer::write_target_to(xml_writer& w) {
			for (size_t sqi = 0; sqi<t()->attribute.size(); ++sqi) {
				w.start_element(0, custom_data_attribute_literal);
				_attribute_writer.get_writer(context(), &t()->attribute[sqi])->write_target_to(w);
				w.end_element(0, custom_data_attribute_literal);
			}
		}

		void CT_cell_attribute_writer::write_target_to(xml_writer& w) {
			if (t()->row.present())
				w.attribute(0, custom_data_row_literal, context()->serialize(t()->row.get()));
			if (t()->col.present())
				w.attribute(0, custom_data_col_literal, context()->serialize(t()->col.get()));
			w.start_element(0, custom_data_attributes_literal);
			_attributes_writer.get_writer(context(), &t()->attributes)->write_target_to(w);
			w.end_element(0, custom_data_attributes_literal);
		}

		void CT_cell_attributes_writer::write_target_to(xml_writer& w) {
			for (size_t sqi = 0; sqi<t()->cell_attribute.size(); ++sqi) {
				w.start_element(0, custom_data_cell_attribute_literal);
				_cell_attribute_writer.get_writer(context(), &t()->cell_attribute[sqi])->write_target_to(w);
				w.end_element(0, custom_data_cell_attribute_literal);
			}
		}

		void CT_variable_writer::write_target_to(xml_writer& w) {
			if (t()->key.present())
				w.attribute(0, custom_data_key_literal, context()->serialize(t()->key.get()));
			w.start_element(0, custom_data_value_literal);
			_value_writer.get_writer(context(), &t()->value)->write_target_to(w);
			w.end_element(0, custom_data_value_literal);
		}

		void CT_variables_writer::write_target_to(xml_writer& w) {
			for (size_t sqi = 0; sqi<t()->variable.size(); ++sqi) {
				w.start_element(0, custom_data_variable_literal);
				_variable_writer.get_writer(context(), &t()->variable[sqi])->write_target_to(w);
				w.end_element(0, custom_data_variable_literal);
			}
		}

		void CT_extended_data_writer::write_target_to(xml_writer& w) {
			w.start_element(0, custom_data_version_literal);
			_version_writer.get_writer(context(), &t()->version)->write_target_to(w);
			w.end_element(0, custom_data_version_literal);
			w.start_element(0, custom_data_worksheet_elements_literal);
			_worksheet_elements_writer.get_writer(context(), &t()->worksheet_elements)->write_target_to(w);
			w.end_element(0, custom_data_worksheet_elements_literal);
			w.start_element(0, custom_data_cell_attributes_literal);
			_cell_attributes_writer.get_writer(context(), &t()->cell_attributes)->write_target_to(w);
			w.end_element(0, custom_data_cell_attributes_literal);
			w.start_element(0, custom_data_variables_literal);
			_variables_writer.get_writer(context(), &t()->variables)->write_target_to(w);
			w.end_element(0, custom_data_variables_literal);
		}

		void custom_data_writer::write_target_to(xml_writer& w) {
			if (t()->extended_data.present()) {
				w.start_element(0, custom_data_extended_data_literal);
					w.attribute(0, custom_data_xmlns_literal, custom_data_http_colon__slash__slash_schemas_dot_openxmlformats_dot_org_slash_spreadsheetml_slash_2006_slash_main_literal);
					w.attribute(custom_data_xmlns_literal, custom_data_xs_literal, custom_data_http_colon__slash__slash_www_dot_w3_dot_org_slash_2001_slash_XMLSchema_literal);
				_extended_data_writer.get_writer(context(), &t()->extended_data.get())->write_target_to(w);
				w.end_element(0, custom_data_extended_data_literal);
			}
		}

	}
}
