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


#include "sml-baseTypes_writers.hpp"
#include "sml-baseTypes_literals.hpp"

namespace spreadsheetml
{
	namespace xio
	{
		void ST_CellRef_writer::write_target_to(xml_writer& w) {
			w.write_element_value(context()->serialize(*t()));
		}

		void CT_Extension_writer::write_target_to(xml_writer& w) {
			if (t()->uri.present())
				w.attribute(0, sml_baseTypes_uri_literal, context()->serialize(t()->uri.get()));
		}

		void CT_ExtensionList_writer::write_target_to(xml_writer& w) {
			for (size_t sqi = 0; sqi<t()->ext.size(); ++sqi) {
				w.start_element(0, sml_baseTypes_ext_literal);
				_ext_writer.get_writer(context(), &t()->ext[sqi])->write_target_to(w);
				w.end_element(0, sml_baseTypes_ext_literal);
			}
		}

		void ST_Xstring_writer::write_target_to(xml_writer& w) {
			w.write_element_value(context()->serialize(*t()));
		}

		void ST_UnsignedIntHex_writer::write_target_to(xml_writer& w) {
			w.write_element_value(context()->serialize(*t()));
		}

		void ST_Ref_writer::write_target_to(xml_writer& w) {
			w.write_element_value(context()->serialize(*t()));
		}

		void ST_Guid_writer::write_target_to(xml_writer& w) {
			w.write_element_value(context()->serialize(*t()));
		}

		void CT_XStringElement_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_baseTypes_v_literal, context()->serialize(t()->v));
		}

		void ST_RefA_writer::write_target_to(xml_writer& w) {
			w.write_element_value(context()->serialize(*t()));
		}

		void ST_Formula_writer::write_target_to(xml_writer& w) {
			ST_Xstring_writer::write_target_to(w);
		}

		void ST_Sqref_writer::write_target_to(xml_writer& w) {
			ST_Ref_writer::write_target_to(w);
		}

		void ST_UnsignedShortHex_writer::write_target_to(xml_writer& w) {
			w.write_element_value(context()->serialize(*t()));
		}

	}
}
