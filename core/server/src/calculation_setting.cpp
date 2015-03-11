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
#include "wss/calculation_setting.hpp"
#include "core_logging.hpp"

calculation_settings::calculation_settings()
    : m_maximum_iterations( 100 )
    , m_minimum_change( 0.001 )
    , m_auto_calculation( true )
{}

calculation_settings::calculation_settings( const calculation_settings& other )
    : m_maximum_iterations( other.m_maximum_iterations )
    , m_minimum_change( other.m_minimum_change )
    , m_auto_calculation( other.m_auto_calculation )
{}

std::size_t calculation_settings::maximum_iterations() const
{
    lock_type lock( m_mutex );
    return m_maximum_iterations;
}

void calculation_settings::maximum_iterations( std::size_t iterations )
{
    lock_type lock( m_mutex );
    m_maximum_iterations = iterations;
}

double calculation_settings::minimum_change() const
{
    lock_type lock( m_mutex );
    return m_minimum_change;
}

void calculation_settings::minimum_change( double minimum_change )
{
    lock_type lock( m_mutex );
    m_minimum_change = minimum_change;
}

void calculation_settings::auto_calculation( bool val )
{
    lock_type lock( m_mutex );
    if ( val != m_auto_calculation ) {
        if ( val ) {
            LOG_CORE_INFO( "Enabling auto calculation!" );
        } else {
            LOG_CORE_INFO( "Disabling auto calculation!" );
        }
    }
    m_auto_calculation = val;
}
