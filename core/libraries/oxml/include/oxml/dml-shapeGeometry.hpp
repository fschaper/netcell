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

#ifndef DML_SHAPEGEOMETRY_HPP
#define DML_SHAPEGEOMETRY_HPP


#include "dml-baseTypes.hpp"

namespace drawingml
{
	using namespace ::xio;
	using namespace ::xio::xml::schema;

	class ST_GeomGuideName;
	class ST_GeomGuideFormula;
	class CT_GeomGuide;
	class CT_GeomGuideList;
	class CT_PresetTextShape;
	class ST_AdjCoordinate;
	class CT_AdjPoint2D;
	class CT_XYAdjustHandle;
	class ST_AdjAngle;
	class CT_PolarAdjustHandle;
	class CT_AdjustHandleList;
	class CT_ConnectionSite;
	class CT_ConnectionSiteList;
	class CT_GeomRect;
	class CT_Path2DClose;
	class CT_Path2DMoveTo;
	class CT_Path2DLineTo;
	class CT_Path2DArcTo;
	class CT_Path2DQuadBezierTo;
	class CT_Path2DCubicBezierTo;
	class CT_Path2D;
	class CT_Path2DList;
	class CT_CustomGeometry2D;
	class CT_PresetGeometry2D;
	class CT_Connection;

	class ST_GeomGuideName : public simple_type<Token>
	{
	public:
		ST_GeomGuideName() {}
		ST_GeomGuideName(const Token& v) : simple_type<Token>(v) {}
	};

	class ST_GeomGuideFormula : public simple_type<String>
	{
	public:
		ST_GeomGuideFormula() {}
		ST_GeomGuideFormula(const String& v) : simple_type<String>(v) {}
	};

	class CT_GeomGuide
	{
	public:
		ST_GeomGuideName name;
		ST_GeomGuideFormula fmla;
	};

	class CT_GeomGuideList
	{
	public:
		std::vector< CT_GeomGuide > gd;
	};

	class ST_TextShapeType
	{
		static String _literals[];
		String _value;
	public:
		enum value { textArchDown, textArchDownPour, textArchUp, textArchUpPour, textButton, textButtonPour, textCanDown, textCanUp, textCascadeDown, textCascadeUp, textChevron, textChevronInverted, textCircle, textCirclePour, textCurveDown, textCurveUp, textDeflate, textDeflateBottom, textDeflateInflate, textDeflateInflateDeflate, textDeflateTop, textDoubleWave1, textFadeDown, textFadeLeft, textFadeRight, textFadeUp, textInflate, textInflateBottom, textInflateTop, textNoShape, textPlain, textRingInside, textRingOutside, textSlantDown, textSlantUp, textStop, textTriangle, textTriangleInverted, textWave1, textWave2, textWave4 };

		static const String textArchDown_literal;
		static const String textArchDownPour_literal;
		static const String textArchUp_literal;
		static const String textArchUpPour_literal;
		static const String textButton_literal;
		static const String textButtonPour_literal;
		static const String textCanDown_literal;
		static const String textCanUp_literal;
		static const String textCascadeDown_literal;
		static const String textCascadeUp_literal;
		static const String textChevron_literal;
		static const String textChevronInverted_literal;
		static const String textCircle_literal;
		static const String textCirclePour_literal;
		static const String textCurveDown_literal;
		static const String textCurveUp_literal;
		static const String textDeflate_literal;
		static const String textDeflateBottom_literal;
		static const String textDeflateInflate_literal;
		static const String textDeflateInflateDeflate_literal;
		static const String textDeflateTop_literal;
		static const String textDoubleWave1_literal;
		static const String textFadeDown_literal;
		static const String textFadeLeft_literal;
		static const String textFadeRight_literal;
		static const String textFadeUp_literal;
		static const String textInflate_literal;
		static const String textInflateBottom_literal;
		static const String textInflateTop_literal;
		static const String textNoShape_literal;
		static const String textPlain_literal;
		static const String textRingInside_literal;
		static const String textRingOutside_literal;
		static const String textSlantDown_literal;
		static const String textSlantUp_literal;
		static const String textStop_literal;
		static const String textTriangle_literal;
		static const String textTriangleInverted_literal;
		static const String textWave1_literal;
		static const String textWave2_literal;
		static const String textWave4_literal;

