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
 *  \author
 *  Florian Schaper <florian.schaper@jedox.com>
 */

#include "precompiled_header.hpp"
#include "wss/extension_registry.hpp"
#include "wss/extension_registry_exception.hpp"

#include <map>

struct extension_registry::extension_registry_impl {
    typedef std::map<std::string, extension_function> extension_function_map_type;
    extension_function_map_type m_extension_function_map;
};

extension_registry::extension_registry()
    : m_impl( new extension_registry_impl )
{}

void extension_registry::register_extension( const std::string& name, extension_function function )
{
    m_impl->m_extension_function_map[ name ] = function;
}

variant extension_registry::operator()( session& cx, const std::string& module_id, const variant& parameter )
{
    extension_registry_impl::extension_function_map_type& map = m_impl->m_extension_function_map;
    extension_registry_impl::extension_function_map_type::iterator it = map.find( module_id );

    if ( it == map.end() ) {
        throw extension_registry_exception();
    }

    return ( it->second )( cx, parameter );
}

extension_registry::~extension_registry()
{

}
