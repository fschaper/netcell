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
#include "wss/abstract_calculation.hpp"
#include "wss/calculation_context.hpp"
#include "wss/formula.hpp"
#include "wss/ast_formula.hpp"

zend_class_entry* wss_application_class;
extern zend_class_entry* wss_workbooks_class;
extern zend_class_entry* wss_workbook_class;
extern zend_class_entry* wss_wss_exception_class;

ZEND_EXTERN_MODULE_GLOBALS( wssme );

struct dummy_dependency : i_dependency {
    dummy_dependency( const sheet_point& pos ) : m_pos( pos ) {}
    void lock( void ) {}
    bool try_lock( void ) {
        return false;
    }
    void unlock( void ) {}
    dependency_type type( void ) const {
        return free_formula_type;
    }
    bool has_formula( void ) const {
        return false;
    }
    bool has_precedents( void ) const {
        return false;
    }
    bool has_dependents( void ) const {
        return false;
    }
    referencetable_type precedents( const shared_dependency_type& ) const {
        static referencetable_type empty;
        return empty;
    }
    referencetable_type precedents( void ) const {
        static referencetable_type empty;
        return empty;
    }
    const dependency_set_type& dependents( void ) const {
        static dependency_set_type empty;
        return empty;
    }
    void value( session&, const variant&, const sheet_point& ) {}
    variant value( interpreter_context& ) const {
        return variant();
    }
    variant value( calculation_context& ) const {
        return variant();
    }
    std::string formula( const locale& ) const {
        return std::string();
    }
    void calculate( calculation_context& ) {}
    void calculate( interpreter_context& ) {}
    weak_worksheet_type worksheet( void ) const {
        return session::thread_session()->selected().worksheet();
    }
    void register_dependent( const shared_dependency_type& ) {}
    void unregister_dependent( const shared_dependency_type& ) {}
    optional_variant_type fetch_cached_volatile( calculation_context& ) const {
        return optional_variant_type();
    }
    bool is_dirty( void ) const {
        return false;
    }
    bool is_volatile( void ) const {
        return false;
    }
    bool is_array( void ) const {
        return false;
    }
    sheet_range array_coverage( void ) const {
        static sheet_range empty( sheet_point( 0, 0 ), sheet_point( 0, 0 ) );
        return empty;
    }
    bool flag_dirty( const bool ) {
        return false;
    }
    const sheet_point& position( void ) const {
        return m_pos;
    }
    void flag_relative( void ) {}
    void raise_volatile_count( void ) {}
    void lower_volatile_count( void ) {}
    unsigned long volatile_count( void ) const {
        return 0;
    }
    unsigned long volatile_count_without_formula( void ) const {
        return 0;
    }
    void internal_flag_dirty( void ) {}
    void internal_raise_volatile_count( void ) {}
    void internal_lower_volatile_count( void ) {}
    void flag_moved( void ) {}
    optional_sheet_range_type coverage( void ) const {
        return optional_sheet_range_type();
    }
    std::string get_debug_identifier( void ) const {
        return "x-me";
    }
private:
    const sheet_point& m_pos;
};

struct dummy_calculation : abstract_calculation {
    dummy_calculation( calculation_context& cc, formula& f, shared_dependency_type sd )
        : abstract_calculation( cc, sd, f, variant(), 0 )
    {}
    variant operator ()( interpreter_context& ) {
        return variant();
    }
};

/* \brief
 * constructs a new PHP application object based on the current session
 */
