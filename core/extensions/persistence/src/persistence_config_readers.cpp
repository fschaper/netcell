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
#include "persistence_config_readers.hpp"
#include "persistence_config_literals.hpp"
#include <xio/xml/binding/driver.hpp>

namespace persistence_cfg
{
    namespace xio
    {
        void CT_patern_fill_reader::read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value )
        {
            if ( ::xercesc::XMLString::equals( localname, persistence_config_patternType_literal ) ) {
                driver()->context()->parse( value, t()->patternType );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, persistence_config_background_image_literal ) ) {
                driver()->context()->parse( value, t()->background_image );
                return;
            }
        }
        void CT_patern_fills_reader::start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs )
        {
            if ( ::xercesc::XMLString::equals( localname, persistence_config_pattern_fill_literal ) ) {
                t()->pattern_fill.resize( t()->pattern_fill.size() + 1 );
                driver()->push( localname, _pattern_fill_reader.get_reader( &t()->pattern_fill.back() ) );
                return;
            }
        }
        void CT_persistence_config_reader::start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs )
        {
            if ( ::xercesc::XMLString::equals( localname, persistence_config_pattern_fills_literal ) ) {
                driver()->push( localname, _pattern_fills_reader.get_reader( &t()->pattern_fills ) );
                return;
            }
        }
        void persistence_config_reader::start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs )
        {
            if ( ::xercesc::XMLString::equals( localname, persistence_config_persistence_settings_literal ) ) {
                driver()->push( localname, _persistence_settings_reader.get_reader( &t()->persistence_settings.getset() ) );
                return;
            }
        }
    }
}
