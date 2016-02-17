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


#include "dml-shapeEffects_readers.hpp"
#include "dml-shapeEffects_literals.hpp"
#include <xio/xml/binding/driver.hpp>

namespace drawingml
{
	namespace xio
	{
		void CT_AlphaBiLevelEffect_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_thresh_literal))
			{
				driver()->context()->parse(value, t()->thresh);
				return;
			}
		}
		void CT_AlphaInverseEffect_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_scrgbClr_literal))
			{
				driver()->push(localname, _scrgbClr_reader.get_reader(&t()->scrgbClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_srgbClr_literal))
			{
				driver()->push(localname, _srgbClr_reader.get_reader(&t()->srgbClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_hslClr_literal))
			{
				driver()->push(localname, _hslClr_reader.get_reader(&t()->hslClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_sysClr_literal))
			{
				driver()->push(localname, _sysClr_reader.get_reader(&t()->sysClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_schemeClr_literal))
			{
				driver()->push(localname, _schemeClr_reader.get_reader(&t()->schemeClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_prstClr_literal))
			{
				driver()->push(localname, _prstClr_reader.get_reader(&t()->prstClr.getset()));
				return;
			}
		}
		void CT_EffectReference_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_ref_literal))
			{
				driver()->context()->parse(value, t()->ref.getset());
				return;
			}
		}
		void CT_AlphaModulateFixedEffect_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_amt_literal))
			{
				driver()->context()->parse(value, t()->amt);
				return;
			}
		}
		void CT_AlphaOutsetEffect_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_rad_literal))
			{
				driver()->context()->parse(value, t()->rad);
				return;
			}
		}
		void CT_AlphaReplaceEffect_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_a_literal))
			{
				driver()->context()->parse(value, t()->a);
				return;
			}
		}
		void CT_BiLevelEffect_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_thresh_literal))
			{
				driver()->context()->parse(value, t()->thresh);
				return;
			}
		}
		void CT_BlurEffect_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_rad_literal))
			{
				driver()->context()->parse(value, t()->rad);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_grow_literal))
			{
				driver()->context()->parse(value, t()->grow);
				return;
			}
		}
		void CT_ColorChangeEffect_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_clrFrom_literal))
			{
				driver()->push(localname, _clrFrom_reader.get_reader(&t()->clrFrom));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_clrTo_literal))
			{
				driver()->push(localname, _clrTo_reader.get_reader(&t()->clrTo));
				return;
			}
		}
		void CT_ColorChangeEffect_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_useA_literal))
			{
				driver()->context()->parse(value, t()->useA);
				return;
			}
		}
		void CT_ColorReplaceEffect_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_scrgbClr_literal))
			{
				driver()->push(localname, _scrgbClr_reader.get_reader(&t()->scrgbClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_srgbClr_literal))
			{
				driver()->push(localname, _srgbClr_reader.get_reader(&t()->srgbClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_hslClr_literal))
			{
				driver()->push(localname, _hslClr_reader.get_reader(&t()->hslClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_sysClr_literal))
			{
				driver()->push(localname, _sysClr_reader.get_reader(&t()->sysClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_schemeClr_literal))
			{
				driver()->push(localname, _schemeClr_reader.get_reader(&t()->schemeClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_prstClr_literal))
			{
				driver()->push(localname, _prstClr_reader.get_reader(&t()->prstClr.getset()));
				return;
			}
		}
		void CT_DuotoneEffect_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_scrgbClr_literal))
			{
				driver()->push(localname, _scrgbClr_reader.get_reader(&t()->scrgbClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_srgbClr_literal))
			{
				driver()->push(localname, _srgbClr_reader.get_reader(&t()->srgbClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_hslClr_literal))
			{
				driver()->push(localname, _hslClr_reader.get_reader(&t()->hslClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_sysClr_literal))
			{
				driver()->push(localname, _sysClr_reader.get_reader(&t()->sysClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_schemeClr_literal))
			{
				driver()->push(localname, _schemeClr_reader.get_reader(&t()->schemeClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_prstClr_literal))
			{
				driver()->push(localname, _prstClr_reader.get_reader(&t()->prstClr.getset()));
				return;
			}
		}
		void CT_SolidColorFillProperties_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_scrgbClr_literal))
			{
				driver()->push(localname, _scrgbClr_reader.get_reader(&t()->scrgbClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_srgbClr_literal))
			{
				driver()->push(localname, _srgbClr_reader.get_reader(&t()->srgbClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_hslClr_literal))
			{
				driver()->push(localname, _hslClr_reader.get_reader(&t()->hslClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_sysClr_literal))
			{
				driver()->push(localname, _sysClr_reader.get_reader(&t()->sysClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_schemeClr_literal))
			{
				driver()->push(localname, _schemeClr_reader.get_reader(&t()->schemeClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_prstClr_literal))
			{
				driver()->push(localname, _prstClr_reader.get_reader(&t()->prstClr.getset()));
				return;
			}
		}
		void CT_GradientStop_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_scrgbClr_literal))
			{
				driver()->push(localname, _scrgbClr_reader.get_reader(&t()->scrgbClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_srgbClr_literal))
			{
				driver()->push(localname, _srgbClr_reader.get_reader(&t()->srgbClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_hslClr_literal))
			{
				driver()->push(localname, _hslClr_reader.get_reader(&t()->hslClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_sysClr_literal))
			{
				driver()->push(localname, _sysClr_reader.get_reader(&t()->sysClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_schemeClr_literal))
			{
				driver()->push(localname, _schemeClr_reader.get_reader(&t()->schemeClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_prstClr_literal))
			{
				driver()->push(localname, _prstClr_reader.get_reader(&t()->prstClr.getset()));
				return;
			}
		}
		void CT_GradientStop_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_pos_literal))
			{
				driver()->context()->parse(value, t()->pos);
				return;
			}
		}
		void CT_GradientStopList_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_gs_literal))
			{
				t()->gs.resize(t()->gs.size()+1);
				driver()->push(localname, _gs_reader.get_reader(&t()->gs.back()));
				return;
			}
		}
		void CT_LinearShadeProperties_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_ang_literal))
			{
				driver()->context()->parse(value, t()->ang.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_scaled_literal))
			{
				driver()->context()->parse(value, t()->scaled.getset());
				return;
			}
		}
		void CT_PathShadeProperties_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_fillToRect_literal))
			{
				driver()->push(localname, _fillToRect_reader.get_reader(&t()->fillToRect.getset()));
				return;
			}
		}
		void CT_PathShadeProperties_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_path_literal))
			{
				driver()->context()->parse(value, t()->path.getset());
				return;
			}
		}
		void CT_GradientFillProperties_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_gsLst_literal))
			{
				driver()->push(localname, _gsLst_reader.get_reader(&t()->gsLst.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_lin_literal))
			{
				driver()->push(localname, _lin_reader.get_reader(&t()->lin.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_path_literal))
			{
				driver()->push(localname, _path_reader.get_reader(&t()->path.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_tileRect_literal))
			{
				driver()->push(localname, _tileRect_reader.get_reader(&t()->tileRect.getset()));
				return;
			}
		}
		void CT_GradientFillProperties_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_flip_literal))
			{
				driver()->context()->parse(value, t()->flip.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_rotWithShape_literal))
			{
				driver()->context()->parse(value, t()->rotWithShape.getset());
				return;
			}
		}
		void CT_TileInfoProperties_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_tx_literal))
			{
				driver()->context()->parse(value, t()->tx.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_ty_literal))
			{
				driver()->context()->parse(value, t()->ty.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_sx_literal))
			{
				driver()->context()->parse(value, t()->sx.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_sy_literal))
			{
				driver()->context()->parse(value, t()->sy.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_flip_literal))
			{
				driver()->context()->parse(value, t()->flip.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_algn_literal))
			{
				driver()->context()->parse(value, t()->algn.getset());
				return;
			}
		}
		void CT_StretchInfoProperties_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_fillRect_literal))
			{
				driver()->push(localname, _fillRect_reader.get_reader(&t()->fillRect.getset()));
				return;
			}
		}
		void CT_BlipFillProperties_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_blip_literal))
			{
				driver()->push(localname, _blip_reader.get_reader(&t()->blip.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_srcRect_literal))
			{
				driver()->push(localname, _srcRect_reader.get_reader(&t()->srcRect.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_tile_literal))
			{
				driver()->push(localname, _tile_reader.get_reader(&t()->tile.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_stretch_literal))
			{
				driver()->push(localname, _stretch_reader.get_reader(&t()->stretch.getset()));
				return;
			}
		}
		void CT_BlipFillProperties_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_dpi_literal))
			{
				driver()->context()->parse(value, t()->dpi.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_rotWithShape_literal))
			{
				driver()->context()->parse(value, t()->rotWithShape.getset());
				return;
			}
		}
		void CT_PatternFillProperties_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_fgClr_literal))
			{
				driver()->push(localname, _fgClr_reader.get_reader(&t()->fgClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_bgClr_literal))
			{
				driver()->push(localname, _bgClr_reader.get_reader(&t()->bgClr.getset()));
				return;
			}
		}
		void CT_PatternFillProperties_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_prst_literal))
			{
				driver()->context()->parse(value, t()->prst.getset());
				return;
			}
		}
		void CT_FillEffect_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_noFill_literal))
			{
				driver()->push(localname, _noFill_reader.get_reader(&t()->noFill.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_solidFill_literal))
			{
				driver()->push(localname, _solidFill_reader.get_reader(&t()->solidFill.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_gradFill_literal))
			{
				driver()->push(localname, _gradFill_reader.get_reader(&t()->gradFill.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_blipFill_literal))
			{
				driver()->push(localname, _blipFill_reader.get_reader(&t()->blipFill.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_pattFill_literal))
			{
				driver()->push(localname, _pattFill_reader.get_reader(&t()->pattFill.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_grpFill_literal))
			{
				driver()->push(localname, _grpFill_reader.get_reader(&t()->grpFill.getset()));
				return;
			}
		}
		void CT_FillOverlayEffect_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_noFill_literal))
			{
				driver()->push(localname, _noFill_reader.get_reader(&t()->noFill.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_solidFill_literal))
			{
				driver()->push(localname, _solidFill_reader.get_reader(&t()->solidFill.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_gradFill_literal))
			{
				driver()->push(localname, _gradFill_reader.get_reader(&t()->gradFill.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_blipFill_literal))
			{
				driver()->push(localname, _blipFill_reader.get_reader(&t()->blipFill.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_pattFill_literal))
			{
				driver()->push(localname, _pattFill_reader.get_reader(&t()->pattFill.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_grpFill_literal))
			{
				driver()->push(localname, _grpFill_reader.get_reader(&t()->grpFill.getset()));
				return;
			}
		}
		void CT_FillOverlayEffect_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_blend_literal))
			{
				driver()->context()->parse(value, t()->blend);
				return;
			}
		}
		void CT_GlowEffect_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_scrgbClr_literal))
			{
				driver()->push(localname, _scrgbClr_reader.get_reader(&t()->scrgbClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_srgbClr_literal))
			{
				driver()->push(localname, _srgbClr_reader.get_reader(&t()->srgbClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_hslClr_literal))
			{
				driver()->push(localname, _hslClr_reader.get_reader(&t()->hslClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_sysClr_literal))
			{
				driver()->push(localname, _sysClr_reader.get_reader(&t()->sysClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_schemeClr_literal))
			{
				driver()->push(localname, _schemeClr_reader.get_reader(&t()->schemeClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_prstClr_literal))
			{
				driver()->push(localname, _prstClr_reader.get_reader(&t()->prstClr.getset()));
				return;
			}
		}
		void CT_GlowEffect_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_rad_literal))
			{
				driver()->context()->parse(value, t()->rad);
				return;
			}
		}
		void CT_HSLEffect_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_hue_literal))
			{
				driver()->context()->parse(value, t()->hue);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_sat_literal))
			{
				driver()->context()->parse(value, t()->sat);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_lum_literal))
			{
				driver()->context()->parse(value, t()->lum);
				return;
			}
		}
		void CT_InnerShadowEffect_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_scrgbClr_literal))
			{
				driver()->push(localname, _scrgbClr_reader.get_reader(&t()->scrgbClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_srgbClr_literal))
			{
				driver()->push(localname, _srgbClr_reader.get_reader(&t()->srgbClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_hslClr_literal))
			{
				driver()->push(localname, _hslClr_reader.get_reader(&t()->hslClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_sysClr_literal))
			{
				driver()->push(localname, _sysClr_reader.get_reader(&t()->sysClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_schemeClr_literal))
			{
				driver()->push(localname, _schemeClr_reader.get_reader(&t()->schemeClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_prstClr_literal))
			{
				driver()->push(localname, _prstClr_reader.get_reader(&t()->prstClr.getset()));
				return;
			}
		}
		void CT_InnerShadowEffect_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_blurRad_literal))
			{
				driver()->context()->parse(value, t()->blurRad);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_dist_literal))
			{
				driver()->context()->parse(value, t()->dist);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_dir_literal))
			{
				driver()->context()->parse(value, t()->dir);
				return;
			}
		}
		void CT_LuminanceEffect_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_bright_literal))
			{
				driver()->context()->parse(value, t()->bright);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_contrast_literal))
			{
				driver()->context()->parse(value, t()->contrast);
				return;
			}
		}
		void CT_OuterShadowEffect_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_scrgbClr_literal))
			{
				driver()->push(localname, _scrgbClr_reader.get_reader(&t()->scrgbClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_srgbClr_literal))
			{
				driver()->push(localname, _srgbClr_reader.get_reader(&t()->srgbClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_hslClr_literal))
			{
				driver()->push(localname, _hslClr_reader.get_reader(&t()->hslClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_sysClr_literal))
			{
				driver()->push(localname, _sysClr_reader.get_reader(&t()->sysClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_schemeClr_literal))
			{
				driver()->push(localname, _schemeClr_reader.get_reader(&t()->schemeClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_prstClr_literal))
			{
				driver()->push(localname, _prstClr_reader.get_reader(&t()->prstClr.getset()));
				return;
			}
		}
		void CT_OuterShadowEffect_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_blurRad_literal))
			{
				driver()->context()->parse(value, t()->blurRad);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_dist_literal))
			{
				driver()->context()->parse(value, t()->dist);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_dir_literal))
			{
				driver()->context()->parse(value, t()->dir);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_sx_literal))
			{
				driver()->context()->parse(value, t()->sx);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_sy_literal))
			{
				driver()->context()->parse(value, t()->sy);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_kx_literal))
			{
				driver()->context()->parse(value, t()->kx);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_ky_literal))
			{
				driver()->context()->parse(value, t()->ky);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_algn_literal))
			{
				driver()->context()->parse(value, t()->algn);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_rotWithShape_literal))
			{
				driver()->context()->parse(value, t()->rotWithShape);
				return;
			}
		}
		void CT_PresetShadowEffect_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_scrgbClr_literal))
			{
				driver()->push(localname, _scrgbClr_reader.get_reader(&t()->scrgbClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_srgbClr_literal))
			{
				driver()->push(localname, _srgbClr_reader.get_reader(&t()->srgbClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_hslClr_literal))
			{
				driver()->push(localname, _hslClr_reader.get_reader(&t()->hslClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_sysClr_literal))
			{
				driver()->push(localname, _sysClr_reader.get_reader(&t()->sysClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_schemeClr_literal))
			{
				driver()->push(localname, _schemeClr_reader.get_reader(&t()->schemeClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_prstClr_literal))
			{
				driver()->push(localname, _prstClr_reader.get_reader(&t()->prstClr.getset()));
				return;
			}
		}
		void CT_PresetShadowEffect_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_prst_literal))
			{
				driver()->context()->parse(value, t()->prst);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_dist_literal))
			{
				driver()->context()->parse(value, t()->dist);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_dir_literal))
			{
				driver()->context()->parse(value, t()->dir);
				return;
			}
		}
		void CT_ReflectionEffect_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_blurRad_literal))
			{
				driver()->context()->parse(value, t()->blurRad);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_stA_literal))
			{
				driver()->context()->parse(value, t()->stA);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_stPos_literal))
			{
				driver()->context()->parse(value, t()->stPos);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_endA_literal))
			{
				driver()->context()->parse(value, t()->endA);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_endPos_literal))
			{
				driver()->context()->parse(value, t()->endPos);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_dist_literal))
			{
				driver()->context()->parse(value, t()->dist);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_dir_literal))
			{
				driver()->context()->parse(value, t()->dir);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_fadeDir_literal))
			{
				driver()->context()->parse(value, t()->fadeDir);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_sx_literal))
			{
				driver()->context()->parse(value, t()->sx);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_sy_literal))
			{
				driver()->context()->parse(value, t()->sy);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_kx_literal))
			{
				driver()->context()->parse(value, t()->kx);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_ky_literal))
			{
				driver()->context()->parse(value, t()->ky);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_algn_literal))
			{
				driver()->context()->parse(value, t()->algn);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_rotWithShape_literal))
			{
				driver()->context()->parse(value, t()->rotWithShape);
				return;
			}
		}
		void CT_RelativeOffsetEffect_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_tx_literal))
			{
				driver()->context()->parse(value, t()->tx);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_ty_literal))
			{
				driver()->context()->parse(value, t()->ty);
				return;
			}
		}
		void CT_SoftEdgesEffect_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_rad_literal))
			{
				driver()->context()->parse(value, t()->rad);
				return;
			}
		}
		void CT_TintEffect_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_hue_literal))
			{
				driver()->context()->parse(value, t()->hue);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_amt_literal))
			{
				driver()->context()->parse(value, t()->amt);
				return;
			}
		}
		void CT_TransformEffect_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_sx_literal))
			{
				driver()->context()->parse(value, t()->sx);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_sy_literal))
			{
				driver()->context()->parse(value, t()->sy);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_kx_literal))
			{
				driver()->context()->parse(value, t()->kx);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_ky_literal))
			{
				driver()->context()->parse(value, t()->ky);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_tx_literal))
			{
				driver()->context()->parse(value, t()->tx);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_ty_literal))
			{
				driver()->context()->parse(value, t()->ty);
				return;
			}
		}
		void CT_EffectContainer_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_cont_literal))
			{
				driver()->push(localname, _cont_reader.get_reader(&t()->cont.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_effect_literal))
			{
				driver()->push(localname, _effect_reader.get_reader(&t()->effect.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_alphaBiLevel_literal))
			{
				driver()->push(localname, _alphaBiLevel_reader.get_reader(&t()->alphaBiLevel.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_alphaCeiling_literal))
			{
				driver()->push(localname, _alphaCeiling_reader.get_reader(&t()->alphaCeiling.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_alphaFloor_literal))
			{
				driver()->push(localname, _alphaFloor_reader.get_reader(&t()->alphaFloor.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_alphaInv_literal))
			{
				driver()->push(localname, _alphaInv_reader.get_reader(&t()->alphaInv.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_alphaMod_literal))
			{
				driver()->push(localname, _alphaMod_reader.get_reader(&t()->alphaMod.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_alphaModFix_literal))
			{
				driver()->push(localname, _alphaModFix_reader.get_reader(&t()->alphaModFix.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_alphaOutset_literal))
			{
				driver()->push(localname, _alphaOutset_reader.get_reader(&t()->alphaOutset.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_alphaRepl_literal))
			{
				driver()->push(localname, _alphaRepl_reader.get_reader(&t()->alphaRepl.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_biLevel_literal))
			{
				driver()->push(localname, _biLevel_reader.get_reader(&t()->biLevel.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_blend_literal))
			{
				driver()->push(localname, _blend_reader.get_reader(&t()->blend.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_blur_literal))
			{
				driver()->push(localname, _blur_reader.get_reader(&t()->blur.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_clrChange_literal))
			{
				driver()->push(localname, _clrChange_reader.get_reader(&t()->clrChange.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_clrRepl_literal))
			{
				driver()->push(localname, _clrRepl_reader.get_reader(&t()->clrRepl.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_duotone_literal))
			{
				driver()->push(localname, _duotone_reader.get_reader(&t()->duotone.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_fill_literal))
			{
				driver()->push(localname, _fill_reader.get_reader(&t()->fill.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_fillOverlay_literal))
			{
				driver()->push(localname, _fillOverlay_reader.get_reader(&t()->fillOverlay.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_glow_literal))
			{
				driver()->push(localname, _glow_reader.get_reader(&t()->glow.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_grayscl_literal))
			{
				driver()->push(localname, _grayscl_reader.get_reader(&t()->grayscl.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_hsl_literal))
			{
				driver()->push(localname, _hsl_reader.get_reader(&t()->hsl.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_innerShdw_literal))
			{
				driver()->push(localname, _innerShdw_reader.get_reader(&t()->innerShdw.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_lum_literal))
			{
				driver()->push(localname, _lum_reader.get_reader(&t()->lum.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_outerShdw_literal))
			{
				driver()->push(localname, _outerShdw_reader.get_reader(&t()->outerShdw.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_prstShdw_literal))
			{
				driver()->push(localname, _prstShdw_reader.get_reader(&t()->prstShdw.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_reflection_literal))
			{
				driver()->push(localname, _reflection_reader.get_reader(&t()->reflection.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_relOff_literal))
			{
				driver()->push(localname, _relOff_reader.get_reader(&t()->relOff.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_softEdge_literal))
			{
				driver()->push(localname, _softEdge_reader.get_reader(&t()->softEdge.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_tint_literal))
			{
				driver()->push(localname, _tint_reader.get_reader(&t()->tint.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_xfrm_literal))
			{
				driver()->push(localname, _xfrm_reader.get_reader(&t()->xfrm.getset()));
				return;
			}
		}
		void CT_EffectContainer_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_type_literal))
			{
				driver()->context()->parse(value, t()->type);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_name_literal))
			{
				driver()->context()->parse(value, t()->name.getset());
				return;
			}
		}
		void CT_AlphaModulateEffect_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_cont_literal))
			{
				driver()->push(localname, _cont_reader.get_reader(&t()->cont));
				return;
			}
		}
		void CT_Blip_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_alphaBiLevel_literal))
			{
				driver()->push(localname, _alphaBiLevel_reader.get_reader(&t()->alphaBiLevel.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_alphaCeiling_literal))
			{
				driver()->push(localname, _alphaCeiling_reader.get_reader(&t()->alphaCeiling.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_alphaFloor_literal))
			{
				driver()->push(localname, _alphaFloor_reader.get_reader(&t()->alphaFloor.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_alphaInv_literal))
			{
				driver()->push(localname, _alphaInv_reader.get_reader(&t()->alphaInv.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_alphaMod_literal))
			{
				driver()->push(localname, _alphaMod_reader.get_reader(&t()->alphaMod.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_alphaModFix_literal))
			{
				driver()->push(localname, _alphaModFix_reader.get_reader(&t()->alphaModFix.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_alphaRepl_literal))
			{
				driver()->push(localname, _alphaRepl_reader.get_reader(&t()->alphaRepl.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_biLevel_literal))
			{
				driver()->push(localname, _biLevel_reader.get_reader(&t()->biLevel.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_blur_literal))
			{
				driver()->push(localname, _blur_reader.get_reader(&t()->blur.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_clrChange_literal))
			{
				driver()->push(localname, _clrChange_reader.get_reader(&t()->clrChange.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_clrRepl_literal))
			{
				driver()->push(localname, _clrRepl_reader.get_reader(&t()->clrRepl.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_duotone_literal))
			{
				driver()->push(localname, _duotone_reader.get_reader(&t()->duotone.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_fillOverlay_literal))
			{
				driver()->push(localname, _fillOverlay_reader.get_reader(&t()->fillOverlay.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_grayscl_literal))
			{
				driver()->push(localname, _grayscl_reader.get_reader(&t()->grayscl.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_hsl_literal))
			{
				driver()->push(localname, _hsl_reader.get_reader(&t()->hsl.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_lum_literal))
			{
				driver()->push(localname, _lum_reader.get_reader(&t()->lum.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_tint_literal))
			{
				driver()->push(localname, _tint_reader.get_reader(&t()->tint.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_Blip_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_embed_literal))
			{
				driver()->context()->parse(value, t()->embed);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_link_literal))
			{
				driver()->context()->parse(value, t()->link);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_cstate_literal))
			{
				driver()->context()->parse(value, t()->cstate);
				return;
			}
		}
		void CT_EffectList_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_blur_literal))
			{
				driver()->push(localname, _blur_reader.get_reader(&t()->blur.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_fillOverlay_literal))
			{
				driver()->push(localname, _fillOverlay_reader.get_reader(&t()->fillOverlay.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_glow_literal))
			{
				driver()->push(localname, _glow_reader.get_reader(&t()->glow.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_innerShdw_literal))
			{
				driver()->push(localname, _innerShdw_reader.get_reader(&t()->innerShdw.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_outerShdw_literal))
			{
				driver()->push(localname, _outerShdw_reader.get_reader(&t()->outerShdw.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_prstShdw_literal))
			{
				driver()->push(localname, _prstShdw_reader.get_reader(&t()->prstShdw.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_reflection_literal))
			{
				driver()->push(localname, _reflection_reader.get_reader(&t()->reflection.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_softEdge_literal))
			{
				driver()->push(localname, _softEdge_reader.get_reader(&t()->softEdge.getset()));
				return;
			}
		}
		void dml_shapeEffects_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_blip_literal))
			{
				driver()->push(localname, _blip_reader.get_reader(&t()->blip.getset()));
				return;
			}
		}
		void CT_FillProperties_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_noFill_literal))
			{
				driver()->push(localname, _noFill_reader.get_reader(&t()->noFill.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_solidFill_literal))
			{
				driver()->push(localname, _solidFill_reader.get_reader(&t()->solidFill.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_gradFill_literal))
			{
				driver()->push(localname, _gradFill_reader.get_reader(&t()->gradFill.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_blipFill_literal))
			{
				driver()->push(localname, _blipFill_reader.get_reader(&t()->blipFill.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_pattFill_literal))
			{
				driver()->push(localname, _pattFill_reader.get_reader(&t()->pattFill.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_grpFill_literal))
			{
				driver()->push(localname, _grpFill_reader.get_reader(&t()->grpFill.getset()));
				return;
			}
		}
		void CT_EffectProperties_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_effectLst_literal))
			{
				driver()->push(localname, _effectLst_reader.get_reader(&t()->effectLst.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_effectDag_literal))
			{
				driver()->push(localname, _effectDag_reader.get_reader(&t()->effectDag.getset()));
				return;
			}
		}
		void CT_BlendEffect_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_cont_literal))
			{
				driver()->push(localname, _cont_reader.get_reader(&t()->cont));
				return;
			}
		}
		void CT_BlendEffect_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeEffects_blend_literal))
			{
				driver()->context()->parse(value, t()->blend);
				return;
			}
		}
	}
}