static PHP_METHOD( application, __construct )
{
    zval* app_uuid = NULL;

    if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "|z", &app_uuid ) == FAILURE ) {
        BEGIN_CORE_CATCH_BLOCK()
        throw fatal_exception( "WRONG_PARAM_COUNT" );
        END_CORE_CATCH_BLOCK()
        WRONG_PARAM_COUNT;
    }

    if ( NULL == app_uuid ) {
        const shared_application_type app = WSS_PHP_G( session_context )->selected().application();

        TEST_SHARED_OBJ( app );

        const std::string uuid( boost::lexical_cast<std::string>( app->uuid() ) );
        zend_update_property_string( wss_application_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_uuid" ), const_cast<char*>( uuid.c_str() ) TSRMLS_CC );
    } else {
        zend_update_property_string( wss_application_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_uuid" ), Z_STRVAL_P( app_uuid ) TSRMLS_CC );
    }
}

/*!
* \brief
* proxy calls made from PHP side to core functions.
* \author
* Radu Racariu <radu@yalos-solutions.com>
*/
static PHP_METHOD( application, __call )
{
    zval* z_function = NULL;
    zval* z_args = NULL;
    if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "zz", &z_function, &z_args ) == FAILURE ) {
        WRONG_PARAM_COUNT;
    }
    bool has_new_ic = false;
    interpreter_context* ic = WSS_PHP_G( interpreter_context );
    try {
        std::string wss_function( Z_STRVAL_P( z_function ) );
        if ( wss_function != "" ) {
            const function_registry& fr = server::instance().functions();
            boost::to_upper( wss_function );
            if ( fr.has_function_entry( wss_function ) ) {
                const variant& arguments = value_converter()( z_args TSRMLS_CC );
#ifdef function_entry
#undef function_entry
#endif
                if ( NULL == ic ) {
                    calculation_context cc( *( WSS_PHP_G( session_context ) ) );
                    ast_formula ast( cc.session(), cc.session().selected().worksheet(), "=1" );
                    const sheet_point& point = WSS_PHP_G( session_context )->selected().range().upper_left();
                    shared_dependency_type sd = boost::make_shared<dummy_dependency>( point );
                    formula f( ast , sd, point );
                    dummy_calculation ac( cc, f, sd );
                    has_new_ic = true;
                    ic =  new interpreter_context( sd,  ac, cc );
                    ic->raise_inside_function_count();
                }

                if ( arguments.is_array() ) {
                    foreach ( const variant & iv, arguments.array() ) {
                        ic->stack().push( interpreter_variant( iv ) );
                    }
                } else {
                    ic->stack().push( interpreter_variant( arguments ) );
                }
                function_parameter fparam( *ic, arguments.is_array() ? ( unsigned int )arguments.array().size() : 1 );
                const interpreter_variant& wss_ret =  fr.function_entry( wss_function )( fparam );
                if ( wss_ret.is_error() ) {
                    RETURN_NULL();
                }
                zval* z_ret = NULL;
                ALLOC_INIT_ZVAL ( z_ret );
                value_converter()( ic->locale(), z_ret, wss_ret );
                if ( has_new_ic && ic ) {
                    delete ic;
                    ic = NULL;
                }
                RETURN_ZVAL( z_ret, 1, 0 );
            } else {
                LOG_PHP_ERROR( "Function \"" +  wss_function + "\" not registered with Palo Web." );
            }
        }
    } catch ( std::exception& e ) {
        if ( has_new_ic && ic ) {
            delete ic;
            ic = NULL;
        }
        LOG_PHP_ERROR( "Error while executing: " +  std::string( Z_STRVAL_P( z_function ) ) + ". Cause: " + e.what() );
        RETURN_NULL();
    }
}

PHP_PROPERTY_SETTER( application );
PHP_PROPERTY_GETTER( application );

/*!
 * \brief
 * TODO this needs to be implemented and documented
 */
static PHP_METHOD( application, activecell )
{

    PHP_FUNC_CHECK_FOR_READONLY_PROPERTY;

    assert( !"not implemented" );
    RETURN_NULL();

}

/*!
 * \brief
 * Returns the PHP Wrapper for the users currently active Range
 *
 * \remarks
 * calls the global function activerange
 *
 * \returns
 * instance of the users currently active range or NULL if the user
 * has no range selected.
 *
 * \see
 * activerange
 */
static PHP_METHOD( application, activerange )
{
    PHP_FUNC_CHECK_FOR_READONLY_PROPERTY;

    zval* zval_function_name;
    ALLOC_INIT_ZVAL( zval_function_name );
    ZVAL_STRING( zval_function_name, "activerange", 1 );
    call_user_function( EG( function_table ), NULL, zval_function_name, return_value, 0, NULL TSRMLS_CC );
    zval_dtor( zval_function_name );
}

/*!
 * \brief
 * TODO this needs to be implemented and documented
 */
static PHP_METHOD( application, activechart )
{

    PHP_FUNC_CHECK_FOR_READONLY_PROPERTY;

    assert( !"not implemented" );
    RETURN_NULL();
}

/*!
 * \brief
 * Returns the PHP Wrapper for the users currently selected Worksheet
 *
 * \remarks
 * calls the global function activesheet
 *
 * \returns
 * instance of the users currently selected worksheet or NULL if the user
 * has no worksheet selected.
 *
 * \see
 * activesheet
 */
static PHP_METHOD( application, activesheet )
{
    PHP_FUNC_CHECK_FOR_READONLY_PROPERTY;

    zval* zval_function_name;
    ALLOC_INIT_ZVAL( zval_function_name );
    ZVAL_STRING( zval_function_name, "activesheet", 1 );
    call_user_function( EG( function_table ), NULL, zval_function_name, return_value, 0, NULL TSRMLS_CC );
    zval_dtor( zval_function_name );
}

/*!
 * \brief
 * returns the workbooks PHP wrapper for the Application object
 *
 * returns an workbooks object which is basically an wrapper around
 * the add/get/remove container functions of wss3.
 *
 * \returns
 * workbooks object
 */
