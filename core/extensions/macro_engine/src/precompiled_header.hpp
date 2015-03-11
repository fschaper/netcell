/**
 *  \file
 *  Copyright (C) 2006-2010 Jedox AG, Freiburg i.Br., Germany
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

#define BOOST_FILESYSTEM_VERSION 2

#ifdef WIN32
# pragma once
#endif

#ifdef WIN32
#ifndef _WIN32_WINNT
#   define _WIN32_WINNT 0x0501
#endif
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
// usage of the PHPSapi requires the php5ts.lib for windows builds
# ifdef _DEBUG
#  if !defined(_MT) && !defined(_DLL)
#   error "You have to link with /MDd during debug build's to be compatible with the php dll"
#  endif
# else
#  if !defined(_MT) && !defined(_DLL)
#   error "You have to link with /MD during debug build's to be compatible with the php dll"
#  endif
# endif  // _DEBUG
#endif // WIN32

#include <map>
#include <list>
#include <string>
#include <vector>
#include <exception>
#include <stdexcept>

#include <boost/thread.hpp>
#include <boost/foreach.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/thread/tss.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem/operations.hpp>

#define foreach BOOST_FOREACH

# if defined(BOOST_MSVC)
# pragma warning(push)
# pragma warning(disable:4800)
# pragma warning(disable:4311)
# pragma warning(disable:4312)
# pragma warning(disable:4244)
# endif

#include <wss/a1conversion.hpp>
#include <wss/object_registry.hpp>
#include <wss/rectangle.hpp>
#include <wss/server.hpp>
#include <wss/session.hpp>
#include <wss/application.hpp>
#include <wss/worksheet_element_storage.hpp>
#include <wss/worksheet.hpp>
#include <wss/range.hpp>
#include <wss/worksheet_element.hpp>
#include <wss/function_registry.hpp>
#include <wss/function_entry.hpp>
#include <wss/named_formula_accessor.hpp>
#include <wss/fatal_exception.hpp>

# if defined(BOOST_MSVC)
# pragma warning(pop)
# endif

#ifdef __unix__
# define PATH_SEPARATOR ":"
# define DIRECTORY_SEPARATOR "/"
# define _strdup strdup
#else
//#define _WIN32_WINNT 0x0400
# define PATH_SEPARATOR ";"
# define DIRECTORY_SEPARATOR "\\"
# define strdup _strdup
#endif // __unix__
