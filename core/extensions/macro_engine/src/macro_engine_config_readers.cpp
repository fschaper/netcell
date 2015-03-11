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
#include "macro_engine_config_readers.hpp"
#include "macro_engine_config_literals.hpp"
#include <xio/xml/binding/driver.hpp>

namespace macro_engine_settings
{
    namespace xio
    {
        void extension_type_reader::read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value )
        {
            if ( ::xercesc::XMLString::equals( localname, macro_engine_config_extension_file_literal ) ) {
                driver()->context()->parse( value, t()->extension_file );
                return;
            }
        }
        void macro_engine_config_php_macro_engine_config_php_extensions_extensions_reader::start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs )
        {
            if ( ::xercesc::XMLString::equals( localname, macro_engine_config_extension_literal ) ) {
                t()->extension.resize( t()->extension.size() + 1 );
                driver()->push( localname, _extension_reader.get_reader( &t()->extension.back() ) );
                return;
            }
        }
        void macro_engine_config_php_macro_engine_config_php_extensions_reader::start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs )
        {
            if ( ::xercesc::XMLString::equals( localname, macro_engine_config_extensions_literal ) ) {
                driver()->push( localname, _extensions_reader.get_reader( &t()->extensions ) );
                return;
            }
        }
        void macro_engine_config_php_macro_engine_config_php_extensions_reader::read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value )
        {
            if ( ::xercesc::XMLString::equals( localname, macro_engine_config_directory_literal ) ) {
                driver()->context()->parse( value, t()->directory );
                return;
            }
        }
        void include_path_type_reader::read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value )
        {
            if ( ::xercesc::XMLString::equals( localname, macro_engine_config_path_literal ) ) {
                driver()->context()->parse( value, t()->path );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, macro_engine_config_relative_literal ) ) {
                driver()->context()->parse( value, t()->relative );
                return;
            }
        }
        void macro_engine_config_php_macro_engine_config_php_files_include_paths_reader::start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs )
        {
            if ( ::xercesc::XMLString::equals( localname, macro_engine_config_include_path_literal ) ) {
                t()->include_path.resize( t()->include_path.size() + 1 );
                driver()->push( localname, _include_path_reader.get_reader( &t()->include_path.back() ) );
                return;
            }
        }
        void macro_engine_config_php_macro_engine_config_php_files_reader::start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs )
        {
            if ( ::xercesc::XMLString::equals( localname, macro_engine_config_include_paths_literal ) ) {
                driver()->push( localname, _include_paths_reader.get_reader( &t()->include_paths.getset() ) );
                return;
            }
        }
        void macro_engine_config_php_macro_engine_config_php_files_reader::read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value )
        {
            if ( ::xercesc::XMLString::equals( localname, macro_engine_config_directory_literal ) ) {
                driver()->context()->parse( value, t()->directory );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, macro_engine_config_temp_directory_literal ) ) {
                driver()->context()->parse( value, t()->temp_directory );
                return;
            }
        }
        void function_type_reader::read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value )
        {
            if ( ::xercesc::XMLString::equals( localname, macro_engine_config_spreadsheet_function_literal ) ) {
                driver()->context()->parse( value, t()->spreadsheet_function );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, macro_engine_config_php_file_literal ) ) {
                driver()->context()->parse( value, t()->php_file );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, macro_engine_config_php_function_literal ) ) {
                driver()->context()->parse( value, t()->php_function );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, macro_engine_config_arguments_count_literal ) ) {
                driver()->context()->parse( value, t()->arguments_count );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, macro_engine_config_always_recalc_literal ) ) {
                driver()->context()->parse( value, t()->always_recalc );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, macro_engine_config_view_independent_calculation_literal ) ) {
                driver()->context()->parse( value, t()->view_independent_calculation );
                return;
            }
        }
        void macro_engine_config_php_macro_engine_config_functions_reader::start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs )
        {
            if ( ::xercesc::XMLString::equals( localname, macro_engine_config_function_literal ) ) {
                t()->function.resize( t()->function.size() + 1 );
                driver()->push( localname, _function_reader.get_reader( &t()->function.back() ) );
                return;
            }
        }
        void macro_engine_config_php_macro_engine_config_functions_reader::read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value )
        {
            if ( ::xercesc::XMLString::equals( localname, macro_engine_config_loglevel_literal ) ) {
                driver()->context()->parse( value, t()->loglevel );
                return;
            }
        }
        void CT_general_settings_reader::end_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname )
        {
            if ( ::xercesc::XMLString::equals( localname, macro_engine_config_console_echo_literal ) ) {
                driver()->context()->parse( driver()->get_characters(), t()->console_echo );
                return;
            }
        }
        void macro_engine_config_php_macro_engine_config_reader::start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs )
        {
            if ( ::xercesc::XMLString::equals( localname, macro_engine_config_php_extensions_literal ) ) {
                driver()->push( localname, _php_extensions_reader.get_reader( &t()->php_extensions.getset() ) );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, macro_engine_config_php_files_literal ) ) {
                driver()->push( localname, _php_files_reader.get_reader( &t()->php_files ) );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, macro_engine_config_functions_literal ) ) {
                driver()->push( localname, _functions_reader.get_reader( &t()->functions ) );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, macro_engine_config_general_settings_literal ) ) {
                driver()->push( localname, _general_settings_reader.get_reader( &t()->general_settings ) );
                return;
            }
        }
        void macro_engine_config_php_macro_engine_config_reader::end_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname )
        {
            if ( ::xercesc::XMLString::equals( localname, macro_engine_config_ini_directives_literal ) ) {
                driver()->context()->parse( driver()->get_characters(), t()->ini_directives.getset() );
                return;
            }
        }
        void macro_engine_config_reader::start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs )
        {
            if ( ::xercesc::XMLString::equals( localname, macro_engine_config_php_macro_engine_config_literal ) ) {
                driver()->push( localname, _php_macro_engine_config_reader.get_reader( &t()->php_macro_engine_config.getset() ) );
                return;
            }
        }
    }
}
