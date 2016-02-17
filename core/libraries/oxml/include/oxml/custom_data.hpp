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

#ifndef CUSTOM_DATA_HPP
#define CUSTOM_DATA_HPP


#include <xio/optional.hpp>
#include <xio/xml/schema/types.hpp>
#include <xio/util/binary_search.hpp>

namespace spreadsheetml
{
	using namespace ::xio;
	using namespace ::xio::xml::schema;

	class CT_version;
	class CT_vt_array;
	class CT_vt_value;
	class CT_wse_property;
	class CT_wse_properties;
	class CT_bounded_point;
	class CT_named_formula;
	class CT_wse_id;
	class CT_wse_type;
	class CT_worksheet_element;
	class CT_worksheet_elements;
	class CT_attribute;
	class CT_attributes;
	class CT_cell_attribute;
	class CT_cell_attributes;
	class CT_variable;
	class CT_variables;
	class CT_extended_data;
	class custom_data;

	class CT_version
	{
	public:
		Short major;
		Short minor;
	};

	class CT_vt_array
	{
	public:
		std::vector< CT_vt_value > vt_value;
	};

	class CT_vt_value
	{
	public:
		optional< String > vt_empty;
		optional< Boolean > vt_bool;
		optional< Double > vt_number;
		optional< String > vt_string;
		optional< Short > vt_error;
		poptional< CT_vt_array > vt_array;
	};

	class CT_wse_property
	{
	public:
		CT_vt_value vt_value;
		optional< String > key;
	};

	class CT_wse_properties
	{
	public:
		std::vector< CT_wse_property > wse_property;
	};

	class CT_bounded_point
	{
	public:
		optional< Long > row;
		optional< Long > col;
	};

	class CT_named_formula
	{
	public:
		CT_vt_value vt_value;
		CT_bounded_point bounded_point;
		optional< String > name;
		optional< String > comment;
		optional< Boolean > scope;
		optional< String > wb_name;
		optional< String > ws_name;
	};

	class CT_wse_id
	{
	public:
		optional< String > value;
	};

	class CT_wse_type
	{
	public:
		optional< String > value;
	};

	class CT_worksheet_element
	{
	public:
		CT_worksheet_element() : wse_scope(false), wse_use_locale(false) {}
		CT_wse_properties wse_properties;
		poptional< CT_named_formula > wse_named_formula;
		poptional< CT_named_formula > wse_target_named_formula;
		poptional< CT_named_formula > wse_location_named_formula;
		CT_wse_id wse_id;
		CT_wse_type wse_type;
		Boolean wse_scope;
		Boolean wse_use_locale;
	};

	class CT_worksheet_elements
	{
	public:
		std::vector< CT_worksheet_element > worksheet_element;
	};

	class CT_attribute
	{
	public:
		optional< String > name;
		optional< String > value;
	};

	class CT_attributes
	{
	public:
		std::vector< CT_attribute > attribute;
	};

	class CT_cell_attribute
	{
	public:
		CT_attributes attributes;
		optional< UnsignedLong > row;
		optional< UnsignedLong > col;
	};

	class CT_cell_attributes
	{
	public:
		std::vector< CT_cell_attribute > cell_attribute;
	};

	class CT_variable
	{
	public:
		CT_vt_value value;
		optional< String > key;
	};

	class CT_variables
	{
	public:
		std::vector< CT_variable > variable;
	};

	class CT_extended_data
	{
	public:
		CT_version version;
		CT_worksheet_elements worksheet_elements;
		CT_cell_attributes cell_attributes;
		CT_variables variables;
	};

	class custom_data
	{
	public:
		poptional< CT_extended_data > extended_data;
	};

}
#endif

