/*!
 *  \file
 *  Copyright (C) 2006-2009 Jedox AG, Freiburg i.Br., Germany
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
#include "wss2php_loglevel.hpp"

std::string wss2php_loglevel( logging::log_level::level log_level )
{
    switch ( log_level ) {
        case logging::log_level::debug:
            return "E_ALL|E_STRICT";

        case logging::log_level::info:
            return "E_ALL";

        case logging::log_level::notice:
            return "E_COMPILE_ERROR|E_RECOVERABLE_ERROR|E_ERROR|E_CORE_ERROR|E_WARNING|E_CORE_WARNING|E_COMPILE_WARNING|E_PARSE|E_NOTICE" ;

        case logging::log_level::warning:
            return "E_COMPILE_ERROR|E_RECOVERABLE_ERROR|E_ERROR|E_CORE_ERROR|E_WARNING|E_CORE_WARNING|E_COMPILE_WARNING|E_PARSE" ;

        case logging::log_level::error:
            return "E_COMPILE_ERROR|E_RECOVERABLE_ERROR|E_ERROR|E_CORE_ERROR";

        case logging::log_level::critical:
            return "E_COMPILE_ERROR|E_ERROR|E_CORE_ERROR";

        default:
            return "E_COMPILE_ERROR|E_ERROR|E_CORE_ERROR";
    }
}



