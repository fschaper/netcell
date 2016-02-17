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
*  Predrag Malicevic <predrag.malicevic@develabs.com>
*  Momcilo Kleut <momcilo.kleut@develabs.com>
*/

#include "precompiled_header.hpp"
#include "CCmdHandler.hpp"
#if defined(_DEBUG)
#include <fstream>
#endif // _DEBUG
#include <wss/scoped_neutral_locale_enforcer.hpp>
#include <wss/core2_compatibility.hpp>
#include <wss/i_import_filter.hpp>
#include <wss/i_export_filter.hpp>

CCmdHandler::Init::Init ()
{
    cmd_handlers_map = boost::assign::list_of<std::pair<std::string, cmd_handler_ptr_t> >

                       ( std::string( "logi" ), &CCmdHandler::cmd_login )
                       ( std::string( "logo" ), &CCmdHandler::cmd_logout )
                       ( std::string( "ilog" ), &CCmdHandler::cmd_is_logged_in )

                       ( std::string( "gusl" ), &CCmdHandler::cmd_get_user_locale )
                       ( std::string( "susl" ), &CCmdHandler::cmd_set_user_locale )
                       ( std::string( "l10nd" ), &CCmdHandler::cmd_l10n_default )
                       ( std::string( "l10nr" ), &CCmdHandler::cmd_l10n_revert )

                       ( std::string( "gsi" ), &CCmdHandler::cmd_get_server_info )

                       ( std::string( "sbrd" ), &CCmdHandler::cmd_set_border )
                       ( std::string( "gbrd" ), &CCmdHandler::cmd_get_border )

                       ( std::string( "gcwe" ), &CCmdHandler::cmd_get_changed_wsels )

                       ( std::string( "snpc" ), &CCmdHandler::cmd_snapshot_create )
                       ( std::string( "snpg" ), &CCmdHandler::cmd_snapshot_get )
                       ( std::string( "snpd" ), &CCmdHandler::cmd_snapshot_diff )

                       ( std::string( "olst" ), &CCmdHandler::cmd_wssobjects_list )
                       ( std::string( "osel" ), &CCmdHandler::cmd_wssobjects_select )
                       ( std::string( "oren" ), &CCmdHandler::cmd_wssobjects_rename )
                       ( std::string( "oadd" ), &CCmdHandler::cmd_wssobjects_add )
                       ( std::string( "odel" ), &CCmdHandler::cmd_wssobjects_delete )

                       ( std::string( "gurn" ), &CCmdHandler::cmd_get_used_range )
                       ( std::string( "gval" ), &CCmdHandler::cmd_get_rng_as_vals )
                       ( std::string( "grar" ), &CCmdHandler::cmd_get_rng_as_rgns )

                       ( std::string( "gdst" ), &CCmdHandler::cmd_get_def_style )
                       ( std::string( "sdst" ), &CCmdHandler::cmd_set_def_style )

                       ( std::string( "gdcr" ), &CCmdHandler::cmd_get_def_colrow_dims )
                       ( std::string( "sdcr" ), &CCmdHandler::cmd_set_def_colrow_dims )
                       ( std::string( "gcr" ), &CCmdHandler::cmd_get_colrow_dims )
                       ( std::string( "scr" ), &CCmdHandler::cmd_set_colrow_dims )
                       ( std::string( "afit" ), &CCmdHandler::cmd_autofit )
                       ( std::string( "adcr" ), &CCmdHandler::cmd_adapt )
                       ( std::string( "gmc" ), &CCmdHandler::cmd_get_max_cell_dims )

                       ( std::string( "sac" ), &CCmdHandler::cmd_set_auto_calc )

                       ( std::string( "gfs" ), &CCmdHandler::cmd_get_formatted_sample )

                       ( std::string( "load" ), &CCmdHandler::cmd_load_workbook )
                       ( std::string( "save" ), &CCmdHandler::cmd_save_workbook )
                       ( std::string( "limp" ), &CCmdHandler::cmd_import_workbook )
                       ( std::string( "lexp" ), &CCmdHandler::cmd_export_workbook )
                       ( std::string( "bns" ), &CCmdHandler::cmd_book_not_saved )
                       ( std::string( "gust" ), &CCmdHandler::cmd_get_undo_state )
                       ( std::string( "undo" ), &CCmdHandler::cmd_undo )
                       ( std::string( "redo" ), &CCmdHandler::cmd_redo )
                       ( std::string( "cprn" ), &CCmdHandler::cmd_copy_range )
                       ( std::string( "cfrn" ), &CCmdHandler::cmd_copyfill_range )
                       ( std::string( "cmrn" ), &CCmdHandler::cmd_copymove_range )
                       ( std::string( "ctrn" ), &CCmdHandler::cmd_cut_range )
                       ( std::string( "ptrn" ), &CCmdHandler::cmd_paste_range )

                       ( std::string( "clat" ), &CCmdHandler::cmd_clear_attributes )
                       ( std::string( "hbd" ), &CCmdHandler::cmd_hb_dependents )
                       ( std::string( "saf" ), &CCmdHandler::cmd_set_array_formula )
                       ( std::string( "uaf" ), &CCmdHandler::cmd_unset_array_formula )

                       ( std::string( "nget" ), &CCmdHandler::cmd_names_get )
                       ( std::string( "nlst" ), &CCmdHandler::cmd_names_list )
                       ( std::string( "nadd" ), &CCmdHandler::cmd_names_add )
                       ( std::string( "nupd" ), &CCmdHandler::cmd_names_update )
                       ( std::string( "ndel" ), &CCmdHandler::cmd_names_delete )
                       ( std::string( "nexs" ), &CCmdHandler::cmd_names_exists )

                       ( std::string( "svar" ), &CCmdHandler::cmd_set_variable )
                       ( std::string( "gvar" ), &CCmdHandler::cmd_get_variable )
                       ( std::string( "gvls" ), &CCmdHandler::cmd_get_variable_list )
                       ( std::string( "cvar" ), &CCmdHandler::cmd_clear_variables )
                       ( std::string( "gbvl" ), &CCmdHandler::cmd_get_book_var_list )

                       ( std::string( "wget" ), &CCmdHandler::cmd_get_wsheet_elements )
                       ( std::string( "wadd" ), &CCmdHandler::cmd_add_wsheet_elements )
                       ( std::string( "wupd" ), &CCmdHandler::cmd_update_wsheet_elements )
                       ( std::string( "wdel" ), &CCmdHandler::cmd_delete_wsheet_elements )

                       ( std::string( "bget" ), &CCmdHandler::cmd_get_wsheet_elements )
                       ( std::string( "badd" ), &CCmdHandler::cmd_add_wsheet_elements )
                       ( std::string( "bupd" ), &CCmdHandler::cmd_update_wsheet_elements )
                       ( std::string( "bdel" ), &CCmdHandler::cmd_delete_wsheet_elements )

                       ( std::string( "cdrg" ), &CCmdHandler::cmd_set_cell_region )
                       ( std::string( "cdrn" ), &CCmdHandler::cmd_set_cell_range )

                       ( std::string( "clr" ), &CCmdHandler::cmd_clear )
                       ( std::string( "co" ), &CCmdHandler::cmd_copypaste )
                       ( std::string( "cm" ), &CCmdHandler::cmd_copymovepaste )
                       ( std::string( "cu" ), &CCmdHandler::cmd_cutpaste )

                       ( std::string( "icel" ), &CCmdHandler::cmd_insert_cells )
                       ( std::string( "dcel" ), &CCmdHandler::cmd_delete_cells )

                       ( std::string( "ic" ), &CCmdHandler::cmd_insert_column )
                       ( std::string( "ir" ), &CCmdHandler::cmd_insert_row )
                       ( std::string( "dc" ), &CCmdHandler::cmd_delete_column )
                       ( std::string( "dr" ), &CCmdHandler::cmd_delete_row )

                       ( std::string( "mrg" ), &CCmdHandler::cmd_merge )
                       ( std::string( "umrg" ), &CCmdHandler::cmd_unmerge )

                       ( std::string( "cfset" ), &CCmdHandler::cmd_cndfmt_set )
                       ( std::string( "cfget" ), &CCmdHandler::cmd_cndfmt_get )
                       ( std::string( "cfmov" ), &CCmdHandler::cmd_cndfmt_move )
                       ( std::string( "cfdel" ), &CCmdHandler::cmd_cndfmt_delete )

                       ( std::string( "mark" ), &CCmdHandler::cmd_mark )

                       ( std::string( "lock" ), &CCmdHandler::cmd_lock )

                       ( std::string( "ocurr" ), &CCmdHandler::cmd_wss_active_objects_select )

                       ( std::string( "tee" ), &CCmdHandler::cmd_trigger_exten_event )
                       ( std::string( "em" ), &CCmdHandler::cmd_execute_macro )

                       ( std::string( "bels" ), &CCmdHandler::cmd_workbook_list_ex )
                       ( std::string( "bcmd" ), &CCmdHandler::cmd_book_change_metadata )

                       ( std::string( "smv" ), &CCmdHandler::cmd_move_worksheet )
                       ( std::string( "scp" ), &CCmdHandler::cmd_copy_worksheet )
                       ( std::string( "sclo" ), &CCmdHandler::cmd_add_clone_worksheet )
                       ( std::string( "srcl" ), &CCmdHandler::cmd_remove_clone_worksheet )

                       ( std::string( "gur" ), &CCmdHandler::cmd_get_unlckd_ranges )
                       ( std::string( "bcc" ), &CCmdHandler::cmd_begin_calc_context )
                       ( std::string( "ecc" ), &CCmdHandler::cmd_end_calc_context )
                       ( std::string( "ping" ), &CCmdHandler::cmd_ping )
                       ( std::string( "gwv" ), &CCmdHandler::cmd_get_workbook_version )
                       ;

    LOG_UI_BACKEND_DEBUG( "compound command handler inited" );
}

const std::string CCmdHandler::HEADER_SESS = "X-Sess-Select";
const std::string CCmdHandler::HEADER_BOOK = "X-WSS-Book";
const std::string CCmdHandler::DEFAULT_SESS_NAME = "WSS_SESSID";
const std::string CCmdHandler::DEFAULT_L10N = "en_US";

const CCmdHandler::Init CCmdHandler::init;

CCmdHandler::CCmdHandler ( const char* handle )
    : BackendHandler( handle )
    , m_json_serializer()
    , m_request( NULL )
    , m_response( NULL )
    , m_result( std::ios_base::out )
    , m_logged_out( true )
{
    name_thread( "ui_backend ccmd handler" );
    LOG_UI_BACKEND_DEBUG( "compound command handler instantiated" );
}

void CCmdHandler::respond ( int status_code, const std::string& response )
{
    using namespace std;

    m_response->Write( response );

    m_response->SetContentLength( ( long )response.size() );
    m_response->SetContentType( string( "application/json; charset=utf-8; charset=UTF-8" ) );

    m_response->SetHeader( string( "Expires" ), string( "Fri, 03 Sep 1999 01:00:00 GMT" ) );
    m_response->SetHeader( string( "Last-Modified" ), get_http_date() );
    m_response->SetHeader( string( "Cache-Control" ), string( "no-store, no-cache, must-revalidate, post-check=0, pre-check=0" ) );
    m_response->SetHeader( string( "Pragma" ), string( "no-cache" ) );

    m_response->SetHttpStatusCode( status_code );
    m_response->SetHttpStatusMsg( BackendHandler::init.status_msg_map.find( status_code )->second );
}

void CCmdHandler::fail ( int status_code, const char* msg )
{
    respond( status_code, std::string( msg ) );
}

void CCmdHandler::succeed ( const std::string& response )
{
    respond( 200, response );
}

void CCmdHandler::succeed ()
{
    respond( 200, m_result.str() );
}

