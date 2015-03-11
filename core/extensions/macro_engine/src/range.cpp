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
#include "array_return_converter.hpp"
#include "array_input_converter.hpp"
#include "value_converter.hpp"

zend_class_entry* wss_range_class;

extern zend_class_entry* wss_application_class;
extern zend_class_entry* wss_worksheet_class;
extern zend_class_entry* wss_worksheets_class;
extern zend_class_entry* wss_workbook_class;
extern zend_class_entry* wss_attribute_class;
extern zend_class_entry* wss_wss_exception_class;

ZEND_EXTERN_MODULE_GLOBALS( wssme );

/*!
 * \brief
 * constructs a new PHP range wrapper object
 *
 * \param parent_object
 * object of worksheet class type
 *
 * \param range_a1_notation
 * string defining an range in a1 notation f.ex "a1:b7"
 *
 * \remarks
 * - any "$" characters in the a1 notation are ignored.
 * - only ranges relative to the current worksheet are allowed.
 *   "Sheet2!A1:A2" would be illigal except when Sheet2 would be the
 *   currently active sheet.
 */
static PHP_METHOD( range, __construct )
{
    zval*   zval_ws         = NULL;
    zval*   zval_ws_uuid    = NULL;
    char*   range_a1        = NULL;
    long    range_a1_len    = 0;

    if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "s|z", &range_a1, &range_a1_len, &zval_ws ) == FAILURE ) {
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
        zend_update_property_string( wss_range_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_ws_uuid" ), const_cast<char*>( uuid.c_str() ) TSRMLS_CC );
    } else {
        zval_ws_uuid = zend_read_property( wss_worksheet_class, zval_ws, WSS_PHP_STRING_NO_NULL( "m_uuid" ), 1 TSRMLS_CC );
        zend_update_property_string( wss_range_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_ws_uuid" ), Z_STRVAL_P( zval_ws_uuid ) TSRMLS_CC );
    }

    zend_update_property_string( wss_range_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_range_a1" ), range_a1 TSRMLS_CC );
}

PHP_PROPERTY_SETTER( range );
PHP_PROPERTY_GETTER( range );

/* \brief
 * wrapper object string representation
 */
static PHP_METHOD( range, __toString )
{
    zval* zval_range_a1 = zend_read_property( wss_range_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_range_a1" ), 0 TSRMLS_CC );
    RETURN_ZVAL( zval_range_a1, 1, 0 );
}


/*!
 * brief
 * returns a reference to the Worksheet object
 *
 * \returns
 * reference to the Worksheet object
 */
static PHP_METHOD( range, parent )
{
    PHP_FUNC_CHECK_FOR_READONLY_PROPERTY;

    zval* zval_ws           = NULL;
    zval* zval_ws_uuid      = zend_read_property( wss_range_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_ws_uuid" ), 1 TSRMLS_CC );
    ALLOC_INIT_ZVAL( zval_ws );
    object_init_ex( zval_ws, wss_worksheet_class );
    zend_call_method_with_1_params( &zval_ws, wss_worksheet_class, NULL, "__construct", NULL, zval_ws_uuid );
    RETURN_ZVAL( zval_ws, 1, 0 );
}

/*!
 * brief
 * returns or sets the range of values on the associated worksheet
 *
 * \param value
 * value to be set on the area defined by the a1 range notation string
 *
 * \returns
 * NULL if setting values otherwise
 * - a single value if the area spanned by range only consists of one cell
 * - a array of values if the are spans more than one cell divided by row and columns
 *   f.ex.
 *   for an range A1:C2 Range("A1:C2")->value() would return:
 *     array("0" =>                    // the first row
 *               array(A1, B1, C1),   // - the columns
 *            "1" =>                    // the second row
 *               array(A2, B2, C2)    // - the columns
 *         );
 *
 * \remarks
 * like in VBA, when given multiple ranges "value" would _set_ a value for all cells spanned by the range
 * but only return the values of the fist cell or range.
 */
static PHP_METHOD( range, value )
{
    zval* zval_value    = NULL;
    zval* zval_ws_uuid  = zend_read_property( wss_range_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_ws_uuid" ), 0 TSRMLS_CC );
    zval* zval_range_a1 = zend_read_property( wss_range_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_range_a1" ), 0 TSRMLS_CC );

    if ( ZEND_NUM_ARGS() > 0 ) {
        if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "|z", &zval_value ) == FAILURE ) {
            WRONG_PARAM_COUNT;
        }
    }

    GET_SHARED_OBJ( worksheet, zval_ws_uuid );

    a1conversion::multi_rect_vector_type    ranges = a1conversion::from_a1::ranges( Z_STRVAL_P( zval_range_a1 ) );

    if ( ranges.empty() ) {
        RETURN_NULL()
    }

    const sheet_range& source_range = ranges[0];

    if ( NULL == zval_value ) {
        calculation_context cc( *( WSS_PHP_G( session_context ) ), WSS_PHP_G( session_context )->selected().application()->calculation_settings() );
        cc.interpreter_context( WSS_PHP_G( interpreter_context ) );
        variant wss_range_result = shared_obj->range( source_range ).value( cc );

        /* convert props format to excel format, and then to zval form */
        array_return_converter()( wss_range_result, source_range );
        value_converter()( WSS_PHP_G( session_context )->locale(), return_value, wss_range_result );
    } else {
        /* iterate over all BoundedRects and set to the specified value */
        variant tmp = value_converter()( zval_value TSRMLS_CC );

        //convert from excel format
        array_input_converter()( tmp );

        a1conversion::multi_rect_vector_type::const_iterator it( ranges.begin() );
        a1conversion::multi_rect_vector_type::const_iterator end( ranges.end() );

        for ( ; it != end; ++it ) {
            shared_obj->range( *it ).value( *( WSS_PHP_G( session_context ) ), tmp );
        }
    }
}

/*!
 * brief
 * returns or sets the range of formulas on the associated worksheet
 *
 * \param value
 * formula to be set on the area defined by the a1 range notation string
 *
 * \returns
 * NULL if setting formulas otherwise
 * - a single formula if the area spanned by range only consists of one cell
 * - a array of formulas if the are spans more than one cell divided by row and columns
 *   f.ex.
 *   for an range A1:C2 Range("A1:C2")->value() would return:
 *     array("0" =>                    // the first row
 *               array(A1, B1, C1),   // - the columns
 *            "1" =>                    // the second row
 *               array(A2, B2, C2)    // - the columns
 *         );
 *
 * \remarks
 * like in VBA, when given multiple ranges "formula" would _set_ a formula for all cells spanned by the range
 * but only return the formulas of the fist cell or range.
 */
static PHP_METHOD( range, formula )
{
    zval* zval_value        = NULL;
    zval* zval_ws_uuid      = zend_read_property( wss_range_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_ws_uuid" ), 0 TSRMLS_CC );
    zval* zval_range_a1     = zend_read_property( wss_range_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_range_a1" ), 0 TSRMLS_CC );

    if ( ZEND_NUM_ARGS() > 0 ) {
        if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "|z", &zval_value ) == FAILURE ) {
            WRONG_PARAM_COUNT;
        }
    }

    GET_SHARED_OBJ( worksheet, zval_ws_uuid );

    a1conversion::multi_rect_vector_type    ranges = a1conversion::from_a1::ranges( Z_STRVAL_P( zval_range_a1 ) );

    if ( ranges.empty() ) {
        RETURN_NULL()
    }

    const sheet_range& source_range = ranges[0];

    if ( NULL == zval_value ) {
        calculation_context cc( *( WSS_PHP_G( session_context ) ), WSS_PHP_G( session_context )->selected().application()->calculation_settings() );
        cc.interpreter_context( WSS_PHP_G( interpreter_context ) );
        variant wss_range_result = shared_obj->range( source_range ).formula( cc );

        /* convert props format to excel format, and then to zval form */
        array_return_converter()( wss_range_result, source_range );
        value_converter()( WSS_PHP_G( session_context )->locale(), return_value, wss_range_result );
    } else {
        /* iterate over all BoundedRects and set to the specified value */
        variant tmp = value_converter()( zval_value TSRMLS_CC );
        //convert from excel format
        array_input_converter()( tmp );

        a1conversion::multi_rect_vector_type::const_iterator it( ranges.begin() );
        a1conversion::multi_rect_vector_type::const_iterator end( ranges.end() );

        for ( ; it != end; ++it ) {
            shared_obj->range( *it ).value( *( WSS_PHP_G( session_context ) ), tmp );
        }
    }
}

/*!
 * brief
 * returns or sets the range of styles on the associated worksheet
 *
 * \param value
 * style to be set on the area defined by the a1 range notation string
 *
 * \returns
 * NULL if setting styles otherwise
 * - a single style if the area spanned by range only consists of one cell
 * - a array of styles if the are spans more than one cell divided by row and columns
 *   f.ex.
 *   for an range A1:C2 Range("A1:C2")->style() would return:
 *     array("0" =>                                  // the first row
 *               array(style11, style12, style13),   // - the columns
 *            "1" =>                                 // the second row
 *               array(style21, style22, style23)    // - the columns
 *         );
 *
 * \remarks
 * like in VBA, when given multiple ranges "style" would _set_ a formula for all cells spanned by the range
 * but only return the styles of the fist cell or range;
 */
static PHP_METHOD( range, style )
{
    zval* zval_value    = NULL;
    zval* zval_ws_uuid  = zend_read_property( wss_range_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_ws_uuid" ), 0 TSRMLS_CC );
    zval* zval_range_a1 = zend_read_property( wss_range_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_range_a1" ), 0 TSRMLS_CC );

    if ( ZEND_NUM_ARGS() > 0 ) {
        if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "|z", &zval_value ) == FAILURE ) {
            WRONG_PARAM_COUNT;
        }
    }

    GET_SHARED_OBJ( worksheet, zval_ws_uuid );

    a1conversion::multi_rect_vector_type    ranges = a1conversion::from_a1::ranges( Z_STRVAL_P( zval_range_a1 ) );

    if ( ranges.empty() ) {
        RETURN_NULL()
    }

    const sheet_range& source_range = ranges[0];

    if ( NULL == zval_value ) {

        css_style_vec_type vec = shared_obj->range( source_range ).style();
        variant wss_range_result( vec );

        /* convert props format to excel format, and then to zval form */
        array_return_converter()( wss_range_result, source_range );
        value_converter()( WSS_PHP_G( session_context )->locale(), return_value, wss_range_result );
    } else {
        /* iterate over all BoundedRects and set to the specified value */
        variant tmp = value_converter()( zval_value TSRMLS_CC );

        for ( int row = source_range.upper_left().row(); row <= source_range.lower_right().row(); row++ ) {
            const variant& row_styles = tmp.is_array() ? tmp.array()[ row - source_range.upper_left().row() ] : tmp;
            for ( int col = source_range.upper_left().column(); col <= source_range.lower_right().column(); col++ ) {
                const variant& crt_style = row_styles.is_array() ? row_styles.array()[ col - source_range.upper_left().column() ] : row_styles;
                shared_obj->range( sheet_range( sheet_point( row, col ) ) ).style( *( WSS_PHP_G( session_context ) ), style_set_type::unserialize( crt_style.string() ) );
            }
        }
    }
}

/*!
 * brief
 * returns or sets the range of un_locked status on the associated worksheet
 *
 * \param value
 * un_locked status to be set on the area defined by the a1 range notation string
 *
 * \returns
 * NULL if setting locked status otherwise
 * - a single locked status if the area spanned by range only consists of one cell
 * - a array of locked statuses if the are spans more than one cell divided by row and columns
 *   f.ex.
 *   for an range A1:C2 Range("A1:C2")->locked() would return:
 *     array("0" =>                                  // the first row
 *               array(locked11, locked12, locked13),   // - the columns
 *            "1" =>                                 // the second row
 *               array(locked21, locked22, locked23)    // - the columns
 *         );
 *
 * \remarks
 * like in VBA, when given multiple ranges "locked" would _set_ a formula for all cells spanned by the range
 * but only return the locked status of the fist cell or range;
 */
static PHP_METHOD( range, un_locked )
{
    zval* zval_value    = NULL;
    zval* zval_ws_uuid  = zend_read_property( wss_range_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_ws_uuid" ), 0 TSRMLS_CC );
    zval* zval_range_a1 = zend_read_property( wss_range_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_range_a1" ), 0 TSRMLS_CC );

    if ( ZEND_NUM_ARGS() > 0 ) {
        if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "|z", &zval_value ) == FAILURE ) {
            WRONG_PARAM_COUNT;
        }
    }

    GET_SHARED_OBJ( worksheet, zval_ws_uuid );

    a1conversion::multi_rect_vector_type    ranges = a1conversion::from_a1::ranges( Z_STRVAL_P( zval_range_a1 ) );

    if ( ranges.empty() ) {
        RETURN_NULL()
    }

    const sheet_range& source_range = ranges[0];

    if ( NULL == zval_value ) {

        sparse_vector<variant> vec;
        {
            const unlocked_cells_vec_type& tmp_vec = shared_obj->range( source_range ).un_locked( *( WSS_PHP_G( session_context ) ), cf::cf_vec_type(), false );
            for ( unlocked_cells_vec_type::const_iterator it = tmp_vec.begin(); it != tmp_vec.end(); ++it ) {
                vec.push_back( variant( *it ) ) ;
            }
        }
        variant wss_range_result( vec );

        /* convert props format to excel format, and then to zval form */
        array_return_converter()( wss_range_result, source_range );
        value_converter()( WSS_PHP_G( session_context )->locale(), return_value, wss_range_result );
    } else if ( IS_BOOL == Z_TYPE_P( zval_value ) ) {

        for ( int row = source_range.upper_left().row(); row <= source_range.lower_right().row(); row++ ) {
            for ( int col = source_range.upper_left().column(); col <= source_range.lower_right().column(); col++ ) {
                shared_obj->range( sheet_range( sheet_point( row, col ) ) ).un_locked( *( WSS_PHP_G( session_context ) ), Z_BVAL_P( zval_value ) );
            }
        }
    } else {
        /* iterate over all BoundedRects and set to the specified value */
        variant tmp = value_converter()( zval_value TSRMLS_CC );

        for ( int row = source_range.upper_left().row(); row <= source_range.lower_right().row(); row++ ) {
            const variant& row_locks = tmp.is_array() ? tmp.array()[ row - source_range.upper_left().row() ] : tmp;
            for ( int col = source_range.upper_left().column(); col <= source_range.lower_right().column(); col++ ) {
                const variant& crt_lock = row_locks.is_array() ? row_locks.array()[ col - source_range.upper_left().column() ] : row_locks;
                shared_obj->range( sheet_range( sheet_point( row, col ) ) ).un_locked( *( WSS_PHP_G( session_context ) ), crt_lock.boolean() );
            }
        }
    }
}

/*!
 * brief
 * sets a single cell attribute on the associated worksheet
 *
 */
static PHP_METHOD( range, attribute )
{
    zval* zval_attribute  = NULL;
    zval* zval_ws_uuid    = zend_read_property( wss_range_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_ws_uuid" ), 0 TSRMLS_CC );
    zval* zval_range_a1   = zend_read_property( wss_range_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_range_a1" ), 0 TSRMLS_CC );

    if ( FAILURE == zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "|z", &zval_attribute ) ) {
        WRONG_PARAM_COUNT;
    }

    if ( NULL == zval_attribute ) {
        WRONG_PARAM_COUNT;
    }

    GET_SHARED_OBJ( worksheet, zval_ws_uuid );

    a1conversion::multi_rect_vector_type    ranges = a1conversion::from_a1::ranges( Z_STRVAL_P( zval_range_a1 ) );

    const sheet_range& source_range = ranges[0];


    switch ( Z_TYPE_P( zval_attribute ) ) {
        case IS_OBJECT: {

            zval* z_key = NULL;
            zval* z_value = NULL;

            zend_call_method_with_0_params( &zval_attribute, wss_attribute_class, NULL, "key", &z_key );
            zend_call_method_with_0_params( &zval_attribute, wss_attribute_class, NULL, "value", &z_value );

            variant key = value_converter()( z_key TSRMLS_CC );
            variant value = value_converter()( z_value TSRMLS_CC );

            a1conversion::multi_rect_vector_type::const_iterator it( ranges.begin() );
            a1conversion::multi_rect_vector_type::const_iterator end( ranges.end() );

            attribute_set_type  attributes;
            attributes.add( key.string(), value.string() );

            for ( ; it != end; ++it ) {
                shared_obj->range( *it ).attribute( *( WSS_PHP_G( session_context ) ), attributes );
            }

        }
        break;

        case IS_STRING: {
            utf8_ci_string key = Z_STRVAL_P( zval_attribute );
            variant wss_range_result = shared_obj->range( source_range ).attribute( key );

            /* convert props format to excel format, and then to zval form */
            array_return_converter()( wss_range_result, source_range );
            value_converter()( WSS_PHP_G( session_context )->locale(), return_value, wss_range_result );
        }
        break;

        default:
            WRONG_PARAM_COUNT;
    }
}

static PHP_METHOD( range, attributes )
{
    PHP_FUNC_CHECK_FOR_READONLY_PROPERTY;

    zval* zval_ws_uuid    = zend_read_property( wss_range_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_ws_uuid" ), 0 TSRMLS_CC );
    zval* zval_range_a1   = zend_read_property( wss_range_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_range_a1" ), 0 TSRMLS_CC );

    GET_SHARED_OBJ( worksheet, zval_ws_uuid );

    a1conversion::multi_rect_vector_type    ranges = a1conversion::from_a1::ranges( Z_STRVAL_P( zval_range_a1 ) );

    variant wss_range_result = shared_obj->range( ranges[0] ).attribute( );

    /* convert props format to excel format, and then to zval form */
    array_return_converter()( wss_range_result, ranges[0] );
    value_converter()( WSS_PHP_G( session_context )->locale(), return_value, wss_range_result );
}

/*!
 * \brief
 * returns the range address in A1 notation
 */
static PHP_METHOD( range, address )
{
    PHP_FUNC_CHECK_FOR_READONLY_PROPERTY;

    zval* zval_range_a1 = zend_read_property( wss_range_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_range_a1" ), 0 TSRMLS_CC );
    RETURN_ZVAL( zval_range_a1, 1, 0 );
}

/*!
 * \brief
 * returns the range width
 */
static PHP_METHOD( range, width )
{
    PHP_FUNC_CHECK_FOR_READONLY_PROPERTY;

    zval* zval_ws_uuid    = zend_read_property( wss_range_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_ws_uuid" ), 0 TSRMLS_CC );
    zval* zval_range_a1   = zend_read_property( wss_range_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_range_a1" ), 0 TSRMLS_CC );

    GET_SHARED_OBJ( worksheet, zval_ws_uuid );

    a1conversion::multi_rect_vector_type    ranges = a1conversion::from_a1::ranges( Z_STRVAL_P( zval_range_a1 ) );

    RETURN_LONG( shared_obj->range( ranges[0] ).width( *WSS_PHP_G( session_context ) ) );

}

/*!
 * \brief
 * returns the range width
 */
static PHP_METHOD( range, height )
{
    PHP_FUNC_CHECK_FOR_READONLY_PROPERTY;

    zval* zval_ws_uuid    = zend_read_property( wss_range_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_ws_uuid" ), 0 TSRMLS_CC );
    zval* zval_range_a1   = zend_read_property( wss_range_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_range_a1" ), 0 TSRMLS_CC );

    GET_SHARED_OBJ( worksheet, zval_ws_uuid );

    a1conversion::multi_rect_vector_type    ranges = a1conversion::from_a1::ranges( Z_STRVAL_P( zval_range_a1 ) );

    RETURN_LONG( shared_obj->range( ranges[0] ).height( *WSS_PHP_G( session_context ) ) );
}

/*!
 * \brief
 * merges the range
 */
static PHP_METHOD( range, merge )
{
    PHP_FUNC_CHECK_FOR_READONLY_PROPERTY;

    zval* zval_ws_uuid    = zend_read_property( wss_range_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_ws_uuid" ), 0 TSRMLS_CC );
    zval* zval_range_a1   = zend_read_property( wss_range_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_range_a1" ), 0 TSRMLS_CC );

    GET_SHARED_OBJ( worksheet, zval_ws_uuid );

    a1conversion::multi_rect_vector_type    ranges = a1conversion::from_a1::ranges( Z_STRVAL_P( zval_range_a1 ) );

    shared_obj->range( ranges[0] ).merge( *WSS_PHP_G( session_context ) );
}

/*!
 * \brief
 * un_merges the range
 */
static PHP_METHOD( range, un_merge )
{
    PHP_FUNC_CHECK_FOR_READONLY_PROPERTY;

    zval* zval_ws_uuid    = zend_read_property( wss_range_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_ws_uuid" ), 0 TSRMLS_CC );
    zval* zval_range_a1   = zend_read_property( wss_range_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_range_a1" ), 0 TSRMLS_CC );

    GET_SHARED_OBJ( worksheet, zval_ws_uuid );

    a1conversion::multi_rect_vector_type    ranges = a1conversion::from_a1::ranges( Z_STRVAL_P( zval_range_a1 ) );

    shared_obj->range( ranges[0] ).un_merge( *WSS_PHP_G( session_context ) );
}

/*!
 * \brief
 * list of all methods of the range object and their access modifiers
 *
 * \see
 * register_range_object
 */
static zend_function_entry wss_range_functions[] = {
    PHP_ME( range, __construct, wss_two_args, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR )
    PHP_ME( range, __set, wss_two_args, ZEND_ACC_PUBLIC )
    PHP_ME( range, __get, wss_one_arg, ZEND_ACC_PUBLIC )
    PHP_ME( range, __toString, wss_no_args, ZEND_ACC_PUBLIC )
    PHP_ME( range, parent, wss_no_args, ZEND_ACC_PUBLIC )
    PHP_ME( range, value, wss_no_args, ZEND_ACC_PUBLIC )
    PHP_ME( range, formula, wss_no_args, ZEND_ACC_PUBLIC )
    PHP_ME( range, style, wss_no_args, ZEND_ACC_PUBLIC )
    PHP_ME( range, address, wss_no_args, ZEND_ACC_PUBLIC )
    PHP_ME( range, attribute, wss_one_arg, ZEND_ACC_PUBLIC )
    PHP_ME( range, un_locked, wss_one_arg, ZEND_ACC_PUBLIC )
    PHP_ME( range, attributes, wss_no_args, ZEND_ACC_PUBLIC )
    PHP_ME( range, width, wss_no_args, ZEND_ACC_PUBLIC )
    PHP_ME( range, height, wss_no_args, ZEND_ACC_PUBLIC )
    PHP_ME( range, merge, wss_no_args, ZEND_ACC_PUBLIC )
    PHP_ME( range, un_merge, wss_no_args, ZEND_ACC_PUBLIC ) {
        NULL, NULL, NULL
    }
};

void register_range_object( TSRMLS_D )
{
    // register internal wss<=>php wrapper objects
    zend_class_entry ce;

    INIT_CLASS_ENTRY( ce, "range", wss_range_functions );
    wss_range_class = zend_register_internal_class( &ce TSRMLS_CC );
    zend_declare_property_null( wss_range_class, WSS_PHP_STRING_NO_NULL( "m_ws_uuid" ), ZEND_ACC_PRIVATE TSRMLS_CC );
    zend_declare_property_null( wss_range_class, WSS_PHP_STRING_NO_NULL( "m_range_a1" ), ZEND_ACC_PRIVATE TSRMLS_CC );
}
