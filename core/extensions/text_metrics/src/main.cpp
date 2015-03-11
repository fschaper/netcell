/**
 *  \file
 *  Copyright (C) 2006-2010 Jedox AG
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
 *
 *  \author
 *  Doru Paraschiv <doru@yalos-solutions.com>
 */
#ifndef BOOST_FILESYSTEM_VERSION
#define BOOST_FILESYSTEM_VERSION 2
#endif
#include <wss/server.hpp>
#include <wss/text_metrics.hpp>
#include "logging.hpp"
#include "metrics_engine.hpp"
#include "textmetric_ftmgr.hpp"

#include "font_config.hpp"
#include "font_config_parser.hpp"

#define DEFAULT_DPI 96
#define DEFAULT_FONT_PATH "C:\\WINDOWS\\Fonts"

/*!
 * \brief
 * initialize the function_library extension and hook into WSS.
 *
 * \param server
 * server instances.
 *
 * \param config_file
 * path and filename to the configuration file for this module.
 *
 * \returns
 * true if the extension could be initialized successfully otherwise
 * returns false.
 *
 * \throws std::exception
 * will throw an exception if the configuration file could not be parsed
 */
extern "C" bool initialize_extension( server& server, const std::string& config_file )
{
    // read configuration file from the configurations directory
    if ( ! boost::filesystem::exists( config_file ) ) {
        LOG_TM_ERROR( "cannot find configuration file: '" << config_file << "'." );
        return false;
    }

    text_metrics_cfg::font_config cfg_doc;

    try {
        ::xio::xml::binding::parser().parse_doc( config_file.c_str(), cfg_doc );
        if ( !cfg_doc.font_setting.present() ) {
            LOG_TM_ERROR( "invalid configuration file: '" << config_file << "'." );
            return false;
        }
        LOG_TM_INFO( "parsing configuration file '" << config_file << "' ... Ok." );
    } catch ( ... ) {
        LOG_TM_ERROR( "parsing configuration file '" << config_file << "' ... Failed." );
        return false;
    }

    text_metrics_cfg::CT_font_config cfg = cfg_doc.font_setting.get();

    std::vector< std:: string > font_list;

    for ( std::vector< text_metrics_cfg::CT_Font >::const_iterator i = cfg.font_list.font.begin(), e = cfg.font_list.font.end(); i != e; i++ ) {
        font_list.push_back( i->font_name );
    }

    textmetric_internal::FTMgr::Yell();
    textmetric_internal::FTMgr::RegisterFontList( font_list );
    std::string font_path( DEFAULT_FONT_PATH );
    if ( cfg.textmetric.font_path.present() ) {
        font_path = cfg.textmetric.font_path.get().font_path;
    }
    textmetric_internal::FTMgr::RegisterFontPath( font_path );

    unsigned int default_dpi = 0;
    if ( cfg.textmetric.dpi.present() ) {
        default_dpi = cfg.textmetric.dpi.get().default_dpi;
    }
    if ( 0 == default_dpi ) {
        default_dpi = DEFAULT_DPI;
    }

    style_set_type default_ss;
    if ( cfg.default_style.present() ) {
        for ( std::vector< text_metrics_cfg::CT_key_val >::const_iterator i = cfg.default_style.get().key_val.begin(), e = cfg.default_style.get().key_val.end(); i != e; i++ ) {
            default_ss.add( i->key, i->val );
        }
    }

    text_metrics::instance().register_engine( text_metrics::shared_engine_type( new textmetric_internal::metrics_engine( default_dpi, default_ss ) ) );
    return true;
}
