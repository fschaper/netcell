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


#include "dml-baseStylesheet_writers.hpp"
#include "dml-baseStylesheet_literals.hpp"

namespace drawingml
{
	namespace xio
	{
		void ST_StyleMatrixColumnIndex_writer::write_target_to(xml_writer& w) {
			w.write_element_value(context()->serialize(*t()));
		}

		void CT_ColorScheme_writer::write_target_to(xml_writer& w) {
			w.attribute(0, dml_baseStylesheet_name_literal, context()->serialize(t()->name));
			w.start_element(0, dml_baseStylesheet_dk1_literal);
			_dk1_writer.get_writer(context(), &t()->dk1)->write_target_to(w);
			w.end_element(0, dml_baseStylesheet_dk1_literal);
			w.start_element(0, dml_baseStylesheet_lt1_literal);
			_lt1_writer.get_writer(context(), &t()->lt1)->write_target_to(w);
			w.end_element(0, dml_baseStylesheet_lt1_literal);
			w.start_element(0, dml_baseStylesheet_dk2_literal);
			_dk2_writer.get_writer(context(), &t()->dk2)->write_target_to(w);
			w.end_element(0, dml_baseStylesheet_dk2_literal);
			w.start_element(0, dml_baseStylesheet_lt2_literal);
			_lt2_writer.get_writer(context(), &t()->lt2)->write_target_to(w);
			w.end_element(0, dml_baseStylesheet_lt2_literal);
			w.start_element(0, dml_baseStylesheet_accent1_literal);
			_accent1_writer.get_writer(context(), &t()->accent1)->write_target_to(w);
			w.end_element(0, dml_baseStylesheet_accent1_literal);
			w.start_element(0, dml_baseStylesheet_accent2_literal);
			_accent2_writer.get_writer(context(), &t()->accent2)->write_target_to(w);
			w.end_element(0, dml_baseStylesheet_accent2_literal);
			w.start_element(0, dml_baseStylesheet_accent3_literal);
			_accent3_writer.get_writer(context(), &t()->accent3)->write_target_to(w);
			w.end_element(0, dml_baseStylesheet_accent3_literal);
			w.start_element(0, dml_baseStylesheet_accent4_literal);
			_accent4_writer.get_writer(context(), &t()->accent4)->write_target_to(w);
			w.end_element(0, dml_baseStylesheet_accent4_literal);
			w.start_element(0, dml_baseStylesheet_accent5_literal);
			_accent5_writer.get_writer(context(), &t()->accent5)->write_target_to(w);
			w.end_element(0, dml_baseStylesheet_accent5_literal);
			w.start_element(0, dml_baseStylesheet_accent6_literal);
			_accent6_writer.get_writer(context(), &t()->accent6)->write_target_to(w);
			w.end_element(0, dml_baseStylesheet_accent6_literal);
			w.start_element(0, dml_baseStylesheet_hlink_literal);
			_hlink_writer.get_writer(context(), &t()->hlink)->write_target_to(w);
			w.end_element(0, dml_baseStylesheet_hlink_literal);
			w.start_element(0, dml_baseStylesheet_folHlink_literal);
			_folHlink_writer.get_writer(context(), &t()->folHlink)->write_target_to(w);
			w.end_element(0, dml_baseStylesheet_folHlink_literal);
			if (t()->extLst.present()) {
				w.start_element(0, dml_baseStylesheet_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, dml_baseStylesheet_extLst_literal);
			}
		}

		void CT_SupplementalFont_writer::write_target_to(xml_writer& w) {
			w.attribute(0, dml_baseStylesheet_script_literal, context()->serialize(t()->script));
			w.attribute(0, dml_baseStylesheet_typeface_literal, context()->serialize(t()->typeface));
		}

