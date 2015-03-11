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


#include "dml-shapeLineProperties_readers.hpp"
#include "dml-shapeLineProperties_literals.hpp"
#include <xio/xml/binding/driver.hpp>

namespace drawingml
{
	namespace xio
	{
		void CT_PresetLineDashProperties_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeLineProperties_val_literal))
			{
				driver()->context()->parse(value, t()->val.getset());
				return;
			}
		}
		void CT_DashStop_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeLineProperties_d_literal))
			{
				driver()->context()->parse(value, t()->d);
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeLineProperties_sp_literal))
			{
				driver()->context()->parse(value, t()->sp);
				return;
			}
		}
		void CT_DashStopList_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeLineProperties_ds_literal))
			{
				t()->ds.resize(t()->ds.size()+1);
				driver()->push(localname, _ds_reader.get_reader(&t()->ds.back()));
				return;
			}
		}
		void CT_LineJoinMiterProperties_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeLineProperties_lim_literal))
			{
				driver()->context()->parse(value, t()->lim.getset());
				return;
			}
		}
		void CT_LineEndProperties_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeLineProperties_type_literal))
			{
				driver()->context()->parse(value, t()->type.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeLineProperties_w_literal))
			{
				driver()->context()->parse(value, t()->w.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeLineProperties_len_literal))
			{
				driver()->context()->parse(value, t()->len.getset());
				return;
			}
		}
		void CT_LineProperties_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeLineProperties_noFill_literal))
			{
				driver()->push(localname, _noFill_reader.get_reader(&t()->noFill.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeLineProperties_solidFill_literal))
			{
				driver()->push(localname, _solidFill_reader.get_reader(&t()->solidFill.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeLineProperties_gradFill_literal))
			{
				driver()->push(localname, _gradFill_reader.get_reader(&t()->gradFill.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeLineProperties_pattFill_literal))
			{
				driver()->push(localname, _pattFill_reader.get_reader(&t()->pattFill.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeLineProperties_prstDash_literal))
			{
				driver()->push(localname, _prstDash_reader.get_reader(&t()->prstDash.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeLineProperties_custDash_literal))
			{
				driver()->push(localname, _custDash_reader.get_reader(&t()->custDash.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeLineProperties_round_literal))
			{
				driver()->push(localname, _round_reader.get_reader(&t()->round.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeLineProperties_bevel_literal))
			{
				driver()->push(localname, _bevel_reader.get_reader(&t()->bevel.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeLineProperties_miter_literal))
			{
				driver()->push(localname, _miter_reader.get_reader(&t()->miter.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeLineProperties_headEnd_literal))
			{
				driver()->push(localname, _headEnd_reader.get_reader(&t()->headEnd.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeLineProperties_tailEnd_literal))
			{
				driver()->push(localname, _tailEnd_reader.get_reader(&t()->tailEnd.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeLineProperties_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_LineProperties_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, dml_shapeLineProperties_w_literal))
			{
				driver()->context()->parse(value, t()->w.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeLineProperties_cap_literal))
			{
				driver()->context()->parse(value, t()->cap.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeLineProperties_cmpd_literal))
			{
				driver()->context()->parse(value, t()->cmpd.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, dml_shapeLineProperties_algn_literal))
			{
				driver()->context()->parse(value, t()->algn.getset());
				return;
			}
		}
	}
}
