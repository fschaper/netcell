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


#include "dml-baseTypes_writers.hpp"
#include "dml-baseTypes_literals.hpp"

namespace drawingml
{
	namespace xio
	{
		void CT_OfficeArtExtension_writer::write_target_to(xml_writer& w) {
			if (t()->uri.present())
				w.attribute(0, dml_baseTypes_uri_literal, context()->serialize(t()->uri.get()));
		}

		void CT_OfficeArtExtensionList_writer::write_target_to(xml_writer& w) {
			for (size_t sqi = 0; sqi<t()->ext.size(); ++sqi) {
				w.start_element(0, dml_baseTypes_ext_literal);
				_ext_writer.get_writer(context(), &t()->ext[sqi])->write_target_to(w);
				w.end_element(0, dml_baseTypes_ext_literal);
			}
		}

		void ST_Percentage_writer::write_target_to(xml_writer& w) {
			w.write_element_value(context()->serialize(*t()));
		}

		void ST_Angle_writer::write_target_to(xml_writer& w) {
			w.write_element_value(context()->serialize(*t()));
		}

		void ST_PositiveFixedAngle_writer::write_target_to(xml_writer& w) {
			ST_Angle_writer::write_target_to(w);
		}

		void CT_SphereCoords_writer::write_target_to(xml_writer& w) {
			w.attribute(0, dml_baseTypes_lat_literal, context()->serialize(t()->lat));
			w.attribute(0, dml_baseTypes_lon_literal, context()->serialize(t()->lon));
			w.attribute(0, dml_baseTypes_rev_literal, context()->serialize(t()->rev));
		}

		void ST_PositivePercentage_writer::write_target_to(xml_writer& w) {
			ST_Percentage_writer::write_target_to(w);
		}

		void ST_Coordinate_writer::write_target_to(xml_writer& w) {
			w.write_element_value(context()->serialize(*t()));
		}

		void CT_Point3D_writer::write_target_to(xml_writer& w) {
			w.attribute(0, dml_baseTypes_x_literal, context()->serialize(t()->x));
			w.attribute(0, dml_baseTypes_y_literal, context()->serialize(t()->y));
			w.attribute(0, dml_baseTypes_z_literal, context()->serialize(t()->z));
		}

		void CT_Vector3D_writer::write_target_to(xml_writer& w) {
			w.attribute(0, dml_baseTypes_dx_literal, context()->serialize(t()->dx));
			w.attribute(0, dml_baseTypes_dy_literal, context()->serialize(t()->dy));
			w.attribute(0, dml_baseTypes_dz_literal, context()->serialize(t()->dz));
		}

		void ST_PositiveCoordinate_writer::write_target_to(xml_writer& w) {
			w.write_element_value(context()->serialize(*t()));
		}

		void ST_PositiveFixedPercentage_writer::write_target_to(xml_writer& w) {
			ST_Percentage_writer::write_target_to(w);
		}

		void CT_PositiveFixedPercentage_writer::write_target_to(xml_writer& w) {
			w.attribute(0, dml_baseTypes_val_literal, context()->serialize(t()->val));
		}

		void CT_ComplementTransform_writer::write_target_to(xml_writer& w) {
		}

		void CT_InverseTransform_writer::write_target_to(xml_writer& w) {
		}

		void CT_GrayscaleTransform_writer::write_target_to(xml_writer& w) {
		}

		void ST_FixedPercentage_writer::write_target_to(xml_writer& w) {
			ST_Percentage_writer::write_target_to(w);
		}

		void CT_FixedPercentage_writer::write_target_to(xml_writer& w) {
			w.attribute(0, dml_baseTypes_val_literal, context()->serialize(t()->val));
		}

		void CT_PositivePercentage_writer::write_target_to(xml_writer& w) {
			w.attribute(0, dml_baseTypes_val_literal, context()->serialize(t()->val));
		}

		void CT_PositiveFixedAngle_writer::write_target_to(xml_writer& w) {
			w.attribute(0, dml_baseTypes_val_literal, context()->serialize(t()->val));
		}

		void CT_Angle_writer::write_target_to(xml_writer& w) {
			w.attribute(0, dml_baseTypes_val_literal, context()->serialize(t()->val));
		}

		void CT_Percentage_writer::write_target_to(xml_writer& w) {
			w.attribute(0, dml_baseTypes_val_literal, context()->serialize(t()->val));
		}

		void CT_GammaTransform_writer::write_target_to(xml_writer& w) {
		}

		void CT_InverseGammaTransform_writer::write_target_to(xml_writer& w) {
		}

