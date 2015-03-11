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


#include "dml-textParagraph_writers.hpp"
#include "dml-textParagraph_literals.hpp"

namespace drawingml
{
	namespace xio
	{
		void ST_TextSpacingPercent_writer::write_target_to(xml_writer& w) {
			ST_Percentage_writer::write_target_to(w);
		}

		void CT_TextSpacingPercent_writer::write_target_to(xml_writer& w) {
			w.attribute(0, dml_textParagraph_val_literal, context()->serialize(t()->val));
		}

		void ST_TextSpacingPoint_writer::write_target_to(xml_writer& w) {
			w.write_element_value(context()->serialize(*t()));
		}

		void CT_TextSpacingPoint_writer::write_target_to(xml_writer& w) {
			w.attribute(0, dml_textParagraph_val_literal, context()->serialize(t()->val));
		}

		void CT_TextSpacing_writer::write_target_to(xml_writer& w) {
			if (t()->spcPct.present()) {
				w.start_element(0, dml_textParagraph_spcPct_literal);
				_spcPct_writer.get_writer(context(), &t()->spcPct.get())->write_target_to(w);
				w.end_element(0, dml_textParagraph_spcPct_literal);
			}
			if (t()->spcPts.present()) {
				w.start_element(0, dml_textParagraph_spcPts_literal);
				_spcPts_writer.get_writer(context(), &t()->spcPts.get())->write_target_to(w);
				w.end_element(0, dml_textParagraph_spcPts_literal);
			}
		}

		void CT_TextTabStop_writer::write_target_to(xml_writer& w) {
			if (t()->pos.present())
				w.attribute(0, dml_textParagraph_pos_literal, context()->serialize(t()->pos.get()));
			if (t()->algn.present())
				w.attribute(0, dml_textParagraph_algn_literal, context()->serialize(t()->algn.get()));
		}

		void CT_TextTabStopList_writer::write_target_to(xml_writer& w) {
			for (size_t sqi = 0; sqi<t()->tab.size(); ++sqi) {
				w.start_element(0, dml_textParagraph_tab_literal);
				_tab_writer.get_writer(context(), &t()->tab[sqi])->write_target_to(w);
				w.end_element(0, dml_textParagraph_tab_literal);
			}
		}

		void ST_TextMargin_writer::write_target_to(xml_writer& w) {
			ST_Coordinate32_writer::write_target_to(w);
		}

		void ST_TextIndentLevelType_writer::write_target_to(xml_writer& w) {
			w.write_element_value(context()->serialize(*t()));
		}

		void ST_TextIndent_writer::write_target_to(xml_writer& w) {
			ST_Coordinate32_writer::write_target_to(w);
		}

