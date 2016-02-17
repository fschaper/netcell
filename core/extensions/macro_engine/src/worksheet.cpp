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

zend_class_entry* wss_worksheet_class;

extern zend_class_entry* wss_application_class;
extern zend_class_entry* wss_worksheets_class;
extern zend_class_entry* wss_workbook_class;
extern zend_class_entry* wss_range_class;
extern zend_class_entry* wss_elements_class;
extern zend_class_entry* wss_row_class;
extern zend_class_entry* wss_column_class;
extern zend_class_entry* wss_wss_exception_class;

ZEND_EXTERN_MODULE_GLOBALS( wssme );

/* \brief
 * constructs a new PHP worksheet wrapper object
 *
 * \param uuid
 * uuid of the worksheet in wss3
 */
static PHP_METHOD( worksheet, __construct )
{
    char* worksheet_uuid = 0;
    long worksheet_uuid_len = 0;

    if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "|s", &worksheet_uuid, &worksheet_uuid_len ) == FAILURE ) {
        BEGIN_CORE_CATCH_BLOCK()
        throw fatal_exception( "WRONG_PARAM_COUNT" );
        END_CORE_CATCH_BLOCK()
        WRONG_PARAM_COUNT;
    }

    if ( NULL == worksheet_uuid ) {
        //defaults for the active worksheet
        const shared_worksheet_type worksheet = WSS_PHP_G( session_context )->selected().worksheet().lock();
        TEST_SHARED_OBJ( worksheet );
        const std::string uuid( boost::lexical_cast<std::string>( worksheet->uuid() ) );
        zend_update_property_string( wss_worksheet_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_uuid" ), const_cast<char*>( uuid.c_str() ) TSRMLS_CC );
    } else {
        zend_update_property_string( wss_worksheet_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_uuid" ), worksheet_uuid TSRMLS_CC );
    }
}

PHP_PROPERTY_SETTER( worksheet );
PHP_PROPERTY_GETTER( worksheet );

/* \brief
 * returns a reference to the worksheets object
 *
 * \returns
 * reference to the worksheets object
 */
static PHP_METHOD( worksheet, parent )
{
    std::string     wb_uuid         = "";
    zval*            zval_wsts      = NULL;
    zval*            zval_wb        = NULL;
    zval*            zval_wb_uuid   = NULL;
    zval*            zval_ws_uuid   = zend_read_property( wss_worksheet_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_uuid" ), 1 TSRMLS_CC );

    GET_SHARED_OBJ( worksheet, zval_ws_uuid );
    wb_uuid = boost::lexical_cast< std::string > ( shared_obj->parent()->uuid() );

    ALLOC_INIT_ZVAL( zval_wb_uuid );
    ZVAL_STRING( zval_wb_uuid, const_cast<char*>( wb_uuid.c_str() ), 1 );
    ALLOC_INIT_ZVAL( zval_wb );
    object_init_ex( zval_wb, wss_workbook_class );
    zend_call_method_with_1_params( &zval_wb, wss_workbook_class, NULL, "__construct", NULL, zval_wb_uuid );
    ALLOC_INIT_ZVAL( zval_wsts );
    object_init_ex( zval_wsts, wss_worksheets_class );
    zend_call_method_with_1_params( &zval_wsts, wss_worksheets_class, NULL, "__construct", NULL, zval_wb );
    zval_dtor( zval_wb_uuid );
    zval_dtor( zval_wb );
    RETURN_ZVAL( zval_wsts, 1, 0 );
}

/* \brief
 * creates and returns an range object
  *
 * \param a1
 * the a1 notation of the new range
 *
 * \returns
 * an range object
 */
static PHP_METHOD( worksheet, range )
{
    zval* zval_range_a1     = NULL;
    zval* zval_range        = NULL;

    if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "z", &zval_range_a1 ) == FAILURE ) {
        WRONG_PARAM_COUNT;
    }

    ALLOC_INIT_ZVAL( zval_range );
    object_init_ex( zval_range, wss_range_class );
    zend_call_method_with_2_params( &zval_range, wss_range_class, NULL, "__construct", NULL, zval_range_a1, getThis() );

    RETURN_ZVAL( zval_range, 1, 0 );
}

/* \brief
 * creates and returns an range object covering the used rectangle
 *
 * \returns
 * an range object
 */
static PHP_METHOD( worksheet, usedrange )
{
    zval* zval_uuid         = NULL;
    zval* zval_range_a1     = NULL;
    zval* zval_range        = NULL;
    std::string used_range_a1;

    PHP_FUNC_CHECK_FOR_READONLY_PROPERTY;

    zval_uuid = zend_read_property( wss_worksheet_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_uuid" ), 1 TSRMLS_CC );
    GET_SHARED_OBJ( worksheet, zval_uuid );

    optional_sheet_range_type used_range = shared_obj->used_range( used_range::all );

    if ( used_range ) {
        used_range_a1 = a1conversion::to_a1::from_range( *used_range );
    }

    ALLOC_INIT_ZVAL( zval_range );
    object_init_ex( zval_range, wss_range_class );
    ALLOC_INIT_ZVAL( zval_range_a1 );
    ZVAL_STRING( zval_range_a1, const_cast<char*>( used_range_a1.c_str() ), 1 );
    zend_call_method_with_2_params( &zval_range, wss_range_class, NULL, "__construct", NULL, zval_range_a1, getThis() );
    zval_dtor( zval_range_a1 );
    RETURN_ZVAL( zval_range, 1, 0 );
}


/* \brief
 * creates and returns an row object
 *
 * \param index
 * the index of the row in this worksheet
 *
 * \returns
 * a row object
 */
static PHP_METHOD( worksheet, row )
{
    zval* zval_index;

    if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "z", &zval_index ) == FAILURE ) {
        WRONG_PARAM_COUNT;
    }

    zval* row_object;
    ALLOC_INIT_ZVAL( row_object );
    object_init_ex( row_object, wss_row_class );
    zend_call_method_with_2_params( &row_object, wss_row_class, NULL, "__construct", NULL, zval_index, getThis() );

    RETURN_ZVAL( row_object, 1, 0 );
}

