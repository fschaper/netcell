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

#ifndef DML_SPREADSHEETDRAWING_READERS_HPP
#define DML_SPREADSHEETDRAWING_READERS_HPP

#include "dml-spreadsheetDrawing.hpp"
#include "dml-baseTypes_readers.hpp"
#include "dml-documentProperties_readers.hpp"
#include "dml-shapeProperties_readers.hpp"
#include "dml-shapeStyle_readers.hpp"
#include "dml-text_readers.hpp"
#include "dml-graphicalObject_readers.hpp"
#include "dml-shapeEffects_readers.hpp"

namespace drawingml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class ST_ColID_reader;
		class ST_RowID_reader;
		class CT_Marker_reader;
		class CT_ShapeNonVisual_reader;
		class CT_Shape_reader;
		class CT_GroupShapeNonVisual_reader;
		class CT_GraphicalObjectFrameNonVisual_reader;
		class CT_GraphicalObjectFrame_reader;
		class CT_ConnectorNonVisual_reader;
		class CT_Connector_reader;
		class CT_PictureNonVisual_reader;
		class CT_Picture_reader;
		class CT_GroupShape_reader;
		class CT_AnchorClientData_reader;
		class CT_TwoCellAnchor_reader;
		class CT_Drawings_reader;
		class dml_spreadsheetDrawing_reader;

		class ST_ColID_reader : public type_reader
		{
		protected:
			ST_ColID* t() { return static_cast<ST_ColID*>(target()); }
			void read_value(const xstring& val);
		};

		class ST_RowID_reader : public type_reader
		{
		protected:
			ST_RowID* t() { return static_cast<ST_RowID*>(target()); }
			void read_value(const xstring& val);
		};

		class CT_Marker_reader : public type_reader
		{
			auto_type_reader< ST_ColID_reader > _col_reader;
			auto_type_reader< ST_Coordinate_reader > _colOff_reader;
			auto_type_reader< ST_RowID_reader > _row_reader;
			auto_type_reader< ST_Coordinate_reader > _rowOff_reader;
		protected:
			CT_Marker* t() { return static_cast<CT_Marker*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_ShapeNonVisual_reader : public type_reader
		{
			auto_type_reader< CT_NonVisualDrawingProps_reader > _cNvPr_reader;
			auto_type_reader< CT_NonVisualDrawingShapeProps_reader > _cNvSpPr_reader;
		protected:
			CT_ShapeNonVisual* t() { return static_cast<CT_ShapeNonVisual*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_Shape_reader : public type_reader
		{
			auto_type_reader< CT_ShapeNonVisual_reader > _nvSpPr_reader;
			auto_type_reader< CT_ShapeProperties_reader > _spPr_reader;
			auto_type_reader< CT_ShapeStyle_reader > _style_reader;
			auto_type_reader< CT_TextBody_reader > _txBody_reader;
		protected:
			CT_Shape* t() { return static_cast<CT_Shape*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_GroupShapeNonVisual_reader : public type_reader
		{
			auto_type_reader< CT_NonVisualDrawingProps_reader > _cNvPr_reader;
			auto_type_reader< CT_NonVisualGroupDrawingShapeProps_reader > _cNvGrpSpPr_reader;
		protected:
			CT_GroupShapeNonVisual* t() { return static_cast<CT_GroupShapeNonVisual*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_GraphicalObjectFrameNonVisual_reader : public type_reader
		{
			auto_type_reader< CT_NonVisualDrawingProps_reader > _cNvPr_reader;
			auto_type_reader< CT_NonVisualGraphicFrameProperties_reader > _cNvGraphicFramePr_reader;
		protected:
			CT_GraphicalObjectFrameNonVisual* t() { return static_cast<CT_GraphicalObjectFrameNonVisual*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_GraphicalObjectFrame_reader : public type_reader
		{
			auto_type_reader< CT_GraphicalObjectFrameNonVisual_reader > _nvGraphicFramePr_reader;
			auto_type_reader< CT_Transform2D_reader > _xfrm_reader;
			auto_type_reader< CT_GraphicalObject_reader > _graphic_reader;
		protected:
			CT_GraphicalObjectFrame* t() { return static_cast<CT_GraphicalObjectFrame*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_ConnectorNonVisual_reader : public type_reader
		{
			auto_type_reader< CT_NonVisualDrawingProps_reader > _cNvPr_reader;
			auto_type_reader< CT_NonVisualConnectorProperties_reader > _cNvCxnSpPr_reader;
		protected:
			CT_ConnectorNonVisual* t() { return static_cast<CT_ConnectorNonVisual*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_Connector_reader : public type_reader
		{
			auto_type_reader< CT_ConnectorNonVisual_reader > _nvCxnSpPr_reader;
			auto_type_reader< CT_ShapeProperties_reader > _spPr_reader;
			auto_type_reader< CT_ShapeStyle_reader > _style_reader;
		protected:
			CT_Connector* t() { return static_cast<CT_Connector*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_PictureNonVisual_reader : public type_reader
		{
			auto_type_reader< CT_NonVisualDrawingProps_reader > _cNvPr_reader;
			auto_type_reader< CT_NonVisualPictureProperties_reader > _cNvPicPr_reader;
		protected:
			CT_PictureNonVisual* t() { return static_cast<CT_PictureNonVisual*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_Picture_reader : public type_reader
		{
			auto_type_reader< CT_PictureNonVisual_reader > _nvPicPr_reader;
			auto_type_reader< CT_BlipFillProperties_reader > _blipFill_reader;
			auto_type_reader< CT_ShapeProperties_reader > _spPr_reader;
			auto_type_reader< CT_ShapeStyle_reader > _style_reader;
		protected:
			CT_Picture* t() { return static_cast<CT_Picture*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_GroupShape_reader : public type_reader
		{
			auto_type_reader< CT_GroupShapeNonVisual_reader > _nvGrpSpPr_reader;
			auto_type_reader< CT_GroupShapeProperties_reader > _grpSpPr_reader;
			auto_type_reader< CT_Shape_reader > _sp_reader;
			auto_type_reader< CT_GroupShape_reader > _grpSp_reader;
			auto_type_reader< CT_GraphicalObjectFrame_reader > _graphicFrame_reader;
			auto_type_reader< CT_Connector_reader > _cxnSp_reader;
			auto_type_reader< CT_Picture_reader > _pic_reader;
		protected:
			CT_GroupShape* t() { return static_cast<CT_GroupShape*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_AnchorClientData_reader : public type_reader
		{
		protected:
			CT_AnchorClientData* t() { return static_cast<CT_AnchorClientData*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_TwoCellAnchor_reader : public type_reader
		{
			auto_type_reader< CT_Marker_reader > _from_reader;
			auto_type_reader< CT_Marker_reader > _to_reader;
			auto_type_reader< CT_Shape_reader > _sp_reader;
			auto_type_reader< CT_GroupShape_reader > _grpSp_reader;
			auto_type_reader< CT_GraphicalObjectFrame_reader > _graphicFrame_reader;
			auto_type_reader< CT_Connector_reader > _cxnSp_reader;
			auto_type_reader< CT_Picture_reader > _pic_reader;
			auto_type_reader< CT_AnchorClientData_reader > _clientData_reader;
		protected:
			CT_TwoCellAnchor* t() { return static_cast<CT_TwoCellAnchor*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Drawings_reader : public type_reader
		{
			auto_type_reader< CT_TwoCellAnchor_reader > _twoCellAnchor_reader;
		protected:
			CT_Drawings* t() { return static_cast<CT_Drawings*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class dml_spreadsheetDrawing_reader : public type_reader
		{
			auto_type_reader< CT_Drawings_reader > _wsDr_reader;
		protected:
			dml_spreadsheetDrawing* t() { return static_cast<dml_spreadsheetDrawing*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

	}
}
#endif

