/**
 *  \file
 *  Copyright (C) 2006-2010 Jedox AG
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
 *  Frieder Hofmann <frieder.hofmann@jedox.com>
 */

#include "precompiled_header.hpp"
#include "wss/get_workbook_variables_command.hpp"
#include "wss/workbook.hpp"
#include "wss/i_import_filter.hpp"
#include "object_lookup.hpp"
#include "wss/filter_registry.hpp"
#include "wss/server.hpp"
#include "wss/invalid_application_exception.hpp"

get_workbook_variables_command::get_workbook_variables_command( session& s, const boost::filesystem::path& file_path )
    : base_command<i_command>::base_command( s )
    , m_file_path( file_path )
{}

void get_workbook_variables_command::execute()
{
    const shared_application_type& app = m_session.selected().application();
    if ( !app ) {
        throw invalid_application_exception();
    }

    filter_registry::shared_import_filter_type  wss_filter  = server::instance().filters().get_import_filter( "wss" );
    //overwrite if exists
    try {
        shared_workbook_type wb = object_lookup::workbook( m_session, app, convert_utf8_ci( m_file_path.leaf() ) );           //might throw object_not_found_exception
        app->remove( wb->uuid() );                                //might throw object_unloading_exception
    } catch ( const object_not_found_exception& ) {
    }


    if ( wss_filter->extended_data_import( m_session, *app, m_file_path ) ) {
        variable_mapping_list_type::const_iterator it( m_session.variable().list().begin() );
        variable_mapping_list_type::const_iterator end_it( m_session.variable().list().end() );
        for ( ; it != end_it; ++it ) {
            m_value.push_back( it->first );
        }
    } else {
        std::vector<std::string> dummy;
        shared_workbook_type wb = wss_filter->do_import( m_session, *app, dummy, m_file_path );
        wb->path( m_file_path );
        m_value = wb->variable_list();
        app->remove( wb->uuid() );

    }
}

get_workbook_variables_command::result_type get_workbook_variables_command::value() const
{
    return m_value;
}

DEFINE_CLONEABLE( get_workbook_variables_command );
