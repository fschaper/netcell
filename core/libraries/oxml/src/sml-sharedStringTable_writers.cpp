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


#include "sml-sharedStringTable_writers.hpp"
#include "sml-sharedStringTable_literals.hpp"

namespace spreadsheetml
{
	namespace xio
	{
		void CT_RPrElt_writer::write_target_to(xml_writer& w) {
			if (t()->rFont.present()) {
				w.start_element(0, sml_sharedStringTable_rFont_literal);
				_rFont_writer.get_writer(context(), &t()->rFont.get())->write_target_to(w);
				w.end_element(0, sml_sharedStringTable_rFont_literal);
			}
			if (t()->charset.present()) {
				w.start_element(0, sml_sharedStringTable_charset_literal);
				_charset_writer.get_writer(context(), &t()->charset.get())->write_target_to(w);
				w.end_element(0, sml_sharedStringTable_charset_literal);
			}
			if (t()->family.present()) {
				w.start_element(0, sml_sharedStringTable_family_literal);
				_family_writer.get_writer(context(), &t()->family.get())->write_target_to(w);
				w.end_element(0, sml_sharedStringTable_family_literal);
			}
			if (t()->b.present()) {
				w.start_element(0, sml_sharedStringTable_b_literal);
				_b_writer.get_writer(context(), &t()->b.get())->write_target_to(w);
				w.end_element(0, sml_sharedStringTable_b_literal);
			}
			if (t()->i.present()) {
				w.start_element(0, sml_sharedStringTable_i_literal);
				_i_writer.get_writer(context(), &t()->i.get())->write_target_to(w);
				w.end_element(0, sml_sharedStringTable_i_literal);
			}
			if (t()->strike.present()) {
				w.start_element(0, sml_sharedStringTable_strike_literal);
				_strike_writer.get_writer(context(), &t()->strike.get())->write_target_to(w);
				w.end_element(0, sml_sharedStringTable_strike_literal);
			}
			if (t()->outline.present()) {
				w.start_element(0, sml_sharedStringTable_outline_literal);
				_outline_writer.get_writer(context(), &t()->outline.get())->write_target_to(w);
				w.end_element(0, sml_sharedStringTable_outline_literal);
			}
			if (t()->shadow.present()) {
				w.start_element(0, sml_sharedStringTable_shadow_literal);
				_shadow_writer.get_writer(context(), &t()->shadow.get())->write_target_to(w);
				w.end_element(0, sml_sharedStringTable_shadow_literal);
			}
			if (t()->condense.present()) {
				w.start_element(0, sml_sharedStringTable_condense_literal);
				_condense_writer.get_writer(context(), &t()->condense.get())->write_target_to(w);
				w.end_element(0, sml_sharedStringTable_condense_literal);
			}
			if (t()->extend.present()) {
				w.start_element(0, sml_sharedStringTable_extend_literal);
				_extend_writer.get_writer(context(), &t()->extend.get())->write_target_to(w);
				w.end_element(0, sml_sharedStringTable_extend_literal);
			}
			if (t()->color.present()) {
				w.start_element(0, sml_sharedStringTable_color_literal);
				_color_writer.get_writer(context(), &t()->color.get())->write_target_to(w);
				w.end_element(0, sml_sharedStringTable_color_literal);
			}
			if (t()->sz.present()) {
				w.start_element(0, sml_sharedStringTable_sz_literal);
				_sz_writer.get_writer(context(), &t()->sz.get())->write_target_to(w);
				w.end_element(0, sml_sharedStringTable_sz_literal);
			}
			if (t()->u.present()) {
				w.start_element(0, sml_sharedStringTable_u_literal);
				_u_writer.get_writer(context(), &t()->u.get())->write_target_to(w);
				w.end_element(0, sml_sharedStringTable_u_literal);
			}
			if (t()->vertAlign.present()) {
				w.start_element(0, sml_sharedStringTable_vertAlign_literal);
				_vertAlign_writer.get_writer(context(), &t()->vertAlign.get())->write_target_to(w);
				w.end_element(0, sml_sharedStringTable_vertAlign_literal);
			}
			if (t()->scheme.present()) {
				w.start_element(0, sml_sharedStringTable_scheme_literal);
				_scheme_writer.get_writer(context(), &t()->scheme.get())->write_target_to(w);
				w.end_element(0, sml_sharedStringTable_scheme_literal);
			}
		}

