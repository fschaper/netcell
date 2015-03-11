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
#include "HandleDispatcher.hpp"

template <typename T>
HandleDispatcher::handler_instantiator<T>::handler_instantiator ( const char* handle )
    : BackendHandler( handle )
{
}

template <typename T>
void HandleDispatcher::handler_instantiator<T>::operator() ( const HttpRequest& request, HttpResponse& response )
{
    ( T( m_handle ) )( request, response );
}

HandleDispatcher::HandleDispatcher ()
{
    using namespace std;

    m_handlers_map = boost::assign::list_of<std::pair<std::string, BackendHandler*> >

                     ( string( "testp" ), new ExampleHandler( "testp" ) )
                     ( string( "testt" ), new handler_instantiator<ExampleHandler>( "testt" ) )
                     ( string( "ccmd" ), new handler_instantiator<CCmdHandler>( "ccmd" ) )


                     ;

    LOG_UI_BACKEND_INFO( "handler dispatcher instantiated." );
}

HandleDispatcher::~HandleDispatcher ()
{
    for ( handlers_map_t::iterator it = m_handlers_map.begin(), it_end = m_handlers_map.end(); it != it_end; ++it ) {
        delete it->second;
    }
}

void HandleDispatcher::operator() ( const std::string& handle, const HttpRequest& request, HttpResponse& response )
{
    handlers_map_t::const_iterator handler_it = m_handlers_map.find( handle );

    if ( handler_it != m_handlers_map.end() ) {
        ( *handler_it->second )( request, response );
    } else {
        response.SetHttpStatusCode( 404 );
        std::string errmsg( "Not Found" );
        response.SetHttpStatusMsg( errmsg );
        response.Write( errmsg );
    }
}


