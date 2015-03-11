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

#ifndef DML_BASETYPES_HPP
#define DML_BASETYPES_HPP


#include "shared-relationshipReference.hpp"

namespace drawingml
{
	using namespace ::xio;
	using namespace ::xio::xml::schema;

	class CT_OfficeArtExtension;
	class CT_OfficeArtExtensionList;
	class ST_Percentage;
	class ST_Angle;
	class ST_PositiveFixedAngle;
	class CT_SphereCoords;
	class ST_PositivePercentage;
	class ST_Coordinate;
	class CT_Point3D;
	class CT_Vector3D;
	class ST_PositiveCoordinate;
	class ST_PositiveFixedPercentage;
	class CT_PositiveFixedPercentage;
	class CT_ComplementTransform;
	class CT_InverseTransform;
	class CT_GrayscaleTransform;
	class ST_FixedPercentage;
	class CT_FixedPercentage;
	class CT_PositivePercentage;
	class CT_PositiveFixedAngle;
	class CT_Angle;
	class CT_Percentage;
	class CT_GammaTransform;
	class CT_InverseGammaTransform;
	class CT_ScRgbColor;
	class ST_HexBinary3;
	class CT_SRgbColor;
	class CT_HslColor;
	class CT_SystemColor;
	class CT_SchemeColor;
	class CT_PresetColor;
	class CT_Color;
	class ST_Coordinate32;
	class ST_PositiveCoordinate32;
	class CT_RelativeRect;
	class ST_FixedAngle;
	class CT_EmbeddedWAVAudioFile;
	class CT_Hyperlink;
	class ST_Guid;
	class CT_Point2D;
	class CT_PositiveSize2D;
	class CT_Transform2D;
	class ST_DrawingElementId;
	class CT_GroupTransform2D;
	class CT_ColorMRU;
	class CT_Ratio;
	class CT_Scale2D;

	class CT_OfficeArtExtension
	{
	public:
		optional< Token > uri;
	};

	class CT_OfficeArtExtensionList
	{
	public:
		std::vector< CT_OfficeArtExtension > ext;
	};

	class ST_Percentage : public simple_type<Int>
	{
	public:
		ST_Percentage() {}
		ST_Percentage(const Int& v) : simple_type<Int>(v) {}
		ST_Percentage(const String& v) { read(v); }
	};

	class ST_Angle : public simple_type<Int>
	{
	public:
		ST_Angle() {}
		ST_Angle(const Int& v) : simple_type<Int>(v) {}
		ST_Angle(const String& v) { read(v); }
	};

	class ST_PositiveFixedAngle : public ST_Angle
	{
	public:
		ST_PositiveFixedAngle() {}
		ST_PositiveFixedAngle(const Int& v) : ST_Angle(v) {}
		ST_PositiveFixedAngle(const String& v) { read(v); }
	};

	class CT_SphereCoords
	{
	public:
		ST_PositiveFixedAngle lat;
		ST_PositiveFixedAngle lon;
		ST_PositiveFixedAngle rev;
	};

	class ST_PositivePercentage : public ST_Percentage
	{
	public:
		ST_PositivePercentage() {}
		ST_PositivePercentage(const Int& v) : ST_Percentage(v) {}
		ST_PositivePercentage(const String& v) { read(v); }
	};

	class ST_Coordinate : public simple_type<Long>
	{
	public:
		ST_Coordinate() {}
		ST_Coordinate(const Long& v) : simple_type<Long>(v) {}
		ST_Coordinate(const String& v) { read(v); }
	};

	class CT_Point3D
	{
	public:
		ST_Coordinate x;
		ST_Coordinate y;
		ST_Coordinate z;
	};

	class CT_Vector3D
	{
	public:
		ST_Coordinate dx;
		ST_Coordinate dy;
		ST_Coordinate dz;
	};

	class ST_PositiveCoordinate : public simple_type<Long>
	{
	public:
		ST_PositiveCoordinate() {}
		ST_PositiveCoordinate(const Long& v) : simple_type<Long>(v) {}
		ST_PositiveCoordinate(const String& v) { read(v); }
	};

	class ST_PositiveFixedPercentage : public ST_Percentage
	{
	public:
		ST_PositiveFixedPercentage() {}
		ST_PositiveFixedPercentage(const Int& v) : ST_Percentage(v) {}
		ST_PositiveFixedPercentage(const String& v) { read(v); }
	};

