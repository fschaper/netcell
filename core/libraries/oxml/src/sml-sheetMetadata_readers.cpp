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


#include "sml-sheetMetadata_readers.hpp"
#include "sml-sheetMetadata_literals.hpp"
#include <xio/xml/binding/driver.hpp>

namespace spreadsheetml
{
	namespace xio
	{
		void CT_MetadataType_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_name_literal))
			{
				driver()->context()->parse(value, t()->name);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_minSupportedVersion_literal))
			{
				driver()->context()->parse(value, t()->minSupportedVersion);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_ghostRow_literal))
			{
				driver()->context()->parse(value, t()->ghostRow);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_ghostCol_literal))
			{
				driver()->context()->parse(value, t()->ghostCol);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_edit_literal))
			{
				driver()->context()->parse(value, t()->edit);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata__delete__literal))
			{
				driver()->context()->parse(value, t()->_delete_);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_copy_literal))
			{
				driver()->context()->parse(value, t()->copy);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_pasteAll_literal))
			{
				driver()->context()->parse(value, t()->pasteAll);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_pasteFormulas_literal))
			{
				driver()->context()->parse(value, t()->pasteFormulas);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_pasteValues_literal))
			{
				driver()->context()->parse(value, t()->pasteValues);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_pasteFormats_literal))
			{
				driver()->context()->parse(value, t()->pasteFormats);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_pasteComments_literal))
			{
				driver()->context()->parse(value, t()->pasteComments);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_pasteDataValidation_literal))
			{
				driver()->context()->parse(value, t()->pasteDataValidation);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_pasteBorders_literal))
			{
				driver()->context()->parse(value, t()->pasteBorders);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_pasteColWidths_literal))
			{
				driver()->context()->parse(value, t()->pasteColWidths);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_pasteNumberFormats_literal))
			{
				driver()->context()->parse(value, t()->pasteNumberFormats);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_merge_literal))
			{
				driver()->context()->parse(value, t()->merge);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_splitFirst_literal))
			{
				driver()->context()->parse(value, t()->splitFirst);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_splitAll_literal))
			{
				driver()->context()->parse(value, t()->splitAll);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_rowColShift_literal))
			{
				driver()->context()->parse(value, t()->rowColShift);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_clearAll_literal))
			{
				driver()->context()->parse(value, t()->clearAll);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_clearFormats_literal))
			{
				driver()->context()->parse(value, t()->clearFormats);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_clearContents_literal))
			{
				driver()->context()->parse(value, t()->clearContents);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_clearComments_literal))
			{
				driver()->context()->parse(value, t()->clearComments);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_assign_literal))
			{
				driver()->context()->parse(value, t()->assign);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_coerce_literal))
			{
				driver()->context()->parse(value, t()->coerce);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_adjust_literal))
			{
				driver()->context()->parse(value, t()->adjust);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_cellMeta_literal))
			{
				driver()->context()->parse(value, t()->cellMeta);
				return;
			}
		}
		void CT_MetadataTypes_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_metadataType_literal))
			{
				t()->metadataType.resize(t()->metadataType.size()+1);
				driver()->push(localname, _metadataType_reader.get_reader(&t()->metadataType.back()));
				return;
			}
		}
		void CT_MetadataTypes_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_count_literal))
			{
				driver()->context()->parse(value, t()->count);
				return;
			}
		}
		void CT_MetadataStrings_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_s_literal))
			{
				t()->s.resize(t()->s.size()+1);
				driver()->push(localname, _s_reader.get_reader(&t()->s.back()));
				return;
			}
		}
		void CT_MetadataStrings_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_count_literal))
			{
				driver()->context()->parse(value, t()->count);
				return;
			}
		}
		void CT_MetadataStringIndex_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_x_literal))
			{
				driver()->context()->parse(value, t()->x);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_s_literal))
			{
				driver()->context()->parse(value, t()->s);
				return;
			}
		}
		void CT_MdxTuple_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_n_literal))
			{
				t()->n.resize(t()->n.size()+1);
				driver()->push(localname, _n_reader.get_reader(&t()->n.back()));
				return;
			}
		}
		void CT_MdxTuple_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_c_literal))
			{
				driver()->context()->parse(value, t()->c);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_ct_literal))
			{
				driver()->context()->parse(value, t()->ct.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_si_literal))
			{
				driver()->context()->parse(value, t()->si.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_fi_literal))
			{
				driver()->context()->parse(value, t()->fi.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_bc_literal))
			{
				driver()->context()->parse(value, t()->bc.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_fc_literal))
			{
				driver()->context()->parse(value, t()->fc.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_i_literal))
			{
				driver()->context()->parse(value, t()->i);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_u_literal))
			{
				driver()->context()->parse(value, t()->u);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_st_literal))
			{
				driver()->context()->parse(value, t()->st);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_b_literal))
			{
				driver()->context()->parse(value, t()->b);
				return;
			}
		}
		void CT_MdxSet_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_n_literal))
			{
				t()->n.resize(t()->n.size()+1);
				driver()->push(localname, _n_reader.get_reader(&t()->n.back()));
				return;
			}
		}
		void CT_MdxSet_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_ns_literal))
			{
				driver()->context()->parse(value, t()->ns);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_c_literal))
			{
				driver()->context()->parse(value, t()->c);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_o_literal))
			{
				driver()->context()->parse(value, t()->o);
				return;
			}
		}
		void CT_MdxMemeberProp_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_n_literal))
			{
				driver()->context()->parse(value, t()->n);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_np_literal))
			{
				driver()->context()->parse(value, t()->np);
				return;
			}
		}
		void CT_MdxKPI_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_n_literal))
			{
				driver()->context()->parse(value, t()->n);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_np_literal))
			{
				driver()->context()->parse(value, t()->np);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_p_literal))
			{
				driver()->context()->parse(value, t()->p);
				return;
			}
		}
		void CT_Mdx_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_t_literal))
			{
				driver()->push(localname, _t_reader.get_reader(&t()->t.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_ms_literal))
			{
				driver()->push(localname, _ms_reader.get_reader(&t()->ms.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_p_literal))
			{
				driver()->push(localname, _p_reader.get_reader(&t()->p.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_k_literal))
			{
				driver()->push(localname, _k_reader.get_reader(&t()->k.getset()));
				return;
			}
		}
		void CT_Mdx_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_n_literal))
			{
				driver()->context()->parse(value, t()->n);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_f_literal))
			{
				driver()->context()->parse(value, t()->f);
				return;
			}
		}
		void CT_MdxMetadata_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_mdx_literal))
			{
				t()->mdx.resize(t()->mdx.size()+1);
				driver()->push(localname, _mdx_reader.get_reader(&t()->mdx.back()));
				return;
			}
		}
		void CT_MdxMetadata_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_count_literal))
			{
				driver()->context()->parse(value, t()->count);
				return;
			}
		}
		void CT_FutureMetadataBlock_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_FutureMetadata_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_bk_literal))
			{
				t()->bk.resize(t()->bk.size()+1);
				driver()->push(localname, _bk_reader.get_reader(&t()->bk.back()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_FutureMetadata_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_name_literal))
			{
				driver()->context()->parse(value, t()->name);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_count_literal))
			{
				driver()->context()->parse(value, t()->count);
				return;
			}
		}
		void CT_MetadataRecord_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_t_literal))
			{
				driver()->context()->parse(value, t()->t);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_v_literal))
			{
				driver()->context()->parse(value, t()->v);
				return;
			}
		}
		void CT_MetadataBlock_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_rc_literal))
			{
				t()->rc.resize(t()->rc.size()+1);
				driver()->push(localname, _rc_reader.get_reader(&t()->rc.back()));
				return;
			}
		}
		void CT_MetadataBlocks_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_bk_literal))
			{
				t()->bk.resize(t()->bk.size()+1);
				driver()->push(localname, _bk_reader.get_reader(&t()->bk.back()));
				return;
			}
		}
		void CT_MetadataBlocks_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_count_literal))
			{
				driver()->context()->parse(value, t()->count);
				return;
			}
		}
		void CT_Metadata_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_metadataTypes_literal))
			{
				driver()->push(localname, _metadataTypes_reader.get_reader(&t()->metadataTypes.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_metadataStrings_literal))
			{
				driver()->push(localname, _metadataStrings_reader.get_reader(&t()->metadataStrings.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_mdxMetadata_literal))
			{
				driver()->push(localname, _mdxMetadata_reader.get_reader(&t()->mdxMetadata.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_futureMetadata_literal))
			{
				t()->futureMetadata.resize(t()->futureMetadata.size()+1);
				driver()->push(localname, _futureMetadata_reader.get_reader(&t()->futureMetadata.back()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_cellMetadata_literal))
			{
				driver()->push(localname, _cellMetadata_reader.get_reader(&t()->cellMetadata.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_valueMetadata_literal))
			{
				driver()->push(localname, _valueMetadata_reader.get_reader(&t()->valueMetadata.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void sml_sheetMetadata_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sheetMetadata_metadata_literal))
			{
				driver()->push(localname, _metadata_reader.get_reader(&t()->metadata.getset()));
				return;
			}
		}
	}
}
