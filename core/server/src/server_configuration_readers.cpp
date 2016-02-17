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
#include "server_configuration_readers.hpp"
#include "server_configuration_literals.hpp"
#include <xio/xml/binding/driver.hpp>

namespace server_settings
{
    namespace xio
    {
        void modifier_type_reader::read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value )
        {
            if ( ::xercesc::XMLString::equals( localname, server_configuration_priority_literal ) ) {
                driver()->context()->parse( value, t()->priority.getset() );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, server_configuration_name_literal ) ) {
                driver()->context()->parse( value, t()->name );
                return;
            }
        }
        void modifiers_type_reader::start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs )
        {
            if ( ::xercesc::XMLString::equals( localname, server_configuration_modifier_literal ) ) {
                t()->modifier.resize( t()->modifier.size() + 1 );
                driver()->push( localname, _modifier_reader.get_reader( &t()->modifier.back() ) );
                return;
            }
        }
        void logger_type_reader::start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs )
        {
            if ( ::xercesc::XMLString::equals( localname, server_configuration_modifiers_literal ) ) {
                driver()->push( localname, _modifiers_reader.get_reader( &t()->modifiers ) );
                return;
            }
        }
        void logger_type_reader::read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value )
        {
            if ( ::xercesc::XMLString::equals( localname, server_configuration_name_literal ) ) {
                driver()->context()->parse( value, t()->name );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, server_configuration_level_literal ) ) {
                driver()->context()->parse( value, t()->level );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, server_configuration_target_literal ) ) {
                driver()->context()->parse( value, t()->target.getset() );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, server_configuration_module_literal ) ) {
                driver()->context()->parse( value, t()->module.getset() );
                return;
            }
        }
        void logging_type_reader::start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs )
        {
            if ( ::xercesc::XMLString::equals( localname, server_configuration_logger_literal ) ) {
                t()->logger.resize( t()->logger.size() + 1 );
                driver()->push( localname, _logger_reader.get_reader( &t()->logger.back() ) );
                return;
            }
        }
        void logging_type_reader::read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value )
        {
            if ( ::xercesc::XMLString::equals( localname, server_configuration_level_literal ) ) {
                driver()->context()->parse( value, t()->level );
                return;
            }
        }
        void garbage_collector_interval_type_reader::read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value )
        {
            if ( ::xercesc::XMLString::equals( localname, server_configuration_seconds_literal ) ) {
                driver()->context()->parse( value, t()->seconds );
                return;
            }
        }
        void garbage_collector_type_reader::start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs )
        {
            if ( ::xercesc::XMLString::equals( localname, server_configuration_interval_literal ) ) {
                driver()->push( localname, _interval_reader.get_reader( &t()->interval ) );
                return;
            }
        }
        void session_timeout_type_reader::read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value )
        {
            if ( ::xercesc::XMLString::equals( localname, server_configuration_seconds_literal ) ) {
                driver()->context()->parse( value, t()->seconds );
                return;
            }
        }
        void session_max_lazy_function_count_type_reader::read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value )
        {
            if ( ::xercesc::XMLString::equals( localname, server_configuration_number_literal ) ) {
                driver()->context()->parse( value, t()->number );
                return;
            }
        }
        void session_type_reader::start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs )
        {
            if ( ::xercesc::XMLString::equals( localname, server_configuration_timeout_literal ) ) {
                driver()->push( localname, _timeout_reader.get_reader( &t()->timeout ) );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, server_configuration_max_lazy_function_count_literal ) ) {
                driver()->push( localname, _max_lazy_function_count_reader.get_reader( &t()->max_lazy_function_count ) );
                return;
            }
        }
        void quota_type_reader::read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value )
        {
            if ( ::xercesc::XMLString::equals( localname, server_configuration_enable_literal ) ) {
                driver()->context()->parse( value, t()->enable );
                return;
            }
        }
        void autosave_interval_type_reader::read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value )
        {
            if ( ::xercesc::XMLString::equals( localname, server_configuration_seconds_literal ) ) {
                driver()->context()->parse( value, t()->seconds );
                return;
            }
        }
        void autosave_type_reader::start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs )
        {
            if ( ::xercesc::XMLString::equals( localname, server_configuration_interval_literal ) ) {
                driver()->push( localname, _interval_reader.get_reader( &t()->interval ) );
                return;
            }
        }
        void module_type_reader::read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value )
        {
            if ( ::xercesc::XMLString::equals( localname, server_configuration_name_literal ) ) {
                driver()->context()->parse( value, t()->name );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, server_configuration_config_literal ) ) {
                driver()->context()->parse( value, t()->config.getset() );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, server_configuration_critical_literal ) ) {
                driver()->context()->parse( value, t()->critical );
                return;
            }
        }
        void extensions_type_reader::start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs )
        {
            if ( ::xercesc::XMLString::equals( localname, server_configuration_extension_literal ) ) {
                t()->extension.resize( t()->extension.size() + 1 );
                driver()->push( localname, _extension_reader.get_reader( &t()->extension.back() ) );
                return;
            }
        }
        void extensions_type_reader::read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value )
        {
            if ( ::xercesc::XMLString::equals( localname, server_configuration_path_literal ) ) {
                driver()->context()->parse( value, t()->path );
                return;
            }
        }
        void wss_configuration_type_reader::start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs )
        {
            if ( ::xercesc::XMLString::equals( localname, server_configuration_logging_literal ) ) {
                driver()->push( localname, _logging_reader.get_reader( &t()->logging ) );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, server_configuration_garbage_collector_literal ) ) {
                driver()->push( localname, _garbage_collector_reader.get_reader( &t()->garbage_collector ) );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, server_configuration_session_literal ) ) {
                driver()->push( localname, _session_reader.get_reader( &t()->session ) );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, server_configuration_quota_literal ) ) {
                driver()->push( localname, _quota_reader.get_reader( &t()->quota ) );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, server_configuration_autosave_literal ) ) {
                driver()->push( localname, _autosave_reader.get_reader( &t()->autosave ) );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, server_configuration_extensions_literal ) ) {
                driver()->push( localname, _extensions_reader.get_reader( &t()->extensions ) );
                return;
            }
        }
        void wss_configuration_type_reader::read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value )
        {
            if ( ::xercesc::XMLString::equals( localname, server_configuration_version_literal ) ) {
                driver()->context()->parse( value, t()->version );
                return;
            }
        }
        void server_configuration_reader::start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs )
        {
            if ( ::xercesc::XMLString::equals( localname, server_configuration_wss_configuration_literal ) ) {
                driver()->push( localname, _wss_configuration_reader.get_reader( &t()->wss_configuration.getset() ) );
                return;
            }
        }
    }
}
