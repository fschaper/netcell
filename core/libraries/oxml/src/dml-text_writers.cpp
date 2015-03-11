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


#include "dml-text_writers.hpp"
#include "dml-text_literals.hpp"

namespace drawingml
{
	namespace xio
	{
		void CT_TextNoAutofit_writer::write_target_to(xml_writer& w) {
		}

		void ST_TextFontScalePercent_writer::write_target_to(xml_writer& w) {
			ST_Percentage_writer::write_target_to(w);
		}

		void CT_TextNormalAutofit_writer::write_target_to(xml_writer& w) {
			if (t()->fontScale != 100000)
				w.attribute(0, dml_text_fontScale_literal, context()->serialize(t()->fontScale));
			if (t()->lnSpcReduction != 0)
				w.attribute(0, dml_text_lnSpcReduction_literal, context()->serialize(t()->lnSpcReduction));
		}

		void CT_TextShapeAutofit_writer::write_target_to(xml_writer& w) {
		}

		void ST_TextColumnCount_writer::write_target_to(xml_writer& w) {
			w.write_element_value(context()->serialize(*t()));
		}

		void CT_TextBodyProperties_writer::write_target_to(xml_writer& w) {
			if (t()->rot.present())
				w.attribute(0, dml_text_rot_literal, context()->serialize(t()->rot.get()));
			if (t()->spcFirstLastPara.present())
				w.attribute(0, dml_text_spcFirstLastPara_literal, context()->serialize(t()->spcFirstLastPara.get()));
			if (t()->vertOverflow.present())
				w.attribute(0, dml_text_vertOverflow_literal, context()->serialize(t()->vertOverflow.get()));
			if (t()->horzOverflow.present())
				w.attribute(0, dml_text_horzOverflow_literal, context()->serialize(t()->horzOverflow.get()));
			if (t()->vert.present())
				w.attribute(0, dml_text_vert_literal, context()->serialize(t()->vert.get()));
			if (t()->wrap.present())
				w.attribute(0, dml_text_wrap_literal, context()->serialize(t()->wrap.get()));
			if (t()->lIns.present())
				w.attribute(0, dml_text_lIns_literal, context()->serialize(t()->lIns.get()));
			if (t()->tIns.present())
				w.attribute(0, dml_text_tIns_literal, context()->serialize(t()->tIns.get()));
			if (t()->rIns.present())
				w.attribute(0, dml_text_rIns_literal, context()->serialize(t()->rIns.get()));
			if (t()->bIns.present())
				w.attribute(0, dml_text_bIns_literal, context()->serialize(t()->bIns.get()));
			if (t()->numCol.present())
				w.attribute(0, dml_text_numCol_literal, context()->serialize(t()->numCol.get()));
			if (t()->spcCol.present())
				w.attribute(0, dml_text_spcCol_literal, context()->serialize(t()->spcCol.get()));
			if (t()->rtlCol.present())
				w.attribute(0, dml_text_rtlCol_literal, context()->serialize(t()->rtlCol.get()));
			if (t()->fromWordArt.present())
				w.attribute(0, dml_text_fromWordArt_literal, context()->serialize(t()->fromWordArt.get()));
			if (t()->anchor.present())
				w.attribute(0, dml_text_anchor_literal, context()->serialize(t()->anchor.get()));
			if (t()->anchorCtr.present())
				w.attribute(0, dml_text_anchorCtr_literal, context()->serialize(t()->anchorCtr.get()));
			if (t()->forceAA.present())
				w.attribute(0, dml_text_forceAA_literal, context()->serialize(t()->forceAA.get()));
			if (t()->upright != false)
				w.attribute(0, dml_text_upright_literal, context()->serialize(t()->upright));
			if (t()->compatLnSpc.present())
				w.attribute(0, dml_text_compatLnSpc_literal, context()->serialize(t()->compatLnSpc.get()));
			if (t()->prstTxWarp.present()) {
				w.start_element(0, dml_text_prstTxWarp_literal);
				_prstTxWarp_writer.get_writer(context(), &t()->prstTxWarp.get())->write_target_to(w);
				w.end_element(0, dml_text_prstTxWarp_literal);
			}
			if (t()->noAutofit.present()) {
				w.start_element(0, dml_text_noAutofit_literal);
				_noAutofit_writer.get_writer(context(), &t()->noAutofit.get())->write_target_to(w);
				w.end_element(0, dml_text_noAutofit_literal);
			}
			if (t()->normAutofit.present()) {
				w.start_element(0, dml_text_normAutofit_literal);
				_normAutofit_writer.get_writer(context(), &t()->normAutofit.get())->write_target_to(w);
				w.end_element(0, dml_text_normAutofit_literal);
			}
			if (t()->spAutoFit.present()) {
				w.start_element(0, dml_text_spAutoFit_literal);
				_spAutoFit_writer.get_writer(context(), &t()->spAutoFit.get())->write_target_to(w);
				w.end_element(0, dml_text_spAutoFit_literal);
			}
			if (t()->scene3d.present()) {
				w.start_element(0, dml_text_scene3d_literal);
				_scene3d_writer.get_writer(context(), &t()->scene3d.get())->write_target_to(w);
				w.end_element(0, dml_text_scene3d_literal);
			}
			if (t()->sp3d.present()) {
				w.start_element(0, dml_text_sp3d_literal);
				_sp3d_writer.get_writer(context(), &t()->sp3d.get())->write_target_to(w);
				w.end_element(0, dml_text_sp3d_literal);
			}
			if (t()->flatTx.present()) {
				w.start_element(0, dml_text_flatTx_literal);
				_flatTx_writer.get_writer(context(), &t()->flatTx.get())->write_target_to(w);
				w.end_element(0, dml_text_flatTx_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, dml_text_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, dml_text_extLst_literal);
			}
		}

