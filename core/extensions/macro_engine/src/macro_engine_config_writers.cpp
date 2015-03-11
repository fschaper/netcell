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
#include "macro_engine_config_writers.hpp"
#include "macro_engine_config_literals.hpp"

namespace macro_engine_settings
{
    namespace xio
    {
        void extension_type_writer::write_target_to( xml_writer& w )
        {
            w.attribute( 0, macro_engine_config_extension_file_literal, context()->serialize( t()->extension_file ) );
        }

        void macro_engine_config_php_macro_engine_config_php_extensions_extensions_writer::write_target_to( xml_writer& w )
        {
            for ( size_t sqi = 0; sqi < t()->extension.size(); ++sqi ) {
                w.start_element( 0, macro_engine_config_extension_literal );
                _extension_writer.get_writer( context(), &t()->extension[sqi] )->write_target_to( w );
                w.end_element( 0, macro_engine_config_extension_literal );
            }
        }

        void macro_engine_config_php_macro_engine_config_php_extensions_writer::write_target_to( xml_writer& w )
        {
            w.attribute( 0, macro_engine_config_directory_literal, context()->serialize( t()->directory ) );
            w.start_element( 0, macro_engine_config_extensions_literal );
            _extensions_writer.get_writer( context(), &t()->extensions )->write_target_to( w );
            w.end_element( 0, macro_engine_config_extensions_literal );
        }

        void include_path_type_writer::write_target_to( xml_writer& w )
        {
            w.attribute( 0, macro_engine_config_path_literal, context()->serialize( t()->path ) );
            w.attribute( 0, macro_engine_config_relative_literal, context()->serialize( t()->relative ) );
        }

        void macro_engine_config_php_macro_engine_config_php_files_include_paths_writer::write_target_to( xml_writer& w )
        {
            for ( size_t sqi = 0; sqi < t()->include_path.size(); ++sqi ) {
                w.start_element( 0, macro_engine_config_include_path_literal );
                _include_path_writer.get_writer( context(), &t()->include_path[sqi] )->write_target_to( w );
                w.end_element( 0, macro_engine_config_include_path_literal );
            }
        }

        void macro_engine_config_php_macro_engine_config_php_files_writer::write_target_to( xml_writer& w )
        {
            w.attribute( 0, macro_engine_config_directory_literal, context()->serialize( t()->directory ) );
            if ( t()->temp_directory != "C:\\WINDOWS\\Temp" ) {
                w.attribute( 0, macro_engine_config_temp_directory_literal, context()->serialize( t()->temp_directory ) );
            }
            if ( t()->include_paths.present() ) {
                w.start_element( 0, macro_engine_config_include_paths_literal );
                _include_paths_writer.get_writer( context(), &t()->include_paths.get() )->write_target_to( w );
                w.end_element( 0, macro_engine_config_include_paths_literal );
            }
        }

        void function_type_writer::write_target_to( xml_writer& w )
        {
            w.attribute( 0, macro_engine_config_spreadsheet_function_literal, context()->serialize( t()->spreadsheet_function ) );
            w.attribute( 0, macro_engine_config_php_file_literal, context()->serialize( t()->php_file ) );
            w.attribute( 0, macro_engine_config_php_function_literal, context()->serialize( t()->php_function ) );
            w.attribute( 0, macro_engine_config_arguments_count_literal, context()->serialize( t()->arguments_count ) );
            w.attribute( 0, macro_engine_config_always_recalc_literal, context()->serialize( t()->always_recalc ) );
            if ( t()->view_independent_calculation != false ) {
                w.attribute( 0, macro_engine_config_view_independent_calculation_literal, context()->serialize( t()->view_independent_calculation ) );
            }
        }

        void macro_engine_config_php_macro_engine_config_functions_writer::write_target_to( xml_writer& w )
        {
            w.attribute( 0, macro_engine_config_loglevel_literal, context()->serialize( t()->loglevel ) );
            for ( size_t sqi = 0; sqi < t()->function.size(); ++sqi ) {
                w.start_element( 0, macro_engine_config_function_literal );
                _function_writer.get_writer( context(), &t()->function[sqi] )->write_target_to( w );
                w.end_element( 0, macro_engine_config_function_literal );
            }
        }

        void CT_general_settings_writer::write_target_to( xml_writer& w )
        {
            w.start_element( 0, macro_engine_config_console_echo_literal );
            w.write_element_value( context()->serialize( t()->console_echo ) );
            w.end_element( 0, macro_engine_config_console_echo_literal );
        }

        void macro_engine_config_php_macro_engine_config_writer::write_target_to( xml_writer& w )
        {
            if ( t()->php_extensions.present() ) {
                w.start_element( 0, macro_engine_config_php_extensions_literal );
                _php_extensions_writer.get_writer( context(), &t()->php_extensions.get() )->write_target_to( w );
                w.end_element( 0, macro_engine_config_php_extensions_literal );
            }
            w.start_element( 0, macro_engine_config_php_files_literal );
            _php_files_writer.get_writer( context(), &t()->php_files )->write_target_to( w );
            w.end_element( 0, macro_engine_config_php_files_literal );
            w.start_element( 0, macro_engine_config_functions_literal );
            _functions_writer.get_writer( context(), &t()->functions )->write_target_to( w );
            w.end_element( 0, macro_engine_config_functions_literal );
            if ( t()->ini_directives.present() ) {
                w.start_element( 0, macro_engine_config_ini_directives_literal );
                w.write_element_value( context()->serialize( t()->ini_directives.get() ) );
                w.end_element( 0, macro_engine_config_ini_directives_literal );
            }
            w.start_element( 0, macro_engine_config_general_settings_literal );
            _general_settings_writer.get_writer( context(), &t()->general_settings )->write_target_to( w );
            w.end_element( 0, macro_engine_config_general_settings_literal );
        }

        void macro_engine_config_writer::write_target_to( xml_writer& w )
        {
            if ( t()->php_macro_engine_config.present() ) {
                w.start_element( 0, macro_engine_config_php_macro_engine_config_literal );
                w.attribute( 0, macro_engine_config_xmlns_literal, macro_engine_config_http_colon__slash__slash_www_dot_jedox_dot_com_slash_jedox_slash_wss_literal );
                w.attribute( macro_engine_config_xmlns_literal, macro_engine_config_NS_literal, macro_engine_config_http_colon__slash__slash_www_dot_jedox_dot_com_slash_jedox_slash_wss_literal );
                w.attribute( macro_engine_config_xmlns_literal, macro_engine_config_xs_literal, macro_engine_config_http_colon__slash__slash_www_dot_w3_dot_org_slash_2001_slash_XMLSchema_literal );
                _php_macro_engine_config_writer.get_writer( context(), &t()->php_macro_engine_config.get() )->write_target_to( w );
                w.end_element( 0, macro_engine_config_php_macro_engine_config_literal );
            }
        }

    }
}
