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


#include "dml-shapeEffects_writers.hpp"
#include "dml-shapeEffects_literals.hpp"

namespace drawingml
{
	namespace xio
	{
		void CT_AlphaBiLevelEffect_writer::write_target_to(xml_writer& w) {
			w.attribute(0, dml_shapeEffects_thresh_literal, context()->serialize(t()->thresh));
		}

		void CT_AlphaCeilingEffect_writer::write_target_to(xml_writer& w) {
		}

		void CT_AlphaFloorEffect_writer::write_target_to(xml_writer& w) {
		}

		void CT_AlphaInverseEffect_writer::write_target_to(xml_writer& w) {
			if (t()->scrgbClr.present()) {
				w.start_element(0, dml_shapeEffects_scrgbClr_literal);
				_scrgbClr_writer.get_writer(context(), &t()->scrgbClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_scrgbClr_literal);
			}
			if (t()->srgbClr.present()) {
				w.start_element(0, dml_shapeEffects_srgbClr_literal);
				_srgbClr_writer.get_writer(context(), &t()->srgbClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_srgbClr_literal);
			}
			if (t()->hslClr.present()) {
				w.start_element(0, dml_shapeEffects_hslClr_literal);
				_hslClr_writer.get_writer(context(), &t()->hslClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_hslClr_literal);
			}
			if (t()->sysClr.present()) {
				w.start_element(0, dml_shapeEffects_sysClr_literal);
				_sysClr_writer.get_writer(context(), &t()->sysClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_sysClr_literal);
			}
			if (t()->schemeClr.present()) {
				w.start_element(0, dml_shapeEffects_schemeClr_literal);
				_schemeClr_writer.get_writer(context(), &t()->schemeClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_schemeClr_literal);
			}
			if (t()->prstClr.present()) {
				w.start_element(0, dml_shapeEffects_prstClr_literal);
				_prstClr_writer.get_writer(context(), &t()->prstClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_prstClr_literal);
			}
		}

		void CT_EffectReference_writer::write_target_to(xml_writer& w) {
			if (t()->ref.present())
				w.attribute(0, dml_shapeEffects_ref_literal, context()->serialize(t()->ref.get()));
		}

		void CT_AlphaModulateFixedEffect_writer::write_target_to(xml_writer& w) {
			if (t()->amt != 100000)
				w.attribute(0, dml_shapeEffects_amt_literal, context()->serialize(t()->amt));
		}

		void CT_AlphaOutsetEffect_writer::write_target_to(xml_writer& w) {
			if (t()->rad != 0L)
				w.attribute(0, dml_shapeEffects_rad_literal, context()->serialize(t()->rad));
		}

		void CT_AlphaReplaceEffect_writer::write_target_to(xml_writer& w) {
			w.attribute(0, dml_shapeEffects_a_literal, context()->serialize(t()->a));
		}

		void CT_BiLevelEffect_writer::write_target_to(xml_writer& w) {
			w.attribute(0, dml_shapeEffects_thresh_literal, context()->serialize(t()->thresh));
		}

		void CT_BlurEffect_writer::write_target_to(xml_writer& w) {
			if (t()->rad != 0L)
				w.attribute(0, dml_shapeEffects_rad_literal, context()->serialize(t()->rad));
			if (t()->grow != true)
				w.attribute(0, dml_shapeEffects_grow_literal, context()->serialize(t()->grow));
		}

		void CT_ColorChangeEffect_writer::write_target_to(xml_writer& w) {
			if (t()->useA != true)
				w.attribute(0, dml_shapeEffects_useA_literal, context()->serialize(t()->useA));
			w.start_element(0, dml_shapeEffects_clrFrom_literal);
			_clrFrom_writer.get_writer(context(), &t()->clrFrom)->write_target_to(w);
			w.end_element(0, dml_shapeEffects_clrFrom_literal);
			w.start_element(0, dml_shapeEffects_clrTo_literal);
			_clrTo_writer.get_writer(context(), &t()->clrTo)->write_target_to(w);
			w.end_element(0, dml_shapeEffects_clrTo_literal);
		}

		void CT_ColorReplaceEffect_writer::write_target_to(xml_writer& w) {
			if (t()->scrgbClr.present()) {
				w.start_element(0, dml_shapeEffects_scrgbClr_literal);
				_scrgbClr_writer.get_writer(context(), &t()->scrgbClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_scrgbClr_literal);
			}
			if (t()->srgbClr.present()) {
				w.start_element(0, dml_shapeEffects_srgbClr_literal);
				_srgbClr_writer.get_writer(context(), &t()->srgbClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_srgbClr_literal);
			}
			if (t()->hslClr.present()) {
				w.start_element(0, dml_shapeEffects_hslClr_literal);
				_hslClr_writer.get_writer(context(), &t()->hslClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_hslClr_literal);
			}
			if (t()->sysClr.present()) {
				w.start_element(0, dml_shapeEffects_sysClr_literal);
				_sysClr_writer.get_writer(context(), &t()->sysClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_sysClr_literal);
			}
			if (t()->schemeClr.present()) {
				w.start_element(0, dml_shapeEffects_schemeClr_literal);
				_schemeClr_writer.get_writer(context(), &t()->schemeClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_schemeClr_literal);
			}
			if (t()->prstClr.present()) {
				w.start_element(0, dml_shapeEffects_prstClr_literal);
				_prstClr_writer.get_writer(context(), &t()->prstClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_prstClr_literal);
			}
		}

