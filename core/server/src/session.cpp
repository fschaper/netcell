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
 *  Florian Schaper <florian.schaper@jedox.com>
 */

#include "precompiled_header.hpp"
#include "wss/session.hpp"
#include "wss/session_sheet_map.hpp"
#include "wss/server.hpp"
#include "wss/storage_rotation.hpp"
#include "wss/scoped_neutral_locale_enforcer.hpp"
#include "wss/scoped_selection_state.hpp"
#include "wss/application.hpp"
#include "auto_save_filesystem.hpp"
#include "wss/i_export_filter.hpp"
#include "core_logging.hpp"

#ifdef _DEBUG
#include "core_logging.hpp"
#include "named_formula_dependency_wrapper.hpp"
#include "wss/free_formula.hpp"
#include "free_formula_impl.hpp"
#include "wss/named_formula_reference.hpp"
#include "named_formula.hpp"
#endif

#if __GNUC__== 4 && __GNUC_MINOR__== 4
uuid_type session_create_uuid()
#else
inline uuid_type session_create_uuid()
#endif
{
    static boost::uuids::random_generator gen;
    return gen();
}

session::session( const ::locale& l, const std::string& username, const std::string password, const group_set_type& groups )
    : m_locale( l )
    , m_uuid( session_create_uuid() )
    , m_session_sheets( new session_sheet_map() )
    , m_username( username )
    , m_password( password )
    , m_groups( groups )
    , m_dont_clear_caches( false )
    , m_is_loading( false )
    , m_calculation_settings( NULL )
{
    m_user_return_format.reset( new user_return_format( *this ) );
    m_transaction.reset( new transaction_wrapper( *this ) );
}

session::~session()
{
    m_calculation_cache.clear( false );
    if ( server::instance().current_state() == server::state::running && m_selected_objects.application() ) {
        server::instance().remove( m_selected_objects.application()->uuid() );
    }
}


shared_session_type session::create( const ::locale& l, const std::string& username, const std::string password, const group_set_type& groups )
{
    const shared_session_type& shared_session = boost::make_shared<session>( l, username, password, groups );
    shared_session->associate_with_current_thread();
    return shared_session;
}

session* session::thread_session()
{
    return m_current_session.get() ? *m_current_session.get() : NULL;
}

const std::string& session::username() const
{
    return m_username;
}

const std::string& session::password() const
{
    return m_password;
}

const group_set_type& session::groups() const
{
    return m_groups;
}

const ::locale& session::locale() const
{
    return m_locale;
}

void session::locale( const ::locale& l )
{
    m_locale = l;
}

selection_state& session::selected()
{
    return m_selected_objects;
}

const selection_state& session::selected() const
{
    return m_selected_objects;
}

void session::selected( const selection_state& s )
{
    m_selected_objects = s;
}

const uuid_type& session::uuid() const
{
    return m_uuid;
}

::clipboard& session::clipboard()
{
    return m_clipboard;
}

variable_store& session::variable()
{
    return m_variable_store;
}

session_sheet_map& session::session_sheets()
{
    return *m_session_sheets;
}

void session::revitalize()
{
    static session_handler& sh = server::instance().session_handler();
    m_timeout = boost::posix_time::second_clock::local_time() + sh.session_timeout();
}

bool session::has_timed_out() const
{
    static session_handler& sh = server::instance().session_handler();
    if ( sh.session_timeout() == boost::posix_time::seconds( 0 ) ) {
        return false;
    }
    return boost::posix_time::second_clock::local_time() > m_timeout;
}

arbitrary_storage& session::storage()
{
    return m_arbitrary_storage;
}

transaction_wrapper& session::undo_redo_log()
{
    return *m_transaction;
}

void session::associate_with_current_thread()
{
    m_current_session.reset( new session*( this ) );
}

user_return_format& session::user_format()
{
    return *m_user_return_format;
}

broken_evaluation_dependencies& session::broken_dependencies()
{
    return m_broken_evaluation_dependencies;
}

