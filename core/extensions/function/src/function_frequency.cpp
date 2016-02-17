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
 *  Radu Racariu <radu@yalos-solutions.com>
 */

#include "precompiled_header.hpp"

/*!
 * \brief
 * Counts how often values occur within a range of values, and returns a vertical array of numbers.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the vertical array of numbers
 *
 * \details
 * must be entered as an array formula (CTRL SHIFT ENTER)
 *
 * \see
 * function_count | function_dcount
 *
 * \author
 * Matthias Roy <matthias.roy@jedox.com>
 * Radu Racariu <radu@yalos-solutions.com>
 */
interpreter_variant function_frequency( function_parameter& parameters )
{
    if ( parameters.count() != 2 ) {
        // formula-error! We give #REF! until we can give a message-window.
        return interpreter_variant( variant::error_ref );
    }

    std::vector<double> frontiers;
    // Evaluate second parameter and fill bins-array of frontiers.
    if ( parameters[1].i_type() == interpreter_variant::type_range ) {
        range_reference& rref = range_reference_cast( parameters[1].reference() );
        sparse_range_array sra( rref, parameters.context() );
        size_t imax = sra.size();
        for ( unsigned int i = 0; i < imax; i++ ) {
            if ( sra[i].type() == variant::type_double ) {
                frontiers.push_back( sra[i].numeric() );
            }
        }
    } else if ( parameters[1].type() == variant::type_array ) {
        const variant::sparse_array_type& arrBins = parameters[1].array();
        size_t arraySize = arrBins.size();
        for ( size_t i = 0; i < arraySize; i++ ) {
            if ( arrBins[i].type() == variant::type_double ) {
                frontiers.push_back( arrBins[i].numeric() );
            }
        }
    } else {
        if ( parameters[1].type() == variant::type_error ) {
            return parameters[1];
        }

        if ( parameters[1].type() != variant::type_double ) {
            return interpreter_variant( variant::error_value );
        }
        frontiers.push_back( parameters[1].numeric() );
    }
    std::vector<double> sorted( frontiers );
    std::sort( sorted.begin(), sorted.end() ); // upwards
    std::vector<bool> got;
    for ( size_t i = 0; i < frontiers.size(); i++ ) {
        got.push_back( false );
    }
    std::vector<double> lowerFrontiers;
    // Set correlated lowerFrontiers.
    for ( size_t i = 0; i < frontiers.size(); i++ ) {
        for ( size_t j = 0; j < sorted.size(); j++ ) {
            if ( sorted[j] == frontiers[i] && !got[j] ) {
                got[j] = true;
                if ( j == 0 ) {
                    lowerFrontiers.push_back( -std::numeric_limits<double>::max() );
                } else {
                    lowerFrontiers.push_back( sorted[j-1] );
                }
            }
        }
    }
    frontiers.push_back( std::numeric_limits<double>::max() );
    lowerFrontiers.push_back( sorted[sorted.size() - 1] );
    std::vector<int> counter;
    for ( size_t i = 0; i < frontiers.size(); i++ ) {
        counter.push_back( 0 );
    }
    // Count data from first parameter.
    if ( parameters[0].i_type() == interpreter_variant::type_range ) {
        range_reference& rref0 = range_reference_cast( parameters[0].reference() );
        sparse_range_array sra0( rref0, parameters.context() );
        size_t imax0 = sra0.size();
        for ( unsigned int i = 0; i < imax0; i++ ) {
            variant vali = sra0[i];
            if ( vali.type() == variant::type_error ) {
                return interpreter_variant( vali );
            }

            if ( vali.type() == variant::type_double ) {
                for ( size_t i = 0; i < frontiers.size(); i++ ) {
                    if ( lowerFrontiers[i] < vali.numeric() && vali.numeric() <= frontiers[i] ) {
                        counter[i]++;
                        break;
                    }
                }
            }
        }
    } else if ( parameters[0].type() == variant::type_array ) {
        const variant::sparse_array_type& arrData = parameters[0].array();
        size_t arraySize = arrData.size();
        for ( size_t i = 0; i < arraySize; i++ ) {
            variant vali = arrData[i];
            if ( vali.type() == variant::type_error ) {
                return interpreter_variant( vali );
            }

            if ( vali.type() == variant::type_double ) {
                for ( size_t i = 0; i < frontiers.size(); i++ ) {
                    if ( lowerFrontiers[i] < vali.numeric() && vali.numeric() <= frontiers[i] ) {
                        counter[i]++;
                        break;
                    }
                }
            }
        }
    } else {
        if ( parameters[0].type() == variant::type_error ) {
            return parameters[0];
        }

        if ( parameters[0].type() != variant::type_double ) {
            return interpreter_variant( variant::error_value );
        }
        for ( size_t i = 0; i < frontiers.size(); i++ ) {
            if ( lowerFrontiers[i] < parameters[0].numeric() && parameters[0].numeric() <= frontiers[i] ) {
                counter[i]++;
                break;
            }
        }
    }
    // Fill return-array.
    if ( parameters.context().has_array_return_type() ) {
        sheet_range arrayCoverage = parameters.context().caller()->array_coverage();
        unsigned int rowCount = arrayCoverage.row_count();
        unsigned int columnCount = arrayCoverage.column_count();
        unsigned int arraySize = arrayCoverage.count();
        variant::sparse_array_type resultArray( arraySize );
        variant res;
        for ( unsigned int rowi = 0; rowi < rowCount; rowi++ ) {
            if ( rowi < counter.size() ) {
                res = variant( static_cast<double>( counter[rowi] ) );
            } else {
                res = variant::error_n_a;
            }
            for ( unsigned int coli = 0; coli < columnCount; coli++ ) {
                resultArray.push_back( res );
            }
        }
        variant result( resultArray, columnCount );
        return interpreter_variant( result );
    }
    variant::sparse_array_type resultArray;

    for ( std::vector<int>::const_iterator it = counter.begin(); it != counter.end(); it++ ) {
        resultArray.push_back( variant ( static_cast<double> ( *it ) ) );
    }

    return interpreter_variant( variant( resultArray ) );
}
