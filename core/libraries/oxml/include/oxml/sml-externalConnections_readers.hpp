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

#ifndef SML_EXTERNALCONNECTIONS_READERS_HPP
#define SML_EXTERNALCONNECTIONS_READERS_HPP

#include "sml-externalConnections.hpp"
#include "sml-baseTypes_readers.hpp"
#include "sml-pivotTableShared_readers.hpp"

namespace spreadsheetml
{
	namespace xio
	{
		using namespace ::xercesc;
		using namespace ::xio::xcs;
		using namespace ::xio::xml::binding;

		class CT_DbPr_reader;
		class CT_OlapPr_reader;
		class CT_TableMissing_reader;
		class CT_Tables_reader;
		class CT_WebPr_reader;
		class CT_TextField_reader;
		class CT_TextFields_reader;
		class CT_TextPr_reader;
		class CT_Parameter_reader;
		class CT_Parameters_reader;
		class CT_Connection_reader;
		class CT_Connections_reader;
		class sml_externalConnections_reader;

		class CT_DbPr_reader : public type_reader
		{
		protected:
			CT_DbPr* t() { return static_cast<CT_DbPr*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_OlapPr_reader : public type_reader
		{
		protected:
			CT_OlapPr* t() { return static_cast<CT_OlapPr*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_TableMissing_reader : public type_reader
		{
		protected:
			CT_TableMissing* t() { return static_cast<CT_TableMissing*>(target()); }
		};

		class CT_Tables_reader : public type_reader
		{
			auto_type_reader< CT_TableMissing_reader > _m_reader;
			auto_type_reader< CT_XStringElement_reader > _s_reader;
			auto_type_reader< CT_Index_reader > _x_reader;
		protected:
			CT_Tables* t() { return static_cast<CT_Tables*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_WebPr_reader : public type_reader
		{
			auto_type_reader< CT_Tables_reader > _tables_reader;
		protected:
			CT_WebPr* t() { return static_cast<CT_WebPr*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_TextField_reader : public type_reader
		{
		protected:
			CT_TextField* t() { return static_cast<CT_TextField*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_TextFields_reader : public type_reader
		{
			auto_type_reader< CT_TextField_reader > _textField_reader;
		protected:
			CT_TextFields* t() { return static_cast<CT_TextFields*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_TextPr_reader : public type_reader
		{
			auto_type_reader< CT_TextFields_reader > _textFields_reader;
		protected:
			CT_TextPr* t() { return static_cast<CT_TextPr*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Parameter_reader : public type_reader
		{
		protected:
			CT_Parameter* t() { return static_cast<CT_Parameter*>(target()); }
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Parameters_reader : public type_reader
		{
			auto_type_reader< CT_Parameter_reader > _parameter_reader;
		protected:
			CT_Parameters* t() { return static_cast<CT_Parameters*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Connection_reader : public type_reader
		{
			auto_type_reader< CT_DbPr_reader > _dbPr_reader;
			auto_type_reader< CT_OlapPr_reader > _olapPr_reader;
			auto_type_reader< CT_WebPr_reader > _webPr_reader;
			auto_type_reader< CT_TextPr_reader > _textPr_reader;
			auto_type_reader< CT_Parameters_reader > _parameters_reader;
			auto_type_reader< CT_ExtensionList_reader > _extLst_reader;
		protected:
			CT_Connection* t() { return static_cast<CT_Connection*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
			void read_attribute(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value);
		};

		class CT_Connections_reader : public type_reader
		{
			auto_type_reader< CT_Connection_reader > _connection_reader;
		protected:
			CT_Connections* t() { return static_cast<CT_Connections*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

		class sml_externalConnections_reader : public type_reader
		{
			auto_type_reader< CT_Connections_reader > _connections_reader;
		protected:
			sml_externalConnections* t() { return static_cast<sml_externalConnections*>(target()); }
			void start_element(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs);
		};

	}
}
#endif

