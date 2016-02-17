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


#include "dml-baseTypes_readers.hpp"
#include "dml-baseTypes_literals.hpp"
#include <xio/xml/binding/driver.hpp>

namespace drawingml
{
	namespace xio
	{
		void CT_OfficeArtExtension_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_uri_literal))
			{
				driver()->context()->parse(value, t()->uri.getset());
				return;
			}
		}
		void CT_OfficeArtExtensionList_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_ext_literal))
			{
				t()->ext.resize(t()->ext.size()+1);
				driver()->push(localname, _ext_reader.get_reader(&t()->ext.back()));
				return;
			}
		}
		void ST_Percentage_reader::read_value(const xstring& val) {{ driver()->context()->parse(val, *t()); }}
		void ST_Angle_reader::read_value(const xstring& val) {{ driver()->context()->parse(val, *t()); }}
		void CT_SphereCoords_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_lat_literal))
			{
				driver()->context()->parse(value, t()->lat);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_lon_literal))
			{
				driver()->context()->parse(value, t()->lon);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_rev_literal))
			{
				driver()->context()->parse(value, t()->rev);
				return;
			}
		}
		void ST_Coordinate_reader::read_value(const xstring& val) {{ driver()->context()->parse(val, *t()); }}
		void CT_Point3D_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_x_literal))
			{
				driver()->context()->parse(value, t()->x);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_y_literal))
			{
				driver()->context()->parse(value, t()->y);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_z_literal))
			{
				driver()->context()->parse(value, t()->z);
				return;
			}
		}
		void CT_Vector3D_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_dx_literal))
			{
				driver()->context()->parse(value, t()->dx);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_dy_literal))
			{
				driver()->context()->parse(value, t()->dy);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_dz_literal))
			{
				driver()->context()->parse(value, t()->dz);
				return;
			}
		}
		void ST_PositiveCoordinate_reader::read_value(const xstring& val) {{ driver()->context()->parse(val, *t()); }}
		void CT_PositiveFixedPercentage_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_val_literal))
			{
				driver()->context()->parse(value, t()->val);
				return;
			}
		}
		void CT_FixedPercentage_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_val_literal))
			{
				driver()->context()->parse(value, t()->val);
				return;
			}
		}
		void CT_PositivePercentage_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_val_literal))
			{
				driver()->context()->parse(value, t()->val);
				return;
			}
		}
		void CT_PositiveFixedAngle_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_val_literal))
			{
				driver()->context()->parse(value, t()->val);
				return;
			}
		}
		void CT_Angle_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_val_literal))
			{
				driver()->context()->parse(value, t()->val);
				return;
			}
		}
		void CT_Percentage_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_val_literal))
			{
				driver()->context()->parse(value, t()->val);
				return;
			}
		}
		void CT_ScRgbColor_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_tint_literal))
			{
				driver()->push(localname, _tint_reader.get_reader(&t()->tint.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_shade_literal))
			{
				driver()->push(localname, _shade_reader.get_reader(&t()->shade.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_comp_literal))
			{
				driver()->push(localname, _comp_reader.get_reader(&t()->comp.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_inv_literal))
			{
				driver()->push(localname, _inv_reader.get_reader(&t()->inv.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_gray_literal))
			{
				driver()->push(localname, _gray_reader.get_reader(&t()->gray.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_alpha_literal))
			{
				driver()->push(localname, _alpha_reader.get_reader(&t()->alpha.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_alphaOff_literal))
			{
				driver()->push(localname, _alphaOff_reader.get_reader(&t()->alphaOff.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_alphaMod_literal))
			{
				driver()->push(localname, _alphaMod_reader.get_reader(&t()->alphaMod.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_hue_literal))
			{
				driver()->push(localname, _hue_reader.get_reader(&t()->hue.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_hueOff_literal))
			{
				driver()->push(localname, _hueOff_reader.get_reader(&t()->hueOff.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_hueMod_literal))
			{
				driver()->push(localname, _hueMod_reader.get_reader(&t()->hueMod.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_sat_literal))
			{
				driver()->push(localname, _sat_reader.get_reader(&t()->sat.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_satOff_literal))
			{
				driver()->push(localname, _satOff_reader.get_reader(&t()->satOff.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_satMod_literal))
			{
				driver()->push(localname, _satMod_reader.get_reader(&t()->satMod.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_lum_literal))
			{
				driver()->push(localname, _lum_reader.get_reader(&t()->lum.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_lumOff_literal))
			{
				driver()->push(localname, _lumOff_reader.get_reader(&t()->lumOff.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_lumMod_literal))
			{
				driver()->push(localname, _lumMod_reader.get_reader(&t()->lumMod.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_red_literal))
			{
				driver()->push(localname, _red_reader.get_reader(&t()->red.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_redOff_literal))
			{
				driver()->push(localname, _redOff_reader.get_reader(&t()->redOff.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_redMod_literal))
			{
				driver()->push(localname, _redMod_reader.get_reader(&t()->redMod.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_green_literal))
			{
				driver()->push(localname, _green_reader.get_reader(&t()->green.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_greenOff_literal))
			{
				driver()->push(localname, _greenOff_reader.get_reader(&t()->greenOff.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_greenMod_literal))
			{
				driver()->push(localname, _greenMod_reader.get_reader(&t()->greenMod.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_blue_literal))
			{
				driver()->push(localname, _blue_reader.get_reader(&t()->blue.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_blueOff_literal))
			{
				driver()->push(localname, _blueOff_reader.get_reader(&t()->blueOff.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_blueMod_literal))
			{
				driver()->push(localname, _blueMod_reader.get_reader(&t()->blueMod.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_gamma_literal))
			{
				driver()->push(localname, _gamma_reader.get_reader(&t()->gamma.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_invGamma_literal))
			{
				driver()->push(localname, _invGamma_reader.get_reader(&t()->invGamma.getset()));
				return;
			}
		}
		void CT_ScRgbColor_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_r_literal))
			{
				driver()->context()->parse(value, t()->r);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_g_literal))
			{
				driver()->context()->parse(value, t()->g);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_b_literal))
			{
				driver()->context()->parse(value, t()->b);
				return;
			}
		}
		void ST_HexBinary3_reader::read_value(const xstring& val) {{ driver()->context()->parse(val, *t()); }}
		void CT_SRgbColor_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_tint_literal))
			{
				driver()->push(localname, _tint_reader.get_reader(&t()->tint.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_shade_literal))
			{
				driver()->push(localname, _shade_reader.get_reader(&t()->shade.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_comp_literal))
			{
				driver()->push(localname, _comp_reader.get_reader(&t()->comp.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_inv_literal))
			{
				driver()->push(localname, _inv_reader.get_reader(&t()->inv.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_gray_literal))
			{
				driver()->push(localname, _gray_reader.get_reader(&t()->gray.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_alpha_literal))
			{
				driver()->push(localname, _alpha_reader.get_reader(&t()->alpha.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_alphaOff_literal))
			{
				driver()->push(localname, _alphaOff_reader.get_reader(&t()->alphaOff.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_alphaMod_literal))
			{
				driver()->push(localname, _alphaMod_reader.get_reader(&t()->alphaMod.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_hue_literal))
			{
				driver()->push(localname, _hue_reader.get_reader(&t()->hue.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_hueOff_literal))
			{
				driver()->push(localname, _hueOff_reader.get_reader(&t()->hueOff.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_hueMod_literal))
			{
				driver()->push(localname, _hueMod_reader.get_reader(&t()->hueMod.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_sat_literal))
			{
				driver()->push(localname, _sat_reader.get_reader(&t()->sat.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_satOff_literal))
			{
				driver()->push(localname, _satOff_reader.get_reader(&t()->satOff.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_satMod_literal))
			{
				driver()->push(localname, _satMod_reader.get_reader(&t()->satMod.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_lum_literal))
			{
				driver()->push(localname, _lum_reader.get_reader(&t()->lum.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_lumOff_literal))
			{
				driver()->push(localname, _lumOff_reader.get_reader(&t()->lumOff.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_lumMod_literal))
			{
				driver()->push(localname, _lumMod_reader.get_reader(&t()->lumMod.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_red_literal))
			{
				driver()->push(localname, _red_reader.get_reader(&t()->red.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_redOff_literal))
			{
				driver()->push(localname, _redOff_reader.get_reader(&t()->redOff.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_redMod_literal))
			{
				driver()->push(localname, _redMod_reader.get_reader(&t()->redMod.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_green_literal))
			{
				driver()->push(localname, _green_reader.get_reader(&t()->green.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_greenOff_literal))
			{
				driver()->push(localname, _greenOff_reader.get_reader(&t()->greenOff.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_greenMod_literal))
			{
				driver()->push(localname, _greenMod_reader.get_reader(&t()->greenMod.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_blue_literal))
			{
				driver()->push(localname, _blue_reader.get_reader(&t()->blue.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_blueOff_literal))
			{
				driver()->push(localname, _blueOff_reader.get_reader(&t()->blueOff.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_blueMod_literal))
			{
				driver()->push(localname, _blueMod_reader.get_reader(&t()->blueMod.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_gamma_literal))
			{
				driver()->push(localname, _gamma_reader.get_reader(&t()->gamma.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_invGamma_literal))
			{
				driver()->push(localname, _invGamma_reader.get_reader(&t()->invGamma.getset()));
				return;
			}
		}
		void CT_SRgbColor_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_val_literal))
			{
				driver()->context()->parse(value, t()->val);
				return;
			}
		}
		void CT_HslColor_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_tint_literal))
			{
				driver()->push(localname, _tint_reader.get_reader(&t()->tint.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_shade_literal))
			{
				driver()->push(localname, _shade_reader.get_reader(&t()->shade.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_comp_literal))
			{
				driver()->push(localname, _comp_reader.get_reader(&t()->comp.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_inv_literal))
			{
				driver()->push(localname, _inv_reader.get_reader(&t()->inv.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_gray_literal))
			{
				driver()->push(localname, _gray_reader.get_reader(&t()->gray.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_alpha_literal))
			{
				driver()->push(localname, _alpha_reader.get_reader(&t()->alpha.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_alphaOff_literal))
			{
				driver()->push(localname, _alphaOff_reader.get_reader(&t()->alphaOff.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_alphaMod_literal))
			{
				driver()->push(localname, _alphaMod_reader.get_reader(&t()->alphaMod.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_hue_literal))
			{
				driver()->push(localname, _hue_reader.get_reader(&t()->hue.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_hueOff_literal))
			{
				driver()->push(localname, _hueOff_reader.get_reader(&t()->hueOff.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_hueMod_literal))
			{
				driver()->push(localname, _hueMod_reader.get_reader(&t()->hueMod.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_sat_literal))
			{
				driver()->push(localname, _sat_reader.get_reader(&t()->sat.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_satOff_literal))
			{
				driver()->push(localname, _satOff_reader.get_reader(&t()->satOff.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_satMod_literal))
			{
				driver()->push(localname, _satMod_reader.get_reader(&t()->satMod.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_lum_literal))
			{
				driver()->push(localname, _lum_reader.get_reader(&t()->lum.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_lumOff_literal))
			{
				driver()->push(localname, _lumOff_reader.get_reader(&t()->lumOff.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_lumMod_literal))
			{
				driver()->push(localname, _lumMod_reader.get_reader(&t()->lumMod.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_red_literal))
			{
				driver()->push(localname, _red_reader.get_reader(&t()->red.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_redOff_literal))
			{
				driver()->push(localname, _redOff_reader.get_reader(&t()->redOff.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_redMod_literal))
			{
				driver()->push(localname, _redMod_reader.get_reader(&t()->redMod.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_green_literal))
			{
				driver()->push(localname, _green_reader.get_reader(&t()->green.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_greenOff_literal))
			{
				driver()->push(localname, _greenOff_reader.get_reader(&t()->greenOff.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_greenMod_literal))
			{
				driver()->push(localname, _greenMod_reader.get_reader(&t()->greenMod.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_blue_literal))
			{
				driver()->push(localname, _blue_reader.get_reader(&t()->blue.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_blueOff_literal))
			{
				driver()->push(localname, _blueOff_reader.get_reader(&t()->blueOff.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_blueMod_literal))
			{
				driver()->push(localname, _blueMod_reader.get_reader(&t()->blueMod.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_gamma_literal))
			{
				driver()->push(localname, _gamma_reader.get_reader(&t()->gamma.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_invGamma_literal))
			{
				driver()->push(localname, _invGamma_reader.get_reader(&t()->invGamma.getset()));
				return;
			}
		}
		void CT_HslColor_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_hue_literal))
			{
				driver()->context()->parse(value, t()->hue_attr);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_sat_literal))
			{
				driver()->context()->parse(value, t()->sat_attr);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_lum_literal))
			{
				driver()->context()->parse(value, t()->lum_attr);
				return;
			}
		}
		void CT_SystemColor_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_tint_literal))
			{
				driver()->push(localname, _tint_reader.get_reader(&t()->tint.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_shade_literal))
			{
				driver()->push(localname, _shade_reader.get_reader(&t()->shade.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_comp_literal))
			{
				driver()->push(localname, _comp_reader.get_reader(&t()->comp.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_inv_literal))
			{
				driver()->push(localname, _inv_reader.get_reader(&t()->inv.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_gray_literal))
			{
				driver()->push(localname, _gray_reader.get_reader(&t()->gray.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_alpha_literal))
			{
				driver()->push(localname, _alpha_reader.get_reader(&t()->alpha.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_alphaOff_literal))
			{
				driver()->push(localname, _alphaOff_reader.get_reader(&t()->alphaOff.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_alphaMod_literal))
			{
				driver()->push(localname, _alphaMod_reader.get_reader(&t()->alphaMod.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_hue_literal))
			{
				driver()->push(localname, _hue_reader.get_reader(&t()->hue.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_hueOff_literal))
			{
				driver()->push(localname, _hueOff_reader.get_reader(&t()->hueOff.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_hueMod_literal))
			{
				driver()->push(localname, _hueMod_reader.get_reader(&t()->hueMod.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_sat_literal))
			{
				driver()->push(localname, _sat_reader.get_reader(&t()->sat.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_satOff_literal))
			{
				driver()->push(localname, _satOff_reader.get_reader(&t()->satOff.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_satMod_literal))
			{
				driver()->push(localname, _satMod_reader.get_reader(&t()->satMod.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_lum_literal))
			{
				driver()->push(localname, _lum_reader.get_reader(&t()->lum.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_lumOff_literal))
			{
				driver()->push(localname, _lumOff_reader.get_reader(&t()->lumOff.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_lumMod_literal))
			{
				driver()->push(localname, _lumMod_reader.get_reader(&t()->lumMod.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_red_literal))
			{
				driver()->push(localname, _red_reader.get_reader(&t()->red.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_redOff_literal))
			{
				driver()->push(localname, _redOff_reader.get_reader(&t()->redOff.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_redMod_literal))
			{
				driver()->push(localname, _redMod_reader.get_reader(&t()->redMod.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_green_literal))
			{
				driver()->push(localname, _green_reader.get_reader(&t()->green.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_greenOff_literal))
			{
				driver()->push(localname, _greenOff_reader.get_reader(&t()->greenOff.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_greenMod_literal))
			{
				driver()->push(localname, _greenMod_reader.get_reader(&t()->greenMod.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_blue_literal))
			{
				driver()->push(localname, _blue_reader.get_reader(&t()->blue.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_blueOff_literal))
			{
				driver()->push(localname, _blueOff_reader.get_reader(&t()->blueOff.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_blueMod_literal))
			{
				driver()->push(localname, _blueMod_reader.get_reader(&t()->blueMod.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_gamma_literal))
			{
				driver()->push(localname, _gamma_reader.get_reader(&t()->gamma.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_invGamma_literal))
			{
				driver()->push(localname, _invGamma_reader.get_reader(&t()->invGamma.getset()));
				return;
			}
		}
		void CT_SystemColor_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_val_literal))
			{
				driver()->context()->parse(value, t()->val);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_lastClr_literal))
			{
				driver()->context()->parse(value, t()->lastClr.getset());
				return;
			}
		}
		void CT_SchemeColor_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_tint_literal))
			{
				driver()->push(localname, _tint_reader.get_reader(&t()->tint.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_shade_literal))
			{
				driver()->push(localname, _shade_reader.get_reader(&t()->shade.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_comp_literal))
			{
				driver()->push(localname, _comp_reader.get_reader(&t()->comp.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_inv_literal))
			{
				driver()->push(localname, _inv_reader.get_reader(&t()->inv.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_gray_literal))
			{
				driver()->push(localname, _gray_reader.get_reader(&t()->gray.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_alpha_literal))
			{
				driver()->push(localname, _alpha_reader.get_reader(&t()->alpha.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_alphaOff_literal))
			{
				driver()->push(localname, _alphaOff_reader.get_reader(&t()->alphaOff.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_alphaMod_literal))
			{
				driver()->push(localname, _alphaMod_reader.get_reader(&t()->alphaMod.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_hue_literal))
			{
				driver()->push(localname, _hue_reader.get_reader(&t()->hue.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_hueOff_literal))
			{
				driver()->push(localname, _hueOff_reader.get_reader(&t()->hueOff.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_hueMod_literal))
			{
				driver()->push(localname, _hueMod_reader.get_reader(&t()->hueMod.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_sat_literal))
			{
				driver()->push(localname, _sat_reader.get_reader(&t()->sat.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_satOff_literal))
			{
				driver()->push(localname, _satOff_reader.get_reader(&t()->satOff.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_satMod_literal))
			{
				driver()->push(localname, _satMod_reader.get_reader(&t()->satMod.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_lum_literal))
			{
				driver()->push(localname, _lum_reader.get_reader(&t()->lum.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_lumOff_literal))
			{
				driver()->push(localname, _lumOff_reader.get_reader(&t()->lumOff.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_lumMod_literal))
			{
				driver()->push(localname, _lumMod_reader.get_reader(&t()->lumMod.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_red_literal))
			{
				driver()->push(localname, _red_reader.get_reader(&t()->red.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_redOff_literal))
			{
				driver()->push(localname, _redOff_reader.get_reader(&t()->redOff.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_redMod_literal))
			{
				driver()->push(localname, _redMod_reader.get_reader(&t()->redMod.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_green_literal))
			{
				driver()->push(localname, _green_reader.get_reader(&t()->green.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_greenOff_literal))
			{
				driver()->push(localname, _greenOff_reader.get_reader(&t()->greenOff.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_greenMod_literal))
			{
				driver()->push(localname, _greenMod_reader.get_reader(&t()->greenMod.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_blue_literal))
			{
				driver()->push(localname, _blue_reader.get_reader(&t()->blue.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_blueOff_literal))
			{
				driver()->push(localname, _blueOff_reader.get_reader(&t()->blueOff.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_blueMod_literal))
			{
				driver()->push(localname, _blueMod_reader.get_reader(&t()->blueMod.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_gamma_literal))
			{
				driver()->push(localname, _gamma_reader.get_reader(&t()->gamma.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_invGamma_literal))
			{
				driver()->push(localname, _invGamma_reader.get_reader(&t()->invGamma.getset()));
				return;
			}
		}
		void CT_SchemeColor_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_val_literal))
			{
				driver()->context()->parse(value, t()->val);
				return;
			}
		}
		void CT_PresetColor_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_tint_literal))
			{
				driver()->push(localname, _tint_reader.get_reader(&t()->tint.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_shade_literal))
			{
				driver()->push(localname, _shade_reader.get_reader(&t()->shade.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_comp_literal))
			{
				driver()->push(localname, _comp_reader.get_reader(&t()->comp.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_inv_literal))
			{
				driver()->push(localname, _inv_reader.get_reader(&t()->inv.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_gray_literal))
			{
				driver()->push(localname, _gray_reader.get_reader(&t()->gray.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_alpha_literal))
			{
				driver()->push(localname, _alpha_reader.get_reader(&t()->alpha.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_alphaOff_literal))
			{
				driver()->push(localname, _alphaOff_reader.get_reader(&t()->alphaOff.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_alphaMod_literal))
			{
				driver()->push(localname, _alphaMod_reader.get_reader(&t()->alphaMod.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_hue_literal))
			{
				driver()->push(localname, _hue_reader.get_reader(&t()->hue.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_hueOff_literal))
			{
				driver()->push(localname, _hueOff_reader.get_reader(&t()->hueOff.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_hueMod_literal))
			{
				driver()->push(localname, _hueMod_reader.get_reader(&t()->hueMod.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_sat_literal))
			{
				driver()->push(localname, _sat_reader.get_reader(&t()->sat.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_satOff_literal))
			{
				driver()->push(localname, _satOff_reader.get_reader(&t()->satOff.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_satMod_literal))
			{
				driver()->push(localname, _satMod_reader.get_reader(&t()->satMod.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_lum_literal))
			{
				driver()->push(localname, _lum_reader.get_reader(&t()->lum.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_lumOff_literal))
			{
				driver()->push(localname, _lumOff_reader.get_reader(&t()->lumOff.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_lumMod_literal))
			{
				driver()->push(localname, _lumMod_reader.get_reader(&t()->lumMod.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_red_literal))
			{
				driver()->push(localname, _red_reader.get_reader(&t()->red.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_redOff_literal))
			{
				driver()->push(localname, _redOff_reader.get_reader(&t()->redOff.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_redMod_literal))
			{
				driver()->push(localname, _redMod_reader.get_reader(&t()->redMod.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_green_literal))
			{
				driver()->push(localname, _green_reader.get_reader(&t()->green.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_greenOff_literal))
			{
				driver()->push(localname, _greenOff_reader.get_reader(&t()->greenOff.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_greenMod_literal))
			{
				driver()->push(localname, _greenMod_reader.get_reader(&t()->greenMod.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_blue_literal))
			{
				driver()->push(localname, _blue_reader.get_reader(&t()->blue.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_blueOff_literal))
			{
				driver()->push(localname, _blueOff_reader.get_reader(&t()->blueOff.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_blueMod_literal))
			{
				driver()->push(localname, _blueMod_reader.get_reader(&t()->blueMod.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_gamma_literal))
			{
				driver()->push(localname, _gamma_reader.get_reader(&t()->gamma.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_invGamma_literal))
			{
				driver()->push(localname, _invGamma_reader.get_reader(&t()->invGamma.getset()));
				return;
			}
		}
		void CT_PresetColor_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_val_literal))
			{
				driver()->context()->parse(value, t()->val.getset());
				return;
			}
		}
		void CT_Color_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_scrgbClr_literal))
			{
				driver()->push(localname, _scrgbClr_reader.get_reader(&t()->scrgbClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_srgbClr_literal))
			{
				driver()->push(localname, _srgbClr_reader.get_reader(&t()->srgbClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_hslClr_literal))
			{
				driver()->push(localname, _hslClr_reader.get_reader(&t()->hslClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_sysClr_literal))
			{
				driver()->push(localname, _sysClr_reader.get_reader(&t()->sysClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_schemeClr_literal))
			{
				driver()->push(localname, _schemeClr_reader.get_reader(&t()->schemeClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_prstClr_literal))
			{
				driver()->push(localname, _prstClr_reader.get_reader(&t()->prstClr.getset()));
				return;
			}
		}
		void ST_Coordinate32_reader::read_value(const xstring& val) {{ driver()->context()->parse(val, *t()); }}
		void CT_RelativeRect_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_l_literal))
			{
				driver()->context()->parse(value, t()->l);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_t_literal))
			{
				driver()->context()->parse(value, t()->t);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_r_literal))
			{
				driver()->context()->parse(value, t()->r);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_b_literal))
			{
				driver()->context()->parse(value, t()->b);
				return;
			}
		}
		void CT_EmbeddedWAVAudioFile_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_embed_literal))
			{
				driver()->context()->parse(value, t()->embed);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_name_literal))
			{
				driver()->context()->parse(value, t()->name);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_builtIn_literal))
			{
				driver()->context()->parse(value, t()->builtIn);
				return;
			}
		}
		void CT_Hyperlink_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_snd_literal))
			{
				driver()->push(localname, _snd_reader.get_reader(&t()->snd.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_Hyperlink_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_id_literal))
			{
				driver()->context()->parse(value, t()->id.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_invalidUrl_literal))
			{
				driver()->context()->parse(value, t()->invalidUrl);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_action_literal))
			{
				driver()->context()->parse(value, t()->action);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_tgtFrame_literal))
			{
				driver()->context()->parse(value, t()->tgtFrame);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_tooltip_literal))
			{
				driver()->context()->parse(value, t()->tooltip);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_history_literal))
			{
				driver()->context()->parse(value, t()->history);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_highlightClick_literal))
			{
				driver()->context()->parse(value, t()->highlightClick);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_endSnd_literal))
			{
				driver()->context()->parse(value, t()->endSnd);
				return;
			}
		}
		void ST_Guid_reader::read_value(const xstring& val) {{ driver()->context()->parse(val, *t()); }}
		void CT_Point2D_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_x_literal))
			{
				driver()->context()->parse(value, t()->x);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_y_literal))
			{
				driver()->context()->parse(value, t()->y);
				return;
			}
		}
		void CT_PositiveSize2D_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_cx_literal))
			{
				driver()->context()->parse(value, t()->cx);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_cy_literal))
			{
				driver()->context()->parse(value, t()->cy);
				return;
			}
		}
		void CT_Transform2D_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_off_literal))
			{
				driver()->push(localname, _off_reader.get_reader(&t()->off.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_ext_literal))
			{
				driver()->push(localname, _ext_reader.get_reader(&t()->ext.getset()));
				return;
			}
		}
		void CT_Transform2D_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_rot_literal))
			{
				driver()->context()->parse(value, t()->rot);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_flipH_literal))
			{
				driver()->context()->parse(value, t()->flipH);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_flipV_literal))
			{
				driver()->context()->parse(value, t()->flipV);
				return;
			}
		}
		void ST_DrawingElementId_reader::read_value(const xstring& val) {{ driver()->context()->parse(val, *t()); }}
		void CT_GroupTransform2D_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_off_literal))
			{
				driver()->push(localname, _off_reader.get_reader(&t()->off.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_ext_literal))
			{
				driver()->push(localname, _ext_reader.get_reader(&t()->ext.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_chOff_literal))
			{
				driver()->push(localname, _chOff_reader.get_reader(&t()->chOff.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_chExt_literal))
			{
				driver()->push(localname, _chExt_reader.get_reader(&t()->chExt.getset()));
				return;
			}
		}
		void CT_GroupTransform2D_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_rot_literal))
			{
				driver()->context()->parse(value, t()->rot);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_flipH_literal))
			{
				driver()->context()->parse(value, t()->flipH);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_flipV_literal))
			{
				driver()->context()->parse(value, t()->flipV);
				return;
			}
		}
		void CT_ColorMRU_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_scrgbClr_literal))
			{
				driver()->push(localname, _scrgbClr_reader.get_reader(&t()->scrgbClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_srgbClr_literal))
			{
				driver()->push(localname, _srgbClr_reader.get_reader(&t()->srgbClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_hslClr_literal))
			{
				driver()->push(localname, _hslClr_reader.get_reader(&t()->hslClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_sysClr_literal))
			{
				driver()->push(localname, _sysClr_reader.get_reader(&t()->sysClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_schemeClr_literal))
			{
				driver()->push(localname, _schemeClr_reader.get_reader(&t()->schemeClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_prstClr_literal))
			{
				driver()->push(localname, _prstClr_reader.get_reader(&t()->prstClr.getset()));
				return;
			}
		}
		void CT_Ratio_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_n_literal))
			{
				driver()->context()->parse(value, t()->n);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_d_literal))
			{
				driver()->context()->parse(value, t()->d);
				return;
			}
		}
		void CT_Scale2D_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_sx_literal))
			{
				driver()->push(localname, _sx_reader.get_reader(&t()->sx));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_baseTypes_sy_literal))
			{
				driver()->push(localname, _sy_reader.get_reader(&t()->sy));
				return;
			}
		}
	}
}