/* \brief
 * creates and returns an col object
 *
 * \param index
 * the index of the column in this worksheet
 *
 * \returns
 * a col object
 */
static PHP_METHOD( worksheet, column )
{
    zval* zval_index;

    if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "z", &zval_index ) == FAILURE ) {
        WRONG_PARAM_COUNT;
    }

    zval* column_object;
    ALLOC_INIT_ZVAL( column_object );
    object_init_ex( column_object, wss_column_class );
    zend_call_method_with_2_params( &column_object, wss_column_class, NULL, "__construct", NULL, zval_index, getThis() );

    RETURN_ZVAL( column_object, 1, 0 );
}

/* \brief
 * returns or sets the name of the worksheet object
 *
 * \param name
 * optional parameter, when given the method sets the name of the worksheet to "name"
 *
 * \returns
 * name of the worksheet object if "name" parameter was omitted
 */
static PHP_METHOD( worksheet, name )
{
    zval* zval_uuid         = NULL;
    char* worksheet_name    = NULL;
    long worksheet_name_len = 0;

    if ( ZEND_NUM_ARGS() > 0 ) {
        if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "s", &worksheet_name, &worksheet_name_len ) == FAILURE ) {
            WRONG_PARAM_COUNT;
        }
    }

    zval_uuid = zend_read_property( wss_worksheet_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_uuid" ), 1 TSRMLS_CC );
    GET_SHARED_OBJ( worksheet, zval_uuid );

    if ( NULL == worksheet_name ) {
        RETURN_STRING( const_cast< char* >( shared_obj->name().c_str() ), 1 );
    } else {
        shared_obj->name( worksheet_name );
    }
}

/* \brief
 * returns the uuid of the worksheet object
 *
 * \returns
 * unique identifier of the worksheet object
 */
static PHP_METHOD( worksheet, uuid )
{
    PHP_FUNC_CHECK_FOR_READONLY_PROPERTY;

    zval* zval_uuid = zend_read_property( wss_worksheet_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_uuid" ), 1 TSRMLS_CC );
    RETURN_ZVAL( zval_uuid, 1, 0 )
}

/* \brief
 * creates and returns the elements asociated to this worksheet
 *
 * \returns
 * a worksheet_elements object
 */
static PHP_METHOD( worksheet, elements )
{
    PHP_FUNC_CHECK_FOR_READONLY_PROPERTY;

    zval* zval_elements = NULL;

    ALLOC_INIT_ZVAL( zval_elements );
    object_init_ex( zval_elements, wss_elements_class );
    zend_call_method_with_1_params( &zval_elements, wss_elements_class, NULL, "__construct", NULL, getThis()  );

    RETURN_ZVAL( zval_elements, 1, 0 );
}

/* \brief
 * list of all methods of the worksheet object and their access modifiers
 *
 * \see
 * register_worksheet_object
 */
static zend_function_entry wss_worksheet_functions[] = {
    PHP_ME( worksheet, __construct, wss_one_arg, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR )
    PHP_ME( worksheet, __set, wss_two_args, ZEND_ACC_PUBLIC )
    PHP_ME( worksheet, __get, wss_one_arg, ZEND_ACC_PUBLIC )
    PHP_ME( worksheet, parent, wss_no_args, ZEND_ACC_PUBLIC )
    PHP_ME( worksheet, name, NULL, ZEND_ACC_PUBLIC )
    PHP_ME( worksheet, uuid, wss_no_args, ZEND_ACC_PUBLIC )
    PHP_ME( worksheet, range, wss_one_arg, ZEND_ACC_PUBLIC )
    PHP_ME( worksheet, usedrange, wss_one_arg, ZEND_ACC_PUBLIC )
    PHP_ME( worksheet, elements, wss_no_args, ZEND_ACC_PUBLIC )
    PHP_ME( worksheet, row, wss_one_arg, ZEND_ACC_PUBLIC )
    PHP_ME( worksheet, column, wss_one_arg, ZEND_ACC_PUBLIC ) {
        NULL, NULL, NULL
    }
};

void register_worksheet_object( TSRMLS_D )
{
    // register internal wss<=>php wrapper objects
    zend_class_entry ce;

    INIT_CLASS_ENTRY( ce, "worksheet", wss_worksheet_functions );
    wss_worksheet_class = zend_register_internal_class( &ce TSRMLS_CC );
    zend_declare_property_null( wss_worksheet_class, WSS_PHP_STRING_NO_NULL( "m_uuid" ), ZEND_ACC_PRIVATE TSRMLS_CC );
}
