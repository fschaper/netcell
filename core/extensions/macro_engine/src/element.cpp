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
#include "value_converter.hpp"

zend_class_entry* wss_element_class;

extern zend_class_entry* wss_worksheet_class;
extern zend_class_entry* wss_wss_exception_class;

ZEND_EXTERN_MODULE_GLOBALS( wssme );

/* \brief
 * constructs a new PHP worksheet_element wrapper object
 */
static PHP_METHOD( element, __construct )
{
    zval* zval_ws               = NULL;
    zval* zval_ws_uuid          = NULL;
    char* ws_element_uuid       = NULL;
    long ws_element_uuid_len    = 0;

    if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "zs", &zval_ws, &ws_element_uuid, &ws_element_uuid_len ) == FAILURE ) {
        BEGIN_CORE_CATCH_BLOCK()
        throw fatal_exception( "WRONG_PARAM_COUNT" );
        END_CORE_CATCH_BLOCK()
        WRONG_PARAM_COUNT;
    }

    zend_call_method_with_0_params( &zval_ws, wss_worksheet_class, NULL, "uuid", &zval_ws_uuid );

    zend_update_property_string( wss_element_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_uuid" ), ws_element_uuid TSRMLS_CC );
    zend_update_property_string( wss_element_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_ws_uuid" ), Z_STRVAL_P( zval_ws_uuid ) TSRMLS_CC );
}

/*!
 * \brief
 * php magic method setter
 *
 * proxy method which redirects all parameters to the passed method implementation.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Radu Ialovoi <ialovoi@yalos-solutions.com>
 */
static PHP_METHOD( element, __set )
{
    zval* zval_name             = NULL;
    zval* zval_value            = NULL;
    zval* zval_prop             = NULL;
    zend_class_entry* ce        = NULL;
    char* lowercase_method_name = NULL;

    if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "zz", &zval_name, &zval_value ) == FAILURE ) {
        WRONG_PARAM_COUNT;
    }

    // php function names are stored in lower-case in format the function tables
    lowercase_method_name = estrndup( Z_STRVAL_P( zval_name ), Z_STRLEN_P( zval_name ) );

    zend_str_tolower( lowercase_method_name, Z_STRLEN_P( zval_name ) );
    ce = Z_OBJCE_P( getThis() );

    if ( zend_hash_exists( &ce->function_table, lowercase_method_name, Z_STRLEN_P( zval_name ) + 1 )  ) {
        zend_call_method( &getThis(), ce, NULL, lowercase_method_name, Z_STRLEN_P( zval_name ), NULL, 1, zval_value, NULL TSRMLS_CC );
    } else {
        ALLOC_INIT_ZVAL( zval_prop );
        ZVAL_STRING( zval_prop, lowercase_method_name, 1 );
        zend_call_method( &getThis(), ce, NULL, "custom_property", 15, NULL, 2, zval_prop, zval_value TSRMLS_CC );
        zval_dtor( zval_prop );
    }

    efree( lowercase_method_name );
    RETURN_NULL()
}

/*!
 * \brief
 * php magic method getter
 *
 * proxy method which redirects all parameters to the passed method implementation.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Radu Ialovoi <ialovoi@yalos-solutions.com>
 */
static PHP_METHOD( element, __get )
{
    zval* zval_name             = NULL;
    zval* zval_return_value     = NULL;
    zval* zval_prop             = NULL;
    char* lowercase_method_name = NULL;
    zend_class_entry* ce        = NULL;

    if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "z", &zval_name ) == FAILURE ) {
        WRONG_PARAM_COUNT;
    }

    // php function names are stored in lower-case in format the function tables
    lowercase_method_name = estrndup( Z_STRVAL_P( zval_name ), Z_STRLEN_P( zval_name ) );

    zend_str_tolower( lowercase_method_name, Z_STRLEN_P( zval_name ) );
    ce = Z_OBJCE_P( getThis() );

    if ( zend_hash_exists( &ce->function_table, lowercase_method_name, Z_STRLEN_P( zval_name ) + 1 )  ) {
        zend_call_method( &getThis(), ce, NULL, lowercase_method_name, Z_STRLEN_P( zval_name ), &zval_return_value, 0, NULL, NULL TSRMLS_CC );
    } else {
        ALLOC_INIT_ZVAL( zval_prop );
        ZVAL_STRING( zval_prop, lowercase_method_name, 1 );
        zend_call_method( &getThis(), ce, NULL, "custom_property", 15, &zval_return_value, 1, zval_prop , NULL TSRMLS_CC );
        zval_dtor( zval_prop );
    }
    efree( lowercase_method_name );
    RETURN_ZVAL( zval_return_value, 1, 0 )
}

/* \brief
 * returns a reference to the Worksheet object
 *
 * \returns
 * reference to the Worksheet object
 */
