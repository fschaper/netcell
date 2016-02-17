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
#include "wss/application.hpp"
#include "wss/object_registry.hpp"
#include "wss/server.hpp"

#include "core_logging.hpp"

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
# include <boost/foreach.hpp>
#endif

application::application( const utf8_ci_string& name )
    : identifiable_object( name )
    , m_calculation_settings()
{
    LOG_CORE_DEBUG( "created application object [" << this->uuid() << "] with name ["  << this->name() << "]" );
}

application::~application()
{
    LOG_CORE_DEBUG( "released application object [" << this->uuid() << "]" );
    server::instance().object_registry().unset( *this );
}

void application::unload()
{
    LOG_CORE_DEBUG( "unloading application object [" << this->uuid() << "]" );
    halt();
    foreach( const shared_workbook_type & wb, locking_iterator() ) {
        wb->unload();
    }
    clear();
}

void application::select( selection_state& s )
{
    LOG_CORE_DEBUG( "selecting application object [" << this->uuid() << "]" );
    s.application( shared_from_this() );
}

shared_application_type application::create( const utf8_ci_string& name )
{
    shared_application_type return_value( boost::make_shared<application>( name ) );
    server::instance().object_registry().set( return_value );
    return return_value;
}

style_set_type& application::default_style()
{
    return m_default_style;
}

const style_set_type& application::default_style() const
{
    return m_default_style;
}

id_name_path_mapping_vec_type application::list_workbooks() const
{
    id_name_path_mapping_vec_type uuid_name_vec;
    foreach( const shared_workbook_type & wb, const_cast<application*>( this )->locking_iterator() ) {
        uuid_name_vec.push_back(
            boost::make_tuple(
                boost::lexical_cast<std::string>( wb->uuid() ),
                convert_utf8_ci( wb->name() ),
                wb->path().file_string(),
                wb->data_string()
            )
        );
    }
    return uuid_name_vec;
}
