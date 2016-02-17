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

#ifndef SML_EXTERNALCONNECTIONS_WRITERS_HPP
#define SML_EXTERNALCONNECTIONS_WRITERS_HPP

#include "sml-externalConnections.hpp"
#include "sml-externalConnections_literals.hpp"
#include "sml-baseTypes_writers.hpp"
#include "sml-pivotTableShared_writers.hpp"

namespace spreadsheetml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_DbPr_writer;
		class CT_OlapPr_writer;
		class CT_TableMissing_writer;
		class CT_Tables_writer;
		class CT_WebPr_writer;
		class CT_TextField_writer;
		class CT_TextFields_writer;
		class CT_TextPr_writer;
		class CT_Parameter_writer;
		class CT_Parameters_writer;
		class CT_Connection_writer;
		class CT_Connections_writer;
		class sml_externalConnections_writer;

		class CT_DbPr_writer : public type_writer
		{
			CT_DbPr* t() { return static_cast<CT_DbPr*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_OlapPr_writer : public type_writer
		{
			CT_OlapPr* t() { return static_cast<CT_OlapPr*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_TableMissing_writer : public type_writer
		{
			CT_TableMissing* t() { return static_cast<CT_TableMissing*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Tables_writer : public type_writer
		{
			auto_type_writer< CT_TableMissing_writer > _m_writer;
			auto_type_writer< CT_XStringElement_writer > _s_writer;
			auto_type_writer< CT_Index_writer > _x_writer;
			CT_Tables* t() { return static_cast<CT_Tables*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_WebPr_writer : public type_writer
		{
			auto_type_writer< CT_Tables_writer > _tables_writer;
			CT_WebPr* t() { return static_cast<CT_WebPr*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_TextField_writer : public type_writer
		{
			CT_TextField* t() { return static_cast<CT_TextField*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_TextFields_writer : public type_writer
		{
			auto_type_writer< CT_TextField_writer > _textField_writer;
			CT_TextFields* t() { return static_cast<CT_TextFields*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_TextPr_writer : public type_writer
		{
			auto_type_writer< CT_TextFields_writer > _textFields_writer;
			CT_TextPr* t() { return static_cast<CT_TextPr*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Parameter_writer : public type_writer
		{
			CT_Parameter* t() { return static_cast<CT_Parameter*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Parameters_writer : public type_writer
		{
			auto_type_writer< CT_Parameter_writer > _parameter_writer;
			CT_Parameters* t() { return static_cast<CT_Parameters*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Connection_writer : public type_writer
		{
			auto_type_writer< CT_DbPr_writer > _dbPr_writer;
			auto_type_writer< CT_OlapPr_writer > _olapPr_writer;
			auto_type_writer< CT_WebPr_writer > _webPr_writer;
			auto_type_writer< CT_TextPr_writer > _textPr_writer;
			auto_type_writer< CT_Parameters_writer > _parameters_writer;
			auto_type_writer< CT_ExtensionList_writer > _extLst_writer;
			CT_Connection* t() { return static_cast<CT_Connection*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class CT_Connections_writer : public type_writer
		{
			auto_type_writer< CT_Connection_writer > _connection_writer;
			CT_Connections* t() { return static_cast<CT_Connections*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

		class sml_externalConnections_writer : public type_writer
		{
			auto_type_writer< CT_Connections_writer > _connections_writer;
			sml_externalConnections* t() { return static_cast<sml_externalConnections*>(target()); }
		public:
			void write_target_to(xml_writer& w);
		};

	}
}
#endif

