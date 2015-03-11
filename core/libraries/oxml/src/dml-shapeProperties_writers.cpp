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


#include "dml-shapeProperties_writers.hpp"
#include "dml-shapeProperties_literals.hpp"

namespace drawingml
{
	namespace xio
	{
		void CT_ShapeProperties_writer::write_target_to(xml_writer& w) {
			if (t()->bwMode.present())
				w.attribute(0, dml_shapeProperties_bwMode_literal, context()->serialize(t()->bwMode.get()));
			if (t()->xfrm.present()) {
                XMLCh ns[2]; ns[0] = 'a';ns[1] = 0;
				w.start_element(ns, dml_shapeProperties_xfrm_literal);
				_xfrm_writer.get_writer(context(), &t()->xfrm.get())->write_target_to(w);
				w.end_element(ns, dml_shapeProperties_xfrm_literal);
			}
			if (t()->custGeom.present()) {
				w.start_element(0, dml_shapeProperties_custGeom_literal);
				_custGeom_writer.get_writer(context(), &t()->custGeom.get())->write_target_to(w);
				w.end_element(0, dml_shapeProperties_custGeom_literal);
			}
			if (t()->prstGeom.present()) {
                XMLCh ns[2]; ns[0] = 'a';ns[1] = 0;
				w.start_element(ns, dml_shapeProperties_prstGeom_literal);
				_prstGeom_writer.get_writer(context(), &t()->prstGeom.get())->write_target_to(w);
				w.end_element(ns, dml_shapeProperties_prstGeom_literal);
			}
			if (t()->noFill.present()) {
				w.start_element(0, dml_shapeProperties_noFill_literal);
				_noFill_writer.get_writer(context(), &t()->noFill.get())->write_target_to(w);
				w.end_element(0, dml_shapeProperties_noFill_literal);
			}
			if (t()->solidFill.present()) {
				w.start_element(0, dml_shapeProperties_solidFill_literal);
				_solidFill_writer.get_writer(context(), &t()->solidFill.get())->write_target_to(w);
				w.end_element(0, dml_shapeProperties_solidFill_literal);
			}
			if (t()->gradFill.present()) {
				w.start_element(0, dml_shapeProperties_gradFill_literal);
				_gradFill_writer.get_writer(context(), &t()->gradFill.get())->write_target_to(w);
				w.end_element(0, dml_shapeProperties_gradFill_literal);
			}
			if (t()->blipFill.present()) {
				w.start_element(0, dml_shapeProperties_blipFill_literal);
				_blipFill_writer.get_writer(context(), &t()->blipFill.get())->write_target_to(w);
				w.end_element(0, dml_shapeProperties_blipFill_literal);
			}
			if (t()->pattFill.present()) {
				w.start_element(0, dml_shapeProperties_pattFill_literal);
				_pattFill_writer.get_writer(context(), &t()->pattFill.get())->write_target_to(w);
				w.end_element(0, dml_shapeProperties_pattFill_literal);
			}
			if (t()->grpFill.present()) {
				w.start_element(0, dml_shapeProperties_grpFill_literal);
				_grpFill_writer.get_writer(context(), &t()->grpFill.get())->write_target_to(w);
				w.end_element(0, dml_shapeProperties_grpFill_literal);
			}
			if (t()->ln.present()) {
				w.start_element(0, dml_shapeProperties_ln_literal);
				_ln_writer.get_writer(context(), &t()->ln.get())->write_target_to(w);
				w.end_element(0, dml_shapeProperties_ln_literal);
			}
			if (t()->effectLst.present()) {
				w.start_element(0, dml_shapeProperties_effectLst_literal);
				_effectLst_writer.get_writer(context(), &t()->effectLst.get())->write_target_to(w);
				w.end_element(0, dml_shapeProperties_effectLst_literal);
			}
			if (t()->effectDag.present()) {
				w.start_element(0, dml_shapeProperties_effectDag_literal);
				_effectDag_writer.get_writer(context(), &t()->effectDag.get())->write_target_to(w);
				w.end_element(0, dml_shapeProperties_effectDag_literal);
			}
			if (t()->scene3d.present()) {
				w.start_element(0, dml_shapeProperties_scene3d_literal);
				_scene3d_writer.get_writer(context(), &t()->scene3d.get())->write_target_to(w);
				w.end_element(0, dml_shapeProperties_scene3d_literal);
			}
			if (t()->sp3d.present()) {
				w.start_element(0, dml_shapeProperties_sp3d_literal);
				_sp3d_writer.get_writer(context(), &t()->sp3d.get())->write_target_to(w);
				w.end_element(0, dml_shapeProperties_sp3d_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, dml_shapeProperties_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, dml_shapeProperties_extLst_literal);
			}
		}

