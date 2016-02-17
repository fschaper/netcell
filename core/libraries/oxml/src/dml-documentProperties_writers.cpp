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

#include "dml-documentProperties_writers.hpp"
#include "dml-documentProperties_literals.hpp"

namespace drawingml
{
	namespace xio
	{
		void CT_NonVisualDrawingProps_writer::write_target_to(xml_writer& w) {
			w.attribute(0, dml_documentProperties_id_literal, context()->serialize(t()->id));
			w.attribute(0, dml_documentProperties_name_literal, context()->serialize(t()->name));
			if (t()->descr != "")
				w.attribute(0, dml_documentProperties_descr_literal, context()->serialize(t()->descr));
			if (t()->hidden != false)
				w.attribute(0, dml_documentProperties_hidden_literal, context()->serialize(t()->hidden));
			if (t()->hlinkClick.present()) {
				XMLCh ns[2]; ns[0] = 'a';ns[1] = 0;
				w.start_element(ns, dml_documentProperties_hlinkClick_literal);
				_hlinkClick_writer.get_writer(context(), &t()->hlinkClick.get())->write_target_to(w);
				w.end_element(0, dml_documentProperties_hlinkClick_literal);
			}
			if (t()->hlinkHover.present()) {
				w.start_element(0, dml_documentProperties_hlinkHover_literal);
				_hlinkHover_writer.get_writer(context(), &t()->hlinkHover.get())->write_target_to(w);
				w.end_element(0, dml_documentProperties_hlinkHover_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, dml_documentProperties_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, dml_documentProperties_extLst_literal);
			}
		}

		void CT_ShapeLocking_writer::write_target_to(xml_writer& w) {
			if (t()->noGrp != false)
				w.attribute(0, dml_documentProperties_noGrp_literal, context()->serialize(t()->noGrp));
			if (t()->noSelect != false)
				w.attribute(0, dml_documentProperties_noSelect_literal, context()->serialize(t()->noSelect));
			if (t()->noRot != false)
				w.attribute(0, dml_documentProperties_noRot_literal, context()->serialize(t()->noRot));
			if (t()->noChangeAspect != false)
				w.attribute(0, dml_documentProperties_noChangeAspect_literal, context()->serialize(t()->noChangeAspect));
			if (t()->noMove != false)
				w.attribute(0, dml_documentProperties_noMove_literal, context()->serialize(t()->noMove));
			if (t()->noResize != false)
				w.attribute(0, dml_documentProperties_noResize_literal, context()->serialize(t()->noResize));
			if (t()->noEditPoints != false)
				w.attribute(0, dml_documentProperties_noEditPoints_literal, context()->serialize(t()->noEditPoints));
			if (t()->noAdjustHandles != false)
				w.attribute(0, dml_documentProperties_noAdjustHandles_literal, context()->serialize(t()->noAdjustHandles));
			if (t()->noChangeArrowheads != false)
				w.attribute(0, dml_documentProperties_noChangeArrowheads_literal, context()->serialize(t()->noChangeArrowheads));
			if (t()->noChangeShapeType != false)
				w.attribute(0, dml_documentProperties_noChangeShapeType_literal, context()->serialize(t()->noChangeShapeType));
			if (t()->noTextEdit != false)
				w.attribute(0, dml_documentProperties_noTextEdit_literal, context()->serialize(t()->noTextEdit));
			if (t()->extLst.present()) {
				w.start_element(0, dml_documentProperties_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, dml_documentProperties_extLst_literal);
			}
		}

		void CT_NonVisualDrawingShapeProps_writer::write_target_to(xml_writer& w) {
			if (t()->txBox != false)
				w.attribute(0, dml_documentProperties_txBox_literal, context()->serialize(t()->txBox));
			if (t()->spLocks.present()) {
				w.start_element(0, dml_documentProperties_spLocks_literal);
				_spLocks_writer.get_writer(context(), &t()->spLocks.get())->write_target_to(w);
				w.end_element(0, dml_documentProperties_spLocks_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, dml_documentProperties_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, dml_documentProperties_extLst_literal);
			}
		}

