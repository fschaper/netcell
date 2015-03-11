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

#include "precompiled_header.hpp"
#include "server_configuration_writers.hpp"
#include "server_configuration_literals.hpp"

namespace server_settings
{
    namespace xio
    {
        void modifier_type_writer::write_target_to( xml_writer& w )
        {
            if ( t()->priority.present() ) {
                w.attribute( 0, server_configuration_priority_literal, context()->serialize( t()->priority.get() ) );
            }
            w.attribute( 0, server_configuration_name_literal, context()->serialize( t()->name ) );
        }

        void modifiers_type_writer::write_target_to( xml_writer& w )
        {
            for ( size_t sqi = 0; sqi < t()->modifier.size(); ++sqi ) {
                w.start_element( 0, server_configuration_modifier_literal );
                _modifier_writer.get_writer( context(), &t()->modifier[sqi] )->write_target_to( w );
                w.end_element( 0, server_configuration_modifier_literal );
            }
        }

        void logger_type_writer::write_target_to( xml_writer& w )
        {
            w.attribute( 0, server_configuration_name_literal, context()->serialize( t()->name ) );
            w.attribute( 0, server_configuration_level_literal, context()->serialize( t()->level ) );
            if ( t()->target.present() ) {
                w.attribute( 0, server_configuration_target_literal, context()->serialize( t()->target.get() ) );
            }
            if ( t()->module.present() ) {
                w.attribute( 0, server_configuration_module_literal, context()->serialize( t()->module.get() ) );
            }
            w.start_element( 0, server_configuration_modifiers_literal );
            _modifiers_writer.get_writer( context(), &t()->modifiers )->write_target_to( w );
            w.end_element( 0, server_configuration_modifiers_literal );
        }

        void logging_type_writer::write_target_to( xml_writer& w )
        {
            if ( t()->level != loglevel_type::debug_literal ) {
                w.attribute( 0, server_configuration_level_literal, context()->serialize( t()->level ) );
            }
            for ( size_t sqi = 0; sqi < t()->logger.size(); ++sqi ) {
                w.start_element( 0, server_configuration_logger_literal );
                _logger_writer.get_writer( context(), &t()->logger[sqi] )->write_target_to( w );
                w.end_element( 0, server_configuration_logger_literal );
            }
        }

        void garbage_collector_interval_type_writer::write_target_to( xml_writer& w )
        {
            if ( t()->seconds != 180L ) {
                w.attribute( 0, server_configuration_seconds_literal, context()->serialize( t()->seconds ) );
            }
        }

        void garbage_collector_type_writer::write_target_to( xml_writer& w )
        {
            w.start_element( 0, server_configuration_interval_literal );
            _interval_writer.get_writer( context(), &t()->interval )->write_target_to( w );
            w.end_element( 0, server_configuration_interval_literal );
        }

        void session_timeout_type_writer::write_target_to( xml_writer& w )
        {
            if ( t()->seconds != 3600L ) {
                w.attribute( 0, server_configuration_seconds_literal, context()->serialize( t()->seconds ) );
            }
        }

        void session_max_lazy_function_count_type_writer::write_target_to( xml_writer& w )
        {
            if ( t()->number != 20 ) {
                w.attribute( 0, server_configuration_number_literal, context()->serialize( t()->number ) );
            }
        }

        void session_type_writer::write_target_to( xml_writer& w )
        {
            w.start_element( 0, server_configuration_timeout_literal );
            _timeout_writer.get_writer( context(), &t()->timeout )->write_target_to( w );
            w.end_element( 0, server_configuration_timeout_literal );
            w.start_element( 0, server_configuration_max_lazy_function_count_literal );
            _max_lazy_function_count_writer.get_writer( context(), &t()->max_lazy_function_count )->write_target_to( w );
            w.end_element( 0, server_configuration_max_lazy_function_count_literal );
        }

        void quota_type_writer::write_target_to( xml_writer& w )
        {
            if ( t()->enable != false ) {
                w.attribute( 0, server_configuration_enable_literal, context()->serialize( t()->enable ) );
            }
        }