		void CT_ScRgbColor_writer::write_target_to(xml_writer& w) {
			w.attribute(0, dml_baseTypes_r_literal, context()->serialize(t()->r));
			w.attribute(0, dml_baseTypes_g_literal, context()->serialize(t()->g));
			w.attribute(0, dml_baseTypes_b_literal, context()->serialize(t()->b));
			if (t()->tint.present()) {
				w.start_element(0, dml_baseTypes_tint_literal);
				_tint_writer.get_writer(context(), &t()->tint.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_tint_literal);
			}
			if (t()->shade.present()) {
				w.start_element(0, dml_baseTypes_shade_literal);
				_shade_writer.get_writer(context(), &t()->shade.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_shade_literal);
			}
			if (t()->comp.present()) {
				w.start_element(0, dml_baseTypes_comp_literal);
				_comp_writer.get_writer(context(), &t()->comp.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_comp_literal);
			}
			if (t()->inv.present()) {
				w.start_element(0, dml_baseTypes_inv_literal);
				_inv_writer.get_writer(context(), &t()->inv.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_inv_literal);
			}
			if (t()->gray.present()) {
				w.start_element(0, dml_baseTypes_gray_literal);
				_gray_writer.get_writer(context(), &t()->gray.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_gray_literal);
			}
			if (t()->alpha.present()) {
				w.start_element(0, dml_baseTypes_alpha_literal);
				_alpha_writer.get_writer(context(), &t()->alpha.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_alpha_literal);
			}
			if (t()->alphaOff.present()) {
				w.start_element(0, dml_baseTypes_alphaOff_literal);
				_alphaOff_writer.get_writer(context(), &t()->alphaOff.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_alphaOff_literal);
			}
			if (t()->alphaMod.present()) {
				w.start_element(0, dml_baseTypes_alphaMod_literal);
				_alphaMod_writer.get_writer(context(), &t()->alphaMod.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_alphaMod_literal);
			}
			if (t()->hue.present()) {
				w.start_element(0, dml_baseTypes_hue_literal);
				_hue_writer.get_writer(context(), &t()->hue.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_hue_literal);
			}
			if (t()->hueOff.present()) {
				w.start_element(0, dml_baseTypes_hueOff_literal);
				_hueOff_writer.get_writer(context(), &t()->hueOff.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_hueOff_literal);
			}
			if (t()->hueMod.present()) {
				w.start_element(0, dml_baseTypes_hueMod_literal);
				_hueMod_writer.get_writer(context(), &t()->hueMod.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_hueMod_literal);
			}
			if (t()->sat.present()) {
				w.start_element(0, dml_baseTypes_sat_literal);
				_sat_writer.get_writer(context(), &t()->sat.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_sat_literal);
			}
			if (t()->satOff.present()) {
				w.start_element(0, dml_baseTypes_satOff_literal);
				_satOff_writer.get_writer(context(), &t()->satOff.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_satOff_literal);
			}
			if (t()->satMod.present()) {
				w.start_element(0, dml_baseTypes_satMod_literal);
				_satMod_writer.get_writer(context(), &t()->satMod.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_satMod_literal);
			}
			if (t()->lum.present()) {
				w.start_element(0, dml_baseTypes_lum_literal);
				_lum_writer.get_writer(context(), &t()->lum.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_lum_literal);
			}
			if (t()->lumOff.present()) {
				w.start_element(0, dml_baseTypes_lumOff_literal);
				_lumOff_writer.get_writer(context(), &t()->lumOff.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_lumOff_literal);
			}
			if (t()->lumMod.present()) {
				w.start_element(0, dml_baseTypes_lumMod_literal);
				_lumMod_writer.get_writer(context(), &t()->lumMod.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_lumMod_literal);
			}
			if (t()->red.present()) {
				w.start_element(0, dml_baseTypes_red_literal);
				_red_writer.get_writer(context(), &t()->red.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_red_literal);
			}
			if (t()->redOff.present()) {
				w.start_element(0, dml_baseTypes_redOff_literal);
				_redOff_writer.get_writer(context(), &t()->redOff.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_redOff_literal);
			}
			if (t()->redMod.present()) {
				w.start_element(0, dml_baseTypes_redMod_literal);
				_redMod_writer.get_writer(context(), &t()->redMod.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_redMod_literal);
			}
			if (t()->green.present()) {
				w.start_element(0, dml_baseTypes_green_literal);
				_green_writer.get_writer(context(), &t()->green.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_green_literal);
			}
			if (t()->greenOff.present()) {
				w.start_element(0, dml_baseTypes_greenOff_literal);
				_greenOff_writer.get_writer(context(), &t()->greenOff.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_greenOff_literal);
			}
			if (t()->greenMod.present()) {
				w.start_element(0, dml_baseTypes_greenMod_literal);
				_greenMod_writer.get_writer(context(), &t()->greenMod.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_greenMod_literal);
			}
			if (t()->blue.present()) {
				w.start_element(0, dml_baseTypes_blue_literal);
				_blue_writer.get_writer(context(), &t()->blue.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_blue_literal);
			}
			if (t()->blueOff.present()) {
				w.start_element(0, dml_baseTypes_blueOff_literal);
				_blueOff_writer.get_writer(context(), &t()->blueOff.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_blueOff_literal);
			}
			if (t()->blueMod.present()) {
				w.start_element(0, dml_baseTypes_blueMod_literal);
				_blueMod_writer.get_writer(context(), &t()->blueMod.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_blueMod_literal);
			}
			if (t()->gamma.present()) {
				w.start_element(0, dml_baseTypes_gamma_literal);
				_gamma_writer.get_writer(context(), &t()->gamma.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_gamma_literal);
			}
			if (t()->invGamma.present()) {
				w.start_element(0, dml_baseTypes_invGamma_literal);
				_invGamma_writer.get_writer(context(), &t()->invGamma.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_invGamma_literal);
			}
		}

		void ST_HexBinary3_writer::write_target_to(xml_writer& w) {
			w.write_element_value(context()->serialize(*t()));
		}

