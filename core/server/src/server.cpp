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
#include <stdlib.h>
#include "wss/server.hpp"
#include "core_logging.hpp"
#include "release_pooled_memory.hpp"
#include "wss/memory_garbage_collector.hpp"
#include "wss/core2_compatibility.hpp"
#include "wss/core_dump_handler.hpp"

server::server()
    : m_session_handler ()
{
    m_session_handler.reset( new ::session_handler( *this ) );
    m_garbage_collector.reset( new ::memory_garbage_collector( *this ) );
    *m_server_state.lock() = state::halted;
    *m_collector_state.lock() = state::halted;
}

server::~server()
{}

void server::startup()
{
    if ( state::halted == locked_state_type::access( m_server_state ) ) {
        LOG_CORE_INFO( "starting up server." );
        start();
        ( *m_server_state.lock() ) = state::running;
        ( *m_collector_state.lock() ) = state::running;
        on_server_startup();
    }
}

void server::shutdown( bool terminate )
{
    if ( state::running == locked_state_type::access( m_server_state ) ) {
        LOG_CORE_INFO( "shutting down server." );
        ( * m_server_state.lock() ) = state::shutting_down;
        ( * m_collector_state.lock() ) = state::shutting_down;
        while ( false == on_server_shutdown() ) {
            boost::thread::yield();
        }
        unload();
        ( * m_server_state.lock() ) = state::halted;
        ( * m_collector_state.lock() ) = state::halted;
        LOG_CORE_INFO( "server halted." );
        core_dump_handler::enable_crash_reporting( false );
        m_server_been_shut_down.notify_all();
        m_await_next_collector_run.notify_all();
        // win console termination workaround
#if defined( _WIN32 )
        if ( terminate ) {
            DWORD pId = GetCurrentProcessId();
            HANDLE pHnd = OpenProcess( PROCESS_TERMINATE, false, pId );
            TerminateProcess( pHnd, 0 );
            CloseHandle( pHnd );
        }
#endif

    }
}

void server::wait_on_shutdown() const
{
    // wait for the server to reach halted state.
    {
        locked_state_type::lock_type lock( m_server_state.unguard().mutex );
        while ( state::halted != m_server_state.unguard().object ) {
            m_server_been_shut_down.wait( lock );
        }
    }
    // wait for collector to reach halted state.
    {
        locked_state_type::lock_type lock( m_collector_state.unguard().mutex );
        while ( state::halted != m_collector_state.unguard().object ) {
            m_await_next_collector_run.wait( lock );
        }
    }
}

void server::unload()
{
    LOG_CORE_DEBUG( "server - unloading objects." );
    halt();
    foreach( const shared_application_type & app, locking_iterator() ) {
        app->unload();
    }
    release_pooled_memory::release_all();
    release_pooled_memory::release_all( true );
    clear();
}

server::state::type server::current_state() const
{
    return m_server_state.lock();
}

function_registry& server::functions()
{
    return function_registry::instance();
}

filter_registry& server::filters()
{
    return filter_registry::instance();
}

const ::server_defaults& server::server_defaults() const
{
    return m_server_defaults;
}

::server_defaults& server::server_defaults()
{
    return m_server_defaults;
}

void server::server_defaults( const ::server_defaults& val )
{
    m_server_defaults = val;
}

::object_registry& server::object_registry()
{
    return m_object_registry;
}

::session_handler& server::session_handler()
{
    return *m_session_handler;
}

::extension_registry& server::extension_registry()
{
    return m_extension_registry;
}

void server::collector_run()
{
    boost::xtime xt;
    while ( state::running == *locked_state_type::access( m_collector_state ) ) {
        LOG_CORE_DEBUG( "running garbage collector." );
        {
            if ( m_garbage_collector->state() == m_garbage_collector->running ) {
                continue;
            }

            unload_expired_applications();
        }

        boost::xtime_get( &xt, boost::TIME_UTC );
        xt.sec += collector_sleep_time;

        locked_state_type::lock_type time_lock( m_collector_state.unguard().mutex );
        m_await_next_collector_run.timed_wait( time_lock, xt );
    }
    ( *m_collector_state.lock() ) = state::halted;
}

void server::unload_expired_applications()
{
    server::iterator_pair li( locking_iterator() );
    for ( server::iterator_pair::iterator it = li.begin(), end = li.end(); it != end;  ) {
        const shared_application_type& current = *it;
        // if only we and the container are holding references to the application
        // remove the application from memory. here we have to subtract all contained workbooks
        // because those do also contain a live reference.
        if ( ( current.use_count() - current->count() ) == 2 ) {
            LOG_CORE_INFO( "garbage collector unloading application [" << boost::lexical_cast<std::string>( current->uuid() ) << "] from memory." );
            uuid_type to_remove = current->uuid();
            ++it;
            remove( to_remove );
        } else {
            ++it;
        }
    }
}

ws_elem_id_type server::next_id()
{
#ifdef _CORE2_COMPATIBILITY_ON_UUIDS_
    return boost::uuids::nil_uuid();
#else
    return BOOST_INTERLOCKED_INCREMENT( &m_id_counter );
#endif // _CORE2_COMPATIBILITY_ON_UUIDS_
}
