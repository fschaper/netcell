/**
 *  \file
 *  Copyright (C) 2006-2010 Jedox AG
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
 *
 *  \author
 *  Florian Schaper <florian.schaper@jedox.com>
 */

#include "precompiled_header.hpp"
#include "configuration.hpp"
#include "wss/version.hpp"
#include "wss/define.hpp"
#include "wss/module_registry.hpp"
#include "wss/extension_module_load_exception.hpp"
#include "wss/session_handler.hpp"
#include "wss/server_defaults.hpp"
#include "wss/server.hpp"
#include "wss/core_dump_handler.hpp"
/*
#include "wss/memory.hpp"
*/

#include "catalogue_reader.hpp"
#include "server_configuration.hpp"
#include "server_configuration_parser.hpp"
#include "core_logging.hpp"
#include "message_defines.hpp"
#include "auto_save.hpp"
#ifdef WIN32
#include "win32_service.hpp"
#endif
#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <boost/filesystem.hpp>
#   include <boost/program_options.hpp>
#   include <boost/assign/list_of.hpp>
#   include <boost/foreach.hpp>
#   include <iostream>
#endif

#if defined(__unix__)
#include <pwd.h>
#include <grp.h>
#define EXTENSION_SUFFIX ".so"
#elif defined( WIN32 )
#ifdef _DEBUG
#define EXTENSION_SUFFIX "_d.dll"
#else
#define EXTENSION_SUFFIX ".dll"
#endif
#endif

configuration::configuration()
{}

