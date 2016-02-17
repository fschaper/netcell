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

#ifndef DML_SHAPE3DCAMERA_HPP
#define DML_SHAPE3DCAMERA_HPP


#include "dml-baseTypes.hpp"

namespace drawingml
{
	using namespace ::xio;
	using namespace ::xio::xml::schema;

	class ST_FOVAngle;
	class CT_Camera;

	class ST_PresetCameraType
	{
		static String _literals[];
		String _value;
	public:
		enum value { isometricBottomDown, isometricBottomUp, isometricLeftDown, isometricLeftUp, isometricOffAxis1Left, isometricOffAxis1Right, isometricOffAxis1Top, isometricOffAxis2Left, isometricOffAxis2Right, isometricOffAxis2Top, isometricOffAxis3Bottom, isometricOffAxis3Left, isometricOffAxis3Right, isometricOffAxis4Bottom, isometricOffAxis4Left, isometricOffAxis4Right, isometricRightDown, isometricRightUp, isometricTopDown, isometricTopUp, legacyObliqueBottom, legacyObliqueBottomLeft, legacyObliqueBottomRight, legacyObliqueFront, legacyObliqueLeft, legacyObliqueRight, legacyObliqueTop, legacyObliqueTopLeft, legacyObliqueTopRight, legacyPerspectiveBottom, legacyPerspectiveBottomLeft, legacyPerspectiveBottomRight, legacyPerspectiveFront, legacyPerspectiveLeft, legacyPerspectiveRight, legacyPerspectiveTop, legacyPerspectiveTopLeft, legacyPerspectiveTopRight, obliqueBottom, obliqueBottomLeft, obliqueBottomRight, obliqueLeft, obliqueRight, obliqueTop, obliqueTopLeft, obliqueTopRight, orthographicFront, perspectiveAbove, perspectiveAboveLeftFacing, perspectiveAboveRightFacing, perspectiveBelow, perspectiveContrastingLeftFacing, perspectiveContrastingRightFacing, perspectiveFront, perspectiveHeroicExtremeLeftFacing, perspectiveHeroicExtremeRightFacing, perspectiveHeroicLeftFacing, perspectiveHeroicRightFacing, perspectiveLeft, perspectiveRelaxed, perspectiveRelaxedModerately, perspectiveRight };

		static const String isometricBottomDown_literal;
		static const String isometricBottomUp_literal;
		static const String isometricLeftDown_literal;
		static const String isometricLeftUp_literal;
		static const String isometricOffAxis1Left_literal;
		static const String isometricOffAxis1Right_literal;
		static const String isometricOffAxis1Top_literal;
		static const String isometricOffAxis2Left_literal;
		static const String isometricOffAxis2Right_literal;
		static const String isometricOffAxis2Top_literal;
		static const String isometricOffAxis3Bottom_literal;
		static const String isometricOffAxis3Left_literal;
		static const String isometricOffAxis3Right_literal;
		static const String isometricOffAxis4Bottom_literal;
		static const String isometricOffAxis4Left_literal;
		static const String isometricOffAxis4Right_literal;
		static const String isometricRightDown_literal;
		static const String isometricRightUp_literal;
		static const String isometricTopDown_literal;
		static const String isometricTopUp_literal;
		static const String legacyObliqueBottom_literal;
		static const String legacyObliqueBottomLeft_literal;
		static const String legacyObliqueBottomRight_literal;
		static const String legacyObliqueFront_literal;
		static const String legacyObliqueLeft_literal;
		static const String legacyObliqueRight_literal;
		static const String legacyObliqueTop_literal;
		static const String legacyObliqueTopLeft_literal;
		static const String legacyObliqueTopRight_literal;
		static const String legacyPerspectiveBottom_literal;
		static const String legacyPerspectiveBottomLeft_literal;
		static const String legacyPerspectiveBottomRight_literal;
		static const String legacyPerspectiveFront_literal;
		static const String legacyPerspectiveLeft_literal;
		static const String legacyPerspectiveRight_literal;
		static const String legacyPerspectiveTop_literal;
		static const String legacyPerspectiveTopLeft_literal;
		static const String legacyPerspectiveTopRight_literal;
		static const String obliqueBottom_literal;
		static const String obliqueBottomLeft_literal;
		static const String obliqueBottomRight_literal;
		static const String obliqueLeft_literal;
		static const String obliqueRight_literal;
		static const String obliqueTop_literal;
		static const String obliqueTopLeft_literal;
		static const String obliqueTopRight_literal;
		static const String orthographicFront_literal;
		static const String perspectiveAbove_literal;
		static const String perspectiveAboveLeftFacing_literal;
		static const String perspectiveAboveRightFacing_literal;
		static const String perspectiveBelow_literal;
		static const String perspectiveContrastingLeftFacing_literal;
		static const String perspectiveContrastingRightFacing_literal;
		static const String perspectiveFront_literal;
		static const String perspectiveHeroicExtremeLeftFacing_literal;
		static const String perspectiveHeroicExtremeRightFacing_literal;
		static const String perspectiveHeroicLeftFacing_literal;
		static const String perspectiveHeroicRightFacing_literal;
		static const String perspectiveLeft_literal;
		static const String perspectiveRelaxed_literal;
		static const String perspectiveRelaxedModerately_literal;
		static const String perspectiveRight_literal;

		ST_PresetCameraType() : _value(legacyObliqueTopLeft_literal) {}
		ST_PresetCameraType(value val) : _value(convert(val)) {}
		ST_PresetCameraType(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 62, 0); }
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

	class ST_FOVAngle : public ST_Angle
	{
	public:
		ST_FOVAngle() {}
		ST_FOVAngle(const Int& v) : ST_Angle(v) {}
		ST_FOVAngle(const String& v) { read(v); }
	};

	class CT_Camera
	{
	public:
		CT_Camera() : zoom(100000) {}
		poptional< CT_SphereCoords > rot;
		ST_PresetCameraType prst;
		poptional< ST_FOVAngle > fov;
		ST_PositivePercentage zoom;
	};

}
#endif

