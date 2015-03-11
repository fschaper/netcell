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

#ifndef SML_AUTOFILTER_READERS_HPP
#define SML_AUTOFILTER_READERS_HPP

#include "sml-autoFilter.hpp"
#include "sml-baseTypes_readers.hpp"
#include "sml-styles_readers.hpp"

namespace spreadsheetml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_Filter_reader;
		class CT_DateGroupItem_reader;
		class CT_Filters_reader;
		class CT_Top10_reader;
		class CT_CustomFilter_reader;
		class CT_CustomFilters_reader;
		class CT_DynamicFilter_reader;
		class CT_ColorFilter_reader;
		class CT_IconFilter_reader;
		class CT_FilterColumn_reader;
		class CT_SortCondition_reader;
		class CT_SortState_reader;
		class CT_AutoFilter_reader;

		class CT_Filter_reader : public type_reader
		{
		protected:
			CT_Filter* t() { return static_cast<CT_Filter*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_DateGroupItem_reader : public type_reader
		{
		protected:
			CT_DateGroupItem* t() { return static_cast<CT_DateGroupItem*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Filters_reader : public type_reader
		{
			auto_type_reader< CT_Filter_reader > _filter_reader;
			auto_type_reader< CT_DateGroupItem_reader > _dateGroupItem_reader;
		protected:
			CT_Filters* t() { return static_cast<CT_Filters*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Top10_reader : public type_reader
		{
		protected:
			CT_Top10* t() { return static_cast<CT_Top10*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_CustomFilter_reader : public type_reader
		{
		protected:
			CT_CustomFilter* t() { return static_cast<CT_CustomFilter*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_CustomFilters_reader : public type_reader
		{
			auto_type_reader< CT_CustomFilter_reader > _customFilter_reader;
		protected:
			CT_CustomFilters* t() { return static_cast<CT_CustomFilters*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_DynamicFilter_reader : public type_reader
		{
		protected:
			CT_DynamicFilter* t() { return static_cast<CT_DynamicFilter*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_ColorFilter_reader : public type_reader
		{
		protected:
			CT_ColorFilter* t() { return static_cast<CT_ColorFilter*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_IconFilter_reader : public type_reader
		{
		protected:
			CT_IconFilter* t() { return static_cast<CT_IconFilter*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_FilterColumn_reader : public type_reader
		{
			auto_type_reader< CT_Filters_reader > _filters_reader;
			auto_type_reader< CT_Top10_reader > _top10_reader;
			auto_type_reader< CT_CustomFilters_reader > _customFilters_reader;
			auto_type_reader< CT_DynamicFilter_reader > _dynamicFilter_reader;
			auto_type_reader< CT_ColorFilter_reader > _colorFilter_reader;
			auto_type_reader< CT_IconFilter_reader > _iconFilter_reader;
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_FilterColumn* t() { return static_cast<CT_FilterColumn*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_SortCondition_reader : public type_reader
		{
		protected:
			CT_SortCondition* t() { return static_cast<CT_SortCondition*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_SortState_reader : public type_reader
		{
			auto_type_reader< CT_SortCondition_reader > _sortCondition_reader;
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_SortState* t() { return static_cast<CT_SortState*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_AutoFilter_reader : public type_reader
		{
			auto_type_reader< CT_FilterColumn_reader > _filterColumn_reader;
			auto_type_reader< CT_SortState_reader > _sortState_reader;
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_AutoFilter* t() { return static_cast<CT_AutoFilter*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

	}
}
#endif

