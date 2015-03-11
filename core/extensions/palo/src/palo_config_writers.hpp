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

#ifndef PALO_CONFIG_WRITERS_HPP
#define PALO_CONFIG_WRITERS_HPP

#include "palo_config.hpp"
#include "palo_config_literals.hpp"
#include <xio/xml/binding/type_writer.hpp>

namespace palo_cfg
{
    namespace xio
    {
        using namespace ::xercesc;
        using namespace ::xio::xcs;
        using namespace ::xio::xml::binding;

        class CT_host_writer;
        class CT_port_writer;
        class CT_username_writer;
        class CT_password_writer;
        class CT_server_writer;
        class CT_certificate_writer;
        class CT_palo_config_writer;
        class palo_config_writer;

        class CT_host_writer : public type_writer
        {
            CT_host* t() {
                return static_cast<CT_host*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class CT_port_writer : public type_writer
        {
            CT_port* t() {
                return static_cast<CT_port*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class CT_username_writer : public type_writer
        {
            CT_username* t() {
                return static_cast<CT_username*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class CT_password_writer : public type_writer
        {
            CT_password* t() {
                return static_cast<CT_password*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class CT_server_writer : public type_writer
        {
            auto_type_writer< CT_host_writer > _host_writer;
            auto_type_writer< CT_port_writer > _port_writer;
            auto_type_writer< CT_username_writer > _username_writer;
            auto_type_writer< CT_password_writer > _password_writer;
            CT_server* t() {
                return static_cast<CT_server*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class CT_certificate_writer : public type_writer
        {
            CT_certificate* t() {
                return static_cast<CT_certificate*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class CT_palo_config_writer : public type_writer
        {
            auto_type_writer< CT_server_writer > _server_writer;
            auto_type_writer< CT_certificate_writer > _certificate_writer;
            CT_palo_config* t() {
                return static_cast<CT_palo_config*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class palo_config_writer : public type_writer
        {
            auto_type_writer< CT_palo_config_writer > _palo_configuration_writer;
            palo_config* t() {
                return static_cast<palo_config*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

    }
}
#endif

