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
 *  Vali Nitu <vali@yalos-solutions.com.com>
 */


#include "precompiled_header.hpp"

#if defined(WIN32)

#include "win32_service_status_updater.hpp"
#include "core_logging.hpp"


void win32_service_status_updater::service_update_timer::update_status()
{
    m_ServiceStatus.dwWaitHint      = m_WaitHint;
    m_ServiceStatus.dwCheckPoint    = m_CheckPoint;

    SetServiceStatus( m_ServiceHandle, &m_ServiceStatus );

    m_UpdateCounter = m_WaitHint / 1000 - 2;
    m_CheckPoint++;
}

void win32_service_status_updater::service_update_timer::update_status_to_started()
{
    m_ServiceStatus.dwControlsAccepted          = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN;
    m_ServiceStatus.dwCurrentState              = SERVICE_RUNNING;
    LOG_CORE_INFO( "Service started succesfully." << std::endl );
    SetServiceStatus( m_ServiceHandle, &m_ServiceStatus );
}


void win32_service_status_updater::service_update_timer::update_status_to_stopped()
{
    m_ServiceStatus.dwControlsAccepted          = 0;
    m_ServiceStatus.dwCurrentState              = SERVICE_STOPPED;
    LOG_CORE_INFO( "Service stopped succesfully." << std::endl );
    SetServiceStatus( m_ServiceHandle, &m_ServiceStatus );
}


win32_service_status_updater::service_update_timer::service_update_timer( SERVICE_STATUS_HANDLE service_handle, bool start_stop, bool* signal )
    : m_ServiceHandle( service_handle ), m_CheckPoint( 0 ), m_WaitHint( 1000 * 30 ), m_Active( signal )
{
    m_ServiceStatus.dwControlsAccepted          = 0;
    m_ServiceStatus.dwServiceType               = SERVICE_WIN32_OWN_PROCESS;
    m_ServiceStatus.dwServiceSpecificExitCode   = 0;
    m_ServiceStatus.dwCurrentState              = start_stop ? SERVICE_START_PENDING : SERVICE_STOP_PENDING;
    m_ServiceStatus.dwWin32ExitCode             = 0;

    m_UpdateCounter = 1;
}

void win32_service_status_updater::service_update_timer::operator()()
{
    while ( *m_Active ) {
        if ( 0 == --m_UpdateCounter ) {
            switch ( m_ServiceStatus.dwCurrentState ) {
                case SERVICE_START_PENDING:
                    LOG_CORE_DEBUG( "Waiting for the service to startup..." << std::endl );
                    break;
                case SERVICE_STOP_PENDING:
                    LOG_CORE_DEBUG( "Waiting for the service to shutdown..." << std::endl );
                    break;
                default:
                    break;
            }
            update_status();
        }
        boost::this_thread::sleep( boost::posix_time::milliseconds( 1 ) );
    }

    switch ( m_ServiceStatus.dwCurrentState ) {
        case SERVICE_START_PENDING:
            update_status_to_started();
            break;
        case SERVICE_STOP_PENDING:
            update_status_to_stopped();
            break;
        default:
            break;
    }
}

win32_service_status_updater::win32_service_status_updater()
{
    timer = NULL;
}

win32_service_status_updater::~win32_service_status_updater()
{
    cleanup_timer();
}

void win32_service_status_updater::set_controlled_service( SERVICE_STATUS_HANDLE handle  )
{
    m_ServiceHandle = handle;
}

void win32_service_status_updater::begin_update_for_start()
{
    cleanup_timer();
    control = true;
    timer = new boost::thread( service_update_timer( m_ServiceHandle, true, &control ) );
}

void win32_service_status_updater::begin_update_for_stop()
{
    cleanup_timer();
    control = true;
    timer = new boost::thread( service_update_timer( m_ServiceHandle, false, &control ) );
}

void win32_service_status_updater::cleanup_timer()
{
    if ( NULL != timer ) {
        control = false;
        timer->join();
        delete timer;
        timer = NULL;
    }
}



#endif

