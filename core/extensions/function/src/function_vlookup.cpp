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
 * Searches for a value in the leftmost column of a table,
 * and then returns a value in the same row from a column you specify in the table.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the value in the same row from a column you specify in the table
 *
 * \details
 *
 * \see
 * function_hlookup | function_index | function_lookup | function_match
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 * Radu Ialovoi <ialovoi@yalos-solutions.com>
 */
interpreter_variant base_vlookup(
    const variant& lookup_value,
    const interpreter_variant& table_array,
    unsigned int col_index,
    const bool range_lookup,
    interpreter_context& context )
{
    bool foundValue = false;

    switch ( table_array.type() ) {
#if 0
        case interpreter_variant::type_range:
            //#if 0
        {
            // get the table array
            range_reference&                    rref = range_reference_cast( table_array.reference() );
            sparse_range_array                  sra( rref, context );
            const unsigned int                  xmax = rref.actualize().position().column_count();
            const unsigned int                  ymax = rref.actualize().position().row_count();

            // if the index is larger than the number of columns return #REF
            if ( col_index > xmax ) {
                return interpreter_variant( variant::error_ref );
            }

            if ( 0 == ymax ) {
                return interpreter_variant( variant::error_n_a );
            }

            unsigned int rowIndex = 0;
            variant last_crt = sra( 0, rowIndex );
            for ( ; rowIndex < ymax; rowIndex++ ) {
                const variant crt = sra( 0, rowIndex );

                if ( rowIndex == 0 && range_lookup && is_larger( crt, lookup_value ) ) {
                    return interpreter_variant( variant::error_n_a );
                }

                if ( rowIndex > 0 && range_lookup && is_larger( last_crt, crt ) ) {
                    return interpreter_variant( variant::error_n_a );
                }

                if ( is_larger( lookup_value, crt ) && rowIndex < ymax - 1 ) {
                    last_crt = crt;
                    continue;
                }

                if ( range_lookup && rowIndex > 0 ) {
                    foundValue = true;
                    if ( !is_equal( crt, lookup_value ) && rowIndex < ymax - 1 ) {
                        rowIndex--;
                    }
                    break;
                }

                if ( is_equal( crt, lookup_value ) ) {
                    foundValue = true;
                    break;
                }
                last_crt = crt;
            }

            // if the value was found, return the requested entry
            if ( true == foundValue ) {
                return interpreter_variant( sra( col_index - 1, rowIndex ) );
            } else {
                // if the value couldn't be found, return #N/A
                return interpreter_variant( variant::error_n_a );
            }
        }
#endif // 0
        case variant::type_array: {
            boost::uint_fast32_t columnWidth = table_array.column_width();
            const variant::sparse_array_type& arr = table_array.array();
            boost::uint_fast32_t arraySize = ( boost::uint_fast32_t ) arr.size();
            boost::uint_fast32_t rows = arraySize / columnWidth;
            // if the index is larger than the number of columns return #REF
            if ( col_index > columnWidth ) {
                return interpreter_variant( variant::error_ref );
            }
            if ( rows == 0 ) {
                return interpreter_variant( variant::error_n_a );
            }

            //int rowIndex = rows - 1;
            unsigned int rowIndex = 0;
            int lastIndex = -1;
            variant last_crt = variant();
            for ( ; rowIndex < rows; rowIndex++ ) {
                const variant& crt = arr[ rowIndex*columnWidth ];

                if ( lookup_value.type() != crt.type() ) {
                    continue;
                }

                if ( is_larger( lookup_value, crt ) && rowIndex < rows - 1 ) {
                    last_crt = crt;
                    lastIndex = rowIndex;
                    //foundValue = true;
                    continue;
                }

                if ( range_lookup && rowIndex > 0 ) {
                    foundValue = true;
                    if ( is_equal( crt, lookup_value ) ) {
                        lastIndex = rowIndex;
                        continue;
                    }

                    if ( is_larger( lookup_value, crt ) && rowIndex == rows - 1 && lookup_value.type() == crt.type() ) {
                        lastIndex = rowIndex;
                        break;
                    }

                }

                if ( is_equal( crt, lookup_value ) ) {
                    foundValue = true;
                    lastIndex = rowIndex;
                    break;
                }
                last_crt = crt;
            }

            if ( range_lookup && lastIndex >= 0 ) {
                foundValue = true;
            }

            // if the value was found, return the requested entry
            if ( foundValue && lastIndex >= 0 ) {
                return interpreter_variant( arr[ lastIndex*columnWidth + col_index - 1 ] );
            } else {
                // if the value couldn't be found, return #N/A
                return interpreter_variant( variant::error_n_a );
            }
        }
        default:
            return interpreter_variant( variant::error_n_a );
    }
}

/*!
 * \brief
 * Searches for a value in the leftmost column of a table,
 * and then returns a value in the same row from a column you specify in the table.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the value in the same row from a column you specify in the table
 *
 * \details
 *
 * \see
 * function_hlookup | function_index | function_lookup | function_match
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 * Radu Ialovoi <ialovoi@yalos-solutions.com>
 */
interpreter_variant function_vlookup( function_parameter& parameters )
{
    if ( parameters.count() < 3 || parameters.count() > 4 ) {
        // formula-error! We give #REF! until we can give a message-window.
        return interpreter_variant( variant::error_ref );
    }

    // get the value to look for
    interpreter_variant toFind = parameters[0];
    if ( variant::type_error == toFind.type() ) {
        return toFind;
    }

    if ( variant::type_double != toFind.type() && variant::type_bool != toFind.type() && variant::type_string != toFind.type() ) {
        return interpreter_variant( variant::error_n_a );
    }

    // get index
    unsigned int columnIndex = static_cast<unsigned int>( parameters[2].numeric() );
    // If columnIndex is less than 1, VLOOKUP returns the #VALUE! error value.
    if ( 1 > columnIndex ) {
        return interpreter_variant( variant::error_value );
    }
    // look for exact match
    bool range_lookup = parameters.count() == 4 ? ( parameters[3].numeric() != 0 ) : true;

    return base_vlookup( toFind, parameters[1], columnIndex, range_lookup, parameters.context() );
}

