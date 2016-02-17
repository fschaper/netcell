/*!
 *  \file
 *  Copyright (C) 2006-2009 Jedox AG, Freiburg i.Br., Germany
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
#include "unicode/timezone.h"

#include "logging.hpp"
#include "php_sapi.hpp"
#include "wss2php_loglevel.hpp"
#include "i_task.hpp"

#include "php_includes.hpp"
#include "session_handler.hpp"

#ifdef PHP_WIN32
# include <io.h>
# include <fcntl.h>
#endif

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

extern _zend_module_entry wssme_module_entry;

extern const char* g_wssme_superglobal_name;
extern const char* g_session_id_name;

ZEND_DECLARE_MODULE_GLOBALS( wssme );

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

#define HARDCODED_INI                      \
    "html_errors=0\r\n"                    \
    "register_argc_argv=0\r\n"             \
    "implicit_flush=1\r\n"                 \
    "output_buffering=0\r\n"               \
    "max_execution_time=0\r\n"             \
    "max_input_time=-1\r\n"                \
    "log_errors=On\r\n"                    \
    "report_memleaks=0\r\n"                \
    "session.save_handler=wss_session\r\n" \
    "session.use_cookies=0\r\n"            \
    "safe_mode=0\r\n"                      \
    "session.cache_limiter=\"\"\r\n"

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

static void sapi_flush( void* server_context )
{
    if ( fflush( stdout ) == EOF ) {
        php_handle_aborted_connection();
    }
}

static int sapi_unbuffered_write( const char* str, uint str_length TSRMLS_DC )
{
    php_sapi::instance().on_unbuffered_write( std::string( str, str_length ) );
    return str_length;
}

static int sapi_send_headers_handler( sapi_headers_struct* sapi_headers TSRMLS_DC )
{
    // we do nothing here, this function is needed to prevent that the fall back
    // header handling is called.
    return SAPI_HEADER_SENT_SUCCESSFULLY;
}

static void sapi_send_single_header_handler( sapi_header_struct* sapi_header, void* server_context TSRMLS_DC )
{}

static int sapi_header_handler( sapi_header_struct* h, sapi_headers_struct* s TSRMLS_DC )
{
    // free allocated header line
    efree( h->header );
    // avoid pushing headers into SAPI headers list
    return 0;
}

static char* sapi_cookie_handler( TSRMLS_D )
{
    return NULL;
}

static void sapi_variable_handler( zval* track_vars_array TSRMLS_DC )
{
    php_sapi::instance().on_handle_trackvars( track_vars_array );
}

static void sapi_log_message_handler( char* message )
{
    TSRMLS_FETCH();
    php_sapi::instance().on_log_message( EG( error_reporting ), std::string( message ) );
}

static int php_module_startup_handler( sapi_module_struct* sapi_module )
{
    if ( php_module_startup( sapi_module, &wssme_module_entry, 1 ) == FAILURE ) {
        return FAILURE;
    }

    return SUCCESS;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

static sapi_module_struct wssme_sapi_module = {
    "wssme_php",                        // name
    "wss macro embedded php engine",    // pretty name

    php_module_startup_handler,         // startup
    php_module_shutdown_wrapper,        // shutdown

    NULL,                               // activate
    NULL /*sapi_deactivation_handler*/, // deactivate

    sapi_unbuffered_write,              // unbuffered write
    sapi_flush,                         // flush
    NULL,                               // get UID
    NULL,                               // getenv

    php_error,                          // error handler

    sapi_header_handler,                // header handler
    sapi_send_headers_handler,          // send headers handler
    sapi_send_single_header_handler,    // send header handler

    NULL,                               // read POST data
    sapi_cookie_handler,                // read Cookies

    sapi_variable_handler,              // register server variables
    sapi_log_message_handler,           // log message
    NULL,                               // get request time

    STANDARD_SAPI_MODULE_PROPERTIES
};

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

/*!
 * \brief
 * detect reentrant php invocation.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
struct php_reentrance_check {
    php_reentrance_check() : is( false ) {}
    ~php_reentrance_check() {
        is = false;
    }
    operator bool() const {
        return is;
    }
    bool is;
};

/*!
 * \brief
 * run a functor inside a thread and do the cleanup
 *
 * \author
 * Radu Racariu <radu@yalos-solutions.com>
 */
class scoped_php_thread
{
public:
    template<class F>
    scoped_php_thread( const F& f ) : m_executed( false ) {
        if ( php_requestor::m_thread_count < php_sapi::max_expected_thread_count ) {
            php_requestor::m_thread_count++;
            m_executed = true;
            boost::thread thread( f );
            // wait for the result to compute
            thread.join();
        }
    }
    ~scoped_php_thread() {
        if ( m_executed ) {
            php_requestor::m_thread_count--;
        }
    }
private:
    bool m_executed;
};

