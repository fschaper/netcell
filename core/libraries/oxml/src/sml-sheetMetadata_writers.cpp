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


#include "sml-sheetMetadata_writers.hpp"
#include "sml-sheetMetadata_literals.hpp"

namespace spreadsheetml
{
	namespace xio
	{
		void CT_MetadataType_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_sheetMetadata_name_literal, context()->serialize(t()->name));
			w.attribute(0, sml_sheetMetadata_minSupportedVersion_literal, context()->serialize(t()->minSupportedVersion));
			if (t()->ghostRow != false)
				w.attribute(0, sml_sheetMetadata_ghostRow_literal, context()->serialize(t()->ghostRow));
			if (t()->ghostCol != false)
				w.attribute(0, sml_sheetMetadata_ghostCol_literal, context()->serialize(t()->ghostCol));
			if (t()->edit != false)
				w.attribute(0, sml_sheetMetadata_edit_literal, context()->serialize(t()->edit));
			if (t()->_delete_ != false)
				w.attribute(0, sml_sheetMetadata__delete__literal, context()->serialize(t()->_delete_));
			if (t()->copy != false)
				w.attribute(0, sml_sheetMetadata_copy_literal, context()->serialize(t()->copy));
			if (t()->pasteAll != false)
				w.attribute(0, sml_sheetMetadata_pasteAll_literal, context()->serialize(t()->pasteAll));
			if (t()->pasteFormulas != false)
				w.attribute(0, sml_sheetMetadata_pasteFormulas_literal, context()->serialize(t()->pasteFormulas));
			if (t()->pasteValues != false)
				w.attribute(0, sml_sheetMetadata_pasteValues_literal, context()->serialize(t()->pasteValues));
			if (t()->pasteFormats != false)
				w.attribute(0, sml_sheetMetadata_pasteFormats_literal, context()->serialize(t()->pasteFormats));
			if (t()->pasteComments != false)
				w.attribute(0, sml_sheetMetadata_pasteComments_literal, context()->serialize(t()->pasteComments));
			if (t()->pasteDataValidation != false)
				w.attribute(0, sml_sheetMetadata_pasteDataValidation_literal, context()->serialize(t()->pasteDataValidation));
			if (t()->pasteBorders != false)
				w.attribute(0, sml_sheetMetadata_pasteBorders_literal, context()->serialize(t()->pasteBorders));
			if (t()->pasteColWidths != false)
				w.attribute(0, sml_sheetMetadata_pasteColWidths_literal, context()->serialize(t()->pasteColWidths));
			if (t()->pasteNumberFormats != false)
				w.attribute(0, sml_sheetMetadata_pasteNumberFormats_literal, context()->serialize(t()->pasteNumberFormats));
			if (t()->merge != false)
				w.attribute(0, sml_sheetMetadata_merge_literal, context()->serialize(t()->merge));
			if (t()->splitFirst != false)
				w.attribute(0, sml_sheetMetadata_splitFirst_literal, context()->serialize(t()->splitFirst));
			if (t()->splitAll != false)
				w.attribute(0, sml_sheetMetadata_splitAll_literal, context()->serialize(t()->splitAll));
			if (t()->rowColShift != false)
				w.attribute(0, sml_sheetMetadata_rowColShift_literal, context()->serialize(t()->rowColShift));
			if (t()->clearAll != false)
				w.attribute(0, sml_sheetMetadata_clearAll_literal, context()->serialize(t()->clearAll));
			if (t()->clearFormats != false)
				w.attribute(0, sml_sheetMetadata_clearFormats_literal, context()->serialize(t()->clearFormats));
			if (t()->clearContents != false)
				w.attribute(0, sml_sheetMetadata_clearContents_literal, context()->serialize(t()->clearContents));
			if (t()->clearComments != false)
				w.attribute(0, sml_sheetMetadata_clearComments_literal, context()->serialize(t()->clearComments));
			if (t()->assign != false)
				w.attribute(0, sml_sheetMetadata_assign_literal, context()->serialize(t()->assign));
			if (t()->coerce != false)
				w.attribute(0, sml_sheetMetadata_coerce_literal, context()->serialize(t()->coerce));
			if (t()->adjust != false)
				w.attribute(0, sml_sheetMetadata_adjust_literal, context()->serialize(t()->adjust));
			if (t()->cellMeta != false)
				w.attribute(0, sml_sheetMetadata_cellMeta_literal, context()->serialize(t()->cellMeta));
		}

		void CT_MetadataTypes_writer::write_target_to(xml_writer& w) {
			if (t()->count != 0U)
				w.attribute(0, sml_sheetMetadata_count_literal, context()->serialize(t()->count));
			for (size_t sqi = 0; sqi<t()->metadataType.size(); ++sqi) {
				w.start_element(0, sml_sheetMetadata_metadataType_literal);
				_metadataType_writer.get_writer(context(), &t()->metadataType[sqi])->write_target_to(w);
				w.end_element(0, sml_sheetMetadata_metadataType_literal);
			}
		}

		void CT_MetadataStrings_writer::write_target_to(xml_writer& w) {
			if (t()->count != 0U)
				w.attribute(0, sml_sheetMetadata_count_literal, context()->serialize(t()->count));
			for (size_t sqi = 0; sqi<t()->s.size(); ++sqi) {
				w.start_element(0, sml_sheetMetadata_s_literal);
				_s_writer.get_writer(context(), &t()->s[sqi])->write_target_to(w);
				w.end_element(0, sml_sheetMetadata_s_literal);
			}
		}

		void CT_MetadataStringIndex_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_sheetMetadata_x_literal, context()->serialize(t()->x));
			if (t()->s != false)
				w.attribute(0, sml_sheetMetadata_s_literal, context()->serialize(t()->s));
		}

		void CT_MdxTuple_writer::write_target_to(xml_writer& w) {
			if (t()->c != 0U)
				w.attribute(0, sml_sheetMetadata_c_literal, context()->serialize(t()->c));
			if (t()->ct.present())
				w.attribute(0, sml_sheetMetadata_ct_literal, context()->serialize(t()->ct.get()));
			if (t()->si.present())
				w.attribute(0, sml_sheetMetadata_si_literal, context()->serialize(t()->si.get()));
			if (t()->fi.present())
				w.attribute(0, sml_sheetMetadata_fi_literal, context()->serialize(t()->fi.get()));
			if (t()->bc.present())
				w.attribute(0, sml_sheetMetadata_bc_literal, context()->serialize(t()->bc.get()));
			if (t()->fc.present())
				w.attribute(0, sml_sheetMetadata_fc_literal, context()->serialize(t()->fc.get()));
			if (t()->i != false)
				w.attribute(0, sml_sheetMetadata_i_literal, context()->serialize(t()->i));
			if (t()->u != false)
				w.attribute(0, sml_sheetMetadata_u_literal, context()->serialize(t()->u));
			if (t()->st != false)
				w.attribute(0, sml_sheetMetadata_st_literal, context()->serialize(t()->st));
			if (t()->b != false)
				w.attribute(0, sml_sheetMetadata_b_literal, context()->serialize(t()->b));
			for (size_t sqi = 0; sqi<t()->n.size(); ++sqi) {
				w.start_element(0, sml_sheetMetadata_n_literal);
				_n_writer.get_writer(context(), &t()->n[sqi])->write_target_to(w);
				w.end_element(0, sml_sheetMetadata_n_literal);
			}
		}

		void CT_MdxSet_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_sheetMetadata_ns_literal, context()->serialize(t()->ns));
			if (t()->c != 0U)
				w.attribute(0, sml_sheetMetadata_c_literal, context()->serialize(t()->c));
			if (t()->o != ST_MdxSetOrder::u_literal)
				w.attribute(0, sml_sheetMetadata_o_literal, context()->serialize(t()->o));
			for (size_t sqi = 0; sqi<t()->n.size(); ++sqi) {
				w.start_element(0, sml_sheetMetadata_n_literal);
				_n_writer.get_writer(context(), &t()->n[sqi])->write_target_to(w);
				w.end_element(0, sml_sheetMetadata_n_literal);
			}
		}

		void CT_MdxMemeberProp_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_sheetMetadata_n_literal, context()->serialize(t()->n));
			w.attribute(0, sml_sheetMetadata_np_literal, context()->serialize(t()->np));
		}

		void CT_MdxKPI_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_sheetMetadata_n_literal, context()->serialize(t()->n));
			w.attribute(0, sml_sheetMetadata_np_literal, context()->serialize(t()->np));
			w.attribute(0, sml_sheetMetadata_p_literal, context()->serialize(t()->p));
		}

		void CT_Mdx_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_sheetMetadata_n_literal, context()->serialize(t()->n));
			w.attribute(0, sml_sheetMetadata_f_literal, context()->serialize(t()->f));
			if (t()->t.present()) {
				w.start_element(0, sml_sheetMetadata_t_literal);
				_t_writer.get_writer(context(), &t()->t.get())->write_target_to(w);
				w.end_element(0, sml_sheetMetadata_t_literal);
			}
			if (t()->ms.present()) {
				w.start_element(0, sml_sheetMetadata_ms_literal);
				_ms_writer.get_writer(context(), &t()->ms.get())->write_target_to(w);
				w.end_element(0, sml_sheetMetadata_ms_literal);
			}
			if (t()->p.present()) {
				w.start_element(0, sml_sheetMetadata_p_literal);
				_p_writer.get_writer(context(), &t()->p.get())->write_target_to(w);
				w.end_element(0, sml_sheetMetadata_p_literal);
			}
			if (t()->k.present()) {
				w.start_element(0, sml_sheetMetadata_k_literal);
				_k_writer.get_writer(context(), &t()->k.get())->write_target_to(w);
				w.end_element(0, sml_sheetMetadata_k_literal);
			}
		}

		void CT_MdxMetadata_writer::write_target_to(xml_writer& w) {
			if (t()->count != 0U)
				w.attribute(0, sml_sheetMetadata_count_literal, context()->serialize(t()->count));
			for (size_t sqi = 0; sqi<t()->mdx.size(); ++sqi) {
				w.start_element(0, sml_sheetMetadata_mdx_literal);
				_mdx_writer.get_writer(context(), &t()->mdx[sqi])->write_target_to(w);
				w.end_element(0, sml_sheetMetadata_mdx_literal);
			}
		}

		void CT_FutureMetadataBlock_writer::write_target_to(xml_writer& w) {
			if (t()->extLst.present()) {
				w.start_element(0, sml_sheetMetadata_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_sheetMetadata_extLst_literal);
			}
		}

		void CT_FutureMetadata_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_sheetMetadata_name_literal, context()->serialize(t()->name));
			if (t()->count != 0U)
				w.attribute(0, sml_sheetMetadata_count_literal, context()->serialize(t()->count));
			for (size_t sqi = 0; sqi<t()->bk.size(); ++sqi) {
				w.start_element(0, sml_sheetMetadata_bk_literal);
				_bk_writer.get_writer(context(), &t()->bk[sqi])->write_target_to(w);
				w.end_element(0, sml_sheetMetadata_bk_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, sml_sheetMetadata_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_sheetMetadata_extLst_literal);
			}
		}

		void CT_MetadataRecord_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_sheetMetadata_t_literal, context()->serialize(t()->t));
			w.attribute(0, sml_sheetMetadata_v_literal, context()->serialize(t()->v));
		}

		void CT_MetadataBlock_writer::write_target_to(xml_writer& w) {
			for (size_t sqi = 0; sqi<t()->rc.size(); ++sqi) {
				w.start_element(0, sml_sheetMetadata_rc_literal);
				_rc_writer.get_writer(context(), &t()->rc[sqi])->write_target_to(w);
				w.end_element(0, sml_sheetMetadata_rc_literal);
			}
		}

		void CT_MetadataBlocks_writer::write_target_to(xml_writer& w) {
			if (t()->count != 0U)
				w.attribute(0, sml_sheetMetadata_count_literal, context()->serialize(t()->count));
			for (size_t sqi = 0; sqi<t()->bk.size(); ++sqi) {
				w.start_element(0, sml_sheetMetadata_bk_literal);
				_bk_writer.get_writer(context(), &t()->bk[sqi])->write_target_to(w);
				w.end_element(0, sml_sheetMetadata_bk_literal);
			}
		}

		void CT_Metadata_writer::write_target_to(xml_writer& w) {
			if (t()->metadataTypes.present()) {
				w.start_element(0, sml_sheetMetadata_metadataTypes_literal);
				_metadataTypes_writer.get_writer(context(), &t()->metadataTypes.get())->write_target_to(w);
				w.end_element(0, sml_sheetMetadata_metadataTypes_literal);
			}
			if (t()->metadataStrings.present()) {
				w.start_element(0, sml_sheetMetadata_metadataStrings_literal);
				_metadataStrings_writer.get_writer(context(), &t()->metadataStrings.get())->write_target_to(w);
				w.end_element(0, sml_sheetMetadata_metadataStrings_literal);
			}
			if (t()->mdxMetadata.present()) {
				w.start_element(0, sml_sheetMetadata_mdxMetadata_literal);
				_mdxMetadata_writer.get_writer(context(), &t()->mdxMetadata.get())->write_target_to(w);
				w.end_element(0, sml_sheetMetadata_mdxMetadata_literal);
			}
			for (size_t sqi = 0; sqi<t()->futureMetadata.size(); ++sqi) {
				w.start_element(0, sml_sheetMetadata_futureMetadata_literal);
				_futureMetadata_writer.get_writer(context(), &t()->futureMetadata[sqi])->write_target_to(w);
				w.end_element(0, sml_sheetMetadata_futureMetadata_literal);
			}
			if (t()->cellMetadata.present()) {
				w.start_element(0, sml_sheetMetadata_cellMetadata_literal);
				_cellMetadata_writer.get_writer(context(), &t()->cellMetadata.get())->write_target_to(w);
				w.end_element(0, sml_sheetMetadata_cellMetadata_literal);
			}
			if (t()->valueMetadata.present()) {
				w.start_element(0, sml_sheetMetadata_valueMetadata_literal);
				_valueMetadata_writer.get_writer(context(), &t()->valueMetadata.get())->write_target_to(w);
				w.end_element(0, sml_sheetMetadata_valueMetadata_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, sml_sheetMetadata_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_sheetMetadata_extLst_literal);
			}
		}

		void sml_sheetMetadata_writer::write_target_to(xml_writer& w) {
			if (t()->metadata.present()) {
				w.start_element(0, sml_sheetMetadata_metadata_literal);
					w.attribute(0, sml_sheetMetadata_xmlns_literal, sml_sheetMetadata_http_colon__slash__slash_schemas_dot_openxmlformats_dot_org_slash_spreadsheetml_slash_2006_slash_main_literal);
					w.attribute(sml_sheetMetadata_xmlns_literal, sml_sheetMetadata_xsd_literal, sml_sheetMetadata_http_colon__slash__slash_www_dot_w3_dot_org_slash_2001_slash_XMLSchema_literal);
				_metadata_writer.get_writer(context(), &t()->metadata.get())->write_target_to(w);
				w.end_element(0, sml_sheetMetadata_metadata_literal);
			}
		}

	}
}
