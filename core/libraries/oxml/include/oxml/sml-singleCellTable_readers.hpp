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

#ifndef SML_SINGLECELLTABLE_READERS_HPP
#define SML_SINGLECELLTABLE_READERS_HPP

#include "sml-singleCellTable.hpp"
#include "sml-baseTypes_readers.hpp"
#include "sml-table_readers.hpp"

namespace spreadsheetml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_XmlPr_reader;
		class CT_XmlCellPr_reader;
		class CT_SingleXmlCell_reader;
		class CT_SingleXmlCells_reader;
		class sml_singleCellTable_reader;

		class CT_XmlPr_reader : public type_reader
		{
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_XmlPr* t() { return static_cast<CT_XmlPr*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_XmlCellPr_reader : public type_reader
		{
			auto_type_reader< CT_XmlPr_reader > _xmlPr_reader;
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_XmlCellPr* t() { return static_cast<CT_XmlCellPr*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_SingleXmlCell_reader : public type_reader
		{
			auto_type_reader< CT_XmlCellPr_reader > _xmlCellPr_reader;
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_SingleXmlCell* t() { return static_cast<CT_SingleXmlCell*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_SingleXmlCells_reader : public type_reader
		{
			auto_type_reader< CT_SingleXmlCell_reader > _singleXmlCell_reader;
		protected:
			CT_SingleXmlCells* t() { return static_cast<CT_SingleXmlCells*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class sml_singleCellTable_reader : public type_reader
		{
			auto_type_reader< CT_SingleXmlCells_reader > _singleXmlCells_reader;
		protected:
			sml_singleCellTable* t() { return static_cast<sml_singleCellTable*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

	}
}
#endif

