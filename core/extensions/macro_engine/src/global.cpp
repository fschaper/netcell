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
#include "logging.hpp"
#include "php_includes.hpp"
#include "php_function_registry.hpp"
#include "value_converter.hpp"

ZEND_EXTERN_MODULE_GLOBALS( wssme );

// globals
const char* g_session_id_name = "session-id";
const char* g_wssme_superglobal_name = "_WSS";

//path for storing temporary files
boost::filesystem::path g_temp_path;

extern zend_class_entry* wss_application_class;
extern zend_class_entry* wss_workbook_class;
extern zend_class_entry* wss_worksheet_class;
extern zend_class_entry* wss_range_class;
extern zend_class_entry* wss_wss_exception_class;

/*!
 * \brief
 * creates an application object initialized with the uuid of the current session
 *
 * effectively calls application::__construct.
 *
 * \returns
 * returns application object
 *
 * \author
 * Radu Ialovoi <ialovoi@yalos-solutions.com>
 */
static PHP_FUNCTION( application )
{
    PHP_FUNC_CHECK_FOR_NO_ARGUMENTS;

#ifdef DEBUG_EXTENSION_PHP_MACRO_ENGINE_PHP_GLOBAL_FUNCTIONS
    LOG_PHP_DEBUG( "firing up the application() global function" );
#endif
    zval* zval_app = NULL;
    ALLOC_INIT_ZVAL( zval_app );
    object_init_ex( zval_app, wss_application_class );
    zend_call_method_with_0_params( &zval_app, wss_application_class, NULL, "__construct", NULL );
    RETURN_ZVAL( zval_app, 1, 0 );
}

/*!
 * \brief
 * Returns the currently active Workbook object depending on the users context
 *
 * determined the currently active workbook from the users session and creates the object
 * hierarchy. (Application->Workbooks->Workbook)
 *
 * \returns
 * returns Workbook object or NULL if the user has no active workbook
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
static PHP_FUNCTION( activeworkbook )
{
    PHP_FUNC_CHECK_FOR_NO_ARGUMENTS;

#ifdef DEBUG_EXTENSION_PHP_MACRO_ENGINE_PHP_GLOBAL_FUNCTIONS
    LOG_PHP_DEBUG( "firing up the activeworkbook() global function" );
#endif
    zval* zval_wb = NULL;
    ALLOC_INIT_ZVAL( zval_wb );
    object_init_ex( zval_wb, wss_workbook_class );
    zend_call_method_with_0_params( &zval_wb, wss_workbook_class, NULL, "__construct", NULL );
    RETURN_ZVAL( zval_wb, 1, 0 );
}

/*!
 * \brief
 * Returns the currently active Worksheet object depending on the users context
 *
 * determined the currently active worksheet from the users session and creates the object
 * hierarchy. (Application->Workbooks->Workbook->Worksheets->Worksheet)
 *
 * \returns
 * returns Worksheet object or NULL if the user has no active worksheet
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
static PHP_FUNCTION( activesheet )
{
    PHP_FUNC_CHECK_FOR_NO_ARGUMENTS;

#ifdef DEBUG_EXTENSION_PHP_MACRO_ENGINE_PHP_GLOBAL_FUNCTIONS
    LOG_PHP_DEBUG( "firing up the activesheet() global function" );
#endif
    zval* zval_ws = NULL;
    ALLOC_INIT_ZVAL( zval_ws );
    object_init_ex( zval_ws, wss_worksheet_class );
    zend_call_method_with_0_params( &zval_ws, wss_worksheet_class, NULL, "__construct", NULL );
    RETURN_ZVAL( zval_ws, 1, 0 );
}

/*!
 * \brief
 * Returns the currently active Range object depending on the users context
 *
 * determines the currently active range from the users session and creates the object
 * hierarchy. (Application->Workbooks->Workbook->Worksheets->Worksheet->Range)
 *
 * \returns
 * returns Range object or NULL if the user has no active range
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
static PHP_FUNCTION( activerange )
{
    zval* zval_range_a1         = NULL;
    zval* zval_range            = NULL;

    const shared_worksheet_type     worksheet = WSS_PHP_G( session_context )->selected().worksheet().lock();

    TEST_SHARED_OBJ( worksheet );

    const std::string               range ( WSS_PHP_G( active_range ) );

    ALLOC_INIT_ZVAL( zval_range_a1 );
    ZVAL_STRING( zval_range_a1, const_cast<char*>( range.c_str() ), 1 );

    ALLOC_INIT_ZVAL( zval_range );
    object_init_ex( zval_range, wss_range_class );

    zend_call_method_with_1_params( &zval_range, wss_range_class, NULL, "__construct", NULL, zval_range_a1 );

    zval_dtor( zval_range_a1 );

    RETURN_ZVAL( zval_range, 1, 0 );
}

/*!
 * \brief
 * returns the temp folder as configured via php_macro_engine_config.xml
 *
 * \returns
 * returns temp folder as configured via php_macro_engine_config.xml
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
static PHP_FUNCTION( temp_directory )
{
    if ( g_temp_path.has_root_path() ) {
        RETURN_STRING( const_cast<char*>( g_temp_path.string().c_str() ), 1 );
    } else {
        boost::filesystem::path absolute_path( boost::filesystem::current_path() / g_temp_path );
        RETURN_STRING( const_cast<char*>( absolute_path.string().c_str() ), 1 );
    }

}

/*!
 * \brief
 * returns the current user from the session object.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
static PHP_FUNCTION( current_user )
{
    PHP_FUNC_CHECK_FOR_NO_ARGUMENTS;
    RETURN_STRING( const_cast<char*>( WSS_PHP_G( session_context )->username().c_str() ), 1 );

}

/*!
 * \brief
 * returns the list of the users groups from the session object.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
static PHP_FUNCTION( current_groups )
{

    zval* array = NULL;
    ALLOC_INIT_ZVAL( array );
    array_init( array );
    BOOST_FOREACH( const std::string & groupname, WSS_PHP_G( session_context )->groups() ) {
        add_next_index_string( array, const_cast<char*>( groupname.c_str() ), 1 );
    }
    RETURN_ZVAL( array, 1, 1 );

}

/*!
 * \brief
 * returns the locale of the current session
 *
 * \returns
 * the locale of the current session
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
static PHP_FUNCTION( locale )
{
    PHP_FUNC_CHECK_FOR_NO_ARGUMENTS;
    std::string lang_code = WSS_PHP_G( session_context )->locale().code();
    RETURN_STRING( const_cast<char*>( lang_code.c_str() ), 1 );

}

/*!
 * \brief
 * returns the current calculation token id from the users session
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
static PHP_FUNCTION( calculation_token )
{
    RETURN_LONG( WSS_PHP_G( session_context )->calculation_token() );

}

/*!
 * \brief
 * register a macro function with the server function registry.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
static PHP_FUNCTION( register_function )
{
    char* spreadsheet_function;
    char* function_name;
    char* php_file;
    long length;
    int is_volatile = 0;
    int is_view_dependent = 0;

    if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "sss|bb", &spreadsheet_function, &length, &function_name, &length, &php_file, &length, &is_volatile, &is_view_dependent ) == FAILURE ) {
        WRONG_PARAM_COUNT;
    }

    php_function_registry::instance().register_function( spreadsheet_function, php_file, function_name, is_volatile != 0, is_view_dependent != 0 );

    RETURN_NULL();

}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

/**
 * \brief
 * Returns the temp folder as configured via php_macro_engine_config.xml
 *
 * \returns
 * returns temp folder as configured via php_macro_engine_config.xml
 *
 * \see
 *
 */
