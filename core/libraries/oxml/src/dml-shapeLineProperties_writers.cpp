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


#include "dml-shapeLineProperties_writers.hpp"
#include "dml-shapeLineProperties_literals.hpp"

namespace drawingml
{
	namespace xio
	{
		void CT_PresetLineDashProperties_writer::write_target_to(xml_writer& w) {
			if (t()->val.present())
				w.attribute(0, dml_shapeLineProperties_val_literal, context()->serialize(t()->val.get()));
		}

		void CT_DashStop_writer::write_target_to(xml_writer& w) {
			w.attribute(0, dml_shapeLineProperties_d_literal, context()->serialize(t()->d));
			w.attribute(0, dml_shapeLineProperties_sp_literal, context()->serialize(t()->sp));
		}

		void CT_DashStopList_writer::write_target_to(xml_writer& w) {
			for (size_t sqi = 0; sqi<t()->ds.size(); ++sqi) {
				w.start_element(0, dml_shapeLineProperties_ds_literal);
				_ds_writer.get_writer(context(), &t()->ds[sqi])->write_target_to(w);
				w.end_element(0, dml_shapeLineProperties_ds_literal);
			}
		}

		void CT_LineJoinRound_writer::write_target_to(xml_writer& w) {
		}

		void CT_LineJoinBevel_writer::write_target_to(xml_writer& w) {
		}

		void CT_LineJoinMiterProperties_writer::write_target_to(xml_writer& w) {
			if (t()->lim.present())
				w.attribute(0, dml_shapeLineProperties_lim_literal, context()->serialize(t()->lim.get()));
		}

		void CT_LineEndProperties_writer::write_target_to(xml_writer& w) {
			if (t()->type.present())
				w.attribute(0, dml_shapeLineProperties_type_literal, context()->serialize(t()->type.get()));
			if (t()->w.present())
				w.attribute(0, dml_shapeLineProperties_w_literal, context()->serialize(t()->w.get()));
			if (t()->len.present())
				w.attribute(0, dml_shapeLineProperties_len_literal, context()->serialize(t()->len.get()));
		}

		void ST_LineWidth_writer::write_target_to(xml_writer& w) {
			ST_Coordinate32_writer::write_target_to(w);
		}

		void CT_LineProperties_writer::write_target_to(xml_writer& w) {
			if (t()->w.present())
				w.attribute(0, dml_shapeLineProperties_w_literal, context()->serialize(t()->w.get()));
			if (t()->cap.present())
				w.attribute(0, dml_shapeLineProperties_cap_literal, context()->serialize(t()->cap.get()));
			if (t()->cmpd.present())
				w.attribute(0, dml_shapeLineProperties_cmpd_literal, context()->serialize(t()->cmpd.get()));
			if (t()->algn.present())
				w.attribute(0, dml_shapeLineProperties_algn_literal, context()->serialize(t()->algn.get()));
			if (t()->noFill.present()) {
				w.start_element(0, dml_shapeLineProperties_noFill_literal);
				_noFill_writer.get_writer(context(), &t()->noFill.get())->write_target_to(w);
				w.end_element(0, dml_shapeLineProperties_noFill_literal);
			}
			if (t()->solidFill.present()) {
				w.start_element(0, dml_shapeLineProperties_solidFill_literal);
				_solidFill_writer.get_writer(context(), &t()->solidFill.get())->write_target_to(w);
				w.end_element(0, dml_shapeLineProperties_solidFill_literal);
			}
			if (t()->gradFill.present()) {
				w.start_element(0, dml_shapeLineProperties_gradFill_literal);
				_gradFill_writer.get_writer(context(), &t()->gradFill.get())->write_target_to(w);
				w.end_element(0, dml_shapeLineProperties_gradFill_literal);
			}
			if (t()->pattFill.present()) {
				w.start_element(0, dml_shapeLineProperties_pattFill_literal);
				_pattFill_writer.get_writer(context(), &t()->pattFill.get())->write_target_to(w);
				w.end_element(0, dml_shapeLineProperties_pattFill_literal);
			}
			if (t()->prstDash.present()) {
				w.start_element(0, dml_shapeLineProperties_prstDash_literal);
				_prstDash_writer.get_writer(context(), &t()->prstDash.get())->write_target_to(w);
				w.end_element(0, dml_shapeLineProperties_prstDash_literal);
			}
			if (t()->custDash.present()) {
				w.start_element(0, dml_shapeLineProperties_custDash_literal);
				_custDash_writer.get_writer(context(), &t()->custDash.get())->write_target_to(w);
				w.end_element(0, dml_shapeLineProperties_custDash_literal);
			}
			if (t()->round.present()) {
				w.start_element(0, dml_shapeLineProperties_round_literal);
				_round_writer.get_writer(context(), &t()->round.get())->write_target_to(w);
				w.end_element(0, dml_shapeLineProperties_round_literal);
			}
			if (t()->bevel.present()) {
				w.start_element(0, dml_shapeLineProperties_bevel_literal);
				_bevel_writer.get_writer(context(), &t()->bevel.get())->write_target_to(w);
				w.end_element(0, dml_shapeLineProperties_bevel_literal);
			}
			if (t()->miter.present()) {
				w.start_element(0, dml_shapeLineProperties_miter_literal);
				_miter_writer.get_writer(context(), &t()->miter.get())->write_target_to(w);
				w.end_element(0, dml_shapeLineProperties_miter_literal);
			}
			if (t()->headEnd.present()) {
				w.start_element(0, dml_shapeLineProperties_headEnd_literal);
				_headEnd_writer.get_writer(context(), &t()->headEnd.get())->write_target_to(w);
				w.end_element(0, dml_shapeLineProperties_headEnd_literal);
			}
			if (t()->tailEnd.present()) {
				w.start_element(0, dml_shapeLineProperties_tailEnd_literal);
				_tailEnd_writer.get_writer(context(), &t()->tailEnd.get())->write_target_to(w);
				w.end_element(0, dml_shapeLineProperties_tailEnd_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, dml_shapeLineProperties_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, dml_shapeLineProperties_extLst_literal);
			}
		}

	}
}