	class CT_PositiveFixedPercentage
	{
	public:
		ST_PositiveFixedPercentage val;
	};

	class CT_ComplementTransform
	{
	public:
	};

	class CT_InverseTransform
	{
	public:
	};

	class CT_GrayscaleTransform
	{
	public:
	};

	class ST_FixedPercentage : public ST_Percentage
	{
	public:
		ST_FixedPercentage() {}
		ST_FixedPercentage(const Int& v) : ST_Percentage(v) {}
		ST_FixedPercentage(const String& v) { read(v); }
	};

	class CT_FixedPercentage
	{
	public:
		ST_FixedPercentage val;
	};

	class CT_PositivePercentage
	{
	public:
		ST_PositivePercentage val;
	};

	class CT_PositiveFixedAngle
	{
	public:
		ST_PositiveFixedAngle val;
	};

	class CT_Angle
	{
	public:
		ST_Angle val;
	};

	class CT_Percentage
	{
	public:
		ST_Percentage val;
	};

	class CT_GammaTransform
	{
	public:
	};

	class CT_InverseGammaTransform
	{
	public:
	};

	class CT_ScRgbColor
	{
	public:
		poptional< CT_PositiveFixedPercentage > tint;
		poptional< CT_PositiveFixedPercentage > shade;
		poptional< CT_ComplementTransform > comp;
		poptional< CT_InverseTransform > inv;
		poptional< CT_GrayscaleTransform > gray;
		poptional< CT_PositiveFixedPercentage > alpha;
		poptional< CT_FixedPercentage > alphaOff;
		poptional< CT_PositivePercentage > alphaMod;
		poptional< CT_PositiveFixedAngle > hue;
		poptional< CT_Angle > hueOff;
		poptional< CT_PositivePercentage > hueMod;
		poptional< CT_Percentage > sat;
		poptional< CT_Percentage > satOff;
		poptional< CT_Percentage > satMod;
		poptional< CT_Percentage > lum;
		poptional< CT_Percentage > lumOff;
		poptional< CT_Percentage > lumMod;
		poptional< CT_Percentage > red;
		poptional< CT_Percentage > redOff;
		poptional< CT_Percentage > redMod;
		poptional< CT_Percentage > green;
		poptional< CT_Percentage > greenOff;
		poptional< CT_Percentage > greenMod;
		poptional< CT_Percentage > blue;
		poptional< CT_Percentage > blueOff;
		poptional< CT_Percentage > blueMod;
		poptional< CT_GammaTransform > gamma;
		poptional< CT_InverseGammaTransform > invGamma;
		ST_Percentage r;
		ST_Percentage g;
		ST_Percentage b;
	};

	class ST_HexBinary3 : public simple_type<HexBinary>
	{
	public:
		ST_HexBinary3() {}
		ST_HexBinary3(const HexBinary& v) : simple_type<HexBinary>(v) {}
		ST_HexBinary3(const String& v) { read(v); }
	};

	class CT_SRgbColor
	{
	public:
		poptional< CT_PositiveFixedPercentage > tint;
		poptional< CT_PositiveFixedPercentage > shade;
		poptional< CT_ComplementTransform > comp;
		poptional< CT_InverseTransform > inv;
		poptional< CT_GrayscaleTransform > gray;
		poptional< CT_PositiveFixedPercentage > alpha;
		poptional< CT_FixedPercentage > alphaOff;
		poptional< CT_PositivePercentage > alphaMod;
		poptional< CT_PositiveFixedAngle > hue;
		poptional< CT_Angle > hueOff;
		poptional< CT_PositivePercentage > hueMod;
		poptional< CT_Percentage > sat;
		poptional< CT_Percentage > satOff;
		poptional< CT_Percentage > satMod;
		poptional< CT_Percentage > lum;
		poptional< CT_Percentage > lumOff;
		poptional< CT_Percentage > lumMod;
		poptional< CT_Percentage > red;
		poptional< CT_Percentage > redOff;
		poptional< CT_Percentage > redMod;
		poptional< CT_Percentage > green;
		poptional< CT_Percentage > greenOff;
		poptional< CT_Percentage > greenMod;
		poptional< CT_Percentage > blue;
		poptional< CT_Percentage > blueOff;
		poptional< CT_Percentage > blueMod;
		poptional< CT_GammaTransform > gamma;
		poptional< CT_InverseGammaTransform > invGamma;
		ST_HexBinary3 val;
	};

