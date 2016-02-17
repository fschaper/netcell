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

#ifndef SML_PIVOTTABLE_HPP
#define SML_PIVOTTABLE_HPP


#include "sml-baseTypes.hpp"
#include "shared-relationshipReference.hpp"
#include "sml-pivotTableShared.hpp"
#include "sml-styles.hpp"
#include "sml-sheet.hpp"
#include "sml-autoFilter.hpp"

namespace spreadsheetml
{
	using namespace ::xio;
	using namespace ::xio::xml::schema;

	class CT_WorksheetSource;
	class CT_PageItem;
	class CT_PCDSCPage;
	class CT_Pages;
	class CT_RangeSet;
	class CT_RangeSets;
	class CT_Consolidation;
	class CT_CacheSource;
	class CT_Tuple;
	class CT_Tuples;
	class CT_X;
	class CT_Missing;
	class CT_Number;
	class CT_Boolean;
	class CT_Error;
	class CT_String;
	class CT_DateTime;
	class CT_SharedItems;
	class CT_RangePr;
	class CT_DiscretePr;
	class CT_GroupItems;
	class CT_FieldGroup;
	class CT_CacheField;
	class CT_CacheFields;
	class CT_FieldUsage;
	class CT_FieldsUsage;
	class CT_GroupMember;
	class CT_GroupMembers;
	class CT_LevelGroup;
	class CT_Groups;
	class CT_GroupLevel;
	class CT_GroupLevels;
	class CT_CacheHierarchy;
	class CT_CacheHierarchies;
	class CT_PCDKPI;
	class CT_PCDKPIs;
	class CT_PCDSDTCEntries;
	class CT_Set;
	class CT_Sets;
	class CT_Query;
	class CT_QueryCache;
	class CT_ServerFormat;
	class CT_ServerFormats;
	class CT_TupleCache;
	class CT_CalculatedItem;
	class CT_CalculatedItems;
	class CT_CalculatedMember;
	class CT_CalculatedMembers;
	class CT_PivotDimension;
	class CT_Dimensions;
	class CT_MeasureGroup;
	class CT_MeasureGroups;
	class CT_MeasureDimensionMap;
	class CT_MeasureDimensionMaps;
	class CT_PivotCacheDefinition;
	class CT_Record;
	class CT_PivotCacheRecords;
	class CT_Location;
	class CT_Item;
	class CT_Items;
	class CT_AutoSortScope;
	class CT_PivotField;
	class CT_PivotFields;
	class CT_Field;
	class CT_RowFields;
	class CT_I;
	class CT_rowItems;
	class CT_ColFields;
	class CT_colItems;
	class CT_PageField;
	class CT_PageFields;
	class CT_DataField;
	class CT_DataFields;
	class CT_Format;
	class CT_Formats;
	class CT_PivotAreas;
	class CT_ConditionalFormat;
	class CT_ConditionalFormats;
	class CT_ChartFormat;
	class CT_ChartFormats;
	class CT_MemberProperty;
	class CT_MemberProperties;
	class CT_Member;
	class CT_Members;
	class CT_PivotHierarchy;
	class CT_PivotHierarchies;
	class CT_PivotTableStyle;
	class CT_PivotFilter;
	class CT_PivotFilters;
	class CT_HierarchyUsage;
	class CT_RowHierarchiesUsage;
	class CT_ColHierarchiesUsage;
	class CT_pivotTableDefinition;
	class sml_pivotTable;

	class CT_WorksheetSource
	{
	public:
		poptional< ST_Ref > ref;
		poptional< ST_Xstring > name;
		poptional< ST_Xstring > sheet;
		poptional< ::relationships::ST_RelationshipId > id;
	};

	class CT_PageItem
	{
	public:
		ST_Xstring name;
	};

	class CT_PCDSCPage
	{
	public:
		std::vector< CT_PageItem > pageItem;
		optional< UnsignedInt > count;
	};

	class CT_Pages
	{
	public:
		std::vector< CT_PCDSCPage > page;
		optional< UnsignedInt > count;
	};

	class CT_RangeSet
	{
	public:
		optional< UnsignedInt > i1;
		optional< UnsignedInt > i2;
		optional< UnsignedInt > i3;
		optional< UnsignedInt > i4;
		poptional< ST_Ref > ref;
		poptional< ST_Xstring > name;
		poptional< ST_Xstring > sheet;
		poptional< ::relationships::ST_RelationshipId > id;
	};

	class CT_RangeSets
	{
	public:
		std::vector< CT_RangeSet > rangeSet;
		optional< UnsignedInt > count;
	};

	class CT_Consolidation
	{
	public:
		CT_Consolidation() : autoPage(true) {}
		poptional< CT_Pages > pages;
		CT_RangeSets rangeSets;
		Boolean autoPage;
	};

	class ST_SourceType
	{
		static String _literals[];
		String _value;
	public:
		enum value { consolidation, external, scenario, worksheet };

		static const String consolidation_literal;
		static const String external_literal;
		static const String scenario_literal;
		static const String worksheet_literal;

		ST_SourceType() : _value(worksheet_literal) {}
		ST_SourceType(value val) : _value(convert(val)) {}
		ST_SourceType(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 4, 0); }
		static String convert(value v) { return _literals[(int)v]; }

		bool operator == (const String& str) const { return str == _value; }
		bool operator == (value val) const {return convert(val) == _value; }
		bool operator != (const String& str) const { return str != _value; }
		bool operator != (value val) const {return convert(val) != _value; }

		const String& operator = (const String& str) { _value = str; return str; }
		const value& operator = (const value& val) { _value = convert(val); return val; }

