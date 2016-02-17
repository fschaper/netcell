/*!
 *  \file
 *  Copyright (C) 2006-2008 Jedox AG, Freiburg i.Br., Germany
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
 *  <a href="http://www.jedox.com/license_worksheetserver.txt">
 *    http://www.jedox.com/license_worksheetserver.txtsa
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
 */

#include "precompiled_header.hpp"

#include "macro_engine_config.hpp"
#include "macro_engine_config_parser.hpp"

#include "logging.hpp"

#include "php_sapi.hpp"
#include "php_function_registry.hpp"
#include "php_file_callback_task.hpp"
#include "php_function_redirection_registry.hpp"
#include "boost/filesystem.hpp"

extern boost::filesystem::path g_temp_path;
extern zend_module_entry wssme_module_entry;

void echo_php_messages_to_screen( const std::string& message )
{
    LOG_PHP_DEBUG( message );
}

logging::log_level::level php_loglevel;

void forward_error_to_log( int loglevel, const std::string& message )
{
    logging::log_level::level crt_level = log_level_converter()( loglevel );
    if ( crt_level >= php_loglevel ) {
        LOG_PHP( crt_level , message );
    }
}


variant php_engine_dispatcher( session& s, const variant& parameter )
{
    enum event_type {
        register_function = 0,
        execute_file = 1,
        register_workbook_function = 2
    };

    // don't run any commands when we're shutting down
    if ( server::instance().current_state() == server::state::shutting_down
            || server::instance().current_state() == server::state::halted ) {
        return false;
    }

    // sanity check
    if ( !parameter.is_array()
            || parameter.array().empty()
            || parameter.array()[0].type() != variant::type_double ) {
        return false;
    }

    switch ( static_cast<int>( parameter.array()[0].numeric() ) ) {
        case register_function: {
            const variant::sparse_array_type& a = parameter.array();

            // sanity check
            {
                if ( a.size() < 6 ) {
                    LOG_PHP_ERROR( "not enough parameters passed to 'register_function' command (expected 5)!" );
                    return false;
                }

                if (   a[1].type() != variant::type_string
                        || a[2].type() != variant::type_string
                        || a[3].type() != variant::type_string
                        || a[4].type() != variant::type_bool
                        || a[5].type() != variant::type_bool ) {
                    LOG_PHP_ERROR( "wrong parameters passed to 'register_function' command (expected sssbb)!" );
                    return false;
                }
            }
            static php_function_registry& functions = php_function_registry::instance();
            functions.register_function( a[1].string(), a[2].string(), a[3].string(), a[4].boolean(), a[5].boolean() );

            return true;
        }
        break;

        case execute_file: {
            const variant::sparse_array_type& a = parameter.array();

            // sanity check
            {
                if ( a.size() < 4 ) {
                    return false;
                }

                if (   a[1].type() != variant::type_string
                        || a[2].type() != variant::type_string
                        || a[3].type() != variant::type_string ) {
                    return false;
                }
            }

            std::string filename = a[1].string();
            if ( ! filename.empty() && filename[0] != '/' ) {
                filename = php_sapi::instance().get_php_basedir() + "/" + filename;
            }
            std::string php_function = a[2].string();
            std::string active_selection = a[3].string();

            php_file_callback_task::parameter_list_type parameters;

            variant::variant_array_type::const_iterator it = a.begin();
            variant::variant_array_type::const_iterator end = a.end();
            it++;
            it++;
            it++;
            it++;

            for ( ; it != end; ++it ) {
                parameters.push_back( interpreter_variant( *it ) );
            }

            php_file_callback_task task( filename, php_function, parameters ) ;
            shared_workbook_type ws = s.selected().workbook().lock();
            php_sapi::auto_requestor_type   requestor( php_sapi::instance().requestor() );
            requestor->execute( s, active_selection, task );
            return task.result();
        }
        break;

        case register_workbook_function: {
            const variant::sparse_array_type& a = parameter.array();

            // sanity check
            {
                if ( a.size() < 6 ) {
                    LOG_PHP_ERROR( "not enough parameters passed to 'register_function' command (expected 5)!" );
                    return false;
                }

                if (   a[1].type() != variant::type_string
                        || a[2].type() != variant::type_string
                        || a[3].type() != variant::type_string
                        || a[4].type() != variant::type_bool
                        || a[5].type() != variant::type_bool ) {
                    LOG_PHP_ERROR( "wrong parameters passed to 'register_function' command (expected sssbb)!" );
                    return false;
                }
            }
            static php_function_redirection_registry& registry = php_function_redirection_registry::instance();
            shared_workbook_type wb = s.selected().workbook().lock();
            registry.register_function( wb->uuid(), a[1].string(), a[2].string(), a[3].string(), a[4].boolean(), a[5].boolean() );
            return true;
        }
        break;

        default:
            LOG_PHP_ERROR( "unknown event command '" << parameter.array()[0].numeric() << "' specified!"  );
            return false;
    }
    return false;
}