		void CT_DuotoneEffect_writer::write_target_to(xml_writer& w) {
			if (t()->scrgbClr.present()) {
				w.start_element(0, dml_shapeEffects_scrgbClr_literal);
				_scrgbClr_writer.get_writer(context(), &t()->scrgbClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_scrgbClr_literal);
			}
			if (t()->srgbClr.present()) {
				w.start_element(0, dml_shapeEffects_srgbClr_literal);
				_srgbClr_writer.get_writer(context(), &t()->srgbClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_srgbClr_literal);
			}
			if (t()->hslClr.present()) {
				w.start_element(0, dml_shapeEffects_hslClr_literal);
				_hslClr_writer.get_writer(context(), &t()->hslClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_hslClr_literal);
			}
			if (t()->sysClr.present()) {
				w.start_element(0, dml_shapeEffects_sysClr_literal);
				_sysClr_writer.get_writer(context(), &t()->sysClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_sysClr_literal);
			}
			if (t()->schemeClr.present()) {
				w.start_element(0, dml_shapeEffects_schemeClr_literal);
				_schemeClr_writer.get_writer(context(), &t()->schemeClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_schemeClr_literal);
			}
			if (t()->prstClr.present()) {
				w.start_element(0, dml_shapeEffects_prstClr_literal);
				_prstClr_writer.get_writer(context(), &t()->prstClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_prstClr_literal);
			}
		}

		void CT_NoFillProperties_writer::write_target_to(xml_writer& w) {
		}

		void CT_SolidColorFillProperties_writer::write_target_to(xml_writer& w) {
			if (t()->scrgbClr.present()) {
				w.start_element(0, dml_shapeEffects_scrgbClr_literal);
				_scrgbClr_writer.get_writer(context(), &t()->scrgbClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_scrgbClr_literal);
			}
			if (t()->srgbClr.present()) {
				w.start_element(0, dml_shapeEffects_srgbClr_literal);
				_srgbClr_writer.get_writer(context(), &t()->srgbClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_srgbClr_literal);
			}
			if (t()->hslClr.present()) {
				w.start_element(0, dml_shapeEffects_hslClr_literal);
				_hslClr_writer.get_writer(context(), &t()->hslClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_hslClr_literal);
			}
			if (t()->sysClr.present()) {
				w.start_element(0, dml_shapeEffects_sysClr_literal);
				_sysClr_writer.get_writer(context(), &t()->sysClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_sysClr_literal);
			}
			if (t()->schemeClr.present()) {
				w.start_element(0, dml_shapeEffects_schemeClr_literal);
				_schemeClr_writer.get_writer(context(), &t()->schemeClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_schemeClr_literal);
			}
			if (t()->prstClr.present()) {
				w.start_element(0, dml_shapeEffects_prstClr_literal);
				_prstClr_writer.get_writer(context(), &t()->prstClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_prstClr_literal);
			}
		}

		void CT_GradientStop_writer::write_target_to(xml_writer& w) {
			w.attribute(0, dml_shapeEffects_pos_literal, context()->serialize(t()->pos));
			if (t()->scrgbClr.present()) {
				w.start_element(0, dml_shapeEffects_scrgbClr_literal);
				_scrgbClr_writer.get_writer(context(), &t()->scrgbClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_scrgbClr_literal);
			}
			if (t()->srgbClr.present()) {
				w.start_element(0, dml_shapeEffects_srgbClr_literal);
				_srgbClr_writer.get_writer(context(), &t()->srgbClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_srgbClr_literal);
			}
			if (t()->hslClr.present()) {
				w.start_element(0, dml_shapeEffects_hslClr_literal);
				_hslClr_writer.get_writer(context(), &t()->hslClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_hslClr_literal);
			}
			if (t()->sysClr.present()) {
				w.start_element(0, dml_shapeEffects_sysClr_literal);
				_sysClr_writer.get_writer(context(), &t()->sysClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_sysClr_literal);
			}
			if (t()->schemeClr.present()) {
				w.start_element(0, dml_shapeEffects_schemeClr_literal);
				_schemeClr_writer.get_writer(context(), &t()->schemeClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_schemeClr_literal);
			}
			if (t()->prstClr.present()) {
				w.start_element(0, dml_shapeEffects_prstClr_literal);
				_prstClr_writer.get_writer(context(), &t()->prstClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_prstClr_literal);
			}
		}

		void CT_GradientStopList_writer::write_target_to(xml_writer& w) {
			for (size_t sqi = 0; sqi<t()->gs.size(); ++sqi) {
				w.start_element(0, dml_shapeEffects_gs_literal);
				_gs_writer.get_writer(context(), &t()->gs[sqi])->write_target_to(w);
				w.end_element(0, dml_shapeEffects_gs_literal);
			}
		}

		void CT_LinearShadeProperties_writer::write_target_to(xml_writer& w) {
			if (t()->ang.present())
				w.attribute(0, dml_shapeEffects_ang_literal, context()->serialize(t()->ang.get()));
			if (t()->scaled.present())
				w.attribute(0, dml_shapeEffects_scaled_literal, context()->serialize(t()->scaled.get()));
		}

		void CT_PathShadeProperties_writer::write_target_to(xml_writer& w) {
			if (t()->path.present())
				w.attribute(0, dml_shapeEffects_path_literal, context()->serialize(t()->path.get()));
			if (t()->fillToRect.present()) {
				w.start_element(0, dml_shapeEffects_fillToRect_literal);
				_fillToRect_writer.get_writer(context(), &t()->fillToRect.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_fillToRect_literal);
			}
		}

		void CT_GradientFillProperties_writer::write_target_to(xml_writer& w) {
			if (t()->flip.present())
				w.attribute(0, dml_shapeEffects_flip_literal, context()->serialize(t()->flip.get()));
			if (t()->rotWithShape.present())
				w.attribute(0, dml_shapeEffects_rotWithShape_literal, context()->serialize(t()->rotWithShape.get()));
			if (t()->gsLst.present()) {
				w.start_element(0, dml_shapeEffects_gsLst_literal);
				_gsLst_writer.get_writer(context(), &t()->gsLst.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_gsLst_literal);
			}
			if (t()->lin.present()) {
				w.start_element(0, dml_shapeEffects_lin_literal);
				_lin_writer.get_writer(context(), &t()->lin.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_lin_literal);
			}
			if (t()->path.present()) {
				w.start_element(0, dml_shapeEffects_path_literal);
				_path_writer.get_writer(context(), &t()->path.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_path_literal);
			}
			if (t()->tileRect.present()) {
				w.start_element(0, dml_shapeEffects_tileRect_literal);
				_tileRect_writer.get_writer(context(), &t()->tileRect.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_tileRect_literal);
			}
		}

