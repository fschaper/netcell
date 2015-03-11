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

#ifndef DML_BASETYPES_READERS_HPP
#define DML_BASETYPES_READERS_HPP

#include "dml-baseTypes.hpp"
#include "shared-relationshipReference_readers.hpp"

namespace drawingml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_OfficeArtExtension_reader;
		class CT_OfficeArtExtensionList_reader;
		class ST_Percentage_reader;
		class ST_Angle_reader;
		class ST_PositiveFixedAngle_reader;
		class CT_SphereCoords_reader;
		class ST_PositivePercentage_reader;
		class ST_Coordinate_reader;
		class CT_Point3D_reader;
		class CT_Vector3D_reader;
		class ST_PositiveCoordinate_reader;
		class ST_PositiveFixedPercentage_reader;
		class CT_PositiveFixedPercentage_reader;
		class CT_ComplementTransform_reader;
		class CT_InverseTransform_reader;
		class CT_GrayscaleTransform_reader;
		class ST_FixedPercentage_reader;
		class CT_FixedPercentage_reader;
		class CT_PositivePercentage_reader;
		class CT_PositiveFixedAngle_reader;
		class CT_Angle_reader;
		class CT_Percentage_reader;
		class CT_GammaTransform_reader;
		class CT_InverseGammaTransform_reader;
		class CT_ScRgbColor_reader;
		class ST_HexBinary3_reader;
		class CT_SRgbColor_reader;
		class CT_HslColor_reader;
		class CT_SystemColor_reader;
		class CT_SchemeColor_reader;
		class CT_PresetColor_reader;
		class CT_Color_reader;
		class ST_Coordinate32_reader;
		class ST_PositiveCoordinate32_reader;
		class CT_RelativeRect_reader;
		class ST_FixedAngle_reader;
		class CT_EmbeddedWAVAudioFile_reader;
		class CT_Hyperlink_reader;
		class ST_Guid_reader;
		class CT_Point2D_reader;
		class CT_PositiveSize2D_reader;
		class CT_Transform2D_reader;
		class ST_DrawingElementId_reader;
		class CT_GroupTransform2D_reader;
		class CT_ColorMRU_reader;
		class CT_Ratio_reader;
		class CT_Scale2D_reader;

		class CT_OfficeArtExtension_reader : public type_reader
		{
		protected:
			CT_OfficeArtExtension* t() { return static_cast<CT_OfficeArtExtension*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_OfficeArtExtensionList_reader : public type_reader
		{
			auto_type_reader< CT_OfficeArtExtension_reader > _ext_reader;
		protected:
			CT_OfficeArtExtensionList* t() { return static_cast<CT_OfficeArtExtensionList*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class ST_Percentage_reader : public type_reader
		{
		protected:
			ST_Percentage* t() { return static_cast<ST_Percentage*>(target()); }
			void read_value(const xstring& val);
		};

		class ST_Angle_reader : public type_reader
		{
		protected:
			ST_Angle* t() { return static_cast<ST_Angle*>(target()); }
			void read_value(const xstring& val);
		};

		class ST_PositiveFixedAngle_reader : public ST_Angle_reader
		{
		protected:
			ST_PositiveFixedAngle* t() { return static_cast<ST_PositiveFixedAngle*>(target()); }
		};

		class CT_SphereCoords_reader : public type_reader
		{
		protected:
			CT_SphereCoords* t() { return static_cast<CT_SphereCoords*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class ST_PositivePercentage_reader : public ST_Percentage_reader
		{
		protected:
			ST_PositivePercentage* t() { return static_cast<ST_PositivePercentage*>(target()); }
		};

		class ST_Coordinate_reader : public type_reader
		{
		protected:
			ST_Coordinate* t() { return static_cast<ST_Coordinate*>(target()); }
			void read_value(const xstring& val);
		};

		class CT_Point3D_reader : public type_reader
		{
		protected:
			CT_Point3D* t() { return static_cast<CT_Point3D*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Vector3D_reader : public type_reader
		{
		protected:
			CT_Vector3D* t() { return static_cast<CT_Vector3D*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class ST_PositiveCoordinate_reader : public type_reader
		{
		protected:
			ST_PositiveCoordinate* t() { return static_cast<ST_PositiveCoordinate*>(target()); }
			void read_value(const xstring& val);
		};

		class ST_PositiveFixedPercentage_reader : public ST_Percentage_reader
		{
		protected:
			ST_PositiveFixedPercentage* t() { return static_cast<ST_PositiveFixedPercentage*>(target()); }
		};

		class CT_PositiveFixedPercentage_reader : public type_reader
		{
		protected:
			CT_PositiveFixedPercentage* t() { return static_cast<CT_PositiveFixedPercentage*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_ComplementTransform_reader : public type_reader
		{
		protected:
			CT_ComplementTransform* t() { return static_cast<CT_ComplementTransform*>(target()); }
		};

		class CT_InverseTransform_reader : public type_reader
		{
		protected:
			CT_InverseTransform* t() { return static_cast<CT_InverseTransform*>(target()); }
		};

		class CT_GrayscaleTransform_reader : public type_reader
		{
		protected:
			CT_GrayscaleTransform* t() { return static_cast<CT_GrayscaleTransform*>(target()); }
		};

		class ST_FixedPercentage_reader : public ST_Percentage_reader
		{
		protected:
			ST_FixedPercentage* t() { return static_cast<ST_FixedPercentage*>(target()); }
		};

		class CT_FixedPercentage_reader : public type_reader
		{
		protected:
			CT_FixedPercentage* t() { return static_cast<CT_FixedPercentage*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_PositivePercentage_reader : public type_reader
		{
		protected:
			CT_PositivePercentage* t() { return static_cast<CT_PositivePercentage*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_PositiveFixedAngle_reader : public type_reader
		{
		protected:
			CT_PositiveFixedAngle* t() { return static_cast<CT_PositiveFixedAngle*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Angle_reader : public type_reader
		{
		protected:
			CT_Angle* t() { return static_cast<CT_Angle*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Percentage_reader : public type_reader
		{
		protected:
			CT_Percentage* t() { return static_cast<CT_Percentage*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_GammaTransform_reader : public type_reader
		{
		protected:
			CT_GammaTransform* t() { return static_cast<CT_GammaTransform*>(target()); }
		};

		class CT_InverseGammaTransform_reader : public type_reader
		{
		protected:
			CT_InverseGammaTransform* t() { return static_cast<CT_InverseGammaTransform*>(target()); }
		};

		class CT_ScRgbColor_reader : public type_reader
		{
			auto_type_reader< CT_PositiveFixedPercentage_reader > _tint_reader;
			auto_type_reader< CT_PositiveFixedPercentage_reader > _shade_reader;
			auto_type_reader< CT_ComplementTransform_reader > _comp_reader;
			auto_type_reader< CT_InverseTransform_reader > _inv_reader;
			auto_type_reader< CT_GrayscaleTransform_reader > _gray_reader;
			auto_type_reader< CT_PositiveFixedPercentage_reader > _alpha_reader;
			auto_type_reader< CT_FixedPercentage_reader > _alphaOff_reader;
			auto_type_reader< CT_PositivePercentage_reader > _alphaMod_reader;
			auto_type_reader< CT_PositiveFixedAngle_reader > _hue_reader;
			auto_type_reader< CT_Angle_reader > _hueOff_reader;
			auto_type_reader< CT_PositivePercentage_reader > _hueMod_reader;
			auto_type_reader< CT_Percentage_reader > _sat_reader;
			auto_type_reader< CT_Percentage_reader > _satOff_reader;
			auto_type_reader< CT_Percentage_reader > _satMod_reader;
			auto_type_reader< CT_Percentage_reader > _lum_reader;
			auto_type_reader< CT_Percentage_reader > _lumOff_reader;
			auto_type_reader< CT_Percentage_reader > _lumMod_reader;
			auto_type_reader< CT_Percentage_reader > _red_reader;
			auto_type_reader< CT_Percentage_reader > _redOff_reader;
			auto_type_reader< CT_Percentage_reader > _redMod_reader;
			auto_type_reader< CT_Percentage_reader > _green_reader;
			auto_type_reader< CT_Percentage_reader > _greenOff_reader;
			auto_type_reader< CT_Percentage_reader > _greenMod_reader;
			auto_type_reader< CT_Percentage_reader > _blue_reader;
			auto_type_reader< CT_Percentage_reader > _blueOff_reader;
			auto_type_reader< CT_Percentage_reader > _blueMod_reader;
			auto_type_reader< CT_GammaTransform_reader > _gamma_reader;
			auto_type_reader< CT_InverseGammaTransform_reader > _invGamma_reader;
		protected:
			CT_ScRgbColor* t() { return static_cast<CT_ScRgbColor*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class ST_HexBinary3_reader : public type_reader
		{
		protected:
			ST_HexBinary3* t() { return static_cast<ST_HexBinary3*>(target()); }
			void read_value(const xstring& val);
		};

		class CT_SRgbColor_reader : public type_reader
		{
			auto_type_reader< CT_PositiveFixedPercentage_reader > _tint_reader;
			auto_type_reader< CT_PositiveFixedPercentage_reader > _shade_reader;
			auto_type_reader< CT_ComplementTransform_reader > _comp_reader;
			auto_type_reader< CT_InverseTransform_reader > _inv_reader;
			auto_type_reader< CT_GrayscaleTransform_reader > _gray_reader;
			auto_type_reader< CT_PositiveFixedPercentage_reader > _alpha_reader;
			auto_type_reader< CT_FixedPercentage_reader > _alphaOff_reader;
			auto_type_reader< CT_PositivePercentage_reader > _alphaMod_reader;
			auto_type_reader< CT_PositiveFixedAngle_reader > _hue_reader;
			auto_type_reader< CT_Angle_reader > _hueOff_reader;
			auto_type_reader< CT_PositivePercentage_reader > _hueMod_reader;
			auto_type_reader< CT_Percentage_reader > _sat_reader;
			auto_type_reader< CT_Percentage_reader > _satOff_reader;
			auto_type_reader< CT_Percentage_reader > _satMod_reader;
			auto_type_reader< CT_Percentage_reader > _lum_reader;
			auto_type_reader< CT_Percentage_reader > _lumOff_reader;
			auto_type_reader< CT_Percentage_reader > _lumMod_reader;
			auto_type_reader< CT_Percentage_reader > _red_reader;
			auto_type_reader< CT_Percentage_reader > _redOff_reader;
			auto_type_reader< CT_Percentage_reader > _redMod_reader;
			auto_type_reader< CT_Percentage_reader > _green_reader;
			auto_type_reader< CT_Percentage_reader > _greenOff_reader;
			auto_type_reader< CT_Percentage_reader > _greenMod_reader;
			auto_type_reader< CT_Percentage_reader > _blue_reader;
			auto_type_reader< CT_Percentage_reader > _blueOff_reader;
			auto_type_reader< CT_Percentage_reader > _blueMod_reader;
			auto_type_reader< CT_GammaTransform_reader > _gamma_reader;
			auto_type_reader< CT_InverseGammaTransform_reader > _invGamma_reader;
		protected:
			CT_SRgbColor* t() { return static_cast<CT_SRgbColor*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_HslColor_reader : public type_reader
		{
			auto_type_reader< CT_PositiveFixedPercentage_reader > _tint_reader;
			auto_type_reader< CT_PositiveFixedPercentage_reader > _shade_reader;
			auto_type_reader< CT_ComplementTransform_reader > _comp_reader;
			auto_type_reader< CT_InverseTransform_reader > _inv_reader;
			auto_type_reader< CT_GrayscaleTransform_reader > _gray_reader;
			auto_type_reader< CT_PositiveFixedPercentage_reader > _alpha_reader;
			auto_type_reader< CT_FixedPercentage_reader > _alphaOff_reader;
			auto_type_reader< CT_PositivePercentage_reader > _alphaMod_reader;
			auto_type_reader< CT_PositiveFixedAngle_reader > _hue_reader;
			auto_type_reader< CT_Angle_reader > _hueOff_reader;
			auto_type_reader< CT_PositivePercentage_reader > _hueMod_reader;
			auto_type_reader< CT_Percentage_reader > _sat_reader;
			auto_type_reader< CT_Percentage_reader > _satOff_reader;
			auto_type_reader< CT_Percentage_reader > _satMod_reader;
			auto_type_reader< CT_Percentage_reader > _lum_reader;
			auto_type_reader< CT_Percentage_reader > _lumOff_reader;
			auto_type_reader< CT_Percentage_reader > _lumMod_reader;
			auto_type_reader< CT_Percentage_reader > _red_reader;
			auto_type_reader< CT_Percentage_reader > _redOff_reader;
			auto_type_reader< CT_Percentage_reader > _redMod_reader;
			auto_type_reader< CT_Percentage_reader > _green_reader;
			auto_type_reader< CT_Percentage_reader > _greenOff_reader;
			auto_type_reader< CT_Percentage_reader > _greenMod_reader;
			auto_type_reader< CT_Percentage_reader > _blue_reader;
			auto_type_reader< CT_Percentage_reader > _blueOff_reader;
			auto_type_reader< CT_Percentage_reader > _blueMod_reader;
			auto_type_reader< CT_GammaTransform_reader > _gamma_reader;
			auto_type_reader< CT_InverseGammaTransform_reader > _invGamma_reader;
		protected:
			CT_HslColor* t() { return static_cast<CT_HslColor*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_SystemColor_reader : public type_reader
		{
			auto_type_reader< CT_PositiveFixedPercentage_reader > _tint_reader;
			auto_type_reader< CT_PositiveFixedPercentage_reader > _shade_reader;
			auto_type_reader< CT_ComplementTransform_reader > _comp_reader;
			auto_type_reader< CT_InverseTransform_reader > _inv_reader;
			auto_type_reader< CT_GrayscaleTransform_reader > _gray_reader;
			auto_type_reader< CT_PositiveFixedPercentage_reader > _alpha_reader;
			auto_type_reader< CT_FixedPercentage_reader > _alphaOff_reader;
			auto_type_reader< CT_PositivePercentage_reader > _alphaMod_reader;
			auto_type_reader< CT_PositiveFixedAngle_reader > _hue_reader;
			auto_type_reader< CT_Angle_reader > _hueOff_reader;
			auto_type_reader< CT_PositivePercentage_reader > _hueMod_reader;
			auto_type_reader< CT_Percentage_reader > _sat_reader;
			auto_type_reader< CT_Percentage_reader > _satOff_reader;
			auto_type_reader< CT_Percentage_reader > _satMod_reader;
			auto_type_reader< CT_Percentage_reader > _lum_reader;
			auto_type_reader< CT_Percentage_reader > _lumOff_reader;
			auto_type_reader< CT_Percentage_reader > _lumMod_reader;
			auto_type_reader< CT_Percentage_reader > _red_reader;
			auto_type_reader< CT_Percentage_reader > _redOff_reader;
			auto_type_reader< CT_Percentage_reader > _redMod_reader;
			auto_type_reader< CT_Percentage_reader > _green_reader;
			auto_type_reader< CT_Percentage_reader > _greenOff_reader;
			auto_type_reader< CT_Percentage_reader > _greenMod_reader;
			auto_type_reader< CT_Percentage_reader > _blue_reader;
			auto_type_reader< CT_Percentage_reader > _blueOff_reader;
			auto_type_reader< CT_Percentage_reader > _blueMod_reader;
			auto_type_reader< CT_GammaTransform_reader > _gamma_reader;
			auto_type_reader< CT_InverseGammaTransform_reader > _invGamma_reader;
		protected:
			CT_SystemColor* t() { return static_cast<CT_SystemColor*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_SchemeColor_reader : public type_reader
		{
			auto_type_reader< CT_PositiveFixedPercentage_reader > _tint_reader;
			auto_type_reader< CT_PositiveFixedPercentage_reader > _shade_reader;
			auto_type_reader< CT_ComplementTransform_reader > _comp_reader;
			auto_type_reader< CT_InverseTransform_reader > _inv_reader;
			auto_type_reader< CT_GrayscaleTransform_reader > _gray_reader;
			auto_type_reader< CT_PositiveFixedPercentage_reader > _alpha_reader;
			auto_type_reader< CT_FixedPercentage_reader > _alphaOff_reader;
			auto_type_reader< CT_PositivePercentage_reader > _alphaMod_reader;
			auto_type_reader< CT_PositiveFixedAngle_reader > _hue_reader;
			auto_type_reader< CT_Angle_reader > _hueOff_reader;
			auto_type_reader< CT_PositivePercentage_reader > _hueMod_reader;
			auto_type_reader< CT_Percentage_reader > _sat_reader;
			auto_type_reader< CT_Percentage_reader > _satOff_reader;
			auto_type_reader< CT_Percentage_reader > _satMod_reader;
			auto_type_reader< CT_Percentage_reader > _lum_reader;
			auto_type_reader< CT_Percentage_reader > _lumOff_reader;
			auto_type_reader< CT_Percentage_reader > _lumMod_reader;
			auto_type_reader< CT_Percentage_reader > _red_reader;
			auto_type_reader< CT_Percentage_reader > _redOff_reader;
			auto_type_reader< CT_Percentage_reader > _redMod_reader;
			auto_type_reader< CT_Percentage_reader > _green_reader;
			auto_type_reader< CT_Percentage_reader > _greenOff_reader;
			auto_type_reader< CT_Percentage_reader > _greenMod_reader;
			auto_type_reader< CT_Percentage_reader > _blue_reader;
			auto_type_reader< CT_Percentage_reader > _blueOff_reader;
			auto_type_reader< CT_Percentage_reader > _blueMod_reader;
			auto_type_reader< CT_GammaTransform_reader > _gamma_reader;
			auto_type_reader< CT_InverseGammaTransform_reader > _invGamma_reader;
		protected:
			CT_SchemeColor* t() { return static_cast<CT_SchemeColor*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_PresetColor_reader : public type_reader
		{
			auto_type_reader< CT_PositiveFixedPercentage_reader > _tint_reader;
			auto_type_reader< CT_PositiveFixedPercentage_reader > _shade_reader;
			auto_type_reader< CT_ComplementTransform_reader > _comp_reader;
			auto_type_reader< CT_InverseTransform_reader > _inv_reader;
			auto_type_reader< CT_GrayscaleTransform_reader > _gray_reader;
			auto_type_reader< CT_PositiveFixedPercentage_reader > _alpha_reader;
			auto_type_reader< CT_FixedPercentage_reader > _alphaOff_reader;
			auto_type_reader< CT_PositivePercentage_reader > _alphaMod_reader;
			auto_type_reader< CT_PositiveFixedAngle_reader > _hue_reader;
			auto_type_reader< CT_Angle_reader > _hueOff_reader;
			auto_type_reader< CT_PositivePercentage_reader > _hueMod_reader;
			auto_type_reader< CT_Percentage_reader > _sat_reader;
			auto_type_reader< CT_Percentage_reader > _satOff_reader;
			auto_type_reader< CT_Percentage_reader > _satMod_reader;
			auto_type_reader< CT_Percentage_reader > _lum_reader;
			auto_type_reader< CT_Percentage_reader > _lumOff_reader;
			auto_type_reader< CT_Percentage_reader > _lumMod_reader;
			auto_type_reader< CT_Percentage_reader > _red_reader;
			auto_type_reader< CT_Percentage_reader > _redOff_reader;
			auto_type_reader< CT_Percentage_reader > _redMod_reader;
			auto_type_reader< CT_Percentage_reader > _green_reader;
			auto_type_reader< CT_Percentage_reader > _greenOff_reader;
			auto_type_reader< CT_Percentage_reader > _greenMod_reader;
			auto_type_reader< CT_Percentage_reader > _blue_reader;
			auto_type_reader< CT_Percentage_reader > _blueOff_reader;
			auto_type_reader< CT_Percentage_reader > _blueMod_reader;
			auto_type_reader< CT_GammaTransform_reader > _gamma_reader;
			auto_type_reader< CT_InverseGammaTransform_reader > _invGamma_reader;
		protected:
			CT_PresetColor* t() { return static_cast<CT_PresetColor*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Color_reader : public type_reader
		{
			auto_type_reader< CT_ScRgbColor_reader > _scrgbClr_reader;
			auto_type_reader< CT_SRgbColor_reader > _srgbClr_reader;
			auto_type_reader< CT_HslColor_reader > _hslClr_reader;
			auto_type_reader< CT_SystemColor_reader > _sysClr_reader;
			auto_type_reader< CT_SchemeColor_reader > _schemeClr_reader;
			auto_type_reader< CT_PresetColor_reader > _prstClr_reader;
		protected:
			CT_Color* t() { return static_cast<CT_Color*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class ST_Coordinate32_reader : public type_reader
		{
		protected:
			ST_Coordinate32* t() { return static_cast<ST_Coordinate32*>(target()); }
			void read_value(const xstring& val);
		};

		class ST_PositiveCoordinate32_reader : public ST_Coordinate32_reader
		{
		protected:
			ST_PositiveCoordinate32* t() { return static_cast<ST_PositiveCoordinate32*>(target()); }
		};

		class CT_RelativeRect_reader : public type_reader
		{
		protected:
			CT_RelativeRect* t() { return static_cast<CT_RelativeRect*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class ST_FixedAngle_reader : public ST_Angle_reader
		{
		protected:
			ST_FixedAngle* t() { return static_cast<ST_FixedAngle*>(target()); }
		};

		class CT_EmbeddedWAVAudioFile_reader : public type_reader
		{
		protected:
			CT_EmbeddedWAVAudioFile* t() { return static_cast<CT_EmbeddedWAVAudioFile*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Hyperlink_reader : public type_reader
		{
			auto_type_reader< CT_EmbeddedWAVAudioFile_reader > _snd_reader;
			auto_type_reader< CT_OfficeArtExtensionList_reader > _extLst_reader;
		protected:
			CT_Hyperlink* t() { return static_cast<CT_Hyperlink*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class ST_Guid_reader : public type_reader
		{
		protected:
			ST_Guid* t() { return static_cast<ST_Guid*>(target()); }
			void read_value(const xstring& val);
		};

		class CT_Point2D_reader : public type_reader
		{
		protected:
			CT_Point2D* t() { return static_cast<CT_Point2D*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_PositiveSize2D_reader : public type_reader
		{
		protected:
			CT_PositiveSize2D* t() { return static_cast<CT_PositiveSize2D*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Transform2D_reader : public type_reader
		{
			auto_type_reader< CT_Point2D_reader > _off_reader;
			auto_type_reader< CT_PositiveSize2D_reader > _ext_reader;
		protected:
			CT_Transform2D* t() { return static_cast<CT_Transform2D*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class ST_DrawingElementId_reader : public type_reader
		{
		protected:
			ST_DrawingElementId* t() { return static_cast<ST_DrawingElementId*>(target()); }
			void read_value(const xstring& val);
		};

		class CT_GroupTransform2D_reader : public type_reader
		{
			auto_type_reader< CT_Point2D_reader > _off_reader;
			auto_type_reader< CT_PositiveSize2D_reader > _ext_reader;
			auto_type_reader< CT_Point2D_reader > _chOff_reader;
			auto_type_reader< CT_PositiveSize2D_reader > _chExt_reader;
		protected:
			CT_GroupTransform2D* t() { return static_cast<CT_GroupTransform2D*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_ColorMRU_reader : public type_reader
		{
			auto_type_reader< CT_ScRgbColor_reader > _scrgbClr_reader;
			auto_type_reader< CT_SRgbColor_reader > _srgbClr_reader;
			auto_type_reader< CT_HslColor_reader > _hslClr_reader;
			auto_type_reader< CT_SystemColor_reader > _sysClr_reader;
			auto_type_reader< CT_SchemeColor_reader > _schemeClr_reader;
			auto_type_reader< CT_PresetColor_reader > _prstClr_reader;
		protected:
			CT_ColorMRU* t() { return static_cast<CT_ColorMRU*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_Ratio_reader : public type_reader
		{
		protected:
			CT_Ratio* t() { return static_cast<CT_Ratio*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Scale2D_reader : public type_reader
		{
			auto_type_reader< CT_Ratio_reader > _sx_reader;
			auto_type_reader< CT_Ratio_reader > _sy_reader;
		protected:
			CT_Scale2D* t() { return static_cast<CT_Scale2D*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

	}
}
#endif

