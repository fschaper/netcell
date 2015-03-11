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


#include "sml-baseTypes_readers.hpp"
#include "sml-baseTypes_literals.hpp"
#include <xio/xml/binding/driver.hpp>

namespace spreadsheetml
{
	namespace xio
	{
		void ST_CellRef_reader::read_value(const xstring& val) {{ driver()->context()->parse(val, *t()); }}
		void CT_Extension_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_baseTypes_uri_literal))
			{
				driver()->context()->parse(value, t()->uri.getset());
				return;
			}
		}
		void CT_ExtensionList_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_baseTypes_ext_literal))
			{
				t()->ext.resize(t()->ext.size()+1);
				driver()->push(localname, _ext_reader.get_reader(&t()->ext.back()));
				return;
			}
		}
		void ST_Xstring_reader::read_value(const xstring& val) {{ driver()->context()->parse(val, *t()); }}
		void ST_UnsignedIntHex_reader::read_value(const xstring& val) {{ driver()->context()->parse(val, *t()); }}
		void ST_Ref_reader::read_value(const xstring& val) {{ driver()->context()->parse(val, *t()); }}
		void ST_Guid_reader::read_value(const xstring& val) {{ driver()->context()->parse(val, *t()); }}
		void CT_XStringElement_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_baseTypes_v_literal))
			{
				driver()->context()->parse(value, t()->v);
				return;
			}
		}
		void ST_RefA_reader::read_value(const xstring& val) {{ driver()->context()->parse(val, *t()); }}
		void ST_UnsignedShortHex_reader::read_value(const xstring& val) {{ driver()->context()->parse(val, *t()); }}
	}
}