		void CT_TileInfoProperties_writer::write_target_to(xml_writer& w) {
			if (t()->tx.present())
				w.attribute(0, dml_shapeEffects_tx_literal, context()->serialize(t()->tx.get()));
			if (t()->ty.present())
				w.attribute(0, dml_shapeEffects_ty_literal, context()->serialize(t()->ty.get()));
			if (t()->sx.present())
				w.attribute(0, dml_shapeEffects_sx_literal, context()->serialize(t()->sx.get()));
			if (t()->sy.present())
				w.attribute(0, dml_shapeEffects_sy_literal, context()->serialize(t()->sy.get()));
			if (t()->flip.present())
				w.attribute(0, dml_shapeEffects_flip_literal, context()->serialize(t()->flip.get()));
			if (t()->algn.present())
				w.attribute(0, dml_shapeEffects_algn_literal, context()->serialize(t()->algn.get()));
		}

		void CT_StretchInfoProperties_writer::write_target_to(xml_writer& w) {
			if (t()->fillRect.present()) {
				w.start_element(0, dml_shapeEffects_fillRect_literal);
				_fillRect_writer.get_writer(context(), &t()->fillRect.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_fillRect_literal);
			}
		}

		void CT_BlipFillProperties_writer::write_target_to(xml_writer& w) {
			if (t()->dpi.present())
				w.attribute(0, dml_shapeEffects_dpi_literal, context()->serialize(t()->dpi.get()));
			if (t()->rotWithShape.present())
				w.attribute(0, dml_shapeEffects_rotWithShape_literal, context()->serialize(t()->rotWithShape.get()));
			if (t()->blip.present()) {
                XMLCh ns[2]; ns[0] = 'a';ns[1] = 0;
				w.start_element(ns, dml_shapeEffects_blip_literal);
				_blip_writer.get_writer(context(), &t()->blip.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_blip_literal);
			}
			if (t()->srcRect.present()) {
				w.start_element(0, dml_shapeEffects_srcRect_literal);
				_srcRect_writer.get_writer(context(), &t()->srcRect.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_srcRect_literal);
			}
			if (t()->tile.present()) {
				w.start_element(0, dml_shapeEffects_tile_literal);
				_tile_writer.get_writer(context(), &t()->tile.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_tile_literal);
			}
			if (t()->stretch.present()) {
				w.start_element(0, dml_shapeEffects_stretch_literal);
				_stretch_writer.get_writer(context(), &t()->stretch.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_stretch_literal);
			}
		}

		void CT_PatternFillProperties_writer::write_target_to(xml_writer& w) {
			if (t()->prst.present())
				w.attribute(0, dml_shapeEffects_prst_literal, context()->serialize(t()->prst.get()));
			if (t()->fgClr.present()) {
				w.start_element(0, dml_shapeEffects_fgClr_literal);
				_fgClr_writer.get_writer(context(), &t()->fgClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_fgClr_literal);
			}
			if (t()->bgClr.present()) {
				w.start_element(0, dml_shapeEffects_bgClr_literal);
				_bgClr_writer.get_writer(context(), &t()->bgClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_bgClr_literal);
			}
		}

		void CT_GroupFillProperties_writer::write_target_to(xml_writer& w) {
		}

		void CT_FillEffect_writer::write_target_to(xml_writer& w) {
			if (t()->noFill.present()) {
				w.start_element(0, dml_shapeEffects_noFill_literal);
				_noFill_writer.get_writer(context(), &t()->noFill.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_noFill_literal);
			}
			if (t()->solidFill.present()) {
				w.start_element(0, dml_shapeEffects_solidFill_literal);
				_solidFill_writer.get_writer(context(), &t()->solidFill.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_solidFill_literal);
			}
			if (t()->gradFill.present()) {
				w.start_element(0, dml_shapeEffects_gradFill_literal);
				_gradFill_writer.get_writer(context(), &t()->gradFill.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_gradFill_literal);
			}
			if (t()->blipFill.present()) {
				w.start_element(0, dml_shapeEffects_blipFill_literal);
				_blipFill_writer.get_writer(context(), &t()->blipFill.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_blipFill_literal);
			}
			if (t()->pattFill.present()) {
				w.start_element(0, dml_shapeEffects_pattFill_literal);
				_pattFill_writer.get_writer(context(), &t()->pattFill.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_pattFill_literal);
			}
			if (t()->grpFill.present()) {
				w.start_element(0, dml_shapeEffects_grpFill_literal);
				_grpFill_writer.get_writer(context(), &t()->grpFill.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_grpFill_literal);
			}
		}

		void CT_FillOverlayEffect_writer::write_target_to(xml_writer& w) {
			w.attribute(0, dml_shapeEffects_blend_literal, context()->serialize(t()->blend));
			if (t()->noFill.present()) {
				w.start_element(0, dml_shapeEffects_noFill_literal);
				_noFill_writer.get_writer(context(), &t()->noFill.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_noFill_literal);
			}
			if (t()->solidFill.present()) {
				w.start_element(0, dml_shapeEffects_solidFill_literal);
				_solidFill_writer.get_writer(context(), &t()->solidFill.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_solidFill_literal);
			}
			if (t()->gradFill.present()) {
				w.start_element(0, dml_shapeEffects_gradFill_literal);
				_gradFill_writer.get_writer(context(), &t()->gradFill.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_gradFill_literal);
			}
			if (t()->blipFill.present()) {
				w.start_element(0, dml_shapeEffects_blipFill_literal);
				_blipFill_writer.get_writer(context(), &t()->blipFill.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_blipFill_literal);
			}
			if (t()->pattFill.present()) {
				w.start_element(0, dml_shapeEffects_pattFill_literal);
				_pattFill_writer.get_writer(context(), &t()->pattFill.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_pattFill_literal);
			}
			if (t()->grpFill.present()) {
				w.start_element(0, dml_shapeEffects_grpFill_literal);
				_grpFill_writer.get_writer(context(), &t()->grpFill.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_grpFill_literal);
			}
		}

