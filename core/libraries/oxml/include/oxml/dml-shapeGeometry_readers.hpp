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

#ifndef DML_SHAPEGEOMETRY_READERS_HPP
#define DML_SHAPEGEOMETRY_READERS_HPP

#include "dml-shapeGeometry.hpp"
#include "dml-baseTypes_readers.hpp"

namespace drawingml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class ST_GeomGuideName_reader;
		class ST_GeomGuideFormula_reader;
		class CT_GeomGuide_reader;
		class CT_GeomGuideList_reader;
		class CT_PresetTextShape_reader;
		class ST_AdjCoordinate_reader;
		class CT_AdjPoint2D_reader;
		class CT_XYAdjustHandle_reader;
		class ST_AdjAngle_reader;
		class CT_PolarAdjustHandle_reader;
		class CT_AdjustHandleList_reader;
		class CT_ConnectionSite_reader;
		class CT_ConnectionSiteList_reader;
		class CT_GeomRect_reader;
		class CT_Path2DClose_reader;
		class CT_Path2DMoveTo_reader;
		class CT_Path2DLineTo_reader;
		class CT_Path2DArcTo_reader;
		class CT_Path2DQuadBezierTo_reader;
		class CT_Path2DCubicBezierTo_reader;
		class CT_Path2D_reader;
		class CT_Path2DList_reader;
		class CT_CustomGeometry2D_reader;
		class CT_PresetGeometry2D_reader;
		class CT_Connection_reader;

		class ST_GeomGuideName_reader : public type_reader
		{
		protected:
			ST_GeomGuideName* t() { return static_cast<ST_GeomGuideName*>(target()); }
			void read_value(const xstring& val);
		};

		class ST_GeomGuideFormula_reader : public type_reader
		{
		protected:
			ST_GeomGuideFormula* t() { return static_cast<ST_GeomGuideFormula*>(target()); }
			void read_value(const xstring& val);
		};

		class CT_GeomGuide_reader : public type_reader
		{
		protected:
			CT_GeomGuide* t() { return static_cast<CT_GeomGuide*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_GeomGuideList_reader : public type_reader
		{
			auto_type_reader< CT_GeomGuide_reader > _gd_reader;
		protected:
			CT_GeomGuideList* t() { return static_cast<CT_GeomGuideList*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_PresetTextShape_reader : public type_reader
		{
			auto_type_reader< CT_GeomGuideList_reader > _avLst_reader;
		protected:
			CT_PresetTextShape* t() { return static_cast<CT_PresetTextShape*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class ST_AdjCoordinate_reader : public type_reader
		{
		protected:
			ST_AdjCoordinate* t() { return static_cast<ST_AdjCoordinate*>(target()); }
			void read_value(const xstring& val);
		};

		class CT_AdjPoint2D_reader : public type_reader
		{
		protected:
			CT_AdjPoint2D* t() { return static_cast<CT_AdjPoint2D*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_XYAdjustHandle_reader : public type_reader
		{
			auto_type_reader< CT_AdjPoint2D_reader > _pos_reader;
		protected:
			CT_XYAdjustHandle* t() { return static_cast<CT_XYAdjustHandle*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class ST_AdjAngle_reader : public type_reader
		{
		protected:
			ST_AdjAngle* t() { return static_cast<ST_AdjAngle*>(target()); }
			void read_value(const xstring& val);
		};

		class CT_PolarAdjustHandle_reader : public type_reader
		{
			auto_type_reader< CT_AdjPoint2D_reader > _pos_reader;
		protected:
			CT_PolarAdjustHandle* t() { return static_cast<CT_PolarAdjustHandle*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_AdjustHandleList_reader : public type_reader
		{
			auto_type_reader< CT_XYAdjustHandle_reader > _ahXY_reader;
			auto_type_reader< CT_PolarAdjustHandle_reader > _ahPolar_reader;
		protected:
			CT_AdjustHandleList* t() { return static_cast<CT_AdjustHandleList*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_ConnectionSite_reader : public type_reader
		{
			auto_type_reader< CT_AdjPoint2D_reader > _pos_reader;
		protected:
			CT_ConnectionSite* t() { return static_cast<CT_ConnectionSite*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_ConnectionSiteList_reader : public type_reader
		{
			auto_type_reader< CT_ConnectionSite_reader > _cxn_reader;
		protected:
			CT_ConnectionSiteList* t() { return static_cast<CT_ConnectionSiteList*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_GeomRect_reader : public type_reader
		{
		protected:
			CT_GeomRect* t() { return static_cast<CT_GeomRect*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Path2DClose_reader : public type_reader
		{
		protected:
			CT_Path2DClose* t() { return static_cast<CT_Path2DClose*>(target()); }
		};

		class CT_Path2DMoveTo_reader : public type_reader
		{
			auto_type_reader< CT_AdjPoint2D_reader > _pt_reader;
		protected:
			CT_Path2DMoveTo* t() { return static_cast<CT_Path2DMoveTo*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_Path2DLineTo_reader : public type_reader
		{
			auto_type_reader< CT_AdjPoint2D_reader > _pt_reader;
		protected:
			CT_Path2DLineTo* t() { return static_cast<CT_Path2DLineTo*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_Path2DArcTo_reader : public type_reader
		{
		protected:
			CT_Path2DArcTo* t() { return static_cast<CT_Path2DArcTo*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Path2DQuadBezierTo_reader : public type_reader
		{
			auto_type_reader< CT_AdjPoint2D_reader > _pt_reader;
		protected:
			CT_Path2DQuadBezierTo* t() { return static_cast<CT_Path2DQuadBezierTo*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_Path2DCubicBezierTo_reader : public type_reader
		{
			auto_type_reader< CT_AdjPoint2D_reader > _pt_reader;
		protected:
			CT_Path2DCubicBezierTo* t() { return static_cast<CT_Path2DCubicBezierTo*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_Path2D_reader : public type_reader
		{
			auto_type_reader< CT_Path2DClose_reader > _close_reader;
			auto_type_reader< CT_Path2DMoveTo_reader > _moveTo_reader;
			auto_type_reader< CT_Path2DLineTo_reader > _lnTo_reader;
			auto_type_reader< CT_Path2DArcTo_reader > _arcTo_reader;
			auto_type_reader< CT_Path2DQuadBezierTo_reader > _quadBezTo_reader;
			auto_type_reader< CT_Path2DCubicBezierTo_reader > _cubicBezTo_reader;
		protected:
			CT_Path2D* t() { return static_cast<CT_Path2D*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Path2DList_reader : public type_reader
		{
			auto_type_reader< CT_Path2D_reader > _path_reader;
		protected:
			CT_Path2DList* t() { return static_cast<CT_Path2DList*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_CustomGeometry2D_reader : public type_reader
		{
			auto_type_reader< CT_GeomGuideList_reader > _avLst_reader;
			auto_type_reader< CT_GeomGuideList_reader > _gdLst_reader;
			auto_type_reader< CT_AdjustHandleList_reader > _ahLst_reader;
			auto_type_reader< CT_ConnectionSiteList_reader > _cxnLst_reader;
			auto_type_reader< CT_GeomRect_reader > _rect_reader;
			auto_type_reader< CT_Path2DList_reader > _pathLst_reader;
		protected:
			CT_CustomGeometry2D* t() { return static_cast<CT_CustomGeometry2D*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_PresetGeometry2D_reader : public type_reader
		{
			auto_type_reader< CT_GeomGuideList_reader > _avLst_reader;
		protected:
			CT_PresetGeometry2D* t() { return static_cast<CT_PresetGeometry2D*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Connection_reader : public type_reader
		{
		protected:
			CT_Connection* t() { return static_cast<CT_Connection*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

	}
}
#endif

