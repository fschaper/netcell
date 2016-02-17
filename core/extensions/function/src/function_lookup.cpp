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
#include "lookup_functors.hpp"

/*!
 * \brief
 * Returns a value either from a one-row or one-column range or from an array.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the value from the corresponding position
 *
 * \details
 * The LOOKUP function has two syntax forms: vector and array.
 * The vector form of LOOKUP looks in a one-row or one-column range (known as a vector) for a value
 * and returns a value from the same position in a second one-row or one-column range.
 * The array form of LOOKUP looks in the first row or column of an array for the specified value
 * and returns a value from the same position in the last row or column of the array.
 *
 * \see
 * function_hlookup | function_index | function_vlookup
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
interpreter_variant function_lookup( function_parameter& parameters )
{
    if ( 2 == parameters.count() ) {

        // get the value to look for
        interpreter_variant toFind = parameters[0];
        if ( variant::type_error == toFind.type() ) {
            return toFind;
        }

        if ( variant::type_double != toFind.type() && variant::type_bool != toFind.type() && variant::type_string != toFind.type() ) {
            return interpreter_variant( variant::error_n_a );
        }

        switch ( parameters[1].i_type() ) {
            case interpreter_variant::type_range: {
                // get the table array
                range_reference&                    rref = range_reference_cast( parameters[1].reference() );
                sparse_range_array                  sra( rref, parameters.context() );
                const unsigned int                  xmax = rref.actualize().position().column_count();
                const unsigned int                  ymax = rref.actualize().position().row_count();

                if ( xmax > ymax ) {
                    return base_hlookup( toFind, parameters[1], ymax, true, parameters.context() );
                } else {
                    return base_vlookup( toFind, parameters[1], xmax, true, parameters.context() );
                }
            }
            case interpreter_variant::type_value: {
                if ( static_cast<variant>( parameters[1] ).type() == variant::type_array ) {
                    boost::uint_fast32_t cols = parameters[1].column_width();
                    const variant::sparse_array_type& arr = parameters[1].array();
                    boost::uint_fast32_t arraySize = ( boost::uint_fast32_t ) arr.size();
                    boost::uint_fast32_t rows = arraySize / cols;

                    if ( cols > rows ) {
                        return base_hlookup( toFind, parameters[1], rows, true, parameters.context() );
                    } else {
                        return base_vlookup( toFind, parameters[1], cols, true, parameters.context() );
                    }
                }
            }
            default:
                return interpreter_variant( variant::error_n_a );
        }
    } else if ( 3 == parameters.count() ) {
        return interpreter_variant( variant::error_ref );
    } else {
        // formula-error! We give #REF! until we can give a message-window.
        return interpreter_variant( variant::error_ref );
    }
}

