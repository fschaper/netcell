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

#ifndef DML_SHAPELINEPROPERTIES_WRITERS_HPP
#define DML_SHAPELINEPROPERTIES_WRITERS_HPP

#include "dml-shapeLineProperties.hpp"
#include "dml-shapeLineProperties_literals.hpp"
#include "dml-shapeEffects_writers.hpp"
#include "dml-baseTypes_writers.hpp"

namespace drawingml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_PresetLineDashProperties_writer;
		class CT_DashStop_writer;
		class CT_DashStopList_writer;
		class CT_LineJoinRound_writer;
		class CT_LineJoinBevel_writer;
		class CT_LineJoinMiterProperties_writer;
		class CT_LineEndProperties_writer;
		class ST_LineWidth_writer;
		class CT_LineProperties_writer;

		class CT_PresetLineDashProperties_writer : public type_writer
		{
			CT_PresetLineDashProperties* t() { return static_cast<CT_PresetLineDashProperties*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_DashStop_writer : public type_writer
		{
			CT_DashStop* t() { return static_cast<CT_DashStop*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_DashStopList_writer : public type_writer
		{
			auto_type_writer< CT_DashStop_writer > _ds_writer;
			CT_DashStopList* t() { return static_cast<CT_DashStopList*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_LineJoinRound_writer : public type_writer
		{
			CT_LineJoinRound* t() { return static_cast<CT_LineJoinRound*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_LineJoinBevel_writer : public type_writer
		{
			CT_LineJoinBevel* t() { return static_cast<CT_LineJoinBevel*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_LineJoinMiterProperties_writer : public type_writer
		{
			CT_LineJoinMiterProperties* t() { return static_cast<CT_LineJoinMiterProperties*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_LineEndProperties_writer : public type_writer
		{
			CT_LineEndProperties* t() { return static_cast<CT_LineEndProperties*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class ST_LineWidth_writer : public ST_Coordinate32_writer
		{
			ST_LineWidth* t() { return static_cast<ST_LineWidth*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_LineProperties_writer : public type_writer
		{
			auto_type_writer< CT_NoFillProperties_writer > _noFill_writer;
			auto_type_writer< CT_SolidColorFillProperties_writer > _solidFill_writer;
			auto_type_writer< CT_GradientFillProperties_writer > _gradFill_writer;
			auto_type_writer< CT_PatternFillProperties_writer > _pattFill_writer;
			auto_type_writer< CT_PresetLineDashProperties_writer > _prstDash_writer;
			auto_type_writer< CT_DashStopList_writer > _custDash_writer;
			auto_type_writer< CT_LineJoinRound_writer > _round_writer;
			auto_type_writer< CT_LineJoinBevel_writer > _bevel_writer;
			auto_type_writer< CT_LineJoinMiterProperties_writer > _miter_writer;
			auto_type_writer< CT_LineEndProperties_writer > _headEnd_writer;
			auto_type_writer< CT_LineEndProperties_writer > _tailEnd_writer;
			auto_type_writer< CT_OfficeArtExtensionList_writer > _extLst_writer;
			CT_LineProperties* t() { return static_cast<CT_LineProperties*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

	}
}
#endif

