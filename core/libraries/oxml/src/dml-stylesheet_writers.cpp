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


#include "dml-stylesheet_writers.hpp"
#include "dml-stylesheet_literals.hpp"

namespace drawingml
{
	namespace xio
	{
		void CT_ColorMapping_writer::write_target_to(xml_writer& w) {
			w.attribute(0, dml_stylesheet_bg1_literal, context()->serialize(t()->bg1));
			w.attribute(0, dml_stylesheet_tx1_literal, context()->serialize(t()->tx1));
			w.attribute(0, dml_stylesheet_bg2_literal, context()->serialize(t()->bg2));
			w.attribute(0, dml_stylesheet_tx2_literal, context()->serialize(t()->tx2));
			w.attribute(0, dml_stylesheet_accent1_literal, context()->serialize(t()->accent1));
			w.attribute(0, dml_stylesheet_accent2_literal, context()->serialize(t()->accent2));
			w.attribute(0, dml_stylesheet_accent3_literal, context()->serialize(t()->accent3));
			w.attribute(0, dml_stylesheet_accent4_literal, context()->serialize(t()->accent4));
			w.attribute(0, dml_stylesheet_accent5_literal, context()->serialize(t()->accent5));
			w.attribute(0, dml_stylesheet_accent6_literal, context()->serialize(t()->accent6));
			w.attribute(0, dml_stylesheet_hlink_literal, context()->serialize(t()->hlink));
			w.attribute(0, dml_stylesheet_folHlink_literal, context()->serialize(t()->folHlink));
			if (t()->extLst.present()) {
				w.start_element(0, dml_stylesheet_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, dml_stylesheet_extLst_literal);
			}
		}

		void CT_ColorSchemeAndMapping_writer::write_target_to(xml_writer& w) {
			w.start_element(0, dml_stylesheet_clrScheme_literal);
			_clrScheme_writer.get_writer(context(), &t()->clrScheme)->write_target_to(w);
			w.end_element(0, dml_stylesheet_clrScheme_literal);
			if (t()->clrMap.present()) {
				w.start_element(0, dml_stylesheet_clrMap_literal);
				_clrMap_writer.get_writer(context(), &t()->clrMap.get())->write_target_to(w);
				w.end_element(0, dml_stylesheet_clrMap_literal);
			}
		}

		void CT_ColorSchemeList_writer::write_target_to(xml_writer& w) {
			for (size_t sqi = 0; sqi<t()->extraClrScheme.size(); ++sqi) {
				w.start_element(0, dml_stylesheet_extraClrScheme_literal);
				_extraClrScheme_writer.get_writer(context(), &t()->extraClrScheme[sqi])->write_target_to(w);
				w.end_element(0, dml_stylesheet_extraClrScheme_literal);
			}
		}

		void CT_OfficeStyleSheet_writer::write_target_to(xml_writer& w) {
			if (t()->name != "")
				w.attribute(0, dml_stylesheet_name_literal, context()->serialize(t()->name));
			w.start_element(0, dml_stylesheet_themeElements_literal);
			_themeElements_writer.get_writer(context(), &t()->themeElements)->write_target_to(w);
			w.end_element(0, dml_stylesheet_themeElements_literal);
			if (t()->objectDefaults.present()) {
				w.start_element(0, dml_stylesheet_objectDefaults_literal);
				_objectDefaults_writer.get_writer(context(), &t()->objectDefaults.get())->write_target_to(w);
				w.end_element(0, dml_stylesheet_objectDefaults_literal);
			}
			if (t()->extraClrSchemeLst.present()) {
				w.start_element(0, dml_stylesheet_extraClrSchemeLst_literal);
				_extraClrSchemeLst_writer.get_writer(context(), &t()->extraClrSchemeLst.get())->write_target_to(w);
				w.end_element(0, dml_stylesheet_extraClrSchemeLst_literal);
			}
			if (t()->custClrLst.present()) {
				w.start_element(0, dml_stylesheet_custClrLst_literal);
				_custClrLst_writer.get_writer(context(), &t()->custClrLst.get())->write_target_to(w);
				w.end_element(0, dml_stylesheet_custClrLst_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, dml_stylesheet_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, dml_stylesheet_extLst_literal);
			}
		}

