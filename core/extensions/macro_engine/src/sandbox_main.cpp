#ifdef sandbox_main

#include <iostream>
#include <string>

//#define PHP_EMBED

#ifdef PHP_EMBED
#   ifdef WIN32
#       pragma comment(lib,"php5embed.lib")
#   endif

extern "C"
{
#   include <sapi/embed/php_embed.h>
};

#else
#   ifdef WIN32
#       pragma comment(lib,"php5ts_debug.lib")
#   endif
#   include "PHPSapi.hpp"
#endif

#include "PHPIncludes.hpp"

void php_out( const std::string& string )
{
    std::cout << string;
}

int main( int argc, char* argv[] )
{
#ifndef PHP_EMBED
    PHPSapi& sapi = PHPSapi::get_instance();
    sapi.on_unbuffered_write.connect( &php_out );
#endif

    {
#ifndef PHP_EMBED
        PHPSapi::auto_requestor_type requestor = sapi.get_requestor();
        TSRMLS_FETCH();
#endif

        // TODO: unused?
        //zval * parameters[2];
        //zval function_name;

        zval* return_value;
        ALLOC_INIT_ZVAL( return_value );

        /*
        MAKE_STD_ZVAL( parameters[0] );
        MAKE_STD_ZVAL( parameters[1] );
        ZVAL_STRING( parameters[0],"Test1",1);
        ZVAL_STRING( parameters[1],"Test2",1);
        ZVAL_STRING(&function_name, "wss_macro_entry", 1);
        */

        zend_file_handle script;
        memset( &script, 0, sizeof( zend_file_handle ) );
        script.type = ZEND_HANDLE_FP;
        script.filename = "php_macro_test.php";
        script.opened_path = NULL;
        script.free_filename = 0;
        script.handle.fp = fopen( script.filename, "rb" );
        assert( NULL != script.handle.fp );

        // TODO: unused?
        //zval * script_return_value = NULL;

#ifdef PHP_EMBED
        argc = 0;
        argv = NULL;
        PHP_EMBED_START_BLOCK( argc, argv )
#endif

        php_execute_script( &script TSRMLS_CC );

#ifdef PHP_EMBED
        PHP_EMBED_END_BLOCK()
#endif

        /*
        zend_execute_scripts(ZEND_REQUIRE_ONCE TSRMLS_CC, NULL, 1, &script );
        zend_eval_string_ex("function wss_macro_entry( $parameter, $value ) { echo 'php script called with '.$parameter.' and '.$value; }", NULL, "wss macro engine", 1 TSRMLS_CC );
        call_user_function( EG(function_table), NULL, &function_name, &return_value, 2, parameters TSRMLS_CC );
        */
    }

    return 0;
}
#endif
