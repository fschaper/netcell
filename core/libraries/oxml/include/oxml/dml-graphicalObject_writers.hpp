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

#ifndef DML_GRAPHICALOBJECT_WRITERS_HPP
#define DML_GRAPHICALOBJECT_WRITERS_HPP

#include "dml-graphicalObject.hpp"
#include "dml-graphicalObject_literals.hpp"
#include <xio/xml/binding/type_writer.hpp>

namespace drawingml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_GraphicalObjectData_writer;
		class CT_GraphicalObject_writer;
		class dml_graphicalObject_writer;

		class CT_GraphicalObjectData_writer : public type_writer
		{
			CT_GraphicalObjectData* t() { return static_cast<CT_GraphicalObjectData*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_GraphicalObject_writer : public type_writer
		{
			auto_type_writer< CT_GraphicalObjectData_writer > _graphicData_writer;
			CT_GraphicalObject* t() { return static_cast<CT_GraphicalObject*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class dml_graphicalObject_writer : public type_writer
		{
			auto_type_writer< CT_GraphicalObject_writer > _graphic_writer;
			dml_graphicalObject* t() { return static_cast<dml_graphicalObject*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

	}
}
#endif