		void CT_GlowEffect_writer::write_target_to(xml_writer& w) {
			if (t()->rad != 0L)
				w.attribute(0, dml_shapeEffects_rad_literal, context()->serialize(t()->rad));
			if (t()->scrgbClr.present()) {
				w.start_element(0, dml_shapeEffects_scrgbClr_literal);
				_scrgbClr_writer.get_writer(context(), &t()->scrgbClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_scrgbClr_literal);
			}
			if (t()->srgbClr.present()) {
				w.start_element(0, dml_shapeEffects_srgbClr_literal);
				_srgbClr_writer.get_writer(context(), &t()->srgbClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_srgbClr_literal);
			}
			if (t()->hslClr.present()) {
				w.start_element(0, dml_shapeEffects_hslClr_literal);
				_hslClr_writer.get_writer(context(), &t()->hslClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_hslClr_literal);
			}
			if (t()->sysClr.present()) {
				w.start_element(0, dml_shapeEffects_sysClr_literal);
				_sysClr_writer.get_writer(context(), &t()->sysClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_sysClr_literal);
			}
			if (t()->schemeClr.present()) {
				w.start_element(0, dml_shapeEffects_schemeClr_literal);
				_schemeClr_writer.get_writer(context(), &t()->schemeClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_schemeClr_literal);
			}
			if (t()->prstClr.present()) {
				w.start_element(0, dml_shapeEffects_prstClr_literal);
				_prstClr_writer.get_writer(context(), &t()->prstClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_prstClr_literal);
			}
		}

		void CT_GrayscaleEffect_writer::write_target_to(xml_writer& w) {
		}

		void CT_HSLEffect_writer::write_target_to(xml_writer& w) {
			if (t()->hue != 0)
				w.attribute(0, dml_shapeEffects_hue_literal, context()->serialize(t()->hue));
			if (t()->sat != 0)
				w.attribute(0, dml_shapeEffects_sat_literal, context()->serialize(t()->sat));
			if (t()->lum != 0)
				w.attribute(0, dml_shapeEffects_lum_literal, context()->serialize(t()->lum));
		}

		void CT_InnerShadowEffect_writer::write_target_to(xml_writer& w) {
			if (t()->blurRad != 0L)
				w.attribute(0, dml_shapeEffects_blurRad_literal, context()->serialize(t()->blurRad));
			if (t()->dist != 0L)
				w.attribute(0, dml_shapeEffects_dist_literal, context()->serialize(t()->dist));
			if (t()->dir != 0)
				w.attribute(0, dml_shapeEffects_dir_literal, context()->serialize(t()->dir));
			if (t()->scrgbClr.present()) {
				w.start_element(0, dml_shapeEffects_scrgbClr_literal);
				_scrgbClr_writer.get_writer(context(), &t()->scrgbClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_scrgbClr_literal);
			}
			if (t()->srgbClr.present()) {
				w.start_element(0, dml_shapeEffects_srgbClr_literal);
				_srgbClr_writer.get_writer(context(), &t()->srgbClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_srgbClr_literal);
			}
			if (t()->hslClr.present()) {
				w.start_element(0, dml_shapeEffects_hslClr_literal);
				_hslClr_writer.get_writer(context(), &t()->hslClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_hslClr_literal);
			}
			if (t()->sysClr.present()) {
				w.start_element(0, dml_shapeEffects_sysClr_literal);
				_sysClr_writer.get_writer(context(), &t()->sysClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_sysClr_literal);
			}
			if (t()->schemeClr.present()) {
				w.start_element(0, dml_shapeEffects_schemeClr_literal);
				_schemeClr_writer.get_writer(context(), &t()->schemeClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_schemeClr_literal);
			}
			if (t()->prstClr.present()) {
				w.start_element(0, dml_shapeEffects_prstClr_literal);
				_prstClr_writer.get_writer(context(), &t()->prstClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_prstClr_literal);
			}
		}

		void CT_LuminanceEffect_writer::write_target_to(xml_writer& w) {
			if (t()->bright != 0)
				w.attribute(0, dml_shapeEffects_bright_literal, context()->serialize(t()->bright));
			if (t()->contrast != 0)
				w.attribute(0, dml_shapeEffects_contrast_literal, context()->serialize(t()->contrast));
		}

