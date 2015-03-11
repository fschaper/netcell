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

#pragma once

#include <wss/interpreter_variant.hpp>
#include <wss/interpreter_context.hpp>
#include <wss/function_entry.hpp>

#undef ERROR
#undef ERROR_NOT_FOUND
#include <PaloSpreadsheetFuncs/GenericContext.h>
#include <PaloSpreadsheetFuncs/GenericArgumentArray.h>

#include "spreadsheet_function.hpp"

using Palo::SpreadsheetFuncs::GenericContext;
using Palo::SpreadsheetFuncs::GenericArgumentArray;
using Palo::SpreadsheetFuncs::GenericCell;

/*!
 * \brief
 * callback into palo spreadsheet function.
 *
 * this class wraps all parameters into the spreadsheet function specific format and executes palo library function.
 * returns the result in worksheetserver format.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class palo_wrapper
{
public:
    /*!
     * \brief
     * palo function callback signature.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    typedef void( spreadsheet_function::*palo_function )( GenericCell&, GenericContext&, GenericArgumentArray& );

    /*!
     * \brief
     * function wrapper that calls into palo spreadsheet functions after parameter conversion.
     *
     * \author
     * Florian Schaper <florian.schaper@jedox.com>
     */
    interpreter_variant operator()( palo_function p_function, const char* function_name, function_parameter& parameter );
};
