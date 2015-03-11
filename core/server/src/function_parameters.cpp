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
#include "wss/function_parameters.hpp"


function_parameter::function_parameter( interpreter_context& ic, unsigned int parameter_count, subtree_vector_auto_type subtree /* = subtree_vector_auto_type */ )
    : m_ic( ic )
    , m_subtree( subtree )
{
    while ( parameter_count-- && !ic.stack().empty() ) {
        m_parameters.push_front( ic.stack().pop() );
    }
}

function_parameter::container_type::size_type function_parameter::count() const
{
    return m_parameters.size();
}

interpreter_context& function_parameter::context() const
{
    return m_ic;
}

::session& function_parameter::session() const
{
    return context().context().session();
}

interpreter_variant& function_parameter::operator[]( container_type::size_type index )
{
    container_type::iterator it( m_parameters.begin() );
    std::advance( it, index );
    return *it;
}

function_parameter::iterator function_parameter::begin()
{
    return m_parameters.begin();
}

function_parameter::const_iterator function_parameter::begin() const
{
    return m_parameters.begin();
}

function_parameter::iterator function_parameter::end()
{
    return m_parameters.end();
}

function_parameter::const_iterator function_parameter::end() const
{
    return m_parameters.end();
}

const function_parameter::subtree_vector_type& function_parameter::subtree() const
{
    assert( "subtree not initialized!" && m_subtree.get() != NULL );
    return *m_subtree;
}
