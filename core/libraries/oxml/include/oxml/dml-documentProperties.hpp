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

#ifndef DML_DOCUMENTPROPERTIES_HPP
#define DML_DOCUMENTPROPERTIES_HPP


#include "dml-baseTypes.hpp"
#include "dml-shapeGeometry.hpp"

namespace drawingml
{
	using namespace ::xio;
	using namespace ::xio::xml::schema;

	class CT_NonVisualDrawingProps;
	class CT_ShapeLocking;
	class CT_NonVisualDrawingShapeProps;
	class CT_GroupLocking;
	class CT_NonVisualGroupDrawingShapeProps;
	class CT_GraphicalObjectFrameLocking;
	class CT_NonVisualGraphicFrameProperties;
	class CT_ConnectorLocking;
	class CT_NonVisualConnectorProperties;
	class CT_PictureLocking;
	class CT_NonVisualPictureProperties;

	class CT_NonVisualDrawingProps
	{
	public:
		CT_NonVisualDrawingProps() : descr(""), hidden(false) {}
		poptional< CT_Hyperlink > hlinkClick;
		poptional< CT_Hyperlink > hlinkHover;
		poptional< CT_OfficeArtExtensionList > extLst;
		ST_DrawingElementId id;
		String name;
		String descr;
		Boolean hidden;
	};

	class CT_ShapeLocking
	{
	public:
		CT_ShapeLocking() : noGrp(false), noSelect(false), noRot(false), noChangeAspect(false), noMove(false), noResize(false), noEditPoints(false), noAdjustHandles(false), noChangeArrowheads(false), noChangeShapeType(false), noTextEdit(false) {}
		poptional< CT_OfficeArtExtensionList > extLst;
		Boolean noGrp;
		Boolean noSelect;
		Boolean noRot;
		Boolean noChangeAspect;
		Boolean noMove;
		Boolean noResize;
		Boolean noEditPoints;
		Boolean noAdjustHandles;
		Boolean noChangeArrowheads;
		Boolean noChangeShapeType;
		Boolean noTextEdit;
	};

	class CT_NonVisualDrawingShapeProps
	{
	public:
		CT_NonVisualDrawingShapeProps() : txBox(false) {}
		poptional< CT_ShapeLocking > spLocks;
		poptional< CT_OfficeArtExtensionList > extLst;
		Boolean txBox;
	};

	class CT_GroupLocking
	{
	public:
		CT_GroupLocking() : noGrp(false), noUngrp(false), noSelect(false), noRot(false), noChangeAspect(false), noMove(false), noResize(false) {}
		poptional< CT_OfficeArtExtensionList > extLst;
		Boolean noGrp;
		Boolean noUngrp;
		Boolean noSelect;
		Boolean noRot;
		Boolean noChangeAspect;
		Boolean noMove;
		Boolean noResize;
	};

	class CT_NonVisualGroupDrawingShapeProps
	{
	public:
		poptional< CT_GroupLocking > grpSpLocks;
		poptional< CT_OfficeArtExtensionList > extLst;
	};

	class CT_GraphicalObjectFrameLocking
	{
	public:
		CT_GraphicalObjectFrameLocking() : noGrp(false), noDrilldown(false), noSelect(false), noChangeAspect(false), noMove(false), noResize(false) {}
		poptional< CT_OfficeArtExtensionList > extLst;
		Boolean noGrp;
		Boolean noDrilldown;
		Boolean noSelect;
		Boolean noChangeAspect;
		Boolean noMove;
		Boolean noResize;
	};

	class CT_NonVisualGraphicFrameProperties
	{
	public:
		poptional< CT_GraphicalObjectFrameLocking > graphicFrameLocks;
		poptional< CT_OfficeArtExtensionList > extLst;
	};

	class CT_ConnectorLocking
	{
	public:
		CT_ConnectorLocking() : noGrp(false), noSelect(false), noRot(false), noChangeAspect(false), noMove(false), noResize(false), noEditPoints(false), noAdjustHandles(false), noChangeArrowheads(false), noChangeShapeType(false) {}
		poptional< CT_OfficeArtExtensionList > extLst;
		Boolean noGrp;
		Boolean noSelect;
		Boolean noRot;
		Boolean noChangeAspect;
		Boolean noMove;
		Boolean noResize;
		Boolean noEditPoints;
		Boolean noAdjustHandles;
		Boolean noChangeArrowheads;
		Boolean noChangeShapeType;
	};

	class CT_NonVisualConnectorProperties
	{
	public:
		poptional< CT_ConnectorLocking > cxnSpLocks;
		poptional< CT_Connection > stCxn;
		poptional< CT_Connection > endCxn;
		poptional< CT_OfficeArtExtensionList > extLst;
	};

	class CT_PictureLocking
	{
	public:
		CT_PictureLocking() : noGrp(false), noSelect(false), noRot(false), noChangeAspect(false), noMove(false), noResize(false), noEditPoints(false), noAdjustHandles(false), noChangeArrowheads(false), noChangeShapeType(false), noCrop(false) {}
		poptional< CT_OfficeArtExtensionList > extLst;
		Boolean noGrp;
		Boolean noSelect;
		Boolean noRot;
		Boolean noChangeAspect;
		Boolean noMove;
		Boolean noResize;
		Boolean noEditPoints;
		Boolean noAdjustHandles;
		Boolean noChangeArrowheads;
		Boolean noChangeShapeType;
		Boolean noCrop;
	};

	class CT_NonVisualPictureProperties
	{
	public:
		CT_NonVisualPictureProperties() : preferRelativeResize(true) {}
		poptional< CT_PictureLocking > picLocks;
		poptional< CT_OfficeArtExtensionList > extLst;
		Boolean preferRelativeResize;
	};

}
#endif

