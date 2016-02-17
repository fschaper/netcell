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

#ifndef SML_PIVOTTABLESHARED_HPP
#define SML_PIVOTTABLESHARED_HPP


#include "sml-baseTypes.hpp"

namespace spreadsheetml
{
	using namespace ::xio;
	using namespace ::xio::xml::schema;

	class CT_Index;
	class CT_PivotAreaReference;
	class CT_PivotAreaReferences;
	class CT_PivotArea;

	class CT_Index
	{
	public:
		UnsignedInt v;
	};

	class CT_PivotAreaReference
	{
	public:
		CT_PivotAreaReference() : selected(true), byPosition(false), relative(false), defaultSubtotal(false), sumSubtotal(false), countASubtotal(false), avgSubtotal(false), maxSubtotal(false), minSubtotal(false), productSubtotal(false), countSubtotal(false), stdDevSubtotal(false), stdDevPSubtotal(false), varSubtotal(false), varPSubtotal(false) {}
		std::vector< CT_Index > x;
		poptional< CT_ExtensionList > extLst;
		optional< UnsignedInt > field;
		optional< UnsignedInt > count;
		Boolean selected;
		Boolean byPosition;
		Boolean relative;
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
	};

	class CT_PivotAreaReferences
	{
	public:
		std::vector< CT_PivotAreaReference > reference;
		optional< UnsignedInt > count;
	};

	class ST_PivotAreaType
	{
		static String _literals[];
		String _value;
	public:
		enum value { all, button, data, none, normal, origin, topRight };

		static const String all_literal;
		static const String button_literal;
		static const String data_literal;
		static const String none_literal;
		static const String normal_literal;
		static const String origin_literal;
		static const String topRight_literal;

		ST_PivotAreaType() : _value(none_literal) {}
		ST_PivotAreaType(value val) : _value(convert(val)) {}
		ST_PivotAreaType(const String& str) : _value(str) {}

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

	class ST_Axis
	{
		static String _literals[];
		String _value;
	public:
		enum value { axisCol, axisPage, axisRow, axisValues };

		static const String axisCol_literal;
		static const String axisPage_literal;
		static const String axisRow_literal;
		static const String axisValues_literal;

		ST_Axis() : _value(axisRow_literal) {}
		ST_Axis(value val) : _value(convert(val)) {}
		ST_Axis(const String& str) : _value(str) {}

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

	class CT_PivotArea
	{
	public:
		CT_PivotArea() : type(ST_PivotAreaType::normal_literal), dataOnly(true), labelOnly(false), grandRow(false), grandCol(false), cacheIndex(false), outline(true), collapsedLevelsAreSubtotals(false) {}
		poptional< CT_PivotAreaReferences > references;
		poptional< CT_ExtensionList > extLst;
		optional< Int > field;
		ST_PivotAreaType type;
		Boolean dataOnly;
		Boolean labelOnly;
		Boolean grandRow;
		Boolean grandCol;
		Boolean cacheIndex;
		Boolean outline;
		poptional< ST_Ref > offset;
		Boolean collapsedLevelsAreSubtotals;
		optional< ST_Axis > axis;
		optional< UnsignedInt > fieldPosition;
	};

}
#endif

