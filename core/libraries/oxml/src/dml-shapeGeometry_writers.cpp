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


#include "dml-shapeGeometry_writers.hpp"
#include "dml-shapeGeometry_literals.hpp"

namespace drawingml
{
	namespace xio
	{
		void ST_GeomGuideName_writer::write_target_to(xml_writer& w) {
			w.write_element_value(context()->serialize(*t()));
		}

		void ST_GeomGuideFormula_writer::write_target_to(xml_writer& w) {
			w.write_element_value(context()->serialize(*t()));
		}

		void CT_GeomGuide_writer::write_target_to(xml_writer& w) {
			w.attribute(0, dml_shapeGeometry_name_literal, context()->serialize(t()->name));
			w.attribute(0, dml_shapeGeometry_fmla_literal, context()->serialize(t()->fmla));
		}

		void CT_GeomGuideList_writer::write_target_to(xml_writer& w) {
			for (size_t sqi = 0; sqi<t()->gd.size(); ++sqi) {
				w.start_element(0, dml_shapeGeometry_gd_literal);
				_gd_writer.get_writer(context(), &t()->gd[sqi])->write_target_to(w);
				w.end_element(0, dml_shapeGeometry_gd_literal);
			}
		}

		void CT_PresetTextShape_writer::write_target_to(xml_writer& w) {
			w.attribute(0, dml_shapeGeometry_prst_literal, context()->serialize(t()->prst));
			if (t()->avLst.present()) {
				w.start_element(0, dml_shapeGeometry_avLst_literal);
				_avLst_writer.get_writer(context(), &t()->avLst.get())->write_target_to(w);
				w.end_element(0, dml_shapeGeometry_avLst_literal);
			}
		}

		void ST_AdjCoordinate_writer::write_target_to(xml_writer& w) {
			w.write_element_value(context()->serialize(*t()));
		}

		void CT_AdjPoint2D_writer::write_target_to(xml_writer& w) {
			w.attribute(0, dml_shapeGeometry_x_literal, context()->serialize(t()->x));
			w.attribute(0, dml_shapeGeometry_y_literal, context()->serialize(t()->y));
		}

		void CT_XYAdjustHandle_writer::write_target_to(xml_writer& w) {
			if (t()->gdRefX.present())
				w.attribute(0, dml_shapeGeometry_gdRefX_literal, context()->serialize(t()->gdRefX.get()));
			if (t()->minX.present())
				w.attribute(0, dml_shapeGeometry_minX_literal, context()->serialize(t()->minX.get()));
			if (t()->maxX.present())
				w.attribute(0, dml_shapeGeometry_maxX_literal, context()->serialize(t()->maxX.get()));
			if (t()->gdRefY.present())
				w.attribute(0, dml_shapeGeometry_gdRefY_literal, context()->serialize(t()->gdRefY.get()));
			if (t()->minY.present())
				w.attribute(0, dml_shapeGeometry_minY_literal, context()->serialize(t()->minY.get()));
			if (t()->maxY.present())
				w.attribute(0, dml_shapeGeometry_maxY_literal, context()->serialize(t()->maxY.get()));
			w.start_element(0, dml_shapeGeometry_pos_literal);
			_pos_writer.get_writer(context(), &t()->pos)->write_target_to(w);
			w.end_element(0, dml_shapeGeometry_pos_literal);
		}

		void ST_AdjAngle_writer::write_target_to(xml_writer& w) {
			w.write_element_value(context()->serialize(*t()));
		}

		void CT_PolarAdjustHandle_writer::write_target_to(xml_writer& w) {
			if (t()->gdRefR.present())
				w.attribute(0, dml_shapeGeometry_gdRefR_literal, context()->serialize(t()->gdRefR.get()));
			if (t()->minR.present())
				w.attribute(0, dml_shapeGeometry_minR_literal, context()->serialize(t()->minR.get()));
			if (t()->maxR.present())
				w.attribute(0, dml_shapeGeometry_maxR_literal, context()->serialize(t()->maxR.get()));
			if (t()->gdRefAng.present())
				w.attribute(0, dml_shapeGeometry_gdRefAng_literal, context()->serialize(t()->gdRefAng.get()));
			if (t()->minAng.present())
				w.attribute(0, dml_shapeGeometry_minAng_literal, context()->serialize(t()->minAng.get()));
			if (t()->maxAng.present())
				w.attribute(0, dml_shapeGeometry_maxAng_literal, context()->serialize(t()->maxAng.get()));
			w.start_element(0, dml_shapeGeometry_pos_literal);
			_pos_writer.get_writer(context(), &t()->pos)->write_target_to(w);
			w.end_element(0, dml_shapeGeometry_pos_literal);
		}

