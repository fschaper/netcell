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

#ifndef _HANDLEDISPATCHER
# define _HANDLEDISPATCHER

// stl
#include <map>

// ui_backend
#include "ExampleHandler.hpp"
#include "CCmdHandler.hpp"




/**
 * \brief
 * Handle dispatcher WSS UI backend.
 */
class HandleDispatcher : public singleton<HandleDispatcher>
{
    friend class singleton<HandleDispatcher>;

    template <typename T>
    class handler_instantiator : public BackendHandler
    {
    public:
        handler_instantiator ( const char* handle );

        void operator() ( const HttpRequest&, HttpResponse& );
    };

public:
    void operator() ( const std::string& handle, const HttpRequest&, HttpResponse& );

private:
    /*!
     * \brief
     * constructor. initializes the HandleDispatcher.
     */
    HandleDispatcher ();

    ~HandleDispatcher ();

private:
    typedef std::map<std::string, BackendHandler*> handlers_map_t;

    handlers_map_t m_handlers_map;
};



#endif // _HANDLEDISPATCHER
