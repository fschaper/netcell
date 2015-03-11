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

#include <boost/scoped_array.hpp>

/*!
* \brief
* evaluates the unicity of the parameters in an array.
*
* ISUNIQUE( ARRAY );
*
* \param function_parameter& parameters
* container of parameters and context which holds information about the current calculation state
*
* \param base_node& n
* AST presentation of the formula currently being calculated.
*
* \returns
* an array of bool the same size of input depicting the non-unicity
*
* \details
*
*
* \see
* function_isunique
*
* \author
* Radu Ialovoi <ialovoi@yalos-solutions.com>
*/
interpreter_variant function_isduplicate( function_parameter& parameters )
{
    if ( 1 != parameters.count() ) {
        // formula-error! We give #N/A until we can give a message-window.
        return interpreter_variant( variant::error_n_a );
    }

    if ( variant::type_array == parameters[0].type() ) {

        const variant::sparse_array_type::mapping_type& array = parameters[0].array().direct();
        size_t          count = array.size();
        variant::sparse_array_type     resultArray( parameters[0].array().size(), false );

        boost::scoped_array<bool> markers( new bool[ count ] );
        for ( size_t i = 0; i < count; i++ ) {
            *( markers.get() + i ) = false;
        }

        size_t pos1 = static_cast< size_t >( -1 );
        for ( variant::sparse_array_type::mapping_type::const_iterator i = array.begin(), e = array.end(); i != e; ++i ) {
            ++pos1;
            if ( *( markers.get() + pos1 ) ) {
                continue;
            }
            bool found = false;
            size_t pos2 = pos1;
            variant::sparse_array_type::mapping_type::const_iterator j = i;
            ++j;
            for ( ; j != e; ++j ) {
                ++pos2;
                if ( i->second == j->second ) {
                    found = true;
                    *( markers.get() + pos2 ) = true;
                    resultArray.set( j->first, variant( true ) );
                }
            }

            if ( found ) {
                resultArray.set( i->first, variant( found ) );
            }
        }

        return interpreter_variant( variant( resultArray ) );
        // Generates an array of logical variants that states the non-unicity of individual iterm in the input.
    }

    return interpreter_variant( false );
}

