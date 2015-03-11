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
 *  Vali Nitu <vali@yalos-solutions.com>
 */

#include "xlsx_import_filter.hpp"
#include "export_wrapper.hpp"
#include "import_wrapper.hpp"

#include "persistence_config.hpp"
#include "persistence_config_parser.hpp"
#include "logging.hpp"

#include "pattern_translate.hpp"

#include <wss/server.hpp>
#include <boost/filesystem.hpp>
/*!
 * \brief
 * loads configuration parameters.
 */
void load_config( const std::string& config_file )
{

    // read configuration file from the configurations directory
    if ( ! boost::filesystem::exists( config_file ) ) {
        LOG_P_ERROR( "cannot find configuration file: '" << config_file << "'." );
        return;
    }

    persistence_cfg::persistence_config cfg_doc;

    try {
        ::xio::xml::binding::parser().parse_doc( config_file.c_str(), cfg_doc );
        if ( !cfg_doc.persistence_settings.present() ) {
            LOG_P_ERROR( "invalid configuration file: '" << config_file << "'." );
            return;
        }
        LOG_P_INFO( "parsing configuration file '" << config_file << "' ... Ok." );
    } catch ( ... ) {
        LOG_P_ERROR( "parsing configuration file '" << config_file << "' ... Failed." );
        return;
    }

    persistence_cfg::CT_persistence_config cfg = cfg_doc.persistence_settings.get();

    pattern_translate::instance().load( cfg.pattern_fills );
}

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
    load_config( config_file );

    filter_registry& r = server.filters();

    r.register_import_filter( filter_registry::shared_import_filter_type( new xlsx::import_wrapper() ) );
    r.register_export_filter( filter_registry::shared_export_filter_type( new xlsx::export_wrapper() ) );

    return true;
}
