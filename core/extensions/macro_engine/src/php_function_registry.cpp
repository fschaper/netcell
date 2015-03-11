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
#include "php_function_registry.hpp"
#include "duplicate_handler_exception.hpp"
#include "php_spreadsheet_file_function_wrapper.hpp"
#include "php_spreadsheet_internal_function_wrapper.hpp"

php_function_registry::php_function_registry()
{}

php_function_registry::~php_function_registry()
{}

void php_function_registry::register_function( const std::string& spreadsheet_function_name, const boost::filesystem::path& filename, const std::string& php_function_name, bool is_volatile /*= false */, bool view_independent_calculation /*= false*/ )
{
    register_handler( spreadsheet_function_name, is_volatile, view_independent_calculation, php_spreadsheet_file_function_wrapper::create( filename, php_function_name, is_volatile, view_independent_calculation ) );
}

void php_function_registry::register_function( const std::string& spreadsheet_function_name, const std::string& php_function_name, bool is_volatile /*= false */, bool view_independent_calculation /*= false*/ )
{
    register_handler( spreadsheet_function_name, is_volatile, view_independent_calculation, php_spreadsheet_internal_function_wrapper::create( php_function_name, is_volatile, view_independent_calculation ) );
}

void php_function_registry::register_handler( const std::string& spreadsheet_function_name, bool is_volatile, bool view_independent_calculation, const shared_function_handler_type& handler )
{
    {
        locked_container_type::access container ( m_container );
        if ( ( *container ).find( boost::algorithm::to_lower_copy( spreadsheet_function_name ) ) != ( *container ).end() ) {
            throw duplicate_handler_exception();
        }
        ( *container )[ boost::algorithm::to_lower_copy( spreadsheet_function_name ) ] = handler;
    }

    function_entry entry( boost::ref( static_cast<i_function_wrapper&>( *handler ) ), convert_utf8_ci( spreadsheet_function_name ), "", is_volatile, false, view_independent_calculation );
    server::instance().functions().register_function( entry );
    session* crt_session = session::thread_session();
    if ( NULL != crt_session ) {
        crt_session->clear_cache();
        crt_session->broken_dependencies().notify( spreadsheet_function_name );
    }
}

bool php_function_registry::has_handler( const std::string& spreadsheet_function_name ) const
{
    locked_container_type::access container( m_container );
    return ( *container ).find( boost::algorithm::to_lower_copy( spreadsheet_function_name ) ) != ( *container ).end();
}
