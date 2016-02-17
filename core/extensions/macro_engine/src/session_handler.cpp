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
#include "session_handler.hpp"
#include <wss/invalid_session_exception.hpp>

extern const char* g_wssme_superglobal_name;
extern const char* g_session_id_name;

static const char* MODULE_STORAGE_KEY = "MACRO_ENGINE";

ps_module ps_mod_wss_session = {
    PS_MOD_SID( wss_session )
};

/*!
 * \brief
 * returns the users session-id
 *
 * \see
 * PHPBridge::execute_task
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
PS_CREATE_SID_FUNC( wss_session )
{
    // TODO (fschaper) in case that we rely on the session
    // being available via the WSS_PHP_G macro we might
    // no longer need this part of the code.
    union {
        zval** wss_me;
        void* ptr;
    } wss_me_t;

    union {
        zval** session_id;
        void* ptr;
    } session_id_t;

    wss_me_t.ptr = NULL;
    session_id_t.ptr = NULL;

    int result = 0;

    // id must have been set by PHPBridge::execute_task
    result = zend_hash_find( &EG( symbol_table ), const_cast<char*>( g_wssme_superglobal_name ), static_cast<unsigned int>( strlen( g_wssme_superglobal_name ) + 1 ), reinterpret_cast<void**>( &wss_me_t ) );
    assert( result != FAILURE );
    result = zend_hash_find( Z_ARRVAL_PP( wss_me_t.wss_me ), const_cast<char*>( g_session_id_name ), static_cast<unsigned int>( strlen( g_session_id_name ) + 1 ), reinterpret_cast<void**>( &session_id_t ) );
    assert( result != FAILURE );

    return estrndup( Z_STRVAL_PP( session_id_t.session_id ), Z_STRLEN_PP( session_id_t.session_id ) ) ;
}

/*!
 * \brief
 * open session.
 *
 * \remarks
 * need to set something in "data" to signal that the session has been created.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
PS_OPEN_FUNC( wss_session )
{
    PS_SET_MOD_DATA( reinterpret_cast<void*>( 1 ) );
    return SUCCESS;
}

/*!
 * \brief
 * close session.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
PS_CLOSE_FUNC( wss_session )
{
    PS_SET_MOD_DATA( reinterpret_cast<void*>( 0 ) );
    return SUCCESS;
}

/*!
 * \brief
 * read data from the session
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
PS_READ_FUNC( wss_session )
{
    int return_value = FAILURE;

    try {
        if ( WSS_PHP_G( session_context ) ) {
            arbitrary_storage::storage_type session_value = WSS_PHP_G( session_context )->storage().retrieve( MODULE_STORAGE_KEY );

            const arbitrary_storage::storage_type::size_type session_value_size = session_value.size();
            if ( session_value_size ) {
                *vallen = static_cast<int> ( session_value_size );
                if ( *vallen == 0 ) {
                    *val = STR_EMPTY_ALLOC();
                } else {
                    *val = static_cast<char*>( emalloc( session_value_size ) );
                    memcpy( *val, &session_value[ 0 ], session_value_size );
                }
                return_value = SUCCESS;
            }
        }
    } catch ( const invalid_session_exception& ) {
    } catch ( const std::runtime_error& ) {
    }

    return return_value;
}

/*!
 * \brief
 * store data in the session
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
PS_WRITE_FUNC( wss_session )
{
    int return_value = FAILURE;
    try {
        if ( WSS_PHP_G( session_context ) ) {
            WSS_PHP_G( session_context )->storage().store( MODULE_STORAGE_KEY, arbitrary_storage::storage_type( val, val + vallen ) );
            return_value = SUCCESS;
        }
    } catch ( const invalid_session_exception& ) {
    } catch ( const std::runtime_error& ) {
    }
    return return_value;
}

/*!
 * \brief
 * destroy session information identified by "key"
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
PS_DESTROY_FUNC( wss_session )
{
    int return_value = FAILURE;
    try {
        if ( WSS_PHP_G( session_context ) ) {
            WSS_PHP_G( session_context )->storage().remove( MODULE_STORAGE_KEY );
            return_value = SUCCESS;
        }
    } catch ( const invalid_session_exception& ) {
    } catch ( const std::runtime_error& ) {
    }
    return return_value;
}

/*!
 * \brief
 * session cleanup
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
PS_GC_FUNC( wss_session )
{
    return SUCCESS;
}
