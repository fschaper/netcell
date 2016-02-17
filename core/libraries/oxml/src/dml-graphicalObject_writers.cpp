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

#include "dml-graphicalObject_writers.hpp"
#include "dml-graphicalObject_literals.hpp"

namespace drawingml
{
	namespace xio
	{
		void CT_GraphicalObjectData_writer::write_target_to(xml_writer& w) {
			if (t()->uri.present())
				w.attribute(0, dml_graphicalObject_uri_literal, context()->serialize(t()->uri.get()));
		}

		void CT_GraphicalObject_writer::write_target_to(xml_writer& w) {
			w.start_element(0, dml_graphicalObject_graphicData_literal);
			_graphicData_writer.get_writer(context(), &t()->graphicData)->write_target_to(w);
			w.end_element(0, dml_graphicalObject_graphicData_literal);
		}

		void dml_graphicalObject_writer::write_target_to(xml_writer& w) {
			if (t()->graphic.present()) {
				w.start_element(0, dml_graphicalObject_graphic_literal);
					w.attribute(0, dml_graphicalObject_xmlns_literal, dml_graphicalObject_http_colon__slash__slash_schemas_dot_openxmlformats_dot_org_slash_drawingml_slash_2006_slash_main_literal);
					w.attribute(dml_graphicalObject_xmlns_literal, dml_graphicalObject_xsd_literal, dml_graphicalObject_http_colon__slash__slash_www_dot_w3_dot_org_slash_2001_slash_XMLSchema_literal);
				_graphic_writer.get_writer(context(), &t()->graphic.get())->write_target_to(w);
				w.end_element(0, dml_graphicalObject_graphic_literal);
			}
		}

	}
}
