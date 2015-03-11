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
#include "wss/type.hpp"
#include "wss/function_registry.hpp"
#include "wss/ci_string.hpp"
#include "wss/boost_mutex_trait.hpp"

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
# include <boost/unordered_map.hpp>
# include <boost/algorithm/string.hpp>
# include <boost/thread/mutex.hpp>
#endif


struct function_registry::function_registry_impl
        : public boost_mutex_trait {
    typedef map_to_use<utf8_ci_string, ::function_entry>::type function_map_type;
    mutex_type m_mutex;
    function_map_type m_function_map;
};

function_registry::function_registry()
    : m_impl( new function_registry_impl )
{}

function_registry::~function_registry()
{}

void function_registry::register_function( const ::function_entry& entry )
{
    function_registry_impl::lock_type lock( m_impl->m_mutex );
    m_impl->m_function_map.insert( function_registry_impl::function_map_type::value_type( entry.internal_name(), entry ) );
}

function_entry& function_registry::function_entry( const std::string& name ) const
{
    function_registry_impl::lock_type lock( m_impl->m_mutex );
    function_registry_impl::function_map_type::iterator it = m_impl->m_function_map.find( convert_utf8_ci( name ) );
    if ( it == m_impl->m_function_map.end() ) {
        throw invalid_function_exception( name );
    }
    return it->second;
}

bool function_registry::has_function_entry( const std::string& name ) const
{
    function_registry_impl::lock_type lock( m_impl->m_mutex );
    return m_impl->m_function_map.find( convert_utf8_ci( name ) ) != m_impl->m_function_map.end();
}