static PHP_FUNCTION( wss_temp_directory )
{
    PHP_FUNC_CHECK_FOR_NO_ARGUMENTS;

    if ( g_temp_path.has_root_path() ) {
        RETURN_STRING( const_cast<char*>( g_temp_path.string().c_str() ), 1 );
    } else {
        boost::filesystem::path absolute_path( boost::filesystem::current_path() / g_temp_path );
        RETURN_STRING( const_cast<char*>( absolute_path.string().c_str() ), 1 );
    }
}

/**
 * \brief
 * set a variable to a passed value
 *
 */
static PHP_FUNCTION( define_variable )
{
    char* variable_name = NULL;
    long variable_name_length = 0;
    zval* value;

    if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "sz", &variable_name, &variable_name_length, &value ) == FAILURE ) {
        WRONG_PARAM_COUNT;
    }

    variant variable = value_converter()( value TSRMLS_CC );
    WSS_PHP_G( session_context )->variable().variable( *WSS_PHP_G( session_context ), variable_name, variable );
}

/**
 * \brief
 * set a variable to a passed value
 *
 */
static PHP_FUNCTION( retrieve_variable )
{
    char* variable_name = NULL;
    long variable_name_length = 0;

    if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "s", &variable_name, &variable_name_length ) == FAILURE ) {
        WRONG_PARAM_COUNT;
    }

    value_converter()( WSS_PHP_G( session_context )->locale(), return_value, WSS_PHP_G( session_context )->variable().variable( variable_name ) );
}

/*!
 * \brief
 * functions registered with PHP on the global scope
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Radu Ialovoi <ialovoi@yalos-solutions.com>
 */

zend_function_entry* get_functions()
{
    static zend_function_entry inst_wssme_functions[] = {
        PHP_FE( application, wss_no_args )
        PHP_FALIAS( activeapplication, application, wss_no_args )
        PHP_FE( activeworkbook, wss_no_args )
        PHP_FE( activesheet, wss_no_args )
        PHP_FE( activerange, wss_no_args )
        PHP_FE( wss_temp_directory, wss_no_args )
        PHP_FE( temp_directory, wss_no_args )
        PHP_FE( locale, wss_no_args )
        PHP_FE( calculation_token, wss_no_args )
        PHP_FE( current_user, wss_no_args )
        PHP_FE( current_groups, wss_no_args )
        PHP_FE( define_variable, wss_two_args )
        PHP_FE( retrieve_variable, wss_one_arg )
        PHP_FE( register_function, NULL ) {
            NULL, NULL, NULL
        }
    };

    return inst_wssme_functions;
}

