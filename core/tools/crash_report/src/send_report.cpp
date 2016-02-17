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
#include "send_report.hpp"

HRESULT send_report( const std::string& version
                     , const CString& crash_file
                     , const std::string& email_address
                     , const std::string& report_detail
                     , CString& server_response )
{
    CInternetSession internet_session;
    CHttpConnection* http_connection;
    CHttpFile* upload_request;
    CStdioFile file_to_upload;
    CString crash_report_call;
    CFileException e;

    try {
        // open the crash dump file from disk
        if ( ! file_to_upload.Open( crash_file, CFile::modeRead | CFile::typeBinary | CFile::shareExclusive, &e ) ) {
            AfxMessageBox( _T( "I'm sorry, but I was unable to open the application crash dump file.\n\rPlease contact support." )
                           , MB_OK );
            return S_FALSE;
        }

        // prepare the connection to the jedox bug report server
        http_connection = internet_session.GetHttpConnection( _T( "bugs.jedox.net" ), ( INTERNET_PORT )INTERNET_DEFAULT_HTTP_PORT, NULL, NULL );
        upload_request = http_connection->OpenRequest(
                             CHttpConnection::HTTP_VERB_POST
                             , _T( "/cgi/create_report.php5" )
                             , NULL
                             , 1
                             , NULL
                             , HTTP_VERSION
                             , INTERNET_FLAG_NO_CACHE_WRITE
                         );

        // prepare the report
        CString http_headers;
        http_headers += "Content-Type: multipart/form-data; boundary=AaB03x";

        std::string formula_data;

        formula_data += "--AaB03x\r\n";
        formula_data += "Content-Disposition: form-data; name=\"product[name]\"\r\n";
        formula_data += "\r\n";
        formula_data += "wss\r\n";

        formula_data += "--AaB03x\r\n";
        formula_data += "Content-Disposition: form-data; name=\"product[version]\"\r\n";
        formula_data += "\r\n";
        formula_data += version;
        formula_data += "\r\n";

        formula_data += "--AaB03x\r\n";
        formula_data += "Content-Disposition: form-data; name=\"client[email]\"\r\n";
        formula_data += "\r\n";
        formula_data += email_address;
        formula_data += "\r\n";

        formula_data += "--AaB03x\r\n";
        formula_data += "Content-Disposition: form-data; name=\"client[report]\"\r\n";
        formula_data += "\r\n";
        formula_data += report_detail;
        formula_data += "\r\n";

        std::string pre_file_headers;
        pre_file_headers += "--AaB03x\r\n";
        pre_file_headers += "Content-Disposition: form-data; name=\"crash_dump_file\"; filename=\"crash.dmp\"\r\n";
        pre_file_headers += "Content-Type: application/octec-string\r\n";
        pre_file_headers += "Content-Transfer-Encoding: binary\r\n";
        pre_file_headers += "\r\n";

        std::string post_file_headers;
        post_file_headers += "\r\n";
        post_file_headers += "--AaB03x--\r\n";

        upload_request->AddRequestHeaders( http_headers, HTTP_ADDREQ_FLAG_REPLACE | HTTP_ADDREQ_FLAG_ADD );

        // total size in bytes of the body that gets send to the server
        unsigned long file_length = ( unsigned long )file_to_upload.GetLength()
                                    + ( unsigned long )formula_data.length()
                                    + ( unsigned long )pre_file_headers.length()
                                    + ( unsigned long )post_file_headers.length();

        // try to initiate the request
        if ( ! upload_request->SendRequestEx( file_length, HSR_SYNC | HSR_INITIATE ) ) {
            AfxMessageBox( _T( "I'm sorry, but I was unable to connect to the jedox reporting server.\n\rPlease contact support." ) , MB_OK );
            return S_FALSE;
        }

        unsigned int bytes_read = 0;
        unsigned int total_bytes_read = 0;
        char buffer[1024];

        // send the form to the server
        upload_request->Write( formula_data.c_str(), ( unsigned long )formula_data.length() );
        upload_request->Write( pre_file_headers.c_str(), ( unsigned long )pre_file_headers.length() );
        do {
            if ( bytes_read = file_to_upload.Read( buffer, sizeof( buffer ) ) ) {
                upload_request->Write( buffer, bytes_read );
                total_bytes_read += bytes_read;
            }
        } while ( bytes_read > 0 );
        upload_request->Write( post_file_headers.c_str(), ( unsigned long )post_file_headers.length() );

        // end the send request
        upload_request->EndRequest( HSR_SYNC );

        // read the server response
        unsigned long response_length = ( unsigned long )upload_request->GetLength();
        while ( 0 != response_length ) {
            LPSTR tmp_response = ( LPSTR )malloc( response_length + 1 );
            tmp_response[response_length] = '\0';
            upload_request->Read( tmp_response, response_length );
            server_response += tmp_response;
            free( tmp_response );
            response_length = ( unsigned long )upload_request->GetLength();
        }

    } catch ( CInternetException* e ) {
        // in the event of the request failing an exception
        // will be emitted. Display message and clean up.
        if ( upload_request ) {
            upload_request->Close();
            delete upload_request;
        }

        if ( http_connection ) {
            http_connection->Close();
            delete http_connection;
        }

        AfxMessageBox( _T( "I'm sorry, but I was unable to connect to the jedox reporting server.\n\rPlease contact support." ), MB_OK );
        e->Delete();

        return S_FALSE;
    }

    // free all resources
    if ( upload_request ) {
        upload_request->Close();
        delete upload_request;
    }

    if ( http_connection ) {
        http_connection->Close();
        delete http_connection;
    }

    return S_OK;
}
