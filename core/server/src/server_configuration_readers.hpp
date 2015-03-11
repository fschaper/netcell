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

#ifndef SERVER_CONFIGURATION_READERS_HPP
#define SERVER_CONFIGURATION_READERS_HPP

#include "server_configuration.hpp"
#include <xio/xml/binding/type_reader.hpp>

namespace server_settings
{
    namespace xio
    {
        using namespace ::xercesc;
        using namespace ::xio::xcs;
        using namespace ::xio::xml::binding;

        class modifier_type_reader;
        class modifiers_type_reader;
        class logger_type_reader;
        class logging_type_reader;
        class garbage_collector_interval_type_reader;
        class garbage_collector_type_reader;
        class session_timeout_type_reader;
        class session_max_lazy_function_count_type_reader;
        class session_type_reader;
        class quota_type_reader;
        class autosave_interval_type_reader;
        class autosave_type_reader;
        class module_type_reader;
        class extensions_type_reader;
        class wss_configuration_type_reader;
        class server_configuration_reader;

        class modifier_type_reader : public type_reader
        {
        protected:
            modifier_type* t() {
                return static_cast<modifier_type*>( target() );
            }
            void read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value );
        };

        class modifiers_type_reader : public type_reader
        {
            auto_type_reader< modifier_type_reader > _modifier_reader;
        protected:
            modifiers_type* t() {
                return static_cast<modifiers_type*>( target() );
            }
            void start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs );
        };

        class logger_type_reader : public type_reader
        {
            auto_type_reader< modifiers_type_reader > _modifiers_reader;
        protected:
            logger_type* t() {
                return static_cast<logger_type*>( target() );
            }
            void start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs );
            void read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value );
        };

        class logging_type_reader : public type_reader
        {
            auto_type_reader< logger_type_reader > _logger_reader;
        protected:
            logging_type* t() {
                return static_cast<logging_type*>( target() );
            }
            void start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs );
            void read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value );
        };

        class garbage_collector_interval_type_reader : public type_reader
        {
        protected:
            garbage_collector_interval_type* t() {
                return static_cast<garbage_collector_interval_type*>( target() );
            }
            void read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value );
        };

        class garbage_collector_type_reader : public type_reader
        {
            auto_type_reader< garbage_collector_interval_type_reader > _interval_reader;
        protected:
            garbage_collector_type* t() {
                return static_cast<garbage_collector_type*>( target() );
            }
            void start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs );
        };

        class session_timeout_type_reader : public type_reader
        {
        protected:
            session_timeout_type* t() {
                return static_cast<session_timeout_type*>( target() );
            }
            void read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value );
        };

        class session_max_lazy_function_count_type_reader : public type_reader
        {
        protected:
            session_max_lazy_function_count_type* t() {
                return static_cast<session_max_lazy_function_count_type*>( target() );
            }
            void read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value );
        };

        class session_type_reader : public type_reader
        {
            auto_type_reader< session_timeout_type_reader > _timeout_reader;
            auto_type_reader< session_max_lazy_function_count_type_reader > _max_lazy_function_count_reader;
        protected:
            session_type* t() {
                return static_cast<session_type*>( target() );
            }
            void start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs );
        };

        class quota_type_reader : public type_reader
        {
        protected:
            quota_type* t() {
                return static_cast<quota_type*>( target() );
            }
            void read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value );
        };

        class autosave_interval_type_reader : public type_reader
        {
        protected:
            autosave_interval_type* t() {
                return static_cast<autosave_interval_type*>( target() );
            }
            void read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value );
        };

        class autosave_type_reader : public type_reader
        {
            auto_type_reader< autosave_interval_type_reader > _interval_reader;
        protected:
            autosave_type* t() {
                return static_cast<autosave_type*>( target() );
            }
            void start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs );
        };

        class module_type_reader : public type_reader
        {
        protected:
            module_type* t() {
                return static_cast<module_type*>( target() );
            }
            void read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value );
        };

        class extensions_type_reader : public type_reader
        {
            auto_type_reader< module_type_reader > _extension_reader;
        protected:
            extensions_type* t() {
                return static_cast<extensions_type*>( target() );
            }
            void start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs );
            void read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value );
        };

        class wss_configuration_type_reader : public type_reader
        {
            auto_type_reader< logging_type_reader > _logging_reader;
            auto_type_reader< garbage_collector_type_reader > _garbage_collector_reader;
            auto_type_reader< session_type_reader > _session_reader;
            auto_type_reader< quota_type_reader > _quota_reader;
            auto_type_reader< autosave_type_reader > _autosave_reader;
            auto_type_reader< extensions_type_reader > _extensions_reader;
        protected:
            wss_configuration_type* t() {
                return static_cast<wss_configuration_type*>( target() );
            }
            void start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs );
            void read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value );
        };

        class server_configuration_reader : public type_reader
        {
            auto_type_reader< wss_configuration_type_reader > _wss_configuration_reader;
        protected:
            server_configuration* t() {
                return static_cast<server_configuration*>( target() );
            }
            void start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs );
        };

    }
}
#endif

