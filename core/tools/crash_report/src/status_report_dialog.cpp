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
#include "status_report_dialog.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// status_report_dialog dialog

BEGIN_DHTML_EVENT_MAP( status_report_dialog )
DHTML_EVENT_ONCLICK( _T( "button_ok" ), on_ok )
END_DHTML_EVENT_MAP()

status_report_dialog::status_report_dialog( CWnd* pParent /*=NULL*/ )
    : CDHtmlDialog( status_report_dialog::IDD, status_report_dialog::IDH, pParent )
{
    m_hIcon = AfxGetApp()->LoadIcon( IDR_MAINFRAME );
}

void status_report_dialog::DoDataExchange( CDataExchange* pDX )
{
    CDHtmlDialog::DoDataExchange( pDX );
}

BEGIN_MESSAGE_MAP( status_report_dialog, CDHtmlDialog )
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


// crash_report_dialog message handlers

BOOL status_report_dialog::OnInitDialog()
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
void status_report_dialog::OnPaint()
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
HCURSOR status_report_dialog::OnQueryDragIcon()
{
    return static_cast<HCURSOR>( m_hIcon );
}

HRESULT status_report_dialog::on_ok( IHTMLElement* pElement )
{
    CDHtmlDialog::OnOK();
    return S_OK;
}

void status_report_dialog::set_issue_id( const CString& issue_id )
{
    m_issue_id = issue_id;
}

void status_report_dialog::OnDocumentComplete( LPDISPATCH pDisp, LPCTSTR szUrl )
{
    IHTMLElement* html_element;
    if ( GetElement( _T( "issue_id" ), &html_element ) == S_OK ) {
        html_element->put_innerHTML( m_issue_id.AllocSysString() );
    }
    if ( GetElement( _T( "issue_url" ), &html_element ) == S_OK ) {
        VARIANT url;
        url.vt = VT_BSTR;
        url.bstrVal = ( CString( "http://bugs.jedox.net/mantis/view.php?id=" ) + m_issue_id ).AllocSysString();
        html_element->setAttribute( CString( "href" ).AllocSysString(), url );
    }
}

HRESULT status_report_dialog::TranslateAcceleratorW( LPMSG lpMsg, const GUID* pguidCmdGroup, DWORD nCmdID )
{
    // disable key F5 - no messing with our dialog
    if ( ( lpMsg->message == WM_KEYDOWN ) && ( lpMsg->wParam == VK_F5 ) ) {
        return S_OK;
    }
    return CDHtmlDialog::TranslateAccelerator( lpMsg, pguidCmdGroup, nCmdID );
}

HRESULT STDMETHODCALLTYPE status_report_dialog::ShowContextMenu( DWORD dwID, POINT* ppt, IUnknown* pcmdtReserved, IDispatch* pdispReserved )
{
    // disable context menu
    return S_OK;
}