		void CT_SRgbColor_writer::write_target_to(xml_writer& w) {
			w.attribute(0, dml_baseTypes_val_literal, context()->serialize(t()->val));
			if (t()->tint.present()) {
				w.start_element(0, dml_baseTypes_tint_literal);
				_tint_writer.get_writer(context(), &t()->tint.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_tint_literal);
			}
			if (t()->shade.present()) {
				w.start_element(0, dml_baseTypes_shade_literal);
				_shade_writer.get_writer(context(), &t()->shade.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_shade_literal);
			}
			if (t()->comp.present()) {
				w.start_element(0, dml_baseTypes_comp_literal);
				_comp_writer.get_writer(context(), &t()->comp.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_comp_literal);
			}
			if (t()->inv.present()) {
				w.start_element(0, dml_baseTypes_inv_literal);
				_inv_writer.get_writer(context(), &t()->inv.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_inv_literal);
			}
			if (t()->gray.present()) {
				w.start_element(0, dml_baseTypes_gray_literal);
				_gray_writer.get_writer(context(), &t()->gray.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_gray_literal);
			}
			if (t()->alpha.present()) {
				w.start_element(0, dml_baseTypes_alpha_literal);
				_alpha_writer.get_writer(context(), &t()->alpha.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_alpha_literal);
			}
			if (t()->alphaOff.present()) {
				w.start_element(0, dml_baseTypes_alphaOff_literal);
				_alphaOff_writer.get_writer(context(), &t()->alphaOff.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_alphaOff_literal);
			}
			if (t()->alphaMod.present()) {
				w.start_element(0, dml_baseTypes_alphaMod_literal);
				_alphaMod_writer.get_writer(context(), &t()->alphaMod.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_alphaMod_literal);
			}
			if (t()->hue.present()) {
				w.start_element(0, dml_baseTypes_hue_literal);
				_hue_writer.get_writer(context(), &t()->hue.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_hue_literal);
			}
			if (t()->hueOff.present()) {
				w.start_element(0, dml_baseTypes_hueOff_literal);
				_hueOff_writer.get_writer(context(), &t()->hueOff.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_hueOff_literal);
			}
			if (t()->hueMod.present()) {
				w.start_element(0, dml_baseTypes_hueMod_literal);
				_hueMod_writer.get_writer(context(), &t()->hueMod.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_hueMod_literal);
			}
			if (t()->sat.present()) {
				w.start_element(0, dml_baseTypes_sat_literal);
				_sat_writer.get_writer(context(), &t()->sat.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_sat_literal);
			}
			if (t()->satOff.present()) {
				w.start_element(0, dml_baseTypes_satOff_literal);
				_satOff_writer.get_writer(context(), &t()->satOff.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_satOff_literal);
			}
			if (t()->satMod.present()) {
				w.start_element(0, dml_baseTypes_satMod_literal);
				_satMod_writer.get_writer(context(), &t()->satMod.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_satMod_literal);
			}
			if (t()->lum.present()) {
				w.start_element(0, dml_baseTypes_lum_literal);
				_lum_writer.get_writer(context(), &t()->lum.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_lum_literal);
			}
			if (t()->lumOff.present()) {
				w.start_element(0, dml_baseTypes_lumOff_literal);
				_lumOff_writer.get_writer(context(), &t()->lumOff.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_lumOff_literal);
			}
			if (t()->lumMod.present()) {
				w.start_element(0, dml_baseTypes_lumMod_literal);
				_lumMod_writer.get_writer(context(), &t()->lumMod.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_lumMod_literal);
			}
			if (t()->red.present()) {
				w.start_element(0, dml_baseTypes_red_literal);
				_red_writer.get_writer(context(), &t()->red.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_red_literal);
			}
			if (t()->redOff.present()) {
				w.start_element(0, dml_baseTypes_redOff_literal);
				_redOff_writer.get_writer(context(), &t()->redOff.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_redOff_literal);
			}
			if (t()->redMod.present()) {
				w.start_element(0, dml_baseTypes_redMod_literal);
				_redMod_writer.get_writer(context(), &t()->redMod.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_redMod_literal);
			}
			if (t()->green.present()) {
				w.start_element(0, dml_baseTypes_green_literal);
				_green_writer.get_writer(context(), &t()->green.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_green_literal);
			}
			if (t()->greenOff.present()) {
				w.start_element(0, dml_baseTypes_greenOff_literal);
				_greenOff_writer.get_writer(context(), &t()->greenOff.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_greenOff_literal);
			}
			if (t()->greenMod.present()) {
				w.start_element(0, dml_baseTypes_greenMod_literal);
				_greenMod_writer.get_writer(context(), &t()->greenMod.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_greenMod_literal);
			}
			if (t()->blue.present()) {
				w.start_element(0, dml_baseTypes_blue_literal);
				_blue_writer.get_writer(context(), &t()->blue.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_blue_literal);
			}
			if (t()->blueOff.present()) {
				w.start_element(0, dml_baseTypes_blueOff_literal);
				_blueOff_writer.get_writer(context(), &t()->blueOff.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_blueOff_literal);
			}
			if (t()->blueMod.present()) {
				w.start_element(0, dml_baseTypes_blueMod_literal);
				_blueMod_writer.get_writer(context(), &t()->blueMod.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_blueMod_literal);
			}
			if (t()->gamma.present()) {
				w.start_element(0, dml_baseTypes_gamma_literal);
				_gamma_writer.get_writer(context(), &t()->gamma.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_gamma_literal);
			}
			if (t()->invGamma.present()) {
				w.start_element(0, dml_baseTypes_invGamma_literal);
				_invGamma_writer.get_writer(context(), &t()->invGamma.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_invGamma_literal);
			}
		}

