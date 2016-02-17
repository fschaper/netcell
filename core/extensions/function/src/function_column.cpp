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
#include "function_helper.hpp"

/*!
 * \brief
 * Returns the column number of the given reference.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the column number
 *
 * \details
 * If reference is a range of cells, and if COLUMN is entered as a horizontal array,
 * COLUMN returns the column numbers of reference as a horizontal array.
 * reference cannot refer to multiple areas.
 *
 * \see
 * function_row | function_columns
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
interpreter_variant function_column( function_parameter& parameters )
{
    if ( parameters.count() > 1 ) {
        // formula-error! We give #REF! until we can give a message-window.
        return interpreter_variant( variant::error_ref );
    }
    // If reference is omitted, it is assumed to be the reference of the cell in which the COLUMN function appears.
    if ( parameters.count() == 0 ) {
        if ( parameters.context().has_array_return_type() ) {
            sheet_range arrayCoverage = parameters.context().caller()->array_coverage();
            //unsigned int rowCount = arrayCoverage.get_row_count();
            unsigned int columnCount = arrayCoverage.column_count();
            /*unsigned int arraySize = arrayCoverage.count();
            variant result( variant::type_array, arraySize, columnCount );
            variant::sparse_array_type& resultArray = result.array();
            for ( unsigned int rowi = 0; rowi < rowCount; rowi++ ) {
            for ( unsigned int coli = 0; coli < columnCount; coli++ ) {
            variant colNumV = variant( static_cast<double>( cx.get_current_cell()->get_position().column() + 1 + coli ) );
            resultArray.push_back( colNumV );
            }
            }*/
            variant::sparse_array_type resultArray( columnCount );
            for ( unsigned int coli = 0; coli < columnCount; coli++ ) {
                variant colNumV = variant( static_cast<double>( parameters.context().caller()->position().column() + 1 + coli ) );
                resultArray.push_back( colNumV );
            }
            variant result( resultArray, columnCount );
            return interpreter_variant( result );
        } else {
            return interpreter_variant( variant( static_cast<double>( row_col_helper::initiator( parameters.context() )->position().column() + 1 ) ) );
        }
    }

    //range& coveredRange = *static_cast<range*>( parameters[0].reference() );
    sheet_range coveredRange( sheet_point( 0, 0 ) );
    switch ( parameters[0].i_type() ) {
        case interpreter_variant::type_range: {
            range_reference& rrefr = range_reference_cast( parameters[0].reference() );
            coveredRange = rrefr.actualize().position();
        }
        break;
        default:
            //assert( "invalid parameter" );
            return interpreter_variant( variant::error_ref );
    }

    if ( coveredRange.column_count() == 1 ) {
        variant colNumV = variant( static_cast<double>( coveredRange.upper_left().column() + 1 ) );
        /*if ( cx.is_array_formula() ) {
        BoundedRect arrayCoverage = cx.get_array_coverage();
        unsigned int rowCount = arrayCoverage.get_row_count();
        unsigned int columnCount = arrayCoverage.get_column_count();
        unsigned int arraySize = arrayCoverage.count();
        variant result( variant::type_array, arraySize, columnCount );
        variant::sparse_array_type& resultArray = result.array();
        for ( unsigned int rowi = 0; rowi < rowCount; rowi++ ) {
        for ( unsigned int coli = 0; coli < columnCount; coli++ ) {
        resultArray.push_back( colNumV );
        }
        }
        return interpreter_variant( result );
        } else {
        return interpreter_variant( colNumV );
        }*/
        return interpreter_variant( colNumV );
    }

    if ( parameters.context().has_array_return_type() ) {
        /*BoundedRect arrayCoverage = cx.get_array_coverage();
        unsigned int rowCount = arrayCoverage.get_row_count();
        unsigned int columnCount = arrayCoverage.get_column_count();
        unsigned int arraySize = arrayCoverage.count();
        variant result( variant::type_array, arraySize, columnCount );
        variant::sparse_array_type& resultArray = result.array();
        for ( unsigned int rowi = 0; rowi < rowCount; rowi++ ) {
        for ( unsigned int coli = 0; coli < columnCount; coli++ ) {
        variant colNumV;
        if ( coli < coveredRange.get_column_count() ) {
        colNumV = variant( static_cast<double>( coveredRange.upper_left().column() + 1 + coli ) );
        } else {
        colNumV = variant::error_n_a;
        }
        resultArray.push_back( colNumV );
        }
        }*/
        unsigned int rowLength = coveredRange.column_count();
        variant::sparse_array_type resultArray( rowLength );
        for ( unsigned int coli = 0; coli < rowLength; coli++ ) {
            variant colNumV = variant( static_cast<double>( coveredRange.upper_left().column() + 1 + coli ) );
            resultArray.set( coli, colNumV );
        }
        variant result( resultArray, rowLength );
        return interpreter_variant( result );
    } else {
        return interpreter_variant( variant( static_cast<double>( coveredRange.upper_left().column() + 1 ) ) );
    }
    // TODO: Choose the right column, when we can handle array formulas.
    // Returns the column number of the given reference.
}