static PHP_METHOD( application, workbooks )
{
    PHP_FUNC_CHECK_FOR_READONLY_PROPERTY;

    zval*            zval_wbs       = NULL;
    zval*            zval_app_uuid   = zend_read_property( wss_application_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_uuid" ), 1 TSRMLS_CC );

    ALLOC_INIT_ZVAL( zval_wbs );
    object_init_ex( zval_wbs, wss_workbooks_class );
    zend_call_method_with_1_params( &zval_wbs, wss_workbooks_class, NULL, "__construct", NULL, zval_app_uuid );
    RETURN_ZVAL( zval_wbs, 1, 0 );
}

/*!
 * \brief
 * returns or sets the name of the application object
 *
 * \param name
 * optional parameter, when given the method sets the name of the application to "name"
 *
 * \returns
 * name of the application object if "name" parameter was omitted
 */
static PHP_METHOD( application, name )
{
    char* application_name = NULL;
    long application_name_len = 0;

    if ( ZEND_NUM_ARGS() > 0 ) {
        if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "s", &application_name, &application_name_len ) == FAILURE ) {
            WRONG_PARAM_COUNT;
        }
    }

    zval* zval_uuid = zend_read_property( wss_application_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_uuid" ), 1 TSRMLS_CC );
    GET_SHARED_OBJ( application, zval_uuid );

    if ( NULL == application_name ) {
        RETURN_STRING( const_cast< char* >( shared_obj->name().c_str() ), 1 );
    } else {
        shared_obj->name( application_name );
    }
}

/*!
 * \brief
 * returns the uuid of the application object
 *
 * \returns
 * unique identifier of the application object
 */
static PHP_METHOD( application, uuid )
{
    PHP_FUNC_CHECK_FOR_READONLY_PROPERTY;

    zval* zval_uuid = zend_read_property( wss_application_class, getThis(), WSS_PHP_STRING_NO_NULL( "m_uuid" ), 1 TSRMLS_CC );
    RETURN_ZVAL( zval_uuid, 1, 0 )
}

/*!
 * \brief
 * from here on the cache won't be cleared until end_calculation is called
*/
static PHP_METHOD( application, begin_calculation )
{
    bool clear_one_more_time = true;
    if ( zend_parse_parameters( ZEND_NUM_ARGS() TSRMLS_CC, "|b", &clear_one_more_time ) == FAILURE ) {
        WRONG_PARAM_COUNT;
    }

    WSS_PHP_G( session_context )->begin_calculation( clear_one_more_time );
}

/*!
 * \brief
 * start clearing the calculation cache again
 */
static PHP_METHOD( application, end_calculation )
{
    WSS_PHP_G( session_context )->end_calculation();
}

/*!
 * \brief
 * list of all methods of the application object and their access modifiers
 *
 * \see
 * register_application_object
 */
static zend_function_entry wss_application_functions[] = {
    PHP_ME( application, __construct, wss_no_args, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR )
    PHP_ME( application, __set, wss_two_args, ZEND_ACC_PUBLIC )
    PHP_ME( application, __get, wss_one_arg, ZEND_ACC_PUBLIC )
    PHP_ME( application, __call, wss_two_args, ZEND_ACC_PUBLIC )
    PHP_ME( application, name, NULL, ZEND_ACC_PUBLIC )
    PHP_ME( application, uuid, wss_no_args, ZEND_ACC_PUBLIC )
    PHP_ME( application, activecell, wss_no_args, ZEND_ACC_PUBLIC )
    PHP_ME( application, activerange, wss_no_args, ZEND_ACC_PUBLIC )
    PHP_ME( application, activechart, wss_no_args, ZEND_ACC_PUBLIC )
    PHP_ME( application, activesheet, wss_no_args, ZEND_ACC_PUBLIC )
    PHP_ME( application, begin_calculation, wss_one_arg, ZEND_ACC_PUBLIC )
    PHP_ME( application, end_calculation, wss_no_args, ZEND_ACC_PUBLIC )
    PHP_ME( application, workbooks, wss_no_args, ZEND_ACC_PUBLIC ) {
        NULL, NULL, NULL
    }
};

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

void register_application_object( TSRMLS_D )
{
    // register internal wss<=>php wrapper objects
    zend_class_entry ce;

    INIT_CLASS_ENTRY( ce, "application", wss_application_functions );
    wss_application_class = zend_register_internal_class( &ce TSRMLS_CC );
    zend_declare_property_null( wss_application_class, WSS_PHP_STRING_NO_NULL( "m_uuid" ), ZEND_ACC_PRIVATE TSRMLS_CC );
}
