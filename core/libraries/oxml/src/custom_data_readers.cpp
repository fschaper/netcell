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

#include "custom_data_readers.hpp"
#include "custom_data_literals.hpp"
#include <xio/xml/binding/driver.hpp>

namespace spreadsheetml
{
	namespace xio
	{
		void CT_version_reader::end_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname)
		{
			if (::xercesc::XMLString::equals(localname, custom_data_major_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->major);
				return;
			}
			if (::xercesc::XMLString::equals(localname, custom_data_minor_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->minor);
				return;
			}
		}
		void CT_vt_array_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, custom_data_vt_value_literal))
			{
				t()->vt_value.resize(t()->vt_value.size()+1);
				driver()->push(localname, _vt_value_reader.get_reader(&t()->vt_value.back()));
				return;
			}
		}
		void CT_vt_value_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, custom_data_vt_array_literal))
			{
				driver()->push(localname, _vt_array_reader.get_reader(&t()->vt_array.getset()));
				return;
			}
		}
		void CT_vt_value_reader::end_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname)
		{
			if (::xercesc::XMLString::equals(localname, custom_data_vt_empty_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->vt_empty.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, custom_data_vt_bool_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->vt_bool.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, custom_data_vt_number_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->vt_number.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, custom_data_vt_string_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->vt_string.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, custom_data_vt_error_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->vt_error.getset());
				return;
			}
		}
		void CT_wse_property_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, custom_data_vt_value_literal))
			{
				driver()->push(localname, _vt_value_reader.get_reader(&t()->vt_value));
				return;
			}
		}
		void CT_wse_property_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, custom_data_key_literal))
			{
				driver()->context()->parse(value, t()->key.getset());
				return;
			}
		}
		void CT_wse_properties_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, custom_data_wse_property_literal))
			{
				t()->wse_property.resize(t()->wse_property.size()+1);
				driver()->push(localname, _wse_property_reader.get_reader(&t()->wse_property.back()));
				return;
			}
		}
		void CT_bounded_point_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, custom_data_row_literal))
			{
				driver()->context()->parse(value, t()->row.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, custom_data_col_literal))
			{
				driver()->context()->parse(value, t()->col.getset());
				return;
			}
		}
		void CT_named_formula_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, custom_data_vt_value_literal))
			{
				driver()->push(localname, _vt_value_reader.get_reader(&t()->vt_value));
				return;
			}
			if (::xercesc::XMLString::equals(localname, custom_data_bounded_point_literal))
			{
				driver()->push(localname, _bounded_point_reader.get_reader(&t()->bounded_point));
				return;
			}
		}
		void CT_named_formula_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, custom_data_name_literal))
			{
				driver()->context()->parse(value, t()->name.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, custom_data_comment_literal))
			{
				driver()->context()->parse(value, t()->comment.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, custom_data_scope_literal))
			{
				driver()->context()->parse(value, t()->scope.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, custom_data_wb_name_literal))
			{
				driver()->context()->parse(value, t()->wb_name.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, custom_data_ws_name_literal))
			{
				driver()->context()->parse(value, t()->ws_name.getset());
				return;
			}
		}
		void CT_wse_id_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, custom_data_value_literal))
			{
				driver()->context()->parse(value, t()->value.getset());
				return;
			}
		}
		void CT_wse_type_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, custom_data_value_literal))
			{
				driver()->context()->parse(value, t()->value.getset());
				return;
			}
		}
		void CT_worksheet_element_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, custom_data_wse_properties_literal))
			{
				driver()->push(localname, _wse_properties_reader.get_reader(&t()->wse_properties));
				return;
			}
			if (::xercesc::XMLString::equals(localname, custom_data_wse_named_formula_literal))
			{
				driver()->push(localname, _wse_named_formula_reader.get_reader(&t()->wse_named_formula.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, custom_data_wse_target_named_formula_literal))
			{
				driver()->push(localname, _wse_target_named_formula_reader.get_reader(&t()->wse_target_named_formula.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, custom_data_wse_location_named_formula_literal))
			{
				driver()->push(localname, _wse_location_named_formula_reader.get_reader(&t()->wse_location_named_formula.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, custom_data_wse_id_literal))
			{
				driver()->push(localname, _wse_id_reader.get_reader(&t()->wse_id));
				return;
			}
			if (::xercesc::XMLString::equals(localname, custom_data_wse_type_literal))
			{
				driver()->push(localname, _wse_type_reader.get_reader(&t()->wse_type));
				return;
			}
		}
		void CT_worksheet_element_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, custom_data_wse_scope_literal))
			{
				driver()->context()->parse(value, t()->wse_scope);
				return;
			}
			if (::xercesc::XMLString::equals(localname, custom_data_wse_use_locale_literal))
			{
				driver()->context()->parse(value, t()->wse_use_locale);
				return;
			}
		}
		void CT_worksheet_elements_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, custom_data_worksheet_element_literal))
			{
				t()->worksheet_element.resize(t()->worksheet_element.size()+1);
				driver()->push(localname, _worksheet_element_reader.get_reader(&t()->worksheet_element.back()));
				return;
			}
		}
		void CT_attribute_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, custom_data_name_literal))
			{
				driver()->context()->parse(value, t()->name.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, custom_data_value_literal))
			{
				driver()->context()->parse(value, t()->value.getset());
				return;
			}
		}
		void CT_attributes_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, custom_data_attribute_literal))
			{
				t()->attribute.resize(t()->attribute.size()+1);
				driver()->push(localname, _attribute_reader.get_reader(&t()->attribute.back()));
				return;
			}
		}
		void CT_cell_attribute_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, custom_data_attributes_literal))
			{
				driver()->push(localname, _attributes_reader.get_reader(&t()->attributes));
				return;
			}
		}
		void CT_cell_attribute_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, custom_data_row_literal))
			{
				driver()->context()->parse(value, t()->row.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, custom_data_col_literal))
			{
				driver()->context()->parse(value, t()->col.getset());
				return;
			}
		}
		void CT_cell_attributes_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, custom_data_cell_attribute_literal))
			{
				t()->cell_attribute.resize(t()->cell_attribute.size()+1);
				driver()->push(localname, _cell_attribute_reader.get_reader(&t()->cell_attribute.back()));
				return;
			}
		}
		void CT_variable_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, custom_data_value_literal))
			{
				driver()->push(localname, _value_reader.get_reader(&t()->value));
				return;
			}
		}
		void CT_variable_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, custom_data_key_literal))
			{
				driver()->context()->parse(value, t()->key.getset());
				return;
			}
		}
		void CT_variables_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, custom_data_variable_literal))
			{
				t()->variable.resize(t()->variable.size()+1);
				driver()->push(localname, _variable_reader.get_reader(&t()->variable.back()));
				return;
			}
		}
		void CT_extended_data_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, custom_data_version_literal))
			{
				driver()->push(localname, _version_reader.get_reader(&t()->version));
				return;
			}
			if (::xercesc::XMLString::equals(localname, custom_data_worksheet_elements_literal))
			{
				driver()->push(localname, _worksheet_elements_reader.get_reader(&t()->worksheet_elements));
				return;
			}
			if (::xercesc::XMLString::equals(localname, custom_data_cell_attributes_literal))
			{
				driver()->push(localname, _cell_attributes_reader.get_reader(&t()->cell_attributes));
				return;
			}
			if (::xercesc::XMLString::equals(localname, custom_data_variables_literal))
			{
				driver()->push(localname, _variables_reader.get_reader(&t()->variables));
				return;
			}
		}
		void custom_data_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, custom_data_extended_data_literal))
			{
				driver()->push(localname, _extended_data_reader.get_reader(&t()->extended_data.getset()));
				return;
			}
		}
	}
}