	class CT_HslColor
	{
	public:
		poptional< CT_PositiveFixedPercentage > tint;
		poptional< CT_PositiveFixedPercentage > shade;
		poptional< CT_ComplementTransform > comp;
		poptional< CT_InverseTransform > inv;
		poptional< CT_GrayscaleTransform > gray;
		poptional< CT_PositiveFixedPercentage > alpha;
		poptional< CT_FixedPercentage > alphaOff;
		poptional< CT_PositivePercentage > alphaMod;
		poptional< CT_PositiveFixedAngle > hue;
		poptional< CT_Angle > hueOff;
		poptional< CT_PositivePercentage > hueMod;
		poptional< CT_Percentage > sat;
		poptional< CT_Percentage > satOff;
		poptional< CT_Percentage > satMod;
		poptional< CT_Percentage > lum;
		poptional< CT_Percentage > lumOff;
		poptional< CT_Percentage > lumMod;
		poptional< CT_Percentage > red;
		poptional< CT_Percentage > redOff;
		poptional< CT_Percentage > redMod;
		poptional< CT_Percentage > green;
		poptional< CT_Percentage > greenOff;
		poptional< CT_Percentage > greenMod;
		poptional< CT_Percentage > blue;
		poptional< CT_Percentage > blueOff;
		poptional< CT_Percentage > blueMod;
		poptional< CT_GammaTransform > gamma;
		poptional< CT_InverseGammaTransform > invGamma;
		ST_PositiveFixedAngle hue_attr;
		ST_Percentage sat_attr;
		ST_Percentage lum_attr;
	};

	class ST_SystemColorVal
	{
		static String _literals[];
		String _value;
	public:
		enum value { _3dDkShadow_, _3dLight_, activeBorder, activeCaption, appWorkspace, background, btnFace, btnHighlight, btnShadow, btnText, captionText, gradientActiveCaption, gradientInactiveCaption, grayText, highlight, highlightText, hotLight, inactiveBorder, inactiveCaption, inactiveCaptionText, infoBk, infoText, menu, menuBar, menuHighlight, menuText, scrollBar, window, windowFrame, windowText };

		static const String _3dDkShadow__literal;
		static const String _3dLight__literal;
		static const String activeBorder_literal;
		static const String activeCaption_literal;
		static const String appWorkspace_literal;
		static const String background_literal;
		static const String btnFace_literal;
		static const String btnHighlight_literal;
		static const String btnShadow_literal;
		static const String btnText_literal;
		static const String captionText_literal;
		static const String gradientActiveCaption_literal;
		static const String gradientInactiveCaption_literal;
		static const String grayText_literal;
		static const String highlight_literal;
		static const String highlightText_literal;
		static const String hotLight_literal;
		static const String inactiveBorder_literal;
		static const String inactiveCaption_literal;
		static const String inactiveCaptionText_literal;
		static const String infoBk_literal;
		static const String infoText_literal;
		static const String menu_literal;
		static const String menuBar_literal;
		static const String menuHighlight_literal;
		static const String menuText_literal;
		static const String scrollBar_literal;
		static const String window_literal;
		static const String windowFrame_literal;
		static const String windowText_literal;

		ST_SystemColorVal() : _value(scrollBar_literal) {}
		ST_SystemColorVal(value val) : _value(convert(val)) {}
		ST_SystemColorVal(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 30, 0); }
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

	class CT_SystemColor
	{
	public:
		poptional< CT_PositiveFixedPercentage > tint;
		poptional< CT_PositiveFixedPercentage > shade;
		poptional< CT_ComplementTransform > comp;
		poptional< CT_InverseTransform > inv;
		poptional< CT_GrayscaleTransform > gray;
		poptional< CT_PositiveFixedPercentage > alpha;
		poptional< CT_FixedPercentage > alphaOff;
		poptional< CT_PositivePercentage > alphaMod;
		poptional< CT_PositiveFixedAngle > hue;
		poptional< CT_Angle > hueOff;
		poptional< CT_PositivePercentage > hueMod;
		poptional< CT_Percentage > sat;
		poptional< CT_Percentage > satOff;
		poptional< CT_Percentage > satMod;
		poptional< CT_Percentage > lum;
		poptional< CT_Percentage > lumOff;
		poptional< CT_Percentage > lumMod;
		poptional< CT_Percentage > red;
		poptional< CT_Percentage > redOff;
		poptional< CT_Percentage > redMod;
		poptional< CT_Percentage > green;
		poptional< CT_Percentage > greenOff;
		poptional< CT_Percentage > greenMod;
		poptional< CT_Percentage > blue;
		poptional< CT_Percentage > blueOff;
		poptional< CT_Percentage > blueMod;
		poptional< CT_GammaTransform > gamma;
		poptional< CT_InverseGammaTransform > invGamma;
		ST_SystemColorVal val;
		poptional< ST_HexBinary3 > lastClr;
	};

