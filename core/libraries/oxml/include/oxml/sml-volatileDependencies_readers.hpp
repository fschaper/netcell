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

#ifndef SML_VOLATILEDEPENDENCIES_READERS_HPP
#define SML_VOLATILEDEPENDENCIES_READERS_HPP

#include "sml-volatileDependencies.hpp"
#include "sml-baseTypes_readers.hpp"

namespace spreadsheetml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_VolTopicRef_reader;
		class CT_VolTopic_reader;
		class CT_VolMain_reader;
		class CT_VolType_reader;
		class CT_VolTypes_reader;
		class sml_volatileDependencies_reader;

		class CT_VolTopicRef_reader : public type_reader
		{
		protected:
			CT_VolTopicRef* t() { return static_cast<CT_VolTopicRef*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_VolTopic_reader : public type_reader
		{
			auto_type_reader< ST_Xstring_reader > _v_reader;
			auto_type_reader< ST_Xstring_reader > _stp_reader;
			auto_type_reader< CT_VolTopicRef_reader > _tr_reader;
		protected:
			CT_VolTopic* t() { return static_cast<CT_VolTopic*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_VolMain_reader : public type_reader
		{
			auto_type_reader< CT_VolTopic_reader > _tp_reader;
		protected:
			CT_VolMain* t() { return static_cast<CT_VolMain*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_VolType_reader : public type_reader
		{
			auto_type_reader< CT_VolMain_reader > _main_reader;
		protected:
			CT_VolType* t() { return static_cast<CT_VolType*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_VolTypes_reader : public type_reader
		{
			auto_type_reader< CT_VolType_reader > _volType_reader;
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_VolTypes* t() { return static_cast<CT_VolTypes*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class sml_volatileDependencies_reader : public type_reader
		{
			auto_type_reader< CT_VolTypes_reader > _volTypes_reader;
		protected:
			sml_volatileDependencies* t() { return static_cast<sml_volatileDependencies*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

	}
}
#endif

