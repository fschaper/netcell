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
#include "lookup_functors.hpp"


interpreter_variant base_match(
    const variant& lookup_value,
    const interpreter_variant& table_array,
    const int match_type,
    interpreter_context& context )
{
    bool foundValue = false;

    if ( interpreter_variant::type_range == table_array.i_type() ) {
        // get the table array
        range_reference&                    rref = range_reference_cast( table_array.reference() );
        sparse_range_array                  sra( rref, context );
        const unsigned int                  xmax = rref.actualize().position().column_count();
        const unsigned int                  ymax = rref.actualize().position().row_count();
        int                                 size = static_cast<int>( sra.size() );


        if ( 0 == ymax || 0 == xmax ) {
            return interpreter_variant( variant::error_n_a );
        }

        if ( ymax > 1 && xmax > 1 ) {
            return interpreter_variant( variant::error_n_a );
        }


        int i = 0;
        for ( ; i < size; i++ ) {
            const variant& crt = sra[i];

            if ( i == 0 && 0 < match_type && is_larger( crt, lookup_value ) ) {
                return interpreter_variant( variant::error_n_a );
            }

            if ( i == 0 && 0 > match_type && is_larger( lookup_value, crt ) ) {
                return interpreter_variant( variant::error_n_a );
            }

            if ( i > 0 && 0 < match_type && is_larger( sra[i-1], sra[i] ) ) {
                return interpreter_variant( variant::error_n_a );
            }

            if ( i > 0 && 0 > match_type && is_larger( sra[i], sra[i-1] ) ) {
                return interpreter_variant( variant::error_n_a );
            }

            if ( 0 < match_type && is_larger( lookup_value, crt ) ) {
                continue;
            }

            if ( 0 > match_type && is_larger( crt, lookup_value ) ) {
                continue;
            }

            if ( 0 != match_type && i > 0 )  {
                foundValue = true;
                if ( !is_equal( crt, lookup_value ) ) {
                    i--;
                }
                break;
            }

            if ( is_equal( crt, lookup_value ) ) {
                foundValue = true;
                break;
            }
        }

        // if the value was found, return the index
        if ( true == foundValue ) {
            if ( i == -1 ) {
                return interpreter_variant( variant::error_n_a );
            }
            return interpreter_variant( static_cast<double>( i + 1 ) );
        } else {
            if ( 0 == match_type ) {
                // if the value couldn't be found and match_type exact return #N/A
                return interpreter_variant( variant::error_n_a );
            } else {
                return interpreter_variant( static_cast<double>( size ) );
            }
        }
    } else {

        if ( variant::type_array == table_array.type() ) {
            boost::uint_fast32_t columnWidth = table_array.column_width();
            const variant::sparse_array_type& arr = table_array.array();
            boost::uint_fast32_t arraySize = ( boost::uint_fast32_t ) arr.size();
            boost::uint_fast32_t rows = arraySize / columnWidth;
            // if the index is larger than the number of columns return #REF
            if ( 1 < columnWidth && 1 < rows ) {
                return interpreter_variant( variant::error_n_a );
            }
            if ( rows == 0 ) {
                return interpreter_variant( variant::error_n_a );
            }

            int i = 0;
            for ( ; i < ( int )arraySize; i++ ) {
                const variant& crt = arr[i];

                if ( i == 0 && 0 < match_type && is_larger( crt, lookup_value ) ) {
                    return interpreter_variant( variant::error_n_a );
                }

                if ( i == 0 && 0 > match_type && is_larger( lookup_value, crt ) ) {
                    return interpreter_variant( variant::error_n_a );
                }

                if ( i > 0 && 0 < match_type && is_larger( arr[i-1], arr[i] ) ) {
                    return interpreter_variant( variant::error_n_a );
                }

                if ( i > 0 && 0 > match_type && is_larger( arr[i], arr[i-1] ) ) {
                    return interpreter_variant( variant::error_n_a );
                }

                if ( 0 < match_type && is_larger( lookup_value, crt ) ) {
                    continue;
                }

                if ( 0 > match_type && is_larger( crt, lookup_value ) ) {
                    continue;
                }

                if ( 0 != match_type && i > 0 )  {
                    foundValue = true;
                    if ( !is_equal( crt, lookup_value ) ) {
                        i--;
                    }
                    break;
                }

                if ( is_equal( crt, lookup_value ) ) {
                    foundValue = true;
                    break;
                }
            }


            // if the value was found, return the index
            if ( true == foundValue ) {
                if ( i == -1 ) {
                    return interpreter_variant( variant::error_n_a );
                }
                return interpreter_variant( static_cast<double>( i + 1 ) );
            } else {
                if ( 0 == match_type ) {
                    // if the value couldn't be found, return #N/A
                    return interpreter_variant( variant::error_n_a );
                } else {
                    return interpreter_variant( static_cast<double>( arraySize ) );
                }
            }
        } else {

            return interpreter_variant( variant::error_n_a );
        }
    }
}

