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


#include "dml-shapeStyle_writers.hpp"
#include "dml-shapeStyle_literals.hpp"

namespace drawingml
{
	namespace xio
	{
		void CT_StyleMatrixReference_writer::write_target_to(xml_writer& w) {
			w.attribute(0, dml_shapeStyle_idx_literal, context()->serialize(t()->idx));
			if (t()->scrgbClr.present()) {
				w.start_element(0, dml_shapeStyle_scrgbClr_literal);
				_scrgbClr_writer.get_writer(context(), &t()->scrgbClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeStyle_scrgbClr_literal);
			}
			if (t()->srgbClr.present()) {
				w.start_element(0, dml_shapeStyle_srgbClr_literal);
				_srgbClr_writer.get_writer(context(), &t()->srgbClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeStyle_srgbClr_literal);
			}
			if (t()->hslClr.present()) {
				w.start_element(0, dml_shapeStyle_hslClr_literal);
				_hslClr_writer.get_writer(context(), &t()->hslClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeStyle_hslClr_literal);
			}
			if (t()->sysClr.present()) {
				w.start_element(0, dml_shapeStyle_sysClr_literal);
				_sysClr_writer.get_writer(context(), &t()->sysClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeStyle_sysClr_literal);
			}
			if (t()->schemeClr.present()) {
				w.start_element(0, dml_shapeStyle_schemeClr_literal);
				_schemeClr_writer.get_writer(context(), &t()->schemeClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeStyle_schemeClr_literal);
			}
			if (t()->prstClr.present()) {
				w.start_element(0, dml_shapeStyle_prstClr_literal);
				_prstClr_writer.get_writer(context(), &t()->prstClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeStyle_prstClr_literal);
			}
		}

		void CT_FontReference_writer::write_target_to(xml_writer& w) {
			w.attribute(0, dml_shapeStyle_idx_literal, context()->serialize(t()->idx));
			if (t()->scrgbClr.present()) {
				w.start_element(0, dml_shapeStyle_scrgbClr_literal);
				_scrgbClr_writer.get_writer(context(), &t()->scrgbClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeStyle_scrgbClr_literal);
			}
			if (t()->srgbClr.present()) {
				w.start_element(0, dml_shapeStyle_srgbClr_literal);
				_srgbClr_writer.get_writer(context(), &t()->srgbClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeStyle_srgbClr_literal);
			}
			if (t()->hslClr.present()) {
				w.start_element(0, dml_shapeStyle_hslClr_literal);
				_hslClr_writer.get_writer(context(), &t()->hslClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeStyle_hslClr_literal);
			}
			if (t()->sysClr.present()) {
				w.start_element(0, dml_shapeStyle_sysClr_literal);
				_sysClr_writer.get_writer(context(), &t()->sysClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeStyle_sysClr_literal);
			}
			if (t()->schemeClr.present()) {
				w.start_element(0, dml_shapeStyle_schemeClr_literal);
				_schemeClr_writer.get_writer(context(), &t()->schemeClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeStyle_schemeClr_literal);
			}
			if (t()->prstClr.present()) {
				w.start_element(0, dml_shapeStyle_prstClr_literal);
				_prstClr_writer.get_writer(context(), &t()->prstClr.get())->write_target_to(w);
				w.end_element(0, dml_shapeStyle_prstClr_literal);
			}
		}

		void CT_ShapeStyle_writer::write_target_to(xml_writer& w) {
			w.start_element(0, dml_shapeStyle_lnRef_literal);
			_lnRef_writer.get_writer(context(), &t()->lnRef)->write_target_to(w);
			w.end_element(0, dml_shapeStyle_lnRef_literal);
			w.start_element(0, dml_shapeStyle_fillRef_literal);
			_fillRef_writer.get_writer(context(), &t()->fillRef)->write_target_to(w);
			w.end_element(0, dml_shapeStyle_fillRef_literal);
			w.start_element(0, dml_shapeStyle_effectRef_literal);
			_effectRef_writer.get_writer(context(), &t()->effectRef)->write_target_to(w);
			w.end_element(0, dml_shapeStyle_effectRef_literal);
			w.start_element(0, dml_shapeStyle_fontRef_literal);
			_fontRef_writer.get_writer(context(), &t()->fontRef)->write_target_to(w);
			w.end_element(0, dml_shapeStyle_fontRef_literal);
		}

	}
}
