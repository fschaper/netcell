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


#include "sml-volatileDependencies_writers.hpp"
#include "sml-volatileDependencies_literals.hpp"

namespace spreadsheetml
{
	namespace xio
	{
		void CT_VolTopicRef_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_volatileDependencies_r_literal, context()->serialize(t()->r));
			w.attribute(0, sml_volatileDependencies_s_literal, context()->serialize(t()->s));
		}

		void CT_VolTopic_writer::write_target_to(xml_writer& w) {
			if (t()->t != ST_VolValueType::n_literal)
				w.attribute(0, sml_volatileDependencies_t_literal, context()->serialize(t()->t));
			w.start_element(0, sml_volatileDependencies_v_literal);
			_v_writer.get_writer(context(), &t()->v)->write_target_to(w);
			w.end_element(0, sml_volatileDependencies_v_literal);
			for (size_t sqi = 0; sqi<t()->stp.size(); ++sqi) {
				w.start_element(0, sml_volatileDependencies_stp_literal);
				_stp_writer.get_writer(context(), &t()->stp[sqi])->write_target_to(w);
				w.end_element(0, sml_volatileDependencies_stp_literal);
			}
			for (size_t sqi = 0; sqi<t()->tr.size(); ++sqi) {
				w.start_element(0, sml_volatileDependencies_tr_literal);
				_tr_writer.get_writer(context(), &t()->tr[sqi])->write_target_to(w);
				w.end_element(0, sml_volatileDependencies_tr_literal);
			}
		}

		void CT_VolMain_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_volatileDependencies_first_literal, context()->serialize(t()->first));
			for (size_t sqi = 0; sqi<t()->tp.size(); ++sqi) {
				w.start_element(0, sml_volatileDependencies_tp_literal);
				_tp_writer.get_writer(context(), &t()->tp[sqi])->write_target_to(w);
				w.end_element(0, sml_volatileDependencies_tp_literal);
			}
		}

		void CT_VolType_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_volatileDependencies_type_literal, context()->serialize(t()->type));
			for (size_t sqi = 0; sqi<t()->main.size(); ++sqi) {
				w.start_element(0, sml_volatileDependencies_main_literal);
				_main_writer.get_writer(context(), &t()->main[sqi])->write_target_to(w);
				w.end_element(0, sml_volatileDependencies_main_literal);
			}
		}

		void CT_VolTypes_writer::write_target_to(xml_writer& w) {
			for (size_t sqi = 0; sqi<t()->volType.size(); ++sqi) {
				w.start_element(0, sml_volatileDependencies_volType_literal);
				_volType_writer.get_writer(context(), &t()->volType[sqi])->write_target_to(w);
				w.end_element(0, sml_volatileDependencies_volType_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, sml_volatileDependencies_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_volatileDependencies_extLst_literal);
			}
		}

		void sml_volatileDependencies_writer::write_target_to(xml_writer& w) {
			if (t()->volTypes.present()) {
				w.start_element(0, sml_volatileDependencies_volTypes_literal);
					w.attribute(0, sml_volatileDependencies_xmlns_literal, sml_volatileDependencies_http_colon__slash__slash_schemas_dot_openxmlformats_dot_org_slash_spreadsheetml_slash_2006_slash_main_literal);
					w.attribute(sml_volatileDependencies_xmlns_literal, sml_volatileDependencies_xsd_literal, sml_volatileDependencies_http_colon__slash__slash_www_dot_w3_dot_org_slash_2001_slash_XMLSchema_literal);
				_volTypes_writer.get_writer(context(), &t()->volTypes.get())->write_target_to(w);
				w.end_element(0, sml_volatileDependencies_volTypes_literal);
			}
		}

	}
}
