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

#include "php_function_redirection_registry.hpp"
#include "php_function_registry.hpp"
#include "php_spreadsheet_file_function_wrapper.hpp"
#include "php_redirected_spreadsheet_function.hpp"

void php_function_redirection_registry::register_function( const uuid_type& workbook_uuid , const std::string& spreadsheet_function_name, const boost::filesystem::path& filename , const std::string& php_function_name , bool is_volatile /*= false */, bool view_independent_calculation /*= false */ )
{
    const std::string lc_spreadsheet_function_name( boost::algorithm::to_lower_copy( spreadsheet_function_name ) );
    {
        locked_workbook_to_list_map_type::access container ( m_container );
        ( *container )[ workbook_uuid ][ lc_spreadsheet_function_name ] = php_spreadsheet_file_function_wrapper::create( filename, php_function_name, is_volatile, view_independent_calculation );
        static php_function_registry& pfr = php_function_registry::instance();
        if ( ! pfr.has_handler( lc_spreadsheet_function_name ) ) {
            pfr.register_handler( lc_spreadsheet_function_name, is_volatile, view_independent_calculation, php_redirected_spreadsheet_function::create( lc_spreadsheet_function_name ) );
        }
    }
}

const shared_function_handler_type& php_function_redirection_registry::retreive( const uuid_type& workbook_uuid , const std::string& spreadsheet_function_name )
{
    return ( *m_container.lock() )[ workbook_uuid ][ spreadsheet_function_name ];
}

php_function_redirection_registry::php_function_redirection_registry()
{
    workbook_delete_event_connection = workbook::on_global_workbook_delete.connect( boost::bind( &php_function_redirection_registry::observe_workbook_deletion, this, _1 ) ) ;
}

php_function_redirection_registry::~php_function_redirection_registry()
{
    workbook_delete_event_connection.disconnect();
}

void php_function_redirection_registry::observe_workbook_deletion( const workbook& wb )
{
    unregister_workbook( wb.uuid() );
}
void php_function_redirection_registry::unregister_workbook( const uuid_type& uuid )
{
    ( *m_container.lock() ).erase( uuid );
}
