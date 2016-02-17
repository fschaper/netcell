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

#pragma once

#include <wss/type.hpp>
#include <wss/locale.hpp>
#include <wss/define.hpp>
#include <wss/friend.hpp>
#include <wss/locked_session.hpp>
#include <wss/locked_object.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <boost/thread/mutex.hpp>
#   include <boost/thread/condition_variable.hpp>
#   include <boost/date_time/posix_time/posix_time.hpp>
#   include <boost/thread/shared_mutex.hpp>
#   include <boost/uuid/uuid.hpp>
#   include <boost/signal.hpp>
#   include <map>
#endif

class server;
struct locked_session_handler_holder;

/*!
 * \brief
 * session manager.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class WSS_MODULE session_handler
{
    friend class server;
    friend class locked_session;
    friend struct locked_session_handler_holder;

    enum collector_state { running, shutdown, halted };

    typedef boost::signal < void( session& ) > on_logout_type;
public:
    /*!
     * \brief
     * will be called for every user logout.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    on_logout_type on_logout;

    /*!
    * \brief
    * get a read (shared) locked view of session handler.
    *
    * \author
    * Radu Racariu <radu@yalos-solutions.com>
    */
    locked_session_handler_holder locked_session_handler();

    /*!
     * \brief
     * create a new session.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    locked_session create( const ::locale& l, const std::string& username = "", const std::string password = "", const group_set_type& groups = group_set_type() );

    /*!
     * \brief
     * get the session identified by the passed uuid.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    locked_session get( const std::string& uuid );

    /*!
     * \brief
     * get the session identified by the passed uuid.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    locked_session get( const uuid_type& uuid );

    /*!
     * \brief
     * get the default session timeout for all sessions
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const boost::posix_time::time_duration& session_timeout();

    /*!
     * \brief
     * set the session timeout for all sessions.
     *
     * a timeout of "0" signifies that sessions never time out.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void session_timeout( const boost::posix_time::time_duration& timeout );


    /*!
     * \brief
     * removes an existing session
     *
     * \author
     * Radu Ialovoi <ialovoi@yalos-solutions.com>
     */
    void remove_session( const uuid_type& uuid );

    /*!
     * \brief
     * removes an existing session
     *
     * \author
     * Radu Ialovoi <ialovoi@yalos-solutions.com>
     */
    void remove_session( const std::string& uuid  );

    /*!
     * \brief
     * autosaves openened documents.
     *
     * \author
     * Radu Ialovoi <ialovoi@yalos-solutions.com>
     */
    void autosave();
    /*!
     * \brief
     * check if there are any sessions registered right now
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    bool empty();

    void clear_connection_cache_on_all_sessions( session& calling_session );

private:

    /*!
     * \brief
     * constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    session_handler( server& );
    /*!
     * \brief
     * restore a session object to the handler.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    //    void restore( const shared_session_type& s );

    /*!
     * \brief
     * periodically invalidates expired sessions.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void invalidate_sessions();

    /*!
     * \brief
     * callback to the server that shuts the session invalidator down.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool stop();

    /*!
     * \brief
     * start the session handler.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void start();

private:
    bool empty_no_locking() const;
private:
    typedef boost::mutex                                            mutex_type;
    typedef mutex_type::scoped_lock                                 lock_type;
    typedef std::pair< uuid_type, shared_session_type >    key_val_type;
    typedef map_to_use<uuid_type, shared_session_type>::type    session_map_type;

    typedef boost::shared_mutex                                 shared_mutex_type;
    typedef boost::unique_lock< shared_mutex_type >             write_lock;
    typedef boost::shared_lock< shared_mutex_type >             read_lock;
    typedef boost::upgrade_lock< shared_mutex_type >            read_write_lock;
    typedef boost::upgrade_to_unique_lock< shared_mutex_type >  upgrade_lock;

    mutable mutex_type m_collector_mutex;
    mutable mutex_type m_state_mutex;
    boost::condition_variable m_wait_for_shutdown;
    volatile collector_state m_state;
    boost::posix_time::time_duration m_timeout;

    shared_mutex_type       m_sessions_mutex;
    session_map_type        m_session_map;
};

struct locked_session_handler_holder {
    friend class session_handler;

    //return true if the session map of the session holder is empty
    bool empty() const;

    ~locked_session_handler_holder();

private:

    locked_session_handler_holder( const session_handler& session_handler );

    const session_handler& m_session_handler;
};
