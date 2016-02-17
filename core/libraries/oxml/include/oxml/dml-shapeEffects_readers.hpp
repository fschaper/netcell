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

#ifndef DML_SHAPEEFFECTS_READERS_HPP
#define DML_SHAPEEFFECTS_READERS_HPP

#include "dml-shapeEffects.hpp"
#include "dml-baseTypes_readers.hpp"
#include "shared-relationshipReference_readers.hpp"

namespace drawingml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_AlphaBiLevelEffect_reader;
		class CT_AlphaCeilingEffect_reader;
		class CT_AlphaFloorEffect_reader;
		class CT_AlphaInverseEffect_reader;
		class CT_EffectReference_reader;
		class CT_AlphaModulateFixedEffect_reader;
		class CT_AlphaOutsetEffect_reader;
		class CT_AlphaReplaceEffect_reader;
		class CT_BiLevelEffect_reader;
		class CT_BlurEffect_reader;
		class CT_ColorChangeEffect_reader;
		class CT_ColorReplaceEffect_reader;
		class CT_DuotoneEffect_reader;
		class CT_NoFillProperties_reader;
		class CT_SolidColorFillProperties_reader;
		class CT_GradientStop_reader;
		class CT_GradientStopList_reader;
		class CT_LinearShadeProperties_reader;
		class CT_PathShadeProperties_reader;
		class CT_GradientFillProperties_reader;
		class CT_TileInfoProperties_reader;
		class CT_StretchInfoProperties_reader;
		class CT_BlipFillProperties_reader;
		class CT_PatternFillProperties_reader;
		class CT_GroupFillProperties_reader;
		class CT_FillEffect_reader;
		class CT_FillOverlayEffect_reader;
		class CT_GlowEffect_reader;
		class CT_GrayscaleEffect_reader;
		class CT_HSLEffect_reader;
		class CT_InnerShadowEffect_reader;
		class CT_LuminanceEffect_reader;
		class CT_OuterShadowEffect_reader;
		class CT_PresetShadowEffect_reader;
		class CT_ReflectionEffect_reader;
		class CT_RelativeOffsetEffect_reader;
		class CT_SoftEdgesEffect_reader;
		class CT_TintEffect_reader;
		class CT_TransformEffect_reader;
		class CT_EffectContainer_reader;
		class CT_AlphaModulateEffect_reader;
		class CT_Blip_reader;
		class CT_EffectList_reader;
		class dml_shapeEffects_reader;
		class CT_FillProperties_reader;
		class CT_EffectProperties_reader;
		class CT_BlendEffect_reader;

		class CT_AlphaBiLevelEffect_reader : public type_reader
		{
		protected:
			CT_AlphaBiLevelEffect* t() { return static_cast<CT_AlphaBiLevelEffect*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_AlphaCeilingEffect_reader : public type_reader
		{
		protected:
			CT_AlphaCeilingEffect* t() { return static_cast<CT_AlphaCeilingEffect*>(target()); }
		};

		class CT_AlphaFloorEffect_reader : public type_reader
		{
		protected:
			CT_AlphaFloorEffect* t() { return static_cast<CT_AlphaFloorEffect*>(target()); }
		};

		class CT_AlphaInverseEffect_reader : public type_reader
		{
			auto_type_reader< CT_ScRgbColor_reader > _scrgbClr_reader;
			auto_type_reader< CT_SRgbColor_reader > _srgbClr_reader;
			auto_type_reader< CT_HslColor_reader > _hslClr_reader;
			auto_type_reader< CT_SystemColor_reader > _sysClr_reader;
			auto_type_reader< CT_SchemeColor_reader > _schemeClr_reader;
			auto_type_reader< CT_PresetColor_reader > _prstClr_reader;
		protected:
			CT_AlphaInverseEffect* t() { return static_cast<CT_AlphaInverseEffect*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_EffectReference_reader : public type_reader
		{
		protected:
			CT_EffectReference* t() { return static_cast<CT_EffectReference*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_AlphaModulateFixedEffect_reader : public type_reader
		{
		protected:
			CT_AlphaModulateFixedEffect* t() { return static_cast<CT_AlphaModulateFixedEffect*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_AlphaOutsetEffect_reader : public type_reader
		{
		protected:
			CT_AlphaOutsetEffect* t() { return static_cast<CT_AlphaOutsetEffect*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_AlphaReplaceEffect_reader : public type_reader
		{
		protected:
			CT_AlphaReplaceEffect* t() { return static_cast<CT_AlphaReplaceEffect*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_BiLevelEffect_reader : public type_reader
		{
		protected:
			CT_BiLevelEffect* t() { return static_cast<CT_BiLevelEffect*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_BlurEffect_reader : public type_reader
		{
		protected:
			CT_BlurEffect* t() { return static_cast<CT_BlurEffect*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_ColorChangeEffect_reader : public type_reader
		{
			auto_type_reader< CT_Color_reader > _clrFrom_reader;
			auto_type_reader< CT_Color_reader > _clrTo_reader;
		protected:
			CT_ColorChangeEffect* t() { return static_cast<CT_ColorChangeEffect*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_ColorReplaceEffect_reader : public type_reader
		{
			auto_type_reader< CT_ScRgbColor_reader > _scrgbClr_reader;
			auto_type_reader< CT_SRgbColor_reader > _srgbClr_reader;
			auto_type_reader< CT_HslColor_reader > _hslClr_reader;
			auto_type_reader< CT_SystemColor_reader > _sysClr_reader;
			auto_type_reader< CT_SchemeColor_reader > _schemeClr_reader;
			auto_type_reader< CT_PresetColor_reader > _prstClr_reader;
		protected:
			CT_ColorReplaceEffect* t() { return static_cast<CT_ColorReplaceEffect*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_DuotoneEffect_reader : public type_reader
		{
			auto_type_reader< CT_ScRgbColor_reader > _scrgbClr_reader;
			auto_type_reader< CT_SRgbColor_reader > _srgbClr_reader;
			auto_type_reader< CT_HslColor_reader > _hslClr_reader;
			auto_type_reader< CT_SystemColor_reader > _sysClr_reader;
			auto_type_reader< CT_SchemeColor_reader > _schemeClr_reader;
			auto_type_reader< CT_PresetColor_reader > _prstClr_reader;
		protected:
			CT_DuotoneEffect* t() { return static_cast<CT_DuotoneEffect*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_NoFillProperties_reader : public type_reader
		{
		protected:
			CT_NoFillProperties* t() { return static_cast<CT_NoFillProperties*>(target()); }
		};

		class CT_SolidColorFillProperties_reader : public type_reader
		{
			auto_type_reader< CT_ScRgbColor_reader > _scrgbClr_reader;
			auto_type_reader< CT_SRgbColor_reader > _srgbClr_reader;
			auto_type_reader< CT_HslColor_reader > _hslClr_reader;
			auto_type_reader< CT_SystemColor_reader > _sysClr_reader;
			auto_type_reader< CT_SchemeColor_reader > _schemeClr_reader;
			auto_type_reader< CT_PresetColor_reader > _prstClr_reader;
		protected:
			CT_SolidColorFillProperties* t() { return static_cast<CT_SolidColorFillProperties*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_GradientStop_reader : public type_reader
		{
			auto_type_reader< CT_ScRgbColor_reader > _scrgbClr_reader;
			auto_type_reader< CT_SRgbColor_reader > _srgbClr_reader;
			auto_type_reader< CT_HslColor_reader > _hslClr_reader;
			auto_type_reader< CT_SystemColor_reader > _sysClr_reader;
			auto_type_reader< CT_SchemeColor_reader > _schemeClr_reader;
			auto_type_reader< CT_PresetColor_reader > _prstClr_reader;
		protected:
			CT_GradientStop* t() { return static_cast<CT_GradientStop*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_GradientStopList_reader : public type_reader
		{
			auto_type_reader< CT_GradientStop_reader > _gs_reader;
		protected:
			CT_GradientStopList* t() { return static_cast<CT_GradientStopList*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_LinearShadeProperties_reader : public type_reader
		{
		protected:
			CT_LinearShadeProperties* t() { return static_cast<CT_LinearShadeProperties*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_PathShadeProperties_reader : public type_reader
		{
			auto_type_reader< CT_RelativeRect_reader > _fillToRect_reader;
		protected:
			CT_PathShadeProperties* t() { return static_cast<CT_PathShadeProperties*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_GradientFillProperties_reader : public type_reader
		{
			auto_type_reader< CT_GradientStopList_reader > _gsLst_reader;
			auto_type_reader< CT_LinearShadeProperties_reader > _lin_reader;
			auto_type_reader< CT_PathShadeProperties_reader > _path_reader;
			auto_type_reader< CT_RelativeRect_reader > _tileRect_reader;
		protected:
			CT_GradientFillProperties* t() { return static_cast<CT_GradientFillProperties*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_TileInfoProperties_reader : public type_reader
		{
		protected:
			CT_TileInfoProperties* t() { return static_cast<CT_TileInfoProperties*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_StretchInfoProperties_reader : public type_reader
		{
			auto_type_reader< CT_RelativeRect_reader > _fillRect_reader;
		protected:
			CT_StretchInfoProperties* t() { return static_cast<CT_StretchInfoProperties*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_BlipFillProperties_reader : public type_reader
		{
			auto_type_reader< CT_Blip_reader > _blip_reader;
			auto_type_reader< CT_RelativeRect_reader > _srcRect_reader;
			auto_type_reader< CT_TileInfoProperties_reader > _tile_reader;
			auto_type_reader< CT_StretchInfoProperties_reader > _stretch_reader;
		protected:
			CT_BlipFillProperties* t() { return static_cast<CT_BlipFillProperties*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_PatternFillProperties_reader : public type_reader
		{
			auto_type_reader< CT_Color_reader > _fgClr_reader;
			auto_type_reader< CT_Color_reader > _bgClr_reader;
		protected:
			CT_PatternFillProperties* t() { return static_cast<CT_PatternFillProperties*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_GroupFillProperties_reader : public type_reader
		{
		protected:
			CT_GroupFillProperties* t() { return static_cast<CT_GroupFillProperties*>(target()); }
		};

		class CT_FillEffect_reader : public type_reader
		{
			auto_type_reader< CT_NoFillProperties_reader > _noFill_reader;
			auto_type_reader< CT_SolidColorFillProperties_reader > _solidFill_reader;
			auto_type_reader< CT_GradientFillProperties_reader > _gradFill_reader;
			auto_type_reader< CT_BlipFillProperties_reader > _blipFill_reader;
			auto_type_reader< CT_PatternFillProperties_reader > _pattFill_reader;
			auto_type_reader< CT_GroupFillProperties_reader > _grpFill_reader;
		protected:
			CT_FillEffect* t() { return static_cast<CT_FillEffect*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_FillOverlayEffect_reader : public type_reader
		{
			auto_type_reader< CT_NoFillProperties_reader > _noFill_reader;
			auto_type_reader< CT_SolidColorFillProperties_reader > _solidFill_reader;
			auto_type_reader< CT_GradientFillProperties_reader > _gradFill_reader;
			auto_type_reader< CT_BlipFillProperties_reader > _blipFill_reader;
			auto_type_reader< CT_PatternFillProperties_reader > _pattFill_reader;
			auto_type_reader< CT_GroupFillProperties_reader > _grpFill_reader;
		protected:
			CT_FillOverlayEffect* t() { return static_cast<CT_FillOverlayEffect*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_GlowEffect_reader : public type_reader
		{
			auto_type_reader< CT_ScRgbColor_reader > _scrgbClr_reader;
			auto_type_reader< CT_SRgbColor_reader > _srgbClr_reader;
			auto_type_reader< CT_HslColor_reader > _hslClr_reader;
			auto_type_reader< CT_SystemColor_reader > _sysClr_reader;
			auto_type_reader< CT_SchemeColor_reader > _schemeClr_reader;
			auto_type_reader< CT_PresetColor_reader > _prstClr_reader;
		protected:
			CT_GlowEffect* t() { return static_cast<CT_GlowEffect*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_GrayscaleEffect_reader : public type_reader
		{
		protected:
			CT_GrayscaleEffect* t() { return static_cast<CT_GrayscaleEffect*>(target()); }
		};

		class CT_HSLEffect_reader : public type_reader
		{
		protected:
			CT_HSLEffect* t() { return static_cast<CT_HSLEffect*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_InnerShadowEffect_reader : public type_reader
		{
			auto_type_reader< CT_ScRgbColor_reader > _scrgbClr_reader;
			auto_type_reader< CT_SRgbColor_reader > _srgbClr_reader;
			auto_type_reader< CT_HslColor_reader > _hslClr_reader;
			auto_type_reader< CT_SystemColor_reader > _sysClr_reader;
			auto_type_reader< CT_SchemeColor_reader > _schemeClr_reader;
			auto_type_reader< CT_PresetColor_reader > _prstClr_reader;
		protected:
			CT_InnerShadowEffect* t() { return static_cast<CT_InnerShadowEffect*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_LuminanceEffect_reader : public type_reader
		{
		protected:
			CT_LuminanceEffect* t() { return static_cast<CT_LuminanceEffect*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_OuterShadowEffect_reader : public type_reader
		{
			auto_type_reader< CT_ScRgbColor_reader > _scrgbClr_reader;
			auto_type_reader< CT_SRgbColor_reader > _srgbClr_reader;
			auto_type_reader< CT_HslColor_reader > _hslClr_reader;
			auto_type_reader< CT_SystemColor_reader > _sysClr_reader;
			auto_type_reader< CT_SchemeColor_reader > _schemeClr_reader;
			auto_type_reader< CT_PresetColor_reader > _prstClr_reader;
		protected:
			CT_OuterShadowEffect* t() { return static_cast<CT_OuterShadowEffect*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_PresetShadowEffect_reader : public type_reader
		{
			auto_type_reader< CT_ScRgbColor_reader > _scrgbClr_reader;
			auto_type_reader< CT_SRgbColor_reader > _srgbClr_reader;
			auto_type_reader< CT_HslColor_reader > _hslClr_reader;
			auto_type_reader< CT_SystemColor_reader > _sysClr_reader;
			auto_type_reader< CT_SchemeColor_reader > _schemeClr_reader;
			auto_type_reader< CT_PresetColor_reader > _prstClr_reader;
		protected:
			CT_PresetShadowEffect* t() { return static_cast<CT_PresetShadowEffect*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_ReflectionEffect_reader : public type_reader
		{
		protected:
			CT_ReflectionEffect* t() { return static_cast<CT_ReflectionEffect*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_RelativeOffsetEffect_reader : public type_reader
		{
		protected:
			CT_RelativeOffsetEffect* t() { return static_cast<CT_RelativeOffsetEffect*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_SoftEdgesEffect_reader : public type_reader
		{
		protected:
			CT_SoftEdgesEffect* t() { return static_cast<CT_SoftEdgesEffect*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_TintEffect_reader : public type_reader
		{
		protected:
			CT_TintEffect* t() { return static_cast<CT_TintEffect*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_TransformEffect_reader : public type_reader
		{
		protected:
			CT_TransformEffect* t() { return static_cast<CT_TransformEffect*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_EffectContainer_reader : public type_reader
		{
			auto_type_reader< CT_EffectContainer_reader > _cont_reader;
			auto_type_reader< CT_EffectReference_reader > _effect_reader;
			auto_type_reader< CT_AlphaBiLevelEffect_reader > _alphaBiLevel_reader;
			auto_type_reader< CT_AlphaCeilingEffect_reader > _alphaCeiling_reader;
			auto_type_reader< CT_AlphaFloorEffect_reader > _alphaFloor_reader;
			auto_type_reader< CT_AlphaInverseEffect_reader > _alphaInv_reader;
			auto_type_reader< CT_AlphaModulateEffect_reader > _alphaMod_reader;
			auto_type_reader< CT_AlphaModulateFixedEffect_reader > _alphaModFix_reader;
			auto_type_reader< CT_AlphaOutsetEffect_reader > _alphaOutset_reader;
			auto_type_reader< CT_AlphaReplaceEffect_reader > _alphaRepl_reader;
			auto_type_reader< CT_BiLevelEffect_reader > _biLevel_reader;
			auto_type_reader< CT_BlendEffect_reader > _blend_reader;
			auto_type_reader< CT_BlurEffect_reader > _blur_reader;
			auto_type_reader< CT_ColorChangeEffect_reader > _clrChange_reader;
			auto_type_reader< CT_ColorReplaceEffect_reader > _clrRepl_reader;
			auto_type_reader< CT_DuotoneEffect_reader > _duotone_reader;
			auto_type_reader< CT_FillEffect_reader > _fill_reader;
			auto_type_reader< CT_FillOverlayEffect_reader > _fillOverlay_reader;
			auto_type_reader< CT_GlowEffect_reader > _glow_reader;
			auto_type_reader< CT_GrayscaleEffect_reader > _grayscl_reader;
			auto_type_reader< CT_HSLEffect_reader > _hsl_reader;
			auto_type_reader< CT_InnerShadowEffect_reader > _innerShdw_reader;
			auto_type_reader< CT_LuminanceEffect_reader > _lum_reader;
			auto_type_reader< CT_OuterShadowEffect_reader > _outerShdw_reader;
			auto_type_reader< CT_PresetShadowEffect_reader > _prstShdw_reader;
			auto_type_reader< CT_ReflectionEffect_reader > _reflection_reader;
			auto_type_reader< CT_RelativeOffsetEffect_reader > _relOff_reader;
			auto_type_reader< CT_SoftEdgesEffect_reader > _softEdge_reader;
			auto_type_reader< CT_TintEffect_reader > _tint_reader;
			auto_type_reader< CT_TransformEffect_reader > _xfrm_reader;
		protected:
			CT_EffectContainer* t() { return static_cast<CT_EffectContainer*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_AlphaModulateEffect_reader : public type_reader
		{
			auto_type_reader< CT_EffectContainer_reader > _cont_reader;
		protected:
			CT_AlphaModulateEffect* t() { return static_cast<CT_AlphaModulateEffect*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_Blip_reader : public type_reader
		{
			auto_type_reader< CT_AlphaBiLevelEffect_reader > _alphaBiLevel_reader;
			auto_type_reader< CT_AlphaCeilingEffect_reader > _alphaCeiling_reader;
			auto_type_reader< CT_AlphaFloorEffect_reader > _alphaFloor_reader;
			auto_type_reader< CT_AlphaInverseEffect_reader > _alphaInv_reader;
			auto_type_reader< CT_AlphaModulateEffect_reader > _alphaMod_reader;
			auto_type_reader< CT_AlphaModulateFixedEffect_reader > _alphaModFix_reader;
			auto_type_reader< CT_AlphaReplaceEffect_reader > _alphaRepl_reader;
			auto_type_reader< CT_BiLevelEffect_reader > _biLevel_reader;
			auto_type_reader< CT_BlurEffect_reader > _blur_reader;
			auto_type_reader< CT_ColorChangeEffect_reader > _clrChange_reader;
			auto_type_reader< CT_ColorReplaceEffect_reader > _clrRepl_reader;
			auto_type_reader< CT_DuotoneEffect_reader > _duotone_reader;
			auto_type_reader< CT_FillOverlayEffect_reader > _fillOverlay_reader;
			auto_type_reader< CT_GrayscaleEffect_reader > _grayscl_reader;
			auto_type_reader< CT_HSLEffect_reader > _hsl_reader;
			auto_type_reader< CT_LuminanceEffect_reader > _lum_reader;
			auto_type_reader< CT_TintEffect_reader > _tint_reader;
			auto_type_reader< CT_OfficeArtExtensionList_reader > _extLst_reader;
		protected:
			CT_Blip* t() { return static_cast<CT_Blip*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_EffectList_reader : public type_reader
		{
			auto_type_reader< CT_BlurEffect_reader > _blur_reader;
			auto_type_reader< CT_FillOverlayEffect_reader > _fillOverlay_reader;
			auto_type_reader< CT_GlowEffect_reader > _glow_reader;
			auto_type_reader< CT_InnerShadowEffect_reader > _innerShdw_reader;
			auto_type_reader< CT_OuterShadowEffect_reader > _outerShdw_reader;
			auto_type_reader< CT_PresetShadowEffect_reader > _prstShdw_reader;
			auto_type_reader< CT_ReflectionEffect_reader > _reflection_reader;
			auto_type_reader< CT_SoftEdgesEffect_reader > _softEdge_reader;
		protected:
			CT_EffectList* t() { return static_cast<CT_EffectList*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class dml_shapeEffects_reader : public type_reader
		{
			auto_type_reader< CT_Blip_reader > _blip_reader;
		protected:
			dml_shapeEffects* t() { return static_cast<dml_shapeEffects*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_FillProperties_reader : public type_reader
		{
			auto_type_reader< CT_NoFillProperties_reader > _noFill_reader;
			auto_type_reader< CT_SolidColorFillProperties_reader > _solidFill_reader;
			auto_type_reader< CT_GradientFillProperties_reader > _gradFill_reader;
			auto_type_reader< CT_BlipFillProperties_reader > _blipFill_reader;
			auto_type_reader< CT_PatternFillProperties_reader > _pattFill_reader;
			auto_type_reader< CT_GroupFillProperties_reader > _grpFill_reader;
		protected:
			CT_FillProperties* t() { return static_cast<CT_FillProperties*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_EffectProperties_reader : public type_reader
		{
			auto_type_reader< CT_EffectList_reader > _effectLst_reader;
			auto_type_reader< CT_EffectContainer_reader > _effectDag_reader;
		protected:
			CT_EffectProperties* t() { return static_cast<CT_EffectProperties*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_BlendEffect_reader : public type_reader
		{
			auto_type_reader< CT_EffectContainer_reader > _cont_reader;
		protected:
			CT_BlendEffect* t() { return static_cast<CT_BlendEffect*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

	}
}
#endif

