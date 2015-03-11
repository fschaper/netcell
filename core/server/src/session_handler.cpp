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
#include "wss/invalid_session_exception.hpp"
#include "wss/session_handler.hpp"
#include "wss/session.hpp"
#include "wss/server.hpp"
#include "wss/core_dump_handler.hpp"
#include "wss/named_thread.hpp"

#include "core_logging.hpp"

session_handler::session_handler( server& server )
    : m_collector_mutex()
    , m_state_mutex()
    , m_state( halted )
    , m_timeout( boost::posix_time::seconds( 0 ) )
{
    server.on_server_startup.connect( boost::bind( &session_handler::start, this ) );
    server.on_server_shutdown.connect( boost::bind( &session_handler::stop, this ) );
}

locked_session session_handler::create( const ::locale& l, const std::string& username, const std::string password, const group_set_type& groups )
{
    shared_session_type s( session::create( l, username, password, groups ) );
    LOG_CORE_DEBUG( "create new session [" << s->uuid() << "]" );
    {
        write_lock  lock( m_sessions_mutex );
        m_session_map[ s->uuid() ] = s;
    }
    return locked_session( s );
}

locked_session session_handler::get( const std::string& uuid )
{
    try {
        return get( boost::lexical_cast<uuid_type>( uuid ) );
    } catch ( const boost::bad_lexical_cast& ) {
        throw invalid_session_exception();
    }
}

locked_session session_handler::get( const uuid_type& uuid )
{
    LOG_CORE_DEBUG( "requesting session [" << uuid << "]" );

    shared_session_type s;
    {
        read_lock   lock( m_sessions_mutex );
        session_map_type::iterator it( m_session_map.find( uuid ) );
        if ( m_session_map.end() == it  ) {
            LOG_CORE_WARNING( "invalid session [" << uuid << "]" );
            throw invalid_session_exception();
        }
        s = it->second;
        s->revitalize();
    }

    // (session) this "arms" the current thread with the session object
    // so it can be retrieved from TLS
    s->associate_with_current_thread();
    return locked_session( s );
}

void session_handler::invalidate_sessions()
{
    name_thread( "session invalidator" );
    boost::xtime xt;
    while ( running == m_state ) {
        {
            LOG_CORE_DEBUG( "running session invalidator." );
            // todo:
            // until we can get boost 1.44 we'll only use write_lock for VS10
            // https://svn.boost.org/trac/boost/ticket/2501 is fixed for 1.44
            // there is also a patch available https://svn.boost.org/trac/boost/attachment/ticket/2501/2501.patch
#if defined(USING_VS_2010)
            write_lock   lock( m_sessions_mutex );
#else
            read_write_lock   lock( m_sessions_mutex );
#endif
            session_map_type::iterator current( m_session_map.begin() );
            session_map_type::iterator end( m_session_map.end() );
            while ( current != end ) {
                if ( current->second->has_timed_out() ) {
                    LOG_CORE_INFO( "invalidating session [" << current->second->uuid() << "]" );
#if !defined(USING_VS_2010)
                    upgrade_lock    write( lock );
#endif
                    m_session_map.erase( current++ );
                } else {
                    current++;
                }
            }
        }

        boost::xtime_get( &xt, boost::TIME_UTC );
        xt.sec += 20;

        lock_type time_lock( m_collector_mutex );
        m_wait_for_shutdown.timed_wait( time_lock, xt );
    }
    write_lock  lock( m_sessions_mutex );
    m_session_map.clear();
    m_state = halted;
}


void session_handler::start()
{
    core_dump_handler::register_handler();
    LOG_CORE_INFO( "session handler starting up!" );
    if ( running != m_state ) {
        lock_type state_lock( m_state_mutex );
        if ( running != m_state ) {
            m_state = running;
            boost::thread::thread( boost::bind( &session_handler::invalidate_sessions, this ) );
        }
    }
}

bool session_handler::stop()
{
    if ( running == m_state ) {
        lock_type state_lock( m_state_mutex );
        if ( running == m_state ) {
            LOG_CORE_INFO( "session handler shutting down!" );
            m_state = shutdown;
            // notify the invalidate:sessions function, that we're stopping now
            m_wait_for_shutdown.notify_all();
        }
    }
    return halted == m_state;
}

const boost::posix_time::time_duration& session_handler::session_timeout()
{
    return m_timeout;
}

void session_handler::session_timeout( const boost::posix_time::time_duration& timeout )
{
    m_timeout = timeout;
}

void session_handler::remove_session( const std::string& uuid )
{
    remove_session( boost::lexical_cast< uuid_type >( uuid ) );
}

void session_handler::remove_session( const uuid_type& uuid )
{
    LOG_CORE_DEBUG( "removing session [" << uuid << "]" );

    write_lock  lock( m_sessions_mutex );
    session_map_type::iterator it( m_session_map.find( uuid ) );
    if ( m_session_map.end() != it ) {
        m_session_map.erase( it );
    }
}

void session_handler::autosave()
{
    std::vector< shared_session_type > active_sessions;
    {
        read_lock  lock( m_sessions_mutex );

        foreach( key_val_type crt,  m_session_map ) {
            active_sessions.push_back( crt.second );
        }
    }

    foreach( shared_session_type & s, active_sessions ) {
        locked_session( s )->autosave();
    }
}

void session_handler::clear_connection_cache_on_all_sessions( session& calling_session )
{
    // this function isn't called often so we play safe here and
    // don't do anything to the session while we have an active lock
    std::vector< shared_session_type > active_sessions;
    {
        read_lock  lock( m_sessions_mutex );

        foreach( key_val_type crt,  m_session_map ) {
            if ( crt.second.get() != &calling_session ) {
                active_sessions.push_back( crt.second );
            }
        }
    }

    calling_session.clear_connection_cache();

    foreach( shared_session_type & s, active_sessions ) {
        locked_session( s )->clear_connection_cache();
    }
}

locked_session_handler_holder session_handler::locked_session_handler()
{
    return locked_session_handler_holder( *this );
}

bool session_handler::empty()
{
    read_lock lock( m_sessions_mutex );
    return m_session_map.empty();
}

bool session_handler::empty_no_locking() const
{
    return m_session_map.empty();
}


bool locked_session_handler_holder::empty() const
{
    //session handler is already locked, so no need to lock again
    return m_session_handler.empty_no_locking();
}

locked_session_handler_holder::~locked_session_handler_holder()
{
    const_cast<boost::shared_mutex&>( m_session_handler.m_sessions_mutex ).unlock_shared();
}

locked_session_handler_holder::locked_session_handler_holder( const session_handler& session_handler )
    : m_session_handler( session_handler )
{
    const_cast<boost::shared_mutex&>( m_session_handler.m_sessions_mutex ).lock_shared();
}
