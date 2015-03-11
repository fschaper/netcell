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

#include "precompiled_header.hpp"
#include "palo_config_writers.hpp"
#include "palo_config_literals.hpp"

namespace palo_cfg
{
    namespace xio
    {
        void CT_host_writer::write_target_to( xml_writer& w )
        {
            if ( t()->name.present() ) {
                w.attribute( 0, palo_config_name_literal, context()->serialize( t()->name.get() ) );
            }
        }

        void CT_port_writer::write_target_to( xml_writer& w )
        {
            if ( t()->name.present() ) {
                w.attribute( 0, palo_config_name_literal, context()->serialize( t()->name.get() ) );
            }
        }

        void CT_username_writer::write_target_to( xml_writer& w )
        {
            if ( t()->name.present() ) {
                w.attribute( 0, palo_config_name_literal, context()->serialize( t()->name.get() ) );
            }
        }

        void CT_password_writer::write_target_to( xml_writer& w )
        {
            if ( t()->name.present() ) {
                w.attribute( 0, palo_config_name_literal, context()->serialize( t()->name.get() ) );
            }
        }

        void CT_server_writer::write_target_to( xml_writer& w )
        {
            w.start_element( 0, palo_config_host_literal );
            _host_writer.get_writer( context(), &t()->host )->write_target_to( w );
            w.end_element( 0, palo_config_host_literal );
            w.start_element( 0, palo_config_port_literal );
            _port_writer.get_writer( context(), &t()->port )->write_target_to( w );
            w.end_element( 0, palo_config_port_literal );
            w.start_element( 0, palo_config_username_literal );
            _username_writer.get_writer( context(), &t()->username )->write_target_to( w );
            w.end_element( 0, palo_config_username_literal );
            w.start_element( 0, palo_config_password_literal );
            _password_writer.get_writer( context(), &t()->password )->write_target_to( w );
            w.end_element( 0, palo_config_password_literal );
        }

        void CT_certificate_writer::write_target_to( xml_writer& w )
        {
            if ( t()->path.present() ) {
                w.attribute( 0, palo_config_path_literal, context()->serialize( t()->path.get() ) );
            }
        }

        void CT_palo_config_writer::write_target_to( xml_writer& w )
        {
            w.start_element( 0, palo_config_server_literal );
            _server_writer.get_writer( context(), &t()->server )->write_target_to( w );
            w.end_element( 0, palo_config_server_literal );
            if ( t()->certificate.present() ) {
                w.start_element( 0, palo_config_certificate_literal );
                _certificate_writer.get_writer( context(), &t()->certificate.get() )->write_target_to( w );
                w.end_element( 0, palo_config_certificate_literal );
            }
        }

        void palo_config_writer::write_target_to( xml_writer& w )
        {
            if ( t()->palo_configuration.present() ) {
                w.start_element( 0, palo_config_palo_configuration_literal );
                w.attribute( 0, palo_config_xmlns_literal, palo_config_http_colon__slash__slash_www_dot_jedox_dot_com_slash_wss_literal );
                w.attribute( palo_config_xmlns_literal, palo_config_NS_literal, palo_config_http_colon__slash__slash_www_dot_jedox_dot_com_slash_wss_literal );
                w.attribute( palo_config_xmlns_literal, palo_config_xs_literal, palo_config_http_colon__slash__slash_www_dot_w3_dot_org_slash_2001_slash_XMLSchema_literal );
                _palo_configuration_writer.get_writer( context(), &t()->palo_configuration.get() )->write_target_to( w );
                w.end_element( 0, palo_config_palo_configuration_literal );
            }
        }

    }
}
