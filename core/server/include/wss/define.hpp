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

#pragma once
#include <boost/foreach.hpp>

#define foreach BOOST_FOREACH

#if defined( WIN32 )
# define NOMINMAX
#endif

#if defined(_DEBUG) && defined(_WSS_UNIT_TESTS)
#  if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#    include<string>
#    include<boost/lexical_cast.hpp>
#  endif
#  undef assert
#  undef my_assert
#  define assert(e) ((void) ((e) ? 0 : throw_on_assertion (#e, __FILE__, __LINE__)))
#  if !defined(_MY_ASSERT_ALREADY_DEFINED_ )
#  define _MY_ASSERT_ALREADY_DEFINED_
template<class err_T, class filename_T, class line_T>
inline void throw_on_assertion( const err_T e, const filename_T file, const line_T line )
{
    throw std::runtime_error( boost::lexical_cast<std::string>( file ) + ":" + boost::lexical_cast<std::string>( line ) + ": failed assertion " + std::string( e ) );
}
#  endif
#endif

#if !defined(NO_WSS_MODULE)
# if !defined( WIN32 )
#  define WSS_MODULE __attribute__ ((__visibility__("default")))
#  if defined ( __GNUC__ ) && defined( __unix__ ) && defined( __i386__ )
#   define __cdecl __attribute__((cdecl))
#  else
#   define __cdecl
#  endif
# else
#  ifdef WSS_BUILD_EXPORTS
#   define WSS_MODULE __declspec( dllexport )
#  else
#   define WSS_MODULE __declspec( dllimport )
#  endif
# endif
#else
# define WSS_MODULE
#endif

#if defined(BOOST_MSVC) && (_MSC_FULL_VER >= 160000000 && _MSC_FULL_VER < 170000000)
# define USING_VS_2010 1
# define _CLRCALL_OR_CDECL_DEFINE_ __CLRCALL_OR_CDECL
#else
# define _CLRCALL_OR_CDECL_DEFINE_ __cdecl
#endif
