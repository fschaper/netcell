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
#include "range_lock_handler.hpp"

#include "wss/lock_timeout_exception.hpp"

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
# include <boost/bind.hpp>
# include <boost/foreach.hpp>
#endif // HAS_PRECOMPILED_HEADER == 0

shared_range_lock_keeper_type range_lock_handler::aquire( const sheet_range& sr, lock::type state )
{
    lock_type lock( m_mutex );
    bool has_lock = m_not_locked.timed_wait( lock, boost::posix_time::milliseconds( 500 ), boost::bind( &range_lock_handler::can_lock_range, this, sr, state ) );
    if ( ! has_lock ) {
        throw lock_timeout_exception();
    }
    container_type::iterator it( std::find_if( m_container.begin(), m_container.end(), boost::bind( &range_lock_keeper::coverage, _1 ) == sr && boost::bind( &range_lock_keeper::type, _1 ) == state ) );

    if ( it != m_container.end() ) {
        return *it;
    } else {
        shared_range_lock_keeper_type new_lock( range_lock_keeper::create( sr, state ) );
        m_container.insert( new_lock );
        return new_lock;
    }
}

void range_lock_handler::release( const shared_range_lock_keeper_type& sr )
{
    lock_type lock( m_mutex );
    if ( sr.use_count() < 3 ) {
        m_container.erase( sr );
        m_not_locked.notify_all();
    }
}

bool range_lock_handler::can_lock_range( const sheet_range& coverage, lock::type state )
{
    // allow overlapping for the same thread.
    const boost::thread::id current_thread_id = boost::this_thread::get_id();
    foreach( const shared_range_lock_keeper_type & sr, m_container ) {
        if ( current_thread_id != sr->thread_id() && sr->coverage().does_intersect( coverage )
                && ( sr->type() == lock::exclusive ) ) {
            return false;
        }
    }
    return true;
}



