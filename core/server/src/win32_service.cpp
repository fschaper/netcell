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

#include "win32_service.hpp"
#include "wss/server.hpp"
#include "configuration.hpp"
#include <tchar.h>



win32_service*                          win32_service::m_p_this;
win32_service_status_updater            win32_service::m_status_updater;


win32_service::win32_service( void ) :
    m_dwErr( 0 )
{
    m_p_this                                 = this;

    m_ssStatus.dwServiceType                = SERVICE_WIN32_OWN_PROCESS;
    m_ssStatus.dwServiceSpecificExitCode    = 0;

}


win32_service::~win32_service( void )
{

}

BOOL win32_service::report_status_to_scmgr(
    DWORD dwCurrentState,
    DWORD dwWin32ExitCode,
    DWORD dwWaitHint )
{
    static DWORD        dwCheckPoint = 1;
    BOOL                fResult = TRUE;

    if ( dwCurrentState == SERVICE_START_PENDING ) {
        m_ssStatus.dwControlsAccepted = 0;
    } else {
        m_ssStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;
    }

    m_ssStatus.dwCurrentState = dwCurrentState;
    m_ssStatus.dwWin32ExitCode = dwWin32ExitCode;
    m_ssStatus.dwWaitHint = dwWaitHint;

    if ( ( dwCurrentState == SERVICE_RUNNING ) ||
            ( dwCurrentState == SERVICE_STOPPED ) ) {
        m_ssStatus.dwCheckPoint = 0;
    } else {
        m_ssStatus.dwCheckPoint = dwCheckPoint++;
    }

    fResult = SetServiceStatus( m_sshStatusHandle, &m_ssStatus );
    // Report the status of the service to the service control manager.
    //
    if ( !fResult ) {
        add_to_message_log( TEXT( "SetServiceStatus failed" ) );
    }

    return fResult;
}


void win32_service::add_to_message_log( LPTSTR lpszMsg )
{
    size_t  strSize = ( sizeof( SZSERVICENAME ) / sizeof( TCHAR ) ) + 100;
    TCHAR   szMsg [( sizeof( SZSERVICENAME ) / sizeof( TCHAR ) ) + 100 ];
    HANDLE  hEventSource;
    LPTSTR  lpszStrings[2];

    m_dwErr = GetLastError();

    // Use event logging to log the error.
    //
    hEventSource = RegisterEventSource( NULL, TEXT( SZSERVICENAME ) );

    _stprintf_s( szMsg, strSize, TEXT( "%s error: %d" ), TEXT( SZSERVICENAME ), m_dwErr );
    lpszStrings[0] = szMsg;
    lpszStrings[1] = lpszMsg;

    if ( hEventSource != NULL ) {
        // handle of event source
        ReportEvent( hEventSource,
                     EVENTLOG_ERROR_TYPE, // event type
                     0,                  // event category
                     0,                  // event ID
                     NULL,               // current user's SID
                     2,                  // strings in lpszStrings
                     0,                  // no bytes of raw data
                     ( LPCTSTR* ) lpszStrings,// array of error strings
                     NULL );                 // no raw data

        DeregisterEventSource( hEventSource );
    }

}


LPTSTR win32_service::get_last_error_text( LPTSTR lpszBuf, DWORD dwSize )
{
    DWORD dwRet;
    LPTSTR lpszTemp = NULL;

    dwRet = FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ARGUMENT_ARRAY,
                           NULL,
                           GetLastError(),
                           LANG_NEUTRAL,
                           ( LPTSTR ) & lpszTemp,
                           0,
                           NULL );

    // supplied buffer is not long enough
    if ( !dwRet || ( ( long )dwSize < ( long )dwRet + 14 ) ) {
        lpszBuf[0] = TEXT( '\0' );
    } else {
        //remove cr and newline character
        lpszTemp[lstrlen( lpszTemp )-2] = TEXT( '\0' );
        _stprintf_s( lpszBuf, dwSize, TEXT( "%s (0x%x)" ), lpszTemp, GetLastError() );
    }

    if ( lpszTemp ) {
        LocalFree( ( HLOCAL ) lpszTemp );
    }

    return lpszBuf;
}


