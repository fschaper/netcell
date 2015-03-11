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

#include "dml-picture_writers.hpp"
#include "dml-picture_literals.hpp"

namespace drawingml
{
	namespace xio
	{
//YLS: this was double generated
/*
		void CT_PictureNonVisual_writer::write_target_to(xml_writer& w) {
			w.start_element(0, dml_picture_cNvPr_literal);
			_cNvPr_writer.get_writer(context(), &t()->cNvPr)->write_target_to(w);
			w.end_element(0, dml_picture_cNvPr_literal);
			w.start_element(0, dml_picture_cNvPicPr_literal);
			_cNvPicPr_writer.get_writer(context(), &t()->cNvPicPr)->write_target_to(w);
			w.end_element(0, dml_picture_cNvPicPr_literal);
		}

		void CT_Picture_writer::write_target_to(xml_writer& w) {
			w.start_element(0, dml_picture_nvPicPr_literal);
			_nvPicPr_writer.get_writer(context(), &t()->nvPicPr)->write_target_to(w);
			w.end_element(0, dml_picture_nvPicPr_literal);
			w.start_element(0, dml_picture_blipFill_literal);
			_blipFill_writer.get_writer(context(), &t()->blipFill)->write_target_to(w);
			w.end_element(0, dml_picture_blipFill_literal);
			w.start_element(0, dml_picture_spPr_literal);
			_spPr_writer.get_writer(context(), &t()->spPr)->write_target_to(w);
			w.end_element(0, dml_picture_spPr_literal);
		} 
*/
		void dml_picture_writer::write_target_to(xml_writer& w) {
			if (t()->pic.present()) {
				w.start_element(0, dml_picture_pic_literal);
					w.attribute(0, dml_picture_xmlns_literal, dml_picture_http_colon__slash__slash_schemas_dot_openxmlformats_dot_org_slash_drawingml_slash_2006_slash_picture_literal);
					w.attribute(dml_picture_xmlns_literal, dml_picture_a_literal, dml_picture_http_colon__slash__slash_schemas_dot_openxmlformats_dot_org_slash_drawingml_slash_2006_slash_main_literal);
					w.attribute(dml_picture_xmlns_literal, dml_picture_xsd_literal, dml_picture_http_colon__slash__slash_www_dot_w3_dot_org_slash_2001_slash_XMLSchema_literal);
				_pic_writer.get_writer(context(), &t()->pic.get())->write_target_to(w);
				w.end_element(0, dml_picture_pic_literal);
			}
		}

	}
}