void CCmdHandler::operator() ( const HttpRequest& request, HttpResponse& response )
{
    using namespace std;

    m_request = &request;
    m_response = &response;

    const IFile* req_body_file = request.BodyFile();

#if defined(_DEBUG)
    static const bool debug_log_commands = true;
    static std::auto_ptr<std::fstream> logging_stream;

    if ( debug_log_commands && logging_stream.get() == NULL ) {
        // (fschaper) this code is not thread safe. multiple requests issued by the UI at the same time
        // may re-initialize the logging stream. do not enable for release builds and use with care while debugging.
        logging_stream.reset( new std::fstream( "c:\\stuff\\debug_stream_core3.txt", std::ios::out | std::ios::app ) );
    }
#endif // _DEBUG

    if ( !req_body_file ) {
        fail( 400, "Bad Request: no POST data" );
        return;
    }

    size_t req_body_size = req_body_file->size();
    boost::scoped_array<char> req_body_buff( new char[req_body_size + 1] );
    req_body_buff[req_body_size] = '\0';

    req_body_file->reset_read();
    req_body_file->fread( req_body_buff.get(), 1, req_body_size );

    const string post_data = req_body_buff.get();
    req_body_buff.reset();

#if defined(_DEBUG)
    if ( debug_log_commands ) {
        ( *logging_stream ) << "command\n" << post_data << std::endl;
    }
#endif // _DEBUG

    LOG_UI_BACKEND_DEBUG( "received compound command: " << post_data );

    json_variant_t parse_data = json::parse( post_data.begin(), post_data.end() );
    if ( parse_data->type() != typeid( json_array_t ) ) {
        fail( 400, "Bad Request: malformed compound commands" );
        return;
    }

    http_props_map_t::const_iterator props_it = m_request->Headers().find( CCmdHandler::HEADER_SESS );
    if ( props_it != m_request->Headers().end() && props_it->second.size() ) {
        m_session_name = string( "WSS" ) + static_cast<char>( toupper( props_it->second[0] ) ) + "_SESSID";
    } else {
        m_session_name = CCmdHandler::DEFAULT_SESS_NAME;
    }

    props_it = m_request->CookieMap().find( m_session_name );

    if ( props_it != m_request->CookieMap().end() ) {
        size_t sess_name_len = m_session_name.size();
        m_session_id = props_it->second.substr( sess_name_len + 1, props_it->second.find_first_of( ';' ) - sess_name_len );
    }

    if ( m_session_id.size() ) {

        try {
            m_session_context = server::instance().session_handler().get( m_session_id );
            m_logged_out = false;
            LOG_UI_BACKEND_DEBUG( "valid session received (" << m_session_id << ")" );
        } catch ( const invalid_session_exception& ) {
            LOG_UI_BACKEND_DEBUG( "no valid session received" );
            m_session_id = "";

        }
    }


    props_it = m_request->Headers().find( CCmdHandler::HEADER_BOOK );
    if ( props_it != m_request->Headers().end() && props_it->second.size() ) {
        vector<string> book_hdr;
        boost::split( book_hdr, props_it->second, boost::is_from_range( ' ', ' ' ) );

        try {
            shared_workbook_type book_obj = m_session_context->selected().workbook().lock();// get_active_workbook().lock();

            if ( book_obj &&  boost::lexical_cast< std::string >( book_obj->uuid() ) != book_hdr[0] ) {
                LOG_UI_BACKEND_DEBUG( "switching to book " << book_hdr[0] );

                select_workbook_command command( *m_session_context,  boost::lexical_cast< uuid_type >( book_hdr[0] ) );
                command.execute();

                if ( book_hdr.size() > 1 ) {
                    select_worksheet_command command( *m_session_context, boost::lexical_cast< uuid_type >( book_hdr[1] ) );
                    command.execute();
                }
            }
        } catch ( const exception& e ) {
            fail( 500, "cannot switch to active book" );
            return;
        }
    }

    unsigned int flags = 0;

    props_it = m_request->Attributes().find( string( "query_string" ) );
    if ( props_it != m_request->Attributes().end() ) {
        stringstream ss( props_it->second );
        ss >> flags;
    }

    const bool stop_on_error = flags & FLAG_STOP_ON_ERROR;
    const bool use_default_l10n = ( flags & FLAG_USE_DEFAULT_L10N ) != 0;

    m_l10n_orig = m_logged_out ? CCmdHandler::DEFAULT_L10N : m_session_context->locale().code();
    //m_l10n_orig = CCmdHandler::DEFAULT_L10N ;

    if ( use_default_l10n && m_l10n_orig != CCmdHandler::DEFAULT_L10N ) {
        try {
            m_session_context->locale( ::locale::create( CCmdHandler::DEFAULT_L10N ) );
        } catch ( std::exception& /*e*/ ) {
            LOG_UI_BACKEND_ERROR( "cannot switch to default locale" );
            fail( 500, "cannot switch to default locale" );
            return;
        }

        m_l10n_curr = CCmdHandler::DEFAULT_L10N;
    } else {
        m_l10n_curr = m_l10n_orig;
    }

    const json_array_t& cmds = boost::any_cast<json_array_t>( *parse_data );

    m_result.clear();
    m_result.str( "" );
    m_result << '[';

    for ( json_array_t::const_iterator it = cmds.begin(), it_end = cmds.end(); it != it_end; ++it ) {
        const json_variant_t& curr_cmd = *it;

        if ( curr_cmd->type() != typeid( json_array_t ) ) {
            m_result << "[false,101,\"malformed command\"],";

            if ( stop_on_error ) {
                break;
            } else {
                continue;
            }
        }

        const json_array_t& cmd = boost::any_cast<json_array_t>( *curr_cmd );

        if ( cmd[0]->type() != typeid( string ) ) {
            m_result << "[false,101,\"malformed command handle\"],";

            if ( stop_on_error ) {
                break;
            } else {
                continue;
            }
        }

        const string cmd_handle = boost::any_cast<string>( *cmd[0] );

        cmd_handlers_map_t::const_iterator cmd_handler_it = CCmdHandler::init.cmd_handlers_map.find( cmd_handle );

        if ( cmd_handler_it == CCmdHandler::init.cmd_handlers_map.end() ) {
            m_result << "[false,102,\"unknown command\"],";
            LOG_UI_BACKEND_ERROR( "unknown command '" << cmd_handle << "' requested." );

            if ( stop_on_error ) {
                break;
            } else {
                continue;
            }
        }

        {
            boost::timer performance;

            if ( !( this->*cmd_handler_it->second )( cmd ) && stop_on_error ) {
                break;
            }

            LOG_UI_BACKEND_DEBUG( cmd_handle << " request completed in " << performance.elapsed() << " seconds." );
        }
    }

    if ( use_default_l10n && !m_logged_out && m_l10n_curr != m_l10n_orig ) {
        try {
            m_session_context->locale( ::locale::create( m_l10n_orig ) );
        } catch ( std::exception& /*e*/ ) {
            LOG_UI_BACKEND_ERROR( "cannot revert to original locale" );
            fail( 500, "cannot revert to original locale" );
            return;
        }

        m_l10n_curr = m_l10n_orig;
    }

    m_result.seekp( -1, ios_base::end );
    m_result << ']';

#if defined(_DEBUG)
    if ( debug_log_commands ) {
        ( *logging_stream ) << "result\n" << m_result.str() << std::endl << std::endl;
    }
#endif // _DEBUG

    succeed();
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

inline bool CCmdHandler::fail_cmd ( const char* cmd, const std::exception& e )
{
    LOG_CCMD_ERROR( cmd, "exception: " << e.what() );

    const wss_runtime_exception* wse = dynamic_cast<const wss_runtime_exception*>( &e );
    int err_code = wse != NULL ? wse->error_code() : 1;

    m_result << "[false," << err_code << "," << m_json_serializer( std::string( e.what() ) ) << "],";

    return false;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

inline bool CCmdHandler::fail_cmd ( const char* cmd, int err_code, const std::string& err_msg )
{
    LOG_CCMD_ERROR( cmd, "error: " << err_code << " (" << err_msg << ")" );

    m_result << "[false," << err_code << "," << m_json_serializer( err_msg ) << "],";

    return false;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

inline bool CCmdHandler::fail_cmd ( const char* cmd, int err_code, const char* err_msg )
{
    LOG_CCMD_ERROR( cmd, "error: " << err_code << " (" << err_msg << ")" );

    m_result << "[false," << err_code << "," << m_json_serializer( std::string( err_msg ) ) << "],";

    return false;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

inline variant CCmdHandler::json2Value( const json_variant_t& element )
{
    if ( element->type() == typeid( int ) ) {
        return variant( double( boost::any_cast<int>( *element ) ) );
    } else if ( element->type() == typeid( double ) ) {
        return variant( boost::any_cast<double>( *element ) );
    } else if ( element->type() == typeid( std::string ) ) {
        return variant( boost::any_cast<std::string>( *element ) );
    } else if ( element->type() == typeid( bool ) ) {
        return variant( boost::any_cast<bool>( *element ) );
    } else if ( element->type() == typeid( json_array_t ) ) {
        return variant( ~element );
    } else if ( element->type() == typeid( json_obj_t ) ) {
        return variant( ~element );
    }

    return variant( "" );
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

inline bool CCmdHandler::transform_coords ( unsigned long& x1, unsigned long& y1 )
{
    return --x1 < 0 || x1 > sheet_dimension::max_column || --y1 < 0 || y1 > sheet_dimension::max_row ? false : true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

inline bool CCmdHandler::transform_coords ( unsigned long& x1, unsigned long& y1, unsigned long& x2, unsigned long& y2 )
{
    if ( --x1 < 0 || x1 > sheet_dimension::max_column || --y1 < 0 || y1 > sheet_dimension::max_row ||
            --x2 < 0 || x2 > sheet_dimension::max_column || --y2 < 0 || y2 > sheet_dimension::max_row ) {
        return false;
    }

    return x2 < x1 || y2 < y1 ? false : true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

inline bool CCmdHandler::bind_rect ( int offset, const json_array_t& coords, sheet_range& br )
{
    unsigned long x1 = boost::any_cast<int>( *coords[offset] ),
                  y1 = boost::any_cast<int>( *coords[1 + offset] ),
                  x2 = boost::any_cast<int>( *coords[2 + offset] ),
                  y2 = boost::any_cast<int>( *coords[3 + offset] );

    if ( !transform_coords( x1, y1, x2, y2 ) ) {
        return false;
    }

    br = sheet_range( sheet_point( y1, x1 ), sheet_point( y2, x2 ) );

    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_login ( const json_array_t& cmd )
{
    using namespace std;

    if ( ! m_logged_out ) {
        return fail_cmd( "cmd_login", ERR_RUNTIME_ERROR, "already logged in" );
    }

    if ( ! test_types<std::string>( 3, 'l', 1, cmd ) ) {
        return fail_cmd( "cmd_login", ERR_PARSING_FAILED, "command malformed" );
    }

    const string username = boost::any_cast<std::string>( *cmd[1] );
    const string password = boost::any_cast<std::string>( *cmd[2] );
    std::set<std::string> group_set;

    if ( cmd.size() > 3 ) {

        if ( cmd[3]->type() != typeid( json_array_t ) ) {
            return fail_cmd( "cmd_login", ERR_PARSING_FAILED, "command malformed" );
        }

        const json_array_t& groups = boost::any_cast<json_array_t>( *cmd[3] );

        for ( json_array_t::size_type group_i = 0; group_i < groups.size(); group_i++ ) {

            if ( groups[group_i]->type() != typeid( std::string ) ) {
                return fail_cmd( "cmd_login", ERR_PARSING_FAILED, "command malformed" );
            }

            group_set.insert( boost::any_cast<string>( *groups[group_i] ) );
        }
    }

    try {
        m_session_context = server::instance().session_handler().create( ::locale::create( "en_US" ), username, password, group_set ) ;

        m_session_id = boost::lexical_cast<std::string>( m_session_context->uuid() );

        m_logged_out = false;

        m_result << "[true,\"" << m_session_id << "\"],";

        m_response->SetHeader( "Set-Cookie", m_session_name + "=" + m_session_id + "; Path=/" );

        LOG_CCMD_INFO( "cmd_login", "logged in with username " << username );

        return true;
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_login", e );
    }
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_logout ( const json_array_t& cmd )
{
    using namespace std;

    if ( m_logged_out ) {
        return fail_cmd( "cmd_logout", ERR_INVALID_SESSION, "invalid session received" );
    }

    try {
        SnapshotManager& snapshot_manager = SnapshotManager::instance();
        snapshot_manager.remove_snapshots( m_session_id );

        server::instance().session_handler().remove_session( m_session_id );
        m_session_id = "";
        m_logged_out = true;

        m_result << "[true],";

        LOG_CCMD_INFO( "cmd_logout", m_session_context->username() + " logged out" );

        return true;
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_logout", e );
    }
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_is_logged_in( const json_array_t& )
{
    m_result << "[true," << ( m_logged_out ? "false" : "true" ) << "],";

    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_ping ( const json_array_t& cmd )
{
    try {
        for ( json_array_t::size_type i = cmd.size() - 1; i > 0; --i ) {
            if ( cmd[i]->type() != typeid( std::string ) ) {
                continue;
            }

            const std::string sess_id = boost::any_cast<std::string>( *cmd[i] );

            if ( sess_id.empty() || sess_id == m_session_id ) {
                continue;
            }
            try {
                server::instance().session_handler().get( sess_id )->revitalize();
            } catch ( const invalid_session_exception& ) {
                continue;
            }
        }
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_ping", e );
    }

    m_result << "[true],";

    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_get_user_locale ( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_get_user_locale", ERR_INVALID_SESSION, "invalid session received" );
    }

    try {
        m_result << "[true,\"" << m_session_context->locale().code() << "\"],";
        return true;
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_get_user_locale", e );
    }
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_set_user_locale ( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_set_user_locale", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( ! test_types<std::string>( 2, 'd', 1, cmd ) ) {
        return fail_cmd( "cmd_set_user_locale", ERR_PARSING_FAILED, "command malformed" );
    }

    const std::string locale = boost::any_cast<std::string>( *cmd[1] );

    try {
        m_session_context->locale( ::locale::create( locale ) );
        m_l10n_curr = locale;
        m_result << std::string( "[true," ) << "true"  << std::string( "]," );

        return true;
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_set_user_locale", e );
    }
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_l10n_default ( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_l10n_default", ERR_INVALID_SESSION, "invalid session received" );
    }

    try {
        if ( m_l10n_curr != CCmdHandler::DEFAULT_L10N ) {
            m_session_context->locale( ::locale::create( CCmdHandler::DEFAULT_L10N ) );
            m_l10n_curr = CCmdHandler::DEFAULT_L10N;
        }

        m_result << std::string( "[true,\"" ) << m_l10n_curr << std::string( "\"]," );

        return true;
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_l10n_default", e );
    }
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_l10n_revert ( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_l10n_revert", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( m_l10n_curr != m_l10n_orig ) {
        m_session_context->locale( ::locale::create( m_l10n_orig ) );
        m_l10n_curr = m_l10n_orig;
    }

    m_result << std::string( "[true,\"" ) << m_l10n_curr << std::string( "\"]," );

    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_get_server_info ( const json_array_t& cmd )
{
    get_server_version_command command;
    m_result << std::string( "[true,\"" ) + execute_fetch( command ) + "\"],";

    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_set_border( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_set_border", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( cmd.size() < 4 ) {
        return fail_cmd( "cmd_set_border", ERR_PARSING_FAILED, "command malformed" );
    }

    try {
        for ( json_array_t::size_type i_cmd = 1; i_cmd < cmd.size(); i_cmd += 3 ) {

            if ( cmd[i_cmd ]->type() != typeid( json_array_t ) ) {
                return fail_cmd( "cmd_set_border", ERR_PARSING_FAILED, "command malformed" );
            }

            if ( cmd[i_cmd +1]->type() != typeid( int ) ) {
                return fail_cmd( "cmd_set_border", ERR_PARSING_FAILED, "command malformed" );
            }

            if ( cmd[i_cmd +2]->type() != typeid( std::string ) ) {
                return fail_cmd( "cmd_set_border", ERR_PARSING_FAILED, "command malformed" );
            }

            const json_array_t& coords = boost::any_cast<json_array_t>( *cmd[i_cmd] );

            if ( ! test_types<int, int, int, int>( 4, 'd', 0, coords ) ) {
                return fail_cmd( "cmd_set_border", ERR_PARSING_FAILED, "command malformed" );
            }

            sheet_range range( sheet_point( 0, 0 ) );

            if ( ! bind_rect( 0, coords, range ) ) {
                return fail_cmd( "cmd_set_border", ERR_PARSING_FAILED, "check_range_coord: invalid coordinates" );
            }

            long type = boost::any_cast<int>( *cmd[i_cmd+1] );
            std::string style = boost::any_cast<std::string>( *cmd[i_cmd+2] );

            set_border_command set_command( *m_session_context, range, type, style );
            m_session_context->undo_redo_log().execute( set_command );
        }

        m_result << std::string( "[true,\"\"]," );
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_set_border", e );
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_get_border( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_get_border", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( ! test_types<json_array_t>( 2, 'd', 1, cmd ) ) {
        return fail_cmd( "cmd_get_border", ERR_PARSING_FAILED, "command malformed" );
    }

    const json_array_t& coords = boost::any_cast<json_array_t>( *cmd[1] );

    if ( ! test_types<int, int, int, int>( 4, 'd', 0, coords ) ) {
        return fail_cmd( "cmd_get_border", ERR_PARSING_FAILED, "command malformed" );
    }

    try {
        sheet_range range( sheet_point( 0, 0 ) );

        if ( ! bind_rect( 0, coords, range ) ) {
            return fail_cmd( "cmd_get_border", ERR_PARSING_FAILED, "check_range_coord: invalid coordinates" );
        }

        get_border_command get_command( *m_session_context, range );

        m_result << std::string( "[true," ) << m_json_serializer( execute_fetch( get_command ), JSONSerializer::JsonEncoding::DEFAULT_ENC ) << std::string( "]," );

    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_get_border", e );
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

inline void CCmdHandler::get_changed_wsels ( std::stringstream& res )
{
    static const std::vector<std::string> ids;

    // get all worksheet elements marked as dirty
    {
        static const std::vector<std::string> return_keys_of_dirty_elements = boost::assign::list_of<std::string>( "e_id" )( "e_type" )( "n_refers_to" )( "n_get_val" )( "id" )( "formel_type" )( "n_source_dims" );
        static const std::vector<std::pair<std::string, variant> > match_all_dirty = boost::assign::list_of<std::pair<std::string, variant> >( std::make_pair( "n_is_dirty", variant( true ) ) ) ;

        get_worksheet_elements_command get_dirty_wsels_cmd( *m_session_context, "", ids, return_keys_of_dirty_elements, match_all_dirty );
        res << ",[\"wdrt\"," << m_json_serializer( execute_fetch( get_dirty_wsels_cmd ), JSONSerializer::JsonEncoding::RAW_IF_CURL_OR_ANGL ) << ']';
    }

    // get all worksheet elements marked as moved
    {
        static const std::vector<std::string> return_keys_of_moved_elements = boost::assign::list_of<std::string>( "e_id" )( "e_type" )( "n_location" )( "pos_offsets" )( "formel_type" );
        static const std::vector<std::pair<std::string, variant> > match_all_moved = boost::assign::list_of<std::pair<std::string, variant> >( std::make_pair( "n_has_moved", variant( true ) ) ) ;

        get_worksheet_elements_command get_moved_wsels_cmd( *m_session_context, "", ids, return_keys_of_moved_elements, match_all_moved );
        res << ",[\"wmvd\"," << m_json_serializer( execute_fetch( get_moved_wsels_cmd ), JSONSerializer::JsonEncoding::RAW_IF_CURL_OR_ANGL ) << ']';

    }

    // get all worksheet elements marked as target dirty
    {
        static const std::vector<std::string> return_keys_of_target_dirty_elements = boost::assign::list_of<std::string>( "e_id" )( "e_type" )( "n_target_ref" )( "n_target_val" )( "id" )( "formel_type" );
        static const std::vector<std::pair<std::string, variant> > match_all_target_dirty = boost::assign::list_of<std::pair<std::string, variant> >( std::make_pair( "n_target_dirty", variant( true ) ) ) ;

        get_worksheet_elements_command get_target_dirty_wsels_cmd( *m_session_context, "", ids, return_keys_of_target_dirty_elements, match_all_target_dirty );

        res << ",[\"wtrd\"," << m_json_serializer( execute_fetch( get_target_dirty_wsels_cmd ), JSONSerializer::JsonEncoding::RAW_IF_CURL_OR_ANGL ) << ']';
    }
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_get_changed_wsels ( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_get_changed_wsels", ERR_INVALID_SESSION, "invalid session received" );
    }

    try {
        std::stringstream res;

        get_changed_wsels( res );

        m_result << "[true" << res.str() << "],";
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_get_changed_wsels", e );
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_snapshot_create ( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_snapshot_create", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( !test_types<int, int, int, int>( 5, 'l', 1, cmd ) ) {
        return fail_cmd( "cmd_snapshot_create", ERR_PARSING_FAILED, "command malformed" );
    }

    try {
        sheet_range coords( sheet_point( 0, 0 ) );

        if ( !bind_rect( 1, cmd, coords ) ) {
            return fail_cmd( "cmd_snapshot_create", ERR_PARSING_FAILED, "check_range_coord: invalid coordinates" );
        }

        const unsigned long property_set = cmd.size() > 5 && cmd[5]->type() == typeid( int ) ? boost::any_cast<int>( *cmd[5] ) : get_server_query_command::query_all;
        const unsigned short dimension_set = cmd.size() > 6 && cmd[6]->type() == typeid( int ) ? boost::any_cast<int>( *cmd[6] ) : SnapshotManager::DimensionTypes::BOTH;
        const unsigned short ttl = cmd.size() > 7 && cmd[7]->type() == typeid( int ) ? boost::any_cast<int>( *cmd[7] ) : 1;
        std::string snapshot_uid = cmd.size() > 8 && cmd[8]->type() == typeid( std::string ) ? boost::any_cast<std::string>( *cmd[8] ) : "";

        static SnapshotManager& snapshot_manager = SnapshotManager::instance();

        SnapshotManager::snapshot_auto_type snapshot = snapshot_manager.make_snapshot( *m_session_context, coords, property_set, dimension_set );
        snapshot_uid = snapshot_manager.save_snapshot( m_session_id, snapshot, ttl, snapshot_uid );

        m_result << std::string( "[true,\"" ) << snapshot_uid << std::string( "\"]," );
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_snapshot_create", e );
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_snapshot_get ( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_snapshot_get", ERR_INVALID_SESSION, "invalid session received" );
    }

    std::string snapshot_uid = cmd.size() > 1 && cmd[1]->type() == typeid( std::string ) ? boost::any_cast<std::string>( *cmd[1] ) : "";

    try {
        static SnapshotManager& snapshot_manager = SnapshotManager::instance();

        SnapshotManager::snapshot_auto_type snapshot = snapshot_manager.get_snapshot( m_session_id, snapshot_uid );

        std::stringstream snapshot_dump;

        if ( snapshot.get() != NULL ) {
            const unsigned x1 = snapshot->coords.upper_left().column() + 1, y1 = snapshot->coords.upper_left().row() + 1,
                           x2 = snapshot->coords.lower_right().column() + 1, y2 = snapshot->coords.lower_right().row() + 1,
                           ur_x = snapshot->used_range.column() + 1, ur_y = snapshot->used_range.row() + 1;

            snapshot_dump << ",{\"uid\":" << m_json_serializer( snapshot->uid ) << ",\"coords\":[" << x1 << "," << y1 << "," << x2 << "," << y2 << "],\"property_set\":" << snapshot->property_set;
            snapshot_dump << ",\"values\":" << m_json_serializer( snapshot->values ) << ",\"dimension_set\":" << snapshot->dimension_set << ",\"col_widths\":" << m_json_serializer( snapshot->col_widths );
            snapshot_dump << ",\"row_heights\":" << m_json_serializer( snapshot->row_heights ) << ",\"used_range\":[" << ur_x << "," << ur_y << "]}";
        } else if ( snapshot_uid != "" ) {
            return fail_cmd( "cmd_snapshot_get", ERR_RUNTIME_ERROR, "specified snapshot non-existent" );
        }

        m_result << std::string( "[true" ) << snapshot_dump.str() << std::string( "]," );
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_snapshot_get", e );
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_snapshot_diff ( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_snapshot_diff", ERR_INVALID_SESSION, "invalid session received" );
    }

    bool check_wsels = cmd.size() > 1 && cmd[1]->type() == typeid( bool ) ? boost::any_cast<bool>( *cmd[1] ) : true;
    std::string snapshot_old_uid = cmd.size() > 2 && cmd[2]->type() == typeid( std::string ) ? boost::any_cast<std::string>( *cmd[2] ) : "";

    try {
        static SnapshotManager& snapshot_manager = SnapshotManager::instance();

        std::stringstream diff;

        if ( cmd.size() > 3 && cmd[3]->type() == typeid( std::string ) ) {
            diff << snapshot_manager.diff_snapshots( *m_session_context, m_session_id, snapshot_old_uid, boost::any_cast<std::string>( *cmd[3] ) );
        } else {
            diff << snapshot_manager.diff_snapshots( *m_session_context, m_session_id, snapshot_old_uid );
        }

        if ( check_wsels ) {
            get_changed_wsels( diff );
        }

        m_result << "[true" << diff.str() << "],";
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_snapshot_diff", e );
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_wssobjects_list( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_wssobjects_list", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( ! test_types<int>( 3, 'g', 1, cmd ) ) {
        return fail_cmd( "cmd_wssobjects_list", ERR_PARSING_FAILED, "command malformed" );
    }

    std::vector<std::pair<std::string ,  std::string > > vec_pairs;

    try {
        const unsigned long query_type  = boost::any_cast<int>( *cmd[1] );

        switch ( query_type ) {

            case 0: { // applications list
                static server& srv = server::instance();
                foreach( const shared_application_type & application, srv.locking_iterator() ) {
                    vec_pairs.push_back( std::make_pair( boost::lexical_cast<std::string>( application->uuid() ), application->name().c_str() ) );
                }
                m_result << std::string( "[true," ) << m_json_serializer( vec_pairs ) << std::string( "]," );
            }
            break;
            case 1: { // workbooks list
                shared_application_type application_object = m_session_context->selected().application();

                if ( application_object ) {
                    foreach( const shared_workbook_type & wb, application_object->locking_iterator() ) {

                        vec_pairs.push_back( std::make_pair( boost::lexical_cast<std::string>( wb->uuid() ), wb->name().c_str() ) );
                    }
                    m_result << std::string( "[true," ) << m_json_serializer( vec_pairs ) << std::string( "]," );
                } else {
                    return fail_cmd( "cmd_wssobjects_list", 100, "handle_wssobjects_list: could not get the workbooks list: no application is currently selected" );
                }
            }
            break;
            case 2: {
                if ( cmd.size() == 2 )  { // worksheets list
                    shared_workbook_type wb =  m_session_context->selected().workbook().lock();

                    if ( wb ) {
                        foreach( const shared_worksheet_type & ws, wb->locking_iterator() ) {
                            vec_pairs.push_back( std::make_pair( boost::lexical_cast<std::string>( ws->uuid() ), ws->name().c_str() ) );
                        }
                        m_result << std::string( "[true," ) << m_json_serializer( vec_pairs ) << std::string( "]," );
                    } else {
                        return fail_cmd( "cmd_wssobjects_list", 100, "handle_wssobjects_list: could not get the worksheets list: no workbook is currently selected" );
                    }
                } else {
                    const shared_application_type& application_object = m_session_context->selected().application();
                    if ( application_object ) {
                        if ( cmd[2]->type() != typeid( std::string ) ) {
                            return fail_cmd( "cmd_wssobjects_list", ERR_PARSING_FAILED, "command malformed" );
                        }

                        const std::string new_wb_id = boost::any_cast<std::string>( *cmd[2] );
                        const uuid_type   new_wb_uuid = boost::lexical_cast<  uuid_type > ( new_wb_id );
                        shared_workbook_type workbook_object =  application_object->get( *m_session_context, new_wb_uuid ) ;
                        if ( workbook_object ) {
                            foreach( const shared_worksheet_type & ws, workbook_object->locking_iterator() ) {
                                vec_pairs.push_back( std::make_pair( boost::lexical_cast<std::string>( ws->uuid() ),  ws->name().c_str() ) );
                            }
                            m_result << std::string( "[true," ) << m_json_serializer( vec_pairs ) << std::string( "]," );
                        } else {
                            return fail_cmd( "cmd_wssobjects_list", 100, "handle_wssobjects_list: could not get the worksheets list: no workbook is currently selected" );
                        }

                    } else {
                        return fail_cmd( "cmd_wssobjects_list", 100, "handle_wssobjects_list: could not get the workbooks list: no application is currently selected" );
                    }

                }
            }
            break;

            case 3: // list cloned worksheets
            default:
                m_result << std::string( "[true," ) << m_json_serializer( m_session_context->session_sheets().list_sheets_with_their_session_sheet() ) << std::string( "]," );
                break;
        }
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_wssobjects_list", e );
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_wssobjects_select( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_wssobjects_select", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( ! test_types<int, std::string>( 3, 'd', 1, cmd ) ) {
        return fail_cmd( "cmd_wssobjects_select", ERR_PARSING_FAILED, "command malformed" );
    }

    try {
        unsigned long query_type  = boost::any_cast<int>( *cmd[1] );
        std::string str_uuid = boost::any_cast<std::string>( *cmd[2] );
        uuid_type object_uuid =  boost::lexical_cast<uuid_type>( str_uuid );

        switch ( query_type ) {
            case 0: {
                select_application_command command( *m_session_context, object_uuid );
                command.execute();
            }
            break;
            case 1: {
                select_workbook_command command( *m_session_context, object_uuid );
                command.execute();
            }
            break;
            case 2:
            default: {
                select_worksheet_command command( *m_session_context, object_uuid );
                command.execute();
            }
            break;
        }
        m_result << std::string( "[true,\"\"]," );
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_wssobjects_select", e );
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_wssobjects_rename( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_wssobjects_rename", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( ! test_types<int, std::string>( 3, 'd', 1, cmd ) ) {
        return fail_cmd( "cmd_wssobjects_rename", ERR_PARSING_FAILED, "command malformed" );
    }

    try {
        unsigned long query_type  = boost::any_cast<int>( *cmd[1] );
        std::string object_new_name = boost::any_cast<std::string>( *cmd[2] );

        switch ( query_type ) {
            case 0: {
                rename_application_command command( *m_session_context, object_new_name );
                m_session_context->undo_redo_log().execute( command );
            }
            break;
            case 1: {
                rename_workbook_command command( *m_session_context, object_new_name );
                m_session_context->undo_redo_log().execute( command );
            }
            break;
            case 2:
            default: {
                rename_worksheet_command command( *m_session_context, object_new_name );
                m_session_context->undo_redo_log().execute( command );
            }
            break;
        }
        m_result << std::string( "[true,\"\"]," );
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_wssobjects_rename", e );
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_wssobjects_add( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_wssobjects_add", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( ! test_types<int, std::string>( 4, 'g', 1, cmd ) ) {
        return fail_cmd( "cmd_wssobjects_add", ERR_PARSING_FAILED, "command malformed" );
    }

    try {
        unsigned long query_type  = boost::any_cast<int>( *cmd[1] );
        std::string object_name = boost::any_cast<std::string>( *cmd[2] );

        switch ( query_type ) {
            case 0: {
                create_application_command command( *m_session_context, object_name );
                m_result << std::string( "[true," ) << m_json_serializer( execute_fetch( command ) ) << std::string( "]," );
            }
            break;
            case 1: {
                create_workbook_command command( *m_session_context, object_name );
                m_result << std::string( "[true," ) << m_json_serializer( execute_fetch( command ) ) << std::string( "]," );
            }
            break;
            case 2:
            default: {

                std::string next_ws_id_str = "";

                if ( cmd.size() == 4 ) {
                    if ( cmd[3]->type()  !=  typeid( std::string ) ) {
                        return fail_cmd( "cmd_wssobjects_add", ERR_PARSING_FAILED, "command malformed" );
                    }

                    next_ws_id_str = boost::any_cast<std::string>( *cmd[3] );
                }

                create_worksheet_command command( *m_session_context, object_name, next_ws_id_str.empty() ? boost::uuids::nil_uuid() : boost::lexical_cast<uuid_type>( next_ws_id_str ) );
                m_result << std::string( "[true," ) << m_json_serializer( execute_fetch( command ) ) << std::string( "]," );
            }
            break;
        }
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_wssobjects_add", e );
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_wssobjects_delete( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_wssobjects_delete", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( ! test_types<int, std::string>( 3, 'd', 1, cmd ) ) {
        return fail_cmd( "cmd_wssobjects_delete", ERR_PARSING_FAILED, "command malformed" );
    }

    try {
        unsigned long query_type  = boost::any_cast<int>( *cmd[1] );
        const uuid_type id = boost::lexical_cast<uuid_type>(  boost::any_cast<std::string>( *cmd[2] ) );

        switch ( query_type ) {
            case 0: {
                remove_application_command( *m_session_context, id ).execute();
            }
            break;
            case 1: {
                remove_workbook_command( *m_session_context, id ).execute();
            }
            break;
            case 2:
            default: {
                remove_worksheet_command( *m_session_context, id ).execute();
            }
            break;
        }
        m_result << std::string( "[true,\"\"]," );
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_wssobjects_delete", e );
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_get_used_range( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_get_used_range", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( cmd.size() != 1 ) {
        return fail_cmd( "cmd_get_used_range", ERR_PARSING_FAILED, "command malformed" );
    }

    try {
        shared_worksheet_type ws = m_session_context->selected().worksheet().lock();
        if ( !ws ) {
            throw invalid_worksheet_exception();
        }
        const optional_sheet_range_type optional_result = ws->used_range( used_range::all_extended );
        m_result << std::string( "[true," ) << m_json_serializer( optional_result ? optional_result->lower_right() : sheet_point( 0, 0 ) , JSONSerializer::JsonEncoding::POINT_TRANSFORM_COORD ) << std::string( "]," );

    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_get_used_range", e );
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_get_rng_as_vals( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_get_rng_as_vals", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( ! test_types<int, int, int, int, int>( 6, 'd', 1, cmd ) ) {
        return fail_cmd( "cmd_get_rng_as_vals", ERR_PARSING_FAILED, "command malformed" );
    }

    unsigned long query_type  = boost::any_cast<int>( *cmd[1] );
    sheet_range get_range( sheet_point( 0, 0 ) ) ;

    if ( ! bind_rect( 2, cmd, get_range ) ) {
        return fail_cmd( "cmd_get_rng_as_vals", ERR_PARSING_FAILED, "check_range_coord: invalid coordinates" );
    }

    try {
        get_server_query_command command( *m_session_context, get_range, query_type );
        m_result << std::string( "[true," ) << m_json_serializer( execute_fetch( command ) ) << std::string( "]," );

    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_get_rng_as_vals", e );
    }
    return true;
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_get_rng_as_rgns ( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_get_rng_as_rgns", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( ! test_types<int, int, int, int, int>( 6, 'l', 1, cmd ) ) {
        return fail_cmd( "cmd_get_rng_as_rgns", ERR_PARSING_FAILED, "command malformed" );
    }

    unsigned long query_type = boost::any_cast<int>( *cmd[1] );
    sheet_range range( sheet_point( 0, 0 ) );

    if ( !bind_rect( 2, cmd, range ) ) {
        return fail_cmd( "cmd_get_rng_as_rgns", ERR_PARSING_FAILED, "check_range_coord: invalid coordinates" );
    }

    bool include_empty = cmd.size() > 6 ? boost::any_cast<bool>( *cmd[6] ) : false;

    try {
        shared_worksheet_type sheet = m_session_context->selected().worksheet().lock();

        if ( ! sheet ) {
            return fail_cmd( "cmd_get_rng_as_rgns", ERR_RUNTIME_ERROR, "no worksheet is currently selected" );
        }

        std::stringstream regions, region, cell;

        unsigned x1 = range.upper_left().column() + 1, x2 = range.lower_right().column() + 1, y = range.upper_left().row() + 1,
                 x = x1, x_old = sheet_dimension::max_column  + 2, y_old = sheet_dimension::max_row + 2,
                 region_x = 0, region_y = 0, region_w = 0;

        get_server_query_command command( *m_session_context, range, query_type );
        const variant& vals = execute_fetch( command );

        //TODO use the underlying map here
        for ( variant::variant_array_type::const_iterator it = vals.array().begin(), it_end = vals.array().end(); it != it_end; ) {
            cell.str( "" );

            if ( query_type & get_server_query_command::query_value ) {
                if ( ( *it ).type() != variant::type_empty ) {
                    cell << "{\"v\":" << m_json_serializer( *it ) << ",\"t\":";

                    switch ( ( *it ).type() ) {
                        case variant::type_double:
                            cell << "\"n\"";
                            break;

                        case variant::type_bool:
                            cell << "\"b\"";
                            break;

                        case variant::type_string:
                            cell << ( ( *it ).string().size() && ( *it ).string().at( 0 ) == '<' ? "\"h\"" : "\"s\"" );
                            break;

                        default:
                            cell << "\"s\"";
                            break;
                    }
                } else if ( include_empty ) {
                    cell << "{\"v\":\"\",\"t\":\"e\"";
                }

                ++it;
            }

            if ( query_type & get_server_query_command::query_formula ) {
                ++it;
            }

            if ( query_type & get_server_query_command::query_style ) {
                if ( ( *it ).type() != variant::type_empty && ( *it ).string().size() ) {
                    cell << ",\"s\":" << m_json_serializer( ( *it ).string() );
                }

                ++it;
            }

            if ( query_type & get_server_query_command::query_formula_where_exists ) {
                if ( ( *it ).type() != variant::type_empty ) {
                    cell << ",\"f\":" << m_json_serializer( ( *it ).string() );
                }

                ++it;
            }

            if ( query_type & get_server_query_command::query_attribute ) {
                if ( ( *it ).type() != variant::type_empty && ( *it ).string().size() ) {
                    cell << ",\"a\":" << ( *it ).string();
                }

                ++it;
            }

            if ( query_type & get_server_query_command::query_dimensions ) {
                ++it;
            }

            if ( query_type & get_server_query_command::query_formatted_value ) {
                if ( ( *it ).type() != variant::type_empty && ( *it ).string().size() ) {
                    cell << ",\"l\":" << m_json_serializer( ( *it ).string() );
                }
                ++it;
            }

            if ( query_type & get_server_query_command::query_format ) {
                if ( ( *it ).type() != variant::type_empty && ( *it ).string().size() ) {
                    cell << ",\"o\":" << m_json_serializer( ( *it ).string() );
                }

                ++it;
            }

            if ( query_type & get_server_query_command::query_merge ) {
                if ( ( *it ).type() != variant::type_empty ) {
                    cell << ",\"m\":" << m_json_serializer( ( *it ).array() );
                }

                ++it;
            }

            if ( query_type & get_server_query_command::query_formula_with_named_ranges ) {
                if ( ( *it ).type() != variant::type_empty ) {
                    cell << ",\"n\":" << m_json_serializer( ( *it ).array() );
                }

                ++it;
            }

            if ( query_type & get_server_query_command::query_lock ) {
                if ( ( *it ).type() != variant::type_empty && !( *it ).numeric() ) {
                    cell << ",\"k\":false";
                }

                ++it;
            }

            if ( cell.str().size() ) {
                cell << '}';

                cell.seekp( 0, std::ios_base::beg ) << '{';

                if ( y == y_old && x == x_old + 1 && ( region_w == 0 || region_w > x - region_x ) ) {
                    region << "," << cell.rdbuf();
                } else if ( y == y_old + 1 && x == region_x && ( region_w == 0 || x_old == region_x + region_w - 1 ) ) {
                    if ( region_w == 0 ) {
                        region_w = x_old - x + 1;
                    }

                    region << "," << cell.rdbuf();
                } else {
                    if ( region.str().size() ) {
                        regions << ",[" << region_x << "," << region_y << "," << region_w << "," << region.rdbuf() << ']';
                        region.str( "" );
                    }

                    region_x = x;
                    region_y = y;
                    region_w = 0;
                    region << cell.rdbuf();
                }

                x_old = x;

                if ( y != y_old ) {
                    y_old = y;
                }
            }

            if ( ++x > x2 ) {
                x = x1;
                ++y;
            }
        }

        if ( region.str().size() ) {
            regions << ",[" << region_x << "," << region_y << "," << region_w << "," << region.rdbuf() << ']';
        }

        m_result << std::string( "[true" ) << regions.str() << std::string( "]," );
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_get_rng_as_rgns", e );
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
bool CCmdHandler::cmd_get_def_style( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_get_def_style", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( cmd.size() != 1 ) {
        return fail_cmd( "cmd_get_def_style", ERR_PARSING_FAILED, "command malformed" );
    }

    try {
        get_default_style_command command( *m_session_context );
        m_result << std::string( "[true," ) << execute_fetch( command ) << std::string( "]," );
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_get_def_style", e );
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_set_def_style( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_set_def_style", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( ! test_types<std::string>( 2, 'd', 1, cmd ) ) {
        return fail_cmd( "cmd_set_def_style", ERR_PARSING_FAILED, "command malformed" );
    }

    std::string style_string = boost::any_cast<std::string>( *cmd[1] );

    try {
        set_default_style_command command( *m_session_context, style_string );
        m_session_context->undo_redo_log().execute( command );
        m_result << std::string( "[true,\"\"]," );
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_set_def_style", e );
    }
    return true;

}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_get_def_colrow_dims( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_get_def_colrow_dims", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( ! test_types<int>( 2, 'd', 1, cmd ) ) {
        return fail_cmd( "cmd_get_def_colrow_dims", ERR_PARSING_FAILED, "command malformed" );
    }

    unsigned long query_type  = boost::any_cast<int>( *cmd[1] );

    try {
        get_default_sheet_dimensions_command command( *m_session_context );
        get_default_sheet_dimensions_command::result_type sheet_dims = execute_fetch( command );

        switch ( query_type ) {
            case 0: // column width
                m_result << std::string( "[true," ) << m_json_serializer( sheet_dims.get<1>() ) << std::string( "]," );
                break;

            case 1: // row height
                m_result << std::string( "[true," ) << m_json_serializer( sheet_dims.get<0>() ) << std::string( "]," );
                break;

            case 2:// both
            default: {
                get_default_sheet_dimensions_command::result_type result_sheet_dims( sheet_dims.get<1>(), sheet_dims.get<0>() );
                m_result << std::string( "[true," ) << m_json_serializer( result_sheet_dims ) << std::string( "]," );

            }
            break;

        }

    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_get_def_colrow_dims", e );
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_set_def_colrow_dims( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_set_def_colrow_dims", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( ! test_types<int, int>( 3, 'd' , 1, cmd ) ) {
        return fail_cmd( "cmd_set_def_colrow_dims", ERR_PARSING_FAILED, "command malformed" );
    }

    int set_row_height  = boost::any_cast<int>( *cmd[1] );
    unsigned long colrow_dim  = boost::any_cast<int>( *cmd[2] );

    try {
        if ( set_row_height == 1 ) {
            set_default_row_height_command command( *m_session_context, colrow_dim );
            m_session_context->undo_redo_log().execute( command );
        } else {
            set_default_column_width_command command( *m_session_context, colrow_dim );
            m_session_context->undo_redo_log().execute( command );
        }
        m_result << std::string( "[true,\"\"]," );
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_set_def_colrow_dims", e );
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_get_colrow_dims( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_get_colrow_dims", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( ! test_types<int, int, int>( 4, 'd', 1, cmd ) ) {
        return fail_cmd( "cmd_get_colrow_dims", ERR_PARSING_FAILED, "command malformed" );
    }

    int get_row_height  = boost::any_cast<int>( *cmd[1] );
    unsigned long line_from  = boost::any_cast<int>( *cmd[2] );
    unsigned long line_to  = boost::any_cast<int>( *cmd[3] );

    try {

        if ( get_row_height == 1 ) {
            get_sparse_row_height_command command( *m_session_context, sheet_layout_trait::line_type( line_from - 1, line_to  - 1 ) );
            m_result << std::string( "[true," ) << m_json_serializer( execute_fetch( command ) ) << std::string( "]," );
        } else {
            get_sparse_column_width_command command( *m_session_context, sheet_layout_trait::line_type( line_from - 1, line_to - 1 ) );
            m_result << std::string( "[true," ) << m_json_serializer( execute_fetch( command ) ) << std::string( "]," );
        }
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_get_colrow_dims", e );
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_set_colrow_dims ( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_set_colrow_dims", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( !test_types<int>( 3, 'l', 1, cmd ) ) {
        return fail_cmd( "cmd_set_colrow_dims", ERR_PARSING_FAILED, "command malformed" );
    }

    try {
        boost::scoped_ptr<SetColRowDims_BaseFunctor> set_dims;

        if ( boost::any_cast<int>( *cmd[1] ) == 0 ) {
            set_dims.reset( new SetColRowDims_Functor<set_column_width_command>() );
        } else {
            set_dims.reset( new SetColRowDims_Functor<set_row_height_command>() );
        }

        for ( json_array_t::size_type cmd_size = cmd.size(), i_sets = 2; i_sets < cmd_size; ++i_sets ) {
            if ( cmd[i_sets]->type() != typeid( json_array_t ) ) {
                return fail_cmd( "cmd_set_colrow_dims", ERR_PARSING_FAILED, "command malformed" );
            }

            const json_array_t& chngset = boost::any_cast<json_array_t>( *cmd[i_sets] );

            if ( !test_types<int, int>( 3, 'l', 0, chngset ) ) {
                return fail_cmd( "cmd_set_colrow_dims", ERR_PARSING_FAILED, "command malformed" );
            }

            unsigned long idx_beg = boost::any_cast<int>( *chngset[0] ),
                          idx_end = boost::any_cast<int>( *chngset[1] );

            const json_array_t::size_type chngset_size = chngset.size();

            if ( chngset_size == 3 ) {
                if ( chngset[2]->type() != typeid( int ) ) {
                    return fail_cmd( "cmd_set_colrow_dims", ERR_PARSING_FAILED, "command malformed" );
                }

                ( *set_dims )( *m_session_context, sheet_layout_trait::line_type( idx_beg - 1, idx_end ), boost::any_cast<int>( *chngset[2] ) );
                continue;
            }

            for ( unsigned long i_dims = 2; idx_beg <= idx_end; ++idx_beg ) {
                if ( chngset[i_dims]->type() != typeid( int ) ) {
                    return fail_cmd( "cmd_set_colrow_dims", ERR_PARSING_FAILED, "command malformed" );
                }

                ( *set_dims )( *m_session_context, sheet_layout_trait::line_type( idx_beg - 1, idx_beg ), boost::any_cast<int>( *chngset[i_dims] ) );

                if ( ++i_dims >= chngset_size ) {
                    i_dims = 2;
                }
            }
        }

        m_result << std::string( "[true,\"\"]," );
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_set_colrow_dims", e );
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_autofit ( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_autofit", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( !test_types<int>( 3, 'l', 1, cmd ) ) {
        return fail_cmd( "cmd_autofit", ERR_PARSING_FAILED, "command malformed" );
    }

    try {
        unsigned short type = boost::any_cast<int>( *cmd[1] ),
                       incr = 5 + type + type;

        boost::scoped_ptr<GetMaxColRowDims_BaseFunctor> get_max_dims;
        boost::scoped_ptr<SetColRowDims_BaseFunctor> set_dims;

        if ( type == 0 ) {
            get_max_dims.reset( new GetMaxColRowDims_Functor<get_sparse_max_cell_width_command>() );
            set_dims.reset( new SetColRowDims_Functor< set_column_width_command >() );
        } else {
            get_max_dims.reset( new GetMaxColRowDims_Functor<get_sparse_max_cell_height_command>() );
            set_dims.reset( new SetColRowDims_Functor<set_row_height_command>() );
        }

        for ( json_array_t::size_type cmd_size = cmd.size(), i_spans = 2; i_spans < cmd_size; ++i_spans ) {
            if ( cmd[i_spans]->type() != typeid( json_array_t ) ) {
                return fail_cmd( "cmd_autofit", ERR_PARSING_FAILED, "command malformed" );
            }

            const json_array_t& span = boost::any_cast<json_array_t>( *cmd[i_spans] );

            if ( ! test_types<int, int>( 2, 'd', 0, span ) ) {
                return fail_cmd( "cmd_autofit", ERR_PARSING_FAILED, "command malformed" );
            }

            const unsigned long idx_beg = boost::any_cast<int>( *span[0] ),
                                idx_end = boost::any_cast<int>( *span[1] );

            const sheet_layout_trait::sparse_value_range_type& dims = ( *get_max_dims )( *m_session_context, sheet_layout_trait::line_type( idx_beg - 1, idx_end - 1 ) );

            for ( sheet_layout_trait::sparse_value_range_type::const_iterator it = dims.begin(), it_end = dims.end(); it != it_end; ++it ) {
                const unsigned long idx = *it;
                ++it;
                const unsigned long dim = *it;
                ++it;

                ( *set_dims )( *m_session_context, sheet_layout_trait::line_type( idx, idx + 1 ), dim + incr );
            }
        }

        m_result << std::string( "[true,\"\"]," );
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_autofit", e );
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_adapt ( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_adapt", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( ! test_types<int>( 3, 'l', 1, cmd ) ) {
        return fail_cmd( "cmd_adapt", ERR_PARSING_FAILED, "command malformed" );
    }

    try {
        int handle_colwidth = boost::any_cast<int>( *cmd[1] );

        for ( json_array_t::size_type i_coords = 2; i_coords < cmd.size(); i_coords++ ) {
            if ( cmd[i_coords]->type() != typeid( json_array_t ) ) {
                return fail_cmd( "cmd_adapt", ERR_PARSING_FAILED, "command malformed" );
            }

            const json_array_t& coords = boost::any_cast<json_array_t>( *cmd[i_coords] );

            if ( ! test_types<int, int>( 2, 'd', 0, coords ) ) {
                return fail_cmd( "cmd_adapt", ERR_PARSING_FAILED, "command malformed" );
            }

            unsigned long line_from = boost::any_cast<int>( *coords[0] );
            unsigned long line_to = boost::any_cast<int>( *coords[1] );

            if ( handle_colwidth == 0 ) {
                get_sparse_max_cell_width_command get_command( *m_session_context, sheet_layout_trait::line_type( line_from - 1, ( line_to - 1 ) ) );
                const get_sparse_max_cell_width_command::result_type& vector_max = execute_fetch( get_command );

                if ( ! vector_max.empty() ) {
                    get_sparse_max_cell_width_command::result_type::const_iterator it_beg = vector_max.begin();
                    get_sparse_max_cell_width_command::result_type::const_iterator it_end = vector_max.end();

                    while ( it_beg != it_end ) {
                        unsigned long from = *it_beg;
                        ++it_beg;
                        unsigned long char_length = ( *it_beg );
                        ++it_beg;
                        ++it_beg;
                        unsigned long current_width;
                        get_sparse_column_width_command command( *m_session_context, sheet_layout_trait::line_type( from , from ) );
                        const std::vector<unsigned long> vector_sparse = execute_fetch( command );

                        vector_sparse.empty() ? current_width = 64 : current_width = vector_sparse.at( 1 );

                        if ( char_length > current_width ) {
                            set_column_width_command set_command( *m_session_context, sheet_layout_trait::line_type( from , from + 1 ), char_length + 5 );
                            m_session_context->undo_redo_log().execute( set_command );
                        }
                    }
                }
            } else {
                get_sparse_max_cell_height_command get_command( *m_session_context, sheet_layout_trait::line_type( line_from - 1, ( line_to - 1 ) ) );
                const get_sparse_max_cell_height_command::result_type& vector_max = execute_fetch( get_command );

                if ( ! vector_max.empty() ) {
                    get_sparse_max_cell_height_command::result_type::const_iterator it_beg = vector_max.begin();
                    get_sparse_max_cell_height_command::result_type::const_iterator it_end = vector_max.end();

                    while ( it_beg != it_end ) {
                        unsigned long from = *it_beg;
                        ++it_beg;
                        unsigned long char_height = ( *it_beg );
                        ++it_beg;
                        ++it_beg;
                        unsigned long current_height;

                        get_sparse_row_height_command command( *m_session_context, sheet_layout_trait::line_type( from, from ) );
                        const std::vector<unsigned long> vector_sparse = execute_fetch( command );

                        vector_sparse.empty() ? current_height = 20 : current_height = vector_sparse.at( 1 );

                        if ( char_height > current_height ) {
                            set_row_height_command set_command( *m_session_context, sheet_layout_trait::line_type( from, from + 1 ), char_height + 7 );
                            m_session_context->undo_redo_log().execute( set_command );
                        }
                    }
                }
            }
        }

        m_result << std::string( "[true,\"\"]," );
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_adapt", e );
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_get_max_cell_dims( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_get_max_cell_dims", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( ! test_types<int, int, int>( 4, 'd', 1, cmd ) ) {
        return fail_cmd( "cmd_get_max_cell_dims", ERR_PARSING_FAILED, "command malformed" );
    }

    int get_row_height  = boost::any_cast<int>( *cmd[1] );
    unsigned long line_from  = boost::any_cast<int>( *cmd[2] );
    unsigned long line_to  = boost::any_cast<int>( *cmd[3] );

    try {
        if ( get_row_height == 1 ) {
            get_sparse_max_cell_height_command command( *m_session_context, sheet_layout_trait::line_type( line_from - 1, line_to - 1 ) );
            m_result << std::string( "[true," ) << m_json_serializer( execute_fetch( command ) ) << std::string( "]," );
        } else {
            get_sparse_max_cell_width_command command( *m_session_context, sheet_layout_trait::line_type( line_from - 1, line_to - 1 ) );
            m_result << std::string( "[true," ) << m_json_serializer( execute_fetch( command ) ) << std::string( "]," );
        }

    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_get_max_cell_dims", e );
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_set_auto_calc ( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_set_auto_calc", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( ! test_types<int>( 2, 'd', 1, cmd ) ) {
        return fail_cmd( "cmd_set_auto_calc", ERR_PARSING_FAILED, "command malformed" );
    }

    try {
        int auto_calc = boost::any_cast<int>( *cmd[1] );

        const shared_application_type& app =  m_session_context->selected().application();
        if ( app ) {
            app->calculation_settings().auto_calculation( auto_calc == 1 ? true : false );
            m_result << std::string( "[true,\"\"]," );
        }
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_set_auto_calc", e );
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_get_formatted_sample( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_get_formatted_sample", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( ! test_types<std::string>( 3, 'd', 1, cmd ) ) {
        return fail_cmd( "cmd_get_formatted_sample", ERR_PARSING_FAILED, "command malformed" );
    }

    try {
        const std::string format_string  = boost::any_cast<std::string>( *cmd[1] );

        variant input_value = json2Value( cmd[2] );

        get_formatted_value_command command( *m_session_context, format_string, input_value );
        m_result << std::string( "[true," ) << m_json_serializer( execute_command <get_formatted_value_command>()( command ) ) << std::string( "]," );


    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_get_formatted_sample", e );
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_load_workbook( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_load_workbook", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( ! test_types<std::string, std::string >( 5, 'g', 1, cmd ) ) {
        return fail_cmd( "cmd_load_workbook", ERR_PARSING_FAILED, "command malformed" );
    }

    try {
        std::string file_path  = boost::any_cast<std::string>( *cmd[1] );
        std::string meta_data  = boost::any_cast<std::string>( *cmd[2] );
        bool overwrite_existing = true;
        bool is_temp = false ;
        if ( cmd.size() > 3 ) {

            if ( cmd[3]->type() != typeid( bool ) ) {
                return fail_cmd( "cmd_load_workbook", ERR_PARSING_FAILED, "command malformed" );
            }

            overwrite_existing = boost::any_cast<bool>( *cmd[3] );
        }
        if ( cmd.size() > 4 ) {
            if ( cmd[4]->type() != typeid( bool ) ) {
                return fail_cmd( "cmd_load_workbook", ERR_PARSING_FAILED, "command malformed" );
            }

            is_temp = boost::any_cast<bool>( *cmd[4] );
        }

        load_workbook_command command( *m_session_context, file_path, meta_data, overwrite_existing, is_temp );
        m_result << std::string( "[true," ) << m_json_serializer( execute_fetch( command ) ) << std::string( "]," );
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_load_workbook", e );
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_save_workbook( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_save_workbook", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( ! test_types<std::string, std::string >( 3, 'l', 1, cmd ) ) {
        return fail_cmd( "cmd_save_workbook", ERR_PARSING_FAILED, "command malformed" );
    }

    try {
        const uuid_type workbook_uuid = boost::lexical_cast<uuid_type>( boost::any_cast<std::string>( *cmd[1] ) );
        const std::string file_path = boost::any_cast<std::string>( *cmd[2] );
        bool overwrite_existing = true;
        bool as_snapshot = false;

        if ( cmd.size() > 3 ) {
            if ( cmd[3]->type() == typeid( bool ) ) {
                overwrite_existing = boost::any_cast<bool>( *cmd[3] );
            }

            if ( cmd.size() > 4 && cmd[4]->type() == typeid( bool ) ) {
                as_snapshot = boost::any_cast<bool>( *cmd[4] );
            }
        }

        save_workbook_command( *m_session_context, workbook_uuid, file_path, overwrite_existing, as_snapshot ).execute();

        m_result << std::string( "[true,\"\"]," );
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_save_workbook", e );
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


bool CCmdHandler::cmd_import_workbook ( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_import_workbook", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( ! test_types<std::string, std::string >( 3, 'l', 1, cmd ) ) {
        return fail_cmd( "cmd_import_workbook", ERR_PARSING_FAILED, "command malformed" );
    }

    try {
        const std::string filter_name = boost::any_cast<std::string>( *cmd[1] );
        const std::string file_path = boost::any_cast<std::string>( *cmd[2] );

        static server& ser = server::instance();
        shared_application_type application_object = m_session_context->selected().application();

        if ( application_object ) {
            filter_registry::shared_import_filter_type filter = ser.filters().get_import_filter( filter_name );
            boost::filesystem::path arg_file_path( file_path );
            std::vector<std::string> progress_list;
            {
                scoped_neutral_locale_enforcer en_us_locale_enforcer( *m_session_context );
                filter->do_import( *m_session_context, *application_object, progress_list, arg_file_path, false );
            }
            m_result << std::string( "[true," ) << m_json_serializer(  progress_list ) << std::string( "]," );
        } else {
            m_result << std::string( "[false,\"\"]," );
        }
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_import_workbook", e );
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_export_workbook ( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_export_workbook", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( ! test_types<std::string, std::string >( 3, 'l', 1, cmd ) ) {
        return fail_cmd( "cmd_export_workbook", ERR_PARSING_FAILED, "command malformed" );
    }

    try {
        const std::string filter_name = boost::any_cast<std::string>( *cmd[1] );
        const std::string file_path = boost::any_cast<std::string>( *cmd[2] );
        const bool as_snapshot = cmd.size() > 3 && cmd[3]->type() == typeid( bool ) ? boost::any_cast<bool>( *cmd[3] ) : false;

        static server& ser = server::instance();
        shared_workbook_type workbook_object = m_session_context->selected().workbook().lock();

        if ( workbook_object ) {
            filter_registry::shared_export_filter_type filter = ser.filters().get_export_filter( filter_name );
            boost::filesystem::path arg_file_path( file_path );
            {
                scoped_neutral_locale_enforcer en_us_locale_enforcer( *m_session_context );
                filter->do_export( *m_session_context, *workbook_object, arg_file_path, as_snapshot, false  );
            }

            m_result << std::string( "[true,\"\"]," );
        } else {
            m_result << std::string( "[false,\"\"]," );
        }
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_export_workbook", e );
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_book_not_saved ( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_book_not_saved", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( cmd.size() != 1 ) {
        return fail_cmd( "cmd_book_not_saved", ERR_PARSING_FAILED, "command malformed" );
    }

    try {
        active_worbook_has_changes_command command( *m_session_context );

        m_result << std::string( "[true," ) << m_json_serializer( execute_fetch( command ) ) << std::string( "]," );
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_book_not_saved", e );
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_get_undo_state ( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_get_undo_state", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( cmd.size()  !=  1 ) {
        return fail_cmd( "cmd_get_undo_state", ERR_PARSING_FAILED, "command malformed" );
    }

    std::vector<unsigned> return_value_array;

    try {
        if ( m_session_context->undo_redo_log().can_undo() ) {
            return_value_array.push_back( 1 );
        } else {
            return_value_array.push_back( 0 );
        }

        if ( m_session_context->undo_redo_log().can_redo() ) {
            return_value_array.push_back( 1 );
        } else {
            return_value_array.push_back( 0 );
        }

        m_result << std::string( "[true," ) << m_json_serializer( return_value_array ) << std::string( "]," );
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_get_undo_state", e );
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_start_undo_transaction ( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_start_undo_transaction", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( cmd.size()  !=  1 ) {
        return fail_cmd( "cmd_start_undo_transaction", ERR_PARSING_FAILED, "command malformed" );
    }

    try {

        m_session_context->undo_redo_log().start_transaction();

    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_start_undo_transaction", e );
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_end_undo_transaction ( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_end_undo_transaction", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( cmd.size()  !=  1 ) {
        return fail_cmd( "cmd_end_undo_transaction", ERR_PARSING_FAILED, "command malformed" );
    }

    try {

        m_session_context->undo_redo_log().end_transaction();

    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_end_undo_transaction", e );
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_undo ( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_undo", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( ! test_types<int >( 2, 'd', 1, cmd ) ) {
        return fail_cmd( "cmd_undo", ERR_PARSING_FAILED, "command malformed" );
    }

    try {
        unsigned long undo_steps = boost::any_cast<int>( *cmd[1] );

        while ( undo_steps-- ) {
            if ( m_session_context->undo_redo_log().can_undo() ) {
                m_session_context->undo_redo_log().undo();
            }
        }
        m_result << std::string( "[true,\"\"]," );

    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_undo", e );
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_redo ( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_redo", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( ! test_types<int >( 2, 'd', 1, cmd ) ) {
        return fail_cmd( "cmd_redo", ERR_PARSING_FAILED, "command malformed" );
    }

    try {
        unsigned long redo_steps = boost::any_cast<int>( *cmd[1] );

        while ( redo_steps-- ) {
            if ( m_session_context->undo_redo_log().can_redo() ) {
                m_session_context->undo_redo_log().redo();
            }
        }
        m_result << std::string( "[true,\"\"]," );

    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_redo", e );
    }

    return true;
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
bool CCmdHandler::cmd_copy_range( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_copy_range", ERR_INVALID_SESSION, "invalid session received" );
    }
    if ( cmd.size() < 2 ) {
        return fail_cmd( "cmd_copy_range", ERR_PARSING_FAILED, "command malformed" );
    }

    std::vector<copy_range_command::result_type> return_value_array;

    try {
        for ( json_array_t::size_type i_cmd = 1; i_cmd < cmd.size(); i_cmd++ ) {
            if ( cmd[i_cmd]->type() != typeid( json_array_t ) ) {
                return fail_cmd( "cmd_copy_range", ERR_PARSING_FAILED, "command malformed" );
            }

            const json_array_t& coords = boost::any_cast<json_array_t>( *cmd[i_cmd] );

            if ( ! test_types<int, int, int, int>( 4, 'd', 0, coords ) ) {
                return fail_cmd( "cmd_copy_range", ERR_PARSING_FAILED, "command malformed" );
            }

            sheet_range copy_range( sheet_point( 0, 0 ) );

            if ( ! bind_rect( 0, coords, copy_range ) ) {
                return fail_cmd( "cmd_copy_range", ERR_PARSING_FAILED, "check_range_coord: invalid coordinates" );
            }

            copy_range_command command( *m_session_context,  copy_range );

            return_value_array.push_back( execute_fetch( command ) );

        }
        m_result << std::string( "[true," ) << m_json_serializer( return_value_array ) << std::string( "]," );

    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_copy_range", e );
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_copyfill_range ( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_copyfill_range", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( cmd.size()  <  2 ) {
        return fail_cmd( "cmd_copyfill_range", ERR_PARSING_FAILED, "command malformed" );
    }

    std::vector<copy_range_command::result_type> return_value_array;

    try {
        for ( json_array_t::size_type i_cmd = 1; i_cmd < cmd.size(); i_cmd++ ) {
            if ( cmd[i_cmd]->type() != typeid( json_array_t ) ) {
                return fail_cmd( "cmd_copyfill_range", ERR_PARSING_FAILED, "command malformed" );
            }

            const json_array_t& coords = boost::any_cast<json_array_t>( *cmd[i_cmd] );

            if ( ! test_types<int, int, int, int>( 4, 'd', 0, coords ) ) {
                return fail_cmd( "cmd_copyfill_range", ERR_PARSING_FAILED, "command malformed" );
            }

            sheet_range copy_range( sheet_point( 0, 0 ) );

            if ( ! bind_rect( 0, coords, copy_range ) ) {
                return fail_cmd( "cmd_copyfill_range", ERR_PARSING_FAILED, "check_range_coord: invalid coordinates" );
            }

            copy_fill_range_command command( *m_session_context, copy_range );
            return_value_array.push_back( execute_fetch( command ) );
        }

        m_result << std::string( "[true," ) << m_json_serializer( return_value_array ) << std::string( "]," );
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_copyfill_range", e );
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_copymove_range ( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_copymove_range", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( cmd.size() < 2 ) {
        return fail_cmd( "cmd_copymove_range", ERR_PARSING_FAILED, "command malformed" );
    }

    std::vector<copy_move_range_command::result_type> return_value_array;

    try {
        for ( json_array_t::size_type size = cmd.size(), i_cmd = 1; i_cmd < size; ++i_cmd ) {
            if ( cmd[i_cmd]->type() != typeid( json_array_t ) ) {
                return fail_cmd( "cmd_copymove_range", ERR_PARSING_FAILED, "command malformed" );
            }

            const json_array_t& coords = boost::any_cast<json_array_t>( *cmd[i_cmd] );

            if ( !test_types<int, int, int, int>( 4, 'd', 0, coords ) ) {
                return fail_cmd( "cmd_copymove_range", ERR_PARSING_FAILED, "command malformed" );
            }

            sheet_range copymove_range( sheet_point( 0, 0 ) );

            if ( !bind_rect( 0, coords, copymove_range ) ) {
                return fail_cmd( "cmd_copymove_range", ERR_PARSING_FAILED, "check_range_coord: invalid coordinates" );
            }

            copy_move_range_command command( *m_session_context, copymove_range );

            return_value_array.push_back( execute_fetch( command ) );

        }
        m_result << std::string( "[true," ) << m_json_serializer( return_value_array ) << std::string( "]," );

    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_copymove_range", e );
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_cut_range( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_cut_range", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( cmd.size() < 2 ) {
        return fail_cmd( "cmd_cut_range", ERR_PARSING_FAILED, "command malformed" );
    }

    std::vector<move_range_command::result_type> return_value_array;

    try {
        for ( json_array_t::size_type i_cmd = 1; i_cmd < cmd.size(); i_cmd++ ) {
            if ( cmd[i_cmd]->type() != typeid( json_array_t ) ) {
                return fail_cmd( "cmd_cut_range", ERR_PARSING_FAILED, "command malformed" );
            }

            const json_array_t& coords = boost::any_cast<json_array_t>( *cmd[i_cmd] );

            if ( ! test_types<int, int, int, int>( 4, 'd', 0, coords ) ) {
                return fail_cmd( "cmd_cut_range", ERR_PARSING_FAILED, "command malformed" );
            }

            sheet_range cut_range( sheet_point( 0, 0 ) );

            if ( ! bind_rect( 0, coords, cut_range ) ) {
                return fail_cmd( "cmd_cut_range", ERR_PARSING_FAILED, "check_range_coord: invalid coordinates" );
            }

            move_range_command command( *m_session_context, cut_range );

            return_value_array.push_back( execute_fetch( command ) );
        }
        m_result << std::string( "[true," ) << m_json_serializer( return_value_array ) << std::string( "]," );

    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_cut_range", e );
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_paste_range( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_paste_range", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( cmd.size() < 2 ) {
        return fail_cmd( "cmd_paste_range", ERR_PARSING_FAILED, "command malformed" );
    }

    try {
        for ( json_array_t::size_type i_cmd = 1; i_cmd < cmd.size(); i_cmd++ ) {
            if ( cmd[i_cmd]->type() != typeid( json_array_t ) ) {
                return fail_cmd( "cmd_paste_range", ERR_PARSING_FAILED, "command malformed" );
            }

            const json_array_t& coords = boost::any_cast<json_array_t>( *cmd[i_cmd] );

            if ( ! test_types<int, int, int, int, int, int>( 6, 'd', 0, coords ) ) {
                return fail_cmd( "cmd_paste_range", ERR_PARSING_FAILED, "command malformed" );
            }

            unsigned long clipboard_id = boost::any_cast<int>( *coords[0] );
            unsigned long paste_type = boost::any_cast<int>( *coords[5] );
            sheet_range paste_range( sheet_point( 0, 0 ) );

            if ( ! bind_rect( 1, coords, paste_range ) ) {
                return fail_cmd( "cmd_cut_range", ERR_PARSING_FAILED, "check_range_coord: invalid coordinates" );
            }

            paste_range_command command( *m_session_context, paste_range, clipboard_id, paste_type );
            m_session_context->undo_redo_log().execute( command );
        }

        m_result << std::string( "[true,\"\"]," );
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_paste_range", e );
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_clear_attributes( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_clear_attributes", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( cmd.size() < 2 ) {
        return fail_cmd( "cmd_clear_attributes", ERR_PARSING_FAILED, "command malformed" );
    }

    try {
        for ( json_array_t::size_type i_cmd = 1; i_cmd < cmd.size(); i_cmd++ ) {
            if ( cmd[i_cmd]->type() != typeid( json_array_t ) ) {
                return fail_cmd( "cmd_clear_attributes", ERR_PARSING_FAILED, "command malformed" );
            }

            const json_array_t& coords = boost::any_cast<json_array_t>( *cmd[i_cmd] );

            if ( ! test_types<int, int, int, int>( 4, 'd', 0, coords ) ) {
                return fail_cmd( "cmd_clear_attributes", ERR_PARSING_FAILED, "command malformed" );
            }

            sheet_range clear_range( sheet_point( 0, 0 ) );

            if ( ! bind_rect( 0, coords, clear_range ) ) {
                return fail_cmd( "cmd_clear_attributes", ERR_PARSING_FAILED, "check_range_coord: invalid coordinates" );
            }

            clear_attributes_command command( *m_session_context, clear_range );
            m_session_context->undo_redo_log().execute( command );
        }

        m_result << std::string( "[true,\"\"]," );
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_clear_attributes", e );
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_hb_dependents( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_hb_dependents", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( cmd.size() < 2 ) {
        return fail_cmd( "cmd_hb_dependents", ERR_PARSING_FAILED, "command malformed" );
    }

    variant return_value_array;

    try {
        for ( json_array_t::size_type i_cmd = 1; i_cmd < cmd.size(); i_cmd++ ) {
            if ( cmd[i_cmd]->type() != typeid( json_array_t ) ) {
                return fail_cmd( "cmd_hb_dependents", ERR_PARSING_FAILED, "command malformed" );
            }

            const json_array_t& coords = boost::any_cast<json_array_t>( *cmd[i_cmd] );

            if ( ! test_types<int, int, int, int>( 4, 'd', 0, coords ) ) {
                return fail_cmd( "cmd_hb_dependents", ERR_PARSING_FAILED, "command malformed" );
            }

            sheet_range hb_range( sheet_point( 0, 0 ) );

            if ( ! bind_rect( 0, coords, hb_range ) ) {
                return fail_cmd( "cmd_hb_dependents", ERR_PARSING_FAILED, "check_range_coord: invalid coordinates" );
            }

            get_dependents_command command( *m_session_context, hb_range );
            return_value_array = execute_fetch( command );
        }
        m_result << std::string( "[true,[" ) <<  m_json_serializer( return_value_array , JSONSerializer::JsonEncoding::POINT_TRANSFORM_COORD ) << std::string( "]]," );

    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_hb_dependents", e );
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_set_array_formula( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_set_array_formula", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( cmd.size() < 2 ) {
        return fail_cmd( "cmd_set_array_formula", ERR_PARSING_FAILED, "command malformed" );
    }

    std::vector<bool> return_value_array;
    try {
        for ( json_array_t::size_type i_cmd = 1; i_cmd < cmd.size(); i_cmd++ ) {
            if ( cmd[i_cmd]->type() != typeid( json_array_t ) ) {
                return fail_cmd( "cmd_set_array_formula", ERR_PARSING_FAILED, "command malformed" );
            }

            const json_array_t& coords = boost::any_cast<json_array_t>( *cmd[i_cmd] );

            if ( ! test_types<int, int, int, int>( 5, 'd', 0, coords ) ) {
                return fail_cmd( "cmd_set_array_formula", ERR_PARSING_FAILED, "command malformed" );
            }

            sheet_range range( sheet_point( 0, 0 ) );

            if ( ! bind_rect( 0, coords, range ) ) {
                return fail_cmd( "cmd_set_array_formula", ERR_PARSING_FAILED, "check_range_coord: invalid coordinates" );
            }

            variant value = json2Value( coords[4] );

            set_array_value_command command( *m_session_context, range, value );
            m_session_context->undo_redo_log().execute( command );
            return_value_array.push_back( true );
        }

        m_result << std::string( "[true," ) <<  m_json_serializer( return_value_array ) << std::string( "]," );
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_set_array_formula", e );
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_unset_array_formula( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_unset_array_formula", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( cmd.size() < 2 ) {
        return fail_cmd( "cmd_unset_array_formula", ERR_PARSING_FAILED, "command malformed" );
    }

    std::vector<bool> return_value_array;
    try {
        const json_array_t::size_type cmd_size = cmd.size();

        for ( json_array_t::size_type i = 1; i < cmd_size; ++i ) {
            if ( cmd[i]->type() != typeid( json_array_t ) ) {
                return fail_cmd( "cmd_unset_array_formula", ERR_PARSING_FAILED, "command malformed" );
            }

            const json_array_t& coords = boost::any_cast<json_array_t>( *cmd[i] );

            if ( ! test_types<int, int, int, int>( 4, 'd', 0, coords ) ) {
                return fail_cmd( "cmd_unset_array_formula", ERR_PARSING_FAILED, "command malformed" );
            }

            sheet_range range( sheet_point( 0, 0 ) );

            if ( ! bind_rect( 0, coords, range ) ) {
                return fail_cmd( "cmd_unset_array_formula", ERR_PARSING_FAILED, "invalid coordinates" );
            }

            deactivate_array_formula_command command( *m_session_context, range );
            m_session_context->undo_redo_log().execute( command );
            return_value_array.push_back( true );
        }

        m_result << std::string( "[true," ) <<  m_json_serializer( return_value_array ) << std::string( "]," );
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_unset_array_formula", e );
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_names_get( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_names_get", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( cmd.size() < 2 ) {
        return fail_cmd( "cmd_names_get", ERR_PARSING_FAILED, "command malformed" );
    }

    std::vector<i_named_formula_manager::key_val_vec_type> return_value_array;
    try {
        for ( json_array_t::size_type i_cmd = 1; i_cmd < cmd.size(); i_cmd++ ) {
            if ( cmd[i_cmd]->type() != typeid( json_array_t ) ) {
                return fail_cmd( "cmd_names_get", ERR_PARSING_FAILED, "command malformed" );
            }

            const json_array_t& coords = boost::any_cast<json_array_t>( *cmd[i_cmd] );

            if ( ! test_types<int, int, std::string, std::string>( 4, 'l', 0, coords ) ) {
                return fail_cmd( "cmd_cut_range", ERR_PARSING_FAILED, "command malformed" );
            }

            unsigned long x1  = boost::any_cast<int>( *coords[0] );
            unsigned long y1  = boost::any_cast<int>( *coords[1] );

            std::string name  = boost::any_cast<std::string>( *coords[2] );
            const std::string id_string = boost::any_cast<std::string>( *coords[3] );
            uuid_type scope = id_string.empty() ? boost::uuids::nil_uuid() : boost::lexical_cast<uuid_type>( id_string );

            if ( !transform_coords( x1, y1 ) ) {
                return fail_cmd( "cmd_names_get", 0, "check_range_coord: invalid coordinates" );
            }

            get_named_formula_command command( *m_session_context, name, scope, sheet_point( y1, x1 ) );

            bool catch_exp ;

            switch ( coords.size() ) {
                case 4:
                    return_value_array.push_back( execute_fetch( command ) );
                    break;
                case 5:
                    if ( coords[4]->type() != typeid( bool ) ) {
                        return fail_cmd( "cmd_names_get", ERR_PARSING_FAILED, "command malformed" );
                    }
                    catch_exp = boost::any_cast<bool>( *coords[4] );
                    if ( catch_exp ) {
                        try {
                            return_value_array.push_back( execute_fetch( command ) );
                        } catch ( named_formula_not_found_exception& /*n*/ ) {
                            i_named_formula_manager::key_val_vec_type vt;
                            return_value_array.push_back( vt );
                        }
                    } else {
                        return_value_array.push_back( execute_fetch( command ) );
                    }
                    break;
                default:
                    return fail_cmd( "cmd_names_get", ERR_PARSING_FAILED, "check_parameters: invalid number parameters" );
                    break;

            }
        }

        m_result << std::string( "[true," ) <<  m_json_serializer( return_value_array ) << std::string( "]," );
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_names_get", e );
    }
    return true;

}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_names_list( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_names_list", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( cmd.size() < 2 ) {
        return fail_cmd( "cmd_names_list", ERR_PARSING_FAILED, "command malformed" );
    }

    std::vector < i_named_formula_manager::key_val_vec_vec_type >  return_value_array;

    try {
        shared_workbook_type workbook = m_session_context->selected().workbook().lock();
        if ( workbook ) {
            for ( json_array_t::size_type i_cmd = 1; i_cmd < cmd.size(); i_cmd++ ) {

                if ( cmd[i_cmd]->type() != typeid( json_array_t ) ) {
                    return fail_cmd( "cmd_names_list", ERR_PARSING_FAILED, "command malformed" );
                }

                const json_array_t& coords = boost::any_cast<json_array_t>( *cmd[i_cmd] );

                if ( ! test_types<int, int>( 2, 'd', 0, coords ) ) {
                    return fail_cmd( "cmd_names_list", ERR_PARSING_FAILED, "command malformed" );
                }

                unsigned long x1  = boost::any_cast<int>( *coords[0] );
                unsigned long y1  = boost::any_cast<int>( *coords[1] );

                if ( !transform_coords( x1, y1 ) ) {
                    return fail_cmd( "cmd_names_list", 0, "check_range_coord: invalid coordinates" );
                }

                get_all_named_formulas_command command( *m_session_context, workbook, sheet_point( y1, x1 ) );
                return_value_array.push_back( execute_fetch( command ) );
            }
        } else {
            return fail_cmd( "cmd_names_list", 100, "handle_names_list: could not get the named formulas list: no workbook is currently selected" );
        }

        m_result << std::string( "[true," ) <<  m_json_serializer( return_value_array ) << std::string( "]," );
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_names_list", e );
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_names_add( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_names_add", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( cmd.size() < 2 ) {
        return fail_cmd( "cmd_names_add", ERR_PARSING_FAILED, "command malformed" );
    }

    std::vector<i_named_formula_manager::key_val_vec_type> return_value_array;

    try {
        for ( json_array_t::size_type i_cmd = 1; i_cmd < cmd.size(); i_cmd++ ) {
            if ( cmd[i_cmd]->type() != typeid( json_array_t ) ) {
                return fail_cmd( "cmd_names_add", ERR_PARSING_FAILED, "command malformed" );
            }

            const json_array_t& coords = boost::any_cast<json_array_t>( *cmd[i_cmd] );

            if ( ! test_types<int, int, json_obj_t>( 3, 'd', 0, coords ) ) {
                return fail_cmd( "cmd_names_add", ERR_PARSING_FAILED, "command malformed" );
            }

            unsigned long x1  = boost::any_cast<int>( *coords[0] );
            unsigned long y1  = boost::any_cast<int>( *coords[1] );

            if ( !transform_coords( x1, y1 ) ) {
                return fail_cmd( "cmd_names_add", ERR_PARSING_FAILED, "check_range_coord: invalid coordinates" );
            }

            json_obj_t  properties ;
            properties = boost::any_cast<json_obj_t>( *coords[2] );
            std::map<std::string, std::string> properties_list;
            json_obj_t::iterator it_map = properties.begin();
            json_obj_t::iterator end_it_map = properties.end();

            while ( it_map != end_it_map ) {
                properties_list.insert( std::make_pair( ( *it_map ).first, boost::any_cast<std::string>( *( *it_map ).second ) ) );
                ++it_map;
            }
            sheet_point formula_point( y1, x1 );
            create_named_formula_command command( *m_session_context, properties_list, formula_point );;
            return_value_array.push_back( execute_fetch( command ) );
        }

        m_result << std::string( "[true," ) <<  m_json_serializer( return_value_array ) << std::string( "]," );
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_names_add", e );
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_names_update( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_names_update", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( cmd.size() < 2 ) {
        return fail_cmd( "cmd_names_update", ERR_PARSING_FAILED, "command malformed" );
    }

    std::vector<i_named_formula_manager::key_val_vec_type> return_value_array;

    try {
        for ( json_array_t::size_type i_cmd = 1; i_cmd < cmd.size(); i_cmd++ ) {
            if ( cmd[i_cmd]->type() != typeid( json_array_t ) ) {
                return fail_cmd( "cmd_names_update", ERR_PARSING_FAILED, "command malformed" );
            }

            const json_array_t& coords = boost::any_cast<json_array_t>( *cmd[i_cmd] );

            if ( ! test_types<int, int>( 4, 'd', 1, coords ) ) {
                return fail_cmd( "cmd_names_update", ERR_PARSING_FAILED, "command malformed" );
            }

            unsigned long x1  = boost::any_cast<int>( *coords[1] );
            unsigned long y1  = boost::any_cast<int>( *coords[2] );
            std::string formula_id = "";

            if ( !transform_coords( x1, y1 ) ) {
                return fail_cmd( "cmd_names_update", 0, "check_range_coord: invalid coordinates" );
            }


            json_obj_t  properties ;
            properties =  boost::any_cast<json_obj_t>( *coords[3] );
            std::map<std::string, std::string>     properties_list;
            json_obj_t::iterator it_map = properties.begin();
            json_obj_t::iterator end_it_map = properties.end();

            while ( it_map != end_it_map ) {
                properties_list.insert( std::make_pair( ( *it_map ).first, boost::any_cast<std::string>( *( *it_map ).second ) ) );
                ++it_map;
            }
            sheet_point formula_point( y1, x1 );

            if ( coords[0]->type() == typeid( std::string ) ) {
                formula_id = boost::any_cast<std::string>( *coords[0] );

                update_named_formula_command command( *m_session_context, formula_id, properties_list, formula_point );
                return_value_array.push_back( execute_fetch( command ) );

            } else if ( coords[0]->type() == typeid( json_array_t ) ) {
                const json_array_t& name_scope = boost::any_cast<json_array_t>( *coords[0] );

                update_named_formula_command command(
                    *m_session_context,
                    named_formula_identifier(
                        boost::any_cast<std::string>( *name_scope[0] ),
                        boost::lexical_cast<uuid_type>( boost::any_cast<std::string>( *name_scope[1] ) ) ),
                    properties_list,
                    formula_point
                );
                return_value_array.push_back( execute_fetch( command ) );

            } else {
                return fail_cmd( "cmd_names_update", ERR_PARSING_FAILED, "command malformed" );
            }
        }

        m_result << std::string( "[true," ) <<  m_json_serializer( return_value_array ) << std::string( "]," );
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_names_update", e );
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_names_delete( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_names_delete", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( cmd.size() < 2 ) {
        return fail_cmd( "cmd_names_delete", ERR_PARSING_FAILED, "command malformed" );
    }

    std::vector<bool> return_value_array;
    try {
        for ( unsigned int i_cmd = 1; i_cmd < cmd.size(); i_cmd++ ) {
            if ( cmd[i_cmd]->type() != typeid( std::string ) ) {
                return fail_cmd( "cmd_names_delete", ERR_PARSING_FAILED, "command malformed" );
            }

            std::string formula_id = boost::any_cast<std::string>( *cmd[i_cmd] );

            remove_named_formula_command command( *m_session_context, formula_id );
            command.execute();
            return_value_array.push_back( true );
        }

        m_result << std::string( "[true," ) <<  m_json_serializer( return_value_array ) << std::string( "]," );
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_names_delete", e );
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_set_variable( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_set_variable", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( cmd.size() < 3 || cmd[1]->type() != typeid( std::string ) ) {
        return fail_cmd( "cmd_set_variable", ERR_PARSING_FAILED, "command malformed" );
    }
    try {
        m_session_context->variable().variable( *m_session_context, boost::any_cast<std::string>( *cmd[1] ), json2Value( cmd[2] ) );
        m_result << std::string( "[true,\"\"]," );
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_set_variable", e );
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_get_variable( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_get_variable", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( ! test_types<std::string>( 2, 'd', 1, cmd ) ) {
        return fail_cmd( "cmd_get_variable", ERR_PARSING_FAILED, "command malformed" );
    }

    try {
        const std::string variable_name = boost::any_cast<std::string>( *cmd[1] );

        m_result << std::string( "[true," ) <<  m_json_serializer( m_session_context->variable().variable( variable_name ) ) << std::string( "]," );
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_get_variable", e );
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_get_variable_list( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_get_variable_list", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( cmd.size() != 1 ) {
        return fail_cmd( "cmd_get_variable_list", ERR_PARSING_FAILED, "command malformed" );
    }

    std::vector<std::string> return_value_array;

    try {
        const std::map<std::string, variant>& variable_map = m_session_context->variable().list();

        for ( std::map<std::string, variant>::const_iterator it = variable_map.begin(), end = variable_map.end(); it != end; ++it ) {
            return_value_array.push_back( ( *it ).first );
        }

        shared_workbook_type wb( m_session_context->selected().workbook().lock() );
        if ( wb ) {
            const variable_name_list_type name_list = wb->variable_list();
            for ( variable_name_list_type::const_iterator it = name_list.begin(), end_it = name_list.end(); it != end_it; ++it ) {
                return_value_array.push_back( *it );
            }
        }

        std::sort( return_value_array.begin(), return_value_array.end() );
        std::vector<std::string>::iterator new_end = std::unique( return_value_array.begin(), return_value_array.end() );
        return_value_array.resize( new_end - return_value_array.begin() );

        m_result << std::string( "[true," ) <<  m_json_serializer( return_value_array ) << std::string( "]," );

    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_get_variable_list", e );
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_clear_variables( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_clear_variables", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( cmd.size() != 1 ) {
        return fail_cmd( "cmd_clear_variables", ERR_PARSING_FAILED, "command malformed" );
    }

    try {
        m_session_context->variable().clear();
        m_result << std::string( "[true,\"\"]," );
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_clear_variables", e );
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_get_book_var_list ( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_get_book_var_list", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( cmd.size() > 2 ) {
        return fail_cmd( "cmd_get_book_var_list", ERR_PARSING_FAILED, "command malformed" );
    }

    try {
        if ( cmd.size() == 1 ) {
            shared_workbook_type wb = m_session_context->selected().workbook().lock();
            if ( wb.get() ) {
                m_result << std::string( "[true," ) << m_json_serializer( wb-> variable_list() ) << std::string( "]," );
            } else {
                return fail_cmd( "cmd_get_book_var_list", ERR_RUNTIME_ERROR, "workbook not available" );
            }
        } else {
            if ( cmd[1]->type()  !=  typeid( std::string ) ) {
                return fail_cmd( "cmd_get_book_var_list", ERR_PARSING_FAILED, "command malformed" );
            }

            std::string file_path = boost::any_cast<std::string>( *cmd[1] );

            if ( file_path != "" ) {
                get_workbook_variables_command command( *m_session_context, file_path );
                m_result << std::string( "[true," ) << m_json_serializer( execute_fetch( command ) ) << std::string( "]," );
            } else {
                m_result << std::string( "[false,\"empty file path\"]," );
            }
        }
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_get_book_var_list", e );
    }

    return true;
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_get_wsheet_elements( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_get_wsheet_elements", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( ! test_types<std::string>( 5, 'd', 1, cmd ) ) {
        return fail_cmd( "cmd_get_wsheet_elements", ERR_PARSING_FAILED, "command malformed" );
    }

    try {
        bool wb_scope = ( boost::any_cast<std::string>( *cmd[0] ) == "bget" ? true : false );

        std::string worksheet_uuid = boost::any_cast<std::string>( *cmd[1] );

        const json_array_t& array_keys_list = boost::any_cast<json_array_t>( *cmd[2] );
        get_worksheet_elements_command::id_vec_type    keys_list;

        for ( unsigned int i_keys = 0; i_keys < array_keys_list.size(); i_keys++ ) {
            keys_list.push_back( boost::any_cast<std::string>( *array_keys_list[i_keys] ) );
        }

        const json_array_t& array_properties_list = boost::any_cast<json_array_t>( *cmd[3] );
        std::vector<std::string>    properties_list;

        for ( unsigned int i_properties = 0; i_properties < array_properties_list.size(); i_properties++ ) {
            properties_list.push_back( boost::any_cast<std::string>( *array_properties_list[i_properties] ) );
        }

        worksheet_element::key_value_vector_type query_list;
        json_obj_t  cmd_wsheet_pairs_list;
        cmd_wsheet_pairs_list = boost::any_cast<json_obj_t >( *cmd[4] );
        json_obj_t::iterator it_map = cmd_wsheet_pairs_list.begin();
        json_obj_t::iterator end_it_map = cmd_wsheet_pairs_list.end();

        while ( it_map != end_it_map ) {
            query_list.push_back( std::make_pair( ( *it_map ).first, json2Value( ( *it_map ).second ) ) );
            ++it_map;
        }
        get_worksheet_elements_command command( *m_session_context, worksheet_uuid, keys_list, properties_list, query_list, wb_scope );
        command.execute();
        m_result << std::string( "[true," ) <<  m_json_serializer( command.value(), JSONSerializer::JsonEncoding::RAW_IF_CURL_OR_ANGL ) << std::string( "]," );

    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_get_wsheet_elements", e );
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_add_wsheet_elements( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_add_wsheet_elements", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( ! test_types<std::string>( 3, 'l', 1, cmd ) ) {
        return fail_cmd( "cmd_add_wsheet_elements", ERR_PARSING_FAILED, "command malformed" );
    }

    std::vector<std::string> return_value_array;
    try {
        bool wb_scope = ( boost::any_cast<std::string>( *cmd[0] ) == "badd" ? true : false );

        std::string worksheet_uuid = boost::any_cast<std::string>( *cmd[1] );

        for ( json_array_t::size_type i_cmd = 2; i_cmd < cmd.size(); i_cmd++ ) {
            worksheet_element::key_value_vector_type properties_list;
            json_obj_t  cmd_wsheet_pairs_list;
            cmd_wsheet_pairs_list = boost::any_cast<json_obj_t>( *cmd[i_cmd] );
            json_obj_t::iterator it_map = cmd_wsheet_pairs_list.begin();
            json_obj_t::iterator end_it_map = cmd_wsheet_pairs_list.end();

            while ( it_map != end_it_map ) {
                properties_list.push_back( std::make_pair( ( *it_map ).first, json2Value( ( *it_map ).second ) ) );
                ++it_map;
            }

            create_worksheet_element_command command( *m_session_context, worksheet_uuid, properties_list, wb_scope );
            return_value_array.push_back( execute_fetch( command ) );
        }

        m_result << std::string( "[true," ) <<  m_json_serializer( return_value_array ) << std::string( "]," );
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_add_wsheet_elements", e );
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_update_wsheet_elements( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_update_wsheet_elements", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( ! test_types<std::string>( 3, 'd', 1, cmd ) ) {
        return fail_cmd( "cmd_update_wsheet_elements", ERR_PARSING_FAILED, "command malformed" );
    }

    try {
        bool wb_scope = ( boost::any_cast<std::string>( *cmd[0] ) == "bupd" ? true : false );
        std::string worksheet_uuid = boost::any_cast<std::string>( *cmd[1] );
        std::vector<std::string> arg_keys_list;
        update_worksheet_elements_command::key_value_vector_vector_type arg_properties_list;
        worksheet_element::key_value_vector_type properties_list;
        json_obj_t cmd_wsheet_key_pairs_list;

        cmd_wsheet_key_pairs_list = boost::any_cast<json_obj_t >( *cmd[2] );
        json_obj_t::iterator it_map = cmd_wsheet_key_pairs_list.begin();
        json_obj_t::iterator end_it_map = cmd_wsheet_key_pairs_list.end();

        while ( it_map != end_it_map ) {
            arg_keys_list.push_back( ( *it_map ).first );
            json_obj_t map_pairs_string_value = boost::any_cast<json_obj_t >( *( *it_map ).second );
            json_obj_t ::iterator it_map_pairs_string_value = map_pairs_string_value.begin();
            json_obj_t ::iterator end_it_map_pairs_string_value = map_pairs_string_value.end();

            while ( it_map_pairs_string_value != end_it_map_pairs_string_value ) {
                properties_list.push_back( std::make_pair( ( *it_map_pairs_string_value ).first, json2Value( ( *it_map_pairs_string_value ).second ) ) );
                ++it_map_pairs_string_value;
            }

            arg_properties_list.push_back( properties_list );
            ++it_map;
        }

        update_worksheet_elements_command command( *m_session_context, worksheet_uuid, arg_keys_list, arg_properties_list, wb_scope );
        command.execute();
        m_result << std::string( "[true,\"\"]," );
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_update_wsheet_elements", e );
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_delete_wsheet_elements( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_delete_wsheet_elements", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( ! test_types<std::string>( 3, 'd', 1, cmd ) ) {
        return fail_cmd( "cmd_delete_wsheet_elements", ERR_PARSING_FAILED, "command malformed" );
    }

    try {
        bool wb_scope = ( boost::any_cast<std::string>( *cmd[0] ) == "bdel" ? true : false );
        std::string worksheet_uuid = boost::any_cast<std::string>( *cmd[1] );
        const json_array_t& array_keys_list = boost::any_cast<json_array_t>( *cmd[2] );
        std::vector<std::string>   keys_list;

        for ( json_array_t::size_type i = 0; i < array_keys_list.size() ; i++ ) {
            keys_list.push_back( boost::any_cast<std::string>( *array_keys_list[i] ) );
        }

        remove_worksheet_element_command command( *m_session_context, worksheet_uuid, keys_list, wb_scope );
        command.execute();
        m_result << std::string( "[true,\"\"]," );
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_delete_wsheet_elements", e );
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

inline void CCmdHandler::set_cell ( const json_obj_t& cell, const sheet_range& range, const bool combine, const bool combine_attrs, const bool combine_style )
{
    bool no_v = true, no_s = true, no_a = true, no_o = true;

    json_obj_t::const_iterator it = cell.begin(), it_end = cell.end();

    while ( it != it_end ) {
        switch ( ( *it ).first.at( 0 ) ) {
                // value
            case 'v': {
#ifdef _CORE2_COMPATIBILITY_ON_AUTO_DETECT_INPUT_
                set_value_command( *m_session_context, range, json2Value( ( *it ).second ) ).execute();
#else
                //some old core 2 code in the ui still shoots true/false
                if ( ( *it ).second->type() == typeid( bool ) ) {
                    if ( boost::any_cast< bool >( *( *it ).second ) ) {
                        set_value_command( *m_session_context, range, variant( true ) ).execute();
                    } else {
                        set_value_command( *m_session_context, range, variant( false ) ).execute();
                    }
                } else if ( ( *it ).second->type() == typeid( std::string ) ) {
                    set_value_command( *m_session_context, range, boost::any_cast<std::string>( *( *it ).second ) ).execute();
                } else if ( ( *it ).second->type() != typeid( void ) ) {
                    set_value_command( *m_session_context, range, json2Value( ( *it ).second ) ).execute();
                }
#endif
                //m_session_context->undo_redo_log().execute( cmd );
                no_v = false;
            }
            break;

            // style
            case 's': {
                if ( ( *it ).second->type() != typeid( std::string ) ) {
                    break;
                }

                if ( !combine_style ) {
                    set_style_command( *m_session_context, range, "" ).execute();
                    // m_session_context->undo_redo_log().execute( cmd );
                }

                set_style_command( *m_session_context, range, boost::any_cast<std::string>( *( *it ).second ) ).execute();
                //  m_session_context->undo_redo_log().execute( cmd );
                no_s = false;
            }
            break;

            // attributes
            case 'a': {
                if ( ( *it ).second->type() != typeid( json_obj_t ) ) {
                    break;
                }

                set_attribute_command( *m_session_context, range, ( ~( *it ).second ).c_str() ).execute();
                //   m_session_context->undo_redo_log().execute( cmd );
                no_a = false;
            }
            break;

            // format
            case 'o': {
                if ( ( *it ).second->type() != typeid( std::string ) ) {
                    break;
                }

                set_format_command( *m_session_context, range, boost::any_cast<std::string>( *( *it ).second ) ).execute();
                // m_session_context->undo_redo_log().execute( cmd );
                no_o = false;
            }
            break;

            default:
                break;
        }

        ++it;
    }

    if ( combine ) {
        return;
    }

    if ( no_v ) {
        set_value_command( *m_session_context, range, variant( variant::type_empty ) ).execute();
        //  m_session_context->undo_redo_log().execute( cmd );
    }

    if ( no_s ) {
        set_style_command( *m_session_context, range, "" ).execute();
        //   m_session_context->undo_redo_log().execute( cmd );
    }

    if ( no_a ) {
        clear_attributes_command( *m_session_context, range ).execute();
        // m_session_context->undo_redo_log().execute( cmd );
    }

    if ( no_o ) {
        set_format_command( *m_session_context, range, "" ).execute();
        //cmd.execute();
    }
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


bool CCmdHandler::cmd_set_cell_region ( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_set_cell_region", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( cmd.size() < 3 ) {
        return fail_cmd( "cmd_set_cell_region", ERR_PARSING_FAILED, "command malformed" );
    }

    try {
        bool combine = false, combine_attrs = true, combine_style = true;

        const json_obj_t& opts = boost::any_cast<json_obj_t>( *cmd[1] );
        json_obj_t::const_iterator it_opts = opts.begin(), it_opts_end = opts.end();

        while ( it_opts != it_opts_end ) {
            if ( ( *it_opts ).first == "cm" ) {
                combine = boost::any_cast<bool>( *( *it_opts ).second );
            } else if ( ( *it_opts ).first == "ca" ) {
                combine_attrs = boost::any_cast<bool>( *( *it_opts ).second );
            } else if ( ( *it_opts ).first == "cs" ) {
                combine_style = boost::any_cast<bool>( *( *it_opts ).second );
            }

            ++it_opts;
        }

        for ( json_array_t::size_type cmd_size = cmd.size(), rgn_i = 2; rgn_i < cmd_size; ++rgn_i ) {
            if ( cmd[rgn_i]->type() != typeid( json_array_t ) ) {
                return fail_cmd( "cmd_set_cell_region", ERR_PARSING_FAILED, "command malformed" );
            }

            const json_array_t& rgn = boost::any_cast<json_array_t>( *cmd[rgn_i] );

            unsigned long x = boost::any_cast<int>( *rgn[0] ),
                          y = boost::any_cast<int>( *rgn[1] ),
                          w = boost::any_cast<int>( *rgn[2] );

            if ( !transform_coords( x, y ) ) {
                return fail_cmd( "cmd_set_cell_region", ERR_PARSING_FAILED, "check_range_coord: invalid coordinates" );
            }

            unsigned long x_curr = x;

            for ( json_array_t::size_type rgn_size = rgn.size(), cell_i = 3; cell_i < rgn_size; ++cell_i ) {
                const json_obj_t& cell = boost::any_cast<json_obj_t>( *rgn[cell_i] );

                set_cell( cell, sheet_range( sheet_point( y, x_curr ) ), combine, combine_attrs, combine_style );

                if ( ++x_curr - x >= w && w > 0 ) {
                    ++y, x_curr = x;
                }
            }
        }

        m_result << std::string( "[true,\"\"]," );
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_set_cell_region", e );
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_set_cell_range ( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_set_cell_range", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( cmd.size() <  3 ) {
        return fail_cmd( "cmd_set_cell_range", ERR_PARSING_FAILED, "command malformed" );
    }

    try {
        bool combine = false, combine_attrs = true, combine_style = true;

        const json_obj_t& opts = boost::any_cast<json_obj_t>( *cmd[1] );
        json_obj_t::const_iterator it_opts = opts.begin(), it_opts_end = opts.end();

        while ( it_opts != it_opts_end ) {
            if ( ( *it_opts ).first == "cm" ) {
                combine = boost::any_cast<bool>( *( *it_opts ).second );
            } else if ( ( *it_opts ).first == "ca" ) {
                combine_attrs = boost::any_cast<bool>( *( *it_opts ).second );
            } else if ( ( *it_opts ).first == "cs" ) {
                combine_style = boost::any_cast<bool>( *( *it_opts ).second );
            }

            ++it_opts;
        }

        for ( json_array_t::size_type cmd_size = cmd.size(), rng_i = 2; rng_i < cmd_size; ++rng_i ) {
            if ( cmd[rng_i]->type() != typeid( json_array_t ) ) {
                return fail_cmd( "cmd_set_cell_range", ERR_PARSING_FAILED, "command malformed" );
            }

            const json_array_t& rng = boost::any_cast<json_array_t>( *cmd[rng_i] );

            const json_array_t::size_type rng_size = rng.size();

            if ( rng_size < 5 ) {
                return fail_cmd( "cmd_set_cell_range", ERR_PARSING_FAILED, "command malformed" );
            }

            unsigned long x1 = boost::any_cast<int>( *rng[0] ),
                          y1 = boost::any_cast<int>( *rng[1] ),
                          x2 = boost::any_cast<int>( *rng[2] ),
                          y2 = boost::any_cast<int>( *rng[3] );

            if ( !transform_coords( x1, y1, x2, y2 ) ) {
                return fail_cmd( "cmd_set_cell_range", ERR_PARSING_FAILED, "check_range_coord: invalid coordinates" );
            }

            if ( rng_size == 5 ) {
                set_cell( boost::any_cast<json_obj_t>( *rng[4] ), sheet_range( sheet_point( y1, x1 ), sheet_point( y2, x2 ) ), combine, combine_attrs, combine_style );
                continue;
            }

            json_array_t::size_type cell_i = 4;

            for ( unsigned long x = x1, rng_len = ( x2 - x1 + 1 ) * ( y2 - y1 + 1 ), i = 0; i < rng_len; ++i ) {
                const json_obj_t& cell = boost::any_cast<json_obj_t>( *rng[cell_i] );

                set_cell( cell, sheet_range( sheet_point( y1, x ) ), combine, combine_attrs, combine_style );

                if ( ++cell_i >= rng_size ) {
                    cell_i = 4;
                }

                if ( ++x > x2 ) {
                    ++y1, x = x1;
                }
            }
        }

        m_result << std::string( "[true,\"\"]," );
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_set_cell_range", e );
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_clear( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_clear", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( cmd.size() < 2 ) {
        return fail_cmd( "cmd_clear", ERR_PARSING_FAILED, "command malformed" );
    }

    std::vector<bool> return_value_array;
    try {
        for ( json_array_t::size_type i_coords = 1; i_coords < cmd.size(); i_coords++ ) {
            if ( cmd[i_coords]->type() != typeid( json_array_t ) ) {
                return fail_cmd( "cmd_clear", ERR_PARSING_FAILED, "command malformed" );
            }

            const json_array_t& coords = boost::any_cast<json_array_t>( *cmd[i_coords] );

            if ( ! test_types<int, int, int, int, int>( 5, 'd', 0, coords ) ) {
                return fail_cmd( "cmd_clear", ERR_PARSING_FAILED, "command malformed" );
            }

            unsigned long clear_type  = boost::any_cast<int>( *coords[0] );
            sheet_range range( sheet_point( 0, 0 ) );

            if ( ! bind_rect( 1, coords, range ) ) {
                return fail_cmd( "cmd_clear", ERR_PARSING_FAILED, "check_range_coord: invalid coordinates" );
            }

            clear_cells_command ccc( *m_session_context, range, clear_type );
            m_session_context->undo_redo_log().execute( ccc );
            return_value_array.push_back( true );

        }

        m_result << std::string( "[true," ) <<  m_json_serializer( return_value_array ) << std::string( "]," );
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_clear", e );
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_copypaste( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_copypaste", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( cmd.size() < 2 ) {
        return fail_cmd( "cmd_copypaste", ERR_PARSING_FAILED, "command malformed" );
    }

    try {
        for ( json_array_t::size_type i_coords = 1; i_coords < cmd.size(); i_coords++ ) {
            if ( cmd[i_coords]->type() != typeid( json_array_t ) ) {
                return fail_cmd( "cmd_copypaste", ERR_PARSING_FAILED, "command malformed" );
            }

            const json_array_t& coords = boost::any_cast<json_array_t>( *cmd[i_coords] );

            if ( ! test_types<int, int, int, int, int, int, int, int>( 8, 'd', 0, coords ) ) {
                return fail_cmd( "cmd_copypaste", ERR_PARSING_FAILED, "command malformed" );
            }

            sheet_range copy_range( sheet_point( 0, 0 ) ) ;
            sheet_range paste_range( sheet_point( 0, 0 ) ) ;

            if ( ! bind_rect( 0, coords, copy_range ) ) {
                return fail_cmd( "cmd_copypaste", ERR_PARSING_FAILED, "check_range_coord: invalid coordinates" );
            }

            if ( ! bind_rect( 4, coords, paste_range ) ) {
                return fail_cmd( "cmd_copypaste", ERR_PARSING_FAILED, "check_range_coord: invalid coordinates" );
            }

            copy_range_command command_copy_range( *m_session_context, copy_range );
            command_copy_range.execute();

            paste_range_command command_paste_range( *m_session_context, paste_range, command_copy_range.value() );
            command_paste_range.execute();
        }

        m_result << std::string( "[true,\"\"]," );
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_copypaste", e );
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_copymovepaste( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_copymovepaste", ERR_INVALID_SESSION, "invalid session received" );
    }
    if ( cmd.size() < 2 ) {
        return fail_cmd( "cmd_copymovepaste", ERR_PARSING_FAILED, "command malformed" );
    }

    try {
        for ( json_array_t::size_type i_coords = 1; i_coords < cmd.size(); i_coords++ ) {
            if ( cmd[i_coords]->type() != typeid( json_array_t ) ) {
                return fail_cmd( "cmd_copymovepaste", ERR_PARSING_FAILED, "command malformed" );
            }

            const json_array_t& coords = boost::any_cast<json_array_t>( *cmd[i_coords] );

            if ( ! test_types<int, int, int, int, int, int, int, int>( 8, 'd' , 0, coords ) ) {
                return fail_cmd( "cmd_copymovepaste", ERR_PARSING_FAILED, "command malformed" );
            }

            sheet_range copy_range( sheet_point( 0, 0 ) ) ;
            sheet_range paste_range( sheet_point( 0, 0 ) ) ;

            if ( ! bind_rect( 0, coords, copy_range ) ) {
                return fail_cmd( "cmd_copymovepaste", ERR_PARSING_FAILED, "check_range_coord: invalid coordinates" );
            }

            if ( ! bind_rect( 4, coords, paste_range ) ) {
                return fail_cmd( "cmd_copymovepaste", ERR_PARSING_FAILED, "check_range_coord: invalid coordinates" );
            }

            copy_move_range_command command_copy( *m_session_context, copy_range );
            command_copy.execute();

            paste_range_command command_paste_range( *m_session_context, paste_range, command_copy.value() );
            command_paste_range.execute();
        }

        m_result << std::string( "[true,\"\"]," );
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_copymovepaste", e );
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_cutpaste ( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_cutpaste", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( cmd.size()  <  2 ) {
        return fail_cmd( "cmd_cutpaste", ERR_PARSING_FAILED, "command malformed" );
    }

    try {
        for ( json_array_t::size_type i_coords = 1; i_coords < cmd.size(); i_coords++ ) {
            if ( cmd[i_coords]->type() != typeid( json_array_t ) ) {
                return fail_cmd( "cmd_cutpaste", ERR_PARSING_FAILED, "command malformed" );
            }

            const json_array_t& coords = boost::any_cast<json_array_t>( *cmd[i_coords] );

            if ( ! test_types<int, int, int, int, int, int, int, int>( 8, 'd', 0, coords ) ) {
                return fail_cmd( "cmd_cutpaste", ERR_PARSING_FAILED, "command malformed" );
            }

            sheet_range cut_range( sheet_point( 0, 0 ) ) ;
            sheet_range paste_range( sheet_point( 0, 0 ) ) ;

            if ( ! bind_rect( 0, coords, cut_range ) ) {
                return fail_cmd( "cmd_cutpaste", ERR_PARSING_FAILED, "check_range_coord: invalid coordinates" );
            }

            if ( ! bind_rect( 4, coords, paste_range ) ) {
                return fail_cmd( "cmd_cutpaste", ERR_PARSING_FAILED, "check_range_coord: invalid coordinates" );
            }

            move_range_command command_move_range( *m_session_context, cut_range );
            command_move_range.execute();

            paste_range_command command_paste_range( *m_session_context,  paste_range, command_move_range.value() );
            command_paste_range.execute();
        }

        m_result << std::string( "[true,\"\"]," );
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_cutpaste", e );
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


bool CCmdHandler::cmd_insert_cells ( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_insert_cells", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( cmd.size() < 2 ) {
        return fail_cmd( "cmd_insert_cells", ERR_PARSING_FAILED, "command malformed" );
    }

    try {
        for ( json_array_t::size_type cmd_size = cmd.size(), i_rngs = 1; i_rngs < cmd_size; ++i_rngs ) {
            if ( cmd[i_rngs]->type() != typeid( json_array_t ) ) {
                return fail_cmd( "cmd_insert_cells", ERR_PARSING_FAILED, "command malformed" );
            }

            const json_array_t& rng = boost::any_cast<json_array_t>( *cmd[i_rngs] );

            if ( !test_types<int, int, int, int>( 4, 'l', 0, rng ) ) {
                return fail_cmd( "cmd_insert_cells", ERR_PARSING_FAILED, "command malformed" );
            }

            sheet_range rect( sheet_point( 0, 0 ) );

            if ( !bind_rect( 0, rng, rect ) ) {
                return fail_cmd( "cmd_insert_cells", ERR_PARSING_FAILED, "invalid coordinates" );
            }

            const json_array_t::size_type rng_size = rng.size();

            const insert_shift_direction::type shift_dir = rng_size > 4 && rng[4]->type() == typeid( int ) ? static_cast<insert_shift_direction::type>( boost::any_cast<int>( *rng[4] ) ) : insert_shift_direction::vertically;
            const copy_format_from::type fmt_copy_from = rng_size > 5 && rng[5]->type() == typeid( int ) ? static_cast<copy_format_from::type>( boost::any_cast<int>( *rng[5] ) ) : copy_format_from::left_or_above;

            insert_cells_command( *m_session_context, rect, shift_dir, fmt_copy_from ).execute();
        }

        m_result << std::string( "[true,\"\"]," );
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_insert_cells", e );
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_delete_cells ( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_delete_cells", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( cmd.size() < 2 ) {
        return fail_cmd( "cmd_delete_cells", ERR_PARSING_FAILED, "command malformed" );
    }

    try {
        for ( json_array_t::size_type cmd_size = cmd.size(), i_rngs = 1; i_rngs < cmd_size; ++i_rngs ) {
            if ( cmd[i_rngs]->type() != typeid( json_array_t ) ) {
                return fail_cmd( "cmd_delete_cells", ERR_PARSING_FAILED, "command malformed" );
            }

            const json_array_t& rng = boost::any_cast<json_array_t>( *cmd[i_rngs] );

            if ( !test_types<int, int, int, int>( 4, 'l', 0, rng ) ) {
                return fail_cmd( "cmd_delete_cells", ERR_PARSING_FAILED, "command malformed" );
            }

            sheet_range rect( sheet_point( 0, 0 ) );

            if ( !bind_rect( 0, rng, rect ) ) {
                return fail_cmd( "cmd_delete_cells", ERR_PARSING_FAILED, "invalid coordinates" );
            }

            const insert_shift_direction::type shift_dir = rng.size() > 4 && rng[4]->type() == typeid( int ) ? static_cast<insert_shift_direction::type>( boost::any_cast<int>( *rng[4] ) ) : insert_shift_direction::horizontally;

            delete_cells_command( *m_session_context, rect, shift_dir ).execute();
        }

        m_result << std::string( "[true,\"\"]," );
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_delete_cells", e );
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_insert_column( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_insert_column", ERR_INVALID_SESSION, "invalid session received" );
    }
    if ( cmd.size() < 2 ) {
        return fail_cmd( "cmd_insert_column", ERR_PARSING_FAILED, "command malformed" );
    }

    try {
        for ( json_array_t::size_type i_coords = 1; i_coords < cmd.size(); i_coords++ ) {
            if ( cmd[i_coords]->type() != typeid( json_array_t ) ) {
                return fail_cmd( "cmd_insert_column", ERR_PARSING_FAILED, "command malformed" );
            }

            const json_array_t& coords = boost::any_cast<json_array_t>( *cmd[i_coords] );

            if ( ! test_types<int, int>( 2, 'd', 0, coords ) ) {
                return fail_cmd( "cmd_insert_column", ERR_PARSING_FAILED, "command malformed" );
            }

            unsigned long column  = boost::any_cast<int>( *coords[0] );
            unsigned long column_count  = boost::any_cast<int>( *coords[1] );

            insert_column_command command( *m_session_context, column - 1, column_count );
            command.execute();
        }

        m_result << std::string( "[true,\"\"]," );
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_insert_column", e );
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_insert_row( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_insert_row", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( cmd.size() < 2 ) {
        return fail_cmd( "cmd_insert_row", ERR_PARSING_FAILED, "command malformed" );
    }

    try {
        for ( json_array_t::size_type i_coords = 1; i_coords < cmd.size(); i_coords++ ) {
            if ( cmd[i_coords]->type() != typeid( json_array_t ) ) {
                return fail_cmd( "cmd_insert_row", ERR_PARSING_FAILED, "command malformed" );
            }

            const json_array_t& coords = boost::any_cast<json_array_t>( *cmd[i_coords] );

            if ( ! test_types<int, int>( 2, 'd', 0, coords ) ) {
                return fail_cmd( "cmd_insert_row", ERR_PARSING_FAILED, "command malformed" );
            }

            unsigned long row  = boost::any_cast<int>( *coords[0] );
            unsigned long row_count  = boost::any_cast<int>( *coords[1] );

            insert_row_command command( *m_session_context, row - 1, row_count );
            command.execute();
        }

        m_result << std::string( "[true,\"\"]," );
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_insert_row", e );
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_delete_column( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_delete_column", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( cmd.size() < 2 ) {
        return fail_cmd( "cmd_delete_column", ERR_PARSING_FAILED, "command malformed" );
    }

    try {
        for ( json_array_t::size_type i_coords = 1; i_coords < cmd.size(); i_coords++ ) {
            if ( cmd[i_coords]->type() != typeid( json_array_t ) ) {
                return fail_cmd( "cmd_delete_column", ERR_PARSING_FAILED, "command malformed" );
            }

            const json_array_t& coords = boost::any_cast<json_array_t>( *cmd[i_coords] );

            if ( ! test_types<int, int>( 2, 'd', 0, coords ) ) {
                return fail_cmd( "cmd_delete_column", ERR_PARSING_FAILED, "command malformed" );
            }

            unsigned long column  = boost::any_cast<int>( *coords[0] );
            unsigned long column_count  = boost::any_cast<int>( *coords[1] );

            delete_column_command  command( *m_session_context, column - 1, column_count );
            command.execute();
        }

        m_result << std::string( "[true,\"\"]," );
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_delete_column", e );
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_delete_row( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_delete_row", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( cmd.size() < 2 ) {
        return fail_cmd( "cmd_delete_row", ERR_PARSING_FAILED, "command malformed" );
    }

    try {
        for ( json_array_t::size_type i_coords = 1; i_coords < cmd.size(); i_coords++ ) {
            if ( cmd[i_coords]->type() != typeid( json_array_t ) ) {
                return fail_cmd( "cmd_delete_row", ERR_PARSING_FAILED, "command malformed" );
            }

            const json_array_t& coords = boost::any_cast<json_array_t>( *cmd[i_coords] );

            if ( ! test_types<int, int>( 2, 'd' , 0, coords ) ) {
                return fail_cmd( "cmd_delete_row", ERR_PARSING_FAILED, "command malformed" );
            }

            unsigned long row  = boost::any_cast<int>( *coords[0] );
            unsigned long row_count  = boost::any_cast<int>( *coords[1] );

            delete_row_command  command( *m_session_context, row - 1, row_count );
            command.execute();
        }

        m_result << std::string( "[true,\"\"]," );
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_delete_row", e );
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_merge( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_merge", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( cmd.size() < 2 ) {
        return fail_cmd( "cmd_merge", ERR_PARSING_FAILED, "command malformed" );
    }

    try {
        for ( json_array_t::size_type i_coords = 1; i_coords < cmd.size(); i_coords++ ) {
            if ( cmd[i_coords]->type() != typeid( json_array_t ) ) {
                return fail_cmd( "cmd_merge", ERR_PARSING_FAILED, "command malformed" );
            }

            const json_array_t& coords = boost::any_cast<json_array_t>( *cmd[i_coords] );

            if ( ! test_types<int, int, int, int>( 4, 'd', 0, coords ) ) {
                return fail_cmd( "cmd_merge", ERR_PARSING_FAILED, "command malformed" );
            }

            sheet_range merge_range( sheet_point( 0, 0 ) );
            if ( ! bind_rect( 0, coords, merge_range ) ) {
                return fail_cmd( "cmd_merge", ERR_PARSING_FAILED, "check_range_coord: invalid coordinates" );
            }

            merge_cells_command command( *m_session_context, merge_range );
            m_session_context->undo_redo_log().execute( command );
        }

        m_result << std::string( "[true,\"\"]," );
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_merge", e );
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_unmerge( const json_array_t& cmd )
{
    if ( cmd.size() < 2 ) {
        return fail_cmd( "cmd_unmerge", ERR_PARSING_FAILED, "command malformed" );
    }

    try {
        for ( json_array_t::size_type i_coords = 1; i_coords < cmd.size(); i_coords++ ) {
            if ( cmd[i_coords]->type() != typeid( json_array_t ) ) {
                return fail_cmd( "cmd_unmerge", ERR_PARSING_FAILED, "command malformed" );
            }

            const json_array_t& coords = boost::any_cast<json_array_t>( *cmd[i_coords] );

            if ( ! test_types<int, int, int, int>( 4, 'd', 0, coords ) ) {
                return fail_cmd( "cmd_unmerge", ERR_PARSING_FAILED, "command malformed" );
            }

            sheet_range unmerge_range( sheet_point( 0, 0 ) );

            if ( ! bind_rect( 0, coords, unmerge_range ) ) {
                return fail_cmd( "cmd_unmerge", ERR_PARSING_FAILED, "check_range_coord: invalid coordinates" );
            }

            unmerge_cells_command command( *m_session_context, unmerge_range );
            m_session_context->undo_redo_log().execute( command );
        }

        m_result << std::string( "[true,\"\"]," );
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_unmerge", e );
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_cndfmt_set( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_cndfmt_set", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( ! test_types<std::string, json_obj_t >( 3, 'l', 1, cmd ) ) {
        return fail_cmd( "cmd_cndfmt_set", ERR_PARSING_FAILED, "command malformed" );
    }

    try {
        const std::string sheet_uuid = boost::any_cast<std::string>( *cmd[1] );

        shared_worksheet_type sheet;
        shared_workbook_type book;

        if ( sheet_uuid.empty() ) {
            sheet = m_session_context->selected().worksheet().lock();
        } else {
            book = m_session_context->selected().workbook().lock();

            if ( book ) {
                sheet = book->get( *m_session_context, boost::lexical_cast<uuid_type>( sheet_uuid ) );
            } else {
                return fail_cmd( "cmd_cndfmt_set", ERR_RUNTIME_ERROR, "no workbook is currently selected" );
            }
        }

        if ( ! sheet ) {
            return fail_cmd( "cmd_cndfmt_set", ERR_RUNTIME_ERROR, "no worksheet is currently selected" );
        }

        const json_array_t::size_type cmd_size = cmd.size();

        for ( json_array_t::size_type i = 2; i < cmd_size; ++i ) {

            if ( cmd[i]->type() != typeid( json_obj_t ) ) {
                return fail_cmd( "cmd_cndfmt_set", ERR_PARSING_FAILED, "command malformed" );
            }

            const json_obj_t& rule = boost::any_cast<json_obj_t >( *cmd[i] );
            json_obj_t::const_iterator it, rule_end = rule.end();

            set_conditional_format cf_format;


            // ranges
            it = rule.find( "ranges" );

            if ( it == rule_end ) {
                return fail_cmd( "cmd_cndfmt_set", ERR_PARSING_FAILED, "command malformed" );
            }

            const json_array_t& ranges = boost::any_cast<json_array_t>( *( it->second ) );
            const json_array_t::size_type ranges_size = ranges.size();

            for ( json_array_t::size_type j = 0; j < ranges_size; ++j ) {
                if ( ranges[j]->type() != typeid( json_array_t ) ) {
                    return fail_cmd( "cmd_cndfmt_set", ERR_PARSING_FAILED, "command malformed" );
                }

                const json_array_t& range = boost::any_cast<json_array_t>( *ranges[j] );

                if ( ! test_types<int, int, int, int >( 4, 'd', 0, range ) ) {
                    return fail_cmd( "cmd_cndfmt_set", ERR_PARSING_FAILED, "command malformed" );
                }

                sheet_range rect( sheet_point( 0, 0 ) );

                if ( ! bind_rect( 0, range, rect ) ) {
                    return fail_cmd( "cmd_cndfmt_set", ERR_PARSING_FAILED, "invalid coordinates" );
                }

                cf_format.selected_range( rect );
            }


            // rule
            it = rule.find( "rule" );

            if ( it == rule_end ) {
                return fail_cmd( "cmd_cndfmt_set", ERR_PARSING_FAILED, "command malformed" );
            }

            cf_format.rule( boost::any_cast<std::string>( *( it->second ) ) );


            // format
            it = rule.find( "format" );

            if ( it != rule_end ) {
                cf_format.format( boost::any_cast<std::string>( *( it->second ) ) );
            }


            // style
            it = rule.find( "style" );

            if ( it != rule_end ) {
                cf_format.style( boost::any_cast<std::string>( *( it->second ) ) );
            }


            // lock
            it = rule.find( "lock" );

            if ( it != rule_end ) {
                cf_format.unlock_cells ( ( boost::any_cast<bool>( *( it->second ) ) ) );
            }


            // border
            it = rule.find( "border" );

            if ( it != rule_end ) {
                const json_obj_t& border = boost::any_cast<json_obj_t >( *( it->second ) );
                json_obj_t::const_iterator border_end = border.end();

                // top
                it = border.find( "top" );

                if ( it != border_end ) {
                    cf_format.add_border( conditional_format_border_types::top, boost::any_cast<std::string>( *( it->second ) ) );
                }

                // bottom
                it = border.find( "bottom" );

                if ( it != border_end ) {
                    cf_format.add_border( conditional_format_border_types::bottom, boost::any_cast<std::string>( *( it->second ) ) );
                }

                // left
                it = border.find( "left" );

                if ( it != border_end ) {
                    cf_format.add_border( conditional_format_border_types::left, boost::any_cast<std::string>( *( it->second ) ) );
                }

                // right
                it = border.find( "right" );

                if ( it != border_end ) {
                    cf_format.add_border( conditional_format_border_types::right, boost::any_cast<std::string>( *( it->second ) ) );
                }
            }


            // operands
            it = rule.find( "operands" );

            if ( it != rule_end ) {
                const json_array_t& operands = boost::any_cast<json_array_t>( *( it->second ) );

                variant variant_array = variant( variant::type_array );
                variant::variant_array_type& array = variant_array.array();

                json_array_t::const_iterator operands_it = operands.begin(), operands_end = operands.end();

                while ( operands_it != operands_end ) {
                    array.push_back( json2Value( *operands_it ) );
                    ++operands_it;
                }

                cf_format.operands( variant_array );
            }


            // set or update
            it = rule.find( "id" );

            if ( it == rule_end ) {
                set_conditional_format_command command( *m_session_context, cf_format, sheet );
                command.execute();
                //m_session_context->handle_command(command);
            } else if ( it->second->type() != typeid( int ) ) {
                return fail_cmd( "cmd_cndfmt_set", ERR_PARSING_FAILED, "command malformed" );
            } else {
                const long id = boost::any_cast<int>( *( it->second ) );

                update_conditional_format_command command( *m_session_context, id, cf_format, sheet );
                command.execute();
                //m_session_context->handle_command(command);
            }
        }

        m_result << std::string( "[true,true]," );

    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_cndfmt_set", e );
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_cndfmt_get( const json_array_t& cmd )
{

    if ( m_logged_out ) {
        return fail_cmd( "cmd_cndfmt_get", ERR_INVALID_SESSION, "invalid session received" );
    }


    try {
        shared_worksheet_type ws;
        shared_workbook_type wb ;

        sheet_range::rectangles_type  rect_list;

        if ( cmd.size() > 1 ) {
            if ( cmd[1]->type() != typeid( std::string ) ) {
                return fail_cmd( "cmd_cndfmt_get", ERR_PARSING_FAILED, "command malformed" );
            }

            const std::string uuid_string = boost::any_cast<std::string>( *cmd[1] );

            if ( !uuid_string.empty() ) {
                wb = m_session_context->selected().workbook().lock();
                if ( wb ) {
                    ws = wb->get( *m_session_context, boost::lexical_cast<uuid_type>( uuid_string ) );
                } else {
                    return fail_cmd( "cmd_cndfmt_get", ERR_RUNTIME_ERROR, "no workbook is currently selected" );
                }
            } else {
                ws = m_session_context->selected().worksheet().lock();
            }
        } else {
            ws = m_session_context->selected().worksheet().lock();
        }

        if ( ! ws ) {
            return fail_cmd( "cmd_cndfmt_get", ERR_RUNTIME_ERROR, "no worksheet is currently selected" );
        }

        if ( cmd.size() > 2 ) {
            if ( cmd[2]->type() != typeid( json_array_t ) ) {
                return fail_cmd( "cmd_cndfmt_get", ERR_PARSING_FAILED, "command malformed" );
            }

            const json_array_t& coords_array = boost::any_cast<json_array_t>( *cmd[2] );

            for ( json_array_t::size_type i_coords = 0; i_coords < coords_array.size(); i_coords++ ) {
                if ( coords_array[i_coords]->type() != typeid( json_array_t ) ) {
                    return fail_cmd( "cmd_cndfmt_get", ERR_PARSING_FAILED, "command malformed" );
                }

                const json_array_t& coords = boost::any_cast<json_array_t>( *coords_array[i_coords] );

                if ( ! test_types<int, int, int, int>( 4, 'd', 0, coords ) ) {
                    return fail_cmd( "cmd_cndfmt_get", ERR_PARSING_FAILED, "command malformed" );
                }

                sheet_range range( sheet_point( 0, 0 ) );

                if ( ! bind_rect( 0, coords, range ) ) {
                    return fail_cmd( "cmd_cndfmt_get", ERR_PARSING_FAILED, "check_range_coord: invalid coordinates" );
                }

                rect_list.push_back( range );
            }

        }

        // call commands
        if ( !rect_list.empty() ) {
            std::vector<get_conditionalformat_list_type> return_value_array;
            get_conditional_format_command get_command( *m_session_context, ws, rect_list );
            return_value_array.push_back( execute_fetch( get_command ) );
            m_result << std::string( "[true," ) <<  m_json_serializer( return_value_array ) << std::string( "]," );
        } else {
            std::vector<get_conditionalformat_list_type> return_value_array;
            get_all_conditional_formats_command get_all_command( *m_session_context, ws );
            return_value_array.push_back( execute_fetch( get_all_command ) );
            m_result << std::string( "[true," ) <<  m_json_serializer( return_value_array ) << std::string( "]," );
        }

    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_cndfmt_get", e );
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_cndfmt_move( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_cndfmt_move", ERR_INVALID_SESSION, "invalid session received" );
    }

    const json_array_t::size_type cmd_size = cmd.size();

    if ( ! test_types<std::string, json_array_t, int, int>( 5, 'l', 1, cmd ) || !( cmd_size % 2 ) ) {
        return fail_cmd( "cmd_cndfmt_move", ERR_PARSING_FAILED, "command malformed" );
    }

    try {
        const std::string sheet_uuid = boost::any_cast<std::string>( *cmd[1] );

        shared_worksheet_type sheet;
        shared_workbook_type book;

        if ( sheet_uuid.empty() ) {
            sheet = m_session_context->selected().worksheet().lock();
        } else {
            book = m_session_context->selected().workbook().lock();

            if ( book ) {
                sheet = book->get( *m_session_context, boost::lexical_cast<uuid_type>( sheet_uuid ) );
            } else {
                return fail_cmd( "cmd_cndfmt_move", ERR_RUNTIME_ERROR, "no workbook is currently selected" );
            }
        }

        if ( ! sheet ) {
            return fail_cmd( "cmd_cndfmt_move", ERR_RUNTIME_ERROR, "no worksheet is currently selected" );
        }

        const json_array_t& ranges = boost::any_cast<json_array_t>( *cmd[2] );
        const json_array_t::size_type ranges_size = ranges.size();

        sheet_range::rectangles_type rects;

        for ( json_array_t::size_type i = 0; i < ranges_size; ++i ) {
            if ( ranges[i]->type() != typeid( json_array_t ) ) {
                return fail_cmd( "cmd_cndfmt_move", ERR_PARSING_FAILED, "command malformed" );
            }

            const json_array_t& range = boost::any_cast<json_array_t>( *ranges[i] );

            if ( ! test_types<int, int, int, int>( 4, 'd', 0, range ) ) {
                return fail_cmd( "cmd_cndfmt_move", ERR_PARSING_FAILED, "command malformed" );
            }

            sheet_range rect( sheet_point( 0, 0 ) );

            if ( ! bind_rect( 0, range, rect ) ) {
                return fail_cmd( "cmd_cndfmt_move", ERR_PARSING_FAILED, "invalid coordinates" );
            }

            rects.push_back( rect );
        }

        if ( rects.empty() ) {
            return fail_cmd( "cmd_cndfmt_move", ERR_PARSING_FAILED, "command malformed" );
        }

        for ( json_array_t::size_type i = 3; i < cmd_size; ++i ) {
            if ( cmd[i]->type() != typeid( int ) ) {
                return fail_cmd( "cmd_cndfmt_move", ERR_PARSING_FAILED, "command malformed" );
            }

            const long rule_id = boost::any_cast<int>( *cmd[i] );

            if ( cmd[++i]->type() != typeid( int ) ) {
                return fail_cmd( "cmd_cndfmt_move", ERR_PARSING_FAILED, "command malformed" );
            }

            const int delta = boost::any_cast<int>( *cmd[i] );

            move_conditional_format_rank_command command( *m_session_context, rule_id, delta, sheet, rects );
            command.execute();
        }

        m_result << std::string( "[true,true]," );

    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_cndfmt_move", e );
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_cndfmt_delete( const json_array_t& cmd )
{

    if ( m_logged_out ) {
        return fail_cmd( "cmd_cndfmt_delete", ERR_INVALID_SESSION, "invalid session received" );
    }

    try {
        sheet_range::rectangles_type  rect_list;
        shared_worksheet_type ws;
        shared_workbook_type wb;

        if ( cmd.size() > 1 ) {
            if ( cmd[1]->type() != typeid( std::string ) ) {
                return fail_cmd( "cmd_cndfmt_delete", ERR_PARSING_FAILED, "command malformed" );
            }
            const std::string uuid_string = boost::any_cast<std::string>( *cmd[1] );
            if ( !uuid_string.empty() ) {
                wb =  m_session_context->selected().workbook().lock();
                if ( wb ) {
                    ws = wb->get( *m_session_context, boost::lexical_cast<uuid_type>( uuid_string ) );
                } else {
                    return fail_cmd( "cmd_cndfmt_delete", ERR_RUNTIME_ERROR, "no workbook is currently selected" );
                }
            } else {
                ws = m_session_context->selected().worksheet().lock();
            }
        } else {
            ws =  m_session_context->selected().worksheet().lock();
        }

        if ( ! ws ) {
            return fail_cmd( "cmd_cndfmt_delete", ERR_RUNTIME_ERROR, "no worksheet is currently selected" );
        }

        if ( cmd.size() > 2 ) {
            if ( cmd[2]->type() != typeid( json_array_t ) ) {
                return fail_cmd( "cmd_cndfmt_delete", ERR_PARSING_FAILED, "command malformed" );
            }

            const json_array_t& coords_array = boost::any_cast<json_array_t>( *cmd[2] );

            for ( json_array_t::size_type i_coords = 0; i_coords < coords_array.size(); i_coords++ ) {
                if ( coords_array[i_coords]->type() != typeid( json_array_t ) ) {
                    return fail_cmd( "cmd_cndfmt_delete", ERR_PARSING_FAILED, "command malformed" );
                }

                const json_array_t& coords = boost::any_cast<json_array_t>( *coords_array[i_coords] );

                if ( ! test_types<int, int, int, int>( 4, 'd', 0, coords ) ) {
                    return fail_cmd( "cmd_cndfmt_delete", ERR_PARSING_FAILED, "command malformed" );
                }

                sheet_range range( sheet_point( 0, 0 ) );
                if ( ! bind_rect( 0, coords, range ) ) {
                    return fail_cmd( "cmd_cndfmt_delete", ERR_PARSING_FAILED, "check_range_coord: invalid coordinates" );
                }

                rect_list.push_back( range );
            }

        }
        std::list< boost::uint_fast32_t > new_ids;
        if ( cmd.size() > 3 ) {
            if ( cmd[3]->type() != typeid( json_array_t ) ) {
                return fail_cmd( "cmd_cndfmt_delete", ERR_PARSING_FAILED, "command malformed" );
            }
            const json_array_t& ids_array = boost::any_cast<json_array_t>( *cmd[3] );
            for ( json_array_t::size_type i_ids = 0; i_ids < ids_array.size(); i_ids++ ) {
                if ( ids_array[i_ids]->type() != typeid( int ) ) {
                    return fail_cmd( "cmd_cndfmt_delete", ERR_PARSING_FAILED, "command malformed" );
                }

                unsigned int x1  = boost::any_cast<int>( *ids_array[i_ids] );
                new_ids.push_back( x1 );
            }
        }

        remove_conditional_format_command delete_command( *m_session_context, ws, rect_list, new_ids );
        delete_command.execute();
        m_result << std::string( "[true,true]," );

    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_cndfmt_delete", e );
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_mark ( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_mark", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( cmd.size()  !=  1 ) {
        return fail_cmd( "cmd_mark", ERR_PARSING_FAILED, "command malformed" );
    }

    // try {
    // m_session_context->mark();
    m_result << std::string( "[true,\"\"]," );
    //     } catch ( const std::exception& e ) {
    //         return fail_cmd( "cmd_mark", e );
    //     }

    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_lock ( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_lock", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( cmd.size()  <  3 ) {
        return fail_cmd( "cmd_lock", ERR_PARSING_FAILED, "command malformed" );
    }

    try {
        for ( json_array_t::size_type i_coords = 1; i_coords < cmd.size(); i_coords += 2 ) {
            if ( cmd[i_coords]->type() != typeid( json_array_t ) ) {
                return fail_cmd( "cmd_lock", ERR_PARSING_FAILED, "command malformed" );
            }

            if ( cmd[i_coords+1]->type() != typeid( bool ) ) {
                return fail_cmd( "cmd_lock", ERR_PARSING_FAILED, "command malformed" );
            }

            const json_array_t& coords = boost::any_cast<json_array_t>( *cmd[i_coords] );
            const bool type = boost::any_cast<bool>( *cmd[i_coords+1] );

            if ( ! test_types<int, int, int, int>( 4, 'd', 0, coords ) ) {
                return fail_cmd( "cmd_lock", ERR_PARSING_FAILED, "command malformed" );
            }

            sheet_range range( sheet_point( 0, 0 ) ) ;

            if ( ! bind_rect( 0, coords, range ) ) {
                return fail_cmd( "cmd_lock", ERR_PARSING_FAILED, "check_range_coord: invalid coordinates" );
            }

            set_cell_lock_command command( *m_session_context, range, type );
            command.execute();
        }

        m_result << std::string( "[true,\"\"]," );
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_lock", e );
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_wss_active_objects_select( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_wss_active_objects_select", ERR_INVALID_SESSION, "invalid session received" );
    }


    if ( ! test_types<int>( 2, 'd', 1, cmd ) ) {
        return fail_cmd( "cmd_wss_active_objects_select", ERR_PARSING_FAILED, "command malformed" );
    }

    try {
        unsigned long query_type  = boost::any_cast<int>( *cmd[1] );

        switch ( query_type ) {
            case 0: {
                const shared_application_type& application_object = m_session_context->selected().application();
                if ( application_object ) {
                    m_result << std::string( "[true," ) << m_json_serializer( boost::lexical_cast<std::string>( application_object->uuid() ) );
                } else {
                    m_result << std::string( "[false" );
                }
                m_result << std::string( "]," );
            }
            break;
            case 1: {
                shared_workbook_type workbook_object = m_session_context->selected().workbook().lock();
                if ( workbook_object ) {
                    m_result << std::string( "[true," ) << m_json_serializer( boost::lexical_cast<std::string>( workbook_object->uuid() ) );
                } else {
                    m_result << std::string( "[false" );
                }
                m_result << std::string( "]," );
            }
            break;
            case 2: {
                shared_worksheet_type worksheet_object = m_session_context->selected().worksheet().lock();
                if ( worksheet_object ) {
                    m_result << std::string( "[true," ) << m_json_serializer( boost::lexical_cast<std::string>( worksheet_object->uuid() ) );
                } else {
                    m_result << std::string( "[false" );
                }
                m_result << std::string( "]," );
            }
            break;
            default:
                return fail_cmd( "cmd_wss_active_objects_select", ERR_PARSING_FAILED, "query_type has to be tristate" );
                break;
        }

    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_wss_active_objects_select", e );
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_trigger_exten_event ( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_trigger_exten_event", ERR_INVALID_SESSION, "invalid session received" );
    }

    json_array_t::size_type cmd_len = cmd.size();

    if ( cmd_len < 2 ) {
        return fail_cmd( "cmd_trigger_exten_event", ERR_PARSING_FAILED, "command malformed" );
    }

    try {
        std::string exten_name = boost::any_cast<std::string>( *cmd[1] );
        variant::variant_array_type event_data;

        for ( json_array_t::size_type idx = 2; idx < cmd_len; ++idx ) {
            event_data.push_back( json2Value( cmd[idx] ) );
        }

        trigger_extension_module_command command( *m_session_context, exten_name, event_data );
        m_result << std::string( "[true," ) << m_json_serializer( execute_fetch( command ) ) << std::string( "]," );
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_trigger_exten_event", e );
    }

    return true;
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_execute_macro( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_execute_macro", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( !test_types<std::string, std::string, std::string, json_array_t>( 5, 'l', 1, cmd ) ) {
        return fail_cmd( "cmd_execute_macro", ERR_PARSING_FAILED, "command malformed" );
    }

    try {
        variant::sparse_array_type event_data;

        // execute file
        event_data.push_back( 1.0 );
        // file name
        event_data.push_back( boost::any_cast<std::string>( *cmd[2] ) );
        // function name
        event_data.push_back( boost::any_cast<std::string>( *cmd[3] ) );
        // active selection
        event_data.push_back( cmd.size() > 5 && cmd[5]->type() == typeid( std::string ) ? boost::any_cast<std::string>( *cmd[5] ) : "" );
        // function params
        event_data.push_back( ~cmd[4] );

        trigger_extension_module_command command( *m_session_context, "php_macro_engine", event_data );
        m_result << std::string( "[true," ) << m_json_serializer( execute_fetch( command ) ) << std::string( "]," );

        // calculate the active sheet prior executing the macro
        //const sheet_range& sr =  m_session_context->selected().range();
        //m_session_context->selected().worksheet().lock()->range( sr ).value( *m_session_context );

    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_execute_macro", e );
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_workbook_list_ex( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_workbook_list_ex", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( cmd.size() != 1 ) {
        return fail_cmd( "cmd_workbook_list_ex", ERR_PARSING_FAILED, "command malformed" );
    }
    std::vector< boost::tuple< std::string, std::string, std::string, std::string > > id_name_mapping;
    try {
        const shared_application_type& application_object = m_session_context->selected().application();
        if ( application_object ) {
            m_result << std::string( "[true," ) << m_json_serializer( application_object->list_workbooks() ) << std::string( "]," );
        } else {
            m_result << std::string( "[false,\"\"]," );
        }
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_workbook_list_ex", e );
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_book_change_metadata ( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_book_change_metadata", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( cmd.size() < 2 || cmd[1]->type() != typeid( std::string ) ) {
        return fail_cmd( "cmd_book_change_metadata", ERR_PARSING_FAILED, "command malformed" );
    }

    try {
        const std::string meta_data = boost::any_cast<std::string>( *cmd[1] ),
                          book_uuid = cmd.size() > 2 && cmd[2]->type() == typeid( std::string ) ? boost::any_cast<std::string>( *cmd[2] ) : "";
        shared_workbook_type wb;
        if ( book_uuid.empty() ) {
            wb = m_session_context->selected().workbook().lock();
        } else {
            const shared_application_type& app = m_session_context->selected().application();
            if ( app ) {
                wb = app->get( *m_session_context, boost::lexical_cast<uuid_type>( book_uuid ) );
            }
        }

        if ( !wb ) {
            throw invalid_workbook_exception();
        }
        wb->data_string( meta_data );

        m_result << std::string( "[true]," );
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_book_change_metadata", e );
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_move_worksheet( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_move_worksheet", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( ! test_types<std::string, std::string>( 4, 'g', 1, cmd ) ) {
        return fail_cmd( "cmd_move_worksheet", ERR_PARSING_FAILED, "command malformed" );
    }

    try {
        std::string ws_id = boost::any_cast<std::string>( *cmd[1] );
        std::string next_ws_id = boost::any_cast<std::string>( *cmd[2] );
        std::string target_wb_id = "";

        if ( cmd.size() == 4 ) {
            if ( cmd[3]->type() != typeid( std::string ) ) {
                return fail_cmd( "cmd_move_worksheet", ERR_PARSING_FAILED, "command malformed" );
            }

            target_wb_id  = boost::any_cast<std::string>( *cmd[3] );
        }

        move_worksheet_command command( *m_session_context, ws_id, next_ws_id, target_wb_id );
        m_result << std::string( "[true," ) << m_json_serializer( execute_fetch( command ) ) << std::string( "]," );
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_move_worksheet", e );
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_copy_worksheet( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_copy_worksheet", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( ! test_types<std::string, std::string>( 4, 'g', 1, cmd ) ) {
        return fail_cmd( "cmd_copy_worksheet", ERR_PARSING_FAILED, "command malformed" );
    }

    try {
        std::string ws_id = boost::any_cast<std::string>( *cmd[1] );
        std::string next_ws_id = boost::any_cast<std::string>( *cmd[2] );
        std::string target_wb_id = "";

        if ( cmd.size() == 4 ) {
            if ( cmd[3]->type() != typeid( std::string ) ) {
                return fail_cmd( "cmd_copy_worksheet", ERR_PARSING_FAILED, "command malformed" );
            }

            target_wb_id  = boost::any_cast<std::string>( *cmd[3] );
        }

        copy_worksheet_command command( *m_session_context, ws_id, next_ws_id, target_wb_id );
        m_result << std::string( "[true," ) << m_json_serializer( execute_fetch( command ) ) << std::string( "]," );
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_copy_worksheet", e );
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_add_clone_worksheet( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_add_clone_worksheet", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( ! test_types<std::string>( 2, 'g', 1, cmd ) ) {
        return fail_cmd( "cmd_add_clone_worksheet", ERR_PARSING_FAILED, "command malformed" );
    }

    try {
        //std::string name  = boost::any_cast<std::string>( *cmd[1] );

        //TODO we don't need a name for cloned sheets anymore
        clone_worksheet_command command( *m_session_context/*, name*/ );
        m_result << std::string( "[true," ) << m_json_serializer( execute_fetch( command ) ) << std::string( "]," );
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_add_clone_worksheet", e );
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_remove_clone_worksheet( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_remove_clone_worksheet", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( ! test_types<std::string>( 2, 'g', 1, cmd ) ) {
        return fail_cmd( "cmd_remove_clone_worksheet", ERR_PARSING_FAILED, "command malformed" );
    }

    try {
        const uuid_type id  = boost::lexical_cast<uuid_type>( boost::any_cast<std::string>( *cmd[1] ) );

        remove_clone_worksheet_command( *m_session_context, id ).execute();
        m_result << std::string( "[true,\"\"]," );
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_remove_clone_worksheet", e );
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_names_exists( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_names_exists", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( cmd.size() < 2 ) {
        return fail_cmd( "cmd_names_exists", ERR_PARSING_FAILED, "command malformed" );
    }

    std::vector<bool> return_value_array;
    return_value_array.reserve( cmd.size() );

    shared_workbook_type wb = m_session_context->selected().workbook().lock();

    if ( !wb ) {
        return fail_cmd( "cmd_names_exists", 0, "no workbook selected" );
    }
    const i_named_formula_manager& name_manager = wb->named_formulas();
    try {
        for ( json_array_t::size_type i_cmd = 1; i_cmd < cmd.size(); i_cmd++ ) {
            if ( cmd[i_cmd]->type() != typeid( json_array_t ) ) {
                return fail_cmd( "cmd_names_exists", ERR_PARSING_FAILED, "command malformed" );
            }

            const json_array_t& names_scopes = boost::any_cast<json_array_t>( *cmd[i_cmd] );

            if ( ! test_types<std::string, std::string>( 2, 'd', 0, names_scopes ) ) {
                return fail_cmd( "cmd_names_exists", ERR_PARSING_FAILED, "command malformed" );
            }

            const std::string scope_str = boost::any_cast<std::string>( *names_scopes[1] );
            const named_formula_identifier nf_identifier(
                boost::any_cast<std::string>( *names_scopes[0] ),
                scope_str.empty() ? boost::uuids::nil_uuid() : boost::lexical_cast<uuid_type>( scope_str )
            );
            return_value_array.push_back( name_manager.exists( nf_identifier ) );
        }
        m_result << std::string( "[true," ) <<  m_json_serializer( return_value_array ) << std::string( "]," );
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_names_exists", e );
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_get_unlckd_ranges ( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_get_unlckd_ranges", ERR_INVALID_SESSION, "invalid session received" );
    }

    try {
        get_cell_lock_list_command command( *m_session_context );
        m_result << std::string( "[true," ) << m_json_serializer( execute_fetch( command ), JSONSerializer::JsonEncoding::POINT_TRANSFORM_COORD ) << std::string( "]," );
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_get_unlckd_ranges", e );
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_begin_calc_context ( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_begin_calc_context", ERR_INVALID_SESSION, "invalid session received" );
    }

    try {
        const bool clear_cache = cmd.size() > 1 && cmd[1]->type() == typeid( bool ) ? boost::any_cast<bool>( *cmd[1] ) : true;


        m_session_context->begin_calculation( clear_cache );

        m_result << std::string( "[true,\"\"]," );
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_begin_calc_context", e );
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CCmdHandler::cmd_end_calc_context ( const json_array_t& cmd )
{
    if ( m_logged_out ) {
        return fail_cmd( "cmd_end_calc_contex", ERR_INVALID_SESSION, "invalid session received" );
    }

    try {
        m_session_context->end_calculation();

        m_result << std::string( "[true,\"\"]," );
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_end_calc_contex", e );
    }

    return true;
}


bool CCmdHandler::cmd_get_workbook_version ( const json_array_t& cmd )
{

    if ( m_logged_out ) {
        return fail_cmd( "cmd_get_workbook_version", ERR_INVALID_SESSION, "invalid session received" );
    }

    if ( ! test_types<std::string>( 2, 'e', 1, cmd ) ) {
        return fail_cmd( "cmd_get_workbook_version", ERR_PARSING_FAILED, "command malformed" );
    }

    try {
        const uuid_type id  = boost::lexical_cast<uuid_type>( boost::any_cast<std::string>( *cmd[1] ) );

        get_workbook_version_command command( *m_session_context, id );
        m_result << std::string( "[true,\"" ) + execute_fetch( command ) + "\"],";
    } catch ( const std::exception& e ) {
        return fail_cmd( "cmd_get_workbook_version", e );
    }
    return true;

}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

template< class T_1 > inline bool CCmdHandler::test_types( json_array_t::size_type _size, char flag, int offset,  const json_array_t& cmd )
{
    if ( flag == 'l' && cmd.size() < _size ) {
        return false;
    } else if ( flag == 'e' && cmd.size() == _size ) {
        return false;
    } else if ( flag == 'g' && cmd.size() > _size ) {
        return false;
    } else if ( flag == 'd' && cmd.size() != _size ) {
        return false;
    } else if ( cmd[ 0 + offset ]->type()  !=  typeid( T_1 ) ) {
        return false;
    }

    return true;
}

template< class T_1, class T_2 > inline bool CCmdHandler::test_types( json_array_t::size_type _size, char flag, int offset,  const json_array_t& cmd )
{
    return ( test_types<T_1>( _size, flag, offset, cmd ) ) ? ! ( cmd[ 1 + offset ]->type()  !=  typeid( T_2 ) ) : false;
}

template< class T_1, class T_2 , class T_3 > inline bool CCmdHandler::test_types( json_array_t::size_type _size, char flag, int offset, const json_array_t& cmd )
{
    return ( test_types<T_1, T_2>( _size, flag, offset, cmd ) ) ? ! ( cmd[ 2 + offset ]->type()  !=  typeid( T_3 ) ) : false;
}

template< class T_1, class T_2 , class T_3,  class T_4 > inline bool CCmdHandler::test_types( json_array_t::size_type _size, char flag, int offset, const json_array_t& cmd )
{
    return ( test_types<T_1, T_2, T_3>( _size, flag, offset, cmd ) ) ? ! ( cmd[ 3 + offset ]->type()  !=  typeid( T_4 ) ) : false;
}

template< class T_1, class T_2 , class T_3,  class T_4,  class T_5 > inline bool CCmdHandler::test_types( json_array_t::size_type _size, char flag, int offset, const json_array_t& cmd )
{
    return ( test_types<T_1, T_2, T_3, T_4>( _size, flag, offset, cmd ) ) ? ! ( cmd[ 4 + offset ]->type()  !=  typeid( T_5 ) ) : false;
}

template< class T_1, class T_2 , class T_3,  class T_4,  class T_5,  class T_6 > inline bool CCmdHandler::test_types( json_array_t::size_type _size, char flag, int offset, const json_array_t& cmd )
{
    return ( test_types<T_1, T_2, T_3, T_4, T_5>( _size, flag, offset, cmd ) ) ? ! ( cmd[ 5 + offset ]->type()  !=  typeid( T_6 ) ) : false;
}

template< class T_1, class T_2 , class T_3,  class T_4,  class T_5,  class T_6,  class T_7,  class T_8   > inline bool CCmdHandler::test_types( json_array_t::size_type _size, char flag, int offset, const json_array_t& cmd )
{
    if ( ! test_types<T_1, T_2, T_3, T_4, T_5, T_6>( _size, flag, offset, cmd ) ) {
        return false;
    } else if ( cmd[ 6 + offset ]->type()  !=  typeid( T_7 ) ) {
        return false;
    } else if ( cmd[ 7 + offset ]->type()  !=  typeid( T_8 ) ) {
        return false;
    }

    return true;
}
