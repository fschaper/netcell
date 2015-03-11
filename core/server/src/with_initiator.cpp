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
#include "wss/with_initiator.hpp"

with_initiator::with_initiator( const shared_dependency_type& initiator )
    : m_initiator( initiator )
    , m_caller( initiator )
    , m_named_formula()
    , m_is_inside_named_formula( false )
{}

with_initiator::with_initiator( const shared_dependency_type& initiator, const shared_dependency_type& named_formula )
    : m_initiator( initiator )
    , m_caller( initiator )
    , m_named_formula( named_formula )
    , m_is_inside_named_formula( true )
{}

const shared_dependency_type& with_initiator::initiator() const
{
    return m_initiator;
}

bool with_initiator::is_inside_named_formula() const
{
    return m_is_inside_named_formula && m_named_formula && m_named_formula != m_initiator;
}

const shared_dependency_type& with_initiator::named_formula_initiator() const
{
    //assert( "different_initiator not given, but now we want to have it. thats not the way it works!" && m_named_formula );
    if ( !m_named_formula ) {
        throw std::logic_error( "different_initiator not given, but now we want to have it. thats not the way it works!" );
    }
    return m_named_formula;
}

const shared_dependency_type& with_initiator::caller() const
{
    return m_caller;
}


with_initiator::scoped_change_caller::scoped_change_caller( with_initiator& initiator,  const shared_dependency_type& caller )
    : m_initiator( initiator )
    , m_old_caller( initiator.m_caller )
{
    m_initiator.m_caller = caller;
}

with_initiator::scoped_change_caller::~scoped_change_caller()
{
    m_initiator.m_caller = m_old_caller;
}
