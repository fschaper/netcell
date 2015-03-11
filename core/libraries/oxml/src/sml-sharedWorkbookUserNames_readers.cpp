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


#include "sml-sharedWorkbookUserNames_readers.hpp"
#include "sml-sharedWorkbookUserNames_literals.hpp"
#include <xio/xml/binding/driver.hpp>

namespace spreadsheetml
{
	namespace xio
	{
		void CT_SharedUser_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookUserNames_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_SharedUser_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookUserNames_guid_literal))
			{
				driver()->context()->parse(value, t()->guid);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookUserNames_name_literal))
			{
				driver()->context()->parse(value, t()->name);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookUserNames_id_literal))
			{
				driver()->context()->parse(value, t()->id);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookUserNames_dateTime_literal))
			{
				driver()->context()->parse(value, t()->dateTime);
				return;
			}
		}
		void CT_Users_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookUserNames_userInfo_literal))
			{
				t()->userInfo.resize(t()->userInfo.size()+1);
				driver()->push(localname, _userInfo_reader.get_reader(&t()->userInfo.back()));
				return;
			}
		}
		void CT_Users_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookUserNames_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
		}
		void sml_sharedWorkbookUserNames_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sharedWorkbookUserNames_users_literal))
			{
				driver()->push(localname, _users_reader.get_reader(&t()->users.getset()));
				return;
			}
		}
	}
}
