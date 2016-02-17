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
#include "wss/log_level_modifier.hpp"

namespace logging
{
    void log_level_modifier::apply( log_level::level level, std::string& to_modify ) const
    {
        switch ( level ) {
            case log_level::trace:
                to_modify.insert( 0, "TRACE " );
                break;
            case log_level::debug:
                to_modify.insert( 0, "DEBUG " );
                break;

            case log_level::info:
                to_modify.insert( 0, "INFO " );
                break;

            case log_level::notice:
                to_modify.insert( 0, "NOTICE " );
                break;

            case log_level::warning:
                to_modify.insert( 0, "WARNING " );
                break;

            case log_level::error:
                to_modify.insert( 0, "ERROR " );
                break;

            case log_level::critical:
                to_modify.insert( 0, "CRITICAL " );
                break;

            default:
                assert( false );
        };
    }

    log_level_modifier::modifier_name_type log_level_modifier::modifier_name() const
    {
        return name();
    }

    log_level_modifier::modifier_name_type log_level_modifier::name()
    {
        return "loglevel";
    }

    log_level_modifier_creator::result_type log_level_modifier_creator::create() const
    {
        return result_type( new log_level_modifier() );
    }
}