		ST_TextShapeType() : _value(textNoShape_literal) {}
		ST_TextShapeType(value val) : _value(convert(val)) {}
		ST_TextShapeType(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 41, 0); }
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

	class CT_PresetTextShape
	{
	public:
		poptional< CT_GeomGuideList > avLst;
		ST_TextShapeType prst;
	};

	class ST_AdjCoordinate : public simple_type<String>
	{
	public:
		ST_AdjCoordinate() {}
		ST_AdjCoordinate(const String& v) : simple_type<String>(v) {}
	};

	class CT_AdjPoint2D
	{
	public:
		ST_AdjCoordinate x;
		ST_AdjCoordinate y;
	};

	class CT_XYAdjustHandle
	{
	public:
		CT_AdjPoint2D pos;
		poptional< ST_GeomGuideName > gdRefX;
		poptional< ST_AdjCoordinate > minX;
		poptional< ST_AdjCoordinate > maxX;
		poptional< ST_GeomGuideName > gdRefY;
		poptional< ST_AdjCoordinate > minY;
		poptional< ST_AdjCoordinate > maxY;
	};

	class ST_AdjAngle : public simple_type<String>
	{
	public:
		ST_AdjAngle() {}
		ST_AdjAngle(const String& v) : simple_type<String>(v) {}
	};

	class CT_PolarAdjustHandle
	{
	public:
		CT_AdjPoint2D pos;
		poptional< ST_GeomGuideName > gdRefR;
		poptional< ST_AdjCoordinate > minR;
		poptional< ST_AdjCoordinate > maxR;
		poptional< ST_GeomGuideName > gdRefAng;
		poptional< ST_AdjAngle > minAng;
		poptional< ST_AdjAngle > maxAng;
	};

	class CT_AdjustHandleList
	{
	public:
		poptional< CT_XYAdjustHandle > ahXY;
		poptional< CT_PolarAdjustHandle > ahPolar;
	};

	class CT_ConnectionSite
	{
	public:
		CT_AdjPoint2D pos;
		ST_AdjAngle ang;
	};

	class CT_ConnectionSiteList
	{
	public:
		std::vector< CT_ConnectionSite > cxn;
	};

	class CT_GeomRect
	{
	public:
		ST_AdjCoordinate l;
		ST_AdjCoordinate t;
		ST_AdjCoordinate r;
		ST_AdjCoordinate b;
	};

	class CT_Path2DClose
	{
	public:
	};

	class CT_Path2DMoveTo
	{
	public:
		CT_AdjPoint2D pt;
	};

	class CT_Path2DLineTo
	{
	public:
		CT_AdjPoint2D pt;
	};

	class CT_Path2DArcTo
	{
	public:
		ST_AdjCoordinate wR;
		ST_AdjCoordinate hR;
		ST_AdjAngle stAng;
		ST_AdjAngle swAng;
	};

	class CT_Path2DQuadBezierTo
	{
	public:
		std::vector< CT_AdjPoint2D > pt;
	};

	class CT_Path2DCubicBezierTo
	{
	public:
		std::vector< CT_AdjPoint2D > pt;
	};

	class ST_PathFillMode
	{
		static String _literals[];
		String _value;
	public:
		enum value { darken, darkenLess, lighten, lightenLess, none, norm };

		static const String darken_literal;
		static const String darkenLess_literal;
		static const String lighten_literal;
		static const String lightenLess_literal;
		static const String none_literal;
		static const String norm_literal;

		ST_PathFillMode() : _value(none_literal) {}
		ST_PathFillMode(value val) : _value(convert(val)) {}
		ST_PathFillMode(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 6, 0); }
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

