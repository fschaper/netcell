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
#include "range_lock_keeper.hpp"

range_lock_keeper::range_lock_keeper( const sheet_range& coverage, lock::type type )
    : m_coverage( coverage )
    , m_lock_type( type )
    , m_thread_id( boost::this_thread::get_id() )
{}

const sheet_range& range_lock_keeper::coverage() const
{
    return m_coverage;
}

lock::type range_lock_keeper::type() const
{
    return m_lock_type;
}

boost::thread::id range_lock_keeper::thread_id() const
{
    return m_thread_id;
}

shared_range_lock_keeper_type range_lock_keeper::create( const sheet_range& coverage, lock::type type )
{
    return boost::make_shared<range_lock_keeper>( coverage, type );
}

bool range_lock_keeper::operator <( const range_lock_keeper& rhs ) const
{
    return m_coverage < rhs.m_coverage;
}

bool range_lock_keeper::operator ==( const range_lock_keeper& rhs ) const
{
    return rhs.m_lock_type == m_lock_type && rhs.m_coverage == m_coverage && rhs.m_thread_id == m_thread_id;
}