		void CT_BaseStylesOverride_writer::write_target_to(xml_writer& w) {
			if (t()->clrScheme.present()) {
				w.start_element(0, dml_stylesheet_clrScheme_literal);
				_clrScheme_writer.get_writer(context(), &t()->clrScheme.get())->write_target_to(w);
				w.end_element(0, dml_stylesheet_clrScheme_literal);
			}
			if (t()->fontScheme.present()) {
				w.start_element(0, dml_stylesheet_fontScheme_literal);
				_fontScheme_writer.get_writer(context(), &t()->fontScheme.get())->write_target_to(w);
				w.end_element(0, dml_stylesheet_fontScheme_literal);
			}
			if (t()->fmtScheme.present()) {
				w.start_element(0, dml_stylesheet_fmtScheme_literal);
				_fmtScheme_writer.get_writer(context(), &t()->fmtScheme.get())->write_target_to(w);
				w.end_element(0, dml_stylesheet_fmtScheme_literal);
			}
		}

		void CT_EmptyElement_writer::write_target_to(xml_writer& w) {
		}

		void dml_stylesheet_writer::write_target_to(xml_writer& w) {
			if (t()->theme.present()) {
				w.start_element(0, dml_stylesheet_theme_literal);
					w.attribute(0, dml_stylesheet_xmlns_literal, dml_stylesheet_http_colon__slash__slash_schemas_dot_openxmlformats_dot_org_slash_drawingml_slash_2006_slash_main_literal);
					w.attribute(dml_stylesheet_xmlns_literal, dml_stylesheet_xsd_literal, dml_stylesheet_http_colon__slash__slash_www_dot_w3_dot_org_slash_2001_slash_XMLSchema_literal);
				_theme_writer.get_writer(context(), &t()->theme.get())->write_target_to(w);
				w.end_element(0, dml_stylesheet_theme_literal);
			}
			if (t()->themeOverride.present()) {
				w.start_element(0, dml_stylesheet_themeOverride_literal);
					w.attribute(0, dml_stylesheet_xmlns_literal, dml_stylesheet_http_colon__slash__slash_schemas_dot_openxmlformats_dot_org_slash_drawingml_slash_2006_slash_main_literal);
					w.attribute(dml_stylesheet_xmlns_literal, dml_stylesheet_xsd_literal, dml_stylesheet_http_colon__slash__slash_www_dot_w3_dot_org_slash_2001_slash_XMLSchema_literal);
				_themeOverride_writer.get_writer(context(), &t()->themeOverride.get())->write_target_to(w);
				w.end_element(0, dml_stylesheet_themeOverride_literal);
			}
			if (t()->themeManager.present()) {
				w.start_element(0, dml_stylesheet_themeManager_literal);
					w.attribute(0, dml_stylesheet_xmlns_literal, dml_stylesheet_http_colon__slash__slash_schemas_dot_openxmlformats_dot_org_slash_drawingml_slash_2006_slash_main_literal);
					w.attribute(dml_stylesheet_xmlns_literal, dml_stylesheet_xsd_literal, dml_stylesheet_http_colon__slash__slash_www_dot_w3_dot_org_slash_2001_slash_XMLSchema_literal);
				_themeManager_writer.get_writer(context(), &t()->themeManager.get())->write_target_to(w);
				w.end_element(0, dml_stylesheet_themeManager_literal);
			}
		}

		void CT_ColorMappingOverride_writer::write_target_to(xml_writer& w) {
			if (t()->masterClrMapping.present()) {
				w.start_element(0, dml_stylesheet_masterClrMapping_literal);
				_masterClrMapping_writer.get_writer(context(), &t()->masterClrMapping.get())->write_target_to(w);
				w.end_element(0, dml_stylesheet_masterClrMapping_literal);
			}
			if (t()->overrideClrMapping.present()) {
				w.start_element(0, dml_stylesheet_overrideClrMapping_literal);
				_overrideClrMapping_writer.get_writer(context(), &t()->overrideClrMapping.get())->write_target_to(w);
				w.end_element(0, dml_stylesheet_overrideClrMapping_literal);
			}
		}

	}
}