void win32_service::cmd_install_service( const std::string& service_name, const std::string& display_name )
{
    SC_HANDLE   schService;
    SC_HANDLE   schSCManager;

    TCHAR szPath[1024+4];

    if ( GetModuleFileName( NULL, szPath, 1024 ) == 0 ) {
        _tprintf( TEXT( "Unable to install %s - %s\n" ), display_name.c_str(), get_last_error_text( m_Err, 256 ) );
        return;
    }

    size_t len = _tcslen( szPath );
    szPath[len] = ' ';
    szPath[len+1] = '-';
    szPath[len+2] = 'x';
    szPath[len+3] = 0;

    schSCManager = OpenSCManager(
                       NULL,                     // machine (NULL == local)
                       NULL,                     // database (NULL == default)
                       // access required
                       SC_MANAGER_CONNECT | SC_MANAGER_CREATE_SERVICE
                   );
    if ( schSCManager ) {
        schService = CreateServiceA(
                         schSCManager,         // SCManager database
                         service_name.c_str(), // name of service
                         display_name.c_str(), // name to display
                         SERVICE_QUERY_STATUS, // desired access
                         // service type
                         SERVICE_WIN32_OWN_PROCESS,
                         SERVICE_AUTO_START,     // start type
                         SERVICE_ERROR_NORMAL,// error control type
                         szPath,                 // service's binary
                         NULL,               // no load ordering group
                         NULL,               // no tag identifier
                         TEXT( SZDEPENDENCIES ),// dependencies
                         NULL,               // LocalSystem account
                         NULL );                 // no password

        if ( schService ) {
            _tprintf( TEXT( "%s installed.\n" ), display_name.c_str() );
            CloseServiceHandle( schService );
        } else {
            _tprintf( TEXT( "CreateService failed - %s\n" ), get_last_error_text( m_Err, 256 ) );
        }

        CloseServiceHandle( schSCManager );
    } else {
        _tprintf( TEXT( "OpenSCManager failed - %s\n" ), get_last_error_text( m_Err, 256 ) );
    }
}


void win32_service::cmd_remove_service( const std::string& service_name )
{
    SC_HANDLE   schService;
    SC_HANDLE   schSCManager;

    schSCManager = OpenSCManager(
                       NULL,                     // machine (NULL == local)
                       NULL,                     // database (NULL == default)
                       SC_MANAGER_CONNECT        // access required
                   );
    if ( schSCManager ) {
        schService = OpenServiceA( schSCManager, service_name.c_str(), DELETE | SERVICE_STOP | SERVICE_QUERY_STATUS );

        if ( schService ) {
            // try to stop the service
            if ( ControlService( schService, SERVICE_CONTROL_STOP, &m_ssStatus ) ) {
                _tprintf( TEXT( "Stopping %s." ), service_name.c_str() );
                Sleep( 1000 );

                while ( QueryServiceStatus( schService, &m_ssStatus ) ) {
                    if ( m_ssStatus.dwCurrentState == SERVICE_STOP_PENDING ) {
                        _tprintf( TEXT( "." ) );
                        Sleep( 1000 );
                    } else {
                        break;
                    }
                }

                if ( m_ssStatus.dwCurrentState == SERVICE_STOPPED ) {
                    _tprintf( TEXT( "\n%s stopped.\n" ), service_name.c_str() );
                } else {
                    _tprintf( TEXT( "\n%s failed to stop.\n" ), service_name.c_str() );
                }

            }

            // now remove the service
            if ( DeleteService( schService ) ) {
                _tprintf( TEXT( "%s removed.\n" ), service_name.c_str() );
            } else {
                _tprintf( TEXT( "DeleteService failed - %s\n" ), get_last_error_text( m_Err, 256 ) );
            }

            CloseServiceHandle( schService );
        } else {
            _tprintf( TEXT( "OpenService failed - %s\n" ), get_last_error_text( m_Err, 256 ) );
        }

        CloseServiceHandle( schSCManager );
    } else {
        _tprintf( TEXT( "OpenSCManager failed - %s\n" ), get_last_error_text( m_Err, 256 ) );
    }
}




