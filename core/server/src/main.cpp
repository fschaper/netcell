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

#include <xercesc/util/PlatformUtils.hpp>

#include "wss/server.hpp"
#include "wss/module_registry.hpp"
#include "wss/version.hpp"
#include "wss/named_thread.hpp"
#include "wss/locale.hpp"
#include "wss/translation_table.hpp"
#include "wss/core_dump_handler.hpp"

//needed because we need to initialize boost::flyweight objects in a single threaded environment
#include "wss/flyweight_types.hpp"

#include "configuration.hpp"
#include "message_defines.hpp"
#include "core_logging.hpp"

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   if defined( WIN32 )
#       define WIN32_LEAN_AND_MEAN
#      include <Windows.h>
#   endif
#   include <iostream>
#endif

#if defined(__unix__)
#   include <stdlib.h>
#   include <signal.h>
#   include <sys/types.h>
#   include <unistd.h>
#   include <pwd.h>
#   include <grp.h>
#elif defined( WIN32 )
#   define WIN32_LEAN_AND_MEAN
#   include <Windows.h>
#endif

#if defined( WIN32 )

/*!
 * \brief
 * callback handler to initiate proper shutdown on console
 * termination requests
 *
 * \param event
 * reason for termination
 *
 * \see
 * main
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
int __stdcall console_termination_handler( unsigned long event )
{
    switch ( event ) {
        case CTRL_C_EVENT:
        case CTRL_BREAK_EVENT:
        case CTRL_SHUTDOWN_EVENT:
        case CTRL_LOGOFF_EVENT:
        case CTRL_CLOSE_EVENT:
            static server& server_instance = server::instance();
            if ( server_instance.current_state() == server::state::running ) {
                LOG_CORE_INFO( "console termination request received, proceeding with server shutdown ..." );
                server_instance.shutdown( true );
            }
            break;
    }
    return 1;
}

void synchronize_service_status();

#elif __unix__
void signal_handler( int sig_num )
{
    static server& server_instance = server::instance();
    if ( server_instance.current_state() == server::state::running ) {
        LOG_CORE_INFO( "console termination request received, proceeding with server shutdown ..." );
        server_instance.shutdown();
    }
}
#endif

/*!
 * \brief
 * server entry point.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
int main( int argc, char* argv[] )
{
    //initialize some data we need to be initialized before any threads are running
    internal_flyweights::init();

    core_dump_handler::register_handler();

    xercesc::XMLPlatformUtils::Initialize();

    // (fschaper) name the process for debugging.
    name_thread( "server main" );

#if defined(WIN32) && defined(_DEBUG) && defined(CRT_DEBUGGING)
    // enable CRT memory checking under windows debug builds
    _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

#if defined(WIN32)

    bool is_service = false;
    bool is_from_scm = false;
    for ( int i = argc; i > 0; i-- ) {
        std::string s = argv[i-1];
        if ( "-x" == s ) {
            is_service = true;
        }

        if ( "--" == s ) {
            is_from_scm = true;
        }

    }

    if ( !is_from_scm && !is_service ) {
        SetConsoleCtrlHandler( static_cast<PHANDLER_ROUTINE>( &console_termination_handler ), 1 );
    }
#elif defined(__unix__)
    // install SIGTERM signal handler
    signal( SIGINT, signal_handler );
#endif

    CONSOLE_OUTL( "palo web core server version " WSS_VERSION_STRING );

    static server& server = server::instance();

    // configure the server based on command line options
    // and configuration file
    bool successful = false;

    try {
        successful = configuration::instance().configure( argc, argv );
    } catch ( const std::exception& e ) {
        CONSOLE_OUTL( "error while reading configuration file!" << e.what() );
        LOG_CORE_ERROR( "palo web core server version " << e.what() );
    }
    if ( ! successful ) {
        return 1;
    }

    // TODO: (fschaper) this has to go into the locale definition
    {
        translation_map::error_mapping::type error_map;
        error_map.insert( translation_map::error_mapping::entity_type( variant::error_null, "#null!" ) );
        error_map.insert( translation_map::error_mapping::entity_type( variant::error_div_null, "#div/0!" ) );
        error_map.insert( translation_map::error_mapping::entity_type( variant::error_value, "#value!" ) );
        error_map.insert( translation_map::error_mapping::entity_type( variant::error_ref, "#ref!" ) );
        error_map.insert( translation_map::error_mapping::entity_type( variant::error_name, "#name!" ) );
        error_map.insert( translation_map::error_mapping::entity_type( variant::error_num, "#num!" ) );
        error_map.insert( translation_map::error_mapping::entity_type( variant::error_n_a, "#n/a" ) );
        translation_table::instance()[ locale::create( "en-*" ) ]->error_translation( error_map );
    }
    {
        translation_map::error_mapping::type error_map;
        error_map.insert( translation_map::error_mapping::entity_type( variant::error_null, "#null!" ) );
        error_map.insert( translation_map::error_mapping::entity_type( variant::error_div_null, "#div/0!" ) );
        error_map.insert( translation_map::error_mapping::entity_type( variant::error_value, "#wert!" ) );
        error_map.insert( translation_map::error_mapping::entity_type( variant::error_ref, "#bezug!" ) );
        error_map.insert( translation_map::error_mapping::entity_type( variant::error_name, "#name!" ) );
        error_map.insert( translation_map::error_mapping::entity_type( variant::error_num, "#zahl!" ) );
        error_map.insert( translation_map::error_mapping::entity_type( variant::error_n_a, "#nv" ) );
        translation_table::instance()[ locale::create( "de-*" ) ]->error_translation( error_map );
    }
    {
        translation_map::error_mapping::type error_map;
        error_map.insert( translation_map::error_mapping::entity_type( variant::error_null, "#nul!" ) );
        error_map.insert( translation_map::error_mapping::entity_type( variant::error_div_null, "#div/0!" ) );
        error_map.insert( translation_map::error_mapping::entity_type( variant::error_value, "#valeur!" ) );
        error_map.insert( translation_map::error_mapping::entity_type( variant::error_ref, "#ref!" ) );
        error_map.insert( translation_map::error_mapping::entity_type( variant::error_name, "#nom!" ) );
        error_map.insert( translation_map::error_mapping::entity_type( variant::error_num, "#nombre!" ) );
        error_map.insert( translation_map::error_mapping::entity_type( variant::error_n_a, "#n/a" ) );
        translation_table::instance()[ locale::create( "fr-*" ) ]->error_translation( error_map );
    }
#if defined(WIN32)
    if ( is_service ) {
        //only allow configuration here. the start/stop will be handled by the scm
        return 1;
    }
#endif

    // clean temp directory
    {
        CONSOLE_OUTL( "cleaning up tmp directory ... " );
        try {
            boost::filesystem::wpath tmp_dir( L"tmp" );
            boost::filesystem::wdirectory_iterator tmp_dir_end;// default construction yields past-the-end
            for ( boost::filesystem::wdirectory_iterator tmp_dir_it( tmp_dir ); tmp_dir_it != tmp_dir_end; ++tmp_dir_it ) {
                boost::filesystem::remove_all( *tmp_dir_it );
            }
        } catch ( const std::exception& e ) {
            LOG_CORE_ERROR( "failed to clean tmp directory: " << e.what() );
        }
    }

    // start the server and notify all extensions
    server.startup();
    CONSOLE_OUTL( "ready." );
    LOG_CORE_INFO( "ready." );
#if defined(WIN32)
    synchronize_service_status();
#endif

    // wait till the server gets the shutdown signal.
    server.wait_on_shutdown();

    core_dump_handler::disarm();

    CONSOLE_OUTL( "Done." << std::endl );
#if defined(WIN32)
    synchronize_service_status();
#endif
    xercesc::XMLPlatformUtils::Terminate();
    return 0;

}