	class ST_SchemeColorVal
	{
		static String _literals[];
		String _value;
	public:
		enum value { accent1, accent2, accent3, accent4, accent5, accent6, bg1, bg2, dk1, dk2, folHlink, hlink, lt1, lt2, phClr, tx1, tx2 };

		static const String accent1_literal;
		static const String accent2_literal;
		static const String accent3_literal;
		static const String accent4_literal;
		static const String accent5_literal;
		static const String accent6_literal;
		static const String bg1_literal;
		static const String bg2_literal;
		static const String dk1_literal;
		static const String dk2_literal;
		static const String folHlink_literal;
		static const String hlink_literal;
		static const String lt1_literal;
		static const String lt2_literal;
		static const String phClr_literal;
		static const String tx1_literal;
		static const String tx2_literal;

		ST_SchemeColorVal() : _value(bg1_literal) {}
		ST_SchemeColorVal(value val) : _value(convert(val)) {}
		ST_SchemeColorVal(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 17, 0); }
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

	class CT_SchemeColor
	{
	public:
		poptional< CT_PositiveFixedPercentage > tint;
		poptional< CT_PositiveFixedPercentage > shade;
		poptional< CT_ComplementTransform > comp;
		poptional< CT_InverseTransform > inv;
		poptional< CT_GrayscaleTransform > gray;
		poptional< CT_PositiveFixedPercentage > alpha;
		poptional< CT_FixedPercentage > alphaOff;
		poptional< CT_PositivePercentage > alphaMod;
		poptional< CT_PositiveFixedAngle > hue;
		poptional< CT_Angle > hueOff;
		poptional< CT_PositivePercentage > hueMod;
		poptional< CT_Percentage > sat;
		poptional< CT_Percentage > satOff;
		poptional< CT_Percentage > satMod;
		poptional< CT_Percentage > lum;
		poptional< CT_Percentage > lumOff;
		poptional< CT_Percentage > lumMod;
		poptional< CT_Percentage > red;
		poptional< CT_Percentage > redOff;
		poptional< CT_Percentage > redMod;
		poptional< CT_Percentage > green;
		poptional< CT_Percentage > greenOff;
		poptional< CT_Percentage > greenMod;
		poptional< CT_Percentage > blue;
		poptional< CT_Percentage > blueOff;
		poptional< CT_Percentage > blueMod;
		poptional< CT_GammaTransform > gamma;
		poptional< CT_InverseGammaTransform > invGamma;
		ST_SchemeColorVal val;
	};

	class ST_PresetColorVal
	{
		static String _literals[];
		String _value;
	public:
		enum value { aliceBlue, antiqueWhite, aqua, aquamarine, azure, beige, bisque, black, blanchedAlmond, blue, blueViolet, brown, burlyWood, cadetBlue, chartreuse, chocolate, coral, cornflowerBlue, cornsilk, crimson, cyan, deepPink, deepSkyBlue, dimGray, dkBlue, dkCyan, dkGoldenrod, dkGray, dkGreen, dkKhaki, dkMagenta, dkOliveGreen, dkOrange, dkOrchid, dkRed, dkSalmon, dkSeaGreen, dkSlateBlue, dkSlateGray, dkTurquoise, dkViolet, dodgerBlue, firebrick, floralWhite, forestGreen, fuchsia, gainsboro, ghostWhite, gold, goldenrod, gray, green, greenYellow, honeydew, hotPink, indianRed, indigo, ivory, khaki, lavender, lavenderBlush, lawnGreen, lemonChiffon, lime, limeGreen, linen, ltBlue, ltCoral, ltCyan, ltGoldenrodYellow, ltGray, ltGreen, ltPink, ltSalmon, ltSeaGreen, ltSkyBlue, ltSlateGray, ltSteelBlue, ltYellow, magenta, maroon, medAquamarine, medBlue, medOrchid, medPurple, medSeaGreen, medSlateBlue, medSpringGreen, medTurquoise, medVioletRed, midnightBlue, mintCream, mistyRose, moccasin, navajoWhite, navy, oldLace, olive, oliveDrab, orange, orangeRed, orchid, paleGoldenrod, paleGreen, paleTurquoise, paleVioletRed, papayaWhip, peachPuff, peru, pink, plum, powderBlue, purple, red, rosyBrown, royalBlue, saddleBrown, salmon, sandyBrown, seaGreen, seaShell, sienna, silver, skyBlue, slateBlue, slateGray, snow, springGreen, steelBlue, tan, teal, thistle, tomato, turquoise, violet, wheat, white, whiteSmoke, yellow, yellowGreen };

