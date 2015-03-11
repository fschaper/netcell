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
 * Creates a cell address as text, given specified row and column numbers.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the cell address as text
 *
 * \details
 *
 * \see
 * function_column | function_row | function_offset
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 * Radu Racariu <radu@yalos-solutions.com>
 */
interpreter_variant function_address( function_parameter& parameters )
{
    if ( parameters.count() < 2 || parameters.count() > 5 ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    // get parameters
    std::string myString = "";
    int row_num = static_cast<int>( parameters[0].numeric() ); // the row number to use in the cell reference.
    int column_num = static_cast<int>( parameters[1].numeric() ); // the column number to use in the cell reference.
    int abs_num = 1;
    if ( parameters.count() >= 3 && parameters[2].type() != variant::type_empty ) {
        abs_num = static_cast<int>( parameters[2].numeric() ); // specifies the type of reference to return.
    }
    bool a1 = true;
    if ( parameters.count() >= 4 && parameters[3].type() != variant::type_empty ) {
        a1 = parameters[3].numeric() != 0.0; // logical value that specifies the A1 or R1C1 reference style.
        // If a1 is true or omitted, ADDRESS returns an A1-style reference; if false, ADDRESS returns an R1C1-style reference.
    }
    std::string sheet_text = ""; // text specifying the name of the worksheet to be used as the external reference.
    // If sheet_text is omitted, no sheet name is used.
    if ( parameters.count() == 5 ) {
        sheet_text = parameters[4].string();
    }

    // build together
    if ( sheet_text != "" ) {
        myString.append( sheet_text + "!" );
    }

    if ( a1 ) {
        if ( abs_num == 1 || abs_num == 3 ) {
            myString.append( "$" );
        }
        myString.append( a1conversion::to_a1::column( column_num - 1, reference::relative ) );
        if ( abs_num == 1 || abs_num == 2 ) {
            myString.append( "$" );
        }
        myString.append( boost::lexical_cast<std::string>( row_num ) );
    } else {
        myString.append( "R" );
        if ( abs_num == 4 || abs_num == 3 ) {
            myString.append( "[" );
        }
        myString.append( boost::lexical_cast<std::string>( row_num ) );
        if ( abs_num == 4 || abs_num == 3 ) {
            myString.append( "]" );
        }
        myString.append( "C" );
        if ( abs_num == 4 || abs_num == 2 ) {
            myString.append( "[" );
        }
        myString.append( boost::lexical_cast<std::string>( column_num ) );
        if ( abs_num == 4 || abs_num == 2 ) {
            myString.append( "]" );
        }
    }

    return interpreter_variant( variant( myString ) );
    // Creates a cell address as text, given specified row and column numbers.
}
