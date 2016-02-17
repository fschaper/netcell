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


#include "dml-text_readers.hpp"
#include "dml-text_literals.hpp"
#include <xio/xml/binding/driver.hpp>

namespace drawingml
{
	namespace xio
	{
		void CT_TextNormalAutofit_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_text_fontScale_literal))
			{
				driver()->context()->parse(value, t()->fontScale);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_text_lnSpcReduction_literal))
			{
				driver()->context()->parse(value, t()->lnSpcReduction);
				return;
			}
		}
		void ST_TextColumnCount_reader::read_value(const xstring& val) {{ driver()->context()->parse(val, *t()); }}
		void CT_TextBodyProperties_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_text_prstTxWarp_literal))
			{
				driver()->push(localname, _prstTxWarp_reader.get_reader(&t()->prstTxWarp.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_text_noAutofit_literal))
			{
				driver()->push(localname, _noAutofit_reader.get_reader(&t()->noAutofit.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_text_normAutofit_literal))
			{
				driver()->push(localname, _normAutofit_reader.get_reader(&t()->normAutofit.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_text_spAutoFit_literal))
			{
				driver()->push(localname, _spAutoFit_reader.get_reader(&t()->spAutoFit.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_text_scene3d_literal))
			{
				driver()->push(localname, _scene3d_reader.get_reader(&t()->scene3d.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_text_sp3d_literal))
			{
				driver()->push(localname, _sp3d_reader.get_reader(&t()->sp3d.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_text_flatTx_literal))
			{
				driver()->push(localname, _flatTx_reader.get_reader(&t()->flatTx.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_text_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_TextBodyProperties_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_text_rot_literal))
			{
				driver()->context()->parse(value, t()->rot.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_text_spcFirstLastPara_literal))
			{
				driver()->context()->parse(value, t()->spcFirstLastPara.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_text_vertOverflow_literal))
			{
				driver()->context()->parse(value, t()->vertOverflow.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_text_horzOverflow_literal))
			{
				driver()->context()->parse(value, t()->horzOverflow.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_text_vert_literal))
			{
				driver()->context()->parse(value, t()->vert.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_text_wrap_literal))
			{
				driver()->context()->parse(value, t()->wrap.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_text_lIns_literal))
			{
				driver()->context()->parse(value, t()->lIns.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_text_tIns_literal))
			{
				driver()->context()->parse(value, t()->tIns.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_text_rIns_literal))
			{
				driver()->context()->parse(value, t()->rIns.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_text_bIns_literal))
			{
				driver()->context()->parse(value, t()->bIns.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_text_numCol_literal))
			{
				driver()->context()->parse(value, t()->numCol.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_text_spcCol_literal))
			{
				driver()->context()->parse(value, t()->spcCol.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_text_rtlCol_literal))
			{
				driver()->context()->parse(value, t()->rtlCol.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_text_fromWordArt_literal))
			{
				driver()->context()->parse(value, t()->fromWordArt.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_text_anchor_literal))
			{
				driver()->context()->parse(value, t()->anchor.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_text_anchorCtr_literal))
			{
				driver()->context()->parse(value, t()->anchorCtr.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_text_forceAA_literal))
			{
				driver()->context()->parse(value, t()->forceAA.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_text_upright_literal))
			{
				driver()->context()->parse(value, t()->upright);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_text_compatLnSpc_literal))
			{
				driver()->context()->parse(value, t()->compatLnSpc.getset());
				return;
			}
		}
		void CT_TextListStyle_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_text_defPPr_literal))
			{
				driver()->push(localname, _defPPr_reader.get_reader(&t()->defPPr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_text_lvl1pPr_literal))
			{
				driver()->push(localname, _lvl1pPr_reader.get_reader(&t()->lvl1pPr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_text_lvl2pPr_literal))
			{
				driver()->push(localname, _lvl2pPr_reader.get_reader(&t()->lvl2pPr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_text_lvl3pPr_literal))
			{
				driver()->push(localname, _lvl3pPr_reader.get_reader(&t()->lvl3pPr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_text_lvl4pPr_literal))
			{
				driver()->push(localname, _lvl4pPr_reader.get_reader(&t()->lvl4pPr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_text_lvl5pPr_literal))
			{
				driver()->push(localname, _lvl5pPr_reader.get_reader(&t()->lvl5pPr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_text_lvl6pPr_literal))
			{
				driver()->push(localname, _lvl6pPr_reader.get_reader(&t()->lvl6pPr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_text_lvl7pPr_literal))
			{
				driver()->push(localname, _lvl7pPr_reader.get_reader(&t()->lvl7pPr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_text_lvl8pPr_literal))
			{
				driver()->push(localname, _lvl8pPr_reader.get_reader(&t()->lvl8pPr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_text_lvl9pPr_literal))
			{
				driver()->push(localname, _lvl9pPr_reader.get_reader(&t()->lvl9pPr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_text_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_TextParagraph_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_text_pPr_literal))
			{
				driver()->push(localname, _pPr_reader.get_reader(&t()->pPr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_text_r_literal))
			{
				driver()->push(localname, _r_reader.get_reader(&t()->r.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_text_br_literal))
			{
				driver()->push(localname, _br_reader.get_reader(&t()->br.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_text_fld_literal))
			{
				driver()->push(localname, _fld_reader.get_reader(&t()->fld.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_text_endParaRPr_literal))
			{
				driver()->push(localname, _endParaRPr_reader.get_reader(&t()->endParaRPr.getset()));
				return;
			}
		}
		void CT_TextBody_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_text_bodyPr_literal))
			{
				driver()->push(localname, _bodyPr_reader.get_reader(&t()->bodyPr));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_text_lstStyle_literal))
			{
				driver()->push(localname, _lstStyle_reader.get_reader(&t()->lstStyle.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_text_p_literal))
			{
				t()->p.resize(t()->p.size()+1);
				driver()->push(localname, _p_reader.get_reader(&t()->p.back()));
				return;
			}
		}
	}
}