		void CT_OuterShadowEffect_writer::write_target_to(xml_writer& w) {
			if (t()->blurRad != 0L)
				w.attribute(0, dml_shapeEffects_blurRad_literal, context()->serialize(t()->blurRad));
			if (t()->dist != 0L)
				w.attribute(0, dml_shapeEffects_dist_literal, context()->serialize(t()->dist));
			if (t()->dir != 0)
				w.attribute(0, dml_shapeEffects_dir_literal, context()->serialize(t()->dir));
			if (t()->sx != 100000)
				w.attribute(0, dml_shapeEffects_sx_literal, context()->serialize(t()->sx));
			if (t()->sy != 100000)
				w.attribute(0, dml_shapeEffects_sy_literal, context()->serialize(t()->sy));
			if (t()->kx != 0)
				w.attribute(0, dml_shapeEffects_kx_literal, context()->serialize(t()->kx));
			if (t()->ky != 0)
				w.attribute(0, dml_shapeEffects_ky_literal, context()->serialize(t()->ky));
			if (t()->algn != ST_RectAlignment::b_literal)
				w.attribute(0, dml_shapeEffects_algn_literal, context()->serialize(t()->algn));
			if (t()->rotWithShape != true)
				w.attribute(0, dml_shapeEffects_rotWithShape_literal, context()->serialize(t()->rotWithShape));
			if (t()->scrgbClr.present()) {
				w.start_element(0, dml_shapeEffects_scrgbClr_literal);
				_scrgbClr_writer.get_writer(context(), &t()->scrgbClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_scrgbClr_literal);
			}
			if (t()->srgbClr.present()) {
				w.start_element(0, dml_shapeEffects_srgbClr_literal);
				_srgbClr_writer.get_writer(context(), &t()->srgbClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_srgbClr_literal);
			}
			if (t()->hslClr.present()) {
				w.start_element(0, dml_shapeEffects_hslClr_literal);
				_hslClr_writer.get_writer(context(), &t()->hslClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_hslClr_literal);
			}
			if (t()->sysClr.present()) {
				w.start_element(0, dml_shapeEffects_sysClr_literal);
				_sysClr_writer.get_writer(context(), &t()->sysClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_sysClr_literal);
			}
			if (t()->schemeClr.present()) {
				w.start_element(0, dml_shapeEffects_schemeClr_literal);
				_schemeClr_writer.get_writer(context(), &t()->schemeClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_schemeClr_literal);
			}
			if (t()->prstClr.present()) {
				w.start_element(0, dml_shapeEffects_prstClr_literal);
				_prstClr_writer.get_writer(context(), &t()->prstClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_prstClr_literal);
			}
		}

		void CT_PresetShadowEffect_writer::write_target_to(xml_writer& w) {
			w.attribute(0, dml_shapeEffects_prst_literal, context()->serialize(t()->prst));
			if (t()->dist != 0L)
				w.attribute(0, dml_shapeEffects_dist_literal, context()->serialize(t()->dist));
			if (t()->dir != 0)
				w.attribute(0, dml_shapeEffects_dir_literal, context()->serialize(t()->dir));
			if (t()->scrgbClr.present()) {
				w.start_element(0, dml_shapeEffects_scrgbClr_literal);
				_scrgbClr_writer.get_writer(context(), &t()->scrgbClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_scrgbClr_literal);
			}
			if (t()->srgbClr.present()) {
				w.start_element(0, dml_shapeEffects_srgbClr_literal);
				_srgbClr_writer.get_writer(context(), &t()->srgbClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_srgbClr_literal);
			}
			if (t()->hslClr.present()) {
				w.start_element(0, dml_shapeEffects_hslClr_literal);
				_hslClr_writer.get_writer(context(), &t()->hslClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_hslClr_literal);
			}
			if (t()->sysClr.present()) {
				w.start_element(0, dml_shapeEffects_sysClr_literal);
				_sysClr_writer.get_writer(context(), &t()->sysClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_sysClr_literal);
			}
			if (t()->schemeClr.present()) {
				w.start_element(0, dml_shapeEffects_schemeClr_literal);
				_schemeClr_writer.get_writer(context(), &t()->schemeClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_schemeClr_literal);
			}
			if (t()->prstClr.present()) {
				w.start_element(0, dml_shapeEffects_prstClr_literal);
				_prstClr_writer.get_writer(context(), &t()->prstClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_prstClr_literal);
			}
		}

		void CT_ReflectionEffect_writer::write_target_to(xml_writer& w) {
			if (t()->blurRad != 0L)
				w.attribute(0, dml_shapeEffects_blurRad_literal, context()->serialize(t()->blurRad));
			if (t()->stA != 100000)
				w.attribute(0, dml_shapeEffects_stA_literal, context()->serialize(t()->stA));
			if (t()->stPos != 0)
				w.attribute(0, dml_shapeEffects_stPos_literal, context()->serialize(t()->stPos));
			if (t()->endA != 0)
				w.attribute(0, dml_shapeEffects_endA_literal, context()->serialize(t()->endA));
			if (t()->endPos != 100000)
				w.attribute(0, dml_shapeEffects_endPos_literal, context()->serialize(t()->endPos));
			if (t()->dist != 0L)
				w.attribute(0, dml_shapeEffects_dist_literal, context()->serialize(t()->dist));
			if (t()->dir != 0)
				w.attribute(0, dml_shapeEffects_dir_literal, context()->serialize(t()->dir));
			if (t()->fadeDir != 5400000)
				w.attribute(0, dml_shapeEffects_fadeDir_literal, context()->serialize(t()->fadeDir));
			if (t()->sx != 100000)
				w.attribute(0, dml_shapeEffects_sx_literal, context()->serialize(t()->sx));
			if (t()->sy != 100000)
				w.attribute(0, dml_shapeEffects_sy_literal, context()->serialize(t()->sy));
			if (t()->kx != 0)
				w.attribute(0, dml_shapeEffects_kx_literal, context()->serialize(t()->kx));
			if (t()->ky != 0)
				w.attribute(0, dml_shapeEffects_ky_literal, context()->serialize(t()->ky));
			if (t()->algn != ST_RectAlignment::b_literal)
				w.attribute(0, dml_shapeEffects_algn_literal, context()->serialize(t()->algn));
			if (t()->rotWithShape != true)
				w.attribute(0, dml_shapeEffects_rotWithShape_literal, context()->serialize(t()->rotWithShape));
		}

		void CT_RelativeOffsetEffect_writer::write_target_to(xml_writer& w) {
			if (t()->tx != 0)
				w.attribute(0, dml_shapeEffects_tx_literal, context()->serialize(t()->tx));
			if (t()->ty != 0)
				w.attribute(0, dml_shapeEffects_ty_literal, context()->serialize(t()->ty));
		}

