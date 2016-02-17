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
#include <wss/version.hpp>

#include "logging.hpp"
#include "php_includes.hpp"
#include "version_info.hpp"

extern "C"
{
#   include "ext/standard/info.h"   // needed for the minfo block
#   include "ext/session/php_session.h"
}

/*!
 * \brief
 * vanity information
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
static PHP_MINFO_FUNCTION( wssme )
{
    php_info_print_table_start();

    php_info_print_table_row( 2, "worksheetserver macro engine (wssme)", "enabled" );
    php_info_print_table_row( 2, "worksheetserver release", WSS_VERSION_STRING );
    php_info_print_table_row( 2, "authors", "Florian Schaper <florian.schaper@jedox.com>; Dragan Simic <dragan.simic@develabs.com>" );
    php_info_print_table_row( 2, "copyright", "(c) 2007-2010 Jedox AG, Freiburg, Germany" );

    php_info_print_table_end();
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

/*!
 * \brief
 * initialization of the wssme globals.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
static void php_wssme_globals_ctor( zend_wssme_globals* wssme_globals TSRMLS_DC )
{
    // initialization during a thread spin-up
    wssme_globals->session_context = NULL;
    wssme_globals->active_range = NULL;
    wssme_globals->interpreter_context = NULL;
}

/*!
 * \brief
 * destructor of the wssme globals.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
static void php_wssme_globals_dtor( zend_wssme_globals* wssme_globals TSRMLS_DC )
{
}

/*!
 * \brief
 * initialization of the worksheetserver php extension
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
static PHP_MINIT_FUNCTION( wssme )
{
    ZEND_INIT_MODULE_GLOBALS( wssme, NULL, NULL );

#ifdef ZTS
    // ZTS PHP extension global variable handling
    ts_allocate_id( &wssme_globals_id,
                    sizeof( zend_wssme_globals ),
                    ( ts_allocate_ctor )php_wssme_globals_ctor,
                    ( ts_allocate_dtor )php_wssme_globals_dtor );
#else
    php_wssme_globals_ctor( &wssme_globals TSRMLS_CC );
#endif // ZTS

    // register wss super global
    zend_register_auto_global( WSS_PHP_STRING_NO_NULL( "_WSS" ), NULL TSRMLS_CC );

    // register all php macro wrappers
    register_application_object( TSRMLS_C );
    register_workbook_object( TSRMLS_C );
    register_worksheet_object( TSRMLS_C );
    register_range_object( TSRMLS_C );
    register_attribute_object( TSRMLS_C );
    register_col_object( TSRMLS_C );
    register_row_object( TSRMLS_C );
    register_worksheet_element_object( TSRMLS_C );
    register_worksheet_elements_object( TSRMLS_C );
    register_worksheets_object( TSRMLS_C );
    register_workbooks_object( TSRMLS_C );
    register_names_object( TSRMLS_C );
    register_name_object( TSRMLS_C );
    register_core_exception_object( TSRMLS_C );
    register_variant_error_object( TSRMLS_C );

    LOG_PHP_DEBUG( "bridge: registered the php module extension (wssme_module) classes" );

    return SUCCESS;
}

/*!
 * \brief
 * shutdown function of the worksheetserver php extension
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
static PHP_MSHUTDOWN_FUNCTION( wssme )
{
#ifndef ZTS
    php_wssme_globals_dtor( &wssme_globals TSRMLS_CC );
#endif

    return SUCCESS;
}

/*!
 * \brief
 * WSS macro engine PHP extension information
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
zend_module_entry wssme_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    WSS_TO_TEXT( WSS_PHP_MODULE_API_NAME ),
    get_functions(),        // functions
    PHP_MINIT( wssme ),     // minit
    PHP_MSHUTDOWN( wssme ), // mshutdown
    NULL,                   // rinit
    NULL,                   // rshutdown
    PHP_MINFO( wssme ),     // minfo
#if ZEND_MODULE_API_NO >= 20010901
    WSS_TO_TEXT( WSS_PHP_EXTENSION_VERSION ),
#endif
    STANDARD_MODULE_PROPERTIES
};

