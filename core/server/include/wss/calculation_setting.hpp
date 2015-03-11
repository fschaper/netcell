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

#include <wss/define.hpp>

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
# include <boost/thread/mutex.hpp>
#endif // HAS_PRECOMPILED_HEADER == 0

/*!
 * \brief
 * application wide settings that influence the calculation.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class WSS_MODULE calculation_settings
{
    typedef boost::mutex mutex_type;
    typedef mutex_type::scoped_lock lock_type;
public:
    /*!
     * \brief
     * constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    calculation_settings();

    /*!
     * \brief
     * copy constructor.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    calculation_settings( const calculation_settings& other );

    /*!
     * \brief
     * sets the maximum number of times a cyclic dependency
     * should recurse.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void maximum_iterations( std::size_t iterations );

    /*!
     * \brief
     * sets the minimum change that must occur between
     * calculations for the cyclic calculation to continue.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    void minimum_change( double minimum_change );

    /*!
     * \brief
     * gets the maximum number of times a cyclic dependency
     * should recurse.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    std::size_t maximum_iterations() const;

    /*!
     * \brief
     * gets the minimum change that must occur between
     * calculations for the cyclic calculation to continue.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    double minimum_change() const;

    /*!
     * \brief
     * enable/disable auto calculation
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    void auto_calculation( bool val );

    /*!
     * \brief
     * auto calculation
     *
     * \author
     * Frieder Hofmann <frieder.hofmann@jedox.com>
     */
    inline bool auto_calculation() const {
        lock_type lock( m_mutex );
        return m_auto_calculation;
    }

private:
    mutable mutex_type m_mutex;
    std::size_t m_maximum_iterations;
    double m_minimum_change;
    bool m_auto_calculation;
};

