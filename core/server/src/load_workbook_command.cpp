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
 *  Vali Nitu <vali@yalos-solutions.com>
 *  Frieder Hofmann <frieder.hofmann@jedox.com>
 */

#include "precompiled_header.hpp"
#include "wss/load_workbook_command.hpp"
#include "wss/application.hpp"
#include "wss/server.hpp"
#include "wss/worksheet.hpp"
#include "object_lookup.hpp"
#include "wss/scoped_neutral_locale_enforcer.hpp"
#include <boost/algorithm/string.hpp>
#include "wss/i_import_filter.hpp"

#include "core_logging.hpp"
#ifdef _DEBUG
#include "abstract_dependency.hpp"
#endif // _DEBUG

namespace bfs = boost::filesystem;

inline bfs::path remove_trailing_autosave_extension( bfs::path file_path )
{
    const std::string file_string = file_path.string();
    if ( ( file_string.size() > 2 ) && ( file_string.compare( file_string.size() - 2, 1, "~" ) == 0 ) ) {

        std::vector<std::string> split_vec;
        const std::string tmp_file_name_string = file_path.leaf();
        boost::algorithm::split( split_vec, tmp_file_name_string, boost::is_from_range( '.', '.' ) );
        std::string path_after_split;
        const std::string::size_type end = split_vec.size() - 3;
        path_after_split = split_vec[0];
        for ( std::string::size_type i = 1; i < end; ++i ) {
            path_after_split.push_back( '.' );
            path_after_split += split_vec[i];
        }
        return bfs::path( file_path.remove_leaf().string() + path_after_split );
    } else {
        return file_path;
    }
}

load_workbook_command::load_workbook_command( session& s, const bfs::path& file_path, const std::string& meta_data, const bool overwrite_existing /* = true */, const bool is_temp /* = false */ )
    : base_command<i_command>::base_command( s )
    , m_file_path( file_path )
    , m_meta_data( meta_data )
    , m_overwrite_existing( overwrite_existing )
    , m_is_temp( is_temp )
{}

void load_workbook_command::execute()
{
#ifdef _DEBUG
    LOG_CORE_DEBUG( ">>>>>>>>>>before load we have \"" << abstract_dependency::use_count() << "\" dependencies!" )
#endif // _DEBUG


    LOG_CORE_INFO( "attempting to load Workbook " << m_file_path << " for user " << m_session.username() );


    shared_application_type       app    = m_session.selected().application();
    if ( ! app ) {
        throw object_not_found_exception();
    }
    shared_workbook_type       wb;

    filter_registry::shared_import_filter_type wss_filter  = server::instance().filters().get_import_filter( "wss" );
    scoped_neutral_locale_enforcer snle( m_session );
    if ( m_overwrite_existing ) {
        try {
            wb = object_lookup::workbook( m_session, app, convert_utf8_ci( m_file_path.leaf() ) );           //might throw object_not_found_exception
            app->remove( wb->uuid() );                                //might throw object_unloading_exception
        } catch ( const object_not_found_exception& ) {
        }
    }
    std::vector<std::string> dummy;
    wb = wss_filter->do_import( m_session, *app, dummy, m_file_path );
    wb->path( remove_trailing_autosave_extension( m_file_path ) );
    wb->data_string( m_meta_data );
    if ( m_is_temp ) {
        wb->is_temp( true );
    }
    m_uuid = boost::lexical_cast<std::string>( wb->uuid() );

    wb->flag_changed( false );
    wb->flag_changed_autosave( false );

    LOG_CORE_INFO( "successfully loaded Workbook " << m_file_path << " for user " << m_session.username() );

#ifdef _DEBUG
    LOG_CORE_DEBUG( ">>>>>>>>>>after load we have \"" << abstract_dependency::use_count() << "\" dependencies!" )
#endif // _DEBUG
}

const load_workbook_command::result_type& load_workbook_command::value() const
{
    return m_uuid;
}

DEFINE_CLONEABLE( load_workbook_command );

