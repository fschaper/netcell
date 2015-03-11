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

#ifndef SML_TABLE_READERS_HPP
#define SML_TABLE_READERS_HPP

#include "sml-table.hpp"
#include "sml-autoFilter_readers.hpp"
#include "sml-baseTypes_readers.hpp"
#include "sml-styles_readers.hpp"

namespace spreadsheetml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_TableFormula_reader;
		class CT_XmlColumnPr_reader;
		class CT_TableColumn_reader;
		class CT_TableColumns_reader;
		class CT_TableStyleInfo_reader;
		class CT_Table_reader;
		class sml_table_reader;

		class CT_TableFormula_reader : public ST_Formula_reader
		{
		protected:
			CT_TableFormula* t() { return static_cast<CT_TableFormula*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_XmlColumnPr_reader : public type_reader
		{
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_XmlColumnPr* t() { return static_cast<CT_XmlColumnPr*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_TableColumn_reader : public type_reader
		{
			auto_type_reader< CT_TableFormula_reader > _calculatedColumnFormula_reader;
			auto_type_reader< CT_TableFormula_reader > _totalsRowFormula_reader;
			auto_type_reader< CT_XmlColumnPr_reader > _xmlColumnPr_reader;
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_TableColumn* t() { return static_cast<CT_TableColumn*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_TableColumns_reader : public type_reader
		{
			auto_type_reader< CT_TableColumn_reader > _tableColumn_reader;
		protected:
			CT_TableColumns* t() { return static_cast<CT_TableColumns*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_TableStyleInfo_reader : public type_reader
		{
		protected:
			CT_TableStyleInfo* t() { return static_cast<CT_TableStyleInfo*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Table_reader : public type_reader
		{
			auto_type_reader< CT_AutoFilter_reader > _autoFilter_reader;
			auto_type_reader< CT_SortState_reader > _sortState_reader;
			auto_type_reader< CT_TableColumns_reader > _tableColumns_reader;
			auto_type_reader< CT_TableStyleInfo_reader > _tableStyleInfo_reader;
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_Table* t() { return static_cast<CT_Table*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class sml_table_reader : public type_reader
		{
			auto_type_reader< CT_Table_reader > _table_reader;
		protected:
			sml_table* t() { return static_cast<sml_table*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

	}
}
#endif

