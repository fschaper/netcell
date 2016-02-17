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
#include "php_function_redirection_registry.hpp"
#include <wss/scoped_neutral_locale_enforcer.hpp>
#include <wss/i_export_filter.hpp>

extern zend_class_entry* wss_workbooks_class;
extern zend_class_entry* wss_worksheets_class;
extern zend_class_entry* wss_names_class;
extern zend_class_entry* wss_name_class;
extern zend_class_entry* wss_wss_exception_class;
extern zend_class_entry* wss_application_class;

zend_class_entry* wss_workbook_class;

ZEND_EXTERN_MODULE_GLOBALS( wssme );

/*!
 * \brief
 * constructs a new workbook wrapper object.
 *
 * \param uuid
 * uuid of the workbook in wss3
 */
static PHP_METHOD( workbook, __construct )
{
    char* workbook_uuid     = 0;
    long workbook_uuid_len  = 0;

    if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "|s", &workbook_uuid, &workbook_uuid_len ) == FAILURE ) {
        BEGIN_CORE_CATCH_BLOCK()
        throw fatal_exception( "WRONG_PARAM_COUNT" );
        END_CORE_CATCH_BLOCK()
        WRONG_PARAM_COUNT;
    }

    if ( NULL == workbook_uuid ) {
        //defaults for the active workbook
        const shared_workbook_type workbook = WSS_PHP_G( session_context )->selected().workbook().lock();
        TEST_SHARED_OBJ( workbook );
        const std::string uuid( boost::lexical_cast<std::string>( workbook->uuid() ) );
        zend_update_property_string( wss_workbook_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_uuid" ), const_cast<char*>( uuid.c_str() ) TSRMLS_CC );
    } else {
        try {
            uuid_type test = boost::lexical_cast< uuid_type >( workbook_uuid );

            zend_update_property_string( wss_workbook_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_uuid" ), workbook_uuid TSRMLS_CC );
        } catch ( std::bad_cast& ) {
            //maybe we have a name here
            try {
                const shared_application_type app = WSS_PHP_G( session_context )->selected().application();
                uuid_type uuid = app->get( *WSS_PHP_G( session_context ) , utf8_ci_string( workbook_uuid ) )->uuid();
                std::string uuid_str =  boost::lexical_cast< std::string >( uuid );
                workbook_uuid = const_cast< char* >( uuid_str.c_str() );
                zend_update_property_string( wss_workbook_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_uuid" ), workbook_uuid TSRMLS_CC );
            } catch ( object_not_found_exception& ) {
                zval* zval_err_msg = NULL;
                ALLOC_INIT_ZVAL( zval_err_msg );
                \
                ZVAL_STRING( zval_err_msg, "The parameter shall be a valid workbook uuid/name.", 1 );

                zval* zval_err_code = NULL;
                \
                ALLOC_INIT_ZVAL( zval_err_code );
                ZVAL_LONG( zval_err_code, 0x000300 );

                zval* zval_exception  = NULL;
                ALLOC_INIT_ZVAL( zval_exception );
                object_init_ex( zval_exception, wss_wss_exception_class );
                zend_call_method_with_2_params( &zval_exception, wss_wss_exception_class, NULL, "__construct", NULL, zval_err_msg, zval_err_code );

                zval_dtor( zval_err_msg );
                zval_dtor( zval_err_code );

                zend_throw_exception_object( zval_exception,  TSRMLS_C );
                \
            }
        }

    }
}

PHP_PROPERTY_SETTER( workbook );
PHP_PROPERTY_GETTER( workbook );

/* \brief
 * returns a reference to the Workbooks object
 */
static PHP_METHOD( workbook, parent )
{
    PHP_FUNC_CHECK_FOR_READONLY_PROPERTY;

    zval*            zval_wb        = NULL;
    zval*            zval_app       = NULL;
    zval*            zval_app_uuid  = NULL;
    zval*            zval_wb_uuid   = zend_read_property( wss_workbook_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_uuid" ), 1 TSRMLS_CC );
    std::string     app_uuid        = "";
    GET_SHARED_OBJ( workbook, zval_wb_uuid );

    app_uuid = boost::lexical_cast< std::string > ( shared_obj->parent()->uuid() );
    ALLOC_INIT_ZVAL( zval_app_uuid );
    ZVAL_STRING( zval_app_uuid, const_cast<char*>( app_uuid.c_str() ), 1 );
    ALLOC_INIT_ZVAL( zval_wb );
    ALLOC_INIT_ZVAL( zval_app );
    object_init_ex( zval_app, wss_application_class );
    zend_call_method_with_1_params( &zval_app, wss_application_class, NULL, "__construct", NULL, zval_app_uuid );
    object_init_ex( zval_wb, wss_workbooks_class );
    zend_call_method_with_1_params( &zval_wb, wss_workbooks_class, NULL, "__construct", NULL, zval_app );
    zval_dtor( zval_app_uuid );
    zval_dtor( zval_app );
    RETURN_ZVAL( zval_wb, 1, 0 );
}


/* \brief
 * returns the worksheets PHP wrapper for the Application object
 *
 * returns an worksheets object which is basically an wrapper around
 * the add/get/remove container functions of wss3.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
static PHP_METHOD( workbook, worksheets )
{
    zval* sheet_id = NULL;
    if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "|z", &sheet_id ) == FAILURE ) {
        WRONG_PARAM_COUNT;
    }

    zval* worksheets_object = zend_read_property( wss_workbook_class, this_ptr, WSS_PHP_STRING_NO_NULL( "m_worksheets" ), 1 TSRMLS_CC );

    object_init_ex( worksheets_object, wss_worksheets_class );
    zend_call_method_with_1_params( &worksheets_object, wss_worksheets_class, NULL, "__construct", NULL, this_ptr );
    zend_update_property( wss_workbook_class, this_ptr, WSS_PHP_STRING_NO_NULL( "m_worksheets" ), worksheets_object TSRMLS_CC );

    if ( sheet_id ) {
        zval* worksheet_object = NULL;
        zend_call_method_with_1_params( &worksheets_object, wss_worksheets_class, NULL, "item", &worksheet_object, sheet_id );
        RETURN_ZVAL( worksheet_object, 1, 0 )
    } else {
        RETURN_ZVAL( worksheets_object, 1, 0 )
    }
}

/* \brief
 * returns or sets the name of the workbook object
 *
 * \param name
 * optional parameter, when given the method sets the name of the workbook to "name"
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
static PHP_METHOD( workbook, name )
{
    zval* zval_uuid         = NULL;
    char* workbook_name     = NULL;
    long workbook_name_len  = 0;

    if ( ZEND_NUM_ARGS() > 0 ) {
        if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "s", &workbook_name, &workbook_name_len ) == FAILURE ) {
            WRONG_PARAM_COUNT;
        }
    }

    zval_uuid = zend_read_property( wss_workbook_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_uuid" ), 1 TSRMLS_CC );
    GET_SHARED_OBJ( workbook, zval_uuid );

    if ( NULL == workbook_name ) {
        RETURN_STRING( const_cast< char* >( shared_obj->name().c_str() ), 1 );
    } else {
        shared_obj->name( workbook_name );
    }
}

/*!
 * \brief
 * register a php function as an spreadsheetfunction with the active workbook.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
static PHP_METHOD( workbook, register_function )
{
    char* spreadsheet_function;
    char* function_name;
    char* php_file;
    long length;
    int is_volatile = 0;
    int is_view_dependent = 0;
    zval* zval_uuid;

    if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "sss|bb", &spreadsheet_function, &length, &function_name, &length, &php_file, &length, &is_volatile, &is_view_dependent ) == FAILURE ) {
        WRONG_PARAM_COUNT;
    }

    zval_uuid = zend_read_property( wss_workbook_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_uuid" ), 0 TSRMLS_CC );
    php_function_redirection_registry::instance().register_function( boost::lexical_cast< uuid_type >( Z_STRVAL_P( zval_uuid ) ), spreadsheet_function, php_file, function_name, is_volatile != 0, is_view_dependent != 0 );

    RETURN_NULL();
}

/*!
 * \brief
 * unregister all functions for the current workbook.
 * optionally takes an parameter to later support de-registreation
 * for individual functions only.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
static PHP_METHOD( workbook, unregister_function )
{
    char* spreadsheet_function;
    long length;
    zval* zval_uuid;

    if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "|s", &spreadsheet_function, &length ) == FAILURE ) {
        WRONG_PARAM_COUNT;
    }

    zval_uuid = zend_read_property( wss_workbook_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_uuid" ), 0 TSRMLS_CC );
    php_function_redirection_registry::instance().unregister_workbook( boost::lexical_cast< uuid_type >( Z_STRVAL_P( zval_uuid ) ) );
}

/*!
 * \brief
 * return a named formula container object.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
static PHP_METHOD( workbook, names )
{
    PHP_FUNC_CHECK_FOR_READONLY_PROPERTY;

    zval* zval_names    = NULL;

    ALLOC_INIT_ZVAL( zval_names );
    object_init_ex( zval_names, wss_names_class );
    zend_call_method_with_1_params( &zval_names, wss_names_class, NULL, "__construct", NULL, getThis() );
    RETURN_ZVAL( zval_names, 1, 0 );
}

/*!
* \brief
* sets/gets the changed flag on workbook.
*
* \author
* Radu Racariu <radu@yalos-solutions.com.com>
*/
static PHP_METHOD( workbook, flag_changed )
{
    long is_changed = -1;
    zval* zval_uuid = NULL;
    if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "|l", &is_changed ) == FAILURE ) {
        WRONG_PARAM_COUNT;
    }

    zval_uuid = zend_read_property( wss_workbook_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_uuid" ), 1 TSRMLS_CC );
    GET_SHARED_OBJ( workbook, zval_uuid );

    if ( is_changed != -1 ) {
        shared_obj->flag_changed( static_cast<bool> ( is_changed ) );
        RETURN_BOOL( static_cast<bool> ( is_changed ) );
    } else {
        RETURN_BOOL( shared_obj->has_changes() );
    }
}

/*!
* \brief
* export current workbook to a given file with a given type.
* types are xlsx or wss
* \author
* Radu Racariu <radu@yalos-solutions.com>
*/
static PHP_METHOD( workbook, export )
{
    zval* zval_uuid = NULL;

    zval_uuid = zend_read_property( wss_workbook_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_uuid" ), 1 TSRMLS_CC );
    GET_SHARED_OBJ( workbook, zval_uuid );

    const std::string& wb_meta_key = boost::lexical_cast<std::string>( shared_obj->uuid() ) + "export_running";
    ::session& session = *WSS_PHP_G( session_context );
    try {
        if ( !session.storage().retrieve( wb_meta_key ).empty() ) {
            RETURN_BOOL( false )
        }
    } catch ( arbitrary_storage_object_not_found_exception& ) {
    }

    char* c_filename = "";
    char* c_filetype = "";
    bool snapshot = false;
    long length;
    if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "s|sb", &c_filename, &length, &c_filetype, &length, &snapshot ) == FAILURE ) {
        WRONG_PARAM_COUNT;
    }

    std::string file_name( c_filename );
    std::string file_type( c_filetype );
    bool is_native = true;

    if ( file_name != "" ) {
        if ( file_type == "" ) {
            file_type = "xlsx";
        }
        if ( "xlsx" == file_type ) {
            is_native = false;
        }
        BEGIN_CORE_CATCH_BLOCK()
        const std::vector<char> on ( 1 );
        session.storage().store( wb_meta_key, on );
        try {
            filter_registry::shared_export_filter_type  wss_filter  = server::instance().filters().get_export_filter( file_type );
            scoped_neutral_locale_enforcer en_us_locale_enforcer( session );
            wss_filter->do_export( session, *shared_obj, file_name, snapshot, is_native );
            session.storage().remove( wb_meta_key );
        } catch ( std::exception& e ) {
            session.storage().remove( wb_meta_key );
            throw e;
        }
        END_CORE_CATCH_BLOCK()
        RETURN_BOOL( true )
    }
    RETURN_BOOL( false )
}

/*!
 * \brief
 * returns the uuid of the application object
 *
 * \returns
 * unique identifier of the application object
 */
static PHP_METHOD( workbook, uuid )
{
    PHP_FUNC_CHECK_FOR_READONLY_PROPERTY;

    zval* zval_uuid = zend_read_property( wss_workbook_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_uuid" ), 1 TSRMLS_CC );
    RETURN_ZVAL( zval_uuid, 1, 0 )
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

/* \brief
 * list of all methods of the workbook object and their access modifiers
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
static zend_function_entry wss_workbook_functions[] = {
    PHP_ME( workbook, __construct, wss_two_args, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR )
    PHP_ME( workbook, __set, wss_two_args, ZEND_ACC_PUBLIC )
    PHP_ME( workbook, __get, wss_one_arg, ZEND_ACC_PUBLIC )
    PHP_ME( workbook, parent, wss_no_args, ZEND_ACC_PUBLIC )
    PHP_ME( workbook, worksheets, NULL, ZEND_ACC_PUBLIC )
    PHP_ME( workbook, uuid, wss_no_args, ZEND_ACC_PUBLIC )
    PHP_ME( workbook, names, NULL, ZEND_ACC_PUBLIC )
    PHP_ME( workbook, flag_changed, wss_one_arg, ZEND_ACC_PUBLIC )
    PHP_ME( workbook, export, wss_two_args, ZEND_ACC_PUBLIC )
    PHP_MALIAS( workbook, sheets, worksheets, NULL, ZEND_ACC_PUBLIC )
    PHP_ME( workbook, register_function, wss_no_args, ZEND_ACC_PUBLIC )
    PHP_ME( workbook, unregister_function, wss_no_args, ZEND_ACC_PUBLIC )
    PHP_ME( workbook, name, NULL, ZEND_ACC_PUBLIC ) {
        NULL, NULL, NULL
    }
};

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

void register_workbook_object( TSRMLS_D )
{
    // register internal wss<=>php wrapper objects
    zend_class_entry ce;

    INIT_CLASS_ENTRY( ce, "workbook", wss_workbook_functions );
    wss_workbook_class = zend_register_internal_class( &ce TSRMLS_CC );
    zend_declare_property_null( wss_workbook_class, WSS_PHP_STRING_NO_NULL( "m_uuid" ), ZEND_ACC_PRIVATE TSRMLS_CC );
    zend_declare_property_null( wss_workbook_class, WSS_PHP_STRING_NO_NULL( "m_worksheets" ), ZEND_ACC_PRIVATE TSRMLS_CC );
    zend_declare_property_null( wss_workbook_class, WSS_PHP_STRING_NO_NULL( "m_names" ), ZEND_ACC_PRIVATE TSRMLS_CC );
    zend_declare_property_null( wss_workbook_class, WSS_PHP_STRING_NO_NULL( "m_parent" ), ZEND_ACC_PRIVATE TSRMLS_CC );
}
