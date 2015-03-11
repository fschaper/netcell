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

zend_class_entry* wss_elements_class;

extern zend_class_entry* wss_worksheet_class;
extern zend_class_entry* wss_element_class;
extern zend_class_entry* wss_wss_exception_class;

ZEND_EXTERN_MODULE_GLOBALS( wssme );

/* \brief
 * constructs a new PHP worksheet element wrapper object
 *
 * \param parent_object
 * object of  class type
 */
static PHP_METHOD( elements, __construct )
{
    zval* zval_ws              = NULL;
    zval* zval_ws_uuid          = NULL;

    if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "|z", &zval_ws ) == FAILURE ) {
        BEGIN_CORE_CATCH_BLOCK()
        throw fatal_exception( "WRONG_PARAM_COUNT" );
        END_CORE_CATCH_BLOCK()
        WRONG_PARAM_COUNT;
    }

    if ( NULL == zval_ws ) {
        const shared_worksheet_type worksheet = WSS_PHP_G( session_context )->selected().worksheet().lock();
        TEST_SHARED_OBJ( worksheet );
        const std::string uuid( boost::lexical_cast<std::string>( worksheet->uuid() ) );
        zend_update_property_string( wss_elements_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_ws_uuid" ), const_cast<char*>( uuid.c_str() ) TSRMLS_CC );
    } else {
        zend_call_method_with_0_params( &zval_ws, wss_worksheet_class, NULL, "uuid", &zval_ws_uuid );
        zend_update_property_string( wss_elements_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_ws_uuid" ), Z_STRVAL_P( zval_ws_uuid ) TSRMLS_CC );
    }
}

PHP_PROPERTY_SETTER( elements );
PHP_PROPERTY_GETTER( elements );

/* \brief
 * returns a reference to the Application object
 *
 * \returns
 * reference to the Application object
 */
static PHP_METHOD( elements, parent )
{
    PHP_FUNC_CHECK_FOR_READONLY_PROPERTY;

    zval* zval_ws       = NULL;
    zval* zval_ws_uuid  = zend_read_property( wss_elements_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_ws_uuid" ), 1 TSRMLS_CC );
    ALLOC_INIT_ZVAL( zval_ws );
    object_init_ex( zval_ws, wss_worksheet_class );
    zend_call_method_with_1_params( &zval_ws, wss_worksheet_class, NULL, "__construct", NULL, zval_ws_uuid );
    RETURN_ZVAL( zval_ws, 1, 0 );
}

/* \brief
 * adds a new, empty worksheetelement to the collection
 *
 * \returns
 * the created worksheet element
 */
static PHP_METHOD( elements, add )
{
    PHP_FUNC_CHECK_FOR_READONLY_PROPERTY;

    zval* zval_ws_elt           = NULL;
    zval* zval_ws_elt_uuid      = NULL;
    zval* zval_ws               = NULL;
    zval* zval_ws_uuid          = zend_read_property( wss_elements_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_ws_uuid" ), 1 TSRMLS_CC );
    GET_SHARED_OBJ( worksheet, zval_ws_uuid )

    shared_worksheet_element_type wselt = worksheet_element::create( shared_obj );
    const std::string uuid( boost::lexical_cast<std::string>( wselt->uuid() ) );

    ALLOC_INIT_ZVAL( zval_ws_elt_uuid );
    ZVAL_STRING( zval_ws_elt_uuid, const_cast<char*>( uuid.c_str() ), 1 );
    ALLOC_INIT_ZVAL( zval_ws_elt );
    object_init_ex( zval_ws_elt, wss_element_class );
    zend_call_method_with_0_params( &getThis(), wss_elements_class, NULL, "parent", &zval_ws );
    zend_call_method_with_2_params( &zval_ws_elt, wss_element_class, NULL, "__construct", NULL, zval_ws, zval_ws_elt_uuid );
    zval_dtor( zval_ws_elt_uuid );
    zval_dtor( zval_ws );

    RETURN_ZVAL( zval_ws_elt, 1, 0 );
}

/* \brief
 * returns the number of elements in the collection
 *
 * \returns
 * the number of elements
 */
static PHP_METHOD( elements, count )
{
    PHP_FUNC_CHECK_FOR_READONLY_PROPERTY;

    zval* zval_ws_uuid            = zend_read_property( wss_elements_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_ws_uuid" ), 1 TSRMLS_CC );
    GET_SHARED_OBJ( worksheet, zval_ws_uuid );
    RETURN_LONG( ( long ) shared_obj->elements().list_all_elements().size() );
}

/* \brief
 * returns the worksheet element identified by id
 *
 * \param

 * \returns
 * the worksheet element identified by id
 */
static PHP_METHOD( elements, item )
{
    zval* zval_ws_elt       = NULL;
    zval* zval_ws_elt_uuid  = NULL;
    zval* zval_ws_uuid      = NULL;
    zval* zval_ws           = NULL;
    char* element_uuid;
    long element_uuid_length;

    if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "s", &element_uuid, &element_uuid_length ) == FAILURE ) {
        WRONG_PARAM_COUNT;
    }

    zval_ws = zend_read_property( wss_elements_class, getThis(), WSS_PHP_STRING_NO_NULL( "parent" ), 1 TSRMLS_CC );
    zval_ws_uuid = zend_read_property( wss_elements_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_ws_uuid" ), 1 TSRMLS_CC );

    GET_SHARED_OBJ( worksheet, zval_ws_uuid );

    BEGIN_CORE_CATCH_BLOCK();
    //uuid validation
    shared_obj->elements().get_worksheet_element( *WSS_PHP_G( session_context ), element_uuid );
    END_CORE_CATCH_BLOCK();

    ALLOC_INIT_ZVAL( zval_ws_elt_uuid );
    ZVAL_STRING( zval_ws_elt_uuid, element_uuid, 1 );
    ALLOC_INIT_ZVAL( zval_ws_elt );
    object_init_ex( zval_ws_elt, wss_element_class );
    zend_call_method_with_2_params( &zval_ws_elt, wss_element_class, NULL, "__construct", NULL, zval_ws, zval_ws_elt_uuid );

    RETURN_ZVAL( zval_ws_elt, 1, 0 );
}

static PHP_METHOD( elements, remove )
{
    zval* zval_ws_uuid      = NULL;
    zval* zval_ws_elt       = NULL;
    zval* zval_ws_elt_uuid  = NULL;


    if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "z", &zval_ws_elt ) == FAILURE ) {
        WRONG_PARAM_COUNT;
    }

    zval_ws_elt_uuid = zend_read_property( wss_element_class, zval_ws_elt, WSS_PHP_STRING_NO_NULL( "m_uuid" ), 1 TSRMLS_CC );
    zval_ws_uuid     = zend_read_property( wss_elements_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_ws_uuid" ), 1 TSRMLS_CC );

    GET_SHARED_OBJ( worksheet, zval_ws_uuid );
    BEGIN_CORE_CATCH_BLOCK();
    shared_obj->elements().delete_worksheet_element( *WSS_PHP_G( session_context ), Z_STRVAL_P( zval_ws_elt_uuid ) );
    END_CORE_CATCH_BLOCK();
}

static PHP_METHOD( elements, list )
{
    PHP_FUNC_CHECK_FOR_READONLY_PROPERTY;

    zval* zval_ws = zend_read_property( wss_elements_class, getThis(), WSS_PHP_STRING_NO_NULL( "parent" ), 1 TSRMLS_CC );
    zval* zval_ws_uuid     = zend_read_property( wss_elements_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_ws_uuid" ), 1 TSRMLS_CC );
    zval* z_array_ret = NULL;
    MAKE_STD_ZVAL( z_array_ret );
    array_init( z_array_ret );
    GET_SHARED_OBJ( worksheet, zval_ws_uuid );

    BEGIN_CORE_CATCH_BLOCK();

    foreach( shared_worksheet_element_type se, shared_obj->elements().list_all_elements() ) {
        zval* zval_ws_elt       = NULL;
        zval* zval_ws_elt_uuid  = NULL;
        ALLOC_INIT_ZVAL( zval_ws_elt_uuid );
        const std::string& we_uuid =  boost::lexical_cast<std::string>( se->uuid() );
        ZVAL_STRING( zval_ws_elt_uuid, const_cast<char*>( we_uuid.c_str() ), 1 );
        ALLOC_INIT_ZVAL( zval_ws_elt );
        object_init_ex( zval_ws_elt, wss_element_class );
        zend_call_method_with_2_params( &zval_ws_elt, wss_element_class, NULL, "__construct", NULL, zval_ws, zval_ws_elt_uuid );
        add_next_index_zval( z_array_ret, zval_ws_elt );
        zval_ws = zend_read_property( wss_elements_class, getThis(), WSS_PHP_STRING_NO_NULL( "parent" ), 1 TSRMLS_CC );
    }

    END_CORE_CATCH_BLOCK();

    RETURN_ZVAL( z_array_ret, 1, 0 );
}

/* \brief
* returns an array of wse according to their search criteria
*
*/
static PHP_METHOD( elements, lookup )
{
    /*
        zval *ids               = NULL;
        zval *values            = NULL;

        if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z|z", &ids, &values) == FAILURE) {
            WRONG_PARAM_COUNT;
        }

        boost::shared_ptr<Application> application = WSS_PHP_G(cx)->get_active_application().lock();
        if ( !application) {
            RETURN_NULL();
        }

        zval *parent_object = zend_read_property(wss_elements_class, getThis(), WSS_PHP_STRING_NO_NULL("m_parent"), 1 TSRMLS_CC);
        zval *worksheet_uuid = zend_read_property(wss_worksheet_class, parent_object, WSS_PHP_STRING_NO_NULL("m_worksheet_uuid"), 0 TSRMLS_CC);
        zval *worksheets_object = zend_read_property(wss_worksheet_class, getThis(), WSS_PHP_STRING_NO_NULL("m_parent"), 0 TSRMLS_CC);
        zval *workbook_object = zend_read_property(wss_worksheets_class, worksheets_object, WSS_PHP_STRING_NO_NULL("m_parent"), 0 TSRMLS_CC);
        zval *workbook_uuid = zend_read_property(wss_workbook_class, workbook_object, WSS_PHP_STRING_NO_NULL("m_workbook_uuid"), 0 TSRMLS_CC);

        try {
            Application::value_type workbook = application->get_by_uuid(*WSS_PHP_G(cx), Z_STRVAL_P(workbook_uuid));
            Workbook::value_type worksheet = workbook->get_by_uuid(*WSS_PHP_G(cx), Z_STRVAL_P(worksheet_uuid));

            std::vector< std::string>               wss_ids;
            std::vector< std::string>               wss_keys;
            WorksheetElement::key_value_vector_type wss_values;

            if ( IS_ARRAY != Z_TYPE_P(ids) ){
                php_error_docref(NULL TSRMLS_CC, E_ERROR, "Invalid argument on pos 1. Expecting array.");
            }
            else{
                val_zval::fill_array_string( ids, wss_ids );
            }

            if ( NULL != values ){
                if ( IS_ARRAY != Z_TYPE_P(values) ){
                    php_error_docref(NULL TSRMLS_CC, E_ERROR, "Invalid argument on pos 3. Expecting array.");
                }
                else {
                    val_zval::fill_array_pair( values, wss_values );
                }
            }

            zval* zval_ret;
            ALLOC_INIT_ZVAL( zval_ret );
            array_init( zval_ret );

            const worksheet_element_vec_type& ws_elems = worksheet->get_worksheet_elements();
            worksheet_element_vec_type::const_iterator it(ws_elems.begin());
            worksheet_element_vec_type::const_iterator end_it(ws_elems.end());

            for ( ;it != end_it; it++ ){
                if ( !wss_ids.empty() ){
                    if ( wss_ids.end() == std::find( wss_ids.begin(), wss_ids.end(), it->first ) ){
                        continue;
                    }
                }
                //          if ( !it->second->match_vals( *WSS_PHP_G(cx), wss_values ) ) continue;

                //add crt to the result set
                zval* ws_element;
                ALLOC_INIT_ZVAL( ws_element );
                object_init_ex(ws_element, wss_element_class);

                zend_update_property_string(
                    wss_element_class, ws_element,"uuid", strlen("uuid"), const_cast<char*>( it->first.c_str() ) TSRMLS_CC);
                zend_update_property(
                    wss_element_class, ws_element,"worksheet", strlen("worksheet"), getThis() TSRMLS_CC);

                add_next_index_zval( zval_ret, ws_element );
            }

            RETURN_ZVAL( zval_ret,  true, true )

        } catch (const std::exception& e) {
            php_error_docref(NULL TSRMLS_CC, E_ERROR, "Errors in execution: %s.", e.what());
        } catch (const std::string& e) {
            php_error_docref(NULL TSRMLS_CC, E_ERROR, "Errors in execution: %s.", e.c_str());
        }

        RETURN_NULL()
    */
}

/* \brief
 * list of all methods of the worksheet elements object and their access modifiers
 *
 */
static zend_function_entry wss_worksheet_elements_functions[] = {
    PHP_ME( elements, __construct, wss_one_arg, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR )
    PHP_ME( elements, __set, wss_two_args, ZEND_ACC_PUBLIC )
    PHP_ME( elements, __get, wss_one_arg, ZEND_ACC_PUBLIC )
    PHP_ME( elements, parent, wss_no_args, ZEND_ACC_PUBLIC )
    PHP_ME( elements, add, wss_one_arg, ZEND_ACC_PUBLIC )
    PHP_ME( elements, remove, wss_one_arg, ZEND_ACC_PUBLIC )
    PHP_ME( elements, lookup, wss_one_arg, ZEND_ACC_PUBLIC )
    PHP_ME( elements, list, wss_no_args, ZEND_ACC_PUBLIC )
    PHP_ME( elements, count, wss_no_args, ZEND_ACC_PUBLIC )
    PHP_ME( elements, item, wss_one_arg, ZEND_ACC_PUBLIC ) {
        NULL, NULL, NULL
    }
};

void register_worksheet_elements_object( TSRMLS_D )
{
    // register internal wss<=>php wrapper objects
    zend_class_entry ce;

    INIT_CLASS_ENTRY( ce, "elements", wss_worksheet_elements_functions );
    wss_elements_class = zend_register_internal_class( &ce TSRMLS_CC );
    zend_declare_property_null( wss_elements_class, WSS_PHP_STRING_NO_NULL( "m_ws_uuid" ), ZEND_ACC_PRIVATE TSRMLS_CC );
}
