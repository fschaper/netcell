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

#include "dml-graphicalObjectFormat_writers.hpp"
#include "dml-graphicalObjectFormat_literals.hpp"

namespace drawingml
{
	namespace xio
	{
		void CT_BackgroundFormatting_writer::write_target_to(xml_writer& w) {
			if (t()->noFill.present()) {
				w.start_element(0, dml_graphicalObjectFormat_noFill_literal);
				_noFill_writer.get_writer(context(), &t()->noFill.get())->write_target_to(w);
				w.end_element(0, dml_graphicalObjectFormat_noFill_literal);
			}
			if (t()->solidFill.present()) {
				w.start_element(0, dml_graphicalObjectFormat_solidFill_literal);
				_solidFill_writer.get_writer(context(), &t()->solidFill.get())->write_target_to(w);
				w.end_element(0, dml_graphicalObjectFormat_solidFill_literal);
			}
			if (t()->gradFill.present()) {
				w.start_element(0, dml_graphicalObjectFormat_gradFill_literal);
				_gradFill_writer.get_writer(context(), &t()->gradFill.get())->write_target_to(w);
				w.end_element(0, dml_graphicalObjectFormat_gradFill_literal);
			}
			if (t()->blipFill.present()) {
				w.start_element(0, dml_graphicalObjectFormat_blipFill_literal);
				_blipFill_writer.get_writer(context(), &t()->blipFill.get())->write_target_to(w);
				w.end_element(0, dml_graphicalObjectFormat_blipFill_literal);
			}
			if (t()->pattFill.present()) {
				w.start_element(0, dml_graphicalObjectFormat_pattFill_literal);
				_pattFill_writer.get_writer(context(), &t()->pattFill.get())->write_target_to(w);
				w.end_element(0, dml_graphicalObjectFormat_pattFill_literal);
			}
			if (t()->grpFill.present()) {
				w.start_element(0, dml_graphicalObjectFormat_grpFill_literal);
				_grpFill_writer.get_writer(context(), &t()->grpFill.get())->write_target_to(w);
				w.end_element(0, dml_graphicalObjectFormat_grpFill_literal);
			}
			if (t()->effectLst.present()) {
				w.start_element(0, dml_graphicalObjectFormat_effectLst_literal);
				_effectLst_writer.get_writer(context(), &t()->effectLst.get())->write_target_to(w);
				w.end_element(0, dml_graphicalObjectFormat_effectLst_literal);
			}
			if (t()->effectDag.present()) {
				w.start_element(0, dml_graphicalObjectFormat_effectDag_literal);
				_effectDag_writer.get_writer(context(), &t()->effectDag.get())->write_target_to(w);
				w.end_element(0, dml_graphicalObjectFormat_effectDag_literal);
			}
		}

		void CT_WholeE2oFormatting_writer::write_target_to(xml_writer& w) {
			if (t()->ln.present()) {
				w.start_element(0, dml_graphicalObjectFormat_ln_literal);
				_ln_writer.get_writer(context(), &t()->ln.get())->write_target_to(w);
				w.end_element(0, dml_graphicalObjectFormat_ln_literal);
			}
			if (t()->effectLst.present()) {
				w.start_element(0, dml_graphicalObjectFormat_effectLst_literal);
				_effectLst_writer.get_writer(context(), &t()->effectLst.get())->write_target_to(w);
				w.end_element(0, dml_graphicalObjectFormat_effectLst_literal);
			}
			if (t()->effectDag.present()) {
				w.start_element(0, dml_graphicalObjectFormat_effectDag_literal);
				_effectDag_writer.get_writer(context(), &t()->effectDag.get())->write_target_to(w);
				w.end_element(0, dml_graphicalObjectFormat_effectDag_literal);
			}
		}

	}
}
