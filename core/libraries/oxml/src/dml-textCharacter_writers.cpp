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


#include "dml-textCharacter_writers.hpp"
#include "dml-textCharacter_literals.hpp"

namespace drawingml
{
	namespace xio
	{
		void ST_TextFontSize_writer::write_target_to(xml_writer& w) {
			w.write_element_value(context()->serialize(*t()));
		}

		void ST_TextTypeface_writer::write_target_to(xml_writer& w) {
			w.write_element_value(context()->serialize(*t()));
		}

		void ST_Panose_writer::write_target_to(xml_writer& w) {
			w.write_element_value(context()->serialize(*t()));
		}

		void CT_TextFont_writer::write_target_to(xml_writer& w) {
			if (t()->typeface.present())
				w.attribute(0, dml_textCharacter_typeface_literal, context()->serialize(t()->typeface.get()));
			if (t()->panose.present())
				w.attribute(0, dml_textCharacter_panose_literal, context()->serialize(t()->panose.get()));
			if (t()->pitchFamily != 0)
				w.attribute(0, dml_textCharacter_pitchFamily_literal, context()->serialize(t()->pitchFamily));
			if (t()->charset != 1)
				w.attribute(0, dml_textCharacter_charset_literal, context()->serialize(t()->charset));
		}

		void CT_TextUnderlineLineFollowText_writer::write_target_to(xml_writer& w) {
		}

		void CT_TextUnderlineFillFollowText_writer::write_target_to(xml_writer& w) {
		}

		void CT_TextUnderlineFillGroupWrapper_writer::write_target_to(xml_writer& w) {
			if (t()->noFill.present()) {
				w.start_element(0, dml_textCharacter_noFill_literal);
				_noFill_writer.get_writer(context(), &t()->noFill.get())->write_target_to(w);
				w.end_element(0, dml_textCharacter_noFill_literal);
			}
			if (t()->solidFill.present()) {
				w.start_element(0, dml_textCharacter_solidFill_literal);
				_solidFill_writer.get_writer(context(), &t()->solidFill.get())->write_target_to(w);
				w.end_element(0, dml_textCharacter_solidFill_literal);
			}
			if (t()->gradFill.present()) {
				w.start_element(0, dml_textCharacter_gradFill_literal);
				_gradFill_writer.get_writer(context(), &t()->gradFill.get())->write_target_to(w);
				w.end_element(0, dml_textCharacter_gradFill_literal);
			}
			if (t()->blipFill.present()) {
				w.start_element(0, dml_textCharacter_blipFill_literal);
				_blipFill_writer.get_writer(context(), &t()->blipFill.get())->write_target_to(w);
				w.end_element(0, dml_textCharacter_blipFill_literal);
			}
			if (t()->pattFill.present()) {
				w.start_element(0, dml_textCharacter_pattFill_literal);
				_pattFill_writer.get_writer(context(), &t()->pattFill.get())->write_target_to(w);
				w.end_element(0, dml_textCharacter_pattFill_literal);
			}
			if (t()->grpFill.present()) {
				w.start_element(0, dml_textCharacter_grpFill_literal);
				_grpFill_writer.get_writer(context(), &t()->grpFill.get())->write_target_to(w);
				w.end_element(0, dml_textCharacter_grpFill_literal);
			}
		}

		void ST_TextLanguageID_writer::write_target_to(xml_writer& w) {
			w.write_element_value(context()->serialize(*t()));
		}

		void ST_TextNonNegativePoint_writer::write_target_to(xml_writer& w) {
			w.write_element_value(context()->serialize(*t()));
		}

		void ST_TextPoint_writer::write_target_to(xml_writer& w) {
			w.write_element_value(context()->serialize(*t()));
		}

