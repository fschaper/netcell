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


zend_class_entry* wss_names_class;

extern zend_class_entry* wss_workbook_class;
extern zend_class_entry* wss_name_class;
extern zend_class_entry* wss_wss_exception_class;

ZEND_EXTERN_MODULE_GLOBALS( wssme );

/* \brief
 * constructs a new PHP names wrapper object
 *
 * \param uuid
 * uuid of the worksheet this object enumerates
 */
static PHP_METHOD( names, __construct )
{
    zval* zval_wb           = NULL;
    zval* zval_wb_uuid      = NULL;

    if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "|z", &zval_wb ) == FAILURE ) {
        BEGIN_CORE_CATCH_BLOCK()
        throw fatal_exception( "WRONG_PARAM_COUNT" );
        END_CORE_CATCH_BLOCK()
        WRONG_PARAM_COUNT;
    }

    if ( NULL == zval_wb ) {
        //defaults for the active workbook
        const shared_workbook_type workbook = WSS_PHP_G( session_context )->selected().workbook().lock();
        TEST_SHARED_OBJ( workbook );
        const std::string uuid( boost::lexical_cast<std::string>( workbook->uuid() ) );
        zend_update_property_string( wss_names_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_wb_uuid" ), const_cast<char*>( uuid.c_str() ) TSRMLS_CC );
    } else {
        zend_call_method_with_0_params( &zval_wb, wss_workbook_class, NULL, "uuid", &zval_wb_uuid );
        zend_update_property_string( wss_names_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_wb_uuid" ), Z_STRVAL_P( zval_wb_uuid ) TSRMLS_CC );
    }
}

PHP_PROPERTY_SETTER( names );
PHP_PROPERTY_GETTER( names );

static PHP_METHOD( names, parent )
{
    zval* zval_wb_uuid  = zend_read_property( wss_names_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_wb_uuid" ), 1 TSRMLS_CC );
    zval* zval_wb       = NULL;
    ALLOC_INIT_ZVAL( zval_wb );
    object_init_ex( zval_wb, wss_workbook_class );
    zend_call_method_with_1_params( &zval_wb, wss_workbook_class, NULL, "__construct", NULL, zval_wb_uuid );
    RETURN_ZVAL( zval_wb, 1, 0 );
}

/*!
 * \brief
 * returns the uuid of the application object
 *
 * \returns
 * unique identifier of the application object
 */
static PHP_METHOD( names, uuid )
{
    zval* zval_wb_uuid = zend_read_property( wss_names_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_wb_uuid" ), 1 TSRMLS_CC );
    RETURN_ZVAL( zval_wb_uuid, 1, 0 )
}

static PHP_METHOD( names, add )
{
    zval* zval_name     = NULL;
    zval* zval_wb       = NULL;

    if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "z", &zval_name ) == FAILURE ) {
        WRONG_PARAM_COUNT;
    }

    zend_call_method_with_0_params( &getThis(), wss_names_class, NULL, "parent", &zval_wb );

    object_init_ex( return_value, wss_name_class );
    zend_call_method_with_2_params( &return_value, wss_name_class, NULL, "__construct", NULL, zval_name, zval_wb );
}

static PHP_METHOD( names, delete )
{
    zval* zval_nf       = NULL;
    zval* zval_nf_uuid  = NULL;
    zval* workbook_uuid = NULL;

    if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "z", &zval_nf )  == FAILURE ) {
        WRONG_PARAM_COUNT;
    }

    zval_nf_uuid = zend_read_property( wss_name_class, zval_nf, WSS_PHP_STRING_NO_NULL( "m_uuid" ), 0 TSRMLS_CC );
    workbook_uuid = zend_read_property( wss_names_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_wb_uuid" ), 0 TSRMLS_CC );
    GET_SHARED_OBJ( workbook, workbook_uuid );

    BEGIN_CORE_CATCH_BLOCK();
    uuid_type nf_uuid = boost::lexical_cast< uuid_type >( Z_STRVAL_P( zval_nf_uuid ) );
    shared_named_formula_accessor_type shared_nf = shared_obj->named_formulas().get_accessor( *( WSS_PHP_G( session_context ) ), nf_uuid );
    shared_nf->remove( *( WSS_PHP_G( session_context ) ) );
    END_CORE_CATCH_BLOCK();
}

static zend_function_entry wss_names_functions[] = {
    PHP_ME( names, __construct, wss_one_arg, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR )
    PHP_ME( names, __set, wss_two_args, ZEND_ACC_PUBLIC )
    PHP_ME( names, __get, wss_one_arg, ZEND_ACC_PUBLIC )
    PHP_ME( names, parent, wss_no_args, ZEND_ACC_PUBLIC )
    PHP_ME( names, uuid, wss_no_args, ZEND_ACC_PUBLIC )
    PHP_MALIAS( names, application, parent, wss_no_args, ZEND_ACC_PUBLIC )
    PHP_ME( names, add, wss_one_arg, ZEND_ACC_PUBLIC )
    PHP_ME( names, delete, wss_no_args, ZEND_ACC_PUBLIC )
    PHP_MALIAS( names, item, add, wss_one_arg, ZEND_ACC_PUBLIC ) {
        NULL, NULL, NULL
    }
};

void register_names_object( TSRMLS_D )
{
    // register internal wss<=>php wrapper objects
    zend_class_entry ce;

    INIT_CLASS_ENTRY( ce, "names", wss_names_functions );
    wss_names_class = zend_register_internal_class( &ce TSRMLS_CC );
    zend_declare_property_null( wss_names_class, WSS_PHP_STRING_NO_NULL( "m_wb_uuid" ), ZEND_ACC_PRIVATE TSRMLS_CC );
}
