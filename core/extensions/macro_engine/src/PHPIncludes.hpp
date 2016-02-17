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
 *  Dragan Simic <dragan.simic@develabs.com>
 */

#ifndef _PHPINCLUDES
#   define _PHPINCLUDES

// Prevent inclusion of the inline math library into
// the object file which includes this header file
#if defined(WIN32) && !defined(_INC_MATH)
#   define _INC_MATH
#   define WSS_PHP_INCLUDES_DO_UNDEF
#endif

// PHP already declares everything as extern "C" but
// you never now
extern "C"
{
#ifdef WIN32
#   define _WS2DEF_
#   define _WINSOCK2API_
#endif

#ifdef WIN32
#   pragma warning ( push, 1 )
#endif

#include "debug_defines.hpp"

#include <main/php.h>
#include <main/php_main.h>

#ifdef WIN32
#   pragma warning ( pop )
#endif
};

#ifdef WSS_PHP_INCLUDES_DO_UNDEF
#   undef _INC_MATH
#endif

#ifdef __unix__
#   define PATH_SEPARATOR ":"
#   define DIRECTORY_SEPARATOR "/"
#else
#   define PATH_SEPARATOR ";"
#   define DIRECTORY_SEPARATOR "\\"
#endif // __unix__

#endif // _PHPINCLUDES
