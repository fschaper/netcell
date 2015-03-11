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

#ifndef CUSTOM_DATA_READERS_HPP
#define CUSTOM_DATA_READERS_HPP

#include "custom_data.hpp"
#include <xio/xml/binding/type_reader.hpp>

namespace spreadsheetml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_version_reader;
		class CT_vt_array_reader;
		class CT_vt_value_reader;
		class CT_wse_property_reader;
		class CT_wse_properties_reader;
		class CT_bounded_point_reader;
		class CT_named_formula_reader;
		class CT_wse_id_reader;
		class CT_wse_type_reader;
		class CT_worksheet_element_reader;
		class CT_worksheet_elements_reader;
		class CT_attribute_reader;
		class CT_attributes_reader;
		class CT_cell_attribute_reader;
		class CT_cell_attributes_reader;
		class CT_variable_reader;
		class CT_variables_reader;
		class CT_extended_data_reader;
		class custom_data_reader;

		class CT_version_reader : public type_reader
		{
		protected:
			CT_version* t() { return static_cast<CT_version*>(target()); }
			void end_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname);
		};

		class CT_vt_array_reader : public type_reader
		{
			auto_type_reader< CT_vt_value_reader > _vt_value_reader;
		protected:
			CT_vt_array* t() { return static_cast<CT_vt_array*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_vt_value_reader : public type_reader
		{
			auto_type_reader< CT_vt_array_reader > _vt_array_reader;
		protected:
			CT_vt_value* t() { return static_cast<CT_vt_value*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void end_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname);
		};

		class CT_wse_property_reader : public type_reader
		{
			auto_type_reader< CT_vt_value_reader > _vt_value_reader;
		protected:
			CT_wse_property* t() { return static_cast<CT_wse_property*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_wse_properties_reader : public type_reader
		{
			auto_type_reader< CT_wse_property_reader > _wse_property_reader;
		protected:
			CT_wse_properties* t() { return static_cast<CT_wse_properties*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_bounded_point_reader : public type_reader
		{
		protected:
			CT_bounded_point* t() { return static_cast<CT_bounded_point*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_named_formula_reader : public type_reader
		{
			auto_type_reader< CT_vt_value_reader > _vt_value_reader;
			auto_type_reader< CT_bounded_point_reader > _bounded_point_reader;
		protected:
			CT_named_formula* t() { return static_cast<CT_named_formula*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_wse_id_reader : public type_reader
		{
		protected:
			CT_wse_id* t() { return static_cast<CT_wse_id*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_wse_type_reader : public type_reader
		{
		protected:
			CT_wse_type* t() { return static_cast<CT_wse_type*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_worksheet_element_reader : public type_reader
		{
			auto_type_reader< CT_wse_properties_reader > _wse_properties_reader;
			auto_type_reader< CT_named_formula_reader > _wse_named_formula_reader;
			auto_type_reader< CT_named_formula_reader > _wse_target_named_formula_reader;
			auto_type_reader< CT_named_formula_reader > _wse_location_named_formula_reader;
			auto_type_reader< CT_wse_id_reader > _wse_id_reader;
			auto_type_reader< CT_wse_type_reader > _wse_type_reader;
		protected:
			CT_worksheet_element* t() { return static_cast<CT_worksheet_element*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_worksheet_elements_reader : public type_reader
		{
			auto_type_reader< CT_worksheet_element_reader > _worksheet_element_reader;
		protected:
			CT_worksheet_elements* t() { return static_cast<CT_worksheet_elements*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_attribute_reader : public type_reader
		{
		protected:
			CT_attribute* t() { return static_cast<CT_attribute*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_attributes_reader : public type_reader
		{
			auto_type_reader< CT_attribute_reader > _attribute_reader;
		protected:
			CT_attributes* t() { return static_cast<CT_attributes*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_cell_attribute_reader : public type_reader
		{
			auto_type_reader< CT_attributes_reader > _attributes_reader;
		protected:
			CT_cell_attribute* t() { return static_cast<CT_cell_attribute*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_cell_attributes_reader : public type_reader
		{
			auto_type_reader< CT_cell_attribute_reader > _cell_attribute_reader;
		protected:
			CT_cell_attributes* t() { return static_cast<CT_cell_attributes*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_variable_reader : public type_reader
		{
			auto_type_reader< CT_vt_value_reader > _value_reader;
		protected:
			CT_variable* t() { return static_cast<CT_variable*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_variables_reader : public type_reader
		{
			auto_type_reader< CT_variable_reader > _variable_reader;
		protected:
			CT_variables* t() { return static_cast<CT_variables*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_extended_data_reader : public type_reader
		{
			auto_type_reader< CT_version_reader > _version_reader;
			auto_type_reader< CT_worksheet_elements_reader > _worksheet_elements_reader;
			auto_type_reader< CT_cell_attributes_reader > _cell_attributes_reader;
			auto_type_reader< CT_variables_reader > _variables_reader;
		protected:
			CT_extended_data* t() { return static_cast<CT_extended_data*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class custom_data_reader : public type_reader
		{
			auto_type_reader< CT_extended_data_reader > _extended_data_reader;
		protected:
			custom_data* t() { return static_cast<custom_data*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

	}
}
#endif

