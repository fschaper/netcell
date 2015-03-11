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

#ifndef SML_BASETYPES_HPP
#define SML_BASETYPES_HPP


#include <xio/optional.hpp>
#include <xio/xml/schema/types.hpp>
#include <xio/util/binary_search.hpp>

namespace spreadsheetml
{
	using namespace ::xio;
	using namespace ::xio::xml::schema;

	class ST_CellRef;
	class CT_Extension;
	class CT_ExtensionList;
	class ST_Xstring;
	class ST_UnsignedIntHex;
	class ST_Ref;
	class ST_Guid;
	class CT_XStringElement;
	class ST_RefA;
	class ST_Formula;
	class ST_Sqref;
	class ST_UnsignedShortHex;

	class ST_CellRef : public simple_type<String>
	{
	public:
		ST_CellRef() {}
		ST_CellRef(const String& v) : simple_type<String>(v) {}
	};

	class CT_Extension
	{
	public:
		optional< Token > uri;
	};

	class CT_ExtensionList
	{
	public:
		std::vector< CT_Extension > ext;
	};

	class ST_Xstring : public simple_type<String>
	{
	public:
		ST_Xstring() {}
		ST_Xstring(const String& v) : simple_type<String>(v) {}
	};

	class ST_UnsignedIntHex : public simple_type<HexBinary>
	{
	public:
		ST_UnsignedIntHex() {}
		ST_UnsignedIntHex(const HexBinary& v) : simple_type<HexBinary>(v) {}
		ST_UnsignedIntHex(const String& v) { read(v); }
	};

	class ST_Ref : public simple_type<String>
	{
	public:
		ST_Ref() {}
		ST_Ref(const String& v) : simple_type<String>(v) {}
	};

	class ST_Guid : public simple_type<Token>
	{
	public:
		ST_Guid() {}
		ST_Guid(const Token& v) : simple_type<Token>(v) {}
	};

	class CT_XStringElement
	{
	public:
		ST_Xstring v;
	};

	class ST_RefA : public simple_type<String>
	{
	public:
		ST_RefA() {}
		ST_RefA(const String& v) : simple_type<String>(v) {}
	};

	class ST_Formula : public ST_Xstring
	{
	public:
		ST_Formula() {}
		ST_Formula(const String& v) : ST_Xstring(v) {}
	};

	class ST_Sqref : public list_type<ST_Ref >
	{
	public:
		ST_Sqref() {}
		ST_Sqref(const String& v) : list_type<ST_Ref >(v) {}
	};

	class ST_UnsignedShortHex : public simple_type<HexBinary>
	{
	public:
		ST_UnsignedShortHex() {}
		ST_UnsignedShortHex(const HexBinary& v) : simple_type<HexBinary>(v) {}
		ST_UnsignedShortHex(const String& v) { read(v); }
	};

}
#endif

