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
 * Returns the row number of a reference.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the row number
 *
 * \details
 * If reference is a range of cells, and if ROW is entered as a vertical array,
 * ROW returns the row numbers of reference as a vertical array.
 * reference cannot refer to multiple areas.
 *
 * \see
 * function_column | function_rows
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
interpreter_variant function_row( function_parameter& parameters )
{
    if ( parameters.count() > 1 ) {
        // formula-error! We give #REF! until we can give a message-window.
        return interpreter_variant( variant::error_ref );
    }
    // If reference is omitted, it is assumed to be the reference of the cell in which the ROW function appears.
    if ( parameters.count() == 0 ) {
        if ( parameters.context().has_array_return_type() ) {
            sheet_range arrayCoverage = parameters.context().caller()->array_coverage();
            unsigned int rowCount = arrayCoverage.row_count();
            /*unsigned int columnCount = arrayCoverage.get_column_count();
            unsigned int arraySize = arrayCoverage.count();
            variant result( variant::type_array, arraySize, columnCount );
            variant::sparse_array_type& resultArray = result.array();
            for ( unsigned int rowi = 0; rowi < rowCount; rowi++ ) {
            variant rowNumV = variant( static_cast<double>( cx.get_current_cell()->get_position().row() + 1 + rowi ) );
            for ( unsigned int coli = 0; coli < columnCount; coli++ ) {
            resultArray.push_back( rowNumV );
            }
            }*/
            variant::sparse_array_type resultArray( rowCount );
            for ( unsigned int rowi = 0; rowi < rowCount; rowi++ ) {
                variant rowNumV = variant( static_cast<double>( parameters.context().caller()->position().row() + 1 + rowi ) );
                resultArray.push_back( rowNumV );
            }
            variant result( resultArray, 1 );
            return interpreter_variant( result );
        } else {
            return interpreter_variant( static_cast<double>( row_col_helper::initiator( parameters.context() )->position().row() + 1 ) );
        }
    }

    sheet_range coveredRange( sheet_point( 0, 0 ) );
    switch ( parameters[ 0 ].i_type() ) {
        case interpreter_variant::type_range: {
            range_reference& rref = range_reference_cast( parameters[0].reference() );
            coveredRange = rref.actualize().position();
        }
        break;

        default:
            //assert( "invalid parameter" );
            return interpreter_variant( variant::error_ref );
    }

    if ( coveredRange.row_count() == 1 ) {
        variant rowNumV = variant( static_cast<double>( coveredRange.upper_left().row() + 1 ) );
        /*if ( cx.is_array_formula() ) {
        BoundedRect arrayCoverage = cx.get_array_coverage();
        unsigned int rowCount = arrayCoverage.get_row_count();
        unsigned int columnCount = arrayCoverage.get_column_count();
        unsigned int arraySize = arrayCoverage.count();
        variant result( variant::type_array, arraySize, columnCount );
        variant::sparse_array_type& resultArray = result.array();
        for ( unsigned int rowi = 0; rowi < rowCount; rowi++ ) {
        for ( unsigned int coli = 0; coli < columnCount; coli++ ) {
        resultArray.push_back( rowNumV );
        }
        }
        return interpreter_variant( result );
        } else {
        return interpreter_variant( rowNumV );
        }*/
        return interpreter_variant( rowNumV );
    }

    if ( parameters.context().has_array_return_type() ) {
        /*BoundedRect arrayCoverage = cx.get_array_coverage();
        unsigned int rowCount = arrayCoverage.get_row_count();
        unsigned int columnCount = arrayCoverage.get_column_count();
        unsigned int arraySize = arrayCoverage.count();
        variant result( variant::type_array, arraySize, columnCount );
        variant::sparse_array_type& resultArray = result.array();
        for ( unsigned int rowi = 0; rowi < rowCount; rowi++ ) {
        variant rowNumV;
        if ( rowi < coveredRange.get_row_count() ) {
        rowNumV = variant( static_cast<double>( coveredRange.upper_left().row() + 1 + rowi ) );
        } else {
        rowNumV = variant::error_n_a;
        }
        for ( unsigned int coli = 0; coli < columnCount; coli++ ) {
        resultArray.push_back( rowNumV );
        }
        }*/
        unsigned int columnLength = coveredRange.row_count();
        variant::sparse_array_type resultArray( columnLength );
        for ( unsigned int rowi = 0; rowi < columnLength; rowi++ ) {
            variant rowNumV = variant( static_cast<double>( coveredRange.upper_left().row() + 1 + rowi ) );
            resultArray.set( rowi, rowNumV );
        }
        variant result( resultArray, 1 );
        return interpreter_variant( result );
    } else {
        return interpreter_variant( variant( static_cast<double>( coveredRange.upper_left().row() + 1 ) ) );
    }
    // TODO: Choose the right row, when we can handle array formulas.
    // Returns the row number of a reference.
}
