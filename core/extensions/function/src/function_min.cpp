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
 *  Radu Ialovoi <ialovoi@yalos-solutions.com>
 */

#include "precompiled_header.hpp"
#include <boost/foreach.hpp>
#include <limits>
#define foreach BOOST_FOREACH

/*!
 * \brief
 * Returns the smallest number in a set of values.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the smallest number of the parameters
 *
 * \details
 * Arguments that are numbers, logical values, or text representations of numbers are counted.
 * Empty parameters are evaluated as 0, empty cells are ignored.
 * Error values cause errors. Text that cannot be translated into numbers cause the #VALUE! error value.
 * If an argument is an array or reference, only numbers in that array or reference are used.
 * Empty cells, logical values, or text in the array or reference are ignored.
 * If the arguments contain no numbers, MIN returns 0.
 *
 * \see
 * function_mina | function_dmin
 *
 * \author
 * Radu Ialovoi <ialovoi@yalos-solutions.com>
 */
interpreter_variant function_min( function_parameter& parameters )
{
    double min = std::numeric_limits<double>::max();
    size_t  count = 0;

    foreach( const variant & i, parameters ) {
        if ( variant::type_array == i.type() ) {
            foreach( const variant::sparse_array_type::mapping_type::value_type & v, i.array().direct() ) {
                if ( !v.second.is_double() ) {
                    continue;
                }
                double crt = v.second.as_double();
                if ( min > crt ) {
                    min = crt;
                }

                count++;
            }
        } else {
            if ( !i.is_double() ) {
                continue;
            }
            double crt = i.as_double();
            if ( min > crt ) {
                min = crt;
            }

            count++;
        }
    }

    if ( 0 == count ) {
        return interpreter_variant( variant( 0.0 ) );
    }

    return interpreter_variant( min );

}
