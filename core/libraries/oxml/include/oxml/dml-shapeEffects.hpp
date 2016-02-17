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

#ifndef DML_SHAPEEFFECTS_HPP
#define DML_SHAPEEFFECTS_HPP


#include "dml-baseTypes.hpp"
#include "shared-relationshipReference.hpp"

namespace drawingml
{
	using namespace ::xio;
	using namespace ::xio::xml::schema;

	class CT_AlphaBiLevelEffect;
	class CT_AlphaCeilingEffect;
	class CT_AlphaFloorEffect;
	class CT_AlphaInverseEffect;
	class CT_EffectReference;
	class CT_AlphaModulateFixedEffect;
	class CT_AlphaOutsetEffect;
	class CT_AlphaReplaceEffect;
	class CT_BiLevelEffect;
	class CT_BlurEffect;
	class CT_ColorChangeEffect;
	class CT_ColorReplaceEffect;
	class CT_DuotoneEffect;
	class CT_NoFillProperties;
	class CT_SolidColorFillProperties;
	class CT_GradientStop;
	class CT_GradientStopList;
	class CT_LinearShadeProperties;
	class CT_PathShadeProperties;
	class CT_GradientFillProperties;
	class CT_TileInfoProperties;
	class CT_StretchInfoProperties;
	class CT_BlipFillProperties;
	class CT_PatternFillProperties;
	class CT_GroupFillProperties;
	class CT_FillEffect;
	class CT_FillOverlayEffect;
	class CT_GlowEffect;
	class CT_GrayscaleEffect;
	class CT_HSLEffect;
	class CT_InnerShadowEffect;
	class CT_LuminanceEffect;
	class CT_OuterShadowEffect;
	class CT_PresetShadowEffect;
	class CT_ReflectionEffect;
	class CT_RelativeOffsetEffect;
	class CT_SoftEdgesEffect;
	class CT_TintEffect;
	class CT_TransformEffect;
	class CT_EffectContainer;
	class CT_AlphaModulateEffect;
	class CT_Blip;
	class CT_EffectList;
	class dml_shapeEffects;
	class CT_FillProperties;
	class CT_EffectProperties;
	class CT_BlendEffect;

	class CT_AlphaBiLevelEffect
	{
	public:
		ST_PositiveFixedPercentage thresh;
	};

	class CT_AlphaCeilingEffect
	{
	public:
	};

	class CT_AlphaFloorEffect
	{
	public:
	};

	class CT_AlphaInverseEffect
	{
	public:
		poptional< CT_ScRgbColor > scrgbClr;
		poptional< CT_SRgbColor > srgbClr;
		poptional< CT_HslColor > hslClr;
		poptional< CT_SystemColor > sysClr;
		poptional< CT_SchemeColor > schemeClr;
		poptional< CT_PresetColor > prstClr;
	};

	class CT_EffectReference
	{
	public:
		optional< Token > ref;
	};

	class CT_AlphaModulateFixedEffect
	{
	public:
		CT_AlphaModulateFixedEffect() : amt(100000) {}
		ST_PositivePercentage amt;
	};

	class CT_AlphaOutsetEffect
	{
	public:
		CT_AlphaOutsetEffect() : rad(0L) {}
		ST_Coordinate rad;
	};

	class CT_AlphaReplaceEffect
	{
	public:
		ST_PositiveFixedPercentage a;
	};

	class CT_BiLevelEffect
	{
	public:
		ST_PositiveFixedPercentage thresh;
	};

	class ST_BlendMode
	{
		static String _literals[];
		String _value;
	public:
		enum value { darken, lighten, mult, over, screen };

		static const String darken_literal;
		static const String lighten_literal;
		static const String mult_literal;
		static const String over_literal;
		static const String screen_literal;

		ST_BlendMode() : _value(over_literal) {}
		ST_BlendMode(value val) : _value(convert(val)) {}
		ST_BlendMode(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 5, 0); }
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