// init the counter
boost::atomic_int php_requestor::m_thread_count( 0 );

void php_requestor::execute( session& s, const std::string& active_range, const i_task& task, interpreter_context* context )
{
    static boost::thread_specific_ptr<php_reentrance_check> reentrant;

    if ( reentrant.get() == 0 ) {
        reentrant.reset( new php_reentrance_check() );
    }

    // (fschaper) determine if the call to a php macro leads to another call of an php macro.
    // php relies on thread local storage etc. so multiple calls from the same thread are impossible
    // and we need to service any additional call from a new thread.
    if ( ! *reentrant ) {
        ( *reentrant ).is = true;
        // fetch a new thread context
        TSRMLS_FETCH();

        int result = php_request_startup( TSRMLS_C );
        assert( result == SUCCESS );

        SG( headers_sent ) = 1;
        SG( request_info ).no_headers = 1;
        zval* wssme_superglobal;
        ALLOC_INIT_ZVAL( wssme_superglobal );
        array_init( wssme_superglobal );
        ZEND_SET_GLOBAL_VAR( "_WSS", wssme_superglobal );

        zval* session_id;
        ALLOC_INIT_ZVAL( session_id );
        const std::string session_uuid( boost::lexical_cast<std::string>( s.uuid() ) );
        ZVAL_STRING( session_id, const_cast<char*>( session_uuid.c_str() ), 1 );
        ZEND_SET_SYMBOL( Z_ARRVAL_P( wssme_superglobal ), const_cast<char*>( g_session_id_name ), session_id );

        // promote $_WSS into a superglobal
        zend_register_auto_global( const_cast<char*>( g_wssme_superglobal_name ), sizeof( g_wssme_superglobal_name )
#ifdef ZEND_ENGINE_2
                                   , NULL TSRMLS_CC );

#   if (PHP_MAJOR_VERSION > 5) || ((PHP_MAJOR_VERSION == 5) && (PHP_MINOR_VERSION > 0))
        // PHP >= 5.1 requirement
        zend_auto_global_disable_jit( const_cast<char*>( g_wssme_superglobal_name ), sizeof( g_wssme_superglobal_name ) TSRMLS_CC );
#   endif
#else
                                   TSRMLS_CC );
#endif

        // initialize the php_bridge extension global variables
        WSS_PHP_G( session_context ) = &s;
        WSS_PHP_G( interpreter_context ) = context;
        WSS_PHP_G( active_range ) = reinterpret_cast<char*>( emalloc( active_range.length() + 1 ) );
        memcpy( WSS_PHP_G( active_range ), active_range.c_str(), active_range.length() + 1 );

        // start php session.
        php_session_start( TSRMLS_C );

        // and execute the task
        try {
            task();
        } catch ( const std::exception& e ) {
            efree( WSS_PHP_G( active_range ) );
            php_request_shutdown( NULL );
            LOG_PHP_ERROR( e.what() );
            ( *reentrant ).is = false;
            return;
        }
        efree( WSS_PHP_G( active_range ) );
        php_request_shutdown( NULL );
        ( *reentrant ).is = false;
    } else {
        scoped_php_thread( boost::bind( &php_requestor::execute, boost::ref( this ), boost::ref( s ), boost::ref( active_range ), boost::ref( task ), boost::ref( context ) ) );
    }
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

php_sapi::php_sapi()
    : m_initialized( false )
{}

void php_sapi::shutdown()
{

    lock_type lock( m_mutex );
    if ( m_initialized ) {
        if ( wssme_sapi_module.shutdown ) {
            wssme_sapi_module.shutdown( &wssme_sapi_module );
        }

        sapi_shutdown();
        tsrm_shutdown();

        if ( wssme_sapi_module.ini_entries ) {
            free( wssme_sapi_module.ini_entries );
            wssme_sapi_module.ini_entries = NULL;
        }
    }
}

