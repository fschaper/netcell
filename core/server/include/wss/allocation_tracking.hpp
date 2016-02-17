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
#if 0

#include <wss/define.hpp>
#include <cstddef>  // for size_t

struct allocation_payload;

/*!
 * \brief
 * allocation tracking and checking
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class WSS_MODULE allocation_tracking
    : boost::noncopyable
{
public:
    /*!
     * \brief
     * constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    allocation_tracking();

    /*!
     * \brief
     * called by the memory allocation routines to raise
     * the memory count associated with the current object.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void raise( std::size_t size );

    /*!
     * \brief
     * called by the memory allocation routines to lower
     * the memory count associated with the current object.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void lower( std::size_t size );

    /*!
     * \brief
     * will check the currently allocated memory against the set bounds.
     *
     * will return false in case the quota limit has been exceeded and the max
     * quota limit is not set to "0".
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    bool inside_quota_bounds();

    /*!
     * \brief
     * sets the quota limit for the current object.
     * "0" signifies that no quota should be applied.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void quota( std::size_t max_allocation );

    /*!
     * \brief
     * track a memory allocation
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    static void track_allocation( std::size_t size, allocation_payload& pl );

    /*!
     * \brief
     * track a memory deallocation
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    static void track_deallocation( std::size_t size, allocation_payload& pl );

private:
    std::size_t m_allocation_count;
    std::size_t m_max_allocation;
};
#endif // 0
