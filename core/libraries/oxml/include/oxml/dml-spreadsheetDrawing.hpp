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

#ifndef DML_SPREADSHEETDRAWING_HPP
#define DML_SPREADSHEETDRAWING_HPP


#include "dml-baseTypes.hpp"
#include "dml-documentProperties.hpp"
#include "dml-shapeProperties.hpp"
#include "dml-shapeStyle.hpp"
#include "dml-text.hpp"
#include "dml-graphicalObject.hpp"
#include "dml-shapeEffects.hpp"

namespace drawingml
{
	using namespace ::xio;
	using namespace ::xio::xml::schema;

	class ST_ColID;
	class ST_RowID;
	class CT_Marker;
	class CT_ShapeNonVisual;
	class CT_Shape;
	class CT_GroupShapeNonVisual;
	class CT_GraphicalObjectFrameNonVisual;
	class CT_GraphicalObjectFrame;
	class CT_ConnectorNonVisual;
	class CT_Connector;
	class CT_PictureNonVisual;
	class CT_Picture;
	class CT_GroupShape;
	class CT_AnchorClientData;
	class CT_TwoCellAnchor;
	class CT_Drawings;
	class dml_spreadsheetDrawing;

	class ST_ColID : public simple_type<Int>
	{
	public:
		ST_ColID() {}
		ST_ColID(const Int& v) : simple_type<Int>(v) {}
		ST_ColID(const String& v) { read(v); }
	};

	class ST_RowID : public simple_type<Int>
	{
	public:
		ST_RowID() {}
		ST_RowID(const Int& v) : simple_type<Int>(v) {}
		ST_RowID(const String& v) { read(v); }
	};

	class CT_Marker
	{
	public:
		ST_ColID col;
		ST_Coordinate colOff;
		ST_RowID row;
		ST_Coordinate rowOff;
	};

	class CT_ShapeNonVisual
	{
	public:
		CT_NonVisualDrawingProps cNvPr;
		CT_NonVisualDrawingShapeProps cNvSpPr;
	};

	class CT_Shape
	{
	public:
		CT_Shape() : fLocksText(true), fPublished(false) {}
		CT_ShapeNonVisual nvSpPr;
		CT_ShapeProperties spPr;
		poptional< CT_ShapeStyle > style;
		poptional< CT_TextBody > txBody;
		optional< String > macro;
		optional< String > textlink;
		Boolean fLocksText;
		Boolean fPublished;
	};

	class CT_GroupShapeNonVisual
	{
	public:
		CT_NonVisualDrawingProps cNvPr;
		CT_NonVisualGroupDrawingShapeProps cNvGrpSpPr;
	};

	class CT_GraphicalObjectFrameNonVisual
	{
	public:
		CT_NonVisualDrawingProps cNvPr;
		CT_NonVisualGraphicFrameProperties cNvGraphicFramePr;
	};

	class CT_GraphicalObjectFrame
	{
	public:
		CT_GraphicalObjectFrame() : fPublished(false) {}
		CT_GraphicalObjectFrameNonVisual nvGraphicFramePr;
		CT_Transform2D xfrm;
		CT_GraphicalObject graphic;
		optional< String > macro;
		Boolean fPublished;
	};

	class CT_ConnectorNonVisual
	{
	public:
		CT_NonVisualDrawingProps cNvPr;
		CT_NonVisualConnectorProperties cNvCxnSpPr;
	};

	class CT_Connector
	{
	public:
		CT_Connector() : fPublished(false) {}
		CT_ConnectorNonVisual nvCxnSpPr;
		CT_ShapeProperties spPr;
		poptional< CT_ShapeStyle > style;
		optional< String > macro;
		Boolean fPublished;
	};

	class CT_PictureNonVisual
	{
	public:
		CT_NonVisualDrawingProps cNvPr;
		CT_NonVisualPictureProperties cNvPicPr;
	};

	class CT_Picture
	{
	public:
		CT_Picture() : macro(""), fPublished(false) {}
		CT_PictureNonVisual nvPicPr;
		CT_BlipFillProperties blipFill;
		CT_ShapeProperties spPr;
		poptional< CT_ShapeStyle > style;
		String macro;
		Boolean fPublished;
	};

	class CT_GroupShape
	{
	public:
		CT_GroupShapeNonVisual nvGrpSpPr;
		CT_GroupShapeProperties grpSpPr;
		poptional< CT_Shape > sp;
		poptional< CT_GroupShape > grpSp;
		poptional< CT_GraphicalObjectFrame > graphicFrame;
		poptional< CT_Connector > cxnSp;
		poptional< CT_Picture > pic;
	};

	class CT_AnchorClientData
	{
	public:
		CT_AnchorClientData() : fLocksWithSheet(true), fPrintsWithSheet(true) {}
		Boolean fLocksWithSheet;
		Boolean fPrintsWithSheet;
	};

	class ST_EditAs
	{
		static String _literals[];
		String _value;
	public:
		enum value { absolute, oneCell, twoCell };

		static const String absolute_literal;
		static const String oneCell_literal;
		static const String twoCell_literal;

		ST_EditAs() : _value(twoCell_literal) {}
		ST_EditAs(value val) : _value(convert(val)) {}
		ST_EditAs(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 3, 0); }
		static String convert(value v) { return _literals[(int)v]; }

		bool operator == (const String& str) const { return str == _value; }
		bool operator == (value val) const {return convert(val) == _value; }
		bool operator != (const String& str) const { return str != _value; }
		bool operator != (value val) const {return convert(val) != _value; }

		const String& operator = (const String& str) { _value = str; return str; }
		const value& operator = (const value& val) { _value = convert(val); return val; }

		operator const String& () const { return _value; }
		operator String& () { return _value; }
		operator value () const { return convert(_value); }
		String serialize() const { return _value; }
	};

	class CT_TwoCellAnchor
	{
	public:
		CT_TwoCellAnchor() : editAs(ST_EditAs::twoCell_literal) {}
		CT_Marker from;
		CT_Marker to;
		poptional< CT_Shape > sp;
		poptional< CT_GroupShape > grpSp;
		poptional< CT_GraphicalObjectFrame > graphicFrame;
		poptional< CT_Connector > cxnSp;
		poptional< CT_Picture > pic;
		CT_AnchorClientData clientData;
		ST_EditAs editAs;
	};

	class CT_Drawings
	{
	public:
		std::vector< CT_TwoCellAnchor > twoCellAnchor;
	};

	class dml_spreadsheetDrawing
	{
	public:
		poptional< CT_Drawings > wsDr;
	};

}
#endif

