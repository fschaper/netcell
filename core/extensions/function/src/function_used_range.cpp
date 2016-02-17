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
 *  Frieder Hofmann <frieder.hofmann@jedox.com>
 */

#include "precompiled_header.hpp"
#include <wss/worksheet.hpp>
#include <wss/range.hpp>

/*!
 * \brief
 * returns the lower right corner of the used range
 *
 * \returns
 * used range
 *
 * \author
 * Frieder Hofmann <frieder.hofmann@jedox.com>
 */

interpreter_variant function_used_range( function_parameter& parameters )
{
    if ( 1 < parameters.count() ) {
        // formula-error! We give #REF! until we can give a message-window.
        return interpreter_variant( variant::error_value );
    }

    shared_worksheet_type ws = parameters.session().selected().worksheet().lock();
    if ( !ws ) {
        return interpreter_variant( variant() );
    }

    optional_sheet_range_type used_range;
    if ( parameters.count() != 0 ) {
        used_range = ws->used_range( static_cast<int>( parameters[0].as_double() ) );
    } else {
        used_range = ws->used_range();
    }
    const sheet_point lower_right_point = used_range ? used_range->lower_right() : sheet_point( 0, 0 );
    return interpreter_variant( variant( a1conversion::to_a1::from_point( lower_right_point ) ) );
}