bool configuration::configure( int argc, char* argv[] )
{
    namespace bfs = boost::filesystem;
    namespace bpo = boost::program_options;

    std::string config_dir;
    std::string config_file;
    std::string locale_dir;
    std::string modules_dir;
    std::string loggers;
    std::string test;
#ifdef __unix__
    std::string switch_account;
#endif

#ifdef WIN32
    std::string service_name;
    std::string display_name;
#endif

    std::string font_dir;

    bfs::path daemon_path( argv[0] );
    bpo::options_description command_line_description( "\nusage: " + bfs::basename( daemon_path ) + " [options]", console_line_length );
    command_line_description.add_options()
    ( "etcdir,d", bpo::value<std::string>( &config_dir )->default_value( "." ), "configuration files directory path" )
    ( "config,c", bpo::value<std::string>( &config_file )->default_value( "config.xml" ), "main configuration file" )
    ( "locale,l", bpo::value<std::string>( &locale_dir )->default_value( "locale" ), "localizations directory path" )
    ( "extensions,e", bpo::value<std::string>( &modules_dir )->default_value( "extension" ), "extensions directory path" )
    ( "fontdir,f", bpo::value<std::string>( &font_dir )->default_value( "font" ), "font files directory path" )
#ifdef __unix__
    ( "user,u", bpo::value<std::string>( &switch_account )->default_value( "" ), "username for unprivileged uid/gid switch" )
#endif
#ifdef WIN32
    ( "install_service,i", "install as windows service" )
    ( "service_name,N", bpo::value<std::string>( &service_name )->default_value( "PaloSuiteCoreService" ), "name of the service" )
    ( "display_name,D", bpo::value<std::string>( &display_name )->default_value( "Palo Suite Core Service" ), "display name of the service" )
    ( "uninstall_service,u", "uninstall windows service" )
    ( "service,x", "start as service (not to be called directly)" )
    ( "no_report,n", "do not start the crash_report dialog if the process terminates unexpectedly" )
#endif
    ( "version,V", "display the version numbers" )
    ( "help,h", "display this help message" );

    bpo::options_description configuration_file_description( "\nconfiguation file format\n", console_line_length );

    try {
        bpo::variables_map var_map;
        bpo::store( bpo::parse_command_line( argc, argv, command_line_description ), var_map );
        bpo::notify( var_map );

#ifdef __unix__
        // switch uid/gid to another account
        if ( switch_account != "" ) {
            DETAILMSG( "switching uid/gid to account '" << switch_account << "' ... " );

            if ( getuid() != 0 ) {
                LOG_CORE_ERROR( "has to be started as root" );
            }

            struct passwd* pw;
            pw = getpwnam( switch_account.c_str() );
            if ( !pw ) {
                LOG_CORE_ERROR( "no such account found" );
            }

            gid_t gids[1] = { pw->pw_gid };
            if ( ( setgroups( 1, gids ) == -1 ) || ( setgid( pw->pw_gid ) == -1 ) ) {
                LOG_CORE_ERROR( "unable to set group id (" << pw->pw_gid << ")" );
            }

            if ( setuid( pw->pw_uid ) == -1 ) {
                LOG_CORE_ERROR( "unable to set user id (" << pw->pw_uid << ")" );
            }
        }
#endif

#ifdef WIN32
        if ( var_map.count( "i" ) || var_map.count( "install_service" ) ) {
            win32_service().cmd_install_service( service_name, display_name );
            return false;
        }

        if ( var_map.count( "u" ) || var_map.count( "uninstall_service" ) ) {
            win32_service().cmd_remove_service( service_name );
            return false;
        }

        if ( var_map.count( "x" ) || var_map.count( "service" ) ) {
            core_dump_handler::enable_crash_reporting( false );
            win32_service().cmd_run_service();
            return false;
        }
#endif

        if ( var_map.count( "no_report" ) || var_map.count( "n" ) ) {
            core_dump_handler::enable_crash_reporting( false );
        }

        if ( var_map.count( "V" ) || var_map.count( "version" ) ) {
            CONSOLE_OUTL( "server version:  " << WSS_VERSION_STRING );
            CONSOLE_OUTL( "build date:      " << WSS_BUILD_DATE_STRING );
            CONSOLE_OUTL( "repository date: " << WSS_REPO_DATE_STRING );
            return false;
        }

        if ( var_map.count( "h" ) || var_map.count( "help" ) ) {
            CONSOLE_OUTL( command_line_description );
            return false;
        }

        std::ifstream config_file_stream( ( bfs::path( config_dir ) / bfs::path( config_file ) ).string().c_str(), std::ios::in );
        if ( ! config_file_stream.good() ) {
            ERRMSG( "failed to open the configuration file '" <<  ( bfs::path( config_dir ) / bfs::path( config_file ) ).string() << "'!" );
            CONSOLE_OUTL( "aborting." );
            return false;
        }

        // parse xml configuration
        server_settings::server_configuration sc;
        ::xio::xml::binding::parser().parse_doc( config_file_stream, sc );
        config_file_stream.close();

        if ( ! sc.wss_configuration.present() ) {
            CONSOLE_OUTL( "invalid configuration file." );
            CONSOLE_OUTL( "aborting." );
            return false;
        }

        server_settings::wss_configuration_type& config = sc.wss_configuration.get();

        // (fschaper) memory quota hooks. this methods will be called for
        // every allocation / deallocation via new and delete operators.
        if ( config.quota.enable == true ) {
            /*
                        allocation_callback( &allocation_tracking::track_allocation );
                        deallocation_callback( &allocation_tracking::track_deallocation );
            */
        }

        // configure logging framework
        CONSOLE_OUTL( "registering system loggers" );
        DETAILMSG( "setting global log level to '" << static_cast<const std::string&>( config.logging.level ) << "'" );
        try {
            logging::logger::instance().level( logging::log_level_factory::instance().create( config.logging.level ) );
        } catch ( const creation_exception& ) {
            ERRMSG( "failed to set global log level. will default to 'error'." );
        }
        foreach( const server_settings::logger_type & logger_section, config.logging.logger ) {
            INFOMSGL( "registering logger '" << logger_section.name << "' with loglevel '" << static_cast<const std::string&>( logger_section.level ) << "'" );
            try {
                logging::i_logger::shared_log_handler_type handler( logging::logger_factory::instance().create( logger_section.name ) );
                handler->level( logging::log_level_factory::instance().create( logger_section.level ) );
                if ( logger_section.target.present() ) {
                    handler->target( logger_section.target.get() );
                }
                foreach( const server_settings::modifier_type & modifier_section, logger_section.modifiers.modifier ) {
                    DETAILMSG( "applying modifier '" << modifier_section.name << "'" );
                    try {
                        handler->register_modifier( ( modifier_section.priority.present() ? modifier_section.priority.get() : 0 ), logging::shared_log_modifier_type( logging::modifier_factory::instance().create( modifier_section.name ) ) );
                    } catch ( const creation_exception& ) {
                        ERRMSG( "unknown modifier!" );
                    }
                }
                logging::logger::instance().register_handler( handler );
            } catch ( const creation_exception& ) {
                ERRMSG( "unknown handler or unsupported loglevel!" );
            }
        }

        //print this message again to the loggers!
        LOG_CORE_INFO( "palo web core server version " WSS_VERSION_STRING );

        std::string prefix = config.extensions.path;

        // load extension modules
        CONSOLE_OUTL( "registering extensions" );
        if ( config.extensions.extension.size() == 0 ) {
            return false;
        }
        foreach( const server_settings::module_type & module_section, config.extensions.extension ) {
            try {
                INFOMSGL( "registering extension '" << module_section.name << "'" );
                std::string module_name = prefix + module_section.name +  EXTENSION_SUFFIX;
                module_registry::instance().register_extension( module_name, ( module_section.config.present() ? module_section.config.get() : "" ) );
            } catch ( const extension_module_load_exception& ) {
                ERRMSG( "registering extension '" << module_section.name << "' failed!" );
                if ( module_section.critical ) {
                    return false;
                }
            }
        }

        // configure the session manager
        server::instance().session_handler().session_timeout( boost::posix_time::seconds( config.session.timeout.seconds ) );
        session::max_lazy_function_count = config.session.max_lazy_function_count.number ;

        // configure the function catalog's
        catalogue_reader::parse_directory_tree( "function_table.xml", locale_dir );

        //configure autosave
        auto_save::instance().set_interval( config.autosave.interval.seconds );

    } catch ( const bpo::unknown_option& ) {
        CONSOLE_OUTL( command_line_description );
        return false;
    } catch ( const bpo::invalid_command_line_syntax& ) {
        CONSOLE_OUTL( command_line_description );
        return false;
    }

    return true;
}
