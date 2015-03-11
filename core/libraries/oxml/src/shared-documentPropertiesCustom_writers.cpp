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


#include "shared-documentPropertiesCustom_writers.hpp"
#include "shared-documentPropertiesCustom_literals.hpp"

namespace custom_properties
{
	namespace xio
	{
		void CT_Property_writer::write_target_to(xml_writer& w) {
			w.attribute(0, shared_documentPropertiesCustom_fmtid_literal, context()->serialize(t()->fmtid));
			w.attribute(0, shared_documentPropertiesCustom_pid_literal, context()->serialize(t()->pid));
			if (t()->name.present())
				w.attribute(0, shared_documentPropertiesCustom_name_literal, context()->serialize(t()->name.get()));
			if (t()->linkTarget.present())
				w.attribute(0, shared_documentPropertiesCustom_linkTarget_literal, context()->serialize(t()->linkTarget.get()));
			if (t()->vector.present()) {
				w.start_element(0, shared_documentPropertiesCustom_vector_literal);
				_vector_writer.get_writer(context(), &t()->vector.get())->write_target_to(w);
				w.end_element(0, shared_documentPropertiesCustom_vector_literal);
			}
			if (t()->array.present()) {
				w.start_element(0, shared_documentPropertiesCustom_array_literal);
				_array_writer.get_writer(context(), &t()->array.get())->write_target_to(w);
				w.end_element(0, shared_documentPropertiesCustom_array_literal);
			}
			if (t()->blob.present()) {
				w.start_element(0, shared_documentPropertiesCustom_blob_literal);
				w.write_element_value(context()->serialize(t()->blob.get()));
				w.end_element(0, shared_documentPropertiesCustom_blob_literal);
			}
			if (t()->oblob.present()) {
				w.start_element(0, shared_documentPropertiesCustom_oblob_literal);
				w.write_element_value(context()->serialize(t()->oblob.get()));
				w.end_element(0, shared_documentPropertiesCustom_oblob_literal);
			}
			if (t()->empty.present()) {
				w.start_element(0, shared_documentPropertiesCustom_empty_literal);
				_empty_writer.get_writer(context(), &t()->empty.get())->write_target_to(w);
				w.end_element(0, shared_documentPropertiesCustom_empty_literal);
			}
			if (t()->null.present()) {
				w.start_element(0, shared_documentPropertiesCustom_null_literal);
				_null_writer.get_writer(context(), &t()->null.get())->write_target_to(w);
				w.end_element(0, shared_documentPropertiesCustom_null_literal);
			}
			if (t()->i1.present()) {
				w.start_element(0, shared_documentPropertiesCustom_i1_literal);
				w.write_element_value(context()->serialize(t()->i1.get()));
				w.end_element(0, shared_documentPropertiesCustom_i1_literal);
			}
			if (t()->i2.present()) {
				w.start_element(0, shared_documentPropertiesCustom_i2_literal);
				w.write_element_value(context()->serialize(t()->i2.get()));
				w.end_element(0, shared_documentPropertiesCustom_i2_literal);
			}
			if (t()->i4.present()) {
				w.start_element(0, shared_documentPropertiesCustom_i4_literal);
				w.write_element_value(context()->serialize(t()->i4.get()));
				w.end_element(0, shared_documentPropertiesCustom_i4_literal);
			}
			if (t()->i8.present()) {
				w.start_element(0, shared_documentPropertiesCustom_i8_literal);
				w.write_element_value(context()->serialize(t()->i8.get()));
				w.end_element(0, shared_documentPropertiesCustom_i8_literal);
			}
			if (t()->_int_.present()) {
				w.start_element(0, shared_documentPropertiesCustom__int__literal);
				w.write_element_value(context()->serialize(t()->_int_.get()));
				w.end_element(0, shared_documentPropertiesCustom__int__literal);
			}
			if (t()->ui1.present()) {
				w.start_element(0, shared_documentPropertiesCustom_ui1_literal);
				w.write_element_value(context()->serialize(t()->ui1.get()));
				w.end_element(0, shared_documentPropertiesCustom_ui1_literal);
			}
			if (t()->ui2.present()) {
				w.start_element(0, shared_documentPropertiesCustom_ui2_literal);
				w.write_element_value(context()->serialize(t()->ui2.get()));
				w.end_element(0, shared_documentPropertiesCustom_ui2_literal);
			}
			if (t()->ui4.present()) {
				w.start_element(0, shared_documentPropertiesCustom_ui4_literal);
				w.write_element_value(context()->serialize(t()->ui4.get()));
				w.end_element(0, shared_documentPropertiesCustom_ui4_literal);
			}
			if (t()->ui8.present()) {
				w.start_element(0, shared_documentPropertiesCustom_ui8_literal);
				w.write_element_value(context()->serialize(t()->ui8.get()));
				w.end_element(0, shared_documentPropertiesCustom_ui8_literal);
			}
			if (t()->uint.present()) {
				w.start_element(0, shared_documentPropertiesCustom_uint_literal);
				w.write_element_value(context()->serialize(t()->uint.get()));
				w.end_element(0, shared_documentPropertiesCustom_uint_literal);
			}
			if (t()->r4.present()) {
				w.start_element(0, shared_documentPropertiesCustom_r4_literal);
				w.write_element_value(context()->serialize(t()->r4.get()));
				w.end_element(0, shared_documentPropertiesCustom_r4_literal);
			}
			if (t()->r8.present()) {
				w.start_element(0, shared_documentPropertiesCustom_r8_literal);
				w.write_element_value(context()->serialize(t()->r8.get()));
				w.end_element(0, shared_documentPropertiesCustom_r8_literal);
			}
			if (t()->decimal.present()) {
				w.start_element(0, shared_documentPropertiesCustom_decimal_literal);
				w.write_element_value(context()->serialize(t()->decimal.get()));
				w.end_element(0, shared_documentPropertiesCustom_decimal_literal);
			}
			if (t()->lpstr.present()) {
				w.start_element(0, shared_documentPropertiesCustom_lpstr_literal);
				w.write_element_value(context()->serialize(t()->lpstr.get()));
				w.end_element(0, shared_documentPropertiesCustom_lpstr_literal);
			}
			if (t()->lpwstr.present()) {
				w.start_element(0, shared_documentPropertiesCustom_lpwstr_literal);
				w.write_element_value(context()->serialize(t()->lpwstr.get()));
				w.end_element(0, shared_documentPropertiesCustom_lpwstr_literal);
			}
			if (t()->bstr.present()) {
				w.start_element(0, shared_documentPropertiesCustom_bstr_literal);
				w.write_element_value(context()->serialize(t()->bstr.get()));
				w.end_element(0, shared_documentPropertiesCustom_bstr_literal);
			}
			if (t()->date.present()) {
				w.start_element(0, shared_documentPropertiesCustom_date_literal);
				w.write_element_value(context()->serialize(t()->date.get()));
				w.end_element(0, shared_documentPropertiesCustom_date_literal);
			}
			if (t()->filetime.present()) {
				w.start_element(0, shared_documentPropertiesCustom_filetime_literal);
				w.write_element_value(context()->serialize(t()->filetime.get()));
				w.end_element(0, shared_documentPropertiesCustom_filetime_literal);
			}
			if (t()->_bool_.present()) {
				w.start_element(0, shared_documentPropertiesCustom__bool__literal);
				w.write_element_value(context()->serialize(t()->_bool_.get()));
				w.end_element(0, shared_documentPropertiesCustom__bool__literal);
			}
			if (t()->cy.present()) {
				w.start_element(0, shared_documentPropertiesCustom_cy_literal);
				_cy_writer.get_writer(context(), &t()->cy.get())->write_target_to(w);
				w.end_element(0, shared_documentPropertiesCustom_cy_literal);
			}
			if (t()->error.present()) {
				w.start_element(0, shared_documentPropertiesCustom_error_literal);
				_error_writer.get_writer(context(), &t()->error.get())->write_target_to(w);
				w.end_element(0, shared_documentPropertiesCustom_error_literal);
			}
			if (t()->stream.present()) {
				w.start_element(0, shared_documentPropertiesCustom_stream_literal);
				w.write_element_value(context()->serialize(t()->stream.get()));
				w.end_element(0, shared_documentPropertiesCustom_stream_literal);
			}
			if (t()->ostream.present()) {
				w.start_element(0, shared_documentPropertiesCustom_ostream_literal);
				w.write_element_value(context()->serialize(t()->ostream.get()));
				w.end_element(0, shared_documentPropertiesCustom_ostream_literal);
			}
			if (t()->storage.present()) {
				w.start_element(0, shared_documentPropertiesCustom_storage_literal);
				w.write_element_value(context()->serialize(t()->storage.get()));
				w.end_element(0, shared_documentPropertiesCustom_storage_literal);
			}
			if (t()->ostorage.present()) {
				w.start_element(0, shared_documentPropertiesCustom_ostorage_literal);
				w.write_element_value(context()->serialize(t()->ostorage.get()));
				w.end_element(0, shared_documentPropertiesCustom_ostorage_literal);
			}
			if (t()->vstream.present()) {
				w.start_element(0, shared_documentPropertiesCustom_vstream_literal);
				_vstream_writer.get_writer(context(), &t()->vstream.get())->write_target_to(w);
				w.end_element(0, shared_documentPropertiesCustom_vstream_literal);
			}
			if (t()->clsid.present()) {
				w.start_element(0, shared_documentPropertiesCustom_clsid_literal);
				_clsid_writer.get_writer(context(), &t()->clsid.get())->write_target_to(w);
				w.end_element(0, shared_documentPropertiesCustom_clsid_literal);
			}
			if (t()->cf.present()) {
				w.start_element(0, shared_documentPropertiesCustom_cf_literal);
				_cf_writer.get_writer(context(), &t()->cf.get())->write_target_to(w);
				w.end_element(0, shared_documentPropertiesCustom_cf_literal);
			}
		}