		void CT_AdjustHandleList_writer::write_target_to(xml_writer& w) {
			if (t()->ahXY.present()) {
				w.start_element(0, dml_shapeGeometry_ahXY_literal);
				_ahXY_writer.get_writer(context(), &t()->ahXY.get())->write_target_to(w);
				w.end_element(0, dml_shapeGeometry_ahXY_literal);
			}
			if (t()->ahPolar.present()) {
				w.start_element(0, dml_shapeGeometry_ahPolar_literal);
				_ahPolar_writer.get_writer(context(), &t()->ahPolar.get())->write_target_to(w);
				w.end_element(0, dml_shapeGeometry_ahPolar_literal);
			}
		}

		void CT_ConnectionSite_writer::write_target_to(xml_writer& w) {
			w.attribute(0, dml_shapeGeometry_ang_literal, context()->serialize(t()->ang));
			w.start_element(0, dml_shapeGeometry_pos_literal);
			_pos_writer.get_writer(context(), &t()->pos)->write_target_to(w);
			w.end_element(0, dml_shapeGeometry_pos_literal);
		}

		void CT_ConnectionSiteList_writer::write_target_to(xml_writer& w) {
			for (size_t sqi = 0; sqi<t()->cxn.size(); ++sqi) {
				w.start_element(0, dml_shapeGeometry_cxn_literal);
				_cxn_writer.get_writer(context(), &t()->cxn[sqi])->write_target_to(w);
				w.end_element(0, dml_shapeGeometry_cxn_literal);
			}
		}

		void CT_GeomRect_writer::write_target_to(xml_writer& w) {
			w.attribute(0, dml_shapeGeometry_l_literal, context()->serialize(t()->l));
			w.attribute(0, dml_shapeGeometry_t_literal, context()->serialize(t()->t));
			w.attribute(0, dml_shapeGeometry_r_literal, context()->serialize(t()->r));
			w.attribute(0, dml_shapeGeometry_b_literal, context()->serialize(t()->b));
		}

		void CT_Path2DClose_writer::write_target_to(xml_writer& w) {
		}

		void CT_Path2DMoveTo_writer::write_target_to(xml_writer& w) {
			w.start_element(0, dml_shapeGeometry_pt_literal);
			_pt_writer.get_writer(context(), &t()->pt)->write_target_to(w);
			w.end_element(0, dml_shapeGeometry_pt_literal);
		}

		void CT_Path2DLineTo_writer::write_target_to(xml_writer& w) {
			w.start_element(0, dml_shapeGeometry_pt_literal);
			_pt_writer.get_writer(context(), &t()->pt)->write_target_to(w);
			w.end_element(0, dml_shapeGeometry_pt_literal);
		}

		void CT_Path2DArcTo_writer::write_target_to(xml_writer& w) {
			w.attribute(0, dml_shapeGeometry_wR_literal, context()->serialize(t()->wR));
			w.attribute(0, dml_shapeGeometry_hR_literal, context()->serialize(t()->hR));
			w.attribute(0, dml_shapeGeometry_stAng_literal, context()->serialize(t()->stAng));
			w.attribute(0, dml_shapeGeometry_swAng_literal, context()->serialize(t()->swAng));
		}

		void CT_Path2DQuadBezierTo_writer::write_target_to(xml_writer& w) {
			for (size_t sqi = 0; sqi<t()->pt.size(); ++sqi) {
				w.start_element(0, dml_shapeGeometry_pt_literal);
				_pt_writer.get_writer(context(), &t()->pt[sqi])->write_target_to(w);
				w.end_element(0, dml_shapeGeometry_pt_literal);
			}
		}

		void CT_Path2DCubicBezierTo_writer::write_target_to(xml_writer& w) {
			for (size_t sqi = 0; sqi<t()->pt.size(); ++sqi) {
				w.start_element(0, dml_shapeGeometry_pt_literal);
				_pt_writer.get_writer(context(), &t()->pt[sqi])->write_target_to(w);
				w.end_element(0, dml_shapeGeometry_pt_literal);
			}
		}

