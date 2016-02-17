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


#include "dml-shapeEffects.hpp"
namespace drawingml
{
	const String ST_BlendMode::darken_literal = "darken";
	const String ST_BlendMode::lighten_literal = "lighten";
	const String ST_BlendMode::mult_literal = "mult";
	const String ST_BlendMode::over_literal = "over";
	const String ST_BlendMode::screen_literal = "screen";
	String ST_BlendMode::_literals[] = { ST_BlendMode::darken_literal, ST_BlendMode::lighten_literal, ST_BlendMode::mult_literal, ST_BlendMode::over_literal, ST_BlendMode::screen_literal };

	const String ST_PathShadeType::circle_literal = "circle";
	const String ST_PathShadeType::rect_literal = "rect";
	const String ST_PathShadeType::shape_literal = "shape";
	String ST_PathShadeType::_literals[] = { ST_PathShadeType::circle_literal, ST_PathShadeType::rect_literal, ST_PathShadeType::shape_literal };

	const String ST_TileFlipMode::none_literal = "none";
	const String ST_TileFlipMode::x_literal = "x";
	const String ST_TileFlipMode::xy_literal = "xy";
	const String ST_TileFlipMode::y_literal = "y";
	String ST_TileFlipMode::_literals[] = { ST_TileFlipMode::none_literal, ST_TileFlipMode::x_literal, ST_TileFlipMode::xy_literal, ST_TileFlipMode::y_literal };