	class CT_BlurEffect
	{
	public:
		CT_BlurEffect() : rad(0L), grow(true) {}
		ST_PositiveCoordinate rad;
		Boolean grow;
	};

	class CT_ColorChangeEffect
	{
	public:
		CT_ColorChangeEffect() : useA(true) {}
		CT_Color clrFrom;
		CT_Color clrTo;
		Boolean useA;
	};

	class CT_ColorReplaceEffect
	{
	public:
		poptional< CT_ScRgbColor > scrgbClr;
		poptional< CT_SRgbColor > srgbClr;
		poptional< CT_HslColor > hslClr;
		poptional< CT_SystemColor > sysClr;
		poptional< CT_SchemeColor > schemeClr;
		poptional< CT_PresetColor > prstClr;
	};

	class CT_DuotoneEffect
	{
	public:
		poptional< CT_ScRgbColor > scrgbClr;
		poptional< CT_SRgbColor > srgbClr;
		poptional< CT_HslColor > hslClr;
		poptional< CT_SystemColor > sysClr;
		poptional< CT_SchemeColor > schemeClr;
		poptional< CT_PresetColor > prstClr;
	};

	class CT_NoFillProperties
	{
	public:
	};

	class CT_SolidColorFillProperties
	{
	public:
		poptional< CT_ScRgbColor > scrgbClr;
		poptional< CT_SRgbColor > srgbClr;
		poptional< CT_HslColor > hslClr;
		poptional< CT_SystemColor > sysClr;
		poptional< CT_SchemeColor > schemeClr;
		poptional< CT_PresetColor > prstClr;
	};

	class CT_GradientStop
	{
	public:
		poptional< CT_ScRgbColor > scrgbClr;
		poptional< CT_SRgbColor > srgbClr;
		poptional< CT_HslColor > hslClr;
		poptional< CT_SystemColor > sysClr;
		poptional< CT_SchemeColor > schemeClr;
		poptional< CT_PresetColor > prstClr;
		ST_PositiveFixedPercentage pos;
	};

	class CT_GradientStopList
	{
	public:
		std::vector< CT_GradientStop > gs;
	};

	class CT_LinearShadeProperties
	{
	public:
		poptional< ST_PositiveFixedAngle > ang;
		optional< Boolean > scaled;
	};

	class ST_PathShadeType
	{
		static String _literals[];
		String _value;
	public:
		enum value { circle, rect, shape };

		static const String circle_literal;
		static const String rect_literal;
		static const String shape_literal;

		ST_PathShadeType() : _value(shape_literal) {}
		ST_PathShadeType(value val) : _value(convert(val)) {}
		ST_PathShadeType(const String& str) : _value(str) {}

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

	class CT_PathShadeProperties
	{
	public:
		poptional< CT_RelativeRect > fillToRect;
		optional< ST_PathShadeType > path;
	};

	class ST_TileFlipMode
	{
		static String _literals[];
		String _value;
	public:
		enum value { none, x, xy, y };

		static const String none_literal;
		static const String x_literal;
		static const String xy_literal;
		static const String y_literal;

		ST_TileFlipMode() : _value(none_literal) {}
		ST_TileFlipMode(value val) : _value(convert(val)) {}
		ST_TileFlipMode(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 4, 0); }
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

	class CT_GradientFillProperties
	{
	public:
		poptional< CT_GradientStopList > gsLst;
		poptional< CT_LinearShadeProperties > lin;
		poptional< CT_PathShadeProperties > path;
		poptional< CT_RelativeRect > tileRect;
		optional< ST_TileFlipMode > flip;
		optional< Boolean > rotWithShape;
	};

	class CT_TileInfoProperties
	{
	public:
		poptional< ST_Coordinate > tx;
		poptional< ST_Coordinate > ty;
		poptional< ST_Percentage > sx;
		poptional< ST_Percentage > sy;
		optional< ST_TileFlipMode > flip;
		optional< ST_RectAlignment > algn;
	};

	class CT_StretchInfoProperties
	{
	public:
		poptional< CT_RelativeRect > fillRect;
	};