void WINAPI win32_service::service_main( DWORD dwArgc, LPTSTR* lpszArgv )
{

    // register our service control handler:
    //
    m_p_this->m_sshStatusHandle = RegisterServiceCtrlHandler( TEXT( SZSERVICENAME ), service_ctrl );

    if ( !m_p_this->m_sshStatusHandle ) {
        goto cleanup;
    }

    // report the status to the service control manager.
    //
    if ( !m_p_this->report_status_to_scmgr(
                SERVICE_START_PENDING,   // service state
                NO_ERROR,                // exit code
                3000 ) ) {                   // wait hint
        goto cleanup;
    }

    m_status_updater.set_controlled_service( m_p_this->m_sshStatusHandle );
    m_status_updater.begin_update_for_start();


    m_p_this->service_start();

cleanup:

    // try to report the stopped status to the service control manager.
    //
    if ( m_p_this->m_sshStatusHandle ) {
        m_p_this->report_status_to_scmgr(
            SERVICE_STOPPED,
            m_p_this->m_dwErr,
            0 );
    }



    return;
}

void WINAPI win32_service::service_ctrl( DWORD dwCtrlCode )
{
    // Handle the requested control code.
    //
    switch ( dwCtrlCode ) {
            // Stop the service.
            //
            // SERVICE_STOP_PENDING should be reported before
            // setting the Stop Event - hServerStopEvent - in
            // ServiceStop().  This avoids a race condition
            // which may result in a 1053 - The Service did not respond...
            // error.
        case SERVICE_CONTROL_STOP:
            m_p_this->report_status_to_scmgr( SERVICE_STOP_PENDING, NO_ERROR, 0 );
            m_p_this->service_stop();
            return;

            // Update the service status.
            //
        case SERVICE_CONTROL_INTERROGATE:
            break;

            // invalid control code
            //
        default:
            break;

    }

    m_p_this->report_status_to_scmgr( m_p_this->m_ssStatus.dwCurrentState, NO_ERROR, 0 );
}

void win32_service::cmd_run_service( )
{
    SERVICE_TABLE_ENTRY dispatchTable[] = {
        { TEXT( SZSERVICENAME ), ( LPSERVICE_MAIN_FUNCTION )service_main},
        { NULL, NULL}
    };

    if ( !StartServiceCtrlDispatcher( dispatchTable ) ) {
        add_to_message_log( TEXT( "StartServiceCtrlDispatcher failed." ) );
    }
}

int main( int argc, char* argv[] );

void win32_service::service_start()
{
    //DebugBreak();
    if ( !report_status_to_scmgr( SERVICE_START_PENDING, NO_ERROR, 3000 ) ) {
        return;
    }
    if ( !report_status_to_scmgr( SERVICE_START_PENDING, NO_ERROR, 3000 ) ) {
        return;
    }


    // report the status to the service control manager.
    if ( !report_status_to_scmgr( SERVICE_RUNNING, NO_ERROR, 0 ) ) {
        return;
    }
    // Call the main routine and block on it.

    char szPath[1024];
    char service_flag[3];
    service_flag[0] = '-';
    service_flag[1] = '-';
    service_flag[2] = 0;

    char*   argv[2];
    argv[0] = szPath;
    argv[1] = service_flag;

    //no need to test as it was verified upon service registration
    GetModuleFileNameA( NULL, szPath, 1024 );

    size_t len = strlen( szPath );
    while ( len && szPath[len] != '\\' ) {
        len--;
    }
    char tmp = szPath[len+1];
    szPath[len+1] = 0;
    SetCurrentDirectoryA( szPath );
    szPath[len+1] = tmp;
    main( 2, argv );


}

void synchronize_service_status()
{
    win32_service::m_status_updater.cleanup_timer();
}

void win32_service::service_stop()
{
    static server& server_instance = server::instance();
    m_status_updater.begin_update_for_stop();
    server_instance.shutdown();
}
#endif
