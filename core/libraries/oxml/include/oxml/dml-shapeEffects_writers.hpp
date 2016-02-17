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

#ifndef DML_SHAPEEFFECTS_WRITERS_HPP
#define DML_SHAPEEFFECTS_WRITERS_HPP

#include "dml-shapeEffects.hpp"
#include "dml-shapeEffects_literals.hpp"
#include "dml-baseTypes_writers.hpp"
#include "shared-relationshipReference_writers.hpp"

namespace drawingml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_AlphaBiLevelEffect_writer;
		class CT_AlphaCeilingEffect_writer;
		class CT_AlphaFloorEffect_writer;
		class CT_AlphaInverseEffect_writer;
		class CT_EffectReference_writer;
		class CT_AlphaModulateFixedEffect_writer;
		class CT_AlphaOutsetEffect_writer;
		class CT_AlphaReplaceEffect_writer;
		class CT_BiLevelEffect_writer;
		class CT_BlurEffect_writer;
		class CT_ColorChangeEffect_writer;
		class CT_ColorReplaceEffect_writer;
		class CT_DuotoneEffect_writer;
		class CT_NoFillProperties_writer;
		class CT_SolidColorFillProperties_writer;
		class CT_GradientStop_writer;
		class CT_GradientStopList_writer;
		class CT_LinearShadeProperties_writer;
		class CT_PathShadeProperties_writer;
		class CT_GradientFillProperties_writer;
		class CT_TileInfoProperties_writer;
		class CT_StretchInfoProperties_writer;
		class CT_BlipFillProperties_writer;
		class CT_PatternFillProperties_writer;
		class CT_GroupFillProperties_writer;
		class CT_FillEffect_writer;
		class CT_FillOverlayEffect_writer;
		class CT_GlowEffect_writer;
		class CT_GrayscaleEffect_writer;
		class CT_HSLEffect_writer;
		class CT_InnerShadowEffect_writer;
		class CT_LuminanceEffect_writer;
		class CT_OuterShadowEffect_writer;
		class CT_PresetShadowEffect_writer;
		class CT_ReflectionEffect_writer;
		class CT_RelativeOffsetEffect_writer;
		class CT_SoftEdgesEffect_writer;
		class CT_TintEffect_writer;
		class CT_TransformEffect_writer;
		class CT_EffectContainer_writer;
		class CT_AlphaModulateEffect_writer;
		class CT_Blip_writer;
		class CT_EffectList_writer;
		class dml_shapeEffects_writer;
		class CT_FillProperties_writer;
		class CT_EffectProperties_writer;
		class CT_BlendEffect_writer;

		class CT_AlphaBiLevelEffect_writer : public type_writer
		{
			CT_AlphaBiLevelEffect* t() { return static_cast<CT_AlphaBiLevelEffect*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_AlphaCeilingEffect_writer : public type_writer
		{
			CT_AlphaCeilingEffect* t() { return static_cast<CT_AlphaCeilingEffect*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_AlphaFloorEffect_writer : public type_writer
		{
			CT_AlphaFloorEffect* t() { return static_cast<CT_AlphaFloorEffect*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_AlphaInverseEffect_writer : public type_writer
		{
			auto_type_writer< CT_ScRgbColor_writer > _scrgbClr_writer;
			auto_type_writer< CT_SRgbColor_writer > _srgbClr_writer;
			auto_type_writer< CT_HslColor_writer > _hslClr_writer;
			auto_type_writer< CT_SystemColor_writer > _sysClr_writer;
			auto_type_writer< CT_SchemeColor_writer > _schemeClr_writer;
			auto_type_writer< CT_PresetColor_writer > _prstClr_writer;
			CT_AlphaInverseEffect* t() { return static_cast<CT_AlphaInverseEffect*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_EffectReference_writer : public type_writer
		{
			CT_EffectReference* t() { return static_cast<CT_EffectReference*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_AlphaModulateFixedEffect_writer : public type_writer
		{
			CT_AlphaModulateFixedEffect* t() { return static_cast<CT_AlphaModulateFixedEffect*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_AlphaOutsetEffect_writer : public type_writer
		{
			CT_AlphaOutsetEffect* t() { return static_cast<CT_AlphaOutsetEffect*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_AlphaReplaceEffect_writer : public type_writer
		{
			CT_AlphaReplaceEffect* t() { return static_cast<CT_AlphaReplaceEffect*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_BiLevelEffect_writer : public type_writer
		{
			CT_BiLevelEffect* t() { return static_cast<CT_BiLevelEffect*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_BlurEffect_writer : public type_writer
		{
			CT_BlurEffect* t() { return static_cast<CT_BlurEffect*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_ColorChangeEffect_writer : public type_writer
		{
			auto_type_writer< CT_Color_writer > _clrFrom_writer;
			auto_type_writer< CT_Color_writer > _clrTo_writer;
			CT_ColorChangeEffect* t() { return static_cast<CT_ColorChangeEffect*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_ColorReplaceEffect_writer : public type_writer
		{
			auto_type_writer< CT_ScRgbColor_writer > _scrgbClr_writer;
			auto_type_writer< CT_SRgbColor_writer > _srgbClr_writer;
			auto_type_writer< CT_HslColor_writer > _hslClr_writer;
			auto_type_writer< CT_SystemColor_writer > _sysClr_writer;
			auto_type_writer< CT_SchemeColor_writer > _schemeClr_writer;
			auto_type_writer< CT_PresetColor_writer > _prstClr_writer;
			CT_ColorReplaceEffect* t() { return static_cast<CT_ColorReplaceEffect*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_DuotoneEffect_writer : public type_writer
		{
			auto_type_writer< CT_ScRgbColor_writer > _scrgbClr_writer;
			auto_type_writer< CT_SRgbColor_writer > _srgbClr_writer;
			auto_type_writer< CT_HslColor_writer > _hslClr_writer;
			auto_type_writer< CT_SystemColor_writer > _sysClr_writer;
			auto_type_writer< CT_SchemeColor_writer > _schemeClr_writer;
			auto_type_writer< CT_PresetColor_writer > _prstClr_writer;
			CT_DuotoneEffect* t() { return static_cast<CT_DuotoneEffect*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_NoFillProperties_writer : public type_writer
		{
			CT_NoFillProperties* t() { return static_cast<CT_NoFillProperties*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_SolidColorFillProperties_writer : public type_writer
		{
			auto_type_writer< CT_ScRgbColor_writer > _scrgbClr_writer;
			auto_type_writer< CT_SRgbColor_writer > _srgbClr_writer;
			auto_type_writer< CT_HslColor_writer > _hslClr_writer;
			auto_type_writer< CT_SystemColor_writer > _sysClr_writer;
			auto_type_writer< CT_SchemeColor_writer > _schemeClr_writer;
			auto_type_writer< CT_PresetColor_writer > _prstClr_writer;
			CT_SolidColorFillProperties* t() { return static_cast<CT_SolidColorFillProperties*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_GradientStop_writer : public type_writer
		{
			auto_type_writer< CT_ScRgbColor_writer > _scrgbClr_writer;
			auto_type_writer< CT_SRgbColor_writer > _srgbClr_writer;
			auto_type_writer< CT_HslColor_writer > _hslClr_writer;
			auto_type_writer< CT_SystemColor_writer > _sysClr_writer;
			auto_type_writer< CT_SchemeColor_writer > _schemeClr_writer;
			auto_type_writer< CT_PresetColor_writer > _prstClr_writer;
			CT_GradientStop* t() { return static_cast<CT_GradientStop*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_GradientStopList_writer : public type_writer
		{
			auto_type_writer< CT_GradientStop_writer > _gs_writer;
			CT_GradientStopList* t() { return static_cast<CT_GradientStopList*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_LinearShadeProperties_writer : public type_writer
		{
			CT_LinearShadeProperties* t() { return static_cast<CT_LinearShadeProperties*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_PathShadeProperties_writer : public type_writer
		{
			auto_type_writer< CT_RelativeRect_writer > _fillToRect_writer;
			CT_PathShadeProperties* t() { return static_cast<CT_PathShadeProperties*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_GradientFillProperties_writer : public type_writer
		{
			auto_type_writer< CT_GradientStopList_writer > _gsLst_writer;
			auto_type_writer< CT_LinearShadeProperties_writer > _lin_writer;
			auto_type_writer< CT_PathShadeProperties_writer > _path_writer;
			auto_type_writer< CT_RelativeRect_writer > _tileRect_writer;
			CT_GradientFillProperties* t() { return static_cast<CT_GradientFillProperties*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_TileInfoProperties_writer : public type_writer
		{
			CT_TileInfoProperties* t() { return static_cast<CT_TileInfoProperties*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_StretchInfoProperties_writer : public type_writer
		{
			auto_type_writer< CT_RelativeRect_writer > _fillRect_writer;
			CT_StretchInfoProperties* t() { return static_cast<CT_StretchInfoProperties*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_BlipFillProperties_writer : public type_writer
		{
			auto_type_writer< CT_Blip_writer > _blip_writer;
			auto_type_writer< CT_RelativeRect_writer > _srcRect_writer;
			auto_type_writer< CT_TileInfoProperties_writer > _tile_writer;
			auto_type_writer< CT_StretchInfoProperties_writer > _stretch_writer;
			CT_BlipFillProperties* t() { return static_cast<CT_BlipFillProperties*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_PatternFillProperties_writer : public type_writer
		{
			auto_type_writer< CT_Color_writer > _fgClr_writer;
			auto_type_writer< CT_Color_writer > _bgClr_writer;
			CT_PatternFillProperties* t() { return static_cast<CT_PatternFillProperties*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_GroupFillProperties_writer : public type_writer
		{
			CT_GroupFillProperties* t() { return static_cast<CT_GroupFillProperties*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_FillEffect_writer : public type_writer
		{
			auto_type_writer< CT_NoFillProperties_writer > _noFill_writer;
			auto_type_writer< CT_SolidColorFillProperties_writer > _solidFill_writer;
			auto_type_writer< CT_GradientFillProperties_writer > _gradFill_writer;
			auto_type_writer< CT_BlipFillProperties_writer > _blipFill_writer;
			auto_type_writer< CT_PatternFillProperties_writer > _pattFill_writer;
			auto_type_writer< CT_GroupFillProperties_writer > _grpFill_writer;
			CT_FillEffect* t() { return static_cast<CT_FillEffect*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_FillOverlayEffect_writer : public type_writer
		{
			auto_type_writer< CT_NoFillProperties_writer > _noFill_writer;
			auto_type_writer< CT_SolidColorFillProperties_writer > _solidFill_writer;
			auto_type_writer< CT_GradientFillProperties_writer > _gradFill_writer;
			auto_type_writer< CT_BlipFillProperties_writer > _blipFill_writer;
			auto_type_writer< CT_PatternFillProperties_writer > _pattFill_writer;
			auto_type_writer< CT_GroupFillProperties_writer > _grpFill_writer;
			CT_FillOverlayEffect* t() { return static_cast<CT_FillOverlayEffect*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_GlowEffect_writer : public type_writer
		{
			auto_type_writer< CT_ScRgbColor_writer > _scrgbClr_writer;
			auto_type_writer< CT_SRgbColor_writer > _srgbClr_writer;
			auto_type_writer< CT_HslColor_writer > _hslClr_writer;
			auto_type_writer< CT_SystemColor_writer > _sysClr_writer;
			auto_type_writer< CT_SchemeColor_writer > _schemeClr_writer;
			auto_type_writer< CT_PresetColor_writer > _prstClr_writer;
			CT_GlowEffect* t() { return static_cast<CT_GlowEffect*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_GrayscaleEffect_writer : public type_writer
		{
			CT_GrayscaleEffect* t() { return static_cast<CT_GrayscaleEffect*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_HSLEffect_writer : public type_writer
		{
			CT_HSLEffect* t() { return static_cast<CT_HSLEffect*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_InnerShadowEffect_writer : public type_writer
		{
			auto_type_writer< CT_ScRgbColor_writer > _scrgbClr_writer;
			auto_type_writer< CT_SRgbColor_writer > _srgbClr_writer;
			auto_type_writer< CT_HslColor_writer > _hslClr_writer;
			auto_type_writer< CT_SystemColor_writer > _sysClr_writer;
			auto_type_writer< CT_SchemeColor_writer > _schemeClr_writer;
			auto_type_writer< CT_PresetColor_writer > _prstClr_writer;
			CT_InnerShadowEffect* t() { return static_cast<CT_InnerShadowEffect*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_LuminanceEffect_writer : public type_writer
		{
			CT_LuminanceEffect* t() { return static_cast<CT_LuminanceEffect*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_OuterShadowEffect_writer : public type_writer
		{
			auto_type_writer< CT_ScRgbColor_writer > _scrgbClr_writer;
			auto_type_writer< CT_SRgbColor_writer > _srgbClr_writer;
			auto_type_writer< CT_HslColor_writer > _hslClr_writer;
			auto_type_writer< CT_SystemColor_writer > _sysClr_writer;
			auto_type_writer< CT_SchemeColor_writer > _schemeClr_writer;
			auto_type_writer< CT_PresetColor_writer > _prstClr_writer;
			CT_OuterShadowEffect* t() { return static_cast<CT_OuterShadowEffect*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_PresetShadowEffect_writer : public type_writer
		{
			auto_type_writer< CT_ScRgbColor_writer > _scrgbClr_writer;
			auto_type_writer< CT_SRgbColor_writer > _srgbClr_writer;
			auto_type_writer< CT_HslColor_writer > _hslClr_writer;
			auto_type_writer< CT_SystemColor_writer > _sysClr_writer;
			auto_type_writer< CT_SchemeColor_writer > _schemeClr_writer;
			auto_type_writer< CT_PresetColor_writer > _prstClr_writer;
			CT_PresetShadowEffect* t() { return static_cast<CT_PresetShadowEffect*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_ReflectionEffect_writer : public type_writer
		{
			CT_ReflectionEffect* t() { return static_cast<CT_ReflectionEffect*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_RelativeOffsetEffect_writer : public type_writer
		{
			CT_RelativeOffsetEffect* t() { return static_cast<CT_RelativeOffsetEffect*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_SoftEdgesEffect_writer : public type_writer
		{
			CT_SoftEdgesEffect* t() { return static_cast<CT_SoftEdgesEffect*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_TintEffect_writer : public type_writer
		{
			CT_TintEffect* t() { return static_cast<CT_TintEffect*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_TransformEffect_writer : public type_writer
		{
			CT_TransformEffect* t() { return static_cast<CT_TransformEffect*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_EffectContainer_writer : public type_writer
		{
			auto_type_writer< CT_EffectContainer_writer > _cont_writer;
			auto_type_writer< CT_EffectReference_writer > _effect_writer;
			auto_type_writer< CT_AlphaBiLevelEffect_writer > _alphaBiLevel_writer;
			auto_type_writer< CT_AlphaCeilingEffect_writer > _alphaCeiling_writer;
			auto_type_writer< CT_AlphaFloorEffect_writer > _alphaFloor_writer;
			auto_type_writer< CT_AlphaInverseEffect_writer > _alphaInv_writer;
			auto_type_writer< CT_AlphaModulateEffect_writer > _alphaMod_writer;
			auto_type_writer< CT_AlphaModulateFixedEffect_writer > _alphaModFix_writer;
			auto_type_writer< CT_AlphaOutsetEffect_writer > _alphaOutset_writer;
			auto_type_writer< CT_AlphaReplaceEffect_writer > _alphaRepl_writer;
			auto_type_writer< CT_BiLevelEffect_writer > _biLevel_writer;
			auto_type_writer< CT_BlendEffect_writer > _blend_writer;
			auto_type_writer< CT_BlurEffect_writer > _blur_writer;
			auto_type_writer< CT_ColorChangeEffect_writer > _clrChange_writer;
			auto_type_writer< CT_ColorReplaceEffect_writer > _clrRepl_writer;
			auto_type_writer< CT_DuotoneEffect_writer > _duotone_writer;
			auto_type_writer< CT_FillEffect_writer > _fill_writer;
			auto_type_writer< CT_FillOverlayEffect_writer > _fillOverlay_writer;
			auto_type_writer< CT_GlowEffect_writer > _glow_writer;
			auto_type_writer< CT_GrayscaleEffect_writer > _grayscl_writer;
			auto_type_writer< CT_HSLEffect_writer > _hsl_writer;
			auto_type_writer< CT_InnerShadowEffect_writer > _innerShdw_writer;
			auto_type_writer< CT_LuminanceEffect_writer > _lum_writer;
			auto_type_writer< CT_OuterShadowEffect_writer > _outerShdw_writer;
			auto_type_writer< CT_PresetShadowEffect_writer > _prstShdw_writer;
			auto_type_writer< CT_ReflectionEffect_writer > _reflection_writer;
			auto_type_writer< CT_RelativeOffsetEffect_writer > _relOff_writer;
			auto_type_writer< CT_SoftEdgesEffect_writer > _softEdge_writer;
			auto_type_writer< CT_TintEffect_writer > _tint_writer;
			auto_type_writer< CT_TransformEffect_writer > _xfrm_writer;
			CT_EffectContainer* t() { return static_cast<CT_EffectContainer*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_AlphaModulateEffect_writer : public type_writer
		{
			auto_type_writer< CT_EffectContainer_writer > _cont_writer;
			CT_AlphaModulateEffect* t() { return static_cast<CT_AlphaModulateEffect*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Blip_writer : public type_writer
		{
			auto_type_writer< CT_AlphaBiLevelEffect_writer > _alphaBiLevel_writer;
			auto_type_writer< CT_AlphaCeilingEffect_writer > _alphaCeiling_writer;
			auto_type_writer< CT_AlphaFloorEffect_writer > _alphaFloor_writer;
			auto_type_writer< CT_AlphaInverseEffect_writer > _alphaInv_writer;
			auto_type_writer< CT_AlphaModulateEffect_writer > _alphaMod_writer;
			auto_type_writer< CT_AlphaModulateFixedEffect_writer > _alphaModFix_writer;
			auto_type_writer< CT_AlphaReplaceEffect_writer > _alphaRepl_writer;
			auto_type_writer< CT_BiLevelEffect_writer > _biLevel_writer;
			auto_type_writer< CT_BlurEffect_writer > _blur_writer;
			auto_type_writer< CT_ColorChangeEffect_writer > _clrChange_writer;
			auto_type_writer< CT_ColorReplaceEffect_writer > _clrRepl_writer;
			auto_type_writer< CT_DuotoneEffect_writer > _duotone_writer;
			auto_type_writer< CT_FillOverlayEffect_writer > _fillOverlay_writer;
			auto_type_writer< CT_GrayscaleEffect_writer > _grayscl_writer;
			auto_type_writer< CT_HSLEffect_writer > _hsl_writer;
			auto_type_writer< CT_LuminanceEffect_writer > _lum_writer;
			auto_type_writer< CT_TintEffect_writer > _tint_writer;
			auto_type_writer< CT_OfficeArtExtensionList_writer > _extLst_writer;
			CT_Blip* t() { return static_cast<CT_Blip*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_EffectList_writer : public type_writer
		{
			auto_type_writer< CT_BlurEffect_writer > _blur_writer;
			auto_type_writer< CT_FillOverlayEffect_writer > _fillOverlay_writer;
			auto_type_writer< CT_GlowEffect_writer > _glow_writer;
			auto_type_writer< CT_InnerShadowEffect_writer > _innerShdw_writer;
			auto_type_writer< CT_OuterShadowEffect_writer > _outerShdw_writer;
			auto_type_writer< CT_PresetShadowEffect_writer > _prstShdw_writer;
			auto_type_writer< CT_ReflectionEffect_writer > _reflection_writer;
			auto_type_writer< CT_SoftEdgesEffect_writer > _softEdge_writer;
			CT_EffectList* t() { return static_cast<CT_EffectList*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class dml_shapeEffects_writer : public type_writer
		{
			auto_type_writer< CT_Blip_writer > _blip_writer;
			dml_shapeEffects* t() { return static_cast<dml_shapeEffects*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_FillProperties_writer : public type_writer
		{
			auto_type_writer< CT_NoFillProperties_writer > _noFill_writer;
			auto_type_writer< CT_SolidColorFillProperties_writer > _solidFill_writer;
			auto_type_writer< CT_GradientFillProperties_writer > _gradFill_writer;
			auto_type_writer< CT_BlipFillProperties_writer > _blipFill_writer;
			auto_type_writer< CT_PatternFillProperties_writer > _pattFill_writer;
			auto_type_writer< CT_GroupFillProperties_writer > _grpFill_writer;
			CT_FillProperties* t() { return static_cast<CT_FillProperties*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_EffectProperties_writer : public type_writer
		{
			auto_type_writer< CT_EffectList_writer > _effectLst_writer;
			auto_type_writer< CT_EffectContainer_writer > _effectDag_writer;
			CT_EffectProperties* t() { return static_cast<CT_EffectProperties*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_BlendEffect_writer : public type_writer
		{
			auto_type_writer< CT_EffectContainer_writer > _cont_writer;
			CT_BlendEffect* t() { return static_cast<CT_BlendEffect*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

	}
}
#endif