		void CT_HslColor_writer::write_target_to(xml_writer& w) {
			w.attribute(0, dml_baseTypes_hue_literal, context()->serialize(t()->hue_attr));
			w.attribute(0, dml_baseTypes_sat_literal, context()->serialize(t()->sat_attr));
			w.attribute(0, dml_baseTypes_lum_literal, context()->serialize(t()->lum_attr));
			if (t()->tint.present()) {
				w.start_element(0, dml_baseTypes_tint_literal);
				_tint_writer.get_writer(context(), &t()->tint.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_tint_literal);
			}
			if (t()->shade.present()) {
				w.start_element(0, dml_baseTypes_shade_literal);
				_shade_writer.get_writer(context(), &t()->shade.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_shade_literal);
			}
			if (t()->comp.present()) {
				w.start_element(0, dml_baseTypes_comp_literal);
				_comp_writer.get_writer(context(), &t()->comp.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_comp_literal);
			}
			if (t()->inv.present()) {
				w.start_element(0, dml_baseTypes_inv_literal);
				_inv_writer.get_writer(context(), &t()->inv.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_inv_literal);
			}
			if (t()->gray.present()) {
				w.start_element(0, dml_baseTypes_gray_literal);
				_gray_writer.get_writer(context(), &t()->gray.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_gray_literal);
			}
			if (t()->alpha.present()) {
				w.start_element(0, dml_baseTypes_alpha_literal);
				_alpha_writer.get_writer(context(), &t()->alpha.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_alpha_literal);
			}
			if (t()->alphaOff.present()) {
				w.start_element(0, dml_baseTypes_alphaOff_literal);
				_alphaOff_writer.get_writer(context(), &t()->alphaOff.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_alphaOff_literal);
			}
			if (t()->alphaMod.present()) {
				w.start_element(0, dml_baseTypes_alphaMod_literal);
				_alphaMod_writer.get_writer(context(), &t()->alphaMod.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_alphaMod_literal);
			}
			if (t()->hue.present()) {
				w.start_element(0, dml_baseTypes_hue_literal);
				_hue_writer.get_writer(context(), &t()->hue.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_hue_literal);
			}
			if (t()->hueOff.present()) {
				w.start_element(0, dml_baseTypes_hueOff_literal);
				_hueOff_writer.get_writer(context(), &t()->hueOff.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_hueOff_literal);
			}
			if (t()->hueMod.present()) {
				w.start_element(0, dml_baseTypes_hueMod_literal);
				_hueMod_writer.get_writer(context(), &t()->hueMod.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_hueMod_literal);
			}
			if (t()->sat.present()) {
				w.start_element(0, dml_baseTypes_sat_literal);
				_sat_writer.get_writer(context(), &t()->sat.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_sat_literal);
			}
			if (t()->satOff.present()) {
				w.start_element(0, dml_baseTypes_satOff_literal);
				_satOff_writer.get_writer(context(), &t()->satOff.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_satOff_literal);
			}
			if (t()->satMod.present()) {
				w.start_element(0, dml_baseTypes_satMod_literal);
				_satMod_writer.get_writer(context(), &t()->satMod.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_satMod_literal);
			}
			if (t()->lum.present()) {
				w.start_element(0, dml_baseTypes_lum_literal);
				_lum_writer.get_writer(context(), &t()->lum.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_lum_literal);
			}
			if (t()->lumOff.present()) {
				w.start_element(0, dml_baseTypes_lumOff_literal);
				_lumOff_writer.get_writer(context(), &t()->lumOff.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_lumOff_literal);
			}
			if (t()->lumMod.present()) {
				w.start_element(0, dml_baseTypes_lumMod_literal);
				_lumMod_writer.get_writer(context(), &t()->lumMod.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_lumMod_literal);
			}
			if (t()->red.present()) {
				w.start_element(0, dml_baseTypes_red_literal);
				_red_writer.get_writer(context(), &t()->red.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_red_literal);
			}
			if (t()->redOff.present()) {
				w.start_element(0, dml_baseTypes_redOff_literal);
				_redOff_writer.get_writer(context(), &t()->redOff.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_redOff_literal);
			}
			if (t()->redMod.present()) {
				w.start_element(0, dml_baseTypes_redMod_literal);
				_redMod_writer.get_writer(context(), &t()->redMod.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_redMod_literal);
			}
			if (t()->green.present()) {
				w.start_element(0, dml_baseTypes_green_literal);
				_green_writer.get_writer(context(), &t()->green.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_green_literal);
			}
			if (t()->greenOff.present()) {
				w.start_element(0, dml_baseTypes_greenOff_literal);
				_greenOff_writer.get_writer(context(), &t()->greenOff.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_greenOff_literal);
			}
			if (t()->greenMod.present()) {
				w.start_element(0, dml_baseTypes_greenMod_literal);
				_greenMod_writer.get_writer(context(), &t()->greenMod.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_greenMod_literal);
			}
			if (t()->blue.present()) {
				w.start_element(0, dml_baseTypes_blue_literal);
				_blue_writer.get_writer(context(), &t()->blue.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_blue_literal);
			}
			if (t()->blueOff.present()) {
				w.start_element(0, dml_baseTypes_blueOff_literal);
				_blueOff_writer.get_writer(context(), &t()->blueOff.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_blueOff_literal);
			}
			if (t()->blueMod.present()) {
				w.start_element(0, dml_baseTypes_blueMod_literal);
				_blueMod_writer.get_writer(context(), &t()->blueMod.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_blueMod_literal);
			}
			if (t()->gamma.present()) {
				w.start_element(0, dml_baseTypes_gamma_literal);
				_gamma_writer.get_writer(context(), &t()->gamma.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_gamma_literal);
			}
			if (t()->invGamma.present()) {
				w.start_element(0, dml_baseTypes_invGamma_literal);
				_invGamma_writer.get_writer(context(), &t()->invGamma.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_invGamma_literal);
			}
		}

