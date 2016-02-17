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

#ifndef CUSTOM_DATA_WRITERS_HPP
#define CUSTOM_DATA_WRITERS_HPP

#include "custom_data.hpp"
#include "custom_data_literals.hpp"
#include <xio/xml/binding/type_writer.hpp>

namespace spreadsheetml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_version_writer;
		class CT_vt_array_writer;
		class CT_vt_value_writer;
		class CT_wse_property_writer;
		class CT_wse_properties_writer;
		class CT_bounded_point_writer;
		class CT_named_formula_writer;
		class CT_wse_id_writer;
		class CT_wse_type_writer;
		class CT_worksheet_element_writer;
		class CT_worksheet_elements_writer;
		class CT_attribute_writer;
		class CT_attributes_writer;
		class CT_cell_attribute_writer;
		class CT_cell_attributes_writer;
		class CT_variable_writer;
		class CT_variables_writer;
		class CT_extended_data_writer;
		class custom_data_writer;

		class CT_version_writer : public type_writer
		{
			CT_version* t() { return static_cast<CT_version*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_vt_array_writer : public type_writer
		{
			auto_type_writer< CT_vt_value_writer > _vt_value_writer;
			CT_vt_array* t() { return static_cast<CT_vt_array*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_vt_value_writer : public type_writer
		{
			auto_type_writer< CT_vt_array_writer > _vt_array_writer;
			CT_vt_value* t() { return static_cast<CT_vt_value*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_wse_property_writer : public type_writer
		{
			auto_type_writer< CT_vt_value_writer > _vt_value_writer;
			CT_wse_property* t() { return static_cast<CT_wse_property*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_wse_properties_writer : public type_writer
		{
			auto_type_writer< CT_wse_property_writer > _wse_property_writer;
			CT_wse_properties* t() { return static_cast<CT_wse_properties*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_bounded_point_writer : public type_writer
		{
			CT_bounded_point* t() { return static_cast<CT_bounded_point*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_named_formula_writer : public type_writer
		{
			auto_type_writer< CT_vt_value_writer > _vt_value_writer;
			auto_type_writer< CT_bounded_point_writer > _bounded_point_writer;
			CT_named_formula* t() { return static_cast<CT_named_formula*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_wse_id_writer : public type_writer
		{
			CT_wse_id* t() { return static_cast<CT_wse_id*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_wse_type_writer : public type_writer
		{
			CT_wse_type* t() { return static_cast<CT_wse_type*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_worksheet_element_writer : public type_writer
		{
			auto_type_writer< CT_wse_properties_writer > _wse_properties_writer;
			auto_type_writer< CT_named_formula_writer > _wse_named_formula_writer;
			auto_type_writer< CT_named_formula_writer > _wse_target_named_formula_writer;
			auto_type_writer< CT_named_formula_writer > _wse_location_named_formula_writer;
			auto_type_writer< CT_wse_id_writer > _wse_id_writer;
			auto_type_writer< CT_wse_type_writer > _wse_type_writer;
			CT_worksheet_element* t() { return static_cast<CT_worksheet_element*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_worksheet_elements_writer : public type_writer
		{
			auto_type_writer< CT_worksheet_element_writer > _worksheet_element_writer;
			CT_worksheet_elements* t() { return static_cast<CT_worksheet_elements*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_attribute_writer : public type_writer
		{
			CT_attribute* t() { return static_cast<CT_attribute*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_attributes_writer : public type_writer
		{
			auto_type_writer< CT_attribute_writer > _attribute_writer;
			CT_attributes* t() { return static_cast<CT_attributes*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_cell_attribute_writer : public type_writer
		{
			auto_type_writer< CT_attributes_writer > _attributes_writer;
			CT_cell_attribute* t() { return static_cast<CT_cell_attribute*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_cell_attributes_writer : public type_writer
		{
			auto_type_writer< CT_cell_attribute_writer > _cell_attribute_writer;
			CT_cell_attributes* t() { return static_cast<CT_cell_attributes*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_variable_writer : public type_writer
		{
			auto_type_writer< CT_vt_value_writer > _value_writer;
			CT_variable* t() { return static_cast<CT_variable*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_variables_writer : public type_writer
		{
			auto_type_writer< CT_variable_writer > _variable_writer;
			CT_variables* t() { return static_cast<CT_variables*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_extended_data_writer : public type_writer
		{
			auto_type_writer< CT_version_writer > _version_writer;
			auto_type_writer< CT_worksheet_elements_writer > _worksheet_elements_writer;
			auto_type_writer< CT_cell_attributes_writer > _cell_attributes_writer;
			auto_type_writer< CT_variables_writer > _variables_writer;
			CT_extended_data* t() { return static_cast<CT_extended_data*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class custom_data_writer : public type_writer
		{
			auto_type_writer< CT_extended_data_writer > _extended_data_writer;
			custom_data* t() { return static_cast<custom_data*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

	}
}
#endif

