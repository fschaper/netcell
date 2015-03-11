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

#ifndef DML_BASETYPES_WRITERS_HPP
#define DML_BASETYPES_WRITERS_HPP

#include "dml-baseTypes.hpp"
#include "dml-baseTypes_literals.hpp"
#include "shared-relationshipReference_writers.hpp"

namespace drawingml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_OfficeArtExtension_writer;
		class CT_OfficeArtExtensionList_writer;
		class ST_Percentage_writer;
		class ST_Angle_writer;
		class ST_PositiveFixedAngle_writer;
		class CT_SphereCoords_writer;
		class ST_PositivePercentage_writer;
		class ST_Coordinate_writer;
		class CT_Point3D_writer;
		class CT_Vector3D_writer;
		class ST_PositiveCoordinate_writer;
		class ST_PositiveFixedPercentage_writer;
		class CT_PositiveFixedPercentage_writer;
		class CT_ComplementTransform_writer;
		class CT_InverseTransform_writer;
		class CT_GrayscaleTransform_writer;
		class ST_FixedPercentage_writer;
		class CT_FixedPercentage_writer;
		class CT_PositivePercentage_writer;
		class CT_PositiveFixedAngle_writer;
		class CT_Angle_writer;
		class CT_Percentage_writer;
		class CT_GammaTransform_writer;
		class CT_InverseGammaTransform_writer;
		class CT_ScRgbColor_writer;
		class ST_HexBinary3_writer;
		class CT_SRgbColor_writer;
		class CT_HslColor_writer;
		class CT_SystemColor_writer;
		class CT_SchemeColor_writer;
		class CT_PresetColor_writer;
		class CT_Color_writer;
		class ST_Coordinate32_writer;
		class ST_PositiveCoordinate32_writer;
		class CT_RelativeRect_writer;
		class ST_FixedAngle_writer;
		class CT_EmbeddedWAVAudioFile_writer;
		class CT_Hyperlink_writer;
		class ST_Guid_writer;
		class CT_Point2D_writer;
		class CT_PositiveSize2D_writer;
		class CT_Transform2D_writer;
		class ST_DrawingElementId_writer;
		class CT_GroupTransform2D_writer;
		class CT_ColorMRU_writer;
		class CT_Ratio_writer;
		class CT_Scale2D_writer;

		class CT_OfficeArtExtension_writer : public type_writer
		{
			CT_OfficeArtExtension* t() { return static_cast<CT_OfficeArtExtension*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_OfficeArtExtensionList_writer : public type_writer
		{
			auto_type_writer< CT_OfficeArtExtension_writer > _ext_writer;
			CT_OfficeArtExtensionList* t() { return static_cast<CT_OfficeArtExtensionList*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class ST_Percentage_writer : public type_writer
		{
			ST_Percentage* t() { return static_cast<ST_Percentage*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class ST_Angle_writer : public type_writer
		{
			ST_Angle* t() { return static_cast<ST_Angle*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class ST_PositiveFixedAngle_writer : public ST_Angle_writer
		{
			ST_PositiveFixedAngle* t() { return static_cast<ST_PositiveFixedAngle*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_SphereCoords_writer : public type_writer
		{
			CT_SphereCoords* t() { return static_cast<CT_SphereCoords*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class ST_PositivePercentage_writer : public ST_Percentage_writer
		{
			ST_PositivePercentage* t() { return static_cast<ST_PositivePercentage*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class ST_Coordinate_writer : public type_writer
		{
			ST_Coordinate* t() { return static_cast<ST_Coordinate*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Point3D_writer : public type_writer
		{
			CT_Point3D* t() { return static_cast<CT_Point3D*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Vector3D_writer : public type_writer
		{
			CT_Vector3D* t() { return static_cast<CT_Vector3D*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class ST_PositiveCoordinate_writer : public type_writer
		{
			ST_PositiveCoordinate* t() { return static_cast<ST_PositiveCoordinate*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class ST_PositiveFixedPercentage_writer : public ST_Percentage_writer
		{
			ST_PositiveFixedPercentage* t() { return static_cast<ST_PositiveFixedPercentage*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_PositiveFixedPercentage_writer : public type_writer
		{
			CT_PositiveFixedPercentage* t() { return static_cast<CT_PositiveFixedPercentage*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_ComplementTransform_writer : public type_writer
		{
			CT_ComplementTransform* t() { return static_cast<CT_ComplementTransform*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_InverseTransform_writer : public type_writer
		{
			CT_InverseTransform* t() { return static_cast<CT_InverseTransform*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_GrayscaleTransform_writer : public type_writer
		{
			CT_GrayscaleTransform* t() { return static_cast<CT_GrayscaleTransform*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class ST_FixedPercentage_writer : public ST_Percentage_writer
		{
			ST_FixedPercentage* t() { return static_cast<ST_FixedPercentage*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_FixedPercentage_writer : public type_writer
		{
			CT_FixedPercentage* t() { return static_cast<CT_FixedPercentage*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_PositivePercentage_writer : public type_writer
		{
			CT_PositivePercentage* t() { return static_cast<CT_PositivePercentage*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_PositiveFixedAngle_writer : public type_writer
		{
			CT_PositiveFixedAngle* t() { return static_cast<CT_PositiveFixedAngle*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Angle_writer : public type_writer
		{
			CT_Angle* t() { return static_cast<CT_Angle*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Percentage_writer : public type_writer
		{
			CT_Percentage* t() { return static_cast<CT_Percentage*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_GammaTransform_writer : public type_writer
		{
			CT_GammaTransform* t() { return static_cast<CT_GammaTransform*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_InverseGammaTransform_writer : public type_writer
		{
			CT_InverseGammaTransform* t() { return static_cast<CT_InverseGammaTransform*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_ScRgbColor_writer : public type_writer
		{
			auto_type_writer< CT_PositiveFixedPercentage_writer > _tint_writer;
			auto_type_writer< CT_PositiveFixedPercentage_writer > _shade_writer;
			auto_type_writer< CT_ComplementTransform_writer > _comp_writer;
			auto_type_writer< CT_InverseTransform_writer > _inv_writer;
			auto_type_writer< CT_GrayscaleTransform_writer > _gray_writer;
			auto_type_writer< CT_PositiveFixedPercentage_writer > _alpha_writer;
			auto_type_writer< CT_FixedPercentage_writer > _alphaOff_writer;
			auto_type_writer< CT_PositivePercentage_writer > _alphaMod_writer;
			auto_type_writer< CT_PositiveFixedAngle_writer > _hue_writer;
			auto_type_writer< CT_Angle_writer > _hueOff_writer;
			auto_type_writer< CT_PositivePercentage_writer > _hueMod_writer;
			auto_type_writer< CT_Percentage_writer > _sat_writer;
			auto_type_writer< CT_Percentage_writer > _satOff_writer;
			auto_type_writer< CT_Percentage_writer > _satMod_writer;
			auto_type_writer< CT_Percentage_writer > _lum_writer;
			auto_type_writer< CT_Percentage_writer > _lumOff_writer;
			auto_type_writer< CT_Percentage_writer > _lumMod_writer;
			auto_type_writer< CT_Percentage_writer > _red_writer;
			auto_type_writer< CT_Percentage_writer > _redOff_writer;
			auto_type_writer< CT_Percentage_writer > _redMod_writer;
			auto_type_writer< CT_Percentage_writer > _green_writer;
			auto_type_writer< CT_Percentage_writer > _greenOff_writer;
			auto_type_writer< CT_Percentage_writer > _greenMod_writer;
			auto_type_writer< CT_Percentage_writer > _blue_writer;
			auto_type_writer< CT_Percentage_writer > _blueOff_writer;
			auto_type_writer< CT_Percentage_writer > _blueMod_writer;
			auto_type_writer< CT_GammaTransform_writer > _gamma_writer;
			auto_type_writer< CT_InverseGammaTransform_writer > _invGamma_writer;
			CT_ScRgbColor* t() { return static_cast<CT_ScRgbColor*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class ST_HexBinary3_writer : public type_writer
		{
			ST_HexBinary3* t() { return static_cast<ST_HexBinary3*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_SRgbColor_writer : public type_writer
		{
			auto_type_writer< CT_PositiveFixedPercentage_writer > _tint_writer;
			auto_type_writer< CT_PositiveFixedPercentage_writer > _shade_writer;
			auto_type_writer< CT_ComplementTransform_writer > _comp_writer;
			auto_type_writer< CT_InverseTransform_writer > _inv_writer;
			auto_type_writer< CT_GrayscaleTransform_writer > _gray_writer;
			auto_type_writer< CT_PositiveFixedPercentage_writer > _alpha_writer;
			auto_type_writer< CT_FixedPercentage_writer > _alphaOff_writer;
			auto_type_writer< CT_PositivePercentage_writer > _alphaMod_writer;
			auto_type_writer< CT_PositiveFixedAngle_writer > _hue_writer;
			auto_type_writer< CT_Angle_writer > _hueOff_writer;
			auto_type_writer< CT_PositivePercentage_writer > _hueMod_writer;
			auto_type_writer< CT_Percentage_writer > _sat_writer;
			auto_type_writer< CT_Percentage_writer > _satOff_writer;
			auto_type_writer< CT_Percentage_writer > _satMod_writer;
			auto_type_writer< CT_Percentage_writer > _lum_writer;
			auto_type_writer< CT_Percentage_writer > _lumOff_writer;
			auto_type_writer< CT_Percentage_writer > _lumMod_writer;
			auto_type_writer< CT_Percentage_writer > _red_writer;
			auto_type_writer< CT_Percentage_writer > _redOff_writer;
			auto_type_writer< CT_Percentage_writer > _redMod_writer;
			auto_type_writer< CT_Percentage_writer > _green_writer;
			auto_type_writer< CT_Percentage_writer > _greenOff_writer;
			auto_type_writer< CT_Percentage_writer > _greenMod_writer;
			auto_type_writer< CT_Percentage_writer > _blue_writer;
			auto_type_writer< CT_Percentage_writer > _blueOff_writer;
			auto_type_writer< CT_Percentage_writer > _blueMod_writer;
			auto_type_writer< CT_GammaTransform_writer > _gamma_writer;
			auto_type_writer< CT_InverseGammaTransform_writer > _invGamma_writer;
			CT_SRgbColor* t() { return static_cast<CT_SRgbColor*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_HslColor_writer : public type_writer
		{
			auto_type_writer< CT_PositiveFixedPercentage_writer > _tint_writer;
			auto_type_writer< CT_PositiveFixedPercentage_writer > _shade_writer;
			auto_type_writer< CT_ComplementTransform_writer > _comp_writer;
			auto_type_writer< CT_InverseTransform_writer > _inv_writer;
			auto_type_writer< CT_GrayscaleTransform_writer > _gray_writer;
			auto_type_writer< CT_PositiveFixedPercentage_writer > _alpha_writer;
			auto_type_writer< CT_FixedPercentage_writer > _alphaOff_writer;
			auto_type_writer< CT_PositivePercentage_writer > _alphaMod_writer;
			auto_type_writer< CT_PositiveFixedAngle_writer > _hue_writer;
			auto_type_writer< CT_Angle_writer > _hueOff_writer;
			auto_type_writer< CT_PositivePercentage_writer > _hueMod_writer;
			auto_type_writer< CT_Percentage_writer > _sat_writer;
			auto_type_writer< CT_Percentage_writer > _satOff_writer;
			auto_type_writer< CT_Percentage_writer > _satMod_writer;
			auto_type_writer< CT_Percentage_writer > _lum_writer;
			auto_type_writer< CT_Percentage_writer > _lumOff_writer;
			auto_type_writer< CT_Percentage_writer > _lumMod_writer;
			auto_type_writer< CT_Percentage_writer > _red_writer;
			auto_type_writer< CT_Percentage_writer > _redOff_writer;
			auto_type_writer< CT_Percentage_writer > _redMod_writer;
			auto_type_writer< CT_Percentage_writer > _green_writer;
			auto_type_writer< CT_Percentage_writer > _greenOff_writer;
			auto_type_writer< CT_Percentage_writer > _greenMod_writer;
			auto_type_writer< CT_Percentage_writer > _blue_writer;
			auto_type_writer< CT_Percentage_writer > _blueOff_writer;
			auto_type_writer< CT_Percentage_writer > _blueMod_writer;
			auto_type_writer< CT_GammaTransform_writer > _gamma_writer;
			auto_type_writer< CT_InverseGammaTransform_writer > _invGamma_writer;
			CT_HslColor* t() { return static_cast<CT_HslColor*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_SystemColor_writer : public type_writer
		{
			auto_type_writer< CT_PositiveFixedPercentage_writer > _tint_writer;
			auto_type_writer< CT_PositiveFixedPercentage_writer > _shade_writer;
			auto_type_writer< CT_ComplementTransform_writer > _comp_writer;
			auto_type_writer< CT_InverseTransform_writer > _inv_writer;
			auto_type_writer< CT_GrayscaleTransform_writer > _gray_writer;
			auto_type_writer< CT_PositiveFixedPercentage_writer > _alpha_writer;
			auto_type_writer< CT_FixedPercentage_writer > _alphaOff_writer;
			auto_type_writer< CT_PositivePercentage_writer > _alphaMod_writer;
			auto_type_writer< CT_PositiveFixedAngle_writer > _hue_writer;
			auto_type_writer< CT_Angle_writer > _hueOff_writer;
			auto_type_writer< CT_PositivePercentage_writer > _hueMod_writer;
			auto_type_writer< CT_Percentage_writer > _sat_writer;
			auto_type_writer< CT_Percentage_writer > _satOff_writer;
			auto_type_writer< CT_Percentage_writer > _satMod_writer;
			auto_type_writer< CT_Percentage_writer > _lum_writer;
			auto_type_writer< CT_Percentage_writer > _lumOff_writer;
			auto_type_writer< CT_Percentage_writer > _lumMod_writer;
			auto_type_writer< CT_Percentage_writer > _red_writer;
			auto_type_writer< CT_Percentage_writer > _redOff_writer;
			auto_type_writer< CT_Percentage_writer > _redMod_writer;
			auto_type_writer< CT_Percentage_writer > _green_writer;
			auto_type_writer< CT_Percentage_writer > _greenOff_writer;
			auto_type_writer< CT_Percentage_writer > _greenMod_writer;
			auto_type_writer< CT_Percentage_writer > _blue_writer;
			auto_type_writer< CT_Percentage_writer > _blueOff_writer;
			auto_type_writer< CT_Percentage_writer > _blueMod_writer;
			auto_type_writer< CT_GammaTransform_writer > _gamma_writer;
			auto_type_writer< CT_InverseGammaTransform_writer > _invGamma_writer;
			CT_SystemColor* t() { return static_cast<CT_SystemColor*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_SchemeColor_writer : public type_writer
		{
			auto_type_writer< CT_PositiveFixedPercentage_writer > _tint_writer;
			auto_type_writer< CT_PositiveFixedPercentage_writer > _shade_writer;
			auto_type_writer< CT_ComplementTransform_writer > _comp_writer;
			auto_type_writer< CT_InverseTransform_writer > _inv_writer;
			auto_type_writer< CT_GrayscaleTransform_writer > _gray_writer;
			auto_type_writer< CT_PositiveFixedPercentage_writer > _alpha_writer;
			auto_type_writer< CT_FixedPercentage_writer > _alphaOff_writer;
			auto_type_writer< CT_PositivePercentage_writer > _alphaMod_writer;
			auto_type_writer< CT_PositiveFixedAngle_writer > _hue_writer;
			auto_type_writer< CT_Angle_writer > _hueOff_writer;
			auto_type_writer< CT_PositivePercentage_writer > _hueMod_writer;
			auto_type_writer< CT_Percentage_writer > _sat_writer;
			auto_type_writer< CT_Percentage_writer > _satOff_writer;
			auto_type_writer< CT_Percentage_writer > _satMod_writer;
			auto_type_writer< CT_Percentage_writer > _lum_writer;
			auto_type_writer< CT_Percentage_writer > _lumOff_writer;
			auto_type_writer< CT_Percentage_writer > _lumMod_writer;
			auto_type_writer< CT_Percentage_writer > _red_writer;
			auto_type_writer< CT_Percentage_writer > _redOff_writer;
			auto_type_writer< CT_Percentage_writer > _redMod_writer;
			auto_type_writer< CT_Percentage_writer > _green_writer;
			auto_type_writer< CT_Percentage_writer > _greenOff_writer;
			auto_type_writer< CT_Percentage_writer > _greenMod_writer;
			auto_type_writer< CT_Percentage_writer > _blue_writer;
			auto_type_writer< CT_Percentage_writer > _blueOff_writer;
			auto_type_writer< CT_Percentage_writer > _blueMod_writer;
			auto_type_writer< CT_GammaTransform_writer > _gamma_writer;
			auto_type_writer< CT_InverseGammaTransform_writer > _invGamma_writer;
			CT_SchemeColor* t() { return static_cast<CT_SchemeColor*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_PresetColor_writer : public type_writer
		{
			auto_type_writer< CT_PositiveFixedPercentage_writer > _tint_writer;
			auto_type_writer< CT_PositiveFixedPercentage_writer > _shade_writer;
			auto_type_writer< CT_ComplementTransform_writer > _comp_writer;
			auto_type_writer< CT_InverseTransform_writer > _inv_writer;
			auto_type_writer< CT_GrayscaleTransform_writer > _gray_writer;
			auto_type_writer< CT_PositiveFixedPercentage_writer > _alpha_writer;
			auto_type_writer< CT_FixedPercentage_writer > _alphaOff_writer;
			auto_type_writer< CT_PositivePercentage_writer > _alphaMod_writer;
			auto_type_writer< CT_PositiveFixedAngle_writer > _hue_writer;
			auto_type_writer< CT_Angle_writer > _hueOff_writer;
			auto_type_writer< CT_PositivePercentage_writer > _hueMod_writer;
			auto_type_writer< CT_Percentage_writer > _sat_writer;
			auto_type_writer< CT_Percentage_writer > _satOff_writer;
			auto_type_writer< CT_Percentage_writer > _satMod_writer;
			auto_type_writer< CT_Percentage_writer > _lum_writer;
			auto_type_writer< CT_Percentage_writer > _lumOff_writer;
			auto_type_writer< CT_Percentage_writer > _lumMod_writer;
			auto_type_writer< CT_Percentage_writer > _red_writer;
			auto_type_writer< CT_Percentage_writer > _redOff_writer;
			auto_type_writer< CT_Percentage_writer > _redMod_writer;
			auto_type_writer< CT_Percentage_writer > _green_writer;
			auto_type_writer< CT_Percentage_writer > _greenOff_writer;
			auto_type_writer< CT_Percentage_writer > _greenMod_writer;
			auto_type_writer< CT_Percentage_writer > _blue_writer;
			auto_type_writer< CT_Percentage_writer > _blueOff_writer;
			auto_type_writer< CT_Percentage_writer > _blueMod_writer;
			auto_type_writer< CT_GammaTransform_writer > _gamma_writer;
			auto_type_writer< CT_InverseGammaTransform_writer > _invGamma_writer;
			CT_PresetColor* t() { return static_cast<CT_PresetColor*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Color_writer : public type_writer
		{
			auto_type_writer< CT_ScRgbColor_writer > _scrgbClr_writer;
			auto_type_writer< CT_SRgbColor_writer > _srgbClr_writer;
			auto_type_writer< CT_HslColor_writer > _hslClr_writer;
			auto_type_writer< CT_SystemColor_writer > _sysClr_writer;
			auto_type_writer< CT_SchemeColor_writer > _schemeClr_writer;
			auto_type_writer< CT_PresetColor_writer > _prstClr_writer;
			CT_Color* t() { return static_cast<CT_Color*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class ST_Coordinate32_writer : public type_writer
		{
			ST_Coordinate32* t() { return static_cast<ST_Coordinate32*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class ST_PositiveCoordinate32_writer : public ST_Coordinate32_writer
		{
			ST_PositiveCoordinate32* t() { return static_cast<ST_PositiveCoordinate32*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_RelativeRect_writer : public type_writer
		{
			CT_RelativeRect* t() { return static_cast<CT_RelativeRect*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class ST_FixedAngle_writer : public ST_Angle_writer
		{
			ST_FixedAngle* t() { return static_cast<ST_FixedAngle*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_EmbeddedWAVAudioFile_writer : public type_writer
		{
			CT_EmbeddedWAVAudioFile* t() { return static_cast<CT_EmbeddedWAVAudioFile*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Hyperlink_writer : public type_writer
		{
			auto_type_writer< CT_EmbeddedWAVAudioFile_writer > _snd_writer;
			auto_type_writer< CT_OfficeArtExtensionList_writer > _extLst_writer;
			CT_Hyperlink* t() { return static_cast<CT_Hyperlink*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class ST_Guid_writer : public type_writer
		{
			ST_Guid* t() { return static_cast<ST_Guid*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Point2D_writer : public type_writer
		{
			CT_Point2D* t() { return static_cast<CT_Point2D*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_PositiveSize2D_writer : public type_writer
		{
			CT_PositiveSize2D* t() { return static_cast<CT_PositiveSize2D*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Transform2D_writer : public type_writer
		{
			auto_type_writer< CT_Point2D_writer > _off_writer;
			auto_type_writer< CT_PositiveSize2D_writer > _ext_writer;
			CT_Transform2D* t() { return static_cast<CT_Transform2D*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class ST_DrawingElementId_writer : public type_writer
		{
			ST_DrawingElementId* t() { return static_cast<ST_DrawingElementId*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_GroupTransform2D_writer : public type_writer
		{
			auto_type_writer< CT_Point2D_writer > _off_writer;
			auto_type_writer< CT_PositiveSize2D_writer > _ext_writer;
			auto_type_writer< CT_Point2D_writer > _chOff_writer;
			auto_type_writer< CT_PositiveSize2D_writer > _chExt_writer;
			CT_GroupTransform2D* t() { return static_cast<CT_GroupTransform2D*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_ColorMRU_writer : public type_writer
		{
			auto_type_writer< CT_ScRgbColor_writer > _scrgbClr_writer;
			auto_type_writer< CT_SRgbColor_writer > _srgbClr_writer;
			auto_type_writer< CT_HslColor_writer > _hslClr_writer;
			auto_type_writer< CT_SystemColor_writer > _sysClr_writer;
			auto_type_writer< CT_SchemeColor_writer > _schemeClr_writer;
			auto_type_writer< CT_PresetColor_writer > _prstClr_writer;
			CT_ColorMRU* t() { return static_cast<CT_ColorMRU*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Ratio_writer : public type_writer
		{
			CT_Ratio* t() { return static_cast<CT_Ratio*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Scale2D_writer : public type_writer
		{
			auto_type_writer< CT_Ratio_writer > _sx_writer;
			auto_type_writer< CT_Ratio_writer > _sy_writer;
			CT_Scale2D* t() { return static_cast<CT_Scale2D*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

	}
}
#endif

