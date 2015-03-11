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

#ifndef SML_AUTOFILTER_WRITERS_HPP
#define SML_AUTOFILTER_WRITERS_HPP

#include "sml-autoFilter.hpp"
#include "sml-autoFilter_literals.hpp"
#include "sml-baseTypes_writers.hpp"
#include "sml-styles_writers.hpp"

namespace spreadsheetml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_Filter_writer;
		class CT_DateGroupItem_writer;
		class CT_Filters_writer;
		class CT_Top10_writer;
		class CT_CustomFilter_writer;
		class CT_CustomFilters_writer;
		class CT_DynamicFilter_writer;
		class CT_ColorFilter_writer;
		class CT_IconFilter_writer;
		class CT_FilterColumn_writer;
		class CT_SortCondition_writer;
		class CT_SortState_writer;
		class CT_AutoFilter_writer;

		class CT_Filter_writer : public type_writer
		{
			CT_Filter* t() { return static_cast<CT_Filter*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_DateGroupItem_writer : public type_writer
		{
			CT_DateGroupItem* t() { return static_cast<CT_DateGroupItem*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Filters_writer : public type_writer
		{
			auto_type_writer< CT_Filter_writer > _filter_writer;
			auto_type_writer< CT_DateGroupItem_writer > _dateGroupItem_writer;
			CT_Filters* t() { return static_cast<CT_Filters*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Top10_writer : public type_writer
		{
			CT_Top10* t() { return static_cast<CT_Top10*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_CustomFilter_writer : public type_writer
		{
			CT_CustomFilter* t() { return static_cast<CT_CustomFilter*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_CustomFilters_writer : public type_writer
		{
			auto_type_writer< CT_CustomFilter_writer > _customFilter_writer;
			CT_CustomFilters* t() { return static_cast<CT_CustomFilters*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_DynamicFilter_writer : public type_writer
		{
			CT_DynamicFilter* t() { return static_cast<CT_DynamicFilter*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_ColorFilter_writer : public type_writer
		{
			CT_ColorFilter* t() { return static_cast<CT_ColorFilter*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_IconFilter_writer : public type_writer
		{
			CT_IconFilter* t() { return static_cast<CT_IconFilter*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_FilterColumn_writer : public type_writer
		{
			auto_type_writer< CT_Filters_writer > _filters_writer;
			auto_type_writer< CT_Top10_writer > _top10_writer;
			auto_type_writer< CT_CustomFilters_writer > _customFilters_writer;
			auto_type_writer< CT_DynamicFilter_writer > _dynamicFilter_writer;
			auto_type_writer< CT_ColorFilter_writer > _colorFilter_writer;
			auto_type_writer< CT_IconFilter_writer > _iconFilter_writer;
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_FilterColumn* t() { return static_cast<CT_FilterColumn*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_SortCondition_writer : public type_writer
		{
			CT_SortCondition* t() { return static_cast<CT_SortCondition*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_SortState_writer : public type_writer
		{
			auto_type_writer< CT_SortCondition_writer > _sortCondition_writer;
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_SortState* t() { return static_cast<CT_SortState*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_AutoFilter_writer : public type_writer
		{
			auto_type_writer< CT_FilterColumn_writer > _filterColumn_writer;
			auto_type_writer< CT_SortState_writer > _sortState_writer;
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_AutoFilter* t() { return static_cast<CT_AutoFilter*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

	}
}
#endif

