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

#ifndef DML_GRAPHICALOBJECTANIMATION_WRITERS_HPP
#define DML_GRAPHICALOBJECTANIMATION_WRITERS_HPP

#include "dml-graphicalObjectAnimation.hpp"
#include "dml-graphicalObjectAnimation_literals.hpp"
#include "dml-baseTypes_writers.hpp"

namespace drawingml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_AnimationDgmElement_writer;
		class CT_AnimationChartElement_writer;
		class CT_AnimationElementChoice_writer;
		class ST_AnimationDgmBuildType_writer;
		class CT_AnimationDgmBuildProperties_writer;
		class ST_AnimationChartBuildType_writer;
		class CT_AnimationChartBuildProperties_writer;
		class CT_AnimationGraphicalObjectBuildProperties_writer;

		class CT_AnimationDgmElement_writer : public type_writer
		{
			CT_AnimationDgmElement* t() { return static_cast<CT_AnimationDgmElement*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_AnimationChartElement_writer : public type_writer
		{
			CT_AnimationChartElement* t() { return static_cast<CT_AnimationChartElement*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_AnimationElementChoice_writer : public type_writer
		{
			auto_type_writer< CT_AnimationDgmElement_writer > _dgm_writer;
			auto_type_writer< CT_AnimationChartElement_writer > _chart_writer;
			CT_AnimationElementChoice* t() { return static_cast<CT_AnimationElementChoice*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class ST_AnimationDgmBuildType_writer : public type_writer
		{
			ST_AnimationDgmBuildType* t() { return static_cast<ST_AnimationDgmBuildType*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_AnimationDgmBuildProperties_writer : public type_writer
		{
			CT_AnimationDgmBuildProperties* t() { return static_cast<CT_AnimationDgmBuildProperties*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class ST_AnimationChartBuildType_writer : public type_writer
		{
			ST_AnimationChartBuildType* t() { return static_cast<ST_AnimationChartBuildType*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_AnimationChartBuildProperties_writer : public type_writer
		{
			CT_AnimationChartBuildProperties* t() { return static_cast<CT_AnimationChartBuildProperties*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_AnimationGraphicalObjectBuildProperties_writer : public type_writer
		{
			auto_type_writer< CT_AnimationDgmBuildProperties_writer > _bldDgm_writer;
			auto_type_writer< CT_AnimationChartBuildProperties_writer > _bldChart_writer;
			CT_AnimationGraphicalObjectBuildProperties* t() { return static_cast<CT_AnimationGraphicalObjectBuildProperties*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

	}
}
#endif

