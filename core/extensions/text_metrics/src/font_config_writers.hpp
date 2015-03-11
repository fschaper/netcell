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

#ifndef FONT_CONFIG_WRITERS_HPP
#define FONT_CONFIG_WRITERS_HPP

#include "font_config.hpp"
#include "font_config_literals.hpp"
#include <xio/xml/binding/type_writer.hpp>

namespace text_metrics_cfg
{
    namespace xio
    {
        using namespace ::xercesc;
        using namespace ::xio::xcs;
        using namespace ::xio::xml::binding;

        class CT_Font_writer;
        class CT_FontList_writer;
        class CT_dpi_writer;
        class CT_path_writer;
        class CT_textmetric_writer;
        class CT_key_val_writer;
        class CT_style_writer;
        class CT_font_config_writer;
        class font_config_writer;

        class CT_Font_writer : public type_writer
        {
            CT_Font* t() {
                return static_cast<CT_Font*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class CT_FontList_writer : public type_writer
        {
            auto_type_writer< CT_Font_writer > _font_writer;
            CT_FontList* t() {
                return static_cast<CT_FontList*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class CT_dpi_writer : public type_writer
        {
            CT_dpi* t() {
                return static_cast<CT_dpi*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class CT_path_writer : public type_writer
        {
            CT_path* t() {
                return static_cast<CT_path*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class CT_textmetric_writer : public type_writer
        {
            auto_type_writer< CT_dpi_writer > _dpi_writer;
            auto_type_writer< CT_path_writer > _font_path_writer;
            CT_textmetric* t() {
                return static_cast<CT_textmetric*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class CT_key_val_writer : public type_writer
        {
            CT_key_val* t() {
                return static_cast<CT_key_val*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class CT_style_writer : public type_writer
        {
            auto_type_writer< CT_key_val_writer > _key_val_writer;
            CT_style* t() {
                return static_cast<CT_style*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class CT_font_config_writer : public type_writer
        {
            auto_type_writer< CT_FontList_writer > _font_list_writer;
            auto_type_writer< CT_textmetric_writer > _textmetric_writer;
            auto_type_writer< CT_style_writer > _default_style_writer;
            CT_font_config* t() {
                return static_cast<CT_font_config*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

        class font_config_writer : public type_writer
        {
            auto_type_writer< CT_font_config_writer > _font_setting_writer;
            font_config* t() {
                return static_cast<font_config*>( target() );
            }
        public:
            void write_target_to( xml_writer& w );
        };

    }
}
#endif

