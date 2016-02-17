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

#ifndef SHARED_DOCUMENTPROPERTIESCUSTOM_WRITERS_HPP
#define SHARED_DOCUMENTPROPERTIESCUSTOM_WRITERS_HPP

#include "shared-documentPropertiesCustom.hpp"
#include "shared-documentPropertiesCustom_literals.hpp"
#include "shared-documentPropertiesVariantTypes_writers.hpp"

namespace custom_properties
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_Property_writer;
		class CT_Properties_writer;
		class shared_documentPropertiesCustom_writer;

		class CT_Property_writer : public type_writer
		{
			auto_type_writer< ::docPropsVTypes::xio::CT_Vector_writer > _vector_writer;
			auto_type_writer< ::docPropsVTypes::xio::CT_Array_writer > _array_writer;
			auto_type_writer< ::docPropsVTypes::xio::CT_Empty_writer > _empty_writer;
			auto_type_writer< ::docPropsVTypes::xio::CT_Null_writer > _null_writer;
			auto_type_writer< ::docPropsVTypes::xio::ST_Cy_writer > _cy_writer;
			auto_type_writer< ::docPropsVTypes::xio::ST_Error_writer > _error_writer;
			auto_type_writer< ::docPropsVTypes::xio::CT_Vstream_writer > _vstream_writer;
			auto_type_writer< ::docPropsVTypes::xio::ST_Clsid_writer > _clsid_writer;
			auto_type_writer< ::docPropsVTypes::xio::CT_Cf_writer > _cf_writer;
			CT_Property* t() { return static_cast<CT_Property*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Properties_writer : public type_writer
		{
			auto_type_writer< CT_Property_writer > _property_writer;
			CT_Properties* t() { return static_cast<CT_Properties*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class shared_documentPropertiesCustom_writer : public type_writer
		{
			auto_type_writer< CT_Properties_writer > _Properties_writer;
			shared_documentPropertiesCustom* t() { return static_cast<shared_documentPropertiesCustom*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

	}
}
#endif

