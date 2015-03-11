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
#include "BackendHandler.hpp"

BackendHandler::Init::Init ()
{
    using namespace std;

    status_msg_map = boost::assign::list_of<pair<int, string> >
                     ( 200, string( "OK" ) )
                     ( 400, string( "Bad Request" ) )
                     ( 401, string( "Unauthorized" ) )
                     ( 403, string( "Forbidden" ) )
                     ( 404, string( "Not Found" ) )
                     ( 500, string( "Internal Server Error" ) )
                     ( 501, string( "Not Implemented" ) )
                     ( 503, string( "Service Unavailable" ) )
                     ;
}

const BackendHandler::Init BackendHandler::init;

BackendHandler::BackendHandler ( const char* handle )
    : m_handle( handle )
{
}
const std::string BackendHandler::get_http_date()
{
    time_t t = time( NULL );
    struct tm tp;
#ifdef _WIN32
    //memcpy( &tp, gmtime( &t ), sizeof( tp ) );
    gmtime_s( &tp, &t );
#else
    gmtime_r( &t, &tp );
#endif

    const char* days[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
    const char* months[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
    char date[30];

    sprintf( date,  "%s, %02d %s %d %02d:%02d:%02d GMT", days[tp.tm_wday], tp.tm_mday, months[tp.tm_mon], tp.tm_year + 1900, tp.tm_hour, tp.tm_min, tp.tm_sec );

    return std::string( date );
}

BackendHandler::~BackendHandler ()
{
}

