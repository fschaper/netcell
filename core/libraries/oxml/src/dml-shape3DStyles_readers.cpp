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


#include "dml-shape3DStyles_readers.hpp"
#include "dml-shape3DStyles_literals.hpp"
#include <xio/xml/binding/driver.hpp>

namespace drawingml
{
	namespace xio
	{
		void CT_Bevel_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_shape3DStyles_w_literal))
			{
				driver()->context()->parse(value, t()->w);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shape3DStyles_h_literal))
			{
				driver()->context()->parse(value, t()->h);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shape3DStyles_prst_literal))
			{
				driver()->context()->parse(value, t()->prst);
				return;
			}
		}
		void CT_Shape3D_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_shape3DStyles_bevelT_literal))
			{
				driver()->push(localname, _bevelT_reader.get_reader(&t()->bevelT.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shape3DStyles_bevelB_literal))
			{
				driver()->push(localname, _bevelB_reader.get_reader(&t()->bevelB.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shape3DStyles_extrusionClr_literal))
			{
				driver()->push(localname, _extrusionClr_reader.get_reader(&t()->extrusionClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shape3DStyles_contourClr_literal))
			{
				driver()->push(localname, _contourClr_reader.get_reader(&t()->contourClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shape3DStyles_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_Shape3D_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_shape3DStyles_z_literal))
			{
				driver()->context()->parse(value, t()->z);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shape3DStyles_extrusionH_literal))
			{
				driver()->context()->parse(value, t()->extrusionH);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shape3DStyles_contourW_literal))
			{
				driver()->context()->parse(value, t()->contourW);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shape3DStyles_prstMaterial_literal))
			{
				driver()->context()->parse(value, t()->prstMaterial);
				return;
			}
		}
		void CT_FlatText_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_shape3DStyles_z_literal))
			{
				driver()->context()->parse(value, t()->z);
				return;
			}
		}
	}
}
