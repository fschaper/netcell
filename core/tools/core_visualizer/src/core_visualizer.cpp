/**
 *  \file 
 *  Copyright (C) 2006-2010 Jedox AG
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License (Version 2) as published
 *  by the Free Software Foundation at http://www.gnu.org/copyleft/gpl.html.
 *
 *  This program is distributed in the hope that it wiluser_locale be useful, but WITHOUT
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
#include <wss/a1conversion.hpp>
#include "core_visualizer.hpp"


/*!
 * \brief
 * display sheet_point objects in A1 notation inside the debugger.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
CORE_VISUALIZER_API HRESULT WINAPI display_sheet_point( DWORD address, DEBUGHELPER *debug_helper, int base, BOOL uni_strings, char *result_string, size_t max_result_size, DWORD reserved )
{
    DWORD bytes_read;
    sheet_point sp(0,0);
    if( FAILED( debug_helper->ReadDebuggeeMemoryEx( debug_helper, debug_helper->GetRealAddress(debug_helper), sizeof(sheet_point), &sp, &bytes_read ) ) ) {
        return E_FAIL;
    }

    if( bytes_read != sizeof(sheet_point) ) {
        return E_FAIL;
    }

    std::string a1_notation = a1conversion::to_a1::from_point( sp );

    strcpy_s( result_string, max_result_size, a1_notation.c_str() );

    return S_OK;
}

/*!
 * \brief
 * display sheet_range objects in A1 notation inside the debugger.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
CORE_VISUALIZER_API HRESULT WINAPI display_sheet_range( DWORD address, DEBUGHELPER *debug_helper, int base, BOOL uni_strings, char *result_string, size_t max_result_size, DWORD reserved )
{

    DWORD bytes_read;
    sheet_range sr( sheet_point( 0,0 ) );
    if( FAILED( debug_helper->ReadDebuggeeMemoryEx( debug_helper, debug_helper->GetRealAddress(debug_helper), sizeof(sheet_range), &sr, &bytes_read ) ) ) {
        return E_FAIL;
    }

    if( bytes_read != sizeof(sheet_range) ) {
        return E_FAIL;
    }

    std::string a1_notation = a1conversion::to_a1::from_range( sr );

    strcpy_s( result_string, max_result_size, a1_notation.c_str() );

    return S_OK;
}

