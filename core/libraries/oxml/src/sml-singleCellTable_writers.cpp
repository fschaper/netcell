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


#include "sml-singleCellTable_writers.hpp"
#include "sml-singleCellTable_literals.hpp"

namespace spreadsheetml
{
	namespace xio
	{
		void CT_XmlPr_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_singleCellTable_mapId_literal, context()->serialize(t()->mapId));
			w.attribute(0, sml_singleCellTable_xpath_literal, context()->serialize(t()->xpath));
			w.attribute(0, sml_singleCellTable_xmlDataType_literal, context()->serialize(t()->xmlDataType));
			if (t()->extLst.present()) {
				w.start_element(0, sml_singleCellTable_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_singleCellTable_extLst_literal);
			}
		}

		void CT_XmlCellPr_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_singleCellTable_id_literal, context()->serialize(t()->id));
			if (t()->uniqueName.present())
				w.attribute(0, sml_singleCellTable_uniqueName_literal, context()->serialize(t()->uniqueName.get()));
			w.start_element(0, sml_singleCellTable_xmlPr_literal);
			_xmlPr_writer.get_writer(context(), &t()->xmlPr)->write_target_to(w);
			w.end_element(0, sml_singleCellTable_xmlPr_literal);
			if (t()->extLst.present()) {
				w.start_element(0, sml_singleCellTable_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_singleCellTable_extLst_literal);
			}
		}

		void CT_SingleXmlCell_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_singleCellTable_id_literal, context()->serialize(t()->id));
			w.attribute(0, sml_singleCellTable_r_literal, context()->serialize(t()->r));
			w.attribute(0, sml_singleCellTable_connectionId_literal, context()->serialize(t()->connectionId));
			w.start_element(0, sml_singleCellTable_xmlCellPr_literal);
			_xmlCellPr_writer.get_writer(context(), &t()->xmlCellPr)->write_target_to(w);
			w.end_element(0, sml_singleCellTable_xmlCellPr_literal);
			if (t()->extLst.present()) {
				w.start_element(0, sml_singleCellTable_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_singleCellTable_extLst_literal);
			}
		}

		void CT_SingleXmlCells_writer::write_target_to(xml_writer& w) {
			for (size_t sqi = 0; sqi<t()->singleXmlCell.size(); ++sqi) {
				w.start_element(0, sml_singleCellTable_singleXmlCell_literal);
				_singleXmlCell_writer.get_writer(context(), &t()->singleXmlCell[sqi])->write_target_to(w);
				w.end_element(0, sml_singleCellTable_singleXmlCell_literal);
			}
		}

		void sml_singleCellTable_writer::write_target_to(xml_writer& w) {
			if (t()->singleXmlCells.present()) {
				w.start_element(0, sml_singleCellTable_singleXmlCells_literal);
					w.attribute(0, sml_singleCellTable_xmlns_literal, sml_singleCellTable_http_colon__slash__slash_schemas_dot_openxmlformats_dot_org_slash_spreadsheetml_slash_2006_slash_main_literal);
					w.attribute(sml_singleCellTable_xmlns_literal, sml_singleCellTable_xsd_literal, sml_singleCellTable_http_colon__slash__slash_www_dot_w3_dot_org_slash_2001_slash_XMLSchema_literal);
				_singleXmlCells_writer.get_writer(context(), &t()->singleXmlCells.get())->write_target_to(w);
				w.end_element(0, sml_singleCellTable_singleXmlCells_literal);
			}
		}

	}
}
