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

#ifndef SML_SUPPLEMENTARYWORKBOOKS_WRITERS_HPP
#define SML_SUPPLEMENTARYWORKBOOKS_WRITERS_HPP

#include "sml-supplementaryWorkbooks.hpp"
#include "sml-supplementaryWorkbooks_literals.hpp"
#include "sml-baseTypes_writers.hpp"
#include "sml-sheet_writers.hpp"
#include "shared-relationshipReference_writers.hpp"

namespace spreadsheetml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_ExternalSheetName_writer;
		class CT_ExternalSheetNames_writer;
		class CT_ExternalDefinedName_writer;
		class CT_ExternalDefinedNames_writer;
		class CT_ExternalCell_writer;
		class CT_ExternalRow_writer;
		class CT_ExternalSheetData_writer;
		class CT_ExternalSheetDataSet_writer;
		class CT_ExternalBook_writer;
		class CT_DdeValue_writer;
		class CT_DdeValues_writer;
		class CT_DdeItem_writer;
		class CT_DdeItems_writer;
		class CT_DdeLink_writer;
		class CT_OleItem_writer;
		class CT_OleItems_writer;
		class CT_OleLink_writer;
		class CT_ExternalLink_writer;
		class sml_supplementaryWorkbooks_writer;

		class CT_ExternalSheetName_writer : public type_writer
		{
			CT_ExternalSheetName* t() { return static_cast<CT_ExternalSheetName*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_ExternalSheetNames_writer : public type_writer
		{
			auto_type_writer< CT_ExternalSheetName_writer > _sheetName_writer;
			CT_ExternalSheetNames* t() { return static_cast<CT_ExternalSheetNames*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_ExternalDefinedName_writer : public type_writer
		{
			CT_ExternalDefinedName* t() { return static_cast<CT_ExternalDefinedName*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_ExternalDefinedNames_writer : public type_writer
		{
			auto_type_writer< CT_ExternalDefinedName_writer > _definedName_writer;
			CT_ExternalDefinedNames* t() { return static_cast<CT_ExternalDefinedNames*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_ExternalCell_writer : public type_writer
		{
			auto_type_writer< ST_Xstring_writer > _v_writer;
			CT_ExternalCell* t() { return static_cast<CT_ExternalCell*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_ExternalRow_writer : public type_writer
		{
			auto_type_writer< CT_ExternalCell_writer > _cell_writer;
			CT_ExternalRow* t() { return static_cast<CT_ExternalRow*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_ExternalSheetData_writer : public type_writer
		{
			auto_type_writer< CT_ExternalRow_writer > _row_writer;
			CT_ExternalSheetData* t() { return static_cast<CT_ExternalSheetData*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_ExternalSheetDataSet_writer : public type_writer
		{
			auto_type_writer< CT_ExternalSheetData_writer > _sheetData_writer;
			CT_ExternalSheetDataSet* t() { return static_cast<CT_ExternalSheetDataSet*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_ExternalBook_writer : public type_writer
		{
			auto_type_writer< CT_ExternalSheetNames_writer > _sheetNames_writer;
			auto_type_writer< CT_ExternalDefinedNames_writer > _definedNames_writer;
			auto_type_writer< CT_ExternalSheetDataSet_writer > _sheetDataSet_writer;
			CT_ExternalBook* t() { return static_cast<CT_ExternalBook*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_DdeValue_writer : public type_writer
		{
			auto_type_writer< ST_Xstring_writer > _val_writer;
			CT_DdeValue* t() { return static_cast<CT_DdeValue*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_DdeValues_writer : public type_writer
		{
			auto_type_writer< CT_DdeValue_writer > _value_writer;
			CT_DdeValues* t() { return static_cast<CT_DdeValues*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_DdeItem_writer : public type_writer
		{
			auto_type_writer< CT_DdeValues_writer > _values_writer;
			CT_DdeItem* t() { return static_cast<CT_DdeItem*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_DdeItems_writer : public type_writer
		{
			auto_type_writer< CT_DdeItem_writer > _ddeItem_writer;
			CT_DdeItems* t() { return static_cast<CT_DdeItems*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_DdeLink_writer : public type_writer
		{
			auto_type_writer< CT_DdeItems_writer > _ddeItems_writer;
			CT_DdeLink* t() { return static_cast<CT_DdeLink*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_OleItem_writer : public type_writer
		{
			CT_OleItem* t() { return static_cast<CT_OleItem*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_OleItems_writer : public type_writer
		{
			auto_type_writer< CT_OleItem_writer > _oleItem_writer;
			CT_OleItems* t() { return static_cast<CT_OleItems*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_OleLink_writer : public type_writer
		{
			auto_type_writer< CT_OleItems_writer > _oleItems_writer;
			CT_OleLink* t() { return static_cast<CT_OleLink*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_ExternalLink_writer : public type_writer
		{
			auto_type_writer< CT_ExternalBook_writer > _externalBook_writer;
			auto_type_writer< CT_DdeLink_writer > _ddeLink_writer;
			auto_type_writer< CT_OleLink_writer > _oleLink_writer;
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_ExternalLink* t() { return static_cast<CT_ExternalLink*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class sml_supplementaryWorkbooks_writer : public type_writer
		{
			auto_type_writer< CT_ExternalLink_writer > _externalLink_writer;
			sml_supplementaryWorkbooks* t() { return static_cast<sml_supplementaryWorkbooks*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

	}
}
#endif

