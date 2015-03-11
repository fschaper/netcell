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

zend_class_entry* wss_worksheets_class;

extern zend_class_entry* wss_application_class;
extern zend_class_entry* wss_workbook_class;
extern zend_class_entry* wss_workbooks_class;
extern zend_class_entry* wss_worksheet_class;
extern zend_class_entry* wss_wss_exception_class;

ZEND_EXTERN_MODULE_GLOBALS( wssme );

/* \brief
 * constructs a new worksheets wrapper object
 *
 * \params uuid
 * The workbook having this worksheet colection
 */
static PHP_METHOD( worksheets, __construct )
{
    zval* zval_wb       = NULL;
    zval* zval_wb_uuid  = NULL;

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
        zend_update_property_string( wss_worksheets_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_wb_uuid" ), const_cast<char*>( uuid.c_str() ) TSRMLS_CC );
    } else {
        zval_wb_uuid = zend_read_property( wss_workbook_class, zval_wb, WSS_PHP_STRING_NO_NULL( "m_uuid" ), 1 TSRMLS_CC );
        zend_update_property_string( wss_worksheets_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_wb_uuid" ), Z_STRVAL_P( zval_wb_uuid ) TSRMLS_CC );
    }
}

PHP_PROPERTY_SETTER( worksheets );
PHP_PROPERTY_GETTER( worksheets );

/* \brief
 * returns a reference to the Workbook object
 *
 * \returns
 * reference to the Workbook object
 */
static PHP_METHOD( worksheets, parent )
{
    zval* zval_wb        = NULL;
    zval* zval_wb_uuid   = zend_read_property( wss_worksheets_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_wb_uuid" ), 1 TSRMLS_CC );

    ALLOC_INIT_ZVAL( zval_wb );
    object_init_ex( zval_wb, wss_workbook_class );
    zend_call_method_with_1_params( &zval_wb, wss_workbook_class, NULL, "__construct", NULL, zval_wb_uuid );
    RETURN_ZVAL( zval_wb, 1, 0 );
}

/* \brief
 * adds a new, empty worksheet to the collection
 *
 * \params name
 * name of the new worksheet to be added
 *
 * \returns
 * the created worksheet
 */
static PHP_METHOD( worksheets, add )
{
    zval*                zval_wb_uuid       = NULL;
    zval*                zval_ws_uuid       = NULL;
    std::string         new_uuid            = "";
    char*                worksheet_name     = NULL;
    long                worksheet_name_len  = 0;

    if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "s", &worksheet_name, &worksheet_name_len ) == FAILURE ) {
        WRONG_PARAM_COUNT;
    }

    zval_wb_uuid = zend_read_property( wss_worksheets_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_wb_uuid" ), 1 TSRMLS_CC );
    GET_SHARED_OBJ( workbook, zval_wb_uuid );

    BEGIN_CORE_CATCH_BLOCK();
    new_uuid = boost::lexical_cast< std::string >( shared_obj->add( convert_utf8_ci( std::string( worksheet_name ) ) )->uuid() );
    END_CORE_CATCH_BLOCK();

    ALLOC_INIT_ZVAL( zval_ws_uuid );
    ZVAL_STRING( zval_ws_uuid, const_cast<char*>( new_uuid.c_str() ), 1 );
    object_init_ex( return_value, wss_worksheet_class );
    zend_call_method_with_1_params( &return_value, wss_worksheet_class, NULL, "__construct", NULL, zval_ws_uuid );
    zval_dtor( zval_ws_uuid );
}

/* \brief
 * removes an existing worksheet
 *
 * \params worksheet
 * the worksheet object
 *
 * \returns
 * nothing
 */
static PHP_METHOD( worksheets, remove )
{
    zval* zval_wb_uuid   = NULL;
    zval* zval_ws        = NULL;
    zval* zval_ws_uuid   = NULL;


    if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "z", &zval_ws ) == FAILURE ) {
        WRONG_PARAM_COUNT;
    }

    zval_ws_uuid    = zend_read_property( wss_worksheet_class, zval_ws, WSS_PHP_STRING_NO_NULL( "m_uuid" ), 1 TSRMLS_CC );
    zval_wb_uuid   = zend_read_property( wss_worksheets_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_wb_uuid" ), 1 TSRMLS_CC );

    GET_SHARED_OBJ( workbook, zval_wb_uuid );

    const uuid_type ws_uuid = boost::lexical_cast< uuid_type >( Z_STRVAL_P( zval_ws_uuid ) );

    BEGIN_CORE_CATCH_BLOCK();
    shared_obj->remove( ws_uuid );
    END_CORE_CATCH_BLOCK();
}

