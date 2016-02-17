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

#ifndef SML_BASETYPES_WRITERS_HPP
#define SML_BASETYPES_WRITERS_HPP

#include "sml-baseTypes.hpp"
#include "sml-baseTypes_literals.hpp"
#include <xio/xml/binding/type_writer.hpp>

namespace spreadsheetml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class ST_CellRef_writer;
		class CT_Extension_writer;
		class CT_ExtensionList_writer;
		class ST_Xstring_writer;
		class ST_UnsignedIntHex_writer;
		class ST_Ref_writer;
		class ST_Guid_writer;
		class CT_XStringElement_writer;
		class ST_RefA_writer;
		class ST_Formula_writer;
		class ST_Sqref_writer;
		class ST_UnsignedShortHex_writer;

		class ST_CellRef_writer : public type_writer
		{
			ST_CellRef* t() { return static_cast<ST_CellRef*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Extension_writer : public type_writer
		{
			CT_Extension* t() { return static_cast<CT_Extension*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_ExtensionList_writer : public type_writer
		{
			auto_type_writer< CT_Extension_writer > _ext_writer;
			CT_ExtensionList* t() { return static_cast<CT_ExtensionList*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class ST_Xstring_writer : public type_writer
		{
			ST_Xstring* t() { return static_cast<ST_Xstring*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class ST_UnsignedIntHex_writer : public type_writer
		{
			ST_UnsignedIntHex* t() { return static_cast<ST_UnsignedIntHex*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class ST_Ref_writer : public type_writer
		{
			ST_Ref* t() { return static_cast<ST_Ref*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class ST_Guid_writer : public type_writer
		{
			ST_Guid* t() { return static_cast<ST_Guid*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_XStringElement_writer : public type_writer
		{
			CT_XStringElement* t() { return static_cast<CT_XStringElement*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class ST_RefA_writer : public type_writer
		{
			ST_RefA* t() { return static_cast<ST_RefA*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class ST_Formula_writer : public ST_Xstring_writer
		{
			ST_Formula* t() { return static_cast<ST_Formula*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class ST_Sqref_writer : public ST_Ref_writer
		{
			ST_Sqref* t() { return static_cast<ST_Sqref*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class ST_UnsignedShortHex_writer : public type_writer
		{
			ST_UnsignedShortHex* t() { return static_cast<ST_UnsignedShortHex*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

	}
}
#endif

