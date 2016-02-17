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

#ifndef WIN32SERVICE_H
#define WIN32SERVICE_H

#include "win32_service_status_updater.hpp"

// name of the executable
#define SZAPPNAME            "core"
// internal name of the service
#define SZSERVICENAME        "PaloSuiteCoreService"
// displayed name of the service
//#define SZSERVICEDISPLAYNAME "Palo Suite Core Service"
// list of service dependencies - "dep1\0dep2\0\0"
#define SZDEPENDENCIES       "PaloSuiteMolapService\0"
//#define SZDEPENDENCIES       ""

void synchronize_service_status();

class win32_service
{
    friend void synchronize_service_status();
private:
    static win32_service*   m_p_this;

    // current status of the service
    SERVICE_STATUS              m_ssStatus;
    SERVICE_STATUS_HANDLE       m_sshStatusHandle;
    DWORD                       m_dwErr;
    TCHAR                       m_Err[256];

    std::string                 m_service_path;

    static win32_service_status_updater             m_status_updater;

    void add_to_message_log( LPTSTR lpszMsg );

    LPTSTR get_last_error_text( LPTSTR lpszBuf, DWORD dwSize );

    BOOL report_status_to_scmgr( DWORD dwCurrentState, DWORD dwWin32ExitCode, DWORD dwWaitHint );

    static void WINAPI service_main( DWORD dwArgc, LPTSTR* lpszArgv );
    static void WINAPI service_ctrl( DWORD dwCtrlCode );

public:

    win32_service( void );
    virtual ~win32_service( void );

    void service_start();
    void service_stop();

    void cmd_install_service( const std::string& service_name, const std::string& display_name );
    void cmd_remove_service( const std::string& service_name );
    void cmd_run_service();
};
#endif
