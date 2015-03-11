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

#ifndef SML_PIVOTTABLE_READERS_HPP
#define SML_PIVOTTABLE_READERS_HPP

#include "sml-pivotTable.hpp"
#include "sml-baseTypes_readers.hpp"
#include "shared-relationshipReference_readers.hpp"
#include "sml-pivotTableShared_readers.hpp"
#include "sml-styles_readers.hpp"
#include "sml-sheet_readers.hpp"
#include "sml-autoFilter_readers.hpp"

namespace spreadsheetml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_WorksheetSource_reader;
		class CT_PageItem_reader;
		class CT_PCDSCPage_reader;
		class CT_Pages_reader;
		class CT_RangeSet_reader;
		class CT_RangeSets_reader;
		class CT_Consolidation_reader;
		class CT_CacheSource_reader;
		class CT_Tuple_reader;
		class CT_Tuples_reader;
		class CT_X_reader;
		class CT_Missing_reader;
		class CT_Number_reader;
		class CT_Boolean_reader;
		class CT_Error_reader;
		class CT_String_reader;
		class CT_DateTime_reader;
		class CT_SharedItems_reader;
		class CT_RangePr_reader;
		class CT_DiscretePr_reader;
		class CT_GroupItems_reader;
		class CT_FieldGroup_reader;
		class CT_CacheField_reader;
		class CT_CacheFields_reader;
		class CT_FieldUsage_reader;
		class CT_FieldsUsage_reader;
		class CT_GroupMember_reader;
		class CT_GroupMembers_reader;
		class CT_LevelGroup_reader;
		class CT_Groups_reader;
		class CT_GroupLevel_reader;
		class CT_GroupLevels_reader;
		class CT_CacheHierarchy_reader;
		class CT_CacheHierarchies_reader;
		class CT_PCDKPI_reader;
		class CT_PCDKPIs_reader;
		class CT_PCDSDTCEntries_reader;
		class CT_Set_reader;
		class CT_Sets_reader;
		class CT_Query_reader;
		class CT_QueryCache_reader;
		class CT_ServerFormat_reader;
		class CT_ServerFormats_reader;
		class CT_TupleCache_reader;
		class CT_CalculatedItem_reader;
		class CT_CalculatedItems_reader;
		class CT_CalculatedMember_reader;
		class CT_CalculatedMembers_reader;
		class CT_PivotDimension_reader;
		class CT_Dimensions_reader;
		class CT_MeasureGroup_reader;
		class CT_MeasureGroups_reader;
		class CT_MeasureDimensionMap_reader;
		class CT_MeasureDimensionMaps_reader;
		class CT_PivotCacheDefinition_reader;
		class CT_Record_reader;
		class CT_PivotCacheRecords_reader;
		class CT_Location_reader;
		class CT_Item_reader;
		class CT_Items_reader;
		class CT_AutoSortScope_reader;
		class CT_PivotField_reader;
		class CT_PivotFields_reader;
		class CT_Field_reader;
		class CT_RowFields_reader;
		class CT_I_reader;
		class CT_rowItems_reader;
		class CT_ColFields_reader;
		class CT_colItems_reader;
		class CT_PageField_reader;
		class CT_PageFields_reader;
		class CT_DataField_reader;
		class CT_DataFields_reader;
		class CT_Format_reader;
		class CT_Formats_reader;
		class CT_PivotAreas_reader;
		class CT_ConditionalFormat_reader;
		class CT_ConditionalFormats_reader;
		class CT_ChartFormat_reader;
		class CT_ChartFormats_reader;
		class CT_MemberProperty_reader;
		class CT_MemberProperties_reader;
		class CT_Member_reader;
		class CT_Members_reader;
		class CT_PivotHierarchy_reader;
		class CT_PivotHierarchies_reader;
		class CT_PivotTableStyle_reader;
		class CT_PivotFilter_reader;
		class CT_PivotFilters_reader;
		class CT_HierarchyUsage_reader;
		class CT_RowHierarchiesUsage_reader;
		class CT_ColHierarchiesUsage_reader;
		class CT_pivotTableDefinition_reader;
		class sml_pivotTable_reader;

		class CT_WorksheetSource_reader : public type_reader
		{
		protected:
			CT_WorksheetSource* t() { return static_cast<CT_WorksheetSource*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_PageItem_reader : public type_reader
		{
		protected:
			CT_PageItem* t() { return static_cast<CT_PageItem*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_PCDSCPage_reader : public type_reader
		{
			auto_type_reader< CT_PageItem_reader > _pageItem_reader;
		protected:
			CT_PCDSCPage* t() { return static_cast<CT_PCDSCPage*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Pages_reader : public type_reader
		{
			auto_type_reader< CT_PCDSCPage_reader > _page_reader;
		protected:
			CT_Pages* t() { return static_cast<CT_Pages*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_RangeSet_reader : public type_reader
		{
		protected:
			CT_RangeSet* t() { return static_cast<CT_RangeSet*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_RangeSets_reader : public type_reader
		{
			auto_type_reader< CT_RangeSet_reader > _rangeSet_reader;
		protected:
			CT_RangeSets* t() { return static_cast<CT_RangeSets*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Consolidation_reader : public type_reader
		{
			auto_type_reader< CT_Pages_reader > _pages_reader;
			auto_type_reader< CT_RangeSets_reader > _rangeSets_reader;
		protected:
			CT_Consolidation* t() { return static_cast<CT_Consolidation*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_CacheSource_reader : public type_reader
		{
			auto_type_reader< CT_WorksheetSource_reader > _worksheetSource_reader;
			auto_type_reader< CT_Consolidation_reader > _consolidation_reader;
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_CacheSource* t() { return static_cast<CT_CacheSource*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Tuple_reader : public type_reader
		{
		protected:
			CT_Tuple* t() { return static_cast<CT_Tuple*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Tuples_reader : public type_reader
		{
			auto_type_reader< CT_Tuple_reader > _tpl_reader;
		protected:
			CT_Tuples* t() { return static_cast<CT_Tuples*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_X_reader : public type_reader
		{
		protected:
			CT_X* t() { return static_cast<CT_X*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Missing_reader : public type_reader
		{
			auto_type_reader< CT_Tuples_reader > _tpls_reader;
			auto_type_reader< CT_X_reader > _x_reader;
		protected:
			CT_Missing* t() { return static_cast<CT_Missing*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Number_reader : public type_reader
		{
			auto_type_reader< CT_Tuples_reader > _tpls_reader;
			auto_type_reader< CT_X_reader > _x_reader;
		protected:
			CT_Number* t() { return static_cast<CT_Number*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Boolean_reader : public type_reader
		{
			auto_type_reader< CT_X_reader > _x_reader;
		protected:
			CT_Boolean* t() { return static_cast<CT_Boolean*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Error_reader : public type_reader
		{
			auto_type_reader< CT_Tuples_reader > _tpls_reader;
			auto_type_reader< CT_X_reader > _x_reader;
		protected:
			CT_Error* t() { return static_cast<CT_Error*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_String_reader : public type_reader
		{
			auto_type_reader< CT_Tuples_reader > _tpls_reader;
			auto_type_reader< CT_X_reader > _x_reader;
		protected:
			CT_String* t() { return static_cast<CT_String*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_DateTime_reader : public type_reader
		{
			auto_type_reader< CT_X_reader > _x_reader;
		protected:
			CT_DateTime* t() { return static_cast<CT_DateTime*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_SharedItems_reader : public type_reader
		{
			auto_type_reader< CT_Missing_reader > _m_reader;
			auto_type_reader< CT_Number_reader > _n_reader;
			auto_type_reader< CT_Boolean_reader > _b_reader;
			auto_type_reader< CT_Error_reader > _e_reader;
			auto_type_reader< CT_String_reader > _s_reader;
			auto_type_reader< CT_DateTime_reader > _d_reader;
		protected:
			CT_SharedItems* t() { return static_cast<CT_SharedItems*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_RangePr_reader : public type_reader
		{
		protected:
			CT_RangePr* t() { return static_cast<CT_RangePr*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_DiscretePr_reader : public type_reader
		{
			auto_type_reader< CT_Index_reader > _x_reader;
		protected:
			CT_DiscretePr* t() { return static_cast<CT_DiscretePr*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_GroupItems_reader : public type_reader
		{
			auto_type_reader< CT_Missing_reader > _m_reader;
			auto_type_reader< CT_Number_reader > _n_reader;
			auto_type_reader< CT_Boolean_reader > _b_reader;
			auto_type_reader< CT_Error_reader > _e_reader;
			auto_type_reader< CT_String_reader > _s_reader;
			auto_type_reader< CT_DateTime_reader > _d_reader;
		protected:
			CT_GroupItems* t() { return static_cast<CT_GroupItems*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_FieldGroup_reader : public type_reader
		{
			auto_type_reader< CT_RangePr_reader > _rangePr_reader;
			auto_type_reader< CT_DiscretePr_reader > _discretePr_reader;
			auto_type_reader< CT_GroupItems_reader > _groupItems_reader;
		protected:
			CT_FieldGroup* t() { return static_cast<CT_FieldGroup*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_CacheField_reader : public type_reader
		{
			auto_type_reader< CT_SharedItems_reader > _sharedItems_reader;
			auto_type_reader< CT_FieldGroup_reader > _fieldGroup_reader;
			auto_type_reader< CT_X_reader > _mpMap_reader;
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_CacheField* t() { return static_cast<CT_CacheField*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_CacheFields_reader : public type_reader
		{
			auto_type_reader< CT_CacheField_reader > _cacheField_reader;
		protected:
			CT_CacheFields* t() { return static_cast<CT_CacheFields*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_FieldUsage_reader : public type_reader
		{
		protected:
			CT_FieldUsage* t() { return static_cast<CT_FieldUsage*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_FieldsUsage_reader : public type_reader
		{
			auto_type_reader< CT_FieldUsage_reader > _fieldUsage_reader;
		protected:
			CT_FieldsUsage* t() { return static_cast<CT_FieldsUsage*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_GroupMember_reader : public type_reader
		{
		protected:
			CT_GroupMember* t() { return static_cast<CT_GroupMember*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_GroupMembers_reader : public type_reader
		{
			auto_type_reader< CT_GroupMember_reader > _groupMember_reader;
		protected:
			CT_GroupMembers* t() { return static_cast<CT_GroupMembers*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_LevelGroup_reader : public type_reader
		{
			auto_type_reader< CT_GroupMembers_reader > _groupMembers_reader;
		protected:
			CT_LevelGroup* t() { return static_cast<CT_LevelGroup*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Groups_reader : public type_reader
		{
			auto_type_reader< CT_LevelGroup_reader > _group_reader;
		protected:
			CT_Groups* t() { return static_cast<CT_Groups*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_GroupLevel_reader : public type_reader
		{
			auto_type_reader< CT_Groups_reader > _groups_reader;
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_GroupLevel* t() { return static_cast<CT_GroupLevel*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_GroupLevels_reader : public type_reader
		{
			auto_type_reader< CT_GroupLevel_reader > _groupLevel_reader;
		protected:
			CT_GroupLevels* t() { return static_cast<CT_GroupLevels*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_CacheHierarchy_reader : public type_reader
		{
			auto_type_reader< CT_FieldsUsage_reader > _fieldsUsage_reader;
			auto_type_reader< CT_GroupLevels_reader > _groupLevels_reader;
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_CacheHierarchy* t() { return static_cast<CT_CacheHierarchy*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_CacheHierarchies_reader : public type_reader
		{
			auto_type_reader< CT_CacheHierarchy_reader > _cacheHierarchy_reader;
		protected:
			CT_CacheHierarchies* t() { return static_cast<CT_CacheHierarchies*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_PCDKPI_reader : public type_reader
		{
		protected:
			CT_PCDKPI* t() { return static_cast<CT_PCDKPI*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_PCDKPIs_reader : public type_reader
		{
			auto_type_reader< CT_PCDKPI_reader > _kpi_reader;
		protected:
			CT_PCDKPIs* t() { return static_cast<CT_PCDKPIs*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_PCDSDTCEntries_reader : public type_reader
		{
			auto_type_reader< CT_Missing_reader > _m_reader;
			auto_type_reader< CT_Number_reader > _n_reader;
			auto_type_reader< CT_Error_reader > _e_reader;
			auto_type_reader< CT_String_reader > _s_reader;
		protected:
			CT_PCDSDTCEntries* t() { return static_cast<CT_PCDSDTCEntries*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Set_reader : public type_reader
		{
			auto_type_reader< CT_Tuples_reader > _tpls_reader;
			auto_type_reader< CT_Tuples_reader > _sortByTuple_reader;
		protected:
			CT_Set* t() { return static_cast<CT_Set*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Sets_reader : public type_reader
		{
			auto_type_reader< CT_Set_reader > _set_reader;
		protected:
			CT_Sets* t() { return static_cast<CT_Sets*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Query_reader : public type_reader
		{
			auto_type_reader< CT_Tuples_reader > _tpls_reader;
		protected:
			CT_Query* t() { return static_cast<CT_Query*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_QueryCache_reader : public type_reader
		{
			auto_type_reader< CT_Query_reader > _query_reader;
		protected:
			CT_QueryCache* t() { return static_cast<CT_QueryCache*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_ServerFormat_reader : public type_reader
		{
		protected:
			CT_ServerFormat* t() { return static_cast<CT_ServerFormat*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_ServerFormats_reader : public type_reader
		{
			auto_type_reader< CT_ServerFormat_reader > _serverFormat_reader;
		protected:
			CT_ServerFormats* t() { return static_cast<CT_ServerFormats*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_TupleCache_reader : public type_reader
		{
			auto_type_reader< CT_PCDSDTCEntries_reader > _entries_reader;
			auto_type_reader< CT_Sets_reader > _sets_reader;
			auto_type_reader< CT_QueryCache_reader > _queryCache_reader;
			auto_type_reader< CT_ServerFormats_reader > _serverFormats_reader;
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_TupleCache* t() { return static_cast<CT_TupleCache*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_CalculatedItem_reader : public type_reader
		{
			auto_type_reader< CT_PivotArea_reader > _pivotArea_reader;
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_CalculatedItem* t() { return static_cast<CT_CalculatedItem*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_CalculatedItems_reader : public type_reader
		{
			auto_type_reader< CT_CalculatedItem_reader > _calculatedItem_reader;
		protected:
			CT_CalculatedItems* t() { return static_cast<CT_CalculatedItems*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_CalculatedMember_reader : public type_reader
		{
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_CalculatedMember* t() { return static_cast<CT_CalculatedMember*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_CalculatedMembers_reader : public type_reader
		{
			auto_type_reader< CT_CalculatedMember_reader > _calculatedMember_reader;
		protected:
			CT_CalculatedMembers* t() { return static_cast<CT_CalculatedMembers*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_PivotDimension_reader : public type_reader
		{
		protected:
			CT_PivotDimension* t() { return static_cast<CT_PivotDimension*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Dimensions_reader : public type_reader
		{
			auto_type_reader< CT_PivotDimension_reader > _dimension_reader;
		protected:
			CT_Dimensions* t() { return static_cast<CT_Dimensions*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_MeasureGroup_reader : public type_reader
		{
		protected:
			CT_MeasureGroup* t() { return static_cast<CT_MeasureGroup*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_MeasureGroups_reader : public type_reader
		{
			auto_type_reader< CT_MeasureGroup_reader > _measureGroup_reader;
		protected:
			CT_MeasureGroups* t() { return static_cast<CT_MeasureGroups*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_MeasureDimensionMap_reader : public type_reader
		{
		protected:
			CT_MeasureDimensionMap* t() { return static_cast<CT_MeasureDimensionMap*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_MeasureDimensionMaps_reader : public type_reader
		{
			auto_type_reader< CT_MeasureDimensionMap_reader > _map_reader;
		protected:
			CT_MeasureDimensionMaps* t() { return static_cast<CT_MeasureDimensionMaps*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_PivotCacheDefinition_reader : public type_reader
		{
			auto_type_reader< CT_CacheSource_reader > _cacheSource_reader;
			auto_type_reader< CT_CacheFields_reader > _cacheFields_reader;
			auto_type_reader< CT_CacheHierarchies_reader > _cacheHierarchies_reader;
			auto_type_reader< CT_PCDKPIs_reader > _kpis_reader;
			auto_type_reader< CT_TupleCache_reader > _tupleCache_reader;
			auto_type_reader< CT_CalculatedItems_reader > _calculatedItems_reader;
			auto_type_reader< CT_CalculatedMembers_reader > _calculatedMembers_reader;
			auto_type_reader< CT_Dimensions_reader > _dimensions_reader;
			auto_type_reader< CT_MeasureGroups_reader > _measureGroups_reader;
			auto_type_reader< CT_MeasureDimensionMaps_reader > _maps_reader;
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_PivotCacheDefinition* t() { return static_cast<CT_PivotCacheDefinition*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Record_reader : public type_reader
		{
			auto_type_reader< CT_Missing_reader > _m_reader;
			auto_type_reader< CT_Number_reader > _n_reader;
			auto_type_reader< CT_Boolean_reader > _b_reader;
			auto_type_reader< CT_Error_reader > _e_reader;
			auto_type_reader< CT_String_reader > _s_reader;
			auto_type_reader< CT_DateTime_reader > _d_reader;
			auto_type_reader< CT_Index_reader > _x_reader;
		protected:
			CT_Record* t() { return static_cast<CT_Record*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_PivotCacheRecords_reader : public type_reader
		{
			auto_type_reader< CT_Record_reader > _r_reader;
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_PivotCacheRecords* t() { return static_cast<CT_PivotCacheRecords*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Location_reader : public type_reader
		{
		protected:
			CT_Location* t() { return static_cast<CT_Location*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Item_reader : public type_reader
		{
		protected:
			CT_Item* t() { return static_cast<CT_Item*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Items_reader : public type_reader
		{
			auto_type_reader< CT_Item_reader > _item_reader;
		protected:
			CT_Items* t() { return static_cast<CT_Items*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_AutoSortScope_reader : public type_reader
		{
			auto_type_reader< CT_PivotArea_reader > _pivotArea_reader;
		protected:
			CT_AutoSortScope* t() { return static_cast<CT_AutoSortScope*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_PivotField_reader : public type_reader
		{
			auto_type_reader< CT_Items_reader > _items_reader;
			auto_type_reader< CT_AutoSortScope_reader > _autoSortScope_reader;
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_PivotField* t() { return static_cast<CT_PivotField*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_PivotFields_reader : public type_reader
		{
			auto_type_reader< CT_PivotField_reader > _pivotField_reader;
		protected:
			CT_PivotFields* t() { return static_cast<CT_PivotFields*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Field_reader : public type_reader
		{
		protected:
			CT_Field* t() { return static_cast<CT_Field*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_RowFields_reader : public type_reader
		{
			auto_type_reader< CT_Field_reader > _field_reader;
		protected:
			CT_RowFields* t() { return static_cast<CT_RowFields*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_I_reader : public type_reader
		{
			auto_type_reader< CT_X_reader > _x_reader;
		protected:
			CT_I* t() { return static_cast<CT_I*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_rowItems_reader : public type_reader
		{
			auto_type_reader< CT_I_reader > _i_reader;
		protected:
			CT_rowItems* t() { return static_cast<CT_rowItems*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_ColFields_reader : public type_reader
		{
			auto_type_reader< CT_Field_reader > _field_reader;
		protected:
			CT_ColFields* t() { return static_cast<CT_ColFields*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_colItems_reader : public type_reader
		{
			auto_type_reader< CT_I_reader > _i_reader;
		protected:
			CT_colItems* t() { return static_cast<CT_colItems*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_PageField_reader : public type_reader
		{
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_PageField* t() { return static_cast<CT_PageField*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_PageFields_reader : public type_reader
		{
			auto_type_reader< CT_PageField_reader > _pageField_reader;
		protected:
			CT_PageFields* t() { return static_cast<CT_PageFields*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_DataField_reader : public type_reader
		{
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_DataField* t() { return static_cast<CT_DataField*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_DataFields_reader : public type_reader
		{
			auto_type_reader< CT_DataField_reader > _dataField_reader;
		protected:
			CT_DataFields* t() { return static_cast<CT_DataFields*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Format_reader : public type_reader
		{
			auto_type_reader< CT_PivotArea_reader > _pivotArea_reader;
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_Format* t() { return static_cast<CT_Format*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Formats_reader : public type_reader
		{
			auto_type_reader< CT_Format_reader > _format_reader;
		protected:
			CT_Formats* t() { return static_cast<CT_Formats*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_PivotAreas_reader : public type_reader
		{
			auto_type_reader< CT_PivotArea_reader > _pivotArea_reader;
		protected:
			CT_PivotAreas* t() { return static_cast<CT_PivotAreas*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_ConditionalFormat_reader : public type_reader
		{
			auto_type_reader< CT_PivotAreas_reader > _pivotAreas_reader;
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_ConditionalFormat* t() { return static_cast<CT_ConditionalFormat*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_ConditionalFormats_reader : public type_reader
		{
			auto_type_reader< CT_ConditionalFormat_reader > _conditionalFormat_reader;
		protected:
			CT_ConditionalFormats* t() { return static_cast<CT_ConditionalFormats*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_ChartFormat_reader : public type_reader
		{
			auto_type_reader< CT_PivotArea_reader > _pivotArea_reader;
		protected:
			CT_ChartFormat* t() { return static_cast<CT_ChartFormat*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_ChartFormats_reader : public type_reader
		{
			auto_type_reader< CT_ChartFormat_reader > _chartFormat_reader;
		protected:
			CT_ChartFormats* t() { return static_cast<CT_ChartFormats*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_MemberProperty_reader : public type_reader
		{
		protected:
			CT_MemberProperty* t() { return static_cast<CT_MemberProperty*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_MemberProperties_reader : public type_reader
		{
			auto_type_reader< CT_MemberProperty_reader > _mp_reader;
		protected:
			CT_MemberProperties* t() { return static_cast<CT_MemberProperties*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Member_reader : public type_reader
		{
		protected:
			CT_Member* t() { return static_cast<CT_Member*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Members_reader : public type_reader
		{
			auto_type_reader< CT_Member_reader > _member_reader;
		protected:
			CT_Members* t() { return static_cast<CT_Members*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_PivotHierarchy_reader : public type_reader
		{
			auto_type_reader< CT_MemberProperties_reader > _mps_reader;
			auto_type_reader< CT_Members_reader > _members_reader;
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_PivotHierarchy* t() { return static_cast<CT_PivotHierarchy*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_PivotHierarchies_reader : public type_reader
		{
			auto_type_reader< CT_PivotHierarchy_reader > _pivotHierarchy_reader;
		protected:
			CT_PivotHierarchies* t() { return static_cast<CT_PivotHierarchies*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_PivotTableStyle_reader : public type_reader
		{
		protected:
			CT_PivotTableStyle* t() { return static_cast<CT_PivotTableStyle*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_PivotFilter_reader : public type_reader
		{
			auto_type_reader< CT_AutoFilter_reader > _autoFilter_reader;
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_PivotFilter* t() { return static_cast<CT_PivotFilter*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_PivotFilters_reader : public type_reader
		{
			auto_type_reader< CT_PivotFilter_reader > _filter_reader;
		protected:
			CT_PivotFilters* t() { return static_cast<CT_PivotFilters*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_HierarchyUsage_reader : public type_reader
		{
		protected:
			CT_HierarchyUsage* t() { return static_cast<CT_HierarchyUsage*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_RowHierarchiesUsage_reader : public type_reader
		{
			auto_type_reader< CT_HierarchyUsage_reader > _rowHierarchyUsage_reader;
		protected:
			CT_RowHierarchiesUsage* t() { return static_cast<CT_RowHierarchiesUsage*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_ColHierarchiesUsage_reader : public type_reader
		{
			auto_type_reader< CT_HierarchyUsage_reader > _colHierarchyUsage_reader;
		protected:
			CT_ColHierarchiesUsage* t() { return static_cast<CT_ColHierarchiesUsage*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_pivotTableDefinition_reader : public type_reader
		{
			auto_type_reader< CT_Location_reader > _location_reader;
			auto_type_reader< CT_PivotFields_reader > _pivotFields_reader;
			auto_type_reader< CT_RowFields_reader > _rowFields_reader;
			auto_type_reader< CT_rowItems_reader > _rowItems_reader;
			auto_type_reader< CT_ColFields_reader > _colFields_reader;
			auto_type_reader< CT_colItems_reader > _colItems_reader;
			auto_type_reader< CT_PageFields_reader > _pageFields_reader;
			auto_type_reader< CT_DataFields_reader > _dataFields_reader;
			auto_type_reader< CT_Formats_reader > _formats_reader;
			auto_type_reader< CT_ConditionalFormats_reader > _conditionalFormats_reader;
			auto_type_reader< CT_ChartFormats_reader > _chartFormats_reader;
			auto_type_reader< CT_PivotHierarchies_reader > _pivotHierarchies_reader;
			auto_type_reader< CT_PivotTableStyle_reader > _pivotTableStyleInfo_reader;
			auto_type_reader< CT_PivotFilters_reader > _filters_reader;
			auto_type_reader< CT_RowHierarchiesUsage_reader > _rowHierarchiesUsage_reader;
			auto_type_reader< CT_ColHierarchiesUsage_reader > _colHierarchiesUsage_reader;
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_pivotTableDefinition* t() { return static_cast<CT_pivotTableDefinition*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class sml_pivotTable_reader : public type_reader
		{
			auto_type_reader< CT_PivotCacheDefinition_reader > _pivotCacheDefinition_reader;
			auto_type_reader< CT_PivotCacheRecords_reader > _pivotCacheRecords_reader;
			auto_type_reader< CT_pivotTableDefinition_reader > _pivotTableDefinition_reader;
		protected:
			sml_pivotTable* t() { return static_cast<sml_pivotTable*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

	}
}
#endif

