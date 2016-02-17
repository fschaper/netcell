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
#include "wss/command_chain.hpp"
#include "wss/define.hpp"

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
# include <boost/foreach.hpp>
#endif // HAS_PRECOMPILED_HEADER == 0

command_chain::command_chain()
{}

void command_chain::add( auto_type& ptr )
{
    m_command_list.push_back( ptr );
}

void command_chain::add( const i_command& c )
{
    m_command_list.push_back( c.clone() );
}

void command_chain::execute()
{
    foreach( i_command & cmd, m_command_list ) {
        cmd.execute();
    }
}

const i_command& command_chain::operator[]( unsigned int i ) const
{
    if ( m_command_list.size() <= i ) {
        throw std::logic_error( "Especially for tester:: out of bounds" );
    }
    command_list_type::const_iterator it( m_command_list.begin() );
    std::advance( it, i );
    return *it;
}

DEFINE_CLONEABLE( command_chain );


