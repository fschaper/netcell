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
#include "wss/interpreter_context.hpp"
#include "wss/session.hpp"

interpreter_context::interpreter_context( const shared_dependency_type& d, ::i_calculation& alias, calculation_context& cc )
    : with_initiator( d )
    , m_alias( alias )
    , m_calculation_context( cc )
    , m_stack()
    , m_is_inside_function_count( 0 )
    , m_last_return_type( return_type_format::unspecified )
    , m_inside_lazy_function_count( 0 )
{
#ifdef _DEBUG
    assert( "no calculation when it is not enabled" && cc.is_calculation_enabled() );
#endif // _DEBUG
    m_calculation_context.interpreter_context( this );
}

interpreter_context::interpreter_context( const shared_dependency_type& d, ::i_calculation& alias, calculation_context& cc, const shared_dependency_type& nf )
    : with_initiator( d, nf )
    , m_alias( alias )
    , m_calculation_context( cc )
    , m_stack()
    , m_is_inside_function_count( 0 )
    , m_last_return_type( return_type_format::unspecified )
    , m_inside_lazy_function_count( 0 )
{
#ifdef _DEBUG
    assert( "no calculation when it is not enabled" && cc.is_calculation_enabled() );
#endif // _DEBUG
    m_calculation_context.interpreter_context( this );
}

::i_calculation& interpreter_context::alias()
{
    return m_alias;
}

bool interpreter_context::has_array_return_type() const
{
    return caller()->is_array();
}

interpreter_context::calculation_stack_type& interpreter_context::stack()
{
    return m_stack;
}


calculation_context& interpreter_context::context()
{
    m_calculation_context.interpreter_context( this );
    return m_calculation_context;
}

const ::locale& interpreter_context::locale() const
{
    return m_calculation_context.session().locale();
}

bool interpreter_context::is_inside_function() const
{
    return 0 < m_is_inside_function_count;
}

void interpreter_context::raise_inside_function_count()
{
    ++m_is_inside_function_count;
}

void interpreter_context::lower_inside_function_count()
{
    assert( "logic error (probably in parser) - tried to lower inside function count below zero! " && m_is_inside_function_count > 0 );
    --m_is_inside_function_count;
}

void interpreter_context::fill_array_with_empty_values()
{
    caller()->must_fill_with_empty();
}

void interpreter_context::last_return_type( return_type_format::type return_type )
{
    if ( m_last_return_type == return_type || return_type_format::unspecified == m_last_return_type  ) {
        m_last_return_type = return_type;
        m_calculation_context.return_type( return_type );
    } else {
        if ( ( return_type_format::date_time == m_last_return_type && return_type_format::numeric == return_type )
                || ( return_type_format::numeric == m_last_return_type && return_type_format::date_time == return_type ) ) {
            m_last_return_type = return_type_format::date_time;
            m_calculation_context.return_type( return_type_format::date_time );
        } else {
            m_last_return_type = return_type_format::unspecified;
            m_calculation_context.return_type( return_type_format::unspecified );
        }
    }
}

return_type_format::type interpreter_context::last_return_type() const
{
    return m_last_return_type;
}
