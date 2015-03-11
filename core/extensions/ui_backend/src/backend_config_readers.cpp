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
#include "backend_config_readers.hpp"
#include "backend_config_literals.hpp"
#include <xio/xml/binding/driver.hpp>

namespace ui_backend_settings
{
    namespace xio
    {
        void backend_config_ui_backend_config_diff_reader::read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value )
        {
            if ( ::xercesc::XMLString::equals( localname, backend_config_gc_interval_literal ) ) {
                driver()->context()->parse( value, t()->gc_interval );
                return;
            }
        }
        void backend_config_ui_backend_config_network_listen_tcp_reader::read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value )
        {
            if ( ::xercesc::XMLString::equals( localname, backend_config_address_literal ) ) {
                driver()->context()->parse( value, t()->address );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, backend_config_port_literal ) ) {
                driver()->context()->parse( value, t()->port );
                return;
            }
        }
        void backend_config_ui_backend_config_network_listen_reader::start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs )
        {
            if ( ::xercesc::XMLString::equals( localname, backend_config_tcp_literal ) ) {
                t()->tcp.resize( t()->tcp.size() + 1 );
                driver()->push( localname, _tcp_reader.get_reader( &t()->tcp.back() ) );
                return;
            }
        }
        void backend_config_ui_backend_config_network_reader::start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs )
        {
            if ( ::xercesc::XMLString::equals( localname, backend_config_listen_literal ) ) {
                driver()->push( localname, _listen_reader.get_reader( &t()->listen ) );
                return;
            }
        }
        void backend_config_ui_backend_config_reader::start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs )
        {
            if ( ::xercesc::XMLString::equals( localname, backend_config_diff_literal ) ) {
                driver()->push( localname, _diff_reader.get_reader( &t()->diff ) );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, backend_config_network_literal ) ) {
                driver()->push( localname, _network_reader.get_reader( &t()->network ) );
                return;
            }
        }
        void backend_config_reader::start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs )
        {
            if ( ::xercesc::XMLString::equals( localname, backend_config_ui_backend_config_literal ) ) {
                driver()->push( localname, _ui_backend_config_reader.get_reader( &t()->ui_backend_config.getset() ) );
                return;
            }
        }
    }
}
