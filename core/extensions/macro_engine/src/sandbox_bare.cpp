
#include <iostream>
#include <stdio.h>
#include <sapi/embed/php_embed.h>

int main( int argc, char* argv[] )
{
    // basic parameter checking
    if ( argc <= 1 ) {
        std::cerr << "Usage: " << argv[0] << " filename.php <arguments>" << std::endl;
        return -1;
    }

#ifdef ZTS
    void** *tsrm_ls;
#endif

    zend_file_handle php_script;

    // set up a file handle structure
    php_script.type = ZEND_HANDLE_FP;
    php_script.filename = argv[1];
    php_script.opened_path = NULL;
    php_script.free_filename = 0;

    if ( !( php_script.handle.fp = fopen( php_script.filename, "rb" ) ) ) {
        std::cerr << "Unable to open: " << argv[1] << std::endl;
        return -1;
    }

    // ignore argv[0] when passing to php
    argc--;
    argv++;

    php_embed_init( argc, argv PTSRMLS_CC );

    zend_first_try {
        php_execute_script( &php_script TSRMLS_CC );
    } zend_end_try();

    php_embed_shutdown( TSRMLS_C );

    return 0;
}