		void CT_SystemColor_writer::write_target_to(xml_writer& w) {
			w.attribute(0, dml_baseTypes_val_literal, context()->serialize(t()->val));
			if (t()->lastClr.present())
				w.attribute(0, dml_baseTypes_lastClr_literal, context()->serialize(t()->lastClr.get()));
			if (t()->tint.present()) {
				w.start_element(0, dml_baseTypes_tint_literal);
				_tint_writer.get_writer(context(), &t()->tint.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_tint_literal);
			}
			if (t()->shade.present()) {
				w.start_element(0, dml_baseTypes_shade_literal);
				_shade_writer.get_writer(context(), &t()->shade.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_shade_literal);
			}
			if (t()->comp.present()) {
				w.start_element(0, dml_baseTypes_comp_literal);
				_comp_writer.get_writer(context(), &t()->comp.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_comp_literal);
			}
			if (t()->inv.present()) {
				w.start_element(0, dml_baseTypes_inv_literal);
				_inv_writer.get_writer(context(), &t()->inv.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_inv_literal);
			}
			if (t()->gray.present()) {
				w.start_element(0, dml_baseTypes_gray_literal);
				_gray_writer.get_writer(context(), &t()->gray.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_gray_literal);
			}
			if (t()->alpha.present()) {
				w.start_element(0, dml_baseTypes_alpha_literal);
				_alpha_writer.get_writer(context(), &t()->alpha.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_alpha_literal);
			}
			if (t()->alphaOff.present()) {
				w.start_element(0, dml_baseTypes_alphaOff_literal);
				_alphaOff_writer.get_writer(context(), &t()->alphaOff.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_alphaOff_literal);
			}
			if (t()->alphaMod.present()) {
				w.start_element(0, dml_baseTypes_alphaMod_literal);
				_alphaMod_writer.get_writer(context(), &t()->alphaMod.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_alphaMod_literal);
			}
			if (t()->hue.present()) {
				w.start_element(0, dml_baseTypes_hue_literal);
				_hue_writer.get_writer(context(), &t()->hue.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_hue_literal);
			}
			if (t()->hueOff.present()) {
				w.start_element(0, dml_baseTypes_hueOff_literal);
				_hueOff_writer.get_writer(context(), &t()->hueOff.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_hueOff_literal);
			}
			if (t()->hueMod.present()) {
				w.start_element(0, dml_baseTypes_hueMod_literal);
				_hueMod_writer.get_writer(context(), &t()->hueMod.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_hueMod_literal);
			}
			if (t()->sat.present()) {
				w.start_element(0, dml_baseTypes_sat_literal);
				_sat_writer.get_writer(context(), &t()->sat.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_sat_literal);
			}
			if (t()->satOff.present()) {
				w.start_element(0, dml_baseTypes_satOff_literal);
				_satOff_writer.get_writer(context(), &t()->satOff.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_satOff_literal);
			}
			if (t()->satMod.present()) {
				w.start_element(0, dml_baseTypes_satMod_literal);
				_satMod_writer.get_writer(context(), &t()->satMod.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_satMod_literal);
			}
			if (t()->lum.present()) {
				w.start_element(0, dml_baseTypes_lum_literal);
				_lum_writer.get_writer(context(), &t()->lum.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_lum_literal);
			}
			if (t()->lumOff.present()) {
				w.start_element(0, dml_baseTypes_lumOff_literal);
				_lumOff_writer.get_writer(context(), &t()->lumOff.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_lumOff_literal);
			}
			if (t()->lumMod.present()) {
				w.start_element(0, dml_baseTypes_lumMod_literal);
				_lumMod_writer.get_writer(context(), &t()->lumMod.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_lumMod_literal);
			}
			if (t()->red.present()) {
				w.start_element(0, dml_baseTypes_red_literal);
				_red_writer.get_writer(context(), &t()->red.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_red_literal);
			}
			if (t()->redOff.present()) {
				w.start_element(0, dml_baseTypes_redOff_literal);
				_redOff_writer.get_writer(context(), &t()->redOff.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_redOff_literal);
			}
			if (t()->redMod.present()) {
				w.start_element(0, dml_baseTypes_redMod_literal);
				_redMod_writer.get_writer(context(), &t()->redMod.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_redMod_literal);
			}
			if (t()->green.present()) {
				w.start_element(0, dml_baseTypes_green_literal);
				_green_writer.get_writer(context(), &t()->green.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_green_literal);
			}
			if (t()->greenOff.present()) {
				w.start_element(0, dml_baseTypes_greenOff_literal);
				_greenOff_writer.get_writer(context(), &t()->greenOff.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_greenOff_literal);
			}
			if (t()->greenMod.present()) {
				w.start_element(0, dml_baseTypes_greenMod_literal);
				_greenMod_writer.get_writer(context(), &t()->greenMod.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_greenMod_literal);
			}
			if (t()->blue.present()) {
				w.start_element(0, dml_baseTypes_blue_literal);
				_blue_writer.get_writer(context(), &t()->blue.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_blue_literal);
			}
			if (t()->blueOff.present()) {
				w.start_element(0, dml_baseTypes_blueOff_literal);
				_blueOff_writer.get_writer(context(), &t()->blueOff.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_blueOff_literal);
			}
			if (t()->blueMod.present()) {
				w.start_element(0, dml_baseTypes_blueMod_literal);
				_blueMod_writer.get_writer(context(), &t()->blueMod.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_blueMod_literal);
			}
			if (t()->gamma.present()) {
				w.start_element(0, dml_baseTypes_gamma_literal);
				_gamma_writer.get_writer(context(), &t()->gamma.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_gamma_literal);
			}
			if (t()->invGamma.present()) {
				w.start_element(0, dml_baseTypes_invGamma_literal);
				_invGamma_writer.get_writer(context(), &t()->invGamma.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_invGamma_literal);
			}
		}

