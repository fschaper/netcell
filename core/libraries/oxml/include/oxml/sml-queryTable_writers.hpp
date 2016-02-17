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

#ifndef SML_QUERYTABLE_WRITERS_HPP
#define SML_QUERYTABLE_WRITERS_HPP

#include "sml-queryTable.hpp"
#include "sml-queryTable_literals.hpp"
#include "sml-baseTypes_writers.hpp"
#include "sml-autoFilter_writers.hpp"

namespace spreadsheetml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_QueryTableField_writer;
		class CT_QueryTableFields_writer;
		class CT_DeletedField_writer;
		class CT_QueryTableDeletedFields_writer;
		class CT_QueryTableRefresh_writer;
		class CT_QueryTable_writer;
		class sml_queryTable_writer;

		class CT_QueryTableField_writer : public type_writer
		{
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_QueryTableField* t() { return static_cast<CT_QueryTableField*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_QueryTableFields_writer : public type_writer
		{
			auto_type_writer< CT_QueryTableField_writer > _queryTableField_writer;
			CT_QueryTableFields* t() { return static_cast<CT_QueryTableFields*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_DeletedField_writer : public type_writer
		{
			CT_DeletedField* t() { return static_cast<CT_DeletedField*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_QueryTableDeletedFields_writer : public type_writer
		{
			auto_type_writer< CT_DeletedField_writer > _deletedField_writer;
			CT_QueryTableDeletedFields* t() { return static_cast<CT_QueryTableDeletedFields*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_QueryTableRefresh_writer : public type_writer
		{
			auto_type_writer< CT_QueryTableFields_writer > _queryTableFields_writer;
			auto_type_writer< CT_QueryTableDeletedFields_writer > _queryTableDeletedFields_writer;
			auto_type_writer< CT_SortState_writer > _sortState_writer;
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_QueryTableRefresh* t() { return static_cast<CT_QueryTableRefresh*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_QueryTable_writer : public type_writer
		{
			auto_type_writer< CT_QueryTableRefresh_writer > _queryTableRefresh_writer;
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_QueryTable* t() { return static_cast<CT_QueryTable*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class sml_queryTable_writer : public type_writer
		{
			auto_type_writer< CT_QueryTable_writer > _queryTable_writer;
			sml_queryTable* t() { return static_cast<sml_queryTable*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

	}
}
#endif

