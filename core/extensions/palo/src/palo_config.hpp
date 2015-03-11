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

#ifndef PALO_CONFIG_HPP
#define PALO_CONFIG_HPP


#include <xio/optional.hpp>
#include <xio/xml/schema/types.hpp>
#include <xio/util/binary_search.hpp>

namespace palo_cfg
{
    using namespace ::xio;
    using namespace ::xio::xml::schema;

    class CT_host;
    class CT_port;
    class CT_username;
    class CT_password;
    class CT_server;
    class CT_certificate;
    class CT_palo_config;
    class palo_config;

    class CT_host
    {
    public:
        optional< String > name;
    };

    class CT_port
    {
    public:
        optional< String > name;
    };

    class CT_username
    {
    public:
        optional< String > name;
    };

    class CT_password
    {
    public:
        optional< String > name;
    };

    class CT_server
    {
    public:
        CT_host host;
        CT_port port;
        CT_username username;
        CT_password password;
    };

    class CT_certificate
    {
    public:
        optional< String > path;
    };

    class CT_palo_config
    {
    public:
        CT_server server;
        poptional< CT_certificate > certificate;
    };

    class palo_config
    {
    public:
        poptional< CT_palo_config > palo_configuration;
    };

}
#endif