		static const String aliceBlue_literal;
		static const String antiqueWhite_literal;
		static const String aqua_literal;
		static const String aquamarine_literal;
		static const String azure_literal;
		static const String beige_literal;
		static const String bisque_literal;
		static const String black_literal;
		static const String blanchedAlmond_literal;
		static const String blue_literal;
		static const String blueViolet_literal;
		static const String brown_literal;
		static const String burlyWood_literal;
		static const String cadetBlue_literal;
		static const String chartreuse_literal;
		static const String chocolate_literal;
		static const String coral_literal;
		static const String cornflowerBlue_literal;
		static const String cornsilk_literal;
		static const String crimson_literal;
		static const String cyan_literal;
		static const String deepPink_literal;
		static const String deepSkyBlue_literal;
		static const String dimGray_literal;
		static const String dkBlue_literal;
		static const String dkCyan_literal;
		static const String dkGoldenrod_literal;
		static const String dkGray_literal;
		static const String dkGreen_literal;
		static const String dkKhaki_literal;
		static const String dkMagenta_literal;
		static const String dkOliveGreen_literal;
		static const String dkOrange_literal;
		static const String dkOrchid_literal;
		static const String dkRed_literal;
		static const String dkSalmon_literal;
		static const String dkSeaGreen_literal;
		static const String dkSlateBlue_literal;
		static const String dkSlateGray_literal;
		static const String dkTurquoise_literal;
		static const String dkViolet_literal;
		static const String dodgerBlue_literal;
		static const String firebrick_literal;
		static const String floralWhite_literal;
		static const String forestGreen_literal;
		static const String fuchsia_literal;
		static const String gainsboro_literal;
		static const String ghostWhite_literal;
		static const String gold_literal;
		static const String goldenrod_literal;
		static const String gray_literal;
		static const String green_literal;
		static const String greenYellow_literal;
		static const String honeydew_literal;
		static const String hotPink_literal;
		static const String indianRed_literal;
		static const String indigo_literal;
		static const String ivory_literal;
		static const String khaki_literal;
		static const String lavender_literal;
		static const String lavenderBlush_literal;
		static const String lawnGreen_literal;
		static const String lemonChiffon_literal;
		static const String lime_literal;
		static const String limeGreen_literal;
		static const String linen_literal;
		static const String ltBlue_literal;
		static const String ltCoral_literal;
		static const String ltCyan_literal;
		static const String ltGoldenrodYellow_literal;
		static const String ltGray_literal;
		static const String ltGreen_literal;
		static const String ltPink_literal;
		static const String ltSalmon_literal;
		static const String ltSeaGreen_literal;
		static const String ltSkyBlue_literal;
		static const String ltSlateGray_literal;
		static const String ltSteelBlue_literal;
		static const String ltYellow_literal;
		static const String magenta_literal;
		static const String maroon_literal;
		static const String medAquamarine_literal;
		static const String medBlue_literal;
		static const String medOrchid_literal;
		static const String medPurple_literal;
		static const String medSeaGreen_literal;
		static const String medSlateBlue_literal;
		static const String medSpringGreen_literal;
		static const String medTurquoise_literal;
		static const String medVioletRed_literal;
		static const String midnightBlue_literal;
		static const String mintCream_literal;
		static const String mistyRose_literal;
		static const String moccasin_literal;
		static const String navajoWhite_literal;
		static const String navy_literal;
		static const String oldLace_literal;
		static const String olive_literal;
		static const String oliveDrab_literal;
		static const String orange_literal;
		static const String orangeRed_literal;
		static const String orchid_literal;
		static const String paleGoldenrod_literal;
		static const String paleGreen_literal;
		static const String paleTurquoise_literal;
		static const String paleVioletRed_literal;
		static const String papayaWhip_literal;
		static const String peachPuff_literal;
		static const String peru_literal;
		static const String pink_literal;
		static const String plum_literal;
		static const String powderBlue_literal;
		static const String purple_literal;
		static const String red_literal;
		static const String rosyBrown_literal;
		static const String royalBlue_literal;
		static const String saddleBrown_literal;
		static const String salmon_literal;
		static const String sandyBrown_literal;
		static const String seaGreen_literal;
		static const String seaShell_literal;
		static const String sienna_literal;
		static const String silver_literal;
		static const String skyBlue_literal;
		static const String slateBlue_literal;
		static const String slateGray_literal;
		static const String snow_literal;
		static const String springGreen_literal;
		static const String steelBlue_literal;
		static const String tan_literal;
		static const String teal_literal;
		static const String thistle_literal;
		static const String tomato_literal;
		static const String turquoise_literal;
		static const String violet_literal;
		static const String wheat_literal;
		static const String white_literal;
		static const String whiteSmoke_literal;
		static const String yellow_literal;
		static const String yellowGreen_literal;

