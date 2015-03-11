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
#include "wss/save_workbook_command.hpp"
#include "wss/application.hpp"
#include "wss/server.hpp"
#include "wss/scoped_neutral_locale_enforcer.hpp"
#include "wss/scoped_selection_state.hpp"
#include "wss/i_export_filter.hpp"
#include "core_logging.hpp"

namespace bfs = boost::filesystem;

save_workbook_command::save_workbook_command( session& s, const uuid_type& id,  const bfs::path& file_path, bool overwrite_existing, bool as_snapshot/* = false*/ )
    : base_command<i_command>::base_command( s )
    , m_wb_id( id )
    , m_file_path( file_path )
    , m_overwrite_existing( overwrite_existing )
    , m_as_snapshot( as_snapshot )
{}

void save_workbook_command::execute()
{
    shared_workbook_type            wb;
    filter_registry::shared_export_filter_type  wss_filter  = server::instance().filters().get_export_filter( "wss" );
    shared_application_type         app    = m_session.selected().application();
    bfs::path         arg_file_path;

    if ( ! app ) {
        throw object_not_found_exception();
    }

    if ( m_wb_id.is_nil() ) {

        wb = m_session.selected().workbook().lock();

        if ( ! wb ) {
            throw object_not_found_exception();
        }

    } else {
        wb = app->get( m_session, m_wb_id );//might throw object_not_found_exception
    }

    if ( m_file_path.empty() ) {
        arg_file_path = wb->path();
    } else {
        arg_file_path = m_file_path;
    }

    //this will ensure that we have en_us locale until this object goes out of scope
    scoped_selection_state          sel_state( m_session );
    scoped_neutral_locale_enforcer  neutral_session( m_session );

    //create a temporary copy first and then move it to the real position
    bfs::path tmp_arg_file_path( arg_file_path.string() + ".~tmp" );

    if ( bfs::exists( tmp_arg_file_path ) ) {
        bfs::remove( tmp_arg_file_path );
    }

    m_session.selected().workbook( wb );

    LOG_CORE_INFO( "saving Workbook " << arg_file_path.string()  << " for user " << m_session.username() );

    wss_filter->do_export( m_session, *wb, tmp_arg_file_path, m_as_snapshot );

    if ( bfs::exists( arg_file_path ) ) {
        bfs::remove( arg_file_path );
    }

    bfs::rename( tmp_arg_file_path, arg_file_path );

    if ( !m_file_path.empty() ) {
        wb->path( arg_file_path );
    }


    m_session.undo_redo_log().remove_workbook_undo_redo_list( *wb );
    wb->flag_changed( false );
    m_session.remove_autosave( wb->path().string() );
}

DEFINE_CLONEABLE( save_workbook_command );

