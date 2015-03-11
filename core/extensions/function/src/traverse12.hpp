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
 *  Radu Ialovoi <ialovoi@yalos-solutions.com>
 */

#include "wss/variant.hpp"
#include "wss/function_parameters.hpp"
#include <boost/foreach.hpp>


#include <wss/sparse_range.hpp>
#include <wss/a1conversion.hpp>
#include <wss/syntax.hpp>
#include <wss/range_reference.hpp>


#define foreach BOOST_FOREACH

#pragma once

/*!
 * \brief
 * traverse strategy for statistical functions taht take 2 array/ranges as parameters
 * the arrays/ranges could be of different sizes
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \see
 * function_covar | function_correl | function_rsq | function_slope | function_intercept
 *
 * \author
 *  Vali Nitu <vali@yalos-solutions.com>
 */


template < class T >

variant traverse12( function_parameter& parameters, T& algorithm )
{

    if ( parameters.count() != 2 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return variant( variant::error_n_a );
    }

    interpreter_variant array1 = parameters[0]; // a cell range of values.
    if ( array1.i_type() != interpreter_variant::type_range && array1.type() != variant::type_array ) {
        return variant( variant::error_n_a );
    }

    interpreter_variant array2 = parameters[1]; // another cell range of values.
    if ( array2.i_type() != interpreter_variant::type_range && array2.type() != variant::type_array ) {
        return variant( variant::error_n_a );
    }

    variant::sparse_array_type arrx, arry;
    size_t arrayxSize;
    size_t arrayySize;
    if ( array1.i_type() == interpreter_variant::type_range ) { // TODO: sparse
        range_reference& rref1 = range_reference_cast( array1.reference() );
        sparse_range_array sra1( rref1, parameters.context() );
        size_t imax1 = sra1.size();
        arrx = variant::sparse_array_type( imax1 );
        for ( unsigned i1 = 0; i1 < imax1; i1++ ) {
            arrx[i1] = sra1[i1];
        }
    } else {
        arrx = array1.array();
    }

    arrayxSize = arrx.size();

    if ( array2.i_type() == interpreter_variant::type_range ) { // TODO: sparse
        range_reference& rref2 = range_reference_cast( array2.reference() );
        sparse_range_array sra2( rref2, parameters.context() );
        size_t imax2 = sra2.size();
        arry = variant::sparse_array_type( imax2 );
        for ( unsigned int i2 = 0; i2 < imax2; i2++ ) {
            arry[i2] = sra2[i2];
        }
    } else {
        arry = array2.array();
    }

    arrayySize = arry.size();
    // If array1 or array2 have a number of data points less than 2 return the #N/A error value.
    if ( arrayxSize < 2 || arrayySize < 2 ) {
        return variant( variant::error_div_null );
    }

    size_t arraySize = arrayxSize > arrayySize ? arrayxSize : arrayySize;

    for ( unsigned long int i = 0; i < arraySize; i++ ) {
        variant xi = i >= arrayxSize ? variant() : arrx[i];
        variant yi = i >= arrayySize ? variant() : arry[i];
        // error values cause errors.
        if ( xi.type() == variant::type_error ) {
            return variant( xi );
        }

        if ( yi.type() == variant::type_error ) {
            return variant( yi );
        }

        // If any array or reference argument contains empty cells, logical values, or text, those value-pairs are ignored.
        //if ( xi.type() == variant::type_double && yi.type() == variant::type_double ) {

        algorithm( xi, yi );
        //}
    }

    return algorithm;
}

