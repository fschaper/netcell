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
 *  Frieder Hofmann <frieder.hofmann@jedox.com>
 */

#include "precompiled_header.hpp"
#include "wss/memory_garbage_collector.hpp"

#include "wss/session_handler.hpp"
#include "wss/server.hpp"
#include "wss/core_dump_handler.hpp"
#include "wss/named_thread.hpp"

#include "core_logging.hpp"
#include "release_pooled_memory.hpp"

memory_garbage_collector::memory_garbage_collector( server& server )
    : m_collector_mutex()
    , m_state_mutex()
    , m_state( halted )
    , m_server( server )
{
    server.on_server_startup.connect( boost::bind( &memory_garbage_collector::start, this ) );
    server.on_server_shutdown.connect( boost::bind( &memory_garbage_collector::stop, this ) );
}

void memory_garbage_collector::release_memory()
{
    name_thread( "memory garbage collector" );
    boost::xtime xt;
    while ( running == m_state ) {
        {
            locked_session_handler_holder sh = m_server.session_handler().locked_session_handler();
            if ( sh.empty() ) {

                LOG_CORE_DEBUG( "running memory garbage collector." );
                m_server.unload_expired_applications();
                release_pooled_memory::release_all();
                release_pooled_memory::release_all( true );
            }
        }

        boost::xtime_get( &xt, boost::TIME_UTC );
        xt.sec += 10;

        lock_type time_lock( m_collector_mutex );
        m_wait_for_shutdown.timed_wait( time_lock, xt );
    }
    m_state = halted;
}

memory_garbage_collector::garbage_collector_state memory_garbage_collector::state()
{
    lock_type state_lock( m_state_mutex );
    return m_state;
}

void memory_garbage_collector::start()
{
    core_dump_handler::register_handler();
    LOG_CORE_INFO( "memory garbage collector starting up!" );
    if ( running != m_state ) {
        lock_type state_lock( m_state_mutex );
        if ( running != m_state ) {
            m_state = running;
            boost::thread::thread( boost::bind( &memory_garbage_collector::release_memory, this ) );
        }
    }
}

bool memory_garbage_collector::stop()
{
    if ( running == m_state ) {
        lock_type state_lock( m_state_mutex );
        if ( running == m_state ) {
            LOG_CORE_INFO( "memory garbage collector shutting down!" );
            m_state = shutdown;
            // notify the release_memory function, that we're stopping now
            m_wait_for_shutdown.notify_all();
        }
    }
    return halted == m_state;
}
