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

#ifndef SML_SUPPLEMENTARYWORKBOOKS_HPP
#define SML_SUPPLEMENTARYWORKBOOKS_HPP


#include "sml-baseTypes.hpp"
#include "sml-sheet.hpp"
#include "shared-relationshipReference.hpp"

namespace spreadsheetml
{
	using namespace ::xio;
	using namespace ::xio::xml::schema;

	class CT_ExternalSheetName;
	class CT_ExternalSheetNames;
	class CT_ExternalDefinedName;
	class CT_ExternalDefinedNames;
	class CT_ExternalCell;
	class CT_ExternalRow;
	class CT_ExternalSheetData;
	class CT_ExternalSheetDataSet;
	class CT_ExternalBook;
	class CT_DdeValue;
	class CT_DdeValues;
	class CT_DdeItem;
	class CT_DdeItems;
	class CT_DdeLink;
	class CT_OleItem;
	class CT_OleItems;
	class CT_OleLink;
	class CT_ExternalLink;
	class sml_supplementaryWorkbooks;

	class CT_ExternalSheetName
	{
	public:
		poptional< ST_Xstring > val;
	};

	class CT_ExternalSheetNames
	{
	public:
		std::vector< CT_ExternalSheetName > sheetName;
	};

	class CT_ExternalDefinedName
	{
	public:
		ST_Xstring name;
		poptional< ST_Xstring > refersTo;
		optional< UnsignedInt > sheetId;
	};

	class CT_ExternalDefinedNames
	{
	public:
		std::vector< CT_ExternalDefinedName > definedName;
	};

	class CT_ExternalCell
	{
	public:
		CT_ExternalCell() : t(ST_CellType::n_literal), vm(0U) {}
		poptional< ST_Xstring > v;
		poptional< ST_CellRef > r;
		ST_CellType t;
		UnsignedInt vm;
	};

	class CT_ExternalRow
	{
	public:
		std::vector< CT_ExternalCell > cell;
		UnsignedInt r;
	};

	class CT_ExternalSheetData
	{
	public:
		CT_ExternalSheetData() : refreshError(false) {}
		std::vector< CT_ExternalRow > row;
		UnsignedInt sheetId;
		Boolean refreshError;
	};

	class CT_ExternalSheetDataSet
	{
	public:
		std::vector< CT_ExternalSheetData > sheetData;
	};

	class CT_ExternalBook
	{
	public:
		poptional< CT_ExternalSheetNames > sheetNames;
		poptional< CT_ExternalDefinedNames > definedNames;
		poptional< CT_ExternalSheetDataSet > sheetDataSet;
		::relationships::ST_RelationshipId id;
	};

	class ST_DdeValueType
	{
		static String _literals[];
		String _value;
	public:
		enum value { b, e, n, nil, str };

		static const String b_literal;
		static const String e_literal;
		static const String n_literal;
		static const String nil_literal;
		static const String str_literal;

		ST_DdeValueType() : _value(nil_literal) {}
		ST_DdeValueType(value val) : _value(convert(val)) {}
		ST_DdeValueType(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 5, 0); }
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

	class CT_DdeValue
	{
	public:
		CT_DdeValue() : t(ST_DdeValueType::n_literal) {}
		ST_Xstring val;
		ST_DdeValueType t;
	};

	class CT_DdeValues
	{
	public:
		CT_DdeValues() : rows(1U), cols(1U) {}
		std::vector< CT_DdeValue > value;
		UnsignedInt rows;
		UnsignedInt cols;
	};

	class CT_DdeItem
	{
	public:
		CT_DdeItem() : name("0"), ole(false), advise(false), preferPic(false) {}
		poptional< CT_DdeValues > values;
		ST_Xstring name;
		Boolean ole;
		Boolean advise;
		Boolean preferPic;
	};

	class CT_DdeItems
	{
	public:
		std::vector< CT_DdeItem > ddeItem;
	};

	class CT_DdeLink
	{
	public:
		poptional< CT_DdeItems > ddeItems;
		ST_Xstring ddeService;
		ST_Xstring ddeTopic;
	};

	class CT_OleItem
	{
	public:
		CT_OleItem() : icon(false), advise(false), preferPic(false) {}
		ST_Xstring name;
		Boolean icon;
		Boolean advise;
		Boolean preferPic;
	};

	class CT_OleItems
	{
	public:
		std::vector< CT_OleItem > oleItem;
	};

	class CT_OleLink
	{
	public:
		poptional< CT_OleItems > oleItems;
		::relationships::ST_RelationshipId id;
		ST_Xstring progId;
	};

	class CT_ExternalLink
	{
	public:
		poptional< CT_ExternalBook > externalBook;
		poptional< CT_DdeLink > ddeLink;
		poptional< CT_OleLink > oleLink;
		poptional< CT_ExtensionList > extLst;
	};

	class sml_supplementaryWorkbooks
	{
	public:
		poptional< CT_ExternalLink > externalLink;
	};

}
#endif