	class CT_BlipFillProperties
	{
	public:
		poptional< CT_Blip > blip;
		poptional< CT_RelativeRect > srcRect;
		poptional< CT_TileInfoProperties > tile;
		poptional< CT_StretchInfoProperties > stretch;
		optional< UnsignedInt > dpi;
		optional< Boolean > rotWithShape;
	};

	class ST_PresetPatternVal
	{
		static String _literals[];
		String _value;
	public:
		enum value { cross, dashDnDiag, dashHorz, dashUpDiag, dashVert, diagBrick, diagCross, divot, dkDnDiag, dkHorz, dkUpDiag, dkVert, dnDiag, dotDmnd, dotGrid, horz, horzBrick, lgCheck, lgConfetti, lgGrid, ltDnDiag, ltHorz, ltUpDiag, ltVert, narHorz, narVert, openDmnd, pct10, pct20, pct25, pct30, pct40, pct5, pct50, pct60, pct70, pct75, pct80, pct90, plaid, shingle, smCheck, smConfetti, smGrid, solidDmnd, sphere, trellis, upDiag, vert, wave, wdDnDiag, wdUpDiag, weave, zigZag };

		static const String cross_literal;
		static const String dashDnDiag_literal;
		static const String dashHorz_literal;
		static const String dashUpDiag_literal;
		static const String dashVert_literal;
		static const String diagBrick_literal;
		static const String diagCross_literal;
		static const String divot_literal;
		static const String dkDnDiag_literal;
		static const String dkHorz_literal;
		static const String dkUpDiag_literal;
		static const String dkVert_literal;
		static const String dnDiag_literal;
		static const String dotDmnd_literal;
		static const String dotGrid_literal;
		static const String horz_literal;
		static const String horzBrick_literal;
		static const String lgCheck_literal;
		static const String lgConfetti_literal;
		static const String lgGrid_literal;
		static const String ltDnDiag_literal;
		static const String ltHorz_literal;
		static const String ltUpDiag_literal;
		static const String ltVert_literal;
		static const String narHorz_literal;
		static const String narVert_literal;
		static const String openDmnd_literal;
		static const String pct10_literal;
		static const String pct20_literal;
		static const String pct25_literal;
		static const String pct30_literal;
		static const String pct40_literal;
		static const String pct5_literal;
		static const String pct50_literal;
		static const String pct60_literal;
		static const String pct70_literal;
		static const String pct75_literal;
		static const String pct80_literal;
		static const String pct90_literal;
		static const String plaid_literal;
		static const String shingle_literal;
		static const String smCheck_literal;
		static const String smConfetti_literal;
		static const String smGrid_literal;
		static const String solidDmnd_literal;
		static const String sphere_literal;
		static const String trellis_literal;
		static const String upDiag_literal;
		static const String vert_literal;
		static const String wave_literal;
		static const String wdDnDiag_literal;
		static const String wdUpDiag_literal;
		static const String weave_literal;
		static const String zigZag_literal;

		ST_PresetPatternVal() : _value(pct5_literal) {}
		ST_PresetPatternVal(value val) : _value(convert(val)) {}
		ST_PresetPatternVal(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 54, 0); }
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

	class CT_PatternFillProperties
	{
	public:
		poptional< CT_Color > fgClr;
		poptional< CT_Color > bgClr;
		optional< ST_PresetPatternVal > prst;
	};

	class CT_GroupFillProperties
	{
	public:
	};

	class CT_FillEffect
	{
	public:
		poptional< CT_NoFillProperties > noFill;
		poptional< CT_SolidColorFillProperties > solidFill;
		poptional< CT_GradientFillProperties > gradFill;
		poptional< CT_BlipFillProperties > blipFill;
		poptional< CT_PatternFillProperties > pattFill;
		poptional< CT_GroupFillProperties > grpFill;
	};

