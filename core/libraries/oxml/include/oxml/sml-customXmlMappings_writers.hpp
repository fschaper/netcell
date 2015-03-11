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

#ifndef SML_CUSTOMXMLMAPPINGS_WRITERS_HPP
#define SML_CUSTOMXMLMAPPINGS_WRITERS_HPP

#include "sml-customXmlMappings.hpp"
#include "sml-customXmlMappings_literals.hpp"
#include <xio/xml/binding/type_writer.hpp>

namespace spreadsheetml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_Schema_writer;
		class CT_DataBinding_writer;
		class CT_Map_writer;
		class CT_MapInfo_writer;
		class sml_customXmlMappings_writer;

		class CT_Schema_writer : public type_writer
		{
			CT_Schema* t() { return static_cast<CT_Schema*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_DataBinding_writer : public type_writer
		{
			CT_DataBinding* t() { return static_cast<CT_DataBinding*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Map_writer : public type_writer
		{
			auto_type_writer< CT_DataBinding_writer > _DataBinding_writer;
			CT_Map* t() { return static_cast<CT_Map*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_MapInfo_writer : public type_writer
		{
			auto_type_writer< CT_Schema_writer > _Schema_writer;
			auto_type_writer< CT_Map_writer > _Map_writer;
			CT_MapInfo* t() { return static_cast<CT_MapInfo*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class sml_customXmlMappings_writer : public type_writer
		{
			auto_type_writer< CT_MapInfo_writer > _MapInfo_writer;
			sml_customXmlMappings* t() { return static_cast<sml_customXmlMappings*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

	}
}
#endif