		void CT_SoftEdgesEffect_writer::write_target_to(xml_writer& w) {
			w.attribute(0, dml_shapeEffects_rad_literal, context()->serialize(t()->rad));
		}

		void CT_TintEffect_writer::write_target_to(xml_writer& w) {
			if (t()->hue != 0)
				w.attribute(0, dml_shapeEffects_hue_literal, context()->serialize(t()->hue));
			if (t()->amt != 0)
				w.attribute(0, dml_shapeEffects_amt_literal, context()->serialize(t()->amt));
		}

		void CT_TransformEffect_writer::write_target_to(xml_writer& w) {
			if (t()->sx != 100000)
				w.attribute(0, dml_shapeEffects_sx_literal, context()->serialize(t()->sx));
			if (t()->sy != 100000)
				w.attribute(0, dml_shapeEffects_sy_literal, context()->serialize(t()->sy));
			if (t()->kx != 0)
				w.attribute(0, dml_shapeEffects_kx_literal, context()->serialize(t()->kx));
			if (t()->ky != 0)
				w.attribute(0, dml_shapeEffects_ky_literal, context()->serialize(t()->ky));
			if (t()->tx != 0L)
				w.attribute(0, dml_shapeEffects_tx_literal, context()->serialize(t()->tx));
			if (t()->ty != 0L)
				w.attribute(0, dml_shapeEffects_ty_literal, context()->serialize(t()->ty));
		}

		void CT_EffectContainer_writer::write_target_to(xml_writer& w) {
			if (t()->type != ST_EffectContainerType::sib_literal)
				w.attribute(0, dml_shapeEffects_type_literal, context()->serialize(t()->type));
			if (t()->name.present())
				w.attribute(0, dml_shapeEffects_name_literal, context()->serialize(t()->name.get()));
			if (t()->cont.present()) {
				w.start_element(0, dml_shapeEffects_cont_literal);
				_cont_writer.get_writer(context(), &t()->cont.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_cont_literal);
			}
			if (t()->effect.present()) {
				w.start_element(0, dml_shapeEffects_effect_literal);
				_effect_writer.get_writer(context(), &t()->effect.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_effect_literal);
			}
			if (t()->alphaBiLevel.present()) {
				w.start_element(0, dml_shapeEffects_alphaBiLevel_literal);
				_alphaBiLevel_writer.get_writer(context(), &t()->alphaBiLevel.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_alphaBiLevel_literal);
			}
			if (t()->alphaCeiling.present()) {
				w.start_element(0, dml_shapeEffects_alphaCeiling_literal);
				_alphaCeiling_writer.get_writer(context(), &t()->alphaCeiling.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_alphaCeiling_literal);
			}
			if (t()->alphaFloor.present()) {
				w.start_element(0, dml_shapeEffects_alphaFloor_literal);
				_alphaFloor_writer.get_writer(context(), &t()->alphaFloor.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_alphaFloor_literal);
			}
			if (t()->alphaInv.present()) {
				w.start_element(0, dml_shapeEffects_alphaInv_literal);
				_alphaInv_writer.get_writer(context(), &t()->alphaInv.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_alphaInv_literal);
			}
			if (t()->alphaMod.present()) {
				w.start_element(0, dml_shapeEffects_alphaMod_literal);
				_alphaMod_writer.get_writer(context(), &t()->alphaMod.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_alphaMod_literal);
			}
			if (t()->alphaModFix.present()) {
				w.start_element(0, dml_shapeEffects_alphaModFix_literal);
				_alphaModFix_writer.get_writer(context(), &t()->alphaModFix.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_alphaModFix_literal);
			}
			if (t()->alphaOutset.present()) {
				w.start_element(0, dml_shapeEffects_alphaOutset_literal);
				_alphaOutset_writer.get_writer(context(), &t()->alphaOutset.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_alphaOutset_literal);
			}
			if (t()->alphaRepl.present()) {
				w.start_element(0, dml_shapeEffects_alphaRepl_literal);
				_alphaRepl_writer.get_writer(context(), &t()->alphaRepl.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_alphaRepl_literal);
			}
			if (t()->biLevel.present()) {
				w.start_element(0, dml_shapeEffects_biLevel_literal);
				_biLevel_writer.get_writer(context(), &t()->biLevel.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_biLevel_literal);
			}
			if (t()->blend.present()) {
				w.start_element(0, dml_shapeEffects_blend_literal);
				_blend_writer.get_writer(context(), &t()->blend.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_blend_literal);
			}
			if (t()->blur.present()) {
				w.start_element(0, dml_shapeEffects_blur_literal);
				_blur_writer.get_writer(context(), &t()->blur.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_blur_literal);
			}
			if (t()->clrChange.present()) {
				w.start_element(0, dml_shapeEffects_clrChange_literal);
				_clrChange_writer.get_writer(context(), &t()->clrChange.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_clrChange_literal);
			}
			if (t()->clrRepl.present()) {
				w.start_element(0, dml_shapeEffects_clrRepl_literal);
				_clrRepl_writer.get_writer(context(), &t()->clrRepl.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_clrRepl_literal);
			}
			if (t()->duotone.present()) {
				w.start_element(0, dml_shapeEffects_duotone_literal);
				_duotone_writer.get_writer(context(), &t()->duotone.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_duotone_literal);
			}
			if (t()->fill.present()) {
				w.start_element(0, dml_shapeEffects_fill_literal);
				_fill_writer.get_writer(context(), &t()->fill.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_fill_literal);
			}
			if (t()->fillOverlay.present()) {
				w.start_element(0, dml_shapeEffects_fillOverlay_literal);
				_fillOverlay_writer.get_writer(context(), &t()->fillOverlay.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_fillOverlay_literal);
			}
			if (t()->glow.present()) {
				w.start_element(0, dml_shapeEffects_glow_literal);
				_glow_writer.get_writer(context(), &t()->glow.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_glow_literal);
			}
			if (t()->grayscl.present()) {
				w.start_element(0, dml_shapeEffects_grayscl_literal);
				_grayscl_writer.get_writer(context(), &t()->grayscl.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_grayscl_literal);
			}
			if (t()->hsl.present()) {
				w.start_element(0, dml_shapeEffects_hsl_literal);
				_hsl_writer.get_writer(context(), &t()->hsl.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_hsl_literal);
			}
			if (t()->innerShdw.present()) {
				w.start_element(0, dml_shapeEffects_innerShdw_literal);
				_innerShdw_writer.get_writer(context(), &t()->innerShdw.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_innerShdw_literal);
			}
			if (t()->lum.present()) {
				w.start_element(0, dml_shapeEffects_lum_literal);
				_lum_writer.get_writer(context(), &t()->lum.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_lum_literal);
			}
			if (t()->outerShdw.present()) {
				w.start_element(0, dml_shapeEffects_outerShdw_literal);
				_outerShdw_writer.get_writer(context(), &t()->outerShdw.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_outerShdw_literal);
			}
			if (t()->prstShdw.present()) {
				w.start_element(0, dml_shapeEffects_prstShdw_literal);
				_prstShdw_writer.get_writer(context(), &t()->prstShdw.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_prstShdw_literal);
			}
			if (t()->reflection.present()) {
				w.start_element(0, dml_shapeEffects_reflection_literal);
				_reflection_writer.get_writer(context(), &t()->reflection.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_reflection_literal);
			}
			if (t()->relOff.present()) {
				w.start_element(0, dml_shapeEffects_relOff_literal);
				_relOff_writer.get_writer(context(), &t()->relOff.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_relOff_literal);
			}
			if (t()->softEdge.present()) {
				w.start_element(0, dml_shapeEffects_softEdge_literal);
				_softEdge_writer.get_writer(context(), &t()->softEdge.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_softEdge_literal);
			}
			if (t()->tint.present()) {
				w.start_element(0, dml_shapeEffects_tint_literal);
				_tint_writer.get_writer(context(), &t()->tint.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_tint_literal);
			}
			if (t()->xfrm.present()) {
				w.start_element(0, dml_shapeEffects_xfrm_literal);
				_xfrm_writer.get_writer(context(), &t()->xfrm.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_xfrm_literal);
			}
		}

