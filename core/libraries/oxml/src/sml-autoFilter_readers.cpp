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


#include "sml-autoFilter_readers.hpp"
#include "sml-autoFilter_literals.hpp"
#include <xio/xml/binding/driver.hpp>

namespace spreadsheetml
{
	namespace xio
	{
		void CT_Filter_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_autoFilter_val_literal))
			{
				driver()->context()->parse(value, t()->val.getset());
				return;
			}
		}
		void CT_DateGroupItem_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_autoFilter_year_literal))
			{
				driver()->context()->parse(value, t()->year);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_autoFilter_month_literal))
			{
				driver()->context()->parse(value, t()->month.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_autoFilter_day_literal))
			{
				driver()->context()->parse(value, t()->day.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_autoFilter_hour_literal))
			{
				driver()->context()->parse(value, t()->hour.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_autoFilter_minute_literal))
			{
				driver()->context()->parse(value, t()->minute.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_autoFilter_second_literal))
			{
				driver()->context()->parse(value, t()->second.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_autoFilter_dateTimeGrouping_literal))
			{
				driver()->context()->parse(value, t()->dateTimeGrouping);
				return;
			}
		}
		void CT_Filters_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_autoFilter_filter_literal))
			{
				t()->filter.resize(t()->filter.size()+1);
				driver()->push(localname, _filter_reader.get_reader(&t()->filter.back()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_autoFilter_dateGroupItem_literal))
			{
				t()->dateGroupItem.resize(t()->dateGroupItem.size()+1);
				driver()->push(localname, _dateGroupItem_reader.get_reader(&t()->dateGroupItem.back()));
				return;
			}
		}
		void CT_Filters_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_autoFilter_blank_literal))
			{
				driver()->context()->parse(value, t()->blank);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_autoFilter_calendarType_literal))
			{
				driver()->context()->parse(value, t()->calendarType);
				return;
			}
		}
		void CT_Top10_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_autoFilter_top_literal))
			{
				driver()->context()->parse(value, t()->top);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_autoFilter_percent_literal))
			{
				driver()->context()->parse(value, t()->percent);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_autoFilter_val_literal))
			{
				driver()->context()->parse(value, t()->val);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_autoFilter_filterVal_literal))
			{
				driver()->context()->parse(value, t()->filterVal.getset());
				return;
			}
		}
		void CT_CustomFilter_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_autoFilter__operator__literal))
			{
				driver()->context()->parse(value, t()->_operator_);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_autoFilter_val_literal))
			{
				driver()->context()->parse(value, t()->val.getset());
				return;
			}
		}
		void CT_CustomFilters_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_autoFilter_customFilter_literal))
			{
				t()->customFilter.resize(t()->customFilter.size()+1);
				driver()->push(localname, _customFilter_reader.get_reader(&t()->customFilter.back()));
				return;
			}
		}
		void CT_CustomFilters_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_autoFilter__and__literal))
			{
				driver()->context()->parse(value, t()->_and_);
				return;
			}
		}
		void CT_DynamicFilter_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_autoFilter_type_literal))
			{
				driver()->context()->parse(value, t()->type);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_autoFilter_val_literal))
			{
				driver()->context()->parse(value, t()->val.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_autoFilter_maxVal_literal))
			{
				driver()->context()->parse(value, t()->maxVal.getset());
				return;
			}
		}
		void CT_ColorFilter_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_autoFilter_dxfId_literal))
			{
				driver()->context()->parse(value, t()->dxfId.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_autoFilter_cellColor_literal))
			{
				driver()->context()->parse(value, t()->cellColor);
				return;
			}
		}
		void CT_IconFilter_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_autoFilter_iconSet_literal))
			{
				driver()->context()->parse(value, t()->iconSet);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_autoFilter_iconId_literal))
			{
				driver()->context()->parse(value, t()->iconId.getset());
				return;
			}
		}
		void CT_FilterColumn_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_autoFilter_filters_literal))
			{
				driver()->push(localname, _filters_reader.get_reader(&t()->filters.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_autoFilter_top10_literal))
			{
				driver()->push(localname, _top10_reader.get_reader(&t()->top10.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_autoFilter_customFilters_literal))
			{
				driver()->push(localname, _customFilters_reader.get_reader(&t()->customFilters.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_autoFilter_dynamicFilter_literal))
			{
				driver()->push(localname, _dynamicFilter_reader.get_reader(&t()->dynamicFilter.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_autoFilter_colorFilter_literal))
			{
				driver()->push(localname, _colorFilter_reader.get_reader(&t()->colorFilter.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_autoFilter_iconFilter_literal))
			{
				driver()->push(localname, _iconFilter_reader.get_reader(&t()->iconFilter.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_autoFilter_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_FilterColumn_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_autoFilter_colId_literal))
			{
				driver()->context()->parse(value, t()->colId);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_autoFilter_hiddenButton_literal))
			{
				driver()->context()->parse(value, t()->hiddenButton);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_autoFilter_showButton_literal))
			{
				driver()->context()->parse(value, t()->showButton);
				return;
			}
		}
		void CT_SortCondition_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_autoFilter_descending_literal))
			{
				driver()->context()->parse(value, t()->descending);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_autoFilter_sortBy_literal))
			{
				driver()->context()->parse(value, t()->sortBy);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_autoFilter_ref_literal))
			{
				driver()->context()->parse(value, t()->ref);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_autoFilter_customList_literal))
			{
				driver()->context()->parse(value, t()->customList.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_autoFilter_dxfId_literal))
			{
				driver()->context()->parse(value, t()->dxfId.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_autoFilter_iconSet_literal))
			{
				driver()->context()->parse(value, t()->iconSet);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_autoFilter_iconId_literal))
			{
				driver()->context()->parse(value, t()->iconId.getset());
				return;
			}
		}
		void CT_SortState_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_autoFilter_sortCondition_literal))
			{
				t()->sortCondition.resize(t()->sortCondition.size()+1);
				driver()->push(localname, _sortCondition_reader.get_reader(&t()->sortCondition.back()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_autoFilter_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_SortState_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_autoFilter_columnSort_literal))
			{
				driver()->context()->parse(value, t()->columnSort);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_autoFilter_caseSensitive_literal))
			{
				driver()->context()->parse(value, t()->caseSensitive);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_autoFilter_sortMethod_literal))
			{
				driver()->context()->parse(value, t()->sortMethod);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_autoFilter_ref_literal))
			{
				driver()->context()->parse(value, t()->ref);
				return;
			}
		}
		void CT_AutoFilter_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_autoFilter_filterColumn_literal))
			{
				t()->filterColumn.resize(t()->filterColumn.size()+1);
				driver()->push(localname, _filterColumn_reader.get_reader(&t()->filterColumn.back()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_autoFilter_sortState_literal))
			{
				driver()->push(localname, _sortState_reader.get_reader(&t()->sortState.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_autoFilter_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_AutoFilter_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_autoFilter_ref_literal))
			{
				driver()->context()->parse(value, t()->ref.getset());
				return;
			}
		}
	}
}
