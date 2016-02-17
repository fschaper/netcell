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

#ifndef DML_SPREADSHEETDRAWING_WRITERS_HPP
#define DML_SPREADSHEETDRAWING_WRITERS_HPP

#include "dml-spreadsheetDrawing.hpp"
#include "dml-spreadsheetDrawing_literals.hpp"
#include "dml-baseTypes_writers.hpp"
#include "dml-documentProperties_writers.hpp"
#include "dml-shapeProperties_writers.hpp"
#include "dml-shapeStyle_writers.hpp"
#include "dml-text_writers.hpp"
#include "dml-graphicalObject_writers.hpp"
#include "dml-shapeEffects_writers.hpp"

namespace drawingml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class ST_ColID_writer;
		class ST_RowID_writer;
		class CT_Marker_writer;
		class CT_ShapeNonVisual_writer;
		class CT_Shape_writer;
		class CT_GroupShapeNonVisual_writer;
		class CT_GraphicalObjectFrameNonVisual_writer;
		class CT_GraphicalObjectFrame_writer;
		class CT_ConnectorNonVisual_writer;
		class CT_Connector_writer;
		class CT_PictureNonVisual_writer;
		class CT_Picture_writer;
		class CT_GroupShape_writer;
		class CT_AnchorClientData_writer;
		class CT_TwoCellAnchor_writer;
		class CT_Drawings_writer;
		class dml_spreadsheetDrawing_writer;

		class ST_ColID_writer : public type_writer
		{
			ST_ColID* t() { return static_cast<ST_ColID*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class ST_RowID_writer : public type_writer
		{
			ST_RowID* t() { return static_cast<ST_RowID*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Marker_writer : public type_writer
		{
			auto_type_writer< ST_ColID_writer > _col_writer;
			auto_type_writer< ST_Coordinate_writer > _colOff_writer;
			auto_type_writer< ST_RowID_writer > _row_writer;
			auto_type_writer< ST_Coordinate_writer > _rowOff_writer;
			CT_Marker* t() { return static_cast<CT_Marker*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_ShapeNonVisual_writer : public type_writer
		{
			auto_type_writer< CT_NonVisualDrawingProps_writer > _cNvPr_writer;
			auto_type_writer< CT_NonVisualDrawingShapeProps_writer > _cNvSpPr_writer;
			CT_ShapeNonVisual* t() { return static_cast<CT_ShapeNonVisual*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Shape_writer : public type_writer
		{
			auto_type_writer< CT_ShapeNonVisual_writer > _nvSpPr_writer;
			auto_type_writer< CT_ShapeProperties_writer > _spPr_writer;
			auto_type_writer< CT_ShapeStyle_writer > _style_writer;
			auto_type_writer< CT_TextBody_writer > _txBody_writer;
			CT_Shape* t() { return static_cast<CT_Shape*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_GroupShapeNonVisual_writer : public type_writer
		{
			auto_type_writer< CT_NonVisualDrawingProps_writer > _cNvPr_writer;
			auto_type_writer< CT_NonVisualGroupDrawingShapeProps_writer > _cNvGrpSpPr_writer;
			CT_GroupShapeNonVisual* t() { return static_cast<CT_GroupShapeNonVisual*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_GraphicalObjectFrameNonVisual_writer : public type_writer
		{
			auto_type_writer< CT_NonVisualDrawingProps_writer > _cNvPr_writer;
			auto_type_writer< CT_NonVisualGraphicFrameProperties_writer > _cNvGraphicFramePr_writer;
			CT_GraphicalObjectFrameNonVisual* t() { return static_cast<CT_GraphicalObjectFrameNonVisual*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_GraphicalObjectFrame_writer : public type_writer
		{
			auto_type_writer< CT_GraphicalObjectFrameNonVisual_writer > _nvGraphicFramePr_writer;
			auto_type_writer< CT_Transform2D_writer > _xfrm_writer;
			auto_type_writer< CT_GraphicalObject_writer > _graphic_writer;
			CT_GraphicalObjectFrame* t() { return static_cast<CT_GraphicalObjectFrame*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_ConnectorNonVisual_writer : public type_writer
		{
			auto_type_writer< CT_NonVisualDrawingProps_writer > _cNvPr_writer;
			auto_type_writer< CT_NonVisualConnectorProperties_writer > _cNvCxnSpPr_writer;
			CT_ConnectorNonVisual* t() { return static_cast<CT_ConnectorNonVisual*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Connector_writer : public type_writer
		{
			auto_type_writer< CT_ConnectorNonVisual_writer > _nvCxnSpPr_writer;
			auto_type_writer< CT_ShapeProperties_writer > _spPr_writer;
			auto_type_writer< CT_ShapeStyle_writer > _style_writer;
			CT_Connector* t() { return static_cast<CT_Connector*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_PictureNonVisual_writer : public type_writer
		{
			auto_type_writer< CT_NonVisualDrawingProps_writer > _cNvPr_writer;
			auto_type_writer< CT_NonVisualPictureProperties_writer > _cNvPicPr_writer;
			CT_PictureNonVisual* t() { return static_cast<CT_PictureNonVisual*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Picture_writer : public type_writer
		{
			auto_type_writer< CT_PictureNonVisual_writer > _nvPicPr_writer;
			auto_type_writer< CT_BlipFillProperties_writer > _blipFill_writer;
			auto_type_writer< CT_ShapeProperties_writer > _spPr_writer;
			auto_type_writer< CT_ShapeStyle_writer > _style_writer;
			CT_Picture* t() { return static_cast<CT_Picture*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_GroupShape_writer : public type_writer
		{
			auto_type_writer< CT_GroupShapeNonVisual_writer > _nvGrpSpPr_writer;
			auto_type_writer< CT_GroupShapeProperties_writer > _grpSpPr_writer;
			auto_type_writer< CT_Shape_writer > _sp_writer;
			auto_type_writer< CT_GroupShape_writer > _grpSp_writer;
			auto_type_writer< CT_GraphicalObjectFrame_writer > _graphicFrame_writer;
			auto_type_writer< CT_Connector_writer > _cxnSp_writer;
			auto_type_writer< CT_Picture_writer > _pic_writer;
			CT_GroupShape* t() { return static_cast<CT_GroupShape*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_AnchorClientData_writer : public type_writer
		{
			CT_AnchorClientData* t() { return static_cast<CT_AnchorClientData*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_TwoCellAnchor_writer : public type_writer
		{
			auto_type_writer< CT_Marker_writer > _from_writer;
			auto_type_writer< CT_Marker_writer > _to_writer;
			auto_type_writer< CT_Shape_writer > _sp_writer;
			auto_type_writer< CT_GroupShape_writer > _grpSp_writer;
			auto_type_writer< CT_GraphicalObjectFrame_writer > _graphicFrame_writer;
			auto_type_writer< CT_Connector_writer > _cxnSp_writer;
			auto_type_writer< CT_Picture_writer > _pic_writer;
			auto_type_writer< CT_AnchorClientData_writer > _clientData_writer;
			CT_TwoCellAnchor* t() { return static_cast<CT_TwoCellAnchor*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Drawings_writer : public type_writer
		{
			auto_type_writer< CT_TwoCellAnchor_writer > _twoCellAnchor_writer;
			CT_Drawings* t() { return static_cast<CT_Drawings*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class dml_spreadsheetDrawing_writer : public type_writer
		{
			auto_type_writer< CT_Drawings_writer > _wsDr_writer;
			dml_spreadsheetDrawing* t() { return static_cast<dml_spreadsheetDrawing*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

	}
}
#endif

