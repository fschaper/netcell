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

#pragma once

// prevent inclusion of the inline math library into
// the object file which includes this header file
#if defined(WIN32) && !defined(_INC_MATH)
# define _INC_MATH
# define WSS_PHP_INCLUDES_DO_UNDEF
#endif

// PHP already declares everything as extern "C" but
// you never now
extern "C"
{
#ifdef WIN32
# pragma warning ( disable: 4311 )
# define _WS2DEF_
#define _WINSOCK2API_
#ifndef NEEDS_SOCKLEN_T
#define HAVE_SOCKLEN_T
#endif
#endif

#include <main/php.h>
#include <main/php_main.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_extensions.h>
#include <Zend/zend_interfaces.h>

#ifdef WIN32
# pragma warning ( default: 4311 )
#endif
}

#ifndef ZTS
#   error "Zend Thread Safety (ZTS) is required for this extension"
#endif

#ifdef WSS_PHP_INCLUDES_DO_UNDEF
# undef _INC_MATH
#endif

#ifdef ZTS
#   include "TSRM.h"
#   define WSS_PHP_G(x) TSRMG(wssme_globals_id, zend_wssme_globals*, x)
#else
#   define WSS_PHP_G(x) (wssme_globals.x)
#endif // ZTS

ZEND_EXTERN_MODULE_GLOBALS( wssme );
class session;

ZEND_BEGIN_MODULE_GLOBALS( wssme )
session* session_context;       // session context
char* active_range;         // active range coordinates (a1)
::interpreter_context* interpreter_context;        // the interpreter context we're running
ZEND_END_MODULE_GLOBALS( wssme )

extern struct _zend_arg_info wss_no_args[1];
extern struct _zend_arg_info wss_one_arg[2];
extern struct _zend_arg_info wss_two_args[3];

#define WSS_PHP_STRING_NO_NULL(x) x, (sizeof(x) - 1)
#define WSS_PHP_STRING(x) x, sizeof(x)

zend_function_entry* get_functions();


#define PHP_FUNC_CHECK_FOR_NO_ARGUMENTS \
    if (ZEND_NUM_ARGS() > 0) { \
        zend_error(E_ERROR, "%s() does not accept any arguments", get_active_function_name(TSRMLS_C)); \
    }

#define PHP_FUNC_CHECK_FOR_READONLY_PROPERTY \
    if (ZEND_NUM_ARGS() > 0) { \
        zend_error(E_ERROR, "%s is a read-only property", get_active_function_name(TSRMLS_C)); \
    }

void register_application_object( TSRMLS_D );
void register_workbook_object( TSRMLS_D );
void register_worksheet_object( TSRMLS_D );
void register_range_object( TSRMLS_D );
void register_attribute_object( TSRMLS_D );
void register_col_object( TSRMLS_D );
void register_worksheet_element_object( TSRMLS_D );
void register_worksheet_elements_object( TSRMLS_D );
void register_row_object( TSRMLS_D );
void register_worksheets_object( TSRMLS_D );
void register_workbooks_object( TSRMLS_D );
void register_names_object( TSRMLS_D );
void register_name_object( TSRMLS_D );
void register_core_exception_object( TSRMLS_D );
void register_variant_error_object( TSRMLS_D );

#define BOOST_UUIDS uuid_type

#define GET_SHARED_OBJ( classname, uuid ) \
    boost::any weak_obj = server::instance().object_registry().get( boost::lexical_cast < BOOST_UUIDS > ( Z_STRVAL_P( uuid ) )  ); \
    if ( weak_obj.empty() ) { \
        zval *zval_err_msg = NULL;\
        ALLOC_INIT_ZVAL( zval_err_msg );\
        ZVAL_STRING( zval_err_msg, "Cannot get object handle.", 1 );\
        \
        zval *zval_err_code = NULL;\
        ALLOC_INIT_ZVAL( zval_err_code );\
        ZVAL_LONG( zval_err_code, 0x000300 );\
        \
        zval *zval_exception  = NULL;\
        ALLOC_INIT_ZVAL( zval_exception );\
        object_init_ex( zval_exception, wss_wss_exception_class );\
        zend_call_method_with_2_params( &zval_exception, wss_wss_exception_class, NULL, "__construct", NULL, zval_err_msg, zval_err_code );\
        zval_dtor( zval_err_msg );\
        zval_dtor( zval_err_code );\
        \
        zend_throw_exception_object( zval_exception,  TSRMLS_C );\
    } \
    shared_##classname##_type shared_obj = boost::any_cast< weak_##classname##_type >( weak_obj ).lock();\
    if ( ! shared_obj )\
    {\
        zval *zval_err_msg = NULL;\
        ALLOC_INIT_ZVAL( zval_err_msg );\
        ZVAL_STRING( zval_err_msg, "Cannot get object handle.", 1 );\
        \
        zval *zval_err_code = NULL;\
        ALLOC_INIT_ZVAL( zval_err_code );\
        ZVAL_LONG( zval_err_code, 0x000300 );\
        \
        zval *zval_exception  = NULL;\
        ALLOC_INIT_ZVAL( zval_exception );\
        object_init_ex( zval_exception, wss_wss_exception_class );\
        zend_call_method_with_2_params( &zval_exception, wss_wss_exception_class, NULL, "__construct", NULL, zval_err_msg, zval_err_code );\
        zval_dtor( zval_err_msg );\
        zval_dtor( zval_err_code );\
        \
        zend_throw_exception_object( zval_exception,  TSRMLS_C );\
    }