		void CT_GroupLocking_writer::write_target_to(xml_writer& w) {
			if (t()->noGrp != false)
				w.attribute(0, dml_documentProperties_noGrp_literal, context()->serialize(t()->noGrp));
			if (t()->noUngrp != false)
				w.attribute(0, dml_documentProperties_noUngrp_literal, context()->serialize(t()->noUngrp));
			if (t()->noSelect != false)
				w.attribute(0, dml_documentProperties_noSelect_literal, context()->serialize(t()->noSelect));
			if (t()->noRot != false)
				w.attribute(0, dml_documentProperties_noRot_literal, context()->serialize(t()->noRot));
			if (t()->noChangeAspect != false)
				w.attribute(0, dml_documentProperties_noChangeAspect_literal, context()->serialize(t()->noChangeAspect));
			if (t()->noMove != false)
				w.attribute(0, dml_documentProperties_noMove_literal, context()->serialize(t()->noMove));
			if (t()->noResize != false)
				w.attribute(0, dml_documentProperties_noResize_literal, context()->serialize(t()->noResize));
			if (t()->extLst.present()) {
				w.start_element(0, dml_documentProperties_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, dml_documentProperties_extLst_literal);
			}
		}

		void CT_NonVisualGroupDrawingShapeProps_writer::write_target_to(xml_writer& w) {
			if (t()->grpSpLocks.present()) {
				w.start_element(0, dml_documentProperties_grpSpLocks_literal);
				_grpSpLocks_writer.get_writer(context(), &t()->grpSpLocks.get())->write_target_to(w);
				w.end_element(0, dml_documentProperties_grpSpLocks_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, dml_documentProperties_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, dml_documentProperties_extLst_literal);
			}
		}

		void CT_GraphicalObjectFrameLocking_writer::write_target_to(xml_writer& w) {
			if (t()->noGrp != false)
				w.attribute(0, dml_documentProperties_noGrp_literal, context()->serialize(t()->noGrp));
			if (t()->noDrilldown != false)
				w.attribute(0, dml_documentProperties_noDrilldown_literal, context()->serialize(t()->noDrilldown));
			if (t()->noSelect != false)
				w.attribute(0, dml_documentProperties_noSelect_literal, context()->serialize(t()->noSelect));
			if (t()->noChangeAspect != false)
				w.attribute(0, dml_documentProperties_noChangeAspect_literal, context()->serialize(t()->noChangeAspect));
			if (t()->noMove != false)
				w.attribute(0, dml_documentProperties_noMove_literal, context()->serialize(t()->noMove));
			if (t()->noResize != false)
				w.attribute(0, dml_documentProperties_noResize_literal, context()->serialize(t()->noResize));
			if (t()->extLst.present()) {
				w.start_element(0, dml_documentProperties_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, dml_documentProperties_extLst_literal);
			}
		}

		void CT_NonVisualGraphicFrameProperties_writer::write_target_to(xml_writer& w) {
			if (t()->graphicFrameLocks.present()) {
				w.start_element(0, dml_documentProperties_graphicFrameLocks_literal);
				_graphicFrameLocks_writer.get_writer(context(), &t()->graphicFrameLocks.get())->write_target_to(w);
				w.end_element(0, dml_documentProperties_graphicFrameLocks_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, dml_documentProperties_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, dml_documentProperties_extLst_literal);
			}
		}

		void CT_ConnectorLocking_writer::write_target_to(xml_writer& w) {
			if (t()->noGrp != false)
				w.attribute(0, dml_documentProperties_noGrp_literal, context()->serialize(t()->noGrp));
			if (t()->noSelect != false)
				w.attribute(0, dml_documentProperties_noSelect_literal, context()->serialize(t()->noSelect));
			if (t()->noRot != false)
				w.attribute(0, dml_documentProperties_noRot_literal, context()->serialize(t()->noRot));
			if (t()->noChangeAspect != false)
				w.attribute(0, dml_documentProperties_noChangeAspect_literal, context()->serialize(t()->noChangeAspect));
			if (t()->noMove != false)
				w.attribute(0, dml_documentProperties_noMove_literal, context()->serialize(t()->noMove));
			if (t()->noResize != false)
				w.attribute(0, dml_documentProperties_noResize_literal, context()->serialize(t()->noResize));
			if (t()->noEditPoints != false)
				w.attribute(0, dml_documentProperties_noEditPoints_literal, context()->serialize(t()->noEditPoints));
			if (t()->noAdjustHandles != false)
				w.attribute(0, dml_documentProperties_noAdjustHandles_literal, context()->serialize(t()->noAdjustHandles));
			if (t()->noChangeArrowheads != false)
				w.attribute(0, dml_documentProperties_noChangeArrowheads_literal, context()->serialize(t()->noChangeArrowheads));
			if (t()->noChangeShapeType != false)
				w.attribute(0, dml_documentProperties_noChangeShapeType_literal, context()->serialize(t()->noChangeShapeType));
			if (t()->extLst.present()) {
				w.start_element(0, dml_documentProperties_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, dml_documentProperties_extLst_literal);
			}
		}

