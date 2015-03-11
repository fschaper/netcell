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

#include "relationships_readers.hpp"
#include "relationships_literals.hpp"
#include <xio/xml/binding/driver.hpp>

namespace rels_ns
{
	namespace xio
	{
		void CT_Relationship_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, relationships_Id_literal))
			{
				driver()->context()->parse(value, t()->Id.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, relationships_Type_literal))
			{
				driver()->context()->parse(value, t()->Type.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, relationships_Target_literal))
			{
				driver()->context()->parse(value, t()->Target.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, relationships_TargetMode_literal))
			{
				driver()->context()->parse(value, t()->TargetMode.getset());
				return;
			}
		}
		void CT_Relationships_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, relationships_Relationship_literal))
			{
				t()->Relationship.resize(t()->Relationship.size()+1);
				driver()->push(localname, _Relationship_reader.get_reader(&t()->Relationship.back()));
				return;
			}
		}
		void relationships_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, relationships_Relationships_literal))
			{
				driver()->push(localname, _Relationships_reader.get_reader(&t()->Relationships.getset()));
				return;
			}
		}
	}
}
