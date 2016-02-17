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

zend_class_entry* wss_attribute_class;
extern zend_class_entry* wss_workbooks_class;
extern zend_class_entry* wss_wss_exception_class;

ZEND_EXTERN_MODULE_GLOBALS( wssme );

/* \brief
 * constructs a new PHP attribute wrapper object
 */
static PHP_METHOD( attribute, __construct )
{
    char* key           = NULL;
    long length         = 0;
    zval* zval_value    = NULL;

    if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "sz", &key, &length, &zval_value ) == FAILURE ) {
        BEGIN_CORE_CATCH_BLOCK()
        throw fatal_exception( "WRONG_PARAM_COUNT" );
        END_CORE_CATCH_BLOCK()
        WRONG_PARAM_COUNT;
    }

    zend_update_property_string( wss_attribute_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_key" ), key TSRMLS_CC );
    zend_update_property( wss_attribute_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_value" ), zval_value TSRMLS_CC );
}

PHP_PROPERTY_SETTER( attribute );
PHP_PROPERTY_GETTER( attribute );

/* \brief
 * accessors for the value
 *
 * \param value
 * optional new value
 *
 * \returns
 * the value if no parameters given. null otherwise
 */
static PHP_METHOD( attribute, value )
{
    zval* zval_value = NULL;

    if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "|z", &zval_value ) == FAILURE ) {
        WRONG_PARAM_COUNT;
    }

    if ( zval_value ) {
        zend_update_property( wss_attribute_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_value" ), zval_value TSRMLS_CC );
    } else {
        zval_value = zend_read_property( wss_attribute_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_value" ), 1 TSRMLS_CC );
    }
    RETURN_ZVAL( zval_value, 1, 0 );
}

/* \brief
 * accessors for the key
 *
 * \param key
 * optional new key
 *
 * \returns
 * the key if no parameters given. null otherwise
 */
static PHP_METHOD( attribute, key )
{
    char* key = NULL;
    long length = 0;

    if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "|s", &key, &length ) == FAILURE ) {
        WRONG_PARAM_COUNT;
    }

    if ( ZEND_NUM_ARGS() > 0 ) {
        if ( ! length ) {
            zend_throw_exception( zend_exception_get_default( TSRMLS_C ), "attribute key must be of string type and can not be null!", 0 TSRMLS_CC );
            return;
        }
        zend_update_property_string( wss_attribute_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_key" ), key TSRMLS_CC );
        RETURN_NULL();
    } else {
        zval* zval_key = zend_read_property( wss_attribute_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_key" ), 1 TSRMLS_CC );
        RETURN_ZVAL( zval_key, 1, 0 );
    }
}

/* \brief
 * list of all methods of the attribute object and their access modifiers
 *
 * \see
 * register_attribute_object
 */
static zend_function_entry wss_attribute_functions[] = {
    PHP_ME( attribute, __construct, wss_one_arg, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR )
    PHP_ME( attribute, __set, wss_two_args, ZEND_ACC_PUBLIC )
    PHP_ME( attribute, __get, wss_one_arg, ZEND_ACC_PUBLIC )
    PHP_ME( attribute, key, NULL, ZEND_ACC_PUBLIC )
    PHP_ME( attribute, value, NULL, ZEND_ACC_PUBLIC ) {
        NULL, NULL, NULL
    }
};

void register_attribute_object( TSRMLS_D )
{
    // register internal wss<=>php wrapper objects
    zend_class_entry ce;

    INIT_CLASS_ENTRY( ce, "attribute", wss_attribute_functions );
    wss_attribute_class = zend_register_internal_class( &ce TSRMLS_CC );
    zend_declare_property_null( wss_attribute_class, WSS_PHP_STRING_NO_NULL( "m_key" ), ZEND_ACC_PRIVATE TSRMLS_CC );
    zend_declare_property_long( wss_attribute_class, WSS_PHP_STRING_NO_NULL( "m_value" ), -1, ZEND_ACC_PRIVATE TSRMLS_CC );
}
