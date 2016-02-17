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

#ifndef SML_BASETYPES_READERS_HPP
#define SML_BASETYPES_READERS_HPP

#include "sml-baseTypes.hpp"
#include <xio/xml/binding/type_reader.hpp>

namespace spreadsheetml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class ST_CellRef_reader;
		class CT_Extension_reader;
		class CT_ExtensionList_reader;
		class ST_Xstring_reader;
		class ST_UnsignedIntHex_reader;
		class ST_Ref_reader;
		class ST_Guid_reader;
		class CT_XStringElement_reader;
		class ST_RefA_reader;
		class ST_Formula_reader;
		class ST_Sqref_reader;
		class ST_UnsignedShortHex_reader;

		class ST_CellRef_reader : public type_reader
		{
		protected:
			ST_CellRef* t() { return static_cast<ST_CellRef*>(target()); }
			void read_value(const xstring& val);
		};

		class CT_Extension_reader : public type_reader
		{
		protected:
			CT_Extension* t() { return static_cast<CT_Extension*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_ExtensionList_reader : public type_reader
		{
			auto_type_reader< CT_Extension_reader > _ext_reader;
		protected:
			CT_ExtensionList* t() { return static_cast<CT_ExtensionList*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class ST_Xstring_reader : public type_reader
		{
		protected:
			ST_Xstring* t() { return static_cast<ST_Xstring*>(target()); }
			void read_value(const xstring& val);
		};

		class ST_UnsignedIntHex_reader : public type_reader
		{
		protected:
			ST_UnsignedIntHex* t() { return static_cast<ST_UnsignedIntHex*>(target()); }
			void read_value(const xstring& val);
		};

		class ST_Ref_reader : public type_reader
		{
		protected:
			ST_Ref* t() { return static_cast<ST_Ref*>(target()); }
			void read_value(const xstring& val);
		};

		class ST_Guid_reader : public type_reader
		{
		protected:
			ST_Guid* t() { return static_cast<ST_Guid*>(target()); }
			void read_value(const xstring& val);
		};

		class CT_XStringElement_reader : public type_reader
		{
		protected:
			CT_XStringElement* t() { return static_cast<CT_XStringElement*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class ST_RefA_reader : public type_reader
		{
		protected:
			ST_RefA* t() { return static_cast<ST_RefA*>(target()); }
			void read_value(const xstring& val);
		};

		class ST_Formula_reader : public ST_Xstring_reader
		{
		protected:
			ST_Formula* t() { return static_cast<ST_Formula*>(target()); }
		};

		class ST_Sqref_reader : public ST_Ref_reader
		{
		protected:
			ST_Sqref* t() { return static_cast<ST_Sqref*>(target()); }
		};

		class ST_UnsignedShortHex_reader : public type_reader
		{
		protected:
			ST_UnsignedShortHex* t() { return static_cast<ST_UnsignedShortHex*>(target()); }
			void read_value(const xstring& val);
		};

	}
}
#endif

