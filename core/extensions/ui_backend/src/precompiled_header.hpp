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
 *  Vali Nitu <vali@yalos-solutions.com>
 */

#pragma once

#ifdef _MSC_VER
# pragma warning ( disable : 4244 )
# pragma warning ( disable : 4267 )
# pragma warning ( disable : 4311 )
# pragma warning ( disable : 4312 )
# pragma warning (push, 2)
#endif

#define BOOST_FILESYSTEM_VERSION 2

// stl
#include <map>
#include <list>
#include <string>
#include <utility>
#include <sstream>


// wss
#include <wss/define.hpp>
#include <wss/session_handler.hpp>
#include <wss/range.hpp>
#include <wss/sheet_range.hpp>
#include <wss/variant.hpp>
#include <wss/worksheet.hpp>
#include <wss/server.hpp>
#include <wss/command.hpp>
#include <wss/threadsafe_singleton.hpp>
#include <wss/sheet_layout_trait.hpp>
#include <wss/execute_fetch.hpp>
#include <wss/named_thread.hpp>
#include <wss/exception.hpp>
#include <wss/type.hpp>
#include <wss/module_registry.hpp>
#include <wss/logger.hpp>

// jlib
#include <wss/singleton.hpp>

//boost
#define BOOST_SPIRIT_THREADSAFE
#include <boost/shared_ptr.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/condition.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/timer.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <boost/thread.hpp>

// ui_backend
#include "memory_manager.hpp"
#include "logging.hpp"
#include "version_info.hpp"
#include "BackendHandler.hpp"


#ifdef _MSC_VER
# pragma warning ( pop )
#endif

