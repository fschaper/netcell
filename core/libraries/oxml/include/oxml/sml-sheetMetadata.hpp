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

#ifndef SML_SHEETMETADATA_HPP
#define SML_SHEETMETADATA_HPP


#include "sml-baseTypes.hpp"

namespace spreadsheetml
{
	using namespace ::xio;
	using namespace ::xio::xml::schema;

	class CT_MetadataType;
	class CT_MetadataTypes;
	class CT_MetadataStrings;
	class CT_MetadataStringIndex;
	class CT_MdxTuple;
	class CT_MdxSet;
	class CT_MdxMemeberProp;
	class CT_MdxKPI;
	class CT_Mdx;
	class CT_MdxMetadata;
	class CT_FutureMetadataBlock;
	class CT_FutureMetadata;
	class CT_MetadataRecord;
	class CT_MetadataBlock;
	class CT_MetadataBlocks;
	class CT_Metadata;
	class sml_sheetMetadata;

	class CT_MetadataType
	{
	public:
		CT_MetadataType() : ghostRow(false), ghostCol(false), edit(false), _delete_(false), copy(false), pasteAll(false), pasteFormulas(false), pasteValues(false), pasteFormats(false), pasteComments(false), pasteDataValidation(false), pasteBorders(false), pasteColWidths(false), pasteNumberFormats(false), merge(false), splitFirst(false), splitAll(false), rowColShift(false), clearAll(false), clearFormats(false), clearContents(false), clearComments(false), assign(false), coerce(false), adjust(false), cellMeta(false) {}
		ST_Xstring name;
		UnsignedInt minSupportedVersion;
		Boolean ghostRow;
		Boolean ghostCol;
		Boolean edit;
		Boolean _delete_;
		Boolean copy;
		Boolean pasteAll;
		Boolean pasteFormulas;
		Boolean pasteValues;
		Boolean pasteFormats;
		Boolean pasteComments;
		Boolean pasteDataValidation;
		Boolean pasteBorders;
		Boolean pasteColWidths;
		Boolean pasteNumberFormats;
		Boolean merge;
		Boolean splitFirst;
		Boolean splitAll;
		Boolean rowColShift;
		Boolean clearAll;
		Boolean clearFormats;
		Boolean clearContents;
		Boolean clearComments;
		Boolean assign;
		Boolean coerce;
		Boolean adjust;
		Boolean cellMeta;
	};

	class CT_MetadataTypes
	{
	public:
		CT_MetadataTypes() : count(0U) {}
		std::vector< CT_MetadataType > metadataType;
		UnsignedInt count;
	};

	class CT_MetadataStrings
	{
	public:
		CT_MetadataStrings() : count(0U) {}
		std::vector< CT_XStringElement > s;
		UnsignedInt count;
	};

	class CT_MetadataStringIndex
	{
	public:
		CT_MetadataStringIndex() : s(false) {}
		UnsignedInt x;
		Boolean s;
	};

	class CT_MdxTuple
	{
	public:
		CT_MdxTuple() : c(0U), i(false), u(false), st(false), b(false) {}
		std::vector< CT_MetadataStringIndex > n;
		UnsignedInt c;
		poptional< ST_Xstring > ct;
		optional< UnsignedInt > si;
		optional< UnsignedInt > fi;
		poptional< ST_UnsignedIntHex > bc;
		poptional< ST_UnsignedIntHex > fc;
		Boolean i;
		Boolean u;
		Boolean st;
		Boolean b;
	};

	class ST_MdxSetOrder
	{
		static String _literals[];
		String _value;
	public:
		enum value { a, aa, ad, d, na, nd, u };

		static const String a_literal;
		static const String aa_literal;
		static const String ad_literal;
		static const String d_literal;
		static const String na_literal;
		static const String nd_literal;
		static const String u_literal;

		ST_MdxSetOrder() : _value(u_literal) {}
		ST_MdxSetOrder(value val) : _value(convert(val)) {}
		ST_MdxSetOrder(const String& str) : _value(str) {}

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

	class CT_MdxSet
	{
	public:
		CT_MdxSet() : c(0U), o(ST_MdxSetOrder::u_literal) {}
		std::vector< CT_MetadataStringIndex > n;
		UnsignedInt ns;
		UnsignedInt c;
		ST_MdxSetOrder o;
	};

	class CT_MdxMemeberProp
	{
	public:
		UnsignedInt n;
		UnsignedInt np;
	};

	class ST_MdxKPIProperty
	{
		static String _literals[];
		String _value;
	public:
		enum value { g, m, s, t, v, w };

		static const String g_literal;
		static const String m_literal;
		static const String s_literal;
		static const String t_literal;
		static const String v_literal;
		static const String w_literal;

		ST_MdxKPIProperty() : _value(v_literal) {}
		ST_MdxKPIProperty(value val) : _value(convert(val)) {}
		ST_MdxKPIProperty(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 6, 0); }
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

	class CT_MdxKPI
	{
	public:
		UnsignedInt n;
		UnsignedInt np;
		ST_MdxKPIProperty p;
	};

	class ST_MdxFunctionType
	{
		static String _literals[];
		String _value;
	public:
		enum value { c, k, m, p, r, s, v };

		static const String c_literal;
		static const String k_literal;
		static const String m_literal;
		static const String p_literal;
		static const String r_literal;
		static const String s_literal;
		static const String v_literal;

		ST_MdxFunctionType() : _value(m_literal) {}
		ST_MdxFunctionType(value val) : _value(convert(val)) {}
		ST_MdxFunctionType(const String& str) : _value(str) {}

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

	class CT_Mdx
	{
	public:
		poptional< CT_MdxTuple > t;
		poptional< CT_MdxSet > ms;
		poptional< CT_MdxMemeberProp > p;
		poptional< CT_MdxKPI > k;
		UnsignedInt n;
		ST_MdxFunctionType f;
	};

	class CT_MdxMetadata
	{
	public:
		CT_MdxMetadata() : count(0U) {}
		std::vector< CT_Mdx > mdx;
		UnsignedInt count;
	};

	class CT_FutureMetadataBlock
	{
	public:
		poptional< CT_ExtensionList > extLst;
	};

	class CT_FutureMetadata
	{
	public:
		CT_FutureMetadata() : count(0U) {}
		std::vector< CT_FutureMetadataBlock > bk;
		poptional< CT_ExtensionList > extLst;
		ST_Xstring name;
		UnsignedInt count;
	};

	class CT_MetadataRecord
	{
	public:
		UnsignedInt t;
		UnsignedInt v;
	};

	class CT_MetadataBlock
	{
	public:
		std::vector< CT_MetadataRecord > rc;
	};

	class CT_MetadataBlocks
	{
	public:
		CT_MetadataBlocks() : count(0U) {}
		std::vector< CT_MetadataBlock > bk;
		UnsignedInt count;
	};

	class CT_Metadata
	{
	public:
		poptional< CT_MetadataTypes > metadataTypes;
		poptional< CT_MetadataStrings > metadataStrings;
		poptional< CT_MdxMetadata > mdxMetadata;
		std::vector< CT_FutureMetadata > futureMetadata;
		poptional< CT_MetadataBlocks > cellMetadata;
		poptional< CT_MetadataBlocks > valueMetadata;
		poptional< CT_ExtensionList > extLst;
	};

	class sml_sheetMetadata
	{
	public:
		poptional< CT_Metadata > metadata;
	};

}
#endif

