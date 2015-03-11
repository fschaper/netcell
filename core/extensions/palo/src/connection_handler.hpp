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
*/

#pragma once


#include <libconnectionpool/ConnectionPool.h>
#include <libpalo_ng/Palo/Server.h>

#include <wss/session.hpp>
#include <wss/type.hpp>

#include <boost/thread/mutex.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/optional.hpp>

#include <stdexcept>
#include <string>
#include <map>
#include <list>

/*!
 * \brief
 *
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class master_connection_failed_exception
    : public std::runtime_error
{
public:
    master_connection_failed_exception()
        : std::runtime_error( "connection to the master server not established!" ) {}

    virtual ~master_connection_failed_exception() throw() {}
};

typedef boost::shared_ptr<jedox::palo::Server> shared_palo_server_type;

/*!
 * \brief
 * manages the connections to the various external palo servers
 * synchronizes it's configuration with the settings of the palo
 * master server.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class connection_handler
    : public Palo::SpreadsheetFuncs::ConnectionPool
{

    typedef long entry_uuid_type;
    typedef uuid_type session_id_type;
    typedef std::string connection_handle_type;

    struct dynamic_connection {
        dynamic_connection() : port( 0 ) {}
        dynamic_connection( const std::string& hostname, unsigned short port ) : hostname( hostname ), port( port ) {}
        std::string hostname;           // hostname that will be used for the dynamic connection
        unsigned short port;            // port that will be used for the dynamic connection
        typedef map_to_use<session_id_type, connection_handle_type>::type session_to_handle_mapping_type;
        session_to_handle_mapping_type session_handle_map;
    };

    typedef boost::optional<dynamic_connection> optional_dynamic_connection;

    struct connection_entry {
        connection_entry() : is_active( false ) {}
        connection_handle_type connection_handle;  // ConnectionPool handle
        bool is_active;                            // true if the connection is available for use
        optional_dynamic_connection dynamic;       // true if the connection will use the current users session username/password information
    };

    typedef map_to_use<entry_uuid_type, connection_entry>::type connection_map_type;
    typedef map_to_use < connection_handle_type, connection_entry*>::type handle_lookup_type;

    typedef boost::mutex mutex_type;
    typedef mutex_type::scoped_lock lock_type;

public:
    static connection_handler& instance();

    /*!
     * \brief
     * connect the connection_handler with the palo master database that contains the connection settings.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void connect( const std::string& hostname, unsigned short port, const std::string& username, const std::string& password );

    /*!
     * \brief
     * synchronize connection settings with the server.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void synchronize_settings();

    /*!
     * \brief
     * disabled function.
     *
     * new connection can only be added using the studio database.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void add( const std::string& key, const ConnectionData& cd );

    /*!
     * \brief
     * disabled function.
     *
     * connections can only be removed using the studio database.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual void remove( const std::string& key, const bool do_logout = false );

    /*!
     * \brief
     * retrieve a connection from the pool.
     *
     * \author
     * Radu Ialovoi <ialovoi@yalos-solutions.com>
     */
    shared_palo_server_type internal_get( session& s, const std::string& key );


    /*!
     * \brief
     * retrieve a connection from the pool. will synchronize the settings if required
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    shared_palo_server_type get( session& s, const std::string& key );

    /*!
     * \brief
     * we need to use our own remove, because the virtual one will call the virtual get
     * instead of our custom one and we will run into an assertion!
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    void remove( session& s, const std::string& key );
    /*!
     * \brief
     * disabled function.
     *
     * to enable dynamic connections only requests with session parameter can be serviced.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    virtual shared_palo_server_type get( const std::string& key, bool adjustFailedMap = true );

    /*!
     * \brief
     * invalidate all dynamic connections for the passed session_id
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void invalidate_session( const session_id_type& s );

private:
    connection_handler();

    inline void remove_dynamic_connections( lock_type& lock, connection_entry& entry );

    inline void add_connection( const entry_uuid_type& entry_uuid
                                , const connection_handle_type& handle
                                , const std::string& hostname
                                , unsigned short port
                                , const std::string& username
                                , const std::string& password );

private:
    mutex_type m_mutex;
    connection_map_type m_connections;
    handle_lookup_type m_entry_lookup;

    shared_palo_server_type  m_master_connection;

    typedef map_to_use<connection_handle_type, entry_uuid_type>::type element_id_mapping_type;
    element_id_mapping_type              m_db_connection_info;
};

