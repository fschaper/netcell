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

#include <wss/define.hpp>
#include <wss/singleton.hpp>
#include <wss/application.hpp>
#include <wss/filter_registry.hpp>
#include <wss/server_defaults.hpp>
#include <wss/object_registry.hpp>
#include <wss/object_container.hpp>
#include <wss/function_registry.hpp>
#include <wss/filter_registry.hpp>
#include <wss/server_defaults.hpp>
#include <wss/locked_object.hpp>
#include <wss/session_handler.hpp>
#include <wss/object_registry.hpp>
#include <wss/extension_registry.hpp>

#if defined( WIN32 )
# pragma warning ( disable : 4251 4275 ) // disable "needs to have dll-interface" warning
#endif // WIN32

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
# include <boost/thread/condition_variable.hpp>
# include <boost/enable_shared_from_this.hpp>
# include <boost/thread/mutex.hpp>
# include <boost/noncopyable.hpp>
# include <boost/signal.hpp>
#endif

class memory_garbage_collector;
/*!
 * \brief
 * server representation.
 *
 * \see
 * application | workbook | worksheet
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class WSS_MODULE server
    : public object_container<server, application, policy::no_parent >
    , public boost::enable_shared_from_this<server>
    , public singleton<server>
{
    FRIEND_CLASS singleton<server>;
    FRIEND_CLASS memory_garbage_collector;

    /*!
     * \brief
     * garbage collector sleep timer.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    static const int collector_sleep_time = 20;

public:
    typedef boost::signal < void() > on_server_startup_type;
    typedef boost::signal < bool(), boolean_combiner<> > on_server_shutdown_type;

    /*!
     * \brief
     * this event will be fired by the server object once startup is complete.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    on_server_startup_type on_server_startup;

    /*!
     * \brief
     * this event will be fired by the server object once shutdown is complete.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    on_server_shutdown_type on_server_shutdown;

    /*!
     * \brief
     * server states.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    struct state
            : non_instantiable {
        enum type {
            halted
            , starting_up
            , running
            , shutting_down
        };
    };

    /*!
     * \brief
     * destructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    ~server();

    /*!
     * \brief
     * start the server engine.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void startup();

    /*!
     * \brief
     * shutdown the server engine.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void shutdown( bool terminate = false );

    /*!
     * \brief
     * get the current state of the server object.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    state::type current_state() const;

    /*!
     * \brief
     * method only returns after the server has been shut down.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void wait_on_shutdown() const;

    /*!
     * \brief
     * get the function registry object from the server.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    function_registry& functions();

    /*!
     * \brief
     * return the import/export filter registry.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    filter_registry& filters();

    /*!
     * \brief
     * return an immutable object with the servers default settings.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const ::server_defaults& server_defaults() const;

    /*!
     * \brief
     * return an mutable object with the servers default settings.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    ::server_defaults& server_defaults();

    /*!
     * \brief
     * sets the servers defaults.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void server_defaults( const ::server_defaults& val );

    /*!
     * \brief
     * return the object registry.
     *
     * the registry is a uuid->object mapping providing direct
     * access to objects provided that you know the uuid and the
     * correct type of the object.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    ::object_registry& object_registry();

    /*!
     * \brief
     * return the session handler.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    ::session_handler& session_handler();

    /*!
     * \brief
     * return the extension registry.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    ::extension_registry& extension_registry();

    ws_elem_id_type next_id();

private:
    /*!
     * \brief
     * unload will be called on object shutdown.
     *
     * releases all workbook objects. will call the unload
     * method on all application objects.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void unload();

    /*!
     * \brief
     * garbage collector run.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void collector_run();

    /*!
    * \brief
    * unload unused applications.
    *
    * \author
    * Radu Racariu <radu@yalos-solutions.com>
    */
    void unload_expired_applications();

    /*!
     * \brief
     * constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    server();

private:
    typedef locked_object<volatile state::type, trait::boost_lock_trait<boost::mutex> > locked_state_type;
    mutable locked_state_type m_server_state;
    mutable locked_state_type m_collector_state;

    volatile ws_elem_id_type m_id_counter;

    mutable boost::condition_variable m_server_been_shut_down;
    mutable boost::condition_variable m_await_next_collector_run;

    ::server_defaults m_server_defaults;
    ::object_registry m_object_registry;
    std::auto_ptr< ::session_handler > m_session_handler;
    std::auto_ptr< ::memory_garbage_collector > m_garbage_collector;
    ::extension_registry m_extension_registry;
};