	class CT_FillOverlayEffect
	{
	public:
		poptional< CT_NoFillProperties > noFill;
		poptional< CT_SolidColorFillProperties > solidFill;
		poptional< CT_GradientFillProperties > gradFill;
		poptional< CT_BlipFillProperties > blipFill;
		poptional< CT_PatternFillProperties > pattFill;
		poptional< CT_GroupFillProperties > grpFill;
		ST_BlendMode blend;
	};

	class CT_GlowEffect
	{
	public:
		CT_GlowEffect() : rad(0L) {}
		poptional< CT_ScRgbColor > scrgbClr;
		poptional< CT_SRgbColor > srgbClr;
		poptional< CT_HslColor > hslClr;
		poptional< CT_SystemColor > sysClr;
		poptional< CT_SchemeColor > schemeClr;
		poptional< CT_PresetColor > prstClr;
		ST_PositiveCoordinate rad;
	};

	class CT_GrayscaleEffect
	{
	public:
	};

	class CT_HSLEffect
	{
	public:
		CT_HSLEffect() : hue(0), sat(0), lum(0) {}
		ST_PositiveFixedAngle hue;
		ST_FixedPercentage sat;
		ST_FixedPercentage lum;
	};

	class CT_InnerShadowEffect
	{
	public:
		CT_InnerShadowEffect() : blurRad(0L), dist(0L), dir(0) {}
		poptional< CT_ScRgbColor > scrgbClr;
		poptional< CT_SRgbColor > srgbClr;
		poptional< CT_HslColor > hslClr;
		poptional< CT_SystemColor > sysClr;
		poptional< CT_SchemeColor > schemeClr;
		poptional< CT_PresetColor > prstClr;
		ST_PositiveCoordinate blurRad;
		ST_PositiveCoordinate dist;
		ST_PositiveFixedAngle dir;
	};

	class CT_LuminanceEffect
	{
	public:
		CT_LuminanceEffect() : bright(0), contrast(0) {}
		ST_FixedPercentage bright;
		ST_FixedPercentage contrast;
	};

	class CT_OuterShadowEffect
	{
	public:
		CT_OuterShadowEffect() : blurRad(0L), dist(0L), dir(0), sx(100000), sy(100000), kx(0), ky(0), algn(ST_RectAlignment::b_literal), rotWithShape(true) {}
		poptional< CT_ScRgbColor > scrgbClr;
		poptional< CT_SRgbColor > srgbClr;
		poptional< CT_HslColor > hslClr;
		poptional< CT_SystemColor > sysClr;
		poptional< CT_SchemeColor > schemeClr;
		poptional< CT_PresetColor > prstClr;
		ST_PositiveCoordinate blurRad;
		ST_PositiveCoordinate dist;
		ST_PositiveFixedAngle dir;
		ST_Percentage sx;
		ST_Percentage sy;
		ST_FixedAngle kx;
		ST_FixedAngle ky;
		ST_RectAlignment algn;
		Boolean rotWithShape;
	};

	class ST_PresetShadowVal
	{
		static String _literals[];
		String _value;
	public:
		enum value { shdw1, shdw10, shdw11, shdw12, shdw13, shdw14, shdw15, shdw16, shdw17, shdw18, shdw19, shdw2, shdw20, shdw3, shdw4, shdw5, shdw6, shdw7, shdw8, shdw9 };

		static const String shdw1_literal;
		static const String shdw10_literal;
		static const String shdw11_literal;
		static const String shdw12_literal;
		static const String shdw13_literal;
		static const String shdw14_literal;
		static const String shdw15_literal;
		static const String shdw16_literal;
		static const String shdw17_literal;
		static const String shdw18_literal;
		static const String shdw19_literal;
		static const String shdw2_literal;
		static const String shdw20_literal;
		static const String shdw3_literal;
		static const String shdw4_literal;
		static const String shdw5_literal;
		static const String shdw6_literal;
		static const String shdw7_literal;
		static const String shdw8_literal;
		static const String shdw9_literal;

		ST_PresetShadowVal() : _value(shdw1_literal) {}
		ST_PresetShadowVal(value val) : _value(convert(val)) {}
		ST_PresetShadowVal(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 20, 0); }
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