extern "C" bool initialize_extension( server& server, const std::string& config_file )
{
    // read configuration file from the configurations directory
    if ( !boost::filesystem::exists( config_file ) ) {
        LOG_PHP_ERROR( "cannot find configuration file: '" << config_file << "'." );
        return false;
    }

    // read configuration file from the configurations directory
    macro_engine_settings::macro_engine_config doc;
    try {
        ::xio::xml::binding::parser parser;
        std::ifstream src( config_file.c_str() );
        parser.parse_doc( src, doc );
        if ( !doc.php_macro_engine_config.present() ) {
            LOG_PHP_ERROR( "invalid configuration file: '" << config_file << "'." );
            return false;
        }
        LOG_PHP_INFO( "parsing configuration file '" << config_file << "' ... Ok." );
        src.close();
    } catch ( ... ) {
        LOG_PHP_ERROR( "parsing configuration file '" << config_file << "' ... Failed." );
        return false;
    }
    macro_engine_settings::macro_engine_config_php_macro_engine_config& cfg = doc.php_macro_engine_config.get();

    // php sapi initialization
    php_sapi& sapi = php_sapi::instance();
    php_sapi::extensions_list_type dynext_list;
    std::string php_basedir = cfg.php_files.directory;
    std::string php_include_paths;
    bool init_result;

    // get the loglevel
    php_loglevel = logging::log_level_factory::instance().create( ( std::string ) cfg.functions.loglevel );

    // additional configured include paths?
    for ( std::vector< macro_engine_settings::include_path_type >::const_iterator it = cfg.php_files.include_paths.get().include_path.begin(),
            end = cfg.php_files.include_paths.get().include_path.end(); it != end; ) {
        php_include_paths.append( it->relative ? ( php_basedir + DIRECTORY_SEPARATOR ) : "" ).append( it->path );
        if ( ++it != end ) {
            php_include_paths.append( PATH_SEPARATOR );
        }
    }

    // additional configured extensions?
    if ( cfg.php_extensions.present() ) {
        for ( std::vector< macro_engine_settings::extension_type >::const_iterator it = cfg.php_extensions.get().extensions.extension.begin(),
                end = cfg.php_extensions.get().extensions.extension.end(); it != end; it++ ) {
            dynext_list.push_back( it->extension_file );
        }
        php_include_paths += PATH_SEPARATOR + cfg.php_files.temp_directory;
        init_result = sapi.initialize(
                          php_loglevel,
                          php_basedir,
                          php_include_paths,
                          cfg.php_extensions.get().directory,
                          cfg.ini_directives.present() ? cfg.ini_directives.get() : "",
                          dynext_list,
                          wssme_module_entry,
                          1 );

    } else {
        init_result = sapi.initialize( php_loglevel, php_basedir, php_include_paths, "", "", dynext_list, wssme_module_entry, 1 );
    }

    if ( !init_result ) {
        LOG_PHP_ERROR( "failed to initialize the PHP module and extension(s)" );
        return false;
    } else {
        LOG_PHP_INFO( "initialized the PHP module and extension(s) with loglevel '" << ( std::string ) cfg.functions.loglevel << "'" );
    }

    //path for storing temporary files
    if ( !boost::filesystem::exists( cfg.php_files.temp_directory ) ) {
        try {
            boost::filesystem::create_directory( cfg.php_files.temp_directory );
        } catch ( const std::exception& e ) {
            LOG_PHP_ERROR( "failed to create tmp directory: " << e.what() );
        }
    } else {
        // clean temp directory
        try {
            std::string tmp_cfg_8( cfg.php_files.temp_directory );
            std::wstring tmp_cfg_16;
            tmp_cfg_16.assign( tmp_cfg_8.begin(), tmp_cfg_8.end() );
            boost::filesystem::wpath tmp_dir( tmp_cfg_16 );
            boost::filesystem::wdirectory_iterator tmp_dir_end;// default construction yields past-the-end
            for ( boost::filesystem::wdirectory_iterator tmp_dir_it( tmp_dir ); tmp_dir_it != tmp_dir_end; ++tmp_dir_it ) {
                boost::filesystem::remove_all( *tmp_dir_it );
            }
        } catch ( const std::exception& e ) {
            LOG_PHP_ERROR( "failed to clean tmp directory: " << e.what() );
        }
    }

    g_temp_path = cfg.php_files.temp_directory;

    if ( cfg.general_settings.console_echo ) {
        sapi.on_unbuffered_write.connect( echo_php_messages_to_screen );
    }
    sapi.on_log_message.connect( forward_error_to_log );

    // spreadsheet functions registration
    unsigned int funcs_no = 0;
    php_function_registry& php_functions = php_function_registry::instance();
    BOOST_FOREACH( const macro_engine_settings::function_type & f, cfg.functions.function ) {
        ++funcs_no;
        if ( ! f.php_file.empty() ) {
            php_functions.register_function(
                f.spreadsheet_function,
                php_basedir + DIRECTORY_SEPARATOR + f.php_file,
                f.php_function,
                f.always_recalc,
                f.view_independent_calculation );
        } else {
            php_functions.register_function( f.spreadsheet_function, f.php_function, f.always_recalc, f.view_independent_calculation );
        }
    }

    // add us to the module registry
    extension_registry& registry = server.extension_registry();
    registry.register_extension( "php_macro_engine", &php_engine_dispatcher );

    LOG_PHP_INFO( "registered " << funcs_no << " spreadsheet function" << ( ( ( funcs_no == 0 ) || ( funcs_no > 1 ) ) ? "s" : "" ) <<
                  ", using '" << php_basedir << "' as the base directory" );
    return true;
}