		ST_PresetColorVal() : _value(aliceBlue_literal) {}
		ST_PresetColorVal(value val) : _value(convert(val)) {}
		ST_PresetColorVal(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 140, 0); }
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

	class CT_PresetColor
	{
	public:
		poptional< CT_PositiveFixedPercentage > tint;
		poptional< CT_PositiveFixedPercentage > shade;
		poptional< CT_ComplementTransform > comp;
		poptional< CT_InverseTransform > inv;
		poptional< CT_GrayscaleTransform > gray;
		poptional< CT_PositiveFixedPercentage > alpha;
		poptional< CT_FixedPercentage > alphaOff;
		poptional< CT_PositivePercentage > alphaMod;
		poptional< CT_PositiveFixedAngle > hue;
		poptional< CT_Angle > hueOff;
		poptional< CT_PositivePercentage > hueMod;
		poptional< CT_Percentage > sat;
		poptional< CT_Percentage > satOff;
		poptional< CT_Percentage > satMod;
		poptional< CT_Percentage > lum;
		poptional< CT_Percentage > lumOff;
		poptional< CT_Percentage > lumMod;
		poptional< CT_Percentage > red;
		poptional< CT_Percentage > redOff;
		poptional< CT_Percentage > redMod;
		poptional< CT_Percentage > green;
		poptional< CT_Percentage > greenOff;
		poptional< CT_Percentage > greenMod;
		poptional< CT_Percentage > blue;
		poptional< CT_Percentage > blueOff;
		poptional< CT_Percentage > blueMod;
		poptional< CT_GammaTransform > gamma;
		poptional< CT_InverseGammaTransform > invGamma;
		optional< ST_PresetColorVal > val;
	};

	class CT_Color
	{
	public:
		poptional< CT_ScRgbColor > scrgbClr;
		poptional< CT_SRgbColor > srgbClr;
		poptional< CT_HslColor > hslClr;
		poptional< CT_SystemColor > sysClr;
		poptional< CT_SchemeColor > schemeClr;
		poptional< CT_PresetColor > prstClr;
	};

	class ST_Coordinate32 : public simple_type<Int>
	{
	public:
		ST_Coordinate32() {}
		ST_Coordinate32(const Int& v) : simple_type<Int>(v) {}
		ST_Coordinate32(const String& v) { read(v); }
	};

	class ST_PositiveCoordinate32 : public ST_Coordinate32
	{
	public:
		ST_PositiveCoordinate32() {}
		ST_PositiveCoordinate32(const Int& v) : ST_Coordinate32(v) {}
		ST_PositiveCoordinate32(const String& v) { read(v); }
	};

	class CT_RelativeRect
	{
	public:
		CT_RelativeRect() : l(0), t(0), r(0), b(0) {}
		ST_Percentage l;
		ST_Percentage t;
		ST_Percentage r;
		ST_Percentage b;
	};

	class ST_RectAlignment
	{
		static String _literals[];
		String _value;
	public:
		enum value { b, bl, br, ctr, l, r, t, tl, tr };

