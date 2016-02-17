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


#include "sml-customXmlMappings_readers.hpp"
#include "sml-customXmlMappings_literals.hpp"
#include <xio/xml/binding/driver.hpp>

namespace spreadsheetml
{
	namespace xio
	{
		void CT_Schema_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_customXmlMappings_ID_literal))
			{
				driver()->context()->parse(value, t()->ID);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_customXmlMappings_SchemaRef_literal))
			{
				driver()->context()->parse(value, t()->SchemaRef.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_customXmlMappings_Namespace_literal))
			{
				driver()->context()->parse(value, t()->Namespace.getset());
				return;
			}
		}
		void CT_DataBinding_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_customXmlMappings_DataBindingName_literal))
			{
				driver()->context()->parse(value, t()->DataBindingName.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_customXmlMappings_FileBinding_literal))
			{
				driver()->context()->parse(value, t()->FileBinding.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_customXmlMappings_ConnectionID_literal))
			{
				driver()->context()->parse(value, t()->ConnectionID.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_customXmlMappings_FileBindingName_literal))
			{
				driver()->context()->parse(value, t()->FileBindingName.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_customXmlMappings_DataBindingLoadMode_literal))
			{
				driver()->context()->parse(value, t()->DataBindingLoadMode);
				return;
			}
		}
		void CT_Map_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_customXmlMappings_DataBinding_literal))
			{
				driver()->push(localname, _DataBinding_reader.get_reader(&t()->DataBinding.getset()));
				return;
			}
		}
		void CT_Map_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_customXmlMappings_ID_literal))
			{
				driver()->context()->parse(value, t()->ID);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_customXmlMappings_Name_literal))
			{
				driver()->context()->parse(value, t()->Name);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_customXmlMappings_RootElement_literal))
			{
				driver()->context()->parse(value, t()->RootElement);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_customXmlMappings_SchemaID_literal))
			{
				driver()->context()->parse(value, t()->SchemaID);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_customXmlMappings_ShowImportExportValidationErrors_literal))
			{
				driver()->context()->parse(value, t()->ShowImportExportValidationErrors);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_customXmlMappings_AutoFit_literal))
			{
				driver()->context()->parse(value, t()->AutoFit);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_customXmlMappings_Append_literal))
			{
				driver()->context()->parse(value, t()->Append);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_customXmlMappings_PreserveSortAFLayout_literal))
			{
				driver()->context()->parse(value, t()->PreserveSortAFLayout);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_customXmlMappings_PreserveFormat_literal))
			{
				driver()->context()->parse(value, t()->PreserveFormat);
				return;
			}
		}
		void CT_MapInfo_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_customXmlMappings_Schema_literal))
			{
				t()->Schema.resize(t()->Schema.size()+1);
				driver()->push(localname, _Schema_reader.get_reader(&t()->Schema.back()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_customXmlMappings_Map_literal))
			{
				t()->Map.resize(t()->Map.size()+1);
				driver()->push(localname, _Map_reader.get_reader(&t()->Map.back()));
				return;
			}
		}
		void CT_MapInfo_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_customXmlMappings_SelectionNamespaces_literal))
			{
				driver()->context()->parse(value, t()->SelectionNamespaces);
				return;
			}
		}
		void sml_customXmlMappings_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_customXmlMappings_MapInfo_literal))
			{
				driver()->push(localname, _MapInfo_reader.get_reader(&t()->MapInfo.getset()));
				return;
			}
		}
	}
}
