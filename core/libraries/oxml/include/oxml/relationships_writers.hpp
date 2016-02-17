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

#ifndef RELATIONSHIPS_WRITERS_HPP
#define RELATIONSHIPS_WRITERS_HPP

#include "relationships.hpp"
#include "relationships_literals.hpp"
#include <xio/xml/binding/type_writer.hpp>

namespace rels_ns
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_Relationship_writer;
		class CT_Relationships_writer;
		class relationships_writer;

		class CT_Relationship_writer : public type_writer
		{
			CT_Relationship* t() { return static_cast<CT_Relationship*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Relationships_writer : public type_writer
		{
			auto_type_writer< CT_Relationship_writer > _Relationship_writer;
			CT_Relationships* t() { return static_cast<CT_Relationships*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class relationships_writer : public type_writer
		{
			auto_type_writer< CT_Relationships_writer > _Relationships_writer;
			relationships* t() { return static_cast<relationships*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

	}
}
#endif

