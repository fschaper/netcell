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


#include "dml-shapeProperties_readers.hpp"
#include "dml-shapeProperties_literals.hpp"
#include <xio/xml/binding/driver.hpp>

namespace drawingml
{
	namespace xio
	{
		void CT_ShapeProperties_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeProperties_xfrm_literal))
			{
				driver()->push(localname, _xfrm_reader.get_reader(&t()->xfrm.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeProperties_custGeom_literal))
			{
				driver()->push(localname, _custGeom_reader.get_reader(&t()->custGeom.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeProperties_prstGeom_literal))
			{
				driver()->push(localname, _prstGeom_reader.get_reader(&t()->prstGeom.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeProperties_noFill_literal))
			{
				driver()->push(localname, _noFill_reader.get_reader(&t()->noFill.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeProperties_solidFill_literal))
			{
				driver()->push(localname, _solidFill_reader.get_reader(&t()->solidFill.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeProperties_gradFill_literal))
			{
				driver()->push(localname, _gradFill_reader.get_reader(&t()->gradFill.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeProperties_blipFill_literal))
			{
				driver()->push(localname, _blipFill_reader.get_reader(&t()->blipFill.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeProperties_pattFill_literal))
			{
				driver()->push(localname, _pattFill_reader.get_reader(&t()->pattFill.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeProperties_grpFill_literal))
			{
				driver()->push(localname, _grpFill_reader.get_reader(&t()->grpFill.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeProperties_ln_literal))
			{
				driver()->push(localname, _ln_reader.get_reader(&t()->ln.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeProperties_effectLst_literal))
			{
				driver()->push(localname, _effectLst_reader.get_reader(&t()->effectLst.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeProperties_effectDag_literal))
			{
				driver()->push(localname, _effectDag_reader.get_reader(&t()->effectDag.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeProperties_scene3d_literal))
			{
				driver()->push(localname, _scene3d_reader.get_reader(&t()->scene3d.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeProperties_sp3d_literal))
			{
				driver()->push(localname, _sp3d_reader.get_reader(&t()->sp3d.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeProperties_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_ShapeProperties_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeProperties_bwMode_literal))
			{
				driver()->context()->parse(value, t()->bwMode.getset());
				return;
			}
		}
		void CT_GroupShapeProperties_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeProperties_xfrm_literal))
			{
				driver()->push(localname, _xfrm_reader.get_reader(&t()->xfrm.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeProperties_noFill_literal))
			{
				driver()->push(localname, _noFill_reader.get_reader(&t()->noFill.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeProperties_solidFill_literal))
			{
				driver()->push(localname, _solidFill_reader.get_reader(&t()->solidFill.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeProperties_gradFill_literal))
			{
				driver()->push(localname, _gradFill_reader.get_reader(&t()->gradFill.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeProperties_blipFill_literal))
			{
				driver()->push(localname, _blipFill_reader.get_reader(&t()->blipFill.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeProperties_pattFill_literal))
			{
				driver()->push(localname, _pattFill_reader.get_reader(&t()->pattFill.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeProperties_grpFill_literal))
			{
				driver()->push(localname, _grpFill_reader.get_reader(&t()->grpFill.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeProperties_effectLst_literal))
			{
				driver()->push(localname, _effectLst_reader.get_reader(&t()->effectLst.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeProperties_effectDag_literal))
			{
				driver()->push(localname, _effectDag_reader.get_reader(&t()->effectDag.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeProperties_scene3d_literal))
			{
				driver()->push(localname, _scene3d_reader.get_reader(&t()->scene3d.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeProperties_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_GroupShapeProperties_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeProperties_bwMode_literal))
			{
				driver()->context()->parse(value, t()->bwMode.getset());
				return;
			}
		}
	}
}
