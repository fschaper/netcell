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

#include "wss/date_timestamp_modifier.hpp"

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   include <sstream>
#   include <iomanip>
#   include <boost/date_time.hpp>
#   include <boost/date_time/local_time/local_time.hpp>
#endif

namespace logging
{

    date_timestamp_modifier::date_timestamp_modifier()
        : m_format( "[%Y/%m/%d %H:%M:%S]" )
    {}

    void date_timestamp_modifier::apply( log_level::level /*level*/, std::string& to_modify ) const
    {
        std::stringstream s;
        boost::posix_time::time_facet* output_facet = new boost::posix_time::time_facet();
        s.imbue( std::locale( std::locale::classic(), output_facet ) );
        output_facet->format( m_format.c_str() );
        s << boost::posix_time::second_clock::local_time() << " ";

        to_modify.insert( 0, s.str() );
    }

    void date_timestamp_modifier::format( const std::string& f )
    {
        m_format = f;
    }

    date_timestamp_modifier::modifier_name_type date_timestamp_modifier::modifier_name() const
    {
        return name();
    }

    date_timestamp_modifier::modifier_name_type date_timestamp_modifier::name()
    {
        return "timestamp";
    }

    date_timestamp_modifier_creator::result_type date_timestamp_modifier_creator::create() const
    {
        return result_type( new date_timestamp_modifier() );
    }
}