		void CT_NonVisualConnectorProperties_writer::write_target_to(xml_writer& w) {
			if (t()->cxnSpLocks.present()) {
				w.start_element(0, dml_documentProperties_cxnSpLocks_literal);
				_cxnSpLocks_writer.get_writer(context(), &t()->cxnSpLocks.get())->write_target_to(w);
				w.end_element(0, dml_documentProperties_cxnSpLocks_literal);
			}
			if (t()->stCxn.present()) {
				w.start_element(0, dml_documentProperties_stCxn_literal);
				_stCxn_writer.get_writer(context(), &t()->stCxn.get())->write_target_to(w);
				w.end_element(0, dml_documentProperties_stCxn_literal);
			}
			if (t()->endCxn.present()) {
				w.start_element(0, dml_documentProperties_endCxn_literal);
				_endCxn_writer.get_writer(context(), &t()->endCxn.get())->write_target_to(w);
				w.end_element(0, dml_documentProperties_endCxn_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, dml_documentProperties_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, dml_documentProperties_extLst_literal);
			}
		}

		void CT_PictureLocking_writer::write_target_to(xml_writer& w) {
			if (t()->noGrp != false)
				w.attribute(0, dml_documentProperties_noGrp_literal, context()->serialize(t()->noGrp));
			if (t()->noSelect != false)
				w.attribute(0, dml_documentProperties_noSelect_literal, context()->serialize(t()->noSelect));
			if (t()->noRot != false)
				w.attribute(0, dml_documentProperties_noRot_literal, context()->serialize(t()->noRot));
			if (t()->noChangeAspect != false)
				w.attribute(0, dml_documentProperties_noChangeAspect_literal, context()->serialize(t()->noChangeAspect));
			if (t()->noMove != false)
				w.attribute(0, dml_documentProperties_noMove_literal, context()->serialize(t()->noMove));
			if (t()->noResize != false)
				w.attribute(0, dml_documentProperties_noResize_literal, context()->serialize(t()->noResize));
			if (t()->noEditPoints != false)
				w.attribute(0, dml_documentProperties_noEditPoints_literal, context()->serialize(t()->noEditPoints));
			if (t()->noAdjustHandles != false)
				w.attribute(0, dml_documentProperties_noAdjustHandles_literal, context()->serialize(t()->noAdjustHandles));
			if (t()->noChangeArrowheads != false)
				w.attribute(0, dml_documentProperties_noChangeArrowheads_literal, context()->serialize(t()->noChangeArrowheads));
			if (t()->noChangeShapeType != false)
				w.attribute(0, dml_documentProperties_noChangeShapeType_literal, context()->serialize(t()->noChangeShapeType));
			if (t()->noCrop != false)
				w.attribute(0, dml_documentProperties_noCrop_literal, context()->serialize(t()->noCrop));
			if (t()->extLst.present()) {
				w.start_element(0, dml_documentProperties_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, dml_documentProperties_extLst_literal);
			}
		}

		void CT_NonVisualPictureProperties_writer::write_target_to(xml_writer& w) {
			if (t()->preferRelativeResize != true)
				w.attribute(0, dml_documentProperties_preferRelativeResize_literal, context()->serialize(t()->preferRelativeResize));
			if (t()->picLocks.present()) {
                XMLCh ns[2]; ns[0] = 'a';ns[1] = 0;
				w.start_element(ns, dml_documentProperties_picLocks_literal);
				_picLocks_writer.get_writer(context(), &t()->picLocks.get())->write_target_to(w);
				w.end_element(0, dml_documentProperties_picLocks_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, dml_documentProperties_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, dml_documentProperties_extLst_literal);
			}
		}

	}
}