		void CT_FontCollection_writer::write_target_to(xml_writer& w) {
			w.start_element(0, dml_baseStylesheet_latin_literal);
			_latin_writer.get_writer(context(), &t()->latin)->write_target_to(w);
			w.end_element(0, dml_baseStylesheet_latin_literal);
			w.start_element(0, dml_baseStylesheet_ea_literal);
			_ea_writer.get_writer(context(), &t()->ea)->write_target_to(w);
			w.end_element(0, dml_baseStylesheet_ea_literal);
			w.start_element(0, dml_baseStylesheet_cs_literal);
			_cs_writer.get_writer(context(), &t()->cs)->write_target_to(w);
			w.end_element(0, dml_baseStylesheet_cs_literal);
			for (size_t sqi = 0; sqi<t()->font.size(); ++sqi) {
				w.start_element(0, dml_baseStylesheet_font_literal);
				_font_writer.get_writer(context(), &t()->font[sqi])->write_target_to(w);
				w.end_element(0, dml_baseStylesheet_font_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, dml_baseStylesheet_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, dml_baseStylesheet_extLst_literal);
			}
		}

		void CT_FontScheme_writer::write_target_to(xml_writer& w) {
			w.attribute(0, dml_baseStylesheet_name_literal, context()->serialize(t()->name));
			w.start_element(0, dml_baseStylesheet_majorFont_literal);
			_majorFont_writer.get_writer(context(), &t()->majorFont)->write_target_to(w);
			w.end_element(0, dml_baseStylesheet_majorFont_literal);
			w.start_element(0, dml_baseStylesheet_minorFont_literal);
			_minorFont_writer.get_writer(context(), &t()->minorFont)->write_target_to(w);
			w.end_element(0, dml_baseStylesheet_minorFont_literal);
			if (t()->extLst.present()) {
				w.start_element(0, dml_baseStylesheet_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, dml_baseStylesheet_extLst_literal);
			}
		}

		void CT_FillStyleList_writer::write_target_to(xml_writer& w) {
			if (t()->noFill.present()) {
				w.start_element(0, dml_baseStylesheet_noFill_literal);
				_noFill_writer.get_writer(context(), &t()->noFill.get())->write_target_to(w);
				w.end_element(0, dml_baseStylesheet_noFill_literal);
			}
			if (t()->solidFill.present()) {
				w.start_element(0, dml_baseStylesheet_solidFill_literal);
				_solidFill_writer.get_writer(context(), &t()->solidFill.get())->write_target_to(w);
				w.end_element(0, dml_baseStylesheet_solidFill_literal);
			}
			if (t()->gradFill.present()) {
				w.start_element(0, dml_baseStylesheet_gradFill_literal);
				_gradFill_writer.get_writer(context(), &t()->gradFill.get())->write_target_to(w);
				w.end_element(0, dml_baseStylesheet_gradFill_literal);
			}
			if (t()->blipFill.present()) {
				w.start_element(0, dml_baseStylesheet_blipFill_literal);
				_blipFill_writer.get_writer(context(), &t()->blipFill.get())->write_target_to(w);
				w.end_element(0, dml_baseStylesheet_blipFill_literal);
			}
			if (t()->pattFill.present()) {
				w.start_element(0, dml_baseStylesheet_pattFill_literal);
				_pattFill_writer.get_writer(context(), &t()->pattFill.get())->write_target_to(w);
				w.end_element(0, dml_baseStylesheet_pattFill_literal);
			}
			if (t()->grpFill.present()) {
				w.start_element(0, dml_baseStylesheet_grpFill_literal);
				_grpFill_writer.get_writer(context(), &t()->grpFill.get())->write_target_to(w);
				w.end_element(0, dml_baseStylesheet_grpFill_literal);
			}
		}

		void CT_LineStyleList_writer::write_target_to(xml_writer& w) {
			for (size_t sqi = 0; sqi<t()->ln.size(); ++sqi) {
				w.start_element(0, dml_baseStylesheet_ln_literal);
				_ln_writer.get_writer(context(), &t()->ln[sqi])->write_target_to(w);
				w.end_element(0, dml_baseStylesheet_ln_literal);
			}
		}

