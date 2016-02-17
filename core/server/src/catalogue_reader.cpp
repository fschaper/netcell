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
 *  Florian Schaper <florian.schaper@jedox.com>
 */

#include "precompiled_header.hpp"
#include "catalogue_reader.hpp"
#include "function_table_parser.hpp"
#include "wss/translation_map.hpp"
#include "wss/translation_table.hpp"
#include "wss/define.hpp"
#include "core_logging.hpp"

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <fstream>
#   include <boost/filesystem.hpp>
#endif

/*!
 * \brief
 * descent recursively and read the catalogue files.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
static void recursive_reader( const std::string& filename, const boost::filesystem::path& current_directory )
{
    if ( boost::filesystem::exists( current_directory ) == false || boost::filesystem::is_directory( current_directory ) == false ) {
        // TODO throw
    }

    for ( boost::filesystem::directory_iterator it( current_directory ), end; it != end; ++it ) {
        if ( boost::filesystem::is_directory( it->status() ) ) {
            recursive_reader( filename, it->path() );
        } else if ( it->path().leaf() == filename ) {
            catalogue_reader::parse_file( it->string() );
        }
    }
}

/*!
 * \brief
 * call the recursive descent.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
void catalogue_reader::parse_directory_tree( const std::string& filename, const boost::filesystem::path& path )
{
    recursive_reader( filename, path );
}

/*!
 * \brief
 * parse the catalogue file and create a translation map.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
void catalogue_reader::parse_file( const boost::filesystem::path& file )
{
    std::ifstream stream( file.string().c_str(), std::ios::in );
    if ( ! stream.good() ) {
        LOG_CORE_ERROR( "failed to load function catalogue '" << file.string() << "'" );
        return;
    }

    ::jedox::wss::function_table ft;
    xio::xml::binding::parser().parse_doc( stream, ft );
    stream.close();

    if ( ft.translation_table.present() ) {
        ::jedox::wss::translation_table_type& tt = ft.translation_table.get();

        shared_translation_map_type map( translation_map::create( ::locale::create( tt.lang ), tt.general.parameter_separator, tt.general.column_separator, tt.general.row_separator, tt.general.use_dot, tt.general.boolean_true, tt.general.boolean_false ) );
        foreach( const ::jedox::wss::function_type & f, tt.function ) {
            map->add( translation_map::function_translation_entry( f.name, f.translation, f.description._long_, f.description._short_ ) );
        }

        translation_table::instance().add( map );
    }
}