		void CT_TextListStyle_writer::write_target_to(xml_writer& w) {
			if (t()->defPPr.present()) {
				w.start_element(0, dml_text_defPPr_literal);
				_defPPr_writer.get_writer(context(), &t()->defPPr.get())->write_target_to(w);
				w.end_element(0, dml_text_defPPr_literal);
			}
			if (t()->lvl1pPr.present()) {
				w.start_element(0, dml_text_lvl1pPr_literal);
				_lvl1pPr_writer.get_writer(context(), &t()->lvl1pPr.get())->write_target_to(w);
				w.end_element(0, dml_text_lvl1pPr_literal);
			}
			if (t()->lvl2pPr.present()) {
				w.start_element(0, dml_text_lvl2pPr_literal);
				_lvl2pPr_writer.get_writer(context(), &t()->lvl2pPr.get())->write_target_to(w);
				w.end_element(0, dml_text_lvl2pPr_literal);
			}
			if (t()->lvl3pPr.present()) {
				w.start_element(0, dml_text_lvl3pPr_literal);
				_lvl3pPr_writer.get_writer(context(), &t()->lvl3pPr.get())->write_target_to(w);
				w.end_element(0, dml_text_lvl3pPr_literal);
			}
			if (t()->lvl4pPr.present()) {
				w.start_element(0, dml_text_lvl4pPr_literal);
				_lvl4pPr_writer.get_writer(context(), &t()->lvl4pPr.get())->write_target_to(w);
				w.end_element(0, dml_text_lvl4pPr_literal);
			}
			if (t()->lvl5pPr.present()) {
				w.start_element(0, dml_text_lvl5pPr_literal);
				_lvl5pPr_writer.get_writer(context(), &t()->lvl5pPr.get())->write_target_to(w);
				w.end_element(0, dml_text_lvl5pPr_literal);
			}
			if (t()->lvl6pPr.present()) {
				w.start_element(0, dml_text_lvl6pPr_literal);
				_lvl6pPr_writer.get_writer(context(), &t()->lvl6pPr.get())->write_target_to(w);
				w.end_element(0, dml_text_lvl6pPr_literal);
			}
			if (t()->lvl7pPr.present()) {
				w.start_element(0, dml_text_lvl7pPr_literal);
				_lvl7pPr_writer.get_writer(context(), &t()->lvl7pPr.get())->write_target_to(w);
				w.end_element(0, dml_text_lvl7pPr_literal);
			}
			if (t()->lvl8pPr.present()) {
				w.start_element(0, dml_text_lvl8pPr_literal);
				_lvl8pPr_writer.get_writer(context(), &t()->lvl8pPr.get())->write_target_to(w);
				w.end_element(0, dml_text_lvl8pPr_literal);
			}
			if (t()->lvl9pPr.present()) {
				w.start_element(0, dml_text_lvl9pPr_literal);
				_lvl9pPr_writer.get_writer(context(), &t()->lvl9pPr.get())->write_target_to(w);
				w.end_element(0, dml_text_lvl9pPr_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, dml_text_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, dml_text_extLst_literal);
			}
		}

		void CT_TextParagraph_writer::write_target_to(xml_writer& w) {
			if (t()->pPr.present()) {
				w.start_element(0, dml_text_pPr_literal);
				_pPr_writer.get_writer(context(), &t()->pPr.get())->write_target_to(w);
				w.end_element(0, dml_text_pPr_literal);
			}
			if (t()->r.present()) {
				w.start_element(0, dml_text_r_literal);
				_r_writer.get_writer(context(), &t()->r.get())->write_target_to(w);
				w.end_element(0, dml_text_r_literal);
			}
			if (t()->br.present()) {
				w.start_element(0, dml_text_br_literal);
				_br_writer.get_writer(context(), &t()->br.get())->write_target_to(w);
				w.end_element(0, dml_text_br_literal);
			}
			if (t()->fld.present()) {
				w.start_element(0, dml_text_fld_literal);
				_fld_writer.get_writer(context(), &t()->fld.get())->write_target_to(w);
				w.end_element(0, dml_text_fld_literal);
			}
			if (t()->endParaRPr.present()) {
				w.start_element(0, dml_text_endParaRPr_literal);
				_endParaRPr_writer.get_writer(context(), &t()->endParaRPr.get())->write_target_to(w);
				w.end_element(0, dml_text_endParaRPr_literal);
			}
		}

		void CT_TextBody_writer::write_target_to(xml_writer& w) {
			w.start_element(0, dml_text_bodyPr_literal);
			_bodyPr_writer.get_writer(context(), &t()->bodyPr)->write_target_to(w);
			w.end_element(0, dml_text_bodyPr_literal);
			if (t()->lstStyle.present()) {
				w.start_element(0, dml_text_lstStyle_literal);
				_lstStyle_writer.get_writer(context(), &t()->lstStyle.get())->write_target_to(w);
				w.end_element(0, dml_text_lstStyle_literal);
			}
			for (size_t sqi = 0; sqi<t()->p.size(); ++sqi) {
				w.start_element(0, dml_text_p_literal);
				_p_writer.get_writer(context(), &t()->p[sqi])->write_target_to(w);
				w.end_element(0, dml_text_p_literal);
			}
		}

	}
}
