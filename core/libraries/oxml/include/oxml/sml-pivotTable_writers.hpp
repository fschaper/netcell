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

#ifndef SML_PIVOTTABLE_WRITERS_HPP
#define SML_PIVOTTABLE_WRITERS_HPP

#include "sml-pivotTable.hpp"
#include "sml-pivotTable_literals.hpp"
#include "sml-baseTypes_writers.hpp"
#include "shared-relationshipReference_writers.hpp"
#include "sml-pivotTableShared_writers.hpp"
#include "sml-styles_writers.hpp"
#include "sml-sheet_writers.hpp"
#include "sml-autoFilter_writers.hpp"

namespace spreadsheetml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_WorksheetSource_writer;
		class CT_PageItem_writer;
		class CT_PCDSCPage_writer;
		class CT_Pages_writer;
		class CT_RangeSet_writer;
		class CT_RangeSets_writer;
		class CT_Consolidation_writer;
		class CT_CacheSource_writer;
		class CT_Tuple_writer;
		class CT_Tuples_writer;
		class CT_X_writer;
		class CT_Missing_writer;
		class CT_Number_writer;
		class CT_Boolean_writer;
		class CT_Error_writer;
		class CT_String_writer;
		class CT_DateTime_writer;
		class CT_SharedItems_writer;
		class CT_RangePr_writer;
		class CT_DiscretePr_writer;
		class CT_GroupItems_writer;
		class CT_FieldGroup_writer;
		class CT_CacheField_writer;
		class CT_CacheFields_writer;
		class CT_FieldUsage_writer;
		class CT_FieldsUsage_writer;
		class CT_GroupMember_writer;
		class CT_GroupMembers_writer;
		class CT_LevelGroup_writer;
		class CT_Groups_writer;
		class CT_GroupLevel_writer;
		class CT_GroupLevels_writer;
		class CT_CacheHierarchy_writer;
		class CT_CacheHierarchies_writer;
		class CT_PCDKPI_writer;
		class CT_PCDKPIs_writer;
		class CT_PCDSDTCEntries_writer;
		class CT_Set_writer;
		class CT_Sets_writer;
		class CT_Query_writer;
		class CT_QueryCache_writer;
		class CT_ServerFormat_writer;
		class CT_ServerFormats_writer;
		class CT_TupleCache_writer;
		class CT_CalculatedItem_writer;
		class CT_CalculatedItems_writer;
		class CT_CalculatedMember_writer;
		class CT_CalculatedMembers_writer;
		class CT_PivotDimension_writer;
		class CT_Dimensions_writer;
		class CT_MeasureGroup_writer;
		class CT_MeasureGroups_writer;
		class CT_MeasureDimensionMap_writer;
		class CT_MeasureDimensionMaps_writer;
		class CT_PivotCacheDefinition_writer;
		class CT_Record_writer;
		class CT_PivotCacheRecords_writer;
		class CT_Location_writer;
		class CT_Item_writer;
		class CT_Items_writer;
		class CT_AutoSortScope_writer;
		class CT_PivotField_writer;
		class CT_PivotFields_writer;
		class CT_Field_writer;
		class CT_RowFields_writer;
		class CT_I_writer;
		class CT_rowItems_writer;
		class CT_ColFields_writer;
		class CT_colItems_writer;
		class CT_PageField_writer;
		class CT_PageFields_writer;
		class CT_DataField_writer;
		class CT_DataFields_writer;
		class CT_Format_writer;
		class CT_Formats_writer;
		class CT_PivotAreas_writer;
		class CT_ConditionalFormat_writer;
		class CT_ConditionalFormats_writer;
		class CT_ChartFormat_writer;
		class CT_ChartFormats_writer;
		class CT_MemberProperty_writer;
		class CT_MemberProperties_writer;
		class CT_Member_writer;
		class CT_Members_writer;
		class CT_PivotHierarchy_writer;
		class CT_PivotHierarchies_writer;
		class CT_PivotTableStyle_writer;
		class CT_PivotFilter_writer;
		class CT_PivotFilters_writer;
		class CT_HierarchyUsage_writer;
		class CT_RowHierarchiesUsage_writer;
		class CT_ColHierarchiesUsage_writer;
		class CT_pivotTableDefinition_writer;
		class sml_pivotTable_writer;

		class CT_WorksheetSource_writer : public type_writer
		{
			CT_WorksheetSource* t() { return static_cast<CT_WorksheetSource*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_PageItem_writer : public type_writer
		{
			CT_PageItem* t() { return static_cast<CT_PageItem*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_PCDSCPage_writer : public type_writer
		{
			auto_type_writer< CT_PageItem_writer > _pageItem_writer;
			CT_PCDSCPage* t() { return static_cast<CT_PCDSCPage*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Pages_writer : public type_writer
		{
			auto_type_writer< CT_PCDSCPage_writer > _page_writer;
			CT_Pages* t() { return static_cast<CT_Pages*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_RangeSet_writer : public type_writer
		{
			CT_RangeSet* t() { return static_cast<CT_RangeSet*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_RangeSets_writer : public type_writer
		{
			auto_type_writer< CT_RangeSet_writer > _rangeSet_writer;
			CT_RangeSets* t() { return static_cast<CT_RangeSets*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Consolidation_writer : public type_writer
		{
			auto_type_writer< CT_Pages_writer > _pages_writer;
			auto_type_writer< CT_RangeSets_writer > _rangeSets_writer;
			CT_Consolidation* t() { return static_cast<CT_Consolidation*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_CacheSource_writer : public type_writer
		{
			auto_type_writer< CT_WorksheetSource_writer > _worksheetSource_writer;
			auto_type_writer< CT_Consolidation_writer > _consolidation_writer;
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_CacheSource* t() { return static_cast<CT_CacheSource*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Tuple_writer : public type_writer
		{
			CT_Tuple* t() { return static_cast<CT_Tuple*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Tuples_writer : public type_writer
		{
			auto_type_writer< CT_Tuple_writer > _tpl_writer;
			CT_Tuples* t() { return static_cast<CT_Tuples*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_X_writer : public type_writer
		{
			CT_X* t() { return static_cast<CT_X*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Missing_writer : public type_writer
		{
			auto_type_writer< CT_Tuples_writer > _tpls_writer;
			auto_type_writer< CT_X_writer > _x_writer;
			CT_Missing* t() { return static_cast<CT_Missing*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Number_writer : public type_writer
		{
			auto_type_writer< CT_Tuples_writer > _tpls_writer;
			auto_type_writer< CT_X_writer > _x_writer;
			CT_Number* t() { return static_cast<CT_Number*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Boolean_writer : public type_writer
		{
			auto_type_writer< CT_X_writer > _x_writer;
			CT_Boolean* t() { return static_cast<CT_Boolean*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Error_writer : public type_writer
		{
			auto_type_writer< CT_Tuples_writer > _tpls_writer;
			auto_type_writer< CT_X_writer > _x_writer;
			CT_Error* t() { return static_cast<CT_Error*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_String_writer : public type_writer
		{
			auto_type_writer< CT_Tuples_writer > _tpls_writer;
			auto_type_writer< CT_X_writer > _x_writer;
			CT_String* t() { return static_cast<CT_String*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_DateTime_writer : public type_writer
		{
			auto_type_writer< CT_X_writer > _x_writer;
			CT_DateTime* t() { return static_cast<CT_DateTime*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_SharedItems_writer : public type_writer
		{
			auto_type_writer< CT_Missing_writer > _m_writer;
			auto_type_writer< CT_Number_writer > _n_writer;
			auto_type_writer< CT_Boolean_writer > _b_writer;
			auto_type_writer< CT_Error_writer > _e_writer;
			auto_type_writer< CT_String_writer > _s_writer;
			auto_type_writer< CT_DateTime_writer > _d_writer;
			CT_SharedItems* t() { return static_cast<CT_SharedItems*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_RangePr_writer : public type_writer
		{
			CT_RangePr* t() { return static_cast<CT_RangePr*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_DiscretePr_writer : public type_writer
		{
			auto_type_writer< CT_Index_writer > _x_writer;
			CT_DiscretePr* t() { return static_cast<CT_DiscretePr*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_GroupItems_writer : public type_writer
		{
			auto_type_writer< CT_Missing_writer > _m_writer;
			auto_type_writer< CT_Number_writer > _n_writer;
			auto_type_writer< CT_Boolean_writer > _b_writer;
			auto_type_writer< CT_Error_writer > _e_writer;
			auto_type_writer< CT_String_writer > _s_writer;
			auto_type_writer< CT_DateTime_writer > _d_writer;
			CT_GroupItems* t() { return static_cast<CT_GroupItems*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_FieldGroup_writer : public type_writer
		{
			auto_type_writer< CT_RangePr_writer > _rangePr_writer;
			auto_type_writer< CT_DiscretePr_writer > _discretePr_writer;
			auto_type_writer< CT_GroupItems_writer > _groupItems_writer;
			CT_FieldGroup* t() { return static_cast<CT_FieldGroup*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_CacheField_writer : public type_writer
		{
			auto_type_writer< CT_SharedItems_writer > _sharedItems_writer;
			auto_type_writer< CT_FieldGroup_writer > _fieldGroup_writer;
			auto_type_writer< CT_X_writer > _mpMap_writer;
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_CacheField* t() { return static_cast<CT_CacheField*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_CacheFields_writer : public type_writer
		{
			auto_type_writer< CT_CacheField_writer > _cacheField_writer;
			CT_CacheFields* t() { return static_cast<CT_CacheFields*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_FieldUsage_writer : public type_writer
		{
			CT_FieldUsage* t() { return static_cast<CT_FieldUsage*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_FieldsUsage_writer : public type_writer
		{
			auto_type_writer< CT_FieldUsage_writer > _fieldUsage_writer;
			CT_FieldsUsage* t() { return static_cast<CT_FieldsUsage*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_GroupMember_writer : public type_writer
		{
			CT_GroupMember* t() { return static_cast<CT_GroupMember*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_GroupMembers_writer : public type_writer
		{
			auto_type_writer< CT_GroupMember_writer > _groupMember_writer;
			CT_GroupMembers* t() { return static_cast<CT_GroupMembers*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_LevelGroup_writer : public type_writer
		{
			auto_type_writer< CT_GroupMembers_writer > _groupMembers_writer;
			CT_LevelGroup* t() { return static_cast<CT_LevelGroup*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Groups_writer : public type_writer
		{
			auto_type_writer< CT_LevelGroup_writer > _group_writer;
			CT_Groups* t() { return static_cast<CT_Groups*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_GroupLevel_writer : public type_writer
		{
			auto_type_writer< CT_Groups_writer > _groups_writer;
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_GroupLevel* t() { return static_cast<CT_GroupLevel*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_GroupLevels_writer : public type_writer
		{
			auto_type_writer< CT_GroupLevel_writer > _groupLevel_writer;
			CT_GroupLevels* t() { return static_cast<CT_GroupLevels*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_CacheHierarchy_writer : public type_writer
		{
			auto_type_writer< CT_FieldsUsage_writer > _fieldsUsage_writer;
			auto_type_writer< CT_GroupLevels_writer > _groupLevels_writer;
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_CacheHierarchy* t() { return static_cast<CT_CacheHierarchy*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_CacheHierarchies_writer : public type_writer
		{
			auto_type_writer< CT_CacheHierarchy_writer > _cacheHierarchy_writer;
			CT_CacheHierarchies* t() { return static_cast<CT_CacheHierarchies*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_PCDKPI_writer : public type_writer
		{
			CT_PCDKPI* t() { return static_cast<CT_PCDKPI*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_PCDKPIs_writer : public type_writer
		{
			auto_type_writer< CT_PCDKPI_writer > _kpi_writer;
			CT_PCDKPIs* t() { return static_cast<CT_PCDKPIs*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_PCDSDTCEntries_writer : public type_writer
		{
			auto_type_writer< CT_Missing_writer > _m_writer;
			auto_type_writer< CT_Number_writer > _n_writer;
			auto_type_writer< CT_Error_writer > _e_writer;
			auto_type_writer< CT_String_writer > _s_writer;
			CT_PCDSDTCEntries* t() { return static_cast<CT_PCDSDTCEntries*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Set_writer : public type_writer
		{
			auto_type_writer< CT_Tuples_writer > _tpls_writer;
			auto_type_writer< CT_Tuples_writer > _sortByTuple_writer;
			CT_Set* t() { return static_cast<CT_Set*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Sets_writer : public type_writer
		{
			auto_type_writer< CT_Set_writer > _set_writer;
			CT_Sets* t() { return static_cast<CT_Sets*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Query_writer : public type_writer
		{
			auto_type_writer< CT_Tuples_writer > _tpls_writer;
			CT_Query* t() { return static_cast<CT_Query*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_QueryCache_writer : public type_writer
		{
			auto_type_writer< CT_Query_writer > _query_writer;
			CT_QueryCache* t() { return static_cast<CT_QueryCache*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_ServerFormat_writer : public type_writer
		{
			CT_ServerFormat* t() { return static_cast<CT_ServerFormat*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_ServerFormats_writer : public type_writer
		{
			auto_type_writer< CT_ServerFormat_writer > _serverFormat_writer;
			CT_ServerFormats* t() { return static_cast<CT_ServerFormats*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_TupleCache_writer : public type_writer
		{
			auto_type_writer< CT_PCDSDTCEntries_writer > _entries_writer;
			auto_type_writer< CT_Sets_writer > _sets_writer;
			auto_type_writer< CT_QueryCache_writer > _queryCache_writer;
			auto_type_writer< CT_ServerFormats_writer > _serverFormats_writer;
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_TupleCache* t() { return static_cast<CT_TupleCache*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_CalculatedItem_writer : public type_writer
		{
			auto_type_writer< CT_PivotArea_writer > _pivotArea_writer;
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_CalculatedItem* t() { return static_cast<CT_CalculatedItem*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_CalculatedItems_writer : public type_writer
		{
			auto_type_writer< CT_CalculatedItem_writer > _calculatedItem_writer;
			CT_CalculatedItems* t() { return static_cast<CT_CalculatedItems*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_CalculatedMember_writer : public type_writer
		{
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_CalculatedMember* t() { return static_cast<CT_CalculatedMember*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_CalculatedMembers_writer : public type_writer
		{
			auto_type_writer< CT_CalculatedMember_writer > _calculatedMember_writer;
			CT_CalculatedMembers* t() { return static_cast<CT_CalculatedMembers*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_PivotDimension_writer : public type_writer
		{
			CT_PivotDimension* t() { return static_cast<CT_PivotDimension*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Dimensions_writer : public type_writer
		{
			auto_type_writer< CT_PivotDimension_writer > _dimension_writer;
			CT_Dimensions* t() { return static_cast<CT_Dimensions*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_MeasureGroup_writer : public type_writer
		{
			CT_MeasureGroup* t() { return static_cast<CT_MeasureGroup*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_MeasureGroups_writer : public type_writer
		{
			auto_type_writer< CT_MeasureGroup_writer > _measureGroup_writer;
			CT_MeasureGroups* t() { return static_cast<CT_MeasureGroups*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_MeasureDimensionMap_writer : public type_writer
		{
			CT_MeasureDimensionMap* t() { return static_cast<CT_MeasureDimensionMap*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_MeasureDimensionMaps_writer : public type_writer
		{
			auto_type_writer< CT_MeasureDimensionMap_writer > _map_writer;
			CT_MeasureDimensionMaps* t() { return static_cast<CT_MeasureDimensionMaps*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_PivotCacheDefinition_writer : public type_writer
		{
			auto_type_writer< CT_CacheSource_writer > _cacheSource_writer;
			auto_type_writer< CT_CacheFields_writer > _cacheFields_writer;
			auto_type_writer< CT_CacheHierarchies_writer > _cacheHierarchies_writer;
			auto_type_writer< CT_PCDKPIs_writer > _kpis_writer;
			auto_type_writer< CT_TupleCache_writer > _tupleCache_writer;
			auto_type_writer< CT_CalculatedItems_writer > _calculatedItems_writer;
			auto_type_writer< CT_CalculatedMembers_writer > _calculatedMembers_writer;
			auto_type_writer< CT_Dimensions_writer > _dimensions_writer;
			auto_type_writer< CT_MeasureGroups_writer > _measureGroups_writer;
			auto_type_writer< CT_MeasureDimensionMaps_writer > _maps_writer;
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_PivotCacheDefinition* t() { return static_cast<CT_PivotCacheDefinition*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Record_writer : public type_writer
		{
			auto_type_writer< CT_Missing_writer > _m_writer;
			auto_type_writer< CT_Number_writer > _n_writer;
			auto_type_writer< CT_Boolean_writer > _b_writer;
			auto_type_writer< CT_Error_writer > _e_writer;
			auto_type_writer< CT_String_writer > _s_writer;
			auto_type_writer< CT_DateTime_writer > _d_writer;
			auto_type_writer< CT_Index_writer > _x_writer;
			CT_Record* t() { return static_cast<CT_Record*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_PivotCacheRecords_writer : public type_writer
		{
			auto_type_writer< CT_Record_writer > _r_writer;
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_PivotCacheRecords* t() { return static_cast<CT_PivotCacheRecords*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Location_writer : public type_writer
		{
			CT_Location* t() { return static_cast<CT_Location*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Item_writer : public type_writer
		{
			CT_Item* t() { return static_cast<CT_Item*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Items_writer : public type_writer
		{
			auto_type_writer< CT_Item_writer > _item_writer;
			CT_Items* t() { return static_cast<CT_Items*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_AutoSortScope_writer : public type_writer
		{
			auto_type_writer< CT_PivotArea_writer > _pivotArea_writer;
			CT_AutoSortScope* t() { return static_cast<CT_AutoSortScope*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_PivotField_writer : public type_writer
		{
			auto_type_writer< CT_Items_writer > _items_writer;
			auto_type_writer< CT_AutoSortScope_writer > _autoSortScope_writer;
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_PivotField* t() { return static_cast<CT_PivotField*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_PivotFields_writer : public type_writer
		{
			auto_type_writer< CT_PivotField_writer > _pivotField_writer;
			CT_PivotFields* t() { return static_cast<CT_PivotFields*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Field_writer : public type_writer
		{
			CT_Field* t() { return static_cast<CT_Field*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_RowFields_writer : public type_writer
		{
			auto_type_writer< CT_Field_writer > _field_writer;
			CT_RowFields* t() { return static_cast<CT_RowFields*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_I_writer : public type_writer
		{
			auto_type_writer< CT_X_writer > _x_writer;
			CT_I* t() { return static_cast<CT_I*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_rowItems_writer : public type_writer
		{
			auto_type_writer< CT_I_writer > _i_writer;
			CT_rowItems* t() { return static_cast<CT_rowItems*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_ColFields_writer : public type_writer
		{
			auto_type_writer< CT_Field_writer > _field_writer;
			CT_ColFields* t() { return static_cast<CT_ColFields*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_colItems_writer : public type_writer
		{
			auto_type_writer< CT_I_writer > _i_writer;
			CT_colItems* t() { return static_cast<CT_colItems*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_PageField_writer : public type_writer
		{
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_PageField* t() { return static_cast<CT_PageField*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_PageFields_writer : public type_writer
		{
			auto_type_writer< CT_PageField_writer > _pageField_writer;
			CT_PageFields* t() { return static_cast<CT_PageFields*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_DataField_writer : public type_writer
		{
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_DataField* t() { return static_cast<CT_DataField*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_DataFields_writer : public type_writer
		{
			auto_type_writer< CT_DataField_writer > _dataField_writer;
			CT_DataFields* t() { return static_cast<CT_DataFields*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Format_writer : public type_writer
		{
			auto_type_writer< CT_PivotArea_writer > _pivotArea_writer;
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_Format* t() { return static_cast<CT_Format*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Formats_writer : public type_writer
		{
			auto_type_writer< CT_Format_writer > _format_writer;
			CT_Formats* t() { return static_cast<CT_Formats*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_PivotAreas_writer : public type_writer
		{
			auto_type_writer< CT_PivotArea_writer > _pivotArea_writer;
			CT_PivotAreas* t() { return static_cast<CT_PivotAreas*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_ConditionalFormat_writer : public type_writer
		{
			auto_type_writer< CT_PivotAreas_writer > _pivotAreas_writer;
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_ConditionalFormat* t() { return static_cast<CT_ConditionalFormat*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_ConditionalFormats_writer : public type_writer
		{
			auto_type_writer< CT_ConditionalFormat_writer > _conditionalFormat_writer;
			CT_ConditionalFormats* t() { return static_cast<CT_ConditionalFormats*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_ChartFormat_writer : public type_writer
		{
			auto_type_writer< CT_PivotArea_writer > _pivotArea_writer;
			CT_ChartFormat* t() { return static_cast<CT_ChartFormat*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_ChartFormats_writer : public type_writer
		{
			auto_type_writer< CT_ChartFormat_writer > _chartFormat_writer;
			CT_ChartFormats* t() { return static_cast<CT_ChartFormats*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_MemberProperty_writer : public type_writer
		{
			CT_MemberProperty* t() { return static_cast<CT_MemberProperty*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_MemberProperties_writer : public type_writer
		{
			auto_type_writer< CT_MemberProperty_writer > _mp_writer;
			CT_MemberProperties* t() { return static_cast<CT_MemberProperties*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Member_writer : public type_writer
		{
			CT_Member* t() { return static_cast<CT_Member*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Members_writer : public type_writer
		{
			auto_type_writer< CT_Member_writer > _member_writer;
			CT_Members* t() { return static_cast<CT_Members*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_PivotHierarchy_writer : public type_writer
		{
			auto_type_writer< CT_MemberProperties_writer > _mps_writer;
			auto_type_writer< CT_Members_writer > _members_writer;
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_PivotHierarchy* t() { return static_cast<CT_PivotHierarchy*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_PivotHierarchies_writer : public type_writer
		{
			auto_type_writer< CT_PivotHierarchy_writer > _pivotHierarchy_writer;
			CT_PivotHierarchies* t() { return static_cast<CT_PivotHierarchies*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_PivotTableStyle_writer : public type_writer
		{
			CT_PivotTableStyle* t() { return static_cast<CT_PivotTableStyle*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_PivotFilter_writer : public type_writer
		{
			auto_type_writer< CT_AutoFilter_writer > _autoFilter_writer;
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_PivotFilter* t() { return static_cast<CT_PivotFilter*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_PivotFilters_writer : public type_writer
		{
			auto_type_writer< CT_PivotFilter_writer > _filter_writer;
			CT_PivotFilters* t() { return static_cast<CT_PivotFilters*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_HierarchyUsage_writer : public type_writer
		{
			CT_HierarchyUsage* t() { return static_cast<CT_HierarchyUsage*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_RowHierarchiesUsage_writer : public type_writer
		{
			auto_type_writer< CT_HierarchyUsage_writer > _rowHierarchyUsage_writer;
			CT_RowHierarchiesUsage* t() { return static_cast<CT_RowHierarchiesUsage*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_ColHierarchiesUsage_writer : public type_writer
		{
			auto_type_writer< CT_HierarchyUsage_writer > _colHierarchyUsage_writer;
			CT_ColHierarchiesUsage* t() { return static_cast<CT_ColHierarchiesUsage*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_pivotTableDefinition_writer : public type_writer
		{
			auto_type_writer< CT_Location_writer > _location_writer;
			auto_type_writer< CT_PivotFields_writer > _pivotFields_writer;
			auto_type_writer< CT_RowFields_writer > _rowFields_writer;
			auto_type_writer< CT_rowItems_writer > _rowItems_writer;
			auto_type_writer< CT_ColFields_writer > _colFields_writer;
			auto_type_writer< CT_colItems_writer > _colItems_writer;
			auto_type_writer< CT_PageFields_writer > _pageFields_writer;
			auto_type_writer< CT_DataFields_writer > _dataFields_writer;
			auto_type_writer< CT_Formats_writer > _formats_writer;
			auto_type_writer< CT_ConditionalFormats_writer > _conditionalFormats_writer;
			auto_type_writer< CT_ChartFormats_writer > _chartFormats_writer;
			auto_type_writer< CT_PivotHierarchies_writer > _pivotHierarchies_writer;
			auto_type_writer< CT_PivotTableStyle_writer > _pivotTableStyleInfo_writer;
			auto_type_writer< CT_PivotFilters_writer > _filters_writer;
			auto_type_writer< CT_RowHierarchiesUsage_writer > _rowHierarchiesUsage_writer;
			auto_type_writer< CT_ColHierarchiesUsage_writer > _colHierarchiesUsage_writer;
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_pivotTableDefinition* t() { return static_cast<CT_pivotTableDefinition*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class sml_pivotTable_writer : public type_writer
		{
			auto_type_writer< CT_PivotCacheDefinition_writer > _pivotCacheDefinition_writer;
			auto_type_writer< CT_PivotCacheRecords_writer > _pivotCacheRecords_writer;
			auto_type_writer< CT_pivotTableDefinition_writer > _pivotTableDefinition_writer;
			sml_pivotTable* t() { return static_cast<sml_pivotTable*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

	}
}
#endif

