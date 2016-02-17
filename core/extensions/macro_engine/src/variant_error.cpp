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
 *  Radu Racariu <radu@yalos-solutions.com>
 */

#include "precompiled_header.hpp"
#include "logging.hpp"
#include "php_includes.hpp"

zend_class_entry* wss_variant_error_class;
extern zend_class_entry* wss_wss_exception_class;

ZEND_EXTERN_MODULE_GLOBALS( wssme );

/* \brief
 * constructs a new PHP variant_error wrapper object
 */
static PHP_METHOD( variant_error, __construct )
{
    long error_code = 0;

    if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "l", &error_code ) == FAILURE || !( error_code > variant::dummy && error_code <= variant::error_n_a ) ) {
        BEGIN_CORE_CATCH_BLOCK()
        throw fatal_exception( "WRONG_PARAM_COUNT or invalid error code argument" );
        END_CORE_CATCH_BLOCK()
        WRONG_PARAM_COUNT;
    }

    zend_update_property_long( wss_variant_error_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_error_code" ), static_cast<variant::error_type>( error_code ) TSRMLS_CC );
}

/* \brief
 * wrapper object string representation
 */
static PHP_METHOD( variant_error, __toString )
{
    zval* zval_message = NULL;
    ALLOC_INIT_ZVAL( zval_message );
    zend_call_method_with_0_params( &getThis(), wss_variant_error_class, NULL, "error_message", &zval_message );
    RETURN_ZVAL( zval_message, 1, 0 );
}


PHP_PROPERTY_SETTER( variant_error );
PHP_PROPERTY_GETTER( variant_error );

/*!
 * brief
 * returns/set the error_code of this variant
 *
 * \returns
 * error_code
 */
static PHP_METHOD( variant_error, error_code )
{
    long value = -1;

    if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "|l", &value ) == FAILURE ) {
        WRONG_PARAM_COUNT;
    }

    if ( value > variant::dummy && value <= variant::error_n_a ) {
        zend_update_property_long( wss_variant_error_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_error_code" ), value TSRMLS_CC );
        RETURN_NULL();
    } else {
        zval* zval_err = zend_read_property( wss_variant_error_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_error_code" ), 1 TSRMLS_CC );
        RETURN_ZVAL( zval_err, 1, 0 );
    }
}

/*!
 * brief
 * returns the error_message of this variant
 *
 * \returns
 * error_message
 */
static PHP_METHOD( variant_error, error_message )
{
    PHP_FUNC_CHECK_FOR_READONLY_PROPERTY;

    zval* zval_err = zend_read_property( wss_variant_error_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_error_code" ), 1 TSRMLS_CC );
    variant v( static_cast<variant::error_type>( Z_LVAL_P( zval_err ) ) );
    zval_dtor( zval_err );
    const std::string& s = v.as_string( WSS_PHP_G( session_context )->locale() );
    char* message = const_cast<char*>( s.c_str() );
    RETURN_STRING( message, true );
}

/* \brief
 * list of all methods of the variant_error object and their access modifiers
 *
 * \see
 * register_variant_error_object
 */
static zend_function_entry variant_error_functions[] = {
    PHP_ME( variant_error, __construct, wss_one_arg, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR )
    PHP_ME( variant_error, __toString, wss_no_args, ZEND_ACC_PUBLIC )
    PHP_ME( variant_error, __set, wss_two_args, ZEND_ACC_PUBLIC )
    PHP_ME( variant_error, __get, wss_one_arg, ZEND_ACC_PUBLIC )
    PHP_ME( variant_error, error_code, wss_no_args, ZEND_ACC_PUBLIC )
    PHP_ME( variant_error, error_message, wss_no_args, ZEND_ACC_PUBLIC ) {
        NULL, NULL, NULL
    }
};


void register_variant_error_object( TSRMLS_D )
{
    // register internal wss<=>php wrapper objects
    zend_class_entry ce;

    INIT_CLASS_ENTRY( ce, "variant_error", variant_error_functions );
    wss_variant_error_class = zend_register_internal_class( &ce TSRMLS_CC );
    zend_declare_property_null( wss_variant_error_class, WSS_PHP_STRING_NO_NULL( "m_error_code" ), ZEND_ACC_PRIVATE TSRMLS_CC );
    zend_declare_property_null( wss_variant_error_class, WSS_PHP_STRING_NO_NULL( "m_error_message" ), ZEND_ACC_PRIVATE TSRMLS_CC );

    // promote variant error constants into wrapper class
    REGISTER_CLASS_CONSTANT_LONG( wss_variant_error_class, NUM, variant::error_num )
    REGISTER_CLASS_CONSTANT_LONG( wss_variant_error_class, DIV_NULL, variant::error_div_null )
    REGISTER_CLASS_CONSTANT_LONG( wss_variant_error_class, VALUE, variant::error_value )
    REGISTER_CLASS_CONSTANT_LONG( wss_variant_error_class, REF, variant::error_ref )
    REGISTER_CLASS_CONSTANT_LONG( wss_variant_error_class, NAME, variant::error_name )
    REGISTER_CLASS_CONSTANT_LONG( wss_variant_error_class, NULL, variant::error_null )
    REGISTER_CLASS_CONSTANT_LONG( wss_variant_error_class, NIL, variant::error_null )
    REGISTER_CLASS_CONSTANT_LONG( wss_variant_error_class, NA, variant::error_n_a )

}
