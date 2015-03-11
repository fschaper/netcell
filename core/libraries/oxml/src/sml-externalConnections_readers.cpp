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


#include "sml-externalConnections_readers.hpp"
#include "sml-externalConnections_literals.hpp"
#include <xio/xml/binding/driver.hpp>

namespace spreadsheetml
{
	namespace xio
	{
		void CT_DbPr_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_connection_literal))
			{
				driver()->context()->parse(value, t()->connection);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_command_literal))
			{
				driver()->context()->parse(value, t()->command.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_serverCommand_literal))
			{
				driver()->context()->parse(value, t()->serverCommand.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_commandType_literal))
			{
				driver()->context()->parse(value, t()->commandType);
				return;
			}
		}
		void CT_OlapPr_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_local_literal))
			{
				driver()->context()->parse(value, t()->local);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_localConnection_literal))
			{
				driver()->context()->parse(value, t()->localConnection.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_localRefresh_literal))
			{
				driver()->context()->parse(value, t()->localRefresh);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_sendLocale_literal))
			{
				driver()->context()->parse(value, t()->sendLocale);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_rowDrillCount_literal))
			{
				driver()->context()->parse(value, t()->rowDrillCount.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_serverFill_literal))
			{
				driver()->context()->parse(value, t()->serverFill);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_serverNumberFormat_literal))
			{
				driver()->context()->parse(value, t()->serverNumberFormat);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_serverFont_literal))
			{
				driver()->context()->parse(value, t()->serverFont);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_serverFontColor_literal))
			{
				driver()->context()->parse(value, t()->serverFontColor);
				return;
			}
		}
		void CT_Tables_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_m_literal))
			{
				driver()->push(localname, _m_reader.get_reader(&t()->m.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_s_literal))
			{
				driver()->push(localname, _s_reader.get_reader(&t()->s.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_x_literal))
			{
				driver()->push(localname, _x_reader.get_reader(&t()->x.getset()));
				return;
			}
		}
		void CT_Tables_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
		}
		void CT_WebPr_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_tables_literal))
			{
				driver()->push(localname, _tables_reader.get_reader(&t()->tables.getset()));
				return;
			}
		}
		void CT_WebPr_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_xml_literal))
			{
				driver()->context()->parse(value, t()->xml);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_sourceData_literal))
			{
				driver()->context()->parse(value, t()->sourceData);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_parsePre_literal))
			{
				driver()->context()->parse(value, t()->parsePre);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_consecutive_literal))
			{
				driver()->context()->parse(value, t()->consecutive);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_firstRow_literal))
			{
				driver()->context()->parse(value, t()->firstRow);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_xl97_literal))
			{
				driver()->context()->parse(value, t()->xl97);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_textDates_literal))
			{
				driver()->context()->parse(value, t()->textDates);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_xl2000_literal))
			{
				driver()->context()->parse(value, t()->xl2000);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_url_literal))
			{
				driver()->context()->parse(value, t()->url.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_post_literal))
			{
				driver()->context()->parse(value, t()->post.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_htmlTables_literal))
			{
				driver()->context()->parse(value, t()->htmlTables);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_htmlFormat_literal))
			{
				driver()->context()->parse(value, t()->htmlFormat);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_editPage_literal))
			{
				driver()->context()->parse(value, t()->editPage.getset());
				return;
			}
		}
		void CT_TextField_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_type_literal))
			{
				driver()->context()->parse(value, t()->type);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_position_literal))
			{
				driver()->context()->parse(value, t()->position);
				return;
			}
		}
		void CT_TextFields_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_textField_literal))
			{
				t()->textField.resize(t()->textField.size()+1);
				driver()->push(localname, _textField_reader.get_reader(&t()->textField.back()));
				return;
			}
		}
		void CT_TextFields_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_count_literal))
			{
				driver()->context()->parse(value, t()->count);
				return;
			}
		}
		void CT_TextPr_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_textFields_literal))
			{
				driver()->push(localname, _textFields_reader.get_reader(&t()->textFields.getset()));
				return;
			}
		}
		void CT_TextPr_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_prompt_literal))
			{
				driver()->context()->parse(value, t()->prompt);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_fileType_literal))
			{
				driver()->context()->parse(value, t()->fileType);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_codePage_literal))
			{
				driver()->context()->parse(value, t()->codePage);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_firstRow_literal))
			{
				driver()->context()->parse(value, t()->firstRow);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_sourceFile_literal))
			{
				driver()->context()->parse(value, t()->sourceFile);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_delimited_literal))
			{
				driver()->context()->parse(value, t()->delimited);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_decimal_literal))
			{
				driver()->context()->parse(value, t()->decimal);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_thousands_literal))
			{
				driver()->context()->parse(value, t()->thousands);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_tab_literal))
			{
				driver()->context()->parse(value, t()->tab);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_space_literal))
			{
				driver()->context()->parse(value, t()->space);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_comma_literal))
			{
				driver()->context()->parse(value, t()->comma);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_semicolon_literal))
			{
				driver()->context()->parse(value, t()->semicolon);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_consecutive_literal))
			{
				driver()->context()->parse(value, t()->consecutive);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_qualifier_literal))
			{
				driver()->context()->parse(value, t()->qualifier);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_delimiter_literal))
			{
				driver()->context()->parse(value, t()->delimiter.getset());
				return;
			}
		}
		void CT_Parameter_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_name_literal))
			{
				driver()->context()->parse(value, t()->name.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_sqlType_literal))
			{
				driver()->context()->parse(value, t()->sqlType);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_parameterType_literal))
			{
				driver()->context()->parse(value, t()->parameterType);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_refreshOnChange_literal))
			{
				driver()->context()->parse(value, t()->refreshOnChange);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_prompt_literal))
			{
				driver()->context()->parse(value, t()->prompt.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_boolean_literal))
			{
				driver()->context()->parse(value, t()->boolean.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections__double__literal))
			{
				driver()->context()->parse(value, t()->_double_.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_integer_literal))
			{
				driver()->context()->parse(value, t()->integer.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections__string__literal))
			{
				driver()->context()->parse(value, t()->_string_.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_cell_literal))
			{
				driver()->context()->parse(value, t()->cell.getset());
				return;
			}
		}
		void CT_Parameters_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_parameter_literal))
			{
				t()->parameter.resize(t()->parameter.size()+1);
				driver()->push(localname, _parameter_reader.get_reader(&t()->parameter.back()));
				return;
			}
		}
		void CT_Parameters_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_count_literal))
			{
				driver()->context()->parse(value, t()->count.getset());
				return;
			}
		}
		void CT_Connection_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_dbPr_literal))
			{
				driver()->push(localname, _dbPr_reader.get_reader(&t()->dbPr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_olapPr_literal))
			{
				driver()->push(localname, _olapPr_reader.get_reader(&t()->olapPr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_webPr_literal))
			{
				driver()->push(localname, _webPr_reader.get_reader(&t()->webPr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_textPr_literal))
			{
				driver()->push(localname, _textPr_reader.get_reader(&t()->textPr.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_parameters_literal))
			{
				driver()->push(localname, _parameters_reader.get_reader(&t()->parameters.getset()));
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_extLst_literal))
			{
				driver()->push(localname, _extLst_reader.get_reader(&t()->extLst.getset()));
				return;
			}
		}
		void CT_Connection_reader::read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value)
		{
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_id_literal))
			{
				driver()->context()->parse(value, t()->id);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_sourceFile_literal))
			{
				driver()->context()->parse(value, t()->sourceFile.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_odcFile_literal))
			{
				driver()->context()->parse(value, t()->odcFile.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_keepAlive_literal))
			{
				driver()->context()->parse(value, t()->keepAlive);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_interval_literal))
			{
				driver()->context()->parse(value, t()->interval);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_name_literal))
			{
				driver()->context()->parse(value, t()->name.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_description_literal))
			{
				driver()->context()->parse(value, t()->description.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_type_literal))
			{
				driver()->context()->parse(value, t()->type.getset());
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_reconnectionMethod_literal))
			{
				driver()->context()->parse(value, t()->reconnectionMethod);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_refreshedVersion_literal))
			{
				driver()->context()->parse(value, t()->refreshedVersion);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_minRefreshableVersion_literal))
			{
				driver()->context()->parse(value, t()->minRefreshableVersion);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_savePassword_literal))
			{
				driver()->context()->parse(value, t()->savePassword);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections__new__literal))
			{
				driver()->context()->parse(value, t()->_new_);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_deleted_literal))
			{
				driver()->context()->parse(value, t()->deleted);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_onlyUseConnectionFile_literal))
			{
				driver()->context()->parse(value, t()->onlyUseConnectionFile);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_background_literal))
			{
				driver()->context()->parse(value, t()->background);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_refreshOnLoad_literal))
			{
				driver()->context()->parse(value, t()->refreshOnLoad);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_saveData_literal))
			{
				driver()->context()->parse(value, t()->saveData);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_credentials_literal))
			{
				driver()->context()->parse(value, t()->credentials);
				return;
			}
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_singleSignOnId_literal))
			{
				driver()->context()->parse(value, t()->singleSignOnId.getset());
				return;
			}
		}
		void CT_Connections_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_connection_literal))
			{
				t()->connection.resize(t()->connection.size()+1);
				driver()->push(localname, _connection_reader.get_reader(&t()->connection.back()));
				return;
			}
		}
		void sml_externalConnections_reader::start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs)
		{
			if (::xercesc::XMLString::equals(localname, sml_externalConnections_connections_literal))
			{
				driver()->push(localname, _connections_reader.get_reader(&t()->connections.getset()));
				return;
			}
		}
	}
}
