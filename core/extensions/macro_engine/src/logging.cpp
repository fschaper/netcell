/*!
 *  \file
 *  Copyright (C) 2006-2008 Jedox AG, Freiburg i.Br., Germany
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
 *  Radu Ialovoi <ialovoi@yalos-solutions.com>
 */
#include "precompiled_header.hpp"
#include "logging.hpp"
#include "php_includes.hpp"

log_level_converter::log_level_converter()
{
}

std::string log_level_converter::operator()( const logging::log_level::level log_level ) const
{
    switch ( log_level ) {
        case logging::log_level::debug:
            return "E_ALL|E_STRICT";

        case logging::log_level::info:
            return "E_ALL";

        case logging::log_level::notice:
            return "E_COMPILE_ERROR|E_RECOVERABLE_ERROR|E_ERROR|E_CORE_ERROR|E_WARNING|E_CORE_WARNING|E_COMPILE_WARNING|E_PARSE|E_NOTICE" ;

        case logging::log_level::warning:
            return "E_COMPILE_ERROR|E_RECOVERABLE_ERROR|E_ERROR|E_CORE_ERROR|E_WARNING|E_CORE_WARNING|E_COMPILE_WARNING|E_PARSE";

        case logging::log_level::error:
            return "E_COMPILE_ERROR|E_RECOVERABLE_ERROR|E_ERROR|E_CORE_ERROR";

        default:
        case logging::log_level::critical:
            return "E_COMPILE_ERROR|E_ERROR|E_CORE_ERROR";
    }
}

logging::log_level::level log_level_converter::operator()( int php_level ) const
{
    if ( php_level & ( E_COMPILE_ERROR | E_RECOVERABLE_ERROR | E_ERROR | E_CORE_ERROR ) ) {
        return logging::log_level::error;
    } else if ( php_level & ( E_WARNING | E_CORE_WARNING | E_COMPILE_WARNING ) ) {
        return logging::log_level::warning;
    } else if ( php_level & ( E_NOTICE ) ) {
        return logging::log_level::notice;
    }
    if ( php_level & ( E_ALL | E_STRICT ) ) {
        return logging::log_level::debug;
    } else {
        return logging::log_level::critical;
    }
}