		void CT_SchemeColor_writer::write_target_to(xml_writer& w) {
			w.attribute(0, dml_baseTypes_val_literal, context()->serialize(t()->val));
			if (t()->tint.present()) {
				w.start_element(0, dml_baseTypes_tint_literal);
				_tint_writer.get_writer(context(), &t()->tint.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_tint_literal);
			}
			if (t()->shade.present()) {
				w.start_element(0, dml_baseTypes_shade_literal);
				_shade_writer.get_writer(context(), &t()->shade.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_shade_literal);
			}
			if (t()->comp.present()) {
				w.start_element(0, dml_baseTypes_comp_literal);
				_comp_writer.get_writer(context(), &t()->comp.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_comp_literal);
			}
			if (t()->inv.present()) {
				w.start_element(0, dml_baseTypes_inv_literal);
				_inv_writer.get_writer(context(), &t()->inv.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_inv_literal);
			}
			if (t()->gray.present()) {
				w.start_element(0, dml_baseTypes_gray_literal);
				_gray_writer.get_writer(context(), &t()->gray.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_gray_literal);
			}
			if (t()->alpha.present()) {
				w.start_element(0, dml_baseTypes_alpha_literal);
				_alpha_writer.get_writer(context(), &t()->alpha.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_alpha_literal);
			}
			if (t()->alphaOff.present()) {
				w.start_element(0, dml_baseTypes_alphaOff_literal);
				_alphaOff_writer.get_writer(context(), &t()->alphaOff.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_alphaOff_literal);
			}
			if (t()->alphaMod.present()) {
				w.start_element(0, dml_baseTypes_alphaMod_literal);
				_alphaMod_writer.get_writer(context(), &t()->alphaMod.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_alphaMod_literal);
			}
			if (t()->hue.present()) {
				w.start_element(0, dml_baseTypes_hue_literal);
				_hue_writer.get_writer(context(), &t()->hue.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_hue_literal);
			}
			if (t()->hueOff.present()) {
				w.start_element(0, dml_baseTypes_hueOff_literal);
				_hueOff_writer.get_writer(context(), &t()->hueOff.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_hueOff_literal);
			}
			if (t()->hueMod.present()) {
				w.start_element(0, dml_baseTypes_hueMod_literal);
				_hueMod_writer.get_writer(context(), &t()->hueMod.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_hueMod_literal);
			}
			if (t()->sat.present()) {
				w.start_element(0, dml_baseTypes_sat_literal);
				_sat_writer.get_writer(context(), &t()->sat.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_sat_literal);
			}
			if (t()->satOff.present()) {
				w.start_element(0, dml_baseTypes_satOff_literal);
				_satOff_writer.get_writer(context(), &t()->satOff.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_satOff_literal);
			}
			if (t()->satMod.present()) {
				w.start_element(0, dml_baseTypes_satMod_literal);
				_satMod_writer.get_writer(context(), &t()->satMod.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_satMod_literal);
			}
			if (t()->lum.present()) {
				w.start_element(0, dml_baseTypes_lum_literal);
				_lum_writer.get_writer(context(), &t()->lum.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_lum_literal);
			}
			if (t()->lumOff.present()) {
				w.start_element(0, dml_baseTypes_lumOff_literal);
				_lumOff_writer.get_writer(context(), &t()->lumOff.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_lumOff_literal);
			}
			if (t()->lumMod.present()) {
				w.start_element(0, dml_baseTypes_lumMod_literal);
				_lumMod_writer.get_writer(context(), &t()->lumMod.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_lumMod_literal);
			}
			if (t()->red.present()) {
				w.start_element(0, dml_baseTypes_red_literal);
				_red_writer.get_writer(context(), &t()->red.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_red_literal);
			}
			if (t()->redOff.present()) {
				w.start_element(0, dml_baseTypes_redOff_literal);
				_redOff_writer.get_writer(context(), &t()->redOff.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_redOff_literal);
			}
			if (t()->redMod.present()) {
				w.start_element(0, dml_baseTypes_redMod_literal);
				_redMod_writer.get_writer(context(), &t()->redMod.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_redMod_literal);
			}
			if (t()->green.present()) {
				w.start_element(0, dml_baseTypes_green_literal);
				_green_writer.get_writer(context(), &t()->green.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_green_literal);
			}
			if (t()->greenOff.present()) {
				w.start_element(0, dml_baseTypes_greenOff_literal);
				_greenOff_writer.get_writer(context(), &t()->greenOff.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_greenOff_literal);
			}
			if (t()->greenMod.present()) {
				w.start_element(0, dml_baseTypes_greenMod_literal);
				_greenMod_writer.get_writer(context(), &t()->greenMod.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_greenMod_literal);
			}
			if (t()->blue.present()) {
				w.start_element(0, dml_baseTypes_blue_literal);
				_blue_writer.get_writer(context(), &t()->blue.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_blue_literal);
			}
			if (t()->blueOff.present()) {
				w.start_element(0, dml_baseTypes_blueOff_literal);
				_blueOff_writer.get_writer(context(), &t()->blueOff.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_blueOff_literal);
			}
			if (t()->blueMod.present()) {
				w.start_element(0, dml_baseTypes_blueMod_literal);
				_blueMod_writer.get_writer(context(), &t()->blueMod.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_blueMod_literal);
			}
			if (t()->gamma.present()) {
				w.start_element(0, dml_baseTypes_gamma_literal);
				_gamma_writer.get_writer(context(), &t()->gamma.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_gamma_literal);
			}
			if (t()->invGamma.present()) {
				w.start_element(0, dml_baseTypes_invGamma_literal);
				_invGamma_writer.get_writer(context(), &t()->invGamma.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_invGamma_literal);
			}
		}

		void CT_PresetColor_writer::write_target_to(xml_writer& w) {
			if (t()->val.present())
				w.attribute(0, dml_baseTypes_val_literal, context()->serialize(t()->val.get()));
			if (t()->tint.present()) {
				w.start_element(0, dml_baseTypes_tint_literal);
				_tint_writer.get_writer(context(), &t()->tint.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_tint_literal);
			}
			if (t()->shade.present()) {
				w.start_element(0, dml_baseTypes_shade_literal);
				_shade_writer.get_writer(context(), &t()->shade.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_shade_literal);
			}
			if (t()->comp.present()) {
				w.start_element(0, dml_baseTypes_comp_literal);
				_comp_writer.get_writer(context(), &t()->comp.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_comp_literal);
			}
			if (t()->inv.present()) {
				w.start_element(0, dml_baseTypes_inv_literal);
				_inv_writer.get_writer(context(), &t()->inv.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_inv_literal);
			}
			if (t()->gray.present()) {
				w.start_element(0, dml_baseTypes_gray_literal);
				_gray_writer.get_writer(context(), &t()->gray.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_gray_literal);
			}
			if (t()->alpha.present()) {
				w.start_element(0, dml_baseTypes_alpha_literal);
				_alpha_writer.get_writer(context(), &t()->alpha.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_alpha_literal);
			}
			if (t()->alphaOff.present()) {
				w.start_element(0, dml_baseTypes_alphaOff_literal);
				_alphaOff_writer.get_writer(context(), &t()->alphaOff.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_alphaOff_literal);
			}
			if (t()->alphaMod.present()) {
				w.start_element(0, dml_baseTypes_alphaMod_literal);
				_alphaMod_writer.get_writer(context(), &t()->alphaMod.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_alphaMod_literal);
			}
			if (t()->hue.present()) {
				w.start_element(0, dml_baseTypes_hue_literal);
				_hue_writer.get_writer(context(), &t()->hue.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_hue_literal);
			}
			if (t()->hueOff.present()) {
				w.start_element(0, dml_baseTypes_hueOff_literal);
				_hueOff_writer.get_writer(context(), &t()->hueOff.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_hueOff_literal);
			}
			if (t()->hueMod.present()) {
				w.start_element(0, dml_baseTypes_hueMod_literal);
				_hueMod_writer.get_writer(context(), &t()->hueMod.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_hueMod_literal);
			}
			if (t()->sat.present()) {
				w.start_element(0, dml_baseTypes_sat_literal);
				_sat_writer.get_writer(context(), &t()->sat.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_sat_literal);
			}
			if (t()->satOff.present()) {
				w.start_element(0, dml_baseTypes_satOff_literal);
				_satOff_writer.get_writer(context(), &t()->satOff.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_satOff_literal);
			}
			if (t()->satMod.present()) {
				w.start_element(0, dml_baseTypes_satMod_literal);
				_satMod_writer.get_writer(context(), &t()->satMod.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_satMod_literal);
			}
			if (t()->lum.present()) {
				w.start_element(0, dml_baseTypes_lum_literal);
				_lum_writer.get_writer(context(), &t()->lum.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_lum_literal);
			}
			if (t()->lumOff.present()) {
				w.start_element(0, dml_baseTypes_lumOff_literal);
				_lumOff_writer.get_writer(context(), &t()->lumOff.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_lumOff_literal);
			}
			if (t()->lumMod.present()) {
				w.start_element(0, dml_baseTypes_lumMod_literal);
				_lumMod_writer.get_writer(context(), &t()->lumMod.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_lumMod_literal);
			}
			if (t()->red.present()) {
				w.start_element(0, dml_baseTypes_red_literal);
				_red_writer.get_writer(context(), &t()->red.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_red_literal);
			}
			if (t()->redOff.present()) {
				w.start_element(0, dml_baseTypes_redOff_literal);
				_redOff_writer.get_writer(context(), &t()->redOff.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_redOff_literal);
			}
			if (t()->redMod.present()) {
				w.start_element(0, dml_baseTypes_redMod_literal);
				_redMod_writer.get_writer(context(), &t()->redMod.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_redMod_literal);
			}
			if (t()->green.present()) {
				w.start_element(0, dml_baseTypes_green_literal);
				_green_writer.get_writer(context(), &t()->green.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_green_literal);
			}
			if (t()->greenOff.present()) {
				w.start_element(0, dml_baseTypes_greenOff_literal);
				_greenOff_writer.get_writer(context(), &t()->greenOff.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_greenOff_literal);
			}
			if (t()->greenMod.present()) {
				w.start_element(0, dml_baseTypes_greenMod_literal);
				_greenMod_writer.get_writer(context(), &t()->greenMod.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_greenMod_literal);
			}
			if (t()->blue.present()) {
				w.start_element(0, dml_baseTypes_blue_literal);
				_blue_writer.get_writer(context(), &t()->blue.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_blue_literal);
			}
			if (t()->blueOff.present()) {
				w.start_element(0, dml_baseTypes_blueOff_literal);
				_blueOff_writer.get_writer(context(), &t()->blueOff.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_blueOff_literal);
			}
			if (t()->blueMod.present()) {
				w.start_element(0, dml_baseTypes_blueMod_literal);
				_blueMod_writer.get_writer(context(), &t()->blueMod.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_blueMod_literal);
			}
			if (t()->gamma.present()) {
				w.start_element(0, dml_baseTypes_gamma_literal);
				_gamma_writer.get_writer(context(), &t()->gamma.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_gamma_literal);
			}
			if (t()->invGamma.present()) {
				w.start_element(0, dml_baseTypes_invGamma_literal);
				_invGamma_writer.get_writer(context(), &t()->invGamma.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_invGamma_literal);
			}
		}