/*!
 * \brief
 * php magic method setter
 *
 * proxy method which redirects all parameters to the passed method implementation.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
#define PHP_PROPERTY_SETTER( classname )\
    static PHP_METHOD( classname, __set )\
    {\
        zval *method_name = NULL;\
        zval *value = NULL;\
        \
        if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "zz", &method_name, &value ) == FAILURE ) {\
            WRONG_PARAM_COUNT;\
        }\
        \
        char *lowercase_method_name = estrndup( Z_STRVAL_P( method_name ), Z_STRLEN_P( method_name ) );\
        \
        zend_str_tolower( lowercase_method_name, Z_STRLEN_P( method_name ) );\
        zend_class_entry *ce = Z_OBJCE_P( getThis() );\
        zend_call_method( &getThis(), ce, NULL, lowercase_method_name, Z_STRLEN_P( method_name ), NULL, 1, value, NULL TSRMLS_CC );\
        \
        efree( lowercase_method_name );\
        RETURN_NULL()\
    }


/*!
 * \brief
 * php magic method getter
 *
 * proxy method which redirects all parameters to the passed method implementation.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
#define PHP_PROPERTY_GETTER( classname )\
    static PHP_METHOD( classname, __get )\
    {\
        zval *method_name = NULL;\
        \
        if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "z", &method_name ) == FAILURE ) {\
            WRONG_PARAM_COUNT;\
        }\
        \
        char *lowercase_method_name = estrndup( Z_STRVAL_P( method_name ), Z_STRLEN_P( method_name ) );\
        zend_str_tolower( lowercase_method_name, Z_STRLEN_P( method_name ) );\
        \
        zend_class_entry *ce = Z_OBJCE_P( getThis() );\
        zval *method_return_value = NULL;\
        zend_call_method( &getThis(), ce, NULL, lowercase_method_name, Z_STRLEN_P( method_name ), &method_return_value, 0, NULL, NULL TSRMLS_CC );\
        \
        efree( lowercase_method_name );\
        RETURN_ZVAL( method_return_value, 1, 0 )\
    }
#define BEGIN_CORE_CATCH_BLOCK()\
    try {

#define END_CORE_CATCH_BLOCK()\
    } catch ( wss_runtime_exception& e ) {\
        zval *zval_err_msg = NULL;\
        ALLOC_INIT_ZVAL( zval_err_msg );\
        ZVAL_STRING( zval_err_msg, const_cast<char*>( e.what() ), 1 );\
        \
        zval *zval_err_code = NULL;\
        ALLOC_INIT_ZVAL( zval_err_code );\
        ZVAL_LONG( zval_err_code, e.error_code() );\
        \
        zval *zval_exception  = NULL;\
        ALLOC_INIT_ZVAL( zval_exception );\
        object_init_ex( zval_exception, wss_wss_exception_class );\
        zend_call_method_with_2_params( &zval_exception, wss_wss_exception_class, NULL, "__construct", NULL, zval_err_msg, zval_err_code );\
        zval_dtor( zval_err_msg );\
        zval_dtor( zval_err_code );\
        \
        zend_throw_exception_object( zval_exception TSRMLS_CC );\
    }
#define END_GENERIC_CORE_CATCH_BLOCK()\
    } catch ( const std::exception& e ) {\
        zval *zval_err_msg = NULL;\
        ALLOC_INIT_ZVAL( zval_err_msg );\
        ZVAL_STRING( zval_err_msg, const_cast<char*>( e.what() ), 1 );\
        \
        zval *zval_err_code = NULL;\
        ALLOC_INIT_ZVAL( zval_err_code );\
        ZVAL_LONG( zval_err_code, 0xCAFEBABE );\
        \
        zval *zval_exception  = NULL;\
        ALLOC_INIT_ZVAL( zval_exception );\
        object_init_ex( zval_exception, wss_wss_exception_class );\
        zend_call_method_with_2_params( &zval_exception, wss_wss_exception_class, NULL, "__construct", NULL, zval_err_msg, zval_err_code );\
        zval_dtor( zval_err_msg );\
        zval_dtor( zval_err_code );\
        \
        zend_throw_exception_object( zval_exception TSRMLS_CC );\
    }

//id for object_not_found_exception

#define TEST_SHARED_OBJ( obj )\
    if ( !obj ){\
        zval *zval_err_msg = NULL;\
        ALLOC_INIT_ZVAL( zval_err_msg );\
        ZVAL_STRING( zval_err_msg, "Cannot get object handle.", 1 );\
        \
        zval *zval_err_code = NULL;\
        ALLOC_INIT_ZVAL( zval_err_code );\
        ZVAL_LONG( zval_err_code, 0x000300 );\
        \
        zval *zval_exception  = NULL;\
        ALLOC_INIT_ZVAL( zval_exception );\
        object_init_ex( zval_exception, wss_wss_exception_class );\
        zend_call_method_with_2_params( &zval_exception, wss_wss_exception_class, NULL, "__construct", NULL, zval_err_msg, zval_err_code );\
        zval_dtor( zval_err_msg );\
        zval_dtor( zval_err_code );\
        \
        zend_throw_exception_object( zval_exception,  TSRMLS_C );\
        return;\
    }
#define REGISTER_CLASS_CONSTANT_LONG(CLASS_ENTRY, CONSTANT_NAME, CONSTANT_VALUE) \
    { \
        zend_declare_class_constant_long(CLASS_ENTRY, "" #CONSTANT_NAME "",  sizeof( "" #CONSTANT_NAME "" ) -1 , CONSTANT_VALUE TSRMLS_CC); \
    }
