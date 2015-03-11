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
*  Frieder Hofmann <frieder.hofmann@jedox.com>
*/

#include "precompiled_header.hpp"
#include <boost/foreach.hpp>
#include <wss/non_instantiable.hpp>

#define foreach BOOST_FOREACH

struct between_helper : public non_instantiable {
    static inline bool compare( const variant& p0, const variant& p1, const variant& p2 ) {
        return ( ( p0 <= p1 && p1 <= p2 ) || ( p2 <= p1 && p1 <= p0 ) );
    }

    static inline interpreter_variant compare( const variant& p0, const variant::sparse_array_type& p1_array, const variant& p2 ) {
        variant::sparse_array_type::mapping_type::const_iterator it( p1_array.direct().begin() ), end_it( p1_array.direct().end() );
        variant::sparse_array_type return_array( true );
        return_array.resize( p1_array.size() );

        for ( ; it != end_it; ++it ) {
            return_array.set( it->first, between_helper::compare( p0, it->second, p2 ) );
        }
        return interpreter_variant( variant( return_array ) );
    }

    static inline interpreter_variant compare( const variant::sparse_array_type& p0_array, const variant::sparse_array_type& p1_array, const variant& p2 ) {
        variant::sparse_array_type::mapping_type::const_iterator it( p1_array.direct().begin() ), end_it( p1_array.direct().end() );
        variant::sparse_array_type return_array( true );
        return_array.resize( p1_array.size() );

        for ( ; it != end_it; ++it ) {
            return_array.set( it->first, between_helper::compare( p0_array[it->first], it->second, p2 ) );
        }
        return interpreter_variant( variant( return_array ) );
    }

    static inline interpreter_variant compare( const variant& p0, const variant::sparse_array_type& p1_array, const variant::sparse_array_type& p2_array ) {
        return compare( p2_array, p1_array, p0 );
    }

    static inline interpreter_variant compare( const variant::sparse_array_type& p0_array, const variant::sparse_array_type& p1_array, const variant::sparse_array_type& p2_array ) {
        variant::sparse_array_type::mapping_type::const_iterator it( p1_array.direct().begin() ), end_it( p1_array.direct().end() );
        variant::sparse_array_type return_array( true );
        return_array.resize( p1_array.size() );

        for ( ; it != end_it; ++it ) {
            return_array.set( it->first, between_helper::compare( p0_array[it->first], it->second, p2_array[it->first] ) );
        }
        return interpreter_variant( variant( return_array ) );
    }

};

/*!
* \brief
* returns true if param 2 is between params 1 and 3 (works on arrays also)
*
* \param function_parameter& parameters
* container of parameters and context which holds information about the current calculation state
*
* \author
* Frieder Hofmann <frieder.hofmann@jedox.com>
*/
interpreter_variant function_between( function_parameter& parameters )
{
    if ( parameters.count() == 3 ) {
        if ( variant::type_array == parameters[1].type() ) {
            if ( variant::type_array == parameters[0].type() ) {

                if ( variant::type_array == parameters[2].type() ) {
                    return between_helper::compare(
                               parameters[0].array(),
                               parameters[1].array(),
                               parameters[2].array()
                           );
                } else {
                    return between_helper::compare(
                               parameters[0].array(),
                               parameters[1].array(),
                               parameters[2]
                           );
                }
            } else {
                if ( variant::type_array == parameters[2].type() ) {
                    return between_helper::compare(
                               parameters[0],
                               parameters[1].array(),
                               parameters[2].array()
                           );
                } else {
                    return between_helper::compare(
                               parameters[0],
                               parameters[1].array(),
                               parameters[2]
                           );
                }
            }
        } else if ( variant::type_array != parameters[0].type() && variant::type_array != parameters[2].type() ) {
            return interpreter_variant( variant( between_helper::compare( parameters[0], parameters[1], parameters[2] ) ) );
        }
    }
    return interpreter_variant( variant::error_value );
}
