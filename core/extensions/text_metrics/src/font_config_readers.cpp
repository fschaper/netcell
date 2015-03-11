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
#include "font_config_readers.hpp"
#include "font_config_literals.hpp"
#include <xio/xml/binding/driver.hpp>

namespace text_metrics_cfg
{
    namespace xio
    {
        void CT_Font_reader::read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value )
        {
            if ( ::xercesc::XMLString::equals( localname, font_config_font_name_literal ) ) {
                driver()->context()->parse( value, t()->font_name );
                return;
            }
        }
        void CT_FontList_reader::start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs )
        {
            if ( ::xercesc::XMLString::equals( localname, font_config_font_literal ) ) {
                t()->font.resize( t()->font.size() + 1 );
                driver()->push( localname, _font_reader.get_reader( &t()->font.back() ) );
                return;
            }
        }
        void CT_dpi_reader::read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value )
        {
            if ( ::xercesc::XMLString::equals( localname, font_config_default_dpi_literal ) ) {
                driver()->context()->parse( value, t()->default_dpi );
                return;
            }
        }
        void CT_path_reader::read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value )
        {
            if ( ::xercesc::XMLString::equals( localname, font_config_font_path_literal ) ) {
                driver()->context()->parse( value, t()->font_path );
                return;
            }
        }
        void CT_textmetric_reader::start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs )
        {
            if ( ::xercesc::XMLString::equals( localname, font_config_dpi_literal ) ) {
                driver()->push( localname, _dpi_reader.get_reader( &t()->dpi.getset() ) );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, font_config_font_path_literal ) ) {
                driver()->push( localname, _font_path_reader.get_reader( &t()->font_path.getset() ) );
                return;
            }
        }
        void CT_key_val_reader::read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value )
        {
            if ( ::xercesc::XMLString::equals( localname, font_config_key_literal ) ) {
                driver()->context()->parse( value, t()->key );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, font_config_val_literal ) ) {
                driver()->context()->parse( value, t()->val );
                return;
            }
        }
        void CT_style_reader::start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs )
        {
            if ( ::xercesc::XMLString::equals( localname, font_config_key_val_literal ) ) {
                t()->key_val.resize( t()->key_val.size() + 1 );
                driver()->push( localname, _key_val_reader.get_reader( &t()->key_val.back() ) );
                return;
            }
        }
        void CT_font_config_reader::start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs )
        {
            if ( ::xercesc::XMLString::equals( localname, font_config_font_list_literal ) ) {
                driver()->push( localname, _font_list_reader.get_reader( &t()->font_list ) );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, font_config_textmetric_literal ) ) {
                driver()->push( localname, _textmetric_reader.get_reader( &t()->textmetric ) );
                return;
            }
            if ( ::xercesc::XMLString::equals( localname, font_config_default_style_literal ) ) {
                driver()->push( localname, _default_style_reader.get_reader( &t()->default_style.getset() ) );
                return;
            }
        }
        void font_config_reader::start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs )
        {
            if ( ::xercesc::XMLString::equals( localname, font_config_font_setting_literal ) ) {
                driver()->push( localname, _font_setting_reader.get_reader( &t()->font_setting.getset() ) );
                return;
            }
        }
    }
}