		void CT_EffectStyleItem_writer::write_target_to(xml_writer& w) {
			if (t()->effectLst.present()) {
				w.start_element(0, dml_baseStylesheet_effectLst_literal);
				_effectLst_writer.get_writer(context(), &t()->effectLst.get())->write_target_to(w);
				w.end_element(0, dml_baseStylesheet_effectLst_literal);
			}
			if (t()->effectDag.present()) {
				w.start_element(0, dml_baseStylesheet_effectDag_literal);
				_effectDag_writer.get_writer(context(), &t()->effectDag.get())->write_target_to(w);
				w.end_element(0, dml_baseStylesheet_effectDag_literal);
			}
			if (t()->scene3d.present()) {
				w.start_element(0, dml_baseStylesheet_scene3d_literal);
				_scene3d_writer.get_writer(context(), &t()->scene3d.get())->write_target_to(w);
				w.end_element(0, dml_baseStylesheet_scene3d_literal);
			}
			if (t()->sp3d.present()) {
				w.start_element(0, dml_baseStylesheet_sp3d_literal);
				_sp3d_writer.get_writer(context(), &t()->sp3d.get())->write_target_to(w);
				w.end_element(0, dml_baseStylesheet_sp3d_literal);
			}
		}

		void CT_EffectStyleList_writer::write_target_to(xml_writer& w) {
			for (size_t sqi = 0; sqi<t()->effectStyle.size(); ++sqi) {
				w.start_element(0, dml_baseStylesheet_effectStyle_literal);
				_effectStyle_writer.get_writer(context(), &t()->effectStyle[sqi])->write_target_to(w);
				w.end_element(0, dml_baseStylesheet_effectStyle_literal);
			}
		}

		void CT_BackgroundFillStyleList_writer::write_target_to(xml_writer& w) {
			if (t()->noFill.present()) {
				w.start_element(0, dml_baseStylesheet_noFill_literal);
				_noFill_writer.get_writer(context(), &t()->noFill.get())->write_target_to(w);
				w.end_element(0, dml_baseStylesheet_noFill_literal);
			}
			if (t()->solidFill.present()) {
				w.start_element(0, dml_baseStylesheet_solidFill_literal);
				_solidFill_writer.get_writer(context(), &t()->solidFill.get())->write_target_to(w);
				w.end_element(0, dml_baseStylesheet_solidFill_literal);
			}
			if (t()->gradFill.present()) {
				w.start_element(0, dml_baseStylesheet_gradFill_literal);
				_gradFill_writer.get_writer(context(), &t()->gradFill.get())->write_target_to(w);
				w.end_element(0, dml_baseStylesheet_gradFill_literal);
			}
			if (t()->blipFill.present()) {
				w.start_element(0, dml_baseStylesheet_blipFill_literal);
				_blipFill_writer.get_writer(context(), &t()->blipFill.get())->write_target_to(w);
				w.end_element(0, dml_baseStylesheet_blipFill_literal);
			}
			if (t()->pattFill.present()) {
				w.start_element(0, dml_baseStylesheet_pattFill_literal);
				_pattFill_writer.get_writer(context(), &t()->pattFill.get())->write_target_to(w);
				w.end_element(0, dml_baseStylesheet_pattFill_literal);
			}
			if (t()->grpFill.present()) {
				w.start_element(0, dml_baseStylesheet_grpFill_literal);
				_grpFill_writer.get_writer(context(), &t()->grpFill.get())->write_target_to(w);
				w.end_element(0, dml_baseStylesheet_grpFill_literal);
			}
		}

		void CT_StyleMatrix_writer::write_target_to(xml_writer& w) {
			if (t()->name != "")
				w.attribute(0, dml_baseStylesheet_name_literal, context()->serialize(t()->name));
			w.start_element(0, dml_baseStylesheet_fillStyleLst_literal);
			_fillStyleLst_writer.get_writer(context(), &t()->fillStyleLst)->write_target_to(w);
			w.end_element(0, dml_baseStylesheet_fillStyleLst_literal);
			w.start_element(0, dml_baseStylesheet_lnStyleLst_literal);
			_lnStyleLst_writer.get_writer(context(), &t()->lnStyleLst)->write_target_to(w);
			w.end_element(0, dml_baseStylesheet_lnStyleLst_literal);
			w.start_element(0, dml_baseStylesheet_effectStyleLst_literal);
			_effectStyleLst_writer.get_writer(context(), &t()->effectStyleLst)->write_target_to(w);
			w.end_element(0, dml_baseStylesheet_effectStyleLst_literal);
			w.start_element(0, dml_baseStylesheet_bgFillStyleLst_literal);
			_bgFillStyleLst_writer.get_writer(context(), &t()->bgFillStyleLst)->write_target_to(w);
			w.end_element(0, dml_baseStylesheet_bgFillStyleLst_literal);
		}

