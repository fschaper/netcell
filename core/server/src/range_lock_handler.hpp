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

#include "wss/lock.hpp"
#include "wss/sheet_range.hpp"
#include "wss/type.hpp"

#include "range_lock_keeper.hpp"

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
# include <boost/thread/condition.hpp>
# include <set>
#endif // HAS_PRECOMPILED_HEADER == 0

/*!
 * \brief
 * lock a region of cells on a worksheet.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class range_lock_handler
{
    typedef set_to_use<shared_range_lock_keeper_type>::type container_type;
    typedef boost::mutex mutex_type;
    typedef mutex_type::scoped_lock lock_type;
public:
    /*!
     * \brief
     * returns a lock to a worksheet region of the requested state once
     * it could be acquired.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    shared_range_lock_keeper_type aquire( const sheet_range& sr, lock::type state );

    /*!
     * \brief
     * releases a lock to a worksheet region.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void release( const shared_range_lock_keeper_type& sr );

private:
    /*!
     * \brief
     * returns true if a lock on a region can be established for the current
     * thread.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool can_lock_range( const sheet_range& sr, lock::type state );

private:
    container_type m_container;
    mutex_type m_mutex;
    boost::condition m_not_locked;
};


