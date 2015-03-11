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

#ifndef DML_SHAPELINEPROPERTIES_HPP
#define DML_SHAPELINEPROPERTIES_HPP


#include "dml-shapeEffects.hpp"
#include "dml-baseTypes.hpp"

namespace drawingml
{
	using namespace ::xio;
	using namespace ::xio::xml::schema;

	class CT_PresetLineDashProperties;
	class CT_DashStop;
	class CT_DashStopList;
	class CT_LineJoinRound;
	class CT_LineJoinBevel;
	class CT_LineJoinMiterProperties;
	class CT_LineEndProperties;
	class ST_LineWidth;
	class CT_LineProperties;

	class ST_PresetLineDashVal
	{
		static String _literals[];
		String _value;
	public:
		enum value { dash, dashDot, dot, lgDash, lgDashDot, lgDashDotDot, solid, sysDash, sysDashDot, sysDashDotDot, sysDot };

		static const String dash_literal;
		static const String dashDot_literal;
		static const String dot_literal;
		static const String lgDash_literal;
		static const String lgDashDot_literal;
		static const String lgDashDotDot_literal;
		static const String solid_literal;
		static const String sysDash_literal;
		static const String sysDashDot_literal;
		static const String sysDashDotDot_literal;
		static const String sysDot_literal;

		ST_PresetLineDashVal() : _value(solid_literal) {}
		ST_PresetLineDashVal(value val) : _value(convert(val)) {}
		ST_PresetLineDashVal(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 11, 0); }
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

	class CT_PresetLineDashProperties
	{
	public:
		optional< ST_PresetLineDashVal > val;
	};

	class CT_DashStop
	{
	public:
		ST_PositivePercentage d;
		ST_PositivePercentage sp;
	};

	class CT_DashStopList
	{
	public:
		std::vector< CT_DashStop > ds;
	};

	class CT_LineJoinRound
	{
	public:
	};

	class CT_LineJoinBevel
	{
	public:
	};

	class CT_LineJoinMiterProperties
	{
	public:
		poptional< ST_PositivePercentage > lim;
	};

	class ST_LineEndType
	{
		static String _literals[];
		String _value;
	public:
		enum value { arrow, diamond, none, oval, stealth, triangle };

		static const String arrow_literal;
		static const String diamond_literal;
		static const String none_literal;
		static const String oval_literal;
		static const String stealth_literal;
		static const String triangle_literal;

		ST_LineEndType() : _value(none_literal) {}
		ST_LineEndType(value val) : _value(convert(val)) {}
		ST_LineEndType(const String& str) : _value(str) {}

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

	class ST_LineEndWidth
	{
		static String _literals[];
		String _value;
	public:
		enum value { lg, med, sm };

		static const String lg_literal;
		static const String med_literal;
		static const String sm_literal;

		ST_LineEndWidth() : _value(sm_literal) {}
		ST_LineEndWidth(value val) : _value(convert(val)) {}
		ST_LineEndWidth(const String& str) : _value(str) {}

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

	class ST_LineEndLength
	{
		static String _literals[];
		String _value;
	public:
		enum value { lg, med, sm };

		static const String lg_literal;
		static const String med_literal;
		static const String sm_literal;

		ST_LineEndLength() : _value(sm_literal) {}
		ST_LineEndLength(value val) : _value(convert(val)) {}
		ST_LineEndLength(const String& str) : _value(str) {}

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

	class CT_LineEndProperties
	{
	public:
		optional< ST_LineEndType > type;
		optional< ST_LineEndWidth > w;
		optional< ST_LineEndLength > len;
	};

	class ST_LineWidth : public ST_Coordinate32
	{
	public:
		ST_LineWidth() {}
		ST_LineWidth(const Int& v) : ST_Coordinate32(v) {}
		ST_LineWidth(const String& v) { read(v); }
	};

	class ST_LineCap
	{
		static String _literals[];
		String _value;
	public:
		enum value { flat, rnd, sq };

		static const String flat_literal;
		static const String rnd_literal;
		static const String sq_literal;

		ST_LineCap() : _value(rnd_literal) {}
		ST_LineCap(value val) : _value(convert(val)) {}
		ST_LineCap(const String& str) : _value(str) {}

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

	class ST_CompoundLine
	{
		static String _literals[];
		String _value;
	public:
		enum value { dbl, sng, thickThin, thinThick, tri };

		static const String dbl_literal;
		static const String sng_literal;
		static const String thickThin_literal;
		static const String thinThick_literal;
		static const String tri_literal;

		ST_CompoundLine() : _value(sng_literal) {}
		ST_CompoundLine(value val) : _value(convert(val)) {}
		ST_CompoundLine(const String& str) : _value(str) {}

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

	class ST_PenAlignment
	{
		static String _literals[];
		String _value;
	public:
		enum value { ctr, in };

		static const String ctr_literal;
		static const String in_literal;

		ST_PenAlignment() : _value(ctr_literal) {}
		ST_PenAlignment(value val) : _value(convert(val)) {}
		ST_PenAlignment(const String& str) : _value(str) {}

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

	class CT_LineProperties
	{
	public:
		poptional< CT_NoFillProperties > noFill;
		poptional< CT_SolidColorFillProperties > solidFill;
		poptional< CT_GradientFillProperties > gradFill;
		poptional< CT_PatternFillProperties > pattFill;
		poptional< CT_PresetLineDashProperties > prstDash;
		poptional< CT_DashStopList > custDash;
		poptional< CT_LineJoinRound > round;
		poptional< CT_LineJoinBevel > bevel;
		poptional< CT_LineJoinMiterProperties > miter;
		poptional< CT_LineEndProperties > headEnd;
		poptional< CT_LineEndProperties > tailEnd;
		poptional< CT_OfficeArtExtensionList > extLst;
		poptional< ST_LineWidth > w;
		optional< ST_LineCap > cap;
		optional< ST_CompoundLine > cmpd;
		optional< ST_PenAlignment > algn;
	};

}
#endif

