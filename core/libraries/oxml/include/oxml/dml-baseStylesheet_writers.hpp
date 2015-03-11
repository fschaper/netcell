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

#ifndef DML_BASESTYLESHEET_WRITERS_HPP
#define DML_BASESTYLESHEET_WRITERS_HPP

#include "dml-baseStylesheet.hpp"
#include "dml-baseStylesheet_literals.hpp"
#include "dml-baseTypes_writers.hpp"
#include "dml-textCharacter_writers.hpp"
#include "dml-shapeEffects_writers.hpp"
#include "dml-shapeLineProperties_writers.hpp"
#include "dml-shape3DScene_writers.hpp"
#include "dml-shape3DStyles_writers.hpp"

namespace drawingml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class ST_StyleMatrixColumnIndex_writer;
		class CT_ColorScheme_writer;
		class CT_SupplementalFont_writer;
		class CT_FontCollection_writer;
		class CT_FontScheme_writer;
		class CT_FillStyleList_writer;
		class CT_LineStyleList_writer;
		class CT_EffectStyleItem_writer;
		class CT_EffectStyleList_writer;
		class CT_BackgroundFillStyleList_writer;
		class CT_StyleMatrix_writer;
		class CT_BaseStyles_writer;
		class CT_CustomColor_writer;
		class CT_CustomColorList_writer;

		class ST_StyleMatrixColumnIndex_writer : public type_writer
		{
			ST_StyleMatrixColumnIndex* t() { return static_cast<ST_StyleMatrixColumnIndex*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_ColorScheme_writer : public type_writer
		{
			auto_type_writer< CT_Color_writer > _dk1_writer;
			auto_type_writer< CT_Color_writer > _lt1_writer;
			auto_type_writer< CT_Color_writer > _dk2_writer;
			auto_type_writer< CT_Color_writer > _lt2_writer;
			auto_type_writer< CT_Color_writer > _accent1_writer;
			auto_type_writer< CT_Color_writer > _accent2_writer;
			auto_type_writer< CT_Color_writer > _accent3_writer;
			auto_type_writer< CT_Color_writer > _accent4_writer;
			auto_type_writer< CT_Color_writer > _accent5_writer;
			auto_type_writer< CT_Color_writer > _accent6_writer;
			auto_type_writer< CT_Color_writer > _hlink_writer;
			auto_type_writer< CT_Color_writer > _folHlink_writer;
			auto_type_writer< CT_OfficeArtExtensionList_writer > _extLst_writer;
			CT_ColorScheme* t() { return static_cast<CT_ColorScheme*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_SupplementalFont_writer : public type_writer
		{
			CT_SupplementalFont* t() { return static_cast<CT_SupplementalFont*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_FontCollection_writer : public type_writer
		{
			auto_type_writer< CT_TextFont_writer > _latin_writer;
			auto_type_writer< CT_TextFont_writer > _ea_writer;
			auto_type_writer< CT_TextFont_writer > _cs_writer;
			auto_type_writer< CT_SupplementalFont_writer > _font_writer;
			auto_type_writer< CT_OfficeArtExtensionList_writer > _extLst_writer;
			CT_FontCollection* t() { return static_cast<CT_FontCollection*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_FontScheme_writer : public type_writer
		{
			auto_type_writer< CT_FontCollection_writer > _majorFont_writer;
			auto_type_writer< CT_FontCollection_writer > _minorFont_writer;
			auto_type_writer< CT_OfficeArtExtensionList_writer > _extLst_writer;
			CT_FontScheme* t() { return static_cast<CT_FontScheme*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_FillStyleList_writer : public type_writer
		{
			auto_type_writer< CT_NoFillProperties_writer > _noFill_writer;
			auto_type_writer< CT_SolidColorFillProperties_writer > _solidFill_writer;
			auto_type_writer< CT_GradientFillProperties_writer > _gradFill_writer;
			auto_type_writer< CT_BlipFillProperties_writer > _blipFill_writer;
			auto_type_writer< CT_PatternFillProperties_writer > _pattFill_writer;
			auto_type_writer< CT_GroupFillProperties_writer > _grpFill_writer;
			CT_FillStyleList* t() { return static_cast<CT_FillStyleList*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_LineStyleList_writer : public type_writer
		{
			auto_type_writer< CT_LineProperties_writer > _ln_writer;
			CT_LineStyleList* t() { return static_cast<CT_LineStyleList*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_EffectStyleItem_writer : public type_writer
		{
			auto_type_writer< CT_EffectList_writer > _effectLst_writer;
			auto_type_writer< CT_EffectContainer_writer > _effectDag_writer;
			auto_type_writer< CT_Scene3D_writer > _scene3d_writer;
			auto_type_writer< CT_Shape3D_writer > _sp3d_writer;
			CT_EffectStyleItem* t() { return static_cast<CT_EffectStyleItem*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_EffectStyleList_writer : public type_writer
		{
			auto_type_writer< CT_EffectStyleItem_writer > _effectStyle_writer;
			CT_EffectStyleList* t() { return static_cast<CT_EffectStyleList*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_BackgroundFillStyleList_writer : public type_writer
		{
			auto_type_writer< CT_NoFillProperties_writer > _noFill_writer;
			auto_type_writer< CT_SolidColorFillProperties_writer > _solidFill_writer;
			auto_type_writer< CT_GradientFillProperties_writer > _gradFill_writer;
			auto_type_writer< CT_BlipFillProperties_writer > _blipFill_writer;
			auto_type_writer< CT_PatternFillProperties_writer > _pattFill_writer;
			auto_type_writer< CT_GroupFillProperties_writer > _grpFill_writer;
			CT_BackgroundFillStyleList* t() { return static_cast<CT_BackgroundFillStyleList*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_StyleMatrix_writer : public type_writer
		{
			auto_type_writer< CT_FillStyleList_writer > _fillStyleLst_writer;
			auto_type_writer< CT_LineStyleList_writer > _lnStyleLst_writer;
			auto_type_writer< CT_EffectStyleList_writer > _effectStyleLst_writer;
			auto_type_writer< CT_BackgroundFillStyleList_writer > _bgFillStyleLst_writer;
			CT_StyleMatrix* t() { return static_cast<CT_StyleMatrix*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_BaseStyles_writer : public type_writer
		{
			auto_type_writer< CT_ColorScheme_writer > _clrScheme_writer;
			auto_type_writer< CT_FontScheme_writer > _fontScheme_writer;
			auto_type_writer< CT_StyleMatrix_writer > _fmtScheme_writer;
			auto_type_writer< CT_OfficeArtExtensionList_writer > _extLst_writer;
			CT_BaseStyles* t() { return static_cast<CT_BaseStyles*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_CustomColor_writer : public type_writer
		{
			auto_type_writer< CT_ScRgbColor_writer > _scrgbClr_writer;
			auto_type_writer< CT_SRgbColor_writer > _srgbClr_writer;
			auto_type_writer< CT_HslColor_writer > _hslClr_writer;
			auto_type_writer< CT_SystemColor_writer > _sysClr_writer;
			auto_type_writer< CT_SchemeColor_writer > _schemeClr_writer;
			auto_type_writer< CT_PresetColor_writer > _prstClr_writer;
			CT_CustomColor* t() { return static_cast<CT_CustomColor*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_CustomColorList_writer : public type_writer
		{
			auto_type_writer< CT_CustomColor_writer > _custClr_writer;
			CT_CustomColorList* t() { return static_cast<CT_CustomColorList*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

	}
}
#endif

