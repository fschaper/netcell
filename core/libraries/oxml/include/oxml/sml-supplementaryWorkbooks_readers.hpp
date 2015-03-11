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

#ifndef SML_SUPPLEMENTARYWORKBOOKS_READERS_HPP
#define SML_SUPPLEMENTARYWORKBOOKS_READERS_HPP

#include "sml-supplementaryWorkbooks.hpp"
#include "sml-baseTypes_readers.hpp"
#include "sml-sheet_readers.hpp"
#include "shared-relationshipReference_readers.hpp"

namespace spreadsheetml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_ExternalSheetName_reader;
		class CT_ExternalSheetNames_reader;
		class CT_ExternalDefinedName_reader;
		class CT_ExternalDefinedNames_reader;
		class CT_ExternalCell_reader;
		class CT_ExternalRow_reader;
		class CT_ExternalSheetData_reader;
		class CT_ExternalSheetDataSet_reader;
		class CT_ExternalBook_reader;
		class CT_DdeValue_reader;
		class CT_DdeValues_reader;
		class CT_DdeItem_reader;
		class CT_DdeItems_reader;
		class CT_DdeLink_reader;
		class CT_OleItem_reader;
		class CT_OleItems_reader;
		class CT_OleLink_reader;
		class CT_ExternalLink_reader;
		class sml_supplementaryWorkbooks_reader;

		class CT_ExternalSheetName_reader : public type_reader
		{
		protected:
			CT_ExternalSheetName* t() { return static_cast<CT_ExternalSheetName*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_ExternalSheetNames_reader : public type_reader
		{
			auto_type_reader< CT_ExternalSheetName_reader > _sheetName_reader;
		protected:
			CT_ExternalSheetNames* t() { return static_cast<CT_ExternalSheetNames*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_ExternalDefinedName_reader : public type_reader
		{
		protected:
			CT_ExternalDefinedName* t() { return static_cast<CT_ExternalDefinedName*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_ExternalDefinedNames_reader : public type_reader
		{
			auto_type_reader< CT_ExternalDefinedName_reader > _definedName_reader;
		protected:
			CT_ExternalDefinedNames* t() { return static_cast<CT_ExternalDefinedNames*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_ExternalCell_reader : public type_reader
		{
			auto_type_reader< ST_Xstring_reader > _v_reader;
		protected:
			CT_ExternalCell* t() { return static_cast<CT_ExternalCell*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_ExternalRow_reader : public type_reader
		{
			auto_type_reader< CT_ExternalCell_reader > _cell_reader;
		protected:
			CT_ExternalRow* t() { return static_cast<CT_ExternalRow*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_ExternalSheetData_reader : public type_reader
		{
			auto_type_reader< CT_ExternalRow_reader > _row_reader;
		protected:
			CT_ExternalSheetData* t() { return static_cast<CT_ExternalSheetData*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_ExternalSheetDataSet_reader : public type_reader
		{
			auto_type_reader< CT_ExternalSheetData_reader > _sheetData_reader;
		protected:
			CT_ExternalSheetDataSet* t() { return static_cast<CT_ExternalSheetDataSet*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_ExternalBook_reader : public type_reader
		{
			auto_type_reader< CT_ExternalSheetNames_reader > _sheetNames_reader;
			auto_type_reader< CT_ExternalDefinedNames_reader > _definedNames_reader;
			auto_type_reader< CT_ExternalSheetDataSet_reader > _sheetDataSet_reader;
		protected:
			CT_ExternalBook* t() { return static_cast<CT_ExternalBook*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_DdeValue_reader : public type_reader
		{
			auto_type_reader< ST_Xstring_reader > _val_reader;
		protected:
			CT_DdeValue* t() { return static_cast<CT_DdeValue*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_DdeValues_reader : public type_reader
		{
			auto_type_reader< CT_DdeValue_reader > _value_reader;
		protected:
			CT_DdeValues* t() { return static_cast<CT_DdeValues*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_DdeItem_reader : public type_reader
		{
			auto_type_reader< CT_DdeValues_reader > _values_reader;
		protected:
			CT_DdeItem* t() { return static_cast<CT_DdeItem*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_DdeItems_reader : public type_reader
		{
			auto_type_reader< CT_DdeItem_reader > _ddeItem_reader;
		protected:
			CT_DdeItems* t() { return static_cast<CT_DdeItems*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_DdeLink_reader : public type_reader
		{
			auto_type_reader< CT_DdeItems_reader > _ddeItems_reader;
		protected:
			CT_DdeLink* t() { return static_cast<CT_DdeLink*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_OleItem_reader : public type_reader
		{
		protected:
			CT_OleItem* t() { return static_cast<CT_OleItem*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_OleItems_reader : public type_reader
		{
			auto_type_reader< CT_OleItem_reader > _oleItem_reader;
		protected:
			CT_OleItems* t() { return static_cast<CT_OleItems*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class CT_OleLink_reader : public type_reader
		{
			auto_type_reader< CT_OleItems_reader > _oleItems_reader;
		protected:
			CT_OleLink* t() { return static_cast<CT_OleLink*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_ExternalLink_reader : public type_reader
		{
			auto_type_reader< CT_ExternalBook_reader > _externalBook_reader;
			auto_type_reader< CT_DdeLink_reader > _ddeLink_reader;
			auto_type_reader< CT_OleLink_reader > _oleLink_reader;
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_ExternalLink* t() { return static_cast<CT_ExternalLink*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class sml_supplementaryWorkbooks_reader : public type_reader
		{
			auto_type_reader< CT_ExternalLink_reader > _externalLink_reader;
		protected:
			sml_supplementaryWorkbooks* t() { return static_cast<sml_supplementaryWorkbooks*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

	}
}
#endif

