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

#include "precompiled_header.hpp"
#include "wss/worksheet.hpp"
#include "wss/sheet_layout_manager.hpp"

/*!
* \brief
* hide row if param 1 is true
*
* \param function_parameter& parameters
* container of parameters and context which holds information about the current calculation state
*
* \author
* Vali Nitu <vali@yalos-solutions.com>
*/
interpreter_variant function_hiderow( function_parameter& parameters )
{
    if ( parameters.count() != 1 ) {
        // formula-error! We give #REF! until we can give a message-window.
        return interpreter_variant( variant::error_ref );
    }

    unsigned int row_no = parameters.context().caller()->position().row();

    const bool hide = parameters[ 0 ].as_boolean( parameters.context().locale() );

    shared_worksheet_type ws = parameters.context().caller()->worksheet().lock();

    if ( hide ) {

        ws->layout().hide_row( row_no );

    } else {

        ws->layout().unhide_row( row_no );

    }

    return interpreter_variant( variant( hide ) );
}
