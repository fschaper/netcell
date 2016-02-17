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

#ifndef SML_VOLATILEDEPENDENCIES_HPP
#define SML_VOLATILEDEPENDENCIES_HPP


#include "sml-baseTypes.hpp"

namespace spreadsheetml
{
	using namespace ::xio;
	using namespace ::xio::xml::schema;

	class CT_VolTopicRef;
	class CT_VolTopic;
	class CT_VolMain;
	class CT_VolType;
	class CT_VolTypes;
	class sml_volatileDependencies;

	class CT_VolTopicRef
	{
	public:
		ST_CellRef r;
		UnsignedInt s;
	};

	class ST_VolValueType
	{
		static String _literals[];
		String _value;
	public:
		enum value { b, e, n, s };

		static const String b_literal;
		static const String e_literal;
		static const String n_literal;
		static const String s_literal;

		ST_VolValueType() : _value(b_literal) {}
		ST_VolValueType(value val) : _value(convert(val)) {}
		ST_VolValueType(const String& str) : _value(str) {}

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

	class CT_VolTopic
	{
	public:
		CT_VolTopic() : t(ST_VolValueType::n_literal) {}
		ST_Xstring v;
		std::vector< ST_Xstring > stp;
		std::vector< CT_VolTopicRef > tr;
		ST_VolValueType t;
	};

	class CT_VolMain
	{
	public:
		std::vector< CT_VolTopic > tp;
		ST_Xstring first;
	};

	class ST_VolDepType
	{
		static String _literals[];
		String _value;
	public:
		enum value { olapFunctions, realTimeData };

		static const String olapFunctions_literal;
		static const String realTimeData_literal;

		ST_VolDepType() : _value(realTimeData_literal) {}
		ST_VolDepType(value val) : _value(convert(val)) {}
		ST_VolDepType(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 2, 0); }
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

	class CT_VolType
	{
	public:
		std::vector< CT_VolMain > main;
		ST_VolDepType type;
	};

	class CT_VolTypes
	{
	public:
		std::vector< CT_VolType > volType;
		poptional< CT_ExtensionList > extLst;
	};

	class sml_volatileDependencies
	{
	public:
		poptional< CT_VolTypes > volTypes;
	};

}
#endif