bool php_sapi::initialize( logging::log_level::level log_level,
                           const std::string& php_basedir,
                           const std::string& include_paths,
                           const std::string& dynamic_extensions_basedir,
                           const std::string& ini_directives,
                           const extensions_list_type& dynamic_extensions_list,
                           zend_module_entry& additional_modules,
                           unsigned num_additional_modules )
{
    lock_type lock( m_mutex );

    if ( !m_initialized ) {
        m_initialized = true;
    } else {
        return false;
    }

    zend_llist global_vars;
    m_php_basedir = php_basedir;

#ifdef PHP_WIN32
    _set_fmode( _O_BINARY );   // sets default for file streams to binary
    _setmode( _fileno( stdin ), O_BINARY );  // make the stdio modes binary
    _setmode( _fileno( stdout ), O_BINARY );
    _setmode( _fileno( stderr ), O_BINARY );
#endif

#ifdef HAVE_SIGNAL_H
# if defined(SIGPIPE) && defined(SIG_IGN)
    signal( SIGPIPE, SIG_IGN );
# endif
#endif

#ifdef ZTS
    // multi threaded php sapi startup
    tsrm_startup( max_expected_thread_count, 1, TSRM_ERROR_LEVEL_CORE, NULL );
    void* tsrm_ls = ts_resource( 0 );
#endif

    // php sapi startup
    sapi_startup( &wssme_sapi_module );

    // php ini settings
    std::stringstream php_ini;
    php_ini << HARDCODED_INI;

    if ( std::string::npos ==  ini_directives.find( "error_reporting" ) ) {
        php_ini << "error_reporting=" << log_level_converter()( log_level ) << "\r\n";
    }
    php_ini << "include_path=\"" << php_basedir << ( ( include_paths != "" ) ? PATH_SEPARATOR : "" ) << include_paths << "\"\r\n"
            << ini_directives << "\r\n";


    LOG_PHP_DEBUG( "configured '" << include_paths << "' as the additional include path(s)" );

    if ( dynamic_extensions_basedir != "" ) {
        php_ini << "extension_dir=\"" << dynamic_extensions_basedir << "\"\r\n";

        for ( extensions_list_type::const_iterator it = dynamic_extensions_list.begin(), end = dynamic_extensions_list.end(); it != end; it++ ) {
            php_ini << "extension=\"" << *it << "\"\r\n";
            LOG_PHP_DEBUG( "php_sapi: added '" << dynamic_extensions_basedir << "/" << *it << "' to the list of dynamically loaded extensions" )
        }
        LOG_PHP_INFO( "configured " << dynamic_extensions_list.size() << " php extension" << ( ( ( dynamic_extensions_list.size() == 0 ) || ( dynamic_extensions_list.size() > 1 ) ) ? "s" : "" ) );
    }

    /*icu::UnicodeString utz( "" );
    icu::TimeZone::createDefault()->getDisplayName( false, icu::TimeZone::SHORT, utz );
    std::string str_tz;
    utz.toUTF8String( str_tz );
    boost::replace_first( str_tz, "+0", "+" );
    php_ini << "date.timezone = \"Etc/" << std::string( str_tz.begin(), str_tz.begin() + str_tz.find( ":" ) ) << "\"\r\n";
    */
    wssme_sapi_module.ini_entries = reinterpret_cast<char*>( malloc( php_ini.str().length() + 2 ) );
    memcpy( wssme_sapi_module.ini_entries, php_ini.str().c_str(), php_ini.str().length() + 1 );
    wssme_sapi_module.ini_entries[php_ini.str().length() + 1] = '\0';

    wssme_sapi_module.php_ini_ignore = 1;
    wssme_sapi_module.phpinfo_as_text = 1;

    // php module and extensions startup
    if ( php_module_startup( &wssme_sapi_module, &additional_modules, num_additional_modules ) == FAILURE ) {
        LOG_PHP_ERROR( "php_sapi: failed to initialize the php module (wssme_sapi_module) and/or " << num_additional_modules << " extensions" )
        free( wssme_sapi_module.ini_entries );
        return false;
    } else {
        LOG_PHP_DEBUG( "php_sapi: initialized the php module (wssme_sapi_module) and " << num_additional_modules << " extensions" );
    }

    // start with an empty list of php globals
    zend_llist_init( &global_vars, sizeof( char* ), NULL, 0 );

    SG( options ) |= SAPI_OPTION_NO_CHDIR;
    SG( request_info ).argc = 0;
    SG( request_info ).argv = NULL;

    php_session_register_module( &ps_mod_wss_session );

    return true;
}

php_sapi::auto_requestor_type php_sapi::requestor() const
{
    lock_type lock( m_mutex );
    return ( m_initialized ) ? auto_requestor_type( new php_requestor() ) : auto_requestor_type( NULL );
}

void php_sapi::free_thread()
{
    lock_type lock( m_mutex );
    if ( m_initialized ) {
        ts_free_thread();
    }
}

const std::string& php_sapi::get_php_basedir() const
{
    return m_php_basedir;
}
