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

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <boost/date_time.hpp>
#   include <boost/thread.hpp>
#endif

namespace utility
{

    /*!
     * \brief
     * sleep an amount of milliseconds.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    inline void sleep( unsigned int milliseconds )
    {
        if ( ! milliseconds ) {
            // nothing to do
            return;
        }

        static const unsigned int nanoseconds_per_millisecond = 1000000;
        static const unsigned int milliseconds_per_second = 1000;

        unsigned int seconds = milliseconds / milliseconds_per_second;
        unsigned int nanoseconds = ( milliseconds % milliseconds_per_second ) * nanoseconds_per_millisecond;

        boost::xtime xt;
        boost::xtime_get( &xt, boost::TIME_UTC );
        xt.sec += seconds;
        xt.nsec += nanoseconds;
        boost::thread::sleep( xt );
    }
}
