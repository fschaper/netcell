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

#ifndef DML_GRAPHICALOBJECTANIMATION_HPP
#define DML_GRAPHICALOBJECTANIMATION_HPP


#include "dml-baseTypes.hpp"

namespace drawingml
{
	using namespace ::xio;
	using namespace ::xio::xml::schema;

	class CT_AnimationDgmElement;
	class CT_AnimationChartElement;
	class CT_AnimationElementChoice;
	class ST_AnimationDgmBuildType;
	class CT_AnimationDgmBuildProperties;
	class ST_AnimationChartBuildType;
	class CT_AnimationChartBuildProperties;
	class CT_AnimationGraphicalObjectBuildProperties;

	class ST_DgmBuildStep
	{
		static String _literals[];
		String _value;
	public:
		enum value { bg, sp };

		static const String bg_literal;
		static const String sp_literal;

		ST_DgmBuildStep() : _value(sp_literal) {}
		ST_DgmBuildStep(value val) : _value(convert(val)) {}
		ST_DgmBuildStep(const String& str) : _value(str) {}

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

	class CT_AnimationDgmElement
	{
	public:
        //TODO: YLS "fixed the uncomplete GUID type by downgrading it to a string
        CT_AnimationDgmElement() : id("{00000000-0000-0000-0000-000000000000}"), bldStep(ST_DgmBuildStep::sp_literal) {}
		ST_Guid id;
		ST_DgmBuildStep bldStep;
	};

	class ST_ChartBuildStep
	{
		static String _literals[];
		String _value;
	public:
		enum value { allPts, category, gridLegend, ptInCategory, ptInSeries, series };

		static const String allPts_literal;
		static const String category_literal;
		static const String gridLegend_literal;
		static const String ptInCategory_literal;
		static const String ptInSeries_literal;
		static const String series_literal;

		ST_ChartBuildStep() : _value(category_literal) {}
		ST_ChartBuildStep(value val) : _value(convert(val)) {}
		ST_ChartBuildStep(const String& str) : _value(str) {}

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

	class CT_AnimationChartElement
	{
	public:
		CT_AnimationChartElement() : seriesIdx(-1), categoryIdx(-1) {}
		Int seriesIdx;
		Int categoryIdx;
		ST_ChartBuildStep bldStep;
	};

	class CT_AnimationElementChoice
	{
	public:
		poptional< CT_AnimationDgmElement > dgm;
		poptional< CT_AnimationChartElement > chart;
	};

	class ST_AnimationDgmBuildType : public simple_type<String>
	{
	public:
		ST_AnimationDgmBuildType() {}
		ST_AnimationDgmBuildType(const String& v) : simple_type<String>(v) {}
	};

	class CT_AnimationDgmBuildProperties
	{
	public:
		CT_AnimationDgmBuildProperties() : bld("allAtOnce"), rev(false) {}
		ST_AnimationDgmBuildType bld;
		Boolean rev;
	};

	class ST_AnimationChartBuildType : public simple_type<String>
	{
	public:
		ST_AnimationChartBuildType() {}
		ST_AnimationChartBuildType(const String& v) : simple_type<String>(v) {}
	};

	class CT_AnimationChartBuildProperties
	{
	public:
		CT_AnimationChartBuildProperties() : bld("allAtOnce"), animBg(true) {}
		ST_AnimationChartBuildType bld;
		Boolean animBg;
	};

	class CT_AnimationGraphicalObjectBuildProperties
	{
	public:
		poptional< CT_AnimationDgmBuildProperties > bldDgm;
		poptional< CT_AnimationChartBuildProperties > bldChart;
	};

}
#endif

