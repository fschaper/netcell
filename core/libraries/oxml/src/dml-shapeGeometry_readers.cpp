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


#include "dml-shapeGeometry_readers.hpp"
#include "dml-shapeGeometry_literals.hpp"
#include <xio/xml/binding/driver.hpp>

namespace drawingml
{
	namespace xio
	{
		void ST_GeomGuideName_reader::read_value(const xstring& val) {{ driver()->context()->parse(val, *t()); }}
		void ST_GeomGuideFormula_reader::read_value(const xstring& val) {{ driver()->context()->parse(val, *t()); }}
		void CT_GeomGuide_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_name_literal))
			{
				driver()->context()->parse(value, t()->name);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_fmla_literal))
			{
				driver()->context()->parse(value, t()->fmla);
				return;
			}
		}
		void CT_GeomGuideList_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_gd_literal))
			{
				t()->gd.resize(t()->gd.size()+1);
				driver()->push(localname, _gd_reader.get_reader(&t()->gd.back()));
				return;
			}
		}
		void CT_PresetTextShape_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_avLst_literal))
			{
				driver()->push(localname, _avLst_reader.get_reader(&t()->avLst.getset()));
				return;
			}
		}
		void CT_PresetTextShape_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_prst_literal))
			{
				driver()->context()->parse(value, t()->prst);
				return;
			}
		}
		void ST_AdjCoordinate_reader::read_value(const xstring& val) {{ driver()->context()->parse(val, *t()); }}
		void CT_AdjPoint2D_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_x_literal))
			{
				driver()->context()->parse(value, t()->x);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_y_literal))
			{
				driver()->context()->parse(value, t()->y);
				return;
			}
		}
		void CT_XYAdjustHandle_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_pos_literal))
			{
				driver()->push(localname, _pos_reader.get_reader(&t()->pos));
				return;
			}
		}
		void CT_XYAdjustHandle_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_gdRefX_literal))
			{
				driver()->context()->parse(value, t()->gdRefX.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_minX_literal))
			{
				driver()->context()->parse(value, t()->minX.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_maxX_literal))
			{
				driver()->context()->parse(value, t()->maxX.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_gdRefY_literal))
			{
				driver()->context()->parse(value, t()->gdRefY.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_minY_literal))
			{
				driver()->context()->parse(value, t()->minY.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_maxY_literal))
			{
				driver()->context()->parse(value, t()->maxY.getset());
				return;
			}
		}
		void ST_AdjAngle_reader::read_value(const xstring& val) {{ driver()->context()->parse(val, *t()); }}
		void CT_PolarAdjustHandle_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_pos_literal))
			{
				driver()->push(localname, _pos_reader.get_reader(&t()->pos));
				return;
			}
		}
		void CT_PolarAdjustHandle_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_gdRefR_literal))
			{
				driver()->context()->parse(value, t()->gdRefR.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_minR_literal))
			{
				driver()->context()->parse(value, t()->minR.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_maxR_literal))
			{
				driver()->context()->parse(value, t()->maxR.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_gdRefAng_literal))
			{
				driver()->context()->parse(value, t()->gdRefAng.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_minAng_literal))
			{
				driver()->context()->parse(value, t()->minAng.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_maxAng_literal))
			{
				driver()->context()->parse(value, t()->maxAng.getset());
				return;
			}
		}
		void CT_AdjustHandleList_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_ahXY_literal))
			{
				driver()->push(localname, _ahXY_reader.get_reader(&t()->ahXY.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_ahPolar_literal))
			{
				driver()->push(localname, _ahPolar_reader.get_reader(&t()->ahPolar.getset()));
				return;
			}
		}
		void CT_ConnectionSite_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_pos_literal))
			{
				driver()->push(localname, _pos_reader.get_reader(&t()->pos));
				return;
			}
		}
		void CT_ConnectionSite_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_ang_literal))
			{
				driver()->context()->parse(value, t()->ang);
				return;
			}
		}
		void CT_ConnectionSiteList_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_cxn_literal))
			{
				t()->cxn.resize(t()->cxn.size()+1);
				driver()->push(localname, _cxn_reader.get_reader(&t()->cxn.back()));
				return;
			}
		}
		void CT_GeomRect_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_l_literal))
			{
				driver()->context()->parse(value, t()->l);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_t_literal))
			{
				driver()->context()->parse(value, t()->t);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_r_literal))
			{
				driver()->context()->parse(value, t()->r);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_b_literal))
			{
				driver()->context()->parse(value, t()->b);
				return;
			}
		}
		void CT_Path2DMoveTo_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_pt_literal))
			{
				driver()->push(localname, _pt_reader.get_reader(&t()->pt));
				return;
			}
		}
		void CT_Path2DLineTo_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_pt_literal))
			{
				driver()->push(localname, _pt_reader.get_reader(&t()->pt));
				return;
			}
		}
		void CT_Path2DArcTo_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_wR_literal))
			{
				driver()->context()->parse(value, t()->wR);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_hR_literal))
			{
				driver()->context()->parse(value, t()->hR);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_stAng_literal))
			{
				driver()->context()->parse(value, t()->stAng);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_swAng_literal))
			{
				driver()->context()->parse(value, t()->swAng);
				return;
			}
		}
		void CT_Path2DQuadBezierTo_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_pt_literal))
			{
				t()->pt.resize(t()->pt.size()+1);
				driver()->push(localname, _pt_reader.get_reader(&t()->pt.back()));
				return;
			}
		}
		void CT_Path2DCubicBezierTo_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_pt_literal))
			{
				t()->pt.resize(t()->pt.size()+1);
				driver()->push(localname, _pt_reader.get_reader(&t()->pt.back()));
				return;
			}
		}
		void CT_Path2D_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_close_literal))
			{
				driver()->push(localname, _close_reader.get_reader(&t()->close.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_moveTo_literal))
			{
				driver()->push(localname, _moveTo_reader.get_reader(&t()->moveTo.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_lnTo_literal))
			{
				driver()->push(localname, _lnTo_reader.get_reader(&t()->lnTo.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_arcTo_literal))
			{
				driver()->push(localname, _arcTo_reader.get_reader(&t()->arcTo.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_quadBezTo_literal))
			{
				driver()->push(localname, _quadBezTo_reader.get_reader(&t()->quadBezTo.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_cubicBezTo_literal))
			{
				driver()->push(localname, _cubicBezTo_reader.get_reader(&t()->cubicBezTo.getset()));
				return;
			}
		}
		void CT_Path2D_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_w_literal))
			{
				driver()->context()->parse(value, t()->w);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_h_literal))
			{
				driver()->context()->parse(value, t()->h);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_fill_literal))
			{
				driver()->context()->parse(value, t()->fill);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_stroke_literal))
			{
				driver()->context()->parse(value, t()->stroke);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_extrusionOk_literal))
			{
				driver()->context()->parse(value, t()->extrusionOk);
				return;
			}
		}
		void CT_Path2DList_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_path_literal))
			{
				t()->path.resize(t()->path.size()+1);
				driver()->push(localname, _path_reader.get_reader(&t()->path.back()));
				return;
			}
		}
		void CT_CustomGeometry2D_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_avLst_literal))
			{
				driver()->push(localname, _avLst_reader.get_reader(&t()->avLst.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_gdLst_literal))
			{
				driver()->push(localname, _gdLst_reader.get_reader(&t()->gdLst.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_ahLst_literal))
			{
				driver()->push(localname, _ahLst_reader.get_reader(&t()->ahLst.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_cxnLst_literal))
			{
				driver()->push(localname, _cxnLst_reader.get_reader(&t()->cxnLst.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_rect_literal))
			{
				driver()->push(localname, _rect_reader.get_reader(&t()->rect.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_pathLst_literal))
			{
				driver()->push(localname, _pathLst_reader.get_reader(&t()->pathLst));
				return;
			}
		}
		void CT_PresetGeometry2D_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_avLst_literal))
			{
				driver()->push(localname, _avLst_reader.get_reader(&t()->avLst.getset()));
				return;
			}
		}
		void CT_PresetGeometry2D_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_prst_literal))
			{
				driver()->context()->parse(value, t()->prst);
				return;
			}
		}
		void CT_Connection_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_id_literal))
			{
				driver()->context()->parse(value, t()->id);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeGeometry_idx_literal))
			{
				driver()->context()->parse(value, t()->idx);
				return;
			}
		}
	}
}
