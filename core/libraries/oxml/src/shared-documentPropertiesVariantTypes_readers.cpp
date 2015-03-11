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


#include "shared-documentPropertiesVariantTypes_readers.hpp"
#include "shared-documentPropertiesVariantTypes_literals.hpp"
#include <xio/xml/binding/driver.hpp>

namespace docPropsVTypes
{
	namespace xio
	{
		void ST_Error_reader::read_value(const xstring& val) {{ driver()->context()->parse(val, *t()); }}
		void ST_Cy_reader::read_value(const xstring& val) {{ driver()->context()->parse(val, *t()); }}
		void CT_Array_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_variant_literal))
			{
				driver()->push(localname, _variant_reader.get_reader(&t()->variant.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_error_literal))
			{
				driver()->push(localname, _error_reader.get_reader(&t()->error.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_cy_literal))
			{
				driver()->push(localname, _cy_reader.get_reader(&t()->cy.getset()));
				return;
			}
		}
		void CT_Array_reader::end_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname)
		{
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_i1_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->i1.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_i2_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->i2.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_i4_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->i4.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes__int__literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->_int_.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_ui1_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->ui1.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_ui2_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->ui2.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_ui4_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->ui4.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_uint_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->uint.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_r4_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->r4.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_r8_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->r8.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_decimal_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->decimal.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_bstr_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->bstr.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_date_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->date.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes__bool__literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->_bool_.getset());
				return;
			}
		}
		void CT_Array_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_lBounds_literal))
			{
				driver()->context()->parse(value, t()->lBounds);
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_uBounds_literal))
			{
				driver()->context()->parse(value, t()->uBounds);
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_baseType_literal))
			{
				driver()->context()->parse(value, t()->baseType);
				return;
			}
		}
		void ST_Clsid_reader::read_value(const xstring& val) {{ driver()->context()->parse(val, *t()); }}
		void CT_Vstream_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_version_literal))
			{
				driver()->context()->parse(value, t()->version.getset());
				return;
			}
		}
		void CT_Vstream_reader::read_value(const xstring& val) {{ driver()->context()->parse(val, *t()); }}
		void ST_Format_reader::read_value(const xstring& val) {{ driver()->context()->parse(val, *t()); }}
		void CT_Cf_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_format_literal))
			{
				driver()->context()->parse(value, t()->format.getset());
				return;
			}
		}
		void CT_Cf_reader::read_value(const xstring& val) {{ driver()->context()->parse(val, *t()); }}
		void CT_Variant_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_variant_literal))
			{
				driver()->push(localname, _variant_reader.get_reader(&t()->variant.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_vector_literal))
			{
				driver()->push(localname, _vector_reader.get_reader(&t()->vector.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_array_literal))
			{
				driver()->push(localname, _array_reader.get_reader(&t()->array.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_empty_literal))
			{
				driver()->push(localname, _empty_reader.get_reader(&t()->empty.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_null_literal))
			{
				driver()->push(localname, _null_reader.get_reader(&t()->null.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_cy_literal))
			{
				driver()->push(localname, _cy_reader.get_reader(&t()->cy.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_error_literal))
			{
				driver()->push(localname, _error_reader.get_reader(&t()->error.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_vstream_literal))
			{
				driver()->push(localname, _vstream_reader.get_reader(&t()->vstream.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_clsid_literal))
			{
				driver()->push(localname, _clsid_reader.get_reader(&t()->clsid.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_cf_literal))
			{
				driver()->push(localname, _cf_reader.get_reader(&t()->cf.getset()));
				return;
			}
		}
		void CT_Variant_reader::end_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname)
		{
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_blob_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->blob.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_oblob_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->oblob.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_i1_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->i1.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_i2_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->i2.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_i4_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->i4.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_i8_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->i8.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes__int__literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->_int_.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_ui1_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->ui1.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_ui2_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->ui2.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_ui4_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->ui4.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_ui8_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->ui8.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_uint_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->uint.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_r4_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->r4.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_r8_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->r8.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_decimal_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->decimal.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_lpstr_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->lpstr.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_lpwstr_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->lpwstr.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_bstr_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->bstr.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_date_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->date.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_filetime_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->filetime.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes__bool__literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->_bool_.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_stream_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->stream.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_ostream_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->ostream.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_storage_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->storage.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_ostorage_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->ostorage.getset());
				return;
			}
		}
		void CT_Vector_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_variant_literal))
			{
				driver()->push(localname, _variant_reader.get_reader(&t()->variant.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_cy_literal))
			{
				driver()->push(localname, _cy_reader.get_reader(&t()->cy.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_error_literal))
			{
				driver()->push(localname, _error_reader.get_reader(&t()->error.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_clsid_literal))
			{
				driver()->push(localname, _clsid_reader.get_reader(&t()->clsid.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_cf_literal))
			{
				driver()->push(localname, _cf_reader.get_reader(&t()->cf.getset()));
				return;
			}
		}
		void CT_Vector_reader::end_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname)
		{
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_i1_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->i1.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_i2_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->i2.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_i4_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->i4.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_i8_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->i8.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_ui1_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->ui1.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_ui2_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->ui2.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_ui4_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->ui4.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_ui8_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->ui8.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_r4_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->r4.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_r8_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->r8.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_lpstr_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->lpstr.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_lpwstr_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->lpwstr.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_bstr_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->bstr.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_date_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->date.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_filetime_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->filetime.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes__bool__literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->_bool_.getset());
				return;
			}
		}
		void CT_Vector_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_baseType_literal))
			{
				driver()->context()->parse(value, t()->baseType);
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_size_literal))
			{
				driver()->context()->parse(value, t()->size);
				return;
			}
		}
		void shared_documentPropertiesVariantTypes_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_variant_literal))
			{
				driver()->push(localname, _variant_reader.get_reader(&t()->variant.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_vector_literal))
			{
				driver()->push(localname, _vector_reader.get_reader(&t()->vector.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_array_literal))
			{
				driver()->push(localname, _array_reader.get_reader(&t()->array.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_empty_literal))
			{
				driver()->push(localname, _empty_reader.get_reader(&t()->empty.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_null_literal))
			{
				driver()->push(localname, _null_reader.get_reader(&t()->null.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_cy_literal))
			{
				driver()->push(localname, _cy_reader.get_reader(&t()->cy.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_error_literal))
			{
				driver()->push(localname, _error_reader.get_reader(&t()->error.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_vstream_literal))
			{
				driver()->push(localname, _vstream_reader.get_reader(&t()->vstream.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_clsid_literal))
			{
				driver()->push(localname, _clsid_reader.get_reader(&t()->clsid.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_cf_literal))
			{
				driver()->push(localname, _cf_reader.get_reader(&t()->cf.getset()));
				return;
			}
		}
		void shared_documentPropertiesVariantTypes_reader::end_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname)
		{
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_blob_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->blob.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_oblob_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->oblob.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_i1_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->i1.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_i2_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->i2.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_i4_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->i4.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_i8_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->i8.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes__int__literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->_int_.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_ui1_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->ui1.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_ui2_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->ui2.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_ui4_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->ui4.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_ui8_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->ui8.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_uint_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->uint.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_r4_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->r4.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_r8_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->r8.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_decimal_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->decimal.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_lpstr_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->lpstr.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_lpwstr_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->lpwstr.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_bstr_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->bstr.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_date_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->date.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_filetime_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->filetime.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes__bool__literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->_bool_.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_stream_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->stream.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_ostream_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->ostream.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_storage_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->storage.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesVariantTypes_ostorage_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->ostorage.getset());
				return;
			}
		}
	}
}
