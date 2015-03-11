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


#include "sml-externalConnections_writers.hpp"
#include "sml-externalConnections_literals.hpp"

namespace spreadsheetml
{
	namespace xio
	{
		void CT_DbPr_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_externalConnections_connection_literal, context()->serialize(t()->connection));
			if (t()->command.present())
				w.attribute(0, sml_externalConnections_command_literal, context()->serialize(t()->command.get()));
			if (t()->serverCommand.present())
				w.attribute(0, sml_externalConnections_serverCommand_literal, context()->serialize(t()->serverCommand.get()));
			if (t()->commandType != 2U)
				w.attribute(0, sml_externalConnections_commandType_literal, context()->serialize(t()->commandType));
		}

		void CT_OlapPr_writer::write_target_to(xml_writer& w) {
			if (t()->local != false)
				w.attribute(0, sml_externalConnections_local_literal, context()->serialize(t()->local));
			if (t()->localConnection.present())
				w.attribute(0, sml_externalConnections_localConnection_literal, context()->serialize(t()->localConnection.get()));
			if (t()->localRefresh != true)
				w.attribute(0, sml_externalConnections_localRefresh_literal, context()->serialize(t()->localRefresh));
			if (t()->sendLocale != false)
				w.attribute(0, sml_externalConnections_sendLocale_literal, context()->serialize(t()->sendLocale));
			if (t()->rowDrillCount.present())
				w.attribute(0, sml_externalConnections_rowDrillCount_literal, context()->serialize(t()->rowDrillCount.get()));
			if (t()->serverFill != true)
				w.attribute(0, sml_externalConnections_serverFill_literal, context()->serialize(t()->serverFill));
			if (t()->serverNumberFormat != true)
				w.attribute(0, sml_externalConnections_serverNumberFormat_literal, context()->serialize(t()->serverNumberFormat));
			if (t()->serverFont != true)
				w.attribute(0, sml_externalConnections_serverFont_literal, context()->serialize(t()->serverFont));
			if (t()->serverFontColor != true)
				w.attribute(0, sml_externalConnections_serverFontColor_literal, context()->serialize(t()->serverFontColor));
		}

		void CT_TableMissing_writer::write_target_to(xml_writer& w) {
		}

		void CT_Tables_writer::write_target_to(xml_writer& w) {
			if (t()->count.present())
				w.attribute(0, sml_externalConnections_count_literal, context()->serialize(t()->count.get()));
			if (t()->m.present()) {
				w.start_element(0, sml_externalConnections_m_literal);
				_m_writer.get_writer(context(), &t()->m.get())->write_target_to(w);
				w.end_element(0, sml_externalConnections_m_literal);
			}
			if (t()->s.present()) {
				w.start_element(0, sml_externalConnections_s_literal);
				_s_writer.get_writer(context(), &t()->s.get())->write_target_to(w);
				w.end_element(0, sml_externalConnections_s_literal);
			}
			if (t()->x.present()) {
				w.start_element(0, sml_externalConnections_x_literal);
				_x_writer.get_writer(context(), &t()->x.get())->write_target_to(w);
				w.end_element(0, sml_externalConnections_x_literal);
			}
		}

		void CT_WebPr_writer::write_target_to(xml_writer& w) {
			if (t()->xml != false)
				w.attribute(0, sml_externalConnections_xml_literal, context()->serialize(t()->xml));
			if (t()->sourceData != false)
				w.attribute(0, sml_externalConnections_sourceData_literal, context()->serialize(t()->sourceData));
			if (t()->parsePre != false)
				w.attribute(0, sml_externalConnections_parsePre_literal, context()->serialize(t()->parsePre));
			if (t()->consecutive != false)
				w.attribute(0, sml_externalConnections_consecutive_literal, context()->serialize(t()->consecutive));
			if (t()->firstRow != false)
				w.attribute(0, sml_externalConnections_firstRow_literal, context()->serialize(t()->firstRow));
			if (t()->xl97 != false)
				w.attribute(0, sml_externalConnections_xl97_literal, context()->serialize(t()->xl97));
			if (t()->textDates != false)
				w.attribute(0, sml_externalConnections_textDates_literal, context()->serialize(t()->textDates));
			if (t()->xl2000 != false)
				w.attribute(0, sml_externalConnections_xl2000_literal, context()->serialize(t()->xl2000));
			if (t()->url.present())
				w.attribute(0, sml_externalConnections_url_literal, context()->serialize(t()->url.get()));
			if (t()->post.present())
				w.attribute(0, sml_externalConnections_post_literal, context()->serialize(t()->post.get()));
			if (t()->htmlTables != false)
				w.attribute(0, sml_externalConnections_htmlTables_literal, context()->serialize(t()->htmlTables));
			if (t()->htmlFormat != ST_HtmlFmt::none_literal)
				w.attribute(0, sml_externalConnections_htmlFormat_literal, context()->serialize(t()->htmlFormat));
			if (t()->editPage.present())
				w.attribute(0, sml_externalConnections_editPage_literal, context()->serialize(t()->editPage.get()));
			if (t()->tables.present()) {
				w.start_element(0, sml_externalConnections_tables_literal);
				_tables_writer.get_writer(context(), &t()->tables.get())->write_target_to(w);
				w.end_element(0, sml_externalConnections_tables_literal);
			}
		}

		void CT_TextField_writer::write_target_to(xml_writer& w) {
			if (t()->type != ST_ExternalConnectionType::general_literal)
				w.attribute(0, sml_externalConnections_type_literal, context()->serialize(t()->type));
			if (t()->position != 0U)
				w.attribute(0, sml_externalConnections_position_literal, context()->serialize(t()->position));
		}

		void CT_TextFields_writer::write_target_to(xml_writer& w) {
			if (t()->count != 1U)
				w.attribute(0, sml_externalConnections_count_literal, context()->serialize(t()->count));
			for (size_t sqi = 0; sqi<t()->textField.size(); ++sqi) {
				w.start_element(0, sml_externalConnections_textField_literal);
				_textField_writer.get_writer(context(), &t()->textField[sqi])->write_target_to(w);
				w.end_element(0, sml_externalConnections_textField_literal);
			}
		}

		void CT_TextPr_writer::write_target_to(xml_writer& w) {
			if (t()->prompt != true)
				w.attribute(0, sml_externalConnections_prompt_literal, context()->serialize(t()->prompt));
			if (t()->fileType != ST_FileType::win_literal)
				w.attribute(0, sml_externalConnections_fileType_literal, context()->serialize(t()->fileType));
			if (t()->codePage != 1252U)
				w.attribute(0, sml_externalConnections_codePage_literal, context()->serialize(t()->codePage));
			if (t()->firstRow != 1U)
				w.attribute(0, sml_externalConnections_firstRow_literal, context()->serialize(t()->firstRow));
			if (t()->sourceFile != "")
				w.attribute(0, sml_externalConnections_sourceFile_literal, context()->serialize(t()->sourceFile));
			if (t()->delimited != true)
				w.attribute(0, sml_externalConnections_delimited_literal, context()->serialize(t()->delimited));
			if (t()->decimal != ".")
				w.attribute(0, sml_externalConnections_decimal_literal, context()->serialize(t()->decimal));
			if (t()->thousands != ",")
				w.attribute(0, sml_externalConnections_thousands_literal, context()->serialize(t()->thousands));
			if (t()->tab != true)
				w.attribute(0, sml_externalConnections_tab_literal, context()->serialize(t()->tab));
			if (t()->space != false)
				w.attribute(0, sml_externalConnections_space_literal, context()->serialize(t()->space));
			if (t()->comma != false)
				w.attribute(0, sml_externalConnections_comma_literal, context()->serialize(t()->comma));
			if (t()->semicolon != false)
				w.attribute(0, sml_externalConnections_semicolon_literal, context()->serialize(t()->semicolon));
			if (t()->consecutive != false)
				w.attribute(0, sml_externalConnections_consecutive_literal, context()->serialize(t()->consecutive));
			if (t()->qualifier != ST_Qualifier::doubleQuote_literal)
				w.attribute(0, sml_externalConnections_qualifier_literal, context()->serialize(t()->qualifier));
			if (t()->delimiter.present())
				w.attribute(0, sml_externalConnections_delimiter_literal, context()->serialize(t()->delimiter.get()));
			if (t()->textFields.present()) {
				w.start_element(0, sml_externalConnections_textFields_literal);
				_textFields_writer.get_writer(context(), &t()->textFields.get())->write_target_to(w);
				w.end_element(0, sml_externalConnections_textFields_literal);
			}
		}

		void CT_Parameter_writer::write_target_to(xml_writer& w) {
			if (t()->name.present())
				w.attribute(0, sml_externalConnections_name_literal, context()->serialize(t()->name.get()));
			if (t()->sqlType != 0)
				w.attribute(0, sml_externalConnections_sqlType_literal, context()->serialize(t()->sqlType));
			if (t()->parameterType != ST_ParameterType::prompt_literal)
				w.attribute(0, sml_externalConnections_parameterType_literal, context()->serialize(t()->parameterType));
			if (t()->refreshOnChange != false)
				w.attribute(0, sml_externalConnections_refreshOnChange_literal, context()->serialize(t()->refreshOnChange));
			if (t()->prompt.present())
				w.attribute(0, sml_externalConnections_prompt_literal, context()->serialize(t()->prompt.get()));
			if (t()->boolean.present())
				w.attribute(0, sml_externalConnections_boolean_literal, context()->serialize(t()->boolean.get()));
			if (t()->_double_.present())
				w.attribute(0, sml_externalConnections__double__literal, context()->serialize(t()->_double_.get()));
			if (t()->integer.present())
				w.attribute(0, sml_externalConnections_integer_literal, context()->serialize(t()->integer.get()));
			if (t()->_string_.present())
				w.attribute(0, sml_externalConnections__string__literal, context()->serialize(t()->_string_.get()));
			if (t()->cell.present())
				w.attribute(0, sml_externalConnections_cell_literal, context()->serialize(t()->cell.get()));
		}

		void CT_Parameters_writer::write_target_to(xml_writer& w) {
			if (t()->count.present())
				w.attribute(0, sml_externalConnections_count_literal, context()->serialize(t()->count.get()));
			for (size_t sqi = 0; sqi<t()->parameter.size(); ++sqi) {
				w.start_element(0, sml_externalConnections_parameter_literal);
				_parameter_writer.get_writer(context(), &t()->parameter[sqi])->write_target_to(w);
				w.end_element(0, sml_externalConnections_parameter_literal);
			}
		}

		void CT_Connection_writer::write_target_to(xml_writer& w) {
			w.attribute(0, sml_externalConnections_id_literal, context()->serialize(t()->id));
			if (t()->sourceFile.present())
				w.attribute(0, sml_externalConnections_sourceFile_literal, context()->serialize(t()->sourceFile.get()));
			if (t()->odcFile.present())
				w.attribute(0, sml_externalConnections_odcFile_literal, context()->serialize(t()->odcFile.get()));
			if (t()->keepAlive != false)
				w.attribute(0, sml_externalConnections_keepAlive_literal, context()->serialize(t()->keepAlive));
			if (t()->interval != 0U)
				w.attribute(0, sml_externalConnections_interval_literal, context()->serialize(t()->interval));
			if (t()->name.present())
				w.attribute(0, sml_externalConnections_name_literal, context()->serialize(t()->name.get()));
			if (t()->description.present())
				w.attribute(0, sml_externalConnections_description_literal, context()->serialize(t()->description.get()));
			if (t()->type.present())
				w.attribute(0, sml_externalConnections_type_literal, context()->serialize(t()->type.get()));
			if (t()->reconnectionMethod != 1U)
				w.attribute(0, sml_externalConnections_reconnectionMethod_literal, context()->serialize(t()->reconnectionMethod));
			w.attribute(0, sml_externalConnections_refreshedVersion_literal, context()->serialize(t()->refreshedVersion));
			if (t()->minRefreshableVersion != 0)
				w.attribute(0, sml_externalConnections_minRefreshableVersion_literal, context()->serialize(t()->minRefreshableVersion));
			if (t()->savePassword != false)
				w.attribute(0, sml_externalConnections_savePassword_literal, context()->serialize(t()->savePassword));
			if (t()->_new_ != false)
				w.attribute(0, sml_externalConnections__new__literal, context()->serialize(t()->_new_));
			if (t()->deleted != false)
				w.attribute(0, sml_externalConnections_deleted_literal, context()->serialize(t()->deleted));
			if (t()->onlyUseConnectionFile != false)
				w.attribute(0, sml_externalConnections_onlyUseConnectionFile_literal, context()->serialize(t()->onlyUseConnectionFile));
			if (t()->background != false)
				w.attribute(0, sml_externalConnections_background_literal, context()->serialize(t()->background));
			if (t()->refreshOnLoad != false)
				w.attribute(0, sml_externalConnections_refreshOnLoad_literal, context()->serialize(t()->refreshOnLoad));
			if (t()->saveData != false)
				w.attribute(0, sml_externalConnections_saveData_literal, context()->serialize(t()->saveData));
			if (t()->credentials != ST_CredMethod::integrated_literal)
				w.attribute(0, sml_externalConnections_credentials_literal, context()->serialize(t()->credentials));
			if (t()->singleSignOnId.present())
				w.attribute(0, sml_externalConnections_singleSignOnId_literal, context()->serialize(t()->singleSignOnId.get()));
			if (t()->dbPr.present()) {
				w.start_element(0, sml_externalConnections_dbPr_literal);
				_dbPr_writer.get_writer(context(), &t()->dbPr.get())->write_target_to(w);
				w.end_element(0, sml_externalConnections_dbPr_literal);
			}
			if (t()->olapPr.present()) {
				w.start_element(0, sml_externalConnections_olapPr_literal);
				_olapPr_writer.get_writer(context(), &t()->olapPr.get())->write_target_to(w);
				w.end_element(0, sml_externalConnections_olapPr_literal);
			}
			if (t()->webPr.present()) {
				w.start_element(0, sml_externalConnections_webPr_literal);
				_webPr_writer.get_writer(context(), &t()->webPr.get())->write_target_to(w);
				w.end_element(0, sml_externalConnections_webPr_literal);
			}
			if (t()->textPr.present()) {
				w.start_element(0, sml_externalConnections_textPr_literal);
				_textPr_writer.get_writer(context(), &t()->textPr.get())->write_target_to(w);
				w.end_element(0, sml_externalConnections_textPr_literal);
			}
			if (t()->parameters.present()) {
				w.start_element(0, sml_externalConnections_parameters_literal);
				_parameters_writer.get_writer(context(), &t()->parameters.get())->write_target_to(w);
				w.end_element(0, sml_externalConnections_parameters_literal);
			}
			if (t()->extLst.present()) {
				w.start_element(0, sml_externalConnections_extLst_literal);
				_extLst_writer.get_writer(context(), &t()->extLst.get())->write_target_to(w);
				w.end_element(0, sml_externalConnections_extLst_literal);
			}
		}

		void CT_Connections_writer::write_target_to(xml_writer& w) {
			for (size_t sqi = 0; sqi<t()->connection.size(); ++sqi) {
				w.start_element(0, sml_externalConnections_connection_literal);
				_connection_writer.get_writer(context(), &t()->connection[sqi])->write_target_to(w);
				w.end_element(0, sml_externalConnections_connection_literal);
			}
		}

		void sml_externalConnections_writer::write_target_to(xml_writer& w) {
			if (t()->connections.present()) {
				w.start_element(0, sml_externalConnections_connections_literal);
					w.attribute(0, sml_externalConnections_xmlns_literal, sml_externalConnections_http_colon__slash__slash_schemas_dot_openxmlformats_dot_org_slash_spreadsheetml_slash_2006_slash_main_literal);
					w.attribute(sml_externalConnections_xmlns_literal, sml_externalConnections_xsd_literal, sml_externalConnections_http_colon__slash__slash_www_dot_w3_dot_org_slash_2001_slash_XMLSchema_literal);
				_connections_writer.get_writer(context(), &t()->connections.get())->write_target_to(w);
				w.end_element(0, sml_externalConnections_connections_literal);
			}
		}

	}
}