	class CT_Path2D
	{
	public:
		CT_Path2D() : w(0L), h(0L), fill(ST_PathFillMode::norm_literal), stroke(true), extrusionOk(true) {}
		poptional< CT_Path2DClose > close;
		poptional< CT_Path2DMoveTo > moveTo;
		poptional< CT_Path2DLineTo > lnTo;
		poptional< CT_Path2DArcTo > arcTo;
		poptional< CT_Path2DQuadBezierTo > quadBezTo;
		poptional< CT_Path2DCubicBezierTo > cubicBezTo;
		ST_PositiveCoordinate w;
		ST_PositiveCoordinate h;
		ST_PathFillMode fill;
		Boolean stroke;
		Boolean extrusionOk;
	};

	class CT_Path2DList
	{
	public:
		std::vector< CT_Path2D > path;
	};

	class CT_CustomGeometry2D
	{
	public:
		poptional< CT_GeomGuideList > avLst;
		poptional< CT_GeomGuideList > gdLst;
		poptional< CT_AdjustHandleList > ahLst;
		poptional< CT_ConnectionSiteList > cxnLst;
		poptional< CT_GeomRect > rect;
		CT_Path2DList pathLst;
	};

	class ST_ShapeType
	{
		static String _literals[];
		String _value;
	public:
		enum value { accentBorderCallout1, accentBorderCallout2, accentBorderCallout3, accentCallout1, accentCallout2, accentCallout3, actionButtonBackPrevious, actionButtonBeginning, actionButtonBlank, actionButtonDocument, actionButtonEnd, actionButtonForwardNext, actionButtonHelp, actionButtonHome, actionButtonInformation, actionButtonMovie, actionButtonReturn, actionButtonSound, arc, bentArrow, bentConnector2, bentConnector3, bentConnector4, bentConnector5, bentUpArrow, bevel, blockArc, borderCallout1, borderCallout2, borderCallout3, bracePair, bracketPair, callout1, callout2, callout3, can, chartPlus, chartStar, chartX, chevron, chord, circularArrow, cloud, cloudCallout, corner, cornerTabs, cube, curvedConnector2, curvedConnector3, curvedConnector4, curvedConnector5, curvedDownArrow, curvedLeftArrow, curvedRightArrow, curvedUpArrow, decagon, diagStripe, diamond, dodecagon, donut, doubleWave, downArrow, downArrowCallout, ellipse, ellipseRibbon, ellipseRibbon2, flowChartAlternateProcess, flowChartCollate, flowChartConnector, flowChartDecision, flowChartDelay, flowChartDisplay, flowChartDocument, flowChartExtract, flowChartInputOutput, flowChartInternalStorage, flowChartMagneticDisk, flowChartMagneticDrum, flowChartMagneticTape, flowChartManualInput, flowChartManualOperation, flowChartMerge, flowChartMultidocument, flowChartOfflineStorage, flowChartOffpageConnector, flowChartOnlineStorage, flowChartOr, flowChartPredefinedProcess, flowChartPreparation, flowChartProcess, flowChartPunchedCard, flowChartPunchedTape, flowChartSort, flowChartSummingJunction, flowChartTerminator, foldedCorner, frame, funnel, gear6, gear9, halfFrame, heart, heptagon, hexagon, homePlate, horizontalScroll, irregularSeal1, irregularSeal2, leftArrow, leftArrowCallout, leftBrace, leftBracket, leftCircularArrow, leftRightArrow, leftRightArrowCallout, leftRightCircularArrow, leftRightRibbon, leftRightUpArrow, leftUpArrow, lightningBolt, line, lineInv, mathDivide, mathEqual, mathMinus, mathMultiply, mathNotEqual, mathPlus, moon, nonIsoscelesTrapezoid, noSmoking, notchedRightArrow, octagon, parallelogram, pentagon, pie, pieWedge, plaque, plaqueTabs, plus, quadArrow, quadArrowCallout, rect, ribbon, ribbon2, rightArrow, rightArrowCallout, rightBrace, rightBracket, round1Rect, round2DiagRect, round2SameRect, roundRect, rtTriangle, smileyFace, snip1Rect, snip2DiagRect, snip2SameRect, snipRoundRect, squareTabs, star10, star12, star16, star24, star32, star4, star5, star6, star7, star8, straightConnector1, stripedRightArrow, sun, swooshArrow, teardrop, trapezoid, triangle, upArrow, upArrowCallout, upDownArrow, upDownArrowCallout, uturnArrow, verticalScroll, wave, wedgeEllipseCallout, wedgeRectCallout, wedgeRoundRectCallout };

