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

/*!
 * \brief
 * Counts the number of cells that are not empty and the values within the list of arguments.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the number of cells that are not empty and the values within the list of arguments
 *
 * \details
 * A value is any type of information, including empty text("") but not including empty cells.
 * If an argument is an array or reference, empty cells within the array or reference are ignored.
 * Use COUNTA to count the number of cells that contain data in a range or array.
 *
 * \see
 * internal::CounterA | function_count | function_dcount | function_dcounta
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */

interpreter_variant function_counta( function_parameter& parameters )
{
    double m_count = 0.0;
    foreach( const interpreter_variant & i, parameters ) {
        switch ( i.type() ) {
            case variant::type_empty:
                //nothing to do in that case
                break;
            case variant::type_array:
                foreach( const variant::sparse_array_type::mapping_type::value_type & v, i.array().direct() ) {
                    if ( v.second.is_empty() ) {
                        continue;
                    }
                    ++m_count;
                }
                break;
            case variant::type_double:
            case variant::type_bool:
            case variant::type_string:
            case variant::type_error:
                ++m_count;
                break;
            default:
                throw std::logic_error( "invalid case" );
        }
    }

    return interpreter_variant( variant( m_count ) );
}

