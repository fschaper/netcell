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

/*!
 * \brief
 * memory garbage collector
 *
 * this handler will run on a schedule
 * and return pooled memory to the system
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */
class memory_garbage_collector
{
    friend class server;

    enum garbage_collector_state { running, shutdown, halted };

    memory_garbage_collector( server&  );

    /*!
     * \brief
     * periodically release pooled memory, if there are no sessions on the server.
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    void release_memory();

    bool stop();

    void start();

    garbage_collector_state state();

    typedef boost::mutex mutex_type;
    typedef mutex_type::scoped_lock lock_type;


    mutable mutex_type m_collector_mutex;
    mutable mutex_type m_state_mutex;
    boost::condition_variable m_wait_for_shutdown;
    volatile garbage_collector_state m_state;
    server& m_server;
};

