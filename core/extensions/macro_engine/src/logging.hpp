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
 *  Florian Schaper <florian.schaper@jedox.com>
 */

#pragma once

#include <wss/logging.hpp>

#define LOG_PHP_ERROR(x) LOG_ERROR("[php_macro_engine] " << x)
#define LOG_PHP_DEBUG(x) LOG_DEBUG("[php_macro_engine] " << x)
#define LOG_PHP_INFO(x)  LOG_INFO("[php_macro_engine] " << x)
#define LOG_PHP(level, x) LOG( level, "[php_macro_engine] " << x )

class log_level_converter
{
public:
    log_level_converter();

    std::string operator()( const logging::log_level::level log_level ) const;
    logging::log_level::level operator()( int php_level ) const;
};
