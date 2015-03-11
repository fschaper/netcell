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
 *  Radu Ialovoi <ialovoi@yalos-solutions.com>
 */

#include "precompiled_header.hpp"
#include <wss/worksheet.hpp>
#include <wss/server.hpp>
#include <wss/object_registry.hpp>
#include "logging.hpp"
#include "php_includes.hpp"

#ifdef __GNUC__
#define VARIABLE_IS_NOT_USED __attribute__ ((unused))
#else
#define VARIABLE_IS_NOT_USED
#endif


zend_class_entry* wss_wss_exception_class;

/* \brief
 * constructs a new PHP row wrapper object
 */
static PHP_METHOD( wss_exception, __construct )
{
    char* message         = NULL;
    long message_len      = 0;
    long code             = 0;

    if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "sl", &message, &message_len, &code ) == FAILURE ) {
        WRONG_PARAM_COUNT;
    }

    zend_update_property_string( wss_wss_exception_class, getThis(), WSS_PHP_STRING_NO_NULL( "message" ), message TSRMLS_CC );
    zend_update_property_long( wss_wss_exception_class, getThis(), WSS_PHP_STRING_NO_NULL( "code" ), code TSRMLS_CC );
}

VARIABLE_IS_NOT_USED PHP_PROPERTY_SETTER( wss_exception );
VARIABLE_IS_NOT_USED PHP_PROPERTY_GETTER( wss_exception );

/* \brief
 * list of all methods of the wss_exception object and their access modifiers
 *
 * \see
 * register_wss_exception_object
 */
static zend_function_entry wss_wss_exception_functions[] = {
    PHP_ME( wss_exception, __construct, wss_one_arg, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR ) {
        NULL, NULL, NULL
    }
};

void register_core_exception_object( TSRMLS_D )
{
    zend_class_entry* exception_ce = zend_exception_get_default( TSRMLS_C );
    zend_class_entry ce;
    INIT_CLASS_ENTRY( ce, "wss_exception", wss_wss_exception_functions );
    wss_wss_exception_class = zend_register_internal_class_ex( &ce, exception_ce, "Exception" TSRMLS_CC );
}
