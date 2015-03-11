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


#include "shared-documentPropertiesCustom_readers.hpp"
#include "shared-documentPropertiesCustom_literals.hpp"
#include <xio/xml/binding/driver.hpp>

namespace custom_properties
{
	namespace xio
	{
		void CT_Property_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesCustom_vector_literal))
			{
				driver()->push(localname, _vector_reader.get_reader(&t()->vector.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesCustom_array_literal))
			{
				driver()->push(localname, _array_reader.get_reader(&t()->array.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesCustom_empty_literal))
			{
				driver()->push(localname, _empty_reader.get_reader(&t()->empty.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesCustom_null_literal))
			{
				driver()->push(localname, _null_reader.get_reader(&t()->null.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesCustom_cy_literal))
			{
				driver()->push(localname, _cy_reader.get_reader(&t()->cy.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesCustom_error_literal))
			{
				driver()->push(localname, _error_reader.get_reader(&t()->error.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesCustom_vstream_literal))
			{
				driver()->push(localname, _vstream_reader.get_reader(&t()->vstream.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesCustom_clsid_literal))
			{
				driver()->push(localname, _clsid_reader.get_reader(&t()->clsid.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesCustom_cf_literal))
			{
				driver()->push(localname, _cf_reader.get_reader(&t()->cf.getset()));
				return;
			}
		}
		void CT_Property_reader::end_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname)
		{
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesCustom_blob_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->blob.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesCustom_oblob_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->oblob.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesCustom_i1_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->i1.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesCustom_i2_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->i2.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesCustom_i4_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->i4.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesCustom_i8_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->i8.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesCustom__int__literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->_int_.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesCustom_ui1_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->ui1.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesCustom_ui2_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->ui2.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesCustom_ui4_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->ui4.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesCustom_ui8_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->ui8.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesCustom_uint_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->uint.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesCustom_r4_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->r4.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesCustom_r8_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->r8.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesCustom_decimal_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->decimal.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesCustom_lpstr_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->lpstr.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesCustom_lpwstr_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->lpwstr.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesCustom_bstr_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->bstr.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesCustom_date_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->date.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesCustom_filetime_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->filetime.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesCustom__bool__literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->_bool_.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesCustom_stream_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->stream.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesCustom_ostream_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->ostream.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesCustom_storage_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->storage.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesCustom_ostorage_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->ostorage.getset());
				return;
			}
		}
		void CT_Property_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesCustom_fmtid_literal))
			{
				driver()->context()->parse(value, t()->fmtid);
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesCustom_pid_literal))
			{
				driver()->context()->parse(value, t()->pid);
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesCustom_name_literal))
			{
				driver()->context()->parse(value, t()->name.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesCustom_linkTarget_literal))
			{
				driver()->context()->parse(value, t()->linkTarget.getset());
				return;
			}
		}
		void CT_Properties_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesCustom_property_literal))
			{
				t()->property.resize(t()->property.size()+1);
				driver()->push(localname, _property_reader.get_reader(&t()->property.back()));
				return;
			}
		}
		void shared_documentPropertiesCustom_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, shared_documentPropertiesCustom_Properties_literal))
			{
				driver()->push(localname, _Properties_reader.get_reader(&t()->Properties.getset()));
				return;
			}
		}
	}
}