	const String ST_PresetPatternVal::cross_literal = "cross";
	const String ST_PresetPatternVal::dashDnDiag_literal = "dashDnDiag";
	const String ST_PresetPatternVal::dashHorz_literal = "dashHorz";
	const String ST_PresetPatternVal::dashUpDiag_literal = "dashUpDiag";
	const String ST_PresetPatternVal::dashVert_literal = "dashVert";
	const String ST_PresetPatternVal::diagBrick_literal = "diagBrick";
	const String ST_PresetPatternVal::diagCross_literal = "diagCross";
	const String ST_PresetPatternVal::divot_literal = "divot";
	const String ST_PresetPatternVal::dkDnDiag_literal = "dkDnDiag";
	const String ST_PresetPatternVal::dkHorz_literal = "dkHorz";
	const String ST_PresetPatternVal::dkUpDiag_literal = "dkUpDiag";
	const String ST_PresetPatternVal::dkVert_literal = "dkVert";
	const String ST_PresetPatternVal::dnDiag_literal = "dnDiag";
	const String ST_PresetPatternVal::dotDmnd_literal = "dotDmnd";
	const String ST_PresetPatternVal::dotGrid_literal = "dotGrid";
	const String ST_PresetPatternVal::horz_literal = "horz";
	const String ST_PresetPatternVal::horzBrick_literal = "horzBrick";
	const String ST_PresetPatternVal::lgCheck_literal = "lgCheck";
	const String ST_PresetPatternVal::lgConfetti_literal = "lgConfetti";
	const String ST_PresetPatternVal::lgGrid_literal = "lgGrid";
	const String ST_PresetPatternVal::ltDnDiag_literal = "ltDnDiag";
	const String ST_PresetPatternVal::ltHorz_literal = "ltHorz";
	const String ST_PresetPatternVal::ltUpDiag_literal = "ltUpDiag";
	const String ST_PresetPatternVal::ltVert_literal = "ltVert";
	const String ST_PresetPatternVal::narHorz_literal = "narHorz";
	const String ST_PresetPatternVal::narVert_literal = "narVert";
	const String ST_PresetPatternVal::openDmnd_literal = "openDmnd";
	const String ST_PresetPatternVal::pct10_literal = "pct10";
	const String ST_PresetPatternVal::pct20_literal = "pct20";
	const String ST_PresetPatternVal::pct25_literal = "pct25";
	const String ST_PresetPatternVal::pct30_literal = "pct30";
	const String ST_PresetPatternVal::pct40_literal = "pct40";
	const String ST_PresetPatternVal::pct5_literal = "pct5";
	const String ST_PresetPatternVal::pct50_literal = "pct50";
	const String ST_PresetPatternVal::pct60_literal = "pct60";
	const String ST_PresetPatternVal::pct70_literal = "pct70";
	const String ST_PresetPatternVal::pct75_literal = "pct75";
	const String ST_PresetPatternVal::pct80_literal = "pct80";
	const String ST_PresetPatternVal::pct90_literal = "pct90";
	const String ST_PresetPatternVal::plaid_literal = "plaid";
	const String ST_PresetPatternVal::shingle_literal = "shingle";
	const String ST_PresetPatternVal::smCheck_literal = "smCheck";
	const String ST_PresetPatternVal::smConfetti_literal = "smConfetti";
	const String ST_PresetPatternVal::smGrid_literal = "smGrid";
	const String ST_PresetPatternVal::solidDmnd_literal = "solidDmnd";
	const String ST_PresetPatternVal::sphere_literal = "sphere";
	const String ST_PresetPatternVal::trellis_literal = "trellis";
	const String ST_PresetPatternVal::upDiag_literal = "upDiag";
	const String ST_PresetPatternVal::vert_literal = "vert";
	const String ST_PresetPatternVal::wave_literal = "wave";
	const String ST_PresetPatternVal::wdDnDiag_literal = "wdDnDiag";
	const String ST_PresetPatternVal::wdUpDiag_literal = "wdUpDiag";
	const String ST_PresetPatternVal::weave_literal = "weave";
	const String ST_PresetPatternVal::zigZag_literal = "zigZag";
	String ST_PresetPatternVal::_literals[] = { ST_PresetPatternVal::cross_literal, ST_PresetPatternVal::dashDnDiag_literal, ST_PresetPatternVal::dashHorz_literal, ST_PresetPatternVal::dashUpDiag_literal, ST_PresetPatternVal::dashVert_literal, ST_PresetPatternVal::diagBrick_literal, ST_PresetPatternVal::diagCross_literal, ST_PresetPatternVal::divot_literal, ST_PresetPatternVal::dkDnDiag_literal, ST_PresetPatternVal::dkHorz_literal, ST_PresetPatternVal::dkUpDiag_literal, ST_PresetPatternVal::dkVert_literal, ST_PresetPatternVal::dnDiag_literal, ST_PresetPatternVal::dotDmnd_literal, ST_PresetPatternVal::dotGrid_literal, ST_PresetPatternVal::horz_literal, ST_PresetPatternVal::horzBrick_literal, ST_PresetPatternVal::lgCheck_literal, ST_PresetPatternVal::lgConfetti_literal, ST_PresetPatternVal::lgGrid_literal, ST_PresetPatternVal::ltDnDiag_literal, ST_PresetPatternVal::ltHorz_literal, ST_PresetPatternVal::ltUpDiag_literal, ST_PresetPatternVal::ltVert_literal, ST_PresetPatternVal::narHorz_literal, ST_PresetPatternVal::narVert_literal, ST_PresetPatternVal::openDmnd_literal, ST_PresetPatternVal::pct10_literal, ST_PresetPatternVal::pct20_literal, ST_PresetPatternVal::pct25_literal, ST_PresetPatternVal::pct30_literal, ST_PresetPatternVal::pct40_literal, ST_PresetPatternVal::pct5_literal, ST_PresetPatternVal::pct50_literal, ST_PresetPatternVal::pct60_literal, ST_PresetPatternVal::pct70_literal, ST_PresetPatternVal::pct75_literal, ST_PresetPatternVal::pct80_literal, ST_PresetPatternVal::pct90_literal, ST_PresetPatternVal::plaid_literal, ST_PresetPatternVal::shingle_literal, ST_PresetPatternVal::smCheck_literal, ST_PresetPatternVal::smConfetti_literal, ST_PresetPatternVal::smGrid_literal, ST_PresetPatternVal::solidDmnd_literal, ST_PresetPatternVal::sphere_literal, ST_PresetPatternVal::trellis_literal, ST_PresetPatternVal::upDiag_literal, ST_PresetPatternVal::vert_literal, ST_PresetPatternVal::wave_literal, ST_PresetPatternVal::wdDnDiag_literal, ST_PresetPatternVal::wdUpDiag_literal, ST_PresetPatternVal::weave_literal, ST_PresetPatternVal::zigZag_literal };

