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


#include "dml-textParagraph_readers.hpp"
#include "dml-textParagraph_literals.hpp"
#include <xio/xml/binding/driver.hpp>

namespace drawingml
{
	namespace xio
	{
		void CT_TextSpacingPercent_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_textParagraph_val_literal))
			{
				driver()->context()->parse(value, t()->val);
				return;
			}
		}
		void ST_TextSpacingPoint_reader::read_value(const xstring& val) {{ driver()->context()->parse(val, *t()); }}
		void CT_TextSpacingPoint_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_textParagraph_val_literal))
			{
				driver()->context()->parse(value, t()->val);
				return;
			}
		}
		void CT_TextSpacing_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_textParagraph_spcPct_literal))
			{
				driver()->push(localname, _spcPct_reader.get_reader(&t()->spcPct.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textParagraph_spcPts_literal))
			{
				driver()->push(localname, _spcPts_reader.get_reader(&t()->spcPts.getset()));
				return;
			}
		}
		void CT_TextTabStop_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_textParagraph_pos_literal))
			{
				driver()->context()->parse(value, t()->pos.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textParagraph_algn_literal))
			{
				driver()->context()->parse(value, t()->algn.getset());
				return;
			}
		}
		void CT_TextTabStopList_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_textParagraph_tab_literal))
			{
				t()->tab.resize(t()->tab.size()+1);
				driver()->push(localname, _tab_reader.get_reader(&t()->tab.back()));
				return;
			}
		}
		void ST_TextIndentLevelType_reader::read_value(const xstring& val) {{ driver()->context()->parse(val, *t()); }}
		void CT_TextParagraphProperties_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_textParagraph_lnSpc_literal))
			{
				driver()->push(localname, _lnSpc_reader.get_reader(&t()->lnSpc.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textParagraph_spcBef_literal))
			{
				driver()->push(localname, _spcBef_reader.get_reader(&t()->spcBef.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textParagraph_spcAft_literal))
			{
				driver()->push(localname, _spcAft_reader.get_reader(&t()->spcAft.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textParagraph_buClrTx_literal))
			{
				driver()->push(localname, _buClrTx_reader.get_reader(&t()->buClrTx.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textParagraph_buClr_literal))
			{
				driver()->push(localname, _buClr_reader.get_reader(&t()->buClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textParagraph_buSzTx_literal))
			{
				driver()->push(localname, _buSzTx_reader.get_reader(&t()->buSzTx.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textParagraph_buSzPct_literal))
			{
				driver()->push(localname, _buSzPct_reader.get_reader(&t()->buSzPct.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textParagraph_buSzPts_literal))
			{
				driver()->push(localname, _buSzPts_reader.get_reader(&t()->buSzPts.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textParagraph_buFontTx_literal))
			{
				driver()->push(localname, _buFontTx_reader.get_reader(&t()->buFontTx.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textParagraph_buFont_literal))
			{
				driver()->push(localname, _buFont_reader.get_reader(&t()->buFont.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textParagraph_buNone_literal))
			{
				driver()->push(localname, _buNone_reader.get_reader(&t()->buNone.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textParagraph_buAutoNum_literal))
			{
				driver()->push(localname, _buAutoNum_reader.get_reader(&t()->buAutoNum.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textParagraph_buChar_literal))
			{
				driver()->push(localname, _buChar_reader.get_reader(&t()->buChar.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textParagraph_buBlip_literal))
			{
				driver()->push(localname, _buBlip_reader.get_reader(&t()->buBlip.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textParagraph_tabLst_literal))
			{
				driver()->push(localname, _tabLst_reader.get_reader(&t()->tabLst.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textParagraph_defRPr_literal))
			{
				driver()->push(localname, _defRPr_reader.get_reader(&t()->defRPr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textParagraph_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_TextParagraphProperties_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_textParagraph_marL_literal))
			{
				driver()->context()->parse(value, t()->marL.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textParagraph_marR_literal))
			{
				driver()->context()->parse(value, t()->marR.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textParagraph_lvl_literal))
			{
				driver()->context()->parse(value, t()->lvl.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textParagraph_indent_literal))
			{
				driver()->context()->parse(value, t()->indent.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textParagraph_algn_literal))
			{
				driver()->context()->parse(value, t()->algn.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textParagraph_defTabSz_literal))
			{
				driver()->context()->parse(value, t()->defTabSz.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textParagraph_rtl_literal))
			{
				driver()->context()->parse(value, t()->rtl.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textParagraph_eaLnBrk_literal))
			{
				driver()->context()->parse(value, t()->eaLnBrk.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textParagraph_fontAlgn_literal))
			{
				driver()->context()->parse(value, t()->fontAlgn.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textParagraph_latinLnBrk_literal))
			{
				driver()->context()->parse(value, t()->latinLnBrk.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textParagraph_hangingPunct_literal))
			{
				driver()->context()->parse(value, t()->hangingPunct.getset());
				return;
			}
		}
		void CT_TextLineBreak_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_textParagraph_rPr_literal))
			{
				driver()->push(localname, _rPr_reader.get_reader(&t()->rPr.getset()));
				return;
			}
		}
		void CT_TextField_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_textParagraph_rPr_literal))
			{
				driver()->push(localname, _rPr_reader.get_reader(&t()->rPr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textParagraph_pPr_literal))
			{
				driver()->push(localname, _pPr_reader.get_reader(&t()->pPr.getset()));
				return;
			}
		}
		void CT_TextField_reader::end_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname)
		{
			if (::xercesc::XMLString::equals(localname, dml_textParagraph_t_literal))
			{
				driver()->context()->parse(driver()->get_characters(), t()->t.getset());
				return;
			}
		}
		void CT_TextField_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_textParagraph_id_literal))
			{
				driver()->context()->parse(value, t()->id);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textParagraph_type_literal))
			{
				driver()->context()->parse(value, t()->type.getset());
				return;
			}
		}
	}
}
