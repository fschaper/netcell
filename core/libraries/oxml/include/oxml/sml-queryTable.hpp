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

#ifndef SML_QUERYTABLE_HPP
#define SML_QUERYTABLE_HPP


#include "sml-baseTypes.hpp"
#include "sml-autoFilter.hpp"

namespace spreadsheetml
{
	using namespace ::xio;
	using namespace ::xio::xml::schema;

	class CT_QueryTableField;
	class CT_QueryTableFields;
	class CT_DeletedField;
	class CT_QueryTableDeletedFields;
	class CT_QueryTableRefresh;
	class CT_QueryTable;
	class sml_queryTable;

	class CT_QueryTableField
	{
	public:
		CT_QueryTableField() : dataBound(true), rowNumbers(false), fillFormulas(false), clipped(false), tableColumnId(0U) {}
		poptional< CT_ExtensionList > extLst;
		UnsignedInt id;
		poptional< ST_Xstring > name;
		Boolean dataBound;
		Boolean rowNumbers;
		Boolean fillFormulas;
		Boolean clipped;
		UnsignedInt tableColumnId;
	};

	class CT_QueryTableFields
	{
	public:
		CT_QueryTableFields() : count(0U) {}
		std::vector< CT_QueryTableField > queryTableField;
		UnsignedInt count;
	};

	class CT_DeletedField
	{
	public:
		ST_Xstring name;
	};

	class CT_QueryTableDeletedFields
	{
	public:
		std::vector< CT_DeletedField > deletedField;
		optional< UnsignedInt > count;
	};

	class CT_QueryTableRefresh
	{
	public:
		CT_QueryTableRefresh() : preserveSortFilterLayout(true), fieldIdWrapped(false), headersInLastRefresh(true), minimumVersion(0), nextId(1U), unboundColumnsLeft(0U), unboundColumnsRight(0U) {}
		CT_QueryTableFields queryTableFields;
		poptional< CT_QueryTableDeletedFields > queryTableDeletedFields;
		poptional< CT_SortState > sortState;
		poptional< CT_ExtensionList > extLst;
		Boolean preserveSortFilterLayout;
		Boolean fieldIdWrapped;
		Boolean headersInLastRefresh;
		UnsignedByte minimumVersion;
		UnsignedInt nextId;
		UnsignedInt unboundColumnsLeft;
		UnsignedInt unboundColumnsRight;
	};

	class ST_GrowShrinkType
	{
		static String _literals[];
		String _value;
	public:
		enum value { insertClear, insertDelete, overwriteClear };

		static const String insertClear_literal;
		static const String insertDelete_literal;
		static const String overwriteClear_literal;

		ST_GrowShrinkType() : _value(insertDelete_literal) {}
		ST_GrowShrinkType(value val) : _value(convert(val)) {}
		ST_GrowShrinkType(const String& str) : _value(str) {}

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

	class CT_QueryTable
	{
	public:
		CT_QueryTable() : headers(true), rowNumbers(false), disableRefresh(false), backgroundRefresh(true), firstBackgroundRefresh(false), refreshOnLoad(false), growShrinkType(ST_GrowShrinkType::insertDelete_literal), fillFormulas(false), removeDataOnSave(false), disableEdit(false), preserveFormatting(true), adjustColumnWidth(true), intermediate(false) {}
		poptional< CT_QueryTableRefresh > queryTableRefresh;
		poptional< CT_ExtensionList > extLst;
		ST_Xstring name;
		Boolean headers;
		Boolean rowNumbers;
		Boolean disableRefresh;
		Boolean backgroundRefresh;
		Boolean firstBackgroundRefresh;
		Boolean refreshOnLoad;
		ST_GrowShrinkType growShrinkType;
		Boolean fillFormulas;
		Boolean removeDataOnSave;
		Boolean disableEdit;
		Boolean preserveFormatting;
		Boolean adjustColumnWidth;
		Boolean intermediate;
		UnsignedInt connectionId;
		optional< UnsignedInt > autoFormatId;
		optional< Boolean > applyNumberFormats;
		optional< Boolean > applyBorderFormats;
		optional< Boolean > applyFontFormats;
		optional< Boolean > applyPatternFormats;
		optional< Boolean > applyAlignmentFormats;
		optional< Boolean > applyWidthHeightFormats;
	};

	class sml_queryTable
	{
	public:
		poptional< CT_QueryTable > queryTable;
	};

}
#endif