		void CT_Color_writer::write_target_to(xml_writer& w) {
			if (t()->scrgbClr.present()) {
				w.start_element(0, dml_baseTypes_scrgbClr_literal);
				_scrgbClr_writer.get_writer(context(), &t()->scrgbClr.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_scrgbClr_literal);
			}
			if (t()->srgbClr.present()) {
				w.start_element(0, dml_baseTypes_srgbClr_literal);
				_srgbClr_writer.get_writer(context(), &t()->srgbClr.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_srgbClr_literal);
			}
			if (t()->hslClr.present()) {
				w.start_element(0, dml_baseTypes_hslClr_literal);
				_hslClr_writer.get_writer(context(), &t()->hslClr.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_hslClr_literal);
			}
			if (t()->sysClr.present()) {
				w.start_element(0, dml_baseTypes_sysClr_literal);
				_sysClr_writer.get_writer(context(), &t()->sysClr.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_sysClr_literal);
			}
			if (t()->schemeClr.present()) {
				w.start_element(0, dml_baseTypes_schemeClr_literal);
				_schemeClr_writer.get_writer(context(), &t()->schemeClr.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_schemeClr_literal);
			}
			if (t()->prstClr.present()) {
				w.start_element(0, dml_baseTypes_prstClr_literal);
				_prstClr_writer.get_writer(context(), &t()->prstClr.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_prstClr_literal);
			}
		}

		void ST_Coordinate32_writer::write_target_to(xml_writer& w) {
			w.write_element_value(context()->serialize(*t()));
		}

		void ST_PositiveCoordinate32_writer::write_target_to(xml_writer& w) {
			ST_Coordinate32_writer::write_target_to(w);
		}

		void CT_RelativeRect_writer::write_target_to(xml_writer& w) {
			if (t()->l != 0)
				w.attribute(0, dml_baseTypes_l_literal, context()->serialize(t()->l));
			if (t()->t != 0)
				w.attribute(0, dml_baseTypes_t_literal, context()->serialize(t()->t));
			if (t()->r != 0)
				w.attribute(0, dml_baseTypes_r_literal, context()->serialize(t()->r));
			if (t()->b != 0)
				w.attribute(0, dml_baseTypes_b_literal, context()->serialize(t()->b));
		}

		void ST_FixedAngle_writer::write_target_to(xml_writer& w) {
			ST_Angle_writer::write_target_to(w);
		}

		void CT_EmbeddedWAVAudioFile_writer::write_target_to(xml_writer& w) {
			w.attribute(dml_baseTypes_r_literal, dml_baseTypes_embed_literal, context()->serialize(t()->embed));
			if (t()->name != "")
				w.attribute(0, dml_baseTypes_name_literal, context()->serialize(t()->name));
			if (t()->builtIn != false)
				w.attribute(0, dml_baseTypes_builtIn_literal, context()->serialize(t()->builtIn));
		}

