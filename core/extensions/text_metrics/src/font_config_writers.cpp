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
#include "font_config_writers.hpp"
#include "font_config_literals.hpp"

namespace text_metrics_cfg
{
    namespace xio
    {
        void CT_Font_writer::write_target_to( xml_writer& w )
        {
            w.attribute( 0, font_config_font_name_literal, context()->serialize( t()->font_name ) );
        }

        void CT_FontList_writer::write_target_to( xml_writer& w )
        {
            for ( size_t sqi = 0; sqi < t()->font.size(); ++sqi ) {
                w.start_element( 0, font_config_font_literal );
                _font_writer.get_writer( context(), &t()->font[sqi] )->write_target_to( w );
                w.end_element( 0, font_config_font_literal );
            }
        }

        void CT_dpi_writer::write_target_to( xml_writer& w )
        {
            if ( t()->default_dpi != 96 ) {
                w.attribute( 0, font_config_default_dpi_literal, context()->serialize( t()->default_dpi ) );
            }
        }

        void CT_path_writer::write_target_to( xml_writer& w )
        {
            if ( t()->font_path != "C:\\WINDOWS\\Fonts" ) {
                w.attribute( 0, font_config_font_path_literal, context()->serialize( t()->font_path ) );
            }
        }

        void CT_textmetric_writer::write_target_to( xml_writer& w )
        {
            if ( t()->dpi.present() ) {
                w.start_element( 0, font_config_dpi_literal );
                _dpi_writer.get_writer( context(), &t()->dpi.get() )->write_target_to( w );
                w.end_element( 0, font_config_dpi_literal );
            }
            if ( t()->font_path.present() ) {
                w.start_element( 0, font_config_font_path_literal );
                _font_path_writer.get_writer( context(), &t()->font_path.get() )->write_target_to( w );
                w.end_element( 0, font_config_font_path_literal );
            }
        }

        void CT_key_val_writer::write_target_to( xml_writer& w )
        {
            w.attribute( 0, font_config_key_literal, context()->serialize( t()->key ) );
            w.attribute( 0, font_config_val_literal, context()->serialize( t()->val ) );
        }

        void CT_style_writer::write_target_to( xml_writer& w )
        {
            for ( size_t sqi = 0; sqi < t()->key_val.size(); ++sqi ) {
                w.start_element( 0, font_config_key_val_literal );
                _key_val_writer.get_writer( context(), &t()->key_val[sqi] )->write_target_to( w );
                w.end_element( 0, font_config_key_val_literal );
            }
        }

        void CT_font_config_writer::write_target_to( xml_writer& w )
        {
            w.start_element( 0, font_config_font_list_literal );
            _font_list_writer.get_writer( context(), &t()->font_list )->write_target_to( w );
            w.end_element( 0, font_config_font_list_literal );
            w.start_element( 0, font_config_textmetric_literal );
            _textmetric_writer.get_writer( context(), &t()->textmetric )->write_target_to( w );
            w.end_element( 0, font_config_textmetric_literal );
            if ( t()->default_style.present() ) {
                w.start_element( 0, font_config_default_style_literal );
                _default_style_writer.get_writer( context(), &t()->default_style.get() )->write_target_to( w );
                w.end_element( 0, font_config_default_style_literal );
            }
        }

        void font_config_writer::write_target_to( xml_writer& w )
        {
            if ( t()->font_setting.present() ) {
                w.start_element( 0, font_config_font_setting_literal );
                w.attribute( 0, font_config_xmlns_literal, font_config_http_colon__slash__slash_www_dot_jedox_dot_com_slash_jedox_slash_wss_literal );
                w.attribute( font_config_xmlns_literal, font_config_NS_literal, font_config_http_colon__slash__slash_www_dot_jedox_dot_com_slash_jedox_slash_wss_literal );
                w.attribute( font_config_xmlns_literal, font_config_xs_literal, font_config_http_colon__slash__slash_www_dot_w3_dot_org_slash_2001_slash_XMLSchema_literal );
                _font_setting_writer.get_writer( context(), &t()->font_setting.get() )->write_target_to( w );
                w.end_element( 0, font_config_font_setting_literal );
            }
        }

    }
}
