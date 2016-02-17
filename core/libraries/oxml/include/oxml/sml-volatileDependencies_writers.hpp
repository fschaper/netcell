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

#ifndef SML_VOLATILEDEPENDENCIES_WRITERS_HPP
#define SML_VOLATILEDEPENDENCIES_WRITERS_HPP

#include "sml-volatileDependencies.hpp"
#include "sml-volatileDependencies_literals.hpp"
#include "sml-baseTypes_writers.hpp"

namespace spreadsheetml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_VolTopicRef_writer;
		class CT_VolTopic_writer;
		class CT_VolMain_writer;
		class CT_VolType_writer;
		class CT_VolTypes_writer;
		class sml_volatileDependencies_writer;

		class CT_VolTopicRef_writer : public type_writer
		{
			CT_VolTopicRef* t() { return static_cast<CT_VolTopicRef*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_VolTopic_writer : public type_writer
		{
			auto_type_writer< ST_Xstring_writer > _v_writer;
			auto_type_writer< ST_Xstring_writer > _stp_writer;
			auto_type_writer< CT_VolTopicRef_writer > _tr_writer;
			CT_VolTopic* t() { return static_cast<CT_VolTopic*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_VolMain_writer : public type_writer
		{
			auto_type_writer< CT_VolTopic_writer > _tp_writer;
			CT_VolMain* t() { return static_cast<CT_VolMain*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_VolType_writer : public type_writer
		{
			auto_type_writer< CT_VolMain_writer > _main_writer;
			CT_VolType* t() { return static_cast<CT_VolType*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_VolTypes_writer : public type_writer
		{
			auto_type_writer< CT_VolType_writer > _volType_writer;
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_VolTypes* t() { return static_cast<CT_VolTypes*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class sml_volatileDependencies_writer : public type_writer
		{
			auto_type_writer< CT_VolTypes_writer > _volTypes_writer;
			sml_volatileDependencies* t() { return static_cast<sml_volatileDependencies*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

	}
}
#endif

