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

#ifndef SML_CUSTOMXMLMAPPINGS_READERS_HPP
#define SML_CUSTOMXMLMAPPINGS_READERS_HPP

#include "sml-customXmlMappings.hpp"
#include <xio/xml/binding/type_reader.hpp>

namespace spreadsheetml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_Schema_reader;
		class CT_DataBinding_reader;
		class CT_Map_reader;
		class CT_MapInfo_reader;
		class sml_customXmlMappings_reader;

		class CT_Schema_reader : public type_reader
		{
		protected:
			CT_Schema* t() { return static_cast<CT_Schema*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_DataBinding_reader : public type_reader
		{
		protected:
			CT_DataBinding* t() { return static_cast<CT_DataBinding*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Map_reader : public type_reader
		{
			auto_type_reader< CT_DataBinding_reader > _DataBinding_reader;
		protected:
			CT_Map* t() { return static_cast<CT_Map*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_MapInfo_reader : public type_reader
		{
			auto_type_reader< CT_Schema_reader > _Schema_reader;
			auto_type_reader< CT_Map_reader > _Map_reader;
		protected:
			CT_MapInfo* t() { return static_cast<CT_MapInfo*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class sml_customXmlMappings_reader : public type_reader
		{
			auto_type_reader< CT_MapInfo_reader > _MapInfo_reader;
		protected:
			sml_customXmlMappings* t() { return static_cast<sml_customXmlMappings*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

	}
}
#endif

