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
#include <wss/session.hpp>
#include "logging.hpp"
#include "php_includes.hpp"
#include "php_file_callback_task.hpp"
#include "value_converter.hpp"

php_file_callback_task::php_file_callback_task( const boost::filesystem::path& file , const std::string& function_name , const parameter_list_type& parameters )
    : m_file( file )
    , m_function_name( function_name )
    , m_parameters( parameters )
{}

void php_file_callback_task::operator()() const
{
    TSRMLS_FETCH();

    zend_first_try {
        zend_file_handle script;
        memset( &script, 0, sizeof( zend_file_handle ) );

        script.type      = ZEND_HANDLE_FP;
        script.filename  = const_cast<char*>( m_file.string().c_str() );
        script.handle.fp = fopen( script.filename, "rb" );

        if ( script.handle.fp != NULL ) {
            // execute the php script
            zend_execute_scripts( ZEND_REQUIRE_ONCE TSRMLS_CC, NULL, 1, &script );

            // the script is now parsed and evaluated
            zval* function_name = NULL;
            ALLOC_INIT_ZVAL( function_name );
            ZVAL_STRING( function_name, const_cast<char*>( m_function_name.c_str() ), true );

            // convert the parameters from jedox::wss:Value to zval format
            zval** parameters = ( zval** )safe_emalloc( m_parameters.size() * sizeof( zval* ), 1, 0 );

            unsigned i = 0;
            for ( parameter_list_type::const_iterator it = m_parameters.begin(); it != m_parameters.end(); ++it, ++i ) {
                MAKE_STD_ZVAL( parameters[i] );
                value_converter()( WSS_PHP_G( session_context )->locale(), parameters[i], *it );
            }

            // now we call the function function_name in the php code*/
            zval* zend_return_value = NULL;
            ALLOC_INIT_ZVAL( zend_return_value );
            call_user_function( EG( function_table ), NULL, function_name, zend_return_value, ( zend_uint ) m_parameters.size(), parameters TSRMLS_CC );
            m_result = value_converter()( zend_return_value TSRMLS_CC );

            // cleanup
            zval_dtor( zend_return_value );
            //free( parameters );
            for ( i = 0; i < m_parameters.size(); ++i ) {
                zval_ptr_dtor( &parameters[i] );
            }
            efree( parameters );
            zval_dtor( function_name );

        } else {
            LOG_PHP_ERROR( "failed to execute PHP function '" << m_function_name << "()' from file '" << m_file.string() << "': unable to open file" );
            m_result = variant::error_value;
        }
    } zend_catch {
        LOG_PHP_ERROR( "failed to execute PHP function '" << m_function_name << "()' from file '" << m_file.string() << "': unable to execute function" );
        m_result = variant::error_value;
    } zend_end_try();
}

const variant& php_file_callback_task::result() const
{
    return m_result;
}
