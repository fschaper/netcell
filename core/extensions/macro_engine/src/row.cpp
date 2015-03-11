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
#include <wss/worksheet.hpp>
#include <wss/server.hpp>
#include <wss/object_registry.hpp>
#include <wss/sheet_layout_manager.hpp>
#include "logging.hpp"
#include "php_includes.hpp"

zend_class_entry* wss_row_class;
extern zend_class_entry* wss_worksheet_class;
extern zend_class_entry* wss_wss_exception_class;

ZEND_EXTERN_MODULE_GLOBALS( wssme );

/* \brief
 * constructs a new PHP row wrapper object
 */
static PHP_METHOD( row, __construct )
{
    zval* zval_ws           = NULL;
    zval* zval_ws_uuid      = NULL;
    long index              = 0;

    if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "l|z", &index, &zval_ws ) == FAILURE ) {
        BEGIN_CORE_CATCH_BLOCK()
        throw fatal_exception( "WRONG_PARAM_COUNT" );
        END_CORE_CATCH_BLOCK()
        WRONG_PARAM_COUNT;
    }

    if ( NULL == zval_ws ) {
        //defaults for the active worksheet
        const shared_worksheet_type worksheet = WSS_PHP_G( session_context )->selected().worksheet().lock();
        TEST_SHARED_OBJ( worksheet );
        const std::string uuid( boost::lexical_cast<std::string>( worksheet->uuid() ) );
        zend_update_property_string( wss_row_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_ws_uuid" ), const_cast<char*>( uuid.c_str() ) TSRMLS_CC );
    } else {
        zend_call_method_with_0_params( &zval_ws, wss_worksheet_class, NULL, "uuid", &zval_ws_uuid );
        zend_update_property_string( wss_row_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_ws_uuid" ), Z_STRVAL_P( zval_ws_uuid ) TSRMLS_CC );
    }

    zend_update_property_long( wss_row_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_idx" ), index TSRMLS_CC );
}

PHP_PROPERTY_SETTER( row );
PHP_PROPERTY_GETTER( row );

/*!
 * brief
 * returns a reference to the Worksheet object
 *
 * \returns
 * reference to the Worksheet object
 */
static PHP_METHOD( row, parent )
{
    PHP_FUNC_CHECK_FOR_READONLY_PROPERTY;

    zval* zval_ws       = NULL;
    zval* zval_ws_uuid  = zend_read_property( wss_row_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_ws_uuid" ), 1 TSRMLS_CC );
    ALLOC_INIT_ZVAL( zval_ws );
    object_init_ex( zval_ws, wss_worksheet_class );
    zend_call_method_with_1_params( &zval_ws, wss_worksheet_class, NULL, "__construct", NULL, zval_ws_uuid );
    RETURN_ZVAL( zval_ws, 1, 0 );
}

/*!
 * brief
 * returns the index of this row in the Worksheet object
 *
 * \returns
 * index of this row in the Worksheet
 */
static PHP_METHOD( row, index )
{
    long value = -1;

    if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "|l", &value ) == FAILURE ) {
        WRONG_PARAM_COUNT;
    }

    if ( -1 != value ) {
        zend_update_property_long( wss_row_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_idx" ), value TSRMLS_CC );
        RETURN_NULL();
    } else {
        zval* zval_idx = zend_read_property( wss_row_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_idx" ), 1 TSRMLS_CC );
        RETURN_ZVAL( zval_idx, 1, 0 );
    }
}

/* \brief
 * accessor for the height
 *
 * \param height
 * optional/ new height
 * \returns
 * the height if no parameters given. null otherwise
 */
static PHP_METHOD( row, height )
{
    long value = -1;

    if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "|l", &value ) == FAILURE ) {
        WRONG_PARAM_COUNT;
    }

    zval* zval_uuid  = zend_read_property( wss_row_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_ws_uuid" ), 1 TSRMLS_CC );
    zval* zval_idx   = zend_read_property( wss_row_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_idx" ), 1 TSRMLS_CC );
    GET_SHARED_OBJ( worksheet, zval_uuid );

    if ( -1 == value ) {
        RETURN_LONG( shared_obj->layout().row_height( Z_LVAL_P( zval_idx ) ) )
    } else {
        shared_obj->layout().row_height( Z_LVAL_P( zval_idx ), value );
        RETURN_NULL()
    }
}

/* \brief
 * list of all methods of the row object and their access modifiers
 *
 * \see
 * register_row_object
 */
static zend_function_entry wss_row_functions[] = {
    PHP_ME( row, __construct, wss_one_arg, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR )
    PHP_ME( row, __set, wss_two_args, ZEND_ACC_PUBLIC )
    PHP_ME( row, __get, wss_one_arg, ZEND_ACC_PUBLIC )
    PHP_ME( row, parent, wss_no_args, ZEND_ACC_PUBLIC )
    PHP_ME( row, index, wss_no_args, ZEND_ACC_PUBLIC )
    PHP_ME( row, height, wss_one_arg, ZEND_ACC_PUBLIC ) {
        NULL, NULL, NULL
    }
};

void register_row_object( TSRMLS_D )
{
    // register internal wss<=>php wrapper objects
    zend_class_entry ce;

    INIT_CLASS_ENTRY( ce, "row", wss_row_functions );
    wss_row_class = zend_register_internal_class( &ce TSRMLS_CC );
    zend_declare_property_null( wss_row_class, WSS_PHP_STRING_NO_NULL( "m_ws_uuid" ), ZEND_ACC_PRIVATE TSRMLS_CC );
    zend_declare_property_null( wss_row_class, WSS_PHP_STRING_NO_NULL( "m_idx" ), ZEND_ACC_PRIVATE TSRMLS_CC );
}
