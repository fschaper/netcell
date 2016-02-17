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

#ifndef SML_QUERYTABLE_READERS_HPP
#define SML_QUERYTABLE_READERS_HPP

#include "sml-queryTable.hpp"
#include "sml-baseTypes_readers.hpp"
#include "sml-autoFilter_readers.hpp"

namespace spreadsheetml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_QueryTableField_reader;
		class CT_QueryTableFields_reader;
		class CT_DeletedField_reader;
		class CT_QueryTableDeletedFields_reader;
		class CT_QueryTableRefresh_reader;
		class CT_QueryTable_reader;
		class sml_queryTable_reader;

		class CT_QueryTableField_reader : public type_reader
		{
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_QueryTableField* t() { return static_cast<CT_QueryTableField*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_QueryTableFields_reader : public type_reader
		{
			auto_type_reader< CT_QueryTableField_reader > _queryTableField_reader;
		protected:
			CT_QueryTableFields* t() { return static_cast<CT_QueryTableFields*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_DeletedField_reader : public type_reader
		{
		protected:
			CT_DeletedField* t() { return static_cast<CT_DeletedField*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_QueryTableDeletedFields_reader : public type_reader
		{
			auto_type_reader< CT_DeletedField_reader > _deletedField_reader;
		protected:
			CT_QueryTableDeletedFields* t() { return static_cast<CT_QueryTableDeletedFields*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_QueryTableRefresh_reader : public type_reader
		{
			auto_type_reader< CT_QueryTableFields_reader > _queryTableFields_reader;
			auto_type_reader< CT_QueryTableDeletedFields_reader > _queryTableDeletedFields_reader;
			auto_type_reader< CT_SortState_reader > _sortState_reader;
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_QueryTableRefresh* t() { return static_cast<CT_QueryTableRefresh*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_QueryTable_reader : public type_reader
		{
			auto_type_reader< CT_QueryTableRefresh_reader > _queryTableRefresh_reader;
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_QueryTable* t() { return static_cast<CT_QueryTable*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class sml_queryTable_reader : public type_reader
		{
			auto_type_reader< CT_QueryTable_reader > _queryTable_reader;
		protected:
			sml_queryTable* t() { return static_cast<sml_queryTable*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

	}
}
#endif

