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
#include "php_spreadsheet_file_function_wrapper.hpp"
#include "php_file_callback_task.hpp"
#include "php_sapi.hpp"

php_spreadsheet_file_function_wrapper::php_spreadsheet_file_function_wrapper( const boost::filesystem::path& file, const std::string& function_name, bool is_volatile, bool is_view_dependent )
    : i_php_function_wrapper( is_volatile, is_view_dependent )
    , m_file( file )
    , m_function_name( function_name )
{
}

interpreter_variant php_spreadsheet_file_function_wrapper::operator()( function_parameter& parameters ) const
{
    session& s = parameters.session();
    php_file_callback_task task( m_file, m_function_name, php_file_callback_task::parameter_list_type( parameters.begin(), parameters.end() ) );
    shared_worksheet_type worksheet = s.selected().worksheet().lock();
    const sheet_point& point = parameters.context().caller()->position();
    std::string coordinates = a1conversion::to_a1::from_point( point );

    php_sapi::auto_requestor_type request( php_sapi::instance().requestor() );
    request->execute( s, coordinates, task, &parameters.context() );
    return interpreter_variant( task.result() );
}

shared_function_handler_type php_spreadsheet_file_function_wrapper::create( const boost::filesystem::path& file, const std::string& function_name, bool is_volatile, bool is_view_dependent )
{
    return shared_function_handler_type( new php_spreadsheet_file_function_wrapper( file, function_name, is_volatile, is_view_dependent ) );
}