	const String ST_PresetShadowVal::shdw1_literal = "shdw1";
	const String ST_PresetShadowVal::shdw10_literal = "shdw10";
	const String ST_PresetShadowVal::shdw11_literal = "shdw11";
	const String ST_PresetShadowVal::shdw12_literal = "shdw12";
	const String ST_PresetShadowVal::shdw13_literal = "shdw13";
	const String ST_PresetShadowVal::shdw14_literal = "shdw14";
	const String ST_PresetShadowVal::shdw15_literal = "shdw15";
	const String ST_PresetShadowVal::shdw16_literal = "shdw16";
	const String ST_PresetShadowVal::shdw17_literal = "shdw17";
	const String ST_PresetShadowVal::shdw18_literal = "shdw18";
	const String ST_PresetShadowVal::shdw19_literal = "shdw19";
	const String ST_PresetShadowVal::shdw2_literal = "shdw2";
	const String ST_PresetShadowVal::shdw20_literal = "shdw20";
	const String ST_PresetShadowVal::shdw3_literal = "shdw3";
	const String ST_PresetShadowVal::shdw4_literal = "shdw4";
	const String ST_PresetShadowVal::shdw5_literal = "shdw5";
	const String ST_PresetShadowVal::shdw6_literal = "shdw6";
	const String ST_PresetShadowVal::shdw7_literal = "shdw7";
	const String ST_PresetShadowVal::shdw8_literal = "shdw8";
	const String ST_PresetShadowVal::shdw9_literal = "shdw9";
	String ST_PresetShadowVal::_literals[] = { ST_PresetShadowVal::shdw1_literal, ST_PresetShadowVal::shdw10_literal, ST_PresetShadowVal::shdw11_literal, ST_PresetShadowVal::shdw12_literal, ST_PresetShadowVal::shdw13_literal, ST_PresetShadowVal::shdw14_literal, ST_PresetShadowVal::shdw15_literal, ST_PresetShadowVal::shdw16_literal, ST_PresetShadowVal::shdw17_literal, ST_PresetShadowVal::shdw18_literal, ST_PresetShadowVal::shdw19_literal, ST_PresetShadowVal::shdw2_literal, ST_PresetShadowVal::shdw20_literal, ST_PresetShadowVal::shdw3_literal, ST_PresetShadowVal::shdw4_literal, ST_PresetShadowVal::shdw5_literal, ST_PresetShadowVal::shdw6_literal, ST_PresetShadowVal::shdw7_literal, ST_PresetShadowVal::shdw8_literal, ST_PresetShadowVal::shdw9_literal };

	const String ST_EffectContainerType::sib_literal = "sib";
	const String ST_EffectContainerType::tree_literal = "tree";
	String ST_EffectContainerType::_literals[] = { ST_EffectContainerType::sib_literal, ST_EffectContainerType::tree_literal };

	const String ST_BlipCompression::email_literal = "email";
	const String ST_BlipCompression::hqprint_literal = "hqprint";
	const String ST_BlipCompression::none_literal = "none";
	const String ST_BlipCompression::print_literal = "print";
	const String ST_BlipCompression::screen_literal = "screen";
	String ST_BlipCompression::_literals[] = { ST_BlipCompression::email_literal, ST_BlipCompression::hqprint_literal, ST_BlipCompression::none_literal, ST_BlipCompression::print_literal, ST_BlipCompression::screen_literal };

}