		void CT_Hyperlink_writer::write_target_to(xml_writer& w) {
			if (t()->id.present())
				w.attribute(dml_baseTypes_r_literal, dml_baseTypes_id_literal, context()->serialize(t()->id.get()));
			if (t()->invalidUrl != "")
				w.attribute(0, dml_baseTypes_invalidUrl_literal, context()->serialize(t()->invalidUrl));
			if (t()->action != "")
				w.attribute(0, dml_baseTypes_action_literal, context()->serialize(t()->action));
			if (t()->tgtFrame != "")
				w.attribute(0, dml_baseTypes_tgtFrame_literal, context()->serialize(t()->tgtFrame));
			if (t()->tooltip != "")
				w.attribute(0, dml_baseTypes_tooltip_literal, context()->serialize(t()->tooltip));
			if (t()->history != true)
				w.attribute(0, dml_baseTypes_history_literal, context()->serialize(t()->history));
			if (t()->highlightClick != false)
				w.attribute(0, dml_baseTypes_highlightClick_literal, context()->serialize(t()->highlightClick));
			if (t()->endSnd != false)
				w.attribute(0, dml_baseTypes_endSnd_literal, context()->serialize(t()->endSnd));
			if (t()->snd.present()) {
				w.start_element(0, dml_baseTypes_snd_literal);
				_snd_writer.get_writer(context(), &t()->snd.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_snd_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, dml_baseTypes_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_extLst_literal);
			}
		}

		void ST_Guid_writer::write_target_to(xml_writer& w) {
			w.write_element_value(context()->serialize(*t()));
		}

		void CT_Point2D_writer::write_target_to(xml_writer& w) {
			w.attribute(0, dml_baseTypes_x_literal, context()->serialize(t()->x));
			w.attribute(0, dml_baseTypes_y_literal, context()->serialize(t()->y));
		}

		void CT_PositiveSize2D_writer::write_target_to(xml_writer& w) {
			w.attribute(0, dml_baseTypes_cx_literal, context()->serialize(t()->cx));
			w.attribute(0, dml_baseTypes_cy_literal, context()->serialize(t()->cy));
		}

		void CT_Transform2D_writer::write_target_to(xml_writer& w) {
			if (t()->rot != 0)
				w.attribute(0, dml_baseTypes_rot_literal, context()->serialize(t()->rot));
			if (t()->flipH != false)
				w.attribute(0, dml_baseTypes_flipH_literal, context()->serialize(t()->flipH));
			if (t()->flipV != false)
				w.attribute(0, dml_baseTypes_flipV_literal, context()->serialize(t()->flipV));
			if (t()->off.present()) {
                XMLCh ns[2]; ns[0] = 'a';ns[1] = 0;
				w.start_element(ns, dml_baseTypes_off_literal);
				_off_writer.get_writer(context(), &t()->off.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_off_literal);
			}
			if (t()->ext.present()) {
                XMLCh ns[2]; ns[0] = 'a';ns[1] = 0;
				w.start_element(ns, dml_baseTypes_ext_literal);
				_ext_writer.get_writer(context(), &t()->ext.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_ext_literal);
			}
		}

		void ST_DrawingElementId_writer::write_target_to(xml_writer& w) {
			w.write_element_value(context()->serialize(*t()));
		}

		void CT_GroupTransform2D_writer::write_target_to(xml_writer& w) {
			if (t()->rot != 0)
				w.attribute(0, dml_baseTypes_rot_literal, context()->serialize(t()->rot));
			if (t()->flipH != false)
				w.attribute(0, dml_baseTypes_flipH_literal, context()->serialize(t()->flipH));
			if (t()->flipV != false)
				w.attribute(0, dml_baseTypes_flipV_literal, context()->serialize(t()->flipV));
			if (t()->off.present()) {
				w.start_element(0, dml_baseTypes_off_literal);
				_off_writer.get_writer(context(), &t()->off.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_off_literal);
			}
			if (t()->ext.present()) {
				w.start_element(0, dml_baseTypes_ext_literal);
				_ext_writer.get_writer(context(), &t()->ext.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_ext_literal);
			}
			if (t()->chOff.present()) {
				w.start_element(0, dml_baseTypes_chOff_literal);
				_chOff_writer.get_writer(context(), &t()->chOff.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_chOff_literal);
			}
			if (t()->chExt.present()) {
				w.start_element(0, dml_baseTypes_chExt_literal);
				_chExt_writer.get_writer(context(), &t()->chExt.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_chExt_literal);
			}
		}

		void CT_ColorMRU_writer::write_target_to(xml_writer& w) {
			if (t()->scrgbClr.present()) {
				w.start_element(0, dml_baseTypes_scrgbClr_literal);
				_scrgbClr_writer.get_writer(context(), &t()->scrgbClr.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_scrgbClr_literal);
			}
			if (t()->srgbClr.present()) {
				w.start_element(0, dml_baseTypes_srgbClr_literal);
				_srgbClr_writer.get_writer(context(), &t()->srgbClr.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_srgbClr_literal);
			}
			if (t()->hslClr.present()) {
				w.start_element(0, dml_baseTypes_hslClr_literal);
				_hslClr_writer.get_writer(context(), &t()->hslClr.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_hslClr_literal);
			}
			if (t()->sysClr.present()) {
				w.start_element(0, dml_baseTypes_sysClr_literal);
				_sysClr_writer.get_writer(context(), &t()->sysClr.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_sysClr_literal);
			}
			if (t()->schemeClr.present()) {
				w.start_element(0, dml_baseTypes_schemeClr_literal);
				_schemeClr_writer.get_writer(context(), &t()->schemeClr.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_schemeClr_literal);
			}
			if (t()->prstClr.present()) {
				w.start_element(0, dml_baseTypes_prstClr_literal);
				_prstClr_writer.get_writer(context(), &t()->prstClr.get())->write_target_to(w);
				w.end_element(0, dml_baseTypes_prstClr_literal);
			}
		}

		void CT_Ratio_writer::write_target_to(xml_writer& w) {
			w.attribute(0, dml_baseTypes_n_literal, context()->serialize(t()->n));
			w.attribute(0, dml_baseTypes_d_literal, context()->serialize(t()->d));
		}

		void CT_Scale2D_writer::write_target_to(xml_writer& w) {
			w.start_element(0, dml_baseTypes_sx_literal);
			_sx_writer.get_writer(context(), &t()->sx)->write_target_to(w);
			w.end_element(0, dml_baseTypes_sx_literal);
			w.start_element(0, dml_baseTypes_sy_literal);
			_sy_writer.get_writer(context(), &t()->sy)->write_target_to(w);
			w.end_element(0, dml_baseTypes_sy_literal);
		}

	}
}
