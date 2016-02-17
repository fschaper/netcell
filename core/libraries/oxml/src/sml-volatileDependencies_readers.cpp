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


#include "sml-volatileDependencies_readers.hpp"
#include "sml-volatileDependencies_literals.hpp"
#include <xio/xml/binding/driver.hpp>

namespace spreadsheetml
{
	namespace xio
	{
		void CT_VolTopicRef_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_volatileDependencies_r_literal))
			{
				driver()->context()->parse(value, t()->r);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_volatileDependencies_s_literal))
			{
				driver()->context()->parse(value, t()->s);
				return;
			}
		}
		void CT_VolTopic_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_volatileDependencies_v_literal))
			{
				driver()->push(localname, _v_reader.get_reader(&t()->v));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_volatileDependencies_stp_literal))
			{
				t()->stp.resize(t()->stp.size()+1);
				driver()->push(localname, _stp_reader.get_reader(&t()->stp.back()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_volatileDependencies_tr_literal))
			{
				t()->tr.resize(t()->tr.size()+1);
				driver()->push(localname, _tr_reader.get_reader(&t()->tr.back()));
				return;
			}
		}
		void CT_VolTopic_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_volatileDependencies_t_literal))
			{
				driver()->context()->parse(value, t()->t);
				return;
			}
		}
		void CT_VolMain_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_volatileDependencies_tp_literal))
			{
				t()->tp.resize(t()->tp.size()+1);
				driver()->push(localname, _tp_reader.get_reader(&t()->tp.back()));
				return;
			}
		}
		void CT_VolMain_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_volatileDependencies_first_literal))
			{
				driver()->context()->parse(value, t()->first);
				return;
			}
		}
		void CT_VolType_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_volatileDependencies_main_literal))
			{
				t()->main.resize(t()->main.size()+1);
				driver()->push(localname, _main_reader.get_reader(&t()->main.back()));
				return;
			}
		}
		void CT_VolType_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_volatileDependencies_type_literal))
			{
				driver()->context()->parse(value, t()->type);
				return;
			}
		}
		void CT_VolTypes_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_volatileDependencies_volType_literal))
			{
				t()->volType.resize(t()->volType.size()+1);
				driver()->push(localname, _volType_reader.get_reader(&t()->volType.back()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_volatileDependencies_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void sml_volatileDependencies_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_volatileDependencies_volTypes_literal))
			{
				driver()->push(localname, _volTypes_reader.get_reader(&t()->volTypes.getset()));
				return;
			}
		}
	}
}
