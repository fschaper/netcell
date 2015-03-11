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

#ifndef SML_SINGLECELLTABLE_WRITERS_HPP
#define SML_SINGLECELLTABLE_WRITERS_HPP

#include "sml-singleCellTable.hpp"
#include "sml-singleCellTable_literals.hpp"
#include "sml-baseTypes_writers.hpp"
#include "sml-table_writers.hpp"

namespace spreadsheetml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_XmlPr_writer;
		class CT_XmlCellPr_writer;
		class CT_SingleXmlCell_writer;
		class CT_SingleXmlCells_writer;
		class sml_singleCellTable_writer;

		class CT_XmlPr_writer : public type_writer
		{
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_XmlPr* t() { return static_cast<CT_XmlPr*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_XmlCellPr_writer : public type_writer
		{
			auto_type_writer< CT_XmlPr_writer > _xmlPr_writer;
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_XmlCellPr* t() { return static_cast<CT_XmlCellPr*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_SingleXmlCell_writer : public type_writer
		{
			auto_type_writer< CT_XmlCellPr_writer > _xmlCellPr_writer;
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_SingleXmlCell* t() { return static_cast<CT_SingleXmlCell*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_SingleXmlCells_writer : public type_writer
		{
			auto_type_writer< CT_SingleXmlCell_writer > _singleXmlCell_writer;
			CT_SingleXmlCells* t() { return static_cast<CT_SingleXmlCells*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class sml_singleCellTable_writer : public type_writer
		{
			auto_type_writer< CT_SingleXmlCells_writer > _singleXmlCells_writer;
			sml_singleCellTable* t() { return static_cast<sml_singleCellTable*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

	}
}
#endif

