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


#include "sml-pivotTableShared_readers.hpp"
#include "sml-pivotTableShared_literals.hpp"
#include <xio/xml/binding/driver.hpp>

namespace spreadsheetml
{
	namespace xio
	{
		void CT_Index_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTableShared_v_literal))
			{
				driver()->context()->parse(value, t()->v);
				return;
			}
		}
		void CT_PivotAreaReference_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTableShared_x_literal))
			{
				t()->x.resize(t()->x.size()+1);
				driver()->push(localname, _x_reader.get_reader(&t()->x.back()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTableShared_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_PivotAreaReference_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTableShared_field_literal))
			{
				driver()->context()->parse(value, t()->field.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTableShared_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTableShared_selected_literal))
			{
				driver()->context()->parse(value, t()->selected);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTableShared_byPosition_literal))
			{
				driver()->context()->parse(value, t()->byPosition);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTableShared_relative_literal))
			{
				driver()->context()->parse(value, t()->relative);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTableShared_defaultSubtotal_literal))
			{
				driver()->context()->parse(value, t()->defaultSubtotal);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTableShared_sumSubtotal_literal))
			{
				driver()->context()->parse(value, t()->sumSubtotal);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTableShared_countASubtotal_literal))
			{
				driver()->context()->parse(value, t()->countASubtotal);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTableShared_avgSubtotal_literal))
			{
				driver()->context()->parse(value, t()->avgSubtotal);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTableShared_maxSubtotal_literal))
			{
				driver()->context()->parse(value, t()->maxSubtotal);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTableShared_minSubtotal_literal))
			{
				driver()->context()->parse(value, t()->minSubtotal);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTableShared_productSubtotal_literal))
			{
				driver()->context()->parse(value, t()->productSubtotal);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTableShared_countSubtotal_literal))
			{
				driver()->context()->parse(value, t()->countSubtotal);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTableShared_stdDevSubtotal_literal))
			{
				driver()->context()->parse(value, t()->stdDevSubtotal);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTableShared_stdDevPSubtotal_literal))
			{
				driver()->context()->parse(value, t()->stdDevPSubtotal);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTableShared_varSubtotal_literal))
			{
				driver()->context()->parse(value, t()->varSubtotal);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTableShared_varPSubtotal_literal))
			{
				driver()->context()->parse(value, t()->varPSubtotal);
				return;
			}
		}
		void CT_PivotAreaReferences_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTableShared_reference_literal))
			{
				t()->reference.resize(t()->reference.size()+1);
				driver()->push(localname, _reference_reader.get_reader(&t()->reference.back()));
				return;
			}
		}
		void CT_PivotAreaReferences_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTableShared_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
		}
		void CT_PivotArea_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTableShared_references_literal))
			{
				driver()->push(localname, _references_reader.get_reader(&t()->references.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTableShared_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_PivotArea_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_pivotTableShared_field_literal))
			{
				driver()->context()->parse(value, t()->field.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTableShared_type_literal))
			{
				driver()->context()->parse(value, t()->type);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTableShared_dataOnly_literal))
			{
				driver()->context()->parse(value, t()->dataOnly);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTableShared_labelOnly_literal))
			{
				driver()->context()->parse(value, t()->labelOnly);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTableShared_grandRow_literal))
			{
				driver()->context()->parse(value, t()->grandRow);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTableShared_grandCol_literal))
			{
				driver()->context()->parse(value, t()->grandCol);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTableShared_cacheIndex_literal))
			{
				driver()->context()->parse(value, t()->cacheIndex);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTableShared_outline_literal))
			{
				driver()->context()->parse(value, t()->outline);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTableShared_offset_literal))
			{
				driver()->context()->parse(value, t()->offset.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTableShared_collapsedLevelsAreSubtotals_literal))
			{
				driver()->context()->parse(value, t()->collapsedLevelsAreSubtotals);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTableShared_axis_literal))
			{
				driver()->context()->parse(value, t()->axis.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_pivotTableShared_fieldPosition_literal))
			{
				driver()->context()->parse(value, t()->fieldPosition.getset());
				return;
			}
		}
	}
}