		void CT_TextCharacterProperties_writer::write_target_to(xml_writer& w) {
			if (t()->kumimoji.present())
				w.attribute(0, dml_textCharacter_kumimoji_literal, context()->serialize(t()->kumimoji.get()));
			if (t()->lang.present())
				w.attribute(0, dml_textCharacter_lang_literal, context()->serialize(t()->lang.get()));
			if (t()->altLang.present())
				w.attribute(0, dml_textCharacter_altLang_literal, context()->serialize(t()->altLang.get()));
			if (t()->sz.present())
				w.attribute(0, dml_textCharacter_sz_literal, context()->serialize(t()->sz.get()));
			if (t()->b.present())
				w.attribute(0, dml_textCharacter_b_literal, context()->serialize(t()->b.get()));
			if (t()->i.present())
				w.attribute(0, dml_textCharacter_i_literal, context()->serialize(t()->i.get()));
			if (t()->u.present())
				w.attribute(0, dml_textCharacter_u_literal, context()->serialize(t()->u.get()));
			if (t()->strike.present())
				w.attribute(0, dml_textCharacter_strike_literal, context()->serialize(t()->strike.get()));
			if (t()->kern.present())
				w.attribute(0, dml_textCharacter_kern_literal, context()->serialize(t()->kern.get()));
			if (t()->cap.present())
				w.attribute(0, dml_textCharacter_cap_literal, context()->serialize(t()->cap.get()));
			if (t()->spc.present())
				w.attribute(0, dml_textCharacter_spc_literal, context()->serialize(t()->spc.get()));
			if (t()->normalizeH.present())
				w.attribute(0, dml_textCharacter_normalizeH_literal, context()->serialize(t()->normalizeH.get()));
			if (t()->baseline.present())
				w.attribute(0, dml_textCharacter_baseline_literal, context()->serialize(t()->baseline.get()));
			if (t()->noProof.present())
				w.attribute(0, dml_textCharacter_noProof_literal, context()->serialize(t()->noProof.get()));
			if (t()->dirty != true)
				w.attribute(0, dml_textCharacter_dirty_literal, context()->serialize(t()->dirty));
			if (t()->err != false)
				w.attribute(0, dml_textCharacter_err_literal, context()->serialize(t()->err));
			if (t()->smtClean != true)
				w.attribute(0, dml_textCharacter_smtClean_literal, context()->serialize(t()->smtClean));
			if (t()->smtId != 0U)
				w.attribute(0, dml_textCharacter_smtId_literal, context()->serialize(t()->smtId));
			if (t()->bmk.present())
				w.attribute(0, dml_textCharacter_bmk_literal, context()->serialize(t()->bmk.get()));
			if (t()->ln.present()) {
				w.start_element(0, dml_textCharacter_ln_literal);
				_ln_writer.get_writer(context(), &t()->ln.get())->write_target_to(w);
				w.end_element(0, dml_textCharacter_ln_literal);
			}
			if (t()->noFill.present()) {
				w.start_element(0, dml_textCharacter_noFill_literal);
				_noFill_writer.get_writer(context(), &t()->noFill.get())->write_target_to(w);
				w.end_element(0, dml_textCharacter_noFill_literal);
			}
			if (t()->solidFill.present()) {
				w.start_element(0, dml_textCharacter_solidFill_literal);
				_solidFill_writer.get_writer(context(), &t()->solidFill.get())->write_target_to(w);
				w.end_element(0, dml_textCharacter_solidFill_literal);
			}
			if (t()->gradFill.present()) {
				w.start_element(0, dml_textCharacter_gradFill_literal);
				_gradFill_writer.get_writer(context(), &t()->gradFill.get())->write_target_to(w);
				w.end_element(0, dml_textCharacter_gradFill_literal);
			}
			if (t()->blipFill.present()) {
				w.start_element(0, dml_textCharacter_blipFill_literal);
				_blipFill_writer.get_writer(context(), &t()->blipFill.get())->write_target_to(w);
				w.end_element(0, dml_textCharacter_blipFill_literal);
			}
			if (t()->pattFill.present()) {
				w.start_element(0, dml_textCharacter_pattFill_literal);
				_pattFill_writer.get_writer(context(), &t()->pattFill.get())->write_target_to(w);
				w.end_element(0, dml_textCharacter_pattFill_literal);
			}
			if (t()->grpFill.present()) {
				w.start_element(0, dml_textCharacter_grpFill_literal);
				_grpFill_writer.get_writer(context(), &t()->grpFill.get())->write_target_to(w);
				w.end_element(0, dml_textCharacter_grpFill_literal);
			}
			if (t()->effectLst.present()) {
				w.start_element(0, dml_textCharacter_effectLst_literal);
				_effectLst_writer.get_writer(context(), &t()->effectLst.get())->write_target_to(w);
				w.end_element(0, dml_textCharacter_effectLst_literal);
			}
			if (t()->effectDag.present()) {
				w.start_element(0, dml_textCharacter_effectDag_literal);
				_effectDag_writer.get_writer(context(), &t()->effectDag.get())->write_target_to(w);
				w.end_element(0, dml_textCharacter_effectDag_literal);
			}
			if (t()->highlight.present()) {
				w.start_element(0, dml_textCharacter_highlight_literal);
				_highlight_writer.get_writer(context(), &t()->highlight.get())->write_target_to(w);
				w.end_element(0, dml_textCharacter_highlight_literal);
			}
			if (t()->uLnTx.present()) {
				w.start_element(0, dml_textCharacter_uLnTx_literal);
				_uLnTx_writer.get_writer(context(), &t()->uLnTx.get())->write_target_to(w);
				w.end_element(0, dml_textCharacter_uLnTx_literal);
			}
			if (t()->uLn.present()) {
				w.start_element(0, dml_textCharacter_uLn_literal);
				_uLn_writer.get_writer(context(), &t()->uLn.get())->write_target_to(w);
				w.end_element(0, dml_textCharacter_uLn_literal);
			}
			if (t()->uFillTx.present()) {
				w.start_element(0, dml_textCharacter_uFillTx_literal);
				_uFillTx_writer.get_writer(context(), &t()->uFillTx.get())->write_target_to(w);
				w.end_element(0, dml_textCharacter_uFillTx_literal);
			}
			if (t()->uFill.present()) {
				w.start_element(0, dml_textCharacter_uFill_literal);
				_uFill_writer.get_writer(context(), &t()->uFill.get())->write_target_to(w);
				w.end_element(0, dml_textCharacter_uFill_literal);
			}
			if (t()->latin.present()) {
				w.start_element(0, dml_textCharacter_latin_literal);
				_latin_writer.get_writer(context(), &t()->latin.get())->write_target_to(w);
				w.end_element(0, dml_textCharacter_latin_literal);
			}
			if (t()->ea.present()) {
				w.start_element(0, dml_textCharacter_ea_literal);
				_ea_writer.get_writer(context(), &t()->ea.get())->write_target_to(w);
				w.end_element(0, dml_textCharacter_ea_literal);
			}
			if (t()->cs.present()) {
				w.start_element(0, dml_textCharacter_cs_literal);
				_cs_writer.get_writer(context(), &t()->cs.get())->write_target_to(w);
				w.end_element(0, dml_textCharacter_cs_literal);
			}
			if (t()->sym.present()) {
				w.start_element(0, dml_textCharacter_sym_literal);
				_sym_writer.get_writer(context(), &t()->sym.get())->write_target_to(w);
				w.end_element(0, dml_textCharacter_sym_literal);
			}
			if (t()->hlinkClick.present()) {
				w.start_element(0, dml_textCharacter_hlinkClick_literal);
				_hlinkClick_writer.get_writer(context(), &t()->hlinkClick.get())->write_target_to(w);
				w.end_element(0, dml_textCharacter_hlinkClick_literal);
			}
			if (t()->hlinkMouseOver.present()) {
				w.start_element(0, dml_textCharacter_hlinkMouseOver_literal);
				_hlinkMouseOver_writer.get_writer(context(), &t()->hlinkMouseOver.get())->write_target_to(w);
				w.end_element(0, dml_textCharacter_hlinkMouseOver_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, dml_textCharacter_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, dml_textCharacter_extLst_literal);
			}
		}

	}
}
