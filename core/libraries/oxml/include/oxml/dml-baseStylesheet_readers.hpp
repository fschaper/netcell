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

#ifndef DML_BASESTYLESHEET_READERS_HPP
#define DML_BASESTYLESHEET_READERS_HPP

#include "dml-baseStylesheet.hpp"
#include "dml-baseTypes_readers.hpp"
#include "dml-textCharacter_readers.hpp"
#include "dml-shapeEffects_readers.hpp"
#include "dml-shapeLineProperties_readers.hpp"
#include "dml-shape3DScene_readers.hpp"
#include "dml-shape3DStyles_readers.hpp"

namespace drawingml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class ST_StyleMatrixColumnIndex_reader;
		class CT_ColorScheme_reader;
		class CT_SupplementalFont_reader;
		class CT_FontCollection_reader;
		class CT_FontScheme_reader;
		class CT_FillStyleList_reader;
		class CT_LineStyleList_reader;
		class CT_EffectStyleItem_reader;
		class CT_EffectStyleList_reader;
		class CT_BackgroundFillStyleList_reader;
		class CT_StyleMatrix_reader;
		class CT_BaseStyles_reader;
		class CT_CustomColor_reader;
		class CT_CustomColorList_reader;

		class ST_StyleMatrixColumnIndex_reader : public type_reader
		{
		protected:
			ST_StyleMatrixColumnIndex* t() { return static_cast<ST_StyleMatrixColumnIndex*>(target()); }
			void read_value(const xstring& val);
		};

		class CT_ColorScheme_reader : public type_reader
		{
			auto_type_reader< CT_Color_reader > _dk1_reader;
			auto_type_reader< CT_Color_reader > _lt1_reader;
			auto_type_reader< CT_Color_reader > _dk2_reader;
			auto_type_reader< CT_Color_reader > _lt2_reader;
			auto_type_reader< CT_Color_reader > _accent1_reader;
			auto_type_reader< CT_Color_reader > _accent2_reader;
			auto_type_reader< CT_Color_reader > _accent3_reader;
			auto_type_reader< CT_Color_reader > _accent4_reader;
			auto_type_reader< CT_Color_reader > _accent5_reader;
			auto_type_reader< CT_Color_reader > _accent6_reader;
			auto_type_reader< CT_Color_reader > _hlink_reader;
			auto_type_reader< CT_Color_reader > _folHlink_reader;
			auto_type_reader< CT_OfficeArtExtensionList_reader > _extLst_reader;
		protected:
			CT_ColorScheme* t() { return static_cast<CT_ColorScheme*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_SupplementalFont_reader : public type_reader
		{
		protected:
			CT_SupplementalFont* t() { return static_cast<CT_SupplementalFont*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_FontCollection_reader : public type_reader
		{
			auto_type_reader< CT_TextFont_reader > _latin_reader;
			auto_type_reader< CT_TextFont_reader > _ea_reader;
			auto_type_reader< CT_TextFont_reader > _cs_reader;
			auto_type_reader< CT_SupplementalFont_reader > _font_reader;
			auto_type_reader< CT_OfficeArtExtensionList_reader > _extLst_reader;
		protected:
			CT_FontCollection* t() { return static_cast<CT_FontCollection*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_FontScheme_reader : public type_reader
		{
			auto_type_reader< CT_FontCollection_reader > _majorFont_reader;
			auto_type_reader< CT_FontCollection_reader > _minorFont_reader;
			auto_type_reader< CT_OfficeArtExtensionList_reader > _extLst_reader;
		protected:
			CT_FontScheme* t() { return static_cast<CT_FontScheme*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_FillStyleList_reader : public type_reader
		{
			auto_type_reader< CT_NoFillProperties_reader > _noFill_reader;
			auto_type_reader< CT_SolidColorFillProperties_reader > _solidFill_reader;
			auto_type_reader< CT_GradientFillProperties_reader > _gradFill_reader;
			auto_type_reader< CT_BlipFillProperties_reader > _blipFill_reader;
			auto_type_reader< CT_PatternFillProperties_reader > _pattFill_reader;
			auto_type_reader< CT_GroupFillProperties_reader > _grpFill_reader;
		protected:
			CT_FillStyleList* t() { return static_cast<CT_FillStyleList*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_LineStyleList_reader : public type_reader
		{
			auto_type_reader< CT_LineProperties_reader > _ln_reader;
		protected:
			CT_LineStyleList* t() { return static_cast<CT_LineStyleList*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_EffectStyleItem_reader : public type_reader
		{
			auto_type_reader< CT_EffectList_reader > _effectLst_reader;
			auto_type_reader< CT_EffectContainer_reader > _effectDag_reader;
			auto_type_reader< CT_Scene3D_reader > _scene3d_reader;
			auto_type_reader< CT_Shape3D_reader > _sp3d_reader;
		protected:
			CT_EffectStyleItem* t() { return static_cast<CT_EffectStyleItem*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_EffectStyleList_reader : public type_reader
		{
			auto_type_reader< CT_EffectStyleItem_reader > _effectStyle_reader;
		protected:
			CT_EffectStyleList* t() { return static_cast<CT_EffectStyleList*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_BackgroundFillStyleList_reader : public type_reader
		{
			auto_type_reader< CT_NoFillProperties_reader > _noFill_reader;
			auto_type_reader< CT_SolidColorFillProperties_reader > _solidFill_reader;
			auto_type_reader< CT_GradientFillProperties_reader > _gradFill_reader;
			auto_type_reader< CT_BlipFillProperties_reader > _blipFill_reader;
			auto_type_reader< CT_PatternFillProperties_reader > _pattFill_reader;
			auto_type_reader< CT_GroupFillProperties_reader > _grpFill_reader;
		protected:
			CT_BackgroundFillStyleList* t() { return static_cast<CT_BackgroundFillStyleList*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_StyleMatrix_reader : public type_reader
		{
			auto_type_reader< CT_FillStyleList_reader > _fillStyleLst_reader;
			auto_type_reader< CT_LineStyleList_reader > _lnStyleLst_reader;
			auto_type_reader< CT_EffectStyleList_reader > _effectStyleLst_reader;
			auto_type_reader< CT_BackgroundFillStyleList_reader > _bgFillStyleLst_reader;
		protected:
			CT_StyleMatrix* t() { return static_cast<CT_StyleMatrix*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_BaseStyles_reader : public type_reader
		{
			auto_type_reader< CT_ColorScheme_reader > _clrScheme_reader;
			auto_type_reader< CT_FontScheme_reader > _fontScheme_reader;
			auto_type_reader< CT_StyleMatrix_reader > _fmtScheme_reader;
			auto_type_reader< CT_OfficeArtExtensionList_reader > _extLst_reader;
		protected:
			CT_BaseStyles* t() { return static_cast<CT_BaseStyles*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_CustomColor_reader : public type_reader
		{
			auto_type_reader< CT_ScRgbColor_reader > _scrgbClr_reader;
			auto_type_reader< CT_SRgbColor_reader > _srgbClr_reader;
			auto_type_reader< CT_HslColor_reader > _hslClr_reader;
			auto_type_reader< CT_SystemColor_reader > _sysClr_reader;
			auto_type_reader< CT_SchemeColor_reader > _schemeClr_reader;
			auto_type_reader< CT_PresetColor_reader > _prstClr_reader;
		protected:
			CT_CustomColor* t() { return static_cast<CT_CustomColor*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_CustomColorList_reader : public type_reader
		{
			auto_type_reader< CT_CustomColor_reader > _custClr_reader;
		protected:
			CT_CustomColorList* t() { return static_cast<CT_CustomColorList*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

	}
}
#endif

