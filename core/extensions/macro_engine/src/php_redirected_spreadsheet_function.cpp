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
#include "php_redirected_spreadsheet_function.hpp"
#include "php_function_redirection_registry.hpp"

php_redirected_spreadsheet_function::php_redirected_spreadsheet_function( const std::string& spreadsheet_function_name )
    : i_php_function_wrapper( false, false ), m_spreadsheet_function_name( spreadsheet_function_name )
{}

interpreter_variant php_redirected_spreadsheet_function::operator()( function_parameter& parameters ) const
{
    static php_function_redirection_registry& registry( php_function_redirection_registry::instance() );
    shared_workbook_type wb = parameters.session().selected().workbook().lock();
    // workbook no longer exists (this shouldn't happen during calculation)
    if ( ! wb ) {
        return interpreter_variant( variant( variant::error_name ) );
    }
    // try to retrieve the handler for the current workbook
    // if there is no handler registered return #NAME!
    const shared_function_handler_type& handler = registry.retreive( wb->uuid(), m_spreadsheet_function_name );
    if ( ! handler ) {
        return interpreter_variant( variant( variant::error_name ) );
    }
    return ( *handler )( parameters );
}

bool php_redirected_spreadsheet_function::is_volatile() const
{
    static php_function_redirection_registry& registry( php_function_redirection_registry::instance() );
    ::session* s = session::thread_session();
    if ( NULL == s ) {
        return false;
    }
    shared_workbook_type wb = s->selected().workbook().lock();
    // workbook no longer exists (this shouldn't happen during calculation)
    if ( ! wb ) {
        return false;
    }
    // try to retrieve the handler for the current workbook
    const shared_function_handler_type& handler = registry.retreive( wb->uuid(), m_spreadsheet_function_name );
    if ( ! handler ) {
        if ( php_function_registry::instance().has_handler( m_spreadsheet_function_name ) ) {
            return true;
        }
        return false;
    }
    return ( *handler ).is_volatile();
}

bool php_redirected_spreadsheet_function::is_view_independent() const
{
    static php_function_redirection_registry& registry( php_function_redirection_registry::instance() );
    ::session* s = session::thread_session();
    if ( NULL == s ) {
        return false;
    }
    shared_workbook_type wb = s->selected().workbook().lock();
    // workbook no longer exists (this shouldn't happen during calculation)
    if ( ! wb ) {
        return false;
    }
    // try to retrieve the handler for the current workbook
    const shared_function_handler_type& handler = registry.retreive( wb->uuid(), m_spreadsheet_function_name );
    if ( ! handler ) {
        return false;
    }
    return ( *handler ).is_view_independent();
}

shared_function_handler_type php_redirected_spreadsheet_function::create( const std::string spreadsheet_function_name )
{
    return shared_function_handler_type( new php_redirected_spreadsheet_function( spreadsheet_function_name ) );
}