        void autosave_interval_type_writer::write_target_to( xml_writer& w )
        {
            if ( t()->seconds != 3600L ) {
                w.attribute( 0, server_configuration_seconds_literal, context()->serialize( t()->seconds ) );
            }
        }

        void autosave_type_writer::write_target_to( xml_writer& w )
        {
            w.start_element( 0, server_configuration_interval_literal );
            _interval_writer.get_writer( context(), &t()->interval )->write_target_to( w );
            w.end_element( 0, server_configuration_interval_literal );
        }

        void module_type_writer::write_target_to( xml_writer& w )
        {
            w.attribute( 0, server_configuration_name_literal, context()->serialize( t()->name ) );
            if ( t()->config.present() ) {
                w.attribute( 0, server_configuration_config_literal, context()->serialize( t()->config.get() ) );
            }
            if ( t()->critical != false ) {
                w.attribute( 0, server_configuration_critical_literal, context()->serialize( t()->critical ) );
            }
        }

        void extensions_type_writer::write_target_to( xml_writer& w )
        {
            if ( t()->path != "extension/" ) {
                w.attribute( 0, server_configuration_path_literal, context()->serialize( t()->path ) );
            }
            for ( size_t sqi = 0; sqi < t()->extension.size(); ++sqi ) {
                w.start_element( 0, server_configuration_extension_literal );
                _extension_writer.get_writer( context(), &t()->extension[sqi] )->write_target_to( w );
                w.end_element( 0, server_configuration_extension_literal );
            }
        }

        void wss_configuration_type_writer::write_target_to( xml_writer& w )
        {
            w.attribute( 0, server_configuration_version_literal, context()->serialize( t()->version ) );
            w.start_element( 0, server_configuration_logging_literal );
            _logging_writer.get_writer( context(), &t()->logging )->write_target_to( w );
            w.end_element( 0, server_configuration_logging_literal );
            w.start_element( 0, server_configuration_garbage_collector_literal );
            _garbage_collector_writer.get_writer( context(), &t()->garbage_collector )->write_target_to( w );
            w.end_element( 0, server_configuration_garbage_collector_literal );
            w.start_element( 0, server_configuration_session_literal );
            _session_writer.get_writer( context(), &t()->session )->write_target_to( w );
            w.end_element( 0, server_configuration_session_literal );
            w.start_element( 0, server_configuration_quota_literal );
            _quota_writer.get_writer( context(), &t()->quota )->write_target_to( w );
            w.end_element( 0, server_configuration_quota_literal );
            w.start_element( 0, server_configuration_autosave_literal );
            _autosave_writer.get_writer( context(), &t()->autosave )->write_target_to( w );
            w.end_element( 0, server_configuration_autosave_literal );
            w.start_element( 0, server_configuration_extensions_literal );
            _extensions_writer.get_writer( context(), &t()->extensions )->write_target_to( w );
            w.end_element( 0, server_configuration_extensions_literal );
        }

        void server_configuration_writer::write_target_to( xml_writer& w )
        {
            if ( t()->wss_configuration.present() ) {
                w.start_element( 0, server_configuration_wss_configuration_literal );
                w.attribute( 0, server_configuration_xmlns_literal, server_configuration_http_colon__slash__slash_www_dot_jedox_dot_com_slash_jedox_slash_wss_literal );
                w.attribute( server_configuration_xmlns_literal, server_configuration_NS_literal, server_configuration_http_colon__slash__slash_www_dot_jedox_dot_com_slash_jedox_slash_wss_literal );
                w.attribute( server_configuration_xmlns_literal, server_configuration_xs_literal, server_configuration_http_colon__slash__slash_www_dot_w3_dot_org_slash_2001_slash_XMLSchema_literal );
                _wss_configuration_writer.get_writer( context(), &t()->wss_configuration.get() )->write_target_to( w );
                w.end_element( 0, server_configuration_wss_configuration_literal );
            }
        }

    }
}
