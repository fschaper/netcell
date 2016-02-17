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


#include "dml-shape3DStyles_writers.hpp"
#include "dml-shape3DStyles_literals.hpp"

namespace drawingml
{
	namespace xio
	{
		void CT_Bevel_writer::write_target_to(xml_writer& w) {
			if (t()->w != 76200L)
				w.attribute(0, dml_shape3DStyles_w_literal, context()->serialize(t()->w));
			if (t()->h != 76200L)
				w.attribute(0, dml_shape3DStyles_h_literal, context()->serialize(t()->h));
			if (t()->prst != ST_BevelPresetType::circle_literal)
				w.attribute(0, dml_shape3DStyles_prst_literal, context()->serialize(t()->prst));
		}

		void CT_Shape3D_writer::write_target_to(xml_writer& w) {
			if (t()->z != 0L)
				w.attribute(0, dml_shape3DStyles_z_literal, context()->serialize(t()->z));
			if (t()->extrusionH != 0L)
				w.attribute(0, dml_shape3DStyles_extrusionH_literal, context()->serialize(t()->extrusionH));
			if (t()->contourW != 0L)
				w.attribute(0, dml_shape3DStyles_contourW_literal, context()->serialize(t()->contourW));
			if (t()->prstMaterial != ST_PresetMaterialType::warmMatte_literal)
				w.attribute(0, dml_shape3DStyles_prstMaterial_literal, context()->serialize(t()->prstMaterial));
			if (t()->bevelT.present()) {
				w.start_element(0, dml_shape3DStyles_bevelT_literal);
				_bevelT_writer.get_writer(context(), &t()->bevelT.get())->write_target_to(w);
				w.end_element(0, dml_shape3DStyles_bevelT_literal);
			}
			if (t()->bevelB.present()) {
				w.start_element(0, dml_shape3DStyles_bevelB_literal);
				_bevelB_writer.get_writer(context(), &t()->bevelB.get())->write_target_to(w);
				w.end_element(0, dml_shape3DStyles_bevelB_literal);
			}
			if (t()->extrusionClr.present()) {
				w.start_element(0, dml_shape3DStyles_extrusionClr_literal);
				_extrusionClr_writer.get_writer(context(), &t()->extrusionClr.get())->write_target_to(w);
				w.end_element(0, dml_shape3DStyles_extrusionClr_literal);
			}
			if (t()->contourClr.present()) {
				w.start_element(0, dml_shape3DStyles_contourClr_literal);
				_contourClr_writer.get_writer(context(), &t()->contourClr.get())->write_target_to(w);
				w.end_element(0, dml_shape3DStyles_contourClr_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, dml_shape3DStyles_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, dml_shape3DStyles_extLst_literal);
			}
		}

		void CT_FlatText_writer::write_target_to(xml_writer& w) {
			if (t()->z != 0L)
				w.attribute(0, dml_shape3DStyles_z_literal, context()->serialize(t()->z));
		}

	}
}
