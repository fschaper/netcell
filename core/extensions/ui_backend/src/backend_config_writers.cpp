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
#include "backend_config_writers.hpp"
#include "backend_config_literals.hpp"

namespace ui_backend_settings
{
    namespace xio
    {
        void backend_config_ui_backend_config_diff_writer::write_target_to( xml_writer& w )
        {
            w.attribute( 0, backend_config_gc_interval_literal, context()->serialize( t()->gc_interval ) );
        }

        void backend_config_ui_backend_config_network_listen_tcp_writer::write_target_to( xml_writer& w )
        {
            w.attribute( 0, backend_config_address_literal, context()->serialize( t()->address ) );
            w.attribute( 0, backend_config_port_literal, context()->serialize( t()->port ) );
        }

        void backend_config_ui_backend_config_network_listen_writer::write_target_to( xml_writer& w )
        {
            for ( size_t sqi = 0; sqi < t()->tcp.size(); ++sqi ) {
                w.start_element( 0, backend_config_tcp_literal );
                _tcp_writer.get_writer( context(), &t()->tcp[sqi] )->write_target_to( w );
                w.end_element( 0, backend_config_tcp_literal );
            }
        }

        void backend_config_ui_backend_config_network_writer::write_target_to( xml_writer& w )
        {
            w.start_element( 0, backend_config_listen_literal );
            _listen_writer.get_writer( context(), &t()->listen )->write_target_to( w );
            w.end_element( 0, backend_config_listen_literal );
        }

        void backend_config_ui_backend_config_writer::write_target_to( xml_writer& w )
        {
            w.start_element( 0, backend_config_diff_literal );
            _diff_writer.get_writer( context(), &t()->diff )->write_target_to( w );
            w.end_element( 0, backend_config_diff_literal );
            w.start_element( 0, backend_config_network_literal );
            _network_writer.get_writer( context(), &t()->network )->write_target_to( w );
            w.end_element( 0, backend_config_network_literal );
        }

        void backend_config_writer::write_target_to( xml_writer& w )
        {
            if ( t()->ui_backend_config.present() ) {
                w.start_element( 0, backend_config_ui_backend_config_literal );
                w.attribute( 0, backend_config_xmlns_literal, backend_config_http_colon__slash__slash_www_dot_jedox_dot_com_slash_jedox_slash_wss_literal );
                w.attribute( backend_config_xmlns_literal, backend_config_NS_literal, backend_config_http_colon__slash__slash_www_dot_jedox_dot_com_slash_jedox_slash_wss_literal );
                w.attribute( backend_config_xmlns_literal, backend_config_xs_literal, backend_config_http_colon__slash__slash_www_dot_w3_dot_org_slash_2001_slash_XMLSchema_literal );
                _ui_backend_config_writer.get_writer( context(), &t()->ui_backend_config.get() )->write_target_to( w );
                w.end_element( 0, backend_config_ui_backend_config_literal );
            }
        }

    }
}
