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

#ifndef FONT_CONFIG_READERS_HPP
#define FONT_CONFIG_READERS_HPP

#include "font_config.hpp"
#include <xio/xml/binding/type_reader.hpp>

namespace text_metrics_cfg
{
    namespace xio
    {
        using namespace ::xercesc;
        using namespace ::xio::xcs;
        using namespace ::xio::xml::binding;

        class CT_Font_reader;
        class CT_FontList_reader;
        class CT_dpi_reader;
        class CT_path_reader;
        class CT_textmetric_reader;
        class CT_key_val_reader;
        class CT_style_reader;
        class CT_font_config_reader;
        class font_config_reader;

        class CT_Font_reader : public type_reader
        {
        protected:
            CT_Font* t() {
                return static_cast<CT_Font*>( target() );
            }
            void read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value );
        };

        class CT_FontList_reader : public type_reader
        {
            auto_type_reader< CT_Font_reader > _font_reader;
        protected:
            CT_FontList* t() {
                return static_cast<CT_FontList*>( target() );
            }
            void start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs );
        };

        class CT_dpi_reader : public type_reader
        {
        protected:
            CT_dpi* t() {
                return static_cast<CT_dpi*>( target() );
            }
            void read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value );
        };

        class CT_path_reader : public type_reader
        {
        protected:
            CT_path* t() {
                return static_cast<CT_path*>( target() );
            }
            void read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value );
        };

        class CT_textmetric_reader : public type_reader
        {
            auto_type_reader< CT_dpi_reader > _dpi_reader;
            auto_type_reader< CT_path_reader > _font_path_reader;
        protected:
            CT_textmetric* t() {
                return static_cast<CT_textmetric*>( target() );
            }
            void start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs );
        };

        class CT_key_val_reader : public type_reader
        {
        protected:
            CT_key_val* t() {
                return static_cast<CT_key_val*>( target() );
            }
            void read_attribute( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const XMLCh* const value );
        };

        class CT_style_reader : public type_reader
        {
            auto_type_reader< CT_key_val_reader > _key_val_reader;
        protected:
            CT_style* t() {
                return static_cast<CT_style*>( target() );
            }
            void start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs );
        };

        class CT_font_config_reader : public type_reader
        {
            auto_type_reader< CT_FontList_reader > _font_list_reader;
            auto_type_reader< CT_textmetric_reader > _textmetric_reader;
            auto_type_reader< CT_style_reader > _default_style_reader;
        protected:
            CT_font_config* t() {
                return static_cast<CT_font_config*>( target() );
            }
            void start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs );
        };

        class font_config_reader : public type_reader
        {
            auto_type_reader< CT_font_config_reader > _font_setting_reader;
        protected:
            font_config* t() {
                return static_cast<font_config*>( target() );
            }
            void start_element( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const ::xercesc::Attributes& attrs );
        };

    }
}
#endif

