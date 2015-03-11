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

#ifndef SERVER_CONFIGURATION_HPP
#define SERVER_CONFIGURATION_HPP


#include <xio/optional.hpp>
#include <xio/xml/schema/types.hpp>
#include <xio/util/binary_search.hpp>

namespace server_settings
{
    using namespace ::xio;
    using namespace ::xio::xml::schema;

    class modifier_type;
    class modifiers_type;
    class logger_type;
    class logging_type;
    class garbage_collector_interval_type;
    class garbage_collector_type;
    class session_timeout_type;
    class session_max_lazy_function_count_type;
    class session_type;
    class quota_type;
    class autosave_interval_type;
    class autosave_type;
    class module_type;
    class extensions_type;
    class wss_configuration_type;
    class server_configuration;

    class modifier_type
    {
    public:
        optional< UnsignedShort > priority;
        String name;
    };

    class modifiers_type
    {
    public:
        std::vector< modifier_type > modifier;
    };

    class loglevel_type
    {
        static String _literals[];
        String _value;
    public:
        enum value { critical, debug, error, info, notice, trace, warning };

        static const String critical_literal;
        static const String debug_literal;
        static const String error_literal;
        static const String info_literal;
        static const String notice_literal;
        static const String trace_literal;
        static const String warning_literal;

        loglevel_type() : _value( trace_literal ) {}
        loglevel_type( value val ) : _value( convert( val ) ) {}
        loglevel_type( const String& str ) : _value( str ) {}

        static value convert( const String& str ) {
            return ( value )::xio::util::binary_search( str, _literals, 7, 0 );
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

    class logger_type
    {
    public:
        modifiers_type modifiers;
        String name;
        loglevel_type level;
        optional< String > target;
        optional< String > module;
    };

    class logging_type
    {
    public:
        logging_type() : level( loglevel_type::debug_literal ) {}
        std::vector< logger_type > logger;
        loglevel_type level;
    };

    class garbage_collector_interval_type
    {
    public:
        garbage_collector_interval_type() : seconds( 180L ) {}
        Long seconds;
    };

    class garbage_collector_type
    {
    public:
        garbage_collector_interval_type interval;
    };

    class session_timeout_type
    {
    public:
        session_timeout_type() : seconds( 3600L ) {}
        Long seconds;
    };

    class session_max_lazy_function_count_type
    {
    public:
        session_max_lazy_function_count_type() : number( 20 ) {}
        Int number;
    };

    class session_type
    {
    public:
        session_timeout_type timeout;
        session_max_lazy_function_count_type max_lazy_function_count;
    };

    class quota_type
    {
    public:
        quota_type() : enable( false ) {}
        Boolean enable;
    };

    class autosave_interval_type
    {
    public:
        autosave_interval_type() : seconds( 3600L ) {}
        Long seconds;
    };

    class autosave_type
    {
    public:
        autosave_interval_type interval;
    };

    class module_type
    {
    public:
        module_type() : critical( false ) {}
        String name;
        optional< String > config;
        Boolean critical;
    };

    class extensions_type
    {
    public:
        extensions_type() : path( "extension/" ) {}
        std::vector< module_type > extension;
        String path;
    };

    class wss_configuration_type
    {
    public:
        logging_type logging;
        garbage_collector_type garbage_collector;
        session_type session;
        quota_type quota;
        autosave_type autosave;
        extensions_type extensions;
        Decimal version;
    };

    class server_configuration
    {
    public:
        poptional< wss_configuration_type > wss_configuration;
    };

}
#endif