		static const String accentBorderCallout1_literal;
		static const String accentBorderCallout2_literal;
		static const String accentBorderCallout3_literal;
		static const String accentCallout1_literal;
		static const String accentCallout2_literal;
		static const String accentCallout3_literal;
		static const String actionButtonBackPrevious_literal;
		static const String actionButtonBeginning_literal;
		static const String actionButtonBlank_literal;
		static const String actionButtonDocument_literal;
		static const String actionButtonEnd_literal;
		static const String actionButtonForwardNext_literal;
		static const String actionButtonHelp_literal;
		static const String actionButtonHome_literal;
		static const String actionButtonInformation_literal;
		static const String actionButtonMovie_literal;
		static const String actionButtonReturn_literal;
		static const String actionButtonSound_literal;
		static const String arc_literal;
		static const String bentArrow_literal;
		static const String bentConnector2_literal;
		static const String bentConnector3_literal;
		static const String bentConnector4_literal;
		static const String bentConnector5_literal;
		static const String bentUpArrow_literal;
		static const String bevel_literal;
		static const String blockArc_literal;
		static const String borderCallout1_literal;
		static const String borderCallout2_literal;
		static const String borderCallout3_literal;
		static const String bracePair_literal;
		static const String bracketPair_literal;
		static const String callout1_literal;
		static const String callout2_literal;
		static const String callout3_literal;
		static const String can_literal;
		static const String chartPlus_literal;
		static const String chartStar_literal;
		static const String chartX_literal;
		static const String chevron_literal;
		static const String chord_literal;
		static const String circularArrow_literal;
		static const String cloud_literal;
		static const String cloudCallout_literal;
		static const String corner_literal;
		static const String cornerTabs_literal;
		static const String cube_literal;
		static const String curvedConnector2_literal;
		static const String curvedConnector3_literal;
		static const String curvedConnector4_literal;
		static const String curvedConnector5_literal;
		static const String curvedDownArrow_literal;
		static const String curvedLeftArrow_literal;
		static const String curvedRightArrow_literal;
		static const String curvedUpArrow_literal;
		static const String decagon_literal;
		static const String diagStripe_literal;
		static const String diamond_literal;
		static const String dodecagon_literal;
		static const String donut_literal;
		static const String doubleWave_literal;
		static const String downArrow_literal;
		static const String downArrowCallout_literal;
		static const String ellipse_literal;
		static const String ellipseRibbon_literal;
		static const String ellipseRibbon2_literal;
		static const String flowChartAlternateProcess_literal;
		static const String flowChartCollate_literal;
		static const String flowChartConnector_literal;
		static const String flowChartDecision_literal;
		static const String flowChartDelay_literal;
		static const String flowChartDisplay_literal;
		static const String flowChartDocument_literal;
		static const String flowChartExtract_literal;
		static const String flowChartInputOutput_literal;
		static const String flowChartInternalStorage_literal;
		static const String flowChartMagneticDisk_literal;
		static const String flowChartMagneticDrum_literal;
		static const String flowChartMagneticTape_literal;
		static const String flowChartManualInput_literal;
		static const String flowChartManualOperation_literal;
		static const String flowChartMerge_literal;
		static const String flowChartMultidocument_literal;
		static const String flowChartOfflineStorage_literal;
		static const String flowChartOffpageConnector_literal;
		static const String flowChartOnlineStorage_literal;
		static const String flowChartOr_literal;
		static const String flowChartPredefinedProcess_literal;
		static const String flowChartPreparation_literal;
		static const String flowChartProcess_literal;
		static const String flowChartPunchedCard_literal;
		static const String flowChartPunchedTape_literal;
		static const String flowChartSort_literal;
		static const String flowChartSummingJunction_literal;
		static const String flowChartTerminator_literal;
		static const String foldedCorner_literal;
		static const String frame_literal;
		static const String funnel_literal;
		static const String gear6_literal;
		static const String gear9_literal;
		static const String halfFrame_literal;
		static const String heart_literal;
		static const String heptagon_literal;
		static const String hexagon_literal;
		static const String homePlate_literal;
		static const String horizontalScroll_literal;
		static const String irregularSeal1_literal;
		static const String irregularSeal2_literal;
		static const String leftArrow_literal;
		static const String leftArrowCallout_literal;
		static const String leftBrace_literal;
		static const String leftBracket_literal;
		static const String leftCircularArrow_literal;
		static const String leftRightArrow_literal;
		static const String leftRightArrowCallout_literal;
		static const String leftRightCircularArrow_literal;
		static const String leftRightRibbon_literal;
		static const String leftRightUpArrow_literal;
		static const String leftUpArrow_literal;
		static const String lightningBolt_literal;
		static const String line_literal;
		static const String lineInv_literal;
		static const String mathDivide_literal;
		static const String mathEqual_literal;
		static const String mathMinus_literal;
		static const String mathMultiply_literal;
		static const String mathNotEqual_literal;
		static const String mathPlus_literal;
		static const String moon_literal;
		static const String nonIsoscelesTrapezoid_literal;
		static const String noSmoking_literal;
		static const String notchedRightArrow_literal;
		static const String octagon_literal;
		static const String parallelogram_literal;
		static const String pentagon_literal;
		static const String pie_literal;
		static const String pieWedge_literal;
		static const String plaque_literal;
		static const String plaqueTabs_literal;
		static const String plus_literal;
		static const String quadArrow_literal;
		static const String quadArrowCallout_literal;
		static const String rect_literal;
		static const String ribbon_literal;
		static const String ribbon2_literal;
		static const String rightArrow_literal;
		static const String rightArrowCallout_literal;
		static const String rightBrace_literal;
		static const String rightBracket_literal;
		static const String round1Rect_literal;
		static const String round2DiagRect_literal;
		static const String round2SameRect_literal;
		static const String roundRect_literal;
		static const String rtTriangle_literal;
		static const String smileyFace_literal;
		static const String snip1Rect_literal;
		static const String snip2DiagRect_literal;
		static const String snip2SameRect_literal;
		static const String snipRoundRect_literal;
		static const String squareTabs_literal;
		static const String star10_literal;
		static const String star12_literal;
		static const String star16_literal;
		static const String star24_literal;
		static const String star32_literal;
		static const String star4_literal;
		static const String star5_literal;
		static const String star6_literal;
		static const String star7_literal;
		static const String star8_literal;
		static const String straightConnector1_literal;
		static const String stripedRightArrow_literal;
		static const String sun_literal;
		static const String swooshArrow_literal;
		static const String teardrop_literal;
		static const String trapezoid_literal;
		static const String triangle_literal;
		static const String upArrow_literal;
		static const String upArrowCallout_literal;
		static const String upDownArrow_literal;
		static const String upDownArrowCallout_literal;
		static const String uturnArrow_literal;
		static const String verticalScroll_literal;
		static const String wave_literal;
		static const String wedgeEllipseCallout_literal;
		static const String wedgeRectCallout_literal;
		static const String wedgeRoundRectCallout_literal;

		ST_ShapeType() : _value(line_literal) {}
		ST_ShapeType(value val) : _value(convert(val)) {}
		ST_ShapeType(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 187, 0); }
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

	class CT_PresetGeometry2D
	{
	public:
		poptional< CT_GeomGuideList > avLst;
		ST_ShapeType prst;
	};

	class CT_Connection
	{
	public:
		ST_DrawingElementId id;
		UnsignedInt idx;
	};

}
#endif

