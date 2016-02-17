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

#ifndef SHARED_DOCUMENTPROPERTIESVARIANTTYPES_HPP
#define SHARED_DOCUMENTPROPERTIESVARIANTTYPES_HPP


#include <xio/optional.hpp>
#include <xio/xml/schema/types.hpp>
#include <xio/util/binary_search.hpp>

namespace docPropsVTypes
{
	using namespace ::xio;
	using namespace ::xio::xml::schema;

	class ST_Error;
	class ST_Cy;
	class CT_Array;
	class CT_Empty;
	class CT_Null;
	class ST_Clsid;
	class CT_Vstream;
	class ST_Format;
	class CT_Cf;
	class CT_Variant;
	class CT_Vector;
	class shared_documentPropertiesVariantTypes;

	class ST_Error : public simple_type<String>
	{
	public:
		ST_Error() {}
		ST_Error(const String& v) : simple_type<String>(v) {}
	};

	class ST_Cy : public simple_type<String>
	{
	public:
		ST_Cy() {}
		ST_Cy(const String& v) : simple_type<String>(v) {}
	};

	class ST_ArrayBaseType
	{
		static String _literals[];
		String _value;
	public:
		enum value { _bool_, bstr, cy, date, decimal, error, i1, i2, i4, _int_, r4, r8, ui1, ui2, ui4, uint, variant };

		static const String _bool__literal;
		static const String bstr_literal;
		static const String cy_literal;
		static const String date_literal;
		static const String decimal_literal;
		static const String error_literal;
		static const String i1_literal;
		static const String i2_literal;
		static const String i4_literal;
		static const String _int__literal;
		static const String r4_literal;
		static const String r8_literal;
		static const String ui1_literal;
		static const String ui2_literal;
		static const String ui4_literal;
		static const String uint_literal;
		static const String variant_literal;

		ST_ArrayBaseType() : _value(variant_literal) {}
		ST_ArrayBaseType(value val) : _value(convert(val)) {}
		ST_ArrayBaseType(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 17, 0); }
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

	class CT_Array
	{
	public:
		poptional< CT_Variant > variant;
		optional< Byte > i1;
		optional< Short > i2;
		optional< Int > i4;
		optional< Int > _int_;
		optional< UnsignedByte > ui1;
		optional< UnsignedShort > ui2;
		optional< UnsignedInt > ui4;
		optional< UnsignedInt > uint;
		optional< Float > r4;
		optional< Double > r8;
		optional< Decimal > decimal;
		optional< String > bstr;
		optional< DateTime > date;
		optional< Boolean > _bool_;
		poptional< ST_Error > error;
		poptional< ST_Cy > cy;
		Int lBounds;
		Int uBounds;
		ST_ArrayBaseType baseType;
	};

	class CT_Empty
	{
	public:
	};

	class CT_Null
	{
	public:
	};

	class ST_Clsid : public simple_type<String>
	{
	public:
		ST_Clsid() {}
		ST_Clsid(const String& v) : simple_type<String>(v) {}
	};

	class CT_Vstream : public simple_type<Base64Binary>
	{
	public:
		CT_Vstream() {}
		CT_Vstream(const Base64Binary& v) : simple_type<Base64Binary>(v) {}
		CT_Vstream(const String& v) { read(v); }
		poptional< ST_Clsid > version;
	};

	class ST_Format : public simple_type<String>
	{
	public:
		ST_Format() {}
		ST_Format(const String& v) : simple_type<String>(v) {}
	};

	class CT_Cf : public simple_type<Base64Binary>
	{
	public:
		CT_Cf() {}
		CT_Cf(const Base64Binary& v) : simple_type<Base64Binary>(v) {}
		CT_Cf(const String& v) { read(v); }
		poptional< ST_Format > format;
	};

