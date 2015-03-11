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

#ifndef PALO_CONFIG_READERS_HPP
#define PALO_CONFIG_READERS_HPP

#include "palo_config.hpp"
#include <xio/xml/binding/type_reader.hpp>

namespace palo_cfg
{
    namespace xio
    {
        using namespace ::xercesc;
        using namespace ::xio::xcs;
        using namespace ::xio::xml::binding;

        class CT_host_reader;
        class CT_port_reader;
        class CT_username_reader;
        class CT_password_reader;
        class CT_server_reader;
        class CT_certificate_reader;
        class CT_palo_config_reader;
        class palo_config_reader;

        class CT_host_reader : public type_reader
        {
        protected:
            CT_host* t() {
                return static_cast<CT_host*>( target() );
            }
            void read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value );
        };

        class CT_port_reader : public type_reader
        {
        protected:
            CT_port* t() {
                return static_cast<CT_port*>( target() );
            }
            void read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value );
        };

        class CT_username_reader : public type_reader
        {
        protected:
            CT_username* t() {
                return static_cast<CT_username*>( target() );
            }
            void read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value );
        };

        class CT_password_reader : public type_reader
        {
        protected:
            CT_password* t() {
                return static_cast<CT_password*>( target() );
            }
            void read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value );
        };

        class CT_server_reader : public type_reader
        {
            auto_type_reader< CT_host_reader > _host_reader;
            auto_type_reader< CT_port_reader > _port_reader;
            auto_type_reader< CT_username_reader > _username_reader;
            auto_type_reader< CT_password_reader > _password_reader;
        protected:
            CT_server* t() {
                return static_cast<CT_server*>( target() );
            }
            void start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs );
        };

        class CT_certificate_reader : public type_reader
        {
        protected:
            CT_certificate* t() {
                return static_cast<CT_certificate*>( target() );
            }
            void read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value );
        };

        class CT_palo_config_reader : public type_reader
        {
            auto_type_reader< CT_server_reader > _server_reader;
            auto_type_reader< CT_certificate_reader > _certificate_reader;
        protected:
            CT_palo_config* t() {
                return static_cast<CT_palo_config*>( target() );
            }
            void start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs );
        };

        class palo_config_reader : public type_reader
        {
            auto_type_reader< CT_palo_config_reader > _palo_configuration_reader;
        protected:
            palo_config* t() {
                return static_cast<palo_config*>( target() );
            }
            void start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs );
        };

    }
}
#endif