		void CT_AlphaModulateEffect_writer::write_target_to(xml_writer& w) {
			w.start_element(0, dml_shapeEffects_cont_literal);
			_cont_writer.get_writer(context(), &t()->cont)->write_target_to(w);
			w.end_element(0, dml_shapeEffects_cont_literal);
		}

		void CT_Blip_writer::write_target_to(xml_writer& w) {
			if (t()->embed != "")
            {
                XMLCh ns[2];ns[0]='r';ns[1]=0;
				w.attribute(ns, dml_shapeEffects_embed_literal, context()->serialize(t()->embed));
            }
			if (t()->link != "")
				w.attribute(0, dml_shapeEffects_link_literal, context()->serialize(t()->link));
			if (t()->cstate != ST_BlipCompression::none_literal)
				w.attribute(0, dml_shapeEffects_cstate_literal, context()->serialize(t()->cstate));
			if (t()->alphaBiLevel.present()) {
				w.start_element(0, dml_shapeEffects_alphaBiLevel_literal);
				_alphaBiLevel_writer.get_writer(context(), &t()->alphaBiLevel.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_alphaBiLevel_literal);
			}
			if (t()->alphaCeiling.present()) {
				w.start_element(0, dml_shapeEffects_alphaCeiling_literal);
				_alphaCeiling_writer.get_writer(context(), &t()->alphaCeiling.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_alphaCeiling_literal);
			}
			if (t()->alphaFloor.present()) {
				w.start_element(0, dml_shapeEffects_alphaFloor_literal);
				_alphaFloor_writer.get_writer(context(), &t()->alphaFloor.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_alphaFloor_literal);
			}
			if (t()->alphaInv.present()) {
				w.start_element(0, dml_shapeEffects_alphaInv_literal);
				_alphaInv_writer.get_writer(context(), &t()->alphaInv.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_alphaInv_literal);
			}
			if (t()->alphaMod.present()) {
				w.start_element(0, dml_shapeEffects_alphaMod_literal);
				_alphaMod_writer.get_writer(context(), &t()->alphaMod.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_alphaMod_literal);
			}
			if (t()->alphaModFix.present()) {
				w.start_element(0, dml_shapeEffects_alphaModFix_literal);
				_alphaModFix_writer.get_writer(context(), &t()->alphaModFix.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_alphaModFix_literal);
			}
			if (t()->alphaRepl.present()) {
				w.start_element(0, dml_shapeEffects_alphaRepl_literal);
				_alphaRepl_writer.get_writer(context(), &t()->alphaRepl.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_alphaRepl_literal);
			}
			if (t()->biLevel.present()) {
				w.start_element(0, dml_shapeEffects_biLevel_literal);
				_biLevel_writer.get_writer(context(), &t()->biLevel.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_biLevel_literal);
			}
			if (t()->blur.present()) {
				w.start_element(0, dml_shapeEffects_blur_literal);
				_blur_writer.get_writer(context(), &t()->blur.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_blur_literal);
			}
			if (t()->clrChange.present()) {
				w.start_element(0, dml_shapeEffects_clrChange_literal);
				_clrChange_writer.get_writer(context(), &t()->clrChange.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_clrChange_literal);
			}
			if (t()->clrRepl.present()) {
				w.start_element(0, dml_shapeEffects_clrRepl_literal);
				_clrRepl_writer.get_writer(context(), &t()->clrRepl.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_clrRepl_literal);
			}
			if (t()->duotone.present()) {
				w.start_element(0, dml_shapeEffects_duotone_literal);
				_duotone_writer.get_writer(context(), &t()->duotone.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_duotone_literal);
			}
			if (t()->fillOverlay.present()) {
				w.start_element(0, dml_shapeEffects_fillOverlay_literal);
				_fillOverlay_writer.get_writer(context(), &t()->fillOverlay.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_fillOverlay_literal);
			}
			if (t()->grayscl.present()) {
				w.start_element(0, dml_shapeEffects_grayscl_literal);
				_grayscl_writer.get_writer(context(), &t()->grayscl.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_grayscl_literal);
			}
			if (t()->hsl.present()) {
				w.start_element(0, dml_shapeEffects_hsl_literal);
				_hsl_writer.get_writer(context(), &t()->hsl.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_hsl_literal);
			}
			if (t()->lum.present()) {
				w.start_element(0, dml_shapeEffects_lum_literal);
				_lum_writer.get_writer(context(), &t()->lum.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_lum_literal);
			}
			if (t()->tint.present()) {
				w.start_element(0, dml_shapeEffects_tint_literal);
				_tint_writer.get_writer(context(), &t()->tint.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_tint_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, dml_shapeEffects_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_extLst_literal);
			}
		}

