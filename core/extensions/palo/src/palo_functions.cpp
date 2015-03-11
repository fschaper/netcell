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
*  Florian Schaper <florian.schaper@jedox.com>
*/


#include "palo_wrapper.hpp"
#include "palo_functions.hpp"

#include <wss/function_entry.hpp>
#include <wss/function_registry.hpp>

// function entry signature:
// function_entry( extension_function callback
//                 , const utf8_ci_string& name
//                 , const std::string& argument_mask
//                 , bool is_volatile = false
//                 , bool is_lazy = false
//                 , bool need_view_independent_calculation = false );

/*!
 * \brief
 * registers the wrapped palo function with worksheetsserver function registry.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
#define REGISTER_PALO_FUNCTION( fFUNCTION, fNAME, fNUMARGS, fVIEWINDEPENDENT, fEXECUTEONSET, fRETURNTYPE ) \
    { std::string f_alias( fNAME ); \
        if (f_alias.find(".") != f_alias.npos ) { \
            boost::replace_all( f_alias, ".", "_" ); \
            registry.register_function( function_entry( &fFUNCTION, convert_utf8_ci( f_alias ), "", true, false, fVIEWINDEPENDENT, fEXECUTEONSET, fRETURNTYPE ) ); \
        } \
    } \
    registry.register_function( function_entry( &fFUNCTION, fNAME, "", true, false, fVIEWINDEPENDENT, fEXECUTEONSET, fRETURNTYPE ) );

/*!
 * \brief
 * wraps a palo spreadsheet function in a callback compatible with worksheetservers function form.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
#define PALO_FUNCTION_WRAPPER(fWRAPPED_NAME, fSPREAD_NAME ) \
    interpreter_variant fWRAPPED_NAME( function_parameter& p ) \
    { \
        return palo_wrapper()( &spreadsheet_function::fSPREAD_NAME, #fSPREAD_NAME, p ); \
    }

//include the auto generated palo functions
#include "function_declaration.hpp"

void register_palo_functions( function_registry& registry )
{
    // include the auto generated function registration
#   include "function_registration.hpp"
}
