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
 *  Dragan Simic <dragan.simic@develabs.com>
 */

#include "logging.hpp"

#include "palo_functions.hpp"
#include "spreadsheet_function.hpp"

#include "palo_config_parser.hpp"
#include "connection_handler.hpp"
#include "palo_config.hpp"

#include <libconnectionpool/ConnectionException.h>
#include <libpalo_ng/Palo/Exception/DatabaseNotFoundException.h>
#include <libpalo_ng/Network/SocketException.h>

#include <wss/define.hpp>
#include <wss/server.hpp>
#include <wss/fatal_exception.hpp>

#include <boost/filesystem.hpp>

/*!
 * \brief
 * palo event dispatcher
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
variant palo_wss3_dispatcher( session& s, const variant& parameter )
{
    if ( !parameter.is_array() || parameter.array().empty() ) {
        return variant( false );
    }

    const double option = parameter.array()[0].numeric();

    enum {
        synchronize_connections = 0,
        synchronize_connections_no_clear_on_sessions = 1
    };

    switch ( static_cast<unsigned long>( option ) ) {
        case synchronize_connections:
            connection_handler::instance().synchronize_settings();
            server::instance().session_handler().clear_connection_cache_on_all_sessions( s );
            break;
        case synchronize_connections_no_clear_on_sessions:
            connection_handler::instance().synchronize_settings();
            break;
        default:
            break;
    }

    return variant( true );
}

extern "C" bool initialize_extension( server& s, const std::string& config_file )
{
    // read configuration file from the configurations directory
    if ( ! boost::filesystem::exists( config_file ) ) {
        LOG_PALO_ERROR( "cannot find configuration file: '" << config_file << "'." );
        return false;
    }

    palo_cfg::palo_config cfg_doc;
    try {
        ::xio::xml::binding::parser().parse_doc( config_file.c_str(), cfg_doc );
        if ( !cfg_doc.palo_configuration.present() ) {
            LOG_PALO_ERROR( "invalid configuration file: '" << config_file << "'." );
            return false;
        }
        LOG_PALO_INFO( "parsing configuration file '" << config_file << "' ... Ok." );
    } catch ( ... ) {
        LOG_PALO_ERROR( "parsing configuration file '" << config_file << "' ... Failed." );
        return false;
    }

    palo_cfg::CT_palo_config cfg = cfg_doc.palo_configuration.get();
    if ( !cfg.server.host.name.present() ) {
        LOG_PALO_ERROR( "invalid configuration file (missing host name)." );
        return false;
    }

    const std::string& host =  cfg.server.host.name.get();
    if ( !cfg.server.port.name.present() ) {
        LOG_PALO_ERROR( "invalid configuration file (missing port definition)." );
        return false;
    }

    unsigned short port = boost::lexical_cast<unsigned short>( cfg.server.port.name.get() );
    if ( !cfg.server.username.name.present() ) {
        LOG_PALO_ERROR( "invalid configuration file (missing username)." );
        return false;
    }

    const std::string& username = cfg.server.username.name.get();
    if ( !cfg.server.password.name.present() ) {
        LOG_PALO_ERROR( "invalid configuration file (missing password)." );
    }

    const std::string& password = cfg.server.password.name.get();

    if ( cfg.certificate.present() ) {
        spreadsheet_function::InitSSL( cfg.certificate.get().path.get() );
    }

    try {
        // failure to create a connection to the palo master server will result in
        // a fatal error terminating the initialization process.
        connection_handler::instance().connect( host, port, username, password );
        connection_handler::instance().synchronize_settings();
        LOG_PALO_INFO( "connected to palo master server at ip address '" << host << "', port '" << port << "'" );
    } catch ( const std::exception& e ) {
        LOG_PALO_ERROR( "caught exception: '" << e.what() << "'" );
        return false;
    }

    // register the palo formula functions with the server
    register_palo_functions( s.functions() );

    // add us to the module registry
    extension_registry& registry = s.extension_registry();
    registry.register_extension( "palo_wss3", &palo_wss3_dispatcher );

    return true;
}