		void CT_Properties_writer::write_target_to(xml_writer& w) {
			for (size_t sqi = 0; sqi<t()->property.size(); ++sqi) {
				w.start_element(0, shared_documentPropertiesCustom_property_literal);
				_property_writer.get_writer(context(), &t()->property[sqi])->write_target_to(w);
				w.end_element(0, shared_documentPropertiesCustom_property_literal);
			}
		}

		void shared_documentPropertiesCustom_writer::write_target_to(xml_writer& w) {
			if (t()->Properties.present()) {
				w.start_element(0, shared_documentPropertiesCustom_Properties_literal);
					w.attribute(0, shared_documentPropertiesCustom_xmlns_literal, shared_documentPropertiesCustom_http_colon__slash__slash_schemas_dot_openxmlformats_dot_org_slash_officeDocument_slash_2006_slash_custom_properties_literal);
					w.attribute(shared_documentPropertiesCustom_xmlns_literal, shared_documentPropertiesCustom_vt_literal, shared_documentPropertiesCustom_http_colon__slash__slash_schemas_dot_openxmlformats_dot_org_slash_officeDocument_slash_2006_slash_docPropsVTypes_literal);
					w.attribute(shared_documentPropertiesCustom_xmlns_literal, shared_documentPropertiesCustom_xsd_literal, shared_documentPropertiesCustom_http_colon__slash__slash_www_dot_w3_dot_org_slash_2001_slash_XMLSchema_literal);
				_Properties_writer.get_writer(context(), &t()->Properties.get())->write_target_to(w);
				w.end_element(0, shared_documentPropertiesCustom_Properties_literal);
			}
		}

	}
}
