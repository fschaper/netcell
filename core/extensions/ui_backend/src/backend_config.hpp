/**
 *  \file
 *  Copyright (C) 2006-2009 Jedox AG
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
 */


// This file has been auto-generated. Don't change it by hand!

#ifndef BACKEND_CONFIG_HPP
#define BACKEND_CONFIG_HPP


#include <xio/optional.hpp>
#include <xio/xml/schema/types.hpp>
#include <xio/util/binary_search.hpp>

namespace ui_backend_settings
{
    using namespace ::xio;
    using namespace ::xio::xml::schema;

    class backend_config_ui_backend_config_diff;
    class backend_config_ui_backend_config_network_listen_tcp;
    class backend_config_ui_backend_config_network_listen;
    class backend_config_ui_backend_config_network;
    class backend_config_ui_backend_config;
    class backend_config;

    class backend_config_ui_backend_config_diff
    {
    public:
        UnsignedShort gc_interval;
    };

    class backend_config_ui_backend_config_network_listen_tcp
    {
    public:
        String address;
        UnsignedShort port;
    };

    class backend_config_ui_backend_config_network_listen
    {
    public:
        std::vector< backend_config_ui_backend_config_network_listen_tcp > tcp;
    };

    class backend_config_ui_backend_config_network
    {
    public:
        backend_config_ui_backend_config_network_listen listen;
    };

    class backend_config_ui_backend_config
    {
    public:
        backend_config_ui_backend_config_diff diff;
        backend_config_ui_backend_config_network network;
    };

    class backend_config
    {
    public:
        poptional< backend_config_ui_backend_config > ui_backend_config;
    };

}
#endif

