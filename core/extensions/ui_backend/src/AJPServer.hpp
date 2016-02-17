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
*  Predrag Malicevic <predrag.malicevic@develabs.com>
*/

#ifndef _AJPSERVER
# define _AJPSERVER

// ui_backend
#include "memory_manager.hpp"
#include "AJPConnection.hpp"
#include "HandleDispatcher.hpp"

// sockets
#include <Sockets/StdoutLog.h>
#include <Sockets/SocketHandler.h>
#include <Sockets/ListenSocket.h>


/**
 * \brief
 * AJP Server for WSS UI Backend.
 */
class AJPServer : public singleton<AJPServer>
{
    friend class singleton<AJPServer>;

    static const unsigned int MAX_CONNECTION_COUNT = 100;
    static const unsigned int BACKLOG_COUNT = 20;

    typedef enum {
        SERVER_RUNNING
        , SERVER_SHUTTING_DOWN
        , SERVER_HALTED
    } server_state_type;

    class SocketLog : public StdLog
    {
    public:
        void error ( ISocketHandler*, Socket*, const std::string& call, int err, const std::string& sys_err, loglevel_t );
    };

    class ConnHandler : public SocketHandler
    {
    public:
        virtual ISocketHandler* Create( StdLog * = NULL );
        virtual ISocketHandler* Create( IMutex&, ISocketHandler&, StdLog * = NULL );

        ConnHandler ( SocketLog* );
        ConnHandler ( IMutex& mutex, ISocketHandler& parent, StdLog *p );

        bool OkToAccept ( Socket* );

        void Shutdown ();

        void server( const AJPServer* );

    private:
        const AJPServer*  m_ajp_server;
    };

public:
    /*!
     * \brief
     * handler for the server callback 'on_server_shutdown'.
     *
     * will initiate the server shutdown and return false with
     * every call as long as threads are still active.
     */
    struct ShutdownInitiator {
        bool operator() () const;
    };

    /*!
     * \brief
     * configure interface the server should bind to.
     *
     * \param hostname
     * hostname/ip address of the interface to bind to.
     *
     * \param port
     * port number on which to bind.
     */
    bool bind_ipaddress ( const std::string& hostname, unsigned short port );

    /*!
     * \brief
     * starts the server when in halted state.
     */
    void run ();

    /*!
     * \brief
     * determines if the server is in 'running' state.
     *
     * \returns
     * returns true if the server is in 'running' state.
     */
    bool is_running () const;

    /*!
     * \brief
     * determines if the server is in 'shutdown' state.
     *
     * \returns
     * returns true if the server is in 'shutdown' state.
     */
    bool is_shutting_down () const;

    /*!
     * \brief
     * determines if the server is in 'halted' state.
     *
     * \returns
     * returns true if the server is in 'halted' state.
     */
    bool is_halted () const;

    /*!
     * \brief
     * initiates the server shutdown if currently running.
     */
    void shutdown ();

private:
    /*!
     * \brief
     * main server loop.
     *
     * accepts new connections and dispatches them.
     *
     * \see
     * AJPServer::run()
     */
    void server_loop ();

    /*!
     * \brief
     * constructor. initializes the AJPServer.
     */
    AJPServer ();

private:
    volatile server_state_type m_server_state;
    ConnHandler m_conn_handler;
};



#endif // _AJPSERVER