void session::begin_calculation( const bool clear_one_more_time /*= true */ )
{
#ifdef _DEBUG
    LOG_CORE_DEBUG( "><><><> free_formula: " << free_formula::m_counter );
    LOG_CORE_DEBUG( "><><><> free_formula_impl: " << free_formula_impl::m_counter );
    LOG_CORE_DEBUG( "><><><> named_formula: " << named_formula::m_counter );
    LOG_CORE_DEBUG( "><><><> named_formula_dependency_wrapper: " << named_formula_dependency_wrapper::m_counter );
    LOG_CORE_DEBUG( "><><><> named_formula_reference: " << named_formula_reference::m_counter );
#endif
    if ( clear_one_more_time ) {
        m_calculation_cache.clear( false );
        m_palo_connection_cache.clear_pinged_and_unreachable_cache();
    }
    m_dont_clear_caches = true;
}

void session::end_calculation()
{
    m_dont_clear_caches = false;
}

void session::autosave()
{
    if ( !m_selected_objects.application()  ) {
        return;
    }

    file_rotation rotation;

    scoped_selection_state          sel_state( *this );
    scoped_neutral_locale_enforcer  neutral_session( *this );

    try {
        foreach( const shared_workbook_type & wb, m_selected_objects.application()->locking_iterator() ) {

            if ( !wb->is_temp() && wb->has_changes_autosave() ) {
                LOG_CORE_INFO( "auto-saving Workbook " << wb->name() << " for user " << username() );
                std::string file_name = wb->path().string() + "." + m_username + "." + boost::lexical_cast< std::string >( m_uuid );

                rotation.rotate( file_name  );

                server::instance().filters().get_export_filter( "wss" )->do_export( *this, *wb, file_name + ".~0" );

                wb->flag_changed_autosave( false );
            }
        }
    } catch ( const std::exception& e ) {
        LOG_CORE_ERROR( "auto-saving failed with error: " << e.what() );
    }
}

void session::remove_autosave( const std::string& path )
{
    std::vector< std::string > files_to_delete;

    bfs::path       tmp_path( path );
    std::string     filename = tmp_path.leaf();
    std::string     session_id = boost::lexical_cast< std::string >( m_uuid );

    if ( !bfs::exists( tmp_path ) ) {
        return;
    }

    if ( tmp_path.extension().size() > 1 && '~' == tmp_path.extension()[1] ) {

        //this is a file loaded from autosave. find the session id that generated this
        tmp_path.remove_leaf();

        std::string::size_type end   = filename.find_last_of( '.', filename.size() - 1 );
        if ( std::string::npos == end ) {
            //malformed here
            return;
        }
        std::string::size_type begin   = filename.find_last_of( '.', end - 1 );
        if ( std::string::npos == begin ) {
            //malformed here
            return;
        }

        std::string::size_type char_cnt = filename.find_first_of( '.' );
        if ( std::string::npos == char_cnt ) {
            //malformed here
            return;
        }
        char_cnt = filename.find_first_of( '.', char_cnt + 1 );
        if ( std::string::npos == char_cnt ) {
            //malformed here
            return;
        }

        filename = filename.substr( 0, char_cnt );
    }

    tmp_path.remove_leaf();
    autosave_filesystem_iterator    file_list( tmp_path, m_username, "", filename );
    while ( !file_list.end() ) {
        files_to_delete.push_back( ( *file_list )->string() );
        ++file_list;
    }

    foreach( std::string file, files_to_delete ) {
        boost::filesystem::remove( file );
    }
}

void session::remove_autosave()
{
    if ( !m_selected_objects.application() ) {
        return;
    }

    std::vector< std::string > files_to_delete;

    foreach( const shared_workbook_type & wb, m_selected_objects.application()->locking_iterator() ) {

        bfs::path       tmp_path = wb->path();
        std::string     filename = tmp_path.leaf();
        tmp_path.remove_leaf();

        autosave_filesystem_iterator    file_list( tmp_path, m_username, boost::lexical_cast< std::string >( m_uuid ), filename );

        while ( !file_list.end() ) {
            files_to_delete.push_back( ( *file_list )->string() );
            ++file_list;
        }
    }

    foreach( std::string file, files_to_delete ) {
        try {
            boost::filesystem::remove( file );
        } catch ( boost::filesystem::filesystem_error& ) {
            //multiple users using the same account, we ignore
        }
    }
}

const ::calculation_settings& session::calculation_settings()
{
    if ( m_calculation_settings == NULL ) {
        m_calculation_settings = &m_selected_objects.application()->calculation_settings();
    }
    return *m_calculation_settings;
}

boost::thread_specific_ptr<session*> session::m_current_session;

int session::max_lazy_function_count = 20;
