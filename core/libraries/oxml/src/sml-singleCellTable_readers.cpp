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


#include "sml-singleCellTable_readers.hpp"
#include "sml-singleCellTable_literals.hpp"
#include <xio/xml/binding/driver.hpp>

namespace spreadsheetml
{
	namespace xio
	{
		void CT_XmlPr_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_singleCellTable_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_XmlPr_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_singleCellTable_mapId_literal))
			{
				driver()->context()->parse(value, t()->mapId);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_singleCellTable_xpath_literal))
			{
				driver()->context()->parse(value, t()->xpath);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_singleCellTable_xmlDataType_literal))
			{
				driver()->context()->parse(value, t()->xmlDataType);
				return;
			}
		}
		void CT_XmlCellPr_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_singleCellTable_xmlPr_literal))
			{
				driver()->push(localname, _xmlPr_reader.get_reader(&t()->xmlPr));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_singleCellTable_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_XmlCellPr_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_singleCellTable_id_literal))
			{
				driver()->context()->parse(value, t()->id);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_singleCellTable_uniqueName_literal))
			{
				driver()->context()->parse(value, t()->uniqueName.getset());
				return;
			}
		}
		void CT_SingleXmlCell_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_singleCellTable_xmlCellPr_literal))
			{
				driver()->push(localname, _xmlCellPr_reader.get_reader(&t()->xmlCellPr));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_singleCellTable_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_SingleXmlCell_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_singleCellTable_id_literal))
			{
				driver()->context()->parse(value, t()->id);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_singleCellTable_r_literal))
			{
				driver()->context()->parse(value, t()->r);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_singleCellTable_connectionId_literal))
			{
				driver()->context()->parse(value, t()->connectionId);
				return;
			}
		}
		void CT_SingleXmlCells_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_singleCellTable_singleXmlCell_literal))
			{
				t()->singleXmlCell.resize(t()->singleXmlCell.size()+1);
				driver()->push(localname, _singleXmlCell_reader.get_reader(&t()->singleXmlCell.back()));
				return;
			}
		}
		void sml_singleCellTable_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_singleCellTable_singleXmlCells_literal))
			{
				driver()->push(localname, _singleXmlCells_reader.get_reader(&t()->singleXmlCells.getset()));
				return;
			}
		}
	}
}
