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


#include "sml-calculationChain_readers.hpp"
#include "sml-calculationChain_literals.hpp"
#include <xio/xml/binding/driver.hpp>

namespace spreadsheetml
{
	namespace xio
	{
		void CT_CalcCell_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_calculationChain_r_literal))
			{
				driver()->context()->parse(value, t()->r);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_calculationChain_i_literal))
			{
				driver()->context()->parse(value, t()->i);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_calculationChain_s_literal))
			{
				driver()->context()->parse(value, t()->s);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_calculationChain_l_literal))
			{
				driver()->context()->parse(value, t()->l);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_calculationChain_t_literal))
			{
				driver()->context()->parse(value, t()->t);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_calculationChain_a_literal))
			{
				driver()->context()->parse(value, t()->a);
				return;
			}
		}
		void CT_CalcChain_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_calculationChain_c_literal))
			{
				t()->c.resize(t()->c.size()+1);
				driver()->push(localname, _c_reader.get_reader(&t()->c.back()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_calculationChain_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void sml_calculationChain_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_calculationChain_calcChain_literal))
			{
				driver()->push(localname, _calcChain_reader.get_reader(&t()->calcChain.getset()));
				return;
			}
		}
	}
}