		operator const String& () const { return _value; }
		operator String& () { return _value; }
		operator value () const { return convert(_value); }
		String serialize() const { return _value; }
	};

	class CT_CacheSource
	{
	public:
		CT_CacheSource() : connectionId(0U) {}
		poptional< CT_WorksheetSource > worksheetSource;
		poptional< CT_Consolidation > consolidation;
		poptional< CT_ExtensionList > extLst;
		ST_SourceType type;
		UnsignedInt connectionId;
	};

	class CT_Tuple
	{
	public:
		optional< UnsignedInt > fld;
		optional< UnsignedInt > hier;
		UnsignedInt item;
	};

	class CT_Tuples
	{
	public:
		std::vector< CT_Tuple > tpl;
		optional< UnsignedInt > c;
	};

	class CT_X
	{
	public:
		CT_X() : v(0) {}
		Int v;
	};

	class CT_Missing
	{
	public:
		CT_Missing() : i(false), un(false), st(false), b(false) {}
		std::vector< CT_Tuples > tpls;
		std::vector< CT_X > x;
		optional< Boolean > u;
		optional< Boolean > f;
		poptional< ST_Xstring > c;
		optional< UnsignedInt > cp;
		optional< UnsignedInt > in;
		poptional< ST_UnsignedIntHex > bc;
		poptional< ST_UnsignedIntHex > fc;
		Boolean i;
		Boolean un;
		Boolean st;
		Boolean b;
	};

	class CT_Number
	{
	public:
		CT_Number() : i(false), un(false), st(false), b(false) {}
		std::vector< CT_Tuples > tpls;
		std::vector< CT_X > x;
		Double v;
		optional< Boolean > u;
		optional< Boolean > f;
		poptional< ST_Xstring > c;
		optional< UnsignedInt > cp;
		optional< UnsignedInt > in;
		poptional< ST_UnsignedIntHex > bc;
		poptional< ST_UnsignedIntHex > fc;
		Boolean i;
		Boolean un;
		Boolean st;
		Boolean b;
	};

	class CT_Boolean
	{
	public:
		std::vector< CT_X > x;
		Boolean v;
		optional< Boolean > u;
		optional< Boolean > f;
		poptional< ST_Xstring > c;
		optional< UnsignedInt > cp;
	};

	class CT_Error
	{
	public:
		CT_Error() : i(false), un(false), st(false), b(false) {}
		poptional< CT_Tuples > tpls;
		std::vector< CT_X > x;
		ST_Xstring v;
		optional< Boolean > u;
		optional< Boolean > f;
		poptional< ST_Xstring > c;
		optional< UnsignedInt > cp;
		optional< UnsignedInt > in;
		poptional< ST_UnsignedIntHex > bc;
		poptional< ST_UnsignedIntHex > fc;
		Boolean i;
		Boolean un;
		Boolean st;
		Boolean b;
	};

	class CT_String
	{
	public:
		CT_String() : i(false), un(false), st(false), b(false) {}
		std::vector< CT_Tuples > tpls;
		std::vector< CT_X > x;
		ST_Xstring v;
		optional< Boolean > u;
		optional< Boolean > f;
		poptional< ST_Xstring > c;
		optional< UnsignedInt > cp;
		optional< UnsignedInt > in;
		poptional< ST_UnsignedIntHex > bc;
		poptional< ST_UnsignedIntHex > fc;
		Boolean i;
		Boolean un;
		Boolean st;
		Boolean b;
	};

	class CT_DateTime
	{
	public:
		std::vector< CT_X > x;
		DateTime v;
		optional< Boolean > u;
		optional< Boolean > f;
		poptional< ST_Xstring > c;
		optional< UnsignedInt > cp;
	};

	class CT_SharedItems
	{
	public:
		CT_SharedItems() : containsSemiMixedTypes(true), containsNonDate(true), containsDate(false), containsString(true), containsBlank(false), containsMixedTypes(false), containsNumber(false), containsInteger(false), longText(false) {}
		poptional< CT_Missing > m;
		poptional< CT_Number > n;
		poptional< CT_Boolean > b;
		poptional< CT_Error > e;
		poptional< CT_String > s;
		poptional< CT_DateTime > d;
		Boolean containsSemiMixedTypes;
		Boolean containsNonDate;
		Boolean containsDate;
		Boolean containsString;
		Boolean containsBlank;
		Boolean containsMixedTypes;
		Boolean containsNumber;
		Boolean containsInteger;
		optional< Double > minValue;
		optional< Double > maxValue;
		optional< DateTime > minDate;
		optional< DateTime > maxDate;
		optional< UnsignedInt > count;
		Boolean longText;
	};

	class ST_GroupBy
	{
		static String _literals[];
		String _value;
	public:
		enum value { days, hours, minutes, months, quarters, range, seconds, years };

		static const String days_literal;
		static const String hours_literal;
		static const String minutes_literal;
		static const String months_literal;
		static const String quarters_literal;
		static const String range_literal;
		static const String seconds_literal;
		static const String years_literal;

		ST_GroupBy() : _value(range_literal) {}
		ST_GroupBy(value val) : _value(convert(val)) {}
		ST_GroupBy(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 8, 0); }
		static String convert(value v) { return _literals[(int)v]; }

		bool operator == (const String& str) const { return str == _value; }
		bool operator == (value val) const {return convert(val) == _value; }
		bool operator != (const String& str) const { return str != _value; }
		bool operator != (value val) const {return convert(val) != _value; }

		const String& operator = (const String& str) { _value = str; return str; }
		const value& operator = (const value& val) { _value = convert(val); return val; }

		operator const String& () const { return _value; }
		operator String& () { return _value; }
		operator value () const { return convert(_value); }
		String serialize() const { return _value; }
	};

	class CT_RangePr
	{
	public:
		CT_RangePr() : autoStart(true), autoEnd(true), groupBy(ST_GroupBy::range_literal), groupInterval(1) {}
		Boolean autoStart;
		Boolean autoEnd;
		ST_GroupBy groupBy;
		optional< Double > startNum;
		optional< Double > endNum;
		optional< DateTime > startDate;
		optional< DateTime > endDate;
		Double groupInterval;
	};

	class CT_DiscretePr
	{
	public:
		std::vector< CT_Index > x;
		optional< UnsignedInt > count;
	};

	class CT_GroupItems
	{
	public:
		poptional< CT_Missing > m;
		poptional< CT_Number > n;
		poptional< CT_Boolean > b;
		poptional< CT_Error > e;
		poptional< CT_String > s;
		poptional< CT_DateTime > d;
		optional< UnsignedInt > count;
	};

	class CT_FieldGroup
	{
	public:
		poptional< CT_RangePr > rangePr;
		poptional< CT_DiscretePr > discretePr;
		poptional< CT_GroupItems > groupItems;
		optional< UnsignedInt > par;
		optional< UnsignedInt > base;
	};

	class CT_CacheField
	{
	public:
		CT_CacheField() : serverField(false), uniqueList(true), sqlType(0), hierarchy(0), level(0U), databaseField(true), memberPropertyField(false) {}
		poptional< CT_SharedItems > sharedItems;
		poptional< CT_FieldGroup > fieldGroup;
		std::vector< CT_X > mpMap;
		poptional< CT_ExtensionList > extLst;
		ST_Xstring name;
		poptional< ST_Xstring > caption;
		poptional< ST_Xstring > propertyName;
		Boolean serverField;
		Boolean uniqueList;
		poptional< ST_NumFmtId > numFmtId;
		poptional< ST_Xstring > formula;
		Int sqlType;
		Int hierarchy;
		UnsignedInt level;
		Boolean databaseField;
		optional< UnsignedInt > mappingCount;
		Boolean memberPropertyField;
	};

	class CT_CacheFields
	{
	public:
		std::vector< CT_CacheField > cacheField;
		optional< UnsignedInt > count;
	};

	class CT_FieldUsage
	{
	public:
		Int x;
	};

	class CT_FieldsUsage
	{
	public:
		std::vector< CT_FieldUsage > fieldUsage;
		optional< UnsignedInt > count;
	};

	class CT_GroupMember
	{
	public:
		CT_GroupMember() : group(false) {}
		ST_Xstring uniqueName;
		Boolean group;
	};

	class CT_GroupMembers
	{
	public:
		std::vector< CT_GroupMember > groupMember;
		optional< UnsignedInt > count;
	};

	class CT_LevelGroup
	{
	public:
		CT_GroupMembers groupMembers;
		ST_Xstring name;
		ST_Xstring uniqueName;
		ST_Xstring caption;
		poptional< ST_Xstring > uniqueParent;
		optional< Int > id;
	};

	class CT_Groups
	{
	public:
		std::vector< CT_LevelGroup > group;
		optional< UnsignedInt > count;
	};

	class CT_GroupLevel
	{
	public:
		CT_GroupLevel() : user(false), customRollUp(false) {}
		poptional< CT_Groups > groups;
		poptional< CT_ExtensionList > extLst;
		ST_Xstring uniqueName;
		ST_Xstring caption;
		Boolean user;
		Boolean customRollUp;
	};

	class CT_GroupLevels
	{
	public:
		std::vector< CT_GroupLevel > groupLevel;
		optional< UnsignedInt > count;
	};

	class CT_CacheHierarchy
	{
	public:
		CT_CacheHierarchy() : measure(false), set(false), iconSet(0), attribute(false), time(false), keyAttribute(false), measures(false), oneField(false), hidden(false) {}
		poptional< CT_FieldsUsage > fieldsUsage;
		poptional< CT_GroupLevels > groupLevels;
		poptional< CT_ExtensionList > extLst;
		ST_Xstring uniqueName;
		poptional< ST_Xstring > caption;
		Boolean measure;
		Boolean set;
		optional< UnsignedInt > parentSet;
		Int iconSet;
		Boolean attribute;
		Boolean time;
		Boolean keyAttribute;
		poptional< ST_Xstring > defaultMemberUniqueName;
		poptional< ST_Xstring > allUniqueName;
		poptional< ST_Xstring > allCaption;
		poptional< ST_Xstring > dimensionUniqueName;
		poptional< ST_Xstring > displayFolder;
		poptional< ST_Xstring > measureGroup;
		Boolean measures;
		UnsignedInt count;
		Boolean oneField;
		optional< UnsignedShort > memberValueDatatype;
		optional< Boolean > unbalanced;
		optional< Boolean > unbalancedGroup;
		Boolean hidden;
	};

	class CT_CacheHierarchies
	{
	public:
		std::vector< CT_CacheHierarchy > cacheHierarchy;
		optional< UnsignedInt > count;
	};

	class CT_PCDKPI
	{
	public:
		ST_Xstring uniqueName;
		poptional< ST_Xstring > caption;
		poptional< ST_Xstring > displayFolder;
		poptional< ST_Xstring > measureGroup;
		poptional< ST_Xstring > parent;
		ST_Xstring value;
		poptional< ST_Xstring > goal;
		poptional< ST_Xstring > status;
		poptional< ST_Xstring > trend;
		poptional< ST_Xstring > weight;
		poptional< ST_Xstring > time;
	};

	class CT_PCDKPIs
	{
	public:
		std::vector< CT_PCDKPI > kpi;
		optional< UnsignedInt > count;
	};

	class CT_PCDSDTCEntries
	{
	public:
		poptional< CT_Missing > m;
		poptional< CT_Number > n;
		poptional< CT_Error > e;
		poptional< CT_String > s;
		optional< UnsignedInt > count;
	};

	class ST_SortType
	{
		static String _literals[];
		String _value;
	public:
		enum value { ascending, ascendingAlpha, ascendingNatural, descending, descendingAlpha, descendingNatural, none };

		static const String ascending_literal;
		static const String ascendingAlpha_literal;
		static const String ascendingNatural_literal;
		static const String descending_literal;
		static const String descendingAlpha_literal;
		static const String descendingNatural_literal;
		static const String none_literal;

		ST_SortType() : _value(none_literal) {}
		ST_SortType(value val) : _value(convert(val)) {}
		ST_SortType(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 7, 0); }
		static String convert(value v) { return _literals[(int)v]; }

		bool operator == (const String& str) const { return str == _value; }
		bool operator == (value val) const {return convert(val) == _value; }
		bool operator != (const String& str) const { return str != _value; }
		bool operator != (value val) const {return convert(val) != _value; }

		const String& operator = (const String& str) { _value = str; return str; }
		const value& operator = (const value& val) { _value = convert(val); return val; }

		operator const String& () const { return _value; }
		operator String& () { return _value; }
		operator value () const { return convert(_value); }
		String serialize() const { return _value; }
	};

	class CT_Set
	{
	public:
		CT_Set() : sortType(ST_SortType::none_literal), queryFailed(false) {}
		std::vector< CT_Tuples > tpls;
		poptional< CT_Tuples > sortByTuple;
		optional< UnsignedInt > count;
		Int maxRank;
		ST_Xstring setDefinition;
		ST_SortType sortType;
		Boolean queryFailed;
	};

	class CT_Sets
	{
	public:
		std::vector< CT_Set > set;
		optional< UnsignedInt > count;
	};

	class CT_Query
	{
	public:
		poptional< CT_Tuples > tpls;
		ST_Xstring mdx;
	};

	class CT_QueryCache
	{
	public:
		std::vector< CT_Query > query;
		optional< UnsignedInt > count;
	};

	class CT_ServerFormat
	{
	public:
		poptional< ST_Xstring > culture;
		poptional< ST_Xstring > format;
	};

	class CT_ServerFormats
	{
	public:
		std::vector< CT_ServerFormat > serverFormat;
		optional< UnsignedInt > count;
	};

	class CT_TupleCache
	{
	public:
		poptional< CT_PCDSDTCEntries > entries;
		poptional< CT_Sets > sets;
		poptional< CT_QueryCache > queryCache;
		poptional< CT_ServerFormats > serverFormats;
		poptional< CT_ExtensionList > extLst;
	};

	class CT_CalculatedItem
	{
	public:
		CT_PivotArea pivotArea;
		poptional< CT_ExtensionList > extLst;
		optional< UnsignedInt > field;
		poptional< ST_Xstring > formula;
	};

	class CT_CalculatedItems
	{
	public:
		std::vector< CT_CalculatedItem > calculatedItem;
		optional< UnsignedInt > count;
	};

	class CT_CalculatedMember
	{
	public:
		CT_CalculatedMember() : solveOrder(0), set(false) {}
		poptional< CT_ExtensionList > extLst;
		ST_Xstring name;
		ST_Xstring mdx;
		poptional< ST_Xstring > memberName;
		poptional< ST_Xstring > hierarchy;
		poptional< ST_Xstring > parent;
		Int solveOrder;
		Boolean set;
	};

	class CT_CalculatedMembers
	{
	public:
		std::vector< CT_CalculatedMember > calculatedMember;
		optional< UnsignedInt > count;
	};

	class CT_PivotDimension
	{
	public:
		CT_PivotDimension() : measure(false) {}
		Boolean measure;
		ST_Xstring name;
		ST_Xstring uniqueName;
		ST_Xstring caption;
	};

	class CT_Dimensions
	{
	public:
		std::vector< CT_PivotDimension > dimension;
		optional< UnsignedInt > count;
	};

	class CT_MeasureGroup
	{
	public:
		ST_Xstring name;
		ST_Xstring caption;
	};

	class CT_MeasureGroups
	{
	public:
		std::vector< CT_MeasureGroup > measureGroup;
		optional< UnsignedInt > count;
	};

	class CT_MeasureDimensionMap
	{
	public:
		optional< UnsignedInt > measureGroup;
		optional< UnsignedInt > dimension;
	};

	class CT_MeasureDimensionMaps
	{
	public:
		std::vector< CT_MeasureDimensionMap > map;
		optional< UnsignedInt > count;
	};

	class CT_PivotCacheDefinition
	{
	public:
		CT_PivotCacheDefinition() : invalid(false), saveData(true), refreshOnLoad(false), optimizeMemory(false), enableRefresh(true), backgroundQuery(false), createdVersion(0), refreshedVersion(0), minRefreshableVersion(0), upgradeOnRefresh(false), tupleCache_attr(false), supportSubquery(false), supportAdvancedDrill(false) {}
		CT_CacheSource cacheSource;
		CT_CacheFields cacheFields;
		poptional< CT_CacheHierarchies > cacheHierarchies;
		poptional< CT_PCDKPIs > kpis;
		poptional< CT_TupleCache > tupleCache;
		poptional< CT_CalculatedItems > calculatedItems;
		poptional< CT_CalculatedMembers > calculatedMembers;
		poptional< CT_Dimensions > dimensions;
		poptional< CT_MeasureGroups > measureGroups;
		poptional< CT_MeasureDimensionMaps > maps;
		poptional< CT_ExtensionList > extLst;
		poptional< ::relationships::ST_RelationshipId > id;
		Boolean invalid;
		Boolean saveData;
		Boolean refreshOnLoad;
		Boolean optimizeMemory;
		Boolean enableRefresh;
		poptional< ST_Xstring > refreshedBy;
		optional< Double > refreshedDate;
		Boolean backgroundQuery;
		optional< UnsignedInt > missingItemsLimit;
		UnsignedByte createdVersion;
		UnsignedByte refreshedVersion;
		UnsignedByte minRefreshableVersion;
		optional< UnsignedInt > recordCount;
		Boolean upgradeOnRefresh;
		Boolean tupleCache_attr;
		Boolean supportSubquery;
		Boolean supportAdvancedDrill;
	};

	class CT_Record
	{
	public:
		poptional< CT_Missing > m;
		poptional< CT_Number > n;
		poptional< CT_Boolean > b;
		poptional< CT_Error > e;
		poptional< CT_String > s;
		poptional< CT_DateTime > d;
		poptional< CT_Index > x;
	};

	class CT_PivotCacheRecords
	{
	public:
		std::vector< CT_Record > r;
		poptional< CT_ExtensionList > extLst;
		optional< UnsignedInt > count;
	};

	class CT_Location
	{
	public:
		CT_Location() : rowPageCount(0U), colPageCount(0U) {}
		ST_Ref ref;
		UnsignedInt firstHeaderRow;
		UnsignedInt firstDataRow;
		UnsignedInt firstDataCol;
		UnsignedInt rowPageCount;
		UnsignedInt colPageCount;
	};

	class ST_ItemType
	{
		static String _literals[];
		String _value;
	public:
		enum value { avg, blank, count, countA, data, _default_, grand, max, min, product, stdDev, stdDevP, sum, var, varP };

		static const String avg_literal;
		static const String blank_literal;
		static const String count_literal;
		static const String countA_literal;
		static const String data_literal;
		static const String _default__literal;
		static const String grand_literal;
		static const String max_literal;
		static const String min_literal;
		static const String product_literal;
		static const String stdDev_literal;
		static const String stdDevP_literal;
		static const String sum_literal;
		static const String var_literal;
		static const String varP_literal;

		ST_ItemType() : _value(data_literal) {}
		ST_ItemType(value val) : _value(convert(val)) {}
		ST_ItemType(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 15, 0); }
		static String convert(value v) { return _literals[(int)v]; }

		bool operator == (const String& str) const { return str == _value; }
		bool operator == (value val) const {return convert(val) == _value; }
		bool operator != (const String& str) const { return str != _value; }
		bool operator != (value val) const {return convert(val) != _value; }

		const String& operator = (const String& str) { _value = str; return str; }
		const value& operator = (const value& val) { _value = convert(val); return val; }

		operator const String& () const { return _value; }
		operator String& () { return _value; }
		operator value () const { return convert(_value); }
		String serialize() const { return _value; }
	};

	class CT_Item
	{
	public:
		CT_Item() : t(ST_ItemType::data_literal), h(false), s(false), sd(true), f(false), m(false), c(false), d(false), e(true) {}
		poptional< ST_Xstring > n;
		ST_ItemType t;
		Boolean h;
		Boolean s;
		Boolean sd;
		Boolean f;
		Boolean m;
		Boolean c;
		optional< UnsignedInt > x;
		Boolean d;
		Boolean e;
	};

	class CT_Items
	{
	public:
		std::vector< CT_Item > item;
		optional< UnsignedInt > count;
	};

	class CT_AutoSortScope
	{
	public:
		CT_PivotArea pivotArea;
	};

	class ST_FieldSortType
	{
		static String _literals[];
		String _value;
	public:
		enum value { ascending, descending, manual };

		static const String ascending_literal;
		static const String descending_literal;
		static const String manual_literal;

		ST_FieldSortType() : _value(manual_literal) {}
		ST_FieldSortType(value val) : _value(convert(val)) {}
		ST_FieldSortType(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 3, 0); }
		static String convert(value v) { return _literals[(int)v]; }

		bool operator == (const String& str) const { return str == _value; }
		bool operator == (value val) const {return convert(val) == _value; }
		bool operator != (const String& str) const { return str != _value; }
		bool operator != (value val) const {return convert(val) != _value; }

		const String& operator = (const String& str) { _value = str; return str; }
		const value& operator = (const value& val) { _value = convert(val); return val; }

		operator const String& () const { return _value; }
		operator String& () { return _value; }
		operator value () const { return convert(_value); }
		String serialize() const { return _value; }
	};

	class CT_PivotField
	{
	public:
		CT_PivotField() : dataField(false), showDropDowns(true), hiddenLevel(false), compact(true), allDrilled(false), outline(true), subtotalTop(true), dragToRow(true), dragToCol(true), multipleItemSelectionAllowed(false), dragToPage(true), dragToData(true), dragOff(true), showAll(true), insertBlankRow(false), serverField(false), insertPageBreak(false), autoShow(false), topAutoShow(true), hideNewItems(false), measureFilter(false), includeNewItemsInFilter(false), itemPageCount(10U), sortType(ST_FieldSortType::manual_literal), nonAutoSortDefault(false), defaultSubtotal(true), sumSubtotal(false), countASubtotal(false), avgSubtotal(false), maxSubtotal(false), minSubtotal(false), productSubtotal(false), countSubtotal(false), stdDevSubtotal(false), stdDevPSubtotal(false), varSubtotal(false), varPSubtotal(false), showPropCell(false), showPropTip(false), showPropAsCaption(false), defaultAttributeDrillState(false) {}
		poptional< CT_Items > items;
		poptional< CT_AutoSortScope > autoSortScope;
		poptional< CT_ExtensionList > extLst;
		poptional< ST_Xstring > name;
		optional< ST_Axis > axis;
		Boolean dataField;
		poptional< ST_Xstring > subtotalCaption;
		Boolean showDropDowns;
		Boolean hiddenLevel;
		poptional< ST_Xstring > uniqueMemberProperty;
		Boolean compact;
		Boolean allDrilled;
		poptional< ST_NumFmtId > numFmtId;
		Boolean outline;
		Boolean subtotalTop;
		Boolean dragToRow;
		Boolean dragToCol;
		Boolean multipleItemSelectionAllowed;
		Boolean dragToPage;
		Boolean dragToData;
		Boolean dragOff;
		Boolean showAll;
		Boolean insertBlankRow;
		Boolean serverField;
		Boolean insertPageBreak;
		Boolean autoShow;
		Boolean topAutoShow;
		Boolean hideNewItems;
		Boolean measureFilter;
		Boolean includeNewItemsInFilter;
		UnsignedInt itemPageCount;
		ST_FieldSortType sortType;
		optional< Boolean > dataSourceSort;
		Boolean nonAutoSortDefault;
		optional< UnsignedInt > rankBy;
		Boolean defaultSubtotal;
		Boolean sumSubtotal;
		Boolean countASubtotal;
		Boolean avgSubtotal;
		Boolean maxSubtotal;
		Boolean minSubtotal;
		Boolean productSubtotal;
		Boolean countSubtotal;
		Boolean stdDevSubtotal;
		Boolean stdDevPSubtotal;
		Boolean varSubtotal;
		Boolean varPSubtotal;
		Boolean showPropCell;
		Boolean showPropTip;
		Boolean showPropAsCaption;
		Boolean defaultAttributeDrillState;
	};

	class CT_PivotFields
	{
	public:
		std::vector< CT_PivotField > pivotField;
		optional< UnsignedInt > count;
	};

	class CT_Field
	{
	public:
		Int x;
	};

	class CT_RowFields
	{
	public:
		CT_RowFields() : count(0U) {}
		std::vector< CT_Field > field;
		UnsignedInt count;
	};

	class CT_I
	{
	public:
		CT_I() : t(ST_ItemType::data_literal), r(0U), i(0U) {}
		std::vector< CT_X > x;
		ST_ItemType t;
		UnsignedInt r;
		UnsignedInt i;
	};

	class CT_rowItems
	{
	public:
		std::vector< CT_I > i;
		optional< UnsignedInt > count;
	};

	class CT_ColFields
	{
	public:
		CT_ColFields() : count(0U) {}
		std::vector< CT_Field > field;
		UnsignedInt count;
	};

	class CT_colItems
	{
	public:
		std::vector< CT_I > i;
		optional< UnsignedInt > count;
	};

	class CT_PageField
	{
	public:
		poptional< CT_ExtensionList > extLst;
		Int fld;
		optional< UnsignedInt > item;
		optional< Int > hier;
		poptional< ST_Xstring > name;
		poptional< ST_Xstring > cap;
	};

	class CT_PageFields
	{
	public:
		std::vector< CT_PageField > pageField;
		optional< UnsignedInt > count;
	};

	class ST_ShowDataAs
	{
		static String _literals[];
		String _value;
	public:
		enum value { difference, index, normal, percent, percentDiff, percentOfCol, percentOfRow, percentOfTotal, runTotal };

		static const String difference_literal;
		static const String index_literal;
		static const String normal_literal;
		static const String percent_literal;
		static const String percentDiff_literal;
		static const String percentOfCol_literal;
		static const String percentOfRow_literal;
		static const String percentOfTotal_literal;
		static const String runTotal_literal;

		ST_ShowDataAs() : _value(normal_literal) {}
		ST_ShowDataAs(value val) : _value(convert(val)) {}
		ST_ShowDataAs(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 9, 0); }
		static String convert(value v) { return _literals[(int)v]; }

		bool operator == (const String& str) const { return str == _value; }
		bool operator == (value val) const {return convert(val) == _value; }
		bool operator != (const String& str) const { return str != _value; }
		bool operator != (value val) const {return convert(val) != _value; }

		const String& operator = (const String& str) { _value = str; return str; }
		const value& operator = (const value& val) { _value = convert(val); return val; }

		operator const String& () const { return _value; }
		operator String& () { return _value; }
		operator value () const { return convert(_value); }
		String serialize() const { return _value; }
	};

	class CT_DataField
	{
	public:
		CT_DataField() : subtotal(ST_DataConsolidateFunction::sum_literal), showDataAs(ST_ShowDataAs::normal_literal), baseField(-1), baseItem(1048832U) {}
		poptional< CT_ExtensionList > extLst;
		poptional< ST_Xstring > name;
		UnsignedInt fld;
		ST_DataConsolidateFunction subtotal;
		ST_ShowDataAs showDataAs;
		Int baseField;
		UnsignedInt baseItem;
		poptional< ST_NumFmtId > numFmtId;
	};

	class CT_DataFields
	{
	public:
		std::vector< CT_DataField > dataField;
		optional< UnsignedInt > count;
	};

	class ST_FormatAction
	{
		static String _literals[];
		String _value;
	public:
		enum value { blank, drill, formatting, formula };

		static const String blank_literal;
		static const String drill_literal;
		static const String formatting_literal;
		static const String formula_literal;

		ST_FormatAction() : _value(blank_literal) {}
		ST_FormatAction(value val) : _value(convert(val)) {}
		ST_FormatAction(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 4, 0); }
		static String convert(value v) { return _literals[(int)v]; }

		bool operator == (const String& str) const { return str == _value; }
		bool operator == (value val) const {return convert(val) == _value; }
		bool operator != (const String& str) const { return str != _value; }
		bool operator != (value val) const {return convert(val) != _value; }

		const String& operator = (const String& str) { _value = str; return str; }
		const value& operator = (const value& val) { _value = convert(val); return val; }

		operator const String& () const { return _value; }
		operator String& () { return _value; }
		operator value () const { return convert(_value); }
		String serialize() const { return _value; }
	};

	class CT_Format
	{
	public:
		CT_Format() : action(ST_FormatAction::formatting_literal) {}
		CT_PivotArea pivotArea;
		poptional< CT_ExtensionList > extLst;
		ST_FormatAction action;
		poptional< ST_DxfId > dxfId;
	};

	class CT_Formats
	{
	public:
		CT_Formats() : count(0U) {}
		std::vector< CT_Format > format;
		UnsignedInt count;
	};

	class CT_PivotAreas
	{
	public:
		std::vector< CT_PivotArea > pivotArea;
		optional< UnsignedInt > count;
	};

	class ST_Scope
	{
		static String _literals[];
		String _value;
	public:
		enum value { data, field, selection };

		static const String data_literal;
		static const String field_literal;
		static const String selection_literal;

		ST_Scope() : _value(selection_literal) {}
		ST_Scope(value val) : _value(convert(val)) {}
		ST_Scope(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 3, 0); }
		static String convert(value v) { return _literals[(int)v]; }

		bool operator == (const String& str) const { return str == _value; }
		bool operator == (value val) const {return convert(val) == _value; }
		bool operator != (const String& str) const { return str != _value; }
		bool operator != (value val) const {return convert(val) != _value; }

		const String& operator = (const String& str) { _value = str; return str; }
		const value& operator = (const value& val) { _value = convert(val); return val; }

		operator const String& () const { return _value; }
		operator String& () { return _value; }
		operator value () const { return convert(_value); }
		String serialize() const { return _value; }
	};

	class ST_Type
	{
		static String _literals[];
		String _value;
	public:
		enum value { all, column, none, row };

		static const String all_literal;
		static const String column_literal;
		static const String none_literal;
		static const String row_literal;

		ST_Type() : _value(none_literal) {}
		ST_Type(value val) : _value(convert(val)) {}
		ST_Type(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 4, 0); }
		static String convert(value v) { return _literals[(int)v]; }

		bool operator == (const String& str) const { return str == _value; }
		bool operator == (value val) const {return convert(val) == _value; }
		bool operator != (const String& str) const { return str != _value; }
		bool operator != (value val) const {return convert(val) != _value; }

		const String& operator = (const String& str) { _value = str; return str; }
		const value& operator = (const value& val) { _value = convert(val); return val; }

		operator const String& () const { return _value; }
		operator String& () { return _value; }
		operator value () const { return convert(_value); }
		String serialize() const { return _value; }
	};

	class CT_ConditionalFormat
	{
	public:
		CT_ConditionalFormat() : scope(ST_Scope::selection_literal), type(ST_Type::none_literal) {}
		CT_PivotAreas pivotAreas;
		poptional< CT_ExtensionList > extLst;
		ST_Scope scope;
		ST_Type type;
		UnsignedInt priority;
	};

	class CT_ConditionalFormats
	{
	public:
		CT_ConditionalFormats() : count(0U) {}
		std::vector< CT_ConditionalFormat > conditionalFormat;
		UnsignedInt count;
	};

	class CT_ChartFormat
	{
	public:
		CT_ChartFormat() : series(false) {}
		CT_PivotArea pivotArea;
		UnsignedInt chart;
		UnsignedInt format;
		Boolean series;
	};

	class CT_ChartFormats
	{
	public:
		CT_ChartFormats() : count(0U) {}
		std::vector< CT_ChartFormat > chartFormat;
		UnsignedInt count;
	};

	class CT_MemberProperty
	{
	public:
		CT_MemberProperty() : showCell(false), showTip(false), showAsCaption(false) {}
		poptional< ST_Xstring > name;
		Boolean showCell;
		Boolean showTip;
		Boolean showAsCaption;
		optional< UnsignedInt > nameLen;
		optional< UnsignedInt > pPos;
		optional< UnsignedInt > pLen;
		optional< UnsignedInt > level;
		UnsignedInt field;
	};

	class CT_MemberProperties
	{
	public:
		std::vector< CT_MemberProperty > mp;
		optional< UnsignedInt > count;
	};

	class CT_Member
	{
	public:
		ST_Xstring name;
	};

	class CT_Members
	{
	public:
		std::vector< CT_Member > member;
		optional< UnsignedInt > count;
		optional< UnsignedInt > level;
	};

	class CT_PivotHierarchy
	{
	public:
		CT_PivotHierarchy() : outline(false), multipleItemSelectionAllowed(false), subtotalTop(false), showInFieldList(true), dragToRow(true), dragToCol(true), dragToPage(true), dragToData(false), dragOff(true), includeNewItemsInFilter(false) {}
		poptional< CT_MemberProperties > mps;
		std::vector< CT_Members > members;
		poptional< CT_ExtensionList > extLst;
		Boolean outline;
		Boolean multipleItemSelectionAllowed;
		Boolean subtotalTop;
		Boolean showInFieldList;
		Boolean dragToRow;
		Boolean dragToCol;
		Boolean dragToPage;
		Boolean dragToData;
		Boolean dragOff;
		Boolean includeNewItemsInFilter;
		poptional< ST_Xstring > caption;
	};

	class CT_PivotHierarchies
	{
	public:
		std::vector< CT_PivotHierarchy > pivotHierarchy;
		optional< UnsignedInt > count;
	};

	class CT_PivotTableStyle
	{
	public:
		optional< String > name;
		optional< Boolean > showRowHeaders;
		optional< Boolean > showColHeaders;
		optional< Boolean > showRowStripes;
		optional< Boolean > showColStripes;
		optional< Boolean > showLastColumn;
	};

	class ST_PivotFilterType
	{
		static String _literals[];
		String _value;
	public:
		enum value { captionBeginsWith, captionBetween, captionContains, captionEndsWith, captionEqual, captionGreaterThan, captionGreaterThanOrEqual, captionLessThan, captionLessThanOrEqual, captionNotBeginsWith, captionNotBetween, captionNotContains, captionNotEndsWith, captionNotEqual, count, dateBetween, dateEqual, dateNewerThan, dateNewerThanOrEqual, dateNotBetween, dateNotEqual, dateOlderThan, dateOlderThanOrEqual, lastMonth, lastQuarter, lastWeek, lastYear, M1, M10, M11, M12, M2, M3, M4, M5, M6, M7, M8, M9, nextMonth, nextQuarter, nextWeek, nextYear, percent, Q1, Q2, Q3, Q4, sum, thisMonth, thisQuarter, thisWeek, thisYear, today, tomorrow, unknown, valueBetween, valueEqual, valueGreaterThan, valueGreaterThanOrEqual, valueLessThan, valueLessThanOrEqual, valueNotBetween, valueNotEqual, yearToDate, yesterday };

		static const String captionBeginsWith_literal;
		static const String captionBetween_literal;
		static const String captionContains_literal;
		static const String captionEndsWith_literal;
		static const String captionEqual_literal;
		static const String captionGreaterThan_literal;
		static const String captionGreaterThanOrEqual_literal;
		static const String captionLessThan_literal;
		static const String captionLessThanOrEqual_literal;
		static const String captionNotBeginsWith_literal;
		static const String captionNotBetween_literal;
		static const String captionNotContains_literal;
		static const String captionNotEndsWith_literal;
		static const String captionNotEqual_literal;
		static const String count_literal;
		static const String dateBetween_literal;
		static const String dateEqual_literal;
		static const String dateNewerThan_literal;
		static const String dateNewerThanOrEqual_literal;
		static const String dateNotBetween_literal;
		static const String dateNotEqual_literal;
		static const String dateOlderThan_literal;
		static const String dateOlderThanOrEqual_literal;
		static const String lastMonth_literal;
		static const String lastQuarter_literal;
		static const String lastWeek_literal;
		static const String lastYear_literal;
		static const String M1_literal;
		static const String M10_literal;
		static const String M11_literal;
		static const String M12_literal;
		static const String M2_literal;
		static const String M3_literal;
		static const String M4_literal;
		static const String M5_literal;
		static const String M6_literal;
		static const String M7_literal;
		static const String M8_literal;
		static const String M9_literal;
		static const String nextMonth_literal;
		static const String nextQuarter_literal;
		static const String nextWeek_literal;
		static const String nextYear_literal;
		static const String percent_literal;
		static const String Q1_literal;
		static const String Q2_literal;
		static const String Q3_literal;
		static const String Q4_literal;
		static const String sum_literal;
		static const String thisMonth_literal;
		static const String thisQuarter_literal;
		static const String thisWeek_literal;
		static const String thisYear_literal;
		static const String today_literal;
		static const String tomorrow_literal;
		static const String unknown_literal;
		static const String valueBetween_literal;
		static const String valueEqual_literal;
		static const String valueGreaterThan_literal;
		static const String valueGreaterThanOrEqual_literal;
		static const String valueLessThan_literal;
		static const String valueLessThanOrEqual_literal;
		static const String valueNotBetween_literal;
		static const String valueNotEqual_literal;
		static const String yearToDate_literal;
		static const String yesterday_literal;

		ST_PivotFilterType() : _value(unknown_literal) {}
		ST_PivotFilterType(value val) : _value(convert(val)) {}
		ST_PivotFilterType(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 66, 0); }
		static String convert(value v) { return _literals[(int)v]; }

		bool operator == (const String& str) const { return str == _value; }
		bool operator == (value val) const {return convert(val) == _value; }
		bool operator != (const String& str) const { return str != _value; }
		bool operator != (value val) const {return convert(val) != _value; }

		const String& operator = (const String& str) { _value = str; return str; }
		const value& operator = (const value& val) { _value = convert(val); return val; }

		operator const String& () const { return _value; }
		operator String& () { return _value; }
		operator value () const { return convert(_value); }
		String serialize() const { return _value; }
	};

	class CT_PivotFilter
	{
	public:
		CT_PivotFilter() : evalOrder(0) {}
		CT_AutoFilter autoFilter;
		poptional< CT_ExtensionList > extLst;
		UnsignedInt fld;
		optional< UnsignedInt > mpFld;
		ST_PivotFilterType type;
		Int evalOrder;
		UnsignedInt id;
		optional< UnsignedInt > iMeasureHier;
		optional< UnsignedInt > iMeasureFld;
		poptional< ST_Xstring > name;
		poptional< ST_Xstring > description;
		poptional< ST_Xstring > stringValue1;
		poptional< ST_Xstring > stringValue2;
	};

	class CT_PivotFilters
	{
	public:
		CT_PivotFilters() : count(0U) {}
		std::vector< CT_PivotFilter > filter;
		UnsignedInt count;
	};

	class CT_HierarchyUsage
	{
	public:
		Int hierarchyUsage;
	};

	class CT_RowHierarchiesUsage
	{
	public:
		std::vector< CT_HierarchyUsage > rowHierarchyUsage;
		optional< UnsignedInt > count;
	};

	class CT_ColHierarchiesUsage
	{
	public:
		std::vector< CT_HierarchyUsage > colHierarchyUsage;
		optional< UnsignedInt > count;
	};

	class CT_pivotTableDefinition
	{
	public:
		CT_pivotTableDefinition() : dataOnRows(false), showError(false), showMissing(true), updatedVersion(0), minRefreshableVersion(0), asteriskTotals(false), showItems(true), editData(false), disableFieldList(false), showCalcMbrs(true), visualTotals(true), showMultipleLabel(true), showDataDropDown(true), showDrill(true), printDrill(false), showMemberPropertyTips(true), showDataTips(true), enableWizard(true), enableDrill(true), enableFieldProperties(true), preserveFormatting(true), useAutoFormatting(false), pageWrap(0U), pageOverThenDown(false), subtotalHiddenItems(false), rowGrandTotals(true), colGrandTotals(true), fieldPrintTitles(false), itemPrintTitles(false), mergeItem(false), showDropZones(true), createdVersion(0), indent(1U), showEmptyRow(false), showEmptyCol(false), showHeaders(true), compact(true), outline(false), outlineData(false), compactData(true), published(false), gridDropZones(false), immersive(true), multipleFieldFilters(true), chartFormat(0U), fieldListSortAscending(false), mdxSubqueries(false), customListSort(true) {}
		CT_Location location;
		poptional< CT_PivotFields > pivotFields;
		poptional< CT_RowFields > rowFields;
		poptional< CT_rowItems > rowItems;
		poptional< CT_ColFields > colFields;
		poptional< CT_colItems > colItems;
		poptional< CT_PageFields > pageFields;
		poptional< CT_DataFields > dataFields;
		poptional< CT_Formats > formats;
		poptional< CT_ConditionalFormats > conditionalFormats;
		poptional< CT_ChartFormats > chartFormats;
		poptional< CT_PivotHierarchies > pivotHierarchies;
		poptional< CT_PivotTableStyle > pivotTableStyleInfo;
		poptional< CT_PivotFilters > filters;
		poptional< CT_RowHierarchiesUsage > rowHierarchiesUsage;
		poptional< CT_ColHierarchiesUsage > colHierarchiesUsage;
		poptional< CT_ExtensionList > extLst;
		ST_Xstring name;
		UnsignedInt cacheId;
		Boolean dataOnRows;
		optional< UnsignedInt > dataPosition;
		optional< UnsignedInt > autoFormatId;
		optional< Boolean > applyNumberFormats;
		optional< Boolean > applyBorderFormats;
		optional< Boolean > applyFontFormats;
		optional< Boolean > applyPatternFormats;
		optional< Boolean > applyAlignmentFormats;
		optional< Boolean > applyWidthHeightFormats;
		ST_Xstring dataCaption;
		poptional< ST_Xstring > grandTotalCaption;
		poptional< ST_Xstring > errorCaption;
		Boolean showError;
		poptional< ST_Xstring > missingCaption;
		Boolean showMissing;
		poptional< ST_Xstring > pageStyle;
		poptional< ST_Xstring > pivotTableStyle;
		poptional< ST_Xstring > vacatedStyle;
		poptional< ST_Xstring > tag;
		UnsignedByte updatedVersion;
		UnsignedByte minRefreshableVersion;
		Boolean asteriskTotals;
		Boolean showItems;
		Boolean editData;
		Boolean disableFieldList;
		Boolean showCalcMbrs;
		Boolean visualTotals;
		Boolean showMultipleLabel;
		Boolean showDataDropDown;
		Boolean showDrill;
		Boolean printDrill;
		Boolean showMemberPropertyTips;
		Boolean showDataTips;
		Boolean enableWizard;
		Boolean enableDrill;
		Boolean enableFieldProperties;
		Boolean preserveFormatting;
		Boolean useAutoFormatting;
		UnsignedInt pageWrap;
		Boolean pageOverThenDown;
		Boolean subtotalHiddenItems;
		Boolean rowGrandTotals;
		Boolean colGrandTotals;
		Boolean fieldPrintTitles;
		Boolean itemPrintTitles;
		Boolean mergeItem;
		Boolean showDropZones;
		UnsignedByte createdVersion;
		UnsignedInt indent;
		Boolean showEmptyRow;
		Boolean showEmptyCol;
		Boolean showHeaders;
		Boolean compact;
		Boolean outline;
		Boolean outlineData;
		Boolean compactData;
		Boolean published;
		Boolean gridDropZones;
		Boolean immersive;
		Boolean multipleFieldFilters;
		UnsignedInt chartFormat;
		poptional< ST_Xstring > rowHeaderCaption;
		poptional< ST_Xstring > colHeaderCaption;
		Boolean fieldListSortAscending;
		Boolean mdxSubqueries;
		Boolean customListSort;
	};

	class sml_pivotTable
	{
	public:
		poptional< CT_PivotCacheDefinition > pivotCacheDefinition;
		poptional< CT_PivotCacheRecords > pivotCacheRecords;
		poptional< CT_pivotTableDefinition > pivotTableDefinition;
	};

}
#endif