/* \brief
 * returns the number of worksheets in the collection
 *
 * \returns
 * the number of worksheets
 */
static PHP_METHOD( worksheets, count )
{
    zval* zval_wb_uuid      = zend_read_property( wss_worksheets_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_wb_uuid" ), 1 TSRMLS_CC );
    GET_SHARED_OBJ( workbook, zval_wb_uuid );
    RETURN_LONG( ( long ) shared_obj->count() );
}

/* \brief
 * returns the worksheet identified by uuid
 *
 * \param
 * the uuid of the worksheet
 *
 * \returns
 * the worksheet identified by uuid
 */
static PHP_METHOD( worksheets, item )
{
    char*    ws_uuid        = NULL;
    size_t  ws_uuid_length  = 0;
    zval*    zval_wb_uuid   = NULL;
    zval*    zval_ws        = NULL;
    zval*    zval_ws_uuid   = NULL;

    if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "s", &ws_uuid, &ws_uuid_length ) == FAILURE ) {
        WRONG_PARAM_COUNT;
    }

    zval_wb_uuid = zend_read_property( wss_worksheets_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_wb_uuid" ), 1 TSRMLS_CC );
    GET_SHARED_OBJ( workbook, zval_wb_uuid );

    BEGIN_CORE_CATCH_BLOCK();
    //validate the uuid
    {
        shared_worksheet_type ws;
        if ( ws = shared_obj->get( *WSS_PHP_G( session_context ), ws_uuid  ) ) {
            const std::string& s = boost::lexical_cast<std::string>( ws->uuid() );
            ws_uuid = _strdup( s.c_str() );
            ws_uuid_length = s.length();
        }
    }
    END_CORE_CATCH_BLOCK();

    ALLOC_INIT_ZVAL( zval_ws_uuid );
    ZVAL_STRING( zval_ws_uuid, ws_uuid, 1 );
    ALLOC_INIT_ZVAL( zval_ws );
    object_init_ex( zval_ws, wss_worksheet_class );
    zend_call_method_with_1_params( &zval_ws, wss_worksheet_class, NULL, "__construct", NULL, zval_ws_uuid );
    zval_dtor( zval_ws_uuid );
    RETURN_ZVAL( zval_ws, 1, 0 );
}

/*!
 * \brief
 * returns the uuid of the worksheets object
 *
 * \returns
 * unique identifier of the worksheets object
 */
static PHP_METHOD( worksheets, uuid )
{
    PHP_FUNC_CHECK_FOR_READONLY_PROPERTY;

    zval* zval_uuid = zend_read_property( wss_worksheets_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_wb_uuid" ), 1 TSRMLS_CC );
    RETURN_ZVAL( zval_uuid, 1, 0 )
}

/* \brief
 * list of all methods of the worksheets object and their access modifiers
 *
 * \see
 * register_worksheets_object
 */
static zend_function_entry wss_worksheets_functions[] = {
    PHP_ME( worksheets, __construct, wss_one_arg, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR )
    PHP_ME( worksheets, __set, wss_two_args, ZEND_ACC_PUBLIC )
    PHP_ME( worksheets, __get, wss_one_arg, ZEND_ACC_PUBLIC )
    PHP_ME( worksheets, parent, wss_no_args, ZEND_ACC_PUBLIC )
    PHP_MALIAS( worksheets, workbook, parent, wss_no_args, ZEND_ACC_PUBLIC )
    PHP_ME( worksheets, add, wss_one_arg, ZEND_ACC_PUBLIC )
    PHP_ME( worksheets, remove, wss_one_arg, ZEND_ACC_PUBLIC )
    PHP_ME( worksheets, uuid, wss_no_args, ZEND_ACC_PUBLIC )
    PHP_ME( worksheets, count, wss_no_args, ZEND_ACC_PUBLIC )
    PHP_ME( worksheets, item, wss_one_arg, ZEND_ACC_PUBLIC ) {
        NULL, NULL, NULL
    }
};

void register_worksheets_object( TSRMLS_D )
{
    // register internal wss<=>php wrapper objects
    zend_class_entry ce;

    INIT_CLASS_ENTRY( ce, "worksheets", wss_worksheets_functions );
    wss_worksheets_class = zend_register_internal_class( &ce TSRMLS_CC );
    zend_declare_property_null( wss_worksheets_class, WSS_PHP_STRING_NO_NULL( "m_wb_uuid" ), ZEND_ACC_PRIVATE TSRMLS_CC );
}
