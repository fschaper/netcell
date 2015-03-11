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


#include "dml-baseStylesheet_readers.hpp"
#include "dml-baseStylesheet_literals.hpp"
#include <xio/xml/binding/driver.hpp>

namespace drawingml
{
	namespace xio
	{
		void ST_StyleMatrixColumnIndex_reader::read_value(const xstring& val) {{ driver()->context()->parse(val, *t()); }}
		void CT_ColorScheme_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_dk1_literal))
			{
				driver()->push(localname, _dk1_reader.get_reader(&t()->dk1));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_lt1_literal))
			{
				driver()->push(localname, _lt1_reader.get_reader(&t()->lt1));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_dk2_literal))
			{
				driver()->push(localname, _dk2_reader.get_reader(&t()->dk2));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_lt2_literal))
			{
				driver()->push(localname, _lt2_reader.get_reader(&t()->lt2));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_accent1_literal))
			{
				driver()->push(localname, _accent1_reader.get_reader(&t()->accent1));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_accent2_literal))
			{
				driver()->push(localname, _accent2_reader.get_reader(&t()->accent2));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_accent3_literal))
			{
				driver()->push(localname, _accent3_reader.get_reader(&t()->accent3));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_accent4_literal))
			{
				driver()->push(localname, _accent4_reader.get_reader(&t()->accent4));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_accent5_literal))
			{
				driver()->push(localname, _accent5_reader.get_reader(&t()->accent5));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_accent6_literal))
			{
				driver()->push(localname, _accent6_reader.get_reader(&t()->accent6));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_hlink_literal))
			{
				driver()->push(localname, _hlink_reader.get_reader(&t()->hlink));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_folHlink_literal))
			{
				driver()->push(localname, _folHlink_reader.get_reader(&t()->folHlink));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_ColorScheme_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_name_literal))
			{
				driver()->context()->parse(value, t()->name);
				return;
			}
		}
		void CT_SupplementalFont_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_script_literal))
			{
				driver()->context()->parse(value, t()->script);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_typeface_literal))
			{
				driver()->context()->parse(value, t()->typeface);
				return;
			}
		}
		void CT_FontCollection_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_latin_literal))
			{
				driver()->push(localname, _latin_reader.get_reader(&t()->latin));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_ea_literal))
			{
				driver()->push(localname, _ea_reader.get_reader(&t()->ea));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_cs_literal))
			{
				driver()->push(localname, _cs_reader.get_reader(&t()->cs));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_font_literal))
			{
				t()->font.resize(t()->font.size()+1);
				driver()->push(localname, _font_reader.get_reader(&t()->font.back()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_FontScheme_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_majorFont_literal))
			{
				driver()->push(localname, _majorFont_reader.get_reader(&t()->majorFont));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_minorFont_literal))
			{
				driver()->push(localname, _minorFont_reader.get_reader(&t()->minorFont));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_FontScheme_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_name_literal))
			{
				driver()->context()->parse(value, t()->name);
				return;
			}
		}
		void CT_FillStyleList_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_noFill_literal))
			{
				driver()->push(localname, _noFill_reader.get_reader(&t()->noFill.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_solidFill_literal))
			{
				driver()->push(localname, _solidFill_reader.get_reader(&t()->solidFill.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_gradFill_literal))
			{
				driver()->push(localname, _gradFill_reader.get_reader(&t()->gradFill.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_blipFill_literal))
			{
				driver()->push(localname, _blipFill_reader.get_reader(&t()->blipFill.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_pattFill_literal))
			{
				driver()->push(localname, _pattFill_reader.get_reader(&t()->pattFill.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_grpFill_literal))
			{
				driver()->push(localname, _grpFill_reader.get_reader(&t()->grpFill.getset()));
				return;
			}
		}
		void CT_LineStyleList_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_ln_literal))
			{
				t()->ln.resize(t()->ln.size()+1);
				driver()->push(localname, _ln_reader.get_reader(&t()->ln.back()));
				return;
			}
		}
		void CT_EffectStyleItem_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_effectLst_literal))
			{
				driver()->push(localname, _effectLst_reader.get_reader(&t()->effectLst.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_effectDag_literal))
			{
				driver()->push(localname, _effectDag_reader.get_reader(&t()->effectDag.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_scene3d_literal))
			{
				driver()->push(localname, _scene3d_reader.get_reader(&t()->scene3d.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_sp3d_literal))
			{
				driver()->push(localname, _sp3d_reader.get_reader(&t()->sp3d.getset()));
				return;
			}
		}
		void CT_EffectStyleList_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_effectStyle_literal))
			{
				t()->effectStyle.resize(t()->effectStyle.size()+1);
				driver()->push(localname, _effectStyle_reader.get_reader(&t()->effectStyle.back()));
				return;
			}
		}
		void CT_BackgroundFillStyleList_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_noFill_literal))
			{
				driver()->push(localname, _noFill_reader.get_reader(&t()->noFill.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_solidFill_literal))
			{
				driver()->push(localname, _solidFill_reader.get_reader(&t()->solidFill.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_gradFill_literal))
			{
				driver()->push(localname, _gradFill_reader.get_reader(&t()->gradFill.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_blipFill_literal))
			{
				driver()->push(localname, _blipFill_reader.get_reader(&t()->blipFill.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_pattFill_literal))
			{
				driver()->push(localname, _pattFill_reader.get_reader(&t()->pattFill.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_grpFill_literal))
			{
				driver()->push(localname, _grpFill_reader.get_reader(&t()->grpFill.getset()));
				return;
			}
		}
		void CT_StyleMatrix_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_fillStyleLst_literal))
			{
				driver()->push(localname, _fillStyleLst_reader.get_reader(&t()->fillStyleLst));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_lnStyleLst_literal))
			{
				driver()->push(localname, _lnStyleLst_reader.get_reader(&t()->lnStyleLst));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_effectStyleLst_literal))
			{
				driver()->push(localname, _effectStyleLst_reader.get_reader(&t()->effectStyleLst));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_bgFillStyleLst_literal))
			{
				driver()->push(localname, _bgFillStyleLst_reader.get_reader(&t()->bgFillStyleLst));
				return;
			}
		}
		void CT_StyleMatrix_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_name_literal))
			{
				driver()->context()->parse(value, t()->name);
				return;
			}
		}
		void CT_BaseStyles_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_clrScheme_literal))
			{
				driver()->push(localname, _clrScheme_reader.get_reader(&t()->clrScheme));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_fontScheme_literal))
			{
				driver()->push(localname, _fontScheme_reader.get_reader(&t()->fontScheme));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_fmtScheme_literal))
			{
				driver()->push(localname, _fmtScheme_reader.get_reader(&t()->fmtScheme));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_CustomColor_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_scrgbClr_literal))
			{
				driver()->push(localname, _scrgbClr_reader.get_reader(&t()->scrgbClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_srgbClr_literal))
			{
				driver()->push(localname, _srgbClr_reader.get_reader(&t()->srgbClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_hslClr_literal))
			{
				driver()->push(localname, _hslClr_reader.get_reader(&t()->hslClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_sysClr_literal))
			{
				driver()->push(localname, _sysClr_reader.get_reader(&t()->sysClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_schemeClr_literal))
			{
				driver()->push(localname, _schemeClr_reader.get_reader(&t()->schemeClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_prstClr_literal))
			{
				driver()->push(localname, _prstClr_reader.get_reader(&t()->prstClr.getset()));
				return;
			}
		}
		void CT_CustomColor_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_name_literal))
			{
				driver()->context()->parse(value, t()->name);
				return;
			}
		}
		void CT_CustomColorList_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_baseStylesheet_custClr_literal))
			{
				t()->custClr.resize(t()->custClr.size()+1);
				driver()->push(localname, _custClr_reader.get_reader(&t()->custClr.back()));
				return;
			}
		}
	}
}
