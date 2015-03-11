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
 * Florian Schaper <florian.schaper@jedox.com>
 */

#include "precompiled_header.hpp"
#include <wss/range_reference.hpp>
#include <wss/worksheet.hpp>
#include <wss/range.hpp>

/*!
 * \brief
 * returns the number of volatile dependencies (the reference itself included).
 *
 * \param function_parameter& parameters
 * single reference or range of references
 *
 * \returns
 * number of volatile dependencies
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
interpreter_variant function_volatile_count( function_parameter& parameters )
{
    if ( 1 != parameters.count() ) {
        // formula-error! We give #REF! until we can give a message-window.
        return interpreter_variant( variant::error_value );
    }

    const interpreter_variant& my_cell = parameters[0];
    if ( interpreter_variant::type_range == my_cell.i_type() ) {
        const shared_reference_type& sr = my_cell.reference();
        if ( sr->type() == i_dependency_reference::range_reference ) {
            shared_worksheet_type sws( range_reference_cast( sr ).worksheet().lock() );
            if ( sws ) {
                return interpreter_variant( sws->range( range_reference_cast( sr ).actualize().position() ).volatile_count() );
            }
        }
    }

    return interpreter_variant( variant::error_value );
}