	class CT_PresetShadowEffect
	{
	public:
		CT_PresetShadowEffect() : dist(0L), dir(0) {}
		poptional< CT_ScRgbColor > scrgbClr;
		poptional< CT_SRgbColor > srgbClr;
		poptional< CT_HslColor > hslClr;
		poptional< CT_SystemColor > sysClr;
		poptional< CT_SchemeColor > schemeClr;
		poptional< CT_PresetColor > prstClr;
		ST_PresetShadowVal prst;
		ST_PositiveCoordinate dist;
		ST_PositiveFixedAngle dir;
	};

	class CT_ReflectionEffect
	{
	public:
		CT_ReflectionEffect() : blurRad(0L), stA(100000), stPos(0), endA(0), endPos(100000), dist(0L), dir(0), fadeDir(5400000), sx(100000), sy(100000), kx(0), ky(0), algn(ST_RectAlignment::b_literal), rotWithShape(true) {}
		ST_PositiveCoordinate blurRad;
		ST_PositiveFixedPercentage stA;
		ST_PositiveFixedPercentage stPos;
		ST_PositiveFixedPercentage endA;
		ST_PositiveFixedPercentage endPos;
		ST_PositiveCoordinate dist;
		ST_PositiveFixedAngle dir;
		ST_PositiveFixedAngle fadeDir;
		ST_Percentage sx;
		ST_Percentage sy;
		ST_FixedAngle kx;
		ST_FixedAngle ky;
		ST_RectAlignment algn;
		Boolean rotWithShape;
	};

	class CT_RelativeOffsetEffect
	{
	public:
		CT_RelativeOffsetEffect() : tx(0), ty(0) {}
		ST_Percentage tx;
		ST_Percentage ty;
	};

	class CT_SoftEdgesEffect
	{
	public:
		ST_PositiveCoordinate rad;
	};

	class CT_TintEffect
	{
	public:
		CT_TintEffect() : hue(0), amt(0) {}
		ST_PositiveFixedAngle hue;
		ST_FixedPercentage amt;
	};

	class CT_TransformEffect
	{
	public:
		CT_TransformEffect() : sx(100000), sy(100000), kx(0), ky(0), tx(0L), ty(0L) {}
		ST_Percentage sx;
		ST_Percentage sy;
		ST_FixedAngle kx;
		ST_FixedAngle ky;
		ST_Coordinate tx;
		ST_Coordinate ty;
	};

	class ST_EffectContainerType
	{
		static String _literals[];
		String _value;
	public:
		enum value { sib, tree };

		static const String sib_literal;
		static const String tree_literal;

		ST_EffectContainerType() : _value(sib_literal) {}
		ST_EffectContainerType(value val) : _value(convert(val)) {}
		ST_EffectContainerType(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 2, 0); }
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

	class CT_EffectContainer
	{
	public:
		CT_EffectContainer() : type(ST_EffectContainerType::sib_literal) {}
		poptional< CT_EffectContainer > cont;
		poptional< CT_EffectReference > effect;
		poptional< CT_AlphaBiLevelEffect > alphaBiLevel;
		poptional< CT_AlphaCeilingEffect > alphaCeiling;
		poptional< CT_AlphaFloorEffect > alphaFloor;
		poptional< CT_AlphaInverseEffect > alphaInv;
		poptional< CT_AlphaModulateEffect > alphaMod;
		poptional< CT_AlphaModulateFixedEffect > alphaModFix;
		poptional< CT_AlphaOutsetEffect > alphaOutset;
		poptional< CT_AlphaReplaceEffect > alphaRepl;
		poptional< CT_BiLevelEffect > biLevel;
		poptional< CT_BlendEffect > blend;
		poptional< CT_BlurEffect > blur;
		poptional< CT_ColorChangeEffect > clrChange;
		poptional< CT_ColorReplaceEffect > clrRepl;
		poptional< CT_DuotoneEffect > duotone;
		poptional< CT_FillEffect > fill;
		poptional< CT_FillOverlayEffect > fillOverlay;
		poptional< CT_GlowEffect > glow;
		poptional< CT_GrayscaleEffect > grayscl;
		poptional< CT_HSLEffect > hsl;
		poptional< CT_InnerShadowEffect > innerShdw;
		poptional< CT_LuminanceEffect > lum;
		poptional< CT_OuterShadowEffect > outerShdw;
		poptional< CT_PresetShadowEffect > prstShdw;
		poptional< CT_ReflectionEffect > reflection;
		poptional< CT_RelativeOffsetEffect > relOff;
		poptional< CT_SoftEdgesEffect > softEdge;
		poptional< CT_TintEffect > tint;
		poptional< CT_TransformEffect > xfrm;
		ST_EffectContainerType type;
		optional< Token > name;
	};

