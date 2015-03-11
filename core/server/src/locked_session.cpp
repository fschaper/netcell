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
 *  Radu Ialovoi <ialovoi@yalos-solutions.com> refactored this starting from session holder
 */

#include "precompiled_header.hpp"
#include "wss/locked_session.hpp"
#include "wss/session_handler.hpp"
#include "wss/uninitialized_session_exception.hpp"
#include "wss/server.hpp"

locked_session::locked_session() {}

locked_session::locked_session( const shared_session_type& session )
    : m_session( session )
    , m_lock( new lock( session->m_lock ) )
{}

locked_session::locked_session( const locked_session& other )
    : m_session( other.m_session )
{
    other.m_lock->unlock();
    m_lock.reset( new lock( m_session->m_lock ) );
    other.m_session.reset();
}

locked_session::~locked_session() {}

locked_session& locked_session::operator=( const locked_session& rhs )
{
    if ( &rhs != this ) {
        m_session = rhs.m_session;
        rhs.m_lock->unlock();
        m_lock.reset( new lock( m_session->m_lock ) );
    }
    return *this;
}

locked_session::operator bool() const
{
    return m_session;
}

const session* locked_session::operator ->() const
{
    if ( ! m_session ) {
        throw uninitialized_session_exception();
    }
    return m_session.get();
}

session* locked_session::operator ->()
{
    if ( ! m_session ) {
        throw uninitialized_session_exception();
    }
    return m_session.get();
}

session& locked_session::operator *() const
{
    if ( ! m_session ) {
        throw uninitialized_session_exception();
    }
    return *m_session;
}

session& locked_session::operator *()
{
    if ( ! m_session ) {
        throw uninitialized_session_exception();
    }
    return *m_session;
}

