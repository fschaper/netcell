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


#include "dml-textCharacter_readers.hpp"
#include "dml-textCharacter_literals.hpp"
#include <xio/xml/binding/driver.hpp>

namespace drawingml
{
	namespace xio
	{
		void ST_TextFontSize_reader::read_value(const xstring& val) {{ driver()->context()->parse(val, *t()); }}
		void ST_TextTypeface_reader::read_value(const xstring& val) {{ driver()->context()->parse(val, *t()); }}
		void ST_Panose_reader::read_value(const xstring& val) {{ driver()->context()->parse(val, *t()); }}
		void CT_TextFont_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_textCharacter_typeface_literal))
			{
				driver()->context()->parse(value, t()->typeface.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textCharacter_panose_literal))
			{
				driver()->context()->parse(value, t()->panose.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textCharacter_pitchFamily_literal))
			{
				driver()->context()->parse(value, t()->pitchFamily);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textCharacter_charset_literal))
			{
				driver()->context()->parse(value, t()->charset);
				return;
			}
		}
		void CT_TextUnderlineFillGroupWrapper_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_textCharacter_noFill_literal))
			{
				driver()->push(localname, _noFill_reader.get_reader(&t()->noFill.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textCharacter_solidFill_literal))
			{
				driver()->push(localname, _solidFill_reader.get_reader(&t()->solidFill.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textCharacter_gradFill_literal))
			{
				driver()->push(localname, _gradFill_reader.get_reader(&t()->gradFill.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textCharacter_blipFill_literal))
			{
				driver()->push(localname, _blipFill_reader.get_reader(&t()->blipFill.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textCharacter_pattFill_literal))
			{
				driver()->push(localname, _pattFill_reader.get_reader(&t()->pattFill.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textCharacter_grpFill_literal))
			{
				driver()->push(localname, _grpFill_reader.get_reader(&t()->grpFill.getset()));
				return;
			}
		}
		void ST_TextLanguageID_reader::read_value(const xstring& val) {{ driver()->context()->parse(val, *t()); }}
		void ST_TextNonNegativePoint_reader::read_value(const xstring& val) {{ driver()->context()->parse(val, *t()); }}
		void ST_TextPoint_reader::read_value(const xstring& val) {{ driver()->context()->parse(val, *t()); }}
		void CT_TextCharacterProperties_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_textCharacter_ln_literal))
			{
				driver()->push(localname, _ln_reader.get_reader(&t()->ln.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textCharacter_noFill_literal))
			{
				driver()->push(localname, _noFill_reader.get_reader(&t()->noFill.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textCharacter_solidFill_literal))
			{
				driver()->push(localname, _solidFill_reader.get_reader(&t()->solidFill.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textCharacter_gradFill_literal))
			{
				driver()->push(localname, _gradFill_reader.get_reader(&t()->gradFill.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textCharacter_blipFill_literal))
			{
				driver()->push(localname, _blipFill_reader.get_reader(&t()->blipFill.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textCharacter_pattFill_literal))
			{
				driver()->push(localname, _pattFill_reader.get_reader(&t()->pattFill.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textCharacter_grpFill_literal))
			{
				driver()->push(localname, _grpFill_reader.get_reader(&t()->grpFill.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textCharacter_effectLst_literal))
			{
				driver()->push(localname, _effectLst_reader.get_reader(&t()->effectLst.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textCharacter_effectDag_literal))
			{
				driver()->push(localname, _effectDag_reader.get_reader(&t()->effectDag.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textCharacter_highlight_literal))
			{
				driver()->push(localname, _highlight_reader.get_reader(&t()->highlight.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textCharacter_uLnTx_literal))
			{
				driver()->push(localname, _uLnTx_reader.get_reader(&t()->uLnTx.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textCharacter_uLn_literal))
			{
				driver()->push(localname, _uLn_reader.get_reader(&t()->uLn.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textCharacter_uFillTx_literal))
			{
				driver()->push(localname, _uFillTx_reader.get_reader(&t()->uFillTx.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textCharacter_uFill_literal))
			{
				driver()->push(localname, _uFill_reader.get_reader(&t()->uFill.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textCharacter_latin_literal))
			{
				driver()->push(localname, _latin_reader.get_reader(&t()->latin.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textCharacter_ea_literal))
			{
				driver()->push(localname, _ea_reader.get_reader(&t()->ea.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textCharacter_cs_literal))
			{
				driver()->push(localname, _cs_reader.get_reader(&t()->cs.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textCharacter_sym_literal))
			{
				driver()->push(localname, _sym_reader.get_reader(&t()->sym.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textCharacter_hlinkClick_literal))
			{
				driver()->push(localname, _hlinkClick_reader.get_reader(&t()->hlinkClick.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textCharacter_hlinkMouseOver_literal))
			{
				driver()->push(localname, _hlinkMouseOver_reader.get_reader(&t()->hlinkMouseOver.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textCharacter_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_TextCharacterProperties_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_textCharacter_kumimoji_literal))
			{
				driver()->context()->parse(value, t()->kumimoji.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textCharacter_lang_literal))
			{
				driver()->context()->parse(value, t()->lang.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textCharacter_altLang_literal))
			{
				driver()->context()->parse(value, t()->altLang.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textCharacter_sz_literal))
			{
				driver()->context()->parse(value, t()->sz.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textCharacter_b_literal))
			{
				driver()->context()->parse(value, t()->b.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textCharacter_i_literal))
			{
				driver()->context()->parse(value, t()->i.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textCharacter_u_literal))
			{
				driver()->context()->parse(value, t()->u.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textCharacter_strike_literal))
			{
				driver()->context()->parse(value, t()->strike.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textCharacter_kern_literal))
			{
				driver()->context()->parse(value, t()->kern.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textCharacter_cap_literal))
			{
				driver()->context()->parse(value, t()->cap.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textCharacter_spc_literal))
			{
				driver()->context()->parse(value, t()->spc.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textCharacter_normalizeH_literal))
			{
				driver()->context()->parse(value, t()->normalizeH.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textCharacter_baseline_literal))
			{
				driver()->context()->parse(value, t()->baseline.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textCharacter_noProof_literal))
			{
				driver()->context()->parse(value, t()->noProof.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textCharacter_dirty_literal))
			{
				driver()->context()->parse(value, t()->dirty);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textCharacter_err_literal))
			{
				driver()->context()->parse(value, t()->err);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textCharacter_smtClean_literal))
			{
				driver()->context()->parse(value, t()->smtClean);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textCharacter_smtId_literal))
			{
				driver()->context()->parse(value, t()->smtId);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_textCharacter_bmk_literal))
			{
				driver()->context()->parse(value, t()->bmk.getset());
				return;
			}
		}
	}
}
