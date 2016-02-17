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
#if 0

#include "wss/allocation_tracking.hpp"
#include "wss/session.hpp"
#include "wss/memory.hpp"

allocation_tracking::allocation_tracking()
    : m_allocation_count( 0 )
    , m_max_allocation( 0 )
{}

void allocation_tracking::raise( std::size_t size )
{
    if ( m_max_allocation != 0 && ( ( m_allocation_count + size ) > m_max_allocation ) ) {
        // (fschaper) this is actually the only exception that is safe to throw at this point
        // since the new and delete handlers exception specification does only allow
        // for std::bad_alloc (which would be swallowed in the case of an nothrow
        // function).
        throw std::bad_alloc();
    }
    m_allocation_count += size;
}

void allocation_tracking::lower( std::size_t size )
{
    m_allocation_count -= size;
}

bool allocation_tracking::inside_quota_bounds()
{
    return m_max_allocation == 0 || m_allocation_count <= m_max_allocation;
}

void allocation_tracking::quota( std::size_t max_allocation )
{
    m_max_allocation = max_allocation;
}

void allocation_tracking::track_allocation( std::size_t size, allocation_payload& pl )
{
    // (fschaper) we may not allocate any memory using the new operators
    // at this point because this would lead to an recursive call.
    session* s = session::thread_session();
    if ( s ) {
        make_payload( weak_session_type( s->shared_from_this() ), pl );
        s->allocation().raise( size );
    }
}

void allocation_tracking::track_deallocation( std::size_t size, allocation_payload& pl )
{
    // (fschaper) we may not allocate any memory using the new operators
    // at this point because this would lead to an recursive call.
    if ( pl.size ) {
        shared_session_type s( static_cast<weak_session_type*>( pl.payload )->lock() );
        if ( s ) {
            s->allocation().lower( size );
        }
    }
}
#endif // 0

