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


#include "dml-styleDefaults_writers.hpp"
#include "dml-styleDefaults_literals.hpp"

namespace drawingml
{
	namespace xio
	{
		void CT_DefaultShapeDefinition_writer::write_target_to(xml_writer& w) {
			w.start_element(0, dml_styleDefaults_spPr_literal);
			_spPr_writer.get_writer(context(), &t()->spPr)->write_target_to(w);
			w.end_element(0, dml_styleDefaults_spPr_literal);
			w.start_element(0, dml_styleDefaults_bodyPr_literal);
			_bodyPr_writer.get_writer(context(), &t()->bodyPr)->write_target_to(w);
			w.end_element(0, dml_styleDefaults_bodyPr_literal);
			w.start_element(0, dml_styleDefaults_lstStyle_literal);
			_lstStyle_writer.get_writer(context(), &t()->lstStyle)->write_target_to(w);
			w.end_element(0, dml_styleDefaults_lstStyle_literal);
			if (t()->style.present()) {
				w.start_element(0, dml_styleDefaults_style_literal);
				_style_writer.get_writer(context(), &t()->style.get())->write_target_to(w);
				w.end_element(0, dml_styleDefaults_style_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, dml_styleDefaults_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, dml_styleDefaults_extLst_literal);
			}
		}

		void CT_ObjectStyleDefaults_writer::write_target_to(xml_writer& w) {
			if (t()->spDef.present()) {
				w.start_element(0, dml_styleDefaults_spDef_literal);
				_spDef_writer.get_writer(context(), &t()->spDef.get())->write_target_to(w);
				w.end_element(0, dml_styleDefaults_spDef_literal);
			}
			if (t()->lnDef.present()) {
				w.start_element(0, dml_styleDefaults_lnDef_literal);
				_lnDef_writer.get_writer(context(), &t()->lnDef.get())->write_target_to(w);
				w.end_element(0, dml_styleDefaults_lnDef_literal);
			}
			if (t()->txDef.present()) {
				w.start_element(0, dml_styleDefaults_txDef_literal);
				_txDef_writer.get_writer(context(), &t()->txDef.get())->write_target_to(w);
				w.end_element(0, dml_styleDefaults_txDef_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, dml_styleDefaults_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, dml_styleDefaults_extLst_literal);
			}
		}

	}
}
