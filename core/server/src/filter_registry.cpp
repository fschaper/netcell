/**
*  \file
*  Copyright (C) 2006-2010 Jedox AG, Freiburg i.Br., Germany
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
*  \Author
*  Florian Schaper <florian.schaper@jedox.com>
*/

#include "precompiled_header.hpp"
#include "wss/filter_registry.hpp"

#include "wss/i_import_filter.hpp"
#include "wss/i_export_filter.hpp"
#include "wss/filter_registry_exception.hpp"

void filter_registry::register_import_filter( const shared_import_filter_type& filter )
{
    const i_import_filter::import_filter_extension_list_type extension_list = filter->extensions();
    for  ( i_import_filter::import_filter_extension_list_type::const_iterator i = extension_list.begin(), e = extension_list.end(); i != e; ++i ) {
        m_import_filter_table[ boost::algorithm::to_lower_copy( *i ) ] = shared_import_filter_type( filter ) ;
    }
}

void filter_registry::register_export_filter( const shared_export_filter_type& filter )
{
    const i_export_filter::export_filter_extension_list_type extension_list = filter->extensions();
    for  ( i_export_filter::export_filter_extension_list_type::const_iterator i = extension_list.begin(), e = extension_list.end(); i != e; ++i ) {
        m_export_filter_table[ boost::algorithm::to_lower_copy( *i ) ] = shared_export_filter_type( filter ) ;
    }
}

filter_registry::shared_import_filter_type filter_registry::get_import_filter( const std::string& file_extension )
{
    import_filter_table_type::const_iterator it( m_import_filter_table.find( boost::algorithm::to_lower_copy( file_extension ) ) );
    if ( it == m_import_filter_table.end() ) {
        throw filter_registry_exception( file_extension );
    }
    return it->second;
}

filter_registry::shared_export_filter_type filter_registry::get_export_filter( const std::string& file_extension )
{
    export_filter_table_type::const_iterator it( m_export_filter_table.find( boost::algorithm::to_lower_copy( file_extension ) ) );
    if ( it == m_export_filter_table.end() ) {
        throw filter_registry_exception( file_extension );
    }
    return it->second;
}
