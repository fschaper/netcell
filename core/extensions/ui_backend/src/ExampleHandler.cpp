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
#include "ExampleHandler.hpp"


ExampleHandler::ExampleHandler ( const char* handle )
    : BackendHandler( handle )
{
}

void ExampleHandler::operator() ( const HttpRequest& request, HttpResponse& response )
{
    using namespace std;

    stringstream ss( ios_base::out );

    ss << "EXAMPLE HANDLER (" << m_handle << ")" << endl << endl;

    ss << "URI:" << endl << request.Uri() << endl << endl;

    ss << "ATTRIBUTES:" << endl;
    for ( http_props_map_t::const_iterator it = request.Attributes().begin(), it_end = request.Attributes().end(); it != it_end; ++it ) {
        ss << it->first << ": " << it->second << endl;
    }
    ss << endl;

    ss << "HEADERS:" << endl;
    for ( http_props_map_t::const_iterator it = request.Headers().begin(), it_end = request.Headers().end(); it != it_end; ++it ) {
        ss << it->first << ": " << it->second << endl;
    }
    ss << endl;

    ss << "COOKIES:" << endl;
    for ( http_props_map_t::const_iterator it = request.CookieMap().begin(), it_end = request.CookieMap().end(); it != it_end; ++it ) {
        ss << it->first << ": " << it->second << endl;
    }
    ss << endl;

    ss << "POST DATA:" << endl;

    const IFile* body_file = request.BodyFile();

    if ( body_file ) {
        size_t body_size = body_file->size();
        char* body = new char[body_size + 1];

        body[body_size] = '\0';
        body_file->fread( body, 1, body_size );
        ss << body;

        delete body;
    }

    response.SetContentType( string( "text/plain" ) );
    response.SetHttpStatusCode( 200 );
    response.SetHttpStatusMsg( string( "OK" ) );

    response.Write( ss.str() );
}