		void CT_Path2D_writer::write_target_to(xml_writer& w) {
			if (t()->w != 0L)
				w.attribute(0, dml_shapeGeometry_w_literal, context()->serialize(t()->w));
			if (t()->h != 0L)
				w.attribute(0, dml_shapeGeometry_h_literal, context()->serialize(t()->h));
			if (t()->fill != ST_PathFillMode::norm_literal)
				w.attribute(0, dml_shapeGeometry_fill_literal, context()->serialize(t()->fill));
			if (t()->stroke != true)
				w.attribute(0, dml_shapeGeometry_stroke_literal, context()->serialize(t()->stroke));
			if (t()->extrusionOk != true)
				w.attribute(0, dml_shapeGeometry_extrusionOk_literal, context()->serialize(t()->extrusionOk));
			if (t()->close.present()) {
				w.start_element(0, dml_shapeGeometry_close_literal);
				_close_writer.get_writer(context(), &t()->close.get())->write_target_to(w);
				w.end_element(0, dml_shapeGeometry_close_literal);
			}
			if (t()->moveTo.present()) {
				w.start_element(0, dml_shapeGeometry_moveTo_literal);
				_moveTo_writer.get_writer(context(), &t()->moveTo.get())->write_target_to(w);
				w.end_element(0, dml_shapeGeometry_moveTo_literal);
			}
			if (t()->lnTo.present()) {
				w.start_element(0, dml_shapeGeometry_lnTo_literal);
				_lnTo_writer.get_writer(context(), &t()->lnTo.get())->write_target_to(w);
				w.end_element(0, dml_shapeGeometry_lnTo_literal);
			}
			if (t()->arcTo.present()) {
				w.start_element(0, dml_shapeGeometry_arcTo_literal);
				_arcTo_writer.get_writer(context(), &t()->arcTo.get())->write_target_to(w);
				w.end_element(0, dml_shapeGeometry_arcTo_literal);
			}
			if (t()->quadBezTo.present()) {
				w.start_element(0, dml_shapeGeometry_quadBezTo_literal);
				_quadBezTo_writer.get_writer(context(), &t()->quadBezTo.get())->write_target_to(w);
				w.end_element(0, dml_shapeGeometry_quadBezTo_literal);
			}
			if (t()->cubicBezTo.present()) {
				w.start_element(0, dml_shapeGeometry_cubicBezTo_literal);
				_cubicBezTo_writer.get_writer(context(), &t()->cubicBezTo.get())->write_target_to(w);
				w.end_element(0, dml_shapeGeometry_cubicBezTo_literal);
			}
		}

		void CT_Path2DList_writer::write_target_to(xml_writer& w) {
			for (size_t sqi = 0; sqi<t()->path.size(); ++sqi) {
				w.start_element(0, dml_shapeGeometry_path_literal);
				_path_writer.get_writer(context(), &t()->path[sqi])->write_target_to(w);
				w.end_element(0, dml_shapeGeometry_path_literal);
			}
		}

		void CT_CustomGeometry2D_writer::write_target_to(xml_writer& w) {
			if (t()->avLst.present()) {
				w.start_element(0, dml_shapeGeometry_avLst_literal);
				_avLst_writer.get_writer(context(), &t()->avLst.get())->write_target_to(w);
				w.end_element(0, dml_shapeGeometry_avLst_literal);
			}
			if (t()->gdLst.present()) {
				w.start_element(0, dml_shapeGeometry_gdLst_literal);
				_gdLst_writer.get_writer(context(), &t()->gdLst.get())->write_target_to(w);
				w.end_element(0, dml_shapeGeometry_gdLst_literal);
			}
			if (t()->ahLst.present()) {
				w.start_element(0, dml_shapeGeometry_ahLst_literal);
				_ahLst_writer.get_writer(context(), &t()->ahLst.get())->write_target_to(w);
				w.end_element(0, dml_shapeGeometry_ahLst_literal);
			}
			if (t()->cxnLst.present()) {
				w.start_element(0, dml_shapeGeometry_cxnLst_literal);
				_cxnLst_writer.get_writer(context(), &t()->cxnLst.get())->write_target_to(w);
				w.end_element(0, dml_shapeGeometry_cxnLst_literal);
			}
			if (t()->rect.present()) {
				w.start_element(0, dml_shapeGeometry_rect_literal);
				_rect_writer.get_writer(context(), &t()->rect.get())->write_target_to(w);
				w.end_element(0, dml_shapeGeometry_rect_literal);
			}
			w.start_element(0, dml_shapeGeometry_pathLst_literal);
			_pathLst_writer.get_writer(context(), &t()->pathLst)->write_target_to(w);
			w.end_element(0, dml_shapeGeometry_pathLst_literal);
		}

		void CT_PresetGeometry2D_writer::write_target_to(xml_writer& w) {
			w.attribute(0, dml_shapeGeometry_prst_literal, context()->serialize(t()->prst));
			if (t()->avLst.present()) {
                XMLCh ns[2]; ns[0] = 'a';ns[1] = 0;
				w.start_element(ns, dml_shapeGeometry_avLst_literal);
				_avLst_writer.get_writer(context(), &t()->avLst.get())->write_target_to(w);
				w.end_element(ns, dml_shapeGeometry_avLst_literal);
			}
		}

		void CT_Connection_writer::write_target_to(xml_writer& w) {
			w.attribute(0, dml_shapeGeometry_id_literal, context()->serialize(t()->id));
			w.attribute(0, dml_shapeGeometry_idx_literal, context()->serialize(t()->idx));
		}

	}
}
