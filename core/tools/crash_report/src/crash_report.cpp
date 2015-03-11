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
*/


#include "stdafx.h"
#include "crash_report.h"
#include "crash_report_dialog.hpp"
#include "status_report_dialog.hpp"
#include "send_report.hpp"
#include "command_line_handler.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// crash_report_application
BEGIN_MESSAGE_MAP( crash_report_application, CWinApp )
    ON_COMMAND( ID_HELP, &CWinApp::OnHelp )
END_MESSAGE_MAP()

// crash_report_application construction
crash_report_application::crash_report_application()
{
    // TODO: add construction code here,
    // Place all significant initialization in InitInstance
}


// The one and only crash_report_application object
crash_report_application theApp;

// crash_report_application initialization
BOOL crash_report_application::InitInstance()
{
    // InitCommonControlsEx() is required on Windows XP if an application
    // manifest specifies use of ComCtl32.dll version 6 or later to enable
    // visual styles.  Otherwise, any window creation will fail.
    INITCOMMONCONTROLSEX InitCtrls;
    InitCtrls.dwSize = sizeof( InitCtrls );
    // Set this to include all the common control classes you want to use
    // in your application.
    InitCtrls.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx( &InitCtrls );

    CWinApp::InitInstance();

    if ( ! AfxSocketInit() ) {
        AfxMessageBox( IDP_SOCKETS_INIT_FAILED );
        return FALSE;
    }

    // Standard initialization
    // If you are not using these features and wish to reduce the size
    // of your final executable, you should remove from the following
    // the specific initialization routines you do not need
    // Change the registry key under which our settings are stored
    // TODO: You should modify this string to be something appropriate
    // such as the name of your company or organization
    SetRegistryKey( _T( "jedox" ) );

    command_line_handler clh;
    ParseCommandLine( clh );

    crash_report_dialog dlg;
    //m_pMainWnd = &dlg;

    CString default_email_address = GetProfileString( _T( "user_information" ), _T( "email" ) );
    if ( ! default_email_address.IsEmpty() ) {
        dlg.set_email_address( default_email_address );
    }
    dlg.set_crash_dump_file( clh.get_crash_dump_file_path() );

    INT_PTR nResponse = dlg.DoModal();

    if ( nResponse == IDOK ) {
        // retrieve the email address from the dialog and store it in the
        // registry - we might have to make use of it again some time
        const CString& email_address = dlg.get_email_address();
        if ( email_address.IsEmpty() == false ) {
            WriteProfileString( _T( "user_information" ), _T( "email" ), email_address );
        }

        // get the report detail from the dialog and send all the information
        // to the jedox bug tracking server.
        const CString& report_detail = dlg.get_report_detail();

        CString server_response;
        USES_CONVERSION;
        if ( send_report( clh.get_product_version(), clh.get_crash_dump_file_path(), W2A( email_address ), W2A( report_detail ), server_response ) == S_OK ) {
            status_report_dialog rdlg;
            rdlg.set_issue_id( server_response );
            INT_PTR response = rdlg.DoModal();
        }
    } else if ( nResponse == IDCANCEL ) {
        // cancel
    }

    // Since the dialog has been closed, return FALSE so that we exit the
    //  application, rather than start the application's message pump.
    return FALSE;
}
