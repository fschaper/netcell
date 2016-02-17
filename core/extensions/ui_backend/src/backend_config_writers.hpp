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

#ifndef BACKEND_CONFIG_WRITERS_HPP
#define BACKEND_CONFIG_WRITERS_HPP

#include "backend_config.hpp"
#include "backend_config_literals.hpp"
#include <xio/xml/binding/type_writer.hpp>

namespace ui_backend_settings
{
    namespace xio
    {
        using namespace ::xercesc;
        using namespace ::xio::xcs;
        using namespace ::xio::xml::binding;

        class backend_config_ui_backend_config_diff_writer;
        class backend_config_ui_backend_config_network_listen_tcp_writer;
        class backend_config_ui_backend_config_network_listen_writer;
        class backend_config_ui_backend_config_network_writer;
        class backend_config_ui_backend_config_writer;
        class backend_config_writer;

        class backend_config_ui_backend_config_diff_writer : public type_writer
        {
            backend_config_ui_backend_config_diff* t() {
                return static_cast<backend_config_ui_backend_config_diff*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class backend_config_ui_backend_config_network_listen_tcp_writer : public type_writer
        {
            backend_config_ui_backend_config_network_listen_tcp* t() {
                return static_cast<backend_config_ui_backend_config_network_listen_tcp*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class backend_config_ui_backend_config_network_listen_writer : public type_writer
        {
            auto_type_writer< backend_config_ui_backend_config_network_listen_tcp_writer > _tcp_writer;
            backend_config_ui_backend_config_network_listen* t() {
                return static_cast<backend_config_ui_backend_config_network_listen*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class backend_config_ui_backend_config_network_writer : public type_writer
        {
            auto_type_writer< backend_config_ui_backend_config_network_listen_writer > _listen_writer;
            backend_config_ui_backend_config_network* t() {
                return static_cast<backend_config_ui_backend_config_network*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class backend_config_ui_backend_config_writer : public type_writer
        {
            auto_type_writer< backend_config_ui_backend_config_diff_writer > _diff_writer;
            auto_type_writer< backend_config_ui_backend_config_network_writer > _network_writer;
            backend_config_ui_backend_config* t() {
                return static_cast<backend_config_ui_backend_config*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class backend_config_writer : public type_writer
        {
            auto_type_writer< backend_config_ui_backend_config_writer > _ui_backend_config_writer;
            backend_config* t() {
                return static_cast<backend_config*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

    }
}
#endif

