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

#pragma once

// crash_report_dialog dialog
class status_report_dialog : public CDHtmlDialog
{
    // Construction
public:
    status_report_dialog( CWnd* pParent = NULL ); // standard constructor

    enum {
        IDD = IDD_STATUS_REPORT_DIALOG
        , IDH = IDR_HTML_STATUS_REPORT_DIALOG
    };

    void set_issue_id( const CString& issue_id );

protected:
    virtual void DoDataExchange( CDataExchange* pDX );  // DDX/DDV support
    HRESULT on_ok( IHTMLElement* pElement );
    virtual void OnDocumentComplete( LPDISPATCH pDisp, LPCTSTR szUrl );
    virtual HRESULT STDMETHODCALLTYPE TranslateAcceleratorW( LPMSG lpMsg, const GUID* pguidCmdGroup, DWORD nCmdID );
    virtual HRESULT STDMETHODCALLTYPE ShowContextMenu( DWORD dwID, POINT* ppt, IUnknown* pcmdtReserved, IDispatch* pdispReserved );
    // Implementation
protected:
    HICON m_hIcon;

    // Generated message map functions
    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()
    DECLARE_DHTML_EVENT_MAP()

private:
    CString m_issue_id;
};
