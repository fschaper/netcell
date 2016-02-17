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

#ifndef SHARED_DOCUMENTPROPERTIESCUSTOM_READERS_HPP
#define SHARED_DOCUMENTPROPERTIESCUSTOM_READERS_HPP

#include "shared-documentPropertiesCustom.hpp"
#include "shared-documentPropertiesVariantTypes_readers.hpp"

namespace custom_properties
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_Property_reader;
		class CT_Properties_reader;
		class shared_documentPropertiesCustom_reader;

		class CT_Property_reader : public type_reader
		{
			auto_type_reader< ::docPropsVTypes::xio::CT_Vector_reader > _vector_reader;
			auto_type_reader< ::docPropsVTypes::xio::CT_Array_reader > _array_reader;
			auto_type_reader< ::docPropsVTypes::xio::CT_Empty_reader > _empty_reader;
			auto_type_reader< ::docPropsVTypes::xio::CT_Null_reader > _null_reader;
			auto_type_reader< ::docPropsVTypes::xio::ST_Cy_reader > _cy_reader;
			auto_type_reader< ::docPropsVTypes::xio::ST_Error_reader > _error_reader;
			auto_type_reader< ::docPropsVTypes::xio::CT_Vstream_reader > _vstream_reader;
			auto_type_reader< ::docPropsVTypes::xio::ST_Clsid_reader > _clsid_reader;
			auto_type_reader< ::docPropsVTypes::xio::CT_Cf_reader > _cf_reader;
		protected:
			CT_Property* t() { return static_cast<CT_Property*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void end_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Properties_reader : public type_reader
		{
			auto_type_reader< CT_Property_reader > _property_reader;
		protected:
			CT_Properties* t() { return static_cast<CT_Properties*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class shared_documentPropertiesCustom_reader : public type_reader
		{
			auto_type_reader< CT_Properties_reader > _Properties_reader;
		protected:
			shared_documentPropertiesCustom* t() { return static_cast<shared_documentPropertiesCustom*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

	}
}
#endif

