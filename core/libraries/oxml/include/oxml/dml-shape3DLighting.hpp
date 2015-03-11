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

#ifndef DML_SHAPE3DLIGHTING_HPP
#define DML_SHAPE3DLIGHTING_HPP


#include "dml-baseTypes.hpp"

namespace drawingml
{
	using namespace ::xio;
	using namespace ::xio::xml::schema;

	class CT_LightRig;

	class ST_LightRigType
	{
		static String _literals[];
		String _value;
	public:
		enum value { balanced, brightRoom, chilly, contrasting, flat, flood, freezing, glow, harsh, legacyFlat1, legacyFlat2, legacyFlat3, legacyFlat4, legacyHarsh1, legacyHarsh2, legacyHarsh3, legacyHarsh4, legacyNormal1, legacyNormal2, legacyNormal3, legacyNormal4, morning, soft, sunrise, sunset, threePt, twoPt };

		static const String balanced_literal;
		static const String brightRoom_literal;
		static const String chilly_literal;
		static const String contrasting_literal;
		static const String flat_literal;
		static const String flood_literal;
		static const String freezing_literal;
		static const String glow_literal;
		static const String harsh_literal;
		static const String legacyFlat1_literal;
		static const String legacyFlat2_literal;
		static const String legacyFlat3_literal;
		static const String legacyFlat4_literal;
		static const String legacyHarsh1_literal;
		static const String legacyHarsh2_literal;
		static const String legacyHarsh3_literal;
		static const String legacyHarsh4_literal;
		static const String legacyNormal1_literal;
		static const String legacyNormal2_literal;
		static const String legacyNormal3_literal;
		static const String legacyNormal4_literal;
		static const String morning_literal;
		static const String soft_literal;
		static const String sunrise_literal;
		static const String sunset_literal;
		static const String threePt_literal;
		static const String twoPt_literal;

		ST_LightRigType() : _value(legacyFlat1_literal) {}
		ST_LightRigType(value val) : _value(convert(val)) {}
		ST_LightRigType(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 27, 0); }
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

	class ST_LightRigDirection
	{
		static String _literals[];
		String _value;
	public:
		enum value { b, bl, br, l, r, t, tl, tr };

		static const String b_literal;
		static const String bl_literal;
		static const String br_literal;
		static const String l_literal;
		static const String r_literal;
		static const String t_literal;
		static const String tl_literal;
		static const String tr_literal;

		ST_LightRigDirection() : _value(tl_literal) {}
		ST_LightRigDirection(value val) : _value(convert(val)) {}
		ST_LightRigDirection(const String& str) : _value(str) {}

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

	class CT_LightRig
	{
	public:
		poptional< CT_SphereCoords > rot;
		ST_LightRigType rig;
		ST_LightRigDirection dir;
	};

}
#endif

