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

#ifndef SERVER_CONFIGURATION_WRITERS_HPP
#define SERVER_CONFIGURATION_WRITERS_HPP

#include "server_configuration.hpp"
#include "server_configuration_literals.hpp"
#include <xio/xml/binding/type_writer.hpp>

namespace server_settings
{
    namespace xio
    {
        using namespace ::xercesc;
        using namespace ::xio::xcs;
        using namespace ::xio::xml::binding;

        class modifier_type_writer;
        class modifiers_type_writer;
        class logger_type_writer;
        class logging_type_writer;
        class garbage_collector_interval_type_writer;
        class garbage_collector_type_writer;
        class session_timeout_type_writer;
        class session_max_lazy_function_count_type_writer;
        class session_type_writer;
        class quota_type_writer;
        class autosave_interval_type_writer;
        class autosave_type_writer;
        class module_type_writer;
        class extensions_type_writer;
        class wss_configuration_type_writer;
        class server_configuration_writer;

        class modifier_type_writer : public type_writer
        {
            modifier_type* t() {
                return static_cast<modifier_type*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class modifiers_type_writer : public type_writer
        {
            auto_type_writer< modifier_type_writer > _modifier_writer;
            modifiers_type* t() {
                return static_cast<modifiers_type*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class logger_type_writer : public type_writer
        {
            auto_type_writer< modifiers_type_writer > _modifiers_writer;
            logger_type* t() {
                return static_cast<logger_type*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class logging_type_writer : public type_writer
        {
            auto_type_writer< logger_type_writer > _logger_writer;
            logging_type* t() {
                return static_cast<logging_type*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class garbage_collector_interval_type_writer : public type_writer
        {
            garbage_collector_interval_type* t() {
                return static_cast<garbage_collector_interval_type*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class garbage_collector_type_writer : public type_writer
        {
            auto_type_writer< garbage_collector_interval_type_writer > _interval_writer;
            garbage_collector_type* t() {
                return static_cast<garbage_collector_type*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class session_timeout_type_writer : public type_writer
        {
            session_timeout_type* t() {
                return static_cast<session_timeout_type*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class session_max_lazy_function_count_type_writer : public type_writer
        {
            session_max_lazy_function_count_type* t() {
                return static_cast<session_max_lazy_function_count_type*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class session_type_writer : public type_writer
        {
            auto_type_writer< session_timeout_type_writer > _timeout_writer;
            auto_type_writer< session_max_lazy_function_count_type_writer > _max_lazy_function_count_writer;
            session_type* t() {
                return static_cast<session_type*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class quota_type_writer : public type_writer
        {
            quota_type* t() {
                return static_cast<quota_type*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class autosave_interval_type_writer : public type_writer
        {
            autosave_interval_type* t() {
                return static_cast<autosave_interval_type*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class autosave_type_writer : public type_writer
        {
            auto_type_writer< autosave_interval_type_writer > _interval_writer;
            autosave_type* t() {
                return static_cast<autosave_type*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class module_type_writer : public type_writer
        {
            module_type* t() {
                return static_cast<module_type*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class extensions_type_writer : public type_writer
        {
            auto_type_writer< module_type_writer > _extension_writer;
            extensions_type* t() {
                return static_cast<extensions_type*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class wss_configuration_type_writer : public type_writer
        {
            auto_type_writer< logging_type_writer > _logging_writer;
            auto_type_writer< garbage_collector_type_writer > _garbage_collector_writer;
            auto_type_writer< session_type_writer > _session_writer;
            auto_type_writer< quota_type_writer > _quota_writer;
            auto_type_writer< autosave_type_writer > _autosave_writer;
            auto_type_writer< extensions_type_writer > _extensions_writer;
            wss_configuration_type* t() {
                return static_cast<wss_configuration_type*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class server_configuration_writer : public type_writer
        {
            auto_type_writer< wss_configuration_type_writer > _wss_configuration_writer;
            server_configuration* t() {
                return static_cast<server_configuration*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

    }
}
#endif

