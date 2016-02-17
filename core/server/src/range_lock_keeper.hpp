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

#pragma once

#include "wss/sheet_range.hpp"
#include "wss/lock.hpp"
#include "wss/type.hpp"

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
# include <boost/thread/thread.hpp>
#endif // HAS_PRECOMPILED_HEADER == 0

/*!
 * \brief
 * object used by the range_lock_handler to keep track of active locks.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class range_lock_keeper
{
    template< class T, class A1, class A2 >
    friend boost::shared_ptr< T > boost::make_shared( A1 const& a1, A2 const& a2 );
public:
    /*!
     * \brief
     * returns the area that is covered by the range_lock.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    const sheet_range& coverage() const;

    /*!
     * \brief
     * the type of the lock (shared or exclusive).
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    lock::type type() const;

    /*!
     * \brief
     * locks the region with the requested locking state.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    static shared_range_lock_keeper_type create( const sheet_range& coverage, lock::type type );

    /*!
     * \brief
     * returns the thread_id that was used to establish the lock of the region.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    boost::thread::id thread_id() const;

    /*!
     * \brief
     * operator lesser than
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool operator <( const range_lock_keeper& rhs ) const;

    /*!
     * \brief
     * operator equals
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool operator ==( const range_lock_keeper& rhs ) const;

private:
    range_lock_keeper( const sheet_range& coverage, lock::type type );

    const sheet_range m_coverage;
    lock::type m_lock_type;
    boost::thread::id m_thread_id;
};