		static const String b_literal;
		static const String bl_literal;
		static const String br_literal;
		static const String ctr_literal;
		static const String l_literal;
		static const String r_literal;
		static const String t_literal;
		static const String tl_literal;
		static const String tr_literal;

		ST_RectAlignment() : _value(tl_literal) {}
		ST_RectAlignment(value val) : _value(convert(val)) {}
		ST_RectAlignment(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 9, 0); }
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

	class ST_FixedAngle : public ST_Angle
	{
	public:
		ST_FixedAngle() {}
		ST_FixedAngle(const Int& v) : ST_Angle(v) {}
		ST_FixedAngle(const String& v) { read(v); }
	};

	class CT_EmbeddedWAVAudioFile
	{
	public:
		CT_EmbeddedWAVAudioFile() : name(""), builtIn(false) {}
		::relationships::ST_RelationshipId embed;
		String name;
		Boolean builtIn;
	};

	class CT_Hyperlink
	{
	public:
		CT_Hyperlink() : invalidUrl(""), action(""), tgtFrame(""), tooltip(""), history(true), highlightClick(false), endSnd(false) {}
		poptional< CT_EmbeddedWAVAudioFile > snd;
		poptional< CT_OfficeArtExtensionList > extLst;
		poptional< ::relationships::ST_RelationshipId > id;
		String invalidUrl;
		String action;
		String tgtFrame;
		String tooltip;
		Boolean history;
		Boolean highlightClick;
		Boolean endSnd;
	};

	class ST_Guid : public simple_type<Token>
	{
	public:
		ST_Guid() {}
		ST_Guid(const Token& v) : simple_type<Token>(v) {}
	};

	class CT_Point2D
	{
	public:
		ST_Coordinate x;
		ST_Coordinate y;
	};

	class CT_PositiveSize2D
	{
	public:
		ST_PositiveCoordinate cx;
		ST_PositiveCoordinate cy;
	};

	class CT_Transform2D
	{
	public:
		CT_Transform2D() : rot(0), flipH(false), flipV(false) {}
		poptional< CT_Point2D > off;
		poptional< CT_PositiveSize2D > ext;
		ST_Angle rot;
		Boolean flipH;
		Boolean flipV;
	};

	class ST_BlackWhiteMode
	{
		static String _literals[];
		String _value;
	public:
		enum value { _auto_, black, blackGray, blackWhite, clr, gray, grayWhite, hidden, invGray, ltGray, white };

		static const String _auto__literal;
		static const String black_literal;
		static const String blackGray_literal;
		static const String blackWhite_literal;
		static const String clr_literal;
		static const String gray_literal;
		static const String grayWhite_literal;
		static const String hidden_literal;
		static const String invGray_literal;
		static const String ltGray_literal;
		static const String white_literal;

		ST_BlackWhiteMode() : _value(clr_literal) {}
		ST_BlackWhiteMode(value val) : _value(convert(val)) {}
		ST_BlackWhiteMode(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 11, 0); }
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

	class ST_DrawingElementId : public simple_type<UnsignedInt>
	{
	public:
		ST_DrawingElementId() {}
		ST_DrawingElementId(const UnsignedInt& v) : simple_type<UnsignedInt>(v) {}
		ST_DrawingElementId(const String& v) { read(v); }
	};

	class CT_GroupTransform2D
	{
	public:
		CT_GroupTransform2D() : rot(0), flipH(false), flipV(false) {}
		poptional< CT_Point2D > off;
		poptional< CT_PositiveSize2D > ext;
		poptional< CT_Point2D > chOff;
		poptional< CT_PositiveSize2D > chExt;
		ST_Angle rot;
		Boolean flipH;
		Boolean flipV;
	};

	class CT_ColorMRU
	{
	public:
		poptional< CT_ScRgbColor > scrgbClr;
		poptional< CT_SRgbColor > srgbClr;
		poptional< CT_HslColor > hslClr;
		poptional< CT_SystemColor > sysClr;
		poptional< CT_SchemeColor > schemeClr;
		poptional< CT_PresetColor > prstClr;
	};

	class CT_Ratio
	{
	public:
		Long n;
		Long d;
	};

	class CT_Scale2D
	{
	public:
		CT_Ratio sx;
		CT_Ratio sy;
	};

}
#endif

