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


#include "sml-sharedStringTable_readers.hpp"
#include "sml-sharedStringTable_literals.hpp"
#include <xio/xml/binding/driver.hpp>

namespace spreadsheetml
{
	namespace xio
	{
		void CT_RPrElt_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sharedStringTable_rFont_literal))
			{
				driver()->push(localname, _rFont_reader.get_reader(&t()->rFont.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedStringTable_charset_literal))
			{
				driver()->push(localname, _charset_reader.get_reader(&t()->charset.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedStringTable_family_literal))
			{
				driver()->push(localname, _family_reader.get_reader(&t()->family.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedStringTable_b_literal))
			{
				driver()->push(localname, _b_reader.get_reader(&t()->b.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedStringTable_i_literal))
			{
				driver()->push(localname, _i_reader.get_reader(&t()->i.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedStringTable_strike_literal))
			{
				driver()->push(localname, _strike_reader.get_reader(&t()->strike.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedStringTable_outline_literal))
			{
				driver()->push(localname, _outline_reader.get_reader(&t()->outline.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedStringTable_shadow_literal))
			{
				driver()->push(localname, _shadow_reader.get_reader(&t()->shadow.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedStringTable_condense_literal))
			{
				driver()->push(localname, _condense_reader.get_reader(&t()->condense.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedStringTable_extend_literal))
			{
				driver()->push(localname, _extend_reader.get_reader(&t()->extend.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedStringTable_color_literal))
			{
				driver()->push(localname, _color_reader.get_reader(&t()->color.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedStringTable_sz_literal))
			{
				driver()->push(localname, _sz_reader.get_reader(&t()->sz.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedStringTable_u_literal))
			{
				driver()->push(localname, _u_reader.get_reader(&t()->u.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedStringTable_vertAlign_literal))
			{
				driver()->push(localname, _vertAlign_reader.get_reader(&t()->vertAlign.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedStringTable_scheme_literal))
			{
				driver()->push(localname, _scheme_reader.get_reader(&t()->scheme.getset()));
				return;
			}
		}
		void CT_RElt_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sharedStringTable_rPr_literal))
			{
				driver()->push(localname, _rPr_reader.get_reader(&t()->rPr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedStringTable_t_literal))
			{
				driver()->push(localname, _t_reader.get_reader(&t()->t));
				return;
			}
		}
		void CT_PhoneticRun_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sharedStringTable_t_literal))
			{
				driver()->push(localname, _t_reader.get_reader(&t()->t));
				return;
			}
		}
		void CT_PhoneticRun_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sharedStringTable_sb_literal))
			{
				driver()->context()->parse(value, t()->sb);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedStringTable_eb_literal))
			{
				driver()->context()->parse(value, t()->eb);
				return;
			}
		}
		void CT_PhoneticPr_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sharedStringTable_fontId_literal))
			{
				driver()->context()->parse(value, t()->fontId);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedStringTable_type_literal))
			{
				driver()->context()->parse(value, t()->type);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedStringTable_alignment_literal))
			{
				driver()->context()->parse(value, t()->alignment);
				return;
			}
		}
		void CT_Rst_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sharedStringTable_t_literal))
			{
				driver()->push(localname, _t_reader.get_reader(&t()->t.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedStringTable_r_literal))
			{
				t()->r.resize(t()->r.size()+1);
				driver()->push(localname, _r_reader.get_reader(&t()->r.back()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedStringTable_rPh_literal))
			{
				t()->rPh.resize(t()->rPh.size()+1);
				driver()->push(localname, _rPh_reader.get_reader(&t()->rPh.back()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedStringTable_phoneticPr_literal))
			{
				driver()->push(localname, _phoneticPr_reader.get_reader(&t()->phoneticPr.getset()));
				return;
			}
		}
		void CT_Sst_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sharedStringTable_si_literal))
			{
				t()->si.resize(t()->si.size()+1);
				driver()->push(localname, _si_reader.get_reader(&t()->si.back()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedStringTable_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_Sst_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_sharedStringTable_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_sharedStringTable_uniqueCount_literal))
			{
				driver()->context()->parse(value, t()->uniqueCount.getset());
				return;
			}
		}
		void sml_sharedStringTable_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_sharedStringTable_sst_literal))
			{
				driver()->push(localname, _sst_reader.get_reader(&t()->sst.getset()));
				return;
			}
		}
	}
}
