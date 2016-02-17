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


#include "dml-shape3DCamera.hpp"
namespace drawingml
{
	const String ST_PresetCameraType::isometricBottomDown_literal = "isometricBottomDown";
	const String ST_PresetCameraType::isometricBottomUp_literal = "isometricBottomUp";
	const String ST_PresetCameraType::isometricLeftDown_literal = "isometricLeftDown";
	const String ST_PresetCameraType::isometricLeftUp_literal = "isometricLeftUp";
	const String ST_PresetCameraType::isometricOffAxis1Left_literal = "isometricOffAxis1Left";
	const String ST_PresetCameraType::isometricOffAxis1Right_literal = "isometricOffAxis1Right";
	const String ST_PresetCameraType::isometricOffAxis1Top_literal = "isometricOffAxis1Top";
	const String ST_PresetCameraType::isometricOffAxis2Left_literal = "isometricOffAxis2Left";
	const String ST_PresetCameraType::isometricOffAxis2Right_literal = "isometricOffAxis2Right";
	const String ST_PresetCameraType::isometricOffAxis2Top_literal = "isometricOffAxis2Top";
	const String ST_PresetCameraType::isometricOffAxis3Bottom_literal = "isometricOffAxis3Bottom";
	const String ST_PresetCameraType::isometricOffAxis3Left_literal = "isometricOffAxis3Left";
	const String ST_PresetCameraType::isometricOffAxis3Right_literal = "isometricOffAxis3Right";
	const String ST_PresetCameraType::isometricOffAxis4Bottom_literal = "isometricOffAxis4Bottom";
	const String ST_PresetCameraType::isometricOffAxis4Left_literal = "isometricOffAxis4Left";
	const String ST_PresetCameraType::isometricOffAxis4Right_literal = "isometricOffAxis4Right";
	const String ST_PresetCameraType::isometricRightDown_literal = "isometricRightDown";
	const String ST_PresetCameraType::isometricRightUp_literal = "isometricRightUp";
	const String ST_PresetCameraType::isometricTopDown_literal = "isometricTopDown";
	const String ST_PresetCameraType::isometricTopUp_literal = "isometricTopUp";
	const String ST_PresetCameraType::legacyObliqueBottom_literal = "legacyObliqueBottom";
	const String ST_PresetCameraType::legacyObliqueBottomLeft_literal = "legacyObliqueBottomLeft";
	const String ST_PresetCameraType::legacyObliqueBottomRight_literal = "legacyObliqueBottomRight";
	const String ST_PresetCameraType::legacyObliqueFront_literal = "legacyObliqueFront";
	const String ST_PresetCameraType::legacyObliqueLeft_literal = "legacyObliqueLeft";
	const String ST_PresetCameraType::legacyObliqueRight_literal = "legacyObliqueRight";
	const String ST_PresetCameraType::legacyObliqueTop_literal = "legacyObliqueTop";
	const String ST_PresetCameraType::legacyObliqueTopLeft_literal = "legacyObliqueTopLeft";
	const String ST_PresetCameraType::legacyObliqueTopRight_literal = "legacyObliqueTopRight";
	const String ST_PresetCameraType::legacyPerspectiveBottom_literal = "legacyPerspectiveBottom";
	const String ST_PresetCameraType::legacyPerspectiveBottomLeft_literal = "legacyPerspectiveBottomLeft";
	const String ST_PresetCameraType::legacyPerspectiveBottomRight_literal = "legacyPerspectiveBottomRight";
	const String ST_PresetCameraType::legacyPerspectiveFront_literal = "legacyPerspectiveFront";
	const String ST_PresetCameraType::legacyPerspectiveLeft_literal = "legacyPerspectiveLeft";
	const String ST_PresetCameraType::legacyPerspectiveRight_literal = "legacyPerspectiveRight";
	const String ST_PresetCameraType::legacyPerspectiveTop_literal = "legacyPerspectiveTop";
	const String ST_PresetCameraType::legacyPerspectiveTopLeft_literal = "legacyPerspectiveTopLeft";
	const String ST_PresetCameraType::legacyPerspectiveTopRight_literal = "legacyPerspectiveTopRight";
	const String ST_PresetCameraType::obliqueBottom_literal = "obliqueBottom";
	const String ST_PresetCameraType::obliqueBottomLeft_literal = "obliqueBottomLeft";
	const String ST_PresetCameraType::obliqueBottomRight_literal = "obliqueBottomRight";
	const String ST_PresetCameraType::obliqueLeft_literal = "obliqueLeft";
	const String ST_PresetCameraType::obliqueRight_literal = "obliqueRight";
	const String ST_PresetCameraType::obliqueTop_literal = "obliqueTop";
	const String ST_PresetCameraType::obliqueTopLeft_literal = "obliqueTopLeft";
	const String ST_PresetCameraType::obliqueTopRight_literal = "obliqueTopRight";
	const String ST_PresetCameraType::orthographicFront_literal = "orthographicFront";
	const String ST_PresetCameraType::perspectiveAbove_literal = "perspectiveAbove";
	const String ST_PresetCameraType::perspectiveAboveLeftFacing_literal = "perspectiveAboveLeftFacing";
	const String ST_PresetCameraType::perspectiveAboveRightFacing_literal = "perspectiveAboveRightFacing";
	const String ST_PresetCameraType::perspectiveBelow_literal = "perspectiveBelow";
	const String ST_PresetCameraType::perspectiveContrastingLeftFacing_literal = "perspectiveContrastingLeftFacing";
	const String ST_PresetCameraType::perspectiveContrastingRightFacing_literal = "perspectiveContrastingRightFacing";
	const String ST_PresetCameraType::perspectiveFront_literal = "perspectiveFront";
	const String ST_PresetCameraType::perspectiveHeroicExtremeLeftFacing_literal = "perspectiveHeroicExtremeLeftFacing";
	const String ST_PresetCameraType::perspectiveHeroicExtremeRightFacing_literal = "perspectiveHeroicExtremeRightFacing";
	const String ST_PresetCameraType::perspectiveHeroicLeftFacing_literal = "perspectiveHeroicLeftFacing";
	const String ST_PresetCameraType::perspectiveHeroicRightFacing_literal = "perspectiveHeroicRightFacing";
	const String ST_PresetCameraType::perspectiveLeft_literal = "perspectiveLeft";
	const String ST_PresetCameraType::perspectiveRelaxed_literal = "perspectiveRelaxed";
	const String ST_PresetCameraType::perspectiveRelaxedModerately_literal = "perspectiveRelaxedModerately";
	const String ST_PresetCameraType::perspectiveRight_literal = "perspectiveRight";
	String ST_PresetCameraType::_literals[] = { ST_PresetCameraType::isometricBottomDown_literal, ST_PresetCameraType::isometricBottomUp_literal, ST_PresetCameraType::isometricLeftDown_literal, ST_PresetCameraType::isometricLeftUp_literal, ST_PresetCameraType::isometricOffAxis1Left_literal, ST_PresetCameraType::isometricOffAxis1Right_literal, ST_PresetCameraType::isometricOffAxis1Top_literal, ST_PresetCameraType::isometricOffAxis2Left_literal, ST_PresetCameraType::isometricOffAxis2Right_literal, ST_PresetCameraType::isometricOffAxis2Top_literal, ST_PresetCameraType::isometricOffAxis3Bottom_literal, ST_PresetCameraType::isometricOffAxis3Left_literal, ST_PresetCameraType::isometricOffAxis3Right_literal, ST_PresetCameraType::isometricOffAxis4Bottom_literal, ST_PresetCameraType::isometricOffAxis4Left_literal, ST_PresetCameraType::isometricOffAxis4Right_literal, ST_PresetCameraType::isometricRightDown_literal, ST_PresetCameraType::isometricRightUp_literal, ST_PresetCameraType::isometricTopDown_literal, ST_PresetCameraType::isometricTopUp_literal, ST_PresetCameraType::legacyObliqueBottom_literal, ST_PresetCameraType::legacyObliqueBottomLeft_literal, ST_PresetCameraType::legacyObliqueBottomRight_literal, ST_PresetCameraType::legacyObliqueFront_literal, ST_PresetCameraType::legacyObliqueLeft_literal, ST_PresetCameraType::legacyObliqueRight_literal, ST_PresetCameraType::legacyObliqueTop_literal, ST_PresetCameraType::legacyObliqueTopLeft_literal, ST_PresetCameraType::legacyObliqueTopRight_literal, ST_PresetCameraType::legacyPerspectiveBottom_literal, ST_PresetCameraType::legacyPerspectiveBottomLeft_literal, ST_PresetCameraType::legacyPerspectiveBottomRight_literal, ST_PresetCameraType::legacyPerspectiveFront_literal, ST_PresetCameraType::legacyPerspectiveLeft_literal, ST_PresetCameraType::legacyPerspectiveRight_literal, ST_PresetCameraType::legacyPerspectiveTop_literal, ST_PresetCameraType::legacyPerspectiveTopLeft_literal, ST_PresetCameraType::legacyPerspectiveTopRight_literal, ST_PresetCameraType::obliqueBottom_literal, ST_PresetCameraType::obliqueBottomLeft_literal, ST_PresetCameraType::obliqueBottomRight_literal, ST_PresetCameraType::obliqueLeft_literal, ST_PresetCameraType::obliqueRight_literal, ST_PresetCameraType::obliqueTop_literal, ST_PresetCameraType::obliqueTopLeft_literal, ST_PresetCameraType::obliqueTopRight_literal, ST_PresetCameraType::orthographicFront_literal, ST_PresetCameraType::perspectiveAbove_literal, ST_PresetCameraType::perspectiveAboveLeftFacing_literal, ST_PresetCameraType::perspectiveAboveRightFacing_literal, ST_PresetCameraType::perspectiveBelow_literal, ST_PresetCameraType::perspectiveContrastingLeftFacing_literal, ST_PresetCameraType::perspectiveContrastingRightFacing_literal, ST_PresetCameraType::perspectiveFront_literal, ST_PresetCameraType::perspectiveHeroicExtremeLeftFacing_literal, ST_PresetCameraType::perspectiveHeroicExtremeRightFacing_literal, ST_PresetCameraType::perspectiveHeroicLeftFacing_literal, ST_PresetCameraType::perspectiveHeroicRightFacing_literal, ST_PresetCameraType::perspectiveLeft_literal, ST_PresetCameraType::perspectiveRelaxed_literal, ST_PresetCameraType::perspectiveRelaxedModerately_literal, ST_PresetCameraType::perspectiveRight_literal };

}
