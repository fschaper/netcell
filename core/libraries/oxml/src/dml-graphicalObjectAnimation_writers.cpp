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

#include "dml-graphicalObjectAnimation_writers.hpp"
#include "dml-graphicalObjectAnimation_literals.hpp"

namespace drawingml
{
	namespace xio
	{
		void CT_AnimationDgmElement_writer::write_target_to(xml_writer& w) {
            //TODO: YLS "fixed the uncomplete GUID type by downgrading it to a string
			if (t()->id != "{00000000-0000-0000-0000-000000000000}")
				w.attribute(0, dml_graphicalObjectAnimation_id_literal, context()->serialize(t()->id));
			if (t()->bldStep != ST_DgmBuildStep::sp_literal)
				w.attribute(0, dml_graphicalObjectAnimation_bldStep_literal, context()->serialize(t()->bldStep));
		}

		void CT_AnimationChartElement_writer::write_target_to(xml_writer& w) {
			if (t()->seriesIdx != -1)
				w.attribute(0, dml_graphicalObjectAnimation_seriesIdx_literal, context()->serialize(t()->seriesIdx));
			if (t()->categoryIdx != -1)
				w.attribute(0, dml_graphicalObjectAnimation_categoryIdx_literal, context()->serialize(t()->categoryIdx));
			w.attribute(0, dml_graphicalObjectAnimation_bldStep_literal, context()->serialize(t()->bldStep));
		}

		void CT_AnimationElementChoice_writer::write_target_to(xml_writer& w) {
			if (t()->dgm.present()) {
				w.start_element(0, dml_graphicalObjectAnimation_dgm_literal);
				_dgm_writer.get_writer(context(), &t()->dgm.get())->write_target_to(w);
				w.end_element(0, dml_graphicalObjectAnimation_dgm_literal);
			}
			if (t()->chart.present()) {
				w.start_element(0, dml_graphicalObjectAnimation_chart_literal);
				_chart_writer.get_writer(context(), &t()->chart.get())->write_target_to(w);
				w.end_element(0, dml_graphicalObjectAnimation_chart_literal);
			}
		}

		void ST_AnimationDgmBuildType_writer::write_target_to(xml_writer& w) {
			w.write_element_value(context()->serialize(*t()));
		}

		void CT_AnimationDgmBuildProperties_writer::write_target_to(xml_writer& w) {
			if (t()->bld != "allAtOnce")
				w.attribute(0, dml_graphicalObjectAnimation_bld_literal, context()->serialize(t()->bld));
			if (t()->rev != false)
				w.attribute(0, dml_graphicalObjectAnimation_rev_literal, context()->serialize(t()->rev));
		}

		void ST_AnimationChartBuildType_writer::write_target_to(xml_writer& w) {
			w.write_element_value(context()->serialize(*t()));
		}

		void CT_AnimationChartBuildProperties_writer::write_target_to(xml_writer& w) {
			if (t()->bld != "allAtOnce")
				w.attribute(0, dml_graphicalObjectAnimation_bld_literal, context()->serialize(t()->bld));
			if (t()->animBg != true)
				w.attribute(0, dml_graphicalObjectAnimation_animBg_literal, context()->serialize(t()->animBg));
		}

		void CT_AnimationGraphicalObjectBuildProperties_writer::write_target_to(xml_writer& w) {
			if (t()->bldDgm.present()) {
				w.start_element(0, dml_graphicalObjectAnimation_bldDgm_literal);
				_bldDgm_writer.get_writer(context(), &t()->bldDgm.get())->write_target_to(w);
				w.end_element(0, dml_graphicalObjectAnimation_bldDgm_literal);
			}
			if (t()->bldChart.present()) {
				w.start_element(0, dml_graphicalObjectAnimation_bldChart_literal);
				_bldChart_writer.get_writer(context(), &t()->bldChart.get())->write_target_to(w);
				w.end_element(0, dml_graphicalObjectAnimation_bldChart_literal);
			}
		}

	}
}