		void CT_TextParagraphProperties_writer::write_target_to(xml_writer& w) {
			if (t()->marL.present())
				w.attribute(0, dml_textParagraph_marL_literal, context()->serialize(t()->marL.get()));
			if (t()->marR.present())
				w.attribute(0, dml_textParagraph_marR_literal, context()->serialize(t()->marR.get()));
			if (t()->lvl.present())
				w.attribute(0, dml_textParagraph_lvl_literal, context()->serialize(t()->lvl.get()));
			if (t()->indent.present())
				w.attribute(0, dml_textParagraph_indent_literal, context()->serialize(t()->indent.get()));
			if (t()->algn.present())
				w.attribute(0, dml_textParagraph_algn_literal, context()->serialize(t()->algn.get()));
			if (t()->defTabSz.present())
				w.attribute(0, dml_textParagraph_defTabSz_literal, context()->serialize(t()->defTabSz.get()));
			if (t()->rtl.present())
				w.attribute(0, dml_textParagraph_rtl_literal, context()->serialize(t()->rtl.get()));
			if (t()->eaLnBrk.present())
				w.attribute(0, dml_textParagraph_eaLnBrk_literal, context()->serialize(t()->eaLnBrk.get()));
			if (t()->fontAlgn.present())
				w.attribute(0, dml_textParagraph_fontAlgn_literal, context()->serialize(t()->fontAlgn.get()));
			if (t()->latinLnBrk.present())
				w.attribute(0, dml_textParagraph_latinLnBrk_literal, context()->serialize(t()->latinLnBrk.get()));
			if (t()->hangingPunct.present())
				w.attribute(0, dml_textParagraph_hangingPunct_literal, context()->serialize(t()->hangingPunct.get()));
			if (t()->lnSpc.present()) {
				w.start_element(0, dml_textParagraph_lnSpc_literal);
				_lnSpc_writer.get_writer(context(), &t()->lnSpc.get())->write_target_to(w);
				w.end_element(0, dml_textParagraph_lnSpc_literal);
			}
			if (t()->spcBef.present()) {
				w.start_element(0, dml_textParagraph_spcBef_literal);
				_spcBef_writer.get_writer(context(), &t()->spcBef.get())->write_target_to(w);
				w.end_element(0, dml_textParagraph_spcBef_literal);
			}
			if (t()->spcAft.present()) {
				w.start_element(0, dml_textParagraph_spcAft_literal);
				_spcAft_writer.get_writer(context(), &t()->spcAft.get())->write_target_to(w);
				w.end_element(0, dml_textParagraph_spcAft_literal);
			}
			if (t()->buClrTx.present()) {
				w.start_element(0, dml_textParagraph_buClrTx_literal);
				_buClrTx_writer.get_writer(context(), &t()->buClrTx.get())->write_target_to(w);
				w.end_element(0, dml_textParagraph_buClrTx_literal);
			}
			if (t()->buClr.present()) {
				w.start_element(0, dml_textParagraph_buClr_literal);
				_buClr_writer.get_writer(context(), &t()->buClr.get())->write_target_to(w);
				w.end_element(0, dml_textParagraph_buClr_literal);
			}
			if (t()->buSzTx.present()) {
				w.start_element(0, dml_textParagraph_buSzTx_literal);
				_buSzTx_writer.get_writer(context(), &t()->buSzTx.get())->write_target_to(w);
				w.end_element(0, dml_textParagraph_buSzTx_literal);
			}
			if (t()->buSzPct.present()) {
				w.start_element(0, dml_textParagraph_buSzPct_literal);
				_buSzPct_writer.get_writer(context(), &t()->buSzPct.get())->write_target_to(w);
				w.end_element(0, dml_textParagraph_buSzPct_literal);
			}
			if (t()->buSzPts.present()) {
				w.start_element(0, dml_textParagraph_buSzPts_literal);
				_buSzPts_writer.get_writer(context(), &t()->buSzPts.get())->write_target_to(w);
				w.end_element(0, dml_textParagraph_buSzPts_literal);
			}
			if (t()->buFontTx.present()) {
				w.start_element(0, dml_textParagraph_buFontTx_literal);
				_buFontTx_writer.get_writer(context(), &t()->buFontTx.get())->write_target_to(w);
				w.end_element(0, dml_textParagraph_buFontTx_literal);
			}
			if (t()->buFont.present()) {
				w.start_element(0, dml_textParagraph_buFont_literal);
				_buFont_writer.get_writer(context(), &t()->buFont.get())->write_target_to(w);
				w.end_element(0, dml_textParagraph_buFont_literal);
			}
			if (t()->buNone.present()) {
				w.start_element(0, dml_textParagraph_buNone_literal);
				_buNone_writer.get_writer(context(), &t()->buNone.get())->write_target_to(w);
				w.end_element(0, dml_textParagraph_buNone_literal);
			}
			if (t()->buAutoNum.present()) {
				w.start_element(0, dml_textParagraph_buAutoNum_literal);
				_buAutoNum_writer.get_writer(context(), &t()->buAutoNum.get())->write_target_to(w);
				w.end_element(0, dml_textParagraph_buAutoNum_literal);
			}
			if (t()->buChar.present()) {
				w.start_element(0, dml_textParagraph_buChar_literal);
				_buChar_writer.get_writer(context(), &t()->buChar.get())->write_target_to(w);
				w.end_element(0, dml_textParagraph_buChar_literal);
			}
			if (t()->buBlip.present()) {
				w.start_element(0, dml_textParagraph_buBlip_literal);
				_buBlip_writer.get_writer(context(), &t()->buBlip.get())->write_target_to(w);
				w.end_element(0, dml_textParagraph_buBlip_literal);
			}
			if (t()->tabLst.present()) {
				w.start_element(0, dml_textParagraph_tabLst_literal);
				_tabLst_writer.get_writer(context(), &t()->tabLst.get())->write_target_to(w);
				w.end_element(0, dml_textParagraph_tabLst_literal);
			}
			if (t()->defRPr.present()) {
				w.start_element(0, dml_textParagraph_defRPr_literal);
				_defRPr_writer.get_writer(context(), &t()->defRPr.get())->write_target_to(w);
				w.end_element(0, dml_textParagraph_defRPr_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, dml_textParagraph_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, dml_textParagraph_extLst_literal);
			}
		}

		void CT_TextLineBreak_writer::write_target_to(xml_writer& w) {
			if (t()->rPr.present()) {
				w.start_element(0, dml_textParagraph_rPr_literal);
				_rPr_writer.get_writer(context(), &t()->rPr.get())->write_target_to(w);
				w.end_element(0, dml_textParagraph_rPr_literal);
			}
		}

		void CT_TextField_writer::write_target_to(xml_writer& w) {
			w.attribute(0, dml_textParagraph_id_literal, context()->serialize(t()->id));
			if (t()->type.present())
				w.attribute(0, dml_textParagraph_type_literal, context()->serialize(t()->type.get()));
			if (t()->rPr.present()) {
				w.start_element(0, dml_textParagraph_rPr_literal);
				_rPr_writer.get_writer(context(), &t()->rPr.get())->write_target_to(w);
				w.end_element(0, dml_textParagraph_rPr_literal);
			}
			if (t()->pPr.present()) {
				w.start_element(0, dml_textParagraph_pPr_literal);
				_pPr_writer.get_writer(context(), &t()->pPr.get())->write_target_to(w);
				w.end_element(0, dml_textParagraph_pPr_literal);
			}
			if (t()->t.present()) {
				w.start_element(0, dml_textParagraph_t_literal);
				w.write_element_value(context()->serialize(t()->t.get()));
				w.end_element(0, dml_textParagraph_t_literal);
			}
		}

	}
}