	class CT_AlphaModulateEffect
	{
	public:
		CT_EffectContainer cont;
	};

	class ST_BlipCompression
	{
		static String _literals[];
		String _value;
	public:
		enum value { email, hqprint, none, print, screen };

		static const String email_literal;
		static const String hqprint_literal;
		static const String none_literal;
		static const String print_literal;
		static const String screen_literal;

		ST_BlipCompression() : _value(email_literal) {}
		ST_BlipCompression(value val) : _value(convert(val)) {}
		ST_BlipCompression(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 5, 0); }
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

	class CT_Blip
	{
	public:
		CT_Blip() : embed(""), link(""), cstate(ST_BlipCompression::none_literal) {}
		poptional< CT_AlphaBiLevelEffect > alphaBiLevel;
		poptional< CT_AlphaCeilingEffect > alphaCeiling;
		poptional< CT_AlphaFloorEffect > alphaFloor;
		poptional< CT_AlphaInverseEffect > alphaInv;
		poptional< CT_AlphaModulateEffect > alphaMod;
		poptional< CT_AlphaModulateFixedEffect > alphaModFix;
		poptional< CT_AlphaReplaceEffect > alphaRepl;
		poptional< CT_BiLevelEffect > biLevel;
		poptional< CT_BlurEffect > blur;
		poptional< CT_ColorChangeEffect > clrChange;
		poptional< CT_ColorReplaceEffect > clrRepl;
		poptional< CT_DuotoneEffect > duotone;
		poptional< CT_FillOverlayEffect > fillOverlay;
		poptional< CT_GrayscaleEffect > grayscl;
		poptional< CT_HSLEffect > hsl;
		poptional< CT_LuminanceEffect > lum;
		poptional< CT_TintEffect > tint;
		poptional< CT_OfficeArtExtensionList > extLst;
		::relationships::ST_RelationshipId embed;
		::relationships::ST_RelationshipId link;
		ST_BlipCompression cstate;
	};

	class CT_EffectList
	{
	public:
		poptional< CT_BlurEffect > blur;
		poptional< CT_FillOverlayEffect > fillOverlay;
		poptional< CT_GlowEffect > glow;
		poptional< CT_InnerShadowEffect > innerShdw;
		poptional< CT_OuterShadowEffect > outerShdw;
		poptional< CT_PresetShadowEffect > prstShdw;
		poptional< CT_ReflectionEffect > reflection;
		poptional< CT_SoftEdgesEffect > softEdge;
	};

	class dml_shapeEffects
	{
	public:
		poptional< CT_Blip > blip;
	};

	class CT_FillProperties
	{
	public:
		poptional< CT_NoFillProperties > noFill;
		poptional< CT_SolidColorFillProperties > solidFill;
		poptional< CT_GradientFillProperties > gradFill;
		poptional< CT_BlipFillProperties > blipFill;
		poptional< CT_PatternFillProperties > pattFill;
		poptional< CT_GroupFillProperties > grpFill;
	};

	class CT_EffectProperties
	{
	public:
		poptional< CT_EffectList > effectLst;
		poptional< CT_EffectContainer > effectDag;
	};

	class CT_BlendEffect
	{
	public:
		CT_EffectContainer cont;
		ST_BlendMode blend;
	};

}
#endif

