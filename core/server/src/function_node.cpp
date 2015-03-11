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
#include "wss/function_node.hpp"

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
# include <boost/algorithm/string.hpp>
#endif // HAS_PRECOMPILED_HEADER == 0

function_node::function_node( const std::string& function_name )
    : m_function_name( string_type( function_name ) )
    , m_lazy_evaluation( false )
    , m_view_independent( false )
{
    try {
        m_function_entry = function_registry::instance().function_entry( function_name );
        m_lazy_evaluation = m_function_entry->is_lazy();
        m_view_independent = m_function_entry->is_in_need_of_view_independent_calculation();
        m_execute_on_set = m_function_entry->execute_on_set();
    } catch ( const invalid_function_exception& ) {
    }
}

function_node::auto_type function_node::create( const std::string& f )
{
    const std::string upper_case_function_name = boost::to_upper_copy( f );
    return auto_type( memory::pooled_creator<function_node>::create( upper_case_function_name ) );
}

bool function_node::is_valid() const
{
    return m_function_entry;
}

bool function_node::is_volatile() const
{
    return ( !m_function_entry ? true : ( *m_function_entry ).is_volatile() );
}

bool function_node::is_view_independent() const
{
    return m_view_independent;
}

bool function_node::executes_on_set() const
{
    return m_execute_on_set;
}

::function_entry& function_node::function_entry()
{
    assert( "invalid entry from function_node requested" && is_valid() );
    return *m_function_entry;
}

const function_node::string_type& function_node::function_name() const
{
    return m_function_name;
}

bool function_node::lazy_evaluation() const
{
    return m_lazy_evaluation;
}