	class CT_Variant
	{
	public:
		poptional< CT_Variant > variant;
		poptional< CT_Vector > vector;
		poptional< CT_Array > array;
		optional< Base64Binary > blob;
		optional< Base64Binary > oblob;
		poptional< CT_Empty > empty;
		poptional< CT_Null > null;
		optional< Byte > i1;
		optional< Short > i2;
		optional< Int > i4;
		optional< Long > i8;
		optional< Int > _int_;
		optional< UnsignedByte > ui1;
		optional< UnsignedShort > ui2;
		optional< UnsignedInt > ui4;
		optional< UnsignedLong > ui8;
		optional< UnsignedInt > uint;
		optional< Float > r4;
		optional< Double > r8;
		optional< Decimal > decimal;
		optional< String > lpstr;
		optional< String > lpwstr;
		optional< String > bstr;
		optional< DateTime > date;
		optional< DateTime > filetime;
		optional< Boolean > _bool_;
		poptional< ST_Cy > cy;
		poptional< ST_Error > error;
		optional< Base64Binary > stream;
		optional< Base64Binary > ostream;
		optional< Base64Binary > storage;
		optional< Base64Binary > ostorage;
		poptional< CT_Vstream > vstream;
		poptional< ST_Clsid > clsid;
		poptional< CT_Cf > cf;
	};

	class ST_VectorBaseType
	{
		static String _literals[];
		String _value;
	public:
		enum value { _bool_, bstr, cf, clsid, cy, date, error, filetime, i1, i2, i4, i8, lpstr, lpwstr, r4, r8, ui1, ui2, ui4, ui8, variant };

		static const String _bool__literal;
		static const String bstr_literal;
		static const String cf_literal;
		static const String clsid_literal;
		static const String cy_literal;
		static const String date_literal;
		static const String error_literal;
		static const String filetime_literal;
		static const String i1_literal;
		static const String i2_literal;
		static const String i4_literal;
		static const String i8_literal;
		static const String lpstr_literal;
		static const String lpwstr_literal;
		static const String r4_literal;
		static const String r8_literal;
		static const String ui1_literal;
		static const String ui2_literal;
		static const String ui4_literal;
		static const String ui8_literal;
		static const String variant_literal;

		ST_VectorBaseType() : _value(variant_literal) {}
		ST_VectorBaseType(value val) : _value(convert(val)) {}
		ST_VectorBaseType(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 21, 0); }
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

	class CT_Vector
	{
	public:
		poptional< CT_Variant > variant;
		optional< Byte > i1;
		optional< Short > i2;
		optional< Int > i4;
		optional< Long > i8;
		optional< UnsignedByte > ui1;
		optional< UnsignedShort > ui2;
		optional< UnsignedInt > ui4;
		optional< UnsignedLong > ui8;
		optional< Float > r4;
		optional< Double > r8;
		optional< String > lpstr;
		optional< String > lpwstr;
		optional< String > bstr;
		optional< DateTime > date;
		optional< DateTime > filetime;
		optional< Boolean > _bool_;
		poptional< ST_Cy > cy;
		poptional< ST_Error > error;
		poptional< ST_Clsid > clsid;
		poptional< CT_Cf > cf;
		ST_VectorBaseType baseType;
		UnsignedInt size;
	};

	class shared_documentPropertiesVariantTypes
	{
	public:
		poptional< CT_Variant > variant;
		poptional< CT_Vector > vector;
		poptional< CT_Array > array;
		optional< Base64Binary > blob;
		optional< Base64Binary > oblob;
		poptional< CT_Empty > empty;
		poptional< CT_Null > null;
		optional< Byte > i1;
		optional< Short > i2;
		optional< Int > i4;
		optional< Long > i8;
		optional< Int > _int_;
		optional< UnsignedByte > ui1;
		optional< UnsignedShort > ui2;
		optional< UnsignedInt > ui4;
		optional< UnsignedLong > ui8;
		optional< UnsignedInt > uint;
		optional< Float > r4;
		optional< Double > r8;
		optional< Decimal > decimal;
		optional< String > lpstr;
		optional< String > lpwstr;
		optional< String > bstr;
		optional< DateTime > date;
		optional< DateTime > filetime;
		optional< Boolean > _bool_;
		poptional< ST_Cy > cy;
		poptional< ST_Error > error;
		optional< Base64Binary > stream;
		optional< Base64Binary > ostream;
		optional< Base64Binary > storage;
		optional< Base64Binary > ostorage;
		poptional< CT_Vstream > vstream;
		poptional< ST_Clsid > clsid;
		poptional< CT_Cf > cf;
	};

}
#endif

