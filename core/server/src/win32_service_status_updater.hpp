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

#ifndef PROGRAMS_SERVICE_UPDATE_TIMER_H
#define PROGRAMS_SERVICE_UPDATE_TIMER_H 1

#include <boost/thread/thread.hpp>



class win32_service_status_updater
{
private:
    class service_update_timer
    {
    private:
        bool*                                           m_Active;
        DWORD                                           m_WaitHint;
        DWORD                                           m_CheckPoint;
        DWORD                                           m_UpdateCounter;
        SERVICE_STATUS                                  m_ServiceStatus;
        SERVICE_STATUS_HANDLE                           m_ServiceHandle;

        void update_status();

        void update_status_to_started();

        void update_status_to_stopped();

    public:

        service_update_timer( SERVICE_STATUS_HANDLE service_handle, bool start_stop, bool* signal );

        void operator()();

    };

    SERVICE_STATUS_HANDLE   m_ServiceHandle;

    boost::thread*          timer;
    bool                    control;

public:
    win32_service_status_updater();

    ~win32_service_status_updater();

    void set_controlled_service( SERVICE_STATUS_HANDLE handle  );

    void begin_update_for_start();

    void begin_update_for_stop();

    void cleanup_timer();

};

#endif