		void CT_BaseStyles_writer::write_target_to(xml_writer& w) {
			w.start_element(0, dml_baseStylesheet_clrScheme_literal);
			_clrScheme_writer.get_writer(context(), &t()->clrScheme)->write_target_to(w);
			w.end_element(0, dml_baseStylesheet_clrScheme_literal);
			w.start_element(0, dml_baseStylesheet_fontScheme_literal);
			_fontScheme_writer.get_writer(context(), &t()->fontScheme)->write_target_to(w);
			w.end_element(0, dml_baseStylesheet_fontScheme_literal);
			w.start_element(0, dml_baseStylesheet_fmtScheme_literal);
			_fmtScheme_writer.get_writer(context(), &t()->fmtScheme)->write_target_to(w);
			w.end_element(0, dml_baseStylesheet_fmtScheme_literal);
			if (t()->extLst.present()) {
				w.start_element(0, dml_baseStylesheet_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, dml_baseStylesheet_extLst_literal);
			}
		}

		void CT_CustomColor_writer::write_target_to(xml_writer& w) {
			if (t()->name != "")
				w.attribute(0, dml_baseStylesheet_name_literal, context()->serialize(t()->name));
			if (t()->scrgbClr.present()) {
				w.start_element(0, dml_baseStylesheet_scrgbClr_literal);
				_scrgbClr_writer.get_writer(context(), &t()->scrgbClr.get())->write_target_to(w);
				w.end_element(0, dml_baseStylesheet_scrgbClr_literal);
			}
			if (t()->srgbClr.present()) {
				w.start_element(0, dml_baseStylesheet_srgbClr_literal);
				_srgbClr_writer.get_writer(context(), &t()->srgbClr.get())->write_target_to(w);
				w.end_element(0, dml_baseStylesheet_srgbClr_literal);
			}
			if (t()->hslClr.present()) {
				w.start_element(0, dml_baseStylesheet_hslClr_literal);
				_hslClr_writer.get_writer(context(), &t()->hslClr.get())->write_target_to(w);
				w.end_element(0, dml_baseStylesheet_hslClr_literal);
			}
			if (t()->sysClr.present()) {
				w.start_element(0, dml_baseStylesheet_sysClr_literal);
				_sysClr_writer.get_writer(context(), &t()->sysClr.get())->write_target_to(w);
				w.end_element(0, dml_baseStylesheet_sysClr_literal);
			}
			if (t()->schemeClr.present()) {
				w.start_element(0, dml_baseStylesheet_schemeClr_literal);
				_schemeClr_writer.get_writer(context(), &t()->schemeClr.get())->write_target_to(w);
				w.end_element(0, dml_baseStylesheet_schemeClr_literal);
			}
			if (t()->prstClr.present()) {
				w.start_element(0, dml_baseStylesheet_prstClr_literal);
				_prstClr_writer.get_writer(context(), &t()->prstClr.get())->write_target_to(w);
				w.end_element(0, dml_baseStylesheet_prstClr_literal);
			}
		}

		void CT_CustomColorList_writer::write_target_to(xml_writer& w) {
			for (size_t sqi = 0; sqi<t()->custClr.size(); ++sqi) {
				w.start_element(0, dml_baseStylesheet_custClr_literal);
				_custClr_writer.get_writer(context(), &t()->custClr[sqi])->write_target_to(w);
				w.end_element(0, dml_baseStylesheet_custClr_literal);
			}
		}

	}
}
