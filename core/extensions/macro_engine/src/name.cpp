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
#include <wss/i_named_formula_manager.hpp>

zend_class_entry* wss_name_class;

extern zend_class_entry* wss_names_class;
extern zend_class_entry* wss_workbook_class;
extern zend_class_entry* wss_wss_exception_class;

ZEND_EXTERN_MODULE_GLOBALS( wssme );

static PHP_METHOD( name, __construct )
{
    zval* zval_wb          = NULL;
    zval* zval_wb_uuid     = NULL;

    char* name              = NULL;
    long name_len           = 0;

    shared_named_formula_accessor_type shared_nf;

    if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "s|z", &name, &name_len, &zval_wb ) == FAILURE ) {
        BEGIN_CORE_CATCH_BLOCK()
        throw fatal_exception( "WRONG_PARAM_COUNT" );
        END_CORE_CATCH_BLOCK()
        WRONG_PARAM_COUNT;
    }

    BEGIN_CORE_CATCH_BLOCK();
    if ( NULL == zval_wb ) {

        const shared_workbook_type shared_obj = WSS_PHP_G( session_context )->selected().workbook().lock();
        TEST_SHARED_OBJ( shared_obj );

        shared_nf = shared_obj->named_formulas().create_and_get_accessor(
                        *( WSS_PHP_G( session_context ) ),
                        name,
                        variant( "=$A$1" ),
                        named_formula_scope::workbook_scope,
                        ( WSS_PHP_G( session_context ) )->selected().worksheet().lock() );

        std::string uuid = boost::lexical_cast< std::string >( shared_obj->uuid() );
        zend_update_property_string( wss_name_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_wb_uuid" ), const_cast<char*>( uuid.c_str() ) TSRMLS_CC );


    } else {

        zend_call_method_with_0_params( &zval_wb, wss_workbook_class, NULL, "uuid", &zval_wb_uuid );
        GET_SHARED_OBJ( workbook, zval_wb_uuid );
        if ( shared_obj->named_formulas().exists( named_formula_identifier( name,  boost::uuids::nil_uuid() ) ) ) {
            shared_nf = shared_obj->named_formulas().get_accessor( *( WSS_PHP_G( session_context ) ), named_formula_identifier( name,  boost::uuids::nil_uuid() ) );
        } else {
            shared_nf = shared_obj->named_formulas().create_and_get_accessor(
                            *( WSS_PHP_G( session_context ) ),
                            name,
                            variant( "=$A$1" ),
                            named_formula_scope::workbook_scope,
                            ( WSS_PHP_G( session_context ) )->selected().worksheet().lock() );
        }
        zend_update_property_string( wss_name_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_wb_uuid" ), Z_STRVAL_P( zval_wb_uuid ) TSRMLS_CC );
    }

    std::string uuid = boost::lexical_cast< std::string >( shared_nf->uuid() );
    zend_update_property_string( wss_name_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_uuid" ), const_cast<char*>( uuid.c_str() ) TSRMLS_CC );
    END_CORE_CATCH_BLOCK();
}

PHP_PROPERTY_SETTER( name );
PHP_PROPERTY_GETTER( name );

static PHP_METHOD( name, parent )
{
    zval* zval_wb       = NULL;
    zval* zval_names    = NULL;
    zval* zval_wb_uuid  = zend_read_property( wss_name_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_wb_uuid" ), 1 TSRMLS_CC );
    ALLOC_INIT_ZVAL( zval_wb );
    object_init_ex( zval_wb, wss_workbook_class );
    zend_call_method_with_1_params( &zval_wb, wss_workbook_class, NULL, "__construct", NULL, zval_wb_uuid );
    ALLOC_INIT_ZVAL( zval_names );
    object_init_ex( zval_names, wss_names_class );
    zend_call_method_with_1_params( &zval_names, wss_names_class, NULL, "__construct", NULL, zval_wb );
    zval_dtor( zval_wb );
    RETURN_ZVAL( zval_names, 1, 0 );
}

static PHP_METHOD( name, refers_to )
{
    char* formula = NULL;
    long formula_len = 0;

    zval* zval_uuid = zend_read_property( wss_name_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_uuid" ), 1 TSRMLS_CC );
    zval* zval_wb_uuid = zend_read_property( wss_name_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_wb_uuid" ), 1 TSRMLS_CC );
    GET_SHARED_OBJ( workbook, zval_wb_uuid );

    BEGIN_CORE_CATCH_BLOCK();
    uuid_type boost_uuid = boost::lexical_cast< uuid_type >( Z_STRVAL_P( zval_uuid ) );
    shared_named_formula_accessor_type shared_nf = shared_obj->named_formulas().get_accessor( *( WSS_PHP_G( session_context ) ), boost_uuid );

    if ( ZEND_NUM_ARGS() > 0 ) {
        if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "s", &formula, &formula_len ) == FAILURE ) {
            WRONG_PARAM_COUNT;
        }
    }

    if ( NULL == formula ) {
        const std::string return_formula = shared_nf->formula( WSS_PHP_G( session_context )->locale() ).string();
        ZVAL_STRING( return_value, const_cast<char*>( return_formula.c_str() ), 1 );
    } else {
        shared_nf->value( *( WSS_PHP_G( session_context ) ), variant( formula ) );
    }
    END_CORE_CATCH_BLOCK();
}

static PHP_METHOD( name, name )
{
    char* name = NULL;
    long name_len = 0;
    if ( ZEND_NUM_ARGS() > 0 ) {
        if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "s", &name, &name_len ) == FAILURE ) {
            WRONG_PARAM_COUNT;
        }
    }

    zval* zval_uuid = zend_read_property( wss_name_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_uuid" ), 1 TSRMLS_CC );
    zval* zval_wb_uuid = zend_read_property( wss_name_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_wb_uuid" ), 1 TSRMLS_CC );
    GET_SHARED_OBJ( workbook, zval_wb_uuid );

    BEGIN_CORE_CATCH_BLOCK();
    uuid_type boost_uuid;
    try {
        boost_uuid = boost::lexical_cast< uuid_type >( Z_STRVAL_P( zval_uuid ) );
    } catch ( std::bad_cast& ) {
        throw invalid_name_exception();
    }
    shared_named_formula_accessor_type shared_nf = shared_obj->named_formulas().get_accessor( *( WSS_PHP_G( session_context ) ), boost_uuid );

    if ( NULL == name ) {
        const std::string return_name = shared_nf->name();
        ZVAL_STRING( return_value, const_cast<char*>( return_name.c_str() ), 1 );
    } else {
        variant formula = shared_nf->formula( ( WSS_PHP_G( session_context ) )->locale() );
        shared_obj->named_formulas().remove( *( WSS_PHP_G( session_context ) ), shared_nf->uuid() );
        shared_nf = shared_obj->named_formulas().create_and_get_accessor(
                        *( WSS_PHP_G( session_context ) ),
                        name,
                        formula,
                        named_formula_scope::workbook_scope,
                        ( WSS_PHP_G( session_context ) )->selected().worksheet().lock() );

        std::string uuid = boost::lexical_cast< std::string >( shared_obj->uuid() );
        zend_update_property_string( wss_name_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_wb_uuid" ), const_cast<char*>( uuid.c_str() ) TSRMLS_CC );
    }
    END_CORE_CATCH_BLOCK();
}

static PHP_METHOD( name, value )
{
    zval* zval_uuid = zend_read_property( wss_name_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_uuid" ), 1 TSRMLS_CC );
    zval* zval_wb_uuid = zend_read_property( wss_name_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_wb_uuid" ), 1 TSRMLS_CC );
    GET_SHARED_OBJ( workbook, zval_wb_uuid );

    BEGIN_CORE_CATCH_BLOCK();
    uuid_type boost_uuid;
    try {
        boost_uuid = boost::lexical_cast< uuid_type >( Z_STRVAL_P( zval_uuid ) );
    } catch ( std::bad_cast& ) {
        throw invalid_name_exception();
    }
    shared_named_formula_accessor_type shared_nf = shared_obj->named_formulas().get_accessor( *( WSS_PHP_G( session_context ) ), boost_uuid );

    variant nf_value = shared_nf->value( *( WSS_PHP_G( session_context ) ) );
    value_converter()( ( WSS_PHP_G( session_context ) )->locale(), return_value, nf_value );
    END_CORE_CATCH_BLOCK();
}

static PHP_METHOD( name, delete )
{
    zval* zval_uuid = zend_read_property( wss_name_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_uuid" ), 1 TSRMLS_CC );
    zval* zval_wb_uuid = zend_read_property( wss_name_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_wb_uuid" ), 1 TSRMLS_CC );
    GET_SHARED_OBJ( workbook, zval_wb_uuid );

    BEGIN_CORE_CATCH_BLOCK();
    uuid_type boost_uuid;
    try {
        boost_uuid = boost::lexical_cast< uuid_type >( Z_STRVAL_P( zval_uuid ) );
    } catch ( std::bad_cast& ) {
        throw invalid_name_exception();
    }
    shared_named_formula_accessor_type shared_nf = shared_obj->named_formulas().get_accessor( *( WSS_PHP_G( session_context ) ), boost_uuid );
    shared_obj->named_formulas().remove( *( WSS_PHP_G( session_context ) ), shared_nf->uuid() );
    END_CORE_CATCH_BLOCK();
}
static zend_function_entry wss_name_functions[] = {
    PHP_ME( name, __construct, wss_one_arg, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR )
    PHP_ME( name, __set, wss_two_args, ZEND_ACC_PUBLIC )
    PHP_ME( name, __get, wss_one_arg, ZEND_ACC_PUBLIC )
    PHP_ME( name, parent, wss_no_args, ZEND_ACC_PUBLIC )
    PHP_ME( name, refers_to, wss_one_arg, ZEND_ACC_PUBLIC )
    PHP_ME( name, value, wss_no_args, ZEND_ACC_PUBLIC )
    PHP_ME( name, delete, wss_no_args, ZEND_ACC_PUBLIC )
    PHP_MALIAS( name, formula, refers_to, wss_one_arg, ZEND_ACC_PUBLIC )
    PHP_MALIAS( name, remove, delete, wss_one_arg, ZEND_ACC_PUBLIC )
    PHP_ME( name, name, wss_one_arg, ZEND_ACC_PUBLIC ) {
        NULL, NULL, NULL
    }
};

void register_name_object( TSRMLS_D )
{
    // register internal wss<=>php wrapper objects
    zend_class_entry ce;

    INIT_CLASS_ENTRY( ce, "name", wss_name_functions );
    wss_name_class = zend_register_internal_class( &ce TSRMLS_CC );
    zend_declare_property_null( wss_name_class, WSS_PHP_STRING_NO_NULL( "m_wb_uuid" ), ZEND_ACC_PRIVATE TSRMLS_CC );
    zend_declare_property_null( wss_name_class, WSS_PHP_STRING_NO_NULL( "m_uuid" ), ZEND_ACC_PRIVATE TSRMLS_CC );
}