static PHP_METHOD( element, worksheet )
{
    PHP_FUNC_CHECK_FOR_READONLY_PROPERTY;

    zval* zval_ws       = NULL;
    zval* zval_ws_uuid  = zend_read_property( wss_element_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_ws_uuid" ), 1 TSRMLS_CC );
    ALLOC_INIT_ZVAL( zval_ws );
    object_init_ex( zval_ws, wss_worksheet_class );
    zend_call_method_with_1_params( &zval_ws, wss_worksheet_class, NULL, "__construct", NULL, zval_ws_uuid );
    RETURN_ZVAL( zval_ws, 1, 0 );
}

/*!
 * \brief
 * returns a reference to the associated worksheet object.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
static PHP_METHOD( element, parent )
{
    PHP_FUNC_CHECK_FOR_READONLY_PROPERTY;

    zval* zval_ws       = NULL;
    zval* zval_ws_uuid  = zend_read_property( wss_element_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_ws_uuid" ), 1 TSRMLS_CC );
    ALLOC_INIT_ZVAL( zval_ws );
    object_init_ex( zval_ws, wss_worksheet_class );
    zend_call_method_with_1_params( &zval_ws, wss_worksheet_class, NULL, "__construct", NULL, zval_ws_uuid );
    RETURN_ZVAL( zval_ws, 1, 0 );
}

/* \brief
 * returns a reference to the uuid object
 *
 * \returns
 * reference to the uuid object
 */
static PHP_METHOD( element, uuid )
{
    PHP_FUNC_CHECK_FOR_READONLY_PROPERTY;

    zval* zval_ret = zend_read_property( wss_element_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_uuid" ), 1 TSRMLS_CC );
    RETURN_ZVAL( zval_ret, 1, 0 )
}

/* \brief
 * accessor for the type object
 *
 * \returns
 * reference to the type object if no parameter is given or null
 */
static PHP_METHOD( element, type )
{
    zval* zval_uuid         = NULL;
    zval* zval_ws_uuid      = NULL;
    char* type_name         = NULL;
    long type_name_len      = 0;

    if ( ZEND_NUM_ARGS() > 0 ) {
        if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "s", &type_name, &type_name_len ) == FAILURE ) {
            WRONG_PARAM_COUNT;
        }
    }

    zval_uuid    = zend_read_property( wss_element_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_uuid" ), 1 TSRMLS_CC );
    zval_ws_uuid = zend_read_property( wss_element_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_ws_uuid" ), 1 TSRMLS_CC );
    GET_SHARED_OBJ( worksheet, zval_ws_uuid );

    if ( NULL == type_name ) {
        RETURN_STRING( const_cast<char*>( shared_obj->elements().get_worksheet_element( *WSS_PHP_G( session_context ), Z_STRVAL_P( zval_uuid ) )->type().c_str() ), 1 )
    } else {
        shared_obj->elements().get_worksheet_element( *WSS_PHP_G( session_context ), Z_STRVAL_P( zval_uuid ) )->type( type_name );
        RETURN_NULL()
    }

}

/* \brief
 * accessor for the is_dirty object
 *
 * \returns
 * reference to the is_dirty object
 */
static PHP_METHOD( element, is_dirty )
{
    PHP_FUNC_CHECK_FOR_READONLY_PROPERTY;


    zval* zval_uuid               = zend_read_property( wss_element_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_uuid" ), 1 TSRMLS_CC );
    zval* zval_ws_uuid            = zend_read_property( wss_element_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_ws_uuid" ), 1 TSRMLS_CC );
    GET_SHARED_OBJ( worksheet, zval_ws_uuid );

    RETURN_BOOL( shared_obj->elements().get_worksheet_element( *WSS_PHP_G( session_context ), Z_STRVAL_P( zval_uuid ) )->is_dirty( *WSS_PHP_G( session_context ) ) );
}

/* \brief
 * accessor for the has_nf object
 *
 * \returns
 * reference to the has_nf object
 */
static PHP_METHOD( element, has_formula )
{
    PHP_FUNC_CHECK_FOR_READONLY_PROPERTY;

    zval* zval_uuid               = zend_read_property( wss_element_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_uuid" ), 1 TSRMLS_CC );
    zval* zval_ws_uuid            = zend_read_property( wss_element_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_ws_uuid" ), 1 TSRMLS_CC );
    GET_SHARED_OBJ( worksheet, zval_ws_uuid );

    RETURN_BOOL( shared_obj->elements().get_worksheet_element( *WSS_PHP_G( session_context ), Z_STRVAL_P( zval_uuid ) )->has_nf( ) );
}

/* \brief
 * accessor for the has_location_nf object
 *
 * \returns
 * reference to the has_location_nf object
 */
static PHP_METHOD( element, has_location_formula )
{
    PHP_FUNC_CHECK_FOR_READONLY_PROPERTY;

    zval* zval_uuid               = zend_read_property( wss_element_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_uuid" ), 1 TSRMLS_CC );
    zval* zval_ws_uuid            = zend_read_property( wss_element_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_ws_uuid" ), 1 TSRMLS_CC );
    GET_SHARED_OBJ( worksheet, zval_ws_uuid );

    RETURN_BOOL( shared_obj->elements().get_worksheet_element( *WSS_PHP_G( session_context ), Z_STRVAL_P( zval_uuid ) )->has_location_nf( ) );
}

/* \brief
 * accessor for the get_nf_value object
 *
 * \returns
 * reference to the get_nf_value object
 */
static PHP_METHOD( element, formula_value )
{
    PHP_FUNC_CHECK_FOR_READONLY_PROPERTY;

    zval* zval_ret       = NULL;
    zval* zval_uuid      = zend_read_property( wss_element_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_uuid" ), 1 TSRMLS_CC );
    zval* zval_ws_uuid   = zend_read_property( wss_element_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_ws_uuid" ), 1 TSRMLS_CC );
    GET_SHARED_OBJ( worksheet, zval_ws_uuid );

    variant nf_value = shared_obj->elements().get_worksheet_element( *WSS_PHP_G( session_context ), Z_STRVAL_P( zval_uuid ) )->get_nf_value( *WSS_PHP_G( session_context ) );

    ALLOC_INIT_ZVAL( zval_ret );
    value_converter()( WSS_PHP_G( session_context )->locale(), zval_ret, nf_value );

    RETURN_ZVAL( zval_ret, 1, 1 )
}

/* \brief
 * returns a reference to the val indexed by key if it exists, NULL otherwise
 *
 * \returns
 * reference to the val if the val is not give. assigns val to key otherwise
 */
static PHP_METHOD( element, custom_property )
{
    zval* zval_key      = NULL;
    zval* zval_val      = NULL;
    zval* zval_uuid     = NULL;
    zval* zval_ws_uuid  = NULL;

    if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "z|z", &zval_key, &zval_val ) == FAILURE ) {
        WRONG_PARAM_COUNT;
    }

    zval_uuid = zend_read_property( wss_element_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_uuid" ), 1 TSRMLS_CC );
    zval_ws_uuid = zend_read_property( wss_element_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_ws_uuid" ), 1 TSRMLS_CC );
    GET_SHARED_OBJ( worksheet, zval_ws_uuid );


    BEGIN_CORE_CATCH_BLOCK()
    if ( NULL == zval_val ) {    //get
        variant prop_value;
        try {
            prop_value = shared_obj->elements().get_worksheet_element( *WSS_PHP_G( session_context ), Z_STRVAL_P( zval_uuid ) )->property( *WSS_PHP_G( session_context ), Z_STRVAL_P( zval_key )  ).second;
        } catch ( worksheet_element_exception& ) {
            //property does not exists
            RETURN_NULL();
        }
        zval* zval_ret = NULL;
        ALLOC_INIT_ZVAL( zval_ret );
        value_converter()( WSS_PHP_G( session_context )->locale(), zval_ret, prop_value );
        RETURN_ZVAL( zval_ret, 1, 1 )
    } else {       //set
        worksheet_element::key_value_type    pair;

        pair.first  = Z_STRVAL_P( zval_key );
        pair.second = value_converter()( zval_val TSRMLS_CC );

        shared_obj->elements().get_worksheet_element( *WSS_PHP_G( session_context ), Z_STRVAL_P( zval_uuid ) )->property( *WSS_PHP_G( session_context ), pair  );

        RETURN_NULL()
    }
    END_CORE_CATCH_BLOCK()
}

/* \brief
 * returns a reference to the val of the system key location
 *
 * \returns
 * reference to the val if the val is not give. assigns val to key otherwise
 */
static PHP_METHOD( element, location )
{
    zval* zval_value        = NULL;
    zval* zval_uuid         = NULL;
    zval* zval_ws_uuid      = NULL;

    if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "|z", &zval_value ) == FAILURE ) {
        WRONG_PARAM_COUNT;
    }

    zval_uuid = zend_read_property( wss_element_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_uuid" ), 1 TSRMLS_CC );
    zval_ws_uuid = zend_read_property( wss_element_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_ws_uuid" ), 1 TSRMLS_CC );
    GET_SHARED_OBJ( worksheet, zval_ws_uuid );

    BEGIN_CORE_CATCH_BLOCK()
    if ( NULL == zval_value ) {    //get
        variant prop_value = shared_obj->elements().get_worksheet_element( *WSS_PHP_G( session_context ), Z_STRVAL_P( zval_uuid ) )->property( *WSS_PHP_G( session_context ), "n_location"  ).second;
        zval* zval_ret = NULL;
        ALLOC_INIT_ZVAL( zval_ret );
        value_converter()( WSS_PHP_G( session_context )->locale(), zval_ret, prop_value );
        RETURN_ZVAL( zval_ret, 1, 1 )
    } else {       //set
        worksheet_element::key_value_type    pair;

        pair.first  = "n_location";
        pair.second = value_converter()( zval_value TSRMLS_CC );

        shared_obj->elements().get_worksheet_element( *WSS_PHP_G( session_context ), Z_STRVAL_P( zval_uuid ) )->property( *WSS_PHP_G( session_context ), pair  );

        RETURN_NULL()
    }
    END_CORE_CATCH_BLOCK()
}

/* \brief
 * returns a reference to the val of the system key refers_to
 *
 * \returns
 * reference to the val if the val is not give. assigns val to key otherwise
 */
static PHP_METHOD( element, refers_to )
{
    zval* zval_value    = NULL;
    zval* zval_uuid     = NULL;
    zval* zval_ws_uuid  = NULL;
    if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "|z", &zval_value ) == FAILURE ) {
        WRONG_PARAM_COUNT;
    }

    zval_uuid = zend_read_property( wss_element_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_uuid" ), 1 TSRMLS_CC );
    zval_ws_uuid = zend_read_property( wss_element_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_ws_uuid" ), 1 TSRMLS_CC );
    GET_SHARED_OBJ( worksheet, zval_ws_uuid );

    BEGIN_CORE_CATCH_BLOCK()
    if ( NULL == zval_value ) {    //get
        variant prop_value = shared_obj->elements().get_worksheet_element( *WSS_PHP_G( session_context ), Z_STRVAL_P( zval_uuid ) )->property( *WSS_PHP_G( session_context ), "n_refers_to"  ).second;
        zval* zval_ret = NULL;
        ALLOC_INIT_ZVAL( zval_ret );
        value_converter()( WSS_PHP_G( session_context )->locale(), zval_ret, prop_value );
        RETURN_ZVAL( zval_ret, 1, 1 )
    } else {       //set
        worksheet_element::key_value_type    pair;

        pair.first  = "n_refers_to";
        pair.second = value_converter()( zval_value TSRMLS_CC );

        shared_obj->elements().get_worksheet_element( *WSS_PHP_G( session_context ), Z_STRVAL_P( zval_uuid ) )->property( *WSS_PHP_G( session_context ), pair  );

        RETURN_NULL()
    }
    END_CORE_CATCH_BLOCK()
}

/* \brief
 * list of all methods of the worksheet_element object and their access modifiers
 *
 * \see
 * register_worksheet_element_object
 */
static zend_function_entry wss_element_functions[] = {
    PHP_ME( element, __construct, wss_one_arg, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR )
    PHP_ME( element, __set, wss_two_args, ZEND_ACC_PUBLIC )
    PHP_ME( element, __get, wss_one_arg, ZEND_ACC_PUBLIC )
    PHP_ME( element, parent, wss_no_args, ZEND_ACC_PUBLIC )
    PHP_ME( element, worksheet, wss_no_args, ZEND_ACC_PUBLIC )
    PHP_ME( element, uuid, wss_no_args, ZEND_ACC_PUBLIC )
    PHP_ME( element, type, wss_no_args, ZEND_ACC_PUBLIC )
    PHP_ME( element, is_dirty, wss_no_args, ZEND_ACC_PUBLIC )
    PHP_ME( element, has_formula, wss_no_args, ZEND_ACC_PUBLIC )
    PHP_ME( element, has_location_formula, wss_no_args, ZEND_ACC_PUBLIC )
    PHP_ME( element, formula_value, wss_two_args, ZEND_ACC_PUBLIC )
    PHP_ME( element, custom_property, wss_two_args, ZEND_ACC_PRIVATE )
    PHP_ME( element, location, wss_one_arg, ZEND_ACC_PUBLIC )
    PHP_ME( element, refers_to, wss_one_arg, ZEND_ACC_PUBLIC ) {
        NULL, NULL, NULL
    }
};

void register_worksheet_element_object( TSRMLS_D )
{
    // register internal wss<=>php wrapper objects
    zend_class_entry ce;

    INIT_CLASS_ENTRY( ce, "element", wss_element_functions );
    wss_element_class = zend_register_internal_class( &ce TSRMLS_CC );
    zend_declare_property_null( wss_element_class, WSS_PHP_STRING_NO_NULL( "m_ws_uuid" ), ZEND_ACC_PRIVATE TSRMLS_CC );
    zend_declare_property_null( wss_element_class, WSS_PHP_STRING_NO_NULL( "m_uuid" ), ZEND_ACC_PRIVATE TSRMLS_CC );
}
