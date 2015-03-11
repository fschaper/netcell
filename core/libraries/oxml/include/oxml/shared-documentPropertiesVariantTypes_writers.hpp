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

#ifndef SHARED_DOCUMENTPROPERTIESVARIANTTYPES_WRITERS_HPP
#define SHARED_DOCUMENTPROPERTIESVARIANTTYPES_WRITERS_HPP

#include "shared-documentPropertiesVariantTypes.hpp"
#include "shared-documentPropertiesVariantTypes_literals.hpp"
#include <xio/xml/binding/type_writer.hpp>

namespace docPropsVTypes
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class ST_Error_writer;
		class ST_Cy_writer;
		class CT_Array_writer;
		class CT_Empty_writer;
		class CT_Null_writer;
		class ST_Clsid_writer;
		class CT_Vstream_writer;
		class ST_Format_writer;
		class CT_Cf_writer;
		class CT_Variant_writer;
		class CT_Vector_writer;
		class shared_documentPropertiesVariantTypes_writer;

		class ST_Error_writer : public type_writer
		{
			ST_Error* t() { return static_cast<ST_Error*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class ST_Cy_writer : public type_writer
		{
			ST_Cy* t() { return static_cast<ST_Cy*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Array_writer : public type_writer
		{
			auto_type_writer< CT_Variant_writer > _variant_writer;
			auto_type_writer< ST_Error_writer > _error_writer;
			auto_type_writer< ST_Cy_writer > _cy_writer;
			CT_Array* t() { return static_cast<CT_Array*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Empty_writer : public type_writer
		{
			CT_Empty* t() { return static_cast<CT_Empty*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Null_writer : public type_writer
		{
			CT_Null* t() { return static_cast<CT_Null*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class ST_Clsid_writer : public type_writer
		{
			ST_Clsid* t() { return static_cast<ST_Clsid*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Vstream_writer : public type_writer
		{
			CT_Vstream* t() { return static_cast<CT_Vstream*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class ST_Format_writer : public type_writer
		{
			ST_Format* t() { return static_cast<ST_Format*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Cf_writer : public type_writer
		{
			CT_Cf* t() { return static_cast<CT_Cf*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Variant_writer : public type_writer
		{
			auto_type_writer< CT_Variant_writer > _variant_writer;
			auto_type_writer< CT_Vector_writer > _vector_writer;
			auto_type_writer< CT_Array_writer > _array_writer;
			auto_type_writer< CT_Empty_writer > _empty_writer;
			auto_type_writer< CT_Null_writer > _null_writer;
			auto_type_writer< ST_Cy_writer > _cy_writer;
			auto_type_writer< ST_Error_writer > _error_writer;
			auto_type_writer< CT_Vstream_writer > _vstream_writer;
			auto_type_writer< ST_Clsid_writer > _clsid_writer;
			auto_type_writer< CT_Cf_writer > _cf_writer;
			CT_Variant* t() { return static_cast<CT_Variant*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Vector_writer : public type_writer
		{
			auto_type_writer< CT_Variant_writer > _variant_writer;
			auto_type_writer< ST_Cy_writer > _cy_writer;
			auto_type_writer< ST_Error_writer > _error_writer;
			auto_type_writer< ST_Clsid_writer > _clsid_writer;
			auto_type_writer< CT_Cf_writer > _cf_writer;
			CT_Vector* t() { return static_cast<CT_Vector*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class shared_documentPropertiesVariantTypes_writer : public type_writer
		{
			auto_type_writer< CT_Variant_writer > _variant_writer;
			auto_type_writer< CT_Vector_writer > _vector_writer;
			auto_type_writer< CT_Array_writer > _array_writer;
			auto_type_writer< CT_Empty_writer > _empty_writer;
			auto_type_writer< CT_Null_writer > _null_writer;
			auto_type_writer< ST_Cy_writer > _cy_writer;
			auto_type_writer< ST_Error_writer > _error_writer;
			auto_type_writer< CT_Vstream_writer > _vstream_writer;
			auto_type_writer< ST_Clsid_writer > _clsid_writer;
			auto_type_writer< CT_Cf_writer > _cf_writer;
			shared_documentPropertiesVariantTypes* t() { return static_cast<shared_documentPropertiesVariantTypes*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

	}
}
#endif

