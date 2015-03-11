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

#ifndef SML_PIVOTTABLESHARED_WRITERS_HPP
#define SML_PIVOTTABLESHARED_WRITERS_HPP

#include "sml-pivotTableShared.hpp"
#include "sml-pivotTableShared_literals.hpp"
#include "sml-baseTypes_writers.hpp"

namespace spreadsheetml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_Index_writer;
		class CT_PivotAreaReference_writer;
		class CT_PivotAreaReferences_writer;
		class CT_PivotArea_writer;

		class CT_Index_writer : public type_writer
		{
			CT_Index* t() { return static_cast<CT_Index*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_PivotAreaReference_writer : public type_writer
		{
			auto_type_writer< CT_Index_writer > _x_writer;
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_PivotAreaReference* t() { return static_cast<CT_PivotAreaReference*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_PivotAreaReferences_writer : public type_writer
		{
			auto_type_writer< CT_PivotAreaReference_writer > _reference_writer;
			CT_PivotAreaReferences* t() { return static_cast<CT_PivotAreaReferences*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_PivotArea_writer : public type_writer
		{
			auto_type_writer< CT_PivotAreaReferences_writer > _references_writer;
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_PivotArea* t() { return static_cast<CT_PivotArea*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

	}
}
#endif

