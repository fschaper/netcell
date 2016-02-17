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
#define NEEDS_SOCKLEN_T
#include "php_includes.hpp"
#include "value_converter.hpp"

extern zend_class_entry* wss_variant_error_class;

void value_converter::operator()( const ::locale& l, zval* zend_value, const variant& value ) const
{
    switch ( value.type() ) {
        case variant::type_empty:
            ZVAL_NULL( zend_value );
            break;

        case variant::type_double:
            ZVAL_DOUBLE( zend_value, value.numeric() );
            break;

        case variant::type_bool:
            ZVAL_BOOL( zend_value, value.numeric() );
            break;

        case variant::type_error: {
            TSRMLS_FETCH();
            object_init_ex( zend_value, wss_variant_error_class );
            zval* err_code = NULL;
            ALLOC_INIT_ZVAL( err_code );
            ZVAL_LONG( err_code, value.error_code() );
            zend_call_method_with_1_params( &zend_value, wss_variant_error_class, NULL, "__construct", NULL, err_code );
            zval_dtor( err_code );
        }
        break;

        case variant::type_string:
            ZVAL_STRING( zend_value, const_cast<char*>( value.string().c_str() ), 1 );
            break;

        case variant::type_array:
            // convert to zval array
            if ( 1 == value.column_width() ) {
                ( *this )( zend_value, value );
            } else {
                ( *this )( zend_value, value, value.column_width() );
            }
            break;
    };
}

variant value_converter::operator()( zval* zend_value TSRMLS_DC, const variant& val )
{
    switch ( Z_TYPE_P( zend_value ) ) {
        case IS_NULL:
            return variant();

        case IS_BOOL:
#ifdef WIN32
# pragma warning ( disable: 4800 )
#endif
            return variant( static_cast< bool >( Z_BVAL_P( zend_value ) ) );
#ifdef WIN32
# pragma warning ( default: 4800 )
#endif
        case IS_STRING:
            return variant( std::string( Z_STRVAL_P( zend_value ), Z_STRLEN_P( zend_value ) ) );

        case IS_DOUBLE:
            return variant( Z_DVAL_P( zend_value ) );

        case IS_LONG:
            return variant( static_cast<double>( Z_LVAL_P( zend_value ) ) );

        case IS_ARRAY: {
            if ( val.is_empty() ) {
                const_cast<variant&>( val ) = variant( variant::type_array );
            }
            zend_hash_apply_with_argument( Z_ARRVAL_P( zend_value ), &hashtable_callback, static_cast<void*>( &const_cast<variant&>( val ) ) TSRMLS_CC );
            return val;
        }

        case IS_OBJECT: {
            if ( strcmp( Z_OBJCE_P( zend_value )->name, wss_variant_error_class->name ) == 0 ) {
                zval* err_code = NULL;
                ALLOC_INIT_ZVAL( err_code );
                ZVAL_LONG( err_code, -1 );
                zend_call_method_with_1_params( &zend_value, wss_variant_error_class, NULL, "error_code", &err_code, err_code );
                variant v ( static_cast<variant::error_type>( Z_LVAL_P( err_code ) ) );
                zval_dtor( err_code );
                return v;
            }
        }
        default:
            return variant();
    }
}

void value_converter::operator()( zval* zend_value, const variant& value ) const
{
    array_init( zend_value );

    foreach( const variant & array_element, value.array() ) {
        switch ( array_element.type() ) {
            case variant::type_empty:
                add_next_index_null( zend_value );
                break;

            case variant::type_double:
                add_next_index_double( zend_value, array_element.numeric() );
                break;

            case variant::type_bool:
                add_next_index_bool( zend_value, static_cast<int>( array_element.numeric() ) );
                break;

            case variant::type_string:
                add_next_index_string( zend_value, const_cast<char*>( array_element.string().c_str() ), 1 );
                break;

            case variant::type_error: {
                TSRMLS_FETCH();
                zval* variant_error = NULL;
                ALLOC_INIT_ZVAL( variant_error );
                object_init_ex( variant_error, wss_variant_error_class );
                zval* err_code = NULL;
                ALLOC_INIT_ZVAL( err_code );
                ZVAL_LONG( err_code, array_element.error_code() );
                zend_call_method_with_1_params( &variant_error, wss_variant_error_class, NULL, "__construct", NULL, err_code );
                zval_dtor( err_code );
                add_next_index_zval( zend_value, variant_error );

            }
            break;

            case variant::type_array: {
                zval* sub_array = NULL;
                MAKE_STD_ZVAL( sub_array );
                if ( 1 == array_element.column_width() ) {
                    ( *this )( sub_array, array_element );
                } else {
                    ( *this )( sub_array, array_element, array_element.column_width() );
                }
                add_next_index_zval( zend_value, sub_array );
            }
            break;

            default:
                add_next_index_null( zend_value );
                break;
        }
    }
}

void value_converter::operator ()( zval* zend_value, const variant& value, size_t col_size ) const
{
    array_init( zend_value );

    zval* crt_column = NULL;
    MAKE_STD_ZVAL( crt_column );
    array_init( crt_column );
    size_t  col_pos = 0;


    foreach( const variant & array_element, value.array() ) {
        switch ( array_element.type() ) {
            case variant::type_empty:
                add_next_index_null( crt_column );
                break;

            case variant::type_double:
                add_next_index_double( crt_column, array_element.numeric() );
                break;

            case variant::type_bool:
                add_next_index_bool( crt_column, static_cast<int>( array_element.numeric() ) );
                break;

            case variant::type_string:
                add_next_index_string( crt_column, const_cast<char*>( array_element.string().c_str() ), 1 );
                break;
            case variant::type_error: {
                TSRMLS_FETCH();
                zval* variant_error = NULL;
                ALLOC_INIT_ZVAL( variant_error );
                object_init_ex( variant_error, wss_variant_error_class );
                zval* err_code = NULL;
                ALLOC_INIT_ZVAL( err_code );
                ZVAL_LONG( err_code, array_element.error_code() );
                zend_call_method_with_1_params( &variant_error, wss_variant_error_class, NULL, "__construct", NULL, err_code );
                zval_dtor( err_code );
                add_next_index_zval( crt_column, variant_error );

            }
            break;
            case variant::type_array: {
                zval* sub_array = NULL;
                MAKE_STD_ZVAL( sub_array );
                ( *this )( sub_array, array_element );
                add_next_index_zval( crt_column, sub_array );
            }
            break;

            default:
                add_next_index_null( crt_column );
                break;
        }
        if ( col_size == ++col_pos ) {
            add_next_index_zval( zend_value, crt_column );

            MAKE_STD_ZVAL( crt_column );
            array_init( crt_column );
            col_pos = 0;
        }
    }
}

int value_converter::hashtable_callback( void* zend_value, void* wss_value TSRMLS_DC )
{
    variant* array_variant = static_cast<variant*>( wss_value );
    zval* z_val = *reinterpret_cast<zval**>( zend_value );
    if ( Z_TYPE_P( z_val ) == IS_ARRAY ) {
        //        array_variant->column_width( zend_hash_num_elements( Z_ARRVAL_P( z_val ) )  );
        //        value_converter()( z_val TSRMLS_CC, *array_variant );
        variant inner_array( variant::type_array );
        value_converter()( z_val TSRMLS_CC, inner_array );
        array_variant->array().push_back( inner_array );
    } else {
        array_variant->array().push_back( value_converter()( z_val TSRMLS_CC, *array_variant ) );
    }
    return ZEND_HASH_APPLY_KEEP;
}

