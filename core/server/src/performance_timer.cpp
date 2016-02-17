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
#include "wss/performance_timer.hpp"

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
# include <iostream>
#endif

/*!
 * \brief
 * constructor. prints starting message to stdout
 *
 * writes a default message to stdout
 *
 */
performance_timer::performance_timer()
{
    std::cout << "timing " << std::endl;
    m_start_time = std::clock();
}

/*!
 * \brief
 * constructor. prints starting message plus passed custom message to stdout
 *
 * writes a default message plus passed string to stdout
 *
 * \param
 * activity
 */
performance_timer::performance_timer( const std::string& activity )
{
    std::cout << "timing " << activity << std::endl;
    m_start_time = std::clock();
}

/*!
 * \brief
 * destructor. prints time spent until destruction in ticks and seconds
 *
 */
performance_timer::~performance_timer()
{
    std::clock_t ticks = std::clock() - m_start_time;
    std::cout << "ticks  : " << ticks << '\n'
              << "seconds: " << static_cast<double>( ticks ) / CLOCKS_PER_SEC << '\n' << std::endl;
}

