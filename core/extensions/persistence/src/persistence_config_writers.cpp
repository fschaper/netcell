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
#include "persistence_config_writers.hpp"
#include "persistence_config_literals.hpp"

namespace persistence_cfg
{
    namespace xio
    {
        void CT_patern_fill_writer::write_target_to( xml_writer& w )
        {
            w.attribute( 0, persistence_config_patternType_literal, context()->serialize( t()->patternType ) );
            w.attribute( 0, persistence_config_background_image_literal, context()->serialize( t()->background_image ) );
        }

        void CT_patern_fills_writer::write_target_to( xml_writer& w )
        {
            for ( size_t sqi = 0; sqi < t()->pattern_fill.size(); ++sqi ) {
                w.start_element( 0, persistence_config_pattern_fill_literal );
                _pattern_fill_writer.get_writer( context(), &t()->pattern_fill[sqi] )->write_target_to( w );
                w.end_element( 0, persistence_config_pattern_fill_literal );
            }
        }

        void CT_persistence_config_writer::write_target_to( xml_writer& w )
        {
            w.start_element( 0, persistence_config_pattern_fills_literal );
            _pattern_fills_writer.get_writer( context(), &t()->pattern_fills )->write_target_to( w );
            w.end_element( 0, persistence_config_pattern_fills_literal );
        }

        void persistence_config_writer::write_target_to( xml_writer& w )
        {
            if ( t()->persistence_settings.present() ) {
                w.start_element( 0, persistence_config_persistence_settings_literal );
                w.attribute( 0, persistence_config_xmlns_literal, persistence_config_http_colon__slash__slash_www_dot_jedox_dot_com_slash_jedox_slash_wss_literal );
                w.attribute( persistence_config_xmlns_literal, persistence_config_NS_literal, persistence_config_http_colon__slash__slash_www_dot_jedox_dot_com_slash_jedox_slash_wss_literal );
                w.attribute( persistence_config_xmlns_literal, persistence_config_xs_literal, persistence_config_http_colon__slash__slash_www_dot_w3_dot_org_slash_2001_slash_XMLSchema_literal );
                _persistence_settings_writer.get_writer( context(), &t()->persistence_settings.get() )->write_target_to( w );
                w.end_element( 0, persistence_config_persistence_settings_literal );
            }
        }

    }
}
