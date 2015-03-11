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

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// crash_report_dialog dialog

BEGIN_DHTML_EVENT_MAP( crash_report_dialog )
DHTML_EVENT_ONCLICK( _T( "button_cancel" ), on_button_cancel )
DHTML_EVENT_ONCLICK( _T( "button_send_report" ), on_button_send_report )
END_DHTML_EVENT_MAP()

crash_report_dialog::crash_report_dialog( CWnd* pParent /*=NULL*/ )
    : CDHtmlDialog( crash_report_dialog::IDD, crash_report_dialog::IDH, pParent )
{
    m_hIcon = AfxGetApp()->LoadIcon( IDR_MAINFRAME );
}

void crash_report_dialog::DoDataExchange( CDataExchange* pDX )
{
    CDHtmlDialog::DoDataExchange( pDX );
}

BEGIN_MESSAGE_MAP( crash_report_dialog, CDHtmlDialog )
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


// crash_report_dialog message handlers

BOOL crash_report_dialog::OnInitDialog()
{
    CDHtmlDialog::OnInitDialog();

    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog
    SetIcon( m_hIcon, TRUE );       // Set big icon
    SetIcon( m_hIcon, FALSE );      // Set small icon

    // Don't allow user to drop shortcut onto this window and have the browser navigate to that web site
    m_pBrowserApp->put_RegisterAsDropTarget( VARIANT_FALSE );
    return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void crash_report_dialog::OnPaint()
{
    if ( IsIconic() ) {
        CPaintDC dc( this ); // device context for painting

        SendMessage( WM_ICONERASEBKGND, reinterpret_cast<WPARAM>( dc.GetSafeHdc() ), 0 );

        // Center icon in client rectangle
        int cxIcon = GetSystemMetrics( SM_CXICON );
        int cyIcon = GetSystemMetrics( SM_CYICON );
        CRect rect;
        GetClientRect( &rect );
        int x = ( rect.Width() - cxIcon + 1 ) / 2;
        int y = ( rect.Height() - cyIcon + 1 ) / 2;

        // Draw the icon
        dc.DrawIcon( x, y, m_hIcon );
    } else {
        CDHtmlDialog::OnPaint();
    }
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR crash_report_dialog::OnQueryDragIcon()
{
    return static_cast<HCURSOR>( m_hIcon );
}

HRESULT crash_report_dialog::on_button_send_report( IHTMLElement* /*pElement*/ )
{
    IHTMLElement* html_element = NULL;

    // retrieve the email address from the dialog
    if ( GetElement( _T( "email_address" ), &html_element ) == S_OK ) {
        VARIANT tmp_email_address;
        html_element->getAttribute( CString( "value" ).AllocSysString(), NULL, &tmp_email_address );
        if ( tmp_email_address.bstrVal ) {
            m_email_address = tmp_email_address.bstrVal;
        }
    }

    // retrieve the problem report from the dialog
    if ( GetElement( _T( "crash_description" ), &html_element ) == S_OK ) {
        VARIANT tmp_report_detail;
        html_element->getAttribute( CString( "value" ).AllocSysString(), NULL, &tmp_report_detail );
        if ( tmp_report_detail.bstrVal ) {
            m_report_detail = tmp_report_detail.bstrVal;
        }
    }

    EndDialog( IDOK );
    return S_OK;
}

HRESULT crash_report_dialog::on_button_cancel( IHTMLElement* /*pElement*/ )
{
    EndDialog( IDCANCEL );
    return S_OK;
}

void crash_report_dialog::OnOK()
{
    // do nothing to prevent closing of the dialog on "enter" and "ESC"
}

void crash_report_dialog::OnCancel()
{
    // do nothing to prevent closing of the dialog on "enter" and "ESC"
}

const CString& crash_report_dialog::get_report_detail() const
{
    return m_report_detail;
}

const CString& crash_report_dialog::get_email_address() const
{
    return m_email_address;
}

void crash_report_dialog::set_email_address( const CString& email_address )
{
    m_email_address = email_address;
}

void crash_report_dialog::set_crash_dump_file( const CString& crash_dump_file_path )
{
    m_crash_dump_file_path = crash_dump_file_path;
}

void crash_report_dialog::OnDocumentComplete( LPDISPATCH pDisp, LPCTSTR szUrl )
{
    IHTMLElement* html_element;
    if ( GetElement( _T( "email_address" ), &html_element ) == S_OK ) {
        VARIANT tmp_email_address;
        tmp_email_address.vt = VT_BSTR;
        tmp_email_address.bstrVal = m_email_address.AllocSysString();
        html_element->setAttribute( CString( "value" ).AllocSysString(), tmp_email_address );
    }

    if ( GetElement( _T( "report_files" ), &html_element ) == S_OK ) {
        VARIANT tmp_crash_dump_file;
        tmp_crash_dump_file.vt = VT_BSTR;
        tmp_crash_dump_file.bstrVal = m_crash_dump_file_path.AllocSysString();
        html_element->setAttribute( CString( "value" ).AllocSysString(), tmp_crash_dump_file );
    }
}

HRESULT crash_report_dialog::TranslateAcceleratorW( LPMSG lpMsg, const GUID* pguidCmdGroup, DWORD nCmdID )
{
    // disable key F5 - no messing with our dialog
    if ( ( lpMsg->message == WM_KEYDOWN ) && ( lpMsg->wParam == VK_F5 ) ) {
        return S_OK;
    }
    return CDHtmlDialog::TranslateAccelerator( lpMsg, pguidCmdGroup, nCmdID );
}

HRESULT crash_report_dialog::ShowContextMenu( DWORD dwID, POINT* ppt, IUnknown* pcmdtReserved, IDispatch* pdispReserved )
{
    // disable context menu
    return S_OK;
}

