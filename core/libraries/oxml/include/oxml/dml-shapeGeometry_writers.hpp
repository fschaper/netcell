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

#ifndef DML_SHAPEGEOMETRY_WRITERS_HPP
#define DML_SHAPEGEOMETRY_WRITERS_HPP

#include "dml-shapeGeometry.hpp"
#include "dml-shapeGeometry_literals.hpp"
#include "dml-baseTypes_writers.hpp"

namespace drawingml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class ST_GeomGuideName_writer;
		class ST_GeomGuideFormula_writer;
		class CT_GeomGuide_writer;
		class CT_GeomGuideList_writer;
		class CT_PresetTextShape_writer;
		class ST_AdjCoordinate_writer;
		class CT_AdjPoint2D_writer;
		class CT_XYAdjustHandle_writer;
		class ST_AdjAngle_writer;
		class CT_PolarAdjustHandle_writer;
		class CT_AdjustHandleList_writer;
		class CT_ConnectionSite_writer;
		class CT_ConnectionSiteList_writer;
		class CT_GeomRect_writer;
		class CT_Path2DClose_writer;
		class CT_Path2DMoveTo_writer;
		class CT_Path2DLineTo_writer;
		class CT_Path2DArcTo_writer;
		class CT_Path2DQuadBezierTo_writer;
		class CT_Path2DCubicBezierTo_writer;
		class CT_Path2D_writer;
		class CT_Path2DList_writer;
		class CT_CustomGeometry2D_writer;
		class CT_PresetGeometry2D_writer;
		class CT_Connection_writer;

		class ST_GeomGuideName_writer : public type_writer
		{
			ST_GeomGuideName* t() { return static_cast<ST_GeomGuideName*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class ST_GeomGuideFormula_writer : public type_writer
		{
			ST_GeomGuideFormula* t() { return static_cast<ST_GeomGuideFormula*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_GeomGuide_writer : public type_writer
		{
			CT_GeomGuide* t() { return static_cast<CT_GeomGuide*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_GeomGuideList_writer : public type_writer
		{
			auto_type_writer< CT_GeomGuide_writer > _gd_writer;
			CT_GeomGuideList* t() { return static_cast<CT_GeomGuideList*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_PresetTextShape_writer : public type_writer
		{
			auto_type_writer< CT_GeomGuideList_writer > _avLst_writer;
			CT_PresetTextShape* t() { return static_cast<CT_PresetTextShape*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class ST_AdjCoordinate_writer : public type_writer
		{
			ST_AdjCoordinate* t() { return static_cast<ST_AdjCoordinate*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_AdjPoint2D_writer : public type_writer
		{
			CT_AdjPoint2D* t() { return static_cast<CT_AdjPoint2D*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_XYAdjustHandle_writer : public type_writer
		{
			auto_type_writer< CT_AdjPoint2D_writer > _pos_writer;
			CT_XYAdjustHandle* t() { return static_cast<CT_XYAdjustHandle*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class ST_AdjAngle_writer : public type_writer
		{
			ST_AdjAngle* t() { return static_cast<ST_AdjAngle*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_PolarAdjustHandle_writer : public type_writer
		{
			auto_type_writer< CT_AdjPoint2D_writer > _pos_writer;
			CT_PolarAdjustHandle* t() { return static_cast<CT_PolarAdjustHandle*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_AdjustHandleList_writer : public type_writer
		{
			auto_type_writer< CT_XYAdjustHandle_writer > _ahXY_writer;
			auto_type_writer< CT_PolarAdjustHandle_writer > _ahPolar_writer;
			CT_AdjustHandleList* t() { return static_cast<CT_AdjustHandleList*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_ConnectionSite_writer : public type_writer
		{
			auto_type_writer< CT_AdjPoint2D_writer > _pos_writer;
			CT_ConnectionSite* t() { return static_cast<CT_ConnectionSite*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_ConnectionSiteList_writer : public type_writer
		{
			auto_type_writer< CT_ConnectionSite_writer > _cxn_writer;
			CT_ConnectionSiteList* t() { return static_cast<CT_ConnectionSiteList*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_GeomRect_writer : public type_writer
		{
			CT_GeomRect* t() { return static_cast<CT_GeomRect*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Path2DClose_writer : public type_writer
		{
			CT_Path2DClose* t() { return static_cast<CT_Path2DClose*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Path2DMoveTo_writer : public type_writer
		{
			auto_type_writer< CT_AdjPoint2D_writer > _pt_writer;
			CT_Path2DMoveTo* t() { return static_cast<CT_Path2DMoveTo*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Path2DLineTo_writer : public type_writer
		{
			auto_type_writer< CT_AdjPoint2D_writer > _pt_writer;
			CT_Path2DLineTo* t() { return static_cast<CT_Path2DLineTo*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Path2DArcTo_writer : public type_writer
		{
			CT_Path2DArcTo* t() { return static_cast<CT_Path2DArcTo*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Path2DQuadBezierTo_writer : public type_writer
		{
			auto_type_writer< CT_AdjPoint2D_writer > _pt_writer;
			CT_Path2DQuadBezierTo* t() { return static_cast<CT_Path2DQuadBezierTo*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Path2DCubicBezierTo_writer : public type_writer
		{
			auto_type_writer< CT_AdjPoint2D_writer > _pt_writer;
			CT_Path2DCubicBezierTo* t() { return static_cast<CT_Path2DCubicBezierTo*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Path2D_writer : public type_writer
		{
			auto_type_writer< CT_Path2DClose_writer > _close_writer;
			auto_type_writer< CT_Path2DMoveTo_writer > _moveTo_writer;
			auto_type_writer< CT_Path2DLineTo_writer > _lnTo_writer;
			auto_type_writer< CT_Path2DArcTo_writer > _arcTo_writer;
			auto_type_writer< CT_Path2DQuadBezierTo_writer > _quadBezTo_writer;
			auto_type_writer< CT_Path2DCubicBezierTo_writer > _cubicBezTo_writer;
			CT_Path2D* t() { return static_cast<CT_Path2D*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Path2DList_writer : public type_writer
		{
			auto_type_writer< CT_Path2D_writer > _path_writer;
			CT_Path2DList* t() { return static_cast<CT_Path2DList*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_CustomGeometry2D_writer : public type_writer
		{
			auto_type_writer< CT_GeomGuideList_writer > _avLst_writer;
			auto_type_writer< CT_GeomGuideList_writer > _gdLst_writer;
			auto_type_writer< CT_AdjustHandleList_writer > _ahLst_writer;
			auto_type_writer< CT_ConnectionSiteList_writer > _cxnLst_writer;
			auto_type_writer< CT_GeomRect_writer > _rect_writer;
			auto_type_writer< CT_Path2DList_writer > _pathLst_writer;
			CT_CustomGeometry2D* t() { return static_cast<CT_CustomGeometry2D*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_PresetGeometry2D_writer : public type_writer
		{
			auto_type_writer< CT_GeomGuideList_writer > _avLst_writer;
			CT_PresetGeometry2D* t() { return static_cast<CT_PresetGeometry2D*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Connection_writer : public type_writer
		{
			CT_Connection* t() { return static_cast<CT_Connection*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

	}
}
#endif

