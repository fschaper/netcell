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

#include <wss/logging.hpp>

#define LOG_CORE( log_level, message ) LOG( log_level, "[core] " << message )
#ifdef _DEBUG
#define LOG_CORE_TRACE( message ) LOG_CORE( ::logging::log_level::trace, message )
#else
#define LOG_CORE_TRACE( message )
#endif // _DEBUG
#define LOG_CORE_DEBUG( message ) LOG_CORE( ::logging::log_level::debug, message )
#define LOG_CORE_INFO( message ) LOG_CORE( ::logging::log_level::info, message )
#define LOG_CORE_NOTICE( message ) LOG_CORE( ::logging::log_level::notice, message )
#define LOG_CORE_WARNING( message ) LOG_CORE( ::logging::log_level::warning, message )
#define LOG_CORE_ERROR( message ) LOG_CORE( ::logging::log_level::error, message )
#define LOG_CORE_CRITICAL( message ) LOG_CORE( ::logging::log_level::critical, message )