		void CT_RElt_writer::write_target_to(xml_writer& w) {
			if (t()->rPr.present()) {
				w.start_element(0, sml_sharedStringTable_rPr_literal);
				_rPr_writer.get_writer(context(), &t()->rPr.get())->write_target_to(w);
				w.end_element(0, sml_sharedStringTable_rPr_literal);
			}
			w.start_element(0, sml_sharedStringTable_t_literal);
			_t_writer.get_writer(context(), &t()->t)->write_target_to(w);
			w.end_element(0, sml_sharedStringTable_t_literal);
		}

		void CT_PhoneticRun_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_sharedStringTable_sb_literal, context()->serialize(t()->sb));
			w.attribute(0, sml_sharedStringTable_eb_literal, context()->serialize(t()->eb));
			w.start_element(0, sml_sharedStringTable_t_literal);
			_t_writer.get_writer(context(), &t()->t)->write_target_to(w);
			w.end_element(0, sml_sharedStringTable_t_literal);
		}

		void CT_PhoneticPr_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_sharedStringTable_fontId_literal, context()->serialize(t()->fontId));
			if (t()->type != ST_PhoneticType::fullwidthKatakana_literal)
				w.attribute(0, sml_sharedStringTable_type_literal, context()->serialize(t()->type));
			if (t()->alignment != ST_PhoneticAlignment::left_literal)
				w.attribute(0, sml_sharedStringTable_alignment_literal, context()->serialize(t()->alignment));
		}

		void CT_Rst_writer::write_target_to(xml_writer& w) {
			if (t()->t.present()) {
				w.start_element(0, sml_sharedStringTable_t_literal);
				_t_writer.get_writer(context(), &t()->t.get())->write_target_to(w);
				w.end_element(0, sml_sharedStringTable_t_literal);
			}
			for (size_t sqi = 0; sqi<t()->r.size(); ++sqi) {
				w.start_element(0, sml_sharedStringTable_r_literal);
				_r_writer.get_writer(context(), &t()->r[sqi])->write_target_to(w);
				w.end_element(0, sml_sharedStringTable_r_literal);
			}
			for (size_t sqi = 0; sqi<t()->rPh.size(); ++sqi) {
				w.start_element(0, sml_sharedStringTable_rPh_literal);
				_rPh_writer.get_writer(context(), &t()->rPh[sqi])->write_target_to(w);
				w.end_element(0, sml_sharedStringTable_rPh_literal);
			}
			if (t()->phoneticPr.present()) {
				w.start_element(0, sml_sharedStringTable_phoneticPr_literal);
				_phoneticPr_writer.get_writer(context(), &t()->phoneticPr.get())->write_target_to(w);
				w.end_element(0, sml_sharedStringTable_phoneticPr_literal);
			}
		}

		void CT_Sst_writer::write_target_to(xml_writer& w) {
			if (t()->count.present())
				w.attribute(0, sml_sharedStringTable_count_literal, context()->serialize(t()->count.get()));
			if (t()->uniqueCount.present())
				w.attribute(0, sml_sharedStringTable_uniqueCount_literal, context()->serialize(t()->uniqueCount.get()));
			for (size_t sqi = 0; sqi<t()->si.size(); ++sqi) {
				w.start_element(0, sml_sharedStringTable_si_literal);
				_si_writer.get_writer(context(), &t()->si[sqi])->write_target_to(w);
				w.end_element(0, sml_sharedStringTable_si_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, sml_sharedStringTable_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_sharedStringTable_extLst_literal);
			}
		}

		void sml_sharedStringTable_writer::write_target_to(xml_writer& w) {
			if (t()->sst.present()) {
				w.start_element(0, sml_sharedStringTable_sst_literal);
					w.attribute(0, sml_sharedStringTable_xmlns_literal, sml_sharedStringTable_http_colon__slash__slash_schemas_dot_openxmlformats_dot_org_slash_spreadsheetml_slash_2006_slash_main_literal);
					w.attribute(sml_sharedStringTable_xmlns_literal, sml_sharedStringTable_xsd_literal, sml_sharedStringTable_http_colon__slash__slash_www_dot_w3_dot_org_slash_2001_slash_XMLSchema_literal);
				_sst_writer.get_writer(context(), &t()->sst.get())->write_target_to(w);
				w.end_element(0, sml_sharedStringTable_sst_literal);
			}
		}

	}
}