		void CT_GroupShapeProperties_writer::write_target_to(xml_writer& w) {
			if (t()->bwMode.present())
				w.attribute(0, dml_shapeProperties_bwMode_literal, context()->serialize(t()->bwMode.get()));
			if (t()->xfrm.present()) {
				w.start_element(0, dml_shapeProperties_xfrm_literal);
				_xfrm_writer.get_writer(context(), &t()->xfrm.get())->write_target_to(w);
				w.end_element(0, dml_shapeProperties_xfrm_literal);
			}
			if (t()->noFill.present()) {
				w.start_element(0, dml_shapeProperties_noFill_literal);
				_noFill_writer.get_writer(context(), &t()->noFill.get())->write_target_to(w);
				w.end_element(0, dml_shapeProperties_noFill_literal);
			}
			if (t()->solidFill.present()) {
				w.start_element(0, dml_shapeProperties_solidFill_literal);
				_solidFill_writer.get_writer(context(), &t()->solidFill.get())->write_target_to(w);
				w.end_element(0, dml_shapeProperties_solidFill_literal);
			}
			if (t()->gradFill.present()) {
				w.start_element(0, dml_shapeProperties_gradFill_literal);
				_gradFill_writer.get_writer(context(), &t()->gradFill.get())->write_target_to(w);
				w.end_element(0, dml_shapeProperties_gradFill_literal);
			}
			if (t()->blipFill.present()) {
				w.start_element(0, dml_shapeProperties_blipFill_literal);
				_blipFill_writer.get_writer(context(), &t()->blipFill.get())->write_target_to(w);
				w.end_element(0, dml_shapeProperties_blipFill_literal);
			}
			if (t()->pattFill.present()) {
				w.start_element(0, dml_shapeProperties_pattFill_literal);
				_pattFill_writer.get_writer(context(), &t()->pattFill.get())->write_target_to(w);
				w.end_element(0, dml_shapeProperties_pattFill_literal);
			}
			if (t()->grpFill.present()) {
				w.start_element(0, dml_shapeProperties_grpFill_literal);
				_grpFill_writer.get_writer(context(), &t()->grpFill.get())->write_target_to(w);
				w.end_element(0, dml_shapeProperties_grpFill_literal);
			}
			if (t()->effectLst.present()) {
				w.start_element(0, dml_shapeProperties_effectLst_literal);
				_effectLst_writer.get_writer(context(), &t()->effectLst.get())->write_target_to(w);
				w.end_element(0, dml_shapeProperties_effectLst_literal);
			}
			if (t()->effectDag.present()) {
				w.start_element(0, dml_shapeProperties_effectDag_literal);
				_effectDag_writer.get_writer(context(), &t()->effectDag.get())->write_target_to(w);
				w.end_element(0, dml_shapeProperties_effectDag_literal);
			}
			if (t()->scene3d.present()) {
				w.start_element(0, dml_shapeProperties_scene3d_literal);
				_scene3d_writer.get_writer(context(), &t()->scene3d.get())->write_target_to(w);
				w.end_element(0, dml_shapeProperties_scene3d_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, dml_shapeProperties_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, dml_shapeProperties_extLst_literal);
			}
		}

	}
}
