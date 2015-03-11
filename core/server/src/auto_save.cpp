/**
*  \file
*  Copyright (C) 2006-2009 Jedox AG, Freiburg i.Br., Germany
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
*  \Author
*  Florian Schaper <florian.schaper@jedox.com>
*  Frieder Hofmann <frieder.hofmann@jedox.com>
*/

#include "precompiled_header.hpp"
#include "auto_save.hpp"

// wss
#include "wss/server.hpp"
#include "core_logging.hpp"
#include "wss/named_thread.hpp"


auto_save::auto_save()
    : m_state( auto_save::SAVE_HANDLER_HALTED )
    , m_interval( 60 )
    , m_worker( NULL )
{
    server::instance().on_server_startup.connect( boost::bind( &auto_save::start, this ) );
    server::instance().on_server_shutdown.connect( boost::bind( &auto_save::stop, this ) );
}

bool auto_save::start()
{
    bool return_value = false;
    if ( SAVE_HANDLER_HALTED == m_state ) {
        m_state = SAVE_HANDLER_RUNNING;
        m_worker = new boost::thread( boost::bind( &auto_save::wait_on_save, this ) );
        return_value = true;
    }
    return return_value;
}

bool auto_save::stop()
{
    if ( SAVE_HANDLER_RUNNING == m_state ) {
        LOG_CORE_INFO( "autosave handler shutting down ..." );
        m_state = SAVE_HANDLER_SHUTTING_DOWN;
        m_wait_for_shutdown.notify_all();
    }

    if ( NULL != m_worker ) {
        m_worker->join();
    }

    return true;
}

void auto_save::set_interval( int sec )
{
    m_interval = sec;
}

void auto_save::wait_on_save()
{
    name_thread( "autosave handler" );
    boost::unique_lock<boost::mutex> lock( m_lock );
    while ( server::state::shutting_down != server::instance().current_state()
            && SAVE_HANDLER_RUNNING == m_state && m_interval > 0 ) {
        boost::xtime xt;
        boost::xtime_get( &xt, boost::TIME_UTC );
        xt.sec += m_interval;

        m_wait_for_shutdown.timed_wait( lock, xt );

        LOG_CORE_INFO( "autosaving ..." );

        server::instance().session_handler().autosave();

        LOG_CORE_INFO( "autosaving done..." );
    }
    m_state = SAVE_HANDLER_HALTED;
    LOG_INFO( "autosave handler halted." );
}
