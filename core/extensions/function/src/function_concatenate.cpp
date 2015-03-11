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
#include <boost/foreach.hpp>
#include <limits>
#define foreach BOOST_FOREACH

/*!
 * \brief
 * Joins several text strings into one text string.
 *
 * \param function_parameter& parameters
 * container of parameters and context which holds information about the current calculation state
 *
 * \param base_node& n
 * AST presentation of the formula currently being calculated.
 *
 * \returns
 * the joined text string
 *
 * \see
 * function_rept
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 * Matthias Roy <matthias.roy@jedox.com>
 */
interpreter_variant function_concatenate( function_parameter& parameters )
{
    interpreter_variant result( variant( "" ) );
    std::string res = result.as_string( parameters.context().locale() );
    for ( size_t i = 0; i < parameters.count(); i++ ) {
        interpreter_variant current = parameters[i];
        switch ( current.type() ) {
            case variant::type_empty:
                //assert( false );
                continue;
                break;

            case variant::type_double:
                res.append( boost::lexical_cast<std::string>( current.numeric() ) );
                break;

            case variant::type_bool:
                res.append( current.numeric() > 0 ? "TRUE" : "FALSE" );
                break;

            case variant::type_error:
                return current;
                //assert( false );

            case variant::type_string:
                res.append( current.string() );
                break;

            case variant::type_array:
                //assert( false );
            {
                const variant::sparse_array_type& arr = current.array();
                switch ( static_cast<const variant&>( arr[0] ).type() ) {
                    case variant::type_double:
                        res.append( boost::lexical_cast<std::string>( static_cast<const variant&>( arr[0] ).numeric() ) );
                        break;
                    case variant::type_bool:
                        res.append( static_cast<const variant&>( arr[0] ).numeric() > 0 ? "TRUE" : "FALSE" );
                        break;
                    case variant::type_error:
                        return interpreter_variant( arr[0] );
                    case variant::type_string:
                        res.append( static_cast<const variant&>( arr[0] ).string() );
                        break;
                    default:
                        continue;
                        break;
                }
            }
            break;

            default:
                continue;
                break;
        }
    }
    return interpreter_variant( variant( res ) );

}