/*!
 * \brief
 * Returns the relative position of an item in an array that matches a specified value in a specified order.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the position
 *
 * \details
 * MATCH returns the position of the matched value within lookup_array.
 * MATCH does not distinguish between uppercase and lowercase letters when matching text values.
 * If MATCH is unsuccessful in finding a match, it returns the #N/A error value.
 *
 * \see
 * function_hlookup | function_index | function_lookup | function_vlookup
 *
 * \author
 * Vali Nitu <vali@yalos-solutions.com>
 */
interpreter_variant function_match( function_parameter& parameters )
{
    if ( parameters.count() < 2 || parameters.count() > 3 ) {
        // formula-error! We give #REF! until we can give a message-window.
        return interpreter_variant( variant::error_ref );
    }

    // get the value to look for
    interpreter_variant toFind = parameters[0];
    if ( variant::type_error == toFind.type() ) {
        return toFind;
    }

    // look for exact match
    int match_type = 1;
    if ( 3 == parameters.count() ) {
        if ( parameters[2].type() == variant::type_string ) {
            try { // text representations of numbers are evaluated.
                match_type = boost::lexical_cast<int>( static_cast<const std::string&>( parameters[2].string() ) );
            } catch ( boost::bad_lexical_cast& ) {
                // text that cannot be translated into numbers causes the #VALUE! error value.
                return interpreter_variant( variant::error_value );
            }
        } else { // Arguments that are numbers or logical values are counted.
            match_type = static_cast<int>( parameters[2].numeric() );
        }
    }



    interpreter_variant array1 = parameters[0];
    variant::variant_array_type arr1;
    size_t colWidth1;
    if ( array1.i_type() == interpreter_variant::type_range ) {
        range_reference& rref1 = range_reference_cast( array1.reference() );
        sparse_range_array sra1( rref1, parameters.context() );
        size_t imax1 = sra1.size();
        size_t xmax1 = rref1.actualize().position().column_count();
        arr1 = variant::sparse_array_type( imax1 );
        for ( unsigned int i = 0; i < imax1; i++ ) {
            arr1[i] = sra1[i];
        }
        colWidth1 = xmax1;
    } else {
        if ( variant::type_array == array1.type() ) {
            arr1 = array1.array();
        } else {
            arr1.push_back( array1.as_string( parameters.context().locale() ) );
        }
        colWidth1 = array1.column_width();
    }


    size_t arraySize1 = arr1.size();
    size_t rows1 = arraySize1 / colWidth1;

    //if ( variant::type_double != toFind.type() && variant::type_bool != toFind.type() && variant::type_string != toFind.type() ) {
    //    return interpreter_variant( variant::error_n_a );
    //}

    if ( arraySize1 > 1 ) {
        variant::sparse_array_type resultArray;
        for ( size_t i = 0; i < rows1; i++ ) {
            for ( size_t j = 0; j < colWidth1; j++ ) {
                resultArray.push_back( base_match( static_cast<const variant&>( arr1[i * colWidth1 + j] ), parameters[1], match_type, parameters.context() ) ); // Fill resultArray
            }
        }
        variant result( resultArray, ( unsigned int )colWidth1 );
        return interpreter_variant( result );
    }

    return base_match( toFind, parameters[1], match_type, parameters.context() );

}

