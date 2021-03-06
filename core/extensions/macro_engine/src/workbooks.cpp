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
#include <wss/invalid_workbook_exception.hpp>

zend_class_entry* wss_workbooks_class;

extern zend_class_entry*  wss_application_class;
extern zend_class_entry* wss_workbook_class;
extern zend_class_entry* wss_wss_exception_class;

ZEND_EXTERN_MODULE_GLOBALS( wssme );

/* \brief
 * constructs a new workbooks object
 *
 * \param app_uuid
 * optional app_uuid this workbooks wraps
 */
static PHP_METHOD( workbooks, __construct )
{
    zval* zval_app      = NULL;
    zval* zval_app_uuid = NULL;

    if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "|z", &zval_app ) == FAILURE ) {
        BEGIN_CORE_CATCH_BLOCK()
        throw fatal_exception( "WRONG_PARAM_COUNT" );
        END_CORE_CATCH_BLOCK()
        WRONG_PARAM_COUNT;
    }

    if ( NULL == zval_app ) {
        //defaults for the active application
        const shared_application_type application = WSS_PHP_G( session_context )->selected().application();
        const std::string uuid( boost::lexical_cast<std::string>( application->uuid() ) );
        zend_update_property_string( wss_workbooks_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_app_uuid" ), const_cast<char*>( uuid.c_str() ) TSRMLS_CC );
    } else {
        zval* zval_a = NULL;
        ALLOC_INIT_ZVAL( zval_a );
        object_init_ex( zval_a, wss_application_class );
        zend_call_method_with_1_params( &zval_a, wss_application_class, NULL, "__construct", NULL, zval_app );
        zval_app_uuid = zend_read_property( wss_application_class, zval_a, WSS_PHP_STRING_NO_NULL( "m_uuid" ), 1 TSRMLS_CC );
        zend_update_property_string( wss_workbooks_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_app_uuid" ), Z_STRVAL_P( zval_app_uuid ) TSRMLS_CC );
    }
}

PHP_PROPERTY_SETTER( workbooks );
PHP_PROPERTY_GETTER( workbooks );

/* \brief
 * returns a reference to the Application object
 *
 */
static PHP_METHOD( workbooks, parent )
{
    zval*    zval_app = NULL;
    zval*    zval_app_uuid = zend_read_property( wss_workbooks_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_app_uuid" ), 1 TSRMLS_CC );

    ALLOC_INIT_ZVAL( zval_app );
    object_init_ex( zval_app, wss_application_class );
    zend_call_method_with_1_params( &zval_app, wss_application_class, NULL, "__construct", NULL, zval_app_uuid );
    RETURN_ZVAL( zval_app, 1, 0 );
}

/* \brief
 * adds a new, empty workbook to the collection
 *
 * \params name
 * name of the new workbook to be added
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
static PHP_METHOD( workbooks, add )
{
    zval*           zval_app_uuid   = NULL;
    zval*           zval_wb_uuid    = NULL;
    char*           workbook_name   = NULL;
    long            workbook_name_len = 0;
    std::string     new_uuid = "";

    if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "s", &workbook_name, &workbook_name_len ) == FAILURE ) {
        WRONG_PARAM_COUNT;
    }

    zval_app_uuid = zend_read_property( wss_workbooks_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_app_uuid" ), 1 TSRMLS_CC );
    GET_SHARED_OBJ( application, zval_app_uuid );

    BEGIN_CORE_CATCH_BLOCK()
    new_uuid = boost::lexical_cast< std::string >( shared_obj->add( convert_utf8_ci( std::string( workbook_name ) ) )->uuid() );
    END_CORE_CATCH_BLOCK()

    ALLOC_INIT_ZVAL( zval_wb_uuid );
    ZVAL_STRING( zval_wb_uuid, const_cast<char*>( new_uuid.c_str() ), 1 );
    object_init_ex( return_value, wss_workbook_class );
    zend_call_method_with_1_params( &return_value, wss_workbook_class, NULL, "__construct", NULL, zval_wb_uuid );
    zval_dtor( zval_wb_uuid );
}

/* \brief
 * removes an existing workbook from the application
 *
 * \params workbook
 * a workbook object
 *
 * \author
 * Radu Ialovoi <ialovoi@yalos-solutions.com>
 */
static PHP_METHOD( workbooks, remove )
{
    zval* zval_app_uuid  = NULL;
    zval* zval_wb        = NULL;
    zval* zval_wb_uuid   = NULL;


    if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "z", &zval_wb ) == FAILURE ) {
        WRONG_PARAM_COUNT;
    }

    zval_wb_uuid    = zend_read_property( wss_workbook_class, zval_wb, WSS_PHP_STRING_NO_NULL( "m_uuid" ), 1 TSRMLS_CC );
    zval_app_uuid   = zend_read_property( wss_workbooks_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_app_uuid" ), 1 TSRMLS_CC );

    GET_SHARED_OBJ( application, zval_app_uuid );

    const uuid_type wb_uuid = boost::lexical_cast< uuid_type >( Z_STRVAL_P( zval_wb_uuid ) );

    BEGIN_CORE_CATCH_BLOCK();
    shared_obj->remove( wb_uuid );
    END_CORE_CATCH_BLOCK();
}

/* \brief
 * returns the number of workbooks in the collection
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
static PHP_METHOD( workbooks, count )
{
    PHP_FUNC_CHECK_FOR_READONLY_PROPERTY;

    zval* zval_app_uuid      = zend_read_property( wss_workbooks_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_app_uuid" ), 1 TSRMLS_CC );
    GET_SHARED_OBJ( application, zval_app_uuid );
    RETURN_LONG( ( long ) shared_obj->count() );
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

/* \brief
 * returns the workbook identified by uuid
 *
 * \param
 * the uuid of the workbook
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
static PHP_METHOD( workbooks, item )
{
    zval*    zval_app_uuid  = NULL;
    zval*    zval_wb_object = NULL;
    zval*    zval_wb_uuid   = NULL;

    char*    wb_uuid        = NULL;
    long    wb_uuid_length  = 0;

    if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "s", &wb_uuid, &wb_uuid_length ) == FAILURE ) {
        WRONG_PARAM_COUNT;
    }

    zval_app_uuid = zend_read_property( wss_workbooks_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_app_uuid" ), 1 TSRMLS_CC );
    GET_SHARED_OBJ( application, zval_app_uuid );

    ALLOC_INIT_ZVAL( zval_wb_uuid );
    ZVAL_STRING( zval_wb_uuid, wb_uuid, 1 );
    ALLOC_INIT_ZVAL( zval_wb_object );
    object_init_ex( zval_wb_object, wss_workbook_class );
    zend_call_method_with_1_params( &zval_wb_object, wss_workbook_class, NULL, "__construct", NULL, zval_wb_uuid );
    zval_dtor( zval_wb_uuid );
    RETURN_ZVAL( zval_wb_object, 1, 0 );
}

/*!
 * \brief
 * returns the uuid of the application object
 *
 * \returns
 * unique identifier of the application object
 */
static PHP_METHOD( workbooks, uuid )
{
    PHP_FUNC_CHECK_FOR_READONLY_PROPERTY;

    zval* zval_uuid = zend_read_property( wss_workbooks_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_app_uuid" ), 1 TSRMLS_CC );
    RETURN_ZVAL( zval_uuid, 1, 0 )
}

/* \brief
 * list of all methods of the workbooks object and their access modifiers
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
static zend_function_entry wss_workbooks_functions[] = {
    PHP_ME( workbooks, __construct, wss_one_arg, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR )
    PHP_ME( workbooks, __set, wss_two_args, ZEND_ACC_PUBLIC )
    PHP_ME( workbooks, __get, wss_one_arg, ZEND_ACC_PUBLIC )
    PHP_ME( workbooks, parent, wss_no_args, ZEND_ACC_PUBLIC )
    PHP_MALIAS( workbooks, application, parent, wss_no_args, ZEND_ACC_PUBLIC )
    PHP_ME( workbooks, uuid, wss_no_args, ZEND_ACC_PUBLIC )
    PHP_ME( workbooks, add, wss_one_arg, ZEND_ACC_PUBLIC )
    PHP_ME( workbooks, remove, wss_one_arg, ZEND_ACC_PUBLIC )
    PHP_ME( workbooks, count, wss_no_args, ZEND_ACC_PUBLIC )
    PHP_ME( workbooks, item, wss_one_arg, ZEND_ACC_PUBLIC ) {
        NULL, NULL, NULL
    }
};

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

void register_workbooks_object( TSRMLS_D )
{
    // register internal wss<=>php wrapper objects
    zend_class_entry ce;

    INIT_CLASS_ENTRY( ce, "workbooks", wss_workbooks_functions );
    wss_workbooks_class = zend_register_internal_class( &ce TSRMLS_CC );
    zend_declare_property_null( wss_workbooks_class, WSS_PHP_STRING_NO_NULL( "m_app_uuid" ), ZEND_ACC_PRIVATE TSRMLS_CC );
}
