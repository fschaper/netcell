/**
 *  \file
 *  Copyright (C) 2006-2010 Jedox AG, Freiburg i.Br., Germany
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
 *  Florian Schaper <florian.schaper@jedox.com>
 *  Predrag Malicevic <predrag.malicevic@develabs.com>
 */

#include "precompiled_header.hpp"

#include "logging.hpp"

#include "backend_config.hpp"
#include "backend_config_parser.hpp"

#include "ui_backend.hpp"

#include <wss/define.hpp>
#include <wss/server.hpp>
#include <wss/fatal_exception.hpp>

#include <boost/filesystem.hpp>



/*!
 * \brief
 * initialize ui_backend extension and hook into WSS.
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
 */
extern "C" bool initialize_extension( server& server, const std::string& config_file )
{

    // read configuration file from the configurations directory
    if ( !boost::filesystem::exists( config_file ) ) {
        LOG_UI_BACKEND_ERROR( "cannot find configuration file: '" << config_file << "'." );
        return false;
    }

    // read configuration file from the configurations directory
    ui_backend_settings::backend_config doc;
    try {
        ::xio::xml::binding::parser parser;
        std::ifstream src( config_file.c_str() );
        parser.parse_doc( src, doc );
        if ( !doc.ui_backend_config.present() ) {
            LOG_UI_BACKEND_ERROR( "invalid configuration file: '" << config_file << "'." );
            return false;
        }
        LOG_UI_BACKEND_INFO( "parsing configuration file '" << config_file << "' ... Ok." );
        src.close();
    } catch ( ... ) {
        LOG_UI_BACKEND_ERROR( "parsing configuration file '" << config_file << "' ... Failed." );
        return false;
    }
    ui_backend_settings::backend_config_ui_backend_config& cfg = doc.ui_backend_config.get();

    std::string ip_address = cfg.network.listen.tcp[0].address;
    unsigned short tcp_port = cfg.network.listen.tcp[0].port;

    AJPServer& as = AJPServer::instance();

    server.on_server_startup.connect( boost::bind( &AJPServer::run, boost::ref( AJPServer::instance() ) ) );
    server.on_server_shutdown.connect( AJPServer::ShutdownInitiator() );

    SnapshotManager::instance();
    server.on_server_startup.connect( boost::bind( &SnapshotManager::gc_startup, boost::ref( SnapshotManager::instance() ) ) );
    server.on_server_shutdown.connect( boost::bind( &SnapshotManager::gc_shutdown, boost::ref( SnapshotManager::instance() ) ) );

    if ( as.bind_ipaddress( ip_address, tcp_port ) ) {
        return true;
    }

    return false;


}
