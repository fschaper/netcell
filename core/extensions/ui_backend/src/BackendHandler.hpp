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

#ifndef _BACKENDHANDLER
# define _BACKENDHANDLER


// sockets
#include <Sockets/HttpRequest.h>
#include <Sockets/HttpResponse.h>


// time
#include <time.h>

/**
 * \brief
 * Backend handler.
 */
class BackendHandler
{
protected:
    typedef std::map<int, std::string> status_msg_map_t;

    class Init
    {
    public:
        status_msg_map_t status_msg_map;

        Init ();
    };

    static const Init init;

    const char* m_handle;

    typedef Utility::ncmap<std::string> http_props_map_t;

public:
    BackendHandler ( const char* handle );

    const std::string get_http_date();

    virtual void operator() ( const HttpRequest&, HttpResponse& ) = 0;

    virtual ~BackendHandler ();
};



#endif // _BACKENDHANDLER
