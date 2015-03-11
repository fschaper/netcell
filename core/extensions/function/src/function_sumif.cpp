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
 * Adds the cells specified by a given criteria.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the sum of the cells specified by the criteria
 *
 * \details
 * Use criteria in the form of a number, expression, or text that defines which cells will be added.
 * For example, criteria can be expressed as 32, "32", ">32", "apples".
 *
 * \see
 * function_countif | function_if | function_sum
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 * Radu Racariu <radu@yalos-solutions.com>
 */
interpreter_variant function_sumif( function_parameter& parameters )
{
    if ( parameters.count() < 2 || parameters.count() > 3 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }
    // If the first parameter is no range, SUMIF returns the #VALUE! error value.
    if ( parameters[0].i_type() != interpreter_variant::type_range ) {
        return interpreter_variant( variant::error_value );
    }

    // If "sum_range" is empty, then "sum_range" corresponds "criteria"
    interpreter_variant addthis = interpreter_variant( variant( "" ) );
    if ( parameters.count() < 3 ) {
        addthis = parameters[0];
    } else {
        addthis = parameters[2];
    }

    // If a number is given, convert into String
    if ( parameters[1].type() == variant::type_double ) {
        std::stringstream ssStream;
        ssStream << parameters[1].numeric();
        interpreter_variant newVal = interpreter_variant( variant( ssStream.str() ) );
        parameters[1] = newVal;
    }

    // Comparison method, always assuming String
    int compareMethod = 0;
    double lookfor = 0;
    if ( parameters[1].type() == variant::type_string ) {
        // Smaller
        if ( ( parameters[1].string() ).substr( 0, 1 ) == "<" ) {
            compareMethod = 1;
            std::stringstream ssStream( ( parameters[1].string() ).substr( 1 ) );
            ssStream >> lookfor;
        }
        // Greater
        else if ( ( parameters[1].string() ).substr( 0, 1 ) == ">" ) {
            compareMethod = 2;
            std::stringstream ssStream( ( parameters[1].string() ).substr( 1 ) );
            ssStream >> lookfor;
        }
        // Equal
        else if ( ( parameters[1].string() ).substr( 0, 1 ) == "=" ) {
            compareMethod = 3;
            std::stringstream ssStream( ( parameters[1].string() ).substr( 1 ) );
            ssStream >> lookfor;
        } else {
            std::stringstream ssStream( ( parameters[1].string() ) );
            ssStream >> lookfor;
        }
    } else {
        return interpreter_variant( variant::error_value );
    }

    double result = 0;
    range_reference& rref1 = range_reference_cast( parameters[0].reference() );
    sparse_range_array sra1( rref1, parameters.context() );
    unsigned int imax1 = rref1.actualize().position().count();
    range_reference& rref2 = range_reference_cast( addthis.reference() );
    sparse_range_array sra2( rref2, parameters.context() );
    for ( unsigned int i = 0; i < imax1; i++ ) {
        if ( sra1[i].type() == variant::type_double ) {
            if ( compareMethod == 1 && sra1[i].numeric() < lookfor ) {
                result = result + sra2[i].numeric();
            } else if ( compareMethod == 2 && sra1[i].numeric() > lookfor ) {
                result = result + sra2[i].numeric();
            } else if ( ( compareMethod == 3 || compareMethod == 0 ) && sra1[i].numeric() == lookfor ) {
                result = result + sra2[i].numeric();
            }
        }
    }
    return interpreter_variant( variant( result ) );
    // Adds the cells specified by a given criteria.
}
