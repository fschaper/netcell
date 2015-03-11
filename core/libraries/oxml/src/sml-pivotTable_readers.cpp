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


#include "sml-pivotTable_readers.hpp"
#include "sml-pivotTable_literals.hpp"
#include <xio/xml/binding/driver.hpp>

namespace spreadsheetml
{
	namespace xio
	{
		void CT_WorksheetSource_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_ref_literal))
			{
				driver()->context()->parse(value, t()->ref.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_name_literal))
			{
				driver()->context()->parse(value, t()->name.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_sheet_literal))
			{
				driver()->context()->parse(value, t()->sheet.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_id_literal))
			{
				driver()->context()->parse(value, t()->id.getset());
				return;
			}
		}
		void CT_PageItem_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_name_literal))
			{
				driver()->context()->parse(value, t()->name);
				return;
			}
		}
		void CT_PCDSCPage_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_pageItem_literal))
			{
				t()->pageItem.resize(t()->pageItem.size()+1);
				driver()->push(localname, _pageItem_reader.get_reader(&t()->pageItem.back()));
				return;
			}
		}
		void CT_PCDSCPage_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
		}
		void CT_Pages_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_page_literal))
			{
				t()->page.resize(t()->page.size()+1);
				driver()->push(localname, _page_reader.get_reader(&t()->page.back()));
				return;
			}
		}
		void CT_Pages_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
		}
		void CT_RangeSet_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_i1_literal))
			{
				driver()->context()->parse(value, t()->i1.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_i2_literal))
			{
				driver()->context()->parse(value, t()->i2.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_i3_literal))
			{
				driver()->context()->parse(value, t()->i3.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_i4_literal))
			{
				driver()->context()->parse(value, t()->i4.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_ref_literal))
			{
				driver()->context()->parse(value, t()->ref.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_name_literal))
			{
				driver()->context()->parse(value, t()->name.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_sheet_literal))
			{
				driver()->context()->parse(value, t()->sheet.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_id_literal))
			{
				driver()->context()->parse(value, t()->id.getset());
				return;
			}
		}
		void CT_RangeSets_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_rangeSet_literal))
			{
				t()->rangeSet.resize(t()->rangeSet.size()+1);
				driver()->push(localname, _rangeSet_reader.get_reader(&t()->rangeSet.back()));
				return;
			}
		}
		void CT_RangeSets_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
		}
		void CT_Consolidation_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_pages_literal))
			{
				driver()->push(localname, _pages_reader.get_reader(&t()->pages.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_rangeSets_literal))
			{
				driver()->push(localname, _rangeSets_reader.get_reader(&t()->rangeSets));
				return;
			}
		}
		void CT_Consolidation_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_autoPage_literal))
			{
				driver()->context()->parse(value, t()->autoPage);
				return;
			}
		}
		void CT_CacheSource_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_worksheetSource_literal))
			{
				driver()->push(localname, _worksheetSource_reader.get_reader(&t()->worksheetSource.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_consolidation_literal))
			{
				driver()->push(localname, _consolidation_reader.get_reader(&t()->consolidation.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_CacheSource_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_type_literal))
			{
				driver()->context()->parse(value, t()->type);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_connectionId_literal))
			{
				driver()->context()->parse(value, t()->connectionId);
				return;
			}
		}
		void CT_Tuple_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_fld_literal))
			{
				driver()->context()->parse(value, t()->fld.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_hier_literal))
			{
				driver()->context()->parse(value, t()->hier.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_item_literal))
			{
				driver()->context()->parse(value, t()->item);
				return;
			}
		}
		void CT_Tuples_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_tpl_literal))
			{
				t()->tpl.resize(t()->tpl.size()+1);
				driver()->push(localname, _tpl_reader.get_reader(&t()->tpl.back()));
				return;
			}
		}
		void CT_Tuples_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_c_literal))
			{
				driver()->context()->parse(value, t()->c.getset());
				return;
			}
		}
		void CT_X_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_v_literal))
			{
				driver()->context()->parse(value, t()->v);
				return;
			}
		}
		void CT_Missing_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_tpls_literal))
			{
				t()->tpls.resize(t()->tpls.size()+1);
				driver()->push(localname, _tpls_reader.get_reader(&t()->tpls.back()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_x_literal))
			{
				t()->x.resize(t()->x.size()+1);
				driver()->push(localname, _x_reader.get_reader(&t()->x.back()));
				return;
			}
		}
		void CT_Missing_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_u_literal))
			{
				driver()->context()->parse(value, t()->u.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_f_literal))
			{
				driver()->context()->parse(value, t()->f.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_c_literal))
			{
				driver()->context()->parse(value, t()->c.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_cp_literal))
			{
				driver()->context()->parse(value, t()->cp.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_in_literal))
			{
				driver()->context()->parse(value, t()->in.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_bc_literal))
			{
				driver()->context()->parse(value, t()->bc.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_fc_literal))
			{
				driver()->context()->parse(value, t()->fc.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_i_literal))
			{
				driver()->context()->parse(value, t()->i);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_un_literal))
			{
				driver()->context()->parse(value, t()->un);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_st_literal))
			{
				driver()->context()->parse(value, t()->st);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_b_literal))
			{
				driver()->context()->parse(value, t()->b);
				return;
			}
		}
		void CT_Number_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_tpls_literal))
			{
				t()->tpls.resize(t()->tpls.size()+1);
				driver()->push(localname, _tpls_reader.get_reader(&t()->tpls.back()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_x_literal))
			{
				t()->x.resize(t()->x.size()+1);
				driver()->push(localname, _x_reader.get_reader(&t()->x.back()));
				return;
			}
		}
		void CT_Number_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_v_literal))
			{
				driver()->context()->parse(value, t()->v);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_u_literal))
			{
				driver()->context()->parse(value, t()->u.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_f_literal))
			{
				driver()->context()->parse(value, t()->f.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_c_literal))
			{
				driver()->context()->parse(value, t()->c.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_cp_literal))
			{
				driver()->context()->parse(value, t()->cp.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_in_literal))
			{
				driver()->context()->parse(value, t()->in.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_bc_literal))
			{
				driver()->context()->parse(value, t()->bc.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_fc_literal))
			{
				driver()->context()->parse(value, t()->fc.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_i_literal))
			{
				driver()->context()->parse(value, t()->i);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_un_literal))
			{
				driver()->context()->parse(value, t()->un);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_st_literal))
			{
				driver()->context()->parse(value, t()->st);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_b_literal))
			{
				driver()->context()->parse(value, t()->b);
				return;
			}
		}
		void CT_Boolean_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_x_literal))
			{
				t()->x.resize(t()->x.size()+1);
				driver()->push(localname, _x_reader.get_reader(&t()->x.back()));
				return;
			}
		}
		void CT_Boolean_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_v_literal))
			{
				driver()->context()->parse(value, t()->v);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_u_literal))
			{
				driver()->context()->parse(value, t()->u.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_f_literal))
			{
				driver()->context()->parse(value, t()->f.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_c_literal))
			{
				driver()->context()->parse(value, t()->c.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_cp_literal))
			{
				driver()->context()->parse(value, t()->cp.getset());
				return;
			}
		}
		void CT_Error_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_tpls_literal))
			{
				driver()->push(localname, _tpls_reader.get_reader(&t()->tpls.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_x_literal))
			{
				t()->x.resize(t()->x.size()+1);
				driver()->push(localname, _x_reader.get_reader(&t()->x.back()));
				return;
			}
		}
		void CT_Error_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_v_literal))
			{
				driver()->context()->parse(value, t()->v);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_u_literal))
			{
				driver()->context()->parse(value, t()->u.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_f_literal))
			{
				driver()->context()->parse(value, t()->f.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_c_literal))
			{
				driver()->context()->parse(value, t()->c.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_cp_literal))
			{
				driver()->context()->parse(value, t()->cp.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_in_literal))
			{
				driver()->context()->parse(value, t()->in.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_bc_literal))
			{
				driver()->context()->parse(value, t()->bc.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_fc_literal))
			{
				driver()->context()->parse(value, t()->fc.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_i_literal))
			{
				driver()->context()->parse(value, t()->i);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_un_literal))
			{
				driver()->context()->parse(value, t()->un);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_st_literal))
			{
				driver()->context()->parse(value, t()->st);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_b_literal))
			{
				driver()->context()->parse(value, t()->b);
				return;
			}
		}
		void CT_String_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_tpls_literal))
			{
				t()->tpls.resize(t()->tpls.size()+1);
				driver()->push(localname, _tpls_reader.get_reader(&t()->tpls.back()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_x_literal))
			{
				t()->x.resize(t()->x.size()+1);
				driver()->push(localname, _x_reader.get_reader(&t()->x.back()));
				return;
			}
		}
		void CT_String_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_v_literal))
			{
				driver()->context()->parse(value, t()->v);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_u_literal))
			{
				driver()->context()->parse(value, t()->u.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_f_literal))
			{
				driver()->context()->parse(value, t()->f.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_c_literal))
			{
				driver()->context()->parse(value, t()->c.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_cp_literal))
			{
				driver()->context()->parse(value, t()->cp.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_in_literal))
			{
				driver()->context()->parse(value, t()->in.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_bc_literal))
			{
				driver()->context()->parse(value, t()->bc.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_fc_literal))
			{
				driver()->context()->parse(value, t()->fc.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_i_literal))
			{
				driver()->context()->parse(value, t()->i);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_un_literal))
			{
				driver()->context()->parse(value, t()->un);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_st_literal))
			{
				driver()->context()->parse(value, t()->st);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_b_literal))
			{
				driver()->context()->parse(value, t()->b);
				return;
			}
		}
		void CT_DateTime_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_x_literal))
			{
				t()->x.resize(t()->x.size()+1);
				driver()->push(localname, _x_reader.get_reader(&t()->x.back()));
				return;
			}
		}
		void CT_DateTime_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_v_literal))
			{
				driver()->context()->parse(value, t()->v);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_u_literal))
			{
				driver()->context()->parse(value, t()->u.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_f_literal))
			{
				driver()->context()->parse(value, t()->f.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_c_literal))
			{
				driver()->context()->parse(value, t()->c.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_cp_literal))
			{
				driver()->context()->parse(value, t()->cp.getset());
				return;
			}
		}
		void CT_SharedItems_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_m_literal))
			{
				driver()->push(localname, _m_reader.get_reader(&t()->m.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_n_literal))
			{
				driver()->push(localname, _n_reader.get_reader(&t()->n.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_b_literal))
			{
				driver()->push(localname, _b_reader.get_reader(&t()->b.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_e_literal))
			{
				driver()->push(localname, _e_reader.get_reader(&t()->e.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_s_literal))
			{
				driver()->push(localname, _s_reader.get_reader(&t()->s.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_d_literal))
			{
				driver()->push(localname, _d_reader.get_reader(&t()->d.getset()));
				return;
			}
		}
		void CT_SharedItems_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_containsSemiMixedTypes_literal))
			{
				driver()->context()->parse(value, t()->containsSemiMixedTypes);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_containsNonDate_literal))
			{
				driver()->context()->parse(value, t()->containsNonDate);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_containsDate_literal))
			{
				driver()->context()->parse(value, t()->containsDate);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_containsString_literal))
			{
				driver()->context()->parse(value, t()->containsString);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_containsBlank_literal))
			{
				driver()->context()->parse(value, t()->containsBlank);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_containsMixedTypes_literal))
			{
				driver()->context()->parse(value, t()->containsMixedTypes);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_containsNumber_literal))
			{
				driver()->context()->parse(value, t()->containsNumber);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_containsInteger_literal))
			{
				driver()->context()->parse(value, t()->containsInteger);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_minValue_literal))
			{
				driver()->context()->parse(value, t()->minValue.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_maxValue_literal))
			{
				driver()->context()->parse(value, t()->maxValue.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_minDate_literal))
			{
				driver()->context()->parse(value, t()->minDate.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_maxDate_literal))
			{
				driver()->context()->parse(value, t()->maxDate.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_longText_literal))
			{
				driver()->context()->parse(value, t()->longText);
				return;
			}
		}
		void CT_RangePr_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_autoStart_literal))
			{
				driver()->context()->parse(value, t()->autoStart);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_autoEnd_literal))
			{
				driver()->context()->parse(value, t()->autoEnd);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_groupBy_literal))
			{
				driver()->context()->parse(value, t()->groupBy);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_startNum_literal))
			{
				driver()->context()->parse(value, t()->startNum.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_endNum_literal))
			{
				driver()->context()->parse(value, t()->endNum.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_startDate_literal))
			{
				driver()->context()->parse(value, t()->startDate.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_endDate_literal))
			{
				driver()->context()->parse(value, t()->endDate.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_groupInterval_literal))
			{
				driver()->context()->parse(value, t()->groupInterval);
				return;
			}
		}
		void CT_DiscretePr_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_x_literal))
			{
				t()->x.resize(t()->x.size()+1);
				driver()->push(localname, _x_reader.get_reader(&t()->x.back()));
				return;
			}
		}
		void CT_DiscretePr_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
		}
		void CT_GroupItems_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_m_literal))
			{
				driver()->push(localname, _m_reader.get_reader(&t()->m.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_n_literal))
			{
				driver()->push(localname, _n_reader.get_reader(&t()->n.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_b_literal))
			{
				driver()->push(localname, _b_reader.get_reader(&t()->b.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_e_literal))
			{
				driver()->push(localname, _e_reader.get_reader(&t()->e.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_s_literal))
			{
				driver()->push(localname, _s_reader.get_reader(&t()->s.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_d_literal))
			{
				driver()->push(localname, _d_reader.get_reader(&t()->d.getset()));
				return;
			}
		}
		void CT_GroupItems_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
		}
		void CT_FieldGroup_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_rangePr_literal))
			{
				driver()->push(localname, _rangePr_reader.get_reader(&t()->rangePr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_discretePr_literal))
			{
				driver()->push(localname, _discretePr_reader.get_reader(&t()->discretePr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_groupItems_literal))
			{
				driver()->push(localname, _groupItems_reader.get_reader(&t()->groupItems.getset()));
				return;
			}
		}
		void CT_FieldGroup_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_par_literal))
			{
				driver()->context()->parse(value, t()->par.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_base_literal))
			{
				driver()->context()->parse(value, t()->base.getset());
				return;
			}
		}
		void CT_CacheField_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_sharedItems_literal))
			{
				driver()->push(localname, _sharedItems_reader.get_reader(&t()->sharedItems.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_fieldGroup_literal))
			{
				driver()->push(localname, _fieldGroup_reader.get_reader(&t()->fieldGroup.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_mpMap_literal))
			{
				t()->mpMap.resize(t()->mpMap.size()+1);
				driver()->push(localname, _mpMap_reader.get_reader(&t()->mpMap.back()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_CacheField_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_name_literal))
			{
				driver()->context()->parse(value, t()->name);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_caption_literal))
			{
				driver()->context()->parse(value, t()->caption.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_propertyName_literal))
			{
				driver()->context()->parse(value, t()->propertyName.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_serverField_literal))
			{
				driver()->context()->parse(value, t()->serverField);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_uniqueList_literal))
			{
				driver()->context()->parse(value, t()->uniqueList);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_numFmtId_literal))
			{
				driver()->context()->parse(value, t()->numFmtId.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_formula_literal))
			{
				driver()->context()->parse(value, t()->formula.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_sqlType_literal))
			{
				driver()->context()->parse(value, t()->sqlType);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_hierarchy_literal))
			{
				driver()->context()->parse(value, t()->hierarchy);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_level_literal))
			{
				driver()->context()->parse(value, t()->level);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_databaseField_literal))
			{
				driver()->context()->parse(value, t()->databaseField);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_mappingCount_literal))
			{
				driver()->context()->parse(value, t()->mappingCount.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_memberPropertyField_literal))
			{
				driver()->context()->parse(value, t()->memberPropertyField);
				return;
			}
		}
		void CT_CacheFields_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_cacheField_literal))
			{
				t()->cacheField.resize(t()->cacheField.size()+1);
				driver()->push(localname, _cacheField_reader.get_reader(&t()->cacheField.back()));
				return;
			}
		}
		void CT_CacheFields_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
		}
		void CT_FieldUsage_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_x_literal))
			{
				driver()->context()->parse(value, t()->x);
				return;
			}
		}
		void CT_FieldsUsage_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_fieldUsage_literal))
			{
				t()->fieldUsage.resize(t()->fieldUsage.size()+1);
				driver()->push(localname, _fieldUsage_reader.get_reader(&t()->fieldUsage.back()));
				return;
			}
		}
		void CT_FieldsUsage_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
		}
		void CT_GroupMember_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_uniqueName_literal))
			{
				driver()->context()->parse(value, t()->uniqueName);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_group_literal))
			{
				driver()->context()->parse(value, t()->group);
				return;
			}
		}
		void CT_GroupMembers_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_groupMember_literal))
			{
				t()->groupMember.resize(t()->groupMember.size()+1);
				driver()->push(localname, _groupMember_reader.get_reader(&t()->groupMember.back()));
				return;
			}
		}
		void CT_GroupMembers_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
		}
		void CT_LevelGroup_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_groupMembers_literal))
			{
				driver()->push(localname, _groupMembers_reader.get_reader(&t()->groupMembers));
				return;
			}
		}
		void CT_LevelGroup_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_name_literal))
			{
				driver()->context()->parse(value, t()->name);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_uniqueName_literal))
			{
				driver()->context()->parse(value, t()->uniqueName);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_caption_literal))
			{
				driver()->context()->parse(value, t()->caption);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_uniqueParent_literal))
			{
				driver()->context()->parse(value, t()->uniqueParent.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_id_literal))
			{
				driver()->context()->parse(value, t()->id.getset());
				return;
			}
		}
		void CT_Groups_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_group_literal))
			{
				t()->group.resize(t()->group.size()+1);
				driver()->push(localname, _group_reader.get_reader(&t()->group.back()));
				return;
			}
		}
		void CT_Groups_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
		}
		void CT_GroupLevel_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_groups_literal))
			{
				driver()->push(localname, _groups_reader.get_reader(&t()->groups.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_GroupLevel_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_uniqueName_literal))
			{
				driver()->context()->parse(value, t()->uniqueName);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_caption_literal))
			{
				driver()->context()->parse(value, t()->caption);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_user_literal))
			{
				driver()->context()->parse(value, t()->user);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_customRollUp_literal))
			{
				driver()->context()->parse(value, t()->customRollUp);
				return;
			}
		}
		void CT_GroupLevels_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_groupLevel_literal))
			{
				t()->groupLevel.resize(t()->groupLevel.size()+1);
				driver()->push(localname, _groupLevel_reader.get_reader(&t()->groupLevel.back()));
				return;
			}
		}
		void CT_GroupLevels_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
		}
		void CT_CacheHierarchy_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_fieldsUsage_literal))
			{
				driver()->push(localname, _fieldsUsage_reader.get_reader(&t()->fieldsUsage.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_groupLevels_literal))
			{
				driver()->push(localname, _groupLevels_reader.get_reader(&t()->groupLevels.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_CacheHierarchy_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_uniqueName_literal))
			{
				driver()->context()->parse(value, t()->uniqueName);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_caption_literal))
			{
				driver()->context()->parse(value, t()->caption.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_measure_literal))
			{
				driver()->context()->parse(value, t()->measure);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_set_literal))
			{
				driver()->context()->parse(value, t()->set);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_parentSet_literal))
			{
				driver()->context()->parse(value, t()->parentSet.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_iconSet_literal))
			{
				driver()->context()->parse(value, t()->iconSet);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_attribute_literal))
			{
				driver()->context()->parse(value, t()->attribute);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_time_literal))
			{
				driver()->context()->parse(value, t()->time);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_keyAttribute_literal))
			{
				driver()->context()->parse(value, t()->keyAttribute);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_defaultMemberUniqueName_literal))
			{
				driver()->context()->parse(value, t()->defaultMemberUniqueName.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_allUniqueName_literal))
			{
				driver()->context()->parse(value, t()->allUniqueName.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_allCaption_literal))
			{
				driver()->context()->parse(value, t()->allCaption.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_dimensionUniqueName_literal))
			{
				driver()->context()->parse(value, t()->dimensionUniqueName.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_displayFolder_literal))
			{
				driver()->context()->parse(value, t()->displayFolder.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_measureGroup_literal))
			{
				driver()->context()->parse(value, t()->measureGroup.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_measures_literal))
			{
				driver()->context()->parse(value, t()->measures);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_count_literal))
			{
				driver()->context()->parse(value, t()->count);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_oneField_literal))
			{
				driver()->context()->parse(value, t()->oneField);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_memberValueDatatype_literal))
			{
				driver()->context()->parse(value, t()->memberValueDatatype.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_unbalanced_literal))
			{
				driver()->context()->parse(value, t()->unbalanced.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_unbalancedGroup_literal))
			{
				driver()->context()->parse(value, t()->unbalancedGroup.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_hidden_literal))
			{
				driver()->context()->parse(value, t()->hidden);
				return;
			}
		}
		void CT_CacheHierarchies_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_cacheHierarchy_literal))
			{
				t()->cacheHierarchy.resize(t()->cacheHierarchy.size()+1);
				driver()->push(localname, _cacheHierarchy_reader.get_reader(&t()->cacheHierarchy.back()));
				return;
			}
		}
		void CT_CacheHierarchies_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
		}
		void CT_PCDKPI_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_uniqueName_literal))
			{
				driver()->context()->parse(value, t()->uniqueName);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_caption_literal))
			{
				driver()->context()->parse(value, t()->caption.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_displayFolder_literal))
			{
				driver()->context()->parse(value, t()->displayFolder.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_measureGroup_literal))
			{
				driver()->context()->parse(value, t()->measureGroup.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_parent_literal))
			{
				driver()->context()->parse(value, t()->parent.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_value_literal))
			{
				driver()->context()->parse(value, t()->value);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_goal_literal))
			{
				driver()->context()->parse(value, t()->goal.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_status_literal))
			{
				driver()->context()->parse(value, t()->status.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_trend_literal))
			{
				driver()->context()->parse(value, t()->trend.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_weight_literal))
			{
				driver()->context()->parse(value, t()->weight.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_time_literal))
			{
				driver()->context()->parse(value, t()->time.getset());
				return;
			}
		}
		void CT_PCDKPIs_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_kpi_literal))
			{
				t()->kpi.resize(t()->kpi.size()+1);
				driver()->push(localname, _kpi_reader.get_reader(&t()->kpi.back()));
				return;
			}
		}
		void CT_PCDKPIs_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
		}
		void CT_PCDSDTCEntries_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_m_literal))
			{
				driver()->push(localname, _m_reader.get_reader(&t()->m.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_n_literal))
			{
				driver()->push(localname, _n_reader.get_reader(&t()->n.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_e_literal))
			{
				driver()->push(localname, _e_reader.get_reader(&t()->e.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_s_literal))
			{
				driver()->push(localname, _s_reader.get_reader(&t()->s.getset()));
				return;
			}
		}
		void CT_PCDSDTCEntries_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
		}
		void CT_Set_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_tpls_literal))
			{
				t()->tpls.resize(t()->tpls.size()+1);
				driver()->push(localname, _tpls_reader.get_reader(&t()->tpls.back()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_sortByTuple_literal))
			{
				driver()->push(localname, _sortByTuple_reader.get_reader(&t()->sortByTuple.getset()));
				return;
			}
		}
		void CT_Set_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_maxRank_literal))
			{
				driver()->context()->parse(value, t()->maxRank);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_setDefinition_literal))
			{
				driver()->context()->parse(value, t()->setDefinition);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_sortType_literal))
			{
				driver()->context()->parse(value, t()->sortType);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_queryFailed_literal))
			{
				driver()->context()->parse(value, t()->queryFailed);
				return;
			}
		}
		void CT_Sets_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_set_literal))
			{
				t()->set.resize(t()->set.size()+1);
				driver()->push(localname, _set_reader.get_reader(&t()->set.back()));
				return;
			}
		}
		void CT_Sets_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
		}
		void CT_Query_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_tpls_literal))
			{
				driver()->push(localname, _tpls_reader.get_reader(&t()->tpls.getset()));
				return;
			}
		}
		void CT_Query_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_mdx_literal))
			{
				driver()->context()->parse(value, t()->mdx);
				return;
			}
		}
		void CT_QueryCache_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_query_literal))
			{
				t()->query.resize(t()->query.size()+1);
				driver()->push(localname, _query_reader.get_reader(&t()->query.back()));
				return;
			}
		}
		void CT_QueryCache_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
		}
		void CT_ServerFormat_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_culture_literal))
			{
				driver()->context()->parse(value, t()->culture.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_format_literal))
			{
				driver()->context()->parse(value, t()->format.getset());
				return;
			}
		}
		void CT_ServerFormats_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_serverFormat_literal))
			{
				t()->serverFormat.resize(t()->serverFormat.size()+1);
				driver()->push(localname, _serverFormat_reader.get_reader(&t()->serverFormat.back()));
				return;
			}
		}
		void CT_ServerFormats_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
		}
		void CT_TupleCache_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_entries_literal))
			{
				driver()->push(localname, _entries_reader.get_reader(&t()->entries.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_sets_literal))
			{
				driver()->push(localname, _sets_reader.get_reader(&t()->sets.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_queryCache_literal))
			{
				driver()->push(localname, _queryCache_reader.get_reader(&t()->queryCache.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_serverFormats_literal))
			{
				driver()->push(localname, _serverFormats_reader.get_reader(&t()->serverFormats.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_CalculatedItem_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_pivotArea_literal))
			{
				driver()->push(localname, _pivotArea_reader.get_reader(&t()->pivotArea));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_CalculatedItem_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_field_literal))
			{
				driver()->context()->parse(value, t()->field.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_formula_literal))
			{
				driver()->context()->parse(value, t()->formula.getset());
				return;
			}
		}
		void CT_CalculatedItems_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_calculatedItem_literal))
			{
				t()->calculatedItem.resize(t()->calculatedItem.size()+1);
				driver()->push(localname, _calculatedItem_reader.get_reader(&t()->calculatedItem.back()));
				return;
			}
		}
		void CT_CalculatedItems_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
		}
		void CT_CalculatedMember_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_CalculatedMember_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_name_literal))
			{
				driver()->context()->parse(value, t()->name);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_mdx_literal))
			{
				driver()->context()->parse(value, t()->mdx);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_memberName_literal))
			{
				driver()->context()->parse(value, t()->memberName.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_hierarchy_literal))
			{
				driver()->context()->parse(value, t()->hierarchy.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_parent_literal))
			{
				driver()->context()->parse(value, t()->parent.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_solveOrder_literal))
			{
				driver()->context()->parse(value, t()->solveOrder);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_set_literal))
			{
				driver()->context()->parse(value, t()->set);
				return;
			}
		}
		void CT_CalculatedMembers_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_calculatedMember_literal))
			{
				t()->calculatedMember.resize(t()->calculatedMember.size()+1);
				driver()->push(localname, _calculatedMember_reader.get_reader(&t()->calculatedMember.back()));
				return;
			}
		}
		void CT_CalculatedMembers_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
		}
		void CT_PivotDimension_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_measure_literal))
			{
				driver()->context()->parse(value, t()->measure);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_name_literal))
			{
				driver()->context()->parse(value, t()->name);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_uniqueName_literal))
			{
				driver()->context()->parse(value, t()->uniqueName);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_caption_literal))
			{
				driver()->context()->parse(value, t()->caption);
				return;
			}
		}
		void CT_Dimensions_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_dimension_literal))
			{
				t()->dimension.resize(t()->dimension.size()+1);
				driver()->push(localname, _dimension_reader.get_reader(&t()->dimension.back()));
				return;
			}
		}
		void CT_Dimensions_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
		}
		void CT_MeasureGroup_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_name_literal))
			{
				driver()->context()->parse(value, t()->name);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_caption_literal))
			{
				driver()->context()->parse(value, t()->caption);
				return;
			}
		}
		void CT_MeasureGroups_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_measureGroup_literal))
			{
				t()->measureGroup.resize(t()->measureGroup.size()+1);
				driver()->push(localname, _measureGroup_reader.get_reader(&t()->measureGroup.back()));
				return;
			}
		}
		void CT_MeasureGroups_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
		}
		void CT_MeasureDimensionMap_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_measureGroup_literal))
			{
				driver()->context()->parse(value, t()->measureGroup.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_dimension_literal))
			{
				driver()->context()->parse(value, t()->dimension.getset());
				return;
			}
		}
		void CT_MeasureDimensionMaps_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_map_literal))
			{
				t()->map.resize(t()->map.size()+1);
				driver()->push(localname, _map_reader.get_reader(&t()->map.back()));
				return;
			}
		}
		void CT_MeasureDimensionMaps_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
		}
		void CT_PivotCacheDefinition_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_cacheSource_literal))
			{
				driver()->push(localname, _cacheSource_reader.get_reader(&t()->cacheSource));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_cacheFields_literal))
			{
				driver()->push(localname, _cacheFields_reader.get_reader(&t()->cacheFields));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_cacheHierarchies_literal))
			{
				driver()->push(localname, _cacheHierarchies_reader.get_reader(&t()->cacheHierarchies.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_kpis_literal))
			{
				driver()->push(localname, _kpis_reader.get_reader(&t()->kpis.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_tupleCache_literal))
			{
				driver()->push(localname, _tupleCache_reader.get_reader(&t()->tupleCache.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_calculatedItems_literal))
			{
				driver()->push(localname, _calculatedItems_reader.get_reader(&t()->calculatedItems.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_calculatedMembers_literal))
			{
				driver()->push(localname, _calculatedMembers_reader.get_reader(&t()->calculatedMembers.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_dimensions_literal))
			{
				driver()->push(localname, _dimensions_reader.get_reader(&t()->dimensions.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_measureGroups_literal))
			{
				driver()->push(localname, _measureGroups_reader.get_reader(&t()->measureGroups.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_maps_literal))
			{
				driver()->push(localname, _maps_reader.get_reader(&t()->maps.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_PivotCacheDefinition_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_id_literal))
			{
				driver()->context()->parse(value, t()->id.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_invalid_literal))
			{
				driver()->context()->parse(value, t()->invalid);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_saveData_literal))
			{
				driver()->context()->parse(value, t()->saveData);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_refreshOnLoad_literal))
			{
				driver()->context()->parse(value, t()->refreshOnLoad);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_optimizeMemory_literal))
			{
				driver()->context()->parse(value, t()->optimizeMemory);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_enableRefresh_literal))
			{
				driver()->context()->parse(value, t()->enableRefresh);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_refreshedBy_literal))
			{
				driver()->context()->parse(value, t()->refreshedBy.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_refreshedDate_literal))
			{
				driver()->context()->parse(value, t()->refreshedDate.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_backgroundQuery_literal))
			{
				driver()->context()->parse(value, t()->backgroundQuery);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_missingItemsLimit_literal))
			{
				driver()->context()->parse(value, t()->missingItemsLimit.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_createdVersion_literal))
			{
				driver()->context()->parse(value, t()->createdVersion);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_refreshedVersion_literal))
			{
				driver()->context()->parse(value, t()->refreshedVersion);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_minRefreshableVersion_literal))
			{
				driver()->context()->parse(value, t()->minRefreshableVersion);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_recordCount_literal))
			{
				driver()->context()->parse(value, t()->recordCount.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_upgradeOnRefresh_literal))
			{
				driver()->context()->parse(value, t()->upgradeOnRefresh);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_tupleCache_literal))
			{
				driver()->context()->parse(value, t()->tupleCache_attr);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_supportSubquery_literal))
			{
				driver()->context()->parse(value, t()->supportSubquery);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_supportAdvancedDrill_literal))
			{
				driver()->context()->parse(value, t()->supportAdvancedDrill);
				return;
			}
		}
		void CT_Record_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_m_literal))
			{
				driver()->push(localname, _m_reader.get_reader(&t()->m.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_n_literal))
			{
				driver()->push(localname, _n_reader.get_reader(&t()->n.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_b_literal))
			{
				driver()->push(localname, _b_reader.get_reader(&t()->b.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_e_literal))
			{
				driver()->push(localname, _e_reader.get_reader(&t()->e.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_s_literal))
			{
				driver()->push(localname, _s_reader.get_reader(&t()->s.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_d_literal))
			{
				driver()->push(localname, _d_reader.get_reader(&t()->d.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_x_literal))
			{
				driver()->push(localname, _x_reader.get_reader(&t()->x.getset()));
				return;
			}
		}
		void CT_PivotCacheRecords_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_r_literal))
			{
				t()->r.resize(t()->r.size()+1);
				driver()->push(localname, _r_reader.get_reader(&t()->r.back()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_PivotCacheRecords_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
		}
		void CT_Location_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_ref_literal))
			{
				driver()->context()->parse(value, t()->ref);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_firstHeaderRow_literal))
			{
				driver()->context()->parse(value, t()->firstHeaderRow);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_firstDataRow_literal))
			{
				driver()->context()->parse(value, t()->firstDataRow);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_firstDataCol_literal))
			{
				driver()->context()->parse(value, t()->firstDataCol);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_rowPageCount_literal))
			{
				driver()->context()->parse(value, t()->rowPageCount);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_colPageCount_literal))
			{
				driver()->context()->parse(value, t()->colPageCount);
				return;
			}
		}
		void CT_Item_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_n_literal))
			{
				driver()->context()->parse(value, t()->n.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_t_literal))
			{
				driver()->context()->parse(value, t()->t);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_h_literal))
			{
				driver()->context()->parse(value, t()->h);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_s_literal))
			{
				driver()->context()->parse(value, t()->s);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_sd_literal))
			{
				driver()->context()->parse(value, t()->sd);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_f_literal))
			{
				driver()->context()->parse(value, t()->f);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_m_literal))
			{
				driver()->context()->parse(value, t()->m);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_c_literal))
			{
				driver()->context()->parse(value, t()->c);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_x_literal))
			{
				driver()->context()->parse(value, t()->x.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_d_literal))
			{
				driver()->context()->parse(value, t()->d);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_e_literal))
			{
				driver()->context()->parse(value, t()->e);
				return;
			}
		}
		void CT_Items_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_item_literal))
			{
				t()->item.resize(t()->item.size()+1);
				driver()->push(localname, _item_reader.get_reader(&t()->item.back()));
				return;
			}
		}
		void CT_Items_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
		}
		void CT_AutoSortScope_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_pivotArea_literal))
			{
				driver()->push(localname, _pivotArea_reader.get_reader(&t()->pivotArea));
				return;
			}
		}
		void CT_PivotField_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_items_literal))
			{
				driver()->push(localname, _items_reader.get_reader(&t()->items.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_autoSortScope_literal))
			{
				driver()->push(localname, _autoSortScope_reader.get_reader(&t()->autoSortScope.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_PivotField_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_name_literal))
			{
				driver()->context()->parse(value, t()->name.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_axis_literal))
			{
				driver()->context()->parse(value, t()->axis.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_dataField_literal))
			{
				driver()->context()->parse(value, t()->dataField);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_subtotalCaption_literal))
			{
				driver()->context()->parse(value, t()->subtotalCaption.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_showDropDowns_literal))
			{
				driver()->context()->parse(value, t()->showDropDowns);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_hiddenLevel_literal))
			{
				driver()->context()->parse(value, t()->hiddenLevel);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_uniqueMemberProperty_literal))
			{
				driver()->context()->parse(value, t()->uniqueMemberProperty.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_compact_literal))
			{
				driver()->context()->parse(value, t()->compact);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_allDrilled_literal))
			{
				driver()->context()->parse(value, t()->allDrilled);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_numFmtId_literal))
			{
				driver()->context()->parse(value, t()->numFmtId.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_outline_literal))
			{
				driver()->context()->parse(value, t()->outline);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_subtotalTop_literal))
			{
				driver()->context()->parse(value, t()->subtotalTop);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_dragToRow_literal))
			{
				driver()->context()->parse(value, t()->dragToRow);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_dragToCol_literal))
			{
				driver()->context()->parse(value, t()->dragToCol);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_multipleItemSelectionAllowed_literal))
			{
				driver()->context()->parse(value, t()->multipleItemSelectionAllowed);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_dragToPage_literal))
			{
				driver()->context()->parse(value, t()->dragToPage);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_dragToData_literal))
			{
				driver()->context()->parse(value, t()->dragToData);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_dragOff_literal))
			{
				driver()->context()->parse(value, t()->dragOff);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_showAll_literal))
			{
				driver()->context()->parse(value, t()->showAll);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_insertBlankRow_literal))
			{
				driver()->context()->parse(value, t()->insertBlankRow);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_serverField_literal))
			{
				driver()->context()->parse(value, t()->serverField);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_insertPageBreak_literal))
			{
				driver()->context()->parse(value, t()->insertPageBreak);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_autoShow_literal))
			{
				driver()->context()->parse(value, t()->autoShow);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_topAutoShow_literal))
			{
				driver()->context()->parse(value, t()->topAutoShow);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_hideNewItems_literal))
			{
				driver()->context()->parse(value, t()->hideNewItems);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_measureFilter_literal))
			{
				driver()->context()->parse(value, t()->measureFilter);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_includeNewItemsInFilter_literal))
			{
				driver()->context()->parse(value, t()->includeNewItemsInFilter);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_itemPageCount_literal))
			{
				driver()->context()->parse(value, t()->itemPageCount);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_sortType_literal))
			{
				driver()->context()->parse(value, t()->sortType);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_dataSourceSort_literal))
			{
				driver()->context()->parse(value, t()->dataSourceSort.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_nonAutoSortDefault_literal))
			{
				driver()->context()->parse(value, t()->nonAutoSortDefault);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_rankBy_literal))
			{
				driver()->context()->parse(value, t()->rankBy.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_defaultSubtotal_literal))
			{
				driver()->context()->parse(value, t()->defaultSubtotal);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_sumSubtotal_literal))
			{
				driver()->context()->parse(value, t()->sumSubtotal);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_countASubtotal_literal))
			{
				driver()->context()->parse(value, t()->countASubtotal);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_avgSubtotal_literal))
			{
				driver()->context()->parse(value, t()->avgSubtotal);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_maxSubtotal_literal))
			{
				driver()->context()->parse(value, t()->maxSubtotal);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_minSubtotal_literal))
			{
				driver()->context()->parse(value, t()->minSubtotal);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_productSubtotal_literal))
			{
				driver()->context()->parse(value, t()->productSubtotal);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_countSubtotal_literal))
			{
				driver()->context()->parse(value, t()->countSubtotal);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_stdDevSubtotal_literal))
			{
				driver()->context()->parse(value, t()->stdDevSubtotal);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_stdDevPSubtotal_literal))
			{
				driver()->context()->parse(value, t()->stdDevPSubtotal);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_varSubtotal_literal))
			{
				driver()->context()->parse(value, t()->varSubtotal);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_varPSubtotal_literal))
			{
				driver()->context()->parse(value, t()->varPSubtotal);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_showPropCell_literal))
			{
				driver()->context()->parse(value, t()->showPropCell);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_showPropTip_literal))
			{
				driver()->context()->parse(value, t()->showPropTip);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_showPropAsCaption_literal))
			{
				driver()->context()->parse(value, t()->showPropAsCaption);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_defaultAttributeDrillState_literal))
			{
				driver()->context()->parse(value, t()->defaultAttributeDrillState);
				return;
			}
		}
		void CT_PivotFields_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_pivotField_literal))
			{
				t()->pivotField.resize(t()->pivotField.size()+1);
				driver()->push(localname, _pivotField_reader.get_reader(&t()->pivotField.back()));
				return;
			}
		}
		void CT_PivotFields_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
		}
		void CT_Field_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_x_literal))
			{
				driver()->context()->parse(value, t()->x);
				return;
			}
		}
		void CT_RowFields_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_field_literal))
			{
				t()->field.resize(t()->field.size()+1);
				driver()->push(localname, _field_reader.get_reader(&t()->field.back()));
				return;
			}
		}
		void CT_RowFields_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_count_literal))
			{
				driver()->context()->parse(value, t()->count);
				return;
			}
		}
		void CT_I_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_x_literal))
			{
				t()->x.resize(t()->x.size()+1);
				driver()->push(localname, _x_reader.get_reader(&t()->x.back()));
				return;
			}
		}
		void CT_I_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_t_literal))
			{
				driver()->context()->parse(value, t()->t);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_r_literal))
			{
				driver()->context()->parse(value, t()->r);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_i_literal))
			{
				driver()->context()->parse(value, t()->i);
				return;
			}
		}
		void CT_rowItems_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_i_literal))
			{
				t()->i.resize(t()->i.size()+1);
				driver()->push(localname, _i_reader.get_reader(&t()->i.back()));
				return;
			}
		}
		void CT_rowItems_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
		}
		void CT_ColFields_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_field_literal))
			{
				t()->field.resize(t()->field.size()+1);
				driver()->push(localname, _field_reader.get_reader(&t()->field.back()));
				return;
			}
		}
		void CT_ColFields_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_count_literal))
			{
				driver()->context()->parse(value, t()->count);
				return;
			}
		}
		void CT_colItems_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_i_literal))
			{
				t()->i.resize(t()->i.size()+1);
				driver()->push(localname, _i_reader.get_reader(&t()->i.back()));
				return;
			}
		}
		void CT_colItems_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
		}
		void CT_PageField_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_PageField_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_fld_literal))
			{
				driver()->context()->parse(value, t()->fld);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_item_literal))
			{
				driver()->context()->parse(value, t()->item.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_hier_literal))
			{
				driver()->context()->parse(value, t()->hier.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_name_literal))
			{
				driver()->context()->parse(value, t()->name.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_cap_literal))
			{
				driver()->context()->parse(value, t()->cap.getset());
				return;
			}
		}
		void CT_PageFields_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_pageField_literal))
			{
				t()->pageField.resize(t()->pageField.size()+1);
				driver()->push(localname, _pageField_reader.get_reader(&t()->pageField.back()));
				return;
			}
		}
		void CT_PageFields_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
		}
		void CT_DataField_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_DataField_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_name_literal))
			{
				driver()->context()->parse(value, t()->name.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_fld_literal))
			{
				driver()->context()->parse(value, t()->fld);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_subtotal_literal))
			{
				driver()->context()->parse(value, t()->subtotal);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_showDataAs_literal))
			{
				driver()->context()->parse(value, t()->showDataAs);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_baseField_literal))
			{
				driver()->context()->parse(value, t()->baseField);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_baseItem_literal))
			{
				driver()->context()->parse(value, t()->baseItem);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_numFmtId_literal))
			{
				driver()->context()->parse(value, t()->numFmtId.getset());
				return;
			}
		}
		void CT_DataFields_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_dataField_literal))
			{
				t()->dataField.resize(t()->dataField.size()+1);
				driver()->push(localname, _dataField_reader.get_reader(&t()->dataField.back()));
				return;
			}
		}
		void CT_DataFields_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
		}
		void CT_Format_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_pivotArea_literal))
			{
				driver()->push(localname, _pivotArea_reader.get_reader(&t()->pivotArea));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_Format_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_action_literal))
			{
				driver()->context()->parse(value, t()->action);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_dxfId_literal))
			{
				driver()->context()->parse(value, t()->dxfId.getset());
				return;
			}
		}
		void CT_Formats_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_format_literal))
			{
				t()->format.resize(t()->format.size()+1);
				driver()->push(localname, _format_reader.get_reader(&t()->format.back()));
				return;
			}
		}
		void CT_Formats_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_count_literal))
			{
				driver()->context()->parse(value, t()->count);
				return;
			}
		}
		void CT_PivotAreas_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_pivotArea_literal))
			{
				t()->pivotArea.resize(t()->pivotArea.size()+1);
				driver()->push(localname, _pivotArea_reader.get_reader(&t()->pivotArea.back()));
				return;
			}
		}
		void CT_PivotAreas_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
		}
		void CT_ConditionalFormat_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_pivotAreas_literal))
			{
				driver()->push(localname, _pivotAreas_reader.get_reader(&t()->pivotAreas));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_ConditionalFormat_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_scope_literal))
			{
				driver()->context()->parse(value, t()->scope);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_type_literal))
			{
				driver()->context()->parse(value, t()->type);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_priority_literal))
			{
				driver()->context()->parse(value, t()->priority);
				return;
			}
		}
		void CT_ConditionalFormats_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_conditionalFormat_literal))
			{
				t()->conditionalFormat.resize(t()->conditionalFormat.size()+1);
				driver()->push(localname, _conditionalFormat_reader.get_reader(&t()->conditionalFormat.back()));
				return;
			}
		}
		void CT_ConditionalFormats_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_count_literal))
			{
				driver()->context()->parse(value, t()->count);
				return;
			}
		}
		void CT_ChartFormat_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_pivotArea_literal))
			{
				driver()->push(localname, _pivotArea_reader.get_reader(&t()->pivotArea));
				return;
			}
		}
		void CT_ChartFormat_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_chart_literal))
			{
				driver()->context()->parse(value, t()->chart);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_format_literal))
			{
				driver()->context()->parse(value, t()->format);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_series_literal))
			{
				driver()->context()->parse(value, t()->series);
				return;
			}
		}
		void CT_ChartFormats_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_chartFormat_literal))
			{
				t()->chartFormat.resize(t()->chartFormat.size()+1);
				driver()->push(localname, _chartFormat_reader.get_reader(&t()->chartFormat.back()));
				return;
			}
		}
		void CT_ChartFormats_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_count_literal))
			{
				driver()->context()->parse(value, t()->count);
				return;
			}
		}
		void CT_MemberProperty_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_name_literal))
			{
				driver()->context()->parse(value, t()->name.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_showCell_literal))
			{
				driver()->context()->parse(value, t()->showCell);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_showTip_literal))
			{
				driver()->context()->parse(value, t()->showTip);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_showAsCaption_literal))
			{
				driver()->context()->parse(value, t()->showAsCaption);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_nameLen_literal))
			{
				driver()->context()->parse(value, t()->nameLen.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_pPos_literal))
			{
				driver()->context()->parse(value, t()->pPos.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_pLen_literal))
			{
				driver()->context()->parse(value, t()->pLen.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_level_literal))
			{
				driver()->context()->parse(value, t()->level.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_field_literal))
			{
				driver()->context()->parse(value, t()->field);
				return;
			}
		}
		void CT_MemberProperties_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_mp_literal))
			{
				t()->mp.resize(t()->mp.size()+1);
				driver()->push(localname, _mp_reader.get_reader(&t()->mp.back()));
				return;
			}
		}
		void CT_MemberProperties_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
		}
		void CT_Member_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_name_literal))
			{
				driver()->context()->parse(value, t()->name);
				return;
			}
		}
		void CT_Members_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_member_literal))
			{
				t()->member.resize(t()->member.size()+1);
				driver()->push(localname, _member_reader.get_reader(&t()->member.back()));
				return;
			}
		}
		void CT_Members_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_level_literal))
			{
				driver()->context()->parse(value, t()->level.getset());
				return;
			}
		}
		void CT_PivotHierarchy_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_mps_literal))
			{
				driver()->push(localname, _mps_reader.get_reader(&t()->mps.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_members_literal))
			{
				t()->members.resize(t()->members.size()+1);
				driver()->push(localname, _members_reader.get_reader(&t()->members.back()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_PivotHierarchy_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_outline_literal))
			{
				driver()->context()->parse(value, t()->outline);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_multipleItemSelectionAllowed_literal))
			{
				driver()->context()->parse(value, t()->multipleItemSelectionAllowed);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_subtotalTop_literal))
			{
				driver()->context()->parse(value, t()->subtotalTop);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_showInFieldList_literal))
			{
				driver()->context()->parse(value, t()->showInFieldList);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_dragToRow_literal))
			{
				driver()->context()->parse(value, t()->dragToRow);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_dragToCol_literal))
			{
				driver()->context()->parse(value, t()->dragToCol);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_dragToPage_literal))
			{
				driver()->context()->parse(value, t()->dragToPage);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_dragToData_literal))
			{
				driver()->context()->parse(value, t()->dragToData);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_dragOff_literal))
			{
				driver()->context()->parse(value, t()->dragOff);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_includeNewItemsInFilter_literal))
			{
				driver()->context()->parse(value, t()->includeNewItemsInFilter);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_caption_literal))
			{
				driver()->context()->parse(value, t()->caption.getset());
				return;
			}
		}
		void CT_PivotHierarchies_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_pivotHierarchy_literal))
			{
				t()->pivotHierarchy.resize(t()->pivotHierarchy.size()+1);
				driver()->push(localname, _pivotHierarchy_reader.get_reader(&t()->pivotHierarchy.back()));
				return;
			}
		}
		void CT_PivotHierarchies_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
		}
		void CT_PivotTableStyle_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_name_literal))
			{
				driver()->context()->parse(value, t()->name.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_showRowHeaders_literal))
			{
				driver()->context()->parse(value, t()->showRowHeaders.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_showColHeaders_literal))
			{
				driver()->context()->parse(value, t()->showColHeaders.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_showRowStripes_literal))
			{
				driver()->context()->parse(value, t()->showRowStripes.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_showColStripes_literal))
			{
				driver()->context()->parse(value, t()->showColStripes.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_showLastColumn_literal))
			{
				driver()->context()->parse(value, t()->showLastColumn.getset());
				return;
			}
		}
		void CT_PivotFilter_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_autoFilter_literal))
			{
				driver()->push(localname, _autoFilter_reader.get_reader(&t()->autoFilter));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_PivotFilter_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_fld_literal))
			{
				driver()->context()->parse(value, t()->fld);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_mpFld_literal))
			{
				driver()->context()->parse(value, t()->mpFld.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_type_literal))
			{
				driver()->context()->parse(value, t()->type);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_evalOrder_literal))
			{
				driver()->context()->parse(value, t()->evalOrder);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_id_literal))
			{
				driver()->context()->parse(value, t()->id);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_iMeasureHier_literal))
			{
				driver()->context()->parse(value, t()->iMeasureHier.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_iMeasureFld_literal))
			{
				driver()->context()->parse(value, t()->iMeasureFld.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_name_literal))
			{
				driver()->context()->parse(value, t()->name.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_description_literal))
			{
				driver()->context()->parse(value, t()->description.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_stringValue1_literal))
			{
				driver()->context()->parse(value, t()->stringValue1.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_stringValue2_literal))
			{
				driver()->context()->parse(value, t()->stringValue2.getset());
				return;
			}
		}
		void CT_PivotFilters_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_filter_literal))
			{
				t()->filter.resize(t()->filter.size()+1);
				driver()->push(localname, _filter_reader.get_reader(&t()->filter.back()));
				return;
			}
		}
		void CT_PivotFilters_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_count_literal))
			{
				driver()->context()->parse(value, t()->count);
				return;
			}
		}
		void CT_HierarchyUsage_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_hierarchyUsage_literal))
			{
				driver()->context()->parse(value, t()->hierarchyUsage);
				return;
			}
		}
		void CT_RowHierarchiesUsage_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_rowHierarchyUsage_literal))
			{
				t()->rowHierarchyUsage.resize(t()->rowHierarchyUsage.size()+1);
				driver()->push(localname, _rowHierarchyUsage_reader.get_reader(&t()->rowHierarchyUsage.back()));
				return;
			}
		}
		void CT_RowHierarchiesUsage_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
		}
		void CT_ColHierarchiesUsage_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_colHierarchyUsage_literal))
			{
				t()->colHierarchyUsage.resize(t()->colHierarchyUsage.size()+1);
				driver()->push(localname, _colHierarchyUsage_reader.get_reader(&t()->colHierarchyUsage.back()));
				return;
			}
		}
		void CT_ColHierarchiesUsage_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
		}
		void CT_pivotTableDefinition_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_location_literal))
			{
				driver()->push(localname, _location_reader.get_reader(&t()->location));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_pivotFields_literal))
			{
				driver()->push(localname, _pivotFields_reader.get_reader(&t()->pivotFields.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_rowFields_literal))
			{
				driver()->push(localname, _rowFields_reader.get_reader(&t()->rowFields.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_rowItems_literal))
			{
				driver()->push(localname, _rowItems_reader.get_reader(&t()->rowItems.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_colFields_literal))
			{
				driver()->push(localname, _colFields_reader.get_reader(&t()->colFields.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_colItems_literal))
			{
				driver()->push(localname, _colItems_reader.get_reader(&t()->colItems.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_pageFields_literal))
			{
				driver()->push(localname, _pageFields_reader.get_reader(&t()->pageFields.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_dataFields_literal))
			{
				driver()->push(localname, _dataFields_reader.get_reader(&t()->dataFields.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_formats_literal))
			{
				driver()->push(localname, _formats_reader.get_reader(&t()->formats.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_conditionalFormats_literal))
			{
				driver()->push(localname, _conditionalFormats_reader.get_reader(&t()->conditionalFormats.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_chartFormats_literal))
			{
				driver()->push(localname, _chartFormats_reader.get_reader(&t()->chartFormats.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_pivotHierarchies_literal))
			{
				driver()->push(localname, _pivotHierarchies_reader.get_reader(&t()->pivotHierarchies.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_pivotTableStyleInfo_literal))
			{
				driver()->push(localname, _pivotTableStyleInfo_reader.get_reader(&t()->pivotTableStyleInfo.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_filters_literal))
			{
				driver()->push(localname, _filters_reader.get_reader(&t()->filters.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_rowHierarchiesUsage_literal))
			{
				driver()->push(localname, _rowHierarchiesUsage_reader.get_reader(&t()->rowHierarchiesUsage.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_colHierarchiesUsage_literal))
			{
				driver()->push(localname, _colHierarchiesUsage_reader.get_reader(&t()->colHierarchiesUsage.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_pivotTableDefinition_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_name_literal))
			{
				driver()->context()->parse(value, t()->name);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_cacheId_literal))
			{
				driver()->context()->parse(value, t()->cacheId);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_dataOnRows_literal))
			{
				driver()->context()->parse(value, t()->dataOnRows);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_dataPosition_literal))
			{
				driver()->context()->parse(value, t()->dataPosition.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_autoFormatId_literal))
			{
				driver()->context()->parse(value, t()->autoFormatId.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_applyNumberFormats_literal))
			{
				driver()->context()->parse(value, t()->applyNumberFormats.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_applyBorderFormats_literal))
			{
				driver()->context()->parse(value, t()->applyBorderFormats.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_applyFontFormats_literal))
			{
				driver()->context()->parse(value, t()->applyFontFormats.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_applyPatternFormats_literal))
			{
				driver()->context()->parse(value, t()->applyPatternFormats.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_applyAlignmentFormats_literal))
			{
				driver()->context()->parse(value, t()->applyAlignmentFormats.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_applyWidthHeightFormats_literal))
			{
				driver()->context()->parse(value, t()->applyWidthHeightFormats.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_dataCaption_literal))
			{
				driver()->context()->parse(value, t()->dataCaption);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_grandTotalCaption_literal))
			{
				driver()->context()->parse(value, t()->grandTotalCaption.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_errorCaption_literal))
			{
				driver()->context()->parse(value, t()->errorCaption.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_showError_literal))
			{
				driver()->context()->parse(value, t()->showError);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_missingCaption_literal))
			{
				driver()->context()->parse(value, t()->missingCaption.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_showMissing_literal))
			{
				driver()->context()->parse(value, t()->showMissing);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_pageStyle_literal))
			{
				driver()->context()->parse(value, t()->pageStyle.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_pivotTableStyle_literal))
			{
				driver()->context()->parse(value, t()->pivotTableStyle.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_vacatedStyle_literal))
			{
				driver()->context()->parse(value, t()->vacatedStyle.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_tag_literal))
			{
				driver()->context()->parse(value, t()->tag.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_updatedVersion_literal))
			{
				driver()->context()->parse(value, t()->updatedVersion);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_minRefreshableVersion_literal))
			{
				driver()->context()->parse(value, t()->minRefreshableVersion);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_asteriskTotals_literal))
			{
				driver()->context()->parse(value, t()->asteriskTotals);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_showItems_literal))
			{
				driver()->context()->parse(value, t()->showItems);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_editData_literal))
			{
				driver()->context()->parse(value, t()->editData);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_disableFieldList_literal))
			{
				driver()->context()->parse(value, t()->disableFieldList);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_showCalcMbrs_literal))
			{
				driver()->context()->parse(value, t()->showCalcMbrs);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_visualTotals_literal))
			{
				driver()->context()->parse(value, t()->visualTotals);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_showMultipleLabel_literal))
			{
				driver()->context()->parse(value, t()->showMultipleLabel);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_showDataDropDown_literal))
			{
				driver()->context()->parse(value, t()->showDataDropDown);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_showDrill_literal))
			{
				driver()->context()->parse(value, t()->showDrill);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_printDrill_literal))
			{
				driver()->context()->parse(value, t()->printDrill);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_showMemberPropertyTips_literal))
			{
				driver()->context()->parse(value, t()->showMemberPropertyTips);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_showDataTips_literal))
			{
				driver()->context()->parse(value, t()->showDataTips);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_enableWizard_literal))
			{
				driver()->context()->parse(value, t()->enableWizard);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_enableDrill_literal))
			{
				driver()->context()->parse(value, t()->enableDrill);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_enableFieldProperties_literal))
			{
				driver()->context()->parse(value, t()->enableFieldProperties);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_preserveFormatting_literal))
			{
				driver()->context()->parse(value, t()->preserveFormatting);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_useAutoFormatting_literal))
			{
				driver()->context()->parse(value, t()->useAutoFormatting);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_pageWrap_literal))
			{
				driver()->context()->parse(value, t()->pageWrap);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_pageOverThenDown_literal))
			{
				driver()->context()->parse(value, t()->pageOverThenDown);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_subtotalHiddenItems_literal))
			{
				driver()->context()->parse(value, t()->subtotalHiddenItems);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_rowGrandTotals_literal))
			{
				driver()->context()->parse(value, t()->rowGrandTotals);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_colGrandTotals_literal))
			{
				driver()->context()->parse(value, t()->colGrandTotals);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_fieldPrintTitles_literal))
			{
				driver()->context()->parse(value, t()->fieldPrintTitles);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_itemPrintTitles_literal))
			{
				driver()->context()->parse(value, t()->itemPrintTitles);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_mergeItem_literal))
			{
				driver()->context()->parse(value, t()->mergeItem);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_showDropZones_literal))
			{
				driver()->context()->parse(value, t()->showDropZones);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_createdVersion_literal))
			{
				driver()->context()->parse(value, t()->createdVersion);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_indent_literal))
			{
				driver()->context()->parse(value, t()->indent);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_showEmptyRow_literal))
			{
				driver()->context()->parse(value, t()->showEmptyRow);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_showEmptyCol_literal))
			{
				driver()->context()->parse(value, t()->showEmptyCol);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_showHeaders_literal))
			{
				driver()->context()->parse(value, t()->showHeaders);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_compact_literal))
			{
				driver()->context()->parse(value, t()->compact);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_outline_literal))
			{
				driver()->context()->parse(value, t()->outline);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_outlineData_literal))
			{
				driver()->context()->parse(value, t()->outlineData);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_compactData_literal))
			{
				driver()->context()->parse(value, t()->compactData);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_published_literal))
			{
				driver()->context()->parse(value, t()->published);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_gridDropZones_literal))
			{
				driver()->context()->parse(value, t()->gridDropZones);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_immersive_literal))
			{
				driver()->context()->parse(value, t()->immersive);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_multipleFieldFilters_literal))
			{
				driver()->context()->parse(value, t()->multipleFieldFilters);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_chartFormat_literal))
			{
				driver()->context()->parse(value, t()->chartFormat);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_rowHeaderCaption_literal))
			{
				driver()->context()->parse(value, t()->rowHeaderCaption.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_colHeaderCaption_literal))
			{
				driver()->context()->parse(value, t()->colHeaderCaption.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_fieldListSortAscending_literal))
			{
				driver()->context()->parse(value, t()->fieldListSortAscending);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_mdxSubqueries_literal))
			{
				driver()->context()->parse(value, t()->mdxSubqueries);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_customListSort_literal))
			{
				driver()->context()->parse(value, t()->customListSort);
				return;
			}
		}
		void sml_pivotTable_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_pivotCacheDefinition_literal))
			{
				driver()->push(localname, _pivotCacheDefinition_reader.get_reader(&t()->pivotCacheDefinition.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_pivotCacheRecords_literal))
			{
				driver()->push(localname, _pivotCacheRecords_reader.get_reader(&t()->pivotCacheRecords.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTable_pivotTableDefinition_literal))
			{
				driver()->push(localname, _pivotTableDefinition_reader.get_reader(&t()->pivotTableDefinition.getset()));
				return;
			}
		}
	}
}
