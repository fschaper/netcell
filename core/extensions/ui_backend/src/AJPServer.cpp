/**
*  \file
*  Copyright (C) 2006-2010 Jedox AG, Freiburg i.Br., Germany
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
*  Predrag Malicevic <predrag.malicevic@develabs.com>
*/

#include "precompiled_header.hpp"
#include "AJPServer.hpp"
#include "wss/core_dump_handler.hpp"


void AJPServer::SocketLog::error ( ISocketHandler*, Socket* sock, const std::string& call, int err, const std::string& sys_err, loglevel_t lvl )
{
    switch ( lvl ) {
        case LOG_LEVEL_WARNING:
        case LOG_LEVEL_INFO:
            break;

        case LOG_LEVEL_ERROR:
        case LOG_LEVEL_FATAL:
            if ( call != "close" ) {
                LOG_UI_BACKEND_ERROR( "socket error in " << call << "(): " << sys_err << " (" << err << ")" );
            }
            break;
    }
}

AJPServer::ConnHandler::ConnHandler ( SocketLog* log )
    : SocketHandler( log )
{}

AJPServer::ConnHandler::ConnHandler (  IMutex& m, ISocketHandler& ish, StdLog* l )
    : SocketHandler( m, ish, l )
{}

ISocketHandler* AJPServer::ConnHandler::Create ( StdLog* log )
{
    ConnHandler* ish = new AJPServer::ConnHandler( ( SocketLog* )( log ) );
    ish->server( this->m_ajp_server );
    return ish;
}

ISocketHandler* AJPServer::ConnHandler::Create ( IMutex& m, ISocketHandler& sh, StdLog* l )
{
    ConnHandler* ish = new AJPServer::ConnHandler( m, sh, ( SocketLog* )( l ) );
    return ish;
}

bool AJPServer::ConnHandler::OkToAccept ( Socket* sock )
{
    return m_ajp_server->is_running() && GetCount() <= MAX_CONNECTION_COUNT;
}

void AJPServer::ConnHandler::server( const AJPServer* server )
{
    m_ajp_server = server;
}

void AJPServer::ConnHandler::Shutdown ()
{
    for ( socket_m::iterator it = m_sockets.begin(), it_end = m_sockets.end(); it != it_end; ++it ) {
        Socket* sock = dynamic_cast<Socket*>( it->second );

        if ( sock ) {
            sock->SetCloseAndDelete();
        }
    }
}

bool AJPServer::ShutdownInitiator::operator() () const
{
    static AJPServer& instance = AJPServer::instance();

    if ( instance.is_running() ) {
        instance.shutdown();
    }

    return instance.is_halted();
}

bool AJPServer::bind_ipaddress ( const std::string& hostname, unsigned short port )
{
    ListenSocket<AJPConnection> *sock = new ListenSocket<AJPConnection>( m_conn_handler );
    sock->SetDeleteByHandler();

    if ( sock->Bind( hostname, port, BACKLOG_COUNT ) != 0 ) {
        LOG_UI_BACKEND_ERROR( "bind on " << hostname << ":" << port << " failed" );
        return false;
    }


    m_conn_handler.Add( sock );

    return true;
}

void AJPServer::run ()
{
    core_dump_handler::register_handler();
    if ( is_halted() ) {
        LOG_UI_BACKEND_INFO( "starting up!" );
        boost::thread::thread( boost::bind( &AJPServer::server_loop, this ) );
    }
}

bool AJPServer::is_running () const
{
    return SERVER_RUNNING == m_server_state;
}

bool AJPServer::is_shutting_down () const
{
    return SERVER_SHUTTING_DOWN == m_server_state;
}

bool AJPServer::is_halted () const
{
    return SERVER_HALTED == m_server_state;
}

void AJPServer::shutdown ()
{
    if ( is_running() ) {
        LOG_UI_BACKEND_INFO( "shutting down!" );
        m_server_state = SERVER_SHUTTING_DOWN;
    }
}

void AJPServer::server_loop ()
{
    name_thread( "ui_backend ajp server" );

    m_server_state = SERVER_RUNNING;
    while ( m_conn_handler.GetCount() ) {
        m_conn_handler.Select( 1, 0 );
        boost::thread::yield();

        if ( SERVER_RUNNING != m_server_state ) {
            m_conn_handler.Shutdown();
        }
    }

    m_server_state = SERVER_HALTED;
    LOG_UI_BACKEND_INFO( "server halted" );
}

AJPServer::AJPServer ()
    : m_server_state( SERVER_HALTED )
    , m_conn_handler( new SocketLog() )
{
    m_conn_handler.server( this );
    unsigned int cpu_core_count = 2;
#ifdef WIN32
    SYSTEM_INFO sysinfo;
    GetSystemInfo( &sysinfo );
    cpu_core_count = sysinfo.dwNumberOfProcessors;
#elif defined(LINUX)
    cpu_core_count = sysconf( _SC_NPROCESSORS_ONLN );
#endif
    m_conn_handler.SetNumberOfThreads( cpu_core_count );
}


