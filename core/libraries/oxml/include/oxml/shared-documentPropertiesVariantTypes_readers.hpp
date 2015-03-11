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

#ifndef SHARED_DOCUMENTPROPERTIESVARIANTTYPES_READERS_HPP
#define SHARED_DOCUMENTPROPERTIESVARIANTTYPES_READERS_HPP

#include "shared-documentPropertiesVariantTypes.hpp"
#include <xio/xml/binding/type_reader.hpp>

namespace docPropsVTypes
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class ST_Error_reader;
		class ST_Cy_reader;
		class CT_Array_reader;
		class CT_Empty_reader;
		class CT_Null_reader;
		class ST_Clsid_reader;
		class CT_Vstream_reader;
		class ST_Format_reader;
		class CT_Cf_reader;
		class CT_Variant_reader;
		class CT_Vector_reader;
		class shared_documentPropertiesVariantTypes_reader;

		class ST_Error_reader : public type_reader
		{
		protected:
			ST_Error* t() { return static_cast<ST_Error*>(target()); }
			void read_value(const xstring& val);
		};

		class ST_Cy_reader : public type_reader
		{
		protected:
			ST_Cy* t() { return static_cast<ST_Cy*>(target()); }
			void read_value(const xstring& val);
		};

		class CT_Array_reader : public type_reader
		{
			auto_type_reader< CT_Variant_reader > _variant_reader;
			auto_type_reader< ST_Error_reader > _error_reader;
			auto_type_reader< ST_Cy_reader > _cy_reader;
		protected:
			CT_Array* t() { return static_cast<CT_Array*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void end_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Empty_reader : public type_reader
		{
		protected:
			CT_Empty* t() { return static_cast<CT_Empty*>(target()); }
		};

		class CT_Null_reader : public type_reader
		{
		protected:
			CT_Null* t() { return static_cast<CT_Null*>(target()); }
		};

		class ST_Clsid_reader : public type_reader
		{
		protected:
			ST_Clsid* t() { return static_cast<ST_Clsid*>(target()); }
			void read_value(const xstring& val);
		};

		class CT_Vstream_reader : public type_reader
		{
		protected:
			CT_Vstream* t() { return static_cast<CT_Vstream*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
			void read_value(const xstring& val);
		};

		class ST_Format_reader : public type_reader
		{
		protected:
			ST_Format* t() { return static_cast<ST_Format*>(target()); }
			void read_value(const xstring& val);
		};

		class CT_Cf_reader : public type_reader
		{
		protected:
			CT_Cf* t() { return static_cast<CT_Cf*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
			void read_value(const xstring& val);
		};

		class CT_Variant_reader : public type_reader
		{
			auto_type_reader< CT_Variant_reader > _variant_reader;
			auto_type_reader< CT_Vector_reader > _vector_reader;
			auto_type_reader< CT_Array_reader > _array_reader;
			auto_type_reader< CT_Empty_reader > _empty_reader;
			auto_type_reader< CT_Null_reader > _null_reader;
			auto_type_reader< ST_Cy_reader > _cy_reader;
			auto_type_reader< ST_Error_reader > _error_reader;
			auto_type_reader< CT_Vstream_reader > _vstream_reader;
			auto_type_reader< ST_Clsid_reader > _clsid_reader;
			auto_type_reader< CT_Cf_reader > _cf_reader;
		protected:
			CT_Variant* t() { return static_cast<CT_Variant*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void end_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname);
		};

		class CT_Vector_reader : public type_reader
		{
			auto_type_reader< CT_Variant_reader > _variant_reader;
			auto_type_reader< ST_Cy_reader > _cy_reader;
			auto_type_reader< ST_Error_reader > _error_reader;
			auto_type_reader< ST_Clsid_reader > _clsid_reader;
			auto_type_reader< CT_Cf_reader > _cf_reader;
		protected:
			CT_Vector* t() { return static_cast<CT_Vector*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void end_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class shared_documentPropertiesVariantTypes_reader : public type_reader
		{
			auto_type_reader< CT_Variant_reader > _variant_reader;
			auto_type_reader< CT_Vector_reader > _vector_reader;
			auto_type_reader< CT_Array_reader > _array_reader;
			auto_type_reader< CT_Empty_reader > _empty_reader;
			auto_type_reader< CT_Null_reader > _null_reader;
			auto_type_reader< ST_Cy_reader > _cy_reader;
			auto_type_reader< ST_Error_reader > _error_reader;
			auto_type_reader< CT_Vstream_reader > _vstream_reader;
			auto_type_reader< ST_Clsid_reader > _clsid_reader;
			auto_type_reader< CT_Cf_reader > _cf_reader;
		protected:
			shared_documentPropertiesVariantTypes* t() { return static_cast<shared_documentPropertiesVariantTypes*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void end_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname);
		};

	}
}
#endif

