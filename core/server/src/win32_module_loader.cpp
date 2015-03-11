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
#include "win32_module_loader.hpp"

#include "wss/extension_module_load_exception.hpp"
#include "wss/extension_function_call_failed_exception.hpp"

#if !defined(HAS_PRECOMPILED_HEADER ) || HAS_PRECOMPILED_HEADER == 0
#   if defined( WIN32 )
#      define WIN32_LEAN_AND_MEAN
#      include <Windows.h>
#   endif
#endif

#if defined( WIN32 )
win32_module_loader::win32_module_loader( const boost::filesystem::path& filename )
    : m_extension_module( NULL )
{
    m_extension_module = reinterpret_cast<void*>( LoadLibraryA( filename.string().c_str() ) );
    if ( NULL == m_extension_module ) {
        throw extension_module_load_exception();
    }
}

void* win32_module_loader::function( const std::string& function_name ) const
{
    void* function_ptr = GetProcAddress( reinterpret_cast<HMODULE>( m_extension_module ), function_name.c_str() );
    if ( NULL == function_ptr ) {
        throw extension_function_call_failed_exception( function_name );
    }
    return function_ptr;
}
#endif // WIN32
