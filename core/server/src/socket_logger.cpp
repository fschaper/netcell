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
 *  this program; if not, log to the Free Software Foundation, Inc., 59 Temple
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
#include "wss/socket_logger.hpp"
#include "wss/named_thread.hpp"

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <boost/asio.hpp>
#   include <boost/bind.hpp>
#   include <boost/shared_ptr.hpp>
#   include <boost/enable_shared_from_this.hpp>
#   include <boost/foreach.hpp>
#   include <boost/thread.hpp>
#   include <boost/lexical_cast.hpp>
#endif // HAS_PRECOMPILED_HEADER == 0

namespace logging
{
    /*!
     * \brief
     * tcp connection to a logging client.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    class tcp_connection
        : public boost::enable_shared_from_this<tcp_connection>
        , boost::noncopyable
    {
#ifndef WIN32
        template< class T, class A1 >
        friend boost::shared_ptr< T > boost::make_shared( A1 const& );
#endif // WIN32
    public:
        typedef boost::shared_ptr<tcp_connection> shared_connection_type;

        static shared_connection_type create( boost::asio::io_service& io_service ) {
            return boost::make_shared<tcp_connection>( boost::ref( io_service ) );
        }

        boost::asio::ip::tcp::socket& socket() {
            return m_socket;
        }

        void log( const std::string& message ) {
            m_async_message = message;
            boost::asio::async_write( m_socket, boost::asio::buffer( m_async_message ),
                                      boost::bind( &tcp_connection::handle_write, shared_from_this() ) );
        }

#ifndef WIN32
    private:
#endif // WIN32
        tcp_connection( boost::asio::io_service& io_service )
            : m_socket( io_service ) {}

    private:
        void handle_write() {}

    private:
        boost::asio::ip::tcp::socket m_socket;
        std::string m_async_message;
    };

    /*!
     * \brief
     * server which accepts and forwards log messages to it's clients.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    class socket_logger::logging_server
        : public boost::enable_shared_from_this<logging_server>
        , boost::noncopyable
    {
        typedef std::list<tcp_connection::shared_connection_type> connection_list_type;
#ifndef WIN32
        template< class T, class A1 >
        friend boost::shared_ptr< T > boost::make_shared( A1 const& );

        template< class T, class A1, class A2 >
        friend boost::shared_ptr< T > boost::make_shared( A1 const&, A2 const& );
#endif
    public:
        static shared_tcp_server_type create( unsigned short port ) {
            return boost::make_shared<logging_server>( port );
        }

        static shared_tcp_server_type create( const std::string& hostname, const std::string& port ) {
            return  boost::make_shared<logging_server>( hostname, port );
        }

        void shutdown() {
            m_io_service.stop();
            m_thread->join();
        }

        void log( const std::string& message ) {
            boost::mutex::scoped_lock lock( m_mutex );
            foreach( const tcp_connection::shared_connection_type & sc, m_connection_list ) {
                sc->log( message );
            }
        }

    private:
        void handle_accept( tcp_connection::shared_connection_type c, const boost::system::error_code& error ) {
            if ( !error ) {
                {
                    boost::mutex::scoped_lock lock( m_mutex );
                    m_connection_list.push_back( c );
                }
                accept_incoming();
            }
        }

        void accept_incoming() {
            tcp_connection::shared_connection_type c( tcp_connection::create( m_acceptor.io_service() ) );
            m_acceptor.async_accept( c->socket(), boost::bind( &logging_server::handle_accept, this, c, boost::asio::placeholders::error ) );
        }
#ifdef WIN32
    public:
#endif
        logging_server( unsigned short port )
            : m_acceptor( m_io_service, boost::asio::ip::tcp::endpoint( boost::asio::ip::tcp::v4(), port ) ) {
            accept_incoming();
            m_thread.reset( new boost::thread( boost::bind( &boost::asio::io_service::run, boost::ref( m_io_service ) ) ) );
        }

        logging_server( const std::string& hostname, const std::string& port )
            : m_acceptor( m_io_service, *boost::asio::ip::tcp::resolver( m_io_service ).resolve( boost::asio::ip::tcp::resolver::query( hostname, port ) ) ) {
            accept_incoming();
            m_thread.reset( new boost::thread( boost::bind( &boost::asio::io_service::run, boost::ref( m_io_service ) ) ) );
        }

    private:
        typedef boost::scoped_ptr<boost::thread> scoped_thread_type;
        boost::asio::io_service m_io_service;
        boost::asio::ip::tcp::acceptor m_acceptor;
        connection_list_type m_connection_list;
        boost::mutex m_mutex;
        scoped_thread_type m_thread;
    };

    socket_logger::~socket_logger()
    {
        pass_repetition_message();
        boost::mutex::scoped_lock lock( m_mutex );
        foreach( const server_map_type::value_type & s, m_server ) {
            s.second->log( "closing logger connection." );
            s.second->shutdown();
        }
    }

    socket_logger::logger_name_type socket_logger::name() const
    {
        return logger_name;
    }

    void socket_logger::actual_log( log_level::level /*level*/, const std::string& message )
    {
        boost::mutex::scoped_lock lock( m_mutex );
        foreach( const server_map_type::value_type & s, m_server ) {
            s.second->log( std::string( message ).append( "\r\n " ) );
        }
    }

    void socket_logger::listen_on( unsigned short port )
    {
        boost::mutex::scoped_lock lock( m_mutex );
        m_server[ port ] = logging_server::create( port );
    }

    void socket_logger::target( const std::string& target )
    {
        try {
            if ( target.find( ':' ) != std::string::npos ) {
                boost::mutex::scoped_lock lock( m_mutex );
                m_server[ boost::lexical_cast<unsigned short>( target.substr( target.find( ':' ) + 1 ) ) ] = logging_server::create( target.substr( 0, target.find( ':' ) ), target.substr( target.find( ':' ) + 1 ) );
            } else {
                boost::mutex::scoped_lock lock( m_mutex );
                const unsigned short port = boost::lexical_cast<unsigned short>( target ) ;
                m_server[ port ] = logging_server::create( port );
            }
        } catch ( const boost::bad_lexical_cast& ) {
            // TODO need configuration exception of some sort.
        }
    }

    socket_logger::logger_name_type socket_logger::logger_name = "socket";

    socket_logger_creator::result_type socket_logger_creator::create() const
    {
        return result_type( new socket_logger() );
    }
}

