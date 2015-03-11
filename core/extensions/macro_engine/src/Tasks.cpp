/*!
 *  \file
 *  Copyright (C) 2006-2008 Jedox AG, Freiburg i.Br., Germany
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
 *  <a href="http://www.jedox.com/license_worksheetserver.txt">
 *    http://www.jedox.com/license_worksheetserver.txt
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
#ifdef Tasks

#include "Tasks.hpp"
#include "PHPIncludes.hpp"
#include "PHPValueConverter.hpp"
#include "logging_wrappers.hpp"

// boost
#include <string>
#include <boost/scoped_array.hpp>

php_eval_file_task_callback::php_eval_file_task_callback( const std::string& php_file_name,
        const std::string& php_callback_function,
        const task_arguments_list_type& php_function_arguments )
    : m_php_file_name( php_file_name )
    , m_php_callback_function( php_callback_function )
    , m_arguments( php_function_arguments )
{}

void php_eval_file_task_callback::operator()() const
{
    TSRMLS_FETCH();

    zend_first_try {
        zend_file_handle script;
        memset( &script, 0, sizeof( zend_file_handle ) );

        script.type      = ZEND_HANDLE_FP;
        script.filename  = const_cast<char*>( m_php_file_name.c_str() );
        script.handle.fp = fopen( script.filename, "rb" );

        if ( script.handle.fp != NULL ) {
            // execute the php script
            zend_execute_scripts( ZEND_REQUIRE_ONCE TSRMLS_CC, NULL, 1, &script );

            // the script is now parsed and evaluated
            zval function_name;
            INIT_ZVAL( function_name );
            ZVAL_STRING( &function_name, const_cast<char*>( m_php_callback_function.c_str() ), 1 );

            // convert the parameters from jedox::wss:Value to zval format
            zval** parameters = ( zval** )safe_emalloc(  m_arguments.size() * sizeof( zval* ), 1, 0 );

            unsigned i = 0;
            for ( task_arguments_list_type::const_iterator it = m_arguments.begin(); it != m_arguments.end(); ++it, ++i ) {
                MAKE_STD_ZVAL( parameters[i] );
                zend_value_converter()( parameters[i], *it );
            }

            // now we call the function function_name in the php code
            zval return_value;
            INIT_ZVAL( return_value );
            call_user_function( EG( function_table ), NULL, &function_name, &return_value, m_arguments.size(), parameters TSRMLS_CC );
            m_return_value = zend_value_converter()( &return_value TSRMLS_CC );

            for ( i = 0; i < m_arguments.size(); ++i ) {
                zval_ptr_dtor( &parameters[i] );
            }

            // cleanup
            zval_dtor( &return_value );
            zval_dtor( &function_name );

        } else {
            LOG_PHP_ERROR( "failed to execute PHP function '" << m_php_callback_function << "()' from file '" << m_php_file_name <<
            "': unable to open file" );
        }
    } zend_catch {
        LOG_PHP_ERROR( "failed to execute PHP function '" << m_php_callback_function << "()' from file '" << m_php_file_name <<
        "': unable to execute function" );
    } zend_end_try();
}

const interpreter_variant& php_eval_file_task_callback::get_result() const
{
    return m_return_value;
}
#endif
