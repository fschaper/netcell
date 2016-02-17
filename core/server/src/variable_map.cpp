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
#include "wss/variable_map.hpp"
#include "wss/algorithm.hpp"
#include "wss/define.hpp"

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <boost/foreach.hpp>
#endif // HAS_PRECOMPILED_HEADER == 0

variable_map::variable_map()
    : m_mutex()
{}

variable_map::variable_map( const variable_map& other )
{
    lock_type lock( other.m_mutex );
    m_variable_ref_map = other.m_variable_ref_map;
}

variable_map& variable_map::operator=( const variable_map& rhs )
{
    if ( this != &rhs ) {
        lock_type lock_rhs( rhs.m_mutex );
        lock_type lock_this( m_mutex );
        m_variable_ref_map = rhs.m_variable_ref_map;
    }
    return *this;
}

void variable_map::add( const std::string& var_name )
{
    lock_type lock( m_mutex );
    m_variable_ref_map[ var_name ]++;
}

void variable_map::remove( const std::string& var_name )
{
    lock_type lock( m_mutex );
    variable_reference_map::iterator it( m_variable_ref_map.find( var_name ) );

    if ( it != m_variable_ref_map.end() && 1 == ( *it ).second ) {
        m_variable_ref_map.erase( it );
    } else {
        --( *it ).second;
    }
}

void variable_map::remove( const variable_map& map )
{
    foreach( const std::string & v, map.list() ) {
        remove( v );
    }
}

void variable_map::merge( const variable_map& other )
{
    if ( this != &other ) {
        foreach( const std::string & var, other.list() ) {
            add( var );
        }
    }
}

variable_name_list_type variable_map::list() const
{
    variable_name_list_type return_value;
    return_value.reserve( m_variable_ref_map.size() );
    std::back_insert_iterator<variable_name_list_type> bit( return_value );
    {
        lock_type lock( m_mutex );
        std::transform( m_variable_ref_map.begin(), m_variable_ref_map.end(), bit, get_first<variable_reference_map>() );
    }

    return return_value;
}

