/**
*  \file
*  Copyright (C) 2006-2010 Jedox AG, Freiburg i.Br., Germany
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
*  Predrag Malicevic <predrag.malicevic@develabs.com>
*/

#include "precompiled_header.hpp"
#include "AJPConnection.hpp"

HandleDispatcher& AJPConnection::handle_dispatcher = HandleDispatcher::instance();

AJPConnection::AJPConnection ( ISocketHandler& h )
    : Ajp13Socket( h )
{
    SetReused( true );
}

void AJPConnection::OnAccept ()
{
    LOG_UI_BACKEND_DEBUG( "accepted new connection" );

    if ( !Detach() ) {
        LOG_UI_BACKEND_ERROR( "detaching failed" );
        SetCloseAndDelete();
    }
}

void AJPConnection::IHttpServer_OnExec ( const HttpRequest& request )
{
    LOG_UI_BACKEND_DEBUG( "accepted new request" );

    const std::string uri = request.Uri();
    size_t second_slash_pos = uri.find_first_of( '/', 1 );
    const std::string handle = second_slash_pos == std::string::npos ? uri.substr( 1 ) : uri.substr( 1, second_slash_pos - 1 );

    HttpResponse response;

    if ( handle.size() ) {
        AJPConnection::handle_dispatcher( handle, request, response );
    } else {
        response.SetHttpStatusCode( 400 );
        std::string errmsg( "Bad Request" );
        response.SetHttpStatusMsg( errmsg );
        response.Write( errmsg + ": handler missing in URI" );
    }

    Ajp13Socket::IHttpServer_Respond( response );
}

void AJPConnection::OnResponseComplete ()
{
}