		void CT_EffectList_writer::write_target_to(xml_writer& w) {
			if (t()->blur.present()) {
				w.start_element(0, dml_shapeEffects_blur_literal);
				_blur_writer.get_writer(context(), &t()->blur.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_blur_literal);
			}
			if (t()->fillOverlay.present()) {
				w.start_element(0, dml_shapeEffects_fillOverlay_literal);
				_fillOverlay_writer.get_writer(context(), &t()->fillOverlay.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_fillOverlay_literal);
			}
			if (t()->glow.present()) {
				w.start_element(0, dml_shapeEffects_glow_literal);
				_glow_writer.get_writer(context(), &t()->glow.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_glow_literal);
			}
			if (t()->innerShdw.present()) {
				w.start_element(0, dml_shapeEffects_innerShdw_literal);
				_innerShdw_writer.get_writer(context(), &t()->innerShdw.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_innerShdw_literal);
			}
			if (t()->outerShdw.present()) {
				w.start_element(0, dml_shapeEffects_outerShdw_literal);
				_outerShdw_writer.get_writer(context(), &t()->outerShdw.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_outerShdw_literal);
			}
			if (t()->prstShdw.present()) {
				w.start_element(0, dml_shapeEffects_prstShdw_literal);
				_prstShdw_writer.get_writer(context(), &t()->prstShdw.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_prstShdw_literal);
			}
			if (t()->reflection.present()) {
				w.start_element(0, dml_shapeEffects_reflection_literal);
				_reflection_writer.get_writer(context(), &t()->reflection.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_reflection_literal);
			}
			if (t()->softEdge.present()) {
				w.start_element(0, dml_shapeEffects_softEdge_literal);
				_softEdge_writer.get_writer(context(), &t()->softEdge.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_softEdge_literal);
			}
		}

		void dml_shapeEffects_writer::write_target_to(xml_writer& w) {
			if (t()->blip.present()) {
				w.start_element(0, dml_shapeEffects_blip_literal);
					w.attribute(0, dml_shapeEffects_xmlns_literal, dml_shapeEffects_http_colon__slash__slash_schemas_dot_openxmlformats_dot_org_slash_drawingml_slash_2006_slash_main_literal);
					w.attribute(dml_shapeEffects_xmlns_literal, dml_shapeEffects_xsd_literal, dml_shapeEffects_http_colon__slash__slash_www_dot_w3_dot_org_slash_2001_slash_XMLSchema_literal);
				_blip_writer.get_writer(context(), &t()->blip.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_blip_literal);
			}
		}

		void CT_FillProperties_writer::write_target_to(xml_writer& w) {
			if (t()->noFill.present()) {
				w.start_element(0, dml_shapeEffects_noFill_literal);
				_noFill_writer.get_writer(context(), &t()->noFill.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_noFill_literal);
			}
			if (t()->solidFill.present()) {
				w.start_element(0, dml_shapeEffects_solidFill_literal);
				_solidFill_writer.get_writer(context(), &t()->solidFill.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_solidFill_literal);
			}
			if (t()->gradFill.present()) {
				w.start_element(0, dml_shapeEffects_gradFill_literal);
				_gradFill_writer.get_writer(context(), &t()->gradFill.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_gradFill_literal);
			}
			if (t()->blipFill.present()) {
				w.start_element(0, dml_shapeEffects_blipFill_literal);
				_blipFill_writer.get_writer(context(), &t()->blipFill.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_blipFill_literal);
			}
			if (t()->pattFill.present()) {
				w.start_element(0, dml_shapeEffects_pattFill_literal);
				_pattFill_writer.get_writer(context(), &t()->pattFill.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_pattFill_literal);
			}
			if (t()->grpFill.present()) {
				w.start_element(0, dml_shapeEffects_grpFill_literal);
				_grpFill_writer.get_writer(context(), &t()->grpFill.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_grpFill_literal);
			}
		}

		void CT_EffectProperties_writer::write_target_to(xml_writer& w) {
			if (t()->effectLst.present()) {
				w.start_element(0, dml_shapeEffects_effectLst_literal);
				_effectLst_writer.get_writer(context(), &t()->effectLst.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_effectLst_literal);
			}
			if (t()->effectDag.present()) {
				w.start_element(0, dml_shapeEffects_effectDag_literal);
				_effectDag_writer.get_writer(context(), &t()->effectDag.get())->write_target_to(w);
				w.end_element(0, dml_shapeEffects_effectDag_literal);
			}
		}

		void CT_BlendEffect_writer::write_target_to(xml_writer& w) {
			w.attribute(0, dml_shapeEffects_blend_literal, context()->serialize(t()->blend));
			w.start_element(0, dml_shapeEffects_cont_literal);
			_cont_writer.get_writer(context(), &t()->cont)->write_target_to(w);
			w.end_element(0, dml_shapeEffects_cont_literal);
		}

	}
}
