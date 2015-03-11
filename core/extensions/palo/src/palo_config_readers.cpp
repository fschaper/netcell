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
#include "palo_config_readers.hpp"
#include "palo_config_literals.hpp"
#include <xio/xml/binding/driver.hpp>

namespace palo_cfg
{
    namespace xio
    {
        void CT_host_reader::read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value )
        {
            if ( ::xercesc::XMLString::equals( localname, palo_config_name_literal ) ) {
                driver()->context()->parse( value, t()->name.getset() );
                return;
            }
        }
        void CT_port_reader::read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value )
        {
            if ( ::xercesc::XMLString::equals( localname, palo_config_name_literal ) ) {
                driver()->context()->parse( value, t()->name.getset() );
                return;
            }
        }
        void CT_username_reader::read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value )
        {
            if ( ::xercesc::XMLString::equals( localname, palo_config_name_literal ) ) {
                driver()->context()->parse( value, t()->name.getset() );
                return;
            }
        }
        void CT_password_reader::read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value )
        {
            if ( ::xercesc::XMLString::equals( localname, palo_config_name_literal ) ) {
                driver()->context()->parse( value, t()->name.getset() );
                return;
            }
        }
        void CT_server_reader::start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs )
        {
            if ( ::xercesc::XMLString::equals( localname, palo_config_host_literal ) ) {
                driver()->push( localname, _host_reader.get_reader( &t()->host ) );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, palo_config_port_literal ) ) {
                driver()->push( localname, _port_reader.get_reader( &t()->port ) );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, palo_config_username_literal ) ) {
                driver()->push( localname, _username_reader.get_reader( &t()->username ) );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, palo_config_password_literal ) ) {
                driver()->push( localname, _password_reader.get_reader( &t()->password ) );
                return;
            }
        }
        void CT_certificate_reader::read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value )
        {
            if ( ::xercesc::XMLString::equals( localname, palo_config_path_literal ) ) {
                driver()->context()->parse( value, t()->path.getset() );
                return;
            }
        }
        void CT_palo_config_reader::start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs )
        {
            if ( ::xercesc::XMLString::equals( localname, palo_config_server_literal ) ) {
                driver()->push( localname, _server_reader.get_reader( &t()->server ) );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, palo_config_certificate_literal ) ) {
                driver()->push( localname, _certificate_reader.get_reader( &t()->certificate.getset() ) );
                return;
            }
        }
        void palo_config_reader::start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs )
        {
            if ( ::xercesc::XMLString::equals( localname, palo_config_palo_configuration_literal ) ) {
                driver()->push( localname, _palo_configuration_reader.get_reader( &t()->palo_configuration.getset() ) );
                return;
            }
        }
    }
}
