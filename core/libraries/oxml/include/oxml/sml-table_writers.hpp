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

#ifndef SML_TABLE_WRITERS_HPP
#define SML_TABLE_WRITERS_HPP

#include "sml-table.hpp"
#include "sml-table_literals.hpp"
#include "sml-autoFilter_writers.hpp"
#include "sml-baseTypes_writers.hpp"
#include "sml-styles_writers.hpp"

namespace spreadsheetml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_TableFormula_writer;
		class CT_XmlColumnPr_writer;
		class CT_TableColumn_writer;
		class CT_TableColumns_writer;
		class CT_TableStyleInfo_writer;
		class CT_Table_writer;
		class sml_table_writer;

		class CT_TableFormula_writer : public ST_Formula_writer
		{
			CT_TableFormula* t() { return static_cast<CT_TableFormula*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_XmlColumnPr_writer : public type_writer
		{
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_XmlColumnPr* t() { return static_cast<CT_XmlColumnPr*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_TableColumn_writer : public type_writer
		{
			auto_type_writer< CT_TableFormula_writer > _calculatedColumnFormula_writer;
			auto_type_writer< CT_TableFormula_writer > _totalsRowFormula_writer;
			auto_type_writer< CT_XmlColumnPr_writer > _xmlColumnPr_writer;
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_TableColumn* t() { return static_cast<CT_TableColumn*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_TableColumns_writer : public type_writer
		{
			auto_type_writer< CT_TableColumn_writer > _tableColumn_writer;
			CT_TableColumns* t() { return static_cast<CT_TableColumns*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_TableStyleInfo_writer : public type_writer
		{
			CT_TableStyleInfo* t() { return static_cast<CT_TableStyleInfo*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Table_writer : public type_writer
		{
			auto_type_writer< CT_AutoFilter_writer > _autoFilter_writer;
			auto_type_writer< CT_SortState_writer > _sortState_writer;
			auto_type_writer< CT_TableColumns_writer > _tableColumns_writer;
			auto_type_writer< CT_TableStyleInfo_writer > _tableStyleInfo_writer;
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_Table* t() { return static_cast<CT_Table*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class sml_table_writer : public type_writer
		{
			auto_type_writer< CT_Table_writer > _table_writer;
			sml_table* t() { return static_cast<sml_table*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

	}
}
#endif

