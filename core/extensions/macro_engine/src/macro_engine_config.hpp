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

#ifndef MACRO_ENGINE_CONFIG_HPP
#define MACRO_ENGINE_CONFIG_HPP


#include <xio/optional.hpp>
#include <xio/xml/schema/types.hpp>
#include <xio/util/binary_search.hpp>

namespace macro_engine_settings
{
    using namespace ::xio;
    using namespace ::xio::xml::schema;

    class extension_type;
    class macro_engine_config_php_macro_engine_config_php_extensions_extensions;
    class macro_engine_config_php_macro_engine_config_php_extensions;
    class include_path_type;
    class macro_engine_config_php_macro_engine_config_php_files_include_paths;
    class macro_engine_config_php_macro_engine_config_php_files;
    class function_type;
    class macro_engine_config_php_macro_engine_config_functions;
    class CT_general_settings;
    class macro_engine_config_php_macro_engine_config;
    class macro_engine_config;

    class extension_type
    {
    public:
        String extension_file;
    };

    class macro_engine_config_php_macro_engine_config_php_extensions_extensions
    {
    public:
        std::vector< extension_type > extension;
    };

    class macro_engine_config_php_macro_engine_config_php_extensions
    {
    public:
        macro_engine_config_php_macro_engine_config_php_extensions_extensions extensions;
        String directory;
    };

    class include_path_type
    {
    public:
        String path;
        Boolean relative;
    };

    class macro_engine_config_php_macro_engine_config_php_files_include_paths
    {
    public:
        std::vector< include_path_type > include_path;
    };

    class macro_engine_config_php_macro_engine_config_php_files
    {
    public:
        macro_engine_config_php_macro_engine_config_php_files() : temp_directory( "C:\\WINDOWS\\Temp" ) {}
        poptional< macro_engine_config_php_macro_engine_config_php_files_include_paths > include_paths;
        String directory;
        String temp_directory;
    };

    class function_type
    {
    public:
        function_type() : view_independent_calculation( false ) {}
        String spreadsheet_function;
        String php_file;
        String php_function;
        PositiveInteger arguments_count;
        Boolean always_recalc;
        Boolean view_independent_calculation;
    };

    class loglevel_type
    {
        static String _literals[];
        String _value;
    public:
        enum value { critical, debug, error, info, notice, warning };

        static const String critical_literal;
        static const String debug_literal;
        static const String error_literal;
        static const String info_literal;
        static const String notice_literal;
        static const String warning_literal;

        loglevel_type() : _value( debug_literal ) {}
        loglevel_type( value val ) : _value( convert( val ) ) {}
        loglevel_type( const String& str ) : _value( str ) {}

        static value convert( const String& str ) {
            return ( value )::xio::util::binary_search( str, _literals, 6, 0 );
        }
        static String convert( value v ) {
            return _literals[( int )v];
        }

        bool operator == ( const String& str ) const {
            return str == _value;
        }
        bool operator == ( value val ) const {
            return convert( val ) == _value;
        }
        bool operator != ( const String& str ) const {
            return str != _value;
        }
        bool operator != ( value val ) const {
            return convert( val ) != _value;
        }

        const String& operator = ( const String& str ) {
            _value = str;
            return str;
        }
        const value& operator = ( const value& val ) {
            _value = convert( val );
            return val;
        }

        operator const String& () const {
            return _value;
        }
        operator String& () {
            return _value;
        }
        operator value () const {
            return convert( _value );
        }
        String serialize() const {
            return _value;
        }
    };

    class macro_engine_config_php_macro_engine_config_functions
    {
    public:
        std::vector< function_type > function;
        loglevel_type loglevel;
    };

    class CT_general_settings
    {
    public:
        Boolean console_echo;
    };

    class macro_engine_config_php_macro_engine_config
    {
    public:
        poptional< macro_engine_config_php_macro_engine_config_php_extensions > php_extensions;
        macro_engine_config_php_macro_engine_config_php_files php_files;
        macro_engine_config_php_macro_engine_config_functions functions;
        optional< String > ini_directives;
        CT_general_settings general_settings;
    };

    class macro_engine_config
    {
    public:
        poptional< macro_engine_config_php_macro_engine_config > php_macro_engine_config;
    };

}
#endif

