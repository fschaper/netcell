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


#include "dml-shapeStyle_readers.hpp"
#include "dml-shapeStyle_literals.hpp"
#include <xio/xml/binding/driver.hpp>

namespace drawingml
{
	namespace xio
	{
		void CT_StyleMatrixReference_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeStyle_scrgbClr_literal))
			{
				driver()->push(localname, _scrgbClr_reader.get_reader(&t()->scrgbClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeStyle_srgbClr_literal))
			{
				driver()->push(localname, _srgbClr_reader.get_reader(&t()->srgbClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeStyle_hslClr_literal))
			{
				driver()->push(localname, _hslClr_reader.get_reader(&t()->hslClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeStyle_sysClr_literal))
			{
				driver()->push(localname, _sysClr_reader.get_reader(&t()->sysClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeStyle_schemeClr_literal))
			{
				driver()->push(localname, _schemeClr_reader.get_reader(&t()->schemeClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeStyle_prstClr_literal))
			{
				driver()->push(localname, _prstClr_reader.get_reader(&t()->prstClr.getset()));
				return;
			}
		}
		void CT_StyleMatrixReference_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeStyle_idx_literal))
			{
				driver()->context()->parse(value, t()->idx);
				return;
			}
		}
		void CT_FontReference_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeStyle_scrgbClr_literal))
			{
				driver()->push(localname, _scrgbClr_reader.get_reader(&t()->scrgbClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeStyle_srgbClr_literal))
			{
				driver()->push(localname, _srgbClr_reader.get_reader(&t()->srgbClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeStyle_hslClr_literal))
			{
				driver()->push(localname, _hslClr_reader.get_reader(&t()->hslClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeStyle_sysClr_literal))
			{
				driver()->push(localname, _sysClr_reader.get_reader(&t()->sysClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeStyle_schemeClr_literal))
			{
				driver()->push(localname, _schemeClr_reader.get_reader(&t()->schemeClr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeStyle_prstClr_literal))
			{
				driver()->push(localname, _prstClr_reader.get_reader(&t()->prstClr.getset()));
				return;
			}
		}
		void CT_FontReference_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeStyle_idx_literal))
			{
				driver()->context()->parse(value, t()->idx);
				return;
			}
		}
		void CT_ShapeStyle_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeStyle_lnRef_literal))
			{
				driver()->push(localname, _lnRef_reader.get_reader(&t()->lnRef));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeStyle_fillRef_literal))
			{
				driver()->push(localname, _fillRef_reader.get_reader(&t()->fillRef));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeStyle_effectRef_literal))
			{
				driver()->push(localname, _effectRef_reader.get_reader(&t()->effectRef));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeStyle_fontRef_literal))
			{
				driver()->push(localname, _fontRef_reader.get_reader(&t()->fontRef));
				return;
			}
		}
	}
}
