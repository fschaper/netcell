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

#ifndef DML_SHAPE3DSTYLES_HPP
#define DML_SHAPE3DSTYLES_HPP


#include "dml-baseTypes.hpp"

namespace drawingml
{
	using namespace ::xio;
	using namespace ::xio::xml::schema;

	class CT_Bevel;
	class CT_Shape3D;
	class CT_FlatText;

	class ST_BevelPresetType
	{
		static String _literals[];
		String _value;
	public:
		enum value { angle, artDeco, circle, convex, coolSlant, cross, divot, hardEdge, relaxedInset, riblet, slope, softRound };

		static const String angle_literal;
		static const String artDeco_literal;
		static const String circle_literal;
		static const String convex_literal;
		static const String coolSlant_literal;
		static const String cross_literal;
		static const String divot_literal;
		static const String hardEdge_literal;
		static const String relaxedInset_literal;
		static const String riblet_literal;
		static const String slope_literal;
		static const String softRound_literal;

		ST_BevelPresetType() : _value(relaxedInset_literal) {}
		ST_BevelPresetType(value val) : _value(convert(val)) {}
		ST_BevelPresetType(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 12, 0); }
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

	class CT_Bevel
	{
	public:
		CT_Bevel() : w(76200L), h(76200L), prst(ST_BevelPresetType::circle_literal) {}
		ST_PositiveCoordinate w;
		ST_PositiveCoordinate h;
		ST_BevelPresetType prst;
	};

	class ST_PresetMaterialType
	{
		static String _literals[];
		String _value;
	public:
		enum value { clear, dkEdge, flat, legacyMatte, legacyMetal, legacyPlastic, legacyWireframe, matte, metal, plastic, powder, softEdge, softmetal, translucentPowder, warmMatte };

		static const String clear_literal;
		static const String dkEdge_literal;
		static const String flat_literal;
		static const String legacyMatte_literal;
		static const String legacyMetal_literal;
		static const String legacyPlastic_literal;
		static const String legacyWireframe_literal;
		static const String matte_literal;
		static const String metal_literal;
		static const String plastic_literal;
		static const String powder_literal;
		static const String softEdge_literal;
		static const String softmetal_literal;
		static const String translucentPowder_literal;
		static const String warmMatte_literal;

		ST_PresetMaterialType() : _value(legacyMatte_literal) {}
		ST_PresetMaterialType(value val) : _value(convert(val)) {}
		ST_PresetMaterialType(const String& str) : _value(str) {}

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

	class CT_Shape3D
	{
	public:
		CT_Shape3D() : z(0L), extrusionH(0L), contourW(0L), prstMaterial(ST_PresetMaterialType::warmMatte_literal) {}
		poptional< CT_Bevel > bevelT;
		poptional< CT_Bevel > bevelB;
		poptional< CT_Color > extrusionClr;
		poptional< CT_Color > contourClr;
		poptional< CT_OfficeArtExtensionList > extLst;
		ST_Coordinate z;
		ST_PositiveCoordinate extrusionH;
		ST_PositiveCoordinate contourW;
		ST_PresetMaterialType prstMaterial;
	};

	class CT_FlatText
	{
	public:
		CT_FlatText() : z(0L) {}
		ST_Coordinate z;
	};

}
#endif

