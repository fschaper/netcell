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
#include "wss/named_thread.hpp"

// see reference at http://msdn.microsoft.com/en-us/library/xcb2z8hs.aspx
#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   if defined(WIN32)
#       define _WIN32_WINNT 0x0502
#       include <Windows.h>
#   endif
#endif

#if defined(WIN32)
#   pragma pack(push,8)
struct threadname_info {
    DWORD type; // Must be 0x1000.
    LPCSTR name; // Pointer to name (in user addr space).
    DWORD thread_id; // Thread ID (-1=caller thread).
    DWORD flags; // Reserved for future use, must be zero.
};
#   pragma pack(pop)

#   define MS_VC_EXCEPTION 0x406D1388
#endif

void name_thread( const char* name )
{
#if defined(WIN32)
    threadname_info info;
    info.type = 0x1000;
    info.name = name;
#   pragma warning( disable : 4311 )
    info.thread_id = GetCurrentThreadId();
    info.flags = 0;

    __try {
        RaiseException( MS_VC_EXCEPTION, 0, sizeof( info ) / sizeof( unsigned long* ), reinterpret_cast<  unsigned long* >( &info ) );
    }
    __except( EXCEPTION_EXECUTE_HANDLER ) {
    }
#endif
}
